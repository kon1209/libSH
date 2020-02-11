#include "shdimmer.h"
#include "shcont.h"


//common read,write,process routines for Dimmer subclasses.Could be replaced by another one.

SmartHomeObjValue readDimmerValue(SmartHomeObjValueId valId, DimmerParams * par){
    switch(valId)
    {
       case 0:return par->inputValue; 
              break;        
       case 1:return par->state;
              break;
       case 2:return par->outState;
              break;             
    } 
    return 0;
}

SmartHomeObjValue writeDimmerValue( SmartHomeObjValueId valId, SmartHomeObjValue shVal, DimmerParams * par){
    switch(valId)
    {
       case 0:par->inputValue = shVal; 
              break;        
       case 1:par->state = shVal;
              break;
       case 2:par->outState = shVal;
              break;             
    } 
}


void processDimmer(DimmerParams * par)
{
   word timePressed = par->inputValue&0x7fff;
   if(par->inputValue&0x8000)
   { //button pressed
        par->trigTime = millis();    
        switch (par->state)
        {
            case DIM_ST_OFF:
                    if(timePressed >= BTN_LONG_PRESSED){
                       par->outState = DIM_VAL_MIN;
                       par->state = DIM_ST_INC;
                    }
                     else{
                       par->outState = 0;
                       par->state = DIM_ST_AUTO_INC;//DIM_ST_ON;
                     }
                    break;
            case DIM_ST_ON:
                     if(timePressed >= BTN_LONG_PRESSED){
                       par->state = DIM_ST_DEC;
                    }
                     else {
                       par->outState = 0;
                       par->state = DIM_ST_OFF;
                     }
                    break;				
            case DIM_ST_AUTO_INC:
                     if(timePressed >= BTN_LONG_PRESSED){
                       par->state = DIM_ST_DEC;
                    }
                     else {
                       par->outState = 0;
                       par->state = DIM_ST_OFF;
                     }
                    break; 
            case DIM_ST_INC:
                      if(timePressed >= BTN_PRESSED){
                       par->outState += DIM_VAL_STEP;
                      if(par->outState > DIM_VAL_MAX) par->outState = DIM_VAL_MIN;
                     }   
                    break;
            case DIM_ST_DEC:
                      if(timePressed >= BTN_PRESSED)
                      {                      
                      if(par->outState < DIM_VAL_MIN+DIM_VAL_STEP) par->outState = DIM_VAL_MAX;
                      else par->outState -= DIM_VAL_STEP;
                     }    
                    break ; 
            }  
    par->inputValue = 0;            
   }
   else
   {
        if( par->state == DIM_ST_INC || par->state == DIM_ST_DEC )
        { 
            if(millis() - par->trigTime > 1000 ) 
            {
                par->state = DIM_ST_ON;	  
                par->trigTime = 0;
            }
        }
        if( par->state == DIM_ST_AUTO_INC)
        {
            if(millis() - par->trigTime > 50)
            {
                par->outState++;
                par->trigTime = millis();
            }
            if(par->outState == DIM_VAL_MAX)
            { 
                par->state = DIM_ST_ON;	  
                par->trigTime = 0;
            }
        }   
   }
}

/*
*
*         Dimmer 
*
*/

Dimmer::Dimmer(SmartHomeObjAddr outProviderAddr):Pin(outProviderAddr,OUTPUT)
{
     _params.state = 0;
     _params.outState = 0;
     _params.inputValue = 0;
}

Dimmer::Dimmer(word * params):Dimmer(params[0])
{}

SmartHomeObjValue Dimmer::readValue(SmartHomeObjValueId valId)
{
    return readDimmerValue(valId, &_params );
}

void Dimmer::writeValue(SmartHomeObjValueId valId, SmartHomeObjValue shVal)
{
    writeDimmerValue(valId,shVal,&_params );
}

void Dimmer::process(){
   word currState = _params.outState;
   processDimmer(&_params);
   if(currState != _params.outState)  pController -> sendMsg(SH_MSG_WRITE_VALUE,vProv,_params.outState);
   
}

/*
*
*         Dimmer Array
*
*/

DimmerArray::DimmerArray(SmartHomeObjAddr baseAddr, SmartHomeObjValue arrSize)
{
    _baseAddr = baseAddr;
    _arrSize = arrSize;
     if(_arrSize>0){
        _params = (DimmerParams *)calloc(_arrSize, sizeof(DimmerParams));
        memset(_params, 0, _arrSize*sizeof(DimmerParams));
    }
}

DimmerArray::~DimmerArray(){
    free(_params);
}   



SmartHomeObjValue DimmerArray::readValue(SmartHomeObjValueId valId)
{
    return readDimmerValue(valId&0xf, &(_params[(valId&0x00f0)>>4]));
}

void DimmerArray::writeValue(SmartHomeObjValueId valId, SmartHomeObjValue shVal)
{
    writeDimmerValue(valId&0xf,shVal,&(_params[(valId&0x00f0)>>4]) );
}

void DimmerArray::process(){
    for (byte  i=0;i<_arrSize; i++){
        word currState =_params[i].outState;
        processDimmer(&_params[i]);
        if(currState != _params[i].outState)  pController -> sendMsg(SH_MSG_WRITE_VALUE, _baseAddr+i, _params[i].outState);
   }
}



