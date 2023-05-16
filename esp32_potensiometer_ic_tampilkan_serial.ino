#include <SPI.h>

// Definisikan pin untuk koneksi dengan 74HC595
const int latchPin = 5;   // Pin RCLK (ST_CP)
const int clockPin = 18;  // Pin SRCLK (SH_CP)
const int dataPin = 23;   // Pin SER (DS)

// Definisikan pin untuk koneksi dengan potensiometer
const int potentiometerPin = 32;  // Pin ADC untuk membaca potensiometer

void setup() {
    // Inisialisasi Serial Monitor
  Serial.begin(9600);
  // Inisialisasi pin sebagai OUTPUT
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  // Setup SPI (Serial Peripheral Interface)
  SPI.begin();

  // Setel kecepatan baca ADC
  analogReadResolution(12);  // Resolusi bacaan ADC 12-bit
}

void loop() {
  // Baca nilai dari potensiometer
  int potValue = analogRead(potentiometerPin);
   

  // Tampilkan nilai potensiometer pada Serial Monitor
  Serial.print("Nilai potensiometer: ");
  Serial.println(potValue);
  // Map nilai dari potensiometer ke rentang 0-4095
  int ledCount = map(potValue, 0, 4095, 0, 8);
  
  // Menghidupkan LED sesuai dengan putaran potensiometer
  byte ledData = 0;
  for (int i = 0; i < ledCount; i++) {
    bitSet(ledData, i);
  }
  sendShiftRegisterData(ledData);

  delay(100);  // Delay untuk stabilisasi
}

// Fungsi untuk mengirimkan data ke 74HC595
void sendShiftRegisterData(byte data) {
  // Mengaktifkan register latch
  digitalWrite(latchPin, LOW);
  
  // Mengirimkan data secara serial menggunakan SPI
  SPI.transfer(data);
  
  // Menonaktifkan register latch, mengirimkan data ke output pin
  digitalWrite(latchPin, HIGH);
}
