const unsigned long FAN_OFF_TIME = 1000l*60*18; //18 Minuten
const unsigned long FAN_ON_TIME = 1000l*60*2; //2 Minuten
const unsigned long LED_STRIP_OFF_TIME = 1000l*60*60*7.5; //7.5 stunden
const unsigned long LED_STRIP_ON_TIME = 1000l*60*30; //30 Minuten

const unsigned long LOOP_INTERVAL = 1000l*60; //1 minuten

const unsigned long PUMP_ON_TIME_UPPER = 1000l*6;
const unsigned long PUMP_OFF_TIME_UPPER = 1000l*60*60*24*2; //2 tage
const unsigned long PUMP_ON_TIME_LOWER = 1000l*4;
const unsigned long PUMP_OFF_TIME_LOWER = 1000l*60*60*24*1; //1 tage

//TODO: test moisture values
#define MIN_MOISTURE_UPPER 500
#define MIN_MOISTURE_LOWER 500

unsigned long lastTimeFans = 0;
bool fansOn = false;
unsigned long lastTimeLeds = 0;
bool ledsOn = false;
unsigned long lastTimePumpUpper = 0;
unsigned long lastTimePumpLower = 0;

void setup() {
  setPinModes();
}


void loop() {
  //run the fans for the sleep time defined on line 19
  if (fansOn) {
    if(millis() - lastTimeFans > FAN_ON_TIME) {
      controlFan(false);
      lastTimeFans = millis();
      fansOn = false;
    }
  } else {
    if(millis() - lastTimeFans > FAN_OFF_TIME) {
      controlFan(true);
      lastTimeFans = millis();
      fansOn = true;
    }
  }

  
  if (ledsOn) {
    if(millis() - lastTimeLeds > LED_STRIP_ON_TIME) {
      controlLEDStrip(false);
      lastTimeLeds = millis();
      ledsOn = false;
    }
  } else {
    if(millis() - lastTimeLeds > LED_STRIP_OFF_TIME) {
      controlLEDStrip(true);
      lastTimeLeds = millis();
      ledsOn = true;
    }
  }

  
  checkMoistureAndWater();
  delay(LOOP_INTERVAL);
}


void checkMoistureAndWater() {
  if(millis() - lastTimePumpUpper > PUMP_OFF_TIME_UPPER) {
    controlPumpUpper(getMoistureUpper() < MIN_MOISTURE_UPPER && isWaterInTank()); // check if earth is dry and there is water in the tank
    delay(PUMP_ON_TIME_UPPER);
    controlPumpUpper(false);
    lastTimePumpUpper = millis();
    checkWaterInTank();
  }


  if(millis() - lastTimePumpLower > PUMP_OFF_TIME_LOWER) {
    controlPumpLower(getMoistureLower() < MIN_MOISTURE_LOWER && isWaterInTank()); // check if earth is dry and there is water in the tank
    delay(PUMP_ON_TIME_LOWER);
    controlPumpLower(false);
    lastTimePumpLower = millis();
    checkWaterInTank();
  }
}

bool checkWaterInTank() {
  bool waterInTank = isWaterInTank();
  controlWaterLED(!waterInTank);
  return waterInTank;
}
