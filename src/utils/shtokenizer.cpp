#include "shtokenizer.h"

shTokenizer::shTokenizer(){
  pos = NULL;
}


void shTokenizer::begin(char * startPosition){
  pos = startPosition;
}

char shTokenizer::getToken(tokAn * tok){
   char * start;
  char result;
   result= TTYPE_UNK;
   start=nullptr;
   while(*pos)
   {
    if(!start)
    {
    if (*pos==' ')
      {
       pos++;continue;
      }
    if(isAlpha(*pos))
      {
         result = TTYPE_NAME;
         start=pos;continue;
      }
    if( isDigit(*pos))
      {   
         result = TTYPE_NUMVAL;
         start=pos;continue;
      }
     tok ->len = 1;
     tok ->ptok = pos;
     pos++;
     return * tok ->ptok;            
    }//!start
    else
    {
      if (!isAlphaNumeric(*pos))
      {
       tok ->len = pos - start;
       tok ->ptok = start;
       return result;
      }   
    } 
    pos++;
   }//while
  return result;
} 


char shTokenizer::checkToken(tokAn * tok){
   char * start;
  char result;
   result= TTYPE_UNK;
   start=0;

  return result;
} 


byte shTokenizer::getParams(byte paramCnt, word * params)
{
  tokAn ntok;
  char lType;
   lType = getToken(&ntok);
   if(lType == '(' ){                  
        for(int i = 0;i < (paramCnt & 0xf); i++)
        {
          lType = getToken(&ntok);
          if(lType == TTYPE_NUMVAL)
            {
             params[i] = strtol( ntok.ptok,NULL,0);
                       
            }else //not numeric param
              {
                 //if(lType == TTYPE_NAME) params[i] = shTokenizer::encodeID(ntok.ptok,ntok.len);               
               // else 
					return 0xE2;   
              }
             lType = getToken(&ntok);
              if(lType == '.'){//object address via objId.valId
              lType = getToken(&ntok);
                if(lType == TTYPE_NUMVAL) params[i] =  (params[i]<<8)+  strtol( ntok.ptok,NULL,0);               
                else return 0xE2;
                lType = getToken(&ntok);
              }
               
             if( *pos == 0)break;
         }//end for
      }else 
         {
         return 0xE3;                        
         }//end if '(' 
      if(lType != ')'){
       return 0xE4;                         
      }
      return 0;
}

