const unsigned long FAN_INTERVAL = 1000l*60*60*3;
const unsigned long LOOP_INTERVAL = 1000l*60*10;

const unsigned long PUMP_DURATION_UPPER = 1000*5;
const unsigned long PUMP_DURATION_LOWER = 1000*5;

//TODO: test moisture values
#define MIN_MOISTURE_UPPER 500
#define MIN_MOISTURE_LOWER 500

unsigned long lastTimeFans = 0;

void setup() {
  setPinModes();
}

void loop() {
  controlFan(false);
  //run the fans for the sleep time defined on line 19
  if(millis() - lastTimeFans > FAN_INTERVAL) { //run the fans every 3 hours for 10 min
    controlFan(true);
    lastTimeFans = millis();
  }
  checkMoistureAndWater();
  delay(LOOP_INTERVAL); //wait 10 min
}


void checkMoistureAndWater() {
  //TODO: test moisture values
  bool wateringUpper = getMoistureUpper() < MIN_MOISTURE_UPPER;
  bool wateringLower = getMoistureLower() < MIN_MOISTURE_LOWER;
  
  unsigned long wateringStarted = millis();

  if(!checkWaterInTank()) {
      wateringUpper = false;
      wateringLower = false;
  }

  controlPumpUpper(wateringUpper);
  controlPumpLower(wateringLower);

  while(wateringUpper || wateringLower) {
    if(!checkWaterInTank()) {
      wateringUpper = false;
      wateringLower = false;
    }

    if(millis() - wateringStarted > PUMP_DURATION_UPPER) {
      wateringUpper = false;
    }
    if(millis() - wateringStarted > PUMP_DURATION_LOWER) {
      wateringLower = false;
    }
    
    if(!wateringUpper) {
      controlPumpUpper(false);
    }
    if(!wateringLower) {
      controlPumpLower(false);
    }
    
  }
}

bool checkWaterInTank() {
  bool waterInTank = isWaterInTank();
  controlWaterLED(!waterInTank);
  return waterInTank;
}
