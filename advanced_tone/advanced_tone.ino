
int noteCount = 1;
int capacitorCount = 10;
int pinReading[1];      // [noteCount]
int prevReading[1][10]; // [noteCount] capacitorCount
int isHigh[1];          // [noteCount]
int pinOffset = 3;      // We use pin 2 to drive the emmiter, so start from pin 3

float        THRESHOLD     = 0.4;
int          EMITTER_PIN   = 2;
unsigned int EMITTER_FREQ  = 38000;
int          INITIAL_DELAY = 300;

long liveInterval = 1600;              // microseconds
long deadInterval = liveInterval * 24; // microseconds

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < noteCount; ++i) {
    pinMode(i + pinOffset     , INPUT);
    digitalWrite(i + pinOffset, HIGH);
  }
  
}

void loop11() {
  Serial.println(digitalRead(3));
}

void loop10() {
    
    for (int i = 0; i < noteCount; ++i) {
      Serial.println(digitalRead(i + pinOffset));
    }
    
    Serial.println();
}

void loop23() {
  tone(2, 38000);
  int startTime = micros();
  delayMicroseconds(300);
  
  // read pins
  for (int i = 0; i < noteCount; ++i) {
    Serial.println(digitalRead(i + pinOffset));
  }
  
  Serial.println();
  while ((micros() - startTime) < liveInterval) {}
  noTone(2);
  delay(deadInterval / 1000);
  delayMicroseconds(deadInterval % 1000);
}

void loop345() {
  tone(2, 38000);
  int startTime = micros();
  delayMicroseconds(300);
  
  // read pins
  for (int i = 0; i < noteCount; ++i) {
    int reading = digitalRead(i + pinOffset);
    if (reading > pinReading[i]) {
      Serial.println(i);
    }
    pinReading[i] = reading;
    Serial.println(reading);
  }
  
//  Serial.println();
  while ((micros() - startTime) < 800) {}
  noTone(2);
  delay(deadInterval / 1000);
  delayMicroseconds(deadInterval % 1000);
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
    
    float sum = 0.0;
    
    for (int j = 0; j < capacitorCount; ++j) {
      int tmp = prevReading[i][j];
      prevReading[i][j] = pinReading[i];
      sum = sum + pinReading[i];
      pinReading[i] = tmp;
    }
    
    float average = sum / (float)capacitorCount;
    
    if ((average > THRESHOLD) && (isHigh[i] == 0)) {
      isHigh[i] = 1;
      //Serial.print(i);
      //Serial.print(" ");
      //Serial.println(average);
    }
    if (average <= THRESHOLD) {
      isHigh[i] = 0;
    }
    Serial.println(average);
  }

  while ((micros() - startTime) < deadInterval) {}
}

