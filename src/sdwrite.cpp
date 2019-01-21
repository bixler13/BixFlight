#include "BixFlight.h"
#include "SdFat.h"
#include "sdwrite.h"
#include "CircularBuffer.h"


SdFat Sd;
CircularBuffer<int,50> buffer;       // uses 638 bytes

void sdwrite_setup(){
  Sd.begin(4);
}

void sdwrite_loop(){

      // Write to current buffer
      int a = roll;
      buffer.push(a);

      // If buffer full...
      if(buffer.isFull()){

        File dataFile = Sd.open("data.csv", O_CREAT | O_APPEND | O_WRITE);

        for( int i = 0; i < 50; i++){
            dataFile.println(buffer[i]);
        }
        dataFile.close();
        dataFile.flush();
        buffer.clear();
      }
    }



















// void sdwrite_setup(){
//
//   Sd.begin(4);
//
// }
//
// void sdwrite_loop(){
//
// File dataFile = Sd.open("datalog.csv", O_CREAT | O_APPEND | O_WRITE);
//
// if (dataFile) {
//     dataFile.println(roll,2);
//     dataFile.close();
//   }
//
// }
