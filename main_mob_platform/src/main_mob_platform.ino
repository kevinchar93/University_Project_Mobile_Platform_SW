#include <RemoteComm.h>
#include <MobilePlatformTypes.h>
#include <MobilePlatformDefinitions.h>
#include <PinMap.h>
#include <AccelStepper.h>
#include <MultiStepper.h>
#include <Lidar360.h>


RemoteComm robotComm(COMM_STATE_PIN, COMM_BUTTON_PIN, COMM_LED_PIN, COMM_BAUD_RATE);

char instructionBuffer [INSTRUCTION_BUFFER_SIZE];
int instructionBytes;
int bytesRead;
Instruction currInstruction;
bool insErrorOccurred;

char lidarDataBuffer [LIDAR_DATA_BUFFER_SIZE];

AccelStepper lidarStep(AccelStepper::DRIVER, LIDAR_STEP, LIDAR_DIR);
LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

void setup()
{
    Serial.begin(115200);
    lcd.begin(LCD_COLS, LCD_ROWS);

    /* Initialise intruction buffer and elements needed to work with it */
    // memset(instructionBuffer, 0, sizeof(instructionBuffer));
    // instructionBytes = 0;
    // bytesRead = 0;
    //
    // // init debug serial
    // Serial.begin(9600);
    // robotComm.setPrint(Serial);
    //
    // // initialise connnection
    // robotComm.waitForConnection();

    const int bSize = 10;
    const int timeDelay = 1000;
    char measureBuff[10];

    Lidar360 lidar360(LIDAR_MAX_SPEED, LIDAR_BUTTON_A, LIDAR_BUTTON_B, LIDAR_MOTOR_SLEEP,
                      LIDAR_MODULE_EN, lidarStep, Serial, lcd);


    while (true)
    {
        lidar360.testHarness();

        // delay 2 mins
        delay(2 * 60000);
    }
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

Instruction parseInstructionString (char* insStr)
{
    char* parserBuffer [PARSER_BUFFER_SIZE];
    int type;
    int val;
    bool gridMode;

    Instruction tempInstruction;

    /* Split the instruction string into tokens we can parse */
    for(int i = INSTRUCTION_FIELD_TYPE; i < INSTRUCTION_FIELD_MAX; i++)
    {
        parserBuffer[i] = strtok((i==0) ? insStr : NULL, ",;");
    }

    /* Convert values in the buffer to the correct datatype */
    type = atoi(parserBuffer[INSTRUCTION_FIELD_TYPE]);

    val = (parserBuffer[INSTRUCTION_FIELD_VALUE] == NULL) ?
            0 : atoi(parserBuffer[INSTRUCTION_FIELD_VALUE]);

    gridMode = (parserBuffer[INSTRUCTION_FIELD_GRID_MODE][0] == 'T' ) ?
                true : false;

    /* Put the extracted values into the instruction struct and return it */
    tempInstruction.type = (INSTRUCTION_SET) type;
    tempInstruction.value = val;
    tempInstruction.gridMode = gridMode;

    return tempInstruction;
}
