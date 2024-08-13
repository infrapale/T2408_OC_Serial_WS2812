/*
  Serial Test for HW Testing

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/SerialPassthrough
*/
#define PIN_RGB 13

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);
  pinMode(PIN_RGB, OUTPUT);
}

void loop() {

  while(true)
  {
    digitalWrite(PIN_RGB,HIGH);
    delay(1);
    digitalWrite(PIN_RGB,LOW);
    delay(1);

  }
  if (Serial.available()) {        // If anything comes in Serial (USB),
    Serial1.write(Serial.read());  // read it and send it out Serial1 (pins 0 & 1)
  }

  if (Serial1.available()) {       // If anything comes in Serial1 (pins 0 & 1)
    char c = Serial1.read();  // read it and send it out Serial (USB)
    Serial1.write(c);
    Serial.write(c);
  }
}
