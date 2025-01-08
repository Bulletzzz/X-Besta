#Variavies de porta serial, reconhecimento de tempo e variavel de reconhecimento
import serial
import time
import numpy as np
import cv2

arduinoData = serial.Serial('COM4', 9600) #Porta serial do computador

def mandarcoordarduino(x, y, w, h):
    # Conversão das coordenadas para um string e envio para o Arduino
    coordinates = f"{x},{y}\r"
    arduinoData.write(coordinates.encode())
    print(f"X{x}Y{y}\n")

#Seleção e dimencionamento da camera
captura = cv2.VideoCapture(0) 
captura.set(cv2.CAP_PROP_FRAME_WIDTH, 1280)
captura.set(cv2.CAP_PROP_FRAME_HEIGHT, 720)

#sistema de reconhecimento facial por cascata e posição padrão da torreta
face_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_frontalface_default.xml')
x = 650
y = 650
h = 0
w = 0

#Abertura e fechamento da camera
while True:
    isTrue, imagem = captura.read()

    gray = cv2.cvtColor(imagem, cv2.COLOR_BGR2GRAY)
    faces = face_cascade.detectMultiScale(gray, 1.05, 8, minSize=(120,120))
    for (x, y, w, h) in faces:
        cv2.rectangle(imagem, (x, y), (x+w, y+h), (0, 255, 0), 5)
    jateveface = 0
    if len(faces) == 1:
        jateveface = 1
        x,y,w,h = faces[0]
        mandarcoordarduino(x, y, w, h)
    else:
        mandarcoordarduino(x, y, w, h)
    cv2.imshow('Video', imagem)

    if cv2.waitKey(20) & 0xFF == ord('d'):
        break

captura.release()
cv2.destroyAllWindows()