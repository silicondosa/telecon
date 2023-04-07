#include "teleconwxplot.h"

TeleconWxPlot::TeleconWxPlot(string plotTitle, int color, size_t depth)
	: m_plotTitle(plotTitle), m_color(color), m_depth(depth) {}

size_t TeleconWxPlot::depth() const {
	return m_depth;
}

int TeleconWxPlot::getColor() const {
	return m_color;
}

const string TeleconWxPlot::getPlotTitle() const {
	return m_plotTitle;
}
