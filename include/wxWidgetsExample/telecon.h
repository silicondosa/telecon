#pragma once

#ifndef TELECON_H
#define TELECON_H

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif // !WX_PRECOMP

#include <mathplot.h>

#define APP_NAME "telecon"
#define ICON_LOC "../resources/telecon_icon.png"

/**
 * telecomApp is the foundational wxWidgets class of telecon, derived from wxApp.
 */
class teleconApp : public wxApp
{
public:
	/** Overridden Oninit function is where user program functionalities begin.*/
	virtual bool OnInit();
};

/**
 * This class defines the object of the primary window of telecon.
 */
class mainFrame : public wxFrame
{
public:
	mainFrame();

	void OnAbout(wxCommandEvent& event);
	void OnQuit(wxCommandEvent& event);
	void OnPrintPreview(wxCommandEvent& event);
	void OnPrint(wxCommandEvent& event);
	void OnFit(wxCommandEvent& event);
	void OnAlignXAxis(wxCommandEvent& event);
	void OnAlignYAxis(wxCommandEvent& event);
	void OnToggleGrid(wxCommandEvent& event);
	void OnToggleScrollbars(wxCommandEvent& event);
	void OnToggleInfoLayer(wxCommandEvent& event);
	void OnSaveScreenshot(wxCommandEvent& event);
	void OnToggleLissajoux(wxCommandEvent& event);
	void OnToggleSine(wxCommandEvent& event);
	void OnToggleCosine(wxCommandEvent& event);
	void OnBlackTheme(wxCommandEvent& event);

	mpWindow* m_plot;
	wxTextCtrl* m_log;

private:
	int axesPos[2];
	bool ticks;
	mpInfoCoords* nfo; // mpInfoLayer* nfo;
	DECLARE_DYNAMIC_CLASS(mainFrame)
	DECLARE_EVENT_TABLE()
};


#endif // !TELECON_H

