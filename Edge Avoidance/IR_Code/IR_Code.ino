const int irSensorPin1 = 2;
const int irSensorPin2 = 3;


void setup() {
  Serial.begin(115200);
  pinMode(irSensorPin1, INPUT);
  pinMode(irSensorPin2, INPUT);

}

void loop() {
  int irSensorState1 = digitalRead(irSensorPin1);
  int irSensorState2 = digitalRead(irSensorPin2);
 
  if (irSensorState1  == HIGH || irSensorState2 == HIGH) {
    Serial.println("Object detected!");
  } else {
    Serial.println("No object detected.");
  }
  delay(1000);
}