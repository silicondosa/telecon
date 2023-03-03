#pragma once

#include "teleconplot.h"


enum LineType {
	LT_SOLID,
	LT_DASHED,
	LT_NONE
};

class TeleconLinePlot : public TeleconPlot {
protected:
	int m_lineWidth;
	LineType m_lineType;
public:
	TeleconLinePlot(DoubleFuncPtr dataFuncPtr, int depth, int color, string plotTitle, int lineWidth, LineType lineType);
	int getLineWidth() const;
	LineType getLineType() const;
	double fetchData(); // Fetches one datum from the controller
	void addToChart(XYChart* chart, DoubleArray xData);
};
