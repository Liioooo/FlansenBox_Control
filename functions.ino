#define pump1Pin 13
#define pump2Pin 12
#define fanPin 11
#define LEDStripPin 10
#define waterLEDPin 9
#define soilSensor1Pin A0
#define soilSensor2Pin A1
#define waterInTankPin A2

void setPinModes() {
  pinMode(pump1Pin, OUTPUT);
  pinMode(pump2Pin, OUTPUT);
  pinMode(fanPin, OUTPUT);
  pinMode(LEDStripPin, OUTPUT);
  pinMode(waterLEDPin, OUTPUT);
}

void controlPump1(bool state) {
  if(state) {
    digitalWrite(pump1Pin, HIGH);
  } else {
    digitalWrite(pump1Pin, LOW);
  }
}

void controlPump2(bool state) {
  if(state) {
    digitalWrite(pump2Pin, HIGH);
  } else {
    digitalWrite(pump2Pin, LOW);
  }
}

void controlFAN(bool state) {
  if(state) {
    digitalWrite(fanPin, HIGH);
  } else {
    digitalWrite(fanPin, LOW);
  }
}

void controlLEDStrip(bool state) {
  if(state) {
    digitalWrite(LEDStripPin, HIGH);
  } else {
    digitalWrite(LEDStripPin, LOW);
  }
}

void controlWaterLED(bool state) {
  if(state) {
    digitalWrite(waterLEDPin, HIGH);
  } else {
    digitalWrite(waterLEDPin, LOW);
  }
}

bool isWaterInTank() {
  int value = analogRead(waterInTankPin);
  return value > 800; //TODO: test the value
}

int getMoisture1() {
  return analogRead(soilSensor1Pin);
}

int getMoisture2() {
  return analogRead(soilSensor2Pin);
}
