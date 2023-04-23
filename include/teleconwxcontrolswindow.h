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
    void inputHandler(wxCommandEvent& event);

    wxBoxSizer *m_controlsBoxSizer;
    wxFlexGridSizer* m_sliderGridSizer;
    //wxFlexGridSizer* m_toggleGridSizer;
    wxFlexGridSizer* m_inputGridSizer;

    unordered_map<int, wxTextCtrl*> m_sliderValues; // Maps index of slider to its value for updating ///(from tcchart, latestvalues)
    unordered_map<int, wxTextCtrl*> m_inputValues; // Maps index of input to its value

    // ~TeleconWxControlsWindow();
};