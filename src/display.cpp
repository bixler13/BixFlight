#include "arduino.h"
#include "BixFlight.h"
#include "display.h"
#include "SPI.h"
#include "Wire.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
#include "common.h"

Adafruit_SSD1306 display(128, 64, &Wire, 4);

void display_setup(){

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0X3C)){
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  display.clearDisplay();
  display.display();
  delay(1000);
}

void display_show(){

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println(F("   Bix Simulator"));

  display.setCursor(0,16);
  display.print("Sabertooth   =      F");
  display.setCursor(100,16);
  display.print("test");

  display.setCursor(0,24);
  display.print("Diode        =      F");
  display.setCursor(100,24);
  display.print("test");

  display.setCursor(0,32);
  display.print("Power Supply =      F");
  display.setCursor(100,32);
  display.print("test");

  display.setCursor(0,55);
  display.print("LED Mode = Blue");

  display.display();

}
