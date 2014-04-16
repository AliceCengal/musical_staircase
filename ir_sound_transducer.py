
import pygame
import serial
import time
from collections import deque

NUMPINS   = 6
CAP_CONST = 20
THRESHOLD = 500

arduino     = serial.Serial('/dev/ttyACM0', 9600)
# capacitor   = deque([0 for x in range(CAP_CONST)])

pygame.mixer.pre_init(channels=2, buffer=1024)
pygame.mixer.init()

letters = ["C3", "D3", "E3", "F3", "G3", "A3", "B3"]
letters = letters[::-1]
piano_notes = [pygame.mixer.Sound("new_piano_notes/Piano"+letter+".wav") for letter in letters]

capacitors  = [deque([1000 for y in range(CAP_CONST)]) for x in range(NUMPINS)]    

count = 0
note  = 0

def piano(i):
    piano_notes[i].play()

def doInputNormalization(raw):
    capacitors[note].popleft()
    capacitors[note].append(raw)
    return sum(capacitors[note])/len(capacitors[note])

def doInput():
    arduinoInput = ""
    arduinoInput = arduino.readline()
    arduinoInput.strip()
    sensor = 0
    try:
        sensor = int(arduinoInput)
    except:
        sensor = 0
    #print(sensor)
    note = sensor/10000
    #print(note)
    return doInputNormalization(sensor - note*10000)

def doStep():
    piano(note)

def checkThreshold(reading):
    return reading > 700;

def controlStrat1():
    while True:
        sensor = doInput()
        #print(note)
        if checkThreshold(sensor):
            doStep()
            sensor2 = doInput()
            #print(sensor2)
            while checkThreshold(sensor2):
                sensor2 = doInput()
                #print(sensor2)

time.sleep(3)
controlStrat1()
