/*
    ModbusSerial.cpp - Source for Modbus Serial Library
    Copyright (C) 2014 André Sarmento Barbosa
*/
#include "minModbusSerial.h"

minModbusSerial::minModbusSerial() {

}

bool minModbusSerial::setSlaveId(byte slaveId){
    _slaveId = slaveId;
    return true;
}

byte minModbusSerial::getSlaveId() {
    return _slaveId;
}

bool minModbusSerial::config(HardwareSerial* port, long baud, u_int format, int txPin) {
    this->_port = port;
    this->_txPin = txPin;
    (*port).begin(baud, format);

  //  delay(2000);

    if (txPin >= 0) {
        pinMode(txPin, OUTPUT);
        digitalWrite(txPin, LOW);
    }

    if (baud > 19200) {
        _t15 = 750;
        _t35 = 1750;
    } else {
        _t15 = 15000000/baud; // 1T * 1.5 = T1.5
        _t35 = 35000000/baud; // 1T * 3.5 = T3.5
    }

    return true;
}

#ifdef USE_SOFTWARE_SERIAL
bool minModbusSerial::config(SoftwareSerial* port, long baud, int txPin) {
    this->_port = port;
    this->_txPin = txPin;
    (*port).begin(baud);

    delay(2000);

    if (txPin >= 0) {
        pinMode(txPin, OUTPUT);
        digitalWrite(txPin, LOW);
    }

    if (baud > 19200) {
        _t15 = 750;
        _t35 = 1750;
    } else {
        _t15 = 15000000/baud; // 1T * 1.5 = T1.5
        _t35 = 35000000/baud; // 1T * 3.5 = T3.5
    }

    return true;
}
#endif

#ifdef __AVR_ATmega32U4__
bool minModbusSerial::config(Serial_* port, long baud, u_int format, int txPin) {
    this->_port = port;
    this->_txPin = txPin;
    (*port).begin(baud, format);
    while (!(*port));

    if (txPin >= 0) {
        pinMode(txPin, OUTPUT);
        digitalWrite(txPin, LOW);
    }

    if (baud > 19200) {
        _t15 = 750;
        _t35 = 1750;
    } else {
        _t15 = 15000000/baud; // 1T * 1.5 = T1.5
        _t35 = 35000000/baud; // 1T * 3.5 = T3.5
    }

    return true;
}
#endif

bool minModbusSerial::receive(byte* frame) {
    //first byte of frame = address
    byte address = frame[0];
    //Last two bytes = crc
    u_int crc = ((frame[_len - 2] << 8) | frame[_len - 1]);

    //Slave Check
    if (address != 0xFF && address != this->getSlaveId()) {
		return false;
	}

    //CRC Check
	//Serial.print(crc,HEX);Serial.print(" - ");Serial.println(this->calcCrc(_frame[0], _frame, _len-2),HEX);
    if (crc != this->calcCrc(_frame[0], _frame+1, _len-3)) {
		return false;
    }

    //PDU starts after first byte
    //framesize PDU = framesize - address(1) - crc(2)
	
    this->receivePDU(frame+1);
    //No reply to Broadcasts
    if (address == 0xFF) _reply = MB_REPLY_OFF;
    return true;
}

bool minModbusSerial::send(byte* frame) {
    byte i;

    if (this->_txPin >= 0) {
        digitalWrite(this->_txPin, HIGH);
        //delay(1);
    }

    for (i = 0 ; i < _len ; i++) {
        (*_port).write(frame[i]);
    }

    (*_port).flush();
    delayMicroseconds(_t35);

    if (this->_txPin >= 0) {
        digitalWrite(this->_txPin, LOW);
    }
}

bool minModbusSerial::sendPDU(byte* pduframe) {
//Serial.println("sendPdu");
    if (this->_txPin >= 0) {
        digitalWrite(this->_txPin, HIGH);
        //delay(1);
    }

    //Send slaveId
    (*_port).write(_slaveId);

    //Send PDU
    byte i;
    for (i = 0 ; i < _len ; i++) {
        (*_port).write(pduframe[i]);
    }

    //Send CRC
    word crc = calcCrc(_slaveId, _frame, _len);
    (*_port).write(crc >> 8);
    (*_port).write(crc & 0xFF);

    (*_port).flush();
    delayMicroseconds(_t35);

    if (this->_txPin >= 0) {
        digitalWrite(this->_txPin, LOW);
    }
}

void minModbusSerial::task() {
    //_len = 0;
    if(_delay && (micros()-_delay > _t15)){
     _delay=0;
    }
    if(_delay != 0)return;  
    if ((*_port).available() > _len ){
        _len = (*_port).available();       
       _delay = micros();     
       return;
    }

    if (_len == 0) return;
   
    byte i;
    _frame = (byte*) malloc(_len);
    for (i=0 ; i < _len ; i++) _frame[i] = (*_port).read();

    if (this->receive(_frame)) {
        if (_reply == MB_REPLY_NORMAL)
            this->sendPDU(_frame);
        else
        if (_reply == MB_REPLY_ECHO)
            this->send(_frame);
    }

    free(_frame);
    _len = 0;
}

 word minModbusSerial::crc16_update(word crc, uint8_t a)
{
  int i;
  crc ^= a;
  for (i = 0; i < 8; ++i)
  {
    if (crc & 1)
      crc = (crc >> 1) ^ 0xA001;
    else
      crc = (crc >> 1);
  }
  return crc;
} 


word minModbusSerial::calcCrc(byte address, byte* pduFrame, byte pduLen) {

 u16 u16CRC = 0xFFFF;
    u16CRC = crc16_update(u16CRC,address);
	for (int i = 0; i < pduLen; i++)
	{		
    u16CRC = crc16_update(u16CRC, pduFrame[i]);
	}	
	return (lowByte(u16CRC)<<8)|(highByte(u16CRC));
}





