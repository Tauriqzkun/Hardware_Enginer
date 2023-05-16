// untuk jalankan ic 745hc595
const int latchPin = 5;   // Pin RCLK (ST_CP)
const int clockPin = 18;  // Pin SRCLK (SH_CP)
const int dataPin = 23;   // Pin SER (DS)
byte leds;
void setup()
{
  Serial.begin(9600);

  // Set all the pins of 74HC595 as OUTPUT
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
}

void loop()
{
  leds = 0;        // inisiasi led untuk mati
  updateShiftRegister();
  delay(500);
  for (int i = 0; i < 8; i++)        // led sebanyak 8 kali perulangan
  {
    bitSet(leds, i);                // untuk set led hidup ke bagian berapa
    updateShiftRegister();
    delay(500);
  }
}

void updateShiftRegister()
{
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, leds);
  digitalWrite(latchPin, HIGH);
}
