#include "teleconplot.h"

TeleconPlot::TeleconPlot(DoubleFuncPtr dataFuncPtr, int depth, int color, string plotTitle)
	: m_dataFuncPtr(dataFuncPtr), m_yData(depth), m_color(color), m_plotTitle(plotTitle) {}

const double& TeleconPlot::operator[](int index) const {
	return m_yData[index];
}

int TeleconPlot::size() const {
	return m_yData.size();
}

int TeleconPlot::depth() const {
	return m_yData.depth();
}

int TeleconPlot::getColor() const {
	return m_color;
}

const string& TeleconPlot::getPlotTitle() const {
	return m_plotTitle;
}
