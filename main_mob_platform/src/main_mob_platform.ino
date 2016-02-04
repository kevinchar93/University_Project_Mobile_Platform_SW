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

/* Vars used to access the stepper motors used in the Lidar and Drive systems */
AccelStepper lidarStepper(AccelStepper::DRIVER, LIDAR_STEP, LIDAR_DIR);
AccelStepper leftDriveStepper(AccelStepper::DRIVER, LEFT_MOTOR_STEP, LEFT_MOTOR_DIR);
AccelStepper rightDriveStepper(AccelStepper::DRIVER, RIGHT_MOTOR_STEP, RIGHT_MOTOR_DIR);

/* Vars used to access the lcd screen on the robot */
LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

/* Vars used to abstract and control the 3 hardware systems used in the robot */
RemoteComm comm;
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

    /* Kick off the debug serial comm and the lcd screen */
    Serial.begin(9600);
    lcd.begin(LCD_COLS, LCD_ROWS);

    /* Call the initialisation methods for RemoteComm, DiffDrive and Lidar360 */
    comm.init(COMM_STATE_PIN, COMM_BUTTON_PIN, COMM_LED_PIN, COMM_BAUD_RATE, Serial, lcd);
    driveSystem.init(MAX_DRIVE_SPEED, LEFT_MOTOR_SLEEP, RIGHT_MOTOR_SLEEP, leftDriveStepper, rightDriveStepper, Serial, lcd);
    lidar.init(LIDAR_MAX_SPEED, LIDAR_BUTTON_A, LIDAR_BUTTON_B, LIDAR_MOTOR_SLEEP, LIDAR_MODULE_EN, lidarStepper, Serial, lcd);

    /* First user has to verify that the lidar output makes senses and it doesent need restarting */
    lidar.verifyLidarOutput();

    /* Then the have to use the A & B button on the robot to put the lidar into zero position */
    lidar.zeroStepperMotor();

    /* Once this is done we can begin waiting for a connection to the control software */
    comm.waitForConnection();
}


void loop()
{
    /* Check for instructions & read them into buffer */
    if ((instructionBytes = comm.isInstructionAvailable()) > 0 )
    {
        Serial.println("--------------------------------------------------------");
        Serial.println("Instruction available read it into buffer");
        // clear instruction buffer before reading into it
        memset(instructionBuffer, 0, sizeof(instructionBuffer));

        // read all the bytes from the serial buffer into the instruction buffer
        bytesRead = comm.readInstructions(instructionBuffer, instructionBytes);
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
            comm.sendMessage(INSTRUCTION_VERIFIED_ERROR);
        }
        else
        {
            Serial.println("No error occured, send okay message");
            // send verification okay message back
            comm.sendMessage(INSTRUCTION_VERIFIED_OK);
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
        comm.sendMessage(charArray);
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

void showLcdMessage(const char* line1, const char* line2, uint16_t dTime, LiquidCrystal* lcd)
{
    if (NULL == line1 || NULL == line2)
    {
        return;
    }

    lcd->clear();
    lcd->setCursor(0,0);
    lcd->print(line1);
    lcd->setCursor(0,1);
    lcd->print(line2);

    delay(dTime);
}

void pressButtonToContinue(uint8_t btn, uint32_t dTime, LiquidCrystal* lcd)
{
    pinMode(btn, INPUT_PULLUP);

    while(true)
    {
        if (digitalRead(btn) == LOW)
        {
            break;
        }
    }

    lcd->clear();
    lcd->setCursor(0,0);
    lcd->print("Button Pressed!");
    delay(dTime);
}
