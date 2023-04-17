import speech_recognition as sr
from datetime import date
from time import sleep
import os
from gtts import gTTS
import serial
  
# initialisation

language = 'es'
r = sr.Recognizer()
mic = sr.Microphone() #my device index is 1, you have to put your device index
ser = serial.Serial("COM12",9600)
print("hello")

while True:

    with mic as source:
        print("say something!…")
        audio = r.adjust_for_ambient_noise(source)
        audio = r.listen(source)
    try:
        recog = r.recognize_google(audio, language = 'es-MX')
        
        if recog == "abajo":
            ser.write(b"abajo,0\n")

        if recog == "arriba":
            ser.write(b"arriba,0\n")

        if recog == "sentado":
            ser.write(b"sentado,0\n")

        print("You said: " + recog)
        mytext = '   dio ha reconocido el comando' + recog
        myobj = gTTS(text=mytext, lang=language, slow=False)
        # Saving the converted audio in a mp3 file named
        # welcome 
        myobj.save("example.mp3")
        # Playing the converted file
        os.system("start example.mp3")
        sleep(5)
    except sr.UnknownValueError:
        print("Google Speech Recognition could not understand audio")
    except sr.RequestError as e:
        print("Could not request results from Google Speech Recognition service; {0}".format(e))
