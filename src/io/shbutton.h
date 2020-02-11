#ifndef SHBUTTON_H
#define SHBUTTON_H

#include "shio.h"

//BUTTON
#define B_PRESSED 1
#define B_RELEASED 0
#define BTN_PRESSED 50
//
#define BTN_NUM 16
struct ButtonParams{
    byte state;
    long timePressed;
    word outState;
};


class Button: public Pin {
  protected:
    ButtonParams _params; 
    byte _inType;
  public:
    Button(SmartHomeObjAddr inProviderAddr, SmartHomeObjValue inType);
    Button(word * params);
    virtual SmartHomeObjValue readValue(SmartHomeObjValueId valId);
    virtual void process(void);
};



class ButtonArray: public  SmartHomeObject {
        ButtonParams * _params;
        SmartHomeObjAddr _baseAddr;
        byte _arrSize;
        byte _inType;
  public:
    ButtonArray(SmartHomeObjAddr baseAddr, SmartHomeObjValue arrSize, SmartHomeObjValue inType);
    virtual ~ButtonArray();
    virtual SmartHomeObjValue readValue(SmartHomeObjValueId valId);
    virtual void process(void);
};


#endif
