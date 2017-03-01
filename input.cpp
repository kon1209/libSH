#include "Arduino.h"
#include "input.h"

   Input::Input(){
   
    }

//	
digitalInput::digitalInput():Input(){    
   } 
   
void digitalInput::process(){
 	if(state){
	pinMode(pin,INPUT_PULLUP);
	state = 0;
	}
    value =  digitalRead(pin);
  } 

 void  * digitalInput::getAddr(byte attrId){
	switch (attrId )
 	{
 	case OBJ_STATE: return &state;
	case DI_PIN: return &pin;
	case DI_VALUE: return &value;	
  	}   
  }   

