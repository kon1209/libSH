#ifndef SHSERIAL_H
#define SHSERIAL_H

#include "shconfig.h"

class SHSerial: public SHBuffer {
	protected:
        bool needUpdate = false;
	public:
	SHSerial(SmartHomeObjValue bufSz);
	SHSerial (word * params);
    //virtual SmartHomeObjValue processMsg(SmartHomeMsgId msgId, SmartHomeObjValueId valId, SmartHomeObjValue  msgVal);
   // virtual SmartHomeObjValue readValue(byte valId);
  //  virtual void writeValue(byte valId, SmartHomeObjValue shVal);
  	//	virtual SmartHomeObjValue * resolve(char * valName){return 0;};//*getValuePointer(valId);};
	virtual void process(void);
};

#endif