#include <arduino.h>
#include "BixFlight.h"
#include "rc_read.h"

void rc_read_setup_ppm(){
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), rc_read_ppm2, FALLING);
 }

void rc_read_ppm2(){
   a=micros(); //store time value a when pin value falling
   c=a-b;      //calculating time inbetween two peaks
   b=a;        //
   x[i]=c;     //storing 15 value in array
   i=i+1;
   if(i==15){
     for(int j=0;j<15;j++) {
       ch1[j]=x[j];
       }
              i=0;
              }
              }//copy store all values from temporary array another array after 15 reading

void rc_read_ppm(){
   int i,j,k=0;
   for(k=14;k>-1;k--){
     if(ch1[k]>10000){
       j=k;
       }
       }  //detecting separation space 10000us in that another array

   for(i=1;i<=6;i++){
     ch[i]=(ch1[i+j]-1000); //assign 6 channel values after separation space
       ch[i]=map(ch[i], 0, 1000, -1000, 1000);
       }

   throttle_input = ch[3];
   roll_input     = ch[1];
   pitch_input    = ch[2];
   mode_input     = ch[6];
   }

void find_mode(){

    if (mode_input > 1000 || mode_input < -1000){
      mode_input = mode_input_prev;
    }

    if (mode_input > 200){
      mode = 1;
    }

    else if (mode_input < -200){
      mode = 3;
    }

    else {
      mode = 2;
    }
    mode_input_prev = mode_input;
  }
