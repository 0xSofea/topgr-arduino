#include <MegunoLink.h>
#include <Filter.h>

ExponentialFilter<float> chain_filter(20, 5);

unsigned long startTime;
int fps = 300;
int count = 0;

void setup() {
  Serial.begin(57600);
  startTime = millis();
}

void loop() {
  unsigned long curTime = millis();
  float chain;
  
  if (curTime > startTime + (1000/fps)){
    
      float volts1 = analogRead(A5)*0.0048828125;  
      float chain = 13*pow(volts1, -1);
      chain_filter.Filter(chain);

      chain = -chain_filter.Current() + 6;
      if (chain < 0) {
        chain = 0;
      } else {
        chain = 1;
      }
      
      Serial.println(chain);
      startTime = millis();
    }
    
}    
