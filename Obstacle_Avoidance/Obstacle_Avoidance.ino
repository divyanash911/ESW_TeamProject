const int trigPin_1 = 13;
const int echoPin_1 = 12;
const int trigPin_2 = 14;
const int echoPin_2 = 27;
const int trigPin_3 = 26;
const int echoPin_3 = 25;
const float threshold = 10;
const int irSensorPin1 = 2;
const int irSensorPin2 = 21;


void setup() {
  Serial.begin(115200);
  pinMode(trigPin_1, OUTPUT);
  pinMode(echoPin_1, INPUT);
  pinMode(trigPin_2, OUTPUT);
  pinMode(echoPin_2, INPUT);
  pinMode(trigPin_3, OUTPUT);
  pinMode(echoPin_3, INPUT);
  pinMode(irSensorPin1, INPUT);
  pinMode(irSensorPin2, INPUT);
}

void loop() {
  int flag_ir = 0;
  int flag_us = 0;

  int irSensorState1 = digitalRead(irSensorPin1);
  int irSensorState2 = digitalRead(irSensorPin2);

  if (irSensorState1 == HIGH || irSensorState2 == HIGH) {
    flag_ir = 1;
    Serial.println("IR alert!");
  }

  // if (distance1 < threshold) {
  //   flag_us = 1;
  //   Serial.println("US Alert!");
  // }
  flag_us=US_combined();

  if (flag_ir == 1 || flag_us == 1) {
    Serial.println("Topale alert!");
    Serial.println("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
  }

  delay(100);
}


int US_combined()
{
  int flag_ret=0;
  long duration;
  digitalWrite(trigPin_1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin_1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_1, LOW);

  duration = pulseIn(echoPin_1, HIGH);
  float distance1 = duration * 0.034 / 2;
  if (distance1 < threshold) {
    flag_ret = 1;
    Serial.println("US_1 Alert!");
  }


  digitalWrite(trigPin_2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin_2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_2, LOW);

  duration = pulseIn(echoPin_2, HIGH);
  float distance2 = duration * 0.034 / 2;
  if (distance2 < threshold) {
    flag_ret = 1;
    Serial.println("US_2 Alert!");
  }

  digitalWrite(trigPin_3, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin_3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_3, LOW);

  duration = pulseIn(echoPin_3, HIGH);
  float distance3 = duration * 0.034 / 2;
  if (distance3 < threshold) {
    flag_ret = 1;
    Serial.println("US_3 Alert!");
  }

  return flag_ret;

}
