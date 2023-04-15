
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
    const int dataRateMillis = 100;
    // Initialization code
    Telecon* telecon = new Telecon();

    shared_ptr<TeleconControls> controls = telecon->addControls("MyControls");
    shared_ptr<TeleconToggle> toggle1 = controls->addToggle("Toggle 1");
    shared_ptr<TeleconToggle> toggle2 = controls->addToggle("Toggle 2");
    shared_ptr<TeleconSlider> slider1 = controls->addSlider("Slider 1", 0, 100,50);

    shared_ptr<TeleconWindow> window = telecon->addWindow("MyWindow");

    shared_ptr<TeleconRealtimeChart> chart1 = window->addRealtimeChart("Chart1", 60.0, dataRateMillis, "time (s)", "lbs");
    shared_ptr<TeleconLinePlot> plot1 = chart1->addLinePlot("Expected Tension", COLOR_BLACK, LT_SOLID, 1, SYMBOL_NO_SYMBOL, true, 5);
    shared_ptr<TeleconLinePlot> plot2 = chart1->addLinePlot("Force", COLOR_GREEN, LT_SOLID, 5, SYMBOL_NO_SYMBOL, true, 5);

    shared_ptr<TeleconRealtimeChart> chart2 = window->addRealtimeChart("Second Chart", 60.0, dataRateMillis, "time (s)", "inches");
    shared_ptr<TeleconLinePlot> plot3 = chart2->addLinePlot("Extension (expected)", COLOR_DEFAULT, LT_SOLID, 1, SYMBOL_CIRCLE, true, 5);
    shared_ptr<TeleconLinePlot> plot4 = chart2->addLinePlot("Extension (actual)", COLOR_GREEN, LT_DASHED, 1, SYMBOL_NO_SYMBOL, true, 5);
    //test for legends
    shared_ptr<TeleconLinePlot> plot5 = chart2->addLinePlot("Extension (expected) dup1", COLOR_RED, LT_SOLID, 1, SYMBOL_CIRCLE, true, 5);
    shared_ptr<TeleconLinePlot> plot6 = chart2->addLinePlot("Extension (expected) dup2", COLOR_GREEN, LT_SOLID, 1, SYMBOL_CIRCLE, true, 5);
    shared_ptr<TeleconLinePlot> plot7 = chart2->addLinePlot("Extension (actual) dup1", COLOR_BLUE, LT_DASHED, 1, SYMBOL_NO_SYMBOL, true, 5);
    shared_ptr<TeleconLinePlot> plot8 = chart2->addLinePlot("Extension (actual) dup2", COLOR_DEFAULT, LT_DASHED, 1, SYMBOL_NO_SYMBOL, true, 5);

    shared_ptr<TeleconWindow> window2 = telecon->addWindow("Second Window");

    shared_ptr<TeleconRealtimeChart> chart3 = window2->addRealtimeChart("Diverging Chart", 6.0, dataRateMillis, "time (s)", "ft", CSM_DIVERGING);
    shared_ptr<TeleconLinePlot> plot9 = chart3->addLinePlot("Plot 1");
    shared_ptr<TeleconLinePlot> plot10 = chart3->addLinePlot("Plot 2");
    shared_ptr<TeleconLinePlot> plot11 = chart3->addLinePlot("Plot 3");
    shared_ptr<TeleconLinePlot> plot12 = chart3->addLinePlot("Plot 4");
 

    shared_ptr<TeleconRealtimeChart> chart4 = window2->addRealtimeChart("Scatter Chart", 6.0, dataRateMillis, "time (s)", "mph", CSM_DIVERGING);
    shared_ptr<TeleconScatterPlot> plot13 = chart4->addScatterPlot("Speed", COLOR_DEFAULT, SYMBOL_CROSS, false);
    shared_ptr<TeleconScatterPlot> plot14 = chart4->addScatterPlot("New one", COLOR_DEFAULT, SYMBOL_CIRCLE, false);
    shared_ptr<TeleconScatterPlot> plot15 = chart4->addScatterPlot("Velocity", COLOR_BLUE, SYMBOL_DIAMOND, true, 3);
    

    telecon->teleconStart();
    telecon->teleconStart();

    // while(true){
    //     this_thread::sleep_for(chrono::milliseconds(200));
    //     // cout << "Toggle 1 state: " << toggle1->state << "    Toggle 2 state: " << toggle2->state << endl;
    //     cout << "Slider 1 state: " << slider1->current_state << endl;
    // }

    telecon->addWindow("Third window");
    window2->addRealtimeChart();
    chart4->addLinePlot("line");
    chart4->addScatterPlot("scatter");

    vector<shared_ptr<TeleconLineScatterPlot>> absoluteTimePlots({ plot1, plot2, plot3, plot4, plot5, plot6, plot7, plot8 });
    vector<shared_ptr<TeleconLineScatterPlot>> relativeTimePlots({ plot9, plot10, plot11, plot12, plot13, plot14, plot15 });

    // Controller code starts here
    wxDateTime start = wxDateTime::UNow();
    double startTimestamp = Chart::chartTime2(start.GetTicks()) + start.GetMillisecond() / 1000.0;

    while (true) {
        wxDateTime now = wxDateTime::UNow(); // Needs to use UNow instead of Now for millisecond precision

        // Convert from wxDateTime to seconds since Unix epoch, then to ChartDirector double timestamp.
        // Since that loses millisecond precision, add it back in with GetMillisecond()
        double nowTimestampAbsolute = Chart::chartTime2(now.GetTicks()) + now.GetMillisecond() / 1000.0;
        double nowTimestampRelative = nowTimestampAbsolute - startTimestamp;
        for (auto absoluteTimePlot : absoluteTimePlots) {
            absoluteTimePlot->pushData(nowTimestampAbsolute, CreateDataPoints());
        }
        for (auto relativeTimePlot : relativeTimePlots) {
            relativeTimePlot->pushData(nowTimestampRelative, CreateDataPoints());
        }
        if (telecon->hasStopped()) {
            break;
        }
        this_thread::sleep_for(chrono::milliseconds(dataRateMillis));
    }

    // Controller code ends here

    telecon->teleconStop();

    delete telecon;

    return 0;
}