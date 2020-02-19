#include <MegunoLink.h>
#include <Filter.h>

ExponentialFilter<float> top_filter(10, 10);
ExponentialFilter<float> mid_filter(10, 10);
ExponentialFilter<float> chain_filter(10, 6);

//ExponentialFilter<float> counter_filter(40, 20);

unsigned long startTime;
int scanZone = 25;
int fps = 300;
int count = 0;

float topVal = 0;
float topTotal = 0;
int topCount = 0;
boolean topHit = false;

float midVal = 0;
float midTotal = 0;
int midCount = 0;
boolean midHit = false;

float interval = 0;
float yDiff = 0;
boolean hit = false;

void setup() {
  startTime = millis();
  Serial.begin(57600);

}

void loop() {
  unsigned long curTime = millis();

  float v, top, mid, chain, volts3, counter;
  

  if (curTime > startTime + (1000/fps)){
    v = analogRead(A0)*0.0048828125;  
    top = 13*pow(v, -1);

    v = analogRead(A3)*0.0048828125;  
    mid = 13*pow(v, -1);
    
    v = analogRead(A5)*0.0048828125;  
    chain = 13*pow(v, -1);
    
    // filter top - mid
    float cap = 30;
    if (top > cap) {
      top = cap;
    }
    if (mid > cap) {
      mid = cap;
    }
    
    top_filter.Filter(top);
    mid_filter.Filter(mid);
    chain_filter.Filter(chain);

    float deadzone = 18.5;
    float chainDeadZone = 6;

    top = abs(top_filter.Current() - cap) - deadzone;
    mid = abs(mid_filter.Current() - cap) - 18.5;
    chain = -chain_filter.Current() + 6;
    float dt = abs(top_filter.Current() - cap) - 9;
    float ds = abs(mid_filter.Current() - cap) - 9;

    if (top < 0) {
      top = 0;
    }
    if (mid < 0) {
      mid = 0;
    }

    if (chain < 0) {
      chain = 0;
    } else {
      chain = 1;
    }

//    if (top > 0 || mid > 0) {
//      interval += 1000/fps;
//
//      if (top > 0) {
//        if (topVal == 0) {
//          topVal = top;
//        }
//
//        if (top > 3) {
//          topTotal += top;
//          
//          topCount++;
//          topHit = true;
//        } 
//      }
//      if (mid > 0) {
//        if (midVal == 0) {
//          midVal = mid;
//        }
//
//        if (mid > 1) {
//          midTotal += mid;
//          
//          midCount++;
//          midHit = true;
//        }
//      }
//
//    }
//
//    // calculate delta pitch by averaging peak points - in mm
//    float delta_y;
//    float avrPeak_top, avrPeak_mid;
//    if (topHit && topCount > 0 && midHit && > midCount > 0) {
//      avrPeak_top = topTotal / topCount;
//      avrPeak_mid = midTotal / midCOunt;
//
//      delta_y = avrPeak_top - avrPeak_mid;
//    }
//
//    // get delta yaw - in ms
//    float delta_x;
//    if (topVal > 0 && midVal > 0) {
//      delta_x = interval;
//      interval = 0;
//    }

    // data visual
    Serial.print(dt);
    Serial.print(',');
    Serial.print(ds);
    Serial.print(',');
    Serial.print(top);
    Serial.print(',');
    Serial.println(mid);
    
  
    // delta left
    

    startTime = millis();
  }
  
}
