/*
    MobilePlatformType - a file that defines all the types used in the
    mobile platforms arduino software, declared as simple enums
*/

#ifndef MOB_PLATFOM_TYPES_H
#define MOB_PLATFOM_TYPES_H

enum MOB_TYPES
{
    /*Error types */
    ERR_NO_SERIAL_DATA          = -2,
    ERR_NOT_INITIALISED         = -1,

    /* Instruction set */
    INSTRUCT_STOP               = 0,
    INSTRUCT_MOVE_FORWARD       = 1,
    INSTRUCT_MOVE_BACKWARD      = 2,
    INSTRUCT_TURN_ZERO_RIGHT_90 = 3,
    INSTRUCT_TURN_ZERO_LEFT_90  = 4,
    INSTRUCT_TURN_AROUND_180    = 5,
    INSTRUCT_LIDAR_360_SWEEP    = 6,
    INSTRUCT_LIDAR_AT_ANGLE     = 7,

    /* Other types */
    SENSOR_READING_LIDAR,
    INSTRUCT_TERMINATOR = '\n'
};
#endif
