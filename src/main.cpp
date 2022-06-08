// wxWidgets "Hello World" Program

// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

// myApp needed for every new program and derived from weApp - Overridden Oninit function is where user program functionalities begin
class MyApp : public wxApp
{
public:
	virtual bool OnInit();
};

// Main window derived from wxFrame. Reacting to events done by "event handler" functions each events - hello, exit and about.
// All programs should have an exit and about events. Also note that these functions need not be virtual or public.
class MyFrame : public wxFrame
{
public:
	MyFrame();

private:
	void OnHello(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
};

// Any class that wishes to respond to events (such as mouse clicks/menu messages/button) must declare an ID in the event table here.
// Notice that the 'exit' and 'about' events don't need to define IDs. Their IDs are automatically assigned.
enum
{
	ID_Hello = 1
};

// Implements the main function which creates an application instance and starts the GUI event loop, then calls the OnInit function
wxIMPLEMENT_APP(MyApp);

// All user-specific code execution begins here. Overrides the inherited OnInit() function.
// Everything from a splash screen to creating the main window can done here.
// Note that a frame is the basic building block of all windows.
// Frames are created hidden first, allowing us to build out the frame before making it visible.
bool MyApp::OnInit()
{
	MyFrame* frame = new MyFrame();
	frame->Show(true);
	return true;
}

// Every frame (building block for a window) is derived from the wxFrame class.
// All elements (buttons, sliders, menus, menu items, status bar, text boxes, image viewers, plots, etc.) need to be bound to a frame.
// Once again, remember that each element that needs to respond to events must also have an event handler and event ID.
// Standard items such as exit and about (also copy, cut, paste, etc.) have default IDs. They still need event handlers though.
MyFrame::MyFrame()
	: wxFrame(NULL, wxID_ANY, "Hello World")
{
	// Create a File menu and append menu items to it.
		// note that the "Quit/Exit" menu item has a default ID.
	wxMenu* menuFile = new wxMenu;
	menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
		"Help string shown in status bar for this menu item");
	menuFile->AppendSeparator();
	menuFile->Append(wxID_EXIT);

	// Create a help menu.
		//Note that the "about" menu item has default ID.
	wxMenu* menuHelp = new wxMenu;
	menuHelp->Append(wxID_ABOUT);

	// Create menu bar, append menus to it, and set it to frame.
	wxMenuBar* menuBar = new wxMenuBar;
	menuBar->Append(menuFile, "&File");
	menuBar->Append(menuHelp, "&Help");

	SetMenuBar(menuBar);

	// Create and set a status bar for context-dependant help text
	CreateStatusBar();
	SetStatusText("Welcome to wxWidgets!");

	// Bind event handler functions to event IDs.
		// There are many types of events. These are all wxEVT_MENU events.
		// We use a function point pointer to the event handler routine and call it on the object of choice (our own object here - so, using 'this').
	Bind(wxEVT_MENU, &MyFrame::OnHello, this, ID_Hello);
	Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
	Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
}

// Event handler implementations

// Event handler for the exit menu item
void MyFrame::OnExit(wxCommandEvent& event)
{
	// The parameter 'true' force closes the main window when the menu item is clicked
		// if no other window is left, the application will quit
	Close(true);
}

// Event handler for the about menu item
void MyFrame::OnAbout(wxCommandEvent& event)
{
	// Create a message box pop-up with the appropriate message and title
	wxMessageBox("This is a wxWidgets Hello World example",
		"About Hello World", wxOK | wxICON_INFORMATION);
}

// Event handler for the Hello button
void MyFrame::OnHello(wxCommandEvent& event)
{
	wxLogMessage("Hello world from wxWidgets!");
}