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
#define DIM_BTN_LONG_PRESSED 500
#define DIM_BTN_PRESSED 100

struct DimmerParams{
    SmartHomeObjValue inputValue;
    byte state;
    word outState; 
    long trigTime; 
};


class Dimmer: public Pin {
    protected:
        DimmerParams _params;
    public:
        Dimmer(SmartHomeObjAddr outProviderAddr);
        Dimmer(word * params);
        virtual SmartHomeObjValue readValue(SmartHomeObjValueId valId);
        virtual void writeValue(SmartHomeObjValueId valId, SmartHomeObjValue shVal);
        virtual void process(void);
};

#define DIM_NUM 16


class DimmerArray: public SmartHomeObject{
        DimmerParams * _params;
        SmartHomeObjAddr _baseAddr;
        byte _arrSize;       
      public:
        DimmerArray(SmartHomeObjAddr baseAddr, SmartHomeObjValue arrSize);
        DimmerArray(word * params);        
        virtual ~DimmerArray();	        
        virtual SmartHomeObjValue readValue(SmartHomeObjValueId valId);
        virtual void writeValue(SmartHomeObjValueId valId, SmartHomeObjValue shVal);
        virtual void process(void);
};


#endif
