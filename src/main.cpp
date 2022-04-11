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
// DriveRF              motor         9
// DriveRM              motor         8
// DriveRB              motor         7
// DriveLF              motor         1
// DriveLM              motor         2
// DriveLB              motor         3
// Gyro                 inertial      5
// RearSolonoid         digital_out   H
// FrontSolonoid        digital_out   G
// Lift                 motor_group   4, 6
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "setup.h"
#include "autonomous.h"
#include "drivercontrol.h"

using namespace vex;

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
