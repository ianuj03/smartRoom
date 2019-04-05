/*
    Sketch to implement Smart Home concept with one light and fan;
    Note: The sketch was written long back, but wasn't uploaded anywhere; So, I'm writting the date of last backup taken
    
    *This sketch uses Triac check another one, which uses Relay
    Last Backup Date: Jan, 2018
*/

#include<DHT.h>
#include<SoftwareSerial.h>

//Electrical appliances
//#define FAN 4
#define LIGHT 5

//Sensors
#define dht11 6
#define LDR A0
#define PIR1 8
#define PIR2 9
#define PIR3 10
#define PIR4 11

//Serial communication with TRIAC
SoftwareSerial control(3,4);

DHT dht;

int ldr_value;

byte speed_set[][1]={{0x00},{0x09},{0x1A},{0x3F},{0x57},{0x7A},{0xAA},{0xFF}};

float tempc,humidity;

void basic();

void setup(){
    pinMode(LIGHT,OUTPUT);
    pinMode(PIR1,INPUT);
    pinMode(PIR2,INPUT);
    pinMode(PIR3,INPUT);
    pinMode(PIR4,INPUT);
    
    dht.setup(dht11);
    pinMode(LDR,INPUT);
    control.begin(9600);
    delay(5000);
}


void loop(){
    
    if(PIR1==HIGH||PIR2==HIGH||PIR3==1||PIR4==1){
        basic();

        //LIGHT
        if(ldr_value<100)
            digitalWrite(LIGHT,1);
        else
            digitalWrite(LIGHT,0);

        
        //FAN
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
            
    }
}

void basic(){
    ldr_value=analogRead(LDR);
    //float total_value=ldr_value*0.0048828125;
    //lux=(2500/total_value-500)/10;
    tempc=dht.getTemperature();
    humidity=dht.getHumidity();   
}

