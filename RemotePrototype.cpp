#include <WiFi.h>
#include <ThingSpeak.h>

#include <WebServer.h>
// WiFi credentials with mobile hotspot set at 2.4GHz bandwidth
const char* ssid = "Aanvik's Hotspot";
const char* password = "a4dzqvhh";
// ThingSpeak API key and channel details
const char* apiKey = "7BNCG3QLALBXHFUR";
const unsigned long channelID = 2288264;
const char* readkey = "J3H4ZFHL66U6RU9E";

WiFiClient client;
WebServer server(80);
void setup() {
  //15 is a PWM pin in Servo
  //initialise server client to send HTTP requests
  Serial.begin(115200);
  while (WiFi.status() != WL_CONNECTED) {
    // connectivity status
      delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  //infinite loop to check wifi
  Serial.println("Connected to WiFi");
  Serial.print("Local IP: ");
  Serial.println(WiFi.localIP());      //fetch IP address where the HTML page will be hosted
  ThingSpeak.begin(client);            // Initialize ThingSpeak communication
  server.on("/", HTTP_GET, SendHTML);  // Define the web page
  server.begin();
}
void loop() {
  server.handleClient();  // Handle incoming web server requests
  // Read value from ThingSpeak channel field 6
  float value = ThingSpeak.readFloatField(channelID, 6, readkey);
  float value1 = ThingSpeak.readFloatField(channelID, 5, readkey);
  float value2 = ThingSpeak.readFloatField(channelID, 4, readkey);
  Serial.println(value);
  // Control the servo based on the received value
  if (value == 1.0) {
    Serial.println("Remote Control Activated...");
    if (value1 == 1.0) {
      Serial.println("Move Forward");
    }
    if (value2 == 1.0) {
      Serial.println("Move Backward");
    }
  } else {
    Serial.println("Remote Control Mode Disabled, Autonomous Mode Continued...");
  }
  delay(1000);  // Wait for a moment before checking again
}
// Function to send HTML content to the client's web browser

void SendHTML() {
  String html = "<html>\
    <head>\
      <title>ESW Project</title>\
      <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\
      <style>\
        body { font-family: Arial; text-align: center; margin:0px auto; padding-top: 30px;}\
        table { margin-left: auto; margin-right: auto; }\
        td { padding: 8px; }\
        .button {\
          background-color: #2f4468;\
          border: none;\
          color: white;\
          padding: 10px 20px;\
          text-align: center;\
          text-decoration: none;\
          display: inline-block;\
          font-size: 18px;\
          margin: 6px 3px;\
          cursor: pointer;\
          -webkit-touch-callout: none;\
          -webkit-user-select: none;\
          -khtml-user-select: none;\
          -moz-user-select: none;\
          -ms-user-select: none;\
          user-select: none;\
          -webkit-tap-highlight-color: rgba(0,0,0,0);\
        }\
      </style>\
    </head>\
    <body>\
      <h1>Hemingway Obstructronics</h1>\
      <table>\
        <tr><td colspan=\"3\" align=\"center\"><a class='button button-on' href='https://api.thingspeak.com/update?api_key=";
  html += apiKey;
  html += "&field5=1'>Forward</a></td></tr>";
  html += "<tr><td align=\"center\"><button class=\"button\" onmousedown=\"toggleCheckbox('left', 1);\" ontouchstart=\"toggleCheckbox('left', 1);\" onmouseup=\"toggleCheckbox('stop', 0);\" ontouchend=\"toggleCheckbox('stop', 0);\">Left</button></td>";
  html += "<td align=\"center\"><button class=\"button\" onmousedown=\"toggleCheckbox('stop', 0);\" ontouchstart=\"toggleCheckbox('stop', 0);\">Stop</button></td>";
  html += "<td align=\"center\"><button class=\"button\" onmousedown=\"toggleCheckbox('right', 1);\" ontouchstart=\"toggleCheckbox('right', 1);\" onmouseup=\"toggleCheckbox('stop', 0);\" ontouchend=\"toggleCheckbox('stop', 0);\">Right</button></td></tr>";
  html += "<tr><td colspan=\"3\" align=\"center\"><a class='button button-on' href='https://api.thingspeak.com/update?api_key=";
  html += apiKey;
  html += "&field4=1'>Backward</a></td></tr></table>";
  html += "<tr><td colspan=\"3\" align=\"center\"><a class='button button-on' href='https://api.thingspeak.com/update?api_key=";
  html += apiKey;
  html += "&field6=1'>Turn on Remote Control Mode</a></td></tr>";
  html += "<tr><td colspan=\"3\" align=\"center\"><a class='button button-on' href='https://api.thingspeak.com/update?api_key=";
  html += apiKey;
  html += "&field6=0'>Turn off Remote Control Mode</a></td></tr>";
  html += "<script>\
        function toggleCheckbox(x, value) {\
          var xhr = new XMLHttpRequest();\
          xhr.open(\"GET\", \"/action?go=\" + x + \"&value=\" + value, true);\
          xhr.send();\
        }\
      </script>\
    </body>\
  </html>";

  server.send(200, "text/html", html);  // Send the HTML content to the client
}
