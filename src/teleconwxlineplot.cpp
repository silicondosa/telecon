#include "teleconwxlineplot.h"

TeleconWxLinePlot::TeleconWxLinePlot(int depth, int color, string plotTitle, int lineWidth, LineType lineType, bool hasSymbol, int symbol, bool fillSymbol, int symbolSize)
    : TeleconWxPlotXY(depth, color, plotTitle, lineWidth, lineType, hasSymbol, symbol, fillSymbol, symbolSize) {}

int TeleconWxLinePlot::getLineWidth() const
{
    return m_lineWidth;
}

LineType TeleconWxLinePlot::getLineType() const
{
    return m_lineType;
}

bool TeleconWxLinePlot::hasSymbol() const
{
    return m_hasSymbol;
}