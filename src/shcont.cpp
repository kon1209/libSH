#include "shcont.h"


SmartHomeController::SmartHomeController(void){
 // addObject(0,(SmartHomeObject *)this, 0);
 //  SmartHomeObject::pController = this;
}


 SmartHomeObject * SmartHomeController::createObject( byte objClass, word * params){ 
     SmartHomeObject * pObj = 0;
                  switch(objClass)
                   {
                   case SHO_CON:
                          pObj = (SmartHomeObject *) new SHConsole(params[1]);
                        break;
                   case SHO_MBS: 
                        #if defined SH_USE_MODBUS
                         pObj = (SmartHomeObject *) new ModbusSmartHome(params[1],params[2],params[3],params[4]);  
                        #endif
                         break; 
                    case SHO_I2E:
                          pObj = (SmartHomeObject *) new I2CExpander(params[1]);
                           break;                         
                    case SHO_I2P:
                          pObj = (SmartHomeObject *) new I2CPWM(params[1]);
                           break;                                                                                                
                   case SHO_DIO: 
                         pObj = (SmartHomeObject *) new DigitalIO();                     
                         break; 
                   case SHO_AIO: 
                         pObj = (SmartHomeObject *) new AnalogIO();                     
                         break;                                     
                   case SHO_BTN:
                        pObj = (SmartHomeObject *) new Button(&params[1]);                      
                        break;
                  case SHO_DIM:
                        pObj = (SmartHomeObject *) new Dimmer(&params[1]);                      
                        break;						
                   case SHO_BLK:
                        pObj = (SmartHomeObject *) new Blinker(&params[1]);                      
                        break;     
                   case SHO_PIN:
                        pObj = (SmartHomeObject *) new Pin(&params[1]);                      
                        break;
                   case SHO_OPIN:
                        pObj = (SmartHomeObject *) new outPin(&params[1]);                      
                        break;						
                   case SHO_BUF:                        
                        pObj = (SmartHomeObject *) new SHBuffer(&params[1]);                      
                        break;
                  case SHO_SER:                        
                        pObj = (SmartHomeObject *) new SHSerial(&params[1]);                      
                        break;
                    case SHO_TRIG:                        
                        pObj = (SmartHomeObject *) new outTrigger(&params[1]);                      
                        break;                                
				    case SHO_REPTR:                        
                        pObj = (SmartHomeObject *) new Repeater(&params[1]);                      
                        break;                                
                   default:
                          return 0;
                        break;
                   }
                   if(pObj) addObject(params[0],pObj, objClass);                                                               
    return 0;
}

SmartHomeObjValue SmartHomeController::execCommand(byte cID, word * params) {
  SmartHomeObjValue result = 0;
                  SmartHomeObject * pObj = 0;
                  SHBuffer * pObjDst =0;
                  switch(cID)
                   {  
                      case SHC_NEW:
                                 createObject(params[0], &params[1]);   
                                 break;
                      case SHC_DEL:
                                  processObject(params[0], cID);                                
                                 break; 
                      case SHC_STOP:
                                  processObject(params[0], cID);                                
                                 break; 
                      case SHC_START:
                                  processObject(params[0], cID);                                
                                 break;                                  
                      case SHC_RAM:
                                result = freeRam();

                                 break;                                                            
                      case SHC_SETC: 
                                 pObj = findObject(params[0]>>8);
                                 if(pObj) pObj ->writeValue(params[0]&0xff,params[1]);
                                 break;          
                      case SHC_SET: //TODO: rework - not correct
                                 pObj = findObject(params[0]>>8);
                                 pObj ->writeValue(params[0]&0xff,params[1]);
                                 break;
                                 
                                 
                      case SHC_SET_BYTES: //TODO: rework - not correct
                                 pObj = findObject(params[0]);
                                 char * pBytes;
								 pBytes=(char *) (params[1]);
                                 for(int i=0; i<strlen(pBytes);i++){
									if(pBytes[i]=='"')break;
									pObj ->writeValue(i, pBytes[i]);
                                 }
                                 break;
                                 
                      case SHC_SET_BITS: //TODO: rework - not correct
                                 pObj = findObject(params[0]);//src
								 byte outNum ;
								 if(pObj){
									outNum = params[0]&0xff;
									pObj ->writeValue(outNum,params[1]);
								 }
                                 break; 
   								 
                      case SHC_GET: 
                                 pObj = findObject(params[0]>>8);
                                 if(pObj) result =pObj ->readValue(params[0]&0xff);
                                 break;
                               
                                 
                      case SHC_PRINT: 
                                 pObj = findObject((params[0]>>8));
                                 if(pObj){
                                  result = pObj ->readValue((params[0]&0xff));
                                 }
                                 break; 

                        case SHC_GETL: 
                                 pObjDst = (SHBuffer *)findObject(params[0]);
                                 pObj = findObject(params[1]);
                                 char cVal;
                                 int i;
                                  pObjDst ->_pBuff[0]='>';
                                 if(pObjDst && pObj)
                                 {
                                    for(i=0; i<30;i++){
                                        cVal =  pObj ->readValue(params[2]+i);
                                        if(cVal== 0xa)break;
                                        pObjDst ->_pBuff[i+1] =cVal;                                    									
                                    }                                 
                                 }
                                    result =i+1;
                                 break;
                                 
                           default:
                                 return 0;
                                  break;         
                    }
return result;
}

byte SmartHomeController::processObject(SmartHomeObjId oID, byte command)
{
    byte result = 0;
   // if(oID == SHO_SYS_OBJ) return result;  
    if(objMap.size()>0){
          objMap.first();
          do{
           int currId = objMap.getKey();
           if(oID == 0xFF || currId == oID){
          objectDescriptor * pObjDesc = objMap.getValue();
            switch (command)
          {
           case SHC_STOP:
             pObjDesc->state = SHO_ST_STOP;
            break;
           case SHC_START:
             pObjDesc->state = SHO_ST_START;
            break;
           case SHC_DEL:           
                delete pObjDesc -> pObject;
                delete pObjDesc;
                objMap.del(currId);
            break;
          default:
               return 0;
                break;
            }
             if(oID != 0xFF)return 1;           
            }
            }while(objMap.next() != NULL);
    
        }
     result = 1;    
    return result;
}

SmartHomeObject* SmartHomeController::addObject(SmartHomeObjId oId, SmartHomeObject* pObj, byte objClass){
 objectDescriptor * pObjDesc = new objectDescriptor; 
 byte priority = SHO_PRIO_LOW<<4;
 if(objClass == SHO_MBS || objClass == SHO_CON || objClass == SHO_SER) priority = SHO_PRIO_HIGHEST<<4;
 
  //if(objClass == SHO_MBS || SHO_CON || SHO_EEP|| SHO_SER)
	  pObjDesc->state = priority | SHO_ST_START;
 // else pObjDesc->state = priority | SHO_ST_STOP;
  //Serial.println( pObjDesc->state,HEX);
  pObjDesc->pObject = pObj;
  
  objMap.add(oId, pObjDesc);
  return pObj;
}


SmartHomeObjValue SmartHomeController::sendMsg(SmartHomeMsgId msgId, SmartHomeObjAddr objAddr, SmartHomeObjValue msgVal)
{
	SmartHomeObject * pSmartHomeObj= findObject(objAddr>>8);
	if(pSmartHomeObj) 
	{
		return pSmartHomeObj -> processMsg(msgId, objAddr&0xff, msgVal);
	}
}

 void SmartHomeController::process(void){
 byte prio;
if(_params[0] && _params[1])
    {
    execCommand(_params[0],&_params[1]);
    memset(_params,0,PARAM_CNT*2);
    }
 if(objMap.size()>0){
 objectDescriptor * pObjDesc; 
 objMap.first();
    do{
    pObjDesc = objMap.getValue();
    prio = pObjDesc -> state >>4 ;
    if( (prio&prioCnt)== prio  && ((pObjDesc -> state &0xf) == SHO_ST_START) ){ pObjDesc ->pObject -> process();
    }
    }while(objMap.next() != NULL);
  } 
  prioCnt++;
}

 objectDescriptor * SmartHomeController::findObjectDescr(SmartHomeObjId oID){
    return objMap.getValue(oID) ; 
 }
 
 
 SmartHomeObject* SmartHomeController::findObject(SmartHomeObjId oID){
 if(oID==0) return this;
 objectDescriptor * pObjDesc = findObjectDescr(oID);
  if(pObjDesc) return pObjDesc -> pObject;
  return 0;
 }
 
 
SmartHomeObjValue SmartHomeController::readValue(byte valId){
    if(valId<PARAM_CNT) return _params[valId];
}

void SmartHomeController::writeValue(byte valId, SmartHomeObjValue shVal){
    if(valId<PARAM_CNT) _params[valId] = shVal;
}
 

int SmartHomeController::freeRam () {
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}
