import serial
import time
#from serial import Serial

portName = 'com9'
baudrate = 38400
timeoutSp=0.1 

class SHSerialTool:
    #Original subnet ID
    def __init__(self,pName, baud): 
        self.ser=serial.Serial(port=pName, baudrate=baud)

    def sendDataWithResponse(self,data):
        print("Command:==> ",data)
        self.sendCommand(data)
        time.sleep(0.001) 
        return self.readResponse()

    def openPort(self):      
        if (self.ser.isOpen() == True):
            self.ser.close()    
        time.sleep(0.5)    
        self.ser.open()
        time.sleep(0.5) 
        return
    
    def closePort(self):
        if (self.ser.isOpen() == True):
            self.ser.close()

    def sendCommand(self,data):
        mbOut=data.encode(encoding='utf_8', errors='strict')
        #outLength = len(mbOut)
        self.ser.write(mbOut)
    
    def readResponse(self):         
        #print("Number bytes read",self.ser.in_waiting )
        ln = self.ser.readline()
        #outStr ='Response :<=='
        outStr =''
        outStr =outStr + ''.join([str(chr(i)) for i in ln])      
        return outStr   

    def receivePacket(self): 
        outPacket=bytearray()
        readyNum=self.ser.in_waiting
        outPacket +=  self.ser.read(1)
        return outPacket

    def sendFileAndExec(self, fName):
        srcFile =  open(fName, "r")
        for commandStr in srcFile:        
            outStr = self.sendDataWithResponse(commandStr)
            print(outStr)                      
        srcFile.close() 
    
    def eraseEEPROM(self,size, eepromAddr="0xee",  startAddr=0, buffSize=20 ):
        i=0
        bufSzCnt=0
        self.sendDataWithResponse(eepromAddr+".0x81="+str(startAddr))      
        time.sleep(0.1)
        while(i<size):
            self.sendDataWithResponse(eepromAddr+"."+str(i)+"=0xff\n")
            i+=1
            bufSzCnt+=1
            if(bufSzCnt >= buffSize):
                self.sendDataWithResponse(eepromAddr+".0x81="+str(startAddr)) 
                bufSzCnt = 0
                time.sleep(0.05)
        return 

    
    def readEEPROM(self,  size, eepromAddr="0xee",  startAddr=0, buffSize=20 ):
        i=0
        self.sendDataWithResponse(eepromAddr+".0x81="+str(startAddr))
        outStr=''
       # srcFile =  open('out.txt', "wb")
        #time.sleep(0.1)
        while(i<size):
            val=int(self.sendDataWithResponse("print("+eepromAddr+"."+str(i)+")\n"))
           # srcFile.write(val.to_bytes(1, byteorder='big'))
            print(val)
            #time.sleep(0.01)
            i+=1        
        return 

    def sendFileToEEPROM(self, fName, eepromAddr="0xee"):
        srcFile =  open(fName, "r")
        writeAddr = 0
        for commandStr in srcFile:
            print(commandStr)
            self.sendDataWithResponse(eepromAddr+".0x81="+str(writeAddr))
            #time.sleep(0.2)    
            mbOut=commandStr.encode(encoding='utf_8', errors='strict')
            i=0
            while(i<len(mbOut)):
                self.sendDataWithResponse(eepromAddr + "." + str(i) + '=' + str(mbOut[i]) + "\n")
                i+=1
            writeAddr = writeAddr+len(mbOut) 
            #time.sleep(0.2)
    #tkval.execute(slID, tkCst.WRITE_SINGLE_REGISTER, sendAddr+eepromAddr+1, output_value=0) 
        #time.sleep(0.2)   
        self.sendDataWithResponse(eepromAddr+".0x81="+str(0))        
        srcFile.close() 



try: 


    shCont=SHSerialTool(portName, baudrate)
    shCont.openPort()
    print("Waiting boot ...")
    time.sleep(2.0)
    #shCont.eraseEEPROM(size=20,startAddr=0) 
    #shCont.readEEPROM(size=20,startAddr=0)
    shCont.sendFileToEEPROM(r"e:/test/3but.txt") 
    shCont.readEEPROM(size=20,startAddr=0)  
    #shCont.sendFileAndExec(r"e:/test/test.txt") 
    #ser.reset_input_buffer()              
    shCont.closePort()

except IOError as e:
    print("Error ", e)
    quit()

