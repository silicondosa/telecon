#include "teleconplot.h"

TeleconPlot::TeleconPlot(int depth, int color, string plotTitle)
	: m_dataToAdd(new list<pair<double, double>>()), m_depth(depth), m_xTimestamps(depth), m_yData(depth), m_color(color), m_plotTitle(plotTitle) {}

void TeleconPlot::pushData(double xTimestamp, double yData)
{
    const lock_guard<mutex> lock(m_dataToAddLock);

    m_dataToAdd->push_back(make_pair(xTimestamp, yData));

    if (m_dataToAdd->size() > m_depth) {
        m_dataToAdd->pop_front();
    }

    // lock_guard automatically releases m_dataToAddLock when it goes out of scope
}

double TeleconPlot::getEarliestTimestamp() const
{
    return m_xTimestamps[0];
}

double TeleconPlot::getLatestTimestamp() const
{
    return m_xTimestamps[m_xTimestamps.size() - 1];
}

double TeleconPlot::getLastestValue() const
{
    return m_yData.latest();
}

int TeleconPlot::size() const {
	return m_xTimestamps.size();
}

int TeleconPlot::depth() const {
	return m_depth;
}

int TeleconPlot::getColor() const {
	return m_color;
}

const string& TeleconPlot::getPlotTitle() const {
	return m_plotTitle;
}
