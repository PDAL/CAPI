@echo off

:: This script assumes that cmake is in PATH
:: TODO Auto-detect latest platform
set SCRIPT_DIR=%~dp0
if not defined GENERATOR set GENERATOR=Visual Studio 15 2017 Win64
if not defined COMPILER_ID set COMPILER_ID=vc.15
if not defined BUILD_TYPE set BUILD_TYPE=Release

set BUILD_DIR=%SCRIPT_DIR%\build\windows.amd64.%COMPILER_ID%

if exist "%BUILD_DIR%\pdal-c.sln" (
	pushd "%BUILD_DIR%"
) else (
	mkdir "%BUILD_DIR%"
	pushd "%BUILD_DIR%"

	mkdir install

	cmake -G "%GENERATOR%" ^
		-DCMAKE_BUILD_TYPE=%BUILD_TYPE% ^
		-DCMAKE_PREFIX_PATH=%OSGEO4W_ROOT% ^
		-DCMAKE_INSTALL_PREFIX=./install ^
		../..
)

:: Build and install solution
cmake --build . --target INSTALL --config %BUILD_TYPE%

popd

