#include "DataPoint.h"

DataPoint::DataPoint(const std::string& dateTime, double autoConsumption, double exportEnergy, double importEnergy, double consumption, double production)
    : dateTime(dateTime), autoConsumption(autoConsumption), exportEnergy(exportEnergy), importEnergy(importEnergy), consumption(consumption), production(production) {}
