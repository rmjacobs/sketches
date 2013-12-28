/*
  The circuit:
 * LCD RS pin to digital pin 8
 * LCD Enable pin to digital pin 9
 * LCD D4 pin to digital pin 4
 * LCD D5 pin to digital pin 5
 * LCD D6 pin to digital pin 6
 * LCD D7 pin to digital pin 7
 * LCD BL pin to digital pin 10
 * KEY pin to analogl pin 0
 *Vcc pin to  +5
 *Trig pin to digital pin A1 of LCD Shield
 *Echo pin to digital pin A2 of LCD Shield
 fuction :  when the serial port sen an "a" to the Board .the Board will show" holl sainsmart "in the lcdkeypad"   
 */

#include <LiquidCrystal.h>
#include <NewPing.h>
//#define CM 1      //Centimeter
//#define INC 0     //Inch
#define TRIGGER_PIN A1      //Trig_pin
#define ECHO_PIN A2      //Echo_pin 
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

LiquidCrystal lcd(8, 13, 9, 4, 5, 6, 7);


//For our purposes will be measuring the distance from the bottom of the tank to the max fill line which is 6 3/4 inches
float tankDepth=7.75; //overall pingDepth
float safeDepth=6.75; //depth to maxfill line
float ROUNDTRIP_CM = 57.00;

void setup()
{
  lcd.clear(); 
  lcd.begin(16, 2);
  lcd.setCursor(0,0); 
  Serial.begin(115200);
  pinMode(TRIGGER_PIN,OUTPUT);       // set TP output for trigger  
  pinMode(ECHO_PIN,INPUT);        // set EP input for echo
}

void loop()
{
  delay(50);
  unsigned int uS = sonar.ping();
  float distance = uS/ROUNDTRIP_CM;
  //convert to inches
  distance = distance * 0.39370;
  //Calculate percent full based on ping depth.
  float percentFull = 100 - ((distance - (tankDepth -safeDepth))/safeDepth *100);
  //Write to display
  lcd.setCursor(0,0); 
  lcd.print(" % Full:  "); 
  lcd.print(percentFull ); 

}












