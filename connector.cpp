#include "Arduino.h"
#include "connector.h"
		
//	Connector definition begin
Connector::Connector(){    
   } 
   
  void Connector::process(){
   setValue(src,dest,type);
  } 

 void  * Connector::getAddr(byte attrId){
 switch (attrId )
 {
 	case OBJ_STATE: return &state;
	case CONN_SRC: return &src;
	case CONN_DEST: return &dest;	
	case CONN_TYPE: return &type;
	
  }   
  }
 //	Connector definition end 
	
