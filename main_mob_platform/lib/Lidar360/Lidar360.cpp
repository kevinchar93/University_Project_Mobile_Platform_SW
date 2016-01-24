#include "Lidar360.h"

Lidar360::Lidar360(AccelStepper &mtr, float maxSpeed, int btnA, int btnB, HardwareSerial  &print, LiquidCrystal &lcd)
{
    _print = &print;
    _lcd = &lcd;

    _motor = &mtr;
    _maxSpeed = maxSpeed;
    _motor->setMaxSpeed(_maxSpeed);

    _buttonA = btnA;
    _buttonB = btnB;

    /* Set the buttons to input mode with a pullup resistor */
    pinMode(_buttonA, INPUT_PULLUP);
    pinMode(_buttonB, INPUT_PULLUP);

    //pinMode(LIDAR_SLEEP, OUTPUT);

    /*  need to set enble pin on the CNC board to low to run stepper drivers */
    // pinMode(LIDAR_EN, OUTPUT);

    /* Init the lidar module it self */
    initLidar();

    /* Now Lidar module is up - check the output to see if we need a reset */
    verifyLidarOutput();

    /* Finally wait for the Lidar to be set to the zero position */
    zeroStepperMotor();

}

void Lidar360::testHarness()
{
    // int angle = 0;
    // int steps = 0;
    // int timer = 3000;
    //
    // for (int i = 0; i <= 360; i+=45)
    // {
    //     angle = i;
    //     steps = angleToApproxSteps(angle);
    //     _lcd->clear();
    //     _lcd->setCursor(0,0);
    //     _lcd->print("Angle: ");
    //     _lcd->print(angle);
    //     _lcd->setCursor(0,1);
    //     _lcd->print("Steps: ");
    //     _lcd->print(steps);
    //     stepToPosition(steps);
    //     delay(timer);
    // }
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

    /* Spin the Lidar to the heaading */
    stepToPosition(numSteps);

    /* Take a distance reading at that angle and store it */
    int distanceRead = llGetDistanceAverage(NUM_READS_FOR_AVERAGE);

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
}

void Lidar360::zeroStepperMotor()
{
    /* Print message to lcd */
    _lcd->clear();
    _lcd->setCursor(0,0);
    _lcd->print("Pls zero Lidar");
    _lcd->setCursor(0,1);
    _lcd->print("Then press A btn");

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
            _motorPosition = 0;
            _motor->setCurrentPosition(_motorPosition);
            reachedZero = true;
        }
    }

    /* Show message to signal end of lidar zeroing */
    _lcd->clear();
    _lcd->setCursor(0,0);
    _lcd->print("Zero positon set");
    delay(3000);
}

void Lidar360::stepToPosition(long pos)
{
    bool reachedTarget = false;

    if (pos > STEPS_PER_REVOLUTION)
        return;

    _motor->moveTo(pos);
    _motor->setSpeed(_maxSpeed);
    _motor->runSpeedToPosition();

    while(!reachedTarget)
    {
        if(_motor->targetPosition() != _motor->currentPosition())
        {
            _motor->runSpeed();
        }
        else
        {
            reachedTarget = true;
        }
    }
}
void Lidar360::powerDownMotor()
{

}

void Lidar360::powerUpMotor()
{

}

void Lidar360::initLidar()
{
    // Opens & joins the irc bus as master
    I2c.begin();

    // Waits to make sure everything is powered up before sending or receiving data
    delay(100);

    // Sets a timeout to ensure no locking up of sketch if I2C communication fails
    I2c.timeOut(50);

     // reset device to defaults for distance measurment
    llWriteAndWait(0x00, 0x00);
}

void Lidar360::verifyLidarOutput()
{
    bool keepLooping = true;
    bool flipFlag = false;
    unsigned long currTime = 0;
    unsigned long prevTime = 0;
    const int interval = 2000;

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

        /* If button A is pressed, move on to zeroing the lidar */
        if (digitalRead(_buttonA) == LOW)
        {
            keepLooping = false;
        }
    }

    /* Delay to allow user to remove finger from button */
    delay(1000);
}

void Lidar360::setLidarOffSet(int offSet)
{

}

void Lidar360::powerDownLidar()
{

}

void Lidar360::powerUpLidar()
{

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

int Lidar360::angleToApproxSteps(int angle)
{
    int val = 0;
    float tempAngle = angle;
    val = tempAngle / (360.0/STEPS_PER_REVOLUTION);
    return val;
}
