#!/usr/bin/python3
import sys
import subprocess
import os
import binascii
from shutil import which
import datetime

if len(sys.argv) != 3:
    sys.stderr.write("Usage: " + sys.argv[0] + " executable datafile.dat\n")
    sys.exit(-1)

version = sys.version_info[0]
print ("Python version: " + str(version))
if version < 3:
    sys.stderr.write("ERROR: Python 3 needed!")
    sys.exit(-1)

if (which("addr2line") is None):
    sys.stderr.write("ERROR: addr2line needed!\n")
    sys.stderr.write("(type 'sudo apt install binutils' on Ubuntu)\n")
    sys.exit(-1)

file_out = open("trace.btf", "w")
file_out.write("#version 2.2.0\n")
file_out.write("#creator Claudio Scordino\n")
file_out.write("#creationDate " + str(datetime.datetime.utcnow().isoformat()) + "\n")
file_out.write("#timescale ns\n")
start = True
with open(sys.argv[2]) as file_in:
    next(file_in)
    next(file_in)
    for line in file_in:
        time = line.split()[7]
        address = line.split()[1]
        if start:
            file_out.write(time + ",Core_1,,T,TASK_A,,start\n")
            start = False
        else:
            file_out.write(time + ",TASK_A,,R," + function + ",,terminate\n")
        function = subprocess.run(["addr2line -f -e " + sys.argv[1] + " " + address], \
        shell=True, stdout=subprocess.PIPE).stdout.decode('utf-8').split()[0]
        file_out.write(time + ",TASK_A,,R," + function + ",,start\n")
file_out.write(time + ",TASK_A,,R," + function + ",,terminate\n")
print ("File trace.btf successfully written")
