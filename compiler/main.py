sys.path.append("..")
import albow, serial
import pygame as pg
import ports, handshake, hmstime
import re

timefind = re.compile("[0-9]?[0-9]:[0-9][0-9]")

def example_main():
	times = []
	inp = ""
	while inp != "done":
		inp = raw_input("Enter times you need to take a pill (hh:mm) ")
		temptimes = []
		for i in timefind.findall(inp): temptimes.append(i)
		inp = raw_input("Enter which compartment the pill will be in (1, 2, 3) ")
		if inp in "123":
			for i in temptimes:
				times.append([tconvert(i), inp])
	s = ports.getSerial()
	handshake.handShakeProtocol(times, s)