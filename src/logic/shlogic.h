#ifndef SHLOGIC_H
#define SHLOGIC_H

#include "shobject.h"

#define OP_OR  '|'
#define OP_XOR '^'  
#define OP_AND '&'
#define OP_NOT  '!'
#define OP_PLUS '+'
#define OP_MINUS '-'
#define OP_MULT '*'
#define OP_MIN '<'
#define OP_MAX '>'
#define OP_MIN2PARAM 'm'
#define OP_MAX2PARAM 'M'

class logicStatement: public SmartHomeObject {
	protected:	
        byte _statement;
        byte _inputNum;
        SmartHomeObjValue * _pInputs;
        SmartHomeObjValue * _pOutputs;
	public:
		virtual void process(void);	 
        logicStatement(byte statement, byte inputNum );
        logicStatement(word * params);        
        ~logicStatement(void);
        virtual SmartHomeObjValue readValue(SmartHomeObjValueId valId);
        virtual void writeValue(SmartHomeObjValueId valId, SmartHomeObjValue shVal);
	};
#endif
    
