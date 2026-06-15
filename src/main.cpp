#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <sensorData.h>

// Sensor Methods and Objects
#include "temperature.h"
#include "pressure.h"
#include "altitude.h"
#include "sensorData.h"

Adafruit_BMP280 bmp;

void setup()
{
  Serial.begin(9600);
  while (!Serial);

  while (!bmp.begin(0x76))
  {
    Serial.println("BMP280 sensor, not found");
    delay(1000);
  }

  Serial.println("BMP280 Sensor Initialized");

  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
}

void loop()
{
  float temperature = bmp.readTemperature();    // Celsius
  float pressure = bmp.readPressure() / 100.0F; // mb/hPa
  float altitude = bmp.readAltitude(1013.25);   // Meters

  SensorData temperatureData = temperatureClassification(temperature, "BMP280");
  SensorData pressureData = pressureClassification(pressure, "BMP280");
  SensorData altitudeData = altitudeClassification(altitude, "BMP280");

  Serial.print("Temperature = ");
  Serial.print(temperatureData.getReading());
  Serial.println(" °C");

  Serial.print("Pressure = ");
  Serial.print(pressureData.getReading());
  Serial.println(" hpd");

  Serial.print("Approx Altitude = ");
  Serial.print(altitudeData.getReading());
  Serial.println(" m");
  Serial.println();
  
  delay(2000); // Read every 2 seconds
}
