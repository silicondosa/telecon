#pragma once

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/tglbtn.h>

#include <string>
#include <vector>
#include <sstream>

#include "TeleconRealTimeLineChart.h"
#include "wxchartviewer.h"



using namespace std;

static const int chartUpdateIntervals[8] = {250, 500, 750, 1000, 1250, 1500, 1750, 2000};

static const int dataInterval = 250;
static const int sampleSize = 240;

TeleconRealTimeLineChart::~TeleconRealTimeLineChart() {
    m_dataRateTimer->Stop();
    m_chartUpdateTimer->Stop();
}

TeleconRealTimeLineChart::TeleconRealTimeLineChart(wxWindow *parent,
                                                    wxWindowID winid,
                                                    const wxPoint &pos,
                                                    const wxSize &size,
                                                    const wxString title,
                                                    const wxString ylabelwxWindow,
                                                    long style,
                                                    const wxString& name)
    : TeleconChartPanel(parent, winid, pos, size, style, name),
    m_timeStamps{ sampleSize } {
    m_bgColour = GetBackgroundColour();

    m_topSizer = new wxBoxSizer(wxHORIZONTAL);
    SetSizer(m_topSizer);

    m_viewOptionsBox = new wxStaticBox(this, wxID_ANY, wxEmptyString);
    m_viewOptionsBoxSizer = new wxStaticBoxSizer(m_viewOptionsBox, wxVERTICAL);
    m_topSizer->Add(m_viewOptionsBoxSizer, 0, wxGROW | wxALL, FromDIP(3));

    SetUpViewOptionsBox();

    m_chartBoxSizer = new wxBoxSizer(wxVERTICAL);
    m_topSizer->Add(m_chartBoxSizer, 1, wxGROW | wxALL, FromDIP(3));

    SetUpChartBox(title, ylabelwxWindow);
}

void TeleconRealTimeLineChart::SetUpViewOptionsBox() {
    // Add play button
    m_playButton = new wxToggleButton(m_viewOptionsBox, ID_PLAY, _(" &Run"), wxDefaultPosition, wxDefaultSize, wxBU_LEFT);
    // m_playButton->SetBitmap(GetBitmapResource("play.png"));
    // m_playButton->SetBitmapMargins(FromDIP(10), FromDIP(0));
    // Initially set the mouse to drag to scroll mode
    m_playButton->SetValue(true);
    m_viewOptionsBoxSizer->Add(m_playButton, 0, wxGROW | wxALL, FromDIP(3));

    // Add pause button
    m_pauseButton = new wxToggleButton(m_viewOptionsBox, ID_PAUSE, _(" &Freeze"), wxDefaultPosition, wxDefaultSize, wxBU_LEFT);
    // m_pauseButton->SetBitmap(GetBitmapResource("pause.png"));
    // m_pauseButton->SetBitmapMargins(FromDIP(10), FromDIP(0));
    m_pauseButton->SetValue(false);
    m_viewOptionsBoxSizer->Add(m_pauseButton, 0, wxGROW | wxALL, FromDIP(3));

    /* Add a small gap after the playand pause buttons.Gaps have nonzero proportion while buttons have zero proportion,
    so gaps will grow but buttons won't if the window is resized */
    m_viewOptionsBoxSizer->Add(3, 3, 1, wxALIGN_CENTER_HORIZONTAL | wxALL, FromDIP(3));

    // Add save button
    m_saveButton = new wxButton(m_viewOptionsBox, wxID_SAVE, _(" &Save"), wxDefaultPosition, wxDefaultSize, wxBU_LEFT);
    // m_saveButton->SetBitmap(GetBitmapResource("save.png"));
    // m_saveButton->SetBitmapMargins(FromDIP(10), FromDIP(0));
    m_viewOptionsBoxSizer->Add(m_saveButton, 0, wxGROW | wxALL, FromDIP(3));

    m_viewOptionsBoxSizer->Add(3, 3, 1, wxALIGN_CENTER_HORIZONTAL | wxALL, FromDIP(3)); // another gap

    // Add graph update period selector. Note: does not affect underlying data fetch rate
    wxStaticText* graphUpdatePeriodStaticText = new wxStaticText(m_viewOptionsBox, wxID_STATIC, _("Update Period (ms)"), wxDefaultPosition, wxDefaultSize, 0);
    m_viewOptionsBoxSizer->Add(graphUpdatePeriodStaticText, 0, wxALIGN_LEFT | wxALL, FromDIP(3));

    wxArrayString m_updatePeriodStrings;
    for (auto i : chartUpdateIntervals) {
        m_updatePeriodStrings.Add(wxString::Format("%d", i));
    }
    m_updatePeriodSelector = new wxChoice(this, ID_UPDATE_PERIOD, wxDefaultPosition, wxDefaultSize, m_updatePeriodStrings, 0);
    m_updatePeriodSelector->SetStringSelection(wxString::Format("%d", chartUpdateIntervals[0]));
    m_viewOptionsBoxSizer->Add(m_updatePeriodSelector, 0, wxGROW | wxALL, FromDIP(3));

    m_viewOptionsBoxSizer->Add(3, 3, 1, wxALIGN_CENTER_HORIZONTAL | wxALL, FromDIP(3));

    m_plotLatestValueFlexGridSizer = new wxFlexGridSizer(0, 2, 0, 0);
    m_viewOptionsBoxSizer->Add(m_plotLatestValueFlexGridSizer, 0, wxGROW | wxALL, FromDIP(3));
}

void TeleconRealTimeLineChart::SetUpChartBox(const wxString title, const wxString ylabel) {
    m_chartTitle = title;
    m_ylabel = ylabel;

    m_chartViewer = new wxChartViewer(this, ID_CHARTVIEWER, wxDefaultPosition, FromDIP(wxSize(600, 270)), wxTAB_TRAVERSAL | wxNO_BORDER);
    m_chartBoxSizer->Add(m_chartViewer, 1, wxGROW | wxALL, FromDIP(3));

    m_currentIndex = 0;

    // Set m_nextDataTime to the current time. It is used by the real time random number
    // generator so it knows what timestamp should be used for the next data point.
    m_nextDataTime = wxDateTime::Now();

    // Set up the data acquisition mechanism. In this demo, we just use a timer to get a sample every ms.
    m_dataRateTimer = new wxTimer(this, ID_DATA_TIMER);
    m_dataRateTimer->Start(dataInterval);

    // Set up the chart update timer
    m_chartUpdateTimer = new wxTimer(this, ID_UPDATE_TIMER);
    m_chartUpdateTimer->Start(chartUpdateIntervals[0]);
}

BEGIN_EVENT_TABLE(TeleconRealTimeLineChart, wxPanel)

EVT_TOGGLEBUTTON(ID_PLAY, TeleconRealTimeLineChart::OnPlayClick)
EVT_TOGGLEBUTTON(ID_PAUSE, TeleconRealTimeLineChart::OnPauseClick)
EVT_CHOICE(ID_UPDATE_PERIOD, TeleconRealTimeLineChart::OnChartUpdatePeriodSelected)
EVT_BUTTON(wxID_SAVE, TeleconRealTimeLineChart::OnSave)

EVT_TIMER(ID_DATA_TIMER, TeleconRealTimeLineChart::OnDataTimer)
EVT_TIMER(ID_UPDATE_TIMER, TeleconRealTimeLineChart::OnChartUpdateTimer)
EVT_CHARTVIEWER_VIEWPORT_CHANGED(ID_CHARTVIEWER, TeleconRealTimeLineChart::OnViewPortChanged)
EVT_CHARTVIEWER_MOUSEMOVE_PLOTAREA(ID_CHARTVIEWER, TeleconRealTimeLineChart::OnMouseMovePlotArea)

END_EVENT_TABLE()

// Event handler
void TeleconRealTimeLineChart::OnPlayClick(wxCommandEvent& event) {
    m_playButton->SetValue(true);
    m_pauseButton->SetValue(false);
    m_chartUpdateTimer->Start();
}

// Event handler
void TeleconRealTimeLineChart::OnPauseClick(wxCommandEvent& event) {
    m_playButton->SetValue(false);
    m_pauseButton->SetValue(true);
    m_chartUpdateTimer->Stop();
}

// Event handler
void TeleconRealTimeLineChart::OnChartUpdatePeriodSelected(wxCommandEvent& event) {
    long interval;
    (m_updatePeriodSelector->GetString(m_updatePeriodSelector->GetSelection())).ToLong(&interval);
    m_chartUpdateTimer->Start(interval);
}

// Event handler
void TeleconRealTimeLineChart::OnSave(wxCommandEvent& event) {
    wxFileDialog saveFileDialog(this, _("Save graphics file"), "", "chartdirector_demo",
        "PNG (*.png)|*.png|JPG (*.jpg)|*.jpg|GIF (*.gif)|*.gif|BMP (*.bmp)|*.bmp|SVG (*.svg)|*.svg|PDF (*.pdf)|*.pdf", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    if (saveFileDialog.ShowModal() == wxID_CANCEL)
        return;     // the user changed idea...

    // save the current contents in the file;
    wxString fileName = saveFileDialog.GetPath();
    if (!fileName.IsEmpty())
    {
        // Save the chart
        BaseChart* c = m_chartViewer->getChart();
        if (0 != c)
        {
            c->makeChart(fileName.ToUTF8());
        }
    }
}

// Event handler
void TeleconRealTimeLineChart::OnChartUpdateTimer(wxTimerEvent& event) {
    // Will result in a call to OnViewPortChanged, which may redraw the chart if needed
    m_chartViewer->updateViewPort(true, false);
}

// Event handler
void TeleconRealTimeLineChart::OnDataTimer(wxTimerEvent& event) {
    GetData(funcArray);
}

// Event handler
// This event occurs if the user scrolls or zooms in or out the chart by dragging or clicking on the chart.
// It can also be triggered by calling WinChartViewer.updateViewPort.
void TeleconRealTimeLineChart::OnViewPortChanged(wxCommandEvent& event) {
    if (m_chartViewer->needUpdateChart()) {
        DrawChart();
    }
}

// A utility to shift a new data value into a data array
static void ShiftData(double* data, int len, double newValue) {
    memmove(data, data + 1, sizeof(*data) * (len - 1));
    data[len - 1] = newValue;
}

// Shift new data values into the real time data series
void TeleconRealTimeLineChart::GetData(/*windowID, chartID, plotID, function ptr */std::vector<FuncPtr>& funcArray) {
    // The current time
    wxDateTime now = wxDateTime::Now();

    // This is our formula for the random number generator
    do
    {
        // We need the currentTime in millisecond resolution
        double currentTime = Chart::chartTime2(m_nextDataTime.GetTicks())
            + m_nextDataTime.GetMillisecond() / 1000.0;

        std::vector<double> data;
        //double dataA = 20 + cos(p * 129241) * 10 + 1 / (cos(p) * cos(p) + 0.01);
        for (auto func : funcArray) {
            data.push_back(func());
        }

        // After obtaining the new values, we need to update the data arrays.
        // Store the new values in the current index position, and increment the index.
        int i = 0;
        for (const double& element : data) {
            m_dataSeries[i].insertNewValue(element);
            i++;
        }
        m_timeStamps.insertNewValue(currentTime);

        m_nextDataTime.Add(wxTimeSpan(0, 0, 0, dataInterval));
    } while (m_nextDataTime < now);

    // We provide some visual feedback to the latest numbers generated, so you can see the
    // data being generated.
    int i = 0;
    for (auto& element : m_dataValues) {
        if (m_dataSeries[0].size() > 0) {
            element->SetValue(wxString::Format("%.2f", m_dataSeries[0].latest()));
        }
        i++;
    }
}

void
TeleconRealTimeLineChart::DrawChart()
{
    // Create an XYChart object 600 x 270 pixels in size, with light grey (f4f4f4) 
    // background, black (000000) border, 1 pixel raised effect, and with a rounded frame.
    XYChart* c = new XYChart(520, 270, 0xf4f4f4, 0x000000, 1);
    c->setRoundedFrame((m_bgColour.Red() << 16) + (m_bgColour.Green() << 8) + m_bgColour.Blue());

    // Set the plotarea at (55, 55) and of size 520 x 185 pixels. Use white (ffffff) 
    // background. Enable both horizontal and vertical grids by setting their colors to 
    // grey (cccccc). Set clipping mode to clip the data lines to the plot area.
    c->setPlotArea(55, 55, 520, 185, 0xffffff, -1, -1, 0xcccccc, 0xcccccc);
    c->setClipping();

    // Add a title to the chart using 15 pts Times New Roman Bold Italic font, with a light
    // grey (dddddd) background, black (000000) border, and a glass like raised effect.
    c->addTitle(m_chartTitle, "Times New Roman Bold Italic", 15
    )->setBackground(0xdddddd, 0x000000, Chart::glassEffect());

    // Set the reference font size of the legend box
    c->getLegend()->setFontSize(8);

    // Configure the y-axis with a 10pts Arial Bold axis title
    c->yAxis()->setTitle(m_ylabel, "Arial Bold", 10);

    // Configure the x-axis to auto-scale with at least 75 pixels between major tick and 
    // 15  pixels between minor ticks. This shows more minor grid lines on the chart.
    c->xAxis()->setTickDensity(75, 15);

    // Set the axes width to 2 pixels
    c->xAxis()->setWidth(2);
    c->yAxis()->setWidth(2);

    // Now we add the data to the chart. 
    if (m_timeStamps.size() > 0) {
        double firstTime = m_timeStamps[0];
        // Set up the x-axis to show the time range in the data buffer
        c->xAxis()->setDateScale(firstTime, firstTime + dataInterval * sampleSize / 1000);

        // Set the x-axis label format
        c->xAxis()->setLabelFormat("{value|hh:nn:ss}");

        // Create a line layer to plot the lines
        LineLayer* layer = c->addLineLayer();

        // The x-coordinates are the timeStamps.
        layer->setXData(DoubleArray(&m_timeStamps[0], m_timeStamps.size()));

        // The 3 data series are used to draw 3 lines.
        int i = 0;
        for (const DataBuffer<double>& element : m_dataSeries) {
            layer->addDataSet(DoubleArray(&element[0], element.size()), m_colorSeries[i], m_plottitleSeries[i]);
            i++;
        }
    }

    // Include track line with legend. If the mouse is on the plot area, show the track 
    // line with legend at the mouse position; otherwise, show them for the latest data
    // values (that is, at the rightmost position).
    TrackLineLegend(c, m_chartViewer->isMouseOnPlotArea() ? m_chartViewer->getPlotAreaMouseX() :
        c->getPlotArea()->getRightX());


    if (m_chartViewer->getChart() != NULL)
    {
        delete m_chartViewer->getChart();
    }
    // Set the chart image to the WinChartViewer
    m_chartViewer->setChart(c);
}

// Draw track cursor when mouse is moving over plotarea
void TeleconRealTimeLineChart::OnMouseMovePlotArea(wxCommandEvent& event)
{
    TrackLineLegend((XYChart*)m_chartViewer->getChart(), m_chartViewer->getPlotAreaMouseX());
    m_chartViewer->updateDisplay();
}

// Draw the track line with legend
void
TeleconRealTimeLineChart::TrackLineLegend(XYChart* c, int mouseX)
{
    // Clear the current dynamic layer and get the DrawArea object to draw on it.
    DrawArea* d = c->initDynamicLayer();

    // The plot area object
    PlotArea* plotArea = c->getPlotArea();

    // Get the data x-value that is nearest to the mouse, and find its pixel coordinate.
    double xValue = c->getNearestXValue(mouseX);
    int xCoor = c->getXCoor(xValue);

    // Draw a vertical track line at the x-position
    d->vline(plotArea->getTopY(), plotArea->getBottomY(), xCoor, d->dashLineColor(0x000000, 0x0101));

    // Container to hold the legend entries
    vector<string> legendEntries;

    // Iterate through all layers to build the legend array
    for (int i = 0; i < c->getLayerCount(); ++i)
    {
        Layer* layer = c->getLayerByZ(i);

        // The data array index of the x-value
        int xIndex = layer->getXIndexOf(xValue);

        // Iterate through all the data sets in the layer
        for (int j = 0; j < layer->getDataSetCount(); ++j)
        {
            DataSet* dataSet = layer->getDataSetByZ(j);

            // We are only interested in visible data sets with names
            const char* dataName = dataSet->getDataName();
            int color = dataSet->getDataColor();
            if (dataName && *dataName && (color != (int)Chart::Transparent))
            {
                // Build the legend entry, consist of the legend icon, name and data value.
                double dataValue = dataSet->getValue(xIndex);
                ostringstream legendEntry;
                legendEntry << "<*block*>" << dataSet->getLegendIcon() << " " << dataName << ": " <<
                    ((dataValue == Chart::NoValue) ? "N/A" : c->formatValue(dataValue, "{value|P4}"))
                    << "<*/*>";
                legendEntries.push_back(legendEntry.str());

                // Draw a track dot for data points within the plot area
                int yCoor = c->getYCoor(dataSet->getPosition(xIndex), dataSet->getUseYAxis());
                if ((yCoor >= plotArea->getTopY()) && (yCoor <= plotArea->getBottomY()))
                {
                    d->circle(xCoor, yCoor, 4, 4, color, color);
                }
            }
        }
    }

    // Create the legend by joining the legend entries
    ostringstream legendText;
    legendText << "<*block,maxWidth=" << plotArea->getWidth() << "*><*block*><*font=Arial Bold*>["
        << c->xAxis()->getFormattedLabel(xValue, "hh:nn:ss") << "]<*/*>";
    for (int i = ((int)legendEntries.size()) - 1; i >= 0; --i)
    {
        legendText << "        " << legendEntries[i];
    }

    // Display the legend on the top of the plot area
    TTFText* t = d->text(legendText.str().c_str(), "Arial", 8);
    t->draw(plotArea->getLeftX() + 5, plotArea->getTopY() - 3, 0x000000, Chart::BottomLeft);
    t->destroy();
}

/*
 * Get bitmap resources
 */

wxBitmap
TeleconRealTimeLineChart::GetBitmapResource(const wxString& name)
{
    // Bitmap retrieval
    wxImage image;
    if (name == wxT("play.png"))
    {
        image.LoadFile(wxT("./icons/play.png"), wxBITMAP_TYPE_PNG);
        image.Rescale(FromDIP(16), FromDIP(16));
        return wxBitmap(image);
    }
    else if (name == wxT("pause.png"))
    {
        image.LoadFile(wxT("./icons/pause.png"), wxBITMAP_TYPE_PNG);
        image.Rescale(FromDIP(16), FromDIP(16));
        return wxBitmap(image);
    }
    else if (name == wxT("save.png"))
    {
        image.LoadFile(wxT("./icons/save_icon.png"), wxBITMAP_TYPE_PNG);
        image.Rescale(FromDIP(16), FromDIP(16));
        return wxBitmap(image);
    }
    return wxNullBitmap;
}

void TeleconRealTimeLineChart::addPlot(const wxString& plotname, double (*ptr)(), int plotcolor, const char* plottitle)
{
    funcArray.push_back(ptr);
    
    wxStaticText* itemStaticText5 = new wxStaticText(this, wxID_STATIC, _(plotname), wxDefaultPosition, wxDefaultSize, 0);
    m_plotLatestValueFlexGridSizer->Add(itemStaticText5, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxALL, FromDIP(3));

    wxTextCtrl* m_alphaValue = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, FromDIP(wxSize(60, -1)), wxTE_READONLY | wxSTATIC_BORDER);
    m_alphaValue->Enable(false);
    m_plotLatestValueFlexGridSizer->Add(m_alphaValue, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxALL, FromDIP(3));
    m_dataValues.push_back(m_alphaValue);

    m_dataSeries.push_back(DataBuffer<double>(sampleSize));
    m_colorSeries.push_back(plotcolor);
    m_plottitleSeries.push_back(plottitle);
}