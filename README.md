# telecon
A cross-platform near real-time telemetry and control GUI for C++ written using the [wxWidgets](https://www.wxwidgets.org/) library.

## Necessary prerequisite: wxWidgets
### Linux
On most Linux distributions, wxWidgets packages are available in system repositories under the name "wxGTK". Note that to develop applications using wxWidgets you may need to install the "development" packages and not just the libraries needed for running the applications using wxWidgets.

For example, to install wxWidgets 3.0 on Ubuntu 20.04 LTS, you need to run the command `apt get libwxgtk3.0-gtk3-dev` on a terminal.

### Windows
- [Download](https://www.wxwidgets.org/downloads/) the latest stable binary zip files for wxWidgets (v3.1.6 used here).
    - You must download the "header files."
    - Then choose either 32-bit or 64-bit app environments to download the corresponding "development files", "release DLLs", and "release DLL PDB files".
- Unzip the files into `C:\wx\3.1.6\`
    - The "header files" zip is unziped as the `include` subdirectory.
    - The zipped "development files" contain the `build` and `lib` subdirectories along with the `wxWdigets.prop` Visual Studio proerty sheet file.
    - The "release DLLs" and "release DLL PDB files" also unzip into the `lib` subdirectory adding additional files to it.
- To avoid having to hard-code the install directory of wxWidgets into your applications, define `wxwin` as an environment variable containing the path (`C:\wx\3.1.6\`) to the files we just downloaded and unziped.
- If using DLLs, append the location of wxWidget's DLL files to the `Path` or `PATH` environment variable. For example, for wxWidgets 3.1.6, the default location of the DLL files is `C:\wx\3.1.6\lib\vc14x_dll\`. This allows the DLLs to be found by your application during runtime.

## Included prerequisite: wxMathPlot library
This project ships with a **modified** copy of the wxMathPlot library. It is an open-source scientific plotting library for wxWidgets. You can find it in `lib/wxMathPlot/` and is distributed under the wxWindows license. From June 2007 the project is maintained by [Davide Rondini](mailto:cdron77@users.sourceforge.net), who carries on the original work by [David Schalig](mailto:mrhill@users.sourceforge.net).
The authors can be contacted via the [wxMathPlot's homepage](https://sourceforge.net/projects/wxmathplot).

## Setting up the development environment
### Windows (Visual Studio 2019 or above)
- Create a new empty project.
- Go to `View|Property Manager|Add Existing Property Sheet` and add `wxWidgets.prop` (from the downloaded development files in wxWidget's root directory) to it.
- Change the `Project|Properties|Linker|System|Subsystem|` property to `Windows`.
- Set `Project|Properties|Configuration Properties|Advanced|Character Set` to `Use Unicode Character Set`.
- To `Project|Properties|C/C++|General|Additional Include Directories|`, append `$(SolutionDir)..\include` and `$(SolutionDir)..\lib\wxMathPlot\include`.
- To `Project|Properties|Linker|General|Additional Linker Directories|`, append `$(SolutionDir)..\lib\wxMathPlot\bin`.

## Coding tips
- Be sure to include the headers (`wx/wxp.h`) or precompiled headers (`wx/wxprec.h`) as necessary to the main source file.
- Also remember that every app should define a new class derived from the `wxApp` with an overridden `OnInit()` function to initialize the program.

