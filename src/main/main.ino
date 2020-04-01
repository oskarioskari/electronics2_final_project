#include <Servo.h>
#include "SR04.h"

Servo servo;
Servo l_motor;
Servo r_motor;

// These values can be changed if needed:
int turnDelay = 1000; // How long the car will turn. Exact value needs to be calculated once the design for wheels is finalized.
int reverseDelay = 1000; // How long the car will reverse each time. Change if needed.
int collision = 20; // Collision distance. Change if car needs to stop earlier/later.

int pos = 90; // Servo position.
int r_speed = 90; // Right motor speed.
int l_speed = 90; // Left motor speed.

int distance = 100;
int dir = 1;
int stuck = 0;

// Pin numbers:
int servoPin = 9;  // PIN: Servo
int echoPin = 11;  // PIN: US-Sensor Echo
int trigPin = 12;  // PIN: US-Sensor Trig
int lMotorPin = 5; // PIN: Left Motor
int rMotorPin = 6; // PIN: Right Motor

SR04 sr04 = SR04(echoPin, trigPin);

void setup() {
  servo.attach(servoPin);
  l_motor.attach(lMotorPin);
  r_motor.attach(rMotorPin);
  servo.write(pos);
  l_motor.write(l_speed);
  r_motor.write(r_speed);
  Serial.begin(115200);
  Serial.println("Started");
}

void loop() {
  delay(2000); // TODO: This might not be needed. Useful when debugging.

  distance = sr04.Distance();
  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance <= collision || stuck == 1) { // Check if there are obstacles too close or if the car is stuck.
    moveStop();
    dir = scanDirections();
    if (dir == -1) {
      stuck = 0;
      turnLeft();
    } else if (dir == 1) {
      stuck = 0;
      turnRight();
    } else if (dir == 0) { // If stuck, reverse.
      stuck = 1;
      moveBackward();
    }
  } else {
    moveForward();
  }
}

int scanDirections() {
  int right = scanRight();
  Serial.println(right);
  int left  = scanLeft();
  Serial.println(left);
  
  if (right>left && right>collision) {
    return 1;
  } else if (right<left && left>collision){
    return -1;
  } else {
    return 0;
  }
}

int scanRight() {
  Serial.println("Right");
  pos = pos-90;
  servo.write(pos);
  delay(1000);
  int dist_r = sr04.Distance();
  delay(100);
  pos = pos+90;
  servo.write(pos);
  delay(1000);
  return dist_r;
}

int scanLeft() {
  Serial.println("Left");
  pos = pos+90;
  servo.write(pos);
  delay(1000);
  int dist_l = sr04.Distance();
  delay(100);
  pos = pos-90;
  servo.write(pos);
  delay(1000);
  return dist_l;
}

void moveCar() {
  l_motor.write(l_speed);
  r_motor.write(r_speed);
}

void moveForward() {
  Serial.println("Move Forward");
  l_speed = 150;
  r_speed = 30;
  moveCar();
}

void moveBackward() {
  Serial.println("Move Backward");
  l_speed = 30;
  r_speed = 150;
  moveCar();
  delay(reverseDelay); // Adjusts the distance the car will reverse.
  moveStop();
}

void moveStop() {
  Serial.println("Stop");
  l_speed = 90;
  r_speed = 90;
  moveCar();
}

void turnRight() {
  Serial.println("Turn Right");
  l_speed = 150;
  r_speed = 90;
  moveCar();
  delay(turnDelay);
  moveStop();
}
void turnLeft() {
  Serial.println("Turn Left");
  l_speed = 90;
  r_speed = 30;
  moveCar();
  delay(turnDelay);
  moveStop();
}
