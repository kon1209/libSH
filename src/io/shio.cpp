
#include "shio.h"
#include "shcont.h"

//Pin object
Pin::Pin(SmartHomeObjId providerId, byte pinNum, byte pinType)
{ 
  _pinNum = pinNum; 
   vProv = (providerId<<8)+pinNum;
  if(pinType < 3) pController->sendMsg(SH_MSG_WRITE_VALUE, vProv|0x80, pinType);
}

Pin::Pin(word * params): Pin(params[0],(byte)params[1],params[2])
{ 
}

SmartHomeObjValue Pin::readValue(byte valId)
{ 
 if(valId == 0) return  pController->sendMsg(SH_MSG_READ_VALUE, vProv,0);
  }

void Pin::writeValue(byte valId, SmartHomeObjValue shVal)
{ 
  if(valId == 0) pController->sendMsg(SH_MSG_WRITE_VALUE, vProv, shVal);
  }  
  
//
Blinker::Blinker(SmartHomeObjId providerId, byte pinNum, byte outType):Pin(providerId,pinNum,OUTPUT){

   _startTime = 0;
   _duration = 0;
   _out = outType;
    _curr_value = _out;
}

Blinker::Blinker(word * params):Blinker(params[0],(byte)params[1],params[2]){
}


void Blinker::writeValue(byte valId, SmartHomeObjValue shVal){
  if(valId == 0) { 
   _duration = shVal;
   if(_duration != 0){
     _curr_value = !(_out);
    _startTime = millis();
   }
   else{
      _curr_value = _out;    
   }
   pController->sendMsg(SH_MSG_WRITE_VALUE, vProv, _curr_value);  
 }
}

void Blinker::process(){
   if(_duration){
    if(millis()-_startTime > _duration)  { 
      _curr_value = !_curr_value;
      pController->sendMsg(SH_MSG_WRITE_VALUE, vProv,_curr_value); 
      _startTime=millis();
     }
   }
}


SmartHomeObjValue DigitalIO::readValue(byte valId)
{ 
   if( valId >= 1 && valId <64) return digitalRead(valId);
   return 0;
  }
  
void DigitalIO::writeValue(byte valId, SmartHomeObjValue shVal)
{
  if( valId >= 1 && valId <64){
    digitalWrite(valId, shVal); 
    return;
  }
    if( valId > 0x7f){
      pinMode(valId & 0x7f, shVal);
    }
  }
  
SmartHomeObjValue AnalogIO::readValue(byte valId)
{ 
   //if( valId >= 1 && valId <64) return digitalRead(valId);
   return 0;
  }
  
void AnalogIO::writeValue(byte valId, SmartHomeObjValue shVal)
{

  if( valId >= 1 && valId <64){
    analogWrite(valId, shVal); 
    return;
  }

  }



         
        //
