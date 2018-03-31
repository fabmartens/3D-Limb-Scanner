int smDirectionPin = 4; //Direction pin
int smStepPin = 3; //Stepper pin

boolean flag1 = false; 
boolean flag2 = false;
boolean flag3 = false;

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

  readButtons();
  actOnButtons();

}

void readButtons() {
  if (digitalRead(limitRest) == HIGH) {
    flag3 = false;
  }
  
  if (digitalRead(buttonPin) == HIGH && digitalRead(limitPush) == HIGH) {
    flag1 = true;
    flag2 = true;
    flag3 = true;
  }
}

void actOnButtons() {
  if (flag1 == true && flag2 == true && flag3 == true) {
    digitalWrite(smDirectionPin, LOW); //Writes the direction to the EasyDriver DIR pin. (HIGH is counter clockwise with black wire at B1 on stepper)
    for (int i = 0; i < stepsToEnd; i++){
      digitalWrite(smStepPin, HIGH);
      delayMicroseconds(forwardDelay);
      digitalWrite(smStepPin, LOW);
      delayMicroseconds(forwardDelay);
    }
    flag1 = false;
 
    delay(4000); //Pauses for a second (the motor does not need to pause between switching direction, so you can safely remove this)
   
    digitalWrite(smDirectionPin, HIGH); //Writes the direction to the EasyDriver DIR pin. (HIGH is counter clockwise with black wire at B1 on stepper)
    for (int i = 0; i < stepsToEnd; i++){
      digitalWrite(smStepPin, HIGH);
      delayMicroseconds(backwardDelay);
      digitalWrite(smStepPin, LOW);
      delayMicroseconds(backwardDelay);
    }
    flag2 = false;
  }
}
