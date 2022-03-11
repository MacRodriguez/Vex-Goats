#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;
// no what wasnt working yesterday with bot
//idk i guess it might have been the invalid motor group constructors
// we had a different program that was working right (autoSchmingus)
//but  it stopped sworking for some reason and the robot wouldn't obey the code in auton mode and drive mode
//there was no syntax errors or parentheses error either idk what it was it wouldn't tell me
//so i made this new program but I forgot to copy over the motor group constructors

//whats the boolean at the end of the motor constructors for
//whether or not the motors are reversed
// VEXcode device constructors
motor leftMotorA = motor(PORT15, ratio6_1, false);
motor leftMotorB = motor(PORT16, ratio6_1, true);
motor leftMotorC = motor(PORT17, ratio6_1, true);
motor_group LeftDriveSmart = motor_group(leftMotorA, leftMotorB, leftMotorC);
motor rightMotorA = motor(PORT5, ratio6_1, true);
motor rightMotorB = motor(PORT7, ratio6_1, false);
motor rightMotorC = motor(PORT8, ratio6_1, false);
motor_group RightDriveSmart = motor_group(rightMotorA, rightMotorB, rightMotorC);
drivetrain Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, 319.19, 355.59999999999997, 127, mm, 0.42857142857142855);
motor backMotor = motor(PORT2, ratio18_1, false);
motor frontMotor = motor(PORT12, ratio18_1, false);
controller Controller1 = controller(primary);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;
// define variables used for controlling motors based on controller inputs
bool Controller1LeftShoulderControlMotorsStopped = true;
bool Controller1RightShoulderControlMotorsStopped = true;
bool DrivetrainLNeedsToBeStopped_Controller1 = true;
bool DrivetrainRNeedsToBeStopped_Controller1 = true;

// define a task that will handle monitoring inputs from Controller1
int rc_auto_loop_function_Controller1() {
  // process the controller input every 20 milliseconds
  // update the motors based on the input values
  while(true) {
    if(RemoteControlCodeEnabled) {
      // calculate the drivetrain motor velocities from the controller joystick axies
      // left = Axis3 + Axis1
      // right = Axis3 - Axis1
      int drivetrainLeftSideSpeed = Controller1.Axis3.position() + (0.75 * Controller1.Axis1.position());
      if(drivetrainLeftSideSpeed >= 0) {
        drivetrainLeftSideSpeed = (drivetrainLeftSideSpeed * drivetrainLeftSideSpeed)/127;
      } else {
        drivetrainLeftSideSpeed = (drivetrainLeftSideSpeed * drivetrainLeftSideSpeed)/-127;
      }
      int drivetrainRightSideSpeed = Controller1.Axis3.position() - (0.75 * Controller1.Axis1.position());
      if(drivetrainRightSideSpeed >= 0) {
        drivetrainRightSideSpeed = (drivetrainRightSideSpeed * drivetrainRightSideSpeed)/127;
      } else {
        drivetrainRightSideSpeed = (drivetrainRightSideSpeed * drivetrainRightSideSpeed)/-127;
      }
      
      // check if the value is inside of the deadband range
      if (drivetrainLeftSideSpeed < 5 && drivetrainLeftSideSpeed > -5) {
        // check if the left motor has already been stopped
        if (DrivetrainLNeedsToBeStopped_Controller1) {
          // stop the left drive motor
          LeftDriveSmart.setStopping(coast);
          LeftDriveSmart.stop();
          // tell the code that the left motor has been stopped
          DrivetrainLNeedsToBeStopped_Controller1 = false;
        }
      } else {
        // reset the toggle so that the deadband code knows to stop the left motor nexttime the input is in the deadband range
        DrivetrainLNeedsToBeStopped_Controller1 = true;
      }
      // check if the value is inside of the deadband range
      if (drivetrainRightSideSpeed < 5 && drivetrainRightSideSpeed > -5) {
        // check if the right motor has already been stopped
        if (DrivetrainRNeedsToBeStopped_Controller1) {
          // stop the right drive motor
          RightDriveSmart.setStopping(coast);
          RightDriveSmart.stop();
          // tell the code that the right motor has been stopped
          DrivetrainRNeedsToBeStopped_Controller1 = false;
        }
      } else {
        // reset the toggle so that the deadband code knows to stop the right motor next time the input is in the deadband range
        DrivetrainRNeedsToBeStopped_Controller1 = true;
      }
      
      // only tell the left drive motor to spin if the values are not in the deadband range
      if (DrivetrainLNeedsToBeStopped_Controller1) {
        LeftDriveSmart.setVelocity(drivetrainLeftSideSpeed, percent);
        LeftDriveSmart.spin(forward);
      }
      // only tell the right drive motor to spin if the values are not in the deadband range
      if (DrivetrainRNeedsToBeStopped_Controller1) {
        RightDriveSmart.setVelocity(drivetrainRightSideSpeed, percent);
        RightDriveSmart.spin(forward);
      }
      // check the ButtonL1/ButtonL2 status to control frontMotor
      if (Controller1.ButtonR1.pressing()) {
        frontMotor.spin(reverse);
        Controller1RightShoulderControlMotorsStopped = false;
      } else if (Controller1.ButtonR2.pressing()) {
        frontMotor.spin(forward);
        Controller1RightShoulderControlMotorsStopped = false;
      } else if (!Controller1RightShoulderControlMotorsStopped) {
        frontMotor.setStopping(hold);
        frontMotor.stop();
        // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
        Controller1RightShoulderControlMotorsStopped = true;
      }
      // check the ButtonR1/ButtonR2 status to control backMotor
      if (Controller1.ButtonL1.pressing()) {
        backMotor.spin(reverse);
        Controller1LeftShoulderControlMotorsStopped = false;
      } else if (Controller1.ButtonL2.pressing()) {
        backMotor.spin(forward);
        Controller1LeftShoulderControlMotorsStopped = false;
      } else if (!Controller1LeftShoulderControlMotorsStopped) {
        backMotor.setStopping(hold);
        backMotor.stop();
        // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
        Controller1LeftShoulderControlMotorsStopped = true;
      }
    }
    // wait before repeating the process
    wait(20, msec);
  }
  return 0;
}

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  task rc_auto_loop_task_Controller1(rc_auto_loop_function_Controller1);
}