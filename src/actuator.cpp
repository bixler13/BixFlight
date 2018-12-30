#include <servo.h>
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
  pitch_servo.write(pitch_servo_angle);
  roll_servo1.write(roll_servo_angle);
  roll_servo2.write(roll_servo2_angle);
}
