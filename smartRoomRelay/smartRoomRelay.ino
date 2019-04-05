/*
	Sketch to implement Smart Home concept with one light and fan;
	Note: The sketch was written long back, but wasn't uploaded anywhere; So, I'm writting the date of last backup taken
    
    *This sketch uses Relays check another one, which uses triac IC
	
	Last Backup Date: Jan, 2018
*/

#include<DHT.h>
#include<String.h>
#include<SoftwareSerial.h>

//Electrical appliances
#define FAN 4
#define LIGHT 5

//Sensors
#define dht11 6
#define LDR A0
#define PIR1 8
#define PIR2 9
#define PIR3 10
#define PIR4 11

//Control option from Bluetooth
SoftwareSerial BT(2,3);

DHT dht;

int ldr_value,l_check=0,f_check=0,flag=0;
float tempc,humidity;
void basic();
void my_room();

void setup(){
    pinMode(FAN,OUTPUT);
    pinMode(LIGHT,OUTPUT);
    pinMode(PIR1,INPUT);
    pinMode(PIR2,INPUT);
    pinMode(PIR3,INPUT);
    pinMode(PIR4,INPUT);
    dht.setup(dht11);
    pinMode(LDR,INPUT);
    BT.begin(38400);
    delay(5000);
}


void loop(){
  
    if(BT.available()){
        if((BT.readString()).equalsIgnoreCase("my room")){
            my_room();
        }
    }
  
    if(PIR1==HIGH||PIR2==HIGH||PIR3==1||PIR4==1){
        flag=1;
        basic();

        if(tempc<23){
            digitalWrite(FAN,0);
            f_check=0;
        }
        else{
            digitalWrite(FAN,1);
            f_check==1;
        }
        if(ldr_value<100){
            digitalWrite(LIGHT,1);
            l_check=1;
        }
        else{
            digitalWrite(LIGHT,0);
            l_check=0;
        }
    }
    else
        flag=0;
}

void basic(){
    ldr_value=analogRead(LDR);
    //float total_value=ldr_value*0.0048828125;
    //lux=(2500/total_value-500)/10;
    tempc=dht.getTemperature();
    humidity=dht.getHumidity();   
}

void my_room(){
    basic();
    BT.println("\n\tHey!! Greetings.");
    BT.print("Temperature of your room is ");
    BT.print(tempc);
    BT.print("C.\nHumidity of your room is ");
    BT.print(humidity);
    BT.print("%.\nLight of your room is ");
    
    if(l_check==0)
        BT.print("OFF.");
    else
        BT.print("ON.");
        BT.print("\nFan of your room is ");
    if(f_check==0)
        BT.print("OFF.");
    else
        BT.print("ON.");
    if(flag==0)
        BT.println("\nRoom is empty.");
    else
        BT.println("\nRoom is not empty.");
}
