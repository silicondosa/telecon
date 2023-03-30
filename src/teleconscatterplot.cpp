#include "teleconscatterplot.h"

TeleconScatterPlot::TeleconScatterPlot(int depth, int color, string plotTitle, int symbol, bool fillSymbol, int symbolSize)
    : TeleconWxPlotXY(depth, color, plotTitle, 0, LT_SOLID, true, symbol, fillSymbol, symbolSize) {}