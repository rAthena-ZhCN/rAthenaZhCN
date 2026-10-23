@echo off
rem rAthena x64 Release build script (CMake + Ninja + MSVC)
rem Usage: build_x64.bat            -> build all targets
rem        build_x64.bat map-server -> build one target
setlocal
cd /d "%~dp0"
set "VSWHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
if not exist "%VSWHERE%" ( echo [ERROR] vswhere.exe not found. Install Visual Studio C++ tools. & pause & exit /b 1 )
for /f "usebackq tokens=*" %%i in (`"%VSWHERE%" -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath`) do set "VSPATH=%%i"
if not defined VSPATH ( echo [ERROR] Visual Studio C++ tools not found. & pause & exit /b 1 )
call "%VSPATH%\VC\Auxiliary\Build\vcvars64.bat" >nul
if errorlevel 1 ( echo [ERROR] vcvars64.bat failed. & pause & exit /b 1 )
set "CMAKE=%VSPATH%\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe"
set "NINJA=%VSPATH%\Common7\IDE\CommonExtensions\Microsoft\CMake\Ninja\ninja.exe"
set "BUILDDIR=out\build\x64-Release"
if not exist "%BUILDDIR%\CMakeCache.txt" (
  echo [INFO] Configuring %BUILDDIR% ...
  "%CMAKE%" -S . -B "%BUILDDIR%" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_MAKE_PROGRAM="%NINJA%"
  if errorlevel 1 goto :fail
)
if "%~1"=="" ( set "TARGETS=" ) else ( set "TARGETS=--target %*" )
echo [INFO] Building %TARGETS% ...
"%CMAKE%" --build "%BUILDDIR%" %TARGETS% -- -j 16
if errorlevel 1 goto :fail
echo.
echo [OK] Build finished. Binaries are in the source root.
pause
exit /b 0
:fail
echo.
echo [ERROR] Build failed. Check the output above.
pause
exit /b 1
