import serial
import time
#import traceback
#import modbus_tk.defines as tkCst
import modbus_tk.modbus_rtu as tkRtu
import mbSlave


portName = 'com30'
baudrate = 38400
timeoutSp=0.1 
portNbr = 21
slaveId=0xF0
errCnts = 0
iterSp = 1
tb = None


print( "timeout: %s [s]" % timeoutSp)
i=0
tkmc = tkRtu.RtuMaster(serial.Serial(port=portName, baudrate=baudrate))
tkmc.set_timeout(timeoutSp)
startTs = time.time()

slave1 = mbSlave.shModbusSlave(slaveId,tkmc) 

#stop console
#sendData(slaveId,tkmc,0x00, [3,3])
time.sleep(0.2)
#eraseEEPROM(slaveId,tkmc,0xE000,100)
#quit()
#sendData(slaveId,tkmc,0x0700, [0x200])
#sendFileAndExec(tkmc, r"e:/test/out3.txt", slaveId, 0x6400, 0x6400)
#sendFileToEEPROM(tkmc,  r"e:/test/out2.txt", slaveId, 0xE0)
time.sleep(0.2)
commonTup=slave1.readEEPROM(0xE0,150)
#print(commonTup)

outStr = ''
for i in commonTup:
    if((i==0xff) ):
        break
    outStr += ''.join([str(chr(i))])
    
print(outStr)


commandStr="ram(0)\n"
#commandStr="7=blk(0x60d,0)"
#commandStr="7.0=500\n"
print(commandStr)
mbOut=commandStr.encode(encoding='utf_8', errors='strict')
#mbOut+=0x0d0a.to_bytes(2,byteorder='big', signed=True);
errCnts,outTup = slave1.sendDataWithResponse(0x6400, 0x6400, mbOut)
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
