/*
 * I2C.h: using software to simulate I2C
 */

#ifndef __PCF8591_H__
#define __PCF8591_H__

#include<Arduino.h>

class PCF8591
{
  private:
    byte SCL;
    byte SDA;
    void SDA_IN();
    void SDA_OUT();
    void SDA_L();
    void SDA_H();
    void SCL_L();
    void SCL_H();
    void byte_transmission(byte byte_data);

  public:
    PCF8591();
    PCF8591(byte CL, byte DA);
    void Init(); // initialize
    void BeginTrans(); // begin transmission
    void Trans(byte value); // transmit voltage value
    void End(); // end transmission
};

#endif
