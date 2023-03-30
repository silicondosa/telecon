#pragma once

#include "teleconplot.h"

class TeleconScatterPlot : public TeleconPlot {
protected:
	int m_symbol;
    bool m_fillSymbol;
    int m_symbolSize;

    list<pair<double, double>>* swapAndGetDataToAdd();
public:
	TeleconScatterPlot(int depth, int color, string plotTitle, int symbol, bool fillSymbol, int symbolSize);
    void prepDataForDraw() override;
    void addToChart(XYChart* chart) override;
	int getSymbol() const;
	int getSymbolSize() const;
	double getLeftmostX() override;
	double getRightmostX() override;
};