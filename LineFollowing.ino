void lineFollowing() {
  uint32_t linePos = getLinePosition();
  distIN = readSharpDistIN(SensorPos);
  int lineDirection = 0;
  if ((linePos > 3600) && (linePos < 4475)) {
    enableMotor(LEFT_MOTOR);
    enableMotor(RIGHT_MOTOR);
    setMotorDirection(LEFT_MOTOR, MOTOR_DIR_FORWARD);
    setMotorDirection(RIGHT_MOTOR, MOTOR_DIR_FORWARD);
    setMotorSpeed(LEFT_MOTOR, 10);
    setMotorSpeed(RIGHT_MOTOR, 12);
    Serial.println(linePos);
    //Adjust Right
  }
  else if ((linePos > 4525) && (linePos < 5400)) {
    enableMotor(LEFT_MOTOR);
    enableMotor(RIGHT_MOTOR);
    setMotorDirection(LEFT_MOTOR, MOTOR_DIR_FORWARD);
    setMotorDirection(RIGHT_MOTOR, MOTOR_DIR_FORWARD);
    setMotorSpeed(LEFT_MOTOR, 12);
    setMotorSpeed(RIGHT_MOTOR, 10);
    Serial.println(linePos);

    //Turn Right
  }
  else if (linePos < 3600) {  //turn LEFT
    if (positionBool == false) {
      setMotorSpeed(LEFT_MOTOR, 0);
      setMotorSpeed(RIGHT_MOTOR, 0);
      delay(500);
      enableMotor(LEFT_MOTOR);
      setMotorDirection(LEFT_MOTOR, MOTOR_DIR_BACKWARD);
      setMotorSpeed(LEFT_MOTOR, 16);
      setMotorSpeed(RIGHT_MOTOR, 16);
    }
  }

  //Turn Left
  else if (linePos > 5400) {  //turn RIGHT
    if (positionBool == false) {
      setMotorSpeed(LEFT_MOTOR, 0);
      setMotorSpeed(RIGHT_MOTOR, 0);
      delay(500);
      enableMotor(RIGHT_MOTOR);
      setMotorDirection(RIGHT_MOTOR, MOTOR_DIR_BACKWARD);
      enableMotor(LEFT_MOTOR);
      setMotorDirection(LEFT_MOTOR, MOTOR_DIR_FORWARD);
      setMotorSpeed(LEFT_MOTOR, 16);
      setMotorSpeed(RIGHT_MOTOR, 16);
    }
  }
    if ((distIN < stopDistance) && (linePosition > 1000) && (linePosition < 7000)) {
    setMotorSpeed(BOTH_MOTORS, 0);
    openClaw();
    delay(1000);
    state = MANUAL;
  }

  //Go straight
  else {  // go straight
    setMotorSpeed(LEFT_MOTOR, 12);
    setMotorSpeed(RIGHT_MOTOR, 12);
    Serial.println(linePos);
  }
}