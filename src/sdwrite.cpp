#include "BixFlight.h"
#include "SdFat.h"
#include "sdwrite.h"
#include "common.h"

    SdFat sd;
    SdFile csvFile;
    int counter = 0;
    char filename[20];
    char datalist[20];

    void sdwrite_setup(){
      randomSeed(analogRead(0));
      long num = random(99);
      sprintf(filename, "data_%d.csv",num);
      sd.begin(4, SPI_FULL_SPEED); //SD_SCK_MHZ(50)
      csvFile.open(filename, O_CREAT | O_APPEND | O_WRITE);
      sprintf(datalist, "time (ms), roll (deg),pitch (deg),pitch_in (pwm),roll_in (pwm), pitch_servo, roll_servo, roll2_servo\n");
      csvFile.write(datalist);
      csvFile.flush();
    }

    void sdlog(){
      csvFile.flush();
      csvFile.open(filename, O_CREAT | O_APPEND | O_WRITE);
      counter = 0;
      }

    void sdwrite_loop(){

        char dataString[20];
        int time_write = timed.totalTime/1000;
        int roll_write = att.raw[ROLL];
        int pitch_write = att.raw[PITCH];
        int rollin_write = command.input[ROLL];
        int pitchin_write = command.input[PITCH];
        int pitch_servo_write = act.pwm[1];
        int roll_servo_write = act.pwm[2];
        int roll_servo2_write = act.pwm[3];


        sprintf(dataString, "%d, %d ,%d ,%d ,%d, %d, %d, %d\n", time_write, roll_write, pitch_write, rollin_write, pitchin_write, pitch_servo_write, roll_servo_write, roll_servo2_write);

        csvFile.write(dataString);

          if(counter >= 1000){
            sdlog();
          }

          counter ++;
          //Serial.println(sizeof(dataString));
        }
