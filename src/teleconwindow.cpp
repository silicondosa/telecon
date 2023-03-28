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

TeleconChart* TeleconWindow::addChart(std::string title, std::string xLabel, std::string yLabel, ColorSequenceMode colorSequenceMode, double defaultTimespan)
{
	TeleconChart* chart = new TeleconChart(title, xLabel, yLabel, colorSequenceMode, defaultTimespan);
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
