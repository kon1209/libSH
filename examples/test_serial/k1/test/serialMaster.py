import serial
import time
#from serial import Serial

portName = 'com6'
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
        time.sleep(0.1)    
        self.ser.open()
        time.sleep(0.1) 
        return
    
    def closePort(self):
        if (self.ser.isOpen() == True):
            self.ser.close()

    def sendCommand(self,data):
        mbOut=data.encode(encoding='utf_8', errors='strict')
        #outLength = len(mbOut)
        self.ser.write(mbOut)
    
    def readResponse(self): 
        outStr =''        
        #print("Number bytes read",self.ser.in_waiting )
        #if(self.ser.in_waiting>0):
        ln = self.ser.readline()
        #outStr ='Response :<=='
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
    
    def eraseEEPROM(self,size, eepromAddr="0xe0",  startAddr=0):
        i=0    
        time.sleep(0.1)
        while(i<size):
            outStr = self.sendDataWithResponse(eepromAddr+"."+ str(startAddr+i)+"=0xf5") 
            print(outStr)
            time.sleep(0.05)
            i+=1
        return 

    
    def readEEPROM(self,  size, eepromAddr="0xe0",  startAddr=0, buffSize=20 ):
        i=0
        bufSzCnt=startAddr
       # self.sendDataWithResponse(eepromAddr+".0x81="+str(startAddr))
        srcFile =  open('out.txt', "wb")
        #time.sleep(0.1)
        while(i<size):
            strVal = self.sendDataWithResponse("print("+eepromAddr+","+str(bufSzCnt)+")\n")
            val=int(strVal[1:])
            if (val ==0 or val == 255):
                break
            srcFile.write(val.to_bytes(1, byteorder='big'))
            print(val)
            bufSzCnt+=1
            i+=1
            #if(bufSzCnt >= buffSize):
             #   self.sendDataWithResponse(eepromAddr+".0x81="+str(startAddr+i)) 
              #  bufSzCnt = 0  
            # time.sleep(0.05)     
        return 

    def getEEPROM(self,  size, eepromAddr="0xe0",  startAddr=0, buffSize=20 ):
        i=0
        bufSzCnt=startAddr
       # self.sendDataWithResponse(eepromAddr+".0x81="+str(startAddr))
        srcFile =  open('out.txt', "wb")
        #time.sleep(0.1)
        while(i<size):
            strVal = self.sendDataWithResponse("getl(100,"+eepromAddr+","+str(bufSzCnt)+")\n")
            if len(strVal)<5:
                break
            print(strVal)            
            bufSzCnt+=len(strVal)-2            
            i+=1
            srcFile.write(strVal[1:].encode())   
        return 


    def sendFileToEEPROM(self, fName, eepromAddr="0xe0", startAddr=0):
        srcFile =  open(fName, "r")
        writeAddr = startAddr
        for commandStr in srcFile:
            print(commandStr)
            #print(outStr)
            time.sleep(0.2)    
           # mbOut=commandStr.encode(encoding='utf_8', errors='strict')
            mbOut=eepromAddr+'.' + str(writeAddr) +'='+'"'+commandStr.rstrip('\n')+'"'+"\n"
            print(self.sendDataWithResponse(mbOut))
            time.sleep(0.5) 
            writeAddr = writeAddr+len(commandStr)
            #time.sleep(0.2)
        srcFile.close() 



try: 


    shCont=SHSerialTool(portName, baudrate)
    shCont.openPort()
    print("Waiting boot ...")
    time.sleep(2.0)
    #shCont.eraseEEPROM(size=20,startAddr=300) 
    #shCont.sendFileToEEPROM(r"3btn.txt") 

   # shCont.getEEPROM(size=11,startAddr=0)  
    shCont.sendFileAndExec(r"8but_8dim.txt") 
    #shCont.sendFileAndExec(r"e:/test/3but_1.txt")
    #ser.reset_input_buffer()              
    shCont.closePort()

except IOError as e:
    print("Error ", e)
    quit()

