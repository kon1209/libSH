#ifndef Connector_h // если библиотека Button не подключена
#define Connector_h // тогда подключаем ее

#include "Arduino.h"
#include "objectSH.h"

#define CONN_SRC 1
#define CONN_DEST 2

class Connector : public virtual objectSH{
 protected:
     void * src;
	 void * dest;
  public:
    Connector();
    void process() ;
    void * getAddr(byte attrId);
};




#endif
