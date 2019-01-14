#ifndef SHTOUCHSENS_H
#define SHTOUCHSENS_H

#include "shio.h"

//BUTTON
#define B_PRESSED 1
#define B_RELEASED 0
#define BTN_PRESSED_TIME 50
class TouchSensor: public Pin {
  protected:
    byte _state;
    long _timePressed;
    word _outState;
  public:
    TouchSensor(SmartHomeObjAddr inProviderAddr);
    TouchSensor(word * params);
    virtual SmartHomeObjValue readValue(byte valId);
    virtual void process(void);
};



#endif
