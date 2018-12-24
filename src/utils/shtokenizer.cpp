#include "shtokenizer.h"

shTokenizer::shTokenizer(){
  pos = NULL;
}

/*
word shTokenizer::encodeID( char * pTok, byte len){
  word result = 0;
if(len > 0 && len < 4){
    if(isAlpha(*pTok) && isLowerCase(*pTok)){
      result = (*pTok - 'a' + 1)<<11;
      if(len > 1){
        pTok++;
        if(isAlpha(*pTok) && (isLowerCase(*pTok))){
        result |= ((*pTok - 'a' + 1)<<6);
        if(len > 2){
           pTok++;
          if(isAlpha(*pTok)){           
            if(isUpperCase(*pTok)) result |= (*pTok - 'A' + 1);
            else result |= (*pTok - 'a' + 1);
          }else{//digit
            result |=(*pTok - '0' + 53);
          }         
        }  
      }
      else{
       result=0;
      }
    }//toklen>1  
  }//first token Lower case
}//check common len
  return result;
}
*/

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
              if(lType == '.'){
              lType = getToken(&ntok);
                if(lType == TTYPE_NUMVAL) params[i+1] =  strtol( ntok.ptok,NULL,0);               
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

