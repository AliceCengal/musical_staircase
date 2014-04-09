
int NOTE_COUNT = 5;
int pinTag[NOTE_COUNT];

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < NOTE_COUNT; ++i) {
    pinTag[i] = i*10000;
  }
}

void loop() {
  
  for (int i = 0; i < NOTE_COUNT; ++i) {
    Serial.println(pinTag[i] + analogRead(i));
  }
//  x=analogRead(0);
//  Serial.println(x);
}

