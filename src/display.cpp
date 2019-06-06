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

if (page.num  == 0) {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println(F(" BixFlight"));

  display.setCursor(0,25);
  display.println(F("    By"));

  display.setCursor(0,50);
  display.println(F("    Bix"));
}

else if (page.num == 1){
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

else if(page.num == 2) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println(F(" BixFlight Live Data"));

  display.setCursor(0,8);
  display.print("-Servo-");

  display.setCursor(75,8);
  display.print("-IMU-");

  display.setCursor(0,16);
  display.print("1");
  display.setCursor(0,24);
  display.print("2");
  display.setCursor(0,32);
  display.print("3");
  display.setCursor(20,16);
  display.print(act.pwms[SERVO1]);
  display.setCursor(20,24);
  display.print(act.pwms[SERVO2]);
  display.setCursor(20,32);
  display.print(act.pwms[SERVO3]);

  display.setCursor(60,16);
  display.print("Pitch");
  display.setCursor(60,24);
  display.print("Roll");
  display.setCursor(60,32);
  display.print("Yaw");
  display.setCursor(95,16);
  display.print(att.raw[PITCH],1);
  display.setCursor(95,24);
  display.print(att.raw[ROLL],1);
  display.setCursor(95,32);
  display.print(att.raw[YAW],1);

  display.setCursor(45,46);
  display.print("Hz");
  display.setCursor(65,46);
  display.print(timed.hz);

  display.setCursor(35,56);
  display.print("On Time");
  display.setCursor(80,56);
  display.print(timed.totalTime/1000000);
}

else if(page.num == 3) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println(F("Screen "));
  display.setCursor(50,0);
  display.print(page.num);
}

else if(page.num == 4) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println(F("Screen "));
  display.setCursor(50,0);
  display.print(page.num);
}

  display.display();

}
