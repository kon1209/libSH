#include "shbutton.h"
#include "shcont.h"

//common read,write,process routines for button subclasses.Could be replaced by another one.
SmartHomeObjValue readButtonValue(SmartHomeObjValueId valId, ButtonParams * par){
  if(valId == 0) return (SmartHomeObjValue)  ((par->timePressed&0x7fff) | (par->outState==B_PRESSED?0x8000:0));
    return 0;
}

void processButton(ButtonParams * par, byte inType, byte pinValue)
{
    if( par->state == B_RELEASED && par->outState == B_PRESSED){
        par->outState = B_RELEASED;
        par->timePressed = 0;
    }
  //button pressed
    if (par->state == B_PRESSED){      
        if(pinValue != inType){
            //Serial.println("released");
            par->state = B_RELEASED;
            par->timePressed = millis() - par->timePressed;
            if ( par->timePressed > BTN_PRESSED)
            {            
               par->outState = B_PRESSED;
            }
         }
        else//still pressed
        {      
        }
    }
    else//button released
    {
        if(pinValue == inType)
        {
        //Serial.println("pressed");
        par->state = B_PRESSED;
        par->timePressed = millis();
        }
    }
}

/*
*
*         Button 
*
*/
Button::Button(SmartHomeObjAddr inProviderAddr, SmartHomeObjValue inType):Pin( inProviderAddr,INPUT) {
    _params.state = 0;
    _params.timePressed = 0;
    _params.outState = 0;
    _inType = inType;
}

Button::Button(word * params):Button(params[0],params[1]){
}

SmartHomeObjValue Button::readValue(SmartHomeObjValueId valId){
    return readButtonValue(valId, &_params);
}

void Button::process(){
    byte pinValue = pController -> sendMsg(SH_MSG_READ_VALUE,vProv,0);
    processButton(&_params, _inType, pinValue);
}

/*
*
*         Button Array
*
*/

ButtonArray::ButtonArray(SmartHomeObjAddr baseAddr, SmartHomeObjValue arrSize, SmartHomeObjValue inType)
{
    _baseAddr = baseAddr;
    _arrSize = arrSize;
    if(_arrSize>0){
        _params = (ButtonParams *)calloc(_arrSize, sizeof(ButtonParams));
        memset(_params, 0, _arrSize*sizeof(ButtonParams));
    }
    _inType = inType;
}

ButtonArray::~ButtonArray(){
    free(_params);
}

ButtonArray::ButtonArray(word * params):ButtonArray(params[0],params[1],params[2]){
}

SmartHomeObjValue ButtonArray::readValue(SmartHomeObjValueId valId){
  return readButtonValue(valId&0xf, &(_params[(valId&0x00f0)>>4]));
}

void ButtonArray::process(){
    byte pinValue;
    for (byte  i=0;i < _arrSize; i++)
    {
        pinValue = pController -> sendMsg(SH_MSG_READ_VALUE, _baseAddr+i,0);
        processButton(&(_params[i]), _inType, pinValue);
    }
}
        
