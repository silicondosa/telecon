#include "teleconlineplot.h"

TeleconLinePlot::TeleconLinePlot(int depth, int color, string plotTitle, int lineWidth, LineType lineType, bool hasSymbol, int symbol, bool fillSymbol, int symbolSize)
    : TeleconWxPlotXY(depth, color, plotTitle, lineWidth, lineType, hasSymbol, symbol, fillSymbol, symbolSize) {}