
#include "teleconwxcontrolswindow.h"

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/tglbtn.h>
#include <vector>

enum
{
  id_button = (wxID_HIGHEST + 1), // declares an id which will be used to call our button
  id_toggle = wxID_HIGHEST + 200,
  id_slider = wxID_HIGHEST + 400
};


BEGIN_EVENT_TABLE(TeleconWxControlsWindow, wxFrame)

END_EVENT_TABLE()

TeleconWxControlsWindow::TeleconWxControlsWindow(shared_ptr<TeleconControls> controls)
    : wxFrame((wxFrame *)NULL, -1, controls->windowName, wxDefaultPosition, wxDefaultSize)
{
  this->controls = controls;

  m_controlsBoxSizer = new wxBoxSizer(wxVERTICAL);

  // wxButton* myButton0 = new wxButton(this, BUTTON_Hello, _T("Hello World"), wxDefaultPosition, wxDefaultSize, 0); // with the text "hello World"

  // wxSlider* mySlider= new wxSlider(this,BUTTON_Slider,5, 0, 10, wxDefaultPosition, wxDefaultSize, 0);

  // m_controlsBoxSizer->Add(myButton0);
  // m_controlsBoxSizer->Add(mySlider);

  // for (TeleconButton b : controls->buttons)
  for (int i = 0; i < controls->buttons.size(); i++)
  {
    auto b = controls->buttons[i];
    wxButton *myButton = new wxButton(this, id_button + i, b->getTitle(), wxDefaultPosition, wxDefaultSize, 0);
    m_controlsBoxSizer->Add(myButton);
    Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(TeleconWxControlsWindow::buttonPressHandler));
  }

  for (int i = 0; i < controls->toggles.size(); i++)
  {
    auto t = controls->toggles[i];
    wxToggleButton *myButton = new wxToggleButton(this, id_toggle + i, t->getTitle(), wxDefaultPosition, wxDefaultSize, 0);
    m_controlsBoxSizer->Add(myButton);
    Connect(wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler(TeleconWxControlsWindow::toggleHandler));
  }

  for (int i = 0; i < controls->sliders.size(); i++)
  {
    auto s = controls->sliders[i];
    wxSlider *mySlider = new wxSlider(this,id_slider,s->current_state, s->min, s->max, wxDefaultPosition, wxDefaultSize, 0);
    m_controlsBoxSizer->Add(mySlider);
    Connect(wxEVT_COMMAND_SLIDER_UPDATED, wxCommandEventHandler(TeleconWxControlsWindow::sliderHandler));
  }

  //CAN HAVE MAP MAPPING BUTTON IDS TO THE BUTTON OBJEcTS

  // m_controlsBoxSizer.
  SetSizerAndFit(m_controlsBoxSizer);
  
}

void TeleconWxControlsWindow::buttonPressHandler(wxCommandEvent &event)
{

  cout << "Hello Button" << event.GetId() << endl;
}

void TeleconWxControlsWindow::toggleHandler(wxCommandEvent &event)
{
  int toggleIndex = event.GetId() - id_toggle;
  controls->toggles[toggleIndex]->state = event.IsChecked();
  // cout << "Hello Toggle: " << event.IsChecked()  << "  " << event.GetId() << endl;
}

void TeleconWxControlsWindow::sliderHandler(wxCommandEvent &event)
{
  int sliderIndex = event.GetId() - id_slider;
  controls->sliders[sliderIndex]->current_state = event.GetInt();
  // cout << "Hello Slider: " << event.GetInt() << "   " << event.GetId() << endl;
  
}