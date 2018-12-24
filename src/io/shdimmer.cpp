
#include "shdimmer.h"
#include "shcont.h"



Dimmer::Dimmer( SmartHomeObjId inId, SmartHomeObjId outId,byte pinNum, byte blkId):Pin(outId, pinNum,OUTPUT){
     _state = 0;
     _outState = 0;
     _inProviderAddr = inId<<8;
     if(blkId) {
		 _blkAddr = blkId<<8;
	 }
}

Dimmer::Dimmer(word * params):Dimmer(params[0],params[1],(byte)params[2],params[3])
{}

void Dimmer::process(){
   SmartHomeObjValue btnValue;
   word currState = _outState;
   //press duration
   if( pController -> sendMsg(SH_MSG_READ_VALUE,_inProviderAddr,0)){//button pressed
    _trigTime = millis();
	
    btnValue =  pController -> sendMsg(SH_MSG_READ_VALUE,_inProviderAddr+1,0); //duration
   switch (_state){
    case DIM_ST_OFF:
                    if(btnValue >= BTN_LONG_PRESSED){
                       _outState = DIM_VAL_MIN;
                       _state = DIM_ST_INC;
                       if(_blkAddr)  pController -> sendMsg(SH_MSG_WRITE_VALUE,_blkAddr,200); //_blk->writeValue(0,200);
                       break;
                    }
                     if(btnValue >= BTN_PRESSED){
                       _outState = DIM_VAL_MAX;
                       _state = DIM_ST_ON;
                     }
                    break;
    case DIM_ST_ON:
                     if(btnValue >= BTN_LONG_PRESSED){
                       _state = DIM_ST_DEC;
					   if(_blkAddr)  pController -> sendMsg(SH_MSG_WRITE_VALUE,_blkAddr,200); //_blk->writeValue(0,200);
                       break;
                    }
                     if(btnValue >= BTN_PRESSED){
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
	  if(_blkAddr)  pController -> sendMsg(SH_MSG_WRITE_VALUE,_blkAddr,0); //_blk->writeValue(0,0);
    }
   }  
   }
   if(currState != _outState)  pController -> sendMsg(SH_MSG_WRITE_VALUE,vProv,_outState);
}
