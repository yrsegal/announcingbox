

import time

def handshakeProtocol(timestampData, serialLink):
	timeheader = "*" + str(time.time())
	stamps = "____".join(["T"+str(i[0])+str(i[1]) for i in timestampData])
	serialLink.write(timeheader)
	serialLink.write(stamps)
