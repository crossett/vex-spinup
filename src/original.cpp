/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       eldon                                                     */
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

using namespace vex;

// Begin project code
#define GreatestAuton 1
#define LeastAuton 0

#define WHEELDIA 4 // inches
#define WHEELCIRCUMFERENCE ((float)WHEELDIA * 3.14)
#define GEARRATIO ((float)84 / 36) // sprocket teeth, wheel/motor
#define WHEELBASE 13
#define DEGREEINCREMENT 10
#define OPEN 1
#define CLOSED 2

void OpenFrontClaw();
void CloseFrontClaw();
void OpenRearClaw();
void CloseRearClaw();

int autonSelect = 1;
void preAutonomous(void) {
  // actions to do when the program starts
  Brain.Screen.clearScreen();
  Gyro.calibrate();
  while (Gyro.isCalibrating())
    ;
  Brain.Screen.print("CALIBRATED:   pre auton code");
  Lift.setStopping(hold);
  wait(1, seconds); // before erasing the screen
  while (true) {
    // touchscreen autonomous selection
    Brain.Screen.clearScreen();
    Brain.Screen.drawLine(200, 0, 200,
                          200); // draw a line through the middle of the screen
    Brain.Screen.setCursor(1, 1);
    switch (autonSelect) {
    case 0:
      Brain.Screen.print("Skills Auton");
      break;
    case 1:
      Brain.Screen.print("Match Auton");
      break;
    default:
      Brain.Screen.print("Error");
    }
    Brain.Screen.setCursor(1, 40);
    Brain.Screen.print("Enter");

    if (Brain.Screen.pressing()) // upon touching the screen
    {
      if (Brain.Screen.xPosition() < 200) // if the touch is on the left side
      {
        // cycle through autonomus programs
        if (autonSelect >= GreatestAuton)
          autonSelect = LeastAuton;
        else
          autonSelect++;

        while (Brain.Screen.pressing()) {
        }
      }
      // if on the right side, exit. AutonSelect is now locked in.
      else
        break;
    }
    wait(20, msec);
  }
  Brain.Screen.clearScreen();
}
int gearing = 1;
int direction = 1; // 1 = forward, -1 = reverse
void CloseFrontClaw();
void raiseLowerArm(int, int);

void checkVelocityLevel() {
  DriveLF.setVelocity((Controller1.Axis3.position() * direction +
                       Controller1.Axis1.position()) /
                          gearing,
                      percent);
  DriveLM.setVelocity((Controller1.Axis3.position() * direction +
                       Controller1.Axis1.position()) /
                          gearing,
                      percent);
  DriveLB.setVelocity((Controller1.Axis3.position() * direction +
                       Controller1.Axis1.position()) /
                          gearing,
                      percent);
  DriveRF.setVelocity((Controller1.Axis3.position() * direction -
                       Controller1.Axis1.position()) /
                          gearing,
                      percent);
  DriveRM.setVelocity((Controller1.Axis3.position() * direction -
                       Controller1.Axis1.position()) /
                          gearing,
                      percent);
  DriveRB.setVelocity((Controller1.Axis3.position() * direction -
                       Controller1.Axis1.position()) /
                          gearing,
                      percent);
}
// void stopAlldrive() {
//   DriveLF.setStopping(hold);
//   DriveLM.setStopping(hold);
//   DriveLB.setStopping(hold);
//   DriveRF.setStopping(hold);
//   DriveRM.setStopping(hold);
//   DriveRB.setStopping(hold);
//   DriveLF.stop();
//   DriveLM.stop();
//   DriveLB.stop();
//   DriveRF.stop();
//   DriveRM.stop();
//   DriveRB.stop();
// }

void CloseAndLift() {
  CloseFrontClaw();
  checkVelocityLevel();
  raiseLowerArm(2000, 1);
}

void setDriveSpeed(int speed) {
  DriveLB.setVelocity(speed, percent);
  DriveLM.setVelocity(speed, percent);
  DriveLF.setVelocity(speed, percent);
  DriveRB.setVelocity(speed, percent);
  DriveRM.setVelocity(speed, percent);
  DriveRF.setVelocity(speed, percent);
}

void PushTo(int speedperc, int timeout,
            int direction) // time in milliseconds.  Dir 1=fwd, -1=reverse
{
  DriveLF.setMaxTorque(40, percent);
  DriveLM.setMaxTorque(40, percent);
  DriveRF.setMaxTorque(40, percent);
  DriveLB.setMaxTorque(40, percent);
  DriveRM.setMaxTorque(40, percent);
  DriveRB.setMaxTorque(40, percent);
  if (direction > 0) {
    DriveLF.spin(forward, speedperc, percent);
    DriveLM.spin(forward, speedperc, percent);
    DriveRF.spin(forward, speedperc, percent);
    DriveLB.spin(forward, speedperc, percent);
    DriveRM.spin(forward, speedperc, percent);
    DriveRB.spin(forward, speedperc, percent);
  } else {
    DriveLF.spin(reverse, speedperc, percent);
    DriveLM.spin(forward, speedperc, percent);
    DriveRF.spin(reverse, speedperc, percent);
    DriveLB.spin(reverse, speedperc, percent);
    DriveRM.spin(forward, speedperc, percent);
    DriveRB.spin(reverse, speedperc, percent);
  }
  wait(timeout, msec);
  DriveLF.setStopping(coast);
  DriveLM.setStopping(coast);
  DriveRF.setStopping(coast);
  DriveLB.setStopping(coast);
  DriveRM.setStopping(coast);
  DriveRB.setStopping(coast);
  DriveLF.stop();
  DriveLM.stop();
  DriveLB.stop();
  DriveRF.stop();
  DriveRM.stop();
  DriveRB.stop();
  DriveLF.setMaxTorque(100, percent);
  DriveLM.setMaxTorque(100, percent);
  DriveRF.setMaxTorque(100, percent);
  DriveLB.setMaxTorque(100, percent);
  DriveRM.setMaxTorque(100, percent);
  DriveRB.setMaxTorque(100, percent);
} // push to

void betterDriveTo(int speedperc, float distance, int do_coast) {
  float turnDist = distance * GEARRATIO / WHEELCIRCUMFERENCE;

  DriveLF.setPosition(0, degrees);
  DriveLM.setPosition(0, degrees);
  DriveLB.setPosition(0, degrees);
  DriveRF.setPosition(0, degrees);
  DriveRM.setPosition(0, degrees);
  DriveRB.setPosition(0, degrees);
  if (distance > 0) // to move "forward"
  {
    while (DriveLF.position(turns) < turnDist) {
      DriveLF.spin(forward, speedperc, percent);
      DriveLM.spin(forward, speedperc, percent);
      DriveRF.spin(forward, speedperc, percent);
      DriveLB.spin(forward, speedperc, percent);
      DriveRM.spin(forward, speedperc, percent);
      DriveRB.spin(forward, speedperc, percent);
    }
  } else // to move "backward"
  {
    while (DriveLF.position(turns) > turnDist) {
      DriveLF.spin(reverse, speedperc, percent);
      DriveLM.spin(reverse, speedperc, percent);
      DriveRF.spin(reverse, speedperc, percent);
      DriveLB.spin(reverse, speedperc, percent);
      DriveRM.spin(reverse, speedperc, percent);
      DriveRB.spin(reverse, speedperc, percent);
    }
  }
  if (do_coast == 0) // not coast, brake
  {
    DriveLF.setStopping(brake);
    DriveLM.setStopping(brake);
    DriveRF.setStopping(brake);
    DriveLB.setStopping(brake);
    DriveRM.setStopping(brake);
    DriveRB.setStopping(brake);
  } else // coast
  {
    DriveLF.setStopping(coast);
    DriveLM.setStopping(coast);
    DriveRF.setStopping(coast);
    DriveLB.setStopping(coast);
    DriveRM.setStopping(coast);
    DriveRB.setStopping(coast);
  }
  DriveLF.stop();
  DriveLM.stop();
  DriveLB.stop();
  DriveRF.stop();
  DriveRM.stop();
  DriveRB.stop();
} // better drive to

#define Kpg ((float)(0.8))

void GyroDriveTo(int speedperc, float distance, int do_coast, float heading) {
  float AngError = heading - Gyro.rotation(degrees);
  float turnDist = distance * GEARRATIO / WHEELCIRCUMFERENCE;
  DriveLF.setPosition(0, degrees);
  DriveLM.setPosition(0, degrees);
  DriveRM.setPosition(0, degrees);
  DriveLB.setPosition(0, degrees);
  DriveRF.setPosition(0, degrees);
  DriveRB.setPosition(0, degrees);
  if (distance < 0)
    speedperc = 0 - speedperc;
  DriveLF.spin(forward, speedperc, percent);
  DriveLM.spin(forward, speedperc, percent);
  DriveRM.spin(forward, speedperc, percent); // start all the motors
  DriveRF.spin(forward, speedperc, percent);
  DriveLB.spin(forward, speedperc, percent);
  DriveRB.spin(forward, speedperc, percent);
  if (distance > 0) // to move "forward"
  {
    while (DriveLF.position(turns) < turnDist) {
      AngError = heading - Gyro.rotation(degrees);
      DriveLF.setVelocity(speedperc + Kpg * AngError, percent);
      DriveLM.setVelocity(speedperc + Kpg * AngError, percent);
      DriveRM.setVelocity(speedperc + Kpg * AngError, percent);
      DriveLB.setVelocity(speedperc + Kpg * AngError, percent);
      DriveRF.setVelocity(speedperc - Kpg * AngError, percent);
      DriveRB.setVelocity(speedperc - Kpg * AngError, percent);
      wait(50, msec);
    }
  } else // to move "backward"
  {
    while (DriveLF.position(turns) > turnDist) {
      AngError = heading - Gyro.rotation(degrees);
      DriveLF.setVelocity(speedperc + Kpg * AngError, percent);
      DriveLM.setVelocity(speedperc + Kpg * AngError, percent);
      DriveRM.setVelocity(speedperc + Kpg * AngError, percent);
      DriveLB.setVelocity(speedperc + Kpg * AngError, percent);
      DriveRF.setVelocity(speedperc - Kpg * AngError, percent);
      DriveRB.setVelocity(speedperc - Kpg * AngError, percent);
      wait(50, msec);
    }
  }
  if (do_coast == 0) // not coast, brake
  {
    DriveLF.setStopping(brake);
    DriveLM.setStopping(brake);
    DriveRM.setStopping(brake);
    DriveRF.setStopping(brake);
    DriveLB.setStopping(brake);
    DriveRB.setStopping(brake);
  } else // coast
  {
    DriveLF.setStopping(coast);
    DriveLM.setStopping(coast);
    DriveRM.setStopping(coast);
    DriveRF.setStopping(coast);
    DriveLB.setStopping(coast);
    DriveRB.setStopping(coast);
  }
  DriveLF.stop();
  DriveLM.stop();
  DriveRM.stop();
  DriveLB.stop();
  DriveRF.stop();
  DriveRB.stop();
} // gyro drive

void OpenFrontClaw() { FrontSolonoid.set(false); }

void CloseFrontClaw() { FrontSolonoid.set(true); }
void OpenRearClaw() { RearSolonoid.set(false); }
void CloseRearClaw() { RearSolonoid.set(true); }

/* we should define the units that will be used in all calls
   For turning, the units will be degreee
   For driving the units will be inches.
*/

void spinDrive(int degree) {
  //   int runningDegree = 0;
  //   while (runningDegree <= degree){
  DriveLB.spinFor(reverse, degree, degrees, false);
  DriveLM.spinFor(reverse, degree, degrees, false);
  DriveRM.spinFor(reverse, degree, degrees, false);
  DriveRB.spinFor(forward, degree, degrees, false);
  DriveLF.spinFor(reverse, degree, degrees, false);
  DriveRF.spinFor(forward, degree, degrees,
                  true); // true makes it wait before continuing
                         //   runningDegree+=DEGREEINCREMENT;
                         //   }
}
void betterTurn(int angle) {
  // wheels are 4";  wheelbase is 13"
  int degree = 2.35 * angle;
  setDriveSpeed(15);
  spinDrive(degree);
}
void raiseLowerArm(
    int amount, int direction) { // this is time based.  Recode for turns based.
  // amount is time in msec;  direction: >0 up; 0 or less, down
  Lift.setMaxTorque(100, percent);
  Lift.setVelocity(70, percent);
  if (direction > 0) { // upward
    Lift.setMaxTorque(100, percent);
    Lift.spin(forward);
    wait(amount, msec); // going upward for a time
    Lift.setStopping(hold);
    Lift.stop();
  } else { // downward
    Lift.setMaxTorque(40, percent);
    Lift.spin(reverse);
    wait(amount, msec);             // going downward for a time
    Lift.setMaxTorque(10, percent); // leave it onpushing down at 10% power
  }
}

// void motortimeout(int time) // sets all drive motor timeout in int seconds
// {
//   DriveLF.setStopping(coast);
//   DriveLM.setStopping(coast);
//   DriveRM.setStopping(coast);
//   DriveLB.setStopping(coast);
//   DriveRF.setStopping(coast);
//   DriveRB.setStopping(coast);
//   DriveLF.setTimeout(time, seconds);
//   DriveLF.stop();
//   DriveLM.setTimeout(time, seconds);
//   DriveLM.stop();
//   DriveRF.setTimeout(time, seconds);
//   DriveRF.stop();
//   DriveLB.setTimeout(time, seconds);
//   DriveLB.stop();
//   DriveRB.setTimeout(time, seconds);
//   DriveRB.stop();
//   DriveRM.setTimeout(time, seconds);
//   DriveRM.stop();
// }

void autonomous(void) {
  Brain.Screen.clearScreen();
  Brain.Screen.print("autonomous code");

  switch (autonSelect) {
  case 0:

    //  driveTo(50,-24);  // testing line only

#define dothefirstpart
#ifdef dothefirstpart
    Gyro.setRotation(10, degrees);
    CloseFrontClaw();         // grab it
    raiseLowerArm(300, 1);    // lift it to clear ramp
    wait(500, msec);          // pause
    betterDriveTo(30, -6, 0); // back up 6"
    wait(500, msec);
    betterTurn(-79); // needs extra angle because of weight?
    wait(1000, msec);
    // raiseLowerArm(800,-1);  // bring it down after turn so it can hit mogo

    // Drive diagonaly accross field
    // betterDriveTo(50,-84,0);  // forward 72" = 3 tiles

    GyroDriveTo(50, -84, 0, 100);

    betterDriveTo(50, 6, 0);     // back away from nuetral goal
    betterTurn(42);              // Turn towards back left corner
    GyroDriveTo(40, -30, 0, 45); // drive backwards into corner
    OpenFrontClaw();             // release goal
    betterTurn(50);              // turn to wall
    raiseLowerArm(800, -1);
    PushTo(80, 1000, -1); // drive to wall and push on it
    // wait(2, seconds);
    betterDriveTo(30, 3, 0);       // forward off wall a bit
    betterTurn(90);                // Turn towards goal
    GyroDriveTo(50, -124, 0, -90); // Drive goal into corner of field
    // goalis in the corner
    betterDriveTo(40, 12, 0); // Drive forward to clear goal
    betterTurn(-60);          // Turn towards wall
    PushTo(80, 2000, -1);     // push into wall
#endif
    GyroDriveTo(40, 87, 0, -4); // Drive forward across field
    betterTurn(78);             // turn towards mobile goal

    betterDriveTo(30, 26, 0); // Go to mobile goal
    CloseFrontClaw();         // Grab goal
    raiseLowerArm(400, 1);    // Lift it alittle bit to drag it

    betterDriveTo(30, -26, 0); // back up dragging mogo
    raiseLowerArm(1600, 1);    // Lift it
    betterTurn(80);            //  turn left
    betterDriveTo(15, 30, 0);
    betterTurn(80);
    PushTo(20, 1000, 1);
    OpenFrontClaw();
    betterDriveTo(30, -60, 0);

    break;
  case 1: // AWP solo auton
    /*Gyro.setRotation(0,degrees);  // initialize the gyro to the present
 heading betterDriveTo(30,20,0); closeClaw(); raiseLowerArm(600,1);
    betterTurn(-30);
    betterDriveTo(20,-13,0);
    betterTurn(-80);
    openClaw();
    betterDriveTo(20,-4,0);
    betterTurn(33);
    GyroDriveTo(35,-77,0,90); // long drive
    betterTurn(90);
   betterDriveTo(20,-9,0);
    MoGotor.setMaxTorque(10,percent);
    MoGotor.setVelocity(50,percent);
    MoGotor.spin(forward);
    wait(1000,msec);
 betterDriveTo(10,10,0);
    MoGotor.spin(reverse);
    MoGotor.setMaxTorque(100,percent);
     wait(100,msec);
     MoGotor.stop(); */

    // Goal rush auton

    betterDriveTo(90, 41, 1);
    wait(100, msec);
    CloseFrontClaw();
    wait(100, msec);
    betterDriveTo(40, -40, 0);

    /*betterDriveTo(50,18,0);
    CloseFrontClaw();
    betterDriveTo(50,-18,0);
    OpenRearClaw();*/
    // Right side 1/2 AWP

    /*CloseFrontClaw();
     wait(100, msec);
     betterDriveTo(50,-10,0);
     OpenFrontClaw();
     //Left 1/2 AWP*/
  default:
    break;
  }
}

void setDriveStopping(vex::brakeType stoppingValue) {
  DriveLF.setStopping(stoppingValue);
  DriveLM.setStopping(stoppingValue);
  DriveRM.setStopping(stoppingValue);
  DriveLB.setStopping(stoppingValue);
  DriveRF.setStopping(stoppingValue);
  DriveRB.setStopping(stoppingValue);
}

void userControl(void) {
  // int FrontClawState = OPEN;
  // int BackClawState = OPEN;

  setDriveStopping(coast);

  Brain.Screen.clearScreen();
  Brain.Screen.print("driver code");
  // place driver control in this while loop
  DriveLF.setMaxTorque(100, percent);
  DriveLM.setMaxTorque(100, percent);
  DriveRM.setMaxTorque(100, percent);
  DriveLM.setMaxTorque(100, percent);
  DriveLB.setMaxTorque(100, percent);
  DriveRB.setMaxTorque(100, percent);
  DriveRM.setMaxTorque(100, percent);
  DriveRF.setMaxTorque(100, percent);
  while (true) {
    wait(20, msec);
    checkVelocityLevel();

    if (
      gearing == 2
      || gearing == 3
      || (gearing == 4 && (abs(Controller1.Axis3.position()) > 5 || abs(Controller1.Axis1.position()) > 5))
    ) {
      DriveLF.spin(forward);
      DriveLM.spin(forward);
      DriveLB.spin(forward);
      DriveRF.spin(forward);
      DriveRM.spin(forward);
      DriveRB.spin(forward);
    } else {
      DriveLF.stop();
      DriveLM.stop();
      DriveLB.stop();
      DriveRF.stop();
      DriveRM.stop();
      DriveRB.stop();
    }

    if (Controller1.ButtonA.pressing()) {
      CloseAndLift();
    } // sets the gearing to 1 if the A button is being pressed
    if (Controller1.ButtonB.pressing()) {
      gearing = 2;
      setDriveStopping(coast);
    } // sets the gearing to 2 if the B button is being pressed
    if (Controller1.ButtonX.pressing()) {
      gearing = 3;
      setDriveStopping(coast);
    } // sets the gearing to 3 if the X button is being pressed
    if (Controller1.ButtonY.pressing()) {
      gearing = 4;
      setDriveStopping(hold);
    } // sets the gearing to 4 if the Y button is being pressed

    if (Controller1.ButtonLeft.pressing()) {
      direction = -1;
    } // reverses the drive if the left button is being pressed
    if (Controller1.ButtonRight.pressing()) {
      direction = 1;
    } // forwards the drive if the left button is being pressed

    // sets the speed of each motor (in percent) to the position of the relevant
    // joystick, divides the speed by the gearing, and spins the drive motors
    if (Controller1.ButtonL1.pressing()) {
      Lift.setMaxTorque(100, percent);
      Lift.setVelocity(70, percent);
      Lift.spin(forward);
    } // If L1 is pressed, it spins the pringtake out
    else if (Controller1.ButtonL2.pressing()) {
      // Lift.setMaxTorque(20,percent);  // use this to go down with limited
      // force
      Lift.setVelocity(70, percent);
      Lift.spin(reverse);
    } // If L2 is pressed, it spins the pringtake in
    else {
      Lift.setStopping(hold);
      Lift.stop();
    } // If neither L1 nor L2 are being pressed, the pringtake is stationary

    if (Controller1.ButtonUp.pressing()) {
      OpenFrontClaw();
      // FrontClawState = OPEN;
    }
    if (Controller1.ButtonDown.pressing()) {
      CloseFrontClaw();
      // FrontClawState = CLOSED;
    }

    // If neither L1 nor L2 are being pressed, the pringtake is stationary

    if (Controller1.ButtonR1.pressing()) {
      OpenRearClaw();
      // BackClawState = OPEN;
    }
    if (Controller1.ButtonR2.pressing()) {
      CloseRearClaw();
      // BackClawState = CLOSED;
    }

    // If neither R1 or R2 are being pressed, the mobile goal lift is stationary

    // Mogofourbar.setVelocity(100,percent);
    // if (Controller1.ButtonUp.pressing()) {
    // Mogofourbar.spin(forward);
    //} //If the up button is being pressed, the mogo four bar will go up
    // else if (Controller1.ButtonDown.pressing()) {
    // Mogofourbar.spin(reverse);
    //} //If the down button is being pressed, the mogo four bar will go down
    // else
    // Mogofourbar.stop()
  }
}


// #######################################################################################
// #######################################################################################
// #######################################################################################

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // create competition instance
  competition Competition;

  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  // Competition.drivercontrol(userControl);
  Competition.drivercontrol(drivercontrol);

  // Run the pre-autonomous function.
  preAutonomous();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(0.001, seconds);
  }
}
