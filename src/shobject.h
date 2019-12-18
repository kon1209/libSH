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
		virtual SmartHomeObjValue processMsg(SmartHomeMsgId msgId, SmartHomeObjValueId valId, SmartHomeObjValue  msgVal)
		{
			if(msgId == SH_MSG_READ_VALUE) return readValue(valId);
            if(msgId == SH_MSG_WRITE_VALUE) writeValue(valId, msgVal); 
			return 0;
		};		
		virtual SmartHomeObjValue readValue(SmartHomeObjValueId valId){return 0;};//*getValuePointer(valId);};
		virtual void writeValue(SmartHomeObjValueId valId, SmartHomeObjValue shVal){};//{*getValuePointer(valId) = shVal;};
};

class SmartHomeArray: public SmartHomeObject{
	public:
    byte _indx = 0;
};

#endif
    
