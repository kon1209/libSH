/*
    ModbusSerial.h - Header for ModbusSerial Library
    Copyright (C) 2014 André Sarmento Barbosa
*/
#include <Arduino.h>
#include "minModbus.h"

#ifndef MINMODBUSSERIAL_H
#define MINMODBUSSERIAL_H

//#define USE_SOFTWARE_SERIAL

#ifdef USE_SOFTWARE_SERIAL
#include <SoftwareSerial.h>
#endif

class minModbusSerial : public minModbus {
    private:
        Stream* _port;
        long  _baud;
        u_int _format;
        int   _txPin;
        unsigned int _t15; // inter character time out
        unsigned int _t35; // frame delay
        byte  _slaveId;
        word calcCrc(byte address, byte* pduframe, byte pdulen);
		word crc16_update(word crc, uint8_t a);
        unsigned long _delay = 0;
    public:
        minModbusSerial();
        bool setSlaveId(byte slaveId);
        byte getSlaveId();
        bool config(HardwareSerial* port, long baud, u_int format, int txPin=-1);
        #ifdef USE_SOFTWARE_SERIAL
        bool config(SoftwareSerial* port, long baud, int txPin=-1);
        #endif
        #ifdef __AVR_ATmega32U4__
        bool config(Serial_* port, long baud, u_int format, int txPin=-1);
        #endif
        void task();
        bool receive(byte* frame);
        bool sendPDU(byte* pduframe);
        bool send(byte* frame);
};


#endif //MODBUSSERIAL_H
