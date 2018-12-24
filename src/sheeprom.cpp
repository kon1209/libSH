#include "sheeprom.h"
#include <EEPROM.h>


#define SH_EEPROM_OP_ADDR 0x81  //1000 0000


SHEeprom::SHEeprom(SmartHomeObjValue bufSz): SHBuffer(bufSz)
{ 
    _opAddress = 0;
    needUpdate = true;
}

SHEeprom::SHEeprom(word * params): SHEeprom(params[0])
{ 
}

void SHEeprom::process(void){
    if(needUpdate){
    char* pCur= _pBuff;
    while(pCur<_pBuff + _bufSize){
        if(_opAddress >= EEPROM.length())break;
        char c = EEPROM[_opAddress];
        if(c==0 || c==0xff ) break;
        *pCur=c;
        _opAddress++;
        pCur++; 
        if(c==0xa) break;        
        }    
    //Serial.println("Update done");    
    needUpdate=false;
    }
}


SmartHomeObjValue SHEeprom::processMsg(SmartHomeMsgId msgId, SmartHomeObjValueId valId, SmartHomeObjValue  msgVal){
if(msgId == SH_MSG_UPDATE_VALUE){  
  needUpdate = true;
  return 0;
}
return SmartHomeObject::processMsg(msgId,valId,msgVal);
}

SmartHomeObjValue SHEeprom::readValue(byte valId)
{ 
 if(valId == SH_BUFF_OP){
 if(_opAddress >= EEPROM.length() || EEPROM[_opAddress]==0 || EEPROM[_opAddress]==0xff )return 0;
 return (SmartHomeObjValue) _pBuff;
}
 if(valId == SH_EEPROM_OP_ADDR) return _opAddress; 
 if(valId < _bufSize && (_opAddress + valId < EEPROM.length())) return EEPROM[ _opAddress + valId ];
  }

void SHEeprom::writeValue(byte valId, SmartHomeObjValue shVal)
{ 
if(valId == SH_EEPROM_OP_ADDR && shVal < EEPROM.length()) {
    _opAddress = shVal;
    return ; }
  if(valId < _bufSize && (_opAddress + valId < EEPROM.length())){
  EEPROM.write( _opAddress + valId ,shVal) ;
  }
  }  