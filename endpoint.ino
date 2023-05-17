#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "Wokwi-GUEST";       // Nama SSID (nama jaringan WiFi)
const char* password = "";   // Kata sandi jaringan WiFi
const char* ip_address = "10.10.0.2"; // Alamat IP ESP32

int potPin = 32; // Pin potensiometer
int potVal;      // Nilai potensiometer

void setup() {
  Serial.begin(115200);

  // Menghubungkan ke jaringan WiFi
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
}

void loop() {
  // Membaca nilai potensiometer
  potVal = analogRead(potPin);

  // Membuat objek HTTPClient
  HTTPClient http;

  String url = "http://" + String(ip_address) + "/get-data";

  // Membuat objek JSON
  DynamicJsonDocument jsonDoc(1024);
  jsonDoc["potensiometer"] = potVal;
  String payload;
  serializeJson(jsonDoc, payload);

  // Melakukan permintaan POST
  http.begin(url);
  http.addHeader("Content-Type", "application/json");
  int httpResponseCode = http.POST(payload);
  if (httpResponseCode == HTTP_CODE_OK) {
    String response = http.getString();
    Serial.println(response);
  } else {
    Serial.print("HTTP POST request failed, error code: ");
    Serial.println(httpResponseCode);
  }

  http.end();  // Mengakhiri permintaan HTTP

  delay(5000);  // Jeda 5 detik antara setiap permintaan
}
