#include "shlogic.h"

void logicStatement::process(void)
{
  //  _pOutputs = 
    switch(_statement){
    case OP_OR:
                break;
    case OP_AND:
                break;
    case OP_NOT:
                break;
    case OP_XOR:
                break;
    case OP_PLUS:
                break;                
    case OP_MINUS:
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

    
