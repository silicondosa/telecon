#include "teleconlineplot.h"

TeleconLinePlot::TeleconLinePlot(int depth, int color, string plotTitle, int lineWidth, LineType lineType, bool hasSymbol, int symbol, bool fillSymbol, int symbolSize)
    : TeleconWxPlot(depth, color, plotTitle), m_lineWidth(lineWidth), m_lineType(lineType), m_hasSymbol(hasSymbol), m_symbol(symbol), m_fillSymbol(fillSymbol), m_symbolSize(symbolSize) {}

list<pair<double, double>>* TeleconLinePlot::swapAndGetDataToAdd()
{
    //printf("First element when swapping: %f", m_dataToAdd->front().first);
    list<pair<double, double>>* newDataToAdd = new list<pair<double, double>>();
    list<pair<double, double>>* oldDataToAdd = m_dataToAdd;

    const lock_guard<mutex> lock(m_dataToAddLock);
    m_dataToAdd = newDataToAdd;
    return oldDataToAdd;
}

void TeleconLinePlot::prepDataForDraw()
{
    list<pair<double, double>>* dataToAdd = swapAndGetDataToAdd();

    for (const auto& xyPair : *dataToAdd) {
        m_xTimestamps.insertNewValue(xyPair.first);
        m_yData.insertNewValue(xyPair.second);
    }

    delete dataToAdd;
}

int TeleconLinePlot::getLineWidth() const {
    return m_lineWidth;
}

LineType TeleconLinePlot::getLineType() const {
    return m_lineType;
}

double TeleconLinePlot::getLeftmostX()
{
    return m_xTimestamps[0];
}

double TeleconLinePlot::getRightmostX()
{
    return m_xTimestamps[m_xTimestamps.size() - 1];
}

void TeleconLinePlot::addToChart(XYChart* chart) {
    if (m_yData.size() <= 0) {
        return;
    }
    // This integer represents both the color and dash status (solid, dashed, or none) of the chart
    int chartDirColor;
    if (m_lineType == LT_SOLID) {
        chartDirColor = m_color;
    } else { // Solid or none
        chartDirColor = chart->dashLineColor(m_color, Chart::DashLine);
    } 
    LineLayer* layer = chart->addLineLayer();

    DataSet* dataSet = layer->addDataSet(DoubleArray(&m_yData[0], (int)m_yData.size()), chartDirColor, m_plotTitle.c_str());

    dataSet->setLineWidth(m_lineWidth);

    if (m_hasSymbol) {
        dataSet->setDataSymbol(m_symbol, m_symbolSize, m_fillSymbol ? m_color : Chart::Transparent, m_color);
    }

    // The x-coordinates are the timeStamps.
    layer->setXData(DoubleArray(&m_xTimestamps[0], (int)m_xTimestamps.size()));
}
