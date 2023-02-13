#ifndef __BASE_H

#define __BASE_H

#include <vector>

#include <wx/wxprec.h>
#include <wx/app.h>
#include <wx/frame.h>
#include <wx/button.h>
#include <wxchartviewer_defs.h>

#include "chartdir.h"


class MainApp : public wxApp
{
public:
    virtual bool OnInit();

};

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

class ChartFrame : public wxFrame {
    public:
        ChartFrame(const wxString &title, const wxPoint &pos, const wxSize &size);
        void populateChart();
        // XYChart* my_chart;
        std::vector<BaseChart*> charts;
        BaseChart* my_chart;

        DECLARE_EVENT_TABLE()
       

};

#endif