#pragma once

#include <string>
#include "databuffer.h"

using namespace std;

enum LineType {
	LT_SOLID,
	LT_DASHED,
	LT_NONE
};

typedef double (*DoubleFuncPtr)();
class TeleconPlot {
private:
	DoubleFuncPtr m_dataFuncPtr; // Function pointer to fetch one datum from the controller
	DataBuffer<double> m_data;
	int m_color; // Represented as an RGB hexadecimal code (one byte per channel)
	int m_lineWidth;
	LineType m_lineType;
	string m_plotTitle;
public:
	TeleconPlot(DoubleFuncPtr dataFuncPtr, size_t memoryDepth, int color, int lineWidth, LineType lineType, string plotTitle);
	double fetchData(); // Fetches one datum from the controller
	// Returns a reference to the oldest datum in the series, if one exists. Other elements are guaranteed to be stored
	// contiguously in order after the oldest element.
	const double& getOldest() const;
	int size() const;
	int getColor() const;
	int getLineWidth() const;
	LineType getLineType() const;
	const string& getPlotTitle() const;
};