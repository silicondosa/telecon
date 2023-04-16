#include "teleconwxrasterplot.h"

TeleconWxRasterPlot::TeleconWxRasterPlot(string plotTitle, double yValue, int color, int symbol, bool fillSymbol, int symbolSize, size_t depth)
    : TeleconWxPlot(plotTitle, color, depth), m_dataToAdd(depth), m_xTimestamps(depth), m_yValue(yValue), m_yValueBuffer(depth), m_symbol(symbol), m_fillSymbol(fillSymbol), m_symbolSize(symbolSize) {}

double TeleconWxRasterPlot::getYValue() const
{
    return m_yValue;
}

size_t TeleconWxRasterPlot::size() const
{
    return m_xTimestamps.size();
}

void TeleconWxRasterPlot::prepDataForDraw()
{
    shared_ptr<list<RasterDataPoint>>dataToAdd = m_dataToAdd.getDataAndClearList();

    for (const auto& activationValue : *dataToAdd) {
        m_xTimestamps.insertNewValue(activationValue.xTimestamp);
        m_yValueBuffer.insertNewValue(activationValue.isActive ? m_yValue : Chart::NoValue);
    }
}

void TeleconWxRasterPlot::addToChart(XYChart* chart)
{
    if (m_xTimestamps.size() <= 0) {
        return;
    }
    ScatterLayer* layer = chart->addScatterLayer(DoubleArray(&m_xTimestamps[0], (int)m_xTimestamps.size()), DoubleArray(&m_yValueBuffer[0], (int)m_yValueBuffer.size()), (string("notitle\\") + m_plotTitle).c_str(), m_symbol, m_symbolSize, m_fillSymbol ? m_color : Chart::Transparent, m_color);
}

double TeleconWxRasterPlot::getLeftmostX() const
{
    return m_xTimestamps[0];
}

double TeleconWxRasterPlot::getRightmostX() const
{
    return m_xTimestamps[m_xTimestamps.size() - 1];
}

string TeleconWxRasterPlot::getLatestValueString() const
{
    if (m_yValueBuffer[m_yValueBuffer.size() - 1] == Chart::NoValue) {
        return "inactive";
    }
    return "active";
}

bool TeleconWxRasterPlot::isIncludedInLegend() const
{
    return false;
}

void TeleconWxRasterPlot::pushData(double xTimestamp, bool isActive)
{
    m_dataToAdd.addDataPoint({ xTimestamp, isActive });
}

bool TeleconWxRasterPlot::isSymbolFilled() const
{
    return m_fillSymbol;
}

int TeleconWxRasterPlot::getSymbol() const
{
    return m_symbol;
}

int TeleconWxRasterPlot::getSymbolSize() const
{
    return m_symbolSize;
}
