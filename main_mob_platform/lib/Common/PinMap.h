/*
    PinMap - a file that defines named lbels to pin numbers so that
    what a pin is mapped to can be assignned in one place
*/

/* Comm system pins */
#define COMM_TX_PIN         18          /* We transmit from this pin */
#define COMM_RX_PIN         19          /* We recieve on this pin */
#define COMM_ENABLE_PIN     -1          /* Not used */
#define COMM_STATE_PIN      22
#define COMM_BUTTON_PIN     23
#define COMM_LED_PIN        24
#define COMM_BAUD_RATE      9600

/* Drive System pins */
#define LEFT_MOTOR_DIR      10     /* Direction pin for LEFT drive stepper */
#define LEFT_MOTOR_STEP     9      /* Step pin for LEFT drive stepper */
#define LEFT_MOTOR_SLEEP    8      /* Sleep pin for LEFT drive stepper */

#define RIGHT_MOTOR_DIR     7     /* Direction pin for RIGHT drive stepper */
#define RIGHT_MOTOR_STEP    6     /* Step pin for RIGHT drive stepper */
#define RIGHT_MOTOR_SLEEP   5     /* Sleep PIN for RIGHT drive stepper */

/* Lidar System pins */
#define LIDAR_DIR           13    /* Direction pin for LIDAR stepper */
#define LIDAR_STEP          12    /* Step pin for LIDAR stepper */
#define LIDAR_MOTOR_SLEEP   11    /* Sleep PIN for LIDAR stepper */

#define LIDAR_BUTTON_A      18    /* Pin for button labeled A on proto board */
#define LIDAR_BUTTON_B      19    /* Pin for button labeled B on proto board */

#define LIDAR_MODULE_EN     17    /* Pin to power down and up the lidar module */

/* LCD Screen pins */
#define LCD_RS 48
#define LCD_EN 49
#define LCD_D4 50
#define LCD_D5 51
#define LCD_D6 52
#define LCD_D7 53

#define LCD_COLS 16
#define LCD_ROWS 2
