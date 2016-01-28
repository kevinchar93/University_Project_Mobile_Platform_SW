/*
    An implementation of a class used to communicate with the Lidar
    on the robot, makes use of code from Pulsed Light located at:
    https://github.com/PulsedLight3D/LIDARLite_StateMachine
*/

#ifndef LIDAR_360_H
#define LIDAR_360_H

#include <Arduino.h>
#include <I2C.h>
#include <math.h>
#include <AccelStepper.h>
#include <LiquidCrystal.h>

#define STEPS_PER_REVOLUTION 700.0

#define NUM_READS_FOR_AVERAGE 3
#define LIDAR_LITE_ADDRESS 0x62

#define LIDAR_MAX_SPEED 550
#define LIDAR_MANUAL_ZERO_SPEED 10.0

#define LIDAR_MOTOR_POWER_DELAY 5
#define LIDAR_MODULE_POWER_DELAY 100

#define LIDAR_BUTTON_PRESS_DELAY 1000

#define LIDAR_MAX_VECTOR_ARRAY_SIZE 360 // defines the max ammount of LidarVecs that will be held in the class array

/* Define number of steps to reach these common angles */
#define LIDAR_0_DEGREES 0
#define LIDAR_45_DEGREES 88
#define LIDAR_90_DEGREES 175
#define LIDAR_135_DEGREES 263
#define LIDAR_180_DEGREES 350
#define LIDAR_225_DEGREES 438
#define LIDAR_270_DEGREES 525
#define LIDAR_315_DEGREES 613
#define LIDAR_360_DEGREES 700

class Lidar360
{
    public:
        Lidar360 (float maxSpeed, int btnA, int btnB, int motorSleep, int lidarEn, AccelStepper &mtr, HardwareSerial  &print, LiquidCrystal &lcd);
        void    testHarness();
        void    getDistanceAtHeading(int heading, char* responseBuffer, int buffSize);

    private:
        void    performSweepScan(const int sampleInterval, const int numReadingsToTake);

        void    zeroStepperMotor();
        void    stepToRelativePosition(long steps);
        void    stepToZeroPosition();
        void    powerDownMotor();
        void    powerUpMotor();

        void    initLidar();
        void    verifyLidarOutput();
        void    powerDownLidar();
        void    powerUpLidar();
        void    setLidarOffSet(int offSet);

        void    llWriteAndWait(char myAddress, char myValue);
        byte    llReadAndWait(char myAddress, int numOfBytes, byte arrayToSave[2]);
        int     llGetDistance();
        int     llGetDistanceAverage(int numberOfReadings);

        long     angleToApproxSteps(int angle);
        float    stepsToApproxAngle(int stepPos);

        typedef struct _lidarVector
        {
            int distance;
            float heading;
        } LidarVec;

        LidarVec sweepReadings[LIDAR_MAX_VECTOR_ARRAY_SIZE];
        int      _numSweepReadings;

        int     _buttonA;
        int     _buttonB;

        int     _motorDir;
        int     _motorStep;
        int     _motorSleep;

        int     _lidarModuleEn;

        float   _maxSpeed;

        AccelStepper* _motor;
        HardwareSerial* _print;
        LiquidCrystal* _lcd;

};
#endif
