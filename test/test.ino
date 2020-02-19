#include <MegunoLink.h>
#include <Filter.h>

ExponentialFilter<float> counter_filter(40, 10);
//ExponentialFilter<float> mid_filter(4, 80);

unsigned long startTime;
int fps = 400;
int count = 0;

void setup() {
  Serial.begin(57600);
  startTime - millis();
}

void loop() {
  unsigned long curTime = millis();

  float volts = analogRead(A0)*0.0048828125;  
  float top = 13*pow(volts, -1);

//  float volts1 = analogRead(A0)*0.0048828125;  
//  float mid = 13*pow(volts1, -1);
//  mid_filter.Filter(mid);
    
    if (curTime > startTime + (1000/fps)){
         if (!(isinf(top))) {
           counter_filter.Filter(top);  
           Serial.println(counter_filter.Current());
//      Serial.print(",");
//      Serial.println(mid_filter.Current());
       }
      startTime = millis();
    }    
  }
