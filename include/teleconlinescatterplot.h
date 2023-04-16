#pragma once

#include "teleconplot.h"

/**
 * Plot implementation that takes in data as data + timestamp, inherits from TeleconPlot.
 * Only line plots and scatter plots use this type of data for now.
 */
class TeleconLineScatterPlot : virtual public TeleconPlot {
public:
    /**
     * Function to push a single data point (yData) into the plot at a certain time (xTimestamp).
     *
     * \param xTimestamp Time the data point was generated, in seconds. The exact interpretation of the time will depend on the implementation; the default implementation (wxChartDir) interprets it as seconds since January 1st, year 1.
     * \param yData The value that will be displayed.
     */
    virtual void pushData(double xTimestamp, double yData) = 0;
};