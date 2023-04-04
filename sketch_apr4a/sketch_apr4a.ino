#include <ESP32Servo.h>

Servo ESC;     // create servo object to control the ESC
int potValue;  // value from the analog pin
const int potPin = 26;
unsigned long currTime;
unsigned long lastTime;
const int intervalTime = 50;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Hello Stefano Riray");
  // Attach the ESC on pin 14
  ESC.attach(14,1000,2000); // (pin, min pulse width, max pulse width in microseconds) 
  lastTime = millis();
}

void loop() {
  potValue = analogRead(potPin);   // reads the value of the potentiometer (value between 0 and 1023)
  potValue = map(potValue, 4095, 0, 0, 180);   // scale it to use it with the servo library (value between 0 and 180)
  if (potValue > 180) {
    potValue = 180;
  } else if (potValue < 0) {
    potValue = 0;
  }
  ESC.write(potValue);    // Send the signal to the ESC
  delay(20);
  currTime = millis();
  if (currTime - lastTime > intervalTime) {
    Serial.println(potValue);
    lastTime = millis();
  }
}
