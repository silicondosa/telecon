#pragma once

#include <string>
#include <vector>

#include "colors.h"
#include "teleconplot.h"
#include "teleconlineplot.h"
#include "teleconscatterplot.h"

using namespace std;

enum CHART_X_AXIS_TYPE {
    CAXT_TIME, // x axis represents a timespan
    CAXT_ARBITARY, // x axis represents some arbitrary non-time data
    CAXT_BOTH // x axis may represent both time and non-time data for different plots
};

class TeleconChart {
protected:
    const string m_title;
    const string m_xLabel;
    const string m_yLabel;
    const ColorSequenceMode m_colorSequenceMode;
    const double m_defaultXAxisSpan;

    vector<TeleconPlot*> m_plots;

    long getNextDefaultColor();
public:
    TeleconChart(string title, string xLabel, string yLabel, ColorSequenceMode colorSequenceMode, double defaultXAxisSpan);

    string getTitle();
    string getXLabel();
    string getYLabel();
    ColorSequenceMode getColorSequenceMode();
    double getDefaultXAxisSpan();
    
    TeleconPlot* getPlot(int index);
    int getNumPlots();

    TeleconPlot* getPlotByName(string name);

    virtual CHART_X_AXIS_TYPE getChartXAxisType() = 0;
};