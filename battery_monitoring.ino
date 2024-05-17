#define BLYNK_TEMPLATE_ID "TMPL6GrvH6a2T"
#define BLYNK_TEMPLATE_NAME "Battery monitoring"
#define BLYNK_AUTH_TOKEN "ARUwZKxVsDBkORHjDmX6VP2Mneq0QFDf"

#include <SoftwareSerial.h>
mySerial Software(10, 11); //virtual Monitor PIN

#include <BlynkSimpleStream.h>
#include <Blynk.h>

char auth[] = BLYNK_AUTH_TOKEN;
BlynkTimer timer;

//battery voltage pin
const int analogPin = A0;


void setup() {
  Serial.begin(9600); //serial monitor
  mySerial.begin(9600); //virtual terminal
  Blynk.begin(Serial, auth);

  timer.setInterval(1000L, myTimerEvent);
}


void myTimerEvent() {
  int sensorValue = analogRead(analogPin);
  float voltage = sensorValue * (5.00 / 1023.00) * 2; //convert ADC value to voltage

calculate battery percentage (min 2.7V max 4.2V)
  float batteryPercentage = (voltage - 2.7) * 100 / (4.2 - 2.7);
  if (batteryPercentage > 100) batteryPercentage = 100;
  if (batteryPercentage < 0) batteryPercentage = 0;

  mySerial.print("ADC Value: ");
  mySerial.print(sensorValue);
  mySerial.print(", Battery Voltage: ");
  mySerial.print(voltage);
  mySerial.print(" V, ");
  mySerial.print("Battery Percentage: ");
  mySerial.print(batteryPercentage);
  mySerial.println(" %");

  Blynk.virtualWrite(V0, voltage); 
  Blynk.virtualWrite(V1, batteryPercentage);
}


void loop() {
  Blynk.run();
  timer.run();
}
