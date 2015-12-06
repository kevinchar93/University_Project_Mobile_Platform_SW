#include "Arduino.h"
#include "RemoteComm.h"

RemoteComm::RemoteComm(int state, int button, int led, int baudRate)
{
    _isInit = false;

    pinMode(state, INPUT);
    pinMode(button, INPUT_PULLUP);
    pinMode(led, OUTPUT);

    _state = state;
    _button = button;
    _led = led;
    _baudRate = baudRate;

    Serial1.begin(_baudRate);
    _isInit = true;
}

void RemoteComm::waitForConnection ()
{
    boolean keepLooping = true;

    int stateValue = LOW;
    int switchValue = HIGH;
    int ledValue = HIGH;

    unsigned long interval = 100;
    unsigned long currTime = 0;
    unsigned long prevTime = 0;

    pinMode(_state, INPUT);
    pinMode(_button, INPUT_PULLUP);
    pinMode(_led, OUTPUT);

    digitalWrite(_led, ledValue);

    while (keepLooping)
    {
        /* Keep looping checkiing to see if connection established, use led as a signal */
        currTime = millis();
        if ((currTime - prevTime) >= interval)
        {
            prevTime = currTime;
            ledValue = (ledValue == HIGH) ? LOW : HIGH;
            digitalWrite(_led, ledValue);
        }

        /* Check bluetooth module state pin to see if in high state (connected) */
        stateValue = digitalRead(_state);

        if (HIGH == stateValue)
        {
            /* We have a connection, blink led slower and wait for button press */
            interval = 333;
            while (keepLooping)
            {
                currTime = millis();
                if (currTime - prevTime >= interval)
                {
                    prevTime = currTime;
                    ledValue = (ledValue == HIGH) ? LOW : HIGH;
                    digitalWrite(_led, ledValue);
                }

                /* Check to see if the user pressed the button, continue if so */
                switchValue = digitalRead(_button);
                keepLooping = (switchValue == HIGH) ? true : false;
            }
        }
    }

    /* Set the led to a solid light to signal program will continue */
    digitalWrite(_led, HIGH);
}

bool RemoteComm::isStillConnected ()
{
    /* Check bluetooth module state pin to see if we still have connection */
    if (_isInit)
    {
        return (digitalRead(_state) == HIGH);
    }
    return false;
}

void RemoteComm::sendReading ()
{

}

int RemoteComm::isInstructionAvailable ()
{
    if (_isInit)
    {
        return Serial1.available();
    }
    return -1;
}

void RemoteComm::readInstructions ()
{
    return '0';
}
