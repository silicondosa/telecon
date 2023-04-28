
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

void printHello(){
    cout << "Callback Hello World" << endl;
}
// void startTelecon(){
    // mytelecon->teleconStart();
// }

// Telecon* mytelecon;

int main(int argc, char* argv[])
{
    const int dataRateMillis = 100;
    // Initialization code
    Telecon* telecon = new Telecon();

    shared_ptr<TeleconControls> controls = telecon->addControls("MyControls");
    controls->addButton("Button 1", printHello);
    shared_ptr<TeleconToggle> toggle1 = controls->addToggle("Toggle 1");
    shared_ptr<TeleconToggle> toggle2 = controls->addToggle("Toggle 2");
    // shared_ptr<TeleconSlider> slider2 = controls->addSlider("Slider 2", 0, 3, 2, 2);
    shared_ptr<TeleconInput> input1 = controls->addInput("Input 1", 300);
    shared_ptr<TeleconInput> input2 = controls->addInput("Input 2", 10);
    shared_ptr<TeleconInput> input3 = controls->addInput("Input 3", 200);

    shared_ptr<TeleconWindow> sineDemoWindow = telecon->addWindow("sineDemoWindow");

    shared_ptr<TeleconRealtimeChart> sinechart = sineDemoWindow->addRealtimeChart("Chart1", 60.0, dataRateMillis, "time (s)", "lbs");
    shared_ptr<TeleconLinePlot> sinePlot = sinechart->addLinePlot("Sin Function", LineStyle(COLOR_BLACK));
    double sinvalue = 0;

    // telecon->teleconStart();
    // wxDateTime start = wxDateTime::UNow();
    // double startTimestamp = Chart::chartTime2(start.GetTicks()) + start.GetMillisecond() / 1000.0;
    // while (true) {
    //     wxDateTime now = wxDateTime::UNow(); // Needs to use UNow instead of Now for millisecond precision
    //     double nowTimestampAbsolute = Chart::chartTime2(now.GetTicks()) + now.GetMillisecond() / 1000.0;
    //     double nowTimestampRelative = nowTimestampAbsolute - startTimestamp;

    //     sinePlot->pushData(nowTimestampRelative, sin(nowTimestampRelative * slider2->getCurrentValue()));

    //     if (telecon->hasStopped()) {
    //         break;
    //     }
    //     this_thread::sleep_for(chrono::milliseconds(dataRateMillis));
    // }
    // telecon->teleconStart();
    // while(true){
    //     this_thread::sleep_for(chrono::milliseconds(200));
    //     // cout << "Toggle 1 state: " << toggle1->state << "    Toggle 2 state: " << toggle2->state << endl;
    //     cout << "Input 1 state: " << input1->getVal() << endl;
    //     cout << "Input 2 state: " << input2->getVal() << endl;
    //     // cout << "Input 3 state: " << input1->getVal() << endl;
    // }

    shared_ptr<TeleconWindow> window = telecon->addWindow("MyWindow");

    shared_ptr<TeleconRealtimeChart> chart1 = window->addRealtimeChart("Chart1", 60.0, dataRateMillis, "time (s)", "lbs");
    shared_ptr<TeleconLinePlot> plot1 = chart1->addLinePlot("Expected Tension", LineStyle(COLOR_BLACK));
    shared_ptr<TeleconLinePlot> plot2 = chart1->addLinePlot("Force", LineStyle(COLOR_GREEN, 5, LT_SOLID));

    SymbolStyle noSymbol(SYMBOL_NO_SYMBOL);
    shared_ptr<TeleconRealtimeChart> chart2 = window->addRealtimeChart("Second Chart", 60.0, dataRateMillis, "time (s)", "inches");
    shared_ptr<TeleconLinePlot> plot3 = chart2->addLinePlot("Extension (expected)", LineStyle(COLOR_DEFAULT), SymbolStyle(SYMBOL_CIRCLE, COLOR_DEFAULT, true, 5));
    shared_ptr<TeleconLinePlot> plot4 = chart2->addLinePlot("Extension (actual)", LineStyle(COLOR_GREEN, 1, LT_DASHED));
    //test for legends
    SymbolStyle circleStyle;
    shared_ptr<TeleconLinePlot> plot5 = chart2->addLinePlot("Extension (expected) dup1", LineStyle(COLOR_RED), circleStyle);
    shared_ptr<TeleconLinePlot> plot6 = chart2->addLinePlot("Extension (expected) dup2", LineStyle(COLOR_GREEN), circleStyle);
    shared_ptr<TeleconLinePlot> plot7 = chart2->addLinePlot("Extension (actual) dup1", LineStyle(COLOR_BLUE, 1, LT_DASHED));
    shared_ptr<TeleconLinePlot> plot8 = chart2->addLinePlot("Extension (actual) dup2", LineStyle(COLOR_DEFAULT, 1, LT_DASHED));

    shared_ptr<TeleconWindow> window2 = telecon->addWindow("Second Window");

    shared_ptr<TeleconRealtimeChart> chart3 = window2->addRealtimeChart("Diverging Chart", 6.0, dataRateMillis, "time (s)", "ft", CSM_DIVERGING);
    shared_ptr<TeleconLinePlot> plot9 = chart3->addLinePlot("Plot 1");
    shared_ptr<TeleconLinePlot> plot10 = chart3->addLinePlot("Plot 2");
    shared_ptr<TeleconLinePlot> plot11 = chart3->addLinePlot("Plot 3");
    shared_ptr<TeleconLinePlot> plot12 = chart3->addLinePlot("Plot 4");

    shared_ptr<TeleconRealtimeChart> chart4 = window2->addRealtimeChart("Scatter Chart", 6.0, dataRateMillis, "time (s)", "mph", CSM_DIVERGING);
    shared_ptr<TeleconScatterPlot> plot13 = chart4->addScatterPlot("Speed", SymbolStyle(SYMBOL_CROSS, COLOR_DEFAULT, false));
    shared_ptr<TeleconScatterPlot> plot14 = chart4->addScatterPlot("New one", SymbolStyle(SYMBOL_CIRCLE, COLOR_DEFAULT, false));
    shared_ptr<TeleconScatterPlot> plot15 = chart4->addScatterPlot("Velocity", SymbolStyle(SYMBOL_DIAMOND, COLOR_BLUE, true, 3));

    shared_ptr<TeleconWindow> window3 = telecon->addWindow("Third Window");

    shared_ptr<TeleconRealtimeChart> chart5 = window3->addRealtimeChart("Raster Chart", 60.0, dataRateMillis, "time (s)", "Neuron", CSM_BLACK);
    
    vector<shared_ptr<TeleconRasterPlot>> rasterPlots;
    for (int i = 0; i < 100; ++i) {
        rasterPlots.push_back(chart5->addRasterPlot("", i, SymbolStyle(SYMBOL_SQUARE, COLOR_RED, false, 3)));
    }
    for (int i = 100; i < 1000; ++i) {
        rasterPlots.push_back(chart5->addRasterPlot("", i));
    }

    shared_ptr<TeleconDataChart> chart6 = window3->addDataChart("Temporal Phase Portrait", 6.0, dataRateMillis, "amount spent ($)", "grade (%)", CSM_DIVERGING);
    vector<shared_ptr<TeleconPhasePortraitPlot>> phasePortraits;
    phasePortraits.push_back(chart6->addPhasePortraitPlot("Student A"));
    phasePortraits.push_back(chart6->addPhasePortraitPlot("Student B"));
    phasePortraits.push_back(chart6->addPhasePortraitPlot("Student C"));
    phasePortraits.push_back(chart6->addPhasePortraitPlot("Student D"));

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

    vector<shared_ptr<TeleconLinePlot>> absoluteTimePlots({ plot1, plot2, plot3, plot4, plot5, plot6, plot7, plot8, plot9, plot10, plot11, plot12});
    vector<shared_ptr<TeleconScatterPlot>> relativeTimePlots({ plot13, plot14, plot15 });

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
        for (auto rasterPlot : rasterPlots) {
            // Using a sine wave with some added noise to give the raster plots a recognizable pattern and not just look like random dots
            rasterPlot->pushData(nowTimestampAbsolute, (40.0 * sin(nowTimestampAbsolute) + CreateDataPoints()) > 100.0);
        }
        for (auto phasePortrait : phasePortraits) {
            phasePortrait->pushData(nowTimestampRelative, CreateDataPoints(), CreateDataPoints());
        }
        
        // sinePlot->pushData(nowTimestampRelative, sin(nowTimestampRelative * slider2->getCurrentValue()));
        // sinePlot->pushData(nowTimestampRelative, sin(sinvalue));
        // sinvalue += slider2->getCurrentValue() * (3.1415 / 10);
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