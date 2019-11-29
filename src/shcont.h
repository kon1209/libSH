#ifndef SHCONT_H
#define SHCONT_H

#include <Arduino.h>
#include "utils/shkvmap.h"
#include "shconfig.h"

#define OBJ_NAME_LEN 6
#define PARAM_CNT 8

struct objectDescriptor{
    //char objName[OBJ_NAME_LEN];
    //byte objClass;
    byte state = SHO_ST_STOP;
    SmartHomeObject * pObject;
};

class SmartHomeController: public SmartHomeObject {
private:  
   word _command=0;
   word _params[PARAM_CNT]; 
   byte prioCnt =0;
   SHMap<SmartHomeObjId, objectDescriptor*> objMap;
   void parseConsole(void); 
   objectDescriptor * findObjectDescr(SmartHomeObjId oID);  
   byte processObject(SmartHomeObjId oID, byte command);
public:
    SmartHomeController();
	int freeRam (void);
    void begin (){};
    SmartHomeObjValue execCommand(byte cID, word * pParamList);        
	SmartHomeObject* createObject(SmartHomeObjId objClass, word * pParamList);
    SmartHomeObject* addObject(SmartHomeObjId oId, SmartHomeObject* pObj, byte objClass);
	SmartHomeObject* findObject(SmartHomeObjId oID);
	SmartHomeObjValue sendMsg(SmartHomeMsgId msgId, SmartHomeObjAddr objAddr, SmartHomeObjValue  msgVal);
	SmartHomeObjValue sendMsg(SmartHomeMsgId msgId, SmartHomeObjAddr objAddr){};    
    virtual SmartHomeObjValue readValue(byte valId);
    virtual void writeValue(byte valId, SmartHomeObjValue shVal);  
	void process(void);

	//	bool step(void);
};
#endif
