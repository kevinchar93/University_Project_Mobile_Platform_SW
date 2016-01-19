/*
    MobilePlatformTypes.h - a file that defines all the types used in the
    mobile platform's arduino software
*/

#ifndef MOB_PLATFOM_TYPES_H
#define MOB_PLATFOM_TYPES_H

/*
    Defines the set of instructions that the robot can receive
    and execute
*/
typedef enum _INSTRUCTION_SET
{
    INS_ERROR               = 0,
    INS_STOP                = 1,
    INS_MOVE_FORWARD        = 2,
    INS_MOVE_BACKWARD       = 3,
    INS_TURN_ZERO_RIGHT_90  = 4,
    INS_TURN_ZERO_LEFT_90   = 5,
    INS_TURN_AROUND_180     = 6,
    INS_LIDAR_360_SWEEP     = 7,
    INS_LIDAR_AT_ANGLE      = 8
} INSTRUCTION_SET;

enum MOB_TYPES
{
    /*Error types */
    ERR_NO_SERIAL_DATA          = -2,
    ERR_NOT_INITIALISED         = -1,

    /* Other types */
    SENSOR_READING_LIDAR,
    INSTRUCT_TERMINATOR = '\n'
};

/*
    Used to define size of and access the char arrays,
    used to implement the instruction parser buffer
*/
enum INSTRUCTION_FIELD
{
    INSTRUCTION_FIELD_TYPE                 = 0,
    INSTRUCTION_FIELD_VALUE                = 1,
    INSTRUCTION_FIELD_GRID_MODE        = 2,
    INSTRUCTION_FIELD_MAX
};

/*
    Defines a struct that will hold information about an instruction
    that can be executed by the robot
*/
typedef struct _Instruction
{
    INSTRUCTION_SET type;
    unsigned int     value;
    bool    gridMode;
} Instruction;
#endif
