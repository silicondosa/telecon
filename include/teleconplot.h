#pragma once

#include <string>

using namespace std;

class TeleconPlot {
public:
    // Returns the current size of the data buffer(s)
    virtual size_t size() const = 0;
    // Returns the capacity (maximum size) of the data buffer(s)
    virtual size_t depth() const = 0;
    virtual int getColor() const = 0;
    virtual const string getPlotTitle() const = 0;

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