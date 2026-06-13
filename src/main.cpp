#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp;

// put function declarations here:
std::string generateMessage(float, float, float);

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

  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Pressure = ");
  Serial.print(pressure);
  Serial.println(" hpd");

  Serial.print("Approx Altitude = ");
  Serial.print(altitude);
  Serial.println(" m");

  std::string result = generateMessage(temperature, pressure, altitude);
  Serial.print("Message = ");
  Serial.println(result.c_str());

  Serial.println();
  delay(2000); // Read every 2 seconds
}

std::string generateMessage(float temperature, float pressure, float altitude)
{
  // Convert pressure to sea level pressure for correct classification
  float seaLevelPressure = bmp.seaLevelForAltitude(altitude, pressure);

  TemperatureCategory tempMsg = temperatureClassification(temperature);
  std::string pressureMsg = pressureClassification(seaLevelPressure);
  std::string altitudeMsg = altitudeClassification(altitude);



  return tempMsg + " " + pressureMsg + " " + altitudeMsg;
}

class SensorData
{
  SensorData(TemperatureCategory t, std::string p, std::string a) : temperature(t), pressure(p), altitude(a) {}
  TemperatureCategory temperature;
  TemperatureCategory pressure;
  TemperatureCategory altitude;
};

namespace Classifications
{
  // Temperature thresholds for classification
  inline constexpr float COLD = 0.0f;
  inline constexpr float COOL = 10.0f;
  inline constexpr float MILD = 18.0f;
  inline constexpr float WARM = 27.0f;

  // Altitude threshold for classification
  inline constexpr float HIGH_ALTITUDE = 1500.0f;

  // Pressure thresholds for classification
  inline constexpr float VERY_LOW_PRESSURE = 948.0f;
  inline constexpr float LOW_PRESSURE = 982.0f;
  inline constexpr float NORMAL_PRESSURE = 1009.0f;
  inline constexpr float HIGH_PRESSURE = 1023.0f;
  inline constexpr float VERY_HIGH_PRESSURE = 1040.0f;
}

std::string altitudeClassification(float altitude)
{
  if (altitude > Classifications::HIGH_ALTITUDE)
  {
    return "High Altitude";
  }
  else
  {
    return "Low Altitude";
  }
}


std::string pressureClassification(float seaLevelPressure)
{
  if (seaLevelPressure >= Classifications::VERY_LOW_PRESSURE && seaLevelPressure < Classifications::LOW_PRESSURE)
  {
    return "Very Low Pressure";
  }
  else if (seaLevelPressure >= Classifications::LOW_PRESSURE && seaLevelPressure < Classifications::NORMAL_PRESSURE)
  {
    return "Low Pressure";
  }
  else if (seaLevelPressure >= Classifications::NORMAL_PRESSURE && seaLevelPressure < Classifications::HIGH_PRESSURE)
  {
    return "Normal Pressure";
  }
  else if (seaLevelPressure >= Classifications::HIGH_PRESSURE && seaLevelPressure < Classifications::VERY_HIGH_PRESSURE)
  {
    return "High Pressure";
  }
  else if (seaLevelPressure >= Classifications::HIGH_PRESSURE && seaLevelPressure < Classifications::VERY_HIGH_PRESSURE)
  {
    return "Very High Pressure";
  }
  else // Replace with error handling
  {
    return "Unknown";
  }
}