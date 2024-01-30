/*
  MotorFunctions.ino - Arduino Sketch for Motor Control
  
  Description:
  This sketch provides functions for controlling a RLSK robot, allowing the
  motors to move forward and stop.

  Functions:
  1. void forward()
    - Activates the motor to move forward.
  2. void backward()
    - Activates the motor to move backward
  3. void spinInPlaceCCW()
    - Activates the motor to spin counterclockwise
  4. void spinInPlaceCW()
    - Activates the motor to spin clockwise
  5. void turnR()
    - Activates the motor to turn right
  6. void turn:()
    - Activates the motor to turn left
  7. void clawGrab()
    - Activates the servo to close claw
  8. void clawRelease()
    - Activates the motor to open claw

  Created by: Mandolyn Loveland
  Version: 2.0
*/
int pos = 0;  // variable to store the servo position

/* Moves robot forward: both motors forward same speed */
void forward() {
  enableMotor(BOTH_MOTORS);
  setMotorDirection(LEFT_MOTOR, MOTOR_DIR_FORWARD);
  setMotorDirection(RIGHT_MOTOR, MOTOR_DIR_FORWARD);
  setMotorSpeed(BOTH_MOTORS, fastSpeed);
}
/* Moves robot backward: both motors backward same speed */
void backward() {
  enableMotor(BOTH_MOTORS);
  setMotorDirection(LEFT_MOTOR, MOTOR_DIR_BACKWARD);
  setMotorDirection(RIGHT_MOTOR, MOTOR_DIR_BACKWARD);
  setMotorSpeed(BOTH_MOTORS, lowSpeed);
}
void spinInPlaceCCW() {
  enableMotor(BOTH_MOTORS);
  setMotorDirection(LEFT_MOTOR, MOTOR_DIR_BACKWARD);
  setMotorDirection(RIGHT_MOTOR, MOTOR_DIR_FORWARD);
  setMotorSpeed(RIGHT_MOTOR, lowSpeed);
  setMotorSpeed(LEFT_MOTOR, fastSpeed);
}
void spinInPlaceCW() {
  enableMotor(BOTH_MOTORS);
  setMotorDirection(LEFT_MOTOR, MOTOR_DIR_FORWARD);
  setMotorDirection(RIGHT_MOTOR, MOTOR_DIR_BACKWARD);
  setMotorSpeed(RIGHT_MOTOR, fastSpeed);
  setMotorSpeed(LEFT_MOTOR, lowSpeed);
}
void turnR() {
  enableMotor(BOTH_MOTORS);
  setMotorDirection(LEFT_MOTOR, MOTOR_DIR_FORWARD);
  setMotorDirection(RIGHT_MOTOR, MOTOR_DIR_FORWARD);
  setMotorSpeed(RIGHT_MOTOR, lowSpeed);
  setMotorSpeed(LEFT_MOTOR, fastSpeed);
}
void turnL() {
  enableMotor(BOTH_MOTORS);
  setMotorDirection(LEFT_MOTOR, MOTOR_DIR_FORWARD);
  setMotorDirection(RIGHT_MOTOR, MOTOR_DIR_FORWARD);
  setMotorSpeed(RIGHT_MOTOR, fastSpeed);
  setMotorSpeed(LEFT_MOTOR, lowSpeed);
}
/* Stops robot forward: both motors disabled */
void stop() {
  disableMotor(BOTH_MOTORS);
}
/* Claw Functions */
void clawGrab() {
  for (pos = 40; pos < 140; pos += 3)  // goes from 0 degrees to 180 degrees in 3 degree steps
  {                                    
    myservo.write(pos);                // tell servo to go to position in variable 'pos'
  }
}
void clawRelease() {
  for (pos = 140; pos >= 41; pos -= 3)  // goes from 180 degrees to 0 degrees in 3 degree steps
  {
    myservo.write(pos);  // tell servo to go to position in variable 'pos'
  }
}
