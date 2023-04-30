#include "teleconchartimplchartdir.h"

TeleconChartImplChartDir::TeleconChartImplChartDir(string title, double memoryDepthSeconds, int dataRateMillis, string xLabel, string yLabel, ColorSequenceMode colorSequenceMode)
    : TeleconChart(title, memoryDepthSeconds, dataRateMillis, xLabel, yLabel, colorSequenceMode) {}

shared_ptr<TeleconWxPlot> TeleconChartImplChartDir::getWxPlot(int index)
{
    return m_plots[index];
}

shared_ptr<TeleconPlot> TeleconChartImplChartDir::getPlot(int index)
{
    return getWxPlot(index);
}

size_t TeleconChartImplChartDir::getNumPlots()
{
    return m_plots.size();
}

shared_ptr<TeleconPlot> TeleconChartImplChartDir::getPlotByName(string name)
{
    for (auto plot : m_plots) {
        if (name.compare(plot->getPlotTitle()) == 0) {
            return plot;
        }
    }
    return nullptr;
}

void TeleconChartImplChartDir::initialize()
{
    m_hasStarted = true;
}