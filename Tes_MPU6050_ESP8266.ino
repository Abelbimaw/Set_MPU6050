#include<Wire.h>
//#define BLYNK_PRINT Serial
//#include <Blynk.h>
#include <ESP8266WiFi.h>
//#include <BlynkSimpleEsp8266.h>
 
//char auth[] = "LHvT-tj0Uoy9xXfjGshKOyRk_cVYZhZd";       // You should get Auth Token in the Blynk App.
char ssid[] = "Alsan";                       // Your WiFi credentials.
char pass[] = "1234567890";
 
const int MPU_addr=0x68;
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
 
int minVal=265;
int maxVal=402;
 
double x;
double y;
double z;
 
void setup(){
Wire.begin();
Wire.beginTransmission(MPU_addr);
Wire.write(0x6B);
Wire.write(0);
Wire.endTransmission(true);
Serial.begin(9600);
//Blynk.begin(auth, ssid, pass);
 }
void loop(){
//Blynk.run();
Wire.beginTransmission(MPU_addr);
Wire.write(0x3B);
Wire.endTransmission(false);
Wire.requestFrom(MPU_addr,14,true);
AcX=Wire.read()<<8|Wire.read();
AcY=Wire.read()<<8|Wire.read();
AcZ=Wire.read()<<8|Wire.read();
int xAng = map(AcX,minVal,maxVal,-90,90);
int yAng = map(AcY,minVal,maxVal,-90,90);
int zAng = map(AcZ,minVal,maxVal,-90,90);
 
x= RAD_TO_DEG * (atan2(-yAng, -zAng)+PI);
y= RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);
z= RAD_TO_DEG * (atan2(-yAng, -xAng)+PI);
 
Serial.print("AngleX= ");
Serial.println(x);
 
Serial.print("AngleY= ");
Serial.println(y);
 
Serial.print("AngleZ= ");
Serial.println(z);
Serial.println("-----------------------------------------");
 
//Blynk.virtualWrite(V2, x);
//Blynk.virtualWrite(V3, y);
//Blynk.virtualWrite(V4, z);
 
delay(1000);
}
