#include "Lidar360.h"

Lidar360::Lidar360(float maxSpeed, int btnA, int btnB, int motorSleep, int lidarEn, AccelStepper &mtr, HardwareSerial  &print, LiquidCrystal &lcd)
{
    _print = &print;
    _lcd = &lcd;

    _motor = &mtr;
    _maxSpeed = maxSpeed;
    _motor->setMaxSpeed(_maxSpeed);

    _buttonA = btnA;
    _buttonB = btnB;

    _motorSleep = motorSleep;
    _lidarModuleEn = lidarEn;

    /* Set the buttons to input mode with a pullup resistor */
    pinMode(_buttonA, INPUT_PULLUP);
    pinMode(_buttonB, INPUT_PULLUP);

    /* Set up the motorSleep and lidarEn pin for sending output */
    pinMode(_motorSleep, OUTPUT);
    pinMode(_lidarModuleEn, OUTPUT);

    /* Power down the motor to save power */
    powerDownMotor();

    /* Init the number of readings in the array readings */
    _numSweepReadings = 0;

    /* Init the lidar module it self */
    initLidar();

    /* Now Lidar module is up - check the output to see if we need a reset */
    verifyLidarOutput();

    /* Finally wait for the Lidar to be set to the zero position */
    zeroStepperMotor();
}

void Lidar360::testHarness()
{
    performSweepScan(10, 3);

    for (int i = 0; i < _numSweepReadings; i++)
    {
        _print->print("Num: "); _print->print(i);
        _print->print(" Heading: "); _print->print(sweepReadings[i].heading);
        _print->print(" Dist: "); _print->println(sweepReadings[i].distance);
    }
}

void Lidar360::getDistanceAtHeading(int heading, char* responseBuffer, int buffSize)
{
    char tempBuff[10];
    const int base = 10;

    if(NULL != responseBuffer)
    {
        memset(responseBuffer, 0, buffSize);
    }

    /* Convert the heaading to a nuber of steps to take */
    int numSteps = angleToApproxSteps(heading);

    /* Spin the Lidar to the heading */
    powerUpMotor();
    stepToRelativePosition(numSteps);

    /* Take a distance reading at that angle and store it */
    powerUpLidar();
    int distanceRead = llGetDistanceAverage(NUM_READS_FOR_AVERAGE);
    powerDownLidar();

    if (NULL != responseBuffer)
    {
        memset(tempBuff, 0, sizeof(tempBuff));

        // convert distance to string place it in the tempBuff, then cpy to responseBuffer
        itoa(distanceRead, tempBuff, base);
        strncpy(responseBuffer, tempBuff, strlen(tempBuff));

        // append a seperator between the distance reading and steps taken
        strncat(responseBuffer, ",", 1);
        memset(tempBuff, 0, sizeof(tempBuff));

        // append the number of steps taken to reach target heading
        itoa(numSteps, tempBuff, base);
        strncat(responseBuffer, tempBuff, strlen(tempBuff));

        // append terminition character to the responseBuffer
        strncat(responseBuffer,";" , 1);
    }

    /* Return the motor to the zero position */
    stepToZeroPosition();
    powerDownMotor();
}

void Lidar360::performSweepScan(const int sampleInterval, const int numReadingsToTake)
{
    bool reachedTarget = false;
    long currPos = 0;

    // Reset the number of sweep readings to zero as we are taking a new sweep
    _numSweepReadings = 0;

    // Power up the motor and the lidar module
    powerUpLidar();
    powerUpMotor();

    // Begin sweep at the zero position
    stepToZeroPosition();

    // Prepare the display
    _lcd->clear();
    _lcd->setCursor(0,0);
    _lcd->print("DO:Sweep Scan");

    _motor->move(STEPS_PER_REVOLUTION);
    _motor->setSpeed(_maxSpeed);

    while(!reachedTarget)
    {
        if(_motor->targetPosition() != _motor->currentPosition())
        {
            _motor->runSpeedToPosition();
        }
        else
        {
            reachedTarget = true;
        }

        /* Take a reading on the step interval specified by sampleInterval */
        currPos = _motor->currentPosition();
        if (0 == (currPos % sampleInterval))
        {
            /* We store the reading and heading of the reading */
            sweepReadings[_numSweepReadings].distance = llGetDistanceAverage(numReadingsToTake);
            sweepReadings[_numSweepReadings].heading = stepsToApproxAngle(currPos);
            _numSweepReadings++;
        }
    }

    // Power down the motor and the lidar modules
    powerDownMotor();
    powerDownLidar();

    _lcd->clear();
    _lcd->setCursor(0,0);
    _lcd->print("DONE:Sweep Scan");
}

void Lidar360::zeroStepperMotor()
{
    /* Print message to lcd */
    _lcd->clear();
    _lcd->setCursor(0,0);
    _lcd->print("Pls zero Lidar");
    _lcd->setCursor(0,1);
    _lcd->print("Then press A btn");

    /* Power up the motor before moving */
    powerUpMotor();

    bool reachedZero = false;

    _motor->setSpeed(LIDAR_MANUAL_ZERO_SPEED);

    while(!reachedZero)
    {
        /* If button B is pressed move a step */
        if (digitalRead(_buttonB) == LOW)
        {
            _motor->runSpeed();
        }
        /* If button A is pressed ,the Lidar has been zeroed */
        else if (digitalRead(_buttonA) == LOW)
        {
            _motor->setCurrentPosition(0);
            reachedZero = true;
        }
    }

    /* Show message to signal end of lidar zeroing */
    _lcd->clear();
    _lcd->setCursor(0,0);
    _lcd->print("Zero positon set");

    /* Power down the motor now we have finished zeroing */
    powerDownMotor();
    delay(LIDAR_BUTTON_PRESS_DELAY);
}

void Lidar360::stepToRelativePosition(long steps)
{
    bool reachedTarget = false;
    const int stepsPerRev = STEPS_PER_REVOLUTION;
    const int stepSpeed = _maxSpeed;

    /* Modulo to wrap the number steps to set in stepsPerRev */
    steps %= stepsPerRev;

    _motor->move(steps);
    _motor->setSpeed(stepSpeed);

    while(!reachedTarget)
    {
        if(_motor->targetPosition() != _motor->currentPosition())
        {
            _motor->runSpeedToPosition();
        }
        else
        {
            reachedTarget = true;
        }
    }
}

void Lidar360::stepToZeroPosition ()
{
    bool reachedZeroPosition = false;
    const int stepsPerRev = STEPS_PER_REVOLUTION;
    const int stepSpeed = _maxSpeed;

    // Wrap the current position to 0 - 700 using modulo
    int pos = (_motor->currentPosition() % stepsPerRev);

    // Subtract the wrapper position (modulo to handle case when pos == 700)
    // to find out how many steps to reach the zero pos
    int remain = (stepsPerRev - pos) % stepsPerRev;

    // Return to zero positon
    _motor->move(remain);
    _motor->setSpeed(stepSpeed);

    while(!reachedZeroPosition)
    {
        if(_motor->targetPosition() != _motor->currentPosition())
        {
            _motor->runSpeedToPosition();
        }
        else
        {
            reachedZeroPosition = true;
        }
    }
    _motor->setCurrentPosition(0);
}

void Lidar360::powerDownMotor()
{
    /* Set sleep pin to LOW to sleep motor */
    digitalWrite(_motorSleep, LOW);
}

void Lidar360::powerUpMotor()
{
    /* Set sleep pin to HIGH to wake motor */
    digitalWrite(_motorSleep, HIGH);
    delay(LIDAR_MOTOR_POWER_DELAY);
}

void Lidar360::initLidar()
{
    /* First power up the module by pulling enable pin HIGH */
    digitalWrite(_lidarModuleEn, HIGH);

    // Opens & joins the irc bus as master
    I2c.begin();

    // Waits to make sure everything is powered up before sending or receiving data
    delay(LIDAR_MODULE_POWER_DELAY);

    // Sets a timeout to ensure no locking up of sketch if I2C communication fails
    I2c.timeOut(50);

     // reset device to defaults for distance measurment
    llWriteAndWait(0x00, 0x00);

    powerDownLidar();
}

void Lidar360::verifyLidarOutput()
{
    bool keepLooping = true;
    bool flipFlag = false;
    unsigned long currTime = 0;
    unsigned long prevTime = 0;
    const int interval = 2000;

    powerUpLidar();

    _lcd->clear();
    _lcd->setCursor(0,1);
    _lcd->print("Dist: ");
    while(keepLooping)
    {
        /* Print the first message on the top line  - switch it every time interval expires */
        currTime = millis();
        if((currTime - prevTime) > interval)
        {
            prevTime = currTime;
            _lcd->setCursor(0,0);
            (false == flipFlag) ? _lcd->print("Check lidar data") : _lcd->print("Press A to cont ");
            flipFlag = !flipFlag;
        }

        /* Print the measurement and wait for user button press */
        _lcd->setCursor(6,1);
        _lcd->print(llGetDistanceAverage(3));
        _lcd->print("   ");

        /* If button A is pressed, move on to zeroing the lidar */
        if (digitalRead(_buttonA) == LOW)
        {
            keepLooping = false;
        }
    }

    _lcd->clear();
    _lcd->setCursor(0,0);
    _lcd->print("Btn Pressed!");
    powerDownLidar();

    /* Delay to allow user to remove finger from button */
    delay(LIDAR_BUTTON_PRESS_DELAY);
}

void Lidar360::setLidarOffSet(int offSet)
{

}

void Lidar360::powerDownLidar()
{
    /* Power down the module by pulling enable pin LOW */
    digitalWrite(_lidarModuleEn, LOW);
}

void Lidar360::powerUpLidar()
{
    /* Power up the module by pulling enable pin HIGH */
    digitalWrite(_lidarModuleEn, HIGH);

    /* Wait for device power up, then reset device to defaults */
    delay(LIDAR_MODULE_POWER_DELAY);
    llWriteAndWait(0x00, 0x00);
}

// Write a register and wait until it responds with success
void Lidar360::llWriteAndWait(char myAddress, char myValue)
{
    uint8_t nackack = 100; // Setup variable to hold ACK/NACK resopnses

    while (nackack != 0)
    { // While NACK keep going (i.e. continue polling until sucess message (ACK) is received )
      nackack = I2c.write(LIDAR_LITE_ADDRESS,myAddress, myValue); // Write to LIDAR-Lite Address with Value
      delay(2); // Wait 2 ms to prevent overpolling
    }
}

byte Lidar360::llReadAndWait(char myAddress, int numOfBytes, byte arrayToSave[2])
{
    uint8_t nackack = 100; // Setup variable to hold ACK/NACK resopnses

    while (nackack != 0)
    { // While NACK keep going (i.e. continue polling until sucess message (ACK) is received )
      nackack = I2c.read(LIDAR_LITE_ADDRESS,myAddress, numOfBytes, arrayToSave); // Read 1-2 Bytes from LIDAR-Lite Address and store in array
      delay(2); // Wait 2 ms to prevent overpolling
    }
    return arrayToSave[2]; // Return array for use in other functions
}

/* ==========================================================================================================================================
Get 2-byte distance from sensor and combine into single 16-bit int
=============================================================================================================================================*/
int Lidar360::llGetDistance()
{
    byte myArray[2]; // array to store bytes from read function
    int distance;

    llWriteAndWait(0x00,0x04); // Write 0x04 to register 0x00 to start getting distance readings
    llReadAndWait(0x8f,2,myArray); // Read 2 bytes from 0x8f
    distance = (myArray[0] << 8) + myArray[1];  // Shift high byte [0] 8 to the left and add low byte [1] to create 16-bit int
    return distance;
}

/* ==========================================================================================================================================
Average readings from velocity and distance
int numberOfReadings - the number of readings you want to average (0-9 are possible, 2-9 are reccomended)
=============================================================================================================================================*/
int Lidar360::llGetDistanceAverage(int numberOfReadings)
{
    int sum = 0; // Variable to store sum

    if(numberOfReadings < 2)
    {
      numberOfReadings = 2; // If the number of readings to be taken is less than 2, default to 2 readings
    }

    for(int i = 0; i < numberOfReadings; i++)
    {
        sum = sum + llGetDistance(); // Add up all of the readings
    }
    sum = sum/numberOfReadings; // Divide the total by the number of readings to get the average
    return sum;
}

/* Convert a given angle to the number of steps to take from zero to reach siad angle */
long Lidar360::angleToApproxSteps(int angle)
{
    return lroundf((angle * STEPS_PER_REVOLUTION) / 360);
}

/* Convert the current position of the motor to an angular representation within 0 - 360 */
float Lidar360::stepsToApproxAngle(int stepPos)
{
    return (float(stepPos) / STEPS_PER_REVOLUTION) * 360.0;
}
