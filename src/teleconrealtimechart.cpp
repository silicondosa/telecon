#include "teleconrealtimechart.h"

#include <iostream>

TeleconRealtimeChart::TeleconRealtimeChart(string title, double memoryDepthSeconds, int dataRateMillis, string xLabel, string yLabel, ColorSequenceMode colorSequenceMode)
	: TeleconChart(title, memoryDepthSeconds, dataRateMillis, xLabel, yLabel, colorSequenceMode) {}

shared_ptr<TeleconLinePlot> TeleconRealtimeChart::addLinePlot(string plottitle, long plotcolor, LineType lineType, int lineWidth, int symbol, bool fillSymbol, int symbolSize, int memoryDepth)
{
    if (m_hasStarted) {
        cout << "telecon: Telecon has already started, plots may not be added." << endl;
        return shared_ptr<TeleconLinePlot>();
    }
	long color = plotcolor == COLOR_DEFAULT ? getNextDefaultColor() : plotcolor;
	// The plus one is because of fencepost effect: in ten seconds (inclusive), sampling one data point per second, you get 11 data points
	int depth = (int)(memoryDepth == -1 ? m_memoryDepthSeconds / (m_dataRateMillis / 1000.0) : memoryDepth) + 1;
	shared_ptr<TeleconWxLinePlot> linePlot = make_shared<TeleconWxLinePlot>(plottitle, color, lineWidth, lineType, symbol != Chart::NoSymbol, symbol, fillSymbol, symbolSize, depth);
	m_plots.push_back(linePlot);
	return linePlot;
}

shared_ptr<TeleconScatterPlot> TeleconRealtimeChart::addScatterPlot(string plottitle, long plotcolor, int symbol, bool fillSymbol, int symbolSize, int memoryDepth)
{
    if (m_hasStarted) {
        cout << "telecon: Telecon has already started, plots may not be added." << endl;
        return shared_ptr<TeleconScatterPlot>();
    }
	long color = plotcolor == COLOR_DEFAULT ? getNextDefaultColor() : plotcolor;
	int depth = (int)(memoryDepth == -1 ? m_memoryDepthSeconds / (m_dataRateMillis / 1000.0) : memoryDepth) + 1;
	shared_ptr<TeleconWxScatterPlot> scatterPlot = make_shared<TeleconWxScatterPlot>(plottitle, color, symbol, fillSymbol, symbolSize, depth);
	m_plots.push_back(scatterPlot);
	return scatterPlot;
}

shared_ptr<TeleconRasterPlot> TeleconRealtimeChart::addRasterPlot(string plottitle, double yValue, long plotcolor, int symbol, bool fillSymbol, int symbolSize, int memoryDepth)
{
    if (m_hasStarted) {
        cout << "telecon: Telecon has already started, plots may not be added." << endl;
        return shared_ptr<TeleconRasterPlot>();
    }
    long color = plotcolor == COLOR_DEFAULT ? getNextDefaultColor() : plotcolor;
    int depth = (int)(memoryDepth == -1 ? m_memoryDepthSeconds / (m_dataRateMillis / 1000.0) : memoryDepth) + 1;
    shared_ptr<TeleconRasterPlot> rasterPlot = make_shared<TeleconWxRasterPlot>(plottitle, yValue, color, symbol, fillSymbol, symbolSize, depth);
    m_plots.push_back(rasterPlot);
    return rasterPlot;
}

double TeleconRealtimeChart::getDefaultXAxisSpan()
{
	return m_memoryDepthSeconds;
}

CHART_X_AXIS_TYPE TeleconRealtimeChart::getChartXAxisType()
{
	return CAXT_TIME;
}
