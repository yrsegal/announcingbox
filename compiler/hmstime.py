

import time

def hmsTimeStamp(ctime=None):
	if not ctime:
		ctime = int(time.time())
	timetuple = time.localtime(ctime)
	timestamp = 3600*timetuple[3]+60*timetuple[4]+timetuple[5]
	return timestamp

def hmsTime(ctimestamp):
	times = ctimestamp % 60
	timem = ((ctimestamp - times)/60) % 60
	timeh = ((ctimestamp - (timem*60))/3600)
	return (timeh, timem, times)