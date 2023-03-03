#include "teleconlineplot.h"

TeleconLinePlot::TeleconLinePlot(DoubleFuncPtr dataFuncPtr, int depth, int color, string plotTitle, int lineWidth, LineType lineType)
    : TeleconPlot(dataFuncPtr, depth, color, plotTitle), m_lineWidth(lineWidth), m_lineType(lineType) {}

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
    if (m_lineType == LT_DASHED) {
        chartDirColor = chart->dashLineColor(m_color, Chart::DashLine);
    } else { // Solid or none
        chartDirColor = m_color;
    } 
    LineLayer* layer = chart->addLineLayer(DoubleArray(&m_yData[0], m_yData.size()), chartDirColor, m_plotTitle.c_str());

    if (m_lineType == LT_NONE) {
        layer->setLineWidth(0);
    } else {
        layer->setLineWidth(m_lineWidth);
    }

    // The x-coordinates are the timeStamps.
    layer->setXData(xData);
}
