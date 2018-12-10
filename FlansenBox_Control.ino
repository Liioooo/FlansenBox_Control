unsigned long lastTimeFans = 0;

void setup() {
  setPinModes();
}

void loop() {
  controlFAN(false);
  //run the fans for the sleep time defined on line 15
  if(millis() - lastTimeFans > 1000 * 60 * 60 * 3) { //run the fans every 3 hours for 10 min
    controlFAN(true);
    lastTimeFans = millis();
  }
  checkMoistureAndWater();
  delay(1000 * 60 * 10); //wait 10 min
}


void checkMoistureAndWater() { //TODO: test moisture values
  bool watering1 = getMoisture1() < 500;
  bool watering2 = getMoisture2() < 500;
  
  unsigned long wateringStarted = millis();
  
  while(watering1 || watering2) {
    if(!checkWaterInTank()) {
      watering1 = false;
      watering2 = false;
    }
    
    if(watering1) {
      watering1 = millis() - wateringStarted < 1000 * 5; 
    }
    controlPump1(watering1);

    if(watering2) {
      watering2 = millis() - wateringStarted < 1000 * 5; 
    }
    controlPump2(watering2);
    delay(1);
  }
}

bool checkWaterInTank() {
  bool waterInTank = isWaterInTank();
  controlWaterLED(!waterInTank);
  return waterInTank;
}
