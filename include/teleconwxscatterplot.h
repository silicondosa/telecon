#pragma once

#include "teleconwxplotxy.h"
#include "teleconscatterplot.h"

// Prevents compiler warnings about inheritance from multiple overlapping classes
// We perform diamond inheritance, which can cause issues, but the way we do it is safe (only one definition for each function)
# pragma warning( disable : 4250)

/**
 * Scatter plot and GUI implementation, inherits from TeleconWxPlotXY and TeleconScatterPlot.
 */
class TeleconWxScatterPlot : public TeleconWxPlotXY, virtual public TeleconScatterPlot {
public:

	/**
	 * Constructor that creates a scatter plot object.
	 * 
	 * \param plotTitle title of the plot as string
	 * \param color color of the plot line as int (enum)
	 * \param symbol symbol type of the plot as int (enum)
	 * \param fillSymbol whether or not the plot line is filled or dotted as bool
	 * \param symbolSize symbol size as an int
	 * \param depth depth of the internal buffer as int
	 */
	TeleconWxScatterPlot(string plotTitle, int color, int symbol, bool fillSymbol, int symbolSize, int depth);
};