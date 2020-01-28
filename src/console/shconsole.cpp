#include "shconsole.h"


const funcDesc fDescs[]   ={ //objects   
                   {"mbs",( SHP_EXIST | 4), SHO_MBS},   
                   {"dio",0, SHO_DIO}, 
                   {"aio",0, SHO_AIO},
                   {"i2e",( SHP_EXIST | 1), SHO_I2E},
                   {"i2p",( SHP_EXIST | 1), SHO_I2P},                                   
                   {"pin",( SHP_EXIST | 2), SHO_PIN},
                   {"opin",( SHP_EXIST | 2), SHO_OPIN},				   
                   {"btn",( SHP_EXIST | 1), SHO_BTN},
                   {"dim",( SHP_EXIST | 2), SHO_DIM},
                   {"blk",( SHP_EXIST | 2), SHO_BLK},
                   {"buff",( SHP_EXIST | 1), SHO_BUF},  
                   {"ser0",( SHP_EXIST | 1), SHO_SER}, 
                   {"trig",( SHP_EXIST | 3), SHO_TRIG},
                   {"rept",( SHP_EXIST | 3), SHO_REPTR},                  
                   //commands                                  
                   {"del",( SHP_EXIST | 1), SHC_DEL},                  
                   {"ram",( SHP_NEEDOUT | SHP_EXIST | 1), SHC_RAM},                                      
                   {"getl",( SHP_NEEDOUT | SHP_EXIST | 3), SHC_GETL},
                   {"stop",( SHP_EXIST | 1), SHC_STOP},
                   {"start",( SHP_EXIST | 1), SHC_START},                   
                   {"print",( SHP_NEEDOUT | SHP_EXIST | 2), SHC_PRINT},
                   {"end",0, SHC_END},                   
                   //{"sbit",(  SHP_EXIST | 3), SHC_SET_BITS},				   
                   };


byte findFunc(char * pFunc){
  for (byte i=0; i < (sizeof(fDescs)/sizeof(funcDesc)); i++){
    if(!strncmp( fDescs[i].fName, pFunc, strlen(fDescs[i].fName ))){
      return i;
    }
  } 
  return 0xff;
}

SHConsole::SHConsole(SmartHomeObjValue bufSz ):SHBuffer(bufSz)
{ 
   pTokenizer = new shTokenizer();
   *_pBuff = 0;
}


 SHConsole::SHConsole (word * params):SHBuffer(params[0]){
 }
//
 char *i2str(int i, char *buf, byte l){

  if (i==0)buf[l++]='0';
  else
  {
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
  }
  buf[l]=0;
  return buf;
} 


void SHConsole::process(void){	
  byte errOut =0;
  funcDesc fDes;
  word result;
 // return;
  if ((*_pBuff !='>') && (*_pBuff !=0) && (*_pBuff !=0xff) )
  {
  int num = strlen(_pBuff);
  if(num >2){
    _pBuff[strlen(_pBuff)]=0x20;
    pTokenizer -> begin(_pBuff);
    tokAn tok,ntok;
    word params[PARAM_CNT];
    word digParam;
    char lType;
    byte fNum;
    //Serial.println(_pBuff);
    lType = pTokenizer -> getToken(&tok);   
      switch (lType)
      {
        case TTYPE_UNK: errOut = 0xE1;
                        break; 
                        
        case TTYPE_NUMVAL:errOut = 0xE2;
                          SmartHomeObject * pObj;      
                          digParam = strtol( tok.ptok,NULL,0);                         
                          lType = pTokenizer -> getToken(&ntok);
                          pObj = pController->findObject(digParam);                         
                          //
                          if( lType == '.' && pObj){                          
                            lType = pTokenizer -> getToken(&ntok);
                            if(lType == TTYPE_NUMVAL){                                                        
                                params[0] = digParam;                                           
                                params[1] = strtol( ntok.ptok,NULL,0);
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
                                   }else
                                   {
                                     if(lType=='"') {
                                    params[2]=(word)(ntok.ptok+1);
                                    errOut = 0; 
                                    result = pController -> execCommand(SHC_SET_BYTES,params);                                   
                                   }
                                   }
                                }
                              }                           
                            //if pObj                                                              
                         }else
                         {                        
                            if( lType == '=' ){
                            if(!pObj){  //object definition
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
                            }else// !pobj 
                            {
                                errOut = 0xE6;
                            }                           
                          }//lType 
                         } //if =  
                         
                        break; 
                                                          
        case TTYPE_NAME: //command    
                         errOut = 0xE5;
                         fNum = findFunc(tok.ptok);
                            if(fNum != 0xff){                   
                                fDes = fDescs[fNum];  
                                errOut = 0;                                
                                //check params 
                           if ((fDes.paramCnt & SHP_EXIST)){  
                                errOut = pTokenizer ->getParams((fDes.paramCnt & 0xf), params);
                                if(errOut) break;     
                            }//end if - check params                               
                        result = pController -> execCommand(fDes.fId,params); 
                       }                 
                     
                  break;
          default:
                    errOut = 0xE0;
                    //_pStream.print(tok.ptok[0],HEX);
                     break;                  
        }//switch
        
        if(fDes.fId == SHC_GETL){
                 memset(_pBuff+result, 0, _bufSize-result);
                _pBuff[0]='>';
                _pBuff[strlen(_pBuff)]=0xd;
                _pBuff[strlen(_pBuff)]=0xa;
     
        }
        else{      
         memset(_pBuff, 0, _bufSize);
        _pBuff[0]='>';
        _pBuff[1] = 'O';
        _pBuff[2] = 'K';       
         if(errOut) {
            _pBuff[1]='E';
            _pBuff[2] =(errOut&0xf)+0x30; 
             }
        else{
            if ((fDes.paramCnt & SHP_NEEDOUT)){           
                i2str(result, _pBuff, 1);
            }       
            }
     _pBuff[strlen(_pBuff)]=0xd;
     _pBuff[strlen(_pBuff)]=0xa;
     }//input len >2
   }//inbuf OK
  }
  
  };


  
  