#pragma once

#include <string>


enum class Category 
{ 
    Cold, Cool, Mild, Warm, Hot, 
    HighAltitude, LowAltitude, 
    VeryLowPressure, LowPressure, NormalPressure, HighPressure, VeryHighPressure,
    Invalid
};


class SensorData{
private:
    
    float reading_;
    Category category_;
    std::string sensorName_;
    
public:
    SensorData(float reading, Category category, const std::string& sensorName);

    float getReading() const;
    Category getCategory() const;
    const std::string& getSensorName() const;
};