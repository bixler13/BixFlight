#include "BixFlight.h"
#include "common.h"
#include "button.h"
#include "arduino.h"

void button_read(){

    button.adc = analogRead(22);

    if(button.adc > 150 && button.adc < 220){
      button.num = 1;
    }

    else if(button.adc > 250 && button.adc < 300){
      button.num = 2;

    }

    else if(button.adc > 350 && button.adc < 450){
      button.num = 3;
    }

    else if(button.adc > 500 && button.adc < 700){
      button.num = 4;
    }

    else if(button.adc > 800 && button.adc < 1100){
      button.num = 5;
    }

    else{
      button.num = 0;
    }

    if(button.num == 2 && button.numlast == !2){
      screen = screen + 1;
    }

    else if(button.num == 4 && button.numlast == !4){
      screen = screen - 1;
    }

    button.numlast = button.num;

}
