#ifndef Input_h // если библиотека Button не подключена
#define Input_h // тогда подключаем ее

#include "Arduino.h"
#include "objectSH.h"

#define DI_PIN 1
#define DI_VALUE 2

class Input : public virtual objectSH{
 protected: byte pin;
  public:
  Input();  
};

class digitalInput:public Input{ 
  byte value; 
  public:
  digitalInput();
  void process() ;
  void * getAddr(byte attrId);
};


#endif
