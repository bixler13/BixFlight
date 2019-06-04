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

 //button press determination
    for(int b=1; b<=5; b++){
      if(button.num == b && button.numlast == !b){
        button.press = b;
      }
      else if(button.num == b && button.numlast == b){
        button.press = 0;
      }
    }
    button.numlast = button.num;

//screen switching

    if(button.press == 4){
      screen = screen - 1;
    }

    if(button.press == 2){
      screen = screen + 1;
    }

    if (screen >= 5){
      screen = 0;
    }

    if (screen <= -1){
      screen = 4;
    }

//value changing
    else if(button.press == 5){
      p_pitch = p_pitch + .1;
    }

    else if(button.press == 3){
      p_pitch = p_pitch - .1;
    }



}
