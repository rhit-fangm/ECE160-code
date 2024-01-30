void floorCalibration(){
    /* Place Robot On Floor (no line) */
    delay(2000);
    Serial.println("Push left button on Launchpad to begin calibration.");
    Serial.println("Make sure the robot is on the floor away from the line.\n");
    /* Wait until button is pressed to start robot */
    waitBtnPressed(START_BUTTON, RED_LED);

    delay(500);
    Serial.println("Running calibration on floor");

    /* Set both motors direction forward */
    setMotorDirection(BOTH_MOTORS, MOTOR_DIR_FORWARD);
    /* Enable both motors */
    enableMotor(BOTH_MOTORS);
    /* Set both motors speed 20 */
    setMotorSpeed(BOTH_MOTORS, 20);

    /* Must be called prior to using getLinePosition() or readCalLineSensor() */
    calibrateLineSensor(lineColor);

    /* Disable both motors */
    disableMotor(BOTH_MOTORS);

    Serial.println("Reading floor values complete");

    Serial.println("Push left button on Launchpad to begin line following.");
    Serial.println("Make sure the robot is on the line.\n");
    /* Wait until button is pressed to start robot */
    waitBtnPressed(START_BUTTON, RED_LED);
    delay(1000);

    enableMotor(BOTH_MOTORS);
}
