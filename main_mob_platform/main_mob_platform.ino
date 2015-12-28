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
        // clear instruction buffer before reading into it
        memset(instructionBuffer, 0, sizeof(instructionBuffer));

        // read all the bytes in the serial buffer into the instruction buffer
        bytesRead = robotComm.readInstructions(instructionBuffer, instructionBytes);
        Serial.print("instruction bytes: ");
        Serial.print(instructionBytes);
        Serial.print(", message: ");
        Serial.print(instructionBuffer);
        Serial.print(", bytes read: ");
        Serial.println(bytesRead);

        // check for mis match in num of bytes read with num bytes received
        insErrorOccurred = !(instructionBytes == bytesRead);

        // if no error occured, parse then attempt to execute instruction
        if (false == insErrorOccurred)
        {
            currInstruction = parseInstructionString(instructionBuffer);
            insErrorOccurred = verifyInstruction(currInstruction);
        }

        // check to see if an error occured on reception or execution
        if (true == insErrorOccurred)
        {
            // send a message to the control sw that an error ocurred
        }
        else
        {
            // send okay message back
            // execute instruction
            // send back any data that was created during the instuction execution
            // send messae saying instruction executed
        }

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
            Serial.println("INS_ERROR received");
            errorOccurred = true;
            break;

        case INS_STOP:
            Serial.println("INS_STOP received");
            errorOccurred = false;
            break;

        case INS_MOVE_FORWARD:
            Serial.println("INS_MOVE_FORWARD received");
            if (((instruct.gridMode == false) && (instruct.value < MAX_SINGLE_TRAVEL_DIST_CM)) ||
                ((instruct.gridMode == true) && (instruct.value < MAX_SINGLED_TRAVEL_DIST_GRID)))
            {
                errorOccurred = false;
            }
            break;

        case INS_MOVE_BACKWARD:
            Serial.println("INS_MOVE_BACKWARD received");
            if (((instruct.gridMode == false) && (instruct.value < MAX_SINGLE_TRAVEL_DIST_CM)) ||
                ((instruct.gridMode == true) && (instruct.value < MAX_SINGLED_TRAVEL_DIST_GRID)))
            {
                errorOccurred = false;
            }
            errorOccurred = false;
            break;

        case INS_TURN_ZERO_RIGHT_90:
            Serial.println("INS_TURN_ZERO_RIGHT_90 received");
            errorOccurred = false;
            break;

        case INS_TURN_ZERO_LEFT_90:
            Serial.println("INS_TURN_ZERO_LEFT_90 received");
            errorOccurred = false;
            break;

        case INS_TURN_AROUND_180:
            Serial.println("INS_TURN_AROUND_180 received");
            errorOccurred = false;
            break;

        case INS_LIDAR_360_SWEEP:
            Serial.println("INS_LIDAR_360_SWEEP received");
            errorOccurred = false;
            break;

        case INS_LIDAR_AT_ANGLE:
            Serial.println("INS_LIDAR_AT_ANGLE received");
            if (instruct.value <= MAX_LIDAR_ANGLE)
            {
                errorOccurred = false;
            }
            break;

        default:
            // no instruction recognised
            Serial.println("no instruction recognised");
            errorOccurred = true;
    }
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
