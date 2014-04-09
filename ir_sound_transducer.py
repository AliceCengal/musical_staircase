
import pygame
import serial
import time
from collections import deque

NUMPINS   = 6
CAP_CONST = 20
THRESHOLD = 500

arduino     = serial.Serial('/dev/ttyACM0', 9600)
capacitor   = deque([0 for x in range(CAP_CONST)])
piano_notes = []

capacitors  = [deque([0 for y in range(CAP_CONST)]) for x in range(NUMPINS)]    

count = 0
note  = 0

def doSoundMixerInit():
    pygame.mixer.pre_init(channels=6, buffer=1024)
    pygame.mixer.init()

def doNotesInit():
    letters = ["d", "e", "f", "g", "a", "b"]
    letters = letters[::-1]
    piano_notes = [pygame.mixer.Sound("piano-notes/"+letter+".wav") for letter in letters]

def piano(i):
    piano_notes[i].play()

def doInputNormalization(raw):
    capacitors[note].popleft()
    capacitor[note].append(raw)
    return sum(capacitor[note])/len(capacitor[note])

def doInput():
    arduinoInput = ""
    arduinoInput = arduino.readline()
    arduinoInput.strip()
    sensor = 0
    try:
        sensor = int(arduinoInput)
    except:
        sensor = 0
    note = sensor/10000
    return doInputNormalization(10000 - sensor)

def doStep():
    piano(note)

def checkThreshold(reading):
    return reading < 0.5;

def controlStrat1():
    while True:
        sensor = doInput()
        if checkThreshold(sensor):
            doStep()
            sensor2 = doInput()
            
            while checkThreshold(sensor2):
                sensor2 = doInput()

doSoundMixerInit()
doNotesInit()

time.sleep(3)
controlStrat1()
