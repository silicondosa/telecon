#pragma once

#include <string>
#include <memory>

#include "symbolstyle.h"

using namespace std;

/**
 * Implementation of a singular plot.
 */
class TeleconPlot {
public:
    /**
     * Getter function for current size of the data buffer(s)
     * 
     * \return size as type size_t.
     */
    virtual size_t size() const = 0;

    /**
     * Getter function for depth, the capacity(maximum size) of the data buffer(s)
     * 
     * \return depth as type size_t.
     */
    virtual size_t depth() const = 0;

    /**
     * Getter function for the title of the plot.
     * 
     * \return title as a string
     */
    virtual const string getPlotTitle() const = 0;

    virtual shared_ptr<const SymbolStyle> getSymbolStyle() const = 0;
};