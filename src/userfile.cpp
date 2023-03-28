
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "telecon.h"

#include <cmath>
#include <random>
#include <thread>

#include "teleconrealtimechart.h"
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
    future<Telecon*> teleconFuture = Telecon::teleconStart();

    teleconFuture.wait();

    Telecon* telecon = teleconFuture.get();

    // Controller code starts here

    while (true) {
        for (int i = 0; i < telecon->getNumWindows(); i++) {
            TeleconWindow* window = telecon->getWindow(i);
            for (int j = 0; j < window->getNumCharts(); j++) {
                TeleconChart* chart = window->getChart(j);
                for (int k = 0; k < chart->getNumPlots(); k++) {
                    TeleconPlot* teleconPlot = chart->getPlot(k);
                    wxDateTime now = wxDateTime::UNow(); // Needs to use UNow instead of Now for millisecond precision

                    // Convert from wxDateTime to seconds since Unix epoch, then to ChartDirector double timestamp.
                    // Since that loses millisecond precision, add it back in with GetMillisecond()
                    double millis = now.GetMillisecond();
                    double nowTimeStamp = Chart::chartTime2(now.GetTicks()) + now.GetMillisecond() / 1000.0;
                    teleconPlot->pushData(nowTimeStamp, CreateDataPoints());
                }
            }
        }
        this_thread::sleep_for(chrono::milliseconds(100));
    }

    // Controller code ends here

    Telecon::teleconJoin(); //Must be called prior to exiting main

    return 0;
}

void Telecon::teleconMain()
{
    TeleconWindow* window = addWindow("MyWindow");

    TeleconChart* chart1 = window->addChart("Chart1", "lbs", "time");
    chart1->addLinePlot("Expected Tension", 1000, COLOR_BLACK, LT_SOLID, 1, SYMBOL_NO_SYMBOL, true, 5);
    chart1->addLinePlot("Force", 1000, COLOR_GREEN, LT_SOLID, 5, SYMBOL_NO_SYMBOL, true, 5);

    TeleconChart* chart2 = window->addChart("Second Chart", "inches", "time");
    chart2->addLinePlot("Extension (expected)", 500, COLOR_DEFAULT, LT_SOLID, 1, SYMBOL_CIRCLE, true, 5);
    chart2->addLinePlot("Extension (actual)", 500, COLOR_GREEN, LT_DASHED, 1, SYMBOL_NO_SYMBOL, true, 5);

    TeleconWindow* window2 = addWindow("Second Window");

    TeleconChart* chart3 = window2->addChart("Diverging Chart", "ft", "time (s)", CSM_DIVERGING, 100.0 / 60.0);
    chart3->addLinePlot("Plot 1", 100);
    chart3->addLinePlot("Plot 2", 100);
    chart3->addLinePlot("Plot 3", 100);
    chart3->addLinePlot("Plot 4", 100);
    /*realTimeChart3->addLinePlot("Plot 5");
    realTimeChart3->addLinePlot("Plot 6");
    realTimeChart3->addLinePlot("Plot 7");
    realTimeChart3->addLinePlot("Plot 8");
    realTimeChart3->addLinePlot("Plot 9");
    realTimeChart3->addLinePlot("Plot 10");
    realTimeChart3->addLinePlot("Plot 11");*/

    TeleconChart* chart4 = window2->addChart("Scatter Chart", "mph", "time", CSM_DIVERGING, 100.0 / 60.0);
    chart4->addScatterPlot("Speed", 100, COLOR_DEFAULT, SYMBOL_CROSS, false);
    chart4->addScatterPlot("New one", 100, COLOR_DEFAULT, SYMBOL_CIRCLE, false);
    chart4->addScatterPlot("Velocity", 100, COLOR_BLUE, SYMBOL_DIAMOND, true, 3);
}