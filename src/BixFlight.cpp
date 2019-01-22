#include <arduino.h>
#include <servo.h>
#include "sensor.h"
#include "BixFlight.h"
#include "actuator.h"
#include "controller.h"
#include "rc_read.h"
#include "sdwrite.h"

#define OUTPUT_IMU
//#define OUTPUT_SERVO
//#define OUTPUT_INPUT

float roll, pitch, yaw, pitch_error, roll_error, yaw_error;
float roll_old, pitch_old, roll_rate, pitch_rate;
float roll_rate_command, pitch_rate_command;
float pitch_error_old, roll_error_old, yaw_error_old;
float dt;

int SDchip_pin = 10; //digitial pin for sd card logging purposes
int pitch_servo_pin = 8;
int roll_servo1_pin = 9;
int roll_servo2_pin = 7;

float pitch_servo_angle = 90; //defined at 90 for startup loop to prevent overheating
float roll_servo_angle = 90;
float roll_servo2_angle = 90;

unsigned long int a,b,c;
int x[15],ch1[15],ch[7],i;
//specifing arrays and variables to store values

float throttle_input, pitch_input, yaw_input, roll_input, mode_input, switch_input;

int mode, swtch;
int mode_input_prev;

float pitch_pidsum, roll_pidsum;
float pitch_command, roll_command;

//Pitch Axis Params
int pitch_servo_center = 90; //Adjust this value to trim the aircraft
float p_pitch = .9; float P_pitch;
float i_pitch = 0; float I_pitch_old; float I_pitch_new;
float d_pitch = 0; float D_pitch;

//Roll Axis Params
int roll_servo_center = 90; //Adjust this value to trim the aircraft
float p_roll = 1.5; float P_roll;
float i_roll = 0; float I_roll_old; float I_roll_new;
float d_roll = 0; float D_roll;


void setup() {
//setup functions/////////////////////////////////////////////////////////////
  servo_setup();
  ppm_read_setup();
  imu_setup();
  sdwrite_setup();
//end setup functions//////////////////////////////////////////////////////////

  #if defined(OUTPUT_IMU)  || defined(OUTPUT_INPUT) || defined(OUTPUT_SERVO)
    Serial.begin(115200);
  #endif

  delay(500); //delay to prepare for loop to bein
}

void loop() {
  float StartTime = micros(); //start the timer to calculate looptime

//board loop///////////////////////////////////////////////////////////////////

  imu_loop();
  ppm_read_loop();
  servo_loop();
  sdwrite_loop();

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


//end board loop//////////////////////////////////////////////////////////////

//serial printing////////////////////////////////////////////////////////////////

#ifdef OUTPUT_INPUT
  Serial.print(throttle_input);
  Serial.print(" , ");
  Serial.print(pitch_input);
  Serial.print(" , ");
  Serial.print(roll_input);
  Serial.print(" , ");
  Serial.print(yaw_input);
  Serial.print(" , ");
  Serial.println(swtch);
#endif

#ifdef OUTPUT_IMU
  // Serial.print(roll);
  // Serial.print(" , ");
  // Serial.print(pitch);
  // Serial.print(" , ");
  // Serial.print(yaw);
  // Serial.print(" , ");
  // Serial.println(dt,3);
#endif

#ifdef OUTPUT_SERVO
  Serial.print(pitch_servo_angle);
  Serial.print(" , ");
  Serial.print(roll_servo_angle);
  Serial.print(" , ");
  Serial.println(roll_servo2_angle);
#endif
//end serial printing/////////////////////////////////////////////////////////

  float EndTime = micros();
  dt = (EndTime - StartTime); //calculate the time between gyro reading values for the complemenatary filter
  dt = (dt) / 1000000; //convert to seconds

}
