#include <arduino.h>
#include <Wire.h>
#include <servo.h>
#include "sensor.h"
#include "BixFlight.h"
#include "actuator.h"
#include "controller.h"
#include "rc_read.h"

float AccX,AccY,AccZ,Temp,GyroX,GyroY,GyroZ;
float accpitch,accroll;
float gyroroll,gyropitch;
float roll,pitch, pitch_error, roll_error;
float dt;

int pitch_servo_pin = 8;
int roll_servo1_pin = 9;
int roll_servo2_pin = 10;

float pitch_servo_angle = 90;
float roll_servo_angle = 90;
float roll_servo2_angle = 90;

unsigned long int a,b,c;
int x[15],ch1[15],ch[7],i;
//specifing arrays and variables to store values

 float throttle_input, pitch_input, roll_input, mode_input;

int mode; //mode 1 - stabilize, mode 2 - acro , mode 3 - manual
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
  IMU_Setup();
  servo_setup();
  rc_read_setup_ppm();
  Serial.begin(57600);
  delay(500);
}

void loop() {
  float StartTime = micros(); //start the timer to calculate looptime

  rc_read_ppm();
  find_mode();
  IMU_Read();
  IMU_Data();
  controller();
  servo_loop();
  delay(10);

  float EndTime = micros();
  dt = (EndTime - StartTime); //calculate the time between gyro reading values for the complemenatary filter
  dt = (dt) / 1000000; //convert to seconds

  Serial.print("Pitch  ");
  Serial.print(pitch);
  Serial.print("  Roll  ");
  Serial.print(roll);
  Serial.print(" mode  ");
  Serial.println(mode);
  //Serial.print(" dt  ");
  //Serial.println(mode);

}
