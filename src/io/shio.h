#ifndef SHIO_H
#define SHIO_H

#include "shobject.h"

#define SHO_PIN_PRID 0
#define SHO_PIN_PNUM 1
#define SHO_PIN_PTYPE 2

class Pin: public SmartHomeObject {
	protected:
		//byte _pinNum;
    SmartHomeObjAddr vProv;
	public:
	Pin(SmartHomeObjAddr providerAddr, byte pinType);
	Pin(word * params);
    virtual SmartHomeObjValue readValue(byte valId);
    virtual void writeValue(byte valId, SmartHomeObjValue shVal);
	//virtual void process(void){/*readValue(_pinNum);*/};
};


class outPin: public Pin {
	protected:
		    byte _out;
	public:
	outPin(SmartHomeObjAddr outProviderAddr, byte outValue);
	outPin(word * params);

};

class Repeater: public Pin {
	protected:
		    byte _out;
            SmartHomeObjAddr _inAddr;
	public:
	Repeater(SmartHomeObjAddr inProviderAddr, SmartHomeObjAddr outProviderAddr, byte outType);
	Repeater(word * params);
	virtual void process(void);
};

class outTrigger: public Pin {
	protected:
		    byte _out;
            SmartHomeObjAddr _inAddr;
	public:
	outTrigger(SmartHomeObjAddr inProviderAddr, SmartHomeObjAddr outProviderAddr, byte outType);
	outTrigger(word * params);
	virtual void process(void);
};

#define BLK_STATE_RUN 1
#define BLK_STATE_STOPPED 0
class Blinker: public Pin {
  protected:
    byte _out;
    byte _curr_value;
    word _duration;
    long _startTime;
  public:
    Blinker(SmartHomeObjAddr providerAddr, byte outType);
    Blinker(word * params);
   virtual void writeValue(byte valId, SmartHomeObjValue shVal);   
   virtual void process(void);
};


/*
class InputPin: public Pin {
public :
      InputPin(word * params):Pin(params)
      InputPin(word * params):Pin(params){ if(_valueProvider) _valueProvider->writeValue(_pinNum|0x80, INPUT);    };
virtual void writeValue(byte valId, SmartHomeObjValue shVal){};
};*/


class DigitalIO: public SmartHomeObject {     
  public:
      DigitalIO(){  };
      void process(void){};
      virtual SmartHomeObjValue readValue(byte valId);
     virtual void writeValue(byte valId, SmartHomeObjValue shVal);
             
};

//
class AnalogIO: public SmartHomeObject {    
  public:
      AnalogIO(){};
      virtual void process(void){};
      virtual SmartHomeObjValue readValue(byte valId);
      virtual void writeValue(byte valId, SmartHomeObjValue shVal);        
};



#endif
