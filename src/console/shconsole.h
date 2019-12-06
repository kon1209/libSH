#ifndef SHCONSOLE_H
#define SHCONSOLE_H

#include "shconfig.h"
#include "shbuffer.h"

#include "utils/shtokenizer.h"

struct funcDesc{
  char fName[6];
  byte paramCnt;//ABCD - A - reserve, B -string direct param,  C-digit direct param,  D-params exists - 0000-(0 - 16) param cnt;
  byte fId;
};


class SHConsole: public SHBuffer {
    protected:
        shTokenizer * pTokenizer;
    public:
        SHConsole(SmartHomeObjValue bufSz);
        SHConsole (word * params);
        virtual void process(void);
};

#endif
