# telecon
A cross-platform near real-time telemetry and control GUI for C++ written using the [wxWidgets](https://www.wxwidgets.org/) library.

## Installing prerequisite: wxWidgets
### Linux
On most Linux distributions, wxWidgets packages are available in system repositories under the name "wxGTK". Note that to develop applications using wxWidgets you may need to install the "development" packages and not just the libraries needed for running the applications using wxWidgets.

For example, to install wxWidgets 3.0 on Ubuntu 20.04 LTS, you need to run the command `apt get libwxgtk3.0-gtk3-dev` on a terminal.

### Mac OS
A native post of wxWidgets for Mac OS is available on MacPorts. For example, to install wxWidgets 3.2 on MacoS, you need to run the command `sudo port install wxWidgets-3.2` on a terminal.

### Windows
- [Download](https://www.wxwidgets.org/downloads/) the latest stable binary zip files for wxWidgets (v3.1.6 used here).
    - You must download the "header files."
    - Then choose either 32-bit or 64-bit app environments to download the corresponding "development files", "release DLLs", and "release DLL PDB files".
- Unzip the files into `C:\wx\3.1.6\`
    - The "header files" zip is unziped as the `include` subdirectory.
    - The zipped "development files" contain the `build` and `lib` subdirectories along with the `wxWdigets.prop` Visual Studio proerty sheet file.
    - The "release DLLs" and "release DLL PDB files" also unzip into the `lib` subdirectory adding additional files to it.
- To avoid having to hard-code the install directory of wxWidgets into your applications, define `wxwin` as an environment variable containing the path (`C:\wx\3.1.6\`) to the files we just downloaded and unziped.

## Setting up the development environment
### Windows (Visual Studio 2019 or above)
- Create a new empty project.
- Go to `View|Property Manager|Add Existing Property Sheet` and add `wxWidgets.prop` (from the downloaded development files in wxWidget's root directory) to it.
- Change the `Project|Properties|Linker|System|Subsystem|` property to `Windows`.
- Be sure to include the headers (`wx/wxp.h`) or precompiled headers (`wx/wxprec.h`) as necessary to the main source file.
- Also remember that every app should define a new class derived from the `wxApp` with an overridden `OnInit()` function to initialize the program.

