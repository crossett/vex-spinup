#include "vex.h"
#include "drivercontrol.h"
#include "actions.h"
#include "globals.h"

// Driver Controll Setup/Loop
void drivercontrol() {
  // Driver Control setup
  SetDrivetrainMaxTorquePercent(100);
  SetDriveValues();
  SpinDrivetrain();
  Brain.Screen.clearScreen();
  Brain.Screen.print("drivercontrol");

  // Handle adaptive driver control
  while (true) {
    wait(.001, seconds);
  }
}

/**
* Controller Inputs
**/

// Button A
void buttonAPressed()
{
  Brain.Screen.print("Event has occurred");
}
void buttonAReleased()
{
  Brain.Screen.print("Event has occurred");
}

// Button: B
void buttonBPressed()
{
  // Brain.Screen.print("Event has occurred");
  if (GEAR > 1) {
    GEAR--;
    SetDriveValues();
    if (GEAR == 1) {
      Controller1.rumble(".");
      SetDrivetrainStopping(hold);
    }
  }
}
void buttonBReleased()
{
  Brain.Screen.print("Event has occurred");
}

// Button: X
void buttonXPressed()
{
  // Brain.Screen.print("Event has occurred");
  if (GEAR < HIGHEST_GEAR) {
    GEAR++;
    SetDriveValues();
    SetDrivetrainStopping(coast);
  }
}
void buttonXReleased()
{
  Brain.Screen.print("Event has occurred");
}

// Button: Y
void buttonYPressed()
{
  // Brain.Screen.print("Event has occurred");
}
void buttonYReleased()
{
  Brain.Screen.print("Event has occurred");
}

// Button: Up
void buttonUpPressed()
{
  // Brain.Screen.print("Event has occurred");
  OpenFrontClaw();
}
void buttonUpReleased()
{
  Brain.Screen.print("Event has occurred");
}

// Button: Down
void buttonDownPressed()
{
  // Brain.Screen.print("Event has occurred");
  CloseFrontClaw();
}
void buttonDownReleased()
{
  Brain.Screen.print("Event has occurred");
}

// Button: Left
void buttonLeftPressed()
{
  // Brain.Screen.print("Event has occurred");
  DIRECTION *= -1;
  SetDriveValues();
}
void buttonLeftReleased()
{
  Brain.Screen.print("Event has occurred");
}

// Button: Right
void buttonRightPressed()
{
  Brain.Screen.print("Event has occurred");
}
void buttonRightReleased()
{
  Brain.Screen.print("Event has occurred");
}

// Button: L1
void buttonL1Pressed()
{
  //Brain.Screen.print("Event has occurred");
  RaiseFourBar();
}
void buttonL1Released()
{
  // Brain.Screen.print("Event has occurred");
  LockFourBar();
}

// Button: L2 
void buttonL2Pressed()
{
  // Brain.Screen.print("Event has occurred");
  LowerFourBar();
}
void buttonL2Released()
{
  // Brain.Screen.print("Event has occurred");
  LockFourBar();
}

// Button: R1
void buttonR1Pressed()
{
  // Brain.Screen.print("Event has occurred");
  OpenRearClaw();
}
void buttonR1Released()
{
  Brain.Screen.print("Event has occurred");
}

// Button: R2
void buttonR2Pressed()
{
  // Brain.Screen.print("Event has occurred");
  CloseRearClaw();
}
void buttonR2Released()
{
  Brain.Screen.print("Event has occurred");
}

// Axes
void axis1Changed()
{
  Brain.Screen.print("Event has occurred");
  TURNING_VELOCITY = Controller1.Axis1.position(percent)*-1;
  SetDriveValues();
}
void axis2Changed()
{
  Brain.Screen.print("Event has occurred");
}
void axis3Changed()
{
  //Brain.Screen.print("Event has occurred");
  FORWARD_VELOCITY = Controller1.Axis3.position(percent);
  SetDriveValues();
}
void axis4Changed()
{
  Brain.Screen.print("Event has occurred");
}

// Callback Registration
void registerControllerCallbackFunctions() {
  Controller1.ButtonA.pressed(buttonAPressed);
  Controller1.ButtonA.released(buttonAReleased);
  Controller1.ButtonB.pressed(buttonBPressed);
  Controller1.ButtonB.released(buttonBReleased);
  Controller1.ButtonX.pressed(buttonXPressed);
  Controller1.ButtonX.released(buttonXReleased);
  Controller1.ButtonY.pressed(buttonYPressed);
  Controller1.ButtonY.released(buttonYReleased);
  Controller1.ButtonUp.pressed(buttonUpPressed);
  Controller1.ButtonUp.released(buttonUpReleased);
  Controller1.ButtonDown.pressed(buttonDownPressed);
  Controller1.ButtonDown.released(buttonDownReleased);
  Controller1.ButtonLeft.pressed(buttonLeftPressed);
  Controller1.ButtonLeft.released(buttonLeftReleased);
  Controller1.ButtonRight.pressed(buttonRightPressed);
  Controller1.ButtonRight.released(buttonRightReleased);
  Controller1.ButtonL1.pressed(buttonL1Pressed);
  Controller1.ButtonL1.released(buttonL1Released);
  Controller1.ButtonL2.pressed(buttonL2Pressed);
  Controller1.ButtonL2.released(buttonL2Released);
  Controller1.ButtonR1.pressed(buttonR1Pressed);
  Controller1.ButtonR1.released(buttonR1Released);
  Controller1.ButtonR2.pressed(buttonR2Pressed);
  Controller1.ButtonR2.released(buttonR2Released);
  Controller1.Axis1.changed(axis1Changed);
  Controller1.Axis2.changed(axis2Changed);
  Controller1.Axis3.changed(axis3Changed);
  Controller1.Axis4.changed(axis4Changed);
}