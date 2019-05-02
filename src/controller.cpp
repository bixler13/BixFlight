#include "BixFlight.h"
#include <arduino.h>
#include "controller.h"
#include "function.h"
#include "common.h"

void controller_loop(){
  //mode determination/////////////////////////////////////////////////////////
    if (mode == 3){
      manual_mode();
    }
    else if (mode ==2){
      acro_mode();
    }
    else{
      horizon_mode();
    }
  //end mode determineation////////////////////////////////////////////////////////
}

void manual_mode(){
 //manual mode
    act.pwm[1] = mapFloat(pitch_input, -1000, 1000, 50, 130);
    act.pwm[2] = mapFloat(roll_input, -1000, 1000, 130 ,50);
    act.pwm[3] = mapFloat(roll_input, -1000, 1000, 130 ,50);
}

void horizon_mode(){
//////////////////////////Pitch Axis/////////////////////////////
    //first we need to calculate error
    pitch_command = mapFloat(pitch_input,-1000,1000,-45,45);
    roll_command = mapFloat(roll_input, -1000, 1000, -30,30);
    pitch_error = pitch_command-att.raw[PITCH];
    roll_error = roll_command-att.raw[ROLL];

    //Calculate the Kp porition
    P_pitch = p_pitch * pitch_error;
    P_roll = p_roll * roll_error;

    //Calculate the Ki portion
      if(throttle_input >= -500){
      I_pitch_old = ((pitch_error * dt)+I_pitch_old);
      I_pitch_new = I_pitch_old *i_pitch;

      I_roll_old = ((roll_error * dt)+I_roll_old);
      I_roll_new = I_roll_old *i_roll;
      }

      else{
        I_pitch_old = 0;
        I_pitch_new = 0;
        I_pitch_old = 0;
        I_pitch_new = 0;
      }

    //Calculate the Kd portion
    D_pitch = ((pitch_error - pitch_error_old)/dt)*d_pitch;
    D_roll = ((roll_error - roll_error_old)/dt)*d_roll;
    pitch_error_old = pitch_error;
    roll_error_old = roll_error;

    pitch_pidsum = (P_pitch + I_pitch_new + D_pitch); //sum the contributions
    roll_pidsum = (P_roll + I_roll_new + D_roll); //sum the contributions
    act.pwm[1] = constrain(pitch_servo_center + pitch_pidsum, 30, 150); //take in account for the servo center (trim)
    act.pwm[2] = constrain(roll_servo_center + roll_pidsum, 30, 150); //take in account for the servo center (trim)
    act.pwm[3] = mapFloat(act.pwm[2], 0, 180, 180 ,0);
    act.pwm[2] = mapFloat(act.pwm[2], 0, 180, 180 ,0);
   }

   void acro_mode(){
     pitch_rate_command = mapFloat(pitch_input, -1000, 1000, -100, 100);
     roll_rate_command = mapFloat(roll_input, -1000, 1000, -100, 100);
     pitch_rate = (pitch - pitch_old) / dt;
     roll_rate = (roll - roll_old) / dt;


     pitch = pitch_old;
     roll = roll_old;
   }
