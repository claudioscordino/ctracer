#!/usr/bin/python3
import sys
import subprocess
import os
import binascii
from shutil import which
import datetime

if len(sys.argv) != 2:
    sys.stderr.write("Usage: " + sys.argv[0] + " executable\n")
    sys.exit(-1)
program=sys.argv[1]

version = sys.version_info[0]
print ("Python version: " + str(version))
if version < 3:
    sys.stderr.write("ERROR: Python 3 needed!")
    sys.exit(-1)

if (which("addr2line") is None):
    sys.stderr.write("ERROR: addr2line needed!\n")
    sys.stderr.write("(type 'sudo apt install binutils' on Ubuntu)\n")
    sys.exit(-1)

file = open("trace.btf", "w")
file.write("#version 2.2.0\n")
file.write("#creator Claudio Scordino\n")
file.write("#creationDate " + str(datetime.datetime.utcnow().isoformat()) + "\n")
file.write("#timescale ns\n")
result = subprocess.run(['./main'], stdout=subprocess.PIPE).stdout.decode('utf-8').splitlines()
print ("Data size = ", len(result))
row = 0
funtion = ""
while (row < len(result)):
    if "TRACE" in result[row]:
        time = result[row].split()[1]
        address = result[row].split()[2]
        if row == 0:
            file.write(time + ",Core_1,,T,TASK_A,,start\n")
        else:
            file.write(time + ",TASK_A,,R," + function + ",,terminate\n")
        function = subprocess.run(["addr2line -f -e " + program + " " + address], \
        shell=True, stdout=subprocess.PIPE).stdout.decode('utf-8').split()[0]
        file.write(time + ",TASK_A,,R," + function + ",,start\n")
    row += 1
file.write(time + ",TASK_A,,R," + function + ",,terminate\n")
