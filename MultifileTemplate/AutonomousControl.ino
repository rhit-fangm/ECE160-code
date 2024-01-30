void AutonomousControl() {
  Serial.print(pRvalue);
  pRvalue = analogRead(pResistor);
  if (pRvalue > 150){
    lineFollowing();
  } else if ((distance < 10 || distance1 < 10) && pRvalue < 150){
      turnR();
    delay(5000);
  } else if((distance < 5 || distance1 < 5) && pRvalue > 150){
    disableMotor(BOTH_MOTORS);
    setMotorSpeed(BOTH_MOTORS, noSpeed);
    clawRelease();
    RobotCurrentState = MANUAL;
  } else{
    lineFollowing();
}


}