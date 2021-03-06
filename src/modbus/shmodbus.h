#ifndef MBSH_H
#define MBSH_H

#include "shobject.h"
#include "minModbus.h"
#include "minModbusSerial.h"

class ModbusSmartHome: public SmartHomeObject,public minModbusSerial {
  protected:

  public:
    ModbusSmartHome(byte serNum, byte serSpeed, byte sId,byte txPin);
    ModbusSmartHome(word * params);
   void addHreg(word offset, word value = 0);
   bool Hreg(word offset, word value);
   word Hreg(word offset);  
   void process(void);  
	virtual SmartHomeObjValue readValue(byte valId);
	virtual void writeValue(byte valId, SmartHomeObjValue shVal);
    };


#endif    
