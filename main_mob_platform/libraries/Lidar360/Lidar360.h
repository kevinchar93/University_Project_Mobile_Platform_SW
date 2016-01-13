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

class Lidar360
{
    public:
        Lidar360(AccelStepper &mtr, float maxSpeed, int btnA, int btnB, HardwareSerial  &print);
        void testHarness();

    private:
        void    zeroStepperMotor();
        void    stepToPosition(long pos);

        void    initLidar();
        void    setLidarOffSet(int offSet);
        void    llWriteAndWait(char myAddress, char myValue);
        byte    llReadAndWait(char myAddress, int numOfBytes, byte arrayToSave[2]);
        int     llGetDistance();
        int     llGetDistanceAverage(int numberOfReadings);



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
