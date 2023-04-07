#pragma once

#include <string>
#include <vector>

#include "colors.h"
#include "teleconwxplot.h"
#include "teleconwxlineplot.h"
#include "teleconwxscatterplot.h"

using namespace std;

enum CHART_X_AXIS_TYPE {
    CAXT_TIME, // x axis represents a timespan
    CAXT_ARBITARY, // x axis represents some arbitrary non-time data
    CAXT_BOTH // x axis may represent both time and non-time data for different plots
};

class TeleconChart {
protected:
    const string m_title;
    const double m_memoryDepthSeconds;
    const int m_dataRateMillis;
    const string m_xLabel;
    const string m_yLabel;
    const ColorSequenceMode m_colorSequenceMode;

    vector<shared_ptr<TeleconPlot>> m_plots;

    long getNextDefaultColor();
public:
    TeleconChart(string title, double memoryDepthSeconds, int dataRateMillis, string xLabel, string yLabel, ColorSequenceMode colorSequenceMode);

    string getTitle();
    string getXLabel();
    string getYLabel();
    ColorSequenceMode getColorSequenceMode();
    virtual double getDefaultXAxisSpan() = 0;
    
    shared_ptr<TeleconPlot> getPlot(int index);
    size_t getNumPlots();

    shared_ptr<TeleconPlot> getPlotByName(string name);

    virtual CHART_X_AXIS_TYPE getChartXAxisType() = 0;
};