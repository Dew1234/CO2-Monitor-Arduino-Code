/*
 HeatingElementRegulation
 
 */
//#include "Adafruit_MAX31855.h" 
#include <PID_v1.h>
double Setpoint, degreesC, Output;
#include <SoftwareSerial.h>
#include "cozir.h"
SoftwareSerial nss(2,3);
COZIR czr(nss);
int heaterPWR = 6;
int heaterDIR= 7;
double setTempUpper = 240;
double setTempLower = 24;
const int temperaturePin = 0;
PID myPID(&degreesC, &Output, &Setpoint,34,2,0, DIRECT); //tweak the PID values
//P value is for driving the values, I value is for dampening, D value is for predicting where it goes
//experiment with the PID control values

void setup() 
{ 
   Serial.begin(9600);
   delay(1000);
   //czr.SetOperatingMode(CZR_POLLING);
   //czr.SetOperatingMode(CZR_STREAMING);
   //czr.CalibrateFreshAir();
   //czr.SetDigiFilter(64);
   
   degreesC = (getVoltage(temperaturePin)-0.5)*100;
   Setpoint = 27;
   //turn the PID on
   myPID.SetMode(AUTOMATIC);
   //pinMode(heaterPWR, OUTPUT);
   //pinMode(heaterDIR, OUTPUT);
   //digitalWrite(heaterDIR, HIGH);
   //analogWrite(heaterPWR, 0);
   //delay(100);
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
     myPID.Compute();
     analogWrite(heaterPWR, Output); 
     int value = analogRead(heaterPWR);
     //Serial.print("PWM:");
     //Serial.print(value);
     /*Serial.print("voltage: ");
     Serial.print(voltage);
     Serial.print("  deg C: ");
     Serial.print(degreesC);
     Serial.print("  deg F: ");
     Serial.println(degreesF); */
     //Serial.print("CO2 : ");
     Serial.println(c);
     Serial.println("");
     //delay(1000);
  } 
  
  float getVoltage(int pin)
  { 
      return (analogRead(pin) * 0.004882814);
  }

  
              
