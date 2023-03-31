
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "telecon.h"

#include <cmath>
#include <random>
#include <thread>

#include "wxchartviewer.h"

double generateRandomDouble(double min, double max)
{
	std::random_device rd;  // Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
	std::uniform_real_distribution<> dis(min, max);
	return dis(gen);
}

double
CreateDataPoints()
{
	double randomDouble = generateRandomDouble(0.0, 20.0);
	double p = randomDouble;
	double dataA = 20 + cos(p * 129241) * 10 + 1 / (cos(p) * cos(p) + 0.01);
	return dataA;
}

int main(int argc, char* argv[])
{
    // Initialization code
    Telecon* telecon = new Telecon();
    TeleconWindow* window = telecon->addWindow("MyWindow");

    TeleconRealtimeChart* chart1 = window->addRealtimeChart("Chart1", "lbs", "time", CSM_BLACK, 100.0 / 60.0);
    TeleconLinePlot* plot1 = chart1->addLinePlot("Expected Tension", 1000, COLOR_BLACK, LT_SOLID, 1, SYMBOL_NO_SYMBOL, true, 5);
    TeleconLinePlot* plot2 = chart1->addLinePlot("Force", 1000, COLOR_GREEN, LT_SOLID, 5, SYMBOL_NO_SYMBOL, true, 5);

    TeleconRealtimeChart* chart2 = window->addRealtimeChart("Second Chart", "inches", "time", CSM_BLACK, 50.0 / 60.0);
    TeleconLinePlot* plot3 = chart2->addLinePlot("Extension (expected)", 500, COLOR_DEFAULT, LT_SOLID, 1, SYMBOL_CIRCLE, true, 5);
    TeleconLinePlot* plot4 = chart2->addLinePlot("Extension (actual)", 500, COLOR_GREEN, LT_DASHED, 1, SYMBOL_NO_SYMBOL, true, 5);
    //test for legends
    TeleconLinePlot* plot5 = chart2->addLinePlot("Extension (expected) dup1", 500, COLOR_RED, LT_SOLID, 1, SYMBOL_CIRCLE, true, 5);
    TeleconLinePlot* plot6 = chart2->addLinePlot("Extension (expected) dup2", 500, COLOR_GREEN, LT_SOLID, 1, SYMBOL_CIRCLE, true, 5);
    TeleconLinePlot* plot7 = chart2->addLinePlot("Extension (actual) dup1", 500, COLOR_BLUE, LT_DASHED, 1, SYMBOL_NO_SYMBOL, true, 5);
    TeleconLinePlot* plot8 = chart2->addLinePlot("Extension (actual) dup2", 500, COLOR_DEFAULT, LT_DASHED, 1, SYMBOL_NO_SYMBOL, true, 5);

    TeleconWindow* window2 = telecon->addWindow("Second Window");

    TeleconRealtimeChart* chart3 = window2->addRealtimeChart("Diverging Chart", "ft", "time (s)", CSM_DIVERGING, 10.0 / 60.0);
    TeleconLinePlot* plot9 = chart3->addLinePlot("Plot 1", 100);
    TeleconLinePlot* plot10 = chart3->addLinePlot("Plot 2", 100);
    TeleconLinePlot* plot11 = chart3->addLinePlot("Plot 3", 100);
    TeleconLinePlot* plot12 = chart3->addLinePlot("Plot 4", 100);
    /*realTimeChart3->addLinePlot("Plot 5");
    realTimeChart3->addLinePlot("Plot 6");
    realTimeChart3->addLinePlot("Plot 7");
    realTimeChart3->addLinePlot("Plot 8");
    realTimeChart3->addLinePlot("Plot 9");
    realTimeChart3->addLinePlot("Plot 10");
    realTimeChart3->addLinePlot("Plot 11");*/

    TeleconRealtimeChart* chart4 = window2->addRealtimeChart("Scatter Chart", "mph", "time", CSM_DIVERGING, 10.0 / 60.0);
    TeleconScatterPlot* plot13 = chart4->addScatterPlot("Speed", 100, COLOR_DEFAULT, SYMBOL_CROSS, false);
    TeleconScatterPlot* plot14 = chart4->addScatterPlot("New one", 100, COLOR_DEFAULT, SYMBOL_CIRCLE, false);
    TeleconScatterPlot* plot15 = chart4->addScatterPlot("Velocity", 100, COLOR_BLUE, SYMBOL_DIAMOND, true, 3);

    telecon->teleconStart();

    vector<TeleconLineScatterPlot*> plots({ plot1, plot2, plot3, plot4, plot5, plot6, plot7, plot8, plot9, plot10, plot11, plot12, plot13, plot14, plot15});

    // Controller code starts here

    while (true) {
        wxDateTime now = wxDateTime::UNow(); // Needs to use UNow instead of Now for millisecond precision

        // Convert from wxDateTime to seconds since Unix epoch, then to ChartDirector double timestamp.
        // Since that loses millisecond precision, add it back in with GetMillisecond()
        double millis = now.GetMillisecond();
        double nowTimeStamp = Chart::chartTime2(now.GetTicks()) + now.GetMillisecond() / 1000.0;
        for (auto i = plots.begin(); i != plots.end(); ++i) {
            (*i)->pushData(nowTimeStamp, CreateDataPoints());
        }
        this_thread::sleep_for(chrono::milliseconds(100));
    }

    // Controller code ends here

    telecon->teleconJoin(); //Must be called prior to exiting main

    return 0;
}