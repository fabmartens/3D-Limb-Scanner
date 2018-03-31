#define smDirectionPin 4 // Direction pin for linear motor
#define smStepPin 3 // Stepper pin for linear motor
#define rotMotorFaceDirectionPin 7 // Direction pin for rotational motor closest to face
#define rotMotorHandDirectionPin 8 // Direction pin for rotational motor closest to hand
#define rotStepPin 9 // Stepper pin for rotational motors

#define buttonPin 10
#define limitRest 5
#define limitPush 6

#define forwardDelay 4000
#define backwardDelay 1000

#define stepsToEnd 12600

void setup(){
  /* Sets step and direction pins to output */
  pinMode(smDirectionPin, OUTPUT);
  pinMode(smStepPin, OUTPUT);
  pinMode(rotMotorFaceDirectionPin, OUTPUT);
  pinMode(rotMotorHandDirectionPin, OUTPUT);
  pinMode(rotStepPin, OUTPUT);

  /* Sets button pins to inputs */
  pinMode(buttonPin, INPUT);
  pinMode(limitRest, INPUT);
  pinMode(limitPush, INPUT);

  Serial.begin(9600);

  moveToStart();
}

/* Moves the linear slider to the start position */
void moveToStart() {
  while (digitalRead(limitPush) == LOW) {
    digitalWrite(smDirectionPin, HIGH); //Writes the direction to the EasyDriver DIR pin. (HIGH is counter clockwise with black wire at B1 on stepper)
    digitalWrite(smStepPin, HIGH);
    delayMicroseconds(forwardDelay);
    digitalWrite(smStepPin, LOW);
    delayMicroseconds(forwardDelay);
  }
}

/* Main loop once slider is set to start position */
void loop(){
  
  if (readButtons()) {
    actOnButtons();
  }
  
}

/* Reads buttons */
boolean readButtons(){
  return (digitalRead(buttonPin) == HIGH && digitalRead(limitPush) == HIGH);
}

/* Runs slider and rotation for the duration of one scan and then resets the slider back to the start position */
void actOnButtons() {
  digitalWrite(smDirectionPin, LOW); //Writes the direction to the EasyDriver DIR pin. (HIGH is counter clockwise with black wire at B1 on stepper)
  digitalWrite(rotMotorFaceDirectionPin, LOW);
  digitalWrite(rotMotorHandDirectionPin, HIGH);
  /* Moves slider all the way to the end, rotating the whole thing as it goes */
  for (int i = 0; i < stepsToEnd; i++){
    digitalWrite(smStepPin, HIGH);
    digitalWrite(rotStepPin, HIGH);
    delayMicroseconds(forwardDelay);
    digitalWrite(smStepPin, LOW);
    digitalWrite(rotStepPin, LOW);
    delayMicroseconds(forwardDelay);
  }

  delay(2000); //Pauses for 2 seconds (the motor does not need to pause between switching direction, so you can safely remove this)

  /* Resets slider back to the start position, rotation stops */
  digitalWrite(smDirectionPin, HIGH); //Writes the direction to the EasyDriver DIR pin. (HIGH is counter clockwise with black wire at B1 on stepper)
  for (int i = 0; i < stepsToEnd; i++){
    digitalWrite(smStepPin, HIGH);
    delayMicroseconds(backwardDelay);
    digitalWrite(smStepPin, LOW);
    delayMicroseconds(backwardDelay);
  }
}
