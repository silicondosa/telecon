#pragma once

#include <string>

#include "chartdir.h"
#include "databuffer.h"

using namespace std;

typedef double (*DoubleFuncPtr)();
class TeleconPlot {
protected:
	DoubleFuncPtr m_dataFuncPtr; // Function pointer to fetch one datum from the controller
	DataBuffer<double> m_yData;
	int m_color; // Represented as an RGB hexadecimal code (one byte per channel)
	string m_plotTitle;
public:
	TeleconPlot(DoubleFuncPtr dataFuncPtr, int depth, int color, string plotTitle);
	virtual double fetchData() = 0; // Fetches one datum from the controller
	virtual void addToChart(XYChart* chart, DoubleArray xData) = 0;
	// Returns a reference to the oldest datum in the series, if one exists. Other elements are guaranteed to be stored
	// contiguously in order after the oldest element.
	const double& operator[](int index) const; // Pass by reference doesn't matter here, just doing it for consistency with DataBuffer
	// Returns the current size of the data buffer
	int size() const;
	// Returns the capacity (maximum size) of the data buffer
	int depth() const;
	int getColor() const;
	
	const string& getPlotTitle() const;
};