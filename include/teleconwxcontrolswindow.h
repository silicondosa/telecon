#pragma once

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <string>
#include <memory>
#include "teleconcontrols.h"

class TeleconWxControlsWindow : public wxFrame
{
public:
    TeleconWxControlsWindow(shared_ptr<TeleconControls> controls);
    DECLARE_EVENT_TABLE()
private:
    shared_ptr<TeleconControls> controls;
    void buttonPressHandler(wxCommandEvent &event);
    void toggleHandler(wxCommandEvent &event);
    void sliderHandler(wxCommandEvent &event);
    wxBoxSizer *m_controlsBoxSizer;
    // ~TeleconWxControlsWindow();
};