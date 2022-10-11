#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

const byte pHpin = A0;
int airquality = A0;
int data_pin = A2;
boolean result[41]; //holds the result
int interval=500; //Sample every 2 seconds
unsigned int temp; //in celcius
unsigned int humidity; //in %RH
float Po;

void setup() {

  //Initiate Serial for Bluetooth Communication
    Serial.begin(9600); 
    lcd.begin(16, 2);
    lcd.print(" H.T.KALUBOWILA ");
    delay(3000);
    lcd.clear();
}

void loop() {
  //Pause before taking next measurement
    delay(interval); 
     Po = (1023 - analogRead(pHpin)) / 57.09;  
    int sensorValue = analogRead(A4);
    int sensorValue1 = analogRead(A1);
    float voltage = sensorValue1 * (5.3 / 1024.0);
  //Trigger reading by holding data pin low for 18ms
    pinMode(data_pin, OUTPUT);
    digitalWrite(data_pin,LOW);
    delay(18);
    digitalWrite(data_pin,HIGH);
    pinMode(data_pin, INPUT_PULLUP); 
  
  //read 41 bits of signal
    for(int i=0;i<=40;i++){
      result[i]=(pulseIn(data_pin, HIGH)>40);
    }

  //Extract Humidity (from byte 1)
    humidity=0;
    for (int i=1;i<=8;i++){
      humidity=humidity<<1;
      if (result[i]) humidity|=1;
    }
      
  //Extract Temperature (from Byte 3)
    temp=0;
    for (int i=17;i<=24;i++){
      temp=temp<<1;
      if (result[i]) temp|=1;
    }
    
   //Send data over Bluetooth
    Serial.print("*T"+String(temp)+"*");
    Serial.print("*H"+String(humidity)+"*");
    Serial.print("*A"+String(sensorValue/10)+"*");
    Serial.print("*D"+String(voltage)+"*");
    Serial.print("*P"+String(Po)+"*");


    lcd.setCursor(0, 0);
    lcd.print("P=");
    lcd.setCursor(2, 0);
    lcd.print(Po);

    lcd.setCursor(7, 0);
    lcd.print("A=");
    lcd.setCursor(9, 0);
    lcd.print(sensorValue/10);

    lcd.setCursor(12, 0);
    lcd.print("T=");
    lcd.setCursor(14, 0);
    lcd.print(temp);

    lcd.setCursor(11, 1);
    lcd.print("H=");
    lcd.setCursor(13, 1);
    lcd.print(humidity);
    lcd.setCursor(15, 1);
    lcd.print("%");

    lcd.setCursor(6, 1);
    lcd.print(voltage);
    
    
    
    if(voltage > 4.20  ){
    lcd.setCursor(0, 1);
    lcd.print("Clean");
    Serial.print("*F"+String("Clean")+"*");
    }

    else{
    lcd.setCursor(0, 1);
    lcd.print("Dirty");
    Serial.print("*F"+String("Dirty")+"*");
    }
}


