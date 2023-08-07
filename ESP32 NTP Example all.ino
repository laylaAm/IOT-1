#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";

const String url = "https://s-m.com.sa/f.html";
String payload = "";

// Define pins
const int ledPin1 = 25;
const int ledPin2 = 5;
const int ledPin6 = 32;
const int ledPin7 = 33;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin6, OUTPUT);
  pinMode(ledPin7, OUTPUT);

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.print("OK! IP=");
  Serial.println(WiFi.localIP());

  Serial.print("Fetching " + url + "... ");
}

void loop() {
  HTTPClient http;
  http.begin(url);
  int httpResponseCode = http.GET();

  if (httpResponseCode > 0) {
    Serial.print("HTTP ");
    Serial.println(httpResponseCode);
    payload = http.getString();
    Serial.println();
    Serial.println(payload);

    if (payload == "forward") {
      digitalWrite(ledPin1, HIGH); // Turn on LED 1
      digitalWrite(ledPin2, HIGH); // Turn on LED 2
      digitalWrite(ledPin6, HIGH); // Turn on LED 3
      digitalWrite(ledPin7, HIGH); // Turn on LED 4
    } else {
      digitalWrite(ledPin1, LOW); // Turn off all LEDs if unknown response received
      digitalWrite(ledPin2, LOW);
      digitalWrite(ledPin6, LOW);
      digitalWrite(ledPin7, LOW);
    }
  } else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
    Serial.println(":-(");
  }
  
  delay(1000); 
}