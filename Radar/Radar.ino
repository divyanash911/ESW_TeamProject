#include <ESP32Servo.h>

Servo myServo; // Create a servo object
int pos = 15;  // Current servo position
int servoDirection = 1; // 1 for clockwise, -1 for counterclockwise

const int trigPin = 5;
const int echoPin = 18;
const int servoPin = 15; // Define the GPIO pin connected to the servo

long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(115200);
  myServo.attach(servoPin); // Attach the servo to the specified pin
}

void loop() {
  // Read the distance asynchronously without blocking
  readDistanceAsync();
  
  myServo.write(pos);
  delay(10); // Adjust this delay for the desired speed of rotation

  // Increment or decrement the servo position based on direction
  pos += servoDirection;

  Serial.print(pos);
  Serial.print(",");

  // Check if the servo has reached the limit
  if (pos >= 165 || pos <= 15) {
    // Change direction when the servo reaches the limit
    servoDirection *= -1;
  }
}

void readDistanceAsync() {
  static unsigned long previousMillis = 0;
  const long interval = 100; // Adjust the interval as needed

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Trigger the ultrasonic sensor
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Read the duration of the pulse
    duration = pulseIn(echoPin, HIGH);

    // Calculate the distance
    distance = duration * 0.034 / 2;

    // Print the distance
  }
    Serial.print(distance);
    Serial.print(".");
}
