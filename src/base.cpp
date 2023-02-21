#include <wx/wxprec.h>
#include <wx/textctrl.h>
#include <iostream>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include "base.h"
#include "wxchartviewer.h"

#include <cmath>
#include <random>

#include "TeleconChart.h"
#include "TeleconBarChart.h"
#include "TeleconChartPanel.h"
#include "TeleconRealTimeLineChart.h"

IMPLEMENT_APP(MainApp);

using namespace std;

double CreateDataPoints();

// void MainApp::addFrame(wxFrame *frame) { frameList.push_back(frame); }

bool MainApp::OnInit()
{
    // MainFrame *MainWin = new MainFrame("Hello World!", wxDefaultPosition, wxSize(500, 400));
    // MainWin->Show(true);
    // SetTopWindow(MainWin);

    // ChartFrame *ChartWin = new ChartFrame("MyChart", wxDefaultPosition, wxDefaultSize);
    // ChartWin->Show(true);


    // ChartFrame* chartframe = new ChartFrame("MyChart", wxDefaultPosition, wxDefaultSize);
    // addFrame(chartframe);
    // // TeleconRealTimeLineChart* chart = window->addChart();
    
    // TeleconRealTimeLineChart* realTimePanel = chartframe->createRealTimePanel(wxDefaultPosition, wxDefaultSize);
    // realTimePanel->AddChart("My Title", "ylabel");
    // realTimePanel->AddPlot("Expected Tension", CreateDataPoints, 0xff0000, "Expected Tension");
    // chartframe->addChart(realTimePanel);
    // chartframe->drawChart();

    teleconMain();

    
    

    // ChartFrame *ChartWin2 = new ChartFrame("MyChart1", wxDefaultPosition, wxDefaultSize);
    // ChartWin2->Show(true);

    for(wxFrame* frame : frameList){
        frame->Show(true);
    }

    // MainFrame *NewWin = new MainFrame("Hello World!", wxDefaultPosition, wxSize(500, 400));
    // NewWin->Show(true);

    return true;
}


void MainApp::addWindow(wxFrame *chartWindow){
    frameList.push_back(chartWindow);
}

TeleconWindow* MainApp::addWindow(string name){
    ChartFrame* window = new ChartFrame(name);
    frameList.push_back(window);
    return window;
}

BEGIN_EVENT_TABLE(MainFrame, wxFrame)
EVT_BUTTON(BUTTON_Hello, MainFrame::OnExit)
EVT_BUTTON(BUTTON_Text, MainFrame::OnText)
END_EVENT_TABLE()

MainFrame::MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame((wxFrame *)NULL, -1, title, pos, size)
{

    //  wxBoxSizer *vbox = new wxBoxSizer (wxVERTICAL);
    wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);

    HelloWorld = new wxButton(this, BUTTON_Hello, _T("Hello World"), wxDefaultPosition, wxDefaultSize, 0);
    TextButton = new wxButton(this, BUTTON_Text, _T("Surprise"), wxDefaultPosition, wxDefaultSize, 0);

    hbox->Add(HelloWorld, 0, wxALL, 10);
    hbox->Add(TextButton, 0, wxALL, 10);

    // vbox->Add(hbox, 0, wxALIGN_CENTER);

    hbox->SetMinSize(400, 300);
    SetSizerAndFit(hbox);

    // CreateStatusBar(2);

    // MainEditBox = new wxTextCtrl(this,TEXT_main );

    // normally we would initialize objects such as buttons and textboxes here
}

void MainFrame::OnExit(wxCommandEvent &event)
{
    Close(TRUE); // Tells the OS to quit running this process
}

void MainFrame::OnText(wxCommandEvent &event)
{
    // Close(TRUE); // Tells the OS to quit running this process

    wxTextEntryDialog *dialog = new wxTextEntryDialog(this, "mydialog");
    if (dialog->ShowModal() == wxID_OK)
    {
        wxString value = dialog->GetValue();
        cout << value << endl;
    }
    // dialog->Show(true);
}

BEGIN_EVENT_TABLE(ChartFrame, wxFrame)
END_EVENT_TABLE()

ChartFrame::ChartFrame(const wxString &title)
    : wxFrame((wxFrame *)NULL, -1, title, wxDefaultPosition, wxDefaultSize)
{
    // populateChart();

    wxBoxSizer *itemBoxSizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(itemBoxSizer);

    // wxChartViewer *chartViewer = new wxChartViewer(this);
    // itemBoxSizer->Add(chartViewer, 1, wxGROW, FromDIP(3));
    // SetSizerAndFit(itemBoxSizer);
    // chartViewer->setChart(my_chart);

    // wxChartViewer *chartViewer1 = new wxChartViewer(this);

    // itemBoxSizer->Add(chartViewer1, 1, wxGROW, FromDIP(3));
    // chartViewer1->setChart(my_chart);

    ///////////////////////

    // TeleconChart *chart = new TeleconBarChart();
    // charts.push_back(chart->makeChart());

    // TeleconChart *chart_2 = new TeleconBarChart();
    // charts.push_back(chart_2->makeChart());

    // for(BaseChart* singleChart : charts){
    //     wxChartViewer *chartViewer = new wxChartViewer(this);
    //     chartViewer->setChart(singleChart);
    //     itemBoxSizer->Add(chartViewer, 1, wxGROW, FromDIP(3));
    // }

    /////////////////////////////

    // TeleconChartPanel *panel = new TeleconChartPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    // itemBoxSizer->Add(panel, 1, wxGROW);
    // TeleconChartPanel *panel2 = new TeleconChartPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    // itemBoxSizer->Add(panel2, 1, wxGROW);

    // TeleconRealTimeLineChart* realTimePanel = new TeleconRealTimeLineChart(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    // realTimePanel->AddChart("My Title", "ylabel");
    // realTimePanel->AddPlot("Expected Tension", CreateDataPoints, 0xff0000, "Expected Tension");
    // itemBoxSizer->Add(realTimePanel, 1, wxGROW);
    // TeleconRealTimeLineChart* realTimePanel2 = new TeleconRealTimeLineChart(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    // realTimePanel2->AddChart("My Title", "ylabel");
    // realTimePanel2->AddPlot("Expected Tension", CreateDataPoints, 0xff0000, "Expected Tension");
    // itemBoxSizer->Add(realTimePanel2, 1, wxGROW);
    userAddChart();

    for (auto panel_element : list_charts)
    {
        itemBoxSizer->Add(panel_element, 1, wxGROW);
    }

    // TeleconPanel->Show();
    // SetTopWindow(TeleconPanel);
    // itemBoxSizer->SetMinSize(300, 300);
    // cout << panel->GetSize().GetX() << endl;
    // panel->SetSize(300, 300);
    SetSizerAndFit(itemBoxSizer);
}

void ChartFrame::drawWindow(){
    wxBoxSizer *itemBoxSizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(itemBoxSizer);
    for (auto panel_element : list_charts)
    {
        itemBoxSizer->Add(panel_element, 1, wxGROW);
    }
    SetSizerAndFit(itemBoxSizer);
}
TeleconRealTimeLineChart* ChartFrame::createRealTimeChart()
{
    TeleconRealTimeLineChart *realTimePanel = new TeleconRealTimeLineChart(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    return realTimePanel;
}

void ChartFrame::addChart(TeleconRealTimeLineChart *chartPanel)
{
    list_charts.push_back(chartPanel);
}

TeleconRealTimeLineChart* ChartFrame::addChart(string title, string ylabel){
    TeleconRealTimeLineChart *realTimePanel = new TeleconRealTimeLineChart(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    list_charts.push_back(realTimePanel);
    realTimePanel->initChart(title, ylabel);
    return realTimePanel;
}

void ChartFrame::populateChart()
{
    double data[] = {56, 145, 80, 94, 60};
    const char *labels[] = {"Mon", "Tue", "Wed", "Thurs", "Fri"};

    XYChart *my_xy_chart = new XYChart(250, 250);
    my_xy_chart->setPlotArea(30, 20, 200, 200);
    my_xy_chart->addBarLayer(DoubleArray(data, 5));
    my_xy_chart->xAxis()->setLabels(StringArray(labels, (int)5));

    my_chart = my_xy_chart;

    // TeleconChart *chart = new TeleconBarChart();
    // Add data, etc.
    // XYChart* newchart = chart->makeChart()
}

// double generateRandomDouble(double min, double max) {
// 	std::random_device rd;  // Will be used to obtain a seed for the random number engine
// 	std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
// 	std::uniform_real_distribution<> dis(min, max);
// 	return dis(gen);
// }

// double
// CreateDataPoints()
// {
// 	double randomDouble = generateRandomDouble(0.0, 20.0);
// 	double p = randomDouble;
// 	double dataA = 20 + cos(p * 129241) * 10 + 1 / (cos(p) * cos(p) + 0.01);
// 	return dataA;
// }
