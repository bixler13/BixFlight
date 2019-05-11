#ifndef TYPES_H
#define TYPES_H

#include <arduino.h>

enum rc {
  ROLL = 1,
  PITCH = 2,
  YAW = 3,
  MODE = 4,
  THROTTLE = 5,
  SWITCH = 6,
};

struct att_t{
  int raw[3];  //raw yaw, pitch , roll
  int rawp[3]; //last raw yaw, pitch, roll
  int error[3]; //error in yaw, pitch, roll from comanded value
  int errorp[3]; //last error in yaw, pitch, roll
}; extern att_t att;

struct command_t{
  int input[6]; //pwm input from tx
  int inputp[6]; //previous input from tx
  int angle[3]; //commanded theta or psi
  int rate[3]; //commanded roll or ptich rate
  int mode = 1;
  int swtch = 1;
}; extern command_t command;

struct act_t{
  int pwm[4]; // servo pwm value (1000-2000) thro, elevator, ail1, ail2, rudder
  int pwms[4]; //servo pwm sent to arduino servo controller
  int center[4];
}; extern act_t act;

struct time_t{
  uint32_t currentTime = 0;
  uint16_t previousTime = 0;
  uint16_t cycleTime = 0; // this is the number in micro second to achieve a full loop, it can differ a little and is taken into account in the PID loop
  uint32_t totalTime = 0;
}; extern time_t time;

struct pid_t{
  int pitch[3]; //pid value for pitch axis P, I,D
  int roll[3]; //pid value for roll axis P,I,D
}; extern pid_t pid;

#endif
