#include "teleconwindow.h"

TeleconWindow::TeleconWindow(std::string title)
	: m_title(title), m_hasQuit(false) {}

TeleconWindow::TeleconWindow()
	: TeleconWindow("") {}

void TeleconWindow::quit()
{
	m_hasQuit.store(true);
}

bool TeleconWindow::hasQuit()
{
	return m_hasQuit.load();
}

std::string TeleconWindow::getTitle()
{
	return m_title;
}

TeleconRealtimeChart* TeleconWindow::addRealtimeChart(std::string title, std::string xLabel, std::string yLabel, ColorSequenceMode colorSequenceMode, double defaultTimespan)
{
	TeleconRealtimeChart* chart = new TeleconRealtimeChart(title, xLabel, yLabel, colorSequenceMode, defaultTimespan);
	m_charts.push_back(chart);
	return chart;
}

TeleconChart* TeleconWindow::getChart(size_t index)
{
	return m_charts[index];
}

size_t TeleconWindow::getNumCharts() const
{
	return m_charts.size();
}

TeleconChart* TeleconWindow::getChartByName(string name)
{
	for (vector<TeleconChart*>::iterator i = m_charts.begin(); i != m_charts.end(); ++i) {
		if (name.compare((*i)->getTitle()) == 0) {
			return *i;
		}
	}
	return nullptr;
}

TeleconPlot* TeleconWindow::getPlotByName(string chartName, string plotName)
{
	TeleconChart* chart = getChartByName(chartName);
	return chart == nullptr ? nullptr : chart->getPlotByName(plotName);
}
