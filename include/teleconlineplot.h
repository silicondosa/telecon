#pragma once

#include "teleconplot.h"
#include "linestyle.h"
#include "symbolstyle.h"

/**
 * Line plot implementation that inherits from TeleconLineScatterPlot.
 */
class TeleconLinePlot : virtual public TeleconPlot {
public:
    static const LineStyle defaultLineStyle;
    static const SymbolStyle defaultSymbolStyle;

    /**
     * Function to push a single data point (yData) into the plot at a certain time (xTimestamp).
     *
     * \param xTimestamp Time the data point was generated, in seconds. The exact interpretation of the time will depend on the implementation; the default implementation (wxChartDir) interprets it as seconds since January 1st, year 1.
     * \param yData The value that will be displayed.
     */
    virtual void pushData(double xTimestamp, double yData) = 0;

    virtual shared_ptr<const LineStyle> getLineStyle() const = 0;
};