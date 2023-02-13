WX_FLAGS = `wx-config --libs --cxxflags`
WX_CHART_DIR_FLAGS = -I ~/git-repos/wxchartdir/include -I ~/git-repos/wxchartdir/wxdemo/common -L ~/git-repos/wxchartdir/lib/linux64/ -l chartdir
WX_MATHPLOT_FLAGS = -I ~/git-repos/telecon/lib/wxMathPlot/include
WX_MATHPLOT_PATH = ~/git-repos/telecon/lib/wxMathPlot/src/mathplot.cpp

# Run export LD_LIBRARY_PATH=~/git-repos/wxchartdir/lib/linux64/
# PROJ_DIR = ~/git-repos/telecon/



teleconapp:  teleconapp.h teleconapp.cpp telecon.o mathplot.o
	g++ -o teleconapp ~/git-repos/wxchartdir/wxdemo/common/wxchartviewer.cpp teleconapp.cpp realtimemultichart.cpp  telecon.o mathplot.o $(WX_FLAGS) $(WX_CHART_DIR_FLAGS);

test: testapp
	LD_LIBRARY_PATH=~/git-repos/wxchartdir/lib/linux64/ ./test

testapp: test.cpp mathplot.o realtimemultichart.h realtimemultichart.cpp
	g++ -o test ~/git-repos/wxchartdir/wxdemo/common/wxchartviewer.cpp test.cpp realtimemultichart.cpp mathplot.o $(WX_FLAGS) $(WX_CHART_DIR_FLAGS);


telecon.o: telecon.h telecon.cpp mathplot.o 
	g++ -c telecon.cpp mathplot.o $(WX_FLAGS) $(WX_CHART_DIR_FLAGS) 


mathplot.o: $(WX_MATHPLOT_PATH) ../lib/wxMathPlot/include/mathplot.h
	g++ -c $(WX_MATHPLOT_PATH) $(WX_FLAGS) $(WX_MATHPLOT_FLAGS) 

run: teleconapp
	LD_LIBRARY_PATH=~/git-repos/wxchartdir/lib/linux64/ ./teleconapp



	
clean: 
	rm *.o teleconapp