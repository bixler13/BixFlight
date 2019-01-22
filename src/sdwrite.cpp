#include "BixFlight.h"
#include "SdFat.h"
#include "sdwrite.h"
#include "CircularBuffer.h"

    SdFat sd;
    SdFile csvFile;
    int counter = 0;


    void sdwrite_setup(){
      sd.begin(4, SPI_FULL_SPEED); //SD_SCK_MHZ(50)
      csvFile.open("data.csv", O_CREAT | O_APPEND | O_WRITE);
    }

    void sdlog(){
      //csvFile.close();
      csvFile.flush();
      csvFile.open("data.csv", O_CREAT | O_APPEND | O_WRITE);
      counter = 0;
      }

    void sdwrite_loop(){

        char dataString[5];
        int roll_write = roll;


        sprintf(dataString, "%d ,", roll_write);

        csvFile.write(dataString);

          if(counter >= 10){
            sdlog();
          }

          counter ++;
          Serial.println(counter);
        }


        //CircularBuffer<int,25> buffer;       // uses 319 bytes //we have 2000

        //
        // // Write to current buffer
        // //int dt = dt;
        // int roll_write = roll;
        // //int pitch_write = pitch;
        // //int yaw_write = yaw;
        //
        // buffer.push(roll_write);
        //
        // // If buffer full...
        // if(buffer.isFull()){
        //
        //   String dataString = "";
        //
        //   for( int i = 0; i < 25; i++){ //conver to string
        //   dataString += String(buffer[i]);
        //   dataString += ",";
        //   }
        //
        //   File dataFile = Sd.open("data.csv", O_CREAT | O_APPEND | O_WRITE);
        //   dataFile.print(dataString);
        //   dataFile.close();
        //   dataFile.flush();
        //   buffer.clear();
        // }
