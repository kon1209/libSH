#ifndef SHBUTTON_H
#define SHBUTTON_H

#include "shio.h"

//BUTTON
#define B_PRESSED 1
#define B_RELEASED 0
#define BTN_PRESSED 50
class Button: public Pin {
  protected:
    byte _state;
    long _timePressed;
    word _outState;
  public:
    Button(SmartHomeObjId providerId, byte pinNum);
    Button(word * params);
    virtual SmartHomeObjValue readValue(byte valId);
    virtual void process(void);
};



#endif
