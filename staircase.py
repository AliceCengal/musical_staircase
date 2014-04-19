import fluidsynth
import serial
import time

arduino = serial.Serial('/dev/tty.usbmodem1411', 9600)

fs = fluidsynth.Synth()
fs.start()

sfid = fs.sfload("AJH_Piano.sf2")
fs.program_select(0, sfid, 0, 0)

# Range C3 - C5
noteLookup = [48, 50, 52, 53, 55, 57, 59, 60, 62, 64, 65, 67, 69, 71, 72]

while True:
  rawInput = arduino.readline()
  rawInput.strip()

  note = -1
  try:
    note = int(rawInput[1::])
  except:
    note = -1

  if (note >= 0 and rawInput[0] == "+" and note < len(noteLookup)):
   print "on " + rawInput[1:2]
   fs.noteon(0, noteLookup[note], 127)
  
  if (note >= 0 and rawInput[0] == "-" and note < len(noteLookup)):
   print "off " + rawInput[1:2]
   fs.noteoff(0, noteLookup[note])
