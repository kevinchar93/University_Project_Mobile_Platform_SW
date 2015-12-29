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
Instruction currInstruction;
bool insErrorOccurred;

char lidarDataBuffer [LIDAR_DATA_BUFFER_SIZE];

void setup()
{
    delay(1000);

    /* Initialise intruction buffer and elements needed to work with it */
    memset(instructionBuffer, 0, sizeof(instructionBuffer));
    instructionBytes = 0;
    bytesRead = 0;

    // init debug serial
    Serial.begin(9600);
    robotComm.setPrint(Serial);

    // initialise connnection
    robotComm.waitForConnection();

}


void loop()
{
    /* Check for instructions & read them into buffer */
    if ((instructionBytes = robotComm.isInstructionAvailable()) > 0 )
    {
        Serial.println("--------------------------------------------------------");
        Serial.println("Instruction available read it into buffer");
        // clear instruction buffer before reading into it
        memset(instructionBuffer, 0, sizeof(instructionBuffer));

        // read all the bytes from the serial buffer into the instruction buffer
        bytesRead = robotComm.readInstructions(instructionBuffer, instructionBytes);
        Serial.print("instruction bytes: ");
        Serial.print(instructionBytes);
        Serial.print(", message: ");
        Serial.print(instructionBuffer);
        Serial.print(", bytes read: ");
        Serial.println(bytesRead);

        Serial.println("Checking for mismatch between bytes read & bytes received");
        // check for mis match in num of bytes read with num bytes received
        insErrorOccurred = !(instructionBytes == bytesRead);

        // if no error occured, parse then verify the instruction
        if (false == insErrorOccurred)
        {
            Serial.println("No error occured, parse instruction & attempt execution");
            currInstruction = parseInstructionString(instructionBuffer);
            insErrorOccurred = verifyInstruction(currInstruction);
        }

        Serial.println("check to see if an error occured during verification");
        // check to see if an error occured during verification
        if (true == insErrorOccurred)
        {
            Serial.println("Error occured, send error message");
            // send a message to the control sw that an error ocurred
            robotComm.sendMessage(INSTRUCTION_VERIFIED_ERROR);
        }
        else
        {
            Serial.println("No error occured, send okay message");
            // send verification okay message back
            robotComm.sendMessage(INSTRUCTION_VERIFIED_OK);
            // execute instruction
            // send back any data that was created during the instruction execution
            // send messae saying instruction executed
        }
        Serial.println("--------------------------------------------------------");

    }
    delay(100);
}

bool verifyInstruction (Instruction instruct)
{
    bool errorOccurred = true;

    switch (instruct.type)
    {
        case INS_ERROR:
            // instruction parser wasn't able to parse the number
            errorOccurred = true;
            break;

        case INS_STOP:
        case INS_MOVE_FORWARD:
        case INS_MOVE_BACKWARD:
        case INS_TURN_ZERO_RIGHT_90:
        case INS_TURN_ZERO_LEFT_90:
        case INS_TURN_AROUND_180:
        case INS_LIDAR_360_SWEEP:
            errorOccurred = false;
            break;

        case INS_LIDAR_AT_ANGLE:
            if (instruct.value <= MAX_LIDAR_ANGLE)
            {
                errorOccurred = false;
            }
            break;

        default:
            // no instruction recognised
            errorOccurred = true;
            break;
    }

    return errorOccurred;
}

void todo1 ()
{
    if (digitalRead(COMM_BUTTON_PIN) == LOW)
    {
        Serial.println("button pressed");
        char charArray[] = "123:1,425:2,552:3,234:4,234:5,213:6,213:7,243:8,125:9\n";
        robotComm.sendMessage(charArray);
        Serial.println("data sent");
        delay(2000);
        Serial.println("delay started");
    }

}
