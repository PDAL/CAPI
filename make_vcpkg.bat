@echo off

:: This script assumes that cmake is in PATH
:: TODO Auto-detect latest platform
set SCRIPT_DIR=%~dp0

::cmake .. "-DCMAKE_TOOLCHAIN_FILE=D:\src\vcpkg\scripts\buildsystems\vcpkg.cmake" -G "Sublime Text 2 - Ninja" -DVCPKG_TARGET_TRIPLET=x86-windows-static -DCMAKE_BUILD_TYPE=Debug

if not defined TOOLCHAIN set TOOLCHAIN=C:\workspace\thirdparty\vcpkg\scripts\buildsystems\vcpkg.cmake
if not defined BUILD_TYPE set BUILD_TYPE=Release
if not defined TRIPLET=x64-windows

set BUILD_DIR=%SCRIPT_DIR%\build\%TRIPLET%

if exist "%BUILD_DIR%\pdal-c.sln" (
	pushd "%BUILD_DIR%"
) else (
	mkdir "%BUILD_DIR%"
	pushd "%BUILD_DIR%"

	mkdir install

	cmake ../.. ^
		-DCMAKE_BUILD_TYPE=%BUILD_TYPE% ^
		-DCMAKE_TOOLCHAIN_FILE=%TOOLCHAIN% ^
		-DVCPKG_TARGET_TRIPLET=%TRIPLET% ^
		-DCMAKE_GENERATOR_PLATFORM=x64

)

:: Build and install solution
cmake --build . --target INSTALL --config %BUILD_TYPE%

popd

