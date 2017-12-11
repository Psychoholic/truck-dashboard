#include <Adafruit_NeoPixel.h>
#include <Math.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define LEDPIN 2
#define NUMBER_PIXELS 24

#define MAXRPM 5000  //it's an old big block Ford, I wouldn't go over this unless you want to be sweeping up parts


#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMBER_PIXELS, LEDPIN, NEO_GRB + NEO_KHZ800);

int potPin = 2;
int val;
int tach = 0;
int curPos = 0;
int pixelnum = 0;
int x = 1;
int rpmperpixel = round(MAXRPM / NUMBER_PIXELS);
int redline = NUMBER_PIXELS * .9; //90% of the total rpm
int yellowline = NUMBER_PIXELS * .7;  //I figured 70% was a good shift point

void setup() {
  strip.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextSize(4);
  display.setTextColor(WHITE);
  strip.setBrightness(16);  // 0 - 255 these things are mega bright so I'd be gentle here

  
}

void loop() {
  val = analogRead(potPin);
  tach = val * 10;
  pixelnum = tach / rpmperpixel; 
  
  //this next little bit is here because the speed of the OLED display was making the LEDs slow
  //updating the display every 50 cycles seems to be a pretty good sweet spot
  
  if ( x < 50 ){ 
    displayTach(pixelnum);
    x++;
  } else {
    displayTach(pixelnum);
    displayOLED(tach);
    x = 1; 
  }
}

void displayTach( int pixelnum) {


  if (pixelnum > curPos) {

    if (pixelnum > redline) {
      strip.setPixelColor(curPos, 16 , 0, 0);
    } else if (pixelnum > yellowline) {
      strip.setPixelColor(curPos, 16, 16, 0);
    } else {
      strip.setPixelColor(curPos,  0, 16, 0);
    }
    strip.show();
    curPos++;

  } else {
    strip.setPixelColor(curPos, 0);
    strip.show();
    --curPos;
  }
}

void displayOLED ( int tach) {
  display.clearDisplay();
  display.setCursor(20, 20);
  display.println(tach);
  display.display();

}



