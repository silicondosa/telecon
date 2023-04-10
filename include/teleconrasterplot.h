#pragma once

#include "teleconplot.h"

class TeleconRasterPlot : virtual public TeleconPlot {
public:
    /**
     * Function to push a single activation data point into the plot at a certain time (xTimestamp).
     *
     * \param xTimestamp time the data point was generated, in seconds. The exact interpretation of the time will depend on the implementation; the default implementation (wxChartDir) interprets it as seconds since January 1st, year 1.
     * \param isActive true if the data point is active and should be displayed. If false the data point will not be displayed.
     */
    virtual void pushData(double xTimestamp, bool isActive = true) = 0;

    /**
     * \return True if the symbol is filled, or false if the center of th symbol will be transparent.
     */
    virtual bool isSymbolFilled() const = 0;

    /**
     * Getter function to return the type of symbol used (e.g., square, circle, triangle).
     *
     * \return Symbol, in the format described in TeleconRealtimeChart::addLinePlot.
     */
    virtual int getSymbol() const = 0;

    /**
     * \return Symbol size in pixels.
     */
    virtual int getSymbolSize() const = 0;
};
