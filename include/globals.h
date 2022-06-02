#include "vex.h"

#define WHEELDIAMETER 4 // inches
#define WHEELCIRCUMFERENCE ((float)WHEELDIA * 3.14)
#define GEARRATIO ((float)84/36) // sprocket teeth, wheel/motor
#define WHEELBASE 13
#define DEGREEINCREMENT 10
#define OPEN 1
#define CLOSED 2

extern int FRONT_CLAW_STATE;
extern int BACK_CLAW_STATE;
extern int HIGHEST_GEAR;
extern int GEAR;
extern int DIRECTION; // 1 = forward, -1 = reverse
extern int TURNING_VELOCITY;
extern int FORWARD_VELOCITY;
extern drivetrain myDrivetrain;
extern motor_group driveL;
extern motor_group driveR;