#include "Arduino.h"
#include "connector.h"
		
//	Connector definition begin
Connector::Connector(){    
   } 
   
  void Connector::process(){
  setValue(src,dest,state);
  } 

 void  * Connector::getAddr(byte attrId){
 switch (attrId )
 {
 	case OBJ_STATE: return &state;
	case CONN_SRC: return &src;
	case CONN_DEST: return &dest;	
	
  }   
  }
 //	Connector definition end 
	
