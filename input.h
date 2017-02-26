#ifndef Input_h // если библиотека Button не подключена
#define Input_h // тогда подключаем ее

#include "Arduino.h"
#include "objectSH.h"
class Input : public virtual objectSH{
 protected: byte pin;
  public:
  Input(byte pinNum);  
};

#endif
