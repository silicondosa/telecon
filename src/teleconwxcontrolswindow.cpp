
#include "teleconwxcontrolswindow.h"

#include <wx/tglbtn.h>
#include <vector>
#include <sstream>


enum
{
  id_button = (wxID_HIGHEST + 1), // declares an id which will be used to call our button
  id_toggle = wxID_HIGHEST + 200,
  id_slider = wxID_HIGHEST + 400,
  id_input = wxID_HIGHEST + 600
};


wxDEFINE_EVENT(wxEVT_INPUT_UPDATE, wxThreadEvent);


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
    m_controlsBoxSizer->Add(myButton, 0, wxLEFT | wxRIGHT, FromDIP(20));
    m_controlsBoxSizer->AddSpacer(FromDIP(10));
    Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(TeleconWxControlsWindow::buttonPressHandler));
  }

  for (int i = 0; i < controls->toggles.size(); i++)
  {
    auto t = controls->toggles[i];
    wxToggleButton* myButton = new wxToggleButton(this, id_toggle + i, wxString(t->getTitle()), wxDefaultPosition, wxDefaultSize, 0);

   /* wxStaticText* buttonName = new wxStaticText(this, wxID_STATIC, wxString(t->getTitle()), wxDefaultPosition, wxDefaultSize, 0);

    m_toggleGridSizer = new wxFlexGridSizer(0, 10, 0, 10);
    m_controlsBoxSizer->Add(m_toggleGridSizer);

    m_toggleGridSizer->Add(buttonName);*/

    m_controlsBoxSizer->Add(myButton, 0, wxLEFT | wxRIGHT, FromDIP(20));
    m_controlsBoxSizer->AddSpacer(FromDIP(10));
    Connect(wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler(TeleconWxControlsWindow::toggleHandler));
  }

  for (int i = 0; i < controls->sliders.size(); i++)
  {
    auto s = controls->sliders[i];
    wxSlider* mySlider = new wxSlider(this, id_slider + i, s->current_state, s->min, s->max, wxDefaultPosition, wxSize(400, -1), wxSL_AUTOTICKS);
    mySlider->SetTickFreq(1);
    wxTextCtrl* sliderVal = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, FromDIP(wxSize(60, -1)), wxTE_READONLY | wxSTATIC_BORDER);
    sliderVal->Enable(false);
    wxStaticText* sliderName = new wxStaticText(this, wxID_STATIC, wxString(s->title), wxDefaultPosition, wxDefaultSize, 0);

    m_sliderGridSizer = new wxFlexGridSizer(0, 10, 0, 10);
    m_controlsBoxSizer->Add(m_sliderGridSizer, 0, wxLEFT | wxRIGHT, FromDIP(20));

    m_sliderGridSizer->Add(sliderName);
    m_sliderGridSizer->Add(mySlider);
    m_sliderGridSizer->Add(sliderVal);
    m_sliderValues.insert(pair(id_slider+i, sliderVal));
    m_controlsBoxSizer->AddSpacer(FromDIP(10));
    m_sliderValues[id_slider + i]->SetValue(s->current_value_to_string());

    Connect(wxEVT_COMMAND_SLIDER_UPDATED, wxCommandEventHandler(TeleconWxControlsWindow::sliderHandler));
  }

  for (int i = 0; i < controls->inputs.size(); i++)
  {
      auto in = controls->inputs[i];
      in->setId(id_input + i);
      in->setFrame(this);
      // wxTextCtrl* myInput = new wxTextCtrl(this, id_button + i, wxString(std::to_string(in->getVal())), wxDefaultPosition, wxDefaultSize, 0);
      wxTextCtrl* myInput = new wxTextCtrl(this, id_input + i, wxString(std::to_string(in->getVal())), wxDefaultPosition, wxSize(FromDIP(200), FromDIP(30)),  
            wxTE_PROCESS_ENTER , wxDefaultValidator);
      // shared_ptr<wxTextCtrl> myInput = make_shared<wxTextCtrl>(this, id_input + i, wxString(std::to_string(in->getVal())), wxDefaultPosition, wxDefaultSize,  
      //       wxTE_PROCESS_ENTER , wxDefaultValidator);
      myInput->Enable(true);
      wxStaticText* inputName = new wxStaticText(this, wxID_STATIC, wxString(in->getTitle()), wxDefaultPosition, wxDefaultSize, 0);

      m_inputGridSizer = new wxFlexGridSizer(0, 10, 0, 10);
      m_controlsBoxSizer->Add(m_inputGridSizer, 0, wxLEFT | wxRIGHT, FromDIP(20));
      m_controlsBoxSizer->AddSpacer(FromDIP(10));

      m_inputGridSizer->Add(inputName);
      m_inputGridSizer->Add(myInput);

      m_inputValues.insert(pair(id_input + i, myInput));
    
      // inputControls.push_back(myInput);

      Connect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(TeleconWxControlsWindow::inputHandler));
  }

  // Connect(wxEVT_INPUT_UPDATE, wxEventHandler(TeleconWxControlsWindow::inputUpdateHandler));
  // Bind(wxEVT_INPUT_UPDATE,&TeleconWxControlsWindow::inputUpdateHandler,this);
  Connect(wxEVT_INPUT_UPDATE, wxThreadEventHandler(TeleconWxControlsWindow::inputUpdateHandler));
  // Connect(wxEVT_THREAD, wxThreadEventHandler(TeleconWxControlsWindow::inputUpdateHandler));
  // cout << "In controlwindow id: " << wxEVT_INPUT_UPDATE << endl;


  // m_controlsBoxSizer.
  SetSizerAndFit(m_controlsBoxSizer);
  
}

void TeleconWxControlsWindow::buttonPressHandler(wxCommandEvent &event)
{
  int buttonIndex = event.GetId() - id_button;
  controls->buttons[buttonIndex]->functionPtr();

  // cout << "Hello Button" << event.GetId() << endl;
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
  int val = event.GetInt();
  controls->sliders[sliderIndex]->current_state = val;
  string currentvalue = controls->sliders[sliderIndex]->current_value_to_string();
  // m_sliderValues[event.GetId()]->SetValue(std::to_string(val));
  // string toDisplay = 
  m_sliderValues[event.GetId()]->SetValue(currentvalue);
}

void TeleconWxControlsWindow::inputHandler(wxCommandEvent& event)
{
    int inputIndex = event.GetId() - id_input;
    string value_str = event.GetString().ToStdString();
    double value_dbl;
    stringstream ss;
    ss << value_str;
    ss >> value_dbl;
  
    controls->inputs[inputIndex]->setVal(value_dbl);
}

void TeleconWxControlsWindow::inputUpdateHandler(wxThreadEvent& event){
  // wxQueueEvent()
  int inputIndex = event.GetId();
  string value_str = event.GetString().ToStdString();
  double value_dbl;
  stringstream ss;
  ss << value_str;
  ss >> value_dbl;
  controls->inputs[inputIndex - id_input]->setVal(value_dbl);
  m_inputValues.find(inputIndex)->second->ChangeValue(event.GetString());
  // m_inputValues.find(inputIndex)->second->focu
  



}