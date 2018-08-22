#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561_U.h>
#include <Wire.h>
#include <BH1750.h>
#include <ELECHOUSE_CC1101.h>
#define panelsNumber 3  //this number must not exceed the number of analog inputs of the Arduino board subtracted by 3
                         //because it needs two analog inputs for the light detector and the current detector
int voltage[panelsNumber],xvolt;
int current;
float valeur;
int analogInputc = panelsNumber;

float R1 = 331000.0; // resistance of R1 (331K)
float R2 = 20000.00; // resistance of R2 (20K)

byte  measurements[2*panelsNumber+3];

BH1750 lightMeter(0x23);

void setup() {
  Serial.begin(9600);
  for(int i=0;i<panelsNumber;i++)
  pinMode(i, INPUT);
  pinMode(analogInputc, INPUT);
  ELECHOUSE_cc1101.Init();

  // Initialize the I2C bus (BH1750 library doesn't do this automatically)
  Wire.begin();
  // On esp8266 you can select SCL and SDA pins using Wire.begin(D4, D3);
  // begin returns a boolean that can be used to detect setup problems.
  if (lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE)) {
    Serial.println(F("begin"));
  }
  else {
    Serial.println(F("Error initialising BH1750"));
  }

}
void loop() {
/***************************************************************/
  // reading light intensity  
  uint16_t lux = lightMeter.readLightLevel();
  measurements[2*panelsNumber+2] = lux;
/***************************************************************/
  // Voltage are Sensed 10000 Times for precision  
  for(int i=0;i<panelsNumber;i++){
    valeur=0.0;
    for (int x = 0; x < 10000; x++){
      xvolt=(analogRead(i) * 5) / 1024.0;
      valeur=valeur+(xvolt * 7 * (R1 + R2) / R2);
      delay(1);
    }
    valeur=valeur/10000.0;
    voltage[i]=100*valeur;
    measurements[2*i]=highByte(voltage[i]);
    measurements[2*i+1]=lowByte(voltage[i]);       
  }
/***************************************************************/
  // Current is Sensed 10000 Times for precision
  valeur=0.0;
  for (int x = 0; x < 10000; x++){
    valeur = (valeur + (.0049 * analogRead(analogInputc))); 
    delay(1);
  }
  valeur=valeur/10000.0;
  valeur = (valeur - 2.5) / 0.19; // Sensed voltage is converter to current
  current=valeur*100;
  measurements[2*panelsNumber]=highByte(current);
  measurements[2*panelsNumber+1]=lowByte(current);
  /***************************************************************/
  //data sending 
  ELECHOUSE_cc1101.SendData(measurements, 2*panelsNumber+3);
  delay(1000);
}



