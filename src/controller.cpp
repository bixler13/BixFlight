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
    act.pwm[SERVO1] = mapFloat(command.input[PITCH], 1000, 2000, 1250, 1750);
    act.pwm[SERVO2] = mapFloat(command.input[ROLL], 1000, 2000, 1250 ,1750);
    act.pwm[SERVO3] = mapFloat(command.input[ROLL], 1000, 2000, 1250 ,1750);
}

void horizon_mode(){
    //first we need to calculate error
    command.angle[PITCH] = mapFloat(command.input[PITCH],1000,2000,-45,45);
    command.angle[ROLL] = mapFloat(command.input[ROLL],1000, 2000, -30,30);
    att.error[PITCH] = command.angle[PITCH]-att.raw[PITCH];
    att.error[ROLL] = command.angle[ROLL]-att.raw[ROLL];

    //Calculate the Kp porition
    P_pitch = p_pitch * att.error[PITCH];
    P_roll = p_roll * att.error[ROLL];

    //Calculate the Ki portion
      I_pitch_old = (((att.error[PITCH] * timed.cycleTime)/100000)+I_pitch_old);
      I_pitch_new = I_pitch_old *i_pitch;

      I_roll_old = ((att.error[ROLL] * timed.cycleTime)+I_roll_old);
      I_roll_new = I_roll_old *i_roll;

    //Calculate the Kd portion
    D_pitch = ((att.error[PITCH] - att.errorp[PITCH])/timed.cycleTime)*d_pitch;
    D_roll = ((att.error[ROLL] - att.errorp[ROLL])/timed.cycleTime)*d_roll;
    att.errorp[PITCH] = att.error[PITCH];
    att.errorp[ROLL] = att.error[ROLL];

    pitch_pidsum = (P_pitch + I_pitch_new + D_pitch); //sum the contributions
    roll_pidsum = (P_roll + I_roll_new + D_roll); //sum the contributions
    act.pwm[SERVO1] = constrain(act.center[SERVO1] - pitch_pidsum, 1250, 1750); //take in account for the servo center (trim)
    act.pwm[SERVO2] = constrain(act.center[SERVO2] + roll_pidsum, 1250, 1750); //take in account for the servo center (trim)
    act.pwm[SERVO3] = constrain(act.center[SERVO3] + roll_pidsum, 1250, 1750); //take in account for the servo center (trim)
   }

   void acro_mode(){
     // command.rate[PITCH] = mapFloat(command.input[PITCH], -1000, 1000, -100, 100);
     // command.rate[ROLL] = mapFloat(command.input[ROLL], -1000, 1000, -100, 100);
     // command.rate[PITCH] = (att.raw[PITCH] - att.rawp[PITCH] ) / time.cycleTime;
     // command.rate[ROLL] = (att.raw[ROLL] - att.rawp[ROLL] ) / time.cycleTime;
     //
     // att.rawp[YAW] = att.raw[YAW];
     // att.rawp[PITCH] = att.raw[PITCH];
     // att.rawp[ROLL] = att.raw[ROLL];
   }
