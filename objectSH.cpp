#include "Arduino.h"
#include "objectSH.h"

void objectSH::setValue(byte * srcA, byte * dstA, byte type){
  switch(type)
{
 	case B2B:  *(byte *)dstA = *(byte *)srcA;
				break;
	case W2W:  *(word *)dstA = *(word *)srcA;
				break;
	case D2D:  *(double  *)dstA = *(double  *)srcA;
				break;
  }   

}