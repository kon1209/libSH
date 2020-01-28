import serial
import time
import traceback
import modbus_tk.defines as tkCst
import modbus_tk.modbus_rtu as tkRtu


portName = 'com30'
baudrate = 38400
timeoutSp=0.1 
portNbr = 21
slaveId=0xF0
errCnts = 0
iterSp = 1
tb = None

def sendDataWithResponse(slID,tkval,inBuff, outBuff, data):
    #data+=0x0d0a.to_bytes(2,byteorder='big', signed=True);
    #print(data)
    errCnt = sendData(slID,tkval,inBuff, data)
    if(errCnt>0):
        return errCnt
    time.sleep(0.2)
    #tkmc.execute(slaveId, tkCst.WRITE_SINGLE_REGISTER, 0xc, output_value=202)     
    errCnt,tup= readData(slID, tkval,outBuff, 20)    
    return errCnt, tup

def sendData(slID,tkval,inBuff, data):
    errCnt =0
    outLength = len(data)
    try:
        tkval.execute( slID, tkCst.WRITE_MULTIPLE_REGISTERS, inBuff,outLength, output_value=data)   
    except:
        errCnt += 1
        tb = traceback.format_exc()
        print ("   !modbus-tk:\terrCnt: %s; last tb: %s" % (errCnt, tb))
    return errCnt

def readData(slID,tkval,outBuff,readLen):
    #status="read data slID - {},tkval - {},outBuff -{},readLen - {}".format(slID,tkval,outBuff,readLen)
    #print(status)
    errCnt =0
    tup=[]
    try:
        tup= tkval.execute(slID, tkCst.READ_HOLDING_REGISTERS,outBuff, readLen)    
    except:
        errCnt += 1
        tb = traceback.format_exc()
        print ("   !modbus-tk:\terrCnt: %s; last tb: %s" % (errCnt, tb))
    return errCnt, tup

def sendFileAndExec(tkval, fName, slID, sendAddr, respAddr):
    srcFile =  open(fName, "r")
    for commandStr in srcFile:
        print(commandStr)
        mbOut=commandStr.encode(encoding='utf_8', errors='strict')
        errCnts,outTup = sendDataWithResponse(slID, tkval ,sendAddr, respAddr, mbOut)
        if(errCnts>0):
            print("R/W Error!")
            quit()
        outStr = ''.join([str(chr(i)) for i in outTup])
        print(outStr)                      
    srcFile.close()   

def sendFileToEEPROM(tkval, fName, slID, eepromAddr):
    srcFile =  open(fName, "r")
    writeAddr = 0
    for commandStr in srcFile:
        print(commandStr)
        tkval.execute(slID, tkCst.WRITE_SINGLE_REGISTER, eepromAddr+0x81, output_value=writeAddr)
        time.sleep(0.2)    
        mbOut=commandStr.encode(encoding='utf_8', errors='strict')
        errCnts = sendData(slID, tkval ,eepromAddr, mbOut)
        if(errCnts>0):
            print("R/W Error!")
            quit()
        writeAddr = writeAddr+len(mbOut) 
        time.sleep(0.2)
    #tkval.execute(slID, tkCst.WRITE_SINGLE_REGISTER, sendAddr+eepromAddr+1, output_value=0) 
    time.sleep(0.2)   
    tkval.execute(slID, tkCst.WRITE_SINGLE_REGISTER, eepromAddr+0x81, output_value=0)                  
    srcFile.close()   

def eraseEEPROM(slID, tkval,eepromAddr, size, startAddr=0,buffSize=30 ):  
    i=0
    bufSzCnt=0
    tkval.execute(slID, tkCst.WRITE_SINGLE_REGISTER, (eepromAddr&0xFF00)+0x81, output_value=startAddr)
    time.sleep(0.1)
    while(i<size):
        tkval.execute(slID, tkCst.WRITE_SINGLE_REGISTER, (eepromAddr&0xFF00)+bufSzCnt, output_value=0xFF)
        time.sleep(0.05)
        i+=1
        bufSzCnt+=1
        if(bufSzCnt >= buffSize):
            tkval.execute(slID, tkCst.WRITE_SINGLE_REGISTER, (eepromAddr&0xFF00)+0x81, output_value=startAddr+i)
            bufSzCnt = 0
            time.sleep(0.05)
    return

def readEEPROM(slID, tkval,eepromAddr,  size, startAddr=0, buffSize=20 ):
    i=0
    commonTup =[]
    readAddress = (eepromAddr<<8) + startAddr
    while(i<size):
        if(i+buffSize>size):
            errCnts, outTup = readData(slID,tkval,readAddress + i,size-i)
        else:
            errCnts, outTup = readData(slID,tkval,readAddress + i,buffSize)
        commonTup+=outTup   
        time.sleep(0.05)
        i+=buffSize
    return commonTup



print( "timeout: %s [s]" % timeoutSp)
i=0
tkmc = tkRtu.RtuMaster(serial.Serial(port=portName, baudrate=baudrate))
tkmc.set_timeout(timeoutSp)
startTs = time.time()

#stop console
#sendData(slaveId,tkmc,0x00, [3,3])
time.sleep(0.2)
#sendData(slaveId,tkmc,0x0700, [0x200])
sendFileAndExec(tkmc, r"e:/test/out3.txt", slaveId, 0x6400, 0x6400)

time.sleep(0.2)
commonTup=readEEPROM(slaveId,tkmc,0xE0,150)
#print(commonTup)

outStr = ''
for i in commonTup:
    if((i==0xff) ):
        break
    outStr += ''.join([str(chr(i))])
    
print(outStr)


#commandStr="ram(0)\n"
#commandStr="7=blk(0x60d,0)"
commandStr="7.0=500\n"
print(commandStr)
mbOut=commandStr.encode(encoding='utf_8', errors='strict')
#mbOut+=0x0d0a.to_bytes(2,byteorder='big', signed=True);
errCnts,outTup = sendDataWithResponse(slaveId,tkmc ,0x6400, 0x6400, mbOut)
outStr = ''.join([str(chr(i)) for i in outTup])
if errCnts >0:
    print ("   !modbus-tk:\terrCnt: %s; last tb: %s" % (errCnts, tb))
print(outStr)                      

quit()

#sendFileToEEPROM(tkmc,  r"e:/test/test_1.txt", slaveId, 0xEE00)
#time.sleep(0.2)

#eraseEEPROM(slaveId,tkmc,0xEE00,100)
#time.sleep(0.2)                  

#sendFileAndExec(tkmc, r"e:/test/test.txt", slaveId, 0x3000, 0x3100) 

#sendData(slaveId,tkmc,0x00, [241,1,0,0x30])


stopTs = time.time()
tkmc.close()
timeDiff = stopTs -  startTs
print("Time diff %.3f [s]/n" % timeDiff)
print("Time per packet exchange %.3f [s]/n" % (timeDiff/iterSp))
print("Packet number per second %.3f [s]/n" % (1/(timeDiff/iterSp)))
if errCnts >0:
    print ("   !modbus-tk:\terrCnt: %s; last tb: %s" % (errCnts, tb))
