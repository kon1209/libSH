#include "shconsole.h"


const funcDesc fDescs[]   ={ //objects   
                   {"mbs",( SHP_EXIST | 4), SHO_MBS},   
                   {"dio",0, SHO_DIO}, 
                   {"aio",0, SHO_AIO},
                   {"i2e",( SHP_EXIST | 1), SHO_I2E},
                   {"i2p",( SHP_EXIST | 1), SHO_I2P},                                   
                   {"pin",( SHP_EXIST | 2), SHO_PIN},
                   {"btn",( SHP_EXIST | 1), SHO_BTN},
                   {"dim",( SHP_EXIST | 3), SHO_DIM},
                   {"blk",( SHP_EXIST | 2), SHO_BLK},
                   {"buff",( SHP_EXIST | 1), SHO_BUF},  
                   {"ser0",( SHP_EXIST | 1), SHO_SER},                    
                   //commands                                  
                   //
                   {"del",( SHP_EXIST | 1), SHC_DEL},                  
                   {"ram",( SHP_NEEDOUT | SHP_EXIST | 1), SHC_RAM},                                      
                   {"get",( SHP_NEEDOUT | SHP_EXIST | 2), SHC_GET},
                   {"stop",( SHP_EXIST | 1), SHC_STOP},
                   {"start",( SHP_EXIST | 1), SHC_START},                   
                   {"print",( SHP_NEEDOUT | SHP_EXIST | 1), SHC_PRINT},                  
                   };


byte findFunc(char * pFunc){
  for (byte i=0; i < (sizeof(fDescs)/sizeof(funcDesc)); i++){
    if(!strncmp( fDescs[i].fName, pFunc, strlen(fDescs[i].fName ))){
      return i;
    }
  } 
  return 0xff;
}

SHConsole::SHConsole( SmartHomeObjId inProviderId, SmartHomeObjId outProviderId)
{ 
   pTokenizer = new shTokenizer();
   _inProviderId = inProviderId;
   _outProviderId = outProviderId; 
}

 SmartHomeObjValue SHConsole::readValue(byte valId)
{ 
  return 0;
 //if(valId == 0) return _valueProvider->readValue(_pinNum);
  }

 void SHConsole::writeValue(byte valId, SmartHomeObjValue shVal)
{  
  if(valId == 0) _inProviderId = shVal;
  if(valId == 1) _outProviderId = shVal;
  }  
//
 char *i2str(int i, char *buf){
  byte l=0;
  if(i<0) buf[l++]='-';
  boolean leadingZ=true;
  for(int div=10000, mod=0; div>0; div/=10){
    mod=i%div;
    i/=div;
    if(!leadingZ || i!=0){
       leadingZ=false;
       buf[l++]=i+'0';
    }
    i=mod;
  }
  buf[l]=0;
  return buf;
} 


void SHConsole::process(void){
	
  byte errOut =0;
  funcDesc fDes;
  word result;
  char * _inBuff;
  char *  _outBuff;
 // return;
  _inBuff = (char *)pController->sendMsg(SH_MSG_READ_VALUE,(_inProviderId<<8)+0x80,0); 
  if (_inBuff && (*_inBuff !=0) && (*_inBuff !=0xff) )
  {
  int num = strlen(_inBuff);
  if(num >2){
     Serial.println(_inBuff);

    // if(_inProviderId) pController->sendMsg(SH_MSG_UPDATE_VALUE,(_inProviderId<<8),0);
    // return;
    // 
    _inBuff[strlen(_inBuff)]=0x20;
    pTokenizer -> begin(_inBuff);
    tokAn tok,ntok;
    word params[PARAM_CNT];
    word digParam;
    char lType;
    byte fNum;

   long proctime = micros();
    lType = pTokenizer -> getToken(&tok);   
      switch (lType)
      {
        case TTYPE_UNK: errOut = 0xE0;

                        break; 
                        
        case TTYPE_NUMVAL:errOut = 0xEF;
                          SmartHomeObject * pObj;      
                          digParam = strtol( tok.ptok,NULL,0);                         
                          lType = pTokenizer -> getToken(&ntok);
                          pObj = pController->findObject(digParam);
                          if( lType == '.' && pObj){                          
                            lType = pTokenizer -> getToken(&ntok);
                            if(lType == TTYPE_NUMVAL){                                                        
                                params[0]=digParam;                                           
                                params[1]=  strtol( ntok.ptok,NULL,0);
                                lType = pTokenizer -> getToken(&ntok);
                                if( lType == '=')
                                {
                                 lType = pTokenizer -> getToken(&ntok);
                                   if(lType == TTYPE_NUMVAL)
                                   {
                                    params[2]=  strtol( ntok.ptok,NULL,0);
                                     errOut = 0; 
                                     result = pController -> execCommand(SHC_SETC,params);
                                     break; 
                                   }
                                }
                              }                           
                            //if pObj                                                              
                         }else{                        
                            if( lType == '=' && (!pObj)){  //object definition
                            lType = pTokenizer -> getToken(&ntok);
                                if(lType==TTYPE_NAME) 
                                {
                                    fNum = findFunc(ntok.ptok);
                                    if(fNum != 0xff){
                                            errOut = 0;  
                                            fDes = fDescs[fNum];
                                            if ((fDes.paramCnt & SHP_EXIST)){ 
                                            errOut = pTokenizer ->getParams((fDes.paramCnt & 0xf), &params[2]); 
                                            if(errOut) break;
                                 }               
                                params[0] = fDes.fId;  params[1]=digParam;
                                result = pController -> execCommand(SHC_NEW, params);                                 
                                break;                          
                              }
                            }                         
                          } // !pobj
                         } //if =                                                  
                        break; 
                                                          
        case TTYPE_NAME: //command                         
                         fNum = findFunc(tok.ptok);
                            if(fNum != 0xff){                   
                                fDes = fDescs[fNum];                  
                                //check params 
                           if ((fDes.paramCnt & SHP_EXIST)){  
                                errOut = pTokenizer ->getParams((fDes.paramCnt & 0xf), params);
                                if(errOut) break;     
                            }//end if - check params 

                  /*     
                    if ((fDes.paramCnt & SHP_DDIG)){ 
                       lType = pTokenizer -> getToken(&ntok);
                       if(lType == TTYPE_NUMVAL){                                            
                         digParam =  strtol( ntok.ptok,NULL,0);
                       }
                    }//end digit processing
                   if ((fDes.paramCnt & SHP_DSTR)){ 
                    lType = pTokenizer -> getToken(&ntok);
                     if(lType == TTYPE_CHARVAL){                                            
                         strPar = ntok.ptok + 1;
                         char * pCh =  strchr(strPar,TTYPE_CHARVAL);
                         if(strlen(strPar)>2 && pCh){                          
                          *pCh = 0;
                       
                         }
                       }
                   }//end str processing
                   */                               
                        result = pController -> execCommand(fDes.fId,params); 
                       }                 
                     
                  break;
          default:
                    errOut = 0xE0;
                    //_pStream.print(tok.ptok[0],HEX);
                     break;                  
        }//switch 
        memset(_inBuff, 0, 30);
        if(_outProviderId){
            _outBuff = (char *)pController->sendMsg(SH_MSG_READ_VALUE,(_outProviderId<<8)+0x80,0);
             memset(_outBuff, 0, 10);
            if(errOut) {
                _outBuff[0]='E';
                _outBuff[1] =(errOut&0xf)+0x30; 
             }
             else{
              if ((fDes.paramCnt & SHP_NEEDOUT)){           
              i2str(result, _outBuff);
             }
             else            
             {
             _outBuff[0] = 'O';
             _outBuff[1] = 'K';
             }
     }
     _outBuff[strlen(_outBuff)]=0xd;
     _outBuff[strlen(_outBuff)]=0xa;
       }      
       if(_inProviderId) pController->sendMsg(SH_MSG_UPDATE_VALUE,(_inProviderId<<8),0); 
     }//input len >2
   }//inbuf OK
  
  };


  
  