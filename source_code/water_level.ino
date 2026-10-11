#include <Servo.h>


Servo myServo;
const int threshold = 500;
const int pin_servo = 3;
const int pin_air = A0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myServo.attach(pin_servo);


  myServo.write(180);
  delay(1000);
}


void loop() {
  // put your main code here, to run repeatedly:
  int sensor_value = analogRead(pin_air);
  Serial.println("Nilai Sensor Hujan: ");
  Serial.println(sensor_value);


  if(sensor_value < threshold){
    Serial.println("Air tidak mecapai threshold");
    myServo.write(180);
    }
  else{
    Serial.println("Air Mencapai threshold");
    myServo.write(0);
  }
  delay(1000);
}
