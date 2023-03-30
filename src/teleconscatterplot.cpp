#include "teleconscatterplot.h"

TeleconScatterPlot::TeleconScatterPlot(int depth, int color, string plotTitle, int symbol, bool fillSymbol, int symbolSize)
    : TeleconPlot(depth, color, plotTitle), m_symbol(symbol), m_fillSymbol(fillSymbol), m_symbolSize(symbolSize) {}

list<pair<double, double>>* TeleconScatterPlot::swapAndGetDataToAdd()
{
    list<pair<double, double>>* newDataToAdd = new list<pair<double, double>>();
    list<pair<double, double>>* oldDataToAdd = m_dataToAdd;

    const lock_guard<mutex> lock(m_dataToAddLock);
    m_dataToAdd = newDataToAdd;
    return oldDataToAdd;
}

void TeleconScatterPlot::prepDataForDraw() {
    list<pair<double, double>>* dataToAdd = swapAndGetDataToAdd();

    for (const auto& xyPair : *dataToAdd) {
        m_xTimestamps.insertNewValue(xyPair.first);
        m_yData.insertNewValue(xyPair.second);
    }

    delete dataToAdd;
}

int TeleconScatterPlot::getSymbol() const {
	return m_symbol;
}

int TeleconScatterPlot::getSymbolSize() const{
    return m_symbolSize;
}

double TeleconScatterPlot::getLeftmostX()
{
    return m_xTimestamps[0];
}

double TeleconScatterPlot::getRightmostX()
{
    return m_xTimestamps[m_xTimestamps.size() - 1];
}

void TeleconScatterPlot::addToChart(XYChart* chart) {
    if (m_yData.size() <= 0) {
        return;
    }
    size_t size = m_xTimestamps.size();
    LineLayer* layer = chart->addScatterLayer(DoubleArray(&m_xTimestamps[0], (int)m_xTimestamps.size()), DoubleArray(&m_yData[0], (int)m_yData.size()), m_plotTitle.c_str(), m_symbol, m_symbolSize, m_fillSymbol ? m_color : Chart::Transparent, m_color);
}