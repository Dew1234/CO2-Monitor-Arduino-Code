#include <SoftwareSerial.h>
#include "cozir.h"
#include <Time.h> //library for recording the current time

SoftwareSerial nss(2,3);
COZIR czr(nss);

void setup()
{
 Serial.begin(9600); 
 delay(5000);
 //czr.SetOperatingMode(CZR_POLLING);
 //czr.SetOperatingMode(CZR_STREAMING);
 //czr.CalibrateFreshAir();
// czr.SetDigiFilter(64);
}

void loop()
{
 delay(1000);
 float t = czr.Celsius();
 float f = czr.Fahrenheit();
 float h = czr.Humidity();
 double c = czr.CO2()*10; //changed it to double so it wouldn't overflow as easily
 //multiplied by ten to get correct ppm value
 int digi = czr.GetDigiFilter();

 if (c > 3000) 
   {
     Serial.print("Warning: CO2 levels are high");
   }
 /*use this to indicate warnings with the specific CO2 levels
 Can replace it with a different warning if needed */
 
 Serial.print("Celcius : ");Serial.println(t);
 Serial.print("Fahrenheit : ");Serial.println(f);
 Serial.print("Humidity : ");Serial.println(h);
 Serial.print("CO2 : ");Serial.println(c);
 Serial.print("Digital Filter : ");Serial.println(digi); 
 Serial.println("");
}
