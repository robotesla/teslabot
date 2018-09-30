from mind.dialog import listen
from mind.dialog import say
from mind.dialog import play_mp3
from cv2 import VideoCapture
from cv2 import cvtColor
from cv2 import COLOR_BGR2GRAY
from cv2 import CascadeClassifier
from cv2 import rectangle
from cv2 import imshow
from cv2 import waitKey
from time import sleep

face_cascade = CascadeClassifier('haarcascades/frontalface.xml')
cap = VideoCapture(0)

while True:
	ret, img = cap.read()
	gray = cvtColor(img, COLOR_BGR2GRAY)
	faces = face_cascade.detectMultiScale(gray, 1.3, 5)
	print(faces)
	for (x,y,w,h) in faces:
		rectangle(img,(x,y),(x+w,y+h),(255, 0, 0), 2)

	imshow('img',img)
	k = waitKey(30) & 0xff
	if k == 27:
		break