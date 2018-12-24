#ifndef SHCONSOLE_H
#define SHCONSOLE_H

#include "shobject.h"
#include "shcont.h"
#include "utils/shtokenizer.h"

class SHConsole: public SmartHomeObject {
   shTokenizer * pTokenizer;
   //char console[30];
  protected:
    SmartHomeObjId _inProviderId ;
    SmartHomeObjId _outProviderId;
   
  public:
    SHConsole(SmartHomeObjId inProviderId, SmartHomeObjId outProviderId);
    virtual SmartHomeObjValue readValue(byte valId);
    virtual void writeValue(byte valId, SmartHomeObjValue shVal);
    virtual void process(void);
};

#endif
