#ifndef SHCONF_H
#define SHCONF_H

#define SH_USE_MODBUS 1
#define SH_USE_I2C 1

#include "shobject.h"
#include "shcont.h"
#include "io/shio.h"
#if defined SH_USE_I2C
	#include "i2c/shi2c.h"
#endif
#include "io/shbutton.h"
#include "io/shdimmer.h"
#include "console/shconsole.h"
#if defined SH_USE_MODBUS
  #include "modbus/shmodbus.h" 
#endif
#include "shbuffer.h"
#include "sheeprom.h"
#include "logic/shlogic.h"
#include "serial/shserial.h"

#endif