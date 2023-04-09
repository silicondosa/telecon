#pragma once

#include "teleconlinescatterplot.h"

enum LineType {
	LT_SOLID,
	LT_DASHED
};

class TeleconLinePlot : virtual public TeleconLineScatterPlot {
public:

	/**
	 * Virtual getter function for plot line width.
	 * 
	 * \return line width as int
	 */
	virtual int getLineWidth() const = 0;

	/**
	 * Virtual getter function for plot line type.
	 *
	 * \return line type as LineType object
	 */
	virtual LineType getLineType() const = 0;

	/**
	 * Virtual getter function to see if plot has a symbol.
	 *
	 * \return symbol status as bool
	 */
	virtual bool hasSymbol() const = 0;

};