#include "teleconwxplot.h"

TeleconWxPlot::TeleconWxPlot(size_t depth, int color, string plotTitle)
	: m_dataToAdd(new list<pair<double, double>>()), m_depth(depth), m_xTimestamps(depth), m_yData(depth), m_color(color), m_plotTitle(plotTitle) {}

void TeleconWxPlot::pushData(double xTimestamp, double yData)
{
    const lock_guard<mutex> lock(m_dataToAddLock);

    m_dataToAdd->push_back(make_pair(xTimestamp, yData));

    if ((int)m_dataToAdd->size() > m_depth) {
        m_dataToAdd->pop_front();
    }

    // lock_guard automatically releases m_dataToAddLock when it goes out of scope
}

size_t TeleconWxPlot::size() const {
	return m_xTimestamps.size();
}

size_t TeleconWxPlot::depth() const {
	return m_depth;
}

int TeleconWxPlot::getColor() const {
	return m_color;
}

const string& TeleconWxPlot::getPlotTitle() const {
	return m_plotTitle;
}
