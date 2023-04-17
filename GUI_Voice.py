from tkinter import *
from PIL import Image
from PIL import ImageTk
import cv2
import imutils
import speech_recognition as sr
from datetime import date
from time import sleep
import os
from gtts import gTTS

# initialisation
if __name__ == '__main__':
    #ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
    ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=1)
    ser.reset_input_buffer()

    while True:
        ser.write(b"Hello from Raspberry Pi!\n")

language = 'es'
r = sr.Recognizer()
mic = sr.Microphone()  # my device index is 1, you have to put your device index
print("hello")


def iniciar():
    global cap
    cap = cv2.VideoCapture('http://192.168.100.21:8000/stream.mjpg')
    visualizar()


def visualizar():
    global cap
    if cap is not None:
        ret, frame = cap.read()
        if ret == True:
            frame = imutils.resize(frame, width=640)
            frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)

            im = Image.fromarray(frame)
            img = ImageTk.PhotoImage(image=im)

            lblVideo.configure(image=img)
            lblVideo.image = img
            lblVideo.after(10, visualizar)
        else:
            lblVideo.image = ""
            cap.release()


def comando():
    with mic as source:
        audio = r.adjust_for_ambient_noise(source)
        audio = r.listen(source)
    try:
        recog = r.recognize_google(audio, language='es-MX')

        if recog == "abajo":
            mytext = 'El comando ' + recog + 'ha sido indentificado'
            myobj = gTTS(text=mytext, lang=language, slow=False)
            myobj.save("welcome.mp3")
            os.system("mpg123 "+"welcome.mp3")
            ser.write(b"abajo\n")

        elif recog == "arriba":
            mytext = 'El comando ' + recog + 'ha sido indentificado'
            myobj = gTTS(text=mytext, lang=language, slow=False)
            myobj.save("welcome.mp3")
            os.system("mpg123 "+"welcome.mp3")
            ser.write(b"arriba\n")

        elif recog == "sentado":
            mytext = 'El comando ' + recog + 'ha sido indentificado'
            myobj = gTTS(text=mytext, lang=language, slow=False)
            myobj.save("welcome.mp3")
            os.system("mpg123 "+"welcome.mp3")
            ser.write(b"sentado\n")

        else:
            mytext = 'El comando ' + recog + 'no es valido'
            myobj = gTTS(text=mytext, lang=language, slow=False)
            myobj.save("welcome.mp3")
            os.system("mpg123 "+"welcome.mp3")

    except sr.UnknownValueError:
        myobj = gTTS(text='No entendi, repita el comando',
                     lang=language, slow=False)
        myobj.save("welcome.mp3")
        os.system("mpg123 "+"welcome.mp3")
    except sr.RequestError as e:
        myobj = gTTS(text='No se pudo conectar con la API',
                     lang=language, slow=False)
        myobj.save("welcome.mp3")
        os.system("mpg123 "+"welcome.mp3")


cap = None
root = Tk()

btnIniciar = Button(root, text="Iniciar", width=45, command=iniciar)
btnIniciar.grid(column=0, row=0, padx=5, pady=5)

btnFinalizar = Button(root, text="Comando", width=45, command=comando)
btnFinalizar.grid(column=1, row=0, padx=5, pady=5)

lblVideo = Label(root)
lblVideo.grid(column=0, row=1, columnspan=2)

root.mainloop()
