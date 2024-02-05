void AutonomousControl() {

  pRvalue = analogRead(pResistor);
  Serial.print(" Light value: ");
  Serial.print(pRvalue);
  Serial.print(" ");

  distance = bluemySonar.read(CM); // use the Ultrasonic function read to get distance
  distance1 = redmySonar.read(CM);
  Serial.print(" Left value: ");
  Serial.print(distance1);
  Serial.print(" ");
  Serial.print(" Right value: ");
  Serial.print(distance);
  Serial.print(" ");

  if ((distance < 15) && (pRvalue > 1000)) {
    stop();
    RobotCurrentState = MANUAL;
  } else if (pRvalue > 1000){
    distance = bluemySonar.read(CM); // use the Ultrasonic function read to get distance
    distance1 = redmySonar.read(CM);
    lineFollowing();
  } else {
    distance = bluemySonar.read(CM); // use the Ultrasonic function read to get distance
    distance1 = redmySonar.read(CM);
    tunnel_navigation();
  }
}

void tunnel_navigation(){
  if (distance < 20) {
    while (distance1 > 15) {
      enableMotor(BOTH_MOTORS);
      setMotorDirection(LEFT_MOTOR, MOTOR_DIR_FORWARD);
      setMotorDirection(RIGHT_MOTOR, MOTOR_DIR_BACKWARD);
      setMotorSpeed(RIGHT_MOTOR, lowSpeed);
      setMotorSpeed(LEFT_MOTOR, lowSpeed);
      distance = bluemySonar.read(CM); // use the Ultrasonic function read to get distance
      distance1 = redmySonar.read(CM);
    }
  }
  else if (distance > 15 && distance1 < 10){
    enableMotor(BOTH_MOTORS);
    setMotorDirection(LEFT_MOTOR, MOTOR_DIR_FORWARD);
    setMotorDirection(RIGHT_MOTOR, MOTOR_DIR_FORWARD);
    setMotorSpeed(RIGHT_MOTOR, lowSpeed);
    setMotorSpeed(LEFT_MOTOR, 60);
  } else {
    enableMotor(BOTH_MOTORS);
    setMotorDirection(LEFT_MOTOR, MOTOR_DIR_FORWARD);
    setMotorDirection(RIGHT_MOTOR, MOTOR_DIR_FORWARD);
    setMotorSpeed(BOTH_MOTORS, lowSpeed);
  }
}