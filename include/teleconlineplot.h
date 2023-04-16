#pragma once

#include "teleconlinescatterplot.h"

/**
 * Describes whether the given line plot uses a solid line or a dashed line to connect points.
 */
enum LineType {
	LT_SOLID,
	LT_DASHED
};

/**
 * Line plot implementation that inherits from TeleconLineScatterPlot.
 */
class TeleconLinePlot : virtual public TeleconLineScatterPlot {
public:

	/**
	 * Getter function for plot line width.
	 * 
	 * \return Line width in pixels as int.
	 */
	virtual int getLineWidth() const = 0;

	/**
	 * Getter function for plot line type (solid or dashed).
	 *
	 * \return Line type as type LineType.
	 */
	virtual LineType getLineType() const = 0;

	/**
	 * Getter function to see if plot has a symbol. If not, only the line will be displayed.
	 *
	 * \return True if a symbol will be drawn, or false otherwise as bool.
	 */
	virtual bool hasSymbol() const = 0;

};