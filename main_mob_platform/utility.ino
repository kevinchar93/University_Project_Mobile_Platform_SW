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
