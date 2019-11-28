#ifndef SHOBJECT_H
#define SHOBJECT_H

#include "shbase.h"

class SmartHomeController;

class SmartHomeObject {
	public:
        static  SmartHomeController * pController;
		SmartHomeObject(){ };
		virtual ~SmartHomeObject(){};	
		virtual void process(void){};
        virtual SmartHomeObjValue get(byte valId){return 0;};
        virtual void set(byte valId, SmartHomeObjValue shVal){};
};

#endif
    
