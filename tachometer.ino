#include <Adafruit_NeoPixel.h>
#include <Math.h>

#define LEDPIN 2 
#define NUMBER_PIXELS 24 

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMBER_PIXELS, LEDPIN, NEO_GRB + NEO_KHZ800);

int potPin = 2;
int val;
int tach = 0;
int curPos=0;
int pixelnum=0;


void setup() {
  strip.begin();
  Serial.begin(19200);
}

void loop() {
 val = analogRead(potPin);
 tach = val * 10;
 pixelnum = tach / 415;
 displayTach(pixelnum);

}

void displayTach( int pixelnum){
  
if(pixelnum > curPos) {
  
  if (pixelnum > 19){
      strip.setPixelColor(curPos, 16, 0, 0);
  } else if (pixelnum >14) {
    strip.setPixelColor(curPos, 16, 16, 0);
  } else {
    strip.setPixelColor(curPos, 0, 16, 0);
  }
      strip.show();
      curPos++;
      
} else {
   strip.setPixelColor(curPos, 0);
      strip.show();
      --curPos;
}



  }



