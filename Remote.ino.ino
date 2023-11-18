#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
int mode=1;         // 0 for auto , 1 for remote
int direc=1;      // 1 for fwd , 2 for back , 3 for left , 4 for right
String receivedString="";
const int trigPin_1 = 13;
const int echoPin_1 = 12 ;
const int trigPin_2 = 32;
const int echoPin_2 = 33;
const int trigPin_3 = 25;
const int echoPin_3 = 35;
const float threshold = 22;
const float threshold_diagonal=18;
const int irSensorPin1 = 2;
const int irSensorPin2 = 21;
const int inp1=27;
const int inp2=26;
const int inp3=18;
const int inp4=19;
const int en1=14;
const int en2=15;
int turnflag=0;

void goback(){
  Serial.println("BACKK");
  digitalWrite(inp1,HIGH);
  digitalWrite(inp2,LOW);
  digitalWrite(inp4,LOW);
  digitalWrite(inp3,HIGH);
  delay(500);
}
void goback_RR(){
  analogWrite(en1,255);
  analogWrite(en2,255);
  digitalWrite(inp1,HIGH);
  digitalWrite(inp2,LOW);
  digitalWrite(inp4,LOW);
  digitalWrite(inp3,HIGH);
  delay(1000);
}
void goback_r(){
  digitalWrite(inp1,HIGH);
  digitalWrite(inp2,LOW);
  digitalWrite(inp4,LOW);
  digitalWrite(inp3,HIGH);
  delay(500);
}

void gorev(){

  digitalWrite(inp1,LOW);
  digitalWrite(inp2,HIGH);
  digitalWrite(inp4,LOW);
  digitalWrite(inp3,HIGH);
  delay(1000);

}

void goleft(){
  Serial.println("LEFTT");
  digitalWrite(inp1,HIGH);
  digitalWrite(inp2,LOW);
  digitalWrite(inp4,HIGH);
  digitalWrite(inp3,LOW);
  delay(350);
}

void goleft_RR(){
  digitalWrite(inp1,HIGH);
  digitalWrite(inp2,LOW);
  digitalWrite(inp4,HIGH);
  digitalWrite(inp3,LOW);
  delay(350);
}

void goright_RR(){
  digitalWrite(inp1,LOW);
  digitalWrite(inp2,HIGH);
  digitalWrite(inp4,LOW);
  digitalWrite(inp3,HIGH);
  delay(300);
}

void goright(){
  Serial.println("RIGHTT");
  digitalWrite(inp1,LOW);
  digitalWrite(inp2,HIGH);
  digitalWrite(inp4,LOW);
  digitalWrite(inp3,HIGH);
  delay(390);
}

void gofwd(){
  Serial.println("FWDD");
  digitalWrite(inp1,LOW);
  digitalWrite(inp2,HIGH);
  digitalWrite(inp4,HIGH);
  digitalWrite(inp3,LOW);
  delay(15);
}

void gofwdsmall(){

  digitalWrite(inp1,LOW);
  digitalWrite(inp2,HIGH);
  digitalWrite(inp4,HIGH);
  digitalWrite(inp3,LOW);
  delay(100);
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
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop() {
    if (SerialBT.available()) {
    receivedString = SerialBT.readStringUntil('\n');
    
    if (receivedString.length() > 0) {
      // Process the received string
      Serial.println("Received: " + receivedString);
    }
  }
  if(receivedString=="auto")
  {
    mode=0;
  }else if(receivedString=="remote")
  {
    mode=1;
    direc=0;
  }else if(receivedString=="fwd")
  {
    direc=1;
  }else if(receivedString=="back")
  {
    direc=2;
  }else if(receivedString=="left")
  {
    direc=3;
  }else if(receivedString=="right")
  {
    direc=4;
  }else
  {
    Serial.println("No Match");
  }
  // Serial.println(mode);
  // Serial.print(direc);
  if(mode==1)
  {
    if(direc==1)
    {
      gofwd();
    }else if(direc==2)
    {
      goback();
    }else if(direc==3)
    {
      goleft();
    }else if(direc==4)
    {
      goright();
    }
  }
  else{

  analogWrite(en1,255);
  analogWrite(en2,255);
  // gofwd();
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
  // Serial.println(distance1);
  digitalWrite(trigPin_2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin_2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_2, LOW);

  duration = pulseIn(echoPin_2, HIGH);
  float distance2 = duration * 0.034 / 2;
  // Serial.println(distance2);
  // float distance2 = 15;

  digitalWrite(trigPin_3, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin_3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_3, LOW);

  duration = pulseIn(echoPin_3, HIGH);
  
  float distance3 = duration * 0.034 / 2;
  // Serial.println(distance3);// float distance3=15;

  if (irSensorState1 == HIGH || irSensorState2 == HIGH) {
    Serial.print(irSensorState1);
    Serial.println(irSensorState2);
    flag_ir = 1;
    Serial.println("IR alert!");
  }
  // flag_ir=0;
  flag_us=US_combined(distance1,distance2,distance3);
  // Serial.println(irSensorState1,irSensorState2,distance1,distance2,distance3);
  // Serial.print(distance1);
  // Serial.print(distance2);
  // Serial.println(distance3);
  if (flag_ir == 1 || flag_us == 1) {
    // Serial.println("Topale alert!");
    // Serial.println("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");

    //Step 1 simon go back
    Serial.print("goback");
    // goback();

    //Step 2 check if IR alert
    //If ir alert simon turn back

    if(flag_ir == 1){
      Serial.println("gorev");
      goback_RR();
      if(turnflag==0){
        goleft_RR();
        turnflag=1;
      }
      else{
        goright_RR();
        turnflag=0;
      }
      // goleft_RR();
    }

    //else if US_1 has an alert , check dist2 and dist 3
    // turn to higher dist side
    //small move fwd
    else{
          goback();
      if(distance1<threshold){

          if(distance2>distance3){
            Serial.println("Goleft");
            goleft();
          }
          else{
            Serial.println("Goright");
            goright();
          }
          Serial.println("Gofwdsmall");
          gofwdsmall();
      }
      else if(distance2<threshold_diagonal){
        Serial.println("goleft");
        // goback_r();
        goleft();
      }
      else if(distance3<threshold_diagonal){
        Serial.println("goright");
        // goback_r();
        goright();
      }
}
     }
     else{
      // Serial.println("GOfwd");

       gofwd();
      }
}
  delay(10);
}


int US_combined(int distance1 , int distance2 , int distance3)
{
  int flag_ret=0;
  
  if (distance1 < threshold) {
    flag_ret = 1;
    // Serial.println(distance1);
    // Serial.println("US_1 Alert!");
  }
  if (distance2 < threshold_diagonal) {
    flag_ret = 1;
    // Serial.println("US_2 Alert!");
  }

  if (distance3 < threshold_diagonal) {
    flag_ret = 1;
    // Serial.println("US_3 Alert!");
  }

  return flag_ret;

}