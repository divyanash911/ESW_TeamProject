#include <WiFi.h>

const char* ssid = "YourWiFiSSID";
const char* password = "YourWiFiPassword";
const char* om2mServer = "http://127.0.0.1:5089"; // Replace with your OM2M server address
const char* om2mResource_u3 = "/~/in-cse/in-name/Autonomous_Mode/Distance_Ultrasonic/Ultrasonic_3"; // Replace with the specific resource path
const char* om2mResource_u2 = "/~/in-cse/in-name/Autonomous_Mode/Distance_Ultrasonic/Ultrasonic_2"; // Replace with the specific resource path
const char* om2mResource_u1 = "/~/in-cse/in-name/Autonomous_Mode/Distance_Ultrasonic/Ultrasonic_1"; // Replace with the specific resource path
const char* om2mResource_u4 = "/~/in-cse/in-name/Radar/Ultrasonic_4"; // Replace with the specific resource path


void setup() {
  Serial.begin(115200);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  // Your data to be sent to OM2M
  String dataToSend = "YourDataHere";
  
  // Construct the full URL to the OM2M resource
  String fullURL = om2mServer + om2mResource;
  
  // Send a POST request to OM2M
  HTTPClient http;
  http.begin(fullURL);
  http.addHeader("Content-Type", "application/json");
  
  int httpResponseCode = http.POST(dataToSend);
  
  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.println("HTTP Response: " + response);
  } else {
    Serial.print("Error on HTTP request: ");
    Serial.println(httpResponseCode);
  }
  
  http.end();
  
  delay(10000); // Send data every 10 seconds (adjust as needed)
}
