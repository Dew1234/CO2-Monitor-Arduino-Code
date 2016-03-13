// This program shown how to control arduino from PC Via Bluetooth
// Connect ...
// arduino>>bluetooth
// D11   >>>  Rx
// D10   >>>  Tx
//Written By Mohannad Rawashdeh
//for http://www.genotronex.com/

// you will need arduino 1.0.1 or higher to run this sketch

#include <SoftwareSerial.h>// import the serial library
#include <HardwareSerial.h>
#include "cozir.h"
SoftwareSerial nss(2,3);
COZIR czr(nss); 
int heaterPWR = 6;
int heaterDIR= 7;
int motorPWR = 9;
int PWMAmount = 10;
int fadeAmount=50;
double setTempUpper = 240;
double setTempLower = 24;
const int temperaturePin = 0;

SoftwareSerial Genotronex(10, 11); // RX, TX
int ledpin=13; // led on D13 will show blink on / off
int BluetoothData; // the data given from Computer

void setup() {
  // put your setup code here, to run once:
  Genotronex.begin(9600);
  Genotronex.println("Bluetooth On please press 1 or 0 blink LED ..");
  pinMode(ledpin,OUTPUT);
  //println(Serial.list());
}

void loop() {
  // put your main code here, to run repeatedly:
   if (Genotronex.available())
   {
         BluetoothData=Genotronex.read();
   if(BluetoothData=='1')
   {   // if number 1 pressed ....
       delay(1000);
         float voltage, degreesC, degreesF;
         float t = czr.Celsius();
         double c = czr.CO2()*10;
         //voltage = getVoltage(temperaturePin);
         degreesC = (voltage - 0.5) * 100.0;
         degreesF = degreesC * (9.0/5.0) + 32.0;
         analogWrite(heaterPWR, 90); //110
         int value = analogRead(heaterPWR);
         analogWrite(motorPWR,PWMAmount); //the pump seems to be stronger when it is 1 than 100
         Serial.println(c);
         Serial.println("");
   }
  if (BluetoothData=='0')
  {// if number 0 pressed ....
      Genotronex.println("No Readings");
  }
  
  /* float getVoltage(int pin)
  { 
      return (analogRead(pin) * 0.004882814);
  }*/
}
delay(100);// prepare for next data ...
}
