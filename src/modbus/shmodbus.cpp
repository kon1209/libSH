#include "shmodbus.h"
 #include "shcont.h"
 
ModbusSmartHome::ModbusSmartHome(byte serNum, byte serSpeed, byte sId, byte txPin){
long baud = ((long)serSpeed) * 1200;
 if(serNum==0) this -> config(&Serial, baud, SERIAL_8N1, txPin);
  else{
#if defined __AVR_ATmega2560__
    this -> config(&Serial1, baud, SERIAL_8N1, txPin);
#endif
    }
  this -> setSlaveId(sId);  
    }

ModbusSmartHome::ModbusSmartHome(word * params):ModbusSmartHome(params[0],params[1],params[2],params[3])
{}
    
void ModbusSmartHome::addHreg(word offset, word value ){
        return;     
     }

 word ModbusSmartHome::Hreg(word offset) {   
    byte providerId = offset>>8;
    word bank = 0;
    //temporary fix for eeprom 16 banks x 256 = 4k 
    //should be replaced with read/write general reference
    if (providerId >0xe0 and providerId <0xf0){
        bank = (providerId & 0xf)<<8;
        providerId = 0xe0;
    }
    SmartHomeObject * _valueProvider = pController->findObject(providerId);
    if(_valueProvider){ 
     return _valueProvider ->readValue((offset&0xff)+bank);     
    }
    return 0;
} 

   bool ModbusSmartHome::Hreg(word offset, word value) {//add 40001
    byte providerId = offset>>8;
    word bank = 0;
    //temporary fix for eeprom 16 banks x 256 = 4k 
    //should be replaced with read/write general reference
    if (providerId >0xe0 and providerId <0xf0){
        bank = (providerId & 0xf)<<8;
        providerId = 0xe0;
    }    
    SmartHomeObject * _valueProvider = pController->findObject(providerId);
    if(_valueProvider){
       _valueProvider ->writeValue((offset&0xff)+bank, value);
       return true;
    }
    return false;
}

 SmartHomeObjValue ModbusSmartHome::readValue(byte valId){
 if(valId == 2) return getSlaveId();
 
 }
 
 void ModbusSmartHome::writeValue(byte valId, SmartHomeObjValue shVal){
 switch (valId){
 case 0:
 
        break;
 case 1:
 
        break;
 case 2:setSlaveId(shVal);
        break;
 case 3:
 
        break;
        
default:
        break;
        }
 }


 void  ModbusSmartHome::process(void){
  this -> task();
  }
