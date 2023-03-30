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
    const string m_xLabel;
    const string m_yLabel;
    const ColorSequenceMode m_colorSequenceMode;
    const double m_defaultXAxisSpan;

    vector<TeleconWxPlot*> m_plots;

    long getNextDefaultColor();
public:
    TeleconChart(string title, string xLabel, string yLabel, ColorSequenceMode colorSequenceMode, double defaultXAxisSpan);

    string getTitle();
    string getXLabel();
    string getYLabel();
    ColorSequenceMode getColorSequenceMode();
    double getDefaultXAxisSpan();
    
    TeleconWxPlot* getPlot(int index);
    int getNumPlots();

    TeleconWxPlot* getPlotByName(string name);

    virtual CHART_X_AXIS_TYPE getChartXAxisType() = 0;
};