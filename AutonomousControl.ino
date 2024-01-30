void AutonomousControl1() {
  // put your code here to run in Autonomous control mode
  unsigned long lastActionTime;
  unsigned long myTime;

  Serial.println("in the AutonomousControl function");

  // State machine loop
  while (AutoCurrentState != IDLE) {
    ps2x.read_gamepad();
    switch (AutoCurrentState) {
      case START:
        Serial.println("in Autonomous mode the current state: START");
        // Add START state instructions here
        delay(5000);
        AutoCurrentState = LINEDRIVE;  // Transition to next state
        lastActionTime = millis();     // Record the time when the forward state started
        break;

      case LINEDRIVE:
        Serial.println("in Autonomous mode the current state: LINEDRIVE");
        lineFollowing();
        Serial.println(pRvalue);
        if (ps2x.Button(PSB_START)) {
          Serial.println("Switching to Manual Mode");
          // go to manual state when square button pushed
          RobotCurrentState = MANUAL;
          // reset autonomous state to start state for the next time
          AutoCurrentState = START;
        }
        if (pRvalue < 160) {
          AutoCurrentState = TUNNEL;
        }
        if (pRvalue > 160){
          if (distMM < 12){
            disableMotor(BOTH_MOTORS);
            setMotorSpeed(BOTH_MOTORS, 0);
            AutoCurrentState = GRAVEYARD;
          }
        }
        break;

      case TUNNEL:
        Serial.println("in Autonomous mode the current state: TUNNEL");
        // Add state instructions here
        if (distMM > 20) {
          enableMotor(BOTH_MOTORS);
          setMotorDirection(LEFT_MOTOR, MOTOR_DIR_FORWARD);
          setMotorDirection(RIGHT_MOTOR, MOTOR_DIR_FORWARD);
          setMotorSpeed(BOTH_MOTORS, 10);
        } else {
            turnR();
        }
        if (pRvalue > 160) {
          AutoCurrentState = LINEDRIVE;
        }  // Transition to next state
        if (ps2x.Button(PSB_START)) {
          Serial.println("Switching to Manual Mode");
          // go to manual state when square button pushed
          RobotCurrentState = MANUAL;
          // reset autonomous state to start state for the next time
          AutoCurrentState = START;
        }
        break;

      case GRAVEYARD:
        Serial.println("in Autonomous mode the current state: AUTO_ACTION3");
        clawRelease();
        delay(1000);  
        RobotCurrentState = MANUAL;
        // reset autonomous state to start state for the next time
        AutoCurrentState = START;
        break;

      case AUTO_ACTION4:
        Serial.println("in Autonomous mode the current state: AUTO_ACTION4");
        // Add state instructions here
        delay(1000);              // Placeholder delay
        AutoCurrentState = IDLE;  // Transition to next state
        break;

      default:
        // Handle unknown state, if needed
        break;
    }
  }

  // The code will exit the while loop when IDLE state is reached
  Serial.println("State: IDLE");
  // Add IDLE state instructions here
}