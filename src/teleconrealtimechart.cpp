// #pragma once

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/tglbtn.h>

#include <string>
#include <vector>
#include <sstream>

#include "teleconrealtimechart.h"
#include "wxchartviewer.h"

#include "teleconscatterplot.h"

using namespace std;

static const int chartUpdateIntervals[8] = {250, 500, 750, 1000, 1250, 1500, 1750, 2000};

TeleconRealTimeChart::~TeleconRealTimeChart()
{
    m_chartUpdateTimer->Stop();
}

TeleconRealTimeChart::TeleconRealTimeChart(
    TeleconChart* chart,
    wxWindow* parent,
    wxWindowID winid,
    const wxPoint& pos,
    const wxSize& size,
    long style,
    const wxString& name
) : wxPanel(parent, winid, pos, size, style, name), m_chart(chart)
{
    m_bgColour = GetBackgroundColour();

    m_topSizer = new wxBoxSizer(wxHORIZONTAL);
    SetSizer(m_topSizer);

    m_viewOptionsBox = new wxStaticBox(this, wxID_ANY, wxEmptyString);
    m_viewOptionsBoxSizer = new wxStaticBoxSizer(m_viewOptionsBox, wxVERTICAL);
    m_topSizer->Add(m_viewOptionsBoxSizer, 0, wxGROW | wxALL, FromDIP(3));

    SetUpViewOptionsBox();

    m_chartBoxSizer = new wxBoxSizer(wxVERTICAL);
    m_topSizer->Add(m_chartBoxSizer, 1, wxGROW | wxALL, FromDIP(3));

    SetUpChartBox();
}

void TeleconRealTimeChart::SetUpViewOptionsBox()
{
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

    /* Add a small gap after the playand pause buttons. Gaps have nonzero proportion while buttons have zero proportion,
    so gaps will grow but buttons won't if the window is resized */
    m_viewOptionsBoxSizer->Add(3, 3, 1, wxALIGN_CENTER_HORIZONTAL | wxALL, FromDIP(3));

    // Add save button
    m_saveButton = new wxButton(m_viewOptionsBox, wxID_SAVE, _(" &Save"), wxDefaultPosition, wxDefaultSize, wxBU_LEFT);
    // m_saveButton->SetBitmap(GetBitmapResource("save.png"));
    // m_saveButton->SetBitmapMargins(FromDIP(10), FromDIP(0));
    m_viewOptionsBoxSizer->Add(m_saveButton, 0, wxGROW | wxALL, FromDIP(3));

    m_viewOptionsBoxSizer->Add(3, 3, 1, wxALIGN_CENTER_HORIZONTAL | wxALL, FromDIP(3)); // another gap

    // Add graph update period selector. Note: does not affect underlying data fetch rate
    wxStaticText *graphUpdatePeriodStaticText = new wxStaticText(m_viewOptionsBox, wxID_STATIC, _("Update Period (ms)"), wxDefaultPosition, wxDefaultSize, 0);
    m_viewOptionsBoxSizer->Add(graphUpdatePeriodStaticText, 0, wxALIGN_LEFT | wxALL, FromDIP(3));

    wxArrayString m_updatePeriodStrings;
    for (auto i : chartUpdateIntervals)
    {
        m_updatePeriodStrings.Add(wxString::Format("%d", i));
    }
    m_updatePeriodSelector = new wxChoice(this, ID_UPDATE_PERIOD, wxDefaultPosition, wxDefaultSize, m_updatePeriodStrings, 0);
    m_updatePeriodSelector->SetStringSelection(wxString::Format("%d", chartUpdateIntervals[0]));
    m_viewOptionsBoxSizer->Add(m_updatePeriodSelector, 0, wxGROW | wxALL, FromDIP(3));

    m_viewOptionsBoxSizer->Add(3, 3, 1, wxALIGN_CENTER_HORIZONTAL | wxALL, FromDIP(3));

    m_plotLatestValueFlexGridSizer = new wxFlexGridSizer(0, 2, 0, 0);
    m_viewOptionsBoxSizer->Add(m_plotLatestValueFlexGridSizer, 0, wxGROW | wxALL, FromDIP(3));

    for (int i = 0; i < m_chart->getNumPlots(); i++) {
        addLatestValueText(m_chart->getPlot(i)->getPlotTitle());
    }
}

void TeleconRealTimeChart::SetUpChartBox()
{
    m_chartViewer = new wxChartViewer(this, ID_CHARTVIEWER, wxDefaultPosition, FromDIP(wxSize(600, 270)), wxTAB_TRAVERSAL | wxNO_BORDER);
    m_chartBoxSizer->Add(m_chartViewer, 1, wxGROW | wxALL, FromDIP(3));

    // Set up the chart update timer
    m_chartUpdateTimer = new wxTimer(this, ID_UPDATE_TIMER);
    m_chartUpdateTimer->Start(chartUpdateIntervals[0]);
}

BEGIN_EVENT_TABLE(TeleconRealTimeChart, wxPanel)

EVT_TOGGLEBUTTON(ID_PLAY, TeleconRealTimeChart::OnPlayClick)
EVT_TOGGLEBUTTON(ID_PAUSE, TeleconRealTimeChart::OnPauseClick)
EVT_CHOICE(ID_UPDATE_PERIOD, TeleconRealTimeChart::OnChartUpdatePeriodSelected)
EVT_BUTTON(wxID_SAVE, TeleconRealTimeChart::OnSave)

EVT_TIMER(ID_UPDATE_TIMER, TeleconRealTimeChart::OnChartUpdateTimer)
EVT_CHARTVIEWER_VIEWPORT_CHANGED(ID_CHARTVIEWER, TeleconRealTimeChart::OnViewPortChanged)
EVT_CHARTVIEWER_MOUSEMOVE_PLOTAREA(ID_CHARTVIEWER, TeleconRealTimeChart::OnMouseMovePlotArea)

END_EVENT_TABLE()

// Event handler
void TeleconRealTimeChart::OnPlayClick(wxCommandEvent &event)
{
    m_playButton->SetValue(true);
    m_pauseButton->SetValue(false);
    m_chartUpdateTimer->Start();
}

// Event handler
void TeleconRealTimeChart::OnPauseClick(wxCommandEvent &event)
{
    m_playButton->SetValue(false);
    m_pauseButton->SetValue(true);
    m_chartUpdateTimer->Stop();
}

// Event handler
void TeleconRealTimeChart::OnChartUpdatePeriodSelected(wxCommandEvent &event)
{
    long interval;
    (m_updatePeriodSelector->GetString(m_updatePeriodSelector->GetSelection())).ToLong(&interval);
    m_chartUpdateTimer->Start(interval);
}

// Event handler
void TeleconRealTimeChart::OnSave(wxCommandEvent &event)
{
    wxFileDialog saveFileDialog(this, _("Save graphics file"), "", "chartdirector_demo",
                                "PNG (*.png)|*.png|JPG (*.jpg)|*.jpg|GIF (*.gif)|*.gif|BMP (*.bmp)|*.bmp|SVG (*.svg)|*.svg|PDF (*.pdf)|*.pdf", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    if (saveFileDialog.ShowModal() == wxID_CANCEL)
        return; // the user changed idea...

    // save the current contents in the file;
    wxString fileName = saveFileDialog.GetPath();
    if (!fileName.IsEmpty())
    {
        // Save the chart
        BaseChart *c = m_chartViewer->getChart();
        if (0 != c)
        {
            c->makeChart(fileName.ToUTF8());
        }
    }
}

// Event handler
void TeleconRealTimeChart::OnChartUpdateTimer(wxTimerEvent &event)
{
    // Will result in a call to OnViewPortChanged, which may redraw the chart if needed
    m_chartViewer->updateViewPort(true, false);
}

// Event handler
// This event occurs if the user scrolls or zooms in or out the chart by dragging or clicking on the chart.
// It can also be triggered by calling WinChartViewer.updateViewPort.
void TeleconRealTimeChart::OnViewPortChanged(wxCommandEvent &event)
{
    if (m_chartViewer->needUpdateChart())
    {
        DrawChart();
    }
}

void TeleconRealTimeChart::DrawChart()
{
    static const int chartWidth = 600;
    static const int chartHeight = 270;
    // Create an XYChart object 600 x 270 pixels in size, with light grey (f4f4f4)
    // background, black (000000) border, 1 pixel raised effect, and with a rounded frame.
    XYChart *c = new XYChart(chartWidth, chartHeight, 0xf4f4f4, 0x000000, 1);
    c->setRoundedFrame((m_bgColour.Red() << 16) + (m_bgColour.Green() << 8) + m_bgColour.Blue());

    // Add a title to the chart using 15 pts Times New Roman Bold Italic font, with a light
    // grey (dddddd) background, black (000000) border, and a glass like raised effect.
    m_titleBox = c->addTitle(m_chart->getTitle().c_str(), "Times New Roman Bold Italic", 15);
    m_titleBox->setBackground(0xdddddd, 0x000000, Chart::glassEffect());

    // Set the plotarea at (55, 55) and of size 520 x 185 pixels. Use white (ffffff)
    // background. Enable both horizontal and vertical grids by setting their colors to
    // grey (cccccc). Set clipping mode to clip the data lines to the plot area.
    // The plot area doesn't actually matter much because we'll correct it later.
    c->setPlotArea(155, 55, 520, 185, 0xffffff, -1, -1, 0xcccccc, 0xcccccc);
    c->setClipping();

    // Set the reference font size of the legend box
    c->getLegend()->setFontSize(8);

    // Configure the x- and y-axes with a 10pts Arial Bold axis title
    c->yAxis()->setTitle(m_chart->getYLabel().c_str(), "Arial Bold", 10);

    c->xAxis()->setTitle(m_chart->getXLabel().c_str(), "Arial Bold", 10);

    // Configure the x-axis to auto-scale with at least 75 pixels between major tick and
    // 15  pixels between minor ticks. This shows more minor grid lines on the chart.
    c->xAxis()->setTickDensity(75, 15);

    // Set the axes width to 2 pixels
    c->xAxis()->setWidth(2);
    c->yAxis()->setWidth(2);

    // Now we add the data to the chart.
    bool hasData = false;
    double firstTime;
    for (int i = 0; i < m_chart->getNumPlots(); i++) {
        TeleconPlot* plot = m_chart->getPlot(i);
        plot->prepDataForDraw();
        if (plot->size() > 0 && (!hasData || plot->getEarliestTimestamp() < firstTime)) {
            firstTime = plot->getEarliestTimestamp();
            hasData = true;
        }
    }
    if (hasData) {
        // Calculate the total time range, and take the larger of that and the suggested range
        double dataTimeInterval = 0.0;
        for (int i = 0; i < m_chart->getNumPlots(); i++) {
            TeleconPlot* plot = m_chart->getPlot(i);
            if (plot->size() > 0 && (plot->getLatestTimestamp() - plot->getEarliestTimestamp() > dataTimeInterval)) {
                dataTimeInterval = plot->getLatestTimestamp() - plot->getEarliestTimestamp();
            }
        }
        // Default timespan is given in minutes, so convert it to seconds
        double defaultTimespanSeconds = m_chart->getDefaultTimespan() * 60.0;
        double dateScale = defaultTimespanSeconds > dataTimeInterval ? defaultTimespanSeconds : dataTimeInterval;
        // Give a 5% margin on either side of the data
        c->xAxis()->setDateScale(firstTime- dateScale * 0.05, firstTime + dateScale * 1.05);

        // Set the x-axis label format
        c->xAxis()->setLabelFormat("{value|hh:nn:ss}");

        // The data series are used to draw lines.
        for (int i = 0; i < m_chart->getNumPlots(); i++) {
            TeleconPlot* plot = m_chart->getPlot(i);
            plot->addToChart(c);
            m_latestValueTextCtrls[i]->SetValue(wxString::Format("%.2f", plot->getLastestValue()));
        }
    }

    // 5 for a margin, 13 for one line of the legend (should be changed to prevent overlap with plot). 9 for height of watermark
    c->packPlotArea(0, m_titleBox->getHeight() + 5 + 13, chartWidth, chartHeight - 9);
    
    // Include track line with legend. If the mouse is on the plot area, show the track
    // line with legend at the mouse position; otherwise, show them for the latest data
    // values (that is, at the rightmost position).
    TrackLineLegend(c, m_chartViewer->isMouseOnPlotArea() ? m_chartViewer->getPlotAreaMouseX() : c->getPlotArea()->getRightX());
    
    if (m_chartViewer->getChart() != NULL)
    {
        delete m_chartViewer->getChart();
    }
    // Set the chart image to the WinChartViewer
    m_chartViewer->setChart(c);
}

// Draw track cursor when mouse is moving over plotarea
void TeleconRealTimeChart::OnMouseMovePlotArea(wxCommandEvent &event)
{
    TrackLineLegend((XYChart *)m_chartViewer->getChart(), m_chartViewer->getPlotAreaMouseX());
    m_chartViewer->updateDisplay();
}

// Draw the track line with legend
void TeleconRealTimeChart::TrackLineLegend(XYChart *c, int mouseX)
{
    // Clear the current dynamic layer and get the DrawArea object to draw on it.
    DrawArea *d = c->initDynamicLayer();

    // The plot area object
    PlotArea *plotArea = c->getPlotArea();

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
        Layer *layer = c->getLayerByZ(i);

        double layerXValue = layer->getNearestXValue(mouseX);

        // The data array index of the x-value
        int xIndex = layer->getXIndexOf(layerXValue);

        // Iterate through all the data sets in the layer
        for (int j = 0; j < layer->getDataSetCount(); ++j)
        {
            DataSet *dataSet = layer->getDataSetByZ(j);

            // We are only interested in visible data sets with names
            const char *dataName = dataSet->getDataName();
            int color = dataSet->getDataColor();
            if (dataName && *dataName)
            {
                // Build the legend entry, consist of the legend icon, name and data value.
                double dataValue = dataSet->getValue(xIndex);
                ostringstream legendEntry;
                legendEntry << "<*block*>" << dataSet->getLegendIcon() << " " << dataName << ": " << ((dataValue == Chart::NoValue) ? "N/A" : c->formatValue(dataValue, "{value|P4}"))
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
    TTFText *t = d->text(legendText.str().c_str(), "Arial", 8);
    t->draw(5, m_titleBox->getHeight(), 0x000000, Chart::TopLeft);
    int height = t->getHeight();
    t->destroy();
}

/*
 * Get bitmap resources
 */

wxBitmap
TeleconRealTimeChart::GetBitmapResource(const wxString &name)
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

void TeleconRealTimeChart::addLatestValueText(string plottitle) {
    wxStaticText* latestValueLabel = new wxStaticText(this, wxID_STATIC, wxString(plottitle), wxDefaultPosition, wxDefaultSize, 0);
    m_plotLatestValueFlexGridSizer->Add(latestValueLabel, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxALL, FromDIP(3));

    wxTextCtrl* latestValueText = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, FromDIP(wxSize(60, -1)), wxTE_READONLY | wxSTATIC_BORDER);
    latestValueText->Enable(false);
    m_plotLatestValueFlexGridSizer->Add(latestValueText, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxALL, FromDIP(3));
    m_latestValueTextCtrls.push_back(latestValueText);
}