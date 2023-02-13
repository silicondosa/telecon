
#ifndef __TELECON_CHART_PANEL

#define __TELECON_CHART_PANEL

#include <wx/wxprec.h>


#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "TeleconChartPanel.h"
#include "wxchartviewer.h"

TeleconChartPanel::TeleconChartPanel(wxWindow *parent,
                                     wxWindowID winid ,
                                     const wxPoint &pos,
                                     const wxSize &size,
                                     long style ,
                                     const wxString &name ) : wxPanel(parent, winid, pos, size, style, name )
{
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    double data[] = {56, 145, 80, 94, 60};
    const char* labels[] = {"Mon", "Tue", "Wed","Thurs", "Fri"};
    XYChart *my_chart = new XYChart(250, 250);
    my_chart->setPlotArea(30, 20, 200, 200);
    my_chart->addBarLayer(DoubleArray(data, 5));
    my_chart->xAxis()->setLabels(StringArray(labels, (int) 5));

    my_base_chart = my_chart;

    wxChartViewer *viewer = new wxChartViewer(this);
    viewer->setChart(my_base_chart);
    // sizer->SetMinSize(300, 300);

    sizer->Add(viewer, 1, wxALIGN_RIGHT, FromDIP(3));

    SetSizerAndFit(sizer);


}

BEGIN_EVENT_TABLE(TeleconChartPanel, wxPanel)
END_EVENT_TABLE()


#endif