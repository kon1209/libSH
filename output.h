#ifndef Output_h // если библиотека Button не подключена
#define Output_h // тогда подключаем ее

#include "Arduino.h"
#include "objectSH.h"

#define DO_PIN 1
#define DO_VALUE 2


class Output:public virtual objectSH{
 protected:
    byte pin;
  public:
  Output();
};

class digitalOutput:public Output{ 
  private:
   void refresh();
    byte value; 
  public:
    digitalOutput();
    void process() ;
    void * getAddr(byte attrId);
};





#endif
