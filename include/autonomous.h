#ifndef AUTONOMOUS_H
#define AUTONOMOUS_H

#include "record.h"
#include "play.h"
#include "manual.h"
#include "drivefunctions.h"
#include "vex.h"

void autonomous(void) 
{
    if (manual && rojo)
    {
        Controller1.Screen.clearScreen();
        Controller1.Screen.setCursor(1, 1);
        Controller1.Screen.print("RM Running");
        Controller1.Screen.setCursor(2, 1);
        Controller1.Screen.print("By: Pratham");
        RM();
    }
    else if (manual && azul)
    {
        Controller1.Screen.clearScreen();
        Controller1.Screen.setCursor(1, 1);
        Controller1.Screen.print("BM Running");
        Controller1.Screen.setCursor(2, 1);
        Controller1.Screen.print("By: Pratham");
        BM();
    }
    else if (( rojo || azul || skills || slow || test))
    {
      Controller1.Screen.clearScreen();
      Controller1.Screen.setCursor(1, 1);
      Brain.Screen.clearScreen();
      Brain.Screen.setFont(fontType::mono30);
      Brain.Screen.setCursor(1, 0);

      if(rojo)
      {
        Controller1.Screen.print("red");
        Brain.Screen.print("red \n");
      }

      if(azul)
      {
        Controller1.Screen.print("blue");
        Brain.Screen.print("blue \n");
      }

      if(skills)
      {
        Controller1.Screen.print(" sk");
        Brain.Screen.print("skills \n");
      }

      if(slow)
      {
        Controller1.Screen.print(" slow");
        Brain.Screen.print("slow mode \n");
      }

      if(test)
      {
        Controller1.Screen.print(" test");
        Brain.Screen.print("test mode \n");
      }

      Controller1.Screen.setCursor(2, 1);
      Controller1.Screen.print("By: Pratham");
      if(!skills)
      {
        play();
      }
      else 
      {
        splay();
      }
    }
    else 
    {
      Controller1.Screen.clearScreen();
      Controller1.Screen.setCursor(1, 1);
      Controller1.Screen.print(":( i sleep");
      Controller1.Screen.setCursor(2, 1);
      Controller1.Screen.print("By: Pratham");
      
      while(!( rojo || azul || skills || slow || test))
      {
        if(Controller1.ButtonLeft.pressing())
        {
          /*
          turn right 90
          drive back 1
          drive forward 1
          */
        }

        if(Controller1.ButtonRight.pressing())
        {
          /*
          turn left 90
          drive back 1
          drive forward 1
          */
        }
      }

    }
    /*
    else
    {
        //Runs ambiguous auton that drops preload in goal zone
        Controller1.Screen.clearScreen();
        Controller1.Screen.setCursor(1, 1);
        Controller1.Screen.print("Ambi mode on");
        Controller1.Screen.setCursor(2, 1);
        Controller1.Screen.print("By: Pratham");
        drive(-2, 100);
        drive(2, 100);
        flipOut();
    }
    */
}
#endif /* AUTONOMUS_H */