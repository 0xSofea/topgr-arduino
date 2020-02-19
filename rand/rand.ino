long randnumber;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  randomSeed(analogRead(0));
}

void loop() {
  // put your main code here, to run repeatedly:
  float count = 0;
  float count1 = 1;
  while(count < 10){
    ++count;
    ++count1;
    Serial.print(count);
    Serial.print(",");
    Serial.println(count1);
   
    delay(50);
  }
}
