#include "RemoteComm.h"

void RemoteComm::init(int state, int button, int led, int baudRate, HardwareSerial  &print, LiquidCrystal &lcd)
{
    _isInit = false;

    pinMode(state, INPUT);
    pinMode(button, INPUT_PULLUP);
    pinMode(led, OUTPUT);

    _state = state;
    _button = button;
    _led = led;
    _baudRate = baudRate;
    _print = &print;
    _lcd = &lcd;

    Serial1.begin(_baudRate);
    _isInit = true;
}

void RemoteComm::waitForConnection ()
{
    /* Print message to lcd */
    _lcd->clear();
    _lcd->setCursor(0,0);
    _lcd->print("Waiting for a");
    _lcd->setCursor(0,1);
    _lcd->print("Connection...");

    bool keepLooping = true;
    bool handShakeSignalA = false;

    int stateValue = LOW;
    int switchValue = HIGH;
    int ledValue = HIGH;

    unsigned long currTime = 0;
    unsigned long interval = REMOTE_COMM_SEARCHNG_INTERVAL;
    unsigned long prevTime = 0;

    unsigned long currTimeHandshake = 0;
    unsigned long intervalHandshake = HANDSHAKE_PULSE_INTERVAL;
    unsigned long prevTimeHandshake = 0;

    pinMode(_state, INPUT);
    pinMode(_button, INPUT_PULLUP);
    pinMode(_led, OUTPUT);

    digitalWrite(_led, ledValue);
    _print->begin(9600);
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
            currTimeHandshake = millis();
            if (currTimeHandshake - prevTimeHandshake >= intervalHandshake)
            {
                prevTimeHandshake = currTimeHandshake;
                /* Check for the handshake first stage */
                handShakeSignalA = handshake();
            }
        }

        if (handShakeSignalA)
        {
            /* We have a connection, blink led slower and wait for button press */
            interval = REMOTE_COMM_CONNECTED_INTERVAL;

            /* Update Lcd message */
            _lcd->clear();
            _lcd->setCursor(0,0);
            _lcd->print("Connected press");
            _lcd->setCursor(0,1);
            _lcd->print("C to continue");
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

            /* Send signal to say we've pressed the button and to continue */
            Serial1.println(HANDSHAKE_SIGNAL_B);
            _print->println("send hand shake stage B signal");
        }
    }

    /* Set the led to a solid light to signal program will continue */
    digitalWrite(_led, HIGH);

    /*
       Place a delay here , it will act as simple debounce mechanism
       as the button might still read high for a while after it is pressed
     */
    delay(REMOTE_COMM_DEBOUNCE_TIME_MS);
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

int RemoteComm::sendMessage (const char* readings)
{
    int sentBytes = Serial1.println(readings);
    Serial1.flush();

    return sentBytes;
}

int RemoteComm::isInstructionAvailable ()
{
    if (_isInit)
    {
        return Serial1.available();
    }
    return ERR_NOT_INITIALISED;
}

int RemoteComm::readInstructions (char* buffer, int bytes)
{
    return Serial1.readBytes(buffer, bytes);
}

bool RemoteComm::handshake()
{
    if (Serial1.available() <= 0)
    {
        _print->println("send handshake signal");
        Serial1.println(HANDSHAKE_SIGNAL_A);
        return false;
    }
    else
    {
        _print->print("read vaue sent:");
        char read = Serial1.read();
        _print->println(read);
        if (read == HANDSHAKE_RECEIVE_SIGNAL)
        {
            _print->println("values match");
            return true;
        }
        else
        {
            _print->println("values do not match");
            return false;
        }

    }
}
