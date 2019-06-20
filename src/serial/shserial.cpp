#include "shserial.h"



SHSerial::SHSerial(SmartHomeObjValue bufSz): SHBuffer(bufSz)
{ 
    needUpdate = true;
}

SHSerial::SHSerial(word * params): SHSerial(params[0])
{ 

}

void SHSerial::process(void){

    if(needUpdate){
    if(strlen(_pBuff)>2){ 
        Serial.write(_pBuff, strlen(_pBuff));
        memset(_pBuff, 0, _bufSize);
    }
     int av= Serial.available();
      if((av>2) &&  (Serial.readBytes(_pBuff, _bufSize)>0)){          
    //Serial.println("Update done");    
    needUpdate=false;
    }
    }  
}

//SmartHomeObjValue * resolve(char * valName){return 0;};//*getValuePointer(valId);};

/*
SmartHomeObjValue SHSerial::processMsg(SmartHomeMsgId msgId, SmartHomeObjValueId valId, SmartHomeObjValue  msgVal){
if(msgId == SH_MSG_UPDATE_VALUE){  
  needUpdate = true;
  return 0;
}
return SmartHomeObject::processMsg(msgId,valId,msgVal);
}
*/