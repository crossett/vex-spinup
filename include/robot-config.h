using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor DriveLF;
extern motor DriveLM;
extern motor DriveLB;
extern motor DriveRF;
extern motor DriveRM;
extern motor DriveRB;
extern motor_group Lift;
extern digital_out RearSolonoid;
extern digital_out FrontSolonoid;
extern inertial Gyro;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );