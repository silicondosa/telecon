#pragma once

#include <string>
#include <memory>
#include <vector>
#include "teleconcontrols.h"

wxDECLARE_EVENT(wxEVT_INPUT_UPDATE, wxThreadEvent);

/**
 * UI handler for the telecon controls window.
 */
class TeleconWxControlsWindow : public wxFrame
{
public:
    /**
     * Constructor.
     * 
     * \param controls TeleconControls object pointer
     */
    TeleconWxControlsWindow(std::shared_ptr<TeleconControls> controls);
    DECLARE_EVENT_TABLE()
private:
    shared_ptr<TeleconControls> controls;
    void buttonPressHandler(wxCommandEvent &event);
    void toggleHandler(wxCommandEvent &event);
    void sliderHandler(wxCommandEvent &event);
    void inputHandler(wxCommandEvent& event);

    void inputUpdateHandler(wxThreadEvent& event);

    wxBoxSizer *m_controlsBoxSizer;
    wxFlexGridSizer* m_sliderGridSizer;
    //wxFlexGridSizer* m_toggleGridSizer;
    wxFlexGridSizer* m_inputGridSizer;

    std::unordered_map<int, wxTextCtrl*> m_sliderValues; // Maps index of slider to its value for updating ///(from tcchart, latestvalues)
    std::unordered_map<int, wxTextCtrl*> m_inputValues; // Maps index of input to its value

    // ~TeleconWxControlsWindow();
};