int noteCount = 15;
boolean pinReading[15];      // [noteCount]
int pinScore[15];
boolean isOn[15];
int pinOffset = 3;      // We use pin 2 to drive the emmiter, so start from pin 3

int RISE_RATE = 3;
int DECAY_RATE = -1;
int HIGH_THRESHOLD = 5;
int LOW_THRESHOLD = 0;

int          EMITTER_PIN   = 2;
unsigned int EMITTER_FREQ  = 38000;
int          INITIAL_DELAY = 300;

long liveInterval = 1000; // microseconds
long deadInterval = 1000; // microseconds

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < noteCount; ++i) {
    pinMode(i + pinOffset     , INPUT);
    digitalWrite(i + pinOffset, HIGH);
  }
  
}

// With capacitor
void loop() {
  tone(EMITTER_PIN, EMITTER_FREQ);
  long startTime = micros();
  delayMicroseconds(INITIAL_DELAY);
  
  for (int i = 0; i < noteCount; ++i) {
    pinReading[i] = digitalRead(i + pinOffset);
  }
  
  while ((micros() - startTime) < liveInterval) {}
  noTone(EMITTER_PIN);
  
  startTime = micros();
  
  // insert new values
  for (int i = 0; i < noteCount; ++i) {
    int me = pinReading[i];
    
    if (me == 1) {
      pinScore[i] += RISE_RATE;
    } else {
      pinScore[i] += DECAY_RATE;
    }
    
    if (pinScore[i] > HIGH_THRESHOLD) {
      pinScore[i] = HIGH_THRESHOLD;
    } else if (pinScore[i] < LOW_THRESHOLD) {
      pinScore[i] = LOW_THRESHOLD;
    }
      
    if (isOn[i] == false && pinScore[i] == HIGH_THRESHOLD) {
      Serial.print("+");
      Serial.println(i);
      isOn[i] = true;
    } else if (isOn[i] == true && pinScore[i] == LOW_THRESHOLD) {
      Serial.print("-");
      Serial.println(i);
      isOn[i] = false;
    }
  }

  while ((micros() - startTime) < deadInterval) {}
}
