#ifndef SHEEPROM_H
#define SHEEPROM_H

#include "shconfig.h"


class SHEeprom: public SHBuffer {
	protected:
		word _opAddress;
        bool needUpdate = false;
	public:
	SHEeprom(SmartHomeObjValue bufSz);
	SHEeprom(word * params);
    virtual SmartHomeObjValue processMsg(SmartHomeMsgId msgId, SmartHomeObjValueId valId, SmartHomeObjValue  msgVal);
    virtual SmartHomeObjValue readValue(byte valId);
    virtual void writeValue(byte valId, SmartHomeObjValue shVal);
	virtual void process(void);
};

#endif
