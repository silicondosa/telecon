#pragma once

#include <string>

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
     * Getter function for the color of the plot.
     * 
     * \return color value as an int (enum)
     */
    virtual int getColor() const = 0;

    /**
     * Getter function for the title of the plot.
     * 
     * \return title as a string
     */
    virtual const string getPlotTitle() const = 0;

    /** 
     * Function to see if the plot symbol is filled or not
     * 
     * \return True if the symbol is filled, or False if the center of th symbol will be transparent.
     */
    virtual bool isSymbolFilled() const = 0;

    /**
     * Getter function to return the type of symbol used (e.g., square, circle, triangle).
     *
     * \return Symbol as int, in the format described in TeleconRealtimeChart::addLinePlot.
     */
    virtual int getSymbol() const = 0;

    /**
     * Getter function of the symbol size in pixels
     * 
     * \return symbol size as int.
     */
    virtual int getSymbolSize() const = 0;
};