#include <PS3BT.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <Adafruit_PWMServoDriver.h>

PS3BT ps3;

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *motor1 = AFMS.getMotor(1);
Adafruit_DCMotor *motor2 = AFMS.getMotor(2);

void setup() {
  Serial.begin(115200);
  AFMS.begin();
  ps3.begin("00:12:6C:4A:8B:4F");
}

void loop() {
  if (ps3.PS3Connected) {
    ps3.readPS3();
    int leftStickY = ps3.getAnalogHat(LeftHatY);
    int rightStickY = ps3.getAnalogHat(RightHatY);
    
    if (leftStickY > 130) {
      motor1->run(FORWARD);
      motor1->setSpeed(map(leftStickY, 130, 255, 0, 255));
    } else if (leftStickY < 125) {
      motor1->run(BACKWARD);
      motor1->setSpeed(map(leftStickY, 0, 125, 0, 255));
    } else {
      motor1->run(RELEASE);
    }
    
    if (rightStickY > 130) {
      motor2->run(FORWARD);
      motor2->setSpeed(map(rightStickY, 130, 255, 0, 255));
    } else if (rightStickY < 125) {
      motor2->run(BACKWARD);
      motor2->setSpeed(map(rightStickY, 0, 125, 0, 255));
    } else {
      motor2->run(RELEASE);
    }
  }
}