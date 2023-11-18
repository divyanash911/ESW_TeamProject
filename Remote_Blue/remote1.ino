// Include necessary libraries
#include <BluetoothSerial.h>

// Define trigger and echo pins
const int trigPin_1 = 13;
const int echoPin_1 = 12;
const int trigPin_2 = 14;
const int echoPin_2 = 27;
const int trigPin_3 = 26;
const int echoPin_3 = 25;
const float threshold = 10;
const int irSensorPin1 = 15;
const int irSensorPin2 = 2;
const int inp1 = 27;
const int inp2 = 26;
const int inp3 = 18;
const int inp4 = 19;
const int en1 = 14;
const int en2 = 15;

BluetoothSerial SerialBT;

void goback() {
  Serial.println("Keep on going back");
  digitalWrite(inp1, LOW);
  digitalWrite(inp2, HIGH);
  digitalWrite(inp3, LOW);
  digitalWrite(inp4, HIGH);
  delay(500);
}

void gorev() {
  digitalWrite(inp1, HIGH);
  digitalWrite(inp2, LOW);
  digitalWrite(inp3, LOW);
  digitalWrite(inp4, HIGH);
  delay(2500);
}

void goleft() {
  Serial.println("Keep on going left");
  digitalWrite(inp1, LOW);
  digitalWrite(inp2, HIGH);
  digitalWrite(inp3, HIGH);
  digitalWrite(inp4, LOW);
  delay(1000);
}

void goright() {
  Serial.println("Keep on going right");
  digitalWrite(inp1, HIGH);
  digitalWrite(inp2, LOW);
  digitalWrite(inp3, LOW);
  digitalWrite(inp4, HIGH);
  delay(1000);
}

void gofwd() {
  Serial.println("Keep on going forward");
  digitalWrite(inp1, HIGH);
  digitalWrite(inp2, LOW);
  digitalWrite(inp3, HIGH);
  digitalWrite(inp4, LOW);
  delay(1000);
}

void gofwdsmall() {
  digitalWrite(inp1, HIGH);
  digitalWrite(inp2, LOW);
  digitalWrite(inp3, HIGH);
  digitalWrite(inp4, LOW);
  delay(500);
}

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32 Car");  // Bluetooth device name

  pinMode(trigPin_1, OUTPUT);
  pinMode(echoPin_1, INPUT);
  pinMode(trigPin_2, OUTPUT);
  pinMode(echoPin_2, INPUT);
  pinMode(trigPin_3, OUTPUT);
  pinMode(echoPin_3, INPUT);
  pinMode(irSensorPin1, INPUT);
  pinMode(irSensorPin2, INPUT);
  pinMode(inp1, OUTPUT);
  pinMode(inp2, OUTPUT);
  pinMode(inp3, OUTPUT);
  pinMode(inp4, OUTPUT);
  pinMode(en1, OUTPUT);
  pinMode(en2, OUTPUT);
}

void loop() {
  static bool remoteControlMode = false;  // Flag to track the mode

  // Check for command from the Serial Bluetooth Terminal on the phone
  if (SerialBT.available()) {
    Serial.write(SerialBT.read());
    String command = SerialBT.readString();

    if (command == "remote") {
      remoteControlMode = true;
      // SerialBT.println("Remote Control Mode on. Insert the following number values to move the object:\n0 for Forward, 1 for Backward, 2 for Left, 3 for Right\n");
      while (remoteControlMode) {
        if (SerialBT.available()) {
          String controlCommand = SerialBT.readString();

          // Check if the command is a valid integer
          while (SerialBT.read() == 'fwd') {
            gofwd();
          } 
          while (SerialBT.read() == 'back') {
            goback();

          } 
          while (SerialBT.read() == 'right') {
            goright();

          } 
          while (SerialBT.read() == 'left') {
            goleft();

          } 
          while (SerialBT.read() == 'autonomous') {
            break;
          }
          // Perform corresponding actions for remote control car
          //   switch (controlCommand) {
          //     case 0:
          //       // Move Forward
          //       gofwd();
          //       break;
          //     case 1:
          //       // Move Backward
          //       goback();
          //       break;
          //     case 2:
          //       // Move Left
          //       goleft();
          //       break;
          //     case 3:
          //       // Move Right
          //       goright();
          //       break;
          //     default:
          //       SerialBT.println("Invalid command");
          //       break;
          //   }
          // } else {
          //   SerialBT.println("Invalid command format");
          // }
        }

        // Add any other necessary code or delay here
        delay(100);
      }
    } 
    else if (command == "autonomous") {
      remoteControlMode = false;
      SerialBT.println("Remote Control Mode stopped, switching to Autonomous Mode");
    } 
    else if (command == "remote") {
      remoteControlMode = true;
      SerialBT.println("Remote Control Mode started, use the bluetooth app for giving directions");
    }
  }
}
