#include <cmath>
#include "altitude.h"
#include "sensorData.h"



namespace AltitudeClassifications
{
  // Altitude threshold for classification
  inline constexpr float highAltitude = 1500.0f;
}

SensorData altitudeClassification(float altitude, const std::string& sensorName)
{
  if(!std::isfinite(altitude))
  {
    return SensorData(altitude, Category::Invalid, sensorName);
  }

  if (altitude > AltitudeClassifications::highAltitude)
  {
    return SensorData(altitude, Category::HighAltitude, sensorName);
  }
  else
  {
    return SensorData(altitude, Category::LowAltitude, sensorName);
  }
}