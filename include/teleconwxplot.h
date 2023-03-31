#pragma once

#include <string>
#include <mutex>
#include <list>

#include "chartdir.h"
#include "databuffer.h"
#include "teleconplot.h"

using namespace std;

class TeleconWxPlot : virtual public TeleconPlot {
protected:
    const size_t m_depth;
	int m_color; // Represented as an RGB hexadecimal code (one byte per channel)
	string m_plotTitle;
public:
	TeleconWxPlot(size_t depth, int color, string plotTitle);
	/* TeleconWxPlot interface functions*/
	// Fetches all data out of the controller thread and adds it to make it visible to UI thread
    virtual void prepDataForDraw() = 0;
    // Adds a layer representing the plot to the given chart
	virtual void addToChart(XYChart* chart) = 0;
    virtual double getLeftmostX() const = 0;
    virtual double getRightmostX() const = 0;
    virtual string getLatestValueString() const = 0;

    /* Functions inherited from TeleconPlot */
	// size() remains abstract;
	virtual size_t depth() const override;
	virtual int getColor() const override;
	virtual const string getPlotTitle() const override;
};