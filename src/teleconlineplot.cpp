#include "teleconlineplot.h"

TeleconLinePlot::TeleconLinePlot(DoubleFuncPtr dataFuncPtr, int depth, int color, string plotTitle, int lineWidth, LineType lineType, bool hasSymbol, int symbol, int symbolSize)
    : TeleconPlot(dataFuncPtr, depth, color, plotTitle), m_lineWidth(lineWidth), m_lineType(lineType), m_hasSymbol(hasSymbol), m_symbol(symbol), m_symbolSize(symbolSize) {}

int TeleconLinePlot::getLineWidth() const {
    return m_lineWidth;
}

LineType TeleconLinePlot::getLineType() const {
    return m_lineType;
}

double TeleconLinePlot::fetchData() {
    double newValue = m_dataFuncPtr();
    m_yData.insertNewValue(newValue);
    return newValue;
}

void TeleconLinePlot::addToChart(XYChart* chart, DoubleArray xData) {
    // This integer represents both the color and dash status (solid, dashed, or none) of the chart
    int chartDirColor;
    if (m_lineType == LT_SOLID) {
        chartDirColor = m_color;
    } else { // Solid or none
        chartDirColor = chart->dashLineColor(m_color, Chart::DashLine);
    } 
    LineLayer* layer = chart->addLineLayer();

    DataSet* dataSet = layer->addDataSet(DoubleArray(&m_yData[0], m_yData.size()), chartDirColor, m_plotTitle.c_str());

    dataSet->setLineWidth(m_lineWidth);

    if (m_hasSymbol) {
        dataSet->setDataSymbol(m_symbol, m_symbolSize);
    }

    // The x-coordinates are the timeStamps.
    layer->setXData(xData);
}
