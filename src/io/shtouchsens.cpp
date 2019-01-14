
#include "shtouchsens.h"
#include "shcont.h"



TouchSensor::TouchSensor(SmartHomeObjAddr inProviderAddr):Pin( inProviderAddr,INPUT){
     _state = 0;
    _timePressed = 0;
     _outState = 0;
}

TouchSensor::TouchSensor(word * params):TouchSensor(params[0]){
}


SmartHomeObjValue TouchSensor::readValue(byte valId){
  if(valId == 0) return (SmartHomeObjValue)  _outState;
  if(valId == 1) return (SmartHomeObjValue)  _timePressed;
  return _outState;
}

void TouchSensor::process(){
  byte pinValue;
  if( _state == B_RELEASED && _outState == B_PRESSED){
    _outState = B_RELEASED;
    _timePressed = 0;
  }
   pinValue = pController -> sendMsg(SH_MSG_READ_VALUE,vProv,0);
  //button pressed
  if (_state == B_PRESSED){
        if(!pinValue){
           _state = B_RELEASED;
           _timePressed = millis() - _timePressed;
           if ( _timePressed > BTN_PRESSED){            
               _outState = B_PRESSED;
            }
         }
    else//still pressed
    {
      
    }
  }
  else//button released
  {
    if(pinValue)
    {
      _state = B_PRESSED;
      _timePressed = millis();
    }
  }
}

        //
