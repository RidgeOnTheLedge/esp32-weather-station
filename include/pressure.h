#pragma once

#include "sensorData.h"
#include <string>

SensorData pressureClassification(float seaLevelPressure, const std::string& sensorName);