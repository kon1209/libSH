#ifndef ObjectSH_h 
#define ObjectSH_h  

#include "Arduino.h"
class objectSH{
	protected:
	bool connected = false;
//	static byte b;
	//registerObj
public:
 void **p;
 virtual void process() = 0; 
 virtual void connect() = 0; 
};

#endif
