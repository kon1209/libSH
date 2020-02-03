
#include "shdimmer.h"
#include "shcont.h"



Dimmer::Dimmer(SmartHomeObjAddr outProviderAddr):Pin(outProviderAddr,OUTPUT)
{
     _state = 0;
     _outState = 0;
     inputValue = 0;
}

Dimmer::Dimmer(word * params):Dimmer(params[0])
{}

SmartHomeObjValue Dimmer::readValue(SmartHomeObjValueId valId)
{
    switch(valId)
    {
       case 0:return inputValue; 
              break;        
       case 1:return _state;
              break;
       case 2:return _outState;
              break;             
    } 
    return 0;
}

void Dimmer::writeValue(SmartHomeObjValueId valId, SmartHomeObjValue shVal)
{
    switch(valId)
    {
       case 0:inputValue = shVal; 
              break;        
       case 1:_state = shVal;
              break;
       case 2:_outState = shVal;
              break;             
    }
}


void Dimmer::process(){
   word currState = _outState;
   if(inputValue&0x8000){ 
    //if( pController -> sendMsg(SH_MSG_READ_VALUE,_inProviderAddr,0)){//button pressed 
   //press duration
  // inputValue =  pController -> sendMsg(SH_MSG_READ_VALUE,_inProviderAddr+1,0); //duration
   //if( inputValue >= BTN_PRESSED){//button pressed
    _trigTime = millis();    
   switch (_state){
    case DIM_ST_OFF:
                    if(inputValue >= BTN_LONG_PRESSED){
                       _outState = DIM_VAL_MIN;
                       _state = DIM_ST_INC;
                    }
                     else{
                       _outState = 0;
                       _state = DIM_ST_AUTO_INC;//DIM_ST_ON;
                     }
                    break;
	case DIM_ST_ON:
                     if(inputValue >= BTN_LONG_PRESSED){
                       _state = DIM_ST_DEC;
                    }
                     else {
                       _outState = 0;
                       _state = DIM_ST_OFF;
                     }
                    break;				
    case DIM_ST_AUTO_INC:
                     if(inputValue >= BTN_LONG_PRESSED){
                       _state = DIM_ST_DEC;
                    }
                     else {
                       _outState = 0;
                       _state = DIM_ST_OFF;
                     }
                    break; 
    case DIM_ST_INC:
                      if(inputValue >= BTN_PRESSED){
                       _outState += DIM_VAL_STEP;
                      if(_outState > DIM_VAL_MAX) _outState = DIM_VAL_MIN;
                     }   
                    break;
    case DIM_ST_DEC:
                      if(inputValue >= BTN_PRESSED)
                      {                      
                      if(_outState < DIM_VAL_MIN+DIM_VAL_STEP) _outState = DIM_VAL_MAX;
                      else _outState -= DIM_VAL_STEP;
                     }    
                    break ; 
            }  
    inputValue = 0;            
   }
   else
   {
    if( _state == DIM_ST_INC ||_state == DIM_ST_DEC )
    { 
        if(millis() -_trigTime > 1000 ) 
        {
        _state = DIM_ST_ON;	  
        _trigTime = 0;
        }
    }
    if( _state == DIM_ST_AUTO_INC)
    {
        if(millis() -_trigTime > 50)
        {
		   _outState++;
	      _trigTime = millis();
        }
        if(_outState == DIM_VAL_MAX)
        { 
		   _state = DIM_ST_ON;	  
		   _trigTime = 0;
		}
	}
   }
   if(currState != _outState)  pController -> sendMsg(SH_MSG_WRITE_VALUE,vProv,_outState);
}




void DimmerArray::process(){
   SmartHomeObjValue inputValue;
     for (byte  i=0;i<DIM_NUM; i++){
   word currState =dimmers[i]._outState;
    if( pController -> sendMsg(SH_MSG_READ_VALUE, dimmers[i]._inProviderAddr,0)){//button pressed 
   //press duration
   inputValue =  pController -> sendMsg(SH_MSG_READ_VALUE, dimmers[i]._inProviderAddr+1,0); //duration
   //if( inputValue >= BTN_PRESSED){//button pressed
    dimmers[i]._trigTime = millis();    
   switch (dimmers[i]._state){
    case DIM_ST_OFF:
                    if(inputValue >= BTN_LONG_PRESSED){
                       dimmers[i]._outState = DIM_VAL_MIN;
                       dimmers[i]._state = DIM_ST_INC;
                    }
                     else{
                       dimmers[i]._outState = 0;
                       dimmers[i]._state = DIM_ST_AUTO_INC;//DIM_ST_ON;
                     }
                    break;
	case DIM_ST_ON:
                     if(inputValue >= BTN_LONG_PRESSED){
                       dimmers[i]._state = DIM_ST_DEC;
                    }
                     else {
                       dimmers[i]._outState = 0;
                       dimmers[i]._state = DIM_ST_OFF;
                     }
                    break;				
    case DIM_ST_AUTO_INC:
                     if(inputValue >= BTN_LONG_PRESSED){
                       dimmers[i]._state = DIM_ST_DEC;
                    }
                     else {
                       dimmers[i]._outState = 0;
                       dimmers[i]._state = DIM_ST_OFF;
                     }
                    break; 
    case DIM_ST_INC:
                      if(inputValue >= BTN_PRESSED){
                      dimmers[i]._outState += DIM_VAL_STEP;
                      if(dimmers[i]._outState > DIM_VAL_MAX) dimmers[i]._outState = DIM_VAL_MIN;
                     }   
                    break;
    case DIM_ST_DEC:
                      if(inputValue >= BTN_PRESSED){                      
                      if(dimmers[i]._outState < DIM_VAL_MIN+DIM_VAL_STEP) dimmers[i]._outState = DIM_VAL_MAX;
                      else dimmers[i]._outState -= DIM_VAL_STEP;
                     }    
                    break ; 
   }                             
   }else{
    if( dimmers[i]._state == DIM_ST_INC ||dimmers[i]._state == DIM_ST_DEC ){ 
		if(millis() - dimmers[i]._trigTime > 1000 ) {
      dimmers[i]._state = DIM_ST_ON;	  
      dimmers[i]._trigTime = 0;
    }
   }
   if( dimmers[i]._state == DIM_ST_AUTO_INC){
	   if(millis() -dimmers[i]._trigTime > 50){
		   dimmers[i]._outState++;
	       dimmers[i]._trigTime = millis();
	   }
	  if(dimmers[i]._outState == DIM_VAL_MAX){ 
		   dimmers[i]._state = DIM_ST_ON;	  
		   dimmers[i]._trigTime = 0;
		   }
	   }
   }   
   if(currState != dimmers[i]._outState)  pController -> sendMsg(SH_MSG_WRITE_VALUE, dimmers[i]._outProviderAddr, dimmers[i]._outState);
   }
}



