#ifndef DATATREE_H
#define DATATREE_H

#include "DataPoint.h"
#include <map>
#include <vector>
#include <memory>

class DataTree {
public:
    void addDataPoint(std::shared_ptr<DataPoint> dataPoint);

private:
    struct Quarter {
        std::vector<std::shared_ptr<DataPoint>> dataPoints;
    };

    struct Day {
        std::map<int, Quarter> quarters;
    };

    struct Month {
        std::map<int, Day> days;
    };

    struct Year {
        std::map<int, Month> months;
    };

    std::map<int, Year> years;
};

#endif // DATATREE_H
