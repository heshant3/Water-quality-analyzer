
int airquality = 0;
void setup()
{
  Serial.begin(9600);

}
void loop()
{

  int sensorValue = analogRead(A4);
  Serial.print("Air Quality = ");
  Serial.print(sensorValue/10);

  Serial.print("%");
  Serial.println();
  delay(100);



}



