#ifndef SHLOGIC_H
#define SHLOGIC_H

#include "shobject.h"

#define OP_OR  1
#define OP_XOR  2
#define OP_AND 4
#define OP_NOT  3
#define OP_PLUS 5
#define OP_MINUS 6
#define OP_MULT 7
#define OP_MIN 8
#define OP_MAX 9
#define OP_MIN2PARAM 0x20
#define OP_MAX2PARAM 0x21

class logicStatement: public SmartHomeObject {
	protected:	
        byte _statement;
        byte _inputNum;
        SmartHomeObjValue * _pInputs;
        SmartHomeObjValue * _pOutputs;
	public:
		virtual void process(void);	 
        logicStatement(byte statement, byte inputNum );      
        ~logicStatement(void);

	};
#endif
    
