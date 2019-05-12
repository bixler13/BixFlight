#include <Servo.h>
#include "actuator.h"
#include "BixFlight.h"
#include "common.h"

#define USE_SERVO

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;


void servo_setup(){
  servo1.attach(thro_servo_pin);
  servo2.attach(pitch_servo_pin);
  servo3.attach(roll_servo1_pin);
  servo4.attach(roll_servo2_pin);
}

void servo_loop(){

  #if(defined(USE_SERVO))
    for(int s = 1; s<=4; s++){
      act.pwms[s] = map(act.pwm[s],1000,2000,0,180);
    }
    servo2.write(act.pwms[SERVO1]);
    servo3.write(act.pwms[SERVO2]);
    servo4.write(act.pwms[SERVO3]);
  #else
    for(int s = 1; s<=4; s++){
    act.pwms[s] = map(act.pwm[s],1000,2000,0,180);
    }
    servo1.write(0); //throttle
    servo2.write(90);
    servo3.write(90);
    servo4.write(90);
  #endif
}
