#include <Adafruit_NeoPixel.h>
#include <Math.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define LEDPIN 2
#define NUMBER_PIXELS 24

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMBER_PIXELS, LEDPIN, NEO_GRB + NEO_KHZ800);

int potPin = 2;
int val;
int tach = 0;
int curPos = 0;
int pixelnum = 0;
int x = 1;


void setup() {
  strip.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextSize(4);
  display.setTextColor(WHITE);
  Serial.begin(19200);

  
}

void loop() {
  val = analogRead(potPin);
  tach = val * 10;
  pixelnum = tach / 415; //This is a test value since there are 24 LEDs and the swing from the pot is 10k it gave me a good way to display
  
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

    if (pixelnum > 19) {
      strip.setPixelColor(curPos, 16, 0, 0);
    } else if (pixelnum > 14) {
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

void displayOLED ( int tach) {
  display.clearDisplay();
  display.setCursor(20, 20);
  display.println(tach);
  display.display();

}



