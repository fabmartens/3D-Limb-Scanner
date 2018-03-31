// #define these too
int smDirectionPin = 4; // Direction pin for linear motor
int smStepPin = 3; // Stepper pin for linear motor
int rotMotorFaceDirectionPin = 7; // Direction pin for rotational motor closest to face
int rotMotorHandDirectionPin = 8; // Direction pin for rotational motor closest to hand
int rotStepPin = 9; // Stepper pin for rotational motors

// #define and take out = for all constants
int buttonPin = 10;
int limitRest = 5;
int limitPush = 6;

int forwardDelay = 1000;
int backwardDelay = 1000;

int stepsToEnd = 12600;

void setup(){
  /*Sets all pin to output; the microcontroller will send them(the pins) bits, it will not expect to receive any bits from thiese pins.*/
  pinMode(smDirectionPin, OUTPUT);
  pinMode(smStepPin, OUTPUT);
  pinMode(rotMotorFaceDirectionPin, OUTPUT);
  pinMode(rotMotorHandDirectionPin, OUTPUT);
  pinMode(rotStepPin, OUTPUT);

  pinMode(buttonPin, INPUT);
  pinMode(limitRest, INPUT);
  pinMode(limitPush, INPUT);

  
 
  Serial.begin(9600);

  moveToStart();
}

void moveToStart() {
  while (digitalRead(limitPush) == LOW) {
    digitalWrite(smDirectionPin, HIGH); //Writes the direction to the EasyDriver DIR pin. (HIGH is counter clockwise with black wire at B1 on stepper)
    digitalWrite(smStepPin, HIGH);
    delayMicroseconds(forwardDelay);
    digitalWrite(smStepPin, LOW);
    delayMicroseconds(forwardDelay);
  }
}

void loop(){
  
  if (readButtons()) {
    actOnButtons();
  }
  
}


boolean readButtons(){
  return (digitalRead(buttonPin) == HIGH && digitalRead(limitPush) == HIGH);
}

void actOnButtons() {
    digitalWrite(smDirectionPin, LOW); //Writes the direction to the EasyDriver DIR pin. (HIGH is counter clockwise with black wire at B1 on stepper)
    digitalWrite(rotMotorFaceDirectionPin, LOW);
    digitalWrite(rotMotorHandDirectionPin, HIGH);
    for (int i = 0; i < stepsToEnd; i++){
      digitalWrite(smStepPin, HIGH);
      digitalWrite(rotStepPin, HIGH);
      delayMicroseconds(forwardDelay);
      digitalWrite(smStepPin, LOW);
      digitalWrite(rotStepPin, LOW);
      delayMicroseconds(forwardDelay);
    }
 
    delay(4000); //Pauses for 4 seconds (the motor does not need to pause between switching direction, so you can safely remove this)
   
    digitalWrite(smDirectionPin, HIGH); //Writes the direction to the EasyDriver DIR pin. (HIGH is counter clockwise with black wire at B1 on stepper)
    for (int i = 0; i < stepsToEnd; i++){
      digitalWrite(smStepPin, HIGH);
      delayMicroseconds(backwardDelay);
      digitalWrite(smStepPin, LOW);
      delayMicroseconds(backwardDelay);
    }
}
