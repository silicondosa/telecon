#include "teleconwxlineplot.h"

TeleconWxLinePlot::TeleconWxLinePlot(string plotTitle, size_t depth, const LineStyle& lineStyle, const SymbolStyle& symbolStyle)
    : TeleconWxPlot(plotTitle, depth, symbolStyle), m_dataToAdd(depth), m_xTimestamps(depth), m_yData(depth), m_lineStyle(make_shared<LineStyle>(lineStyle))
{
    if (m_lineStyle->getLineColor() == COLOR_DEFAULT) {
        m_lineStyle->setLineColor(COLOR_BLACK);
    }
    if (m_symbolStyle->getSymbolColor() == COLOR_DEFAULT) {
        m_symbolStyle->setSymbolColor(m_lineStyle->getLineColor());
    }
}

void TeleconWxLinePlot::prepDataForDraw()
{
    shared_ptr<list<LinePlotDataPoint>> dataToAdd = m_dataToAdd.getDataAndClearList();

    for (const auto& xyPair : *dataToAdd) {
        m_xTimestamps.insertNewValue(xyPair.xTimestamp);
        m_yData.insertNewValue(xyPair.yData);
    }
}

double TeleconWxLinePlot::getLeftmostX() const
{
    return m_xTimestamps[0];
}

double TeleconWxLinePlot::getRightmostX() const
{
    return m_xTimestamps[m_xTimestamps.size() - 1];
}

string TeleconWxLinePlot::getLatestValueString() const
{
    // Can't believe this is still the only way to do this in C++17 (formatting directly into c++ string isn't added until C++20)
    int size_s = std::snprintf(nullptr, 0, "%.2f", m_yData[m_yData.size() - 1]) + 1; // Extra space for '\0'
    std::unique_ptr<char[]> buf(new char[size_s]);
    std::snprintf(buf.get(), size_s, "%.2f", m_yData[m_yData.size() - 1]);
    return string(buf.get());
}

bool TeleconWxLinePlot::isIncludedInLegend() const
{
    return true;
}

void TeleconWxLinePlot::addToChart(XYChart* chart)
{
    if (m_yData.size() <= 0) {
        return;
    }
    TeleconWxPlot::addLinePlotToChart(
        chart,
        m_plotTitle,
        true,
        DoubleArray(&m_xTimestamps[0], (int)m_xTimestamps.size()),
        DoubleArray(&m_yData[0], (int)m_yData.size()),
        m_lineStyle,
        m_symbolStyle
    );
}

size_t TeleconWxLinePlot::size() const
{
    return m_xTimestamps.size();
}

void TeleconWxLinePlot::pushData(double xTimestamp, double yData)
{
    m_dataToAdd.addDataPoint({ xTimestamp, yData });
}

shared_ptr<const LineStyle> TeleconWxLinePlot::getLineStyle() const
{
    return m_lineStyle;
}
