
int noteCount = 7;
long pinTag[7];

void setup() {
  Serial.begin(9600);
  
  // Set which pin to tone
  //tone(2, 38000);
  
  //pinMode(2,INPUT);
  pinMode(3,INPUT);
  pinMode(4,INPUT);
  pinMode(5,INPUT);
  pinMode(6,INPUT);
  pinMode(7,INPUT);
  pinMode(8,INPUT);
  
  //for (int i = 0; i < noteCount; ++i) {
  //  pinTag[i] = i*10000;
  //}
}

void loop() {
  
  //for (int i = 2; i < (noteCount+2); ++i) {
  //  Serial.println(pinTag[i-2] + digitalRead(i));
  //}

  //Serial.println(pinTag[0] + analogRead(0));
  //delay(50);
  //Serial.println(analogRead(0));
}

