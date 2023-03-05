#pragma once

#include "teleconplot.h"

class TeleconScatterPlot : public TeleconPlot {
protected:
	int m_symbol;
    int m_symbolSize;

    list<pair<double, double>>* swapAndGetDataToAdd();
public:
	TeleconScatterPlot(DoubleFuncPtr dataFuncPtr, int depth, int color, string plotTitle, int symbol, int symbolSize);
    void prepDataForDraw() override;
    void addToChart(XYChart* chart) override;
	int getSymbol() const;
	int getSymbolSize() const;
};