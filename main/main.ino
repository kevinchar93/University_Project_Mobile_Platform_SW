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

    char a[] = "1,40;";
    char b[] = "2;";
    char c[] = "3;";
    char d[] = "4,50;";
    char e[] = "5,60,T;";
    char f[] = "8,70,F;";


    parseInstructionString(a);
    parseInstructionString(b);
    parseInstructionString(c);
    parseInstructionString(d);
    parseInstructionString(e);
    parseInstructionString(f);


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

Instruction parseInstructionString (char* insStr)
{
    char* parserBuffer [PARSER_BUFFER_SIZE];

    for(int i = INSTRUCTION_FIELD_TYPE; i < INSTRUCTION_FIELD_MAX; i++)
    {
        parserBuffer[i] = strtok((i==0) ? insStr : NULL, ",;");
    }

    // DEBGUG
    Serial.print("Instruction type:");
    Serial.println(parserBuffer[INSTRUCTION_FIELD_TYPE]);
    if (parserBuffer[INSTRUCTION_FIELD_VALUE] != NULL)
    {
        Serial.print("Instruction value:");
        Serial.println(parserBuffer[INSTRUCTION_FIELD_VALUE]);
    }

    if (parserBuffer[INSTRUCTION_FIELD_USE_DIRECT_VALUE] != NULL)
    {
        Serial.print("Instruction use dir value:");
        Serial.println(parserBuffer[INSTRUCTION_FIELD_USE_DIRECT_VALUE]);
    }
    Serial.flush();

    return {0 , 0 , 0};
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
