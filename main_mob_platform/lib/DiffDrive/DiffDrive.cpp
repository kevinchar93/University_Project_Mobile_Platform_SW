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
    delay(DD_LCD_DISPLAY_TIME);

    const float distTravelledPerStepMM = DD_WHEEL_CIRCUMFERENCE_MM / DD_STEPS_PER_WHEEL_REV;

    /* In grid mode, the distanceMM represents the ammount of grid spaces to move,
       Other wise it represets an explicit distance to travel in millimeters */
    distToTravelMM = gridMode ? (distanceMM * gridSizeMM) : distanceMM;

    /* Calculate approx number of steps to take to reach the target position */
    numStepsToTake = lroundf((float)distToTravelMM / distTravelledPerStepMM);

    /* Calculate the actual distance that the steppers will travel */
    actualTravelDist = numStepsToTake * distTravelledPerStepMM;

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
            delay(DD_MOTOR_STOP_TIME);
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
    delay(DD_LCD_DISPLAY_TIME);

    return actualTravelDist;
}

float DiffDrive::moveBackward(const uint16_t distanceMM, const bool gridMode, const uint16_t gridSizeMM)
{
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
    delay(DD_LCD_DISPLAY_TIME);

    const float distTravelledPerStepMM = DD_WHEEL_CIRCUMFERENCE_MM / DD_STEPS_PER_WHEEL_REV;

    /* In grid mode, the distanceMM represents the ammount of grid spaces to move,
       Other wise it represets an explicit distance to travel in millimeters */
    distToTravelMM = gridMode ? (distanceMM * gridSizeMM) : distanceMM;

    /* Calculate approx number of steps to take to reach the target position */
    numStepsToTake = lroundf((float)distToTravelMM / distTravelledPerStepMM);

    /* Calculate the actual distance that the steppers will travel */
    actualTravelDist = numStepsToTake * distTravelledPerStepMM;

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
            delay(DD_MOTOR_STOP_TIME);
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
    delay(DD_LCD_DISPLAY_TIME);

    return actualTravelDist;
}

float DiffDrive::turnRight90Degrees()
{
    bool reachedTargetPosition = false;
    const float DIST_PER_STEP_MM = DD_WHEEL_CIRCUMFERENCE_MM / DD_STEPS_PER_WHEEL_REV;
    int32_t targetPositions [DD_NUMBER_OF_DRIVE_MOTORS];

    /* We can calculate the amout to turn by calculating the legth of an arc with
       angle 90 degres, arc length = circumference * (angle /360)*/
    const float distanceForTurnMM = DD_WHEEL_BASE_CIRCUMFERENCE_MM * (90.0 / 360.0);

    /* We can then calculate how many steps for each motor to take by dividing distanceForTurnMM by
       the distance travelled on each step of the the drive motors  */
    const int16_t numStepsToTake = lroundf(distanceForTurnMM / DIST_PER_STEP_MM);

    /* Set the target positions for motors in the motor group - making a right turn so both share
       the same target positon, but the left motor moves forward and the right motor moves backward  */
    targetPositions[DD_LEFT_MOTOR_POS_INDEX] = numStepsToTake;
    targetPositions[DD_RIGHT_MOTOR_POS_INDEX] = -numStepsToTake;

    /* Print message to lcd */
    _lcd->clear();
    _lcd->setCursor(0,0);
    _lcd->print("DO:");
    _lcd->setCursor(0,1);
    _lcd->print("Turn Right");
    delay(DD_LCD_DISPLAY_TIME);

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
            delay(DD_MOTOR_STOP_TIME);
        }
    }

    /* Set the positons of each motor back to zero so we can move them again next call */
    _rightMotor->setCurrentPosition(0);
    _leftMotor->setCurrentPosition(0);
    powerDownMotors();

    /* Print message to lcd */
    _lcd->clear();
    _lcd->setCursor(0,0);
    _lcd->print("DONE:");
    _lcd->setCursor(0,1);
    _lcd->print("Turn Right");
    delay(DD_LCD_DISPLAY_TIME);
}

float DiffDrive::turnLeft90Degrees()
{
    bool reachedTargetPosition = false;
    const float DIST_PER_STEP_MM = DD_WHEEL_CIRCUMFERENCE_MM / DD_STEPS_PER_WHEEL_REV;
    int32_t targetPositions [DD_NUMBER_OF_DRIVE_MOTORS];

    /* We can calculate the amout to turn by calculating the legth of an arc with
       angle 90 degres, arc length = circumference * (angle /360)*/
    const float distanceForTurnMM = DD_WHEEL_BASE_CIRCUMFERENCE_MM * (90.0 / 360.0);

    /* We can then calculate how many steps for each motor to take by dividing distanceForTurnMM by
       the distance travelled on each step of the the drive motors  */
    const int16_t numStepsToTake = lroundf(distanceForTurnMM / DIST_PER_STEP_MM);

    /* Set the target positions for motors in the motor group - making a left turn so both share
       the same target positon, but the left motor moves backward and the right motor moves forward  */
    targetPositions[DD_LEFT_MOTOR_POS_INDEX] = -numStepsToTake;
    targetPositions[DD_RIGHT_MOTOR_POS_INDEX] = numStepsToTake;

    /* Print message to lcd */
    _lcd->clear();
    _lcd->setCursor(0,0);
    _lcd->print("DO:");
    _lcd->setCursor(0,1);
    _lcd->print("Turn Left");
    delay(DD_LCD_DISPLAY_TIME);

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
            delay(DD_MOTOR_STOP_TIME);
        }
    }

    /* Set the positons of each motor back to zero so we can move them again next call */
    _rightMotor->setCurrentPosition(0);
    _leftMotor->setCurrentPosition(0);
    powerDownMotors();

    /* Print message to lcd */
    _lcd->clear();
    _lcd->setCursor(0,0);
    _lcd->print("DONE:");
    _lcd->setCursor(0,1);
    _lcd->print("Turn Left");
    delay(DD_LCD_DISPLAY_TIME);
}

float DiffDrive::turnAround180Degrees()
{
    bool reachedTargetPosition = false;
    const float DIST_PER_STEP_MM = DD_WHEEL_CIRCUMFERENCE_MM / DD_STEPS_PER_WHEEL_REV;
    int32_t targetPositions [DD_NUMBER_OF_DRIVE_MOTORS];

    /* We can calculate the amout to turn by calculating the legth of an arc with
       angle 90 degres, arc length = circumference * (angle /360)*/
    const float distanceForTurnMM = DD_WHEEL_BASE_CIRCUMFERENCE_MM * (180.0 / 360.0);

    /* We can then calculate how many steps for each motor to take by dividing distanceForTurnMM by
       the distance travelled on each step of the the drive motors  */
    const int16_t numStepsToTake = lroundf(distanceForTurnMM / DIST_PER_STEP_MM);

    /* Set the target positions for motors in the motor group - making a left turn so both share
       the same target positon, but the left motor moves backward and the right motor moves forward  */
    targetPositions[DD_LEFT_MOTOR_POS_INDEX] = -numStepsToTake;
    targetPositions[DD_RIGHT_MOTOR_POS_INDEX] = numStepsToTake;

    /* Print message to lcd */
    _lcd->clear();
    _lcd->setCursor(0,0);
    _lcd->print("DO:");
    _lcd->setCursor(0,1);
    _lcd->print("Turn Around");
    delay(DD_LCD_DISPLAY_TIME);

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
            delay(DD_MOTOR_STOP_TIME);
        }
    }

    /* Set the positons of each motor back to zero so we can move them again next call */
    _rightMotor->setCurrentPosition(0);
    _leftMotor->setCurrentPosition(0);
    powerDownMotors();

    /* Print message to lcd */
    _lcd->clear();
    _lcd->setCursor(0,0);
    _lcd->print("DONE:");
    _lcd->setCursor(0,1);
    _lcd->print("Turn Around");
    delay(DD_LCD_DISPLAY_TIME);
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
