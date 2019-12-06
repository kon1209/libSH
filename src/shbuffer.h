#ifndef SHBUFFER_H
#define SHBUFFER_H

#include "shobject.h"
#include <Arduino.h>

#define SH_BUFF_OP 0x80  //1000 0000

class SHBuffer: public SmartHomeObject {
    public:
        char * _pBuff;
        byte  _bufSize;
	SHBuffer(SmartHomeObjValue bufSz);
    SHBuffer(word * params);
    ~SHBuffer();
    virtual SmartHomeObjValue readValue(byte valId);
    virtual void writeValue(byte valId, SmartHomeObjValue shVal);
	virtual void process(void){};    
};

#endif
