#include <Arduino.h>
#include <String.h>
#include "MobilePlatformTypes.h"
#include "MobilePlatformDefinitions.h"


Instruction parseInstructionString (char* insStr)
{
    char* parserBuffer [PARSER_BUFFER_SIZE];
    int type;
    int val;
    bool gridMode;

    Instruction tempInstruction;

    for(int i = INSTRUCTION_FIELD_TYPE; i < INSTRUCTION_FIELD_MAX; i++)
    {
        parserBuffer[i] = strtok((i==0) ? insStr : NULL, ",;");
    }

    /* DEBGUG
    Serial.print("Instruction type:");
    Serial.println(parserBuffer[INSTRUCTION_FIELD_TYPE]);
    if (parserBuffer[INSTRUCTION_FIELD_VALUE] != NULL)
    {
        Serial.print("Instruction value:");
        Serial.println(parserBuffer[INSTRUCTION_FIELD_VALUE]);
    }

    if (parserBuffer[INSTRUCTION_FIELD_GRID_MODE] != NULL)
    {
        Serial.print("Instruction use dir value:");
        Serial.println(parserBuffer[INSTRUCTION_FIELD_GRID_MODE]);
    }
    Serial.flush();
    */

    /* Convert values in the buffer to the correct datatype */
    type = atoi(parserBuffer[INSTRUCTION_FIELD_TYPE]);

    val = (parserBuffer[INSTRUCTION_FIELD_VALUE] == NULL) ?
            0 : atoi(parserBuffer[INSTRUCTION_FIELD_VALUE]);

    gridMode = (parserBuffer[INSTRUCTION_FIELD_GRID_MODE][0] == 'T' ) ?
                true : false;

    /*
    Serial.println("Parsed values with atio function");
    Serial.print("parsed Type: ");
    Serial.println(type);
    Serial.print("parsed val: ");
    Serial.println(val);
    Serial.print("parsed gridMode: ");
    Serial.println(gridMode);
    Serial.println("----------------------------");
    Serial.println();
    Serial.flush();
    */

    tempInstruction.type = (INSTRUCTION_SET) type;
    tempInstruction.value = val;
    tempInstruction.gridMode = gridMode;

    return tempInstruction;
}
