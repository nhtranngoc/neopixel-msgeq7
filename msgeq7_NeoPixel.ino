#include <Adafruit_NeoPixel.h>

#define PIN 10

int analogPin = 0; // read from multiplexer using analog input 0
int strobePin = 2; // strobe is attached to digital pin 2
int resetPin = 3; // reset is attached to digital pin 3
int spectrumValue[6]; // to hold a2d values

Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);

uint32_t red = strip.Color(255, 0, 0);
uint32_t orange = strip.Color(255, 127, 0);
uint32_t yellow = strip.Color(255, 255, 0);
uint32_t green = strip.Color(0, 255, 0);
uint32_t blue = strip.Color(0, 0, 255);
uint32_t purple = strip.Color(75, 0, 130);


void setup(){
  strip.begin();
  strip.show();
  pinMode(analogPin, INPUT);
  pinMode(strobePin, OUTPUT);
  pinMode(resetPin, OUTPUT);
  analogReference(DEFAULT);
  digitalWrite(resetPin, LOW);
  digitalWrite(strobePin, HIGH);
}

void loop()
{
 digitalWrite(resetPin, HIGH);
 digitalWrite(resetPin, LOW);

 for (int i = 0; i < 6; i++)
 {
   digitalWrite(strobePin, LOW);
   delayMicroseconds(30); // to allow the output to settle
   spectrumValue[i] = map(analogRead(analogPin), 0, 1023, 0, 9);
   setPixel(i*10, i*10+spectrumValue[i]);
   setReverse(i*10, i*10+spectrumValue[i]);
   strip.show();
   digitalWrite(strobePin, HIGH);
// Serial for debugging.
//  Serial.print(spectrumValue[i]);
//  Serial.print(" ");

 }
// Serial.println();
  delay(30);
}

void setPixel(int start_bit, int pixelValue){
  for(int j=start_bit; j<pixelValue; j++){
    strip.setPixelColor(j, colorChoose(start_bit));
  }
}


void setReverse(int start_bit, int pixelValue){
  for(int k=start_bit+9; k>pixelValue;k--){
    strip.setPixelColor(k, 0,0,0);
  }
}

uint32_t colorChoose(int start_bit){
  switch (start_bit){
    case 0: 
      return red;
      break;
    case 10:
      return orange;
      break;
    case 20:
      return yellow;
      break;
    case 30:
      return green;
      break;
    case 40:
      return blue;
      break;
    case 50:
      return purple;
      break;
  }
}
