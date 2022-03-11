/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       macrodriguez                                              */
/*    Created:      Mon Mar 07 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Drivetrain           drivetrain    3, 7, 16, 17    
// backMotor            motor         12              
// frontMotor           motor         2               
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include<cmath>
using namespace vex;

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Brain.Screen.print("Executing AutoSchmingus");
  Drivetrain.setDriveVelocity(90, rpm);
  frontMotor.spinFor(forward, 700, degrees);
  Drivetrain.driveFor(forward, 42, inches);
  frontMotor.spinFor(reverse, 700, degrees);
  Drivetrain.turnFor(180, degrees);
  Drivetrain.driveFor(forward, 42, inches);
  Brain.Screen.print("Finished with AutoSchmingus");
}
