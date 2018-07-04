#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <DHT.h>

#define BMP_SCK 13
#define BMP_MISO 12
#define BMP_MOSI 11 
#define BMP_CS 10

#define DHTPIN 2

//Adafruit_BMP280 bmp; // I2C
Adafruit_BMP280 bmp(BMP_CS); // hardware SPI
//Adafruit_BMP280 bmp(BMP_CS, BMP_MOSI, BMP_MISO,  BMP_SCK);

DHT dht(DHTPIN, DHT22);

void setup() {
  Serial.begin(9600);
  Serial.println(F("BMP280 test"));
  
  if (!bmp.begin()) {  
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    while (1);
  }

  dht.begin();
}

void loop() {
    Serial.print(F("Temperature = "));
    Serial.print(bmp.readTemperature());
    Serial.println(" *C");
    
    Serial.print(F("Pressure = "));
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");

    Serial.print(F("Approx altitude = "));
    Serial.print(bmp.readAltitude(1013.25)); // this should be adjusted to your local forcase
    Serial.println(" m");
    float h = dht.readHumidity();

// Считываем температуру

// Проверка удачно прошло ли считывание.

    if (!isnan(h)) {

        Serial.print(F("Humidity = "));
        Serial.println(h);        

    } else {
        Serial.println("Не удается считать показания влажности");
    }
    
    Serial.println();
    delay(2000);
}
