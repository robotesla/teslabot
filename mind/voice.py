import speech_recognition as sr
from yandex_speech import TTS
from pygame import mixer
from pygame.time import delay
from os import remove
from platform import system

r = sr.Recognizer()
tts = TTS("oksana", "mp3", "60556d09-0e84-42b7-8974-9d0b01cfee33")
mixer.init(frequency=48000)

def listen():
	'''
	Listening audio input from the microphone
	and return the recognized text using google's
	speech to text open api and library speechrecognition
	'''
	with sr.Microphone() as source:
		audio = r.listen(source)
	try:
		return r.recognize_google(audio, language="ru-RU")
	except sr.UnknownValueError:
		return 1
	except sr.RequestError:
		return 2

def say(text, savepath = 'phrases/livespeech.mp3'):
	'''
	Instantly to synthesize the text
	and speak it through the speakers
	'''
	tts.generate(text)
	tts.save(savepath)
	play_mp3(savepath)
	remove(savepath)
	# print('Done.')

def play_mp3(file_path, iswait = True):
	'''
	Plays local mp3 file from
	the hard drive
	'''
	mixer.music.load(file_path)
	mixer.music.play()
	if iswait == True:
		while mixer.music.get_busy():
			delay(0)
