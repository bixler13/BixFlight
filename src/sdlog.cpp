#include <arduino.h>
#include  <SD.h>
#include <SPI.h>
#include "BixFlight.h"
#include "sdlog.h"

File log_file; //creating the file that will be written too in the sd card

void sdlog_setup(){
  SD.begin(SDchip_pin);
}


void sdlog_loop(){

  log_file = SD.open("DATA.txt", FILE_WRITE);

  if (log_file){
    log_file.print(dt,3);
    log_file.print(" , ");
    log_file.print(pitch,1);
    log_file.print(" , ");
    log_file.println(roll,1);
  }
  log_file.close();
}
