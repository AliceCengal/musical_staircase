
int noteCount = 3;
int pinReading[3];
int pinOffset = 3;

void setup() {
  Serial.begin(9600);
  
  for (int i = 0; i < noteCount; ++i) {
    pinMode(i + pinOffset, INPUT);
  }
  
}

void loop() {
  
  tone(2, 38000);
  int startTime = micros();
  delayMicroseconds(300);
  
  // read pins
  //for (int i = 0; i < noteCount; ++i) {
    Serial.println(digitalRead(2));
  //}
  
  Serial.println();
  while ((micros() - startTime) < 800) {}
  noTone(2);
  delay(999);
  delayMicroseconds(200);
}
