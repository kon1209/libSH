#include "shi2c.h"
//
I2CExpander::I2CExpander( byte i2cAddr,SmartHomeObjValue expSize)
{ _i2cAddr = i2cAddr;
        _needWrite = true; 
        _needRead = false;
        _numBytes=expSize; 
        }

I2CExpander::I2CExpander(word * params):I2CExpander(params[0],params[1]){
    
}

void I2CExpander::updatePins(void)
{
	//_inPinValues=0;
	Wire.beginTransmission((int)_i2cAddr);
    int status = Wire.endTransmission();
    if (0 == status){
        if(Wire.requestFrom( (int)_i2cAddr,_numBytes) == _numBytes)
        {		
        //if(Wire.available())
            //{
           _inPinValues = Wire.read(); //read byte 1
           if(_numBytes>1){
              _inPinValues |= (Wire.read())<<8; //read byte 2
            }  
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
	//Wire.write((_outPinValues & 0xFF00) >> 8);
	Wire.endTransmission();
      }    
  }
      
SmartHomeObjValue I2CExpander::readValue(SmartHomeObjValueId valId){
        if (valId >= 0 && valId <16) return (_inPinValues>>valId)&1;
        return 0;
        }
         
void I2CExpander::writeValue(SmartHomeObjValueId valId, SmartHomeObjValue shVal){
        if (valId >= 0 && valId <16) {
          _needWrite = true;
       //   bitClear(_currPinValues,valId);
          bitWrite(_outPinValues, valId, (shVal&1));
        //  _currPinValues |= ((shVal&1)<<valId);
        }
        
        }  


I2CPWM::I2CPWM(byte i2cAddr){
  _i2cAddr = i2cAddr;/* _needWrite = false; _needRead = false;*/ 
  pwm = Adafruit_PWMServoDriver(_i2cAddr);
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);  //new  The int.osc. is closer to 27MHz
  pwm.setPWMFreq(100);  // This is the maximum PWM frequency
    Wire.setClock(400000);//new 100 000 hz
  }

void I2CPWM::writeValue(SmartHomeObjValueId valId, SmartHomeObjValue shVal)
{
  if( valId >= 0 && valId <16){
    pwm.setPin(valId, shVal*16);     
  }
}
         
        //
