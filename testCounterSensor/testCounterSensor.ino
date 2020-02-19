#include <MegunoLink.h>
#include <Filter.h>

ExponentialFilter<float> counter_filter(40, 10);
ExponentialFilter<float> chain_filter(10, 10);

unsigned long startTime;
int fps = 600;
int count = 0;

void setup() {
  Serial.begin(57600);
  startTime - millis();
}

void loop() {
  unsigned long curTime = millis();

//  float volts = analogRead(A0)*0.0048828125;  
//  float top = 13*pow(volts, -1);
//  mid_filter.Filter(mid);
    
  if (curTime > startTime + (1000/fps)){
    
      float volts1 = analogRead(A5)*0.0048828125;  
      float chain = 13*pow(volts1, -1);
      Serial.println(chain);
//      Serial.print(",");
//      Serial.println(mid_filter.Current());
    }
    startTime = millis();
}    
