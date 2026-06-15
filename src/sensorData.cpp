#include "sensorData.h"

SensorData::SensorData(float reading, Category category, const std::string& sensorName)
    : reading_(reading), category_(category), sensorName_(sensorName) {}


float SensorData::getReading() const
{
    return reading_;
}

Category SensorData::getCategory() const
{
    return category_;
}

const std::string& SensorData::getSensorName() const
{
    return sensorName_;
}