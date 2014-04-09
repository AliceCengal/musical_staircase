
int noteCount = 5;
unsigned int pinTag[5];

void setup() {
  pinMode(2, INPUT);
  Serial.begin(9600);
  for (int i = 0; i < noteCount; ++i) {
    pinTag[i] = i*10000;
  }
}

void loop() {
  
  for (int i = 0; i < noteCount; ++i) {
//    Serial.println(pinTag[i] + analogRead(i));
    if (i < 3) {
      Serial.println(analogRead(2));
    } else {
      Serial.println(digitalRead(2));      
    }  
    delay(50);
  }
//  x=analogRead(0);
//  Serial.println(x);
}

