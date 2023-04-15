WX_FLAGS = `wx-config --libs --cxxflags`
WX_CHART_DIR_FLAGS = -I ~/git-repos/wxchartdir/include -I ~/git-repos/wxchartdir/wxdemo/common -L ~/git-repos/wxchartdir/lib/linux64/ -l chartdir
WX_MATHPLOT_FLAGS = -I ~/git-repos/telecon/lib/wxMathPlot/include
WX_MATHPLOT_PATH = ~/git-repos/telecon/lib/wxMathPlot/src/mathplot.cpp

TEST_FLAGS = -I ../include/

# Run export LD_LIBRARY_PATH=~/git-repos/wxchartdir/lib/linux64/
# PROJ_DIR = ~/git-repos/telecon/

OBJECTS = teleconwindow.o teleconrealtimechart.o teleconwxplot.o \
		teleconwxlineplot.o teleconwxscatterplot.o teleconchart.o telecon.o \
		teleconwxchart.o teleconwxplotxy.o teleconwxwindow.o teleconwxapp.o \
		teleconwxcontrolswindow.o teleconcontrols.o


CXXFLAGS = 

# base: baseapp
# 	LD_LIBRARY_PATH=~/git-repos/wxchartdir/lib/linux64/ ./base

# baseapp: ../include/base.h base.cpp wxchartviewer.o $(OBJECTS) userfile.cpp
# 	g++ -o base wxchartviewer.o base.cpp userfile.cpp -I ../include/ $(OBJECTS) $(TEST_FLAGS) $(WX_FLAGS) $(WX_CHART_DIR_FLAGS);

run: myapp
	LD_LIBRARY_PATH=~/git-repos/wxchartdir/lib/linux64/ ./myapp

myapp: userfile.cpp $(OBJECTS) wxchartviewer.o
	g++ $(CXXFLAGS) -o myapp wxchartviewer.o userfile.cpp -I ../include/ $(OBJECTS) $(TEST_FLAGS) $(WX_FLAGS) $(WX_CHART_DIR_FLAGS);

teleconwxapp.o: ../include/teleconwxapp.h teleconwxapp.cpp
	g++ $(CXXFLAGS) -c teleconwxapp.cpp -I ../include/ $(WX_FLAGS) $(WX_CHART_DIR_FLAGS)

telecon.o: ../include/telecon.h telecon.cpp
	g++ $(CXXFLAGS) -c telecon.cpp -I ../include/ $(WX_FLAGS) $(WX_CHART_DIR_FLAGS)

teleconchart.o: ../include/teleconchart.h teleconchart.cpp
	g++ $(CXXFLAGS) -c teleconchart.cpp -I ../include/ $(WX_FLAGS) $(WX_CHART_DIR_FLAGS)

teleconwxcontrolswindow.o: ../include/teleconwxcontrolswindow.h teleconwxcontrolswindow.cpp
	g++ $(CXXFLAGS) -c teleconwxcontrolswindow.cpp -I ../include/ $(WX_FLAGS) $(WX_CHART_DIR_FLAGS)

teleconcontrols.o: ../include/teleconcontrols.h teleconcontrols.cpp
	g++ $(CXXFLAGS) -c teleconcontrols.cpp -I ../include/ $(WX_FLAGS) $(WX_CHART_DIR_FLAGS)

# teleconframe.o: ../include/teleconframe.h teleconframe.cpp
# 	g++ $(CXXFLAGS) -c teleconframe.cpp -I ../include/ $(WX_FLAGS) $(WX_CHART_DIR_FLAGS)

teleconwindow.o: ../include/teleconwindow.h teleconwindow.cpp
	g++ $(CXXFLAGS) -c teleconwindow.cpp -I ../include/ $(WX_FLAGS) $(WX_CHART_DIR_FLAGS)

teleconwxwindow.o: ../include/teleconwindow.h teleconwxwindow.cpp
	g++ $(CXXFLAGS) -c teleconwxwindow.cpp -I ../include/ $(WX_FLAGS) $(WX_CHART_DIR_FLAGS)

teleconrealtimechart.o: ../include/teleconrealtimechart.h teleconrealtimechart.cpp 
	g++ $(CXXFLAGS) -c teleconrealtimechart.cpp -I ../include/ $(WX_FLAGS) $(WX_CHART_DIR_FLAGS)

teleconwxplot.o: teleconwxplot.cpp ../include/teleconwxplot.h
	g++ $(CXXFLAGS) -c teleconwxplot.cpp -I ../include/ $(WX_FLAGS) $(WX_CHART_DIR_FLAGS)

teleconwxplotxy.o: teleconwxplotxy.cpp ../include/teleconwxplotxy.h
	g++ $(CXXFLAGS) -c teleconwxplotxy.cpp -I ../include/ $(WX_FLAGS) $(WX_CHART_DIR_FLAGS)

teleconwxchart.o: teleconwxchart.cpp ../include/teleconwxchart.h
	g++ $(CXXFLAGS) -c teleconwxchart.cpp -I ../include/ $(WX_FLAGS) $(WX_CHART_DIR_FLAGS)

teleconwxlineplot.o: teleconwxlineplot.cpp ../include/teleconwxlineplot.h
	g++ $(CXXFLAGS) -c teleconwxlineplot.cpp -I ../include/ $(WX_FLAGS) $(WX_CHART_DIR_FLAGS)

teleconwxscatterplot.o: teleconwxscatterplot.cpp ../include/teleconwxscatterplot.h
	g++ $(CXXFLAGS) -c teleconwxscatterplot.cpp -I ../include/ $(WX_FLAGS) $(WX_CHART_DIR_FLAGS)

# start.o: start.cpp ../include/start.h
# 	g++ $(CXXFLAGS) -c start.cpp -I ../include/ $(WX_FLAGS) $(WX_CHART_DIR_FLAGS)

wxchartviewer.o: ~/git-repos/wxchartdir/wxdemo/common/wxchartviewer.cpp
	g++ $(CXXFLAGS) -c ~/git-repos/wxchartdir/wxdemo/common/wxchartviewer.cpp $(WX_FLAGS) $(WX_CHART_DIR_FLAGS)

# telecon.o: telecon.h telecon.cpp mathplot.o 
# 	g++ -c telecon.cpp mathplot.o $(WX_FLAGS) $(WX_CHART_DIR_FLAGS) 


mathplot.o: $(WX_MATHPLOT_PATH) ~/git-repos/telecon/lib/wxMathPlot/include/mathplot.h
	g++ -c $(WX_MATHPLOT_PATH) $(WX_FLAGS) $(WX_MATHPLOT_FLAGS) 




	
clean: 
	rm *.o myapp