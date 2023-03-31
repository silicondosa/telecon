#include "teleconchart.h"

TeleconChart::TeleconChart(string title, string xLabel, string yLabel, ColorSequenceMode colorSequenceMode, double defaultXAxisSpan)
	: m_title(title), m_xLabel(xLabel), m_yLabel(yLabel), m_colorSequenceMode(colorSequenceMode), m_defaultXAxisSpan(defaultXAxisSpan) {}

string TeleconChart::getTitle()
{
	return m_title;
}

string TeleconChart::getXLabel()
{
	return m_xLabel;
}

string TeleconChart::getYLabel()
{
	return m_yLabel;
}

ColorSequenceMode TeleconChart::getColorSequenceMode()
{
	return m_colorSequenceMode;
}

double TeleconChart::getDefaultXAxisSpan()
{
	return m_defaultXAxisSpan;
}

long TeleconChart::getNextDefaultColor() {
	switch (m_colorSequenceMode) {
	case CSM_BLACK:
		return COLOR_BLACK;
		break;
	case CSM_DIVERGING:
		// Cycle through the colors in CSM_COLORS_DIVERGING
		return CSM_COLORS_DIVERGING[m_plots.size() % CSM_COLORS_DIVERGING.size()];
		break;
	}
	// Should be impossible, cases are exhaustive
	return COLOR_BLACK;
}

TeleconPlot* TeleconChart::getPlot(int index)
{
	return m_plots[index];
}

size_t TeleconChart::getNumPlots()
{
	return m_plots.size();
}

TeleconPlot* TeleconChart::getPlotByName(string name)
{
	for (auto i = m_plots.begin(); i != m_plots.end(); ++i) {
		if (name.compare((*i)->getPlotTitle()) == 0) {
			return *i;
		}
	}
	return nullptr;
}
