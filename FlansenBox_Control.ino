#define FAN_INTERVAL 1000 * 60 * 60 * 3
#define LOOP_INTERVAL 1000 * 60 * 10
#define PUMP1_DURATION 1000 * 5
#define PUMP2_DURATION 1000 * 5

unsigned long lastTimeFans = 0;

void setup() {
  setPinModes();
}

void loop() {
  controlFAN(false);
  //run the fans for the sleep time defined on line 19
  if(millis() - lastTimeFans > FAN_INTERVAL) { //run the fans every 3 hours for 10 min
    controlFAN(true);
    lastTimeFans = millis();
  }
  checkMoistureAndWater();
  delay(LOOP_INTERVAL); //wait 10 min
}


void checkMoistureAndWater() { 
  //TODO: test moisture values
  bool watering1 = getMoisture1() < 500;
  bool watering2 = getMoisture2() < 500;
  
  unsigned long wateringStarted = millis();

  if(!checkWaterInTank()) {
      watering1 = false;
      watering2 = false;
  }

  controlPump1(watering1);
  controlPump2(watering2);

  while(watering1 || watering2) {
    if(!checkWaterInTank()) {
      watering1 = false;
      watering2 = false;
    }

    if(millis() - wateringStarted > PUMP1_DURATION) {
      watering1 = false;
    }
    if(millis() - wateringStarted > PUMP2_DURATION) {
      watering2 = false;
    }
    
    if(!watering1) {
      controlPump1(false);
    }
    if(!watering2) {
      controlPump2(false);
    }
    
  }
}

bool checkWaterInTank() {
  bool waterInTank = isWaterInTank();
  controlWaterLED(!waterInTank);
  return waterInTank;
}
