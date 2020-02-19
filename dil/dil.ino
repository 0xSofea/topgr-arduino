
int dps = 400;
unsigned long interval = (1000/dps); // 400 per second
unsigned long startTime;

unsigned long timeNow = 0;
bool timeNow_state = false;

void setup() {
  startTime = millis();
}

void loop() {
  unsigned long curTime = millis();

  if (curTime > (startTime + interval) ){

    timeNow_state = true;

    if (timeNow_state) {
      timeNow += interval;
    }

    startTime = curTime;
  }
}
