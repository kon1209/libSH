#ifndef digitalInput_h // если библиотека Button не подключена
#define digitalInput_h // тогда подключаем ее

#include "Arduino.h"
#include "input.h"

class digitalInput:public Input{ 
  byte value; 
  public:
  digitalInput(byte pinNum);
  void  process();  
  void connect();

};

#endif
