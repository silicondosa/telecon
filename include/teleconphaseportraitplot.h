#pragma once

#include "teleconplot.h"
#include "linestyle.h"

/**
 * The user-level interface for interacting with temporal phase portraits.
 * A temporal phase portrait is a sequence of 3-dimensional points that consist of a timestamp and two values, displayed on the x- and y-axes.
 * The points may be connected by a line (by default they are), and represented with a symbol (by the default they are).
 */
class TeleconPhasePortraitPlot : virtual public TeleconPlot
{
public:
    /** The default ::LineStyle used to represent temporal phase portraits, which is a solid line, of the default color, 5 pixels wide. */
    static const LineStyle defaultLineStyle;
    /** The default ::SymbolStyle used to represent temporal phase portraits, which is a solid square of the default color, 5 pixels wide. */
    static const SymbolStyle defaultSymbolStyle;

    /**
     * Function to push a single data point (xData, yData) into the plot at a certain time (timestamp).
     *
     * \param timestamp Time the data point was generated, represented as seconds since an epoch.
     * The epoch used will depend on the implementation; the default implementation (wxChartDir) uses January 1st, year 1.
     * However, since charts display only hours, minutes, and seconds, for short time spans (less than a day), the epoch could be user-defined (for example, the beginning of the experiment which is producing data).
     * Data points must be inserted with the timestamps in ascending order (the same order that they were created).
     * \param xData The x value that will be displayed.
     * \param yData The y value that will be displayed.
     */
    virtual void pushData(double timestamp, double xData, double yData) = 0;

    /**
     * \return The ::LineStyle representing how the line connecting points (if any) should be displayed.
     */
    virtual shared_ptr<const LineStyle> getLineStyle() const = 0;
};
