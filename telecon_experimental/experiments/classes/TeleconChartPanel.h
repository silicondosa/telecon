
#include <wx/wxprec.h>
#include <wx/panel.h>

#include "chartdir.h"

class TeleconChartPanel : public wxPanel
{
    public:
        TeleconChartPanel(wxWindow *parent,
                wxWindowID winid = wxID_ANY,
                const wxPoint& pos = wxDefaultPosition,
                const wxSize& size = wxDefaultSize,
                long style = wxTAB_TRAVERSAL | wxNO_BORDER,
                const wxString& name = wxASCII_STR(wxPanelNameStr));

        // ~TeleconChartPanel(){ }

        BaseChart* my_base_chart;

        DECLARE_EVENT_TABLE()

        
};