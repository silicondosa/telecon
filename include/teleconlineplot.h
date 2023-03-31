#pragma once

#include "teleconlinescatterplot.h"

enum LineType {
	LT_SOLID,
	LT_DASHED
};

class TeleconLinePlot : virtual public TeleconLineScatterPlot {
public:
	virtual int getLineWidth() const = 0;
	virtual LineType getLineType() const = 0;
	virtual bool hasSymbol() const = 0;
};