#include <AccelStepper.h>
#include <MultiStepper.h>
#include <Servo.h>
#define MotorInterfaceType 4
#define PI 3.1415926535897932384626433832795

// Connect pins 1-4 of two ULN2003 stepper drivers, the first to pins 8-11 and
// the second to pins 2-5 of the Arduino Uno, respectively. (The permutations
// of the pin orders below are idiosyncrasies of the software library; ignore
// these permuted orders and wire pins in ascending order.)
AccelStepper X(MotorInterfaceType, 8, 10, 9, 11);
AccelStepper Y(MotorInterfaceType, 2, 4, 3, 5);
MultiStepper XY;

long sq[6][2] = {{1000, 1000},{2000, 1000}, {2000, 3000}, {0, 3000}, {0, 1000}, {1000, 1000}};

long start[2] = {0, 0};
long pos_xy[2] = {0, 0};




void setup() {
  X.setMaxSpeed(500.0);
  Y.setMaxSpeed(500.0);

  XY.addStepper(X);
  XY.addStepper(Y);

  Serial.begin(9600);
  circle_square();
  return_to_start();
}


void circle_square() {
  int i = 0;
  delay(2000);

  for(i = 0; i < 6; i++) {
    XY.moveTo(sq[i]);
    while (X.distanceToGo() != 0 || Y.distanceToGo() != 0) {
      XY.runSpeedToPosition();
    }
  }
  i = 0;
  double angle = PI/360;
  for(int i=0; i<720; i++){
    long point[2] = {-1000 * sin(angle * i)+ 1000, -1000 * cos(angle * i) + 2000};
    XY.moveTo(point);
    while (X.distanceToGo() != 0 || Y.distanceToGo() != 0) {
      XY.runSpeedToPosition();
    }
  }
}


void return_to_start(){
  delay(2000);
  XY.moveTo(start);
    while (X.distanceToGo() != 0 || Y.distanceToGo() != 0) {
      XY.runSpeedToPosition();
    }
}

// Enter coordinates through the serial interface, e.g. "1000 5000" followed by
// hitting the enter button.
void loop() {

  if (X.distanceToGo() == 0) {
     while (Serial.available() == 0) {}

     String s;
     pos_xy[0] = Serial.parseInt();
     pos_xy[1] = Serial.parseInt();
     s = Serial.readString();
     Serial.print("x = ");
     Serial.print(pos_xy[0]);
     Serial.print("  y = ");
     Serial.print(pos_xy[1]);
     Serial.println(s);
     XY.moveTo(pos_xy);
  }

  XY.runSpeedToPosition();
  return_to_start();
}
