#include <arduino.h>
#include <Servo.h>
#include "sensor.h"
#include "BixFlight.h"
#include "actuator.h"
#include "controller.h"
#include "rc_read.h"
#include "sdwrite.h"
#include "common.h"

#define OUTPUT_IMU
//#define OUTPUT_SERVO
//#define OUTPUT_INPUT
//#define OUTPUT_OTHER

float roll, pitch, yaw, pitch_error, roll_error, yaw_error;
float roll_old, pitch_old, roll_rate, pitch_rate;
float roll_rate_command, pitch_rate_command;
float pitch_error_old, roll_error_old, yaw_error_old;
float dt = .02;

int SDchip_pin = 10; //digitial pin for sd card logging purposes
int thro_servo_pin = 11;
int pitch_servo_pin = 8;
int roll_servo1_pin = 9;
int roll_servo2_pin = 7;

float thro_servo_angle = 0;
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

//#define LOOP_TIME 10000 //20,000 = 50hz 10,000 = 100hz

void setup() {
//setup functions/////////////////////////////////////////////////////////////
  servo_setup();
  ppm_read_setup();
  imu_setup();
  sdwrite_setup();
//end setup functions//////////////////////////////////////////////////////////

  #if defined(OUTPUT_IMU)  || defined(OUTPUT_INPUT) || defined(OUTPUT_SERVO) || defined(OUTPUT_OTHER)
    Serial.begin(115200);
  #endif

  delay(500); //delay to prepare for loop to bein
}

void loop() {

//board loop sceduler///////////////////////////////////////////////////////////////////

  imu_loop(); //get imu data
  ppm_read_loop(); //get rc data
  controller_loop();
  servo_loop(); //write to servos
  sdwrite_loop(); //write to sd card

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
  Serial.print(att.raw[YAW]);
  Serial.print(" , ");
  Serial.print(att.raw[PITCH]);
  Serial.print(" , ");
  Serial.print(att.raw[ROLL]);
  Serial.print(" , ");
  Serial.print(time.cycleTime);
  Serial.print(" , ");
  Serial.println(time.totalTime);
#endif

#ifdef OUTPUT_SERVO
  Serial.print(act.pwm[1]);
  Serial.print(" , ");
  Serial.print(act.pwm[2]);
  Serial.print(" , ");
  Serial.println(act.pwm[3]);
#endif

#ifdef OUTPUT_OTHER
  Serial.print(act.pwm[1]);
  Serial.print(" , ");
  Serial.print(time.cycleTime);
  Serial.print(" , ");
  Serial.println(att.raw[0]);
#endif
//end serial printing/////////////////////////////////////////////////////////

  while(1) {
    time.currentTime = micros();
    time.cycleTime = time.currentTime - time.previousTime;
    #if defined(LOOP_TIME)
      if (time.cycleTime >= LOOP_TIME) break;
    #else
      break;
    #endif
      }
  time.previousTime = time.currentTime;
  time.totalTime = time.totalTime + time.cycleTime;

}
