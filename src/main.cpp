#include "vex.h"
ROBOT_BASE ROBOT;
ACCESS_OS OS;

int main() 
{
  // Run the pre-autonomous function.
  pre_auton();

  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Prevent main from exiting with an infinite loop.
  while (1) 
  {
    vex::task::sleep(20);
    // vex::task::sleep(175); //Sleep the task for a short amount of time to
    // prevent wasted resources.
  }
}