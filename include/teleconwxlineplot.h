#pragma once

#include "teleconwxplotxy.h"

class TeleconWxLinePlot : public TeleconWxPlotXY {
public:
	TeleconWxLinePlot(int depth, int color, string plotTitle, int lineWidth, LineType lineType, bool hasSymbol, int symbol, bool fillSymbol, int symbolSize);
};
