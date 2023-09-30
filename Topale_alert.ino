const int trigPin = 13;
const int echoPin = 12;
const float threshold = 10;
const int irSensorPin1 = 2;
const int irSensorPin2 = 21;

void setup() {
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(irSensorPin1, INPUT);
  pinMode(irSensorPin2, INPUT);
}

void loop() {
  int flag = 0;

  long duration;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  float distance1 = duration * 0.034 / 2;

  int irSensorState1 = digitalRead(irSensorPin1);
  int irSensorState2 = digitalRead(irSensorPin2);

  if (irSensorState1 == HIGH || irSensorState2 == HIGH) {
    flag = 1;
    Serial.println("IR alert!");
  }

  if (distance1 < threshold) {
    flag = 1;
    Serial.println("US Alert!");
  }

  if (flag == 1) {
    Serial.println("Topale alert!");
    Serial.println("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
  }

  delay(100);
}
