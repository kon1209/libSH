#ifndef ObjectSH_h 
#define ObjectSH_h  

#include "Arduino.h"
class objectSH{

public:
 virtual void process() = 0; 
 virtual void * getAddr(byte attrId) =0;
};

#endif
