#include <arduino.h>
#include  <SD.h>
#include <SPI.h>
#include "BixFlight.h"
#include "sdlog.h"

File log_file; //creating the file that will be written too in the sd card

void sdlog_setup(){

  // see if the card is present and can be initialized:
  if (!SD.begin(SDchip_pin)) {
    Serial.println("SD Card failed, or not present");
    // don't do anything more:
    while (1);
  }
  Serial.println("SD Card Initialized");

  log_file = SD.open("DATA.txt", FILE_WRITE);

  if (log_file){
    Serial.println("Log File Open");
    log_file.println("dt, pitch, roll");
  }
  log_file.close();
}


void sdlog(){
  //String mystring;
  //mystring = String(roll);

  log_file = SD.open("DATA.txt", FILE_WRITE);

  if (log_file){
    log_file.print(dt);
    log_file.print(" , ");
    log_file.print(pitch);
    log_file.print(" , ");
    log_file.println(roll);
  }
  log_file.close();

}
