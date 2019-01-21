#include "BixFlight.h"
#include "SdFat.h"
#include "sdwrite.h"

SdFat Sd;



void sdwrite_setup(){

  Sd.begin(4);

}

void sdwrite_loop(){

File dataFile = Sd.open("datalog.csv", O_CREAT | O_APPEND | O_WRITE);

if (dataFile) {
    dataFile.println(roll,2);
    dataFile.close();
  }

}
