#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

#define BMP_SCK 13
#define BMP_MISO 12
#define BMP_MOSI 11 
#define BMP_CS 10

#define DHTPIN A0

#define TEMP_ARR_LEN 3
#define PRESS_ARR_LEN 6
#define ALT_ARR_LEN 4
#define HUM_ARR_LEN 3

//TOTAL STRING 17 BYTES

//Adafruit_BMP280 bmp; // I2C
Adafruit_BMP280 bmp(BMP_CS); // hardware SPI
//Adafruit_BMP280 bmp(BMP_CS, BMP_MOSI, BMP_MISO,  BMP_SCK);

float calc_hum(float val) { 
  float H; 
  H = 0.163 * val;
  //RH10 = val + 6*val/10 + 3*val/100; = 0.163*val 
  return(H); 
}

long floatToLong(float val) {
  long res = (long) val;
  long md = (long) (val * 10);
  md %= 10;
  if (md >= 5) {
    res++;
  }
  return res;
}

char numToChar(long num) {
  num %= 10;
  return (char) (num + '0');
}

void numToCharArr(long num, char *arr, int len) {
  for (int i = len - 1; i >= 0; i--) {
    arr[i] = numToChar(num);
    num /= 10;
  }
}
void printCharArr(char *arr, int len) {
  for (int i = 0; i < len; i++) {
    Serial.print(arr[i]);
  }
}

void setup() {
  Serial.begin(9600);
  
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
    long tempVal = floatToLong(bmp.readTemperature());
    long pressVal = floatToLong(bmp.readPressure());
    long altVal = floatToLong(bmp.readAltitude(1013.25));
    long humVal = floatToLong(calc_hum(analogRead(DHTPIN)));

    char tempArr[TEMP_ARR_LEN];
    char pressArr[PRESS_ARR_LEN];
    char altArr[ALT_ARR_LEN];
    char humArr[HUM_ARR_LEN];

    numToCharArr(tempVal, tempArr, TEMP_ARR_LEN);
    numToCharArr(pressVal, pressArr, PRESS_ARR_LEN);
    numToCharArr(altVal, altArr, ALT_ARR_LEN);
    numToCharArr(humVal, humArr, HUM_ARR_LEN);

    printCharArr(tempArr, TEMP_ARR_LEN);
    printCharArr(pressArr, PRESS_ARR_LEN);
    printCharArr(altArr, ALT_ARR_LEN);
    printCharArr(humArr, HUM_ARR_LEN);
    Serial.print('\n');
  }
}
