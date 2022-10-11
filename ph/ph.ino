// pHRead.ino

// Constants:-
const byte pHpin = A0;    // Connect the sensor's Po output to analogue pin 0.

// Variables:-
float Po;
int kk;
void setup()
{
    Serial.begin(115200);
}

void loop()
{
    Po = (1023 - analogRead(pHpin)) / 73.07;   // Read and reverse the analogue input value from the pH sensor then scale 0-14.
    kk = (Po,2);                    // Print the result in the serial monitor.
     Serial.println (kk); 
    delay(100);                              // Take 1 reading per second.
}
