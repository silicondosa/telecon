WX_FLAGS = `wx-config --libs --cxxflags`
WX_CHART_DIR_FLAGS = -I ~/git-repos/wxchartdir/include -I ~/git-repos/wxchartdir/wxdemo/common -L ~/git-repos/wxchartdir/lib/linux64/ -l chartdir
WX_MATHPLOT_FLAGS = -I ../lib/wxMathPlot/include
# WX_MATHPLOT_PATH = ../lib/wxMathPlot/src/mathplot.cpp

# Run export LD_LIBRARY_PATH=~/git-repos/wxchartdir/lib/linux64/



teleconapp: teleconapp.h teleconapp.cpp telecon.o mathplot.o
	g++ -o teleconapp ~/git-repos/wxchartdir/wxdemo/common/wxchartviewer.cpp teleconapp.cpp telecon.o mathplot.o $(WX_FLAGS) $(WX_CHART_DIR_FLAGS);

telecon.o: telecon.h telecon.cpp mathplot.o
	g++ -c telecon.cpp mathplot.o $(WX_FLAGS) $(WX_CHART_DIR_FLAGS) 


mathplot.o: ../lib/wxMathPlot/src/mathplot.cpp ../lib/wxMathPlot/include/mathplot.h
	g++ -c ../lib/wxMathPlot/src/mathplot.cpp $(WX_FLAGS) $(WX_MATHPLOT_FLAGS) 

run: teleconapp
	LD_LIBRARY_PATH=~/git-repos/wxchartdir/lib/linux64/ ./teleconapp



	
clean: 
	rm *.o teleconapp