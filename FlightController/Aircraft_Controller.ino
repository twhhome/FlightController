#include <Arduino.h>
#include "Aircraft.h"

Aircraft* Vehicle;
/* In those below functions, pause interruption is disabled:
 *    ProgramShouldRun(), Init(), Connect(), TakeOff(), Land(), EndProgram(), RepeatProgram()
 * In those below functions, stop interruption is disabled:
 *    ProgramShouldRun(), Init(), Connect(), EndProgram(), RepeatProgram()
 * In those below situations, both interruptions are disabled:
 *    in the span between the aircraft has landed and it takes off again
 */
boolean first_run = true;

void setup(){
  
}

void loop(){
  if(first_run == true)
  {
    Vehicle = new Aircraft;
    ProgramInit();
    while(!Vehicle->ProgramShouldRun());
    Vehicle->Init();
    Vehicle->Connect();
    first_run = false;
    Vehicle->StartProgram();
  }
  /*
   * put your own flight code here
   */
   Vehicle->TakeOff();
   Vehicle->TurnLeft(3000, 50);
   Vehicle->Hover(2000);
   Vehicle->TurnLeft(3000, 100);
   Vehicle->Hover(2000);
   /*
   Vehicle->GoUp(500, 75);
   Vehicle->Hover(1000);
   Vehicle->GoDown(500, 75);
   Vehicle->Hover(1000);
   Vehicle->GoLeft(1000, 75);
   Vehicle->Hover(1000);
   Vehicle->GoRight(1000, 75);
   Vehicle->Hover(1000);
   Vehicle->Forward(1000, 75);
   Vehicle->Hover(1000);
   Vehicle->Backward(1000, 75);
   Vehicle->Hover(1000);
   Vehicle->TurnLeft(1000, 75);
   Vehicle->Hover(1000);
   Vehicle->TurnRight(1000, 75);
   Vehicle->Hover(1000);
   */
   Vehicle->Land();
   Vehicle->RepeatProgram();
}
