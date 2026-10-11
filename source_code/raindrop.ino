#include <Servo.h>
Servo myServo;

const int rainPin = A0;
const int servoPin = 9;
const int threshold = 500;

int servoPosition = 0;

void setup() {
  Serial.begin(9600);
  myServo.attach(servoPin);
  myServo.write(servoPosition);
}


void loop() {
  int rainValue = analogRead(rainPin);

  Serial.print("Rain Value: ");
  Serial.println(rainValue);


  if (rainValue < threshold) {
    Serial.println("Hujan");


    while (rainValue < threshold && servoPosition < 180) {
      servoPosition++;
      myServo.write(servoPosition);


      delay(20);


      rainValue = analogRead(rainPin);
    }
  }
  else {
    Serial.println("Tidak Hujan");


    while (rainValue >= threshold && servoPosition > 0) {
      servoPosition--;
      myServo.write(servoPosition);


      delay(20);


      rainValue = analogRead(rainPin);
    }
  }


  delay(100);
}
