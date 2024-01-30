/* RemoteControlPlaystation() function
This function uses a playstation controller and the PLSK libraray with
an RLSK robot using to implement remote controller. 

A few actions are programed for an example. 

Button control map:
DPAD UP - Forwards
DPAD Down - Backwards
DPAD Right - Turn right
DPAD Left - Turn left
Cross - Stop
Circle - Spin CCW
Square - Spin CW
Bumper R2 - Open Claw
Bumper L2 - Close Claw

*/
void RemoteControlPlaystation() {
  // put your code here to run in remote control mode
  if (ps2x.Button(PSB_PAD_UP)) {
    Serial.println("Moving forwards...");
    forward();
  } else if (ps2x.Button(PSB_PAD_DOWN)) {
    Serial.println("Moving backwards...");
    backward();
  } else if (ps2x.Button(PSB_PAD_RIGHT)) {
    Serial.println("Turning right...");
    turnR();
  } else if (ps2x.Button(PSB_PAD_LEFT)) {
    Serial.println("Turning left...");
    turnL();
  } else if (ps2x.Button(PSB_CROSS)) {
    Serial.println("Stopping...");
    stop();
  } else if (ps2x.Button(PSB_CIRCLE)) {
    Serial.println("Spinning left...");
    spinInPlaceCCW();
  } else if (ps2x.Button(PSB_SQUARE)) {
    Serial.println("Spinning right...");
    spinInPlaceCW();
  } else if (ps2x.Button(PSB_R2)) {
    Serial.println("Claw opening...");
    clawGrab();
  } else if (ps2x.Button(PSB_L2)) {
    Serial.println("Claw closing...");
    clawRelease();
  }
}