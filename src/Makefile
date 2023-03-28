WX_FLAGS = `wx-config --libs --cxxflags`
WX_CHART_DIR_FLAGS = -I ~/git-repos/wxchartdir/include -I ~/git-repos/wxchartdir/wxdemo/common -L ~/git-repos/wxchartdir/lib/linux64/ -l chartdir
WX_MATHPLOT_FLAGS = -I ~/git-repos/telecon/lib/wxMathPlot/include
WX_MATHPLOT_PATH = ~/git-repos/telecon/lib/wxMathPlot/src/mathplot.cpp

TEST_FLAGS = -I ../include/

# Run export LD_LIBRARY_PATH=~/git-repos/wxchartdir/lib/linux64/
# PROJ_DIR = ~/git-repos/telecon/

OBJECTS = teleconwindow.o teleconrealtimechart.o teleconplot.o teleconlineplot.o teleconscatterplot.o teleconchart.o telecon.o teleconframe.o



# base: baseapp
# 	LD_LIBRARY_PATH=~/git-repos/wxchartdir/lib/linux64/ ./base

# baseapp: ../include/base.h base.cpp wxchartviewer.o $(OBJECTS) userfile.cpp
# 	g++ -o base wxchartviewer.o base.cpp userfile.cpp -I ../include/ $(OBJECTS) $(TEST_FLAGS) $(WX_FLAGS) $(WX_CHART_DIR_FLAGS);

run: myapp
	LD_LIBRARY_PATH=~/git-repos/wxchartdir/lib/linux64/ ./myapp

myapp: userfile.cpp $(OBJECTS) wxchartviewer.o
	g++ -o myapp wxchartviewer.o userfile.cpp -I ../include/ $(OBJECTS) $(TEST_FLAGS) $(WX_FLAGS) $(WX_CHART_DIR_FLAGS);

telecon.o: ../include/telecon.h telecon.cpp
	g++ -c telecon.cpp -I ../include/ $(WX_FLAGS) $(WX_CHART_DIR_FLAGS)

teleconchart.o: ../include/teleconchart.h teleconchart.cpp
	g++ -c teleconchart.cpp -I ../include/ $(WX_FLAGS) $(WX_CHART_DIR_FLAGS)

teleconframe.o: ../include/teleconframe.h teleconframe.cpp
	g++ -c teleconframe.cpp -I ../include/ $(WX_FLAGS) $(WX_CHART_DIR_FLAGS)

teleconwindow.o: ../include/teleconwindow.h teleconwindow.cpp
	g++ -c teleconwindow.cpp -I ../include/ $(WX_FLAGS) $(WX_CHART_DIR_FLAGS)

teleconrealtimechart.o: ../include/teleconrealtimechart.h teleconrealtimechart.cpp ../include/teleconplot.h
	g++ -c teleconrealtimechart.cpp -I ../include/ $(WX_FLAGS) $(WX_CHART_DIR_FLAGS)

teleconplot.o: teleconplot.cpp ../include/teleconplot.h
	g++ -c teleconplot.cpp -I ../include/ $(WX_FLAGS) $(WX_CHART_DIR_FLAGS)

teleconlineplot.o: teleconlineplot.cpp ../include/teleconlineplot.h
	g++ -c teleconlineplot.cpp -I ../include/ $(WX_FLAGS) $(WX_CHART_DIR_FLAGS)

teleconscatterplot.o: teleconscatterplot.cpp ../include/teleconscatterplot.h
	g++ -c teleconscatterplot.cpp -I ../include/ $(WX_FLAGS) $(WX_CHART_DIR_FLAGS)

# start.o: start.cpp ../include/start.h
# 	g++ -c start.cpp -I ../include/ $(WX_FLAGS) $(WX_CHART_DIR_FLAGS)

wxchartviewer.o: ~/git-repos/wxchartdir/wxdemo/common/wxchartviewer.cpp
	g++ -c ~/git-repos/wxchartdir/wxdemo/common/wxchartviewer.cpp $(WX_FLAGS) $(WX_CHART_DIR_FLAGS)

# telecon.o: telecon.h telecon.cpp mathplot.o 
# 	g++ -c telecon.cpp mathplot.o $(WX_FLAGS) $(WX_CHART_DIR_FLAGS) 


mathplot.o: $(WX_MATHPLOT_PATH) ~/git-repos/telecon/lib/wxMathPlot/include/mathplot.h
	g++ -c $(WX_MATHPLOT_PATH) $(WX_FLAGS) $(WX_MATHPLOT_FLAGS) 




	
clean: 
	rm *.o myapp