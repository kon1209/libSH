#include "shserial.h"

SHSerial::SHSerial(SmartHomeObjId ioProvider): SHBuffer((SmartHomeObjValue)0)
{ 
 _ioProvider = ioProvider;
}

SHSerial::SHSerial(word * params): SHSerial(params[0])
{ 

}

void SHSerial::process(void){
SHBuffer * _valueProvider = (SHBuffer *) pController->findObject(_ioProvider);
if (_valueProvider){
     if(*(_valueProvider->_pBuff) =='>')
       { 
            Serial.write(_valueProvider->_pBuff, strlen(_valueProvider->_pBuff));
            memset(_valueProvider->_pBuff,0,_valueProvider->_bufSize);
      }
    int av= Serial.available();
    if(av>2){          
             Serial.readBytesUntil( 0xd, _valueProvider->_pBuff, _valueProvider->_bufSize);                  
    }     
 }
 }
    


/*
SmartHomeObjValue SHSerial::processMsg(SmartHomeMsgId msgId, SmartHomeObjValueId valId, SmartHomeObjValue  msgVal){
if(msgId == SH_MSG_UPDATE_VALUE){  
  needUpdate = true;
  return 0;
}
return SmartHomeObject::processMsg(msgId,valId,msgVal);
}*/
