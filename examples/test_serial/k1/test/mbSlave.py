import time
import traceback
import modbus_tk.defines as tkCst



class shModbusSlave():
    def __init__(self,slID,tkval):
        self._slID = slID
        self._tkval = tkval

    def sendDataWithResponse(self,inBuff, outBuff, data):
        #data+=0x0d0a.to_bytes(2,byteorder='big', signed=True);
        #print(data)
        errCnt = self.sendData(inBuff, data)
        if(errCnt>0):
            return errCnt
        time.sleep(0.1)     
        errCnt,tup= self.readData(outBuff, 20)    
        return errCnt, tup

    def sendData(self,inBuff, data):
        errCnt =0
        outLength = len(data)
        try:
            self._tkval.execute( self._slID, tkCst.WRITE_MULTIPLE_REGISTERS, inBuff, outLength, output_value=data)   
        except:
            errCnt += 1
            tb = traceback.format_exc()
            print ("   !modbus-tk:\terrCnt: %s; last tb: %s" % (errCnt, tb))
        return errCnt

    def readData(self,outBuff,readLen):
        #status="read data slID - {},tkval - {},outBuff -{},readLen - {}".format(slID,tkval,outBuff,readLen)
        #print(status)
        errCnt =0
        tup=[]
        try:
            tup= self._tkval.execute(self._slID, tkCst.READ_HOLDING_REGISTERS,outBuff, readLen)    
        except:
            errCnt += 1
            tb = traceback.format_exc()
            print ("   !modbus-tk:\terrCnt: %s; last tb: %s" % (errCnt, tb))
        return errCnt, tup

    def sendFileAndExec(self, fName, sendAddr, respAddr):
        srcFile =  open(fName, "r")
        for commandStr in srcFile:
            self.execOneCommand(commandStr,sendAddr, respAddr) 
            time.sleep(0.1)                     
        srcFile.close()   

    def execOneCommand(self, commandStr, sendAddr, respAddr):
        print(commandStr)
        mbOut=commandStr.encode(encoding='utf_8', errors='strict')
        errCnts,outTup = self.sendDataWithResponse(sendAddr, respAddr, mbOut)
        if(errCnts>0):
            print("R/W Error!")
            quit()
        outStr = ''.join([str(chr(i)) for i in outTup])
        print(outStr)
        return outStr                      

    def sendFileToEEPROM(self,fName, eepromAddr):
        srcFile =  open(fName, "r")
        writeAddr = 0
        for commandStr in srcFile:
            addLen = len(commandStr)
            commandStr=str(eepromAddr)+'.' + str(writeAddr) +'='+'"'+commandStr.rstrip('\n')+'"'+"\n" 
            print(commandStr)   
            mbOut=commandStr.encode(encoding='utf_8', errors='strict')
            errCnts = self.sendData(0x6400, mbOut)
            if(errCnts>0):
                print("R/W Error!")
                quit()
            writeAddr = writeAddr+addLen 
            time.sleep(0.5)                   
        srcFile.close()   

    def eraseEEPROM(self, eepromAddr, size, startAddr=0 ):  
        i=0
        time.sleep(0.1)
        addrToErase = (eepromAddr&0xFF00)+startAddr
        while(i<size):
            self._tkval.execute(self._slID, tkCst.WRITE_SINGLE_REGISTER, addrToErase+ i, output_value=0x0)
            time.sleep(0.05)
            i+=1

    def readEEPROM(self, eepromAddr,  size, startAddr=0, buffSize=30 ):
        i=0
        commonTup =[]
        readAddress = (eepromAddr<<8) + startAddr
        while(i<size):
            if(i+buffSize>size):
                errCnts, outTup = self.readData(readAddress + i,size-i)
            else:
                errCnts, outTup = self.readData(readAddress + i,buffSize)
            commonTup+=outTup   
            time.sleep(0.05)
            i+=buffSize
        return commonTup

