#include <arduino.h>
#include <PWMServo.h>
#include "sensor.h"
#include "BixFlight.h"
#include "actuator.h"
#include "controller.h"
#include "rc_read.h"
#include "sdwrite.h"
#include "common.h"
#include "display.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
#include "button.h"

#define OUTPUT_IMU
//#define OUTPUT_SERVO
//#define OUTPUT_INPUT
#define OUTPUT_OTHER

//#define USE_RC
int thro_servo_pin = 10;
int pitch_servo_pin = 9;
int roll_servo1_pin = 6;
int roll_servo2_pin = 5;

unsigned long int a,b,c;
int x[15],ch1[15],ch[7],i;
//specifing arrays and variables to store values

int pitch_pidsum, roll_pidsum;
int pitch_command, roll_command;

//Pitch Axis Params
float p_pitch = 3; float P_pitch;
float i_pitch = 0; float I_pitch_old; float I_pitch_new; //.04 start
float d_pitch = 0; float D_pitch;

//Roll Axis Params
float p_roll = 6; float P_roll;
float i_roll = 0; float I_roll_old; float I_roll_new; //.07
float d_roll = 0; float D_roll;

//#define LOOP_TIME 10000 //20,000 = 50hz 10,000 = 100hz

void setup() {

  act.center[SERVO1] = 1510;
  act.center[SERVO2] = 1550;
  act.center[SERVO3] = 1550;
//setup functions/////////////////////////////////////////////////////////////
  servo_setup();
  ppm_read_setup();
  imu_setup();
  sdwrite_setup();
  display_setup();
//end setup functions//////////////////////////////////////////////////////////

  #if defined(OUTPUT_IMU)  || defined(OUTPUT_INPUT) || defined(OUTPUT_SERVO) || defined(OUTPUT_OTHER)
    Serial.begin(115200);
  #endif

  delay(500); //delay to prepare for loop to bein
}

void loop() {
//board loop sceduler///////////////////////////////////////////////////////////////////

  imu_loop(); //get imu data

  #if defined(USE_RC)
      ppm_read_loop(); //get rc data
  #else
  command.input[PITCH] = 1500;
  command.input[ROLL] = 1500;
  command.mode = 5;
  #endif

  controller_loop();
  servo_loop(); //write to servos
  sdwrite_loop(); //write to sd card
  button_read();
  display_show();

//end board loop//////////////////////////////////////////////////////////////

//serial printing////////////////////////////////////////////////////////////////

#ifdef OUTPUT_INPUT
  Serial.print(command.input[THROTTLE]);
  Serial.print(" , ");
  Serial.print(command.input[PITCH]);
  Serial.print(" , ");
  Serial.print(command.input[ROLL]);
  Serial.print(" , ");
  Serial.print(command.input[YAW]);
  Serial.print(" , ");
  Serial.print(command.mode);
  Serial.print(" , ");
#endif

#ifdef OUTPUT_IMU
  Serial.print("Yaw ");
  Serial.print(att.raw[YAW]);
  Serial.print(" , ");
  Serial.print(att.raw[ROLL]);
  Serial.print(" , ");
  Serial.println(att.raw[PITCH]);
  // Serial.print(" , ");
  // Serial.print(timed.cycleTime);
  // Serial.print(" , ");
  // Serial.println(timed.totalTime);
#endif

#ifdef OUTPUT_SERVO
  Serial.print(act.pwms[SERVO1]);
  Serial.print(" , ");
  Serial.print(act.pwms[SERVO2]);
  Serial.print(" , ");
  Serial.println(act.pwms[SERVO3]);
#endif

#ifdef OUTPUT_OTHER
  Serial.print(button.num);
  Serial.print(" , ");
  Serial.print(button.numlast);
  Serial.print(" , ");
  Serial.print(button.press);
  Serial.print(" , ");
  Serial.print(page.num);
  Serial.print(" , ");
  Serial.println(button.adc);
#endif

//end serial printing/////////////////////////////////////////////////////////

  while(1) {
    timed.currentTime = micros();
    timed.cycleTime = timed.currentTime - timed.previousTime;
    timed.hz = 1 * (1000000 / timed.cycleTime);
    #if defined(LOOP_TIME)
      if (timed.cycleTime >= LOOP_TIME) break;
    #else
      break;
    #endif
      }
  timed.previousTime = timed.currentTime;
  timed.totalTime = timed.totalTime + timed.cycleTime;

}
