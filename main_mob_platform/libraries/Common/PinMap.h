/*
    PinMap - a file that defines named lbels to pin numbers so that
    what a pin is mapped to can be assignned in one place
*/

/* Comm system pins */
#define COMM_TX_PIN 18          // we transmit from this pin
#define COMM_RX_PIN 19          // we recieve on this pin
#define COMM_ENABLE_PIN -1      // not used
#define COMM_STATE_PIN 22
#define COMM_BUTTON_PIN 23
#define COMM_LED_PIN 24
#define COMM_BAUD_RATE 9600

/* Drive System pins */
#define DS_EN 8   /* Enable pin for the drive system */

#define LEFT_DIR 5   /* Direction pin for left (X) stepper */
#define LEFT_STEP 2  /* Step pin for left (X) stepper */

#define RIGHT_DIR 6   /* Direction pin for right (Y) stepper */
#define RIGHT_STEP 3  /* Step pin for right (Y) stepper */

/* Lidar System pins */
#define LIDAR_DIR 7   /* Direction pin for LIDAR (Z) stepper */
#define LIDAR_STEP 4  /* Step pin for LIDAR (Z) stepper */
#define LIDAR_BUTTON_A 25
#define LIDAR_BUTTON_B 26
