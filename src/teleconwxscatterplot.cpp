#include "teleconwxscatterplot.h"

TeleconWxScatterPlot::TeleconWxScatterPlot(string plotTitle, size_t depth, const SymbolStyle& symbolStyle)
    : TeleconWxPlot(plotTitle, depth, symbolStyle), m_dataToAdd(depth), m_xTimestamps(depth), m_yData(depth)
{
    if (m_symbolStyle->getSymbolColor() == COLOR_DEFAULT) {
        m_symbolStyle->setSymbolColor(COLOR_BLACK);
    }
}

void TeleconWxScatterPlot::prepDataForDraw()
{
    shared_ptr<list<ScatterPlotDataPoint>> dataToAdd = m_dataToAdd.getDataAndClearList();

    for (const auto& xyPair : *dataToAdd) {
        m_xTimestamps.insertNewValue(xyPair.xTimestamp);
        m_yData.insertNewValue(xyPair.yData);
    }
}

double TeleconWxScatterPlot::getLeftmostX() const
{
    return m_xTimestamps[0];
}

double TeleconWxScatterPlot::getRightmostX() const
{
    return m_xTimestamps[m_xTimestamps.size() - 1];
}

string TeleconWxScatterPlot::getLatestValueString() const
{
    // Can't believe this is still the only way to do this in C++17 (formatting directly into c++ string isn't added until C++20)
    int size_s = std::snprintf(nullptr, 0, "%.2f", m_yData[m_yData.size() - 1]) + 1; // Extra space for '\0'
    std::unique_ptr<char[]> buf(new char[size_s]);
    std::snprintf(buf.get(), size_s, "%.2f", m_yData[m_yData.size() - 1]);
    return string(buf.get());
}

bool TeleconWxScatterPlot::isIncludedInLegend() const
{
    return true;
}

void TeleconWxScatterPlot::addToChart(XYChart* chart)
{
    if (m_yData.size() <= 0) {
        return;
    }
    TeleconWxPlot::addScatterPlotToChart(
        chart,
        m_plotTitle,
        true,
        DoubleArray(&m_xTimestamps[0], (int)m_xTimestamps.size()),
        DoubleArray(&m_yData[0], (int)m_yData.size()),
        m_symbolStyle
    );
}

size_t TeleconWxScatterPlot::size() const
{
    return m_xTimestamps.size();
}

void TeleconWxScatterPlot::pushData(double xTimestamp, double yData)
{
    m_dataToAdd.addDataPoint({ xTimestamp, yData });
}