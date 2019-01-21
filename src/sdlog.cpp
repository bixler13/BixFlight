#include <arduino.h>
#include <SPI.h>
#include "BixFlight.h"
#include "sdlog.h"
#include "SdFat.h"

SdFat sd;
SdFile file; //creating the file that will be written too in the sd card
#define FILE_BASE_NAME "Data"

///////////////////////////////////////////////////////////////

void writeHeader() {
  file.print("dt , pitch , roll");
  file.println();
}
///////////////////////////////////////////////////////////

void sdlog_setup(){
  const uint8_t BASE_NAME_SIZE = sizeof(FILE_BASE_NAME) - 1;
  char fileName[13] = FILE_BASE_NAME "00.csv";

  if (!sd.begin(SS, SD_SCK_MHZ(50))) {
    sd.initErrorHalt();
  }
  // Find an unused file name.
  if (BASE_NAME_SIZE > 6) {
    //error("FILE_BASE_NAME too long");
  }
  while (sd.exists(fileName)) {
    if (fileName[BASE_NAME_SIZE + 1] != '9') {
      fileName[BASE_NAME_SIZE + 1]++;
    } else if (fileName[BASE_NAME_SIZE] != '9') {
      fileName[BASE_NAME_SIZE + 1] = '0';
      fileName[BASE_NAME_SIZE]++;
    } else {
      //error("Can't create file name");
    }
  }
  if (!file.open(fileName, O_WRONLY | O_CREAT | O_EXCL)) {
    //error("file.open");
  }

  writeHeader();

  //sd.begin(SDchip_pin);
}

//////////////////////////////////////////////////////////////////////////////

void sdlog_loop(){

file.print(dt);
file.print(" , ");
file.print(pitch);
file.print( "," );
file.print(roll);
file.println();
  // log_file = sd.open("DATA.txt", FILE_WRITE);
  //
  // if (log_file){
  //   log_file.print(dt,3);
  //   log_file.print(" , ");
  //   log_file.print(pitch,1);
  //   log_file.print(" , ");
  //   log_file.println(roll,1);
  // }
  // log_file.close();
}
