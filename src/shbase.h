#ifndef SHBASE_H
#define SHBASE_H

#include <Arduino.h>
#include <Wire.h>

#define SH_MSG_READ_VALUE 1
#define SH_MSG_WRITE_VALUE 2
#define SH_MSG_UPDATE_VALUE 3


#define SHO_PRIO_LOWEST 0xF
#define SHO_PRIO_LOW 0x7
#define SHO_PRIO_MIDDLE 0x3
#define SHO_PRIO_HIGH 0x1
#define SHO_PRIO_HIGHEST 0x0

#define SHO_ST_STOP 0
#define SHO_ST_START 1
#define SHO_ALL 0xFF
#define SHO_SYS_OBJ 5

//obj
#define SHO_SER  3
#define SHO_CON  2
#define SHO_MBS  4
#define SHO_DIO  5
#define SHO_AIO  6
#define SHO_I2E  10
#define SHO_I2P  11
#define SHO_PIN  20
#define SHO_BTN  21
#define SHO_BLK  22
#define SHO_DIM  30
#define SHO_BUF  40
#define SHO_EEP  100
//commands
//
#define SHC_NEW  1
#define SHC_DEL  2
#define SHC_STOP  3
#define SHC_START  4
#define SHC_RAM  5

#define SHC_SET 240
#define SHC_SETC 241
#define SHC_GET 242
#define SHC_PRINT 243
//ABCD - A - reserve, B -string direct param,  C-digit direct param,  D-params exists - 0000-(0 - 16) param cnt;
#define SHP_NEEDOUT 0x80
#define SHP_DSTR  0x40
#define SHP_DDIG  0x20
#define SHP_EXIST  0x10

typedef  word SmartHomeObjValue;
typedef  byte SmartHomeObjValueId;
typedef  byte SmartHomeObjId; // 
typedef  word SmartHomeObjAddr;//1-st  objId, second valId
typedef  byte SmartHomeMsgId; // 

struct funcDesc{
  char fName[6];
  byte paramCnt;//ABCD - A - reserve, B -string direct param,  C-digit direct param,  D-params exists - 0000-(0 - 16) param cnt;
  byte fId;
};







#endif
