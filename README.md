# libSH
Smart Home Library for Arduino.

This Library contains different objects neccessary for creating different Arduino based Smart Home hardware.
It contains shcont (Smart Home Controller object) which is responsible for lifecycle of other Smart Home objects(create, run, stop,switch with priorites, delete etc..).
They are : 
    - shconcole - python like command interpreter. Commands could be loaded from serial port or eeprom.
      Due to lack of memory hex digits are used instead of variable names.
    - shio - base Digital and Analog IO
    - Pin - digital or Analog input/output pin. Could be 
    - shi2c - I2C PWM (8/16 PWM outputs) and I2C Expander - (16 I/o ports)
    - shbutton - button
    - shdimmer - dimmer. It input could be connected to shbutton or other SH object.
    - shmodbus - Modbus implementation(holding registers only).
    - sheeprom - EEPROM wrapper for SH objects.
    - shserial - Serial wrapper for SH objects.

All objects interacts using messages via sendMsg(MESSAGE TYPE, SH OBJECT ADDRESS, Message Value);
Till now possible message types:  SH_MSG_READ_VALUE, SH_MSG_WRITE_VALUE ,SH_MSG_UPDATE_VALUE . 
SH OBJECT ADDRESS - word (16 bit) contains Object Addres in 2 nd byte and Object Value Address in 1st byte.

Configuration example:
    6=dio() - create Digital IO Object
    7=aio() - create Analog IO Object
    0xb1=btn(0x605) - create btn Object. Connect it to digital pin 5.
    0xd1=dim(0xb1.01, 0x700) - create  dimmer. Input 0xb101 -button