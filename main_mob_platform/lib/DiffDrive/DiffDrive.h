#ifndef DIFF_DRIVE_H
#define DIFF_DRIVE_H

#include <Arduino.h>
#include <I2C.h>
#include <math.h>
#include <AccelStepper.h>
#include <MultiStepper.h>
#include <LiquidCrystal.h>

#define DD_WHEEL_DIAMETER 66.0
#define DD_STEPS_PER_WHEEL_REV 200.0
#define DD_WHEEL_CIRCUMFERENCE_MM M_PI * DD_WHEEL_DIAMETER

#define DD_WHEEL_BASE_DIAMETER_MM 265.0
#define DD_WHEEL_BASE_CIRCUMFERENCE_MM M_PI * DD_WHEEL_BASE_DIAMETER_MM

#define DD_GYRO_ADDRESS 0x436353

#define DD_MOTOR_POWER_DELAY 2

#define DD_NUMBER_OF_DRIVE_MOTORS 2
#define DD_LEFT_MOTOR_POS_INDEX 0
#define DD_RIGHT_MOTOR_POS_INDEX 1

#define DD_LCD_DISPLAY_TIME 100
#define DD_MOTOR_STOP_TIME 500



class DiffDrive
{
    public:
       void     init(const float maxSpeed, const uint8_t leftMotorSleep, const uint8_t rightMotorSleep,
                     AccelStepper &leftMotor, AccelStepper &rightMotor, HardwareSerial  &print, LiquidCrystal &lcd);

        float   moveForward(const uint16_t distanceMM, const bool gridMode = false, const uint16_t gridSizeMM = 0);
        float   moveBackward(const uint16_t distanceMM, const bool gridMode = false, const uint16_t gridSizeMM = 0);
        float   turnRight90Degrees();
        float   turnLeft90Degrees();
        float   turnAround180Degrees();

    private:
        void    powerUpMotors();
        void    powerDownMotors();

        float   _maxSpeed;

        uint8_t _leftMotorSleep;
        uint8_t _rightMotorSleep;

        AccelStepper*   _leftMotor;
        AccelStepper*   _rightMotor;
        MultiStepper    _motorGroup;

        HardwareSerial* _print;
        LiquidCrystal*  _lcd;
};


#endif
