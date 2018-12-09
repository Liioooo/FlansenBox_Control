unsigned long lastTimeFans = 0;

void setup() {
  setPinModes();
}

void loop() {
  controlFAN(false);
  if(millis() - lastTimeFans > 1000 * 60 * 60 * 3) { //run the fans every 3 hours for 10 min (line 15)
    controlFAN(true);
    lastTimeFans = millis();
  }
  checkMoistureAndWater();
  checkWaterInTank();
  delay(1000 * 60 * 10); //wait 10 min
}


void checkMoistureAndWater() { //TODO: test moisture values
  if(getMoisture1() < 500) {
    waterUpperStage();
  }
  if(getMoisture2() < 500) {
    waterLowerStage();
  }
}

void waterUpperStage() {
  if(checkWaterInTank()) {
    controlPump1(true);
    delay(1000 * 10); //TODO: test watering times
    controlPump1(false);
    checkWaterInTank();
  }
}

void waterLowerStage() {
  if(checkWaterInTank()) {
    controlPump2(true);
    delay(1000 * 10); //TODO: test watering times
    controlPump2(false);
    checkWaterInTank();
  }
}

bool checkWaterInTank() {
  bool waterInTank = isWaterInTank();
  controlWaterLED(!waterInTank);
  return waterInTank;
}
