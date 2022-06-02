#include "vex.h"
#include "globals.h"
#include "actions.h"

void OpenFrontClaw() {
  FrontSolonoid.set(false);
}

void CloseFrontClaw() {
  FrontSolonoid.set(true);
}

void OpenRearClaw() {
  RearSolonoid.set(false);
}

void CloseRearClaw() {
  RearSolonoid.set(true);
}

void RaiseFourBar() {
  Lift.setMaxTorque(100, percent);
  Lift.setVelocity(70, percent);
  Lift.spin(forward);
}

void LowerFourBar() {
  Lift.setMaxTorque(100, percent);
  Lift.setVelocity(70, percent);
  Lift.spin(reverse);
}

void LockFourBar() {
  Lift.setStopping(hold);
  Lift.stop();
}

void SetDrivetrainMaxTorquePercent(int maxTorque) {
  driveL.setMaxTorque(maxTorque, percent);
  driveR.setMaxTorque(maxTorque, percent);
}

void SetDrivetrainStopping(brakeType mode) {
  myDrivetrain.setStopping(mode);
}

void SpinDrivetrain() {
  myDrivetrain.drive(forward);
}

void SetDriveValues() {
  // Controller1.Screen.clearLine();
  // Controller1.Screen.print("GEAR: " + GEAR);
  // calculate the drivetrain motor velocities from the controller joystick axies
  // left = Axis3 + Axis1
  // right = Axis3 - Axis1
  int drivetrainLeftSideSpeed = ((FORWARD_VELOCITY*DIRECTION) + TURNING_VELOCITY) / (HIGHEST_GEAR-GEAR+1);
  int drivetrainRightSideSpeed = ((FORWARD_VELOCITY*DIRECTION) - TURNING_VELOCITY) / (HIGHEST_GEAR-GEAR+1);
  
  // check if the value is inside of the deadband range
  if (drivetrainLeftSideSpeed < 5 && drivetrainLeftSideSpeed > -5) {
    driveL.stop();
  } else {
    driveL.setVelocity(drivetrainLeftSideSpeed, percent);
    driveL.spin(forward);
  }
  
  // check if the value is inside of the deadband range
  if (drivetrainRightSideSpeed < 5 && drivetrainRightSideSpeed > -5) {
    driveR.stop();
  } else {
    driveR.setVelocity(drivetrainRightSideSpeed, percent);
    driveR.spin(forward);
  }
}


