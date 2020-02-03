#ifndef SHBUTTON_H
#define SHBUTTON_H

#include "shio.h"

//BUTTON
#define B_PRESSED 1
#define B_RELEASED 0
#define BTN_PRESSED 50
//
#define BTN_NUM 32

class Button: public Pin {
  protected:
    byte _state;
    long _timePressed;
    byte _outState;
    byte _inType;
  public:
    Button(SmartHomeObjAddr inProviderAddr, SmartHomeObjValue inType);
    Button(word * params);
    virtual SmartHomeObjValue readValue(SmartHomeObjValueId valId);
    virtual void process(void);
};



class ButtonArray: public  SmartHomeObject   {
struct Button{
    SmartHomeObjAddr _inProviderAddr;
    byte _state;
    long _timePressed;
    word _outState;
} buttons[BTN_NUM];
word _index = 0 ;
  public:
    ButtonArray(){};
    virtual SmartHomeObjValue readValue(SmartHomeObjValueId valId);
    virtual void process(void);
};


#endif
