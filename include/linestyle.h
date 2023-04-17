#pragma once

#include "enums.h"

class LineStyle
{
private:
    int m_lineColor;
    int m_lineWidth;
    PlotLineType m_lineType;
public:
    LineStyle(int lineColor = COLOR_DEFAULT, int lineWidth = 1, PlotLineType lineType = LT_SOLID);
    void setLineColor(int lineColor);
    int getLineColor() const;
    void setLineWidth(int lineWidth);
    int getLineWidth() const;
    void setLineType(PlotLineType lineType);
    PlotLineType getLineType() const;
};
