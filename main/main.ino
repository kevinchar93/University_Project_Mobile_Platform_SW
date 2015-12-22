#include <RemoteComm.h>
#include <MobilePlatformTypes.h>
#include <PinMap.h>
#include <AccelStepper.h>
#include <MultiStepper.h>


RemoteComm robotComm(COMM_STATE_PIN, COMM_BUTTON_PIN, COMM_LED_PIN, COMM_BAUD_RATE);
char instructionBuffer [INSTRUCTION_BUFFER_SIZE];
int instructionBytes;
int bytesRead;

void setup()
{
    /* Initialise intruction buffer and elements needed to work with it */
    memset(instructionBuffer, 0, sizeof(instructionBuffer));
    instructionBytes = 0;
    bytesRead = 0;

    robotComm.setPrint(Serial);
    robotComm.waitForConnection();

}

void loop()
{
    Serial.begin(9600);
    if ((instructionBytes = robotComm.isInstructionAvailable()) > 0 )
    {
        bytesRead = robotComm.readInstructions(instructionBuffer, instructionBytes);
        Serial.print("instruction bytes: ");
        Serial.println(instructionBytes);
        Serial.print("Message: ");
        Serial.println(instructionBuffer);
        Serial.print("bytes read: ");
        Serial.println(bytesRead);
    }
    delay(100);
}

void todo1 ()
{
    if (digitalRead(COMM_BUTTON_PIN) == LOW)
    {
        Serial.println("button pressed");
        char charArray[] = "123:1,425:2,552:3,234:4,234:5,213:6,213:7,243:8,125:9\n";
        robotComm.sendReadings(charArray);
        Serial.println("data sent");
        delay(2000);
        Serial.println("delay started");
    }
}
