/*
 * Aircraft.h: control aircraft
 */

#ifndef __AIRCRAFT_H__
#define __AIRCRAFT_H__

#include<Arduino.h>
#include "TLC5620.h"
#include "PCF8591.h"

enum {
  IN_PROGRAM, UNDEFINED
};

class Aircraft
{
  private:
    TLC5620 tlc5620; // 前四个通道
    PCF8591 pcf8591;
    boolean pause_interrupt_able;
    boolean stop_interrupt_able;
    int code, value; // record the code and value of the i2c before interruption
    volatile boolean interrupt;
    int state;

  public:
    volatile boolean interruptable;
    Aircraft();
    int get_state() { return state; }
    bool ProgramShouldRun();
    void StartProgram();
    void AfterLaunch();
    void Init(); // 全部输出为0
    void Reset(byte num); // 复位
    void Connect();
    void TakeOff();
    void Land();
    void GoUp(int t, byte spd); // spd range: 0 - 100
    void GoDown(int t, byte spd);
    void GoLeft(int t, byte spd);
    void GoRight(int t, byte spd);
    void TurnLeft(int t, byte spd);
    void TurnRight(int t, byte spd);
    void Forward(int t, byte spd);
    void Backward(int t, byte spd);
    void RollForward();
    void RollBackward();
    void RollLeft();
    void RollRight();
    void Hover(int t); // 维持当前状态不动
    //void EndProgram(); // 程序结束
    void RepeatProgram();
    void pauseISR();
    void stopISR();
    void SerialControl();
};

extern Aircraft* Vehicle;
void ProgramInit();
void PauseISR();
void StopISR();

#endif
