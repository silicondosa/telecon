#include "teleconwxphaseportraitplot.h"

TeleconWxPhasePortraitPlot::TeleconWxPhasePortraitPlot(string plotTitle, int color, int lineWidth, LineType lineType, bool hasSymbol, int symbol, bool fillSymbol, int symbolSize, size_t depth)
    : TeleconWxPlot(plotTitle, color, depth), m_dataToAdd(depth), m_timestamps(depth), m_xData(depth), m_yData(depth), m_lineWidth(lineWidth), m_lineType(lineType), m_hasSymbol(hasSymbol), m_symbol(symbol), m_fillSymbol(fillSymbol), m_symbolSize(symbolSize) {}

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
    int chartDirColor;
    if (m_lineType == LT_SOLID) {
        chartDirColor = m_color;
    } else { // Solid or none
        chartDirColor = chart->dashLineColor(m_color, Chart::DashLine);
    }
    LineLayer* layer = chart->addLineLayer();

    DataSet* dataSet = layer->addDataSet(DoubleArray(&m_yData[0], (int)m_yData.size()), chartDirColor, (string("\\") + m_plotTitle).c_str());

    dataSet->setLineWidth(m_lineWidth);

    if (m_hasSymbol) {
        dataSet->setDataSymbol(m_symbol, m_symbolSize, m_fillSymbol ? m_color : Chart::Transparent, m_color);
    }

    layer->setXData(DoubleArray(&m_xData[0], (int)m_xData.size()));
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

bool TeleconWxPhasePortraitPlot::isSymbolFilled() const
{
    return m_fillSymbol;
}

int TeleconWxPhasePortraitPlot::getSymbol() const
{
    return m_symbol;
}

int TeleconWxPhasePortraitPlot::getSymbolSize() const
{
    return m_symbolSize;
}
