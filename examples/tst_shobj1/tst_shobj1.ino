
//#include <Wire.h>
#include <shconfig.h>

SmartHomeController * pCont = new SmartHomeController();
SmartHomeController * SmartHomeObject::pController = pCont;

void setup() {
  Serial.begin(38400);
  SmartHomeObject * pObj;  
  // create objects
  pObj = (SmartHomeObject *)  new DigitalIO();
   pCont -> addObject(0x6,pObj, SHO_DIO); 

 pObj = (SmartHomeObject *) new ModbusSmartHome(1,32,0xF0,2);
 pCont -> addObject(2,pObj, SHO_MBS);

  // I2CPWM(4,0x40);   I2CExpander(5,0x20);    

  pObj = (SmartHomeObject *) new SHConsole(30);
  pCont -> addObject(100, pObj, SHO_CON);

 pObj = (SmartHomeObject *) new SHEeprom((byte)0);
 pCont -> addObject(0xE0,pObj,SHO_EEP);  
 
 pObj = (SmartHomeObject *) new SHSerial(100);
 pCont -> addObject(0x33,pObj,SHO_SER);  
/*
for (byte i =0;i<0x10;i++){
 pObj = (SmartHomeObject *) new Button(0x608);
 pCont -> addObject(0x40+i,pObj,SHO_BTN);
     
}
for (byte i =0;i<0x10;i++){
 pObj = (SmartHomeObject *) new Dimmer(0x40+i,0x60a);
 pCont -> addObject(0x70+i,pObj,SHO_DIM);
     
}*/
/*
  pObj = (SmartHomeObject *) new ButtonArray();
  pCont -> addObject(0x10,pObj,SHO_BTN); 

 pObj = (SmartHomeObject *) new DimmerArray();
 pCont -> addObject(0x11,pObj,SHO_DIM); 
*/
  
  //Serial.print( pCont ->freeRam());  
}

void loop() {
  pCont -> process();
}
