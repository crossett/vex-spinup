#include "vex.h"

void OpenFrontClaw();
void CloseFrontClaw();
void OpenRearClaw();
void CloseRearClaw();
void RaiseFourBar();
void LowerFourBar();
void LockFourBar();
void SetDrivetrainMaxTorquePercent(int maxTorque);
void SetDrivetrainStopping(brakeType mode);
void SpinDrivetrain();
void SetDrivetrainVelocityPercent(int velocityPercent);
void SetDrivetrainTurningPercent(int turningPercent);
void SetDriveValues();