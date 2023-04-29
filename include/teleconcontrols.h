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

/**
 * Button for Controls window, linked to a function pointer.
 */
class TeleconButton
{
public:

    /**
     * Constructor.
     * 
     * \param title Title of the button
     * \param callback Function that the button should call back to
     */
    TeleconButton(string title, func_t callback);

    /**
     * A function pointer that points to the callback function linked to the button.
     */
    func_t functionPtr;

    /**
     * Getter function for button title.
     * 
     * \return title of button as string
     */
    string getTitle();

    /**
     * State of the button, off (default) or on.
     */
    atomic_bool state = false;

private:
    string title;
};

/**
 * Slider for Controls window, generates a value based on the slider between min and max values.
 */
class TeleconSlider
{
public:

    /**
     * Constructor.
     * 
     * \param title Title of the slider
     * \param min Minimum value that the slider should output
     * \param max Maximum value that the slider should output
     * \param current_state Current value of the slider
     * \param precision How much each slider tick represents
     */
    TeleconSlider(string title, int min, int max, int current_state, int precision);

    /**
     * Title of the slider.
     */
    std::string title;

    /**
     * Minimum value that the slider should output.
     */
    int min;

    /**
     * Maximum value that the slider should output.
     */
    int max;

    /**
     * Current value of the slider.
     */
    atomic_int current_state;

    //TODO
    int precision;
    int offset;

    /**
     * Gets the current value of the slider.
     * 
     * \return current value of the slider as double
     */
    double getCurrentValue();

    /**
     * Gets the current value of the slider as a string.
     * 
     * \return current value of the slider as string
     */
    string current_value_to_string();
};

/**
 * Button for Controls window that stays either on or off when clicked.
 */
class TeleconToggle
{
public:

    /**
     * Constructor.
     * 
     * \param title Title of the toggle button
     */
    TeleconToggle(string title);

    /**
     * Title of the toggle button.
     */
    std::string title;

    /**
     * Gets the toggle title.
     * 
     * \return Title as a string
     */
    string getTitle();

    /**
     * State of the toggle (default off). False = off, True = on
     */
    atomic_bool state = false;
};


/**
 * Input box for Controls window, set value to text in box.
 */
class TeleconInput
{
public:

    /**
     * Constructor.
     * 
     * \param title Title of the input box
     * \param startVal Starting value of the input box
     */
    TeleconInput(string title, int startVal);

    /**
     * Title of the input box.
     */
    std::string title;

    /**
     * Gets the title of the input box.
     * 
     * \return Title as string
     */
    string getTitle();

    /**
     * Current value of the input box.
     */
    atomic<double> val;

    /**
     * Gets the value of the input box.
     * 
     * \return current value as double
     */
    double getVal();

    /**
     * Sets the value of the input box.
     * 
     * \param newVal Value to set input box to
     */
    void setVal(double newVal);

    /**
     * Sets ID of the input box.
     * 
     * \param id ID of the input box as int
     */
    void setId(int id);

    /**
     * Sets wxFrame of the input box.
     * 
     * \param frame Frame of the input box as wxFrame pointer
     */
    void setFrame(wxFrame* frame);

    /**
     * Updats the visual value displayed in the input box.
     * 
     * \param value Valule as a double
     */
    void updateInputBox(double value);

    /**
     * Default Deconstructor.
     * 
     */
    ~TeleconInput();
private:
    wxFrame* frame;
    int id;
    
};


/**
 * Controls portion of TeleCon. Object that represents the controller layout, that can take buttons, toggles, sliders, and input fields.
 */
class TeleconControls
{
public:

    /**
     * Constructor.
     * 
     * \param windowName Name of the window as string
     */
    TeleconControls(string windowName);

    /**
     * Adds a button to controls list.
     * 
     * \param title Title of the button
     * \param callback FUnction the button is tied to
     * \return shared pointer to a TeleconButton object
     */
    shared_ptr<TeleconButton> addButton(string title, func_t callback);

    /**
     * Adds a toggle to controls list.
     *
     * \param title Title of the toggle button
     * \return shared pointer to a TeleconToggle object
     */
    shared_ptr<TeleconToggle> addToggle(string title);

    /**
     * Adds a slider to controls list.
     * 
     * \param title Title of the slider
     * \param min Minimum value of the slider
     * \param max Maximum value of the slider
     * \param startPos Starting default value of the slider
     * \param precision Precision of the slider (tick rate)
     * \return shared pointer to a TeleconSlider object
     */
    shared_ptr<TeleconSlider> addSlider(string title, int min, int max, int startPos, int precision);

    /**
     * Adds an input box to controls list.
     * 
     * \param title Title of the input box
     * \param startVal Starting default value of the input box
     * \return shared pointer to a TeleconInput object
     */
    shared_ptr<TeleconInput> addInput(string title, int startVal);

    /**
     * Name of the Controls window as string.
     */
    string windowName;

    /**
     * List (vector) of all TeleconButton pointers in the controls list.
     */
    vector<shared_ptr<TeleconButton>> buttons;

    /**
     * List (vector) of all TeleconToggle pointers in the controls list.
     */
    vector<shared_ptr<TeleconToggle>> toggles;

    /**
     * List (vector) of all TeleconSlider pointers in the controls list.
     */
    vector<shared_ptr<TeleconSlider>> sliders;

    /**
     * List (vector) of all TeleconInput pointers in the controls list.
     */
    vector<shared_ptr<TeleconInput>> inputs;
};