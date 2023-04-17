#pragma once

#include <string>
#include <memory>

#include "symbolstyle.h"

using namespace std;

/**
 * Abstract class of the user-level interface for interacting with plots.
 * All types of plots inherit from this class.
 */
class TeleconPlot {
public:
    /**
     * \return Current size of the plot (number of data points). Always <= depth.
     */
    virtual size_t size() const = 0;

    /**
     * \return Depth (maximum size) of the plot. Always >= size.
     */
    virtual size_t depth() const = 0;

    /**
     * \return The title of the plot, as displayed in the legend.
     */
    virtual const string getPlotTitle() const = 0;

    /**
     * \return The ::SymbolStyle representing how the symbol representing points (if any) should be displayed.
     */
    virtual shared_ptr<const SymbolStyle> getSymbolStyle() const = 0;
};