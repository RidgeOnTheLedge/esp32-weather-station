#include <cmath>
#include "pressure.h"
#include "sensorData.h"

namespace PressureClassifications
{
  // Pressure thresholds for classification
  inline constexpr float veryLowPressure = 948.0f;
  inline constexpr float lowPressure = 982.0f;
  inline constexpr float normalPressure = 1009.0f;
  inline constexpr float highPressure = 1023.0f;
}

SensorData pressureClassification(float seaLevelPressure, const std::string& sensorName)
{
    if(!std::isfinite(seaLevelPressure))
    {
        return SensorData(seaLevelPressure, Category::Invalid, sensorName);
    }

  if (seaLevelPressure < PressureClassifications::veryLowPressure)
  {
    return SensorData(seaLevelPressure, Category::VeryLowPressure, sensorName);
  }
  else if (seaLevelPressure < PressureClassifications::lowPressure)
  {
    return SensorData(seaLevelPressure, Category::LowPressure, sensorName);
  }
  else if (seaLevelPressure < PressureClassifications::normalPressure)
  {
    return SensorData(seaLevelPressure, Category::NormalPressure, sensorName);
  }
  else if (seaLevelPressure < PressureClassifications::highPressure)
  {
    return SensorData(seaLevelPressure, Category::HighPressure, sensorName);
  }

  return SensorData(seaLevelPressure, Category::VeryHighPressure, sensorName);
}