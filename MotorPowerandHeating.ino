
/*
 HeatingElementRegulation
 
 */
//#include "Adafruit_MAX31855.h" 
#include <SoftwareSerial.h>
#include "cozir.h"
SoftwareSerial nss(2,3);
COZIR czr(nss);
int heaterPWR = 6;
int heaterDIR= 7;
int motorPWR = 10;
int PWMAmount = 10;
int fadeAmount=50;
double setTempUpper = 240;
double setTempLower = 24;
const int temperaturePin = 0;

void setup() 
{ 
   Serial.begin(9600);
   delay(1000);
   //pinMode(motorPWR, OUTPUT);
   //czr.SetOperatingMode(CZR_POLLING);
   //czr.SetOperatingMode(CZR_STREAMING);
   //czr.CalibrateFreshAir();
   //czr.SetDigiFilter(64);
   
   //pinMode(heaterPWR, OUTPUT);
   //pinMode(heaterDIR, OUTPUT);
   //digitalWrite(heaterDIR, HIGH);
   //analogWrite(heaterPWR, 0);
   //delay(100);h
} 

//need to remember to use the battery pack or else the temperature won't be accurate
void loop()  
  { 
     delay(1000);
     float voltage, degreesC, degreesF;
     float t = czr.Celsius();
     double c = czr.CO2()*10;
     voltage = getVoltage(temperaturePin);
     degreesC = (voltage - 0.5) * 100.0;
     degreesF = degreesC * (9.0/5.0) + 32.0;
     analogWrite(heaterPWR, 90); //110
     int value = analogRead(heaterPWR);
     analogWrite(motorPWR,PWMAmount); //the pump seems to be stronger when it is 1 than 100
     /*PWMAmount += fadeAmount;
     if (PWMAmount == 100 || PWMAmount == 255)
     {
         fadeAmount = -fadeAmount;
     }
     delay(10);*/
     //digitalWrite(motorPWR, HIGH); //need to comment this out or else motor won't run
     //Serial.print("PWM:");
     //Serial.print(value);
     /*Serial.print("voltage: ");
     Serial.print(voltage);
     Serial.print("  deg C: ");
     Serial.print(degreesC);
     Serial.print("  deg F: ");
     Serial.println(degreesF);
     Serial.print("CO2 : ");*/
     Serial.println(c);
     Serial.println("");
     
     //delay(1000);
  } 
  
  float getVoltage(int pin)
  { 
      return (analogRead(pin) * 0.004882814);
  }

  
      
