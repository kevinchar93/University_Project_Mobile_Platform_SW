/*
    MobilePlatformType - a file that defines all the types used in the
    mobile platforms arduino software, declared as simple enums
*/

#ifndef MOB_PLATFOM_TYPES_H
#define MOB_PLATFOM_TYPES_H

#define INSTRUCTION_BUFFER_SIZE 256

/* RemoteComm definitions */
#define HANDSHAKE_RECEIVE_SIGNAL 'S'
#define HANDSHAKE_PULSE_INTERVAL 500
#define HANDSHAKE_SIGNAL_A 'A'
#define HANDSHAKE_SIGNAL_B 'B'

#define REMOTE_COMM_SEARCHNG_INTERVAL 100
#define REMOTE_COMM_CONNECTED_INTERVAL 333
#define REMOTE_COMM_DEBOUNCE_TIME_MS 200


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
