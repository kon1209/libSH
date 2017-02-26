#include "Arduino.h"
#include "digInput.h"

  digitalInput::digitalInput(byte pinNum):Input(pinNum){ 
    
   } 
   
  void digitalInput::process(){
    value =  digitalRead(pin);
  } 

 void digitalInput::connect(){
	byte * t;

	if(!connected){
	p=malloc(2*sizeof( byte *));
	connected = true; 
	*p = &pin;
	t=*p;t+=sizeof( byte *);
	t = &value;
	}
  }   

  /*
   byte * digitalInput::read(){
  return  value;
  }
  
  void digitalInput:: write(const byte * val){
  }
*/

