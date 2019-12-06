#ifndef SHSERIAL_H
#define SHSERIAL_H

#include "shconfig.h"

class SHSerial: public SHBuffer {
	protected:
        SmartHomeObjId _ioProvider;
	public:
	SHSerial(SmartHomeObjId ioProvider);
	SHSerial (word * params);
   // virtual SmartHomeObjValue processMsg(SmartHomeMsgId msgId, SmartHomeObjValueId valId, SmartHomeObjValue  msgVal);
   // virtual SmartHomeObjValue readValue(byte valId);
  //  virtual void writeValue(byte valId, SmartHomeObjValue shVal);
	virtual void process(void);
};

#endif