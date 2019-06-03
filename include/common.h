#ifndef TYPES_H
#define TYPES_H

#include <Arduino.h>

enum attitude {
  YAW = 1,
  PITCH = 2,
  ROLL = 3,
};

enum rc {
  THROTTLE = 1,
  ELEVATOR = 2,
  AILERON = 3,
  RUDDER = 4,
  MODE = 5,
  SWITCH = 6,
};

enum servo {
  SERVO1 = 1,
  SERVO2 = 2,
  SERVO3 = 3,
  SERVO4 = 4,
};

struct attt{
  float raw[3];  //raw yaw, pitch , roll
  float rawp[3]; //last raw yaw, pitch, roll
  float error[3]; //error in yaw, pitch, roll from comanded value
  float errorp[3]; //last error in yaw, pitch, roll
}; extern attt att;

struct commandt{
  int input[6]; //pwm input from tx
  int inputp[6]; //previous input from tx
  int angle[3]; //commanded theta or psi
  int rate[3]; //commanded roll or ptich rate
  int mode = 1;
  int swtch = 1;
}; extern commandt command;

struct actt{
  int pwm[4]; // servo pwm value (1000-2000) thro, elevator, ail1, ail2, rudder
  int pwms[4]; //servo pwm sent to arduino servo controller
  int center[4];
}; extern actt act;

struct timet{
  uint32_t currentTime = 0;
  uint16_t previousTime = 0;
  uint16_t cycleTime = 0; // this is the number in micro second to achieve a full loop, it can differ a little and is taken into account in the PID loop
  uint32_t totalTime = 0;
  uint16_t hz = 0;
}; extern timet timed;

struct pidt{
  int pitch[3]; //pid value for pitch axis P, I,D
  int roll[3]; //pid value for roll axis P,I,D
}; extern pidt pid;

struct buttont{
  int adc = 0;
  int num = 0;
  int numlast = 0;
}; extern buttont button;

#endif
