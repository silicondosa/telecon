WX_FLAGS = `wx-config --libs --cxxflags`
WX_CHART_DIR_FLAGS = -I ~/git-repos/wxchartdir/include -I ~/git-repos/wxchartdir/wxdemo/common -L ~/git-repos/wxchartdir/lib/linux64/ -l chartdir
WX_MATHPLOT_FLAGS = -I ~/git-repos/telecon/lib/wxMathPlot/include
WX_MATHPLOT_PATH = ~/git-repos/telecon/lib/wxMathPlot/src/mathplot.cpp

TEST_FLAGS = -I ../include/

# Run export LD_LIBRARY_PATH=~/git-repos/wxchartdir/lib/linux64/
# PROJ_DIR = ~/git-repos/telecon/

OBJECTS = TeleconBarChart.o TeleconChartPanel.o TeleconRealTimeLineChart.o teleconplot.o start.o



base: baseapp
	LD_LIBRARY_PATH=~/git-repos/wxchartdir/lib/linux64/ ./base

baseapp: ../include/base.h base.cpp wxchartviewer.o $(OBJECTS) userfile.cpp
	g++ -o base wxchartviewer.o base.cpp userfile.cpp -I ../include/ $(OBJECTS) $(TEST_FLAGS) $(WX_FLAGS) $(WX_CHART_DIR_FLAGS);

TeleconBarChart.o: TeleconBarChart.cpp ../include/TeleconChart.h ../include/TeleconBarChart.h
	g++ -c TeleconBarChart.cpp -I ../include/ $(WX_CHART_DIR_FLAGS)

TeleconChartPanel.o: ../include/TeleconChartPanel.h TeleconChartPanel.cpp
	g++ -c TeleconChartPanel.cpp -I ../include/ $(WX_FLAGS) $(WX_CHART_DIR_FLAGS)

TeleconRealTimeLineChart.o: ../include/TeleconRealTimeLineChart.h TeleconRealTimeLineChart.cpp ../include/teleconplot.h
	g++ -c TeleconRealTimeLineChart.cpp -I ../include/ $(WX_FLAGS) $(WX_CHART_DIR_FLAGS)

teleconplot.o: teleconplot.cpp ../include/teleconplot.h
	g++ -c teleconplot.cpp -I ../include/ $(WX_FLAGS) $(WX_CHART_DIR_FLAGS)

start.o: start.cpp ../include/start.h
	g++ -c start.cpp -I ../include/ $(WX_FLAGS) $(WX_CHART_DIR_FLAGS)

wxchartviewer.o: ~/git-repos/wxchartdir/wxdemo/common/wxchartviewer.cpp
	g++ -c ~/git-repos/wxchartdir/wxdemo/common/wxchartviewer.cpp $(WX_FLAGS) $(WX_CHART_DIR_FLAGS)

telecon.o: telecon.h telecon.cpp mathplot.o 
	g++ -c telecon.cpp mathplot.o $(WX_FLAGS) $(WX_CHART_DIR_FLAGS) 


mathplot.o: $(WX_MATHPLOT_PATH) ~/git-repos/telecon/lib/wxMathPlot/include/mathplot.h
	g++ -c $(WX_MATHPLOT_PATH) $(WX_FLAGS) $(WX_MATHPLOT_FLAGS) 




	
clean: 
	rm *.o base