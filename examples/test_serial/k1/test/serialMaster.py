import serial
import time
#from serial import Serial

portName = 'com28'
baudrate = 38400
timeoutSp=0.1 

class SHSerialTool:
    #Original subnet ID
    def __init__(self,pName, baud): 
        self.ser=serial.Serial(port=pName, baudrate=baud)

    def sendDataWithResponse(self,data):
        print("Command:==> ",data)
        self.sendCommand(data)
        time.sleep(0.2) 
        return self.readResponse()

    def openPort(self):      
        if (self.ser.isOpen() == True):
            self.ser.close()    
        time.sleep(0.5)    
        self.ser.open()
        return
    
    def closePort(self):
        if (self.ser.isOpen() == True):
            self.ser.close()

    def sendCommand(self,data):
        mbOut=data.encode(encoding='utf_8', errors='strict')
        #outLength = len(mbOut)
        self.ser.write(mbOut)
    
    def readResponse(self): 
        ln = self.ser.readline()
        outStr ='Response :<=='
        outStr =outStr + ''.join([str(chr(i)) for i in ln])
      
        return outStr   

    def receivePacket(self):
 
        outPacket=bytearray()
        readyNum=self.ser.in_waiting
        outPacket +=  self.ser.read(1)

        return outPacket



try: 
    shCont=SHSerialTool(portName, baudrate)
    shCont.openPort()
    time.sleep(1.0)  
 
 
    print(shCont.sendDataWithResponse('6=dio()'))
    #ser.reset_input_buffer()      
        
    shCont.closePort()

except IOError as e:
    print("Error ", e)
    quit()

