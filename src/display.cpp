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
  display.println(F("   BixFlight"));

  display.setCursor(0,16);
  display.print("ROLL ");
  display.setCursor(50,16);
  display.print(att.raw[ROLL]);

  display.setCursor(0,24);
  display.print("PITCH ");
  display.setCursor(50,24);
  display.print(att.raw[PITCH]);

  display.setCursor(0,32);
  display.print("YAW ");
  display.setCursor(50,32);
  display.print(att.raw[YAW]);

  display.display();

}
