#include "teleconscatterplot.h"

TeleconScatterPlot::TeleconScatterPlot(DoubleFuncPtr dataFuncPtr, int depth, int color, string plotTitle, int symbol, int symbolSize)
    : TeleconPlot(dataFuncPtr, depth, color, plotTitle), m_symbol(symbol), m_symbolSize(symbolSize) {}

int TeleconScatterPlot::getSymbol() const {
	return m_symbol;
}

int TeleconScatterPlot::getSymbolSize() const{
    return m_symbolSize;
}

double TeleconScatterPlot::fetchData() {
    double newValue = m_dataFuncPtr();
    m_yData.insertNewValue(newValue);
    return newValue;
}

void TeleconScatterPlot::addToChart(XYChart* chart, DoubleArray xData) {
    LineLayer* layer = chart->addScatterLayer(xData, DoubleArray(&m_yData[0], m_yData.size()), m_plotTitle.c_str(), m_symbol, m_symbolSize, m_color, m_color);
}