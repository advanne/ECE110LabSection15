// Basic communication code for EGR 110 Lab Section 15
// PLEASE CHANGE ALL "TODO"S

// TODO: THIS WILL CHANGE BASED ON YOUR ROBOT'S CONFIGURATION
// Choose a character unique to your team's robot
#define UNIQUE_ROBOT_CODE '5'

// Define pins for XBee serial
#define Rx 17 //define transmitting pin
#define Tx 16 //define recieving pin

// TODO: THIS WILL CHANGE BASED ON YOUR ROBOT'S CONFIGURATION
// Define pins for button and LED inputs/outputs
#define BUTTON_INPUT 10
#define SEND_LED_OUTPUT 5
#define RECEIVE_LED_OUTPUT 7

void setup() {
  pinMode (BUTTON_INPUT, INPUT); // set up button pin
  pinMode (SEND_LED_OUTPUT, OUTPUT); // set up LED indicating signal sent
  pinMode (RECEIVE_LED_OUTPUT, OUTPUT); // set up LED indicating signal received

  pinMode(47, INPUT);
  pinMode(49, INPUT);
  pinMode(51, INPUT);
  pinMode(53, INPUT);
  pinMode(52, INPUT);
  
  Serial.begin(9600); // set up keyboard serial
  Serial2.begin(9600); // set up XBee serial
  
  delay(500);
}

void loop() {

  // Memory for serial printing string formatting
  char buf[32];

  // If button pressed, send signal
  if (digitalRead(BUTTON_INPUT)) {
    
    // Send signal
    char outgoing = UNIQUE_ROBOT_CODE;
    Serial2.print(outgoing);

    // Print signal to serial
    sprintf(buf, "Broadcast signal %c", outgoing);
    Serial.println(buf);

    // Blink send indicator LED
    digitalWrite(SEND_LED_OUTPUT, HIGH);
    delay(1500);
    digitalWrite(SEND_LED_OUTPUT, LOW);
  }

  // If signal received from XBee serial
  if (Serial2.available()){

    // Receive signal
    char incoming = Serial2.read();

    // Check that signal is not coming from this robot
    if (incoming != UNIQUE_ROBOT_CODE) {

      // Print signal to serial
      sprintf(buf, "Received signal %d", incoming);
      Serial.println(buf);
      
      // Blink receive indicator LED
      digitalWrite(RECEIVE_LED_OUTPUT, HIGH);
      delay(1500);
      digitalWrite(RECEIVE_LED_OUTPUT, LOW);
    }
  }

  // Throttling
  delay(50);
}
