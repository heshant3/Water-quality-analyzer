
#define Vref 4.95

int airquality = 0;  


void setup(){
  Serial.begin(9600);
  delay(300);//Let system settle
  
  delay(700);//Wait rest of 1000ms recommended delay before
  //accessing sensor
}//end "setup()"

void loop(){
  //This is the "heart" of the program.


    
   
  int sensorValue1 = analogRead(A1);
  int sensorValue;
  int m;
  long sensorSum;
    for(m=0;m<50;m++)
  {
    sensorValue=analogRead(A0);//Connect the PH Sensor to A0 port
    sensorSum += sensorValue;
  }
   sensorValue =   sensorSum/50;
   
//Serial.print(" the PH value is"); 
Serial.println("*P"+String(7-1000*(sensorValue-372)*Vref/59.16/1023)+"*");
Serial.println("*A"+String(sensorValue1/10)+"*");

  delay(800);

  if(   6  > (7-1000*(sensorValue-372)*Vref/59.16/1023) ){

       Serial.println("*s"+String("Dirty water")+"*");
  }

  if((7-1000*(sensorValue-372)*Vref/59.16/1023) > 8.90){

       Serial.println("*s"+String("Dirty water")+"*");
  }
   else{
    Serial.println("*s"+String("Clean water")+"*");
   }
   
  
}

