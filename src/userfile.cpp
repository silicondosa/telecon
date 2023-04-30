
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "teleconcontrols.h"
#include "telecon.h"
#include "teleconimplchartdir.h"

#include <cmath>
#include <random>
#include <thread>

#include "wxchartviewer.h"


// Helper functions to generate random data points

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

shared_ptr<TeleconInput> input2;

void printHello(){
    cout << "Callback Hello World" << endl;
    // input2->updateInputBox(4000);
    
}



/**
 * Here is an example of how to use Telecon.
 */
int main(int argc, char* argv[])
{
    // Constants
    const int dataRateMillis = 100;


    // START SETTING UP COMPONENTS TO BE USED FOR TELEMETRY AND CONTROLS


    // Initialization code, create a telecon object
    Telecon* telecon = new TeleconImplChartDir();



    // CONTROLS SETUP BEGIN
    // A CONTROL window can have BUTTONS, TOGGLES, SLIDERS, and INPUTS

    // Create a controls window
    shared_ptr<TeleconControls> controls = telecon->addControls("MyControls");     // For windows, add it directly to the created Telecon object

    // Different control elements
    // For control elements, use add[element] on your created TeleconControls object
    controls->addButton("Button 1", printHello);     // You can add a button that is linked to a function (in this case we have printHello()
    shared_ptr<TeleconToggle> run = controls->addToggle("Run");     // You can also add a toggle button
    shared_ptr<TeleconSlider> slider2 = controls->addSlider("Frequency", 0, 3, 1, 2);     // Here is a slider with min value 0 and max value 3, starting at 1 with precision 2
    shared_ptr<TeleconSlider> slider3 = controls->addSlider("Amplitude", 0, 3, 2, 2);     // Here is another slider, you can add multiple elements of the same type
    shared_ptr<TeleconInput> input1 = controls->addInput("Input 1", 300);     // Here is an input field with a default value of 300
    input2 = controls->addInput("Input 2", 10);     // Another input field with default value 10
    shared_ptr<TeleconInput> input3 = controls->addInput("amplitude", 1);     // A third input field

    // Create a normal window to be controlled by the previously created controls window
    shared_ptr<TeleconWindow> sineDemoWindow = telecon->addWindow("sineDemoWindow");     // Since this is a window, add directly to Telecon object

    // Create a plot that displays updates from the controls window
    // First create a chart, since all plots need to be displayed in a chart
    shared_ptr<TeleconRealtimeChart> sinechart = sineDemoWindow->addRealtimeChart("Chart1", 60.0, dataRateMillis, "time (s)", "lbs");     //add charts to window objects
    // Then we can add a plot to an existing chart
    shared_ptr<TeleconLinePlot> sinePlot = sinechart->addLinePlot("Sine Function", LineStyle(COLOR_BLACK));
    double sinvalue = 0;

    // CONTROLS SETUP END



    // TELEMETRY SETUP BEGIN
    // Hierarchy of elements: A WINDOW has CHARTS which contain PLOTS
    // A WINDOW may have different types of CHARTS, but it is best practice that CHARTS only contain the same type PLOTS

    // Create a window [1]
    shared_ptr<TeleconWindow> window = telecon->addWindow("MyWindow");

    // Create a Realtime Chart for Line Plots
    shared_ptr<TeleconRealtimeChart> chart1 = window->addRealtimeChart("Chart1", 60.0, dataRateMillis, "time (s)", "lbs");
    // Add plots to the created chart
    shared_ptr<TeleconLinePlot> plot1 = chart1->addLinePlot("Expected Tension", LineStyle(COLOR_BLACK));
    shared_ptr<TeleconLinePlot> plot2 = chart1->addLinePlot("Force", LineStyle(COLOR_GREEN, 5, LT_SOLID));

    // Create another Realtime Chart for Line Plots
    shared_ptr<TeleconRealtimeChart> chart2 = window->addRealtimeChart("Second Chart", 60.0, dataRateMillis, "time (s)", "inches");
    // Add plots to this chart
    shared_ptr<TeleconLinePlot> plot3 = chart2->addLinePlot("Extension (expected)", LineStyle(COLOR_DEFAULT), SymbolStyle(SYMBOL_CIRCLE, COLOR_DEFAULT, true, 5));
    shared_ptr<TeleconLinePlot> plot4 = chart2->addLinePlot("Extension (actual)", LineStyle(COLOR_GREEN, 1, LT_DASHED));
    SymbolStyle circleStyle;  // create a symbol object for plot point display custimization
    shared_ptr<TeleconLinePlot> plot5 = chart2->addLinePlot("Extension (expected) dup1", LineStyle(COLOR_RED), circleStyle);
    shared_ptr<TeleconLinePlot> plot6 = chart2->addLinePlot("Extension (expected) dup2", LineStyle(COLOR_GREEN), circleStyle);
    shared_ptr<TeleconLinePlot> plot7 = chart2->addLinePlot("Extension (actual) dup1", LineStyle(COLOR_BLUE, 1, LT_DASHED));
    shared_ptr<TeleconLinePlot> plot8 = chart2->addLinePlot("Extension (actual) dup2", LineStyle(COLOR_DEFAULT, 1, LT_DASHED));

    // Create another window [2]
    shared_ptr<TeleconWindow> window2 = telecon->addWindow("Second Window");

    // Similarly create a chart and add plots
    shared_ptr<TeleconRealtimeChart> chart3 = window2->addRealtimeChart("Diverging Chart", 6.0, dataRateMillis, "time (s)", "ft", CSM_DIVERGING);
    shared_ptr<TeleconLinePlot> plot9 = chart3->addLinePlot("Plot 1");
    shared_ptr<TeleconLinePlot> plot10 = chart3->addLinePlot("Plot 2");
    shared_ptr<TeleconLinePlot> plot11 = chart3->addLinePlot("Plot 3");
    shared_ptr<TeleconLinePlot> plot12 = chart3->addLinePlot("Plot 4");

    // Another Realtime Chart, but this time with Scatter Plots
    shared_ptr<TeleconRealtimeChart> chart4 = window2->addRealtimeChart("Scatter Chart", 6.0, dataRateMillis, "time (s)", "mph", CSM_DIVERGING);
    shared_ptr<TeleconScatterPlot> plot13 = chart4->addScatterPlot("Speed", SymbolStyle(SYMBOL_CROSS, COLOR_DEFAULT, false));
    shared_ptr<TeleconScatterPlot> plot14 = chart4->addScatterPlot("New one", SymbolStyle(SYMBOL_CIRCLE, COLOR_DEFAULT, false));
    shared_ptr<TeleconScatterPlot> plot15 = chart4->addScatterPlot("Velocity", SymbolStyle(SYMBOL_DIAMOND, COLOR_BLUE, true, 3));

    // Create another window [3]
    shared_ptr<TeleconWindow> window3 = telecon->addWindow("Third Window");

    // Create a Realtime Chart, but this time for Raster Plots.
    shared_ptr<TeleconRealtimeChart> chart5 = window3->addRealtimeChart("Raster Chart", 60.0, dataRateMillis, "time (s)", "Neuron", CSM_BLACK);
    
    // Set up Raster Plots. 
    // They are also added to the chart like the other plots, but due to the nature of the plot the setup may be different
    // How you store the shared pointers is up to you
    vector<shared_ptr<TeleconRasterPlot>> rasterPlots;
    for (int i = 0; i < 100; ++i) {
        rasterPlots.push_back(chart5->addRasterPlot("", i, SymbolStyle(SYMBOL_SQUARE, COLOR_RED, false, 3)));
    }
    for (int i = 100; i < 1000; ++i) {
        rasterPlots.push_back(chart5->addRasterPlot("", i));
    }

    // Now create a Data Chart to add Temporal Phse Portrait Plots
    shared_ptr<TeleconDataChart> chart6 = window3->addDataChart("Temporal Phase Portrait", 6.0, dataRateMillis, "amount spent ($)", "grade (%)", CSM_DIVERGING);
    vector<shared_ptr<TeleconPhasePortraitPlot>> phasePortraits;
    phasePortraits.push_back(chart6->addPhasePortraitPlot("Student A"));
    phasePortraits.push_back(chart6->addPhasePortraitPlot("Student B"));
    phasePortraits.push_back(chart6->addPhasePortraitPlot("Student C"));
    phasePortraits.push_back(chart6->addPhasePortraitPlot("Student D"));


    // Storing previously created plots for easier access, but this portion is not necessary
    vector<shared_ptr<TeleconLinePlot>> absoluteTimePlots({ plot1, plot2, plot3, plot4, plot5, plot6, plot7, plot8, plot9, plot10, plot11, plot12});
    vector<shared_ptr<TeleconScatterPlot>> relativeTimePlots({ plot13, plot14, plot15 });

    // TELEMETRY SETUP END



    // Make sure to start Telecon!
    telecon->teleconStart();



    // CONTROLLER CODE BEGIN
    // This portion is to generate data to push into the plots
    wxDateTime start = wxDateTime::UNow();
    double startTimestamp = Chart::chartTime2(start.GetTicks()) + start.GetMillisecond() / 1000.0;

    // Loop until Telecon has stopped
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
        
        // sinePlot->pushData(nowTimestampRelative, slider3->getCurrentValue() * (nowTimestampRelative * slider2->getCurrentValue()));
        if(run->state){
            sinePlot->pushData(nowTimestampRelative,  input3->getVal() *  slider3->getCurrentValue() * sin(sinvalue));
            sinvalue += slider2->getCurrentValue() * (3.1415 / 10);
        }
        if (telecon->hasStopped()) {
            break;
        }

        this_thread::sleep_for(chrono::milliseconds(dataRateMillis));

    }

    // CONTROLLER CODE END


    // Make sure to stop Telecon as well
    telecon->teleconStop();


    delete telecon;

    return 0;
}