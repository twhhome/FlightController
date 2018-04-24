#include "Aircraft.h"

Aircraft* Vehicle;

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
  Vehicle->TakeOff();
  Vehicle->Forward(10000, 50);
  Vehicle->Backward(10000, 50);
  Vehicle->GoUp(10000, 50);
  Vehicle->GoDown(10000, 50);
  Vehicle->GoLeft(10000, 50);
  Vehicle->GoRight(10000, 50);
  Vehicle->TurnLeft(10000, 50);
  Vehicle->TurnRight(10000, 50);
  Vehicle->Hover(10000);
  Vehicle->RollForward();
  Vehicle->Land();
  Vehicle->RepeatProgram();

}