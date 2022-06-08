#pragma once

#ifndef TELECON_H
#define TELECON_H

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif // !WX_PRECOMP

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
	mainFrame(const wxString& title);
};

#endif // !TELECON_H

