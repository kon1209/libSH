#include "shi2c.h"
//
void I2CExpander::updatePins(void)
{
	//_inPinValues=0;
	 Wire.beginTransmission((int)_i2cAddr);
     int status = Wire.endTransmission();

  if (0 == status){
    if(Wire.requestFrom( (int)_i2cAddr,2) == 2)
	{		//request two bytes of data

    //if(Wire.available())
		//{
       _inPinValues = Wire.read(); //read byte 1
       _inPinValues |= (Wire.read())<<8; //read byte 2
        //}  
  }		
  }  
}	

void I2CExpander::process(void)
 {
  updatePins();
  delay(10);
  if(_needWrite){
    _needWrite  = false;
	Wire.beginTransmission((int)_i2cAddr);
	Wire.write(_outPinValues & 0x00FF);
	Wire.write((_outPinValues & 0xFF00) >> 8);
	Wire.endTransmission();
      }    
  }
/*      
SmartHomeObjValue I2CExpander::readValue(byte valId){
        if (valId >= 0 && valId <16) return (_inPinValues>>valId)&1;
        }
         
void I2CExpander::writeValue(byte valId, SmartHomeObjValue shVal){
        if (valId >= 0 && valId <16) {
          _needWrite = true;
       //   bitClear(_currPinValues,valId);
          bitWrite(_outPinValues, valId, (shVal&1));
        //  _currPinValues |= ((shVal&1)<<valId);
        }
        
        }  
SmartHomeObjValue * resolve(char * valName){return 0;};//*getValuePointer(valId);};

*/

I2CPWM::I2CPWM(byte i2cAddr){
  _i2cAddr = i2cAddr;/* _needWrite = false; _needRead = false;*/ 
  pwm = Adafruit_PWMServoDriver(_i2cAddr);
  pwm.begin();
  pwm.setPWMFreq(1600);  // This is the maximum PWM frequency
  }
/*
void I2CPWM::writeValue(byte valId, SmartHomeObjValue shVal)
{
  if( valId >= 0 && valId <16){
    pwm.setPin(valId, shVal*16);     
  }
}*/
         
        //
