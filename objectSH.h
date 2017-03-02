#ifndef ObjectSH_h 
#define ObjectSH_h  

#include "Arduino.h"

#define OBJ_STATE 0

#define B2B 1
#define W2W 2
#define D2D 4 

class objectSH{
protected:
 void setValue(byte * srcA, byte * dstA, byte type);
 //void getValue(byte * srcA, byte * dstA, byte type);
public:
 byte state=0;
 //void setValue(byte * srcA, byte * dstA, byte type);
 virtual void * getAddr(byte attrId) =0;
 virtual void process() = 0; 
 
};




#endif
