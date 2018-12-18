#define pumpUpperPin 9
#define pumpLowerPin 10
#define fanPin 11
#define LEDStripPin 8

#define waterLEDPin 7 //red LED, water indicator

#define soilSensorUpperPin A0
#define soilSensorLowerPin A1
#define soilSensorUpperCurrent 5 // current for sensor 1
#define soilSensorLowerCurrent 6 // current for sensor 2

#define waterInTankPin A2 // input pin for water measering
#define waterInTankCurrent 4 // current for water tank measering

#define WATER_IN_TANK_MIN_VALUE 800 //TODO: test the value

void setPinModes() {
  // set timers for PWM frequency otside the hearing spektrum 
  TCCR1B = TCCR1B & 0b11111000 | 0x01; // pin 9,10
  TCCR2B = TCCR2B & 0b11111000 | 0x01; // pin 11,3
  
  pinMode(pumpUpperPin, OUTPUT);
  pinMode(pumpLowerPin, OUTPUT);
  pinMode(fanPin, OUTPUT);
  pinMode(LEDStripPin, OUTPUT);
  pinMode(waterLEDPin, OUTPUT);
  pinMode(soilSensorUpperCurrent, OUTPUT);
  pinMode(soilSensorLowerCurrent, OUTPUT);
  pinMode(waterInTankCurrent, OUTPUT);

}

void controlPumpUpper(bool state) {
  if(state) {
    // drossels the speed dow
    analogWrite(pumpUpperPin, 255);
    delay(800); // start the motor
    analogWrite(pumpUpperPin, 150);
  } else {
    analogWrite(pumpUpperPin, 0);
  }
}

void controlPumpLower(bool state) {
  if(state) {
    // drossels the speed dow
    analogWrite(pumpLowerPin, 255);
    delay(800); // start the motor
    analogWrite(pumpLowerPin, 150);
  } else {
    analogWrite(pumpLowerPin, 0);
  }
}

void controlFAN(bool state) {
  if(state) {
    // drossels the speed dow
    analogWrite(fanPin, 255);
    delay(800); // start the motor
    analogWrite(fanPin, 150);
  } else {
    analogWrite(fanPin, 0);
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
  digitalWrite(waterInTankCurrent, HIGH);
  delay(200);
  int value = analogRead(waterInTankPin);
  digitalWrite(waterInTankCurrent, LOW);
  return value > WATER_IN_TANK_MIN_VALUE; //TODO: test the value
}

int getMoistureUpper() {
  digitalWrite(soilSensorUpperCurrent, HIGH);
  delay(400);
  int val =  analogRead(soilSensorUpperPin);
  digitalWrite(soilSensorLowerCurrent, LOW);
  return val;
}

int getMoistureLower() {
  digitalWrite(soilSensorLowerCurrent, HIGH);
  delay(400);
  int val = analogRead(soilSensorLowerPin);
  digitalWrite(soilSensorLowerCurrent, LOW);
  return val;
}
