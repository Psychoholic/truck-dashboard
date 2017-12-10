#include <Adafruit_NeoPixel.h>
#include <Math.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define LEDPIN 2 
#define NUMBER_PIXELS 24 

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2


#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMBER_PIXELS, LEDPIN, NEO_GRB + NEO_KHZ800);

int potPin = 2;
int val;
int tach = 0;
int curPos=0;
int pixelnum=0;


void setup() {
  strip.begin();
  Serial.begin(19200);
   display.begin(SSD1306_SWITCHCAPVCC, 0x3C); 
     display.setTextSize(4);

     
 
}

void loop() {
 val = analogRead(potPin);
 tach = val * 10;
 pixelnum = tach / 415;
 displayTach(pixelnum);

 display.setCursor(20,20);
   display.setTextColor(WHITE);
  display.clearDisplay();
  display.println(tach);
  display.display();

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



