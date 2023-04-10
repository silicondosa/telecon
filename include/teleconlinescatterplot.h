#pragma once

#include "teleconplot.h"

class TeleconLineScatterPlot : virtual public TeleconPlot {
public:

	/**
	 * Function to push a single data point (yData) into the plot at a certain time (xTimestamp).
	 * 
	 * \param xTimestamp Time the data point was generated, in seconds. The exact interpretation of the time will depend on the implementation; the default implementation (wxChartDir) interprets it as seconds since January 1st, year 1.
	 * \param yData The value that will be displayed.
	 */
	virtual void pushData(double xTimestamp, double yData) = 0;

	/**
	 * Getter function to return if symbol is filled or only an outline.
	 * 
	 * \return True if the symbol is filled, or false otherwise.
	 */
	virtual bool isSymbolFilled() const = 0;

	/**
	 * Getter function to return the type of symbol used (e.g., square, circle, tirangle).
	 * 
	 * \return Symbol, in the format described in TeleconRealtimeChart::addLinePlot.
	 */
	virtual int getSymbol() const = 0;

	/**
	 * Getter function to return symbol size.
	 * 
	 * \return Symbol size in pixels.
	 */
	virtual int getSymbolSize() const = 0;
};