@echo off

:: This script assumes that cmake is in PATH
:: TODO Auto-detect latest platform
set SCRIPT_DIR=%~dp0
if not defined GENERATOR set GENERATOR=Visual Studio 14 2015 Win64
if not defined COMPILER_ID set COMPILER_ID=vc.14
if not defined BUILD_TYPE set BUILD_TYPE=Release

mkdir "%SCRIPT_DIR%\build\windows.amd64.%COMPILER_ID%.%BUILD_TYPE%"
pushd "%SCRIPT_DIR%\build\windows.amd64.%COMPILER_ID%.%BUILD_TYPE%"

mkdir install

cmake -G "%GENERATOR%" ^
	-DCMAKE_BUILD_TYPE=%BUILD_TYPE% ^
	-DCMAKE_PREFIX_PATH=%OSGEO4W_ROOT% ^
	-DCMAKE_DEBUG_POSTFIX=d ^
	-DCMAKE_INSTALL_PREFIX=./install ^
	../..

:: Build and install solution
cmake --build . --target INSTALL --config %BUILD_TYPE%

popd

