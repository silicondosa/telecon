#pragma once

#include <string>
#include <mutex>
#include <list>

#include "chartdir.h"
#include "databuffer.h"
#include "teleconplot.h"

using namespace std;

/**
 * Plot GUI that inherits from TeleconPlot.
 */
class TeleconWxPlot : virtual public TeleconPlot {
protected:
    const size_t m_depth;
	int m_color; // Represented as an RGB hexadecimal code (one byte per channel)
	string m_plotTitle;
public:

	/**
	 * Constructor.
	 * 
	 * \param plotTitle title of the plot as string
	 * \param color color as an int (enum)
	 * \param depth depth of the plot databuffer as type size_t
	 */
	TeleconWxPlot(string plotTitle, int color, size_t depth);
	/* TeleconWxPlot interface functions*/

	/**
	 * Fetches all data out of the controller threadand adds it to make it visible to UI thread.
	 * 
	 */
    virtual void prepDataForDraw() = 0;

    /**
     * Adds a layer representing the plot to the given chart.
     * 
     * \param chart of type XYChart* 
     */
	virtual void addToChart(XYChart* chart) = 0;

	/**
	 * Getter function for left most x.
	 * 
	 * \return left most x value as double
	 */
    virtual double getLeftmostX() const = 0;

	/**
	 * Getter function for right most x.
	 * 
	 * \return right most x value as a double
	 */
    virtual double getRightmostX() const = 0;

	/**
	 * Getter function for latest value.
	 * 
	 * \return latest value as a string
	 */
    virtual string getLatestValueString() const = 0;

    virtual bool isIncludedInLegend() const = 0;

    /* Functions inherited from TeleconPlot */

	/**
	 * size() remains abstract.
	 * 
	 * \return depth of type size_t
	 */
	virtual size_t depth() const override;

	/**
	 * Getter function for plot color.
	 * 
	 * \return color as int (enum)
	 */
	virtual int getColor() const override;

	/**
	 * Getter function for plot title.
	 * 
	 * \return title as string
	 */
	virtual const string getPlotTitle() const override;
};