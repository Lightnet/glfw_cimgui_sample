# glfw_cimgui_sample

# licenses: MIT

# Information:
  Very simple glfw and cimgui in c lanugage code with cmake build.

  Using the msys64 compiler for small dev build on windows 64 bit.

  There are two github repo to build this sample application.

  Note you might need to install some packages to support it. There are at least +5 pacakges needed to install. Can't remember better search engine to find and install.

# Toolchain:
- msys64\mingw64\bin

## build.bat
```
@echo off
setlocal
set MSYS2_PATH=C:\msys64\mingw64\bin
set PATH=%MSYS2_PATH%;%PATH%

:: Verify paths exist
if not exist "%MSYS2_PATH%\gcc.exe" (
    echo Error: MSYS2 gcc not found at %MSYS2_PATH%\gcc.exe
    exit /b 1
)
if not exist "%MSYS2_PATH%\g++.exe" (
    echo Error: MSYS2 g++ not found at %MSYS2_PATH%\g++.exe
    exit /b 1
)
if not exist "%VULKAN_SDK%\Bin" (
    echo Warning: Vulkan SDK not found at %VULKAN_SDK%\Bin
)

:: Create build directory if it doesn't exist
if not exist build mkdir build
cd build

:: Run CMake configuration and log both stdout and stderr
echo Running CMake configuration...
cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=%MSYS2_PATH%\gcc.exe -DCMAKE_CXX_COMPILER=%MSYS2_PATH%\g++.exe > cmake_log.txt 2>&1
if %ERRORLEVEL% neq 0 (
    echo CMake configuration failed. Check cmake_log.txt for details.
    exit /b %ERRORLEVEL%
)

:: Run CMake build and append to the log
echo Running CMake build...
cmake --build . --config Debug >> cmake_log.txt 2>&1
if %ERRORLEVEL% neq 0 (
    echo CMake build failed. Check cmake_log.txt for details.
    exit /b %ERRORLEVEL%
)

echo Build completed successfully. Log saved to build\cmake_log.txt
endlocal
```

# Notes:

```
ImGui_Begin > igBegin 
```
 There some convert change to reflect c format for easy to read. The prefixed ImGui_"name" for c++ for c is ig"name". File easy found in cimgui.cpp for api.


# Credits:
- https://github.com/peko/cimgui-c-example
- https://github.com/cimgui/cimgui
- https://github.com/WEREMSOFT/c99-raylib-cimgui-template
- 