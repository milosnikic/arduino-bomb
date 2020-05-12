int inputSignalPin = 13;
int outputSignalPin = 12;
int disablePin = 10;
int photoResistor = A0;
int buzzerPin = 11;
boolean startBomb = false;

void setup() {
  pinMode(inputSignalPin, INPUT);
  pinMode(outputSignalPin, OUTPUT);
  pinMode(photoResistor, INPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("Wait 5 seconds.");
  delay(5000);
}

void loop() {
  // Read value of photoresistor
  int value = analogRead(photoResistor);
  // Lower value, more bright
  Serial.println(value);
  if (value < 450) {
    startBomb = true;
    digitalWrite(outputSignalPin, HIGH);
  }

  while (startBomb) {
    int disabledVal = digitalRead(disablePin);
    int inputVal = digitalRead(inputSignalPin);
    Serial.print("Disabled value: ");
    Serial.println(disabledVal);
    Serial.print("Input value: ");
    Serial.println(inputVal);
    if (inputVal == HIGH) {
      tone(buzzerPin, 1000);
      delay(100);
      noTone(buzzerPin);
      delay(900);
    }
    if (disabledVal == HIGH) {
      while (1) {
        Serial.print("Disabled value: ");
        Serial.println(disabledVal);
        Serial.print("Input value: ");
        Serial.println(inputVal);
        tone(buzzerPin, 1000);
      }
    }
  }
}
