#include <iostream>

#include "teleconrealtimechartimplchartdir.h"

TeleconRealtimeChartImplChartDir::TeleconRealtimeChartImplChartDir(string title, double memoryDepthSeconds, int dataRateMillis, string xLabel, string yLabel, ColorSequenceMode colorSequenceMode)
    : TeleconChart(title, memoryDepthSeconds, dataRateMillis, xLabel, yLabel, colorSequenceMode),
    TeleconChartImplChartDir(title, memoryDepthSeconds, dataRateMillis, xLabel, yLabel, colorSequenceMode),
    TeleconRealtimeChart(title, memoryDepthSeconds, dataRateMillis, xLabel, yLabel, colorSequenceMode) {}

shared_ptr<TeleconLinePlot> TeleconRealtimeChartImplChartDir::addLinePlot(std::string plottitle, const LineStyle& lineStyle, const SymbolStyle& symbolStyle, size_t memoryDepth)
{
    if (TeleconChart::m_hasStarted) {
        cout << "telecon: Telecon has already started, plots may not be added." << endl;
        return shared_ptr<TeleconLinePlot>();
    }
    LineStyle plotLineStyle(lineStyle);
    SymbolStyle plotSymbolStyle(symbolStyle);
    if (lineStyle.getLineColor() == COLOR_DEFAULT) {
        plotLineStyle.setLineColor(TeleconChart::getNextDefaultColor());
    }
    if (symbolStyle.getSymbolColor() == COLOR_DEFAULT) {
        plotSymbolStyle.setSymbolColor(plotLineStyle.getLineColor());
    }
    // The plus one is because of fencepost effect: in ten seconds (inclusive), sampling one data point per second, you get 11 data points
    size_t depth = memoryDepth == -1 ? (size_t)(TeleconChart::m_memoryDepthSeconds / (TeleconChart::m_dataRateMillis / 1000.0) + 1) : memoryDepth;
    shared_ptr<TeleconWxLinePlot> linePlot = make_shared<TeleconWxLinePlot>(plottitle, depth, plotLineStyle, plotSymbolStyle);
    m_plots.push_back(linePlot);
    return linePlot;
}

shared_ptr<TeleconScatterPlot> TeleconRealtimeChartImplChartDir::addScatterPlot(std::string plottitle, const SymbolStyle& symbolStyle, size_t memoryDepth)
{
    if (TeleconChart::m_hasStarted) {
        cout << "telecon: Telecon has already started, plots may not be added." << endl;
        return shared_ptr<TeleconScatterPlot>();
    }
    SymbolStyle plotSymbolStyle(symbolStyle);
    if (symbolStyle.getSymbolColor() == COLOR_DEFAULT) {
        plotSymbolStyle.setSymbolColor(TeleconChart::getNextDefaultColor());
    }
    size_t depth = memoryDepth == -1 ? (size_t)(TeleconChart::m_memoryDepthSeconds / (TeleconChart::m_dataRateMillis / 1000.0) + 1) : memoryDepth;
    shared_ptr<TeleconWxScatterPlot> scatterPlot = make_shared<TeleconWxScatterPlot>(plottitle, depth, plotSymbolStyle);
    m_plots.push_back(scatterPlot);
    return scatterPlot;
}

shared_ptr<TeleconRasterPlot> TeleconRealtimeChartImplChartDir::addRasterPlot(string plottitle, double yValue, const SymbolStyle& symbolStyle, size_t memoryDepth)
{
    if (TeleconChart::m_hasStarted) {
        cout << "telecon: Telecon has already started, plots may not be added." << endl;
        return shared_ptr<TeleconRasterPlot>();
    }
    SymbolStyle plotSymbolStyle(symbolStyle);
    if (symbolStyle.getSymbolColor() == COLOR_DEFAULT) {
        plotSymbolStyle.setSymbolColor(TeleconChart::getNextDefaultColor());
    }
    size_t depth = memoryDepth == -1 ? (size_t)(TeleconChart::m_memoryDepthSeconds / (TeleconChart::m_dataRateMillis / 1000.0) + 1) : memoryDepth;
    shared_ptr<TeleconWxRasterPlot> rasterPlot = make_shared<TeleconWxRasterPlot>(plottitle, yValue, depth, plotSymbolStyle);
    m_plots.push_back(rasterPlot);
    return rasterPlot;
}