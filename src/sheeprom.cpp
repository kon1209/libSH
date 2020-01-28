#include "sheeprom.h"
#include <EEPROM.h>


#define SH_EEPROM_OP_ADDR 0x81  //1000 0000


SHEeprom::SHEeprom(SmartHomeObjId ioProvider): SHBuffer((SmartHomeObjValue)0)
{ 
    _index = 0;
    needUpdate = true;
    _ioProvider = ioProvider;
}

SHEeprom::SHEeprom(word * params): SHEeprom(params[0])
{ 
}

void SHEeprom::process(void){
    if(_ioProvider && needUpdate){
        SHBuffer * _valueProvider = (SHBuffer *) pController->findObject(_ioProvider);
        if ( _valueProvider){ 
            char* pCur= _valueProvider->_pBuff;
            while(pCur<_valueProvider->_pBuff +_valueProvider->_bufSize)
            {
            if(_index >= EEPROM.length())break;
            char c = EEPROM[_index];
            if(c==0 || c==0xff ){
                //Serial.println("Update done");
                needUpdate=false;
                break;
                }
            *pCur=c;
            _index++;
            pCur++; 
            if(c==0xa) break;        
            }                
        }
    }
}


SmartHomeObjValue SHEeprom::processMsg(SmartHomeMsgId msgId, SmartHomeObjValueId valId, SmartHomeObjValue  msgVal){
if(msgId == SH_MSG_UPDATE_VALUE){  
  needUpdate = true;
  return 0;
}
return SmartHomeObject::processMsg(msgId,valId,msgVal);
}

SmartHomeObjValue SHEeprom::readValue(SmartHomeObjValueId valId)
{ 
//Serial.println(valId);
 if(valId  < EEPROM.length()) return EEPROM[valId ];
  }

void SHEeprom::writeValue(SmartHomeObjValueId valId, SmartHomeObjValue shVal)
{ 
  if( valId  < EEPROM.length()){
  EEPROM.write(  valId ,(byte) shVal) ;
  }
  }  