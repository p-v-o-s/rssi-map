import time, glob, serial, os

ports = glob.glob("/dev/ttyUSB*")
ports.sort()

mote = serial.Serial(ports[0], baudrate=9600)
mote.flush()

n = 1
fn = "log_%d.csv" % n
while os.path.isfile(fn):
    n += 1
    fn = "log_%d.csv" % n

logfile = open(fn,'w')

try:
    while True:
        line = mote.readline().strip()
        line = ("%0.6f," % time.time()) + line
        print line
        logfile.write(line + "\n")
        logfile.flush()
        
except KeyboardInterrupt:
    pass
finally:
    logfile.close()
    mote.close()
