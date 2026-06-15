#include <cmath>

#include "temperature.h"
#include "sensorData.h"
namespace TemperatureClassifications
{
  // Temperature thresholds for classification
  inline constexpr float cold = 0.0f;
  inline constexpr float cool = 10.0f;
  inline constexpr float mild = 18.0f;
  inline constexpr float warm = 27.0f;
}

SensorData temperatureClassification(float temperature, const std::string& sensorName)
{
  // Check for valid temperature
  if(!std::isfinite(temperature))
  {
    return SensorData(temperature, Category::Invalid, sensorName);
  }

  if (temperature < TemperatureClassifications::cold)
  {
    return SensorData(temperature, Category::Cold, sensorName);
  }
  else if (temperature < TemperatureClassifications::cool)
  {
    return SensorData(temperature, Category::Cool, sensorName);
  }
  else if (temperature < TemperatureClassifications::mild)
  {
    return SensorData(temperature, Category::Mild, sensorName);
  }
  else if (temperature < TemperatureClassifications::warm)
  {
    return SensorData(temperature, Category::Warm, sensorName);
  }
  
  return SensorData(temperature, Category::Hot, sensorName);
}