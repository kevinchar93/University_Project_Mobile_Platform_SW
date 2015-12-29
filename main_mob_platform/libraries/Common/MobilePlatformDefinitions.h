/*
    MobilePlatformDefinitons.h - a file that defines all the types used in the
    mobile platform's arduino software
*/

#ifndef MOB_PLATFOM_DEFS_H
#define MOB_PLATFOM_DEFS_H

#include "MobilePlatformTypes.h"

/* Size of the instruction buffer used in the main.ino */
#define INSTRUCTION_BUFFER_SIZE 32

/* Defs related to the instruction handling */
#define PARSER_BUFFER_SIZE INSTRUCTION_FIELD_MAX
#define INSTRUCTION_VERIFIED_OK "INS_OK;"
#define INSTRUCTION_VERIFIED_ERROR "INS_ER;"
#define INSTRUCTION_COMPLETE "INS_DONE;"

/* Defs related to the serial handshake procedure */
#define HANDSHAKE_RECEIVE_SIGNAL 'S'
#define HANDSHAKE_PULSE_INTERVAL 500
#define HANDSHAKE_SIGNAL_A 'A'
#define HANDSHAKE_SIGNAL_B 'B'

/* Defs related to the RemoteComm waitForConnection procedure */
#define REMOTE_COMM_SEARCHNG_INTERVAL 100
#define REMOTE_COMM_CONNECTED_INTERVAL 333
#define REMOTE_COMM_DEBOUNCE_TIME_MS 200

/* Defs related to the robots motion */

/* Def related to the robots LIDAR */
#define MAX_LIDAR_ANGLE 360
#define LIDAR_DATA_BUFFER_SIZE 4500

#endif
