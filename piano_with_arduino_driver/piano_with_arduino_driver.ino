
int noteCount = 7;
int pinReading[7];
int pinOffset = 2;

void setup() {
  Serial.begin(9600);
  
  for (int i = 0; i < noteCount; ++i) {
    pinMode(i + pinOffset, INPUT);
  }
  
  Serial.println(micros());
  
  for (int i = 0; i < noteCount; ++i) {
    Serial.println(digitalRead(i + pinOffset));
  }
  
  Serial.println(micros());
}

void loop() {
 //Serial.println(digitalRead(2));
 //delay(50);
}

//void loop() {
//  for (int i = 0; i < noteCount; ++i) {
//    int reading = digitalRead(i + pinOffset);
    //if ((reading - pinReading[i]) < 0) {
    //  Serial.print("step on note: ");
    //  Serial.println(i);
    //}
//    Serial.print(i);
//    Serial.print("  ");
//    Serial.println(reading);
 //   pinReading[i] = reading;
 // }
//}

