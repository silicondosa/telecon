#pragma once

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "chartdir.h"
#include "TeleconRealTimeLineChart.h"
#include "teleconwindow.h"

#include <vector>
#include <memory>
#include <thread>

class Telecon : public wxApp
{
private:
    static shared_ptr<thread> t;

    std::vector<wxFrame*> frameList;

    static void teleconAppInit(Telecon* mainAppInstance);

    // Private constructor because Telecon should only be created via teleconStart()
    Telecon() = default;

public:
    static Telecon* teleconStart();
    static void teleconJoin();

    TeleconWindow* addWindow(std::string name);
    bool OnInit() override;

    virtual void teleconMain();
};