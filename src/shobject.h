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
		virtual SmartHomeObjValue readValue(byte valId){return 0;};//*getValuePointer(valId);};
		virtual void writeValue(byte valId, SmartHomeObjValue shVal){};//{*getValuePointer(valId) = shVal;};
};

#endif
    
