
#include <memory>
#include "teleconcontrols.h"



TeleconControls::TeleconControls(string windowName){
    this->windowName = windowName;
}

shared_ptr<TeleconButton> TeleconControls::addButton(string title){
    shared_ptr<TeleconButton> button = make_shared<TeleconButton>(title);
    buttons.push_back(button);
    return button;

}

shared_ptr<TeleconToggle> TeleconControls::addToggle(string title){
    shared_ptr<TeleconToggle> toggle = make_shared<TeleconToggle>(title);
    toggles.push_back(toggle);
    return toggle;
}

shared_ptr<TeleconSlider> TeleconControls::addSlider(string title, int min, int max, int startPos){
    shared_ptr<TeleconSlider> slider = make_shared<TeleconSlider>(title, min, max, startPos);
    sliders.push_back(slider);
    return slider;
}


TeleconButton::TeleconButton(string title){
    this->title = title;
}
TeleconToggle::TeleconToggle(string title){
    this->title = title;
}
TeleconSlider::TeleconSlider(string title, int min, int max, int startPos){
    this->title = title;
    this->min = min;
    this->max = max;
    this->current_state = startPos;
}


string TeleconButton::getTitle(){
    return title;
}

string TeleconToggle::getTitle(){
    return title;
}