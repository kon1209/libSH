
#include "shio.h"
#include "shcont.h"

//Pin object
Pin::Pin(SmartHomeObjAddr providerAddr, byte pinType)
{ 
 // _pinNum = providerAddr &0xff; 
   vProv = providerAddr;
  if(pinType < 3) pController->sendMsg(SH_MSG_WRITE_VALUE, vProv|0x80, pinType);
}

Pin::Pin(word * params): Pin(params[0],params[1])
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


Repeater::Repeater(SmartHomeObjAddr inProviderAddr, SmartHomeObjAddr outProviderAddr, byte outType):Pin(outProviderAddr,OUTPUT){
    _out = outType;
    _inAddr = inProviderAddr;
    pController->sendMsg(SH_MSG_WRITE_VALUE, vProv, _out);
}

Repeater::Repeater(word * params):Repeater(params[0],params[1], params[2]){

} 

void Repeater::process(){ 
    SmartHomeObjValue inVal = pController->sendMsg(SH_MSG_READ_VALUE, _inAddr,0);
	if(_out != inVal){
	_out = inVal;	
    pController->sendMsg(SH_MSG_WRITE_VALUE, vProv, _out);
    }
}

outTrigger::outTrigger(SmartHomeObjAddr inProviderAddr, SmartHomeObjAddr outProviderAddr, byte outType):Pin(outProviderAddr,OUTPUT){
    _out = outType;
    _inAddr = inProviderAddr;
    pController->sendMsg(SH_MSG_WRITE_VALUE, vProv, _out);
    //pController->sendMsg(SH_MSG_WRITE_VALUE, _inAddr|0x80, INPUT_PULLUP);
}

outTrigger::outTrigger(word * params):outTrigger(params[0],params[1], params[2]){

} 

void outTrigger::process(){ 
    SmartHomeObjValue inVal = pController->sendMsg(SH_MSG_READ_VALUE, _inAddr,0);
    if(inVal == 1){
    _out = !(_out);
    pController->sendMsg(SH_MSG_WRITE_VALUE, vProv, _out);
    }
    
}
//
Blinker::Blinker(SmartHomeObjAddr providerAddr, byte outType):Pin(providerAddr,OUTPUT){

   _startTime = 0;
   _duration = 0;
   _out = outType;
   _curr_value = _out;
}

Blinker::Blinker(word * params):Blinker(params[0],params[1]){
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
	// if(_blkAddr)  pController -> sendMsg(SH_MSG_WRITE_VALUE,_blkAddr,200); //_blk->writeValue(0,200);   
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
