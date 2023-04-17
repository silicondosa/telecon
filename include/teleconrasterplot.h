#pragma once

#include "teleconplot.h"

/**
 * The user-level interface for interacting with raster plots.
 * A raster plot has a y-value, and is a sequence of 2-dimensional points that consist of a timestamp and an activation boolean:
 * if the activation is true, a point will be displayed at the given timestamp and y-value. Otherwise no point will be displayed.
 * Designed for e.g. neuron activation plots.
 */
class TeleconRasterPlot : virtual public TeleconPlot {
public:
    /** The default ::SymbolStyle used to represent raster plots, which is a solid circle of the default color, 1 pixel wide. */
    static const SymbolStyle defaultSymbolStyle;

    /**
     * Function to push a single activation data point into the plot at a certain time (xTimestamp).
     *
     * \param timestamp Time the data point was generated, represented as seconds since an epoch.
     * The epoch used will depend on the implementation; the default implementation (wxChartDir) uses January 1st, year 1.
     * However, since charts display only hours, minutes, and seconds, for short time spans (less than a day), the epoch could be user-defined (for example, the beginning of the experiment which is producing data).
     * Data points must be inserted with the timestamps in ascending order (the same order that they were created).
     * \param isActive If true, a point will be displayed at the given timestamp. Otherwise no point will be displayed.
     */
    virtual void pushData(double xTimestamp, bool isActive = true) = 0;
};
