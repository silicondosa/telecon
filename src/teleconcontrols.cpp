
#include <memory>
#include <cmath>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <limits>
#include "teleconcontrols.h"
#include "teleconwxcontrolswindow.h"

using namespace std;

TeleconControls::TeleconControls(string windowName)
{
    this->windowName = windowName;
}

shared_ptr<TeleconButton> TeleconControls::addButton(string title, func_t callback)
{
    shared_ptr<TeleconButton> button = make_shared<TeleconButton>(title, callback);
    buttons.push_back(button);
    return button;
}

shared_ptr<TeleconToggle> TeleconControls::addToggle(string title)
{
    shared_ptr<TeleconToggle> toggle = make_shared<TeleconToggle>(title);
    toggles.push_back(toggle);
    return toggle;
}

shared_ptr<TeleconSlider> TeleconControls::addSlider(string title, int min, int max, int startPos, int precision)
{
    shared_ptr<TeleconSlider> slider = make_shared<TeleconSlider>(title, min, max, startPos, precision);
    sliders.push_back(slider);
    return slider;
}

shared_ptr<TeleconInput> TeleconControls::addInput(string title, int startVal)
{
    shared_ptr<TeleconInput> input = make_shared<TeleconInput>(title, startVal);
    inputs.push_back(input);
    return input;
}

TeleconButton::TeleconButton(string title, func_t callback)
{
    this->title = title;
    this->functionPtr = callback;
}
TeleconToggle::TeleconToggle(string title)
{
    this->title = title;
}
TeleconSlider::TeleconSlider(string title, int min, int max, int startPos, int precision)
{
    int numSteps = (max - min) * pow(10, precision);
    this->min = 0;
    this->max = numSteps;
    this->offset = min;
    this->title = title;
    this->current_state = (startPos - offset) * pow(10, precision);
    this->precision = precision;
}

double TeleconSlider::getCurrentValue()
{
    return ((double)offset) + ((double)current_state) / pow(10, precision);
}

string TeleconSlider::current_value_to_string(){
    stringstream ss;
    ss << std::fixed << std::setprecision(precision) << getCurrentValue();
    return ss.str();
}

TeleconInput::TeleconInput(string title, int startVal)
{
    this->title = title;
    this->val = startVal;
}

string TeleconButton::getTitle()
{
    return title;
}

string TeleconToggle::getTitle()
{
    return title;
}

string TeleconInput::getTitle()
{
    return title;
}

double TeleconInput::getVal()
{
    return val;
}

void TeleconInput::setVal(double newVal)
{
    this->val = newVal;
}

void TeleconInput::setId(int id){
    this->id = id;
}
void TeleconInput::setFrame(wxFrame* frame){
    this->frame = frame;
}
void TeleconInput::updateInputBox(double value){
    wxThreadEvent* event = new wxThreadEvent(wxEVT_INPUT_UPDATE, id);
    stringstream ss;
    ss << std::fixed << std::setprecision(std::numeric_limits<double>::max_digits10) << value;
    event->SetString(ss.str());
    ((TeleconWxControlsWindow*) frame)->GetEventHandler()->QueueEvent(event);
}

TeleconInput::~TeleconInput(){ 

}