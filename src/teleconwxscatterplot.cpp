#include "teleconwxscatterplot.h"

TeleconWxScatterPlot::TeleconWxScatterPlot(string plotTitle, int color, int symbol, bool fillSymbol, int symbolSize, int depth)
    : TeleconWxPlotXY(plotTitle, color, 0, LT_SOLID, true, symbol, fillSymbol, symbolSize, depth) {}
