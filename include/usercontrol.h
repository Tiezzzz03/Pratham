#ifndef USERCONTROL_H
#define USERCONTROL_H

#include "vex.h"
#include "controls.h"
#include "autonomous.h"

void usercontrol(void) 
{
    while(1) 
    {
        controls();
        
        //Press Y to run autonomus
        /*
        if(Controller1.ButtonY.pressing())
        {
          autonomous();
        }
        */

        // -----------------------------Debug Mode (gets drive data for pid control)
        if(Debug.pressing() == 1)
        {
          Brain.Screen.clearScreen();
          Brain.Screen.setCursor(1, 0);
          Brain.Screen.print("Recording data");
          getData();
          Brain.Screen.clearScreen();
          Brain.Screen.setCursor(1, 0);
          Brain.Screen.print("Done!");
        }
    }
}

#endif