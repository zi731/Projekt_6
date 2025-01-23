#ifndef DATAPOINT_H
#define DATAPOINT_H

#include <string>

class DataPoint {
public:
    std::string dateTime;
    double autoConsumption;
    double exportEnergy;
    double importEnergy;
    double consumption;
    double production;

    DataPoint(const std::string& dateTime, double autoConsumption, double exportEnergy, double importEnergy, double consumption, double production);
};

#endif // DATAPOINT_H
