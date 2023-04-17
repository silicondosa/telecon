#pragma once

#include <string>
#include <mutex>
#include <list>

#include "chartdir.h"
#include "databuffer.h"
#include "teleconplot.h"
#include "symbolstyle.h"
#include "linestyle.h"

using namespace std;

/**
 * Plot GUI that inherits from TeleconPlot.
 */
class TeleconWxPlot : virtual public TeleconPlot {
protected:
    const size_t m_depth;
	string m_plotTitle;
    shared_ptr<SymbolStyle> m_symbolStyle;

    static int getChartDirSymbolFromPlotSymbol(PlotSymbol symbol);
public:
    static void addLinePlotToChart(XYChart* chart, string plotTitle, bool includeInLegend, DoubleArray xArray, DoubleArray yArray, shared_ptr<const LineStyle> lineStyle, shared_ptr<const SymbolStyle> symbolStyle);
    static void addScatterPlotToChart(XYChart* chart, string plotTitle, bool includeInLegend, DoubleArray xArray, DoubleArray yArray, shared_ptr<const SymbolStyle> symbolStyle);

	/**
	 * Constructor.
	 * 
	 * \param plotTitle title of the plot as string
	 * \param color color as an int (enum)
	 * \param depth depth of the plot databuffer as type size_t
	 */
	TeleconWxPlot(string plotTitle, size_t depth, const SymbolStyle &symbolStyle);
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

	/**
	 * Helper function to know if the plot is included in the legend.
	 * 
	 * \return included in legend status as bool
	 */
    virtual bool isIncludedInLegend() const = 0;

    /* Functions inherited from TeleconPlot */

    // Inherited via TeleconRasterPlot
	/**
	 * size() remains abstract.
	 * 
	 * \return depth of type size_t
	 */
	virtual size_t depth() const override;

	/**
	 * Getter function for plot title.
	 * 
	 * \return title as string
	 */
	virtual const string getPlotTitle() const override;

    virtual shared_ptr<const SymbolStyle> getSymbolStyle() const;
};