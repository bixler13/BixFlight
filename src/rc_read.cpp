#include <arduino.h>
#include "BixFlight.h"
#include "rc_read.h"
#include "common.h"

void ppm_read_setup(){
  pinMode(23, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(23), rc_read_ppm2, FALLING);
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

void ppm_read_loop(){
   int i,j,k=0;
   for(k=14;k>-1;k--){
     if(ch1[k]>10000){
       j=k;
       }
       }  //detecting separation space 10000us in that another array

   for(i=1;i<=6;i++){
     ch[i]=(ch1[i+j]-1000); //assign 6 channel values after separation space
       ch[i]=map(ch[i], 0, 1000, 1000, 2000);
       }

   command.input[THROTTLE] = ch[3];
   command.input[ROLL]     = ch[1];
   command.input[PITCH]    = ch[2];
   command.input[MODE]     = ch[6];
   command.input[YAW]     = ch[4];
   command.input[SWITCH]   = ch[5];

    if (command.input[MODE] > 2000 || command.input[MODE] < 1000){
      command.input[MODE] = command.inputp[MODE];
    }

    if (command.input[MODE] > 1600){
      command.mode = 1;
    }

    else if (command.input[MODE] < 1400){
      command.mode = 3;
    }

    else {
      command.mode = 2;
    }
    command.inputp[MODE] = command.input[MODE];

  if (command.input[SWITCH] >= 1500){
    command.swtch = 1;
  }

  else {
    command.swtch = 0;
  }
}
