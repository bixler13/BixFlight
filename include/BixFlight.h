#ifndef BIXFLIGHT_H
#define BIXFLIGHT_H

extern int SDchip_pin;

extern int thro_servo_pin;
extern int pitch_servo_pin;
extern int roll_servo1_pin;
extern int roll_servo2_pin;

extern unsigned long int a,b,c;
extern int x[15],ch1[15],ch[7],i;

extern float pitch_pidsum, roll_pidsum;
extern float pitch_command, roll_command;

//Pitch Axis Params
extern int pitch_servo_center; //Adjust this value to trim the aircraft
extern float p_pitch; extern float P_pitch;
extern float i_pitch; extern float I_pitch_old; extern float I_pitch_new;
extern float d_pitch; extern float D_pitch;

//Roll Axis Params
extern int roll_servo_center; //Adjust this value to trim the aircraft
extern float p_roll; extern float P_roll;
extern float i_roll; extern float I_roll_old; extern float I_roll_new;
extern float d_roll; extern float D_roll;

#endif
