#ifndef SHBUTTON_H
#define SHBUTTON_H

#include "shio.h"

//BUTTON
#define B_PRESSED 1
#define B_RELEASED 0
#define BTN_PRESSED 50
class Button{
  public:
    byte pinValue;
    byte _state;
    long _timePressed;
    byte _outState;
/*    
    Button(){};
    virtual void process(void){};
    virtual SmartHomeObjValue get(byte valId);{}*/
};

class ButtonArray: public SmartHomeObject {
  protected:
    Button * _buttons[20];
    byte _bNum;
  public:
    ButtonArray(byte bNum);
    //ButtonArray(word * params);
   // virtual SmartHomeObjValue readValue(byte valId);
    virtual SmartHomeObjValue get(byte valId){};
    virtual void process(void);
};


#endif
