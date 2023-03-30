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
    bool m_fillSymbol;
    int m_symbol;
    int m_symbolSize;
    list<pair<double, double>>* swapAndGetDataToAdd();
public:
	TeleconLinePlot(int depth, int color, string plotTitle, int lineWidth, LineType lineType, bool hasSymbol, int symbol, bool fillSymbol, int symbolSize);
    void prepDataForDraw() override;
	void addToChart(XYChart* chart) override;
	int getLineWidth() const;
	LineType getLineType() const;
	double getLeftmostX() override;
	double getRightmostX() override;
};
