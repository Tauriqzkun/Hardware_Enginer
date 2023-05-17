//untuk jalankan potensiometer 
/*
 * untuk menjalan program ini saya menggunakan wokmi.com untuk mempermudah simulasi
 * dan software arduino untuk membantu simpan file sebagai file .ino
 */
const int pot = 32;   // Pin potensiometer
float floatMap(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void setup() {
  Serial.begin(9600);
}
void loop() {
  int analogValue = analogRead(pot);
  float voltage = floatMap(analogValue, 0, 4095, 0, 3.3);
  // Tampilan nilai 
  Serial.print("Analog: ");
  Serial.print(analogValue); //tampilkan nilai analog 
  Serial.print(", Voltage: ");
  Serial.println(voltage); //tampilkan nilai volt 
  delay(1000);
}
