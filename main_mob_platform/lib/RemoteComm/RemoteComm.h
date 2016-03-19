/*
    RemoteComm - Bluetooth communication with the robot astracted into a
    library to make communication with a controlling device easier and more
    intuitive.
*/

#ifndef REMOTE_COMM_H
#define REMOTE_COMM_H

#include <Arduino.h>
#include <LiquidCrystal.h>
#include "MobilePlatformTypes.h"

/* Defs related to the RemoteComm waitForConnection procedure */
#define REMOTE_COMM_SEARCHNG_INTERVAL 100
#define REMOTE_COMM_CONNECTED_INTERVAL 333
#define REMOTE_COMM_DEBOUNCE_TIME_MS 200

/* Defs related to the serial handshake procedure */
#define HANDSHAKE_RECEIVE_SIGNAL 'S'
#define HANDSHAKE_PULSE_INTERVAL 500
#define HANDSHAKE_SIGNAL_A "A;"
#define HANDSHAKE_SIGNAL_B "B;"

class RemoteComm
{
    public:
        void    init(int state, int button, int led, int baudRate, HardwareSerial  &print, LiquidCrystal &lcd);
        void    waitForConnection ();
        bool    isStillConnected();
        int     sendMessage(const char* readings);
        int     isInstructionAvailable();
        int     readInstructions(char* buffer, int bytes);

    private:
        bool    handshake();
        int _state;
        int _button;
        int _led;
        int _baudRate;
        bool _isInit;

        HardwareSerial* _print;
        LiquidCrystal* _lcd;
};

#endif
