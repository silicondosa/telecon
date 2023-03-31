#include "teleconwxplot.h"

TeleconWxPlot::TeleconWxPlot(size_t depth, int color, string plotTitle)
	: m_depth(depth), m_color(color), m_plotTitle(plotTitle) {}

size_t TeleconWxPlot::depth() const {
	return m_depth;
}

int TeleconWxPlot::getColor() const {
	return m_color;
}

const string TeleconWxPlot::getPlotTitle() const {
	return m_plotTitle;
}
