#include <temperature_types.h>
#include <cmath>

TemperatureCategory temperatureClassification(float temperature)
{
  // Check for valid temperature
  if(!std::isfinite(temperature))
  {
    return TemperatureCategory::Unknown;
  }

  if (temperature < Classifications::cold)
  {
    return TemperatureCategory::Cold;
  }
  else if (temperature < Classifications::cool)
  {
    return TemperatureCategory::Cool;
  }
  else if (temperature < Classifications::mild)
  {
    return TemperatureCategory::Mild;
  }
  else if (temperature < Classifications::warm)
  {
    return TemperatureCategory::Warm;
  }
  
  return TemperatureCategory::Hot;
}