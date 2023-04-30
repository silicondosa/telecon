#include <iostream>

#include "teleconwindowimplchartdir.h"

TeleconWindowImplChartDir::TeleconWindowImplChartDir(std::string title)
    : TeleconWindow(title) {}

shared_ptr<TeleconChartImplChartDir> TeleconWindowImplChartDir::getChartImpl(size_t index)
{
    return m_charts[index];
}

shared_ptr<TeleconRealtimeChart> TeleconWindowImplChartDir::addRealtimeChart(std::string title, double memoryDepthSeconds, int dataRateMillis, std::string xLabel, std::string yLabel, ColorSequenceMode colorSequenceMode)
{
    if (m_hasStarted) {
        cout << "telecon: Telecon has already started, charts may not be added." << endl;
        return shared_ptr<TeleconRealtimeChart>();
    }
    shared_ptr<TeleconRealtimeChartImplChartDir> chart = make_shared<TeleconRealtimeChartImplChartDir>(title, memoryDepthSeconds, dataRateMillis, xLabel, yLabel, colorSequenceMode);
    m_charts.push_back(chart);
    return chart;
}

shared_ptr<TeleconDataChart> TeleconWindowImplChartDir::addDataChart(std::string title, double memoryDepthSeconds, int dataRateMillis, std::string xLabel, std::string yLabel, ColorSequenceMode colorSequenceMode)
{
    if (m_hasStarted) {
        cout << "telecon: Telecon has already started, charts may not be added." << endl;
        return shared_ptr<TeleconDataChart>();
    }
    shared_ptr<TeleconDataChartImplChartDir> chart = make_shared<TeleconDataChartImplChartDir>(title, memoryDepthSeconds, dataRateMillis, xLabel, yLabel, colorSequenceMode);
    m_charts.push_back(chart);
    return chart;
}

shared_ptr<TeleconChart> TeleconWindowImplChartDir::getChart(size_t index)
{
    return getChartImpl(index);
}

size_t TeleconWindowImplChartDir::getNumCharts() const
{
    return m_charts.size();
}

shared_ptr<TeleconChart> TeleconWindowImplChartDir::getChartByName(string name)
{
    for (auto chart : m_charts) {
        if (name.compare(chart->getTitle()) == 0) {
            return chart;
        }
    }
    return nullptr;
}

shared_ptr<TeleconPlot> TeleconWindowImplChartDir::getPlotByName(string chartName, string plotName)
{
    shared_ptr<TeleconChart> chart = getChartByName(chartName);
    return chart == nullptr ? nullptr : chart->getPlotByName(plotName);
}

void TeleconWindowImplChartDir::initialize()
{
    m_hasStarted = true;
    for (shared_ptr<TeleconChartImplChartDir> chart : m_charts) {
        chart->initialize();
    }
}