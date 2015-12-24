#include <RemoteComm.h>
#include <MobilePlatformTypes.h>
#include <MobilePlatformDefinitions.h>
#include <PinMap.h>
#include <AccelStepper.h>
#include <MultiStepper.h>


RemoteComm robotComm(COMM_STATE_PIN, COMM_BUTTON_PIN, COMM_LED_PIN, COMM_BAUD_RATE);
char instructionBuffer [INSTRUCTION_BUFFER_SIZE];
int instructionBytes;
int bytesRead;


void setup()
{
    delay(3000);
    /* Initialise intruction buffer and elements needed to work with it */
    memset(instructionBuffer, 0, sizeof(instructionBuffer));
    instructionBytes = 0;
    bytesRead = 0;
    Serial.begin(9600);

    Instruction temp;

    const int numIns = 6;
    const int insSize = 10;

    char ins[numIns][insSize] = {"1,40;", "2,3453,T;" , "3;" , "4,50;" , "5,60,T;" , "8,70,F;"};


    for (int i = 0; i < numIns; i++)
    {
        Serial.print("Instruction num:");
        Serial.println(i);

        temp = parseInstructionString(ins[i]);

        Serial.print("Instruction num: ");
        Serial.println(temp.type);

        Serial.print("Instruction value: ");
        Serial.println(temp.value);

        Serial.print("Grid mode? : ");
        Serial.println(temp.gridMode);

        Serial.println("--------------------------");
        Serial.println();

        Serial.flush();
    }


    robotComm.setPrint(Serial);
    robotComm.waitForConnection();

}


void loop()
{
    /*
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
    */
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
