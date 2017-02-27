#include "Arduino.h"
#include "digInput.h"

  digitalInput::digitalInput(byte pinNum):Input(pinNum){ 
    
   } 
   
  void digitalInput::process(){
    value =  digitalRead(pin);
  } 

 void  * digitalInput::getAddr(byte attrId){
	if(attrId == 0) return &pin;
	else return &value;	
  }   


