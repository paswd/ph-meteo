#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

#define BMP_SCK 13
#define BMP_MISO 12
#define BMP_MOSI 11 
#define BMP_CS 10

#define DHTPIN A0

//Adafruit_BMP280 bmp; // I2C
Adafruit_BMP280 bmp(BMP_CS); // hardware SPI
//Adafruit_BMP280 bmp(BMP_CS, BMP_MOSI, BMP_MISO,  BMP_SCK);

//DHT dht(DHTPIN, DHT22);
float humVal = 0;

float calc_hum(float val){ 
  float H; 
  H = 0.163 * val;
  //RH10 = val + 6*val/10 + 3*val/100; = 0.163*val 
  return(H); 
} 

void setup() {
  Serial.begin(9600);
  //Serial.println(F("BMP280 test"));
  
  if (!bmp.begin()) {  
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    while (1);
  }
}

void loop() {
  if (Serial.available() > 0) {
    int in_byte = Serial.read();
    if (in_byte != '1') {
      return;
    }
    Serial.print(F("Temperature = "));
    Serial.print(bmp.readTemperature());
    Serial.println(" *C");
    
    Serial.print(F("Pressure = "));
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");

    Serial.print(F("Approx altitude = "));
    Serial.print(bmp.readAltitude(1013.25)); // this should be adjusted to your local forcase
    Serial.println(" m");

    humVal = calc_hum(analogRead(DHTPIN));
    Serial.print(F("Humedad = "));
    Serial.print(humVal);
    Serial.println(" %");
    Serial.println();
    
    //delay(2000);
  }
}
