#include "shlogic.h"
#include "shcont.h"

void logicStatement::process(void)
{
  //  _pOutputs = 
  SmartHomeObjValue outVal ;
  SmartHomeObjValue tmp=0;
  for(int i=0; i < _inputNum;i++){
	  if(_pInputs[i] == 0) return ;
	  if(i==0){
		  outVal = pController->sendMsg(SH_MSG_READ_VALUE, _pInputs[0], 0);
		  continue;
	  }	
    switch(_statement){
    case OP_OR: 				
				outVal |= pController->sendMsg(SH_MSG_READ_VALUE, _pInputs[i], 0);				
                break;
    case OP_AND:
				outVal &= pController->sendMsg(SH_MSG_READ_VALUE, _pInputs[i], 0);	
                break;
    case OP_NOT:
				outVal != pController->sendMsg(SH_MSG_READ_VALUE, _pInputs[i], 0);	
                break;
    case OP_XOR:
				outVal ^= pController->sendMsg(SH_MSG_READ_VALUE, _pInputs[i], 0);	
                break;
    case OP_PLUS:
				outVal += pController->sendMsg(SH_MSG_READ_VALUE, _pInputs[i], 0);	
                break;                
    case OP_MINUS:
				outVal -= pController->sendMsg(SH_MSG_READ_VALUE, _pInputs[i], 0);	
                break;
    case OP_MULT:
                break;
    case OP_MIN:
                if(i==0) continue;
                tmp = pController->sendMsg(SH_MSG_READ_VALUE, _pInputs[i], 0);
		        if (tmp < outVal) outVal= tmp;    
                break;
    case OP_MAX:
                
                if(i==0) continue;
                tmp = pController->sendMsg(SH_MSG_READ_VALUE, _pInputs[i], 0);
                if (tmp > outVal) outVal= tmp;   
                break;
    case OP_MIN2PARAM:
                break;     
    case OP_MAX2PARAM:
                break;     
    default:
            break;
    }
  }
  //Serial.println(outVal);
	//pController->sendMsg(SH_MSG_WRITE_VALUE, _pOutputs[0], outVal);
     _pOutputs[0]= outVal;
}        

logicStatement::logicStatement(byte statement, byte inputNum ):SmartHomeObject()
        { 
             byte k = 1;
            _statement = statement;
            _inputNum = inputNum;
            if(_statement == OP_MAX2PARAM ||  _statement == OP_MIN2PARAM) k = 2;
            _pInputs = (SmartHomeObjValue *) malloc((_inputNum*k)*2);
            _pOutputs = (SmartHomeObjValue *) malloc(k*2);
          for(int i=0; i < _inputNum;i++){
          _pInputs[i] = 0;  }        
        }

logicStatement::logicStatement(word * params):logicStatement(params[0],params[1]){}
        
 logicStatement::~logicStatement(void){
         if(_pInputs) free(_pInputs);
         if(_pOutputs) free(_pOutputs);
        }

SmartHomeObjValue logicStatement::readValue(SmartHomeObjValueId valId)
{
     switch((valId&0xf0)>>4)
    {
       case 0: return _pOutputs[0] ; 
              break;        
       case 1: if(valId&0xf < _inputNum  ) return _pInputs[valId&0xf] ; 
              break;             
    } 
    return 0;
}

void logicStatement::writeValue(SmartHomeObjValueId valId, SmartHomeObjValue shVal)
{
      switch((valId&0xf0)>>4)
    {
       case 0: // _pOutputs[0] = shVal; 
              break;        
       case 1:
        byte vId = byte(valId&0xf);
       if(vId < _inputNum  )
       {

        _pInputs[vId] = shVal ; }
              break;             
    } 
 
}        
        
    
