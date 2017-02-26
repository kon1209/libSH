#include "Arduino.h"
#include "input.h"

   Input::Input(byte pinNum){
    pin = pinNum;
    pinMode(pin,INPUT_PULLUP);
    }

