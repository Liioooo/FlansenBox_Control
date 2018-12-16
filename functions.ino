#define pump1Pin 9
#define pump2Pin 10
#define fanPin 11
#define LEDStripPin 8

#define waterLEDPin 7 //red LED, water indicator

#define soilSensor1Pin A0
#define soilSensor2Pin A1
#define soilSensor1Current 5 // current for sensor 1
#define soilSensor2Current 6 // current for sensor 2

#define waterInTankPin A2 //input pin for water measering
#define waterInTankCurrent 4 // current for water tank measering

void setPinModes() {
  // set timers for PWM frequency otside the hearing spektrum 
  TCCR1B = TCCR1B & 0b11111000 | 0x01; // pin 9,10
  TCCR2B = TCCR2B & 0b11111000 | 0x01; // pin 11,3
  
  pinMode(pump1Pin, OUTPUT);
  pinMode(pump2Pin, OUTPUT);
  pinMode(fanPin, OUTPUT);
  pinMode(LEDStripPin, OUTPUT);
  pinMode(waterLEDPin, OUTPUT);
  pinMode(soilSensor1Current, OUTPUT);
  pinMode(soilSensor2Current, OUTPUT);
  pinMode(waterInTankCurrent, OUTPUT);

}

void controlPump1(bool state) {
  if(state) {
    // drossels the speed dow
    analogWrite(pump1Pin, 255);
    delay(800); // start the motor
    analogWrite(pump1Pin, 150);
  } else {
    analogWrite(pump1Pin, 0);
  }
}

void controlPump2(bool state) {
  if(state) {
    // drossels the speed dow
    analogWrite(pump2Pin, 255);
    delay(800); // start the motor
    analogWrite(pump2Pin, 150);
  } else {
    analogWrite(pump2Pin, 0);
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
  return value > 800; //TODO: test the value
}

int getMoisture1() {
  digitalWrite(soilSensor1Current, HIGH);
  delay(400);
  int val =  analogRead(soilSensor1Pin);
  digitalWrite(soilSensor2Current, LOW);
  return val;
}

int getMoisture2() {
  digitalWrite(soilSensor2Current, HIGH);
  delay(400);
  int val = analogRead(soilSensor2Pin);
  digitalWrite(soilSensor2Current, LOW);
  return val;
}
