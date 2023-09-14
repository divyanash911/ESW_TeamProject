#include <Servo.h>

Servo servo;
const int trigPin = 9;  
const int echoPin = 10; 

void setup() {
  servo.attach(8); 
  servo.write(90); 
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  int distance;
  for (int angle = 0; angle <= 180; angle += 1) {
    servo.write(angle);
    delay(15); 
    distance = getDistance();
    if (distance < 30 && distance > 0) {
      Serial.print("Obstacle detected at ");
      Serial.print(angle);
      Serial.print(" degrees, Distance: ");
      Serial.print(distance);
      Serial.println(" cm");
    }
  }
  for (int angle = 180; angle >= 0; angle -= 1) {
    servo.write(angle);
    delay(15);
    distance = getDistance();
    if (distance < 30 && distance > 0) {
      Serial.print("Obstacle detected at ");
      Serial.print(angle);
      Serial.print(" degrees, Distance: ");
      Serial.print(distance);
      Serial.println(" cm");
    }
  }
}

int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  return pulseIn(echoPin, HIGH) / 58.0; 
}
