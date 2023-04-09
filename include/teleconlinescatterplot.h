#pragma once

#include "teleconplot.h"

class TeleconLineScatterPlot : virtual public TeleconPlot {
public:

	/**
	 * Virtual function to push data (yData) into the plot at a certain time (xTimestamp).
	 * 
	 * \param xTimestamp as double
	 * \param yData as double
	 */
	virtual void pushData(double xTimestamp, double yData) = 0;

	/**
	 * Virtual getter function to return if symbol is filled.
	 * 
	 * \return symbol filled as bool 
	 */
	virtual bool isSymbolFilled() const = 0;

	/**
	 * Virtual getter function to return symbol.
	 * 
	 * \return symbol as int
	 */
	virtual int getSymbol() const = 0;

	/**
	 * Virtual getter function to return symbol size.
	 * 
	 * \return symbol size as int
	 */
	virtual int getSymbolSize() const = 0;
};