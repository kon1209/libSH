#ifndef SHEEPROM_H
#define SHEEPROM_H

#include "shconfig.h"


class SHEeprom: public SHBuffer {
	protected:
        SmartHomeObjId _ioProvider;    
        bool needUpdate = false;
        word _index = 0 ;
	public:
	SHEeprom(SmartHomeObjId ioProvider);
	SHEeprom(word * params);
    virtual SmartHomeObjValue processMsg(SmartHomeMsgId msgId, SmartHomeObjValueId valId, SmartHomeObjValue  msgVal);
    virtual SmartHomeObjValue readValue(SmartHomeObjValueId valId);
    virtual void writeValue(SmartHomeObjValueId valId, SmartHomeObjValue shVal);
	virtual void process(void);
};

#endif
