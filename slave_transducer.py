import pygame
import serial
import time

NUMPINS = 6
arduino = serial.Serial('/dev/ttyACM0', 9600)

pygame.mixer.pre_init(channels=2, buffer=1024)
pygame.mixer.init()

letters = ["C3", "D3", "E3", "F3", "G3", "A3", "B3"]
letters = letters[::-1]
piano_notes = [pygame.mixer.Sound("new_piano_notes/Piano"+letter+".wav") for letter in letters]

while True:
  rawInput = arduino.readline()
  rawInput.strip()
  note = -1
  try:
    note = int(rawInput)
  except:
    note = -1
  
  if (note != -1 and note < 6):
    piano_notes[note].play()
