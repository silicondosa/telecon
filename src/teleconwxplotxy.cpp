#include "teleconwxplotxy.h"

TeleconWxPlotXY::TeleconWxPlotXY(string plotTitle, int color, int lineWidth, LineType lineType, bool hasSymbol, int symbol, bool fillSymbol, int symbolSize, size_t depth)
    : TeleconWxPlot(plotTitle, color, depth), m_dataToAdd(m_depth), m_xTimestamps(m_depth), m_yData(m_depth), m_lineWidth(lineWidth), m_lineType(lineType), m_hasSymbol(hasSymbol), m_symbol(symbol), m_fillSymbol(fillSymbol), m_symbolSize(symbolSize) {}

void TeleconWxPlotXY::prepDataForDraw()
{
    shared_ptr<list<XYPlotDataPoint>> dataToAdd = m_dataToAdd.getDataAndClearList();

    for (const auto& xyPair : *dataToAdd) {
        m_xTimestamps.insertNewValue(xyPair.xTimestamp);
        m_yData.insertNewValue(xyPair.yData);
    }
}

double TeleconWxPlotXY::getLeftmostX() const
{
    return m_xTimestamps[0];
}

double TeleconWxPlotXY::getRightmostX() const
{
    return m_xTimestamps[m_xTimestamps.size() - 1];
}

string TeleconWxPlotXY::getLatestValueString() const
{
    // Can't believe this is still the only way to do this in C++17 (formatting directly into c++ string isn't added until C++20)
    int size_s = std::snprintf(nullptr, 0, "%.2f", m_yData[m_yData.size() - 1]) + 1; // Extra space for '\0'
    std::unique_ptr<char[]> buf(new char[size_s]);
    std::snprintf(buf.get(), size_s, "%.2f", m_yData[m_yData.size() - 1]);
    return string(buf.get());
}

bool TeleconWxPlotXY::isIncludedInLegend() const
{
    return true;
}

void TeleconWxPlotXY::addToChart(XYChart* chart) {
    if (m_yData.size() <= 0) {
        return;
    }
    // This integer represents both the color and dash status (solid, dashed, or none) of the chart
    int chartDirColor;
    if (m_lineType == LT_SOLID) {
        chartDirColor = m_color;
    }
    else { // Solid or none
        chartDirColor = chart->dashLineColor(m_color, Chart::DashLine);
    }
    LineLayer* layer = chart->addLineLayer();

    DataSet* dataSet = layer->addDataSet(DoubleArray(&m_yData[0], (int)m_yData.size()), chartDirColor, (string("\\") + m_plotTitle).c_str());

    dataSet->setLineWidth(m_lineWidth);

    if (m_hasSymbol) {
        dataSet->setDataSymbol(m_symbol, m_symbolSize, m_fillSymbol ? m_color : Chart::Transparent, m_color);
    }

    // The x-coordinates are the timeStamps.
    layer->setXData(DoubleArray(&m_xTimestamps[0], (int)m_xTimestamps.size()));
}

size_t TeleconWxPlotXY::size() const
{
    return m_xTimestamps.size();
}

void TeleconWxPlotXY::pushData(double xTimestamp, double yData)
{
    m_dataToAdd.addDataPoint({ xTimestamp, yData });
}

bool TeleconWxPlotXY::isSymbolFilled() const
{
    return m_fillSymbol;
}

int TeleconWxPlotXY::getSymbol() const
{
    return m_symbol;
}

int TeleconWxPlotXY::getSymbolSize() const
{
    return m_symbolSize;
}