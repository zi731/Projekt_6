#include "DataTree.h"
#include <sstream>
#include <iomanip>

void DataTree::addDataPoint(std::shared_ptr<DataPoint> dataPoint) {
    // Parse the date and time from the dataPoint
    std::istringstream ss(dataPoint->dateTime);
    int day, month, year, hour, minute;
    char delimiter;
    ss >> day >> delimiter >> month >> delimiter >> year >> hour >> delimiter >> minute;

    // Determine the quarter based on the hour and minute
    int quarter = (hour * 60 + minute) / 360 + 1;

    // Add the data point to the appropriate place in the tree
    years[year].months[month].days[day].quarters[quarter].dataPoints.push_back(dataPoint);
}
