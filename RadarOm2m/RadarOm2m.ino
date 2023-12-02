#include <ESP32Servo.h>
#include <WiFi.h>
#include <HTTPClient.h>
Servo myServo; // Create a servo object
int pos = 15;  // Current servo position
int servoDirection = 1; // 1 for clockwise, -1 for counterclockwise
HTTPClient http;
const int trigPin = 5;
const int echoPin = 18;
const int servoPin = 15; // Define the GPIO pin connected to the servo
const char* ssid = "Divyansh";
const char* password = "dpkahotspot";
#define CSE_IP "192.168.154.90"
#define CSE_PORT 5089
#define OM2M_ORGIN "admin:admin"
#define OM2M_AE "RADAR"
#define OM2M_DATA_CONT "Node-1"
#define OM2M_MN "/~/in-cse/in-name/"
long long int count=0;
long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  myServo.attach(servoPin); // Attach the servo to the specified pin

  WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }

    Serial.println("Connected to WiFi");


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

  // Send data to OM2M
    // HTTPClient http;
    // http.begin(String(om2mServer));
    // http.addHeader("Content-Type", "application/json;ty=4");
    // http.addHeader("X-M2M-Origin", "admin:admin");
    // http.addHeader("Content-Length", "100");
    // String dataPayload = "{\"m2m:cin\":{\"con\":\"" + String(pos) + "\"}}";


    // int httpResponseCode = http.POST(dataPayload);
    // if (httpResponseCode > 0) {
    //     Serial.println("Data sent successfully to OM2M");
    // } else {
    //     Serial.println(http.errorToString(httpResponseCode).c_str());
    // }

    // http.end();

    om2mPublish(distance,pos);

    


  // Check if the servo has reached the limit
  if (pos >= 165 || pos <= 15) {
    // Change direction when the servo reaches the limit
    servoDirection *= -1;
  }
}

void om2mPublish(int fillpercent, int aqivalue) {
  unsigned long int epochTime = count++;
  String data = "[" + String(epochTime) + ", " + String(fillpercent) + " , " + String(aqivalue) + "]";

  String server = "http://" + String() + CSE_IP + ":" + String() + CSE_PORT + String() + OM2M_MN;

  // Serial.println(data);
  http.begin(server + String() + OM2M_AE + "/" + OM2M_DATA_CONT + "/");

  http.addHeader("X-M2M-Origin", OM2M_ORGIN);
  http.addHeader("Content-Type", "application/json;ty=4");
  http.addHeader("Content-Length", "100");

  String label = "Bin-1";

  String req_data = String() + "{\"m2m:cin\": {"
                    + "\"con\": \"" + data + "\","
                    + "\"rn\": \"" + "cin_" + String(epochTime) + "\","
                    + "\"lbl\": \"" + label + "\","
                    + "\"cnf\": \"text\""
                    + "}}";
  int code = http.POST(req_data);
  // Serial.println(http.errorToString(code).c_str());
  http.end();
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