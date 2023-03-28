#include "teleconchart.h"

TeleconChart::TeleconChart(std::string title, std::string xLabel, std::string yLabel, ColorSequenceMode colorSequenceMode, double defaultTimespan)
	: m_title(title), m_xLabel(xLabel), m_yLabel(yLabel), m_colorSequenceMode(colorSequenceMode), m_defaultTimespan(defaultTimespan) {}

std::string TeleconChart::getTitle()
{
	return m_title;
}

std::string TeleconChart::getXLabel()
{
	return m_xLabel;
}

std::string TeleconChart::getYLabel()
{
	return m_yLabel;
}

ColorSequenceMode TeleconChart::getColorSequenceMode()
{
	return m_colorSequenceMode;
}

double TeleconChart::getDefaultTimespan()
{
	return m_defaultTimespan;
}

static long getNextDefaultColor(ColorSequenceMode csm, int index) {
	switch (csm) {
	case CSM_BLACK:
		return COLOR_BLACK;
		break;
	case CSM_DIVERGING:
		// Cycle through the colors in CSM_COLORS_DIVERGING
		return CSM_COLORS_DIVERGING[index % CSM_COLORS_DIVERGING.size()];
		break;
	}
	// Should be impossible, cases are exhaustive
	return COLOR_BLACK;
}

TeleconLinePlot* TeleconChart::addLinePlot(std::string plottitle, int memoryDepth, long plotcolor, LineType lineType, int lineWidth, int symbol, bool fillSymbol, int symbolSize)
{
	long color = plotcolor == COLOR_DEFAULT ? getNextDefaultColor(m_colorSequenceMode, m_plots.size()) : plotcolor;
	TeleconLinePlot* linePlot = new TeleconLinePlot(memoryDepth, color, plottitle, lineWidth, lineType, symbol != Chart::NoSymbol, symbol, fillSymbol, symbolSize);
	m_plots.push_back(linePlot);
	return linePlot;
}

TeleconScatterPlot* TeleconChart::addScatterPlot(std::string plottitle, int memoryDepth, long plotcolor, int symbol, bool fillSymbol, int symbolSize)
{
	long color = plotcolor == COLOR_DEFAULT ? getNextDefaultColor(m_colorSequenceMode, m_plots.size()) : plotcolor;
	TeleconScatterPlot* scatterPlot = new TeleconScatterPlot(memoryDepth, color, plottitle, symbol, fillSymbol, symbolSize);
	m_plots.push_back(scatterPlot);
	return scatterPlot;
}

TeleconPlot* TeleconChart::getPlot(int index)
{
	return m_plots[index];
}

int TeleconChart::getNumPlots()
{
	return m_plots.size();
}
