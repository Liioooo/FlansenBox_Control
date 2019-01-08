//=============
//TEST VALUE
//=============

const unsigned long FAN_OFF_TIME = 1000l*60*60; //1 stunde
const unsigned long FAN_ON_TIME = 1000l*60*3; //3 minuten
const unsigned long LED_STRIP_OFF_TIME = 1000l*60*60*5; //5 stunden
const unsigned long LED_STRIP_ON_TIME = 1000l*60*60; //1 stunde

const unsigned long LOOP_INTERVAL = 1000l*60*1; //1 minuten

const unsigned long PUMP_ON_TIME_UPPER = 1000l*3;
const unsigned long PUMP_OFF_TIME_UPPER = 1000l*60*60*24*5; //5 tage
const unsigned long PUMP_ON_TIME_LOWER = 1000l*1;
const unsigned long PUMP_OFF_TIME_LOWER = 1000l*60*60*24*2; //2 tage

//TODO: test moisture values
#define MIN_MOISTURE_UPPER 200
#define MIN_MOISTURE_LOWER 200

unsigned long lastTimeFans = 0;
bool fansOn = false;
unsigned long lastTimeLeds = 0;
bool ledsOn = false;
unsigned long lastTimePumpUpper = 0;
unsigned long lastTimePumpLower = 0;

void setup() {
  setPinModes();
}

bool isRunning = 1==1;
bool dauerPump = 1==0;
bool dauerLeucht = 1==0;

void loop() {
  if (isRunning) {
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
  } else if (dauerPump) {
    controlPumpUpper(true);
    controlPumpLower(true);
  } else if (dauerLeucht) {
    controlLEDStrip(true);
    controlFan(true);
  }

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
  
  if(millis() - lastTimePumpUpper > PUMP_OFF_TIME_UPPER) {
    controlPumpUpper(wateringUpper);
    while (millis() < wateringStarted + PUMP_ON_TIME_UPPER) {
      delay(100);
    }
    controlPumpUpper(false);
    lastTimePumpUpper = millis();
  }

  if(millis() - lastTimePumpLower > PUMP_OFF_TIME_LOWER) {
    controlPumpLower(wateringLower);
    while (millis() < wateringStarted + PUMP_ON_TIME_LOWER) {
      delay(100);
    }
    controlPumpLower(false);
    lastTimePumpLower = millis();
  }
}

bool checkWaterInTank() {
  bool waterInTank = isWaterInTank();
  controlWaterLED(!waterInTank);
  return waterInTank;
}
