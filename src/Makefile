WX_FLAGS = `wx-config --libs --cxxflags`
WX_CHART_DIR_FLAGS = -I ../lib/wxchartdir/include -I ../lib/wxchartdir/wxdemo/common -L ../lib/wxchartdir/lib/linux64/ -l chartdir
# WX_MATHPLOT_FLAGS = -I ~/git-repos/telecon/lib/wxMathPlot/include
# WX_MATHPLOT_PATH = ~/git-repos/telecon/lib/wxMathPlot/src/mathplot.cpp

TEST_FLAGS = -I ../include/

OBJECTS = teleconwindow.o teleconrealtimechart.o teleconwxplot.o \
		teleconwxlineplot.o teleconwxscatterplot.o teleconchart.o telecon.o \
		teleconwxchart.o teleconwxwindow.o teleconwxapp.o \
		teleconwxcontrolswindow.o teleconcontrols.o teleconphaseportrait.o \
		telecondatachart.o teleconrasterplot.o teleconwxrasterplot.o \
		teleconwxphaseportraitplot.o symbolstyle.o linestyle.o teleconlineplot.o \
		teleconscatterplot.o teleconimplchartdir.o teleconchartimplchartdir.o \
		teleconrealtimechartimplchartdir.o teleconwindowimplchartdir.o telecondatachartimplchartdir.o


CFLAGS =

run: myapp
	LD_LIBRARY_PATH=~/git-repos/wxchartdir/lib/linux64/ ./myapp

myapp: userfile.cpp $(OBJECTS) wxchartviewer.o
	g++ $(CFLAGS) -o myapp wxchartviewer.o userfile.cpp -I ../include/ $(OBJECTS) $(TEST_FLAGS) $(WX_FLAGS) $(WX_CHART_DIR_FLAGS);

.cpp.o:
	g++ ${CFLAGS} -I ../include/ -c $< $(WX_FLAGS) $(WX_CHART_DIR_FLAGS)

wxchartviewer.o: ~/git-repos/wxchartdir/wxdemo/common/wxchartviewer.cpp
	g++ $(CFLAGS) -c ~/git-repos/wxchartdir/wxdemo/common/wxchartviewer.cpp $(WX_FLAGS) $(WX_CHART_DIR_FLAGS)

clean: 
	rm *.o myapp