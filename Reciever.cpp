#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <Servo.h>

const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

AsyncWebServer server(80);
Servo servo;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  
  servo.attach(2);
  
  server.on("/update", HTTP_POST, [](AsyncWebServerRequest *request) {
    String temperature = request->getParam("temperature", true)->value();
    if (temperature == "1") {
      servo.write(180);  // Rotate servo motor
      delay(5000);       // Keep it at 180 degrees for 5 seconds
      servo.write(0);    // Reset to 0 degrees
    }
    request->send(200, "text/plain", "OK");
  });
  
  server.begin();
}

void loop() {
}
