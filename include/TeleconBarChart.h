
#include "TeleconChart.h"

#include "chartdir.h"

class TeleconBarChart : public TeleconChart {
    public:
        TeleconBarChart(){ }
        virtual XYChart* makeChart();

};