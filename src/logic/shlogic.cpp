#include "shlogic.h"
#include "shcont.h"

void logicStatement::process(void)
{
  //  _pOutputs = 
  word outVal;
  for(int i=0; i < _inputNum;i++){
	  if(_pInputs[i] == 0) return;
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
                break;
    case OP_MAX:
                break;
    case OP_MIN2PARAM:
                break;     
    case OP_MAX2PARAM:
                break;     
    default:
            break;
    }
  }
  
	pController->sendMsg(SH_MSG_WRITE_VALUE, _pOutputs[0], outVal);
}        

logicStatement::logicStatement(byte statement, byte inputNum ):SmartHomeObject()
        { 
             byte k = 1;
            _statement = statement;
            _inputNum = inputNum;
            if(_statement == OP_MAX2PARAM ||  _statement == OP_MIN2PARAM) k = 2;
            _pInputs = (SmartHomeObjValue *) malloc((_inputNum*k)*2);
            _pOutputs = (SmartHomeObjValue *) malloc(k*2);            
        }
        
 logicStatement::~logicStatement(void){
         if(_pInputs) free(_pInputs);
         if(_pOutputs) free(_pOutputs);
        }

    
