/*
    MobilePlatformType - a file that defines all the types used in the
    mobile platforms arduino software, declared as simple enums
*/

#ifndef MOB_PLATFOM_TYPES_H
#define MOB_PLATFOM_TYPES_H

enum MOB_TYPES
{
    /*Error types */
    ERR_NO_SERIAL_DATA = -2,
    ERR_NOT_INITIALISED = -1,

    /* Instruction types */
    INSTRUCT_STOP,
    INSTRUCT_MOVE_FORWARD,
    INSTRUCT_MOV_BACKWARD,
    INSTRUCT_TURN_ZERO_RIGHT,
    INSTRUCT_TURN_ZERO_LEFT,
    INSTRUCT_TURN_RIGHT_ON_WHEEL,
    INSTRUCT_TURN_LEFT_ON_WHEEL,
    INSTRUCT_TURN_ABOUT_POINT_RIGHT,
    INSTRUCT_TURN_ABOUT_POINT_LEFT,
    INSTRUCT_LIDAR_360_SWEEP,
    INSTRUCT_LIDAR_AT_POINT,

    /* Other types */
    SENSOR_READING_LIDAR
};
#endif
