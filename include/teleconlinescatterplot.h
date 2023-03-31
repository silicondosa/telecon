#pragma once

#include "teleconplot.h"

class TeleconLineScatterPlot : virtual public TeleconPlot {
public:
	virtual void pushData(double xTimestamp, double yData) = 0;
	virtual bool isSymbolFilled() const = 0;
	virtual int getSymbol() const = 0;
	virtual int getSymbolSize() const = 0;
};