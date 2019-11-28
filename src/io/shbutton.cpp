
#include "shbutton.h"
#include "shcont.h"

/*
SmartHomeObjValue Button::readValue(byte valId){
  if(valId == 0) return (SmartHomeObjValue)  _outState;
  if(valId == 1) return (SmartHomeObjValue)  _timePressed;
  return _outState;
}
*/

ButtonArray::ButtonArray(byte bNum){
    _bNum = bNum;     
    //_buttons  =  (Button **) malloc(_bNum*sizeof(Button *)); 
    for (int i =0; i<_bNum;i++)  
    {   
        _buttons[i] = new Button();
    } 
}

/*
ButtonArray::ButtonArray(word * params):ButtonArray(params[0]){
}
*/


void ButtonArray::process(){
    for (int i =0; i<_bNum; i++){
        Button * currButton = _buttons[i];
        if(currButton->_state == B_RELEASED && currButton->_outState == B_PRESSED)
        {
            currButton->_outState = B_RELEASED;
            currButton->_timePressed = 0;
        }
  // pinValue = pController -> sendMsg(SH_MSG_READ_VALUE,vProv,0);
  //button pressed
        if (currButton->_state == B_PRESSED){
            if(! currButton->pinValue){
                currButton->_state = B_RELEASED;
                currButton->_timePressed = millis() - currButton->_timePressed;
                if ( currButton->_timePressed > BTN_PRESSED){            
                        currButton->_outState = B_PRESSED;
                    }
            }
        else//still pressed
            {
     
            }
       }
       else//button released
        {
        if(currButton->pinValue)
            {
            currButton->_state = B_PRESSED;
            currButton->_timePressed = millis();
            }
        }
    }
}

        //
