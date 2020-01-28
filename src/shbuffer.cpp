
#include "shbuffer.h"

SHBuffer::SHBuffer(SmartHomeObjValue bufSz)
{           
    _bufSize = bufSz;
    if(_bufSize >0){
    _pBuff = (char *) malloc(bufSz);
    memset(_pBuff,0,_bufSize);
    }
    //_pCurr = _pBuff;
}

SHBuffer::SHBuffer(word * params): SHBuffer(params[0])
{ 
}

SHBuffer::~SHBuffer(){
    if(_bufSize >0) free(_pBuff);
}

SmartHomeObjValue SHBuffer::readValue(SmartHomeObjValueId valId)
{ 
 if(_bufSize && valId < _bufSize ) return _pBuff[valId];
 return 0;
  }

void SHBuffer::writeValue(SmartHomeObjValueId valId, SmartHomeObjValue shVal)
{
  if(_bufSize && valId < _bufSize )  _pBuff[valId]=shVal ; 
  }  
