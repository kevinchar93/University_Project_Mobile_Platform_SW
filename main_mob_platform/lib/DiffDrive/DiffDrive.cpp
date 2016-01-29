#include "DiffDrive.h"

DiffDrive::DiffDrive(const float maxSpeed, const uint8_t leftMotorSleep, const uint8_t rightMotorSleep, AccelStepper &leftMotor,
                     AccelStepper &rightMotor, HardwareSerial  &print, LiquidCrystal &lcd)
 {
     /* Set the class variables from supplied parameters */
     _maxSpeed = maxSpeed;
     _leftMotorSleep = leftMotorSleep;
     _rightMotorSleep = rightMotorSleep;

     _leftMotor = &leftMotor;
     _rightMotor = &rightMotor;

     _print = &print;
     _lcd = &lcd;

     /* Put the motors to sleep to save power */
     powerDownMotors();
 }

void DiffDrive::moveForward(const uint32_t distanceMM, const bool gridMode, const uint32_t gridSize)
{
    uint32_t totalTravelDistance = 0;

    // In grid mode, then distanceMM represents the ammount of grid spaces to move,
    // Other wise it represets distance to travel in milimeters
    totalTravelDistance = gridMode ? (distanceMM * gridSize) : distance;


}

void DiffDrive::moveBackward(const uint32_t distanceMM, const bool gridMode, const uint32_t gridSize)
{
    uint32_t totalTravelDistance = 0;

    // In grid mode, then distanceMM represents the ammount of grid spaces to move,
    // Other wise it represets distance to travel in milimeters
    totalTravelDistance = gridMode ? (distanceMM * gridSize) : distance;

    
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
    delay(LIDAR_MOTOR_POWER_DELAY);
}

void DiffDrive::powerDownMotors()
{
    /* Set sleep pins to LOW to put motors to sleep */
    digitalWrite(_leftMotorSleep, LOW);
    digitalWrite(_rightMotorSleep, LOW);
    delay(LIDAR_MOTOR_POWER_DELAY);
}
