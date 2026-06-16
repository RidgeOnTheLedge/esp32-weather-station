#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <sensorData.h>
#include <SD.h>
#include <RTClib.h>

// Sensor Methods and Objects
#include "temperature.h"
#include "pressure.h"
#include "altitude.h"
#include "sensorData.h"

#define AOUT_PIN A6
#define PIN_SPI_CS D10

Adafruit_BMP280 bmp;
File myFile;
RTC_DS3231 rtc;
char fileName[64];
DateTime now;

char daysOfWeek[7][12] = {
    "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup()
{
  Serial.begin(9600);
  while (!Serial)
    ;

  if (!SD.begin(PIN_SPI_CS))
  {
    while (1)
    {
      Serial.println(F("SD CARD FAILED, OR NOT PRESENT!"));
      delay(1000);
    }
  }

  Serial.println(F("SD Card Initialized."));

  while (!bmp.begin(0x76))
  {
    Serial.println("BMP280 sensor, not found");
    delay(1000);
  }

  Serial.println("BMP280 Sensor Initialized");

  while (!rtc.begin())
  {
    Serial.println("RTC not found");
    delay(1000);
  }

  Serial.println("RTC Initialized");

  while (!SD.begin(PIN_SPI_CS))
  {
    Serial.println("SD init failed");
    delay(1000);
  }

  Serial.println("SD Card Initialized");

  uint32_t cardSize = SD.cardSize() / (1024 * 1024);
  String str = "SDCard Size: " + String(cardSize) + "MB";
  Serial.println(str);

  now = rtc.now();

  snprintf(fileName, sizeof(fileName),
           "/enviromental_data_%04d-%02d-%02d.csv",
           now.year(), now.month(), now.day());

  if (!SD.exists(fileName))
  {
    File f = SD.open(fileName, FILE_WRITE);
    if (f)
    {
      f.println("date,day,time,moisture,temperature_C,pressure_hPa,altitude_m");
      f.close();
      Serial.println("Header written");
    }
  }

  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
}

void loop()
{
  now = rtc.now();
  // open file for writing

  float temperature = bmp.readTemperature();    // Celsius
  float pressure = bmp.readPressure() / 100.0F; // mb/hPa
  float altitude = bmp.readAltitude(1013.25);   // Meters

  SensorData temperatureData = temperatureClassification(temperature, "BMP280");
  SensorData pressureData = pressureClassification(pressure, "BMP280");
  SensorData altitudeData = altitudeClassification(altitude, "BMP280");

  myFile = SD.open("/esp32.txt", FILE_WRITE);

  Serial.printf("%04d-%02d-%02d,%s,%02d:%02d:%02d,%d,%.2f,%.2f,%.2f\n",
                now.year(), now.month(), now.day(),
                daysOfWeek[now.dayOfTheWeek()],
                now.hour(), now.minute(), now.second(),
                analogRead(AOUT_PIN),
                temperatureData.getReading(),
                pressureData.getReading(),
                altitudeData.getReading());
  if (myFile)
  {
    myFile.printf("%04d-%02d-%02d,%s,%02d:%02d:%02d,%d,%.2f,%.2f,%.2f\n",
                  now.year(), now.month(), now.day(),
                  daysOfWeek[now.dayOfTheWeek()],
                  now.hour(), now.minute(), now.second(),
                  analogRead(AOUT_PIN),
                  temperatureData.getReading(),
                  pressureData.getReading(),
                  altitudeData.getReading());

    myFile.close();
  }
  else
  {
    Serial.println("File open failed");
  }
  
  delay(2000); // Read every 2 seconds
}
