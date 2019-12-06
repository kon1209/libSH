
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

SmartHomeObjValue SHBuffer::readValue(byte valId)
{ 
 /*
 if(valId == SH_BUFF_OP){
 return (SmartHomeObjValue) _pBuff;
} */
 if(_bufSize && valId < _bufSize ) return _pBuff[valId];
 return 0;
  }

void SHBuffer::writeValue(byte valId, SmartHomeObjValue shVal)
{// if(valId == 0) memset(_pBuff,0,_bufSize);
  if(_bufSize && valId < _bufSize )  _pBuff[valId]=shVal ; 
  }  
