#include <MegunoLink.h>
#include <Filter.h>

ExponentialFilter<float> top_filter(4, 80);
ExponentialFilter<float> mid_filter(4, 80);

unsigned long startTime;
int scanZone = 15;
int fps = 400;
float timeNow = 0;
bool timeNow_state = false;

float data_top[600];
float data_mid[600];

int index = 0;
bool reading = false;

void setup() {
  startTime = millis();
  Serial.begin(57600);

  memset(data_top, -1, sizeof(data_top));
  memset(data_mid, -1, sizeof(data_mid));
}

void loop() {
  unsigned long curTime = millis();

  float volts, top, volts1, mid;

  if (curTime > startTime + (1000/fps)){
    volts = analogRead(A0)*0.0048828125;  
    top = 13*pow(volts, -1);

    volts1 = analogRead(A7)*0.0048828125;  
    mid = 13*pow(volts1, -1);
        
    if (!(isinf(top) || isinf(mid))) {
      top_filter.Filter(top);   
      mid_filter.Filter(mid);
      
      if (top_filter.Current() < scanZone || mid_filter.Current() < scanZone) {
        if (top_filter.Current() < scanZone) {                  
          data_top[index] = top_filter.Current();

        } else {
          data_top[index] = 0;
          
        }
        
        if (mid_filter.Current() < scanZone) {                   
          data_mid[index] = mid_filter.Current();

        } else {
          data_mid[index] = 0;

        }

        reading = true;
        index++;
        
      } else {
        timeNow += (1000/fps);
        //timeNow_state = true;
         
        //Send pi          
        if (reading) {
          //if (timeNow_state) {
            Serial.print("Time now: ");
            Serial.println(timeNow);
    
            timeNow = 0;
            //timeNow_state = false;
          //}
  
          Serial.print("TOP: ");
          for(int x = 0; x < index; x++) {
            Serial.print(data_top[x]);
            Serial.print(',');
          }
          Serial.print('\n');
  
          Serial.print("MID: ");
          for(int x = 0; x < index; x++) {
            Serial.print(data_mid[x]);
            Serial.print(',');
           
          }
          Serial.print('\n');
                    
          memset(data_top, -1, sizeof(data_top));
          memset(data_mid, -1, sizeof(data_mid));
             
          reading = false;
          index = 0;
        }
      }
      
      
    }
          
    startTime = millis();
      
  }
} 
   
