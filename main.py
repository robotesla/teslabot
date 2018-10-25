from mind.voice import *
from mind.dialog import *
from protocol.motors import move_forward
from protocol.motors import stop_action
from cv2 import VideoCapture
from cv2 import cvtColor
from cv2 import COLOR_BGR2GRAY
from cv2 import CAP_PROP_FRAME_WIDTH
from cv2 import CAP_PROP_FRAME_HEIGHT
from cv2 import CascadeClassifier
from time import sleep

face_cascade = CascadeClassifier('assets/frontalface.xml')
cap = VideoCapture(0)

cap.set(CAP_PROP_FRAME_WIDTH, 1280)
cap.set(CAP_PROP_FRAME_HEIGHT, 720)

is_face_found = False

while True:
	ret, img = cap.read()
	gray = cvtColor(img, COLOR_BGR2GRAY)
	faces = face_cascade.detectMultiScale(gray, 1.3, 5)
	
	if len(faces) != 0:
		for (x, y, w, h) in faces:
			print('Face detected at ' + str(x) + ', ' + str(y))
			stop_action()
		if is_face_found == False:
			say('Привет!')

		is_face_found = True
		listened_text = listen()
		print('Listened: \"' + str(listened_text) + "\"")
		if listened_text == 1 or listened_text == 2:
			continue
		neural_answer = get_response(listened_text)
		say(str(neural_answer))
	else:
		print('Faces not found. Going forward.')
		move_forward(255)
		is_face_found = False