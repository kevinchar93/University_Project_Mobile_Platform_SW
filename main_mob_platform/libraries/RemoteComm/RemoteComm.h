/*
    RemoteComm - Bluetooth communication with the robot astracted into a
    library to make communication with a controlling device easier and more
    intuitive.
*/

#ifndef REMOTE_COMM_H
#define REMOTE_COMM_H

#include <Arduino.h>

class RemoteComm
{
    public:
        RemoteComm(int state, int button, int led, int baudRate);
        void    waitForConnection ();
        bool    isStillConnected();
        int     sendReadings(char* readings);
        int     isInstructionAvailable();
        int     readInstructions(char* buffer, int bytes);
        void    setPrint(HardwareSerial  &print);

    private:
        bool    handshake();
        int _state;
        int _button;
        int _led;
        int _baudRate;
        bool _isInit;
        HardwareSerial* _print;
};

#endif
