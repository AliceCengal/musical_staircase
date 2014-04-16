
import pygame
import serial
import time
from collections import deque

class Transducer:
  
  def __init__(self):
    self.numPin = 8
    self.capacitorConst = 20
    self.threshold = 500
    self.arduino = serial.Serial('/dev/ttyACM0', 9600)
    
    pygame.mixer.pre_init(channels=6, buffer=1024)
    pygame.mixer.init()
    
    self.letters = ["C3", "D3", "E3", "F3", "G3", "A3", "B3"]
    self.letters = self.letters[::-1]
    self.piano_notes = [pygame.mixer.Sound("new_piano_notes/Piano"+letter+".wav") for letter in self.letters]
    
    #self.capacitors  = [deque([0 for y in range(self.capacitorConst)]) for x in range(self.numPin)]
    
    self.count = 0
    self.note = 0
    self.prev = 0
    self.isPlaying = -1
    
    self.isHigh = [False for x in range(self.numPin)]
    
  
  def piano(self, i):
    self.piano_notes[i].play()
  
  def doInputNormalization(self, raw):
    #self.capacitors[self.note].popleft()
    #self.capacitors[self.note].append(raw)
    return raw #sum(self.capacitors[self.note])/len(self.capacitors[self.note])
  
  def doInput(self):
    arduinoInput = ""
    arduinoInput = self.arduino.readline()
    arduinoInput.strip()
    sensor = 0
    try:
        sensor = int(arduinoInput)
    except:
        sensor = self.prev
    #print(sensor)
    self.note = sensor / 10000
    #print(self.note)
    self.prev = sensor % 10000 # self.doInputNormalization(sensor % 10000)
    #print(self.prev)
    return self.prev
  
  def doStep(self):
    #print(self.note)
    if self.note != self.isPlaying:
      self.isPlaying = self.note
      self.piano(self.note)
  
  def doStep(self, note):
    print(note)
    self.piano(note)
  
  def checkThreshold(self, reading):
    return reading > self.threshold
  
  def controlStrat1(self):
    while True:
      sensor = self.doInput()
      
      if self.checkThreshold(sensor):
        
        self.doStep()
        
        sensor2 = self.doInput()
        
        while self.checkThreshold(sensor2):
          sensor2 = self.doInput()
          

  def controlStrat2(self):
    while True:
      sensor = self.doInput()
      
      if self.checkThreshold(sensor):
        if not self.isHigh[self.note]:
          self.isHigh[self.note] = True
          self.doStep(self.note)
      else:
        self.isHigh[self.note] = False
  

Transducer().controlStrat2()












