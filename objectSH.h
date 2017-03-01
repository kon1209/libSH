#ifndef ObjectSH_h 
#define ObjectSH_h  

#include "Arduino.h"

#define OBJ_STATE 0

class objectSH{
public:
 byte state=0;
 virtual void * getAddr(byte attrId) =0;
 virtual void process() = 0; 
 
};

#endif
