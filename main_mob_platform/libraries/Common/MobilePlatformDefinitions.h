/*
    MobilePlatformDefinitons.h - a file that defines all the types used in the
    mobile platform's arduino software
*/

#ifndef MOB_PLATFOM_DEFS_H
#define MOB_PLATFOM_DEFS_H

#include "MobilePlatformTypes.h"

/* Size of the instruction buffer used in the main.ino */
#define INSTRUCTION_BUFFER_SIZE 32

/* Defs related to the instruction parser utility function */
#define PARSER_BUFFER_SIZE INSTRUCTION_FIELD_MAX

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
#define MAX_SINGLE_TRAVEL_DIST_CM 500
#define MAX_SINGLED_TRAVEL_DIST_GRID 20

/* Def related to the robots LIDAR */
#define MAX_LIDAR_ANGLE 360

#endif
