#include <Servo.h>
#include "actuator.h"
#include "BixFlight.h"


Servo pitch_servo;
Servo roll_servo1;
Servo roll_servo2;


void servo_setup(){
  pitch_servo.attach(pitch_servo_pin);
  roll_servo1.attach(roll_servo1_pin);
  roll_servo2.attach(roll_servo2_pin);
}

void servo_loop(){
  //pitch_servo.write(act.pwm[1]);
  //roll_servo1.write(act.pwm[2]);
  //roll_servo2.write(act.pwm[3]);

  pitch_servo.write(90);
  roll_servo1.write(90);
  roll_servo2.write(90);
}
