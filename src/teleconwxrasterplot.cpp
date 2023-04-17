#include "teleconwxrasterplot.h"

TeleconWxRasterPlot::TeleconWxRasterPlot(string plotTitle, double yValue, size_t depth, const SymbolStyle& symbolStyle)
    : TeleconWxPlot(plotTitle, depth, symbolStyle), m_dataToAdd(depth), m_xTimestamps(depth), m_yValue(yValue), m_yValueBuffer(depth)
{
    if (m_symbolStyle->getSymbolColor() == COLOR_DEFAULT) {
        m_symbolStyle->setSymbolColor(COLOR_BLACK);
    }
}

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
    TeleconWxPlot::addScatterPlotToChart(
        chart,
        m_plotTitle,
        false,
        DoubleArray(&m_xTimestamps[0], (int)m_xTimestamps.size()),
        DoubleArray(&m_yValueBuffer[0], (int)m_yValueBuffer.size()),
        m_symbolStyle
    );
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