#pragma once

#include "teleconwindow.h"
#include "telecondatachartimplchartdir.h"
#include "teleconrealtimechartimplchartdir.h"

class TeleconWindowImplChartDir : public TeleconWindow
{
private:
    std::vector<shared_ptr<TeleconChartImplChartDir>> m_charts;
public:
    TeleconWindowImplChartDir(std::string title = "");
    shared_ptr<TeleconChartImplChartDir> getChartImpl(size_t index);
    /**
     * Initializer function. After this has been called, no further changes to the window may be made.
     */
    void initialize();
    virtual shared_ptr<TeleconRealtimeChart> addRealtimeChart(std::string title, double memoryDepthSeconds, int dataRateMillis, std::string xLabel, std::string yLabel, ColorSequenceMode colorSequenceMode) override;
    virtual shared_ptr<TeleconDataChart> addDataChart(std::string title, double memoryDepthSeconds, int dataRateMillis, std::string xLabel, std::string yLabel, ColorSequenceMode colorSequenceMode) override;
    virtual shared_ptr<TeleconChart> getChart(size_t index) override;
    virtual size_t getNumCharts() const override;
    virtual shared_ptr<TeleconChart> getChartByName(string name) override;
    virtual shared_ptr<TeleconPlot> getPlotByName(string chartName, string plotName) override;
};