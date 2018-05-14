#include "Aircraft.h"
#include<Arduino.h>

int bound100(byte spd)
{
    if (spd > 100) return 100;
    else if (spd > 0) return spd;
    else return 0;
}


void ProgramInit() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(11, OUTPUT);
  attachInterrupt(0, PauseISR, FALLING);
  attachInterrupt(1, StopISR, FALLING);
}

void PauseISR() {
  Serial.println("Press Button");
  if(Vehicle->interruptable == true)
  {
    Vehicle->interruptable = false;
    if(Vehicle->get_state() == IN_PROGRAM)
      Vehicle->pauseISR();
  }
  else
    Vehicle->interruptable = true;
}

void StopISR() {
  Vehicle->stopISR();
}

void Aircraft::pauseISR() {
  if(pause_interrupt_able)
  {
    digitalWrite(11, HIGH);
    for(int i = 0; i <= 200; i++)
      Serial.print('0');
    digitalWrite(11, LOW);
    Serial.println("press pause");
    Serial.print("code: ");
    Serial.println(code);
    Serial.print("value:  ");
    Serial.println(value);
    cli();
    interrupt = true;
    if(code != 0)
    {
      switch(code)
      {
        case 1:
          tlc5620.writeTLC5620(DACA, DAC_REF, 111);
          break;
        case 2:
          tlc5620.writeTLC5620(DACB, DAC_REF, 111);
          break;
        case 3:
          tlc5620.writeTLC5620(DACC, DAC_REF, 111);
          break;
        case 4:
          tlc5620.writeTLC5620(DACD, DAC_REF, 111);
          break;
        case 5:
          pcf8591.BeginTrans();
          pcf8591.Trans(178);
          pcf8591.End();
      }
    }
    for(int i = 1; i < 150; i++)
      Serial.print('0'); // delay time
    while(digitalRead(A1) != LOW)
    {
      if(digitalRead(3) == LOW)
        stopISR();
    }
    digitalWrite(11, HIGH);
    for(int i = 0; i <= 200; i++)
      Serial.print('0');  // delay time
    digitalWrite(11, LOW);
    Serial.println("press pause again");
    if(code != 0)
    {
      switch(code)
      {
        case 1:
          tlc5620.writeTLC5620(DACA, DAC_REF, value);
          break;
        case 2:
          tlc5620.writeTLC5620(DACB, DAC_REF, value);
          break;
        case 3:
          tlc5620.writeTLC5620(DACC, DAC_REF, value);
          break;
        case 4:
          tlc5620.writeTLC5620(DACD, DAC_REF, value);
          break;
        case 5:
          pcf8591.BeginTrans();
          pcf8591.Trans(value);
          pcf8591.End();
      }
    }
    for(int i = 1; i < 50; i++)
      Serial.println(i); // delay time
    if(code == 5)
    {
      for(int i = 1; i < 200; i++)
        Serial.println(i); // delay time
    }
  }
}

void Aircraft::stopISR() {
  if(stop_interrupt_able)
  {
    cli();
    digitalWrite(11, HIGH);
    for(int i = 0; i <= 200; i++)
      Serial.print('0');
    digitalWrite(11, LOW);
    tlc5620.writeTLC5620(DACA, DAC_REF, 0);
    tlc5620.writeTLC5620(DACB, DAC_REF, 227);
    tlc5620.writeTLC5620(DACC, DAC_REF, 0);
    tlc5620.writeTLC5620(DACD, DAC_REF, 0);
    for(int i = 0; i < 200; i++)
      Serial.print(i); // delay time
    while(1);
  }
}

Aircraft::Aircraft():tlc5620(4, 5, 6, 7), pcf8591(8, 9)
{
  pcf8591.Init();
  tlc5620.initTLC5620();
  pause_interrupt_able = false;
  stop_interrupt_able = false;
  interrupt = false;
  interruptable = false;
  state = UNDEFINED;
}

bool Aircraft::ProgramShouldRun()
{
  int val = analogRead(A0);
  if(val >= 100) // reach 3V
  {
    pcf8591.BeginTrans();
    pcf8591.Trans(178);
    pcf8591.End();
    return true;
  }
  else
    return false;
}

void Aircraft::StartProgram()
{
  interruptable = false;
  Serial.println("start program");
  while(digitalRead(A1) != LOW);
  digitalWrite(11, HIGH);
  delay(100);
  digitalWrite(11, LOW);
  delay(500);
}

void Aircraft::AfterLaunch()
{
  interruptable = false;
  Serial.println("The aircraft has launched");
  while(digitalRead(A1) != LOW);
  digitalWrite(11, HIGH);
  delay(100);
  digitalWrite(11, LOW);
  delay(500);
  state = IN_PROGRAM;
}

void Aircraft::Init()
{
  for(byte i = 1; i <= 4; i++)
    Reset(i);
  delay(2000);
}

void Aircraft::Reset(byte num)
{
  Serial.println("called Reset");
  code = num;
  value = 111;
  switch(num)
  {
    case 1:
      tlc5620.writeTLC5620(DACA, DAC_REF, value);
      break;
    case 2:
      tlc5620.writeTLC5620(DACB, DAC_REF, value);
      break;
    case 3:
      tlc5620.writeTLC5620(DACC, DAC_REF, value);
      break;
    case 4:
      tlc5620.writeTLC5620(DACD, DAC_REF, value);
      break;
  }
}

void Aircraft::Connect()
{
  tlc5620.writeTLC5620(DACA, DAC_REF, 227);
  delay(500);
  tlc5620.writeTLC5620(DACA, DAC_REF, 0);
  delay(1000);
  Reset(1);
  delay(2000);
}

void Aircraft::TakeOff()
{
  state = UNDEFINED;
  stop_interrupt_able = true;
  pcf8591.BeginTrans();
  pcf8591.Trans(0);
  pcf8591.End();
  delay(1000);
  pcf8591.BeginTrans();
  pcf8591.Trans(178);
  pcf8591.End();
  delay(1000);
  AfterLaunch();
}

void Aircraft::Land()
{
  state = UNDEFINED;
  stop_interrupt_able = true;
  pcf8591.BeginTrans();
  pcf8591.Trans(61);
  pcf8591.End();
  delay(1000);
  pcf8591.BeginTrans();
  pcf8591.Trans(178);
  pcf8591.End();
  delay(1000);
}

void Aircraft::GoUp(int t, byte spd)
{
  pause_interrupt_able = true;
  stop_interrupt_able = true;
  code = 1;
  value = 111 + 1.16 * bound100(spd);
  tlc5620.writeTLC5620(DACA, DAC_REF, value);
  delay(t);
  Reset(1);
}

void Aircraft::GoDown(int t, byte spd)
{
  pause_interrupt_able = true;
  stop_interrupt_able = true;
  code = 1;
  value = 111 - 1.11 * bound100(spd);
  tlc5620.writeTLC5620(DACA, DAC_REF, value);
  delay(t);
  Reset(1);
}

void Aircraft::GoLeft(int t, byte spd)
{
  pause_interrupt_able = true;
  stop_interrupt_able = true;
  code = 4;
  value = 111 - 1.11 * bound100(spd);
  tlc5620.writeTLC5620(DACD, DAC_REF, value);
  delay(t);
  Reset(4);
}

void Aircraft::GoRight(int t, byte spd)
{
  pause_interrupt_able = true;
  stop_interrupt_able = true;
  code = 4;
  value = 111 + 1.16 * bound100(spd);
  tlc5620.writeTLC5620(DACD, DAC_REF, value);
  delay(t);
  Reset(4);
}

void Aircraft::TurnLeft(int t,  byte spd)
{
  pause_interrupt_able = true;
  stop_interrupt_able = true;
  code = 2;
  value = 111 - 1.11 * bound100(spd);
  tlc5620.writeTLC5620(DACB, DAC_REF, value);
  delay(t);
  Reset(2);
}

void Aircraft::TurnRight(int t, byte spd)
{
  pause_interrupt_able = true;
  stop_interrupt_able = true;
  code = 2;
  value = 111 + 1.16 * bound100(spd);
  tlc5620.writeTLC5620(DACB, DAC_REF, value);
  delay(t);
  Reset(2);
}

void Aircraft::Forward(int t, byte spd)
{
  pause_interrupt_able = true;
  stop_interrupt_able = true;
  code = 3;
  value = 111 + 1.16 * bound100(spd);
  tlc5620.writeTLC5620(DACC, DAC_REF, value);
  delay(t);
  Reset(3);
}

void Aircraft::Backward(int t, byte spd)
{
  pause_interrupt_able = true;
  stop_interrupt_able = true;
  code = 3;
  value = 111 - 1.11 * bound100(spd);
  tlc5620.writeTLC5620(DACC, DAC_REF, value);
  delay(t);
  Reset(3);
}

void Aircraft::RollForward()
{
  pause_interrupt_able = true;
  stop_interrupt_able = true;
  code = 5;
  value = 91;
  pcf8591.BeginTrans();
  pcf8591.Trans(value);
  pcf8591.End();
  delay(1000);
  code = 3;
  value = 227;
  tlc5620.writeTLC5620(DACC, DAC_REF, value);
  delay(1000);
  Reset(3);
  code = 5;
  value = 178;
  pcf8591.BeginTrans();
  pcf8591.Trans(value);
  pcf8591.End();
  delay(7000);
}

void Aircraft::RollBackward()
{
  pause_interrupt_able = true;
  stop_interrupt_able = true;
  code = 5;
  value = 91;
  pcf8591.BeginTrans();
  pcf8591.Trans(value);
  pcf8591.End();
  delay(1000);
  code = 3;
  value = 0;
  tlc5620.writeTLC5620(DACC, DAC_REF, value);
  delay(1000);
  Reset(3);
  code = 5;
  value = 178;
  pcf8591.BeginTrans();
  pcf8591.Trans(value);
  pcf8591.End();
  delay(3000);
}

void Aircraft::RollLeft()
{
  pause_interrupt_able = true;
  stop_interrupt_able = true;
  code = 5;
  value = 91;
  pcf8591.BeginTrans();
  pcf8591.Trans(value);
  pcf8591.End();
  delay(1000);
  code = 4;
  value = 0;
  tlc5620.writeTLC5620(DACD, DAC_REF, value);
  delay(1000);
  Reset(4);
  code = 5;
  value = 178;
  pcf8591.BeginTrans();
  pcf8591.Trans(value);
  pcf8591.End();
  delay(3000);
}

void Aircraft::RollRight()
{
  pause_interrupt_able = true;
  stop_interrupt_able = true;
  code = 5;
  value = 91;
  pcf8591.BeginTrans();
  pcf8591.Trans(value);
  pcf8591.End();
  delay(1000);
  code = 4;
  value = 227;
  tlc5620.writeTLC5620(DACD, DAC_REF, value);
  delay(1000);
  Reset(4);
  code = 5;
  value = 178;
  pcf8591.BeginTrans();
  pcf8591.Trans(value);
  pcf8591.End();
  delay(3000);
}

void Aircraft::Hover(int t)
{
  pause_interrupt_able = true;
  stop_interrupt_able = true;
  delay(t);
}
/*
void Aircraft::EndProgram()
{
  pause_interrupt_able = false;
  stop_interrupt_able = false;
  while(analogRead(A0) >= 100)
  {
      
  }
  tlc5620.writeTLC5620(DACA, DAC_REF, 0);
  tlc5620.writeTLC5620(DACB, DAC_REF, 0);
  tlc5620.writeTLC5620(DACC, DAC_REF, 0);
  tlc5620.writeTLC5620(DACD, DAC_REF, 0);
  pcf8591.BeginTrans();
  pcf8591.Trans(0);
  pcf8591.End();
}
*/
void Aircraft::RepeatProgram()
{
  interruptable = false;
  Serial.println("Prepare for repeat");
  while(digitalRead(A1) != LOW);
  digitalWrite(11, HIGH);
  delay(100);
  digitalWrite(11, LOW);
  delay(500);
}
