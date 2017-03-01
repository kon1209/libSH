#ifndef Controller_h // если библиотека Button не подключена
#define Controller_h // тогда подключаем ее

#include "Arduino.h"
#include "objectSH.h"

#define DI_PIN 1
#define DI_VALUE 2

class Controller : public virtual objectSH{
private:
   objectSH * objList;

// protected: byte pin;
  public:
  Controller();  
  void process() ;
  void * getAddr(byte attrId);
  void setObj(byte obj, byte attrId, byte * value); 
  void setObj(byte obj, byte attrId, word * value);
  void getObj(byte obj, byte attrId, byte * value);	
  void getObj(byte obj, byte attrId, word * value); 
};


#endif
