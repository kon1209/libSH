#ifndef SHDIMMER_H
#define SHDIMMER_H

#include "shio.h"


#define DIM_ST_OFF 0
#define DIM_ST_ON 1
#define DIM_ST_AUTO_INC 2
#define DIM_ST_INC 3
#define DIM_ST_DEC 4
#define DIM_VAL_MAX 0xff
#define DIM_VAL_MIN 0x10
#define DIM_VAL_STEP 20
#define BTN_LONG_PRESSED 500
#define BTN_PRESSED 50


class Dimmer: public Pin {
  protected:
    byte _state;
    word _outState; 
    long _trigTime;
    SmartHomeObjAddr _inProviderAddr;
  public:
    Dimmer(SmartHomeObjAddr inProviderAddr, SmartHomeObjAddr outProviderAddr);
    Dimmer(word * params);
    virtual SmartHomeObjValue readValue(byte valId){};
    virtual void process(void);
};

#define DIM_NUM 16


class DimmerArray: public SmartHomeObject{
  struct Dimmer{
    byte _state;
    word _outState; 
    long _trigTime;
    SmartHomeObjAddr _outProviderAddr;
    SmartHomeObjAddr _inProviderAddr;   
    }dimmers[DIM_NUM];
 word _index = 0 ;   
  public:
    DimmerArray(){};
    virtual SmartHomeObjValue readValue(byte valId){};
    virtual void process(void);
};


#endif
