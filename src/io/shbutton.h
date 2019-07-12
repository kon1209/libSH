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
    byte _outState;
  public:
    Button(SmartHomeObjAddr inProviderAddr);
    Button(word * params);
   // virtual SmartHomeObjValue readValue(byte valId);
    virtual void process(void);
};


#endif
