/*
    An implementation of a class used to communicate with the Lidar
    on the robot, makes use of code from Pulsed Light located at:
    https://github.com/PulsedLight3D/LIDARLite_StateMachine
*/

#ifndef LIDAR_360_H
#define LIDAR_360_H

#include <Arduino.h>
#include <I2C.h>
#include "PinMap.h"

#define DRIVE_GEAR 16
#define DRIVEN_GEAR 56

#define NUM_READS_FOR_AVERAGE 3
#define LIDAR_LITE_ADDRESS 0x62

class Lidar360
{
    public:

    private:
        void    initLidar(int btnA, int btnB);
        void    setLidarOffSet(int offSet);
        void    llWriteAndWait(char myAddress, char myValue);
        byte    llReadAndWait(char myAddress, int numOfBytes, byte arrayToSave[2]);
        int     llGetDistance();
        int     llGetDistanceAverage(int numberOfReadings);

        int _buttonA;
        int _buttonB;
};
#endif
