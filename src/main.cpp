/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       TA Engineer                                               */
/*    Created:      Fri Apr 08 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// DriveLF              motor         1               
// DriveLM              motor         2               
// DriveLB              motor         3               
// DriveRF              motor         9               
// DriveRM              motor         8               
// DriveRB              motor         7               
// Lift                 motor_group   6, 4            
// RearSolonoid         digital_out   H               
// FrontSolonoid        digital_out   G               
// Gyro                 inertial      5               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "setup.h"
#include "autonomous.h"
#include "drivercontrol.h"
#include "globals.h"

/* TODO:

Brain Screen:
* 

Controller Screen:
* Motor temp

*/
using namespace vex;

int FRONT_CLAW_STATE = OPEN;
int BACK_CLAW_STATE = OPEN;
int HIGHEST_GEAR = 4;
int GEAR = 1;
int DIRECTION = -1; // -1 = forward, 1 = reverse
int TURNING_VELOCITY = 0;
int FORWARD_VELOCITY = 0;
const float wheelTravel = 319.19;
const int trackWidth = 382;
const int wheelBase = 254;
motor_group driveL(DriveLF, DriveLM, DriveLB);
motor_group driveR(DriveRF, DriveRM, DriveRB);
drivetrain myDrivetrain(driveL, driveR, wheelTravel, trackWidth, wheelBase, mm, 0.42857142857142855);

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // Register Controller Callback Functions
  registerControllerCallbackFunctions();

  // create competition instance
  competition Competition;

  // Set up callbacks for autonomous and driver control periods
  Competition.autonomous(autonomous);
  Competition.drivercontrol(drivercontrol);

  // Run setup function
  setup();

  // Prevent main from exiting with an infinite loop
  while (true) {
    wait(0.001, seconds);
  }
}
