#include "teleconwindow.h"

#include <iostream>

TeleconWindow::TeleconWindow(std::string title)
	: m_title(title), m_hasRequestedQuit(false), m_hasQuit(false), m_hasStartedInitialization(false) {}

TeleconWindow::TeleconWindow()
	: TeleconWindow("") {}

void TeleconWindow::requestQuit()
{
	m_hasRequestedQuit = true;
}

bool TeleconWindow::hasRequestedQuit()
{
	return m_hasRequestedQuit;
}

void TeleconWindow::setHasQuit()
{
	std::unique_lock lock(m_hasQuitLock);
	m_hasQuit = true;
	lock.unlock();
	m_hasQuitCV.notify_all();
}

bool TeleconWindow::hasQuit()
{
	std::lock_guard lock(m_hasQuitLock);
	return m_hasQuit;
}

void TeleconWindow::waitUntilQuit()
{
	std::unique_lock lock(m_hasQuitLock);
	while (!m_hasQuit) {
		m_hasQuitCV.wait(lock);
	}
}

std::string TeleconWindow::getTitle()
{
	return m_title;
}

void TeleconWindow::initialize()
{
    m_hasStartedInitialization = true;
    for (auto& chart : m_charts) {
        chart->initialize();
    }
}

shared_ptr<TeleconRealtimeChart> TeleconWindow::addRealtimeChart(std::string title, double memoryDepthSeconds, int dataRateMillis, std::string xLabel, std::string yLabel, ColorSequenceMode colorSequenceMode)
{
    if (m_hasStartedInitialization) {
        cout << "telecon: Telecon has already started, charts may not be added." << endl;
        return shared_ptr<TeleconRealtimeChart>();
    }
	shared_ptr<TeleconRealtimeChart> chart = make_shared<TeleconRealtimeChart>(title, memoryDepthSeconds, dataRateMillis, xLabel, yLabel, colorSequenceMode);
	m_charts.push_back(chart);
	return chart;
}

shared_ptr<TeleconChart> TeleconWindow::getChart(size_t index)
{
	return m_charts[index];
}

size_t TeleconWindow::getNumCharts() const
{
	return m_charts.size();
}

shared_ptr<TeleconChart> TeleconWindow::getChartByName(string name)
{
	for (auto chart : m_charts) {
		if (name.compare(chart->getTitle()) == 0) {
			return chart;
		}
	}
	return nullptr;
}

shared_ptr<TeleconPlot> TeleconWindow::getPlotByName(string chartName, string plotName)
{
	shared_ptr<TeleconChart> chart = getChartByName(chartName);
	return chart == nullptr ? nullptr : chart->getPlotByName(plotName);
}
