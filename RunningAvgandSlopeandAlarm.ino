
/*
 HeatingElementRegulation
 
 */
//#include "Adafruit_MAX31855.h" 
#include <SoftwareSerial.h>
#include "RunningAverage.h"
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
const int buzzerPin = 13;

int samples = 0;
RunningAverage myRA(75); //take 75 readings
int CO2readings[100]; //can't be too large or else the program won't run
int index = 0;
int slope = 0;
int x = 0; 
int y = 0;

void setup() 
{ 
   Serial.begin(9600);
   pinMode (buzzerPin, OUTPUT);
   //Serial.println(RUNNINGAVERAGE_LIB_VERSION);
   //myRA.fillValue(100,5);
   myRA.clear();
   delay(1000);
   //pinMode(motorPWR, OUTPUT);
   //czr.SetOperatingMode(CZR_POLLING);
   //czr.SetOperatingMode(CZR_STREAMING);
   //czr.CalibrateFreshAir();
   //czr.SetDigiFilter(64);
   
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
     
     myRA.addValue(c);
     if(samples == 0)
     {
         Serial.println("Slope: = 0");
         //float Average1 = myRA.getElement(samples);
     }
     if(samples > 0)
     {
          float Average1 = myRA.getElement(samples-1);
          float Average2 = myRA.getElement(samples);
          slope = Average2- Average1;
          Serial.println(slope);
     }
     
     samples++;
     int avg_CO2 = myRA.getAverage();
     Serial.print("Running Average:");
     Serial.println(avg_CO2);
     if(samples == 75)
     {
       samples=0;
       myRA.clear();
     }
     if (slope>=20 || slope<= -20)
     {
        x++;
        if(x>3 && slope>=20 && slope <50)
        {
        y=0;
        Serial.println("CO2 level is increasing");
        tone(buzzerPin, 100, 1000);
        }
        if (slope>=50)
        {
            Serial.println("Exercising. False Alarm"); 
            //tone(buzzerPin, 100, 1000);
        }
        if (x>3 && slope<=-20)
        {
          y=0;
          Serial.println("CO2 level is decreasing");
        }
     }
     else
     {
          y++;
          if (y>=3) //check to see if it is back at equilibrium
          {
            x=0;
            Serial.println("CO2 level at equilibrium");
          } 
     }
     
     
     Serial.println(c);
     Serial.println("");
     
     /*if (index = 0)
     {
        CO2readings[index] = c;
        index++;
        //x++;
        Serial.println("Slope:0"); 
     }
     
     if (1 <= index < 999)
     {
         CO2readings[index] = c;
         Serial.print("Slope: ");
         Serial.println(CO2readings[index]-CO2readings[index-1]);
         //x++;
         index++;
         //calculateSlope(index, CO2readings[x], (index-1), CO2readings[x-1]);  
     }
     else //wrap from the beginning
     {
         index = 0;
         memset(CO2readings, 0, sizeof(CO2readings));
     }
     //delay(1000);*/
  } 
  
  float getVoltage(int pin)
  { 
      return (analogRead(pin) * 0.004882814);
  }

  int calculateSlope(int x1, int y1, int x2, int y2)
 {
   return ((y2-y1)/(x2-x1));
 }
  
      
