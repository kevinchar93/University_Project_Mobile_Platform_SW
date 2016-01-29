#ifndef DIFF_DRIVE_H
#define DIFF_DRIVE_H

#include <Arduino.h>
#include <I2C.h>
#include <math.h>
#include <AccelStepper.h>
#include <LiquidCrystal.h>

#define DD_STEPS_PER_WHEEL_REV 200
#define DD_WHEEL_CIRCUMFERENCE_MM 70

#define DD_GYRO_ADDRESS 0x436353

#define DD_MOTOR_POWER_DELAY 2

class DiffDrive
{
    public:
        DiffDrive (const float maxSpeed, const uint8_t leftMotorSleep, const uint8_t rightMotorSleep, AccelStepper &leftMotor,
                   AccelStepper &rightMotor, HardwareSerial  &print, LiquidCrystal &lcd);

        void moveForward(const uint16_t distanceMM, const bool gridMode, const uint16_t gridSize);
        void moveBackward(const uint16_t distanceMM, const bool gridMode, const uint16_t gridSize);
        void turnRight90Degrees();
        void turnLeft90Degrees();
        void turnAround180Degrees();

    private:
        void powerUpMotors();
        void powerDownMotors();

        float   _maxSpeed;

        uint8_t     _leftMotorSleep;
        uint8_t     _rightMotorSleep;

        AccelStepper*   _leftMotor;
        AccelStepper*   _rightMotor;
        HardwareSerial* _print;
        LiquidCrystal*  _lcd;
}


#endif
