# telecon
A cross-platform near real-time telemetry and control GUI for C++ written using the [wxWidgets](https://www.wxwidgets.org/) library.

## Prerequisite list
Telecon projects use three prerequisite packages: wxWidgets, wxMathPlot, and wxChartDir. Not every project uses every package. If using an existing project, all packages will already be set up except for wxWidgets; if creating a new project, see the steps below.

## Necessary prerequisite: wxWidgets
### Linux
On most Linux distributions, wxWidgets packages are available in system repositories under the name "wxGTK". Note that to develop applications using wxWidgets you may need to install the "development" packages and not just the libraries needed for running the applications using wxWidgets.

For example, to install wxWidgets 3.0 on Ubuntu 20.04 LTS, you need to run the command `apt get libwxgtk3.0-gtk3-dev` on a terminal.

### Windows
- [Download](https://www.wxwidgets.org/downloads/) the latest stable binary zip files for wxWidgets (v3.2.1 used here).
    - You must download the "header files."
    - Then choose either 32-bit or 64-bit app environments to download the corresponding "development files", "release DLLs", and "release DLL PDB files".
- Unzip the files into `C:\wx\3.2.1\`
    - The "header files" zip is unzipped as the `include` subdirectory.
    - The zipped "development files" contain the `build` and `lib` subdirectories along with the `wxWidgets.prop` Visual Studio proerty sheet file.
    - The "release DLLs" and "release DLL PDB files" also unzip into the `lib` subdirectory adding additional files to it.
- If using DLLs, append the location of wxWidget's DLL files to the `Path` or `PATH` environment variable. For example, for wxWidgets 3.2.1 64-bit, the default location of the DLL files is `C:\wx\3.2.1\lib\vc14x_x64_dll\`. This allows the DLLs to be found by your application during runtime.

## Included prerequisite: wxMathPlot library
This project ships with a **modified** copy of the wxMathPlot library. It is an open-source scientific plotting library for wxWidgets. You can find it in `lib/wxMathPlot/` and is distributed under the wxWindows license. From June 2007 the project is maintained by [Davide Rondini](mailto:cdron77@users.sourceforge.net), who carries on the original work by [David Schalig](mailto:mrhill@users.sourceforge.net).
The authors can be contacted via the [wxMathPlot's homepage](https://sourceforge.net/projects/wxmathplot).

## Included prerequisite: wxChartDir
This project includes wxChartDir as a submodule. It provides components for the integration and use of the commercial C++ library ChartDirector, available at https://github.com/utelle/wxchartdir.
Use the --recurse-submodules flag when cloning or checking out branches to ensure that wxChartDir is modified appropriately.

## Setting up the development environment
### Windows (Visual Studio 2019 or above)
- Install wxWidgets according to the instructions above.
- Create a new empty project.
- Go to `View|Property Manager|Add Existing Property Sheet` and add `wxWidgets.prop` (from the downloaded development files in wxWidget's root directory) to it.
- Change the `Project|Properties|Linker|System|Subsystem|` property to `Windows`.
- Set `Project|Properties|Configuration Properties|Advanced|Character Set` to `Use Unicode Character Set`.
- Set `Project|Properties|Configuration Properties|General|C++ Language Standard` to `ISO C++ 17 Standard`, if desired.
- To `Project|Properties|C/C++|General|Additional Include Directories|`, append `$(SolutionDir)..\include`, which is where you should place any needed header files. You can use a subdirectory of include instead, if desired.
If using wxMathPlot:
- To `Project|Properties|C/C++|General|Additional Include Directories|`, append `$(SolutionDir)..\lib\wxMathPlot\include`.
- In the Solution Explorer, add `telecon\lib\wxMathPlot\include\mathplot.h` to Header Files
- In the Solution Explorer, add `telecon\lib\wxMathPlot\src\mathplot.cpp` to Source Files
If using wxChartDir:
- To `Project|Properties|C/C++|General|Additional Include Directories|`, append `$(SolutionDir)..\lib\wxchartdir\include` and `$(SolutionDir)..\lib\wxchartdir\wxdemo\common`
- To `Project|Properties|Linker|General|Additional Linker Directories|`, append `$(SolutionDir)..\lib\wxchartdir\lib\win64`
- To `Project|Properties|Linker|Input|Additional Dependencies|`, append `chartdir70.lib`
- In the Solution Explorer, add `telecon\lib\wxchartdir\wxdemo\common\wxchartviewer.cpp` to Source Files

## Coding tips
- Be sure to include the headers (`wx/wxp.h`) or precompiled headers (`wx/wxprec.h`) as necessary to the main source file.
- Also remember that every app should define a new class derived from the `wxApp` with an overridden `OnInit()` function to initialize the program.

