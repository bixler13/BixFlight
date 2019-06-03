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
  delay(100);
}

void display_show(){

if (screen  == 0) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println(F("     BixFlight"));

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

  display.setCursor(0,40);
  display.print("hz ");
  display.setCursor(50,40);
  display.print(timed.hz);
}

else if (screen == 1){
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println(F("    BixFlight PIDS"));

  display.setCursor(10,8);
  display.print("Pitch");

  display.setCursor(85,8);
  display.print("Roll");

  display.setCursor(0,16);
  display.print("p");
  display.setCursor(0,24);
  display.print("i");
  display.setCursor(0,32);
  display.print("d");
  display.setCursor(20,16);
  display.print(p_pitch);
  display.setCursor(20,24);
  display.print(i_pitch);
  display.setCursor(20,32);
  display.print(d_pitch);

  display.setCursor(75,16);
  display.print("p");
  display.setCursor(75,24);
  display.print("i");
  display.setCursor(75,32);
  display.print("d");
  display.setCursor(100,16);
  display.print(p_roll);
  display.setCursor(100,24);
  display.print(i_roll);
  display.setCursor(100,32);
  display.print(d_roll);
}

else if(screen == 2) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println(F("Screen "));
  display.setCursor(50,0);
  display.print(screen);
}

else if(screen == 3) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println(F("Screen "));
  display.setCursor(50,0);
  display.print(screen);
}

else if(screen == 4) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println(F("Screen "));
  display.setCursor(50,0);
  display.print(screen);
}

if (screen > 4){
  screen = 0;
}

if (screen < 0){
  screen = 4;
}

  display.display();

}
