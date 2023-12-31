#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";

const String forwardUrl = "https://s-m.com.sa/f.html";
const String backwardUrl = "https://s-m.com.sa/b.html";
const String rightUrl = "https://s-m.com.sa/r.html";
const String leftUrl = "https://s-m.com.sa/l.html";
String payload = "";

// Define pins
const int ledPin1 = 25;
const int ledPin2 = 5;
const int ledPin3 = 32;
const int ledPin4 = 33;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.print("OK! IP=");
  Serial.println(WiFi.localIP());

  Serial.print("Fetching " + forwardUrl + backwardUrl+ rightUrl+ leftUrl +"... ");
}

void loop() {
  HTTPClient http;
  http.begin(forwardUrl);
  int httpResponseCode = http.GET();

  if (httpResponseCode > 0) {
    Serial.print("HTTP ");
    Serial.println(httpResponseCode);
    payload = http.getString();
    Serial.println();
    Serial.println(payload);

    if (payload == "forward ") {
      digitalWrite(ledPin1, HIGH);
    } else if (payload == "Right") {
      digitalWrite(ledPin2, HIGH);
    } else if (payload == "Backward") {
      digitalWrite(ledPin3, HIGH);
    } else if (payload == "left") {
      digitalWrite(ledPin4, HIGH);
    } else {
      digitalWrite(ledPin1, LOW); // Turn off all LEDs if unknown response received
      digitalWrite(ledPin2, LOW);
      digitalWrite(ledPin3, LOW);
      digitalWrite(ledPin4, LOW);
    }
  } else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
    Serial.println(":-(");
  }
  
  delay(1000); 
}