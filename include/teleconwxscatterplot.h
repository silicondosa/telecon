#pragma once

#include "teleconwxplotxy.h"
#include "teleconscatterplot.h"

// Prevents compiler warnings about inheritance from multiple overlapping classes
// We perform diamond inheritance, which can cause issues, but the way we do it is safe (only one definition for each function)
# pragma warning( disable : 4250)

/**
 * .
 */
class TeleconWxScatterPlot : public TeleconWxPlotXY, virtual public TeleconScatterPlot {
public:
	TeleconWxScatterPlot(string plotTitle, int color, int symbol, bool fillSymbol, int symbolSize, int depth);
};