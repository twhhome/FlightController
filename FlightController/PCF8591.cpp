#include "PCF8591.h"
#include<Arduino.h>

PCF8591::PCF8591()
{
  SCL = 0;
  SDA = 0;
}

PCF8591::PCF8591(byte CL, byte DA)
{
  SCL = CL;
  SDA = DA;
}

void PCF8591::SDA_IN()
{
  pinMode(SDA, INPUT);
}

void PCF8591::SDA_OUT()
{
  pinMode(SDA, OUTPUT);
}

void PCF8591::SDA_L()
{
  digitalWrite(SDA, LOW);
}

void PCF8591::SDA_H()
{
  digitalWrite(SDA, HIGH);
}

void PCF8591::SCL_L()
{
  digitalWrite(SCL, LOW);
}

void PCF8591::SCL_H()
{
  digitalWrite(SCL, HIGH);
}

void PCF8591::byte_transmission(byte byte_data)
{
  byte i, shelter;
  shelter = 0x80;           //这是掩码，shelter的二进制就是 1000 0000

  //传输数据
  for (i=1; i<=8; i++)      
  {
    //这个if else输出数据
    //&意味按位求与，即若shelter=1000 0000，结果就是byte_data的第一位
    if ((byte_data & shelter)==0)
      SDA_L();
    else
      SDA_H();
    //输出数据的同时，需要模拟一次时钟
    SCL_H(); 
    SCL_L();
    //shelter往右移位一位
    shelter >>= 1;
  }
  SDA_IN();         //SDA变成输入引脚（接受DAC芯片的ACK信号）
  SCL_H();  //SCL输出一个时钟周期（让DAC芯片输出ACK信号）
  SCL_L();   
  SDA_OUT();        //SDA变回输出引脚
}

void PCF8591::Init()
{
  SDA_OUT();
  pinMode(SCL, OUTPUT);
}

void PCF8591::BeginTrans()
{
  // START condition
  SCL_H();
  SDA_H();
  SDA_L();
  SCL_L();
  
  byte_transmission(0x48 << 1); // 寻址
}

void PCF8591::Trans(byte value)
{
  byte_transmission(0x40); // turn on DAC
  byte_transmission(value);
}

void PCF8591::End()
{
  SDA_L();
  SCL_H();
  SDA_H();
}

