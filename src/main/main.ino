#include <Servo.h>
#include "SR04.h"

Servo servo;
int pos = 0; // Initial servo position. Change this if US-Sensor isn't pointing directly forward!
int distance = 100; // Measured distance to obstacle. Set to some value at start.
int collision = 20; // Collision distance. Change if car needs to stop earlier/later.
int dir = 1;

int servoPin = 9; // PIN: Servo
int echoPin = 11; // PIN: US-Sensor Echo
int trigPin = 12; // PIN: US-Sensor Trig

SR04 sr04 = SR04(echoPin, trigPin);

void setup() {
  servo.attach(servoPin);
  Serial.begin(115200);
  Serial.println("Started");
}

void loop() {
  servo.write(pos);
  delay(100); // TODO: This might not be needed. Maybe remove later?
  
  distance = sr04.Distance();

  if (distance <= collision) { // Check if there are obstacles too close
    moveStop();
    dir = scanDirections();
    if (dir == -1) {
      turnLeft();
    } else {
      turnRight();
    }
  }
}

int scanDirections() {
  // Figure out where to go
  // code here
  return -1;
}

void scanRight() {
  // code here
}

void scanLeft() {
  // code here
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
