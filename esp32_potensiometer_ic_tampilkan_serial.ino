// untuk jalankan ic 745hc595
const int latchPin = 5;   // Pin RCLK (ST_CP)
const int clockPin = 18;  // Pin SRCLK (SH_CP)
const int dataPin = 23;   // Pin SER (DS)
byte leds;     
//untuk jalankan potensiometer 
const int pot = 32;   // Pin potensiometer
float floatMap(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

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
        // read the input on analog pin GIOP36:
  int analogValue = analogRead(pot);
  // Rescale to potentiometer's voltage (from 0V to 3.3V):
  float voltage = floatMap(analogValue, 0, 4095, 0, 3.3);

  // print out the value you read:
  Serial.print("Analog: ");
  Serial.print(analogValue);
  Serial.print(", Voltage: ");
  Serial.println(voltage);
  }

  //delay(1000);
}

void updateShiftRegister()
{
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, LSBFIRST, leds);
   digitalWrite(latchPin, HIGH);
}
