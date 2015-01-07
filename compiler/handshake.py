

import serial

def transmitUntil(signal, waitingSignal, serialLink):
	serialLink.write(signal)
	waitForSignal(waitingSignal, serialLink)

def waitForSignal(signal, serialLink):
	data = serialLink.read(1)
	while data != signal:
		data = serialLink.read(1)

def handshakeProtocol(timestampData, serialLink):
	transmitUntil("S", "s", serialLink)
	for i in timestampData:
		serialLink.write(str(i))
		serialLink.write("T")
		waitForSignal("t", serialLink)
	transmitUntil("E", "e", serialLink)