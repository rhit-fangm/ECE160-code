/*
  Calls functions in files:
  FloorCalibration.ino
  AutonomousControl.ino
  PSRemoteControl.ino
  MotorFunctions.ino

  written for the MSP432401 board
  Author: Mandolyn Loveland, Srishti Kamra, Michael Fang
  Last revised: 11/28/2023

***** Hardware Connections: *****
     start button       P3.0
     playstation connections
     brown wire         P1.7 
     orange wire        P1.6 
     yellow wire        P2.3
     blue wire          P6.7
*/

// this is to see if github works
// test 2
//test from rose laptop
// test 3
// changes
// test on Srishti's computer

// Load libraries used
#include "SimpleRSLK.h"
#include <Servo.h>
#include "PS2X_lib.h"
#include <TinyIRremote.h>
#include <Ultrasonic.h>

// Define pin numbers for the button on the PlayStation controller
#define PS2_DAT 14  //P1.7 <-> brown wire
#define PS2_CMD 15  //P1.6 <-> orange wire
#define PS2_SEL 34  //P2.3 <-> yellow wire (also called attention)
#define PS2_CLK 35  //P6.7 <-> blue wire

#define START_BUTTON 18  //P3.0 a push button on top of the breadboard

// set up pins for IR transmission and recieving
#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)
#define IR_RCV_PIN 33
#define IR_TRX_PIN 37  //pin 37 in end
//initialize IR pins
IRsender sendIR(IR_TRX_PIN);
IRreceiver irRX(IR_RCV_PIN);
IRData IRresults;
IRData IRmsg;
uint16_t IRcommand;
int IRaddress;

//ultrasonic sensor pin definitions
const int triggerPin = 9;
const int triggerPin1 = 10;

Ultrasonic bluemySonar(triggerPin);
Ultrasonic redmySonar(triggerPin1);

long distance; // data type long is larger than an integer (int)
//photoresistor pins
const int pResistor = A9;  //NEEDS an ANALOG Input Pin  // dummy pin, will be more LEDs later
int pRvalue = analogRead(pResistor);

// Create an instance of the playstation controller object
PS2X ps2x;

bool isCalibrationComplete = false;


// Define remote mode either playstation controller or IR remote controller
enum RobotState {
  INITIALIZATION,
  MANUAL,
  AUTONOMOUS
};

// Declare and initialize the current state variables
RobotState RobotCurrentState = INITIALIZATION;

// Tuning Parameters
const uint16_t noSpeed = 0;
const uint16_t lowSpeed = 20;
const uint16_t fastSpeed = 30;

const unsigned long movementDuration = 2000;
const uint8_t lineColor = LIGHT_LINE;
uint32_t linePos = getLinePosition();
bool positionBool = false;
Servo myservo;


void setup() {
  Serial.begin(57600);
  Serial.print("Starting up Robot code...... ");

  //run setup code
  setupRSLK();
  //sonar setup
  pinMode(triggerPin, OUTPUT);
  pinMode(triggerPin1, OUTPUT);

  // set pushbutton on breadboard to use internal pullup resistor
  pinMode(START_BUTTON, INPUT_PULLUP);
  setupWaitBtn(START_BUTTON);
  setupLed(RED_LED);


  if (sendIR.initIRSender()) {
    Serial.println(F("Ready to Transmit NEC IR signals on pin " STR(IR_TRX_PIN)));
  } else {
    Serial.println("Initialization of IR Transmitter Failed.");
    while (1) { ; }
  }
  delay(500);
  enableTXLEDFeedback(GREEN_LED);
  IRmsg.protocol = NEC;
  IRmsg.address = IRaddress;
  IRmsg.command = IRcommand;
  IRmsg.isRepeat = false;
  // IR Receiver
  if (irRX.initIRReceiver()) {
    Serial.println(F("Ready to Receiver NEC IR Signals at Pin " STR(IR_RCV_PIN)));
  } else {
    Serial.println("Initializaiton of IR receiver Failed.");
    while (1) { ; }
  }
  delay(500);
  enableRXLEDFeedback(BLUE_LED);
  //photoresistor initialization
  pinMode(pResistor, INPUT);
  //attach servo
  myservo.attach(SRV_0);
  // Initialize Playstation Controller
  bool pressures = false;
  bool rumble = false;
  int error = 1;

  while (error) {
    error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);

    if (error == 0)
      Serial.print("Found Controller, configured successful ");

    else if (error == 1)
      Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");

    else if (error == 2)
      Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");

    else if (error == 3)
      Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
    delayMicroseconds(1000 * 1000);
  }
}
void loop() {
  // Read input from PlayStation controller
  ps2x.read_gamepad();
  // Perform actions based on the current state
  executeStateActions();

  if (ps2x.Button(PSB_L1)) {
    votive();
  }
  if (ps2x.Button(PSB_R1)) {
    catrina();
  }
}
void executeStateActions() {
  switch (RobotCurrentState) {
    case INITIALIZATION:
      // Perform actions for intialization state
      Serial.println("Initialization Mode");
      if (isCalibrationComplete == false) {
        floorCalibration();
        isCalibrationComplete = true;
      }
      if (ps2x.ButtonPressed(PSB_SELECT)) {
        RobotCurrentState = AUTONOMOUS;
      }
      if (ps2x.ButtonPressed(PSB_START)) {
        RobotCurrentState = MANUAL;
      }

      break;
    case MANUAL:
      // Perform actions for the manual state
      Serial.println("Manual Mode");
      RemoteControlPlaystation();
      if (ps2x.ButtonPressed(PSB_SELECT)) {
        RobotCurrentState = AUTONOMOUS;
      }
      // Add any additional actions for the manual state
      break;

    case AUTONOMOUS:
      // Perform actions for the autonomous state
      Serial.println("Autonomous Mode");
      AutonomousControl();  //* needs to work on
      if (ps2x.ButtonPressed(PSB_START)) {
        RobotCurrentState = MANUAL;
      }
      // Add any additional actions for the autonomous state
      break;
  }
}
