#include <Servo.h>
#include "SR04.h"

Servo servo;
int pos = 90; // Current servo position.
int distance = 100; // Measured distance to obstacle. Set to some value at start.
int collision = 20; // Collision distance. Change if car needs to stop earlier/later.
int dir = 1;

int servoPin = 9; // PIN: Servo
int echoPin = 11; // PIN: US-Sensor Echo
int trigPin = 12; // PIN: US-Sensor Trig

SR04 sr04 = SR04(echoPin, trigPin);

void setup() {
  servo.attach(servoPin);
  servo.write(pos);
  Serial.begin(115200);
  Serial.println("Started");
}

void loop() {
  delay(2000); // TODO: This might not be needed. Useful when debugging.

  distance = sr04.Distance();
  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance <= collision) { // Check if there are obstacles too close
    Serial.println("Stop");
    moveStop();
    dir = scanDirections();
    if (dir == -1) {
      Serial.println("Turn Left");
      turnLeft();
    } else {
      Serial.println("Turn Right");
      turnRight();
    }
  } else {
    Serial.println("Move Forward");
    moveForward();
  }
}

int scanDirections() {
  int right = scanRight();
  Serial.println(right);
  int left  = scanLeft();
  Serial.println(left);
  
  if (right > left) {
    return 1;
  } else {
    return -1;
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

void moveForward() {
  // Move the car forward
  // code here
}

void moveBackward() {
  // Move the car backward
  // code here
}

void moveStop() {
  // Stop the car
  // code here
}

void turnRight() {
  // code here
}
void turnLeft() {
  // code here
}
