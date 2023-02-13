

#include "chartdir.h"

#include "TeleconBarChart.h"

using namespace std;

XYChart* TeleconBarChart::makeChart(){

    double data[] = {56, 145, 80, 94, 60};
    const char* labels[] = {"Mon", "Tue", "Wed","Thurs", "Fri"};
    XYChart *my_chart = new XYChart(250, 250);
    my_chart->setPlotArea(30, 20, 200, 200);
    my_chart->addBarLayer(DoubleArray(data, 5));
    my_chart->xAxis()->setLabels(StringArray(labels, (int) 5));

    return my_chart;
}

