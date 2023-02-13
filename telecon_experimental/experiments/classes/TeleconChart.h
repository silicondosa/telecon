#ifndef __TELECON_CHART

#define __TELECON_CHART

#include "chartdir.h"

class TeleconChart {
    public: 
        TeleconChart(){ }
        virtual XYChart* makeChart() = 0;
};

#endif