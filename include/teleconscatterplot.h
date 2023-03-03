#pragma once

#include "teleconplot.h"

class TeleconScatterPlot : public TeleconPlot {
protected:
	int m_symbol;
    int m_symbolSize;
public:
	TeleconScatterPlot(DoubleFuncPtr dataFuncPtr, int depth, int color, string plotTitle, int symbol, int symbolSize);
	int getSymbol() const;
	int getSymbolSize() const;
	double fetchData();
    void addToChart(XYChart* chart, DoubleArray xData);
};