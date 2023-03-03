
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "base.h"

#include <cmath>
#include <random>
#include <thread>

#include "TeleconRealTimeLineChart.h"
#include "wxchartviewer.h"
#include "start.h"


double generateRandomDouble(double min, double max) {
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



void ChartFrame::userAddChart(){
    // TeleconRealTimeLineChart* realTimePanel = createRealTimePanel(wxDefaultPosition, wxDefaultSize);
    // realTimePanel->AddChart("My Title", "ylabel");
    // realTimePanel->AddPlot("Expected Tension", CreateDataPoints, 0xff0000, "Expected Tension");

    // TeleconRealTimeLineChart* realTimePanel2 = createRealTimePanel(wxDefaultPosition, wxDefaultSize);
    // realTimePanel2->AddChart("My Title", "ylabel");
    // realTimePanel2->AddPlot("Expected Tension", CreateDataPoints, 0x00b40a, "Expected Tension");
    // realTimePanel2->AddPlot("Expected Tension", CreateDataPoints, 0xff00ff, "Expected Tension");

    // TeleconRealTimeLineChart* realTimePanel3 = createRealTimePanel(wxDefaultPosition, wxDefaultSize);
    // realTimePanel3->AddChart("My Title", "ylabel");
    // realTimePanel3->AddPlot("Expected Tension", CreateDataPoints, 0x0000ff, "Expected Tension");

    // addChart(realTimePanel);
    // addChart(realTimePanel2);
    // addChart(realTimePanel3);

}   

void Telecon::teleconMain(){

    TeleconWindow* window = addWindow("MyWindow");

    TeleconRealTimeLineChart* realTimeChart = window->addChart("Chart1", "lbs");
    realTimeChart->addLinePlot(CreateDataPoints, 0xff0000, "Expected Tension", 1, LT_SOLID);
    realTimeChart->addLinePlot(CreateDataPoints, 0x00ff00, "Force", 5, LT_SOLID);

    TeleconRealTimeLineChart* realTimeChart2 = window->addChart("Second Chart", "inches");
    realTimeChart2->addLinePlot(CreateDataPoints, 0x00ff00, "Extension", 1, LT_DASHED);


    TeleconWindow* window2 = addWindow("Second Window");

    TeleconRealTimeLineChart* realTimeChart3 = window2->addChart("Third Chart", "mph");
    realTimeChart3->addScatterPlot(CreateDataPoints, 0x0000ff, "Speed", Chart::SquareShape, 5);


    window->drawWindow();
    window2->drawWindow();

}



int main(int argc, char *argv[])
{   

    
    teleconStart();




    teleconJoin(); //Must be called prior to exiting main

    return 0;
}