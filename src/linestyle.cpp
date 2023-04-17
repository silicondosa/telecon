#include "linestyle.h"

LineStyle::LineStyle(int lineColor, int lineWidth, PlotLineType lineType)
    : m_lineColor(lineColor), m_lineWidth(lineWidth), m_lineType(lineType) {}

void LineStyle::setLineColor(int lineColor)
{
    m_lineColor = lineColor;
}

int LineStyle::getLineColor() const
{
    return m_lineColor;
}

void LineStyle::setLineWidth(int lineWidth)
{
    m_lineWidth = lineWidth;
}

int LineStyle::getLineWidth() const
{
    return m_lineWidth;
}

void LineStyle::setLineType(PlotLineType lineType)
{
    m_lineType = lineType;
}

PlotLineType LineStyle::getLineType() const
{
    return m_lineType;
}
