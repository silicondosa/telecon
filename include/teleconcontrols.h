#pragma once

#include <string>
#include <vector>

using namespace std;

class TeleconButton
{
public:
    TeleconButton(string title);

    string getTitle();
    bool state = false;

private:
    string title;
};

class TeleconSlider
{
public:
    TeleconSlider(string title, int min, int max, int current_state);
    std::string title;
    int min;
    int max;
    int current_state;
};

class TeleconToggle
{
public:
    TeleconToggle(string title);
    std::string title;
    string getTitle();
    bool state = false;
};

class TeleconControls
{
public:
    TeleconControls(string windowName);
    shared_ptr<TeleconButton> addButton(string title);
    shared_ptr<TeleconToggle> addToggle(string title);
    shared_ptr<TeleconSlider> addSlider(string title, int min, int max, int startPos);

    string windowName;
    vector<shared_ptr<TeleconButton>> buttons;
    vector<shared_ptr<TeleconToggle>> toggles;
    vector<shared_ptr<TeleconSlider>> sliders;
};