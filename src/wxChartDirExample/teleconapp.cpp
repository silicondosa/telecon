// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "teleconapp.h"
#include <stdlib.h> 
#include <cmath>
#include <random>

/*
 * Application instance implementation
 */

IMPLEMENT_APP(TeleconApp)

/*
 * TeleconApp type definition
 */

IMPLEMENT_CLASS(TeleconApp, wxApp )

/*
 * TeleconApp event table definition
 */

BEGIN_EVENT_TABLE(TeleconApp, wxApp )
END_EVENT_TABLE()

/*
 * Constructor for TeleconApp
 */

	TeleconApp::TeleconApp()
{
  Init();
}

/*
 * Member initialisation
 */

void
TeleconApp::Init()
{
}


/*
 * Function to generate random Double values
 */
double generateRandomDouble(double min, double max) {
	std::random_device rd;  // Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
	std::uniform_real_distribution<> dis(min, max);
	return dis(gen);
}

/*
 * Function to create random data points
 */
double
CreateDataPoints()
{
	double randomDouble = generateRandomDouble(0.0, 20.0);
	double p = randomDouble;
	double dataA = 20 + cos(p * 129241) * 10 + 1 / (cos(p) * cos(p) + 0.01);
	return dataA;
}


/*
 * Initialisation for TeleconApp
 */

bool
TeleconApp::OnInit()
{    
#if wxUSE_XPM
  wxImage::AddHandler(new wxXPMHandler);
#endif
#if wxUSE_LIBPNG
  wxImage::AddHandler(new wxPNGHandler);
#endif
#if wxUSE_LIBJPEG
  wxImage::AddHandler(new wxJPEGHandler);
#endif
#if wxUSE_GIF
  wxImage::AddHandler(new wxGIFHandler);
#endif

  // teleconMain();

  Telecon* teleconDialog = new Telecon();
  teleconDialog->createWindow("Telecon Window", 700, 700);
  teleconDialog->AddChart("Muscle 1","Voltages");
  teleconDialog->AddPlot("Expected Tension", CreateDataPoints, 0xff0000, (char*)"Expected Tension");
  teleconDialog->AddPlot("Actual Tension", CreateDataPoints, 0x00cc00, (char*)"Actual Tension");
  teleconDialog->AddPlot("Applied Tension", CreateDataPoints, 0x0000ff, (char*)"Applied Tension");
  teleconDialog->Show();
  SetTopWindow(teleconDialog);

  return true;
}

/*
 * Cleanup for TeleconApp
 */

int
TeleconApp::OnExit()
{    
  return wxApp::OnExit();
}

