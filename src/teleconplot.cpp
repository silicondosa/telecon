#include "teleconplot.h"

TeleconPlot::TeleconPlot(DoubleFuncPtr dataFuncPtr, size_t memoryDepth, int color, int lineWidth, LineType lineType, string plotTitle)
	: m_dataFuncPtr(dataFuncPtr), m_data(memoryDepth), m_color(color), m_lineWidth(lineWidth), m_lineType(lineType), m_plotTitle(plotTitle) {}

double TeleconPlot::fetchData() {
	double newValue = m_dataFuncPtr();
	m_data.insertNewValue(newValue);
	return newValue;
}

const double& TeleconPlot::getOldest() const {
	return m_data[0];
}

int TeleconPlot::size() const {
	return m_data.size();
}

int TeleconPlot::getColor() const {
	return m_color;
}

int TeleconPlot::getLineWidth() const {
	return m_lineWidth;
}

LineType TeleconPlot::getLineType() const {
	return m_lineType;
}

const string& TeleconPlot::getPlotTitle() const {
	return m_plotTitle;
}
