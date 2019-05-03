#ifndef TYPES_H
#define TYPES_H

#include <arduino.h>

enum rc {
  ROLL,
  PITCH,
  YAW,
};

struct att_t{
  int raw[3];  //raw yaw, pitch , roll
}; extern att_t att;

struct act_t{
  int pwm[4]; // servo pwm value (0-180) thro, elevator, ail1, ail2, rudd
}; extern act_t act;

struct time_t{
  uint32_t currentTime = 0;
  uint16_t previousTime = 0;
  uint16_t cycleTime = 0; // this is the number in micro second to achieve a full loop, it can differ a little and is taken into account in the PID loop
  uint32_t totalTime = 0;
}; extern time_t time;



#endif
