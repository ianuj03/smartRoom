#include<DHT.h>
#include<SoftwareSerial.h>
SoftwareSerial control(3,4);
DHT dht;
byte speed_set[][1]={{0x00},{0x09},{0x1A},{0x3F},{0x57},{0x7A},{0xAA},{0xFF}};
void setup(){
  control.begin(9600);
  dht.setup(6);
  Serial.begin(9600);
}
void loop(){
  float tempc=dht.getTemperature();
  Serial.println(tempc);
  if(tempc<21)
    control.write(speed_set[0][0]);
  else if(tempc<22)
    control.write(speed_set[1][0]);
  else if(tempc<23)
    control.write(speed_set[2][0]);
  else if(tempc<24)
    control.write(speed_set[3][0]);
  else if(tempc<25)
    control.write(speed_set[4][0]);
  else if(tempc<26)
    control.write(speed_set[5][0]);
  else if(tempc<=27)
    control.write(speed_set[6][0]);
  else
    control.write(speed_set[7][0]);
  delay(5000);
}

