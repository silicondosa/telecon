
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "telecon.h"

#include <cmath>
#include <random>
#include <thread>

#include "TeleconRealTimeLineChart.h"
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

    Telecon* telecon = Telecon::teleconStart();

    Telecon::teleconJoin(); //Must be called prior to exiting main

    return 0;
}

void Telecon::teleconMain()
{
    TeleconWindow* window = addWindow("MyWindow");

    TeleconRealTimeLineChart* realTimeChart = window->addChart("Chart1", "time", "lbs");
    realTimeChart->addLinePlot(CreateDataPoints, "Expected Tension", 0xff0000, LT_SOLID, 1);
    realTimeChart->addLinePlot(CreateDataPoints, "Force", 0x00ff00, LT_SOLID, 5);

    TeleconRealTimeLineChart* realTimeChart2 = window->addChart("Second Chart", "time", "inches");
    realTimeChart2->addLinePlot(CreateDataPoints, "Extension (expected)", -1L, Chart::CircleShape, 5, LT_SOLID, 1);
    realTimeChart2->addLinePlot(CreateDataPoints, "Extension (actual)", 0x00ff00, LT_DASHED, 1);

    TeleconWindow* window2 = addWindow("Second Window");

    TeleconRealTimeLineChart* realTimeChart3 = window2->addChart("Diverging Chart", "time", "ft", CSM_DIVERGING);
    realTimeChart3->addLinePlot(CreateDataPoints, "Plot 1");
    realTimeChart3->addLinePlot(CreateDataPoints, "Plot 2");
    realTimeChart3->addLinePlot(CreateDataPoints, "Plot 3");

    TeleconRealTimeLineChart* realTimeChart4 = window2->addChart("Scatter Chart", "time", "mph");
    realTimeChart4->addScatterPlot(CreateDataPoints, "Speed");
    realTimeChart4->addScatterPlot(CreateDataPoints, "Velocity", 0x00ff00, Chart::DiamondShape, 3);

    window->drawWindow();
    window2->drawWindow();
}