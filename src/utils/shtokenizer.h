#ifndef SHTOKENIZER_H
#define SHTOKENIZER_H
#include "shbase.h"

#define TTYPE_UNK  0
#define TTYPE_NAME 'n'
#define TTYPE_NUMVAL 'd'
#define TTYPE_CHARVAL '"'
#define TTYPE_EQ '='
#define TTYPE_CEND ';'

const char spStr[] ="<>+-*!&|^";

struct tokAn{
  char * ptok;
  byte len;
}; 

class shTokenizer{
  private:
      char * pos;     
  public:
      shTokenizer();
      void begin(char * startPosition);
      char getToken(tokAn * tok);
      char checkToken(tokAn * tok);      
      byte getParams(byte paramCnt, word * params);
     static  word encodeID(char * pTok, byte len);
};



#endif
