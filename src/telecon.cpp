// wxWidgets "Hello World" Program

// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <telecon.h>

wxIMPLEMENT_APP(teleconApp);

bool teleconApp::OnInit()
{
	mainFrame* mainWindow = new mainFrame(wxT("TELECON"));
	mainWindow->Show(true);
	return true;
}

mainFrame::mainFrame(const wxString& title) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(250, 150))
{
	Center();
}

