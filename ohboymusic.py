
import pygame
import serial
import time

numpins = 6
ser = serial.Serial('/dev/ttyACM0', 9600)

// Sound Mixer init
pygame.mixer.pre_init(channels=6, buffer=1024)
pygame.mixer.init()

# 1 2 3   5 6    8
# g a b c d e f# g
# g a b   d e    g
# c d e f g a b  c
# 8 6 5 3 2 1
letters = ["d", "e", "f", "g", "a", "b"]
letters = letters[::-1]
piano_notes = [pygame.mixer.Sound("piano-notes/"+letter+".wav") for letter in letters]

def piano(i):
    piano_notes[i].play()

count = 0
note  = 0

time.sleep(3)

def getInput():
    arduinoInput = ""
    arduinoInput = ser.readline()
    arduinoInput.strip()
    try:
        sensor = int(arduinoInput)
        return sensor
    except:
        return 0

def doStep():
    count += 1
    count %= 6
    piano(count)

def controlStrat1():
    while True:
        sensor = getInput()
        if sensor < 1000:
            doStep()
            sensor2 = getInput()
            
            while sensor2 < 1000:
                sensor2 = getInput()

controlStrat1()



