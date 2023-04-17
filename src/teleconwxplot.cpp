#include "teleconwxplot.h"

int TeleconWxPlot::getChartDirSymbolFromPlotSymbol(PlotSymbol symbol)
{
    switch (symbol) {
    case SYMBOL_NO_SYMBOL:
        return Chart::NoShape;
        break;
    case SYMBOL_CIRCLE:
        return Chart::CircleShape;
        break;
    case SYMBOL_SQUARE:
        return Chart::SquareShape;
        break;
    case SYMBOL_TRIANGLE:
        return Chart::TriangleShape;
        break;
    case SYMBOL_DIAMOND:
        return Chart::DiamondShape;
        break;
    case SYMBOL_CROSS:
        return Chart::Cross2Shape(0.3);
        break;
    case SYMBOL_PLUS:
        return Chart::CrossShape(0.3);
        break;
    case SYMBOL_STAR:
        return Chart::StarShape(5);
        break;
    default:
        // Should be impossible, cases are exhaustive
        return Chart::NoShape;
        break;
    }
}

void TeleconWxPlot::addLinePlotToChart(XYChart* chart, string plotTitle, bool includeInLegend, DoubleArray xArray, DoubleArray yArray, shared_ptr<const LineStyle> lineStyle, shared_ptr<const SymbolStyle> symbolStyle)
{
    int chartDirColor;
    if (lineStyle->getLineType() == LT_SOLID) {
        chartDirColor = lineStyle->getLineColor();
    } else { // Solid or none
        chartDirColor = chart->dashLineColor(lineStyle->getLineColor(), Chart::DashLine);
    }
    LineLayer* layer = chart->addLineLayer();

    DataSet* dataSet = layer->addDataSet(
        yArray,
        chartDirColor,
        ((includeInLegend ? string("\\") : string("notitle\\")) + plotTitle).c_str()
    );

    dataSet->setLineWidth(lineStyle->getLineWidth());

    dataSet->setDataSymbol(
        getChartDirSymbolFromPlotSymbol(symbolStyle->getSymbol()),
        symbolStyle->getSymbolSize(), (symbolStyle->getFillSymbol() ? symbolStyle->getSymbolColor() : Chart::Transparent),
        symbolStyle->getSymbolColor()
    );

    layer->setXData(xArray);
}

void TeleconWxPlot::addScatterPlotToChart(XYChart* chart, string plotTitle, bool includeInLegend, DoubleArray xArray, DoubleArray yArray, shared_ptr<const SymbolStyle> symbolStyle)
{
    ScatterLayer* layer = chart->addScatterLayer(
        xArray,
        yArray,
        ((includeInLegend ? string("\\") : string("notitle\\")) + plotTitle).c_str(),
        getChartDirSymbolFromPlotSymbol(symbolStyle->getSymbol()),
        symbolStyle->getSymbolSize(),
        symbolStyle->getFillSymbol() ? symbolStyle->getSymbolColor() : Chart::Transparent,
        symbolStyle->getSymbolColor()
    );
}

TeleconWxPlot::TeleconWxPlot(string plotTitle, size_t depth, const SymbolStyle& symbolStyle)
	: m_plotTitle(plotTitle), m_depth(depth), m_symbolStyle(make_shared<SymbolStyle>(symbolStyle)) {}

size_t TeleconWxPlot::depth() const {
	return m_depth;
}

const string TeleconWxPlot::getPlotTitle() const {
	return m_plotTitle;
}

shared_ptr<const SymbolStyle> TeleconWxPlot::getSymbolStyle() const
{
    return m_symbolStyle;
}
