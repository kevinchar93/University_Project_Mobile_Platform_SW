/*
    MobilePlatformDefinitons.h - a file that defines all the types used in the
    mobile platform's arduino software
*/

#ifndef MOB_PLATFOM_DEFS_H
#define MOB_PLATFOM_DEFS_H

#include "MobilePlatformTypes.h"

/* Size of the instruction buffer used in the main_mob_platform.ino */
#define INSTRUCTION_BUFFER_SIZE 32

/* Defs related to the instruction handling */
#define PARSER_BUFFER_SIZE 3    // instructions have upto 3 components: type, value & gridmode
#define INSTRUCTION_VERIFIED_OK "INS_OK"
#define INSTRUCTION_VERIFIED_ERROR "INS_ERR"
#define INSTRUCTION_COMPLETE "INS_DONE"
#define INSTRUCTION_DATA_AVAILABLE "INS_DATA_AVAIL"
#define INSTRUCTION_DELAY 250

/* Defs related to the robots motion */
#define MAX_DRIVE_SPEED 250

/* Def related to the robots LIDAR */
#define MAX_LIDAR_ANGLE 360

/* Def related to how much to delay the main loop by each call */
#define MAIN_LOOP_DELAY 100

/* max number of readings is 360, buffer size is this multiplied by max number of bytes
   per reading str (11) plus semicolon and teminating null character giving total of 3962 bytes
   3964 used as it is closest sufficient multiple of 4 */
//#define LIDAR_DATA_BUFFER_SIZE 3964

/* In reality the mega platform has limited memory, and with the sample interval defined in Lidar360
   by LIDAR_SAMPLE_INTERVAL being 20, 35 measurements will be taken, 35 * 11 bytes per string
   representation of each measurment = 385 bytes, rounded to 400 */
#define LIDAR_DATA_BUFFER_SIZE 400

/* Smaller buffer for getting the distance at a given heading */
#define LIDAR_HEADING_DIST_BUFFER 20
#endif
