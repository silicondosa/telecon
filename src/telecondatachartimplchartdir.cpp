#include <iostream>

#include "telecondatachartimplchartdir.h"

TeleconDataChartImplChartDir::TeleconDataChartImplChartDir(string title, double memoryDepthSeconds, int dataRateMillis, string xLabel, string yLabel, ColorSequenceMode colorSequenceMode)
    : TeleconChart(title, memoryDepthSeconds, dataRateMillis, xLabel, yLabel, colorSequenceMode),
    TeleconChartImplChartDir(title, memoryDepthSeconds, dataRateMillis, xLabel, yLabel, colorSequenceMode),
    TeleconDataChart(title, memoryDepthSeconds, dataRateMillis, xLabel, yLabel, colorSequenceMode) {}

shared_ptr<TeleconPhasePortraitPlot> TeleconDataChartImplChartDir::addPhasePortraitPlot(std::string plottitle, const LineStyle& lineStyle, const SymbolStyle& symbolStyle, size_t memoryDepth)
{
    if (TeleconChart::m_hasStarted) {
        cout << "telecon: Telecon has already started, plots may not be added." << endl;
        return shared_ptr<TeleconPhasePortraitPlot>();
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
    shared_ptr<TeleconWxPhasePortraitPlot> phasePortrait = make_shared<TeleconWxPhasePortraitPlot>(plottitle, depth, plotLineStyle, plotSymbolStyle);
    m_plots.push_back(phasePortrait);
    return phasePortrait;
}
