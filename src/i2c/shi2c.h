#ifndef SHI2C_H
#define SHI2C_H

#include "shobject.h"
#include <Adafruit_PWMServoDriver.h>
//
class I2CExpander: public SmartHomeObject {
  private:
      byte _i2cAddr;
      bool _needWrite;
      bool _needRead;      
      u16 _inPinValues = 0xff;
	  u16 _outPinValues = 0xff;
	  void updatePins(void);
  public:
      I2CExpander( byte i2cAddr){ _i2cAddr = i2cAddr; _needWrite = false; _needRead = false; }
      virtual void process(void);
      virtual SmartHomeObjValue readValue(byte valId);
      virtual void writeValue(byte valId, SmartHomeObjValue shVal);        
};



class I2CPWM: public SmartHomeObject {
  private:
      byte _i2cAddr;
      Adafruit_PWMServoDriver pwm;
     // bool _needWrite;
    //  bool _needRead;      
   //   u16 _currPinValues;
  public:
      I2CPWM(byte i2cAddr);
      virtual void process(void){};
      virtual SmartHomeObjValue readValue(byte valId){};
      virtual void writeValue(byte valId, SmartHomeObjValue shVal);        
};

#endif
