#include <iostream>
#include <fstream>
#include <sstream>
#include "DataPoint.h"
#include "DataTree.h"

int main() {
    std::ifstream file("Chart Export.csv");
    std::string line;
    DataTree dataTree;

    // Pomijamy pierwszą linię
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string dateTime;
        std::string autoConsumptionStr, exportEnergyStr, importEnergyStr, consumptionStr, productionStr;

        std::getline(ss, dateTime, ',');
        std::getline(ss, autoConsumptionStr, ',');
        std::getline(ss, exportEnergyStr, ',');
        std::getline(ss, importEnergyStr, ',');
        std::getline(ss, consumptionStr, ',');
        std::getline(ss, productionStr, ',');

        // Usuwamy cudzysłowy z wartości liczbowych
        autoConsumptionStr.erase(remove(autoConsumptionStr.begin(), autoConsumptionStr.end(), '\"'), autoConsumptionStr.end());
        exportEnergyStr.erase(remove(exportEnergyStr.begin(), exportEnergyStr.end(), '\"'), exportEnergyStr.end());
        importEnergyStr.erase(remove(importEnergyStr.begin(), importEnergyStr.end(), '\"'), importEnergyStr.end());
        consumptionStr.erase(remove(consumptionStr.begin(), consumptionStr.end(), '\"'), consumptionStr.end());
        productionStr.erase(remove(productionStr.begin(), productionStr.end(), '\"'), productionStr.end());

        double autoConsumption = std::stod(autoConsumptionStr);
        double exportEnergy = std::stod(exportEnergyStr);
        double importEnergy = std::stod(importEnergyStr);
        double consumption = std::stod(consumptionStr);
        double production = std::stod(productionStr);

        auto dataPoint = std::make_shared<DataPoint>(dateTime, autoConsumption, exportEnergy, importEnergy, consumption, production);
        dataTree.addDataPoint(dataPoint);
    }

    // Tutaj można dodać kod do analizy danych

    return 0;
}
