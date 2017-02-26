#ifndef Input_h // если библиотека Button не подключена
#define Input_h // тогда подключаем ее

#include "Arduino.h"
class Output{
 protected: byte pin;
  public:
  Output(byte pinNum);
  void process();    
};

#endif
