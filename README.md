# telecon
A cross-platform near real-time telemetry and control GUI for C++ written using the [wxWidgets](https://www.wxwidgets.org/) library.

## Prerequisite list
Telecon projects use four prerequisite libraries: wxWidgets, wxMathPlot, wxChartDir, and ChartDirector. Not every project uses every library. See the steps below to set up the libraries.

## Necessary prerequisite: wxWidgets
### Linux
Install wxWidgets 3.2 from https://docs.codelite.org/wxWidgets/repo320/. Note that to develop applications using wxWidgets you may need to install the "development" packages and not just the libraries needed for running the applications using wxWidgets.  

After installation, check that the `wx-config` command works in your terminal. If it does, navigate into `telecon/src/` and run `make`  

### Windows
- [Download](https://www.wxwidgets.org/downloads/) the latest stable binary zip files for wxWidgets (v3.2.1 used here).
    - You must download the "header files."
    - Then choose either 32-bit or 64-bit app environments to download the corresponding "development files", "release DLLs", and "release DLL PDB files".
- Unzip the files into `C:\wx\3.2.1\`
    - The "header files" zip is unzipped as the `include` subdirectory.
    - The zipped "development files" contain the `build` and `lib` subdirectories along with the `wxWidgets.prop` Visual Studio proerty sheet file.
    - The "release DLLs" and "release DLL PDB files" also unzip into the `lib` subdirectory adding additional files to it.
- To avoid having to hard-code the install directory of wxWidgets into your applications, define wxwin as an environment variable containing the path (C:\wx\3.2.1\) to the files we just downloaded and unzipped.
- If using DLLs, append the location of wxWidget's DLL files to the `Path` or `PATH` environment variable. For example, for wxWidgets 3.2.1 64-bit, the default location of the DLL files is `C:\wx\3.2.1\lib\vc14x_x64_dll\`. This allows the DLLs to be found by your application during runtime.

## Included prerequisite: wxMathPlot library
This project ships with a **modified** copy of the wxMathPlot library. It is an open-source scientific plotting library for wxWidgets. You can find it in `lib/wxMathPlot/` and is distributed under the wxWindows license. From June 2007 the project is maintained by [Davide Rondini](mailto:cdron77@users.sourceforge.net), who carries on the original work by [David Schalig](mailto:mrhill@users.sourceforge.net).
The authors can be contacted via the [wxMathPlot's homepage](https://sourceforge.net/projects/wxmathplot).

## Included prerequisite: wxChartDir/ChartDirector
This project includes wxChartDir as a submodule. It provides components for the integration and use of the commercial C++ library ChartDirector, available at https://github.com/utelle/wxchartdir.
Use the --recurse-submodules flag when cloning or checking out branches to ensure that wxChartDir is modified appropriately.

wxChartDir includes the trial version of [ChartDirector](https://www.advsofteng.com/index.html), a versatile charting library that provides support for many different types of plots.

## Setting up the development environment
### Using the existing projects
- The Telecon project is already configured for use on a 64-bit Windows machine
- Only wxWidgets must be installed (see above)

### Creating a new project (Visual Studio 2022 or above)
- Install wxWidgets according to the instructions above.
- Create a new empty project.
- Go to `View|Property Manager|Add Existing Property Sheet` and add `wxWidgets.prop` (from the downloaded development files in wxWidget's root directory) to it. Then edit the .vcxproj file to make the import path relative to the wxwin environment variable, if desired.
- Set `Project|Properties|Configuration Properties|Advanced|Character Set` to `Use Unicode Character Set`.
- Set `Project|Properties|Configuration Properties|General|C++ Language Standard` to `ISO C++ 17 Standard`.
- To `Project|Properties|C/C++|General|Additional Include Directories|`, append `$(SolutionDir)..\include`, which is where you should place any needed header files. You can use a subdirectory of include instead, if desired.
- Add any needed source files (.c or .cpp) to `/src` or a subdirectory as needed

If using wxMathPlot:
- To `Project|Properties|C/C++|General|Additional Include Directories|`, append `$(SolutionDir)..\lib\wxMathPlot\include`.
- In the Solution Explorer, add `telecon\lib\wxMathPlot\include\mathplot.h` to Header Files
- In the Solution Explorer, add `telecon\lib\wxMathPlot\src\mathplot.cpp` to Source Files

If using wxChartDir/ChartDirector:
- To `Project|Properties|C/C++|General|Additional Include Directories|`, append `$(SolutionDir)..\lib\wxchartdir\include` and `$(SolutionDir)..\lib\wxchartdir\wxdemo\common`
- To `Project|Properties|Linker|General|Additional Linker Directories|`, append `$(SolutionDir)..\lib\wxchartdir\lib\win64`. Replace win64 with your target platform if needed
- To `Project|Properties|Linker|Input|Additional Dependencies|`, append `chartdir70.lib`
- In the Solution Explorer, add `telecon\lib\wxchartdir\wxdemo\common\wxchartviewer.cpp` to Source Files
- When running you application, you will need to link the ChartDirector DLL file. This can be done in several ways. One method, used in the included project, is to copy the DLL to the output folder by setting `Project|Properties|Build Events|Post-Build Event|Command Line` to `xcopy /y "$(SolutionDir)..\lib\wxchartdir\lib\win64\chartdir70.dll" $(OutDir)`; replace win64 with your target platform if needed. Another method is to add the DLL file to the Path environment variable.

## Coding tips
- Be sure to include the headers (`wx/wxp.h`) or precompiled headers (`wx/wxprec.h`) as necessary to the main source file.
- Also remember that every app should define a new class derived from the `wxApp` with an overridden `OnInit()` function to initialize the program.