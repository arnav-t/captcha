#!/usr/bin/python3

import urllib.request
import time
import os
import moviepy.editor as mpy

mapURL = 'http://satellite.imd.gov.in/img/3Dasiasec_bt1.jpg'
currDir = '/home/avz/Documents/py/insat/'
fps = 2
gifName = 'animation.gif'

def saveMap(count):
	urllib.request.urlretrieve(mapURL, currDir + str(count) + '.jpg')

currentMap = 0

if os.stat(currDir + 'maps.log').st_size:
	with open(currDir + 'maps.log', 'r') as logfile:
		for line in logfile:
			pass
		currentMap = (int(line[-6]) + 1)%10

t = time.localtime()
currTime = time.strftime('%b-%d-%Y_%R:%S', t)

saveMap(currentMap)
with open(currDir + 'maps.log', 'a') as logfile:
	logfile.write(currTime + ' ' + str(currentMap) + '.jpg\n')

images = []
for i in range(10):
	images.append(currDir + str((currentMap - 9 + i)%10) + '.jpg')
clip = mpy.ImageSequenceClip(images, fps=fps)
clip.write_gif(currDir + gifName, fps=fps)
