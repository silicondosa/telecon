#pragma once

#include "teleconwindow.h"
#include "telecondatachartimplchartdir.h"
#include "teleconrealtimechartimplchartdir.h"

/**
 * The wxChartDir implementation of the TeleconWindow interface.
 */
class TeleconWindowImplChartDir : public TeleconWindow
{
private:
    std::vector<shared_ptr<TeleconChartImplChartDir>> m_charts;
public:
    /**
     * \copydoc TeleconWindow::TeleconWindow
     */
    TeleconWindowImplChartDir(std::string title = "");

    /**
     * \param index the index of the TeleconChart to return as a TeleconChartImplChartDir, relative to the order added.
     * \return A pointer to the TeleconChart requested.
     */
    shared_ptr<TeleconChartImplChartDir> getChartImpl(size_t index);

    /**
     * Initializer function. After this has been called, no further changes to the window may be made.
     */
    void initialize();

    /**
     * \copydoc TeleconWindow::addRealtimechart
     */
    virtual shared_ptr<TeleconRealtimeChart> addRealtimeChart(std::string title, double memoryDepthSeconds, int dataRateMillis, std::string xLabel, std::string yLabel, ColorSequenceMode colorSequenceMode) override;
    
    /**
     * \copydoc TeleconWindow::addDatachart
     */
    virtual shared_ptr<TeleconDataChart> addDataChart(std::string title, double memoryDepthSeconds, int dataRateMillis, std::string xLabel, std::string yLabel, ColorSequenceMode colorSequenceMode) override;
    
    /**
     * \copydoc TeleconWindow::getChart
     */
    virtual shared_ptr<TeleconChart> getChart(size_t index) override;
    
    /**
     * \copydoc TeleconWindow::getNumCharts
     */
    virtual size_t getNumCharts() const override;

    /**
     * \copydoc TeleconWindow::getChartByName
     */
    virtual shared_ptr<TeleconChart> getChartByName(string name) override;
    
    /**
     * \copydoc TeleconWindow::getPlotByName
     */
    virtual shared_ptr<TeleconPlot> getPlotByName(string chartName, string plotName) override;
};