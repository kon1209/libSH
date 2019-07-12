#ifndef SHOBJECT_H
#define SHOBJECT_H

#include "shbase.h"


class SmartHomeController;

//Pin Defs


class SmartHomeObject {
	public:
        static  SmartHomeController * pController;
		SmartHomeObject(){ };
		virtual ~SmartHomeObject(){};	
		virtual void process(void){};
		virtual SmartHomeObjValue * resolve(char * valName){return 0;};//*getValuePointer(valId);};
        virtual SmartHomeObjValue onLink(void ){return 0;};
};

#endif
    
