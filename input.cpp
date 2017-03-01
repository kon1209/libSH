#include "Arduino.h"
#include "input.h"

   Input::Input(byte pinNum){
    pin = pinNum;
    pinMode(pin,INPUT_PULLUP);
    }

//	
digitalInput::digitalInput(byte pinNum):Input(pinNum){    
   } 
   
void digitalInput::process(){
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

