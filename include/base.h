#ifndef __BASE_H

#define __BASE_H



#include <wx/wxprec.h>
#include <wx/app.h>
#include <wx/frame.h>
#include <wx/button.h>
#include <wxchartviewer_defs.h>

#include "chartdir.h"
#include "TeleconRealTimeLineChart.h"

#include <vector>
#include <string>

// void teleconMain();


typedef class ChartFrame : public wxFrame {
    public:
        ChartFrame(const wxString &title);
        void populateChart();
        TeleconRealTimeLineChart* createRealTimeChart();
        // XYChart* my_chart;
        std::vector<BaseChart*> charts;
        BaseChart* my_chart;

        void drawWindow();


        virtual void userAddChart(); //For user to impement 
        void addChart(TeleconRealTimeLineChart*);
        TeleconRealTimeLineChart* addChart(std::string title, string xlabel, std::string ylabel, ColorSequenceMode colorSequenceMode = CSM_BLACK);

        DECLARE_EVENT_TABLE()
    private:
        std::vector<TeleconRealTimeLineChart*> list_charts;
       

} TeleconWindow;

typedef class MainApp : public wxApp
{
public:
    virtual bool OnInit();

    void addWindow(wxFrame* frame);
    ChartFrame* addWindow(std::string name);

    virtual void teleconMain();

private:

    std::vector<wxFrame*> frameList;

} Telecon;

class MainFrame : public wxFrame
{
public:
    MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size);
    wxButton *HelloWorld;
    wxButton *TextButton;
    wxTextCtrl *MainEditBox;
    void OnExit(wxCommandEvent &event);
    void OnText(wxCommandEvent &event);

    DECLARE_EVENT_TABLE()
};

enum
{
    BUTTON_Hello = wxID_HIGHEST + 1,
    BUTTON_Text,
    TEXT_main

};

#endif