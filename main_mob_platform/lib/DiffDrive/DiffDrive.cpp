#include "DiffDrive.h"

void DiffDrive::init(const float maxSpeed, const uint8_t leftMotorSleep, const uint8_t rightMotorSleep, AccelStepper &leftMotor,
                     AccelStepper &rightMotor, HardwareSerial  &print, LiquidCrystal &lcd)
 {
     /* Set the class variables from supplied parameters */
     _print = &print;
     _lcd = &lcd;

     _maxSpeed = maxSpeed;
     _leftMotorSleep = leftMotorSleep;
     _rightMotorSleep = rightMotorSleep;

     pinMode(_leftMotorSleep, OUTPUT);
     pinMode(_rightMotorSleep, OUTPUT);

     _leftMotor = &leftMotor;
     _rightMotor = &rightMotor;

     /* Set motors max speeds and add them to the MultiStepper object */
     _leftMotor->setMaxSpeed(_maxSpeed);
     _rightMotor->setMaxSpeed(_maxSpeed);

     _motorGroup.addStepper(*_leftMotor);
     _motorGroup.addStepper(*_rightMotor);

     /* Put the motors to sleep to save power */
     powerDownMotors();
 }

float DiffDrive::moveForward(const uint16_t distanceMM, const bool gridMode, const uint16_t gridSizeMM)
{
    _print->println("begin moveForward");

    float actualTravelDist = 0;
    uint32_t distToTravelMM = 0;
    int32_t numStepsToTake = 0;
    bool reachedTargetPosition = false;
    int32_t targetPositions [DD_NUMBER_OF_DRIVE_MOTORS];

    /* Print message to lcd */
    _lcd->clear();
    _lcd->setCursor(0,0);
    _lcd->print("FWD,GM:");_lcd->print(gridMode? "T," : "F,");_lcd->print(gridMode? gridSizeMM : 0);
    _lcd->setCursor(0,1);
    _lcd->print("Dist:");_lcd->print(distanceMM);
    delay(1000);

    const float distTravelledPerStepMM = DD_WHEEL_CIRCUMFERENCE_MM / DD_STEPS_PER_WHEEL_REV;
    _print->print("distTravelledPerStepMM: ");_print->println(distTravelledPerStepMM);

    /* In grid mode, the distanceMM represents the ammount of grid spaces to move,
       Other wise it represets an explicit distance to travel in millimeters */
    distToTravelMM = gridMode ? (distanceMM * gridSizeMM) : distanceMM;
    _print->print("distToTravelMM: ");_print->println(distToTravelMM);

    /* Calculate approx number of steps to take to reach the target position */
    numStepsToTake = lroundf((float)distToTravelMM / distTravelledPerStepMM);
    _print->print("numStepsToTake: ");_print->println(numStepsToTake);

    /* Calculate the actual distance that the steppers will travel */
    actualTravelDist = numStepsToTake * distTravelledPerStepMM;
    _print->print("actualTravelDist: ");_print->println(actualTravelDist);

    /* Set the target positions for motors in the motor group - going forward straight so both share
       the same target positon and the positon is a positive integer */
    targetPositions[DD_LEFT_MOTOR_POS_INDEX] = numStepsToTake;
    targetPositions[DD_RIGHT_MOTOR_POS_INDEX] = numStepsToTake;

    /* Move the motors to their target positions */
    powerUpMotors();
    _motorGroup.moveTo(targetPositions);

    while(!reachedTargetPosition)
    {
        if (false == _motorGroup.run())
        {
            reachedTargetPosition = true;
            _leftMotor->stop();
            _rightMotor->stop();
            delay(500);
        }
    }

    /* Set the positons of each motor back to zero so we can move them again next call */
    _rightMotor->setCurrentPosition(0);
    _leftMotor->setCurrentPosition(0);
    powerDownMotors();

    /* Print message to lcd */
    _lcd->clear();
    _lcd->setCursor(0,0);
    _lcd->print("Done:Move Fwd");
    delay(1000);

    _print->println("end moveForward");

    return actualTravelDist;
}

float DiffDrive::moveBackward(const uint16_t distanceMM, const bool gridMode, const uint16_t gridSizeMM)
{
    _print->println("begin moveBackward");

    float actualTravelDist = 0;
    uint32_t distToTravelMM = 0;
    int32_t numStepsToTake = 0;
    bool reachedTargetPosition = false;
    int32_t targetPositions [DD_NUMBER_OF_DRIVE_MOTORS];

    /* Print message to lcd */
    _lcd->clear();
    _lcd->setCursor(0,0);
    _lcd->print("BWD,GM:");_lcd->print(gridMode? "T," : "F,");_lcd->print(gridMode? gridSizeMM : 0);
    _lcd->setCursor(0,1);
    _lcd->print("Dist:");_lcd->print(distanceMM);
    delay(1000);

    const float distTravelledPerStepMM = DD_WHEEL_CIRCUMFERENCE_MM / DD_STEPS_PER_WHEEL_REV;
    _print->print("distTravelledPerStepMM: ");_print->println(distTravelledPerStepMM);

    /* In grid mode, the distanceMM represents the ammount of grid spaces to move,
       Other wise it represets an explicit distance to travel in millimeters */
    distToTravelMM = gridMode ? (distanceMM * gridSizeMM) : distanceMM;
    _print->print("distToTravelMM: ");_print->println(distToTravelMM);

    /* Calculate approx number of steps to take to reach the target position */
    numStepsToTake = lroundf((float)distToTravelMM / distTravelledPerStepMM);
    _print->print("numStepsToTake: ");_print->println(numStepsToTake);

    /* Calculate the actual distance that the steppers will travel */
    actualTravelDist = numStepsToTake * distTravelledPerStepMM;
    _print->print("actualTravelDist: ");_print->println(actualTravelDist);

    /* Set the target positions for motors in the motor group - going backward straight so both share
       the same target positon and the positon is a negative integer */
    targetPositions[DD_LEFT_MOTOR_POS_INDEX] = -numStepsToTake;
    targetPositions[DD_RIGHT_MOTOR_POS_INDEX] = -numStepsToTake;

    /* Move the motors to their target positions */
    powerUpMotors();
    _motorGroup.moveTo(targetPositions);

    while(!reachedTargetPosition)
    {
        if (false == _motorGroup.run())
        {
            reachedTargetPosition = true;
            _leftMotor->stop();
            _rightMotor->stop();
            delay(500);
        }
    }

    /* Set the positons of each motor back to zero so we can move them again next call */
    _rightMotor->setCurrentPosition(0);
    _leftMotor->setCurrentPosition(0);
    powerDownMotors();

    /* Print message to lcd */
    _lcd->clear();
    _lcd->setCursor(0,0);
    _lcd->print("Done:Move Bwd");
    delay(1000);

    _print->println("end moveBackward");

    return actualTravelDist;
}

void DiffDrive::turnRight90Degrees()
{

}

void DiffDrive::turnLeft90Degrees()
{

}

void DiffDrive::turnAround180Degrees()
{

}

void DiffDrive::powerUpMotors()
{
    /* Set sleep pins to HIGH to wake motors */
    digitalWrite(_leftMotorSleep, HIGH);
    digitalWrite(_rightMotorSleep, HIGH);
    delay(DD_MOTOR_POWER_DELAY);
}

void DiffDrive::powerDownMotors()
{
    /* Set sleep pins to LOW to put motors to sleep */
    digitalWrite(_leftMotorSleep, LOW);
    digitalWrite(_rightMotorSleep, LOW);
    delay(DD_MOTOR_POWER_DELAY);
}
