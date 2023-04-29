#pragma once

#include "teleconchart.h"
#include "teleconwxplot.h"

/**
 * The wxChartDir implementation of the TeleconChart interface.
 */
class TeleconChartImplChartDir : virtual public TeleconChart
{
protected:
    /** A list of the plots that have been added to the chart. */
    vector<shared_ptr<TeleconWxPlot>> m_plots;
public:
    /**
     * \copydoc TeleconChart::TeleconChart
     */
    TeleconChartImplChartDir(string title, double memoryDepthSeconds, int dataRateMillis, string xLabel, string yLabel, ColorSequenceMode colorSequenceMode);

    /**
     * \param index the index of the TeleconPlot to return as a TeleconWxPlot, relative to the order added.
     * \return A pointer to the TeleconWxPlot requested.
     */
    shared_ptr<TeleconWxPlot> getWxPlot(int index);

    /**
     * Initializer function. After this has been called, no further changes to the chart may be made.
     */
    void initialize();

    /**
     * \copydoc TeleconChart::getPlot
     */
    virtual shared_ptr<TeleconPlot> getPlot(int index) override;

    /**
     * \copydoc TeleconChart::getNumPlots
     */
    virtual size_t getNumPlots() override;

    /**
     * \copydoc TeleconChart::getPlotByName
     */
    virtual shared_ptr<TeleconPlot> getPlotByName(string name) override;
};
