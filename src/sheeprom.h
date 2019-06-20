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
    //virtual SmartHomeObjValue * resolve(char * valName){return 0;};//*getValuePointer(valId);};   
	virtual void process(void);
};

#endif
