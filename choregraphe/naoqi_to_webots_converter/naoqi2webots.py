#/usr/bin/python3
import datetime
import argparse
import importlib
import os
from typing import List, Tuple

class Naoqi2Webots():
	def __init__(self):
		self.standInit= {
				"HeadPitch": 0,
				"HeadYaw": 0,
				"LAnklePitch": -0.345087,
				"LAnkleRoll": -0.00726946,
				"LElbowRoll": -1.0093,
				"LElbowYaw": -1.38179,
				"LHand": 0.257812,
				"LHipPitch": -0.443515,
				"LHipRoll": 0.00781505,
				"LHipYawPitch": 0,
				"LKneePitch": 0.691102,
				"LShoulderPitch": 1.40072,
				"LShoulderRoll": 0.296187,
				"LWristYaw": 0.00399396,
				"RAnklePitch": -0.345087,
				"RAnkleRoll": 0.00726919, 
				"RElbowRoll": 1.0093,
				"RElbowYaw": 1.38179,
				"RHand": 0.257812,
				"RHipPitch": -0.443515,
				"RHipRoll": -0.00781466,
				"RHipYawPitch": 0,
				"RKneePitch": 0.691102,
				"RShoulderPitch": 1.40072,
				"RShoulderRoll": -0.296187,
				"RWristYaw": 0.00399396
				}

	def parseTime(self, t: float) -> str:
		"""
		Parse time from naoqi to webots format

		:param t: Time in seconds
		:type t: float

		:returns: Time in mm:ss:fff
		:rtype: str
		"""
		m = int(t/60)
		s = int(t-m*60)
		ms = int((t-m*60-s)*1000000)

		time = datetime.time(minute=m, second=s, microsecond=ms)
		return time.strftime("%M:%S:%f")[:-3]

	def parse(self, names: List[str], keys: List[float], times: List[float]) -> Tuple[List[List[str]], List[float]]:
		"""
		Parse the motion format of naoqi to webots

		:param names: Names of the joints
		:type names: List[str]
		:param keys: Key values of joints
		:type keys: List[float]
		:param times: Time values
		:type times: List[float]

		:returns: A tuple containing a lists of lists with the values of joints per time and a list of floats with times
		:rtype: Tuple[List[float], List[float]]
		"""
		allTimes = []
		for time in times:
			for t in time:
				if not t in allTimes:
					allTimes.append(t)

		allTimes.sort()

		# list of lists of dim joints*times length
		allKeys = [[None]*len(names) for _ in range(len(allTimes))]

		for nameindex, (key, time) in enumerate(zip(keys, times)):
			for k, t in zip(key, time):
				timeIndex = allTimes.index(t)
				
				if timeIndex == 0:
					allKeys[timeIndex][nameindex] = str(k)
				else:
					# for every value before the current that is None, set the current value
					for i in range(timeIndex):
						if i == 0 and not allKeys[i][nameindex]:
							allKeys[i][nameindex] = str(k)
							allKeys[i][nameindex] = str(self.standInit[names[nameindex]])

						elif i!=0 and not allKeys[i][nameindex]:
							allKeys[i][nameindex] = allKeys[i-1][nameindex]	
					allKeys[timeIndex][nameindex] = str(k)

			if timeIndex < len(allTimes):
				for aKey in allKeys[timeIndex:]:
					aKey[nameindex] = allKeys[timeIndex-1][nameindex]

		return allKeys, allTimes


if __name__ == '__main__':


	parser = argparse.ArgumentParser()
	parser.add_argument("--orig",type=str, default='animations/Stand/BodyTalk/Listening.py', help="Origin python file with naoqi motions")
	parser.add_argument("--dest",type=str, default='motions/animations/Stand/BodyTalk/Listening', help="Destination path for motion files")
	args = parser.parse_args()

	origPath, origPackage, origFile = "/".join(args.orig.split("/")[:-1]), ".".join(args.orig.split("/")[:-1]), args.orig.split("/")[-1]
	destPath = args.dest

	n2w = Naoqi2Webots()


	nh = []
	wm = []
	s = []
	wb = []
	d = []

	# Dynamic import of libraries. The motion library must be in animations folder. 
	nm = importlib.import_module("%s.%s" % (origPackage, origFile.split(".")[0]))

	for fname in dir(nm):
		movement = getattr(nm, fname)
		if callable(movement):
			names, keys, times = movement()
			allKeys, allTimes = n2w.parse(names, keys, times)

			if not os.path.exists(destPath):
				os.makedirs(destPath)

			with open("%s/%s.motion" % (destPath, fname), "w") as fmotion:
				

				nh.append('node_handle_.param("motion_%s", wb_file_motion_%s_, std::string("%s/%s.motion"));\n' % (fname, fname, destPath, fname))
				wm.append('wb_motion_%s_         = new webots::Motion(wb_file_motion_%s_);\n' % (fname, fname))
				s.append('std::string wb_file_motion_%s_;\n' % fname)
				wb.append('webots::Motion* wb_motion_%s_;\n' % fname)
				d.append('delete wb_motion_%s_;\n' % fname)
				
				fmotion.write("#WEBOTS_MOTION,V1.0,%s\n" % ",".join(names))
				
				for i, (keys, time) in enumerate(zip(allKeys, allTimes)):
					row = "%s,Pose%d,%s\n" % (n2w.parseTime(time), i+1, ",".join(keys))
					fmotion.write(row)
				
	with open("cpp/webots_code_%s.txt" % origFile, "w") as fcode:

		fcode.write("//Node handle\n")
		fcode.writelines(nh)
		fcode.write("// load motion files\n")
		fcode.writelines(wm)
		fcode.writelines("// Webots Motions files\n")
		fcode.writelines(s)
		fcode.write("// Webots Motions\n")
		fcode.writelines(wb)
		fcode.write("// destructors\n")
		fcode.writelines(d)
		