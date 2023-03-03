#pragma once

#include "teleconplot.h"

enum LineType {
	LT_SOLID,
	LT_DASHED
};

class TeleconLinePlot : public TeleconPlot {
protected:
	int m_lineWidth;
	LineType m_lineType;
    bool m_hasSymbol;
    int m_symbol;
    int m_symbolSize;
public:
	TeleconLinePlot(DoubleFuncPtr dataFuncPtr, int depth, int color, string plotTitle, int lineWidth, LineType lineType, bool hasSymbol, int symbol, int symbolSize);
	int getLineWidth() const;
	LineType getLineType() const;
	double fetchData(); // Fetches one datum from the controller
	void addToChart(XYChart* chart, DoubleArray xData);
};
