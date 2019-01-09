#include "BixFlight.h"
#include <arduino.h>
#include "controller.h"
#include "function.h"

void controller(){
  if (mode == 3){ //manual mode
    pitch_servo_angle = mapFloat(pitch_input, -1000, 1000, 50, 130);
    roll_servo2_angle = mapFloat(roll_input, -1000, 1000, 130 ,50);
    roll_servo_angle = mapFloat(roll_input, -1000, 1000, 130 ,50);
  }

  else{
//////////////////////////Pitch Axis/////////////////////////////
    //first we need to calculate error
    pitch_command = mapFloat(pitch_input,-1000,1000,-45,45);
    pitch_error = pitch_command-pitch;

    //Calculate the Kp porition
    P_pitch = p_pitch * pitch_error;

    //Calculate the Ki portion
    if(pitch_servo_angle > 31 && pitch_servo_angle < 149){
      I_pitch_old = ((pitch_error * dt)+I_pitch_old);
      I_pitch_new = I_pitch_old *i_pitch;
    }

    //Calculate the Kd portion
    D_pitch = ((pitch_error - pitch_error_old)/dt)*d_pitch;
    pitch_error_old = pitch_error;

    pitch_pidsum = (P_pitch + I_pitch_new + D_pitch); //sum the contributions
    pitch_servo_angle = constrain(pitch_servo_center + pitch_pidsum, 30, 150); //take in account for the servo center (trim)

    /////////////////////////Roll Axis//////////////////////////////
    //first we need to calculate error
    roll_command = mapFloat(roll_input, -1000, 1000, -30,30);
    roll_error = roll_command-roll;

    //Calculate the Kp porition
    P_roll = p_roll * roll_error;

    //Calculate the Ki portion
    I_roll_old = ((roll_error * dt)+I_roll_old);
    I_roll_new = I_roll_old *i_roll;

    //Calculate the Kd portion
    D_roll = ((roll_error - roll_error_old)/dt)*d_roll;
    roll_error_old = roll_error;

    roll_pidsum = (P_roll + I_roll_new + D_roll); //sum the contributions
    roll_servo_angle = constrain(roll_servo_center + roll_pidsum, 30, 150); //take in account for the servo center (trim)
    roll_servo2_angle = mapFloat(roll_servo_angle, 0, 180, 180 ,0);
    roll_servo_angle = mapFloat(roll_servo_angle, 0, 180, 180 ,0);
   }
  }
