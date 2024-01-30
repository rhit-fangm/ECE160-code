void catrina() {
  if (irRX.decodeIR(&IRresults)) {
    Serial.print("A=0x");
    Serial.print(IRresults.address, HEX);
    Serial.print(" C=0x");
    Serial.print(IRresults.command, HEX);
    // IRresults.command = IRcommand;
    IRcommand = IRresults.command;
  } else {
    Serial.println("No Data Recieved for Skull");
  }
  IRmsg.address = 0xCE;
  IRmsg.command = IRcommand;
  sendIR.write(&IRmsg);
  Serial.println("Transmitted Address:  ");
  Serial.println(IRmsg.address, HEX);
  Serial.println("Transmitted Command:  ");
  Serial.println(IRmsg.command, HEX);

  delay(500);
}
void votive() {
  IRmsg.address = 0xEE;
  IRmsg.command = 0xA0;
  sendIR.write(&IRmsg);
  delay(500);
  Serial.println("VOTIVE");
  Serial.print("Address:  ");
  Serial.println(IRmsg.address);
  Serial.print("Command:  ");
  Serial.println(IRmsg.command);
}