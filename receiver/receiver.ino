//

int outputSignalPin = 13;
int inputSignalPin = 12;
int disablePin = 11;
boolean startBomb = false;
boolean firstTimeStartingBomb = true;


int digit1 = A5; //PWM Display pin 7
int digit2 = A2; //PWM Display pin 10
int digit3 = A1; //PWM Display pin 11
int digit4 = 5; //PWM Display pin 6

int segA = A4; //Display pin 8
int segB = A0; //Display pin 12
int segC = 3; //Display pin 4
int segD = 1; //Display pin 2
int segE = 0; //Display pin 1
int segF = A3; //Display pin 9
int segG = 4; //Display pin 5
int point = 2; //Display pin 3

int wire1 = 7;
int wire2 = 8;
int wire3 = 9;
int wire4 = 10;

int speedFlag = 0;
int timeCounter = 300; // 5 min, 300 sec 65 min, 3900sec
int change = 0;
long lastTime = 0;
unsigned long timePassed = 0;

void setup() {
  pinMode(outputSignalPin, OUTPUT);
  pinMode(inputSignalPin, INPUT_PULLUP);
  pinMode(disablePin, OUTPUT);

  pinMode(segA, OUTPUT);
  pinMode(segB, OUTPUT);
  pinMode(segC, OUTPUT);
  pinMode(segD, OUTPUT);
  pinMode(segE, OUTPUT);
  pinMode(segF, OUTPUT);
  pinMode(segG, OUTPUT);

  pinMode(digit1, OUTPUT);
  pinMode(digit2, OUTPUT);
  pinMode(digit3, OUTPUT);
  pinMode(digit4, OUTPUT);

  pinMode(point, OUTPUT);

  pinMode(wire1, INPUT_PULLUP);
  pinMode(wire2, INPUT_PULLUP);
  pinMode(wire3, INPUT_PULLUP);
  pinMode(wire4, INPUT_PULLUP);
  pinMode(inputSignalPin, INPUT);
}

void loop() {

  
  if (digitalRead(inputSignalPin)) {
    startBomb = true;
  }
  
  while (startBomb) {
    if (firstTimeStartingBomb) {
      timePassed = millis();
      firstTimeStartingBomb = false;
    }
    if (timeCounter <= 0) gameOver();
    if (digitalRead(wire3)) gameOver();
    if (digitalRead(wire2)) defused(timeCounter);

    switch (speedFlag) {

      case 0:
        if (digitalRead(wire1)) speedFlag = 1;
        if (digitalRead(wire4)) speedFlag = 2;

        change = (millis() - timePassed  - lastTime) / 1000;
        if (change) {
          timeCounter -= change;
          lastTime = millis() - timePassed;
        }
        break;

      case 1:
        if (digitalRead(wire4)) speedFlag = 3;
        change = (millis() - timePassed - lastTime) / 500;
        if (change) {
          timeCounter -= change;
          lastTime = millis() - timePassed ;
        }
        break;

      case 2:
        if (digitalRead(wire1)) speedFlag = 3;
        change = (millis() - timePassed  - lastTime) / 500;
        if (change) {
          timeCounter -= change;
          lastTime = millis() - timePassed ;
        }
        break;

      case 3:
        change = (millis() - timePassed  - lastTime) / 250;
        if (change) {
          timeCounter -= change;
          lastTime = millis() - timePassed ;
        }
        break;
    }

    digitalWrite(outputSignalPin, HIGH);
    digitalWrite(disablePin, LOW);
    displayNumber((timeCounter / 60) * 100 + timeCounter % 60);
    digitalWrite(outputSignalPin, LOW);
  }

}

void displayNumber(int toDisplay) {
#define DISPLAY_BRIGHTNESS  500

#define DIGIT_ON  LOW
#define DIGIT_OFF  HIGH

  for (int digit = 4 ; digit > 0 ; digit--) {

    //Turn on a digit for a short amount of time
    switch (digit) {
      case 1:
        digitalWrite(digit1, DIGIT_ON);
        break;
      case 2:
        digitalWrite(digit2, DIGIT_ON);
        digitalWrite(point, HIGH);
        break;
      case 3:
        digitalWrite(digit3, DIGIT_ON);
        break;
      case 4:
        digitalWrite(digit4, DIGIT_ON);
        break;
    }

    //Turn on the right segments for this digit
    lightNumber(toDisplay % 10);
    toDisplay /= 10;

    delayMicroseconds(DISPLAY_BRIGHTNESS);
    //Display digit for fraction of a second (1us to 5000us, 500 is pretty good)

    //Turn off all segments
    lightNumber(10);

    //Turn off all digits
    digitalWrite(digit1, DIGIT_OFF);
    digitalWrite(digit2, DIGIT_OFF);
    digitalWrite(digit3, DIGIT_OFF);
    digitalWrite(digit4, DIGIT_OFF);
    digitalWrite(point, LOW);
  }
}

void gameOver() {
  digitalWrite(disablePin, HIGH);
  while (1) {
    int period = 500;
    for (int i = 0; i < period / 2; i++) displayNumber(0);
    delay(period);
  }
}

void defused(int timeLeft) {
  while (1) {
    displayNumber((timeLeft / 60) * 100 + timeLeft % 60);
  }
}

//Given a number, turns on those segments
//If number == 10, then turn off number
void lightNumber(int numberToDisplay) {

#define SEGMENT_ON  HIGH
#define SEGMENT_OFF LOW

  switch (numberToDisplay) {

    case 0:
      digitalWrite(segA, SEGMENT_ON);
      digitalWrite(segB, SEGMENT_ON);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_ON);
      digitalWrite(segE, SEGMENT_ON);
      digitalWrite(segF, SEGMENT_ON);
      digitalWrite(segG, SEGMENT_OFF);
      break;

    case 1:
      digitalWrite(segA, SEGMENT_OFF);
      digitalWrite(segB, SEGMENT_ON);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_OFF);
      digitalWrite(segE, SEGMENT_OFF);
      digitalWrite(segF, SEGMENT_OFF);
      digitalWrite(segG, SEGMENT_OFF);
      break;

    case 2:
      digitalWrite(segA, SEGMENT_ON);
      digitalWrite(segB, SEGMENT_ON);
      digitalWrite(segC, SEGMENT_OFF);
      digitalWrite(segD, SEGMENT_ON);
      digitalWrite(segE, SEGMENT_ON);
      digitalWrite(segF, SEGMENT_OFF);
      digitalWrite(segG, SEGMENT_ON);
      break;

    case 3:
      digitalWrite(segA, SEGMENT_ON);
      digitalWrite(segB, SEGMENT_ON);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_ON);
      digitalWrite(segE, SEGMENT_OFF);
      digitalWrite(segF, SEGMENT_OFF);
      digitalWrite(segG, SEGMENT_ON);
      break;

    case 4:
      digitalWrite(segA, SEGMENT_OFF);
      digitalWrite(segB, SEGMENT_ON);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_OFF);
      digitalWrite(segE, SEGMENT_OFF);
      digitalWrite(segF, SEGMENT_ON);
      digitalWrite(segG, SEGMENT_ON);
      break;

    case 5:
      digitalWrite(segA, SEGMENT_ON);
      digitalWrite(segB, SEGMENT_OFF);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_ON);
      digitalWrite(segE, SEGMENT_OFF);
      digitalWrite(segF, SEGMENT_ON);
      digitalWrite(segG, SEGMENT_ON);
      break;

    case 6:
      digitalWrite(segA, SEGMENT_ON);
      digitalWrite(segB, SEGMENT_OFF);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_ON);
      digitalWrite(segE, SEGMENT_ON);
      digitalWrite(segF, SEGMENT_ON);
      digitalWrite(segG, SEGMENT_ON);
      break;

    case 7:
      digitalWrite(segA, SEGMENT_ON);
      digitalWrite(segB, SEGMENT_ON);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_OFF);
      digitalWrite(segE, SEGMENT_OFF);
      digitalWrite(segF, SEGMENT_OFF);
      digitalWrite(segG, SEGMENT_OFF);
      break;

    case 8:
      digitalWrite(segA, SEGMENT_ON);
      digitalWrite(segB, SEGMENT_ON);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_ON);
      digitalWrite(segE, SEGMENT_ON);
      digitalWrite(segF, SEGMENT_ON);
      digitalWrite(segG, SEGMENT_ON);
      break;

    case 9:
      digitalWrite(segA, SEGMENT_ON);
      digitalWrite(segB, SEGMENT_ON);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_ON);
      digitalWrite(segE, SEGMENT_OFF);
      digitalWrite(segF, SEGMENT_ON);
      digitalWrite(segG, SEGMENT_ON);
      break;

    case 10:
      digitalWrite(segA, SEGMENT_OFF);
      digitalWrite(segB, SEGMENT_OFF);
      digitalWrite(segC, SEGMENT_OFF);
      digitalWrite(segD, SEGMENT_OFF);
      digitalWrite(segE, SEGMENT_OFF);
      digitalWrite(segF, SEGMENT_OFF);
      digitalWrite(segG, SEGMENT_OFF);
      break;
  }
}
