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
 * Plot GUI implementation, inherits from TeleconPlot.
 * 
 * This is an implementation class and should not be interacted with directly by the user.
 */
class TeleconWxPlot : virtual public TeleconPlot {
protected:
    /** The depth (maximum size) of the plot. */
    const size_t m_depth;
    /** The title of the plot, as displayed in the legend. */
	string m_plotTitle;
    /** The ::SymbolStyle representing how the symbol representing points (if any) should be displayed. */
    shared_ptr<SymbolStyle> m_symbolStyle;

    /** Helper function to extract the ChartDirector representation of a symbol from the Telecon representation of a symbol. */
    static int getChartDirSymbolFromPlotSymbol(PlotSymbol symbol);
public:
    /**
     * Helper function to enable code reuse for similar plots which involve both a symbol and a line.
     * 
     * \param chart the chart to which to draw the plot.
     * \param plotTitle the title of the plot, as displayed in the legend.
     * \param includeInLegend if true, the given plot will be included in the legend.
     * \param xArray an array of the x-values of the data points.
     * \param yArray an array of the y-values of the data points.
     * \param lineStyle describes how the line connecting the data points (if any) should be displayed.
     * \param symbolStyle describes how the symbol representing the data points (if any) should be displayed.
     */
    static void addLinePlotToChart(XYChart* chart, string plotTitle, bool includeInLegend, DoubleArray xArray, DoubleArray yArray, shared_ptr<const LineStyle> lineStyle, shared_ptr<const SymbolStyle> symbolStyle);
    /**
     * Helper function to enable code reuse for similar plots which involve only a symbol.
     *
     * \param chart the chart to which to draw the plot.
     * \param plotTitle the title of the plot, as displayed in the legend.
     * \param includeInLegend if true, the given plot will be included in the legend.
     * \param xArray an array of the x-values of the data points.
     * \param yArray an array of the y-values of the data points.
     * \param symbolStyle describes how the symbol representing the data points (if any) should be displayed.
     */
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
	 * Fetches all data out of the controller thread and adds it to make it visible to UI thread.
	 * Should be called before drawing the plot with TeleconWxPlot::addToChart.
	 */
    virtual void prepDataForDraw() = 0;

    /**
     * Draws this plot to the given chart.
     * 
     * \param chart The chart to which to draw this plot.
     */
	virtual void addToChart(XYChart* chart) = 0;

	/**
	 * Getter function for left most x.
	 * 
	 * \return Left most x-value, which may be based either on the timestamp or on the x-data, depending on the type of the plot.
	 */
    virtual double getLeftmostX() const = 0;

    /**
     * Getter function for right most x.
     *
     * \return Right most x-value, which may be based either on the timestamp or on the x-data, depending on the type of the plot.
     */
    virtual double getRightmostX() const = 0;

	/**
	 * \return A string representation of the latest value added to the plot, including only the actual data, not the timestamp.
	 */
    virtual string getLatestValueString() const = 0;

	/**
	 * \return True if this plot should be included in the legend, or false otherwise.
	 */
    virtual bool isIncludedInLegend() const = 0;

	/**
	 * \return The depth (maximum size) of the plot.
     * \note TeleconPlot::size remains abstract.
     */
	virtual size_t depth() const override;

	/**
	 * \return The title of the plot, as displayed in the legend.
	 */
	virtual const string getPlotTitle() const override;

    /**
     * \return The ::SymbolStyle representing how the symbol representing points (if any) should be displayed.
     */
    virtual shared_ptr<const SymbolStyle> getSymbolStyle() const;
};