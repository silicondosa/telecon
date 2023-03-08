
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
        for (auto& teleconWindow : *telecon) {
            for (auto& teleconChart : *teleconWindow) {
                for (auto& teleconPlot : *teleconChart) {
                    wxDateTime now = wxDateTime::UNow(); // Needs to UNow instead of Now for millisecond precision

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

    TeleconRealTimeChart* realTimeChart = window->addChart("Chart1", "lbs", "time");
    realTimeChart->addLinePlot("Expected Tension", COLOR_BLACK, LT_SOLID, 1, SYMBOL_NO_SYMBOL, true, 5);
    realTimeChart->addLinePlot("Force", COLOR_GREEN, LT_SOLID, 5, SYMBOL_NO_SYMBOL, true, 5);

    TeleconRealTimeChart* realTimeChart2 = window->addChart("Second Chart", "inches", "time");
    realTimeChart2->addLinePlot("Extension (expected)", COLOR_DEFAULT, LT_SOLID, 1, SYMBOL_CIRCLE, true, 5);
    realTimeChart2->addLinePlot("Extension (actual)", COLOR_GREEN, LT_DASHED, 1, SYMBOL_NO_SYMBOL, true, 5);

    TeleconWindow* window2 = addWindow("Second Window");

    TeleconRealTimeChart* realTimeChart3 = window2->addChart("Diverging Chart", "ft", "time (s)", 100, 1000, CSM_DIVERGING);
    realTimeChart3->addLinePlot("Plot 1");
    realTimeChart3->addLinePlot("Plot 2");
    realTimeChart3->addLinePlot("Plot 3");
    realTimeChart3->addLinePlot("Plot 4");
    /*realTimeChart3->addLinePlot("Plot 5");
    realTimeChart3->addLinePlot("Plot 6");
    realTimeChart3->addLinePlot("Plot 7");
    realTimeChart3->addLinePlot("Plot 8");
    realTimeChart3->addLinePlot("Plot 9");
    realTimeChart3->addLinePlot("Plot 10");
    realTimeChart3->addLinePlot("Plot 11");*/

    TeleconRealTimeChart* realTimeChart4 = window2->addChart("Scatter Chart", "mph", "time", 100, 1000, CSM_DIVERGING);
    realTimeChart4->addScatterPlot("Speed", COLOR_DEFAULT, SYMBOL_CROSS, false);
    realTimeChart4->addScatterPlot("New one", COLOR_DEFAULT, SYMBOL_CIRCLE, false);
    realTimeChart4->addScatterPlot("Velocity", COLOR_BLUE, SYMBOL_DIAMOND, true, 3);

    window->drawWindow();
    window2->drawWindow();
}