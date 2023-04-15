#pragma once

#include "teleconplot.h"

/**
 * Raster plot implementation, inherits from TeleconPlot.
 */
class TeleconRasterPlot : virtual public TeleconPlot {
public:

    /**
     * Function to push a single activation data point into the plot at a certain time (xTimestamp).
     *
     * \param xTimestamp time the data point was generated, in seconds. The exact interpretation of the time will depend on the implementation; the default implementation (wxChartDir) interprets it as seconds since January 1st, year 1.
     * \param isActive true if the data point is active and should be displayed. If false the data point will not be displayed.
     */
    virtual void pushData(double xTimestamp, bool isActive = true) = 0;
};
