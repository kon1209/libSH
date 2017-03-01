#include "Arduino.h"
#include "controller.h"
	
Controller::Controller(){    
   } 
   
void Controller::process(){
    
  } 

 void  * Controller::getAddr(byte attrId){
	switch (attrId )
 {
 	case OBJ_STATE: return &state;
	//case DI_PIN: return &pin;
	//case DI_VALUE: return &value;	
  }   
  }   

