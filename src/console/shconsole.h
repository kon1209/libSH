#ifndef SHCONSOLE_H
#define SHCONSOLE_H

#include "shobject.h"
#include "shcont.h"
#include "utils/shtokenizer.h"

struct funcDesc{
  char fName[6];
  byte paramCnt;//ABCD - A - reserve, B -string direct param,  C-digit direct param,  D-params exists - 0000-(0 - 16) param cnt;
  byte fId;
};


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
