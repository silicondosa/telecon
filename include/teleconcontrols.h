#pragma once

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <string>
#include <vector>
#include <memory>


using namespace std;

typedef void (*func_t)();

class TeleconButton
{
public:
    TeleconButton(string title, func_t callback);
    func_t functionPtr;
    string getTitle();
    volatile bool state = false;

private:
    string title;
};

class TeleconSlider
{
public:
    TeleconSlider(string title, int min, int max, int current_state, int precision);
    std::string title;
    int min;
    int max;
    volatile int current_state;

    //TODO
    int precision;
    int offset;

    double getCurrentValue();
    string current_value_to_string();
};

class TeleconToggle
{
public:
    TeleconToggle(string title);
    std::string title;
    string getTitle();
    volatile bool state = false;
};

class TeleconInput
{
public:
    TeleconInput(string title, int startVal);
    std::string title;
    string getTitle();
    volatile double val;
    double getVal();
    void setVal(double newVal);
    void setId(int id);
    void setFrame(wxFrame* frame);
    void updateInputBox(double value);
    ~TeleconInput();
private:
    wxFrame* frame;
    int id;
    
};

class TeleconControls
{
public:
    TeleconControls(string windowName);
    shared_ptr<TeleconButton> addButton(string title, func_t callback);
    shared_ptr<TeleconToggle> addToggle(string title);
    shared_ptr<TeleconSlider> addSlider(string title, int min, int max, int startPos, int precision);
    shared_ptr<TeleconInput> addInput(string title, int startVal);

    string windowName;
    vector<shared_ptr<TeleconButton>> buttons;
    vector<shared_ptr<TeleconToggle>> toggles;
    vector<shared_ptr<TeleconSlider>> sliders;
    vector<shared_ptr<TeleconInput>> inputs;
};