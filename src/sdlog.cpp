#include <arduino.h>
#include  <SD.h>
#include <SPI.h>
#include "BixFlight.h"
#include "sdlog.h"

void sdlog_setup(){
  // see if the card is present and can be initialized:
  if (!SD.begin(SDchip_pin)) {
    Serial.println("SD Card failed, or not present");
    // don't do anything more:
    while (1);
  }
  Serial.println("card initialized.");
}


void sdlog(){

}
