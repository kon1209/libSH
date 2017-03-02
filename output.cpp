#include "Arduino.h"
#include "output.h"
   Output::Output(){
    }
		
//	digitalOutput definition begin
digitalOutput::digitalOutput():Output(){ 
    
   } 
   
  void digitalOutput::process(){
  if (state) refresh();
    digitalWrite(pin, value);
  } 

void digitalOutput::refresh(){
    pinMode(pin, OUTPUT);
	state = 0;
  }   
  
 void  * digitalOutput::getAddr(byte attrId){
 switch (attrId )
 {
 	case OBJ_STATE: return &state;
	case DO_PIN: return &pin;
	case DO_VALUE: return &value;	
  }   
  }
 //	digitalOutput definition end 
	
