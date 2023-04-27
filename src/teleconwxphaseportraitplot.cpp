#include "teleconwxphaseportraitplot.h"
#include <cfloat>
#include <cmath>

TeleconWxPhasePortraitPlot::TeleconWxPhasePortraitPlot(string plotTitle, size_t depth, const LineStyle& lineStyle, const SymbolStyle& symbolStyle)
    : TeleconWxPlot(plotTitle, depth, symbolStyle), m_dataToAdd(depth), m_timestamps(depth), m_xData(depth), m_yData(depth), m_lineStyle(make_shared<LineStyle>(lineStyle))
{
    if (m_lineStyle->getLineColor() == COLOR_DEFAULT) {
        m_lineStyle->setLineColor(COLOR_BLACK);
    }
    if (m_symbolStyle->getSymbolColor() == COLOR_DEFAULT) {
        m_symbolStyle->setSymbolColor(m_lineStyle->getLineColor());
    }
}

size_t TeleconWxPhasePortraitPlot::size() const
{
    return m_timestamps.size();
}

void TeleconWxPhasePortraitPlot::prepDataForDraw()
{
    shared_ptr<list<PhasePortraitDataPoint>> dataToAdd = m_dataToAdd.getDataAndClearList();

    for (const auto& dataPoint : *dataToAdd) {
        m_timestamps.insertNewValue(dataPoint.timestamp);
        m_xData.insertNewValue(dataPoint.xData);
        m_yData.insertNewValue(dataPoint.yData);
    }
}

void TeleconWxPhasePortraitPlot::addToChart(XYChart * chart)
{
    if (m_timestamps.size() <= 0) {
        return;
    }
    TeleconWxPlot::addLinePlotToChart(
        chart,
        m_plotTitle,
        true,
        DoubleArray(&m_xData[0], (int)m_xData.size()),
        DoubleArray(&m_yData[0], (int)m_yData.size()),
        m_lineStyle,
        m_symbolStyle
    );
}

double TeleconWxPhasePortraitPlot::getLeftmostX() const
{
    // TODO: Improve this from a linear search to a binary search (or O(1) if possible by keeping track of the endpoints?)
    double minValue = DBL_MAX;
    for (int i = 0; i < m_xData.size(); ++i) {
        minValue = fmin(minValue, m_xData[i]);
    }
    return minValue;
}

double TeleconWxPhasePortraitPlot::getRightmostX() const
{
    // TODO: Improve this from a linear search to a binary search (or O(1) if possible by keeping track of the endpoints?)
    double maxValue = DBL_MIN;
    for (int i = 0; i < m_xData.size(); ++i) {
        maxValue = fmax(maxValue, m_xData[i]);
    }
    return maxValue;
}

string TeleconWxPhasePortraitPlot::getLatestValueString() const
{
    // Can't believe this is still the only way to do this in C++17 (formatting directly into c++ string isn't added until C++20)
    int size_s = std::snprintf(nullptr, 0, "(%.2f,%.2f)", m_xData[m_xData.size() - 1], m_yData[m_yData.size() - 1]) + 1; // Extra space for '\0'
    std::unique_ptr<char[]> buf(new char[size_s]);
    std::snprintf(buf.get(), size_s, "(%.2f,%.2f)", m_xData[m_xData.size() - 1], m_yData[m_yData.size() - 1]);
    return string(buf.get());
}

bool TeleconWxPhasePortraitPlot::isIncludedInLegend() const
{
    return true;
}

void TeleconWxPhasePortraitPlot::pushData(double timestamp, double xData, double yData)
{
    m_dataToAdd.addDataPoint({ timestamp, xData, yData });
}

shared_ptr<const LineStyle> TeleconWxPhasePortraitPlot::getLineStyle() const
{
    return m_lineStyle;
}
