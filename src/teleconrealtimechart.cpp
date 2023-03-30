#include "teleconrealtimechart.h"

TeleconRealtimeChart::TeleconRealtimeChart(string title, string xLabel, string yLabel, ColorSequenceMode colorSequenceMode, double defaultTimespan)
	: TeleconChart(title, xLabel, yLabel, colorSequenceMode, defaultTimespan) {}

TeleconWxLinePlot* TeleconRealtimeChart::addLinePlot(string plottitle, int memoryDepth, long plotcolor, LineType lineType, int lineWidth, int symbol, bool fillSymbol, int symbolSize)
{
	long color = plotcolor == COLOR_DEFAULT ? getNextDefaultColor() : plotcolor;
	TeleconWxLinePlot* linePlot = new TeleconWxLinePlot(memoryDepth, color, plottitle, lineWidth, lineType, symbol != Chart::NoSymbol, symbol, fillSymbol, symbolSize);
	m_plots.push_back(linePlot);
	return linePlot;
}

TeleconWxScatterPlot* TeleconRealtimeChart::addScatterPlot(string plottitle, int memoryDepth, long plotcolor, int symbol, bool fillSymbol, int symbolSize)
{
	long color = plotcolor == COLOR_DEFAULT ? getNextDefaultColor() : plotcolor;
	TeleconWxScatterPlot* scatterPlot = new TeleconWxScatterPlot(memoryDepth, color, plottitle, symbol, fillSymbol, symbolSize);
	m_plots.push_back(scatterPlot);
	return scatterPlot;
}

CHART_X_AXIS_TYPE TeleconRealtimeChart::getChartXAxisType()
{
	return CAXT_TIME;
}
