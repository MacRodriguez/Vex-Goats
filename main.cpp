/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       macrodriguez                                              */
/*    Created:      Thu Mar 10 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  Drivetrain.setDriveVelocity(100, rpm);
  Drivetrain.driveFor(forward, 24, inches);
  frontMotor.spinFor(forward, 700, degrees);
  Drivetrain.turnFor(left, 50, degrees);
  Drivetrain.driveFor(forward, 31, inches);
  frontMotor.spinFor(forward, 700, degrees);
  Drivetrain.turnFor(left, 150, degrees);
  Drivetrain.driveFor(forward, 38, inches);
  
}
