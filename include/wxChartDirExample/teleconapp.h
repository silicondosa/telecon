#ifndef TELECONAPP_H_
#define TELECONAPP_H_

/*!
 * Includes
 */

#include "wx/image.h"

#include "telecon.h"

/*!
 * TeleconApp class declaration
 */

class TeleconApp: public wxApp
{    
  DECLARE_CLASS(TeleconApp)
  DECLARE_EVENT_TABLE()

public:
  /// Constructor
    TeleconApp();

  void Init();

  /// Initialises the application
  virtual bool OnInit();

  /// Called on exit
  virtual int OnExit();
};

/*!
 * Application instance declaration 
 */

DECLARE_APP(TeleconApp)

#endif
    // TELECONAPP_H_
