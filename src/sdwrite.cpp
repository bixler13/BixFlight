#include "BixFlight.h"
#include "SdFat.h"
#include "sdwrite.h"
#include "CircularBuffer.h"

    SdFat Sd;
    CircularBuffer<int,25> buffer;       // uses 319 bytes //we have 2000

    void sdwrite_setup(){
      Sd.begin(4, SPI_FULL_SPEED); //SPI_FULL_SPEED
    }

    void sdwrite_loop(){

          // Write to current buffer
          //int dt = dt;
          int roll_write = roll;
          //int pitch_write = pitch;
          //int yaw_write = yaw;

          buffer.push(roll_write);

          // If buffer full...
          if(buffer.isFull()){

            String dataString = "";

            for( int i = 0; i < 25; i++){ //conver to string
            dataString += String(buffer[i]);
            dataString += ",";
            }

            File dataFile = Sd.open("data.csv", O_CREAT | O_APPEND | O_WRITE);
            dataFile.print(dataString);
            dataFile.close();
            dataFile.flush();
            buffer.clear();
          }
        }
