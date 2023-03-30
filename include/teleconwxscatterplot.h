#pragma once

#include "teleconwxplotxy.h"

class TeleconWxScatterPlot : public TeleconWxPlotXY {
public:
	TeleconWxScatterPlot(int depth, int color, string plotTitle, int symbol, bool fillSymbol, int symbolSize);
};