#pragma once

#include "teleconwxplotxy.h"

class TeleconScatterPlot : public TeleconWxPlotXY {
public:
	TeleconScatterPlot(int depth, int color, string plotTitle, int symbol, bool fillSymbol, int symbolSize);
};