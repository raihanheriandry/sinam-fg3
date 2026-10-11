#include <Servo.h>

Servo myServo;

const int soilPin = A0;
const int servoPin = 9;

int soilValue = 0;
int threshold = 500;

void setup() {
  Serial.begin(9600);

  myServo.attach(servoPin);
  myServo.write(0);

  Serial.println("Sistem Soil Moisture + Servo");
}

void loop() {
  soilValue = analogRead(soilPin);

  Serial.print("Soil Value: ");
  Serial.println(soilValue);

  if (soilValue > threshold) {
    Serial.println("Tanah KERING");
    myServo.write(90);
  } else {
    Serial.println("Tanah BASAH");
    myServo.write(0);
  }

  delay(1000);
}
