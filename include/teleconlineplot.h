#pragma once

#include "teleconwxplotxy.h"

class TeleconLinePlot : public TeleconWxPlotXY {
public:
	TeleconLinePlot(int depth, int color, string plotTitle, int lineWidth, LineType lineType, bool hasSymbol, int symbol, bool fillSymbol, int symbolSize);
};
