
#include "shdimmer.h"
#include "shcont.h"



Dimmer::Dimmer(SmartHomeObjAddr inProviderAddr, SmartHomeObjAddr outProviderAddr):Pin(outProviderAddr,OUTPUT){
     _state = 0;
     _outState = 0;
     _inProviderAddr = inProviderAddr;
}

Dimmer::Dimmer(word * params):Dimmer(params[0],params[1])
{}

void Dimmer::process(){
   SmartHomeObjValue btnValue;
   word currState = _outState;
    if( pController -> sendMsg(SH_MSG_READ_VALUE,_inProviderAddr,0)){//button pressed 
   //press duration
   btnValue =  pController -> sendMsg(SH_MSG_READ_VALUE,_inProviderAddr+1,0); //duration
   //if( btnValue >= BTN_PRESSED){//button pressed
    _trigTime = millis();    
   switch (_state){
    case DIM_ST_OFF:
                    if(btnValue >= BTN_LONG_PRESSED){
                       _outState = DIM_VAL_MIN;
                       _state = DIM_ST_INC;
                    }
                     else{
                       _outState = 0;
                       _state = DIM_ST_AUTO_INC;//DIM_ST_ON;
                     }
                    break;
	case DIM_ST_ON:
                     if(btnValue >= BTN_LONG_PRESSED){
                       _state = DIM_ST_DEC;
                    }
                     else {
                       _outState = 0;
                       _state = DIM_ST_OFF;
                     }
                    break;				
    case DIM_ST_AUTO_INC:
                     if(btnValue >= BTN_LONG_PRESSED){
                       _state = DIM_ST_DEC;
                    }
                     else {
                       _outState = 0;
                       _state = DIM_ST_OFF;
                     }
                    break; 
    case DIM_ST_INC:
                      if(btnValue >= BTN_PRESSED){
                       _outState += DIM_VAL_STEP;
                      if(_outState > DIM_VAL_MAX) _outState = DIM_VAL_MIN;
                     }   
                    break;
    case DIM_ST_DEC:
                      if(btnValue >= BTN_PRESSED){                      
                      if(_outState < DIM_VAL_MIN+DIM_VAL_STEP) _outState = DIM_VAL_MAX;
                      else _outState -= DIM_VAL_STEP;
                     }    
                    break ; 
   }                             
   }else{
    if( _state == DIM_ST_INC ||_state == DIM_ST_DEC ){ 
		if(millis() -_trigTime > 1000 ) {
      _state = DIM_ST_ON;	  
      _trigTime = 0;
    }
   }
   if( _state == DIM_ST_AUTO_INC){
	   if(millis() -_trigTime > 50){
		   _outState++;
	      _trigTime = millis();
	   }
	  if(_outState == DIM_VAL_MAX){ 
		   _state = DIM_ST_ON;	  
		   _trigTime = 0;
		   }
	   }
   }
   if(currState != _outState)  pController -> sendMsg(SH_MSG_WRITE_VALUE,vProv,_outState);
}
