#include <RemoteComm.h>
#include <MobilePlatformTypes.h>
#include <MobilePlatformDefinitions.h>
#include <PinMap.h>
#include <AccelStepper.h>
#include <DiffDrive.h>
#include <Lidar360.h>

/* Vars used to store instruction informatin */
Instruction currInstruction;
char instructionBuffer [INSTRUCTION_BUFFER_SIZE];
int instructionBytes;
int bytesRead;
bool insErrorOccurred;

/* Vars used to store information from the lidar module */
char lidarDataBuffer [LIDAR_DATA_BUFFER_SIZE];
char lidarHeadingDistBuffer [LIDAR_HEADING_DIST_BUFFER];

/* Vars used to access the stepper motors used in the Lidar and Drive systems */
AccelStepper lidarStepper(AccelStepper::DRIVER, LIDAR_STEP, LIDAR_DIR);
AccelStepper leftDriveStepper(AccelStepper::DRIVER, LEFT_MOTOR_STEP, LEFT_MOTOR_DIR);
AccelStepper rightDriveStepper(AccelStepper::DRIVER, RIGHT_MOTOR_STEP, RIGHT_MOTOR_DIR);

/* Vars used to access the lcd screen on the robot */
LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

/* Vars used to abstract and control the 3 hardware systems used in the robot */
RemoteComm com;
Lidar360 lidar;
DiffDrive driveSystem;

void setup()
{
    /* Initialise intruction buffer and elements needed to work with it */
    memset(instructionBuffer, 0, sizeof(instructionBuffer));
    instructionBytes = 0;
    instructionBytes = 0;
    bytesRead = 0;
    insErrorOccurred = false;

    /* Kick off the debug serial com and the lcd screen */
    Serial.begin(9600);
    lcd.begin(LCD_COLS, LCD_ROWS);

    /* Call the initialisation methods for RemoteComm, DiffDrive and Lidar360 */
    com.init(COMM_STATE_PIN, COMM_BUTTON_PIN, COMM_LED_PIN, COMM_BAUD_RATE, Serial, lcd);
    driveSystem.init(MAX_DRIVE_SPEED, LEFT_MOTOR_SLEEP, RIGHT_MOTOR_SLEEP, leftDriveStepper, rightDriveStepper, Serial, lcd);
    lidar.init(LIDAR_MAX_SPEED, LIDAR_BUTTON_A, LIDAR_BUTTON_B, LIDAR_MOTOR_SLEEP, LIDAR_MODULE_EN, lidarStepper, Serial, lcd);

    /* First user has to verify that the lidar output makes senses and it doesent need restarting */
    lidar.verifyLidarOutput();

    /* Then the have to use the A & B button on the robot to put the lidar into zero position */
    lidar.zeroStepperMotor();

    /* Once this is done we can begin waiting for a connection to the control software */
    com.waitForConnection();
    Serial.println("Connected");
}


void loop()
{
    showLcdMessage("Waiting for an", "instruction", 0, lcd);

    /* Check for instructions & read them into buffer */
    if ((instructionBytes = com.isInstructionAvailable()) > 0 )
    {
        showLcdMessage("Instruction", "received!", 0, lcd);

        Serial.println("--------------------------------------------------------");
        Serial.println("Instruction available read it into buffer");

        /* Clear instruction buffer before reading into it */
        memset(instructionBuffer, 0, sizeof(instructionBuffer));

        /* Read all the bytes from the serial buffer into the instruction buffer */
        bytesRead = com.readInstructions(instructionBuffer, instructionBytes);
        Serial.print("instruction bytes: ");
        Serial.print(instructionBytes);
        Serial.print(", message: ");
        Serial.print(instructionBuffer);
        Serial.print(", bytes read: ");
        Serial.println(bytesRead);

        Serial.println("Checking for mismatch between bytes read & bytes received");

        /* Check for mis match in num of bytes read with num bytes received */
        insErrorOccurred = !(instructionBytes == bytesRead);

        /* If no error occured, parse then verify the instruction */
        if (false == insErrorOccurred)
        {
            Serial.println("No error occured, parse instruction & attempt execution");
            currInstruction = parseInstructionString(instructionBuffer);
            insErrorOccurred = verifyInstruction(currInstruction);
        }

        Serial.println("check to see if an error occured during verification");
        /* Check to see if an error occured during verification */
        if (true == insErrorOccurred)
        {
            Serial.println("Error occured, send error message");

            /* Send a message to the control sw that an error ocurred */
            com.sendMessage(INSTRUCTION_VERIFIED_ERROR);
        }
        else
        {
            Serial.println("No error occured, send okay message");

            /* Send verification okay message back */
            com.sendMessage(INSTRUCTION_VERIFIED_OK);

            /* Execute the instruction */
            insErrorOccurred = executeInstruction(currInstruction);

            if (true == insErrorOccurred)
            {
                Serial.println("Error occured, send error message");
                /* Send a message to the control sw that an error ocurred */
                com.sendMessage(INSTRUCTION_VERIFIED_ERROR);
            }
            else
            {
                /* Send verification completion message back */
                delay(INSTRUCTION_DELAY);
                switch (currInstruction.type)
                {
                    case INS_MOVE_FORWARD:
                    case INS_MOVE_BACKWARD:
                    case INS_TURN_ZERO_RIGHT_90:
                    case INS_TURN_ZERO_LEFT_90:
                    case INS_TURN_AROUND_180:
                        Serial.println("No error occured, send complete message");
                        com.sendMessage(INSTRUCTION_COMPLETE);
                        break;
                    case INS_LIDAR_360_SWEEP:
                    case INS_LIDAR_AT_ANGLE:
                        Serial.println("No error occured, send data available message");
                        com.sendMessage(INSTRUCTION_DATA_AVAILABLE);
                        break;
                }

                /* Wait a period of time for the control sw to recieve the message before sending data */
                delay(INSTRUCTION_DELAY);

                /* Send data that was created on either a sweep or measurment at heading */
                switch (currInstruction.type)
                {
                    case INS_LIDAR_360_SWEEP:
                        Serial.println("Send sweep data");
                        com.sendMessage(lidarDataBuffer);
                        break;
                    case INS_LIDAR_AT_ANGLE:
                        Serial.println("Send heading data");
                        Serial.println(lidarHeadingDistBuffer);
                        com.sendMessage(lidarHeadingDistBuffer);
                        break;
                }
            }
        }
        Serial.println("--------------------------------------------------------");
    }

    /* Check if we are still connected */
    if (false == com.isStillConnected())
    {
        /* If we have lost connection wait for reconnect */
        com.waitForConnection();
    }

    delay(MAIN_LOOP_DELAY);
}

/**
 * Execute the given instruction
 *
 * @param instruction The instruction to execute
 */
bool executeInstruction (Instruction instruction)
{
    bool errorOccurred = false;

    switch (instruction.type)
    {
        case INS_MOVE_FORWARD:
            driveSystem.moveForward(instruction.value, instruction.gridMode, instruction.gridSizeMM);
            errorOccurred = false;
            break;
        case INS_MOVE_BACKWARD:
            driveSystem.moveBackward(instruction.value, instruction.gridMode, instruction.gridSizeMM);
            errorOccurred = false;
            break;
        case INS_TURN_ZERO_RIGHT_90:
            driveSystem.turnRight90Degrees();
            errorOccurred = false;
            break;
        case INS_TURN_ZERO_LEFT_90:
            driveSystem.turnLeft90Degrees();
            errorOccurred = false;
            break;
        case INS_TURN_AROUND_180:
            driveSystem.turnAround180Degrees();
            errorOccurred = false;
            break;
        case INS_LIDAR_360_SWEEP:
            lidar.getDistanceSweep(lidarDataBuffer, sizeof(lidarDataBuffer));
            errorOccurred = false;
            break;
        case INS_LIDAR_AT_ANGLE:
            lidar.getDistanceAtHeading(instruction.value, lidarHeadingDistBuffer, sizeof(lidarHeadingDistBuffer));
            errorOccurred = false;
            break;
        case INS_STOP:
        case INS_ERROR:
        /* These instruction do not occur */
        default:
            /* No instruction recognised */
            errorOccurred = true;
            break;
    }

    return errorOccurred;
}


/**
 * Verify that an instruction is valid and can be executed
 *
 * @param instruction The instruction to verify
 */
bool verifyInstruction (Instruction instruction)
{
    bool errorOccurred = false;

    switch (instruction.type)
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
            if (instruction.value <= MAX_LIDAR_ANGLE)
            {
                errorOccurred = false;
            }
            break;

        default:
            /* No instruction recognised */
            errorOccurred = true;
            break;
    }

    return errorOccurred;
}

/**
 * Parses a given instruction string an turns it into an instruction struct
 *
 * @param insStr the instruction string to parse
 */
Instruction parseInstructionString (char* insStr)
{
    char* parserBuffer [PARSER_BUFFER_SIZE];
    int type;
    int val;
    int gridSizeMM;
    bool gridMode;

    Instruction tempInstruction;

    /* Split the instruction string into tokens we can parse */
    for(int i = 0; i < PARSER_BUFFER_SIZE; i++)
    {
        parserBuffer[i] = strtok((i==0) ? insStr : NULL, ",;");
    }

    /* Convert values in the buffer to the correct datatype */
    type = atoi(parserBuffer[INSTRUCTION_FIELD_TYPE]);

    val = (parserBuffer[INSTRUCTION_FIELD_VALUE] == NULL) ?
            0 : atoi(parserBuffer[INSTRUCTION_FIELD_VALUE]);

    gridMode = (parserBuffer[INSTRUCTION_FIELD_GRID_MODE][0] == 'T' ) ?
                true : false;

    gridSizeMM = (parserBuffer[INSTRUCTION_FIELD_GRIDE_SIZE] == NULL) ?
            0 : atoi(parserBuffer[INSTRUCTION_FIELD_GRIDE_SIZE]);

    /* Put the extracted values into the instruction struct and return it */
    tempInstruction.type = (INSTRUCTION_SET) type;
    tempInstruction.value = val;
    tempInstruction.gridMode = gridMode;
    tempInstruction.gridSizeMM = gridSizeMM;

    return tempInstruction;
}


/**
 * Display a message on the LCD screen
 *
 * @param line1 The string to display on line one (16 characters max)
 * @param line2 The string to display on line two (16 characters max)
 * @param dTime The time to keep the message on the screen for (delays)
 * @param lcd The lcd to print the message to
 */
void showLcdMessage(const char* line1, const char* line2, uint16_t dTime, LiquidCrystal& lcd)
{
    if (NULL == line1 || NULL == line2)
    {
        return;
    }

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(line1);
    lcd.setCursor(0,1);
    lcd.print(line2);

    delay(dTime);
}


/**
 * Halt execution until a given button is pressed
 *
 * @param btn The button that will be polled for a press
 * @param dTime The time to delay for after the button is pressed
 * @param lcd Lcd to print "button pressed" message to
 */
void pressButtonToContinue(uint8_t btn, uint32_t dTime, LiquidCrystal& lcd)
{
    pinMode(btn, INPUT_PULLUP);

    while(true)
    {
        if (digitalRead(btn) == LOW)
        {
            break;
        }
    }

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Button Pressed!");
    delay(dTime);
}
