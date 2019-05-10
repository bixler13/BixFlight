#include "BixFlight.h"
#include <arduino.h>
#include "controller.h"
#include "function.h"
#include "common.h"

void controller_loop(){
  //mode determination/////////////////////////////////////////////////////////
    if (command.mode == 3){
      manual_mode();
    }
    else if (command.mode ==2){
      acro_mode();
    }
    else{
      horizon_mode();
    }
  //end mode determineation////////////////////////////////////////////////////////
}

void manual_mode(){
 //manual mode
    act.pwm[1] = mapFloat(command.input[PITCH], -1000, 1000, 50, 130);
    act.pwm[2] = mapFloat(command.input[ROLL], -1000, 1000, 130 ,50);
    act.pwm[3] = mapFloat(command.input[ROLL], -1000, 1000, 130 ,50);
}

void horizon_mode(){
    //first we need to calculate error
    command.angle[PITCH] = mapFloat(command.input[PITCH],-1000,1000,-45,45);
    command.angle[ROLL] = mapFloat(command.input[ROLL], -1000, 1000, -30,30);
    att.error[PITCH] = command.angle[PITCH]-att.raw[PITCH];
    att.error[ROLL] = command.angle[ROLL]-att.raw[ROLL];

    //Calculate the Kp porition
    P_pitch = p_pitch * att.error[PITCH];
    P_roll = p_roll * att.error[ROLL];

    //Calculate the Ki portion
      I_pitch_old = ((att.error[PITCH] * time.cycleTime)+I_pitch_old);
      I_pitch_new = I_pitch_old *i_pitch;

      I_roll_old = ((att.error[ROLL] * time.cycleTime)+I_roll_old);
      I_roll_new = I_roll_old *i_roll;

    //Calculate the Kd portion
    D_pitch = ((att.error[PITCH] - att.errorp[PITCH])/time.cycleTime)*d_pitch;
    D_roll = ((att.error[ROLL] - att.errorp[ROLL])/time.cycleTime)*d_roll;
    att.errorp[PITCH] = att.error[PITCH];
    att.errorp[ROLL] = att.error[ROLL];

    pitch_pidsum = (P_pitch + I_pitch_new + D_pitch); //sum the contributions
    roll_pidsum = (P_roll + I_roll_new + D_roll); //sum the contributions
    act.pwm[1] = constrain(act.center[PITCH] - pitch_pidsum, 30, 150); //take in account for the servo center (trim)
    act.pwm[2] = constrain(act.center[ROLL] + roll_pidsum, 30, 150); //take in account for the servo center (trim)
    act.pwm[3] = mapFloat(act.pwm[2], 0, 180, 180 ,0);
    act.pwm[2] = mapFloat(act.pwm[2], 0, 180, 180 ,0);
   }

   void acro_mode(){
     command.rate[PITCH] = mapFloat(command.input[PITCH], -1000, 1000, -100, 100);
     command.rate[ROLL] = mapFloat(command.input[ROLL], -1000, 1000, -100, 100);
     command.rate[PITCH] = (att.raw[PITCH] - att.rawp[PITCH] ) / time.cycleTime;
     command.rate[ROLL] = (att.raw[ROLL] - att.rawp[ROLL] ) / time.cycleTime;

     att.rawp[YAW] = att.raw[YAW];
     att.rawp[PITCH] = att.raw[PITCH];
     att.rawp[ROLL] = att.raw[ROLL];
   }
