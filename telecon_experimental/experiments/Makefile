WX_FLAGS = `wx-config --libs --cxxflags`
WX_CHART_DIR_FLAGS = -I ~/git-repos/wxchartdir/include -I ~/git-repos/wxchartdir/wxdemo/common -L ~/git-repos/wxchartdir/lib/linux64/ -l chartdir
WX_MATHPLOT_FLAGS = -I ~/git-repos/telecon/lib/wxMathPlot/include
WX_MATHPLOT_PATH = ~/git-repos/telecon/lib/wxMathPlot/src/mathplot.cpp

TEST_FLAGS = -I classes

# Run export LD_LIBRARY_PATH=~/git-repos/wxchartdir/lib/linux64/
# PROJ_DIR = ~/git-repos/telecon/

OBJECTS = TeleconBarChart.o TeleconChartPanel.o TeleconRealTimeLineChart.o



base: baseapp
	LD_LIBRARY_PATH=~/git-repos/wxchartdir/lib/linux64/ ./base

baseapp: base.h base.cpp wxchartviewer.o TeleconBarChart.o TeleconChartPanel.o TeleconRealTimeLineChart.o
	g++ -o base wxchartviewer.o base.cpp $(OBJECTS) $(TEST_FLAGS) $(WX_FLAGS) $(WX_CHART_DIR_FLAGS);

TeleconBarChart.o: classes/TeleconBarChart.cpp classes/TeleconChart.h classes/TeleconBarChart.h
	g++ -c classes/TeleconBarChart.cpp -I classes $(WX_CHART_DIR_FLAGS)

TeleconChartPanel.o: classes/TeleconChartPanel.h classes/TeleconChartPanel.cpp
	g++ -c classes/TeleconChartPanel.cpp -I classes $(WX_FLAGS) $(WX_CHART_DIR_FLAGS)

TeleconRealTimeLineChart.o: classes/TeleconRealTimeLineChart.h classes/TeleconRealTimeLineChart.cpp
	g++ -c classes/TeleconRealTimeLineChart.cpp -I classes $(WX_FLAGS) $(WX_CHART_DIR_FLAGS)

wxchartviewer.o: ~/git-repos/wxchartdir/wxdemo/common/wxchartviewer.cpp
	g++ -c ~/git-repos/wxchartdir/wxdemo/common/wxchartviewer.cpp $(WX_FLAGS) $(WX_CHART_DIR_FLAGS)

telecon.o: telecon.h telecon.cpp mathplot.o 
	g++ -c telecon.cpp mathplot.o $(WX_FLAGS) $(WX_CHART_DIR_FLAGS) 


mathplot.o: $(WX_MATHPLOT_PATH) ~/git-repos/telecon/lib/wxMathPlot/include/mathplot.h
	g++ -c $(WX_MATHPLOT_PATH) $(WX_FLAGS) $(WX_MATHPLOT_FLAGS) 




	
clean: 
	rm *.o base