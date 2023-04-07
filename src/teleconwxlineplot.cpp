#include "teleconwxlineplot.h"

TeleconWxLinePlot::TeleconWxLinePlot(string plotTitle, int color, int lineWidth, LineType lineType, bool hasSymbol, int symbol, bool fillSymbol, int symbolSize, int depth)
    : TeleconWxPlotXY(plotTitle, color, lineWidth, lineType, hasSymbol, symbol, fillSymbol, symbolSize, depth) {}

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