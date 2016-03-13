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
double setTempUpper = 240;
double setTempLower = 24;
const int temperaturePin = 0;

void setup() 
{ 
   Serial.begin(9600);
   delay(1000);
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
     analogWrite(heaterPWR, 110); 
     int value = analogRead(heaterPWR);
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

  
//PID control
/**void PID(double Actual, double SetPt, boolean reset){
  double kP=100, kI=0, kD=10;
  static double Previous_Error=0, Integral=0, t1=0;
  if(reset==true){
    Previous_Error=0;
    Integral=0;
    t1=0;
  }
  double t2 = millis();
  double dt = (t2-t1)/1000;
  double Error = SetPt-Actual;
  double P = kP*Error;
  double I = kI*(Integral + Error*dt);
  double D = kD*((Error - Previous_Error)/dt);
  double heat = (P+I+D);
  heat = saturation(heat);
  analogWrite(heaterPWR,heat);
  Previous_Error=Error;
  Integral += Error*dt;
  t1=t2;
  clock=millis();
  if(clock>=nextPrint){
    nextPrint=clock+1000;
    Serial.print("C = ");
    Serial.println(thermocouple.readCelsius());
    Serial.print("Heat output = ");
    Serial.print(heat/255*100);
    Serial.println("%");
  }  
}
double saturation(double heat){
  if(heat<0){
    return 0;
  }
  else if(heat>255){
    return 255;
  }
  else{
    return heat;
  }
}    */                  
