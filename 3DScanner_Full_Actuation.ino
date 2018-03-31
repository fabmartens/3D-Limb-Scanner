#define LINEAR_DIR_PIN 4 // Direction pin for linear motor
#define LINEAR_STEP_PIN 3 // Stepper pin for linear motor
#define ROT_FACE_DIR_PIN 7 // Direction pin for rotational motor closest to face
#define ROT_HAND_DIR_PIN 8 // Direction pin for rotational motor closest to hand
#define ROT_STEP_PIN 9 // Stepper pin for rotational motors

#define BUTTON_PIN 10
#define LIMIT_REST_PIN 5
#define LIMIT_PUSH_PIN 6

#define FORWARD_DELAY 4000
#define BACKWARD_DELAY 1000

#define STEPS_TO_END 12600

void setup(){
  /* Sets step and direction pins to output */
  pinMode(LINEAR_DIR_PIN, OUTPUT);
  pinMode(LINEAR_STEP_PIN, OUTPUT);
  pinMode(ROT_FACE_DIR_PIN, OUTPUT);
  pinMode(ROT_HAND_DIR_PIN, OUTPUT);
  pinMode(ROT_STEP_PIN, OUTPUT);

  /* Sets button pins to inputs */
  pinMode(BUTTON_PIN, INPUT);
  pinMode(LIMIT_REST_PIN, INPUT);
  pinMode(LIMIT_PUSH_PIN, INPUT);

  Serial.begin(9600);

  moveToStart();
}

/* Moves the linear slider to the start position */
void moveToStart() {
  while (digitalRead(LIMIT_PUSH_PIN) == LOW) {
    digitalWrite(LINEAR_DIR_PIN, HIGH); //Writes the direction to the EasyDriver DIR pin. (HIGH is counter clockwise with black wire at B1 on stepper)
    digitalWrite(LINEAR_STEP_PIN, HIGH);
    delayMicroseconds(FORWARD_DELAY);
    digitalWrite(LINEAR_STEP_PIN, LOW);
    delayMicroseconds(FORWARD_DELAY);
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
  return (digitalRead(BUTTON_PIN) == HIGH && digitalRead(LIMIT_PUSH_PIN) == HIGH);
}

/**
 * For stepper motors. Motor will step numSteps time
 * Function will delay for at least 2 x delayTime
 */
void moveSteps(int stepPin, int numSteps, int delayTime) {
  for (int i = 0; i < numSteps; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(delayTime);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(delayTime);
  }
}

/* Runs slider and rotation for the duration of one scan and then resets the slider back to the start position */
void actOnButtons() {
  digitalWrite(LINEAR_DIR_PIN, LOW); //Writes the direction to the EasyDriver DIR pin. (HIGH is counter clockwise with black wire at B1 on stepper)
  digitalWrite(ROT_FACE_DIR_PIN, LOW);
  digitalWrite(ROT_HAND_DIR_PIN, HIGH);
  /* Moves slider all the way to the end, rotating the whole thing as it goes */
  
  /* Moves slider to the end while rotating, in an incremental path */
  for (int i = 0; i < STEPS_TO_END; i++){
    moveSteps(LINEAR_STEP_PIN, 5, FORWARD_DELAY);
    moveSteps(ROT_STEP_PIN, 3, FORWARD_DELAY);
    delay(5000);
  }
    /* Moves slider to the end while rotating, in a helical path */
//  for (int i = 0; i < STEPS_TO_END; i++){
//    digitalWrite(LINEAR_STEP_PIN, HIGH);
//    digitalWrite(ROT_STEP_PIN, HIGH);
//    delayMicroseconds(FORWARD_DELAY);
//    digitalWrite(LINEAR_STEP_PIN, LOW);
//    digitalWrite(ROT_STEP_PIN, LOW);
//    delayMicroseconds(FORWARD_DELAY);
//  }

  delay(2000); //Pauses for 2 seconds (the motor does not need to pause between switching direction, so you can safely remove this)

  /* Resets slider back to the start position, rotation stops */
  digitalWrite(LINEAR_DIR_PIN, HIGH); //Writes the direction to the EasyDriver DIR pin. (HIGH is counter clockwise with black wire at B1 on stepper)
  moveSteps(LINEAR_STEP_PIN, STEPS_TO_END, BACKWARD_DELAY);
  
//  for (int i = 0; i < STEPS_TO_END; i++){
//    digitalWrite(LINEAR_STEP_PIN, HIGH);
//    delayMicroseconds(BACKWARD_DELAY);
//    digitalWrite(LINEAR_STEP_PIN, LOW);
//    delayMicroseconds(BACKWARD_DELAY);
//  }
}
