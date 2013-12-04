#ifndef ROBOHOCKEY_EXTERN_ANGELINA_HERMESCODES_H
#define ROBOHOCKEY_EXTERN_ANGELINA_HERMESCODES_H

// Message types
// Control messages
#define HERMES_CONNECT				1
#define HERMES_STATUS				2

#define HERMES_LEFT_PLAYGROUND		3
#define HERMES_GAME_START			4
#define HERMES_GAME_OVER			5
#define HERMES_READY				6
#define HERMES_DONE					7
#define HERMES_ERROR				8
#define HERMES_KEEP_ALIVE			9

// Data messages for angelina
#define HERMES_DATA_T1				11
#define HERMES_DATA_T2				12
#define HERMES_DATA_T3				13
#define HERMES_DATA_T4				14

// Data messages for the robots
#define HERMES_SCORE				21
#define HERMES_A_B					22

#define HERMES_LOOKINGFOR			31
#define HERMES_ANGELINAFOUND		32

#define HERMES_DETECTION_START		41
#define HERMES_STOP_MOVEMENT		42
#define HERMES_TEAMCOLOR			43

#endif
