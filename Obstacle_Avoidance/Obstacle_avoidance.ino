const int trigPin_1 = 13;
const int echoPin_1 = 12;
const int trigPin_2 = 14;
const int echoPin_2 = 27;
const int trigPin_3 = 26;
const int echoPin_3 = 25;
const float threshold = 10;
const int irSensorPin1 = 2;
const int irSensorPin2 = 21;
const int inp1=27
const int inp2=26
const int inp3=18
const int inp4=19;
const int en1=14;
const int en2=15;

void goback(){

  digitalWrite(inp1,LOW);
  digitalWrite(inp2,HIGH);
  digitalWrite(inp3,LOW);
  digitalWrite(inp4,HIGH);
  delay(500);
}

void gorev(){

  digitalWrite(inp1,HIGH);
  digitalWrite(inp2,LOW);
  digitalWrite(inp3,LOW);
  digitalWrite(inp4,HIGH);
  delay(2500);

}

void goleft(){

  digitalWrite(inp1,LOW);
  digitalWrite(inp2,HIGH);
  digitalWrite(inp3,HIGH);
  digitalWrite(inp4,LOW);
  delay(1000);
}

void goright(){

  digitalWrite(inp1,HIGH);
  digitalWrite(inp2,LOW);
  digitalWrite(inp3,LOW);
  digitalWrite(inp4,HIGH);
  delay(1000);

}

void gofwd(){

  digitalWrite(inp1,HIGH);
  digitalWrite(inp2,LOW);
  digitalWrite(inp3,HIGH
  digitalWrite(inp4,LOW);
  delay(1000);

}

void gofwdsmall(){

  digitalWrite(inp1,HIGH);
  digitalWrite(inp2,LOW);
  digitalWrite(inp3,HIGH);
  digitalWrite(inp4,LOW);
  delay(500);

}

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
  pinMode(inp1,OUTPUT);
  pinMode(inp2,OUTPUT);
  pinMode(inp3,OUTPUT);
  pinMode(inp4,OUTPUT);
  pinMode(en1,OUTPUT);
  pinMode(en2,OUTPUT);
}

void loop() {
  analogWrite(en1,255);
  analogWrite(en2,255);
  
  int flag_ir = 0;
  int flag_us = 0;

  int irSensorState1 = digitalRead(irSensorPin1);
  int irSensorState2 = digitalRead(irSensorPin2);

  long duration;
  digitalWrite(trigPin_1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin_1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_1, LOW);

  duration = pulseIn(echoPin_1, HIGH);
  float distance1 = duration * 0.034 / 2;
  digitalWrite(trigPin_2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin_2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_2, LOW);

  duration = pulseIn(echoPin_2, HIGH);
  float distance2 = duration * 0.034 / 2;

  digitalWrite(trigPin_3, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin_3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_3, LOW);

  duration = pulseIn(echoPin_3, HIGH);
  float distance3 = duration * 0.034 / 2;

  if (irSensorState1 == HIGH || irSensorState2 == HIGH) {
    flag_ir = 1;
    Serial.println("IR alert!");
  }
  
  flag_us=US_combined();

  if (flag_ir == 1 || flag_us == 1) {
    Serial.println("Topale alert!");
    Serial.println("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");

    //Step 1 simon go back

    goback();

    //Step 2 check if IR alert
    //If ir alert simon turn back

    if(flag_ir == 1){
      gorev();
    }

    //else if US_1 has an alert , check dist2 and dist 3
    // turn to higher dist side
    //small move fwd
    else{

      if(distance1<threshold){

          if(distance2>distance3){
            goleft();
          }
          else{
            goright();
          }

          gofwdsmall();
      }
}
     }
     else{

      gofwd();

     }

  delay(100);
}


int US_combined(int distance1 , int distance2 , int distance3)
{
  int flag_ret=0;
  
  if (distance1 < threshold) {
    flag_ret = 1;
    Serial.println("US_1 Alert!");
  }
  if (distance2 < threshold) {
    flag_ret = 1;
    Serial.println("US_2 Alert!");
  }

  if (distance3 < threshold) {
    flag_ret = 1;
    Serial.println("US_3 Alert!");
  }

  return flag_ret;

}