#!/usr/bin/python3
import sys
import subprocess
import os
import binascii
from shutil import which
import datetime

if len(sys.argv) != 3 and len(sys.argv) != 4:
	sys.stderr.write("Usage: " + sys.argv[0] + " executable datafile.dat [addr2line-command]\n")
	sys.exit(-1)

addr2line="addr2line"
if len(sys.argv) == 4:
	addr2line=sys.argv[3]

version = sys.version_info[0]
print ("Python version: " + str(version))
if version < 3:
	sys.stderr.write("ERROR: Python 3 needed!")
	sys.exit(-1)

if (which(addr2line) is None):
	sys.stderr.write("ERROR: addr2line needed!\n")
	sys.stderr.write("(type 'sudo apt install binutils' on Ubuntu)\n")
	sys.exit(-1)

file_out = open("trace.txt", "w")
file_out.write("time:\tfunction:\tcaller:\targ1:\targ2:\targ3:\targ4:\n")
file_out.write("===========================================================\n");
start = True
with open(sys.argv[2]) as file_in:
	# Skip first two lines
	next(file_in)
	next(file_in)
	for line in file_in:
		if len(line.split()) < 7:
			break
		time = line.split()[7]
		function_address = line.split()[1]

		function = subprocess.run([addr2line + " -f -e " + sys.argv[1] + " " + function_address], \
		shell=True, stdout=subprocess.PIPE).stdout.decode('utf-8').split()[0]

		caller_address = line.split()[2]
		caller = subprocess.run([addr2line + " -f -e " + sys.argv[1] + " " + caller_address], \
		shell=True, stdout=subprocess.PIPE).stdout.decode('utf-8').split()[0]
		file_out.write(time + "\t" + function + "\t" + caller + "\t" + line.split()[3] + "\t" \
		+ line.split()[4] + "\t" + line.split()[5] + "\t" + line.split()[6] + "\n")
print ("File trace.txt successfully written")
