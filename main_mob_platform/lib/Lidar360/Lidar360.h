/*
    An implementation of a class used to communicate with the Lidar
    on the robot, makes use of code from Pulsed Light located at:
    https://github.com/PulsedLight3D/LIDARLite_StateMachine
*/

#ifndef LIDAR_360_H
#define LIDAR_360_H

#include <Arduino.h>
#include <I2C.h>
#include <AccelStepper.h>
#include "PinMap.h"

#define STEPS_PER_REVOLUTION 560

#define NUM_READS_FOR_AVERAGE 3
#define LIDAR_LITE_ADDRESS 0x62

#define LIDAR_MANUAL_ZERO_SPEED 50.0

/* Define number of steps to reach these common angles */
#define LIDAR_0_DEGREES 0
#define LIDAR_45_DEGREES 70
#define LIDAR_90_DEGREES 140
#define LIDAR_135_DEGREES 210
#define LIDAR_180_DEGREES 280
#define LIDAR_225_DEGREES 350
#define LIDAR_270_DEGREES 420
#define LIDAR_315_DEGREES 490

class Lidar360
{
    public:
        Lidar360(AccelStepper &mtr, float maxSpeed, int btnA, int btnB, HardwareSerial  &print);
        void    testHarness();
        char*   getDistanceAtHeading(int heading, char* responseBuffer);

    private:
        void    zeroStepperMotor();
        void    stepToPosition(long pos);

        void    initLidar();
        void    setLidarOffSet(int offSet);
        void    llWriteAndWait(char myAddress, char myValue);
        byte    llReadAndWait(char myAddress, int numOfBytes, byte arrayToSave[2]);
        int     llGetDistance();
        int     llGetDistanceAverage(int numberOfReadings);

        int     angleToApproxSteps(int angle);

        int _buttonA;
        int _buttonB;
        int _motorDir;
        int _motorStep;

        float _maxSpeed;

        long _motorPosition;

        AccelStepper* _motor;
        HardwareSerial* _print;
};
#endif
