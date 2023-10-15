#include <WiFi.h>
#include <HTTPServer.h>

const char* ssid = "your-ssid";
const char* password = "your-password";
const int serverPort = 80;

const int inp1=27
const int inp2=26
const int inp3=18
const int inp4=19;
const int en1=14;
const int en2=15;

HTTPServer server(serverPort);

void setup() {
    // Connect to Wi-Fi
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
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
    }

    // Start the HTTP server
    server.on("/", HTTP_POST, handleCommand);
    server.begin();
}

void loop() {
    analogWrite(en1,255);
    analogWrite(en2,255);
    server.handleClient();
    delay(10);
}

void handleCommand(HTTPServerRequest request) {
    if (request.url() == "/your-container") {
        if (request.hasArg("command")) {
            String command = request.arg("command");
            executeCommand(command);
            request.send(200, "text/plain", "Command executed: " + command);
        } else {
            request.send(400, "text/plain", "Bad Request");
        }
    } else {
        request.send(404, "text/plain", "Not Found");
    }
}

void executeCommand(String command) {
    // Implement your car control code here based on the received command
    if(command=="forward")
    {
      gofwd();
    }else if(command == "backward")
    {
      goback();
    }else if(command == "right")
    {
      goright();
    }else if(command == "left")
    {
      goleft();
    }
}


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

