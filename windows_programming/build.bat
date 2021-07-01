@echo off
if not exist build MKDIR build

rem REFERENCES:https://docs.microsoft.com/en-us/cpp/build/reference/compiler-options-listed-alphabetically?view=vs-2019

set SOURCES=^
..\src\main.c

rem ==========              COMPILER(MSVC)            ==========     
rem ============================================================
set MSVC_COMMON_FLAGS=^
-nologo

set MSVC_WARNINGS=^
-wd4013 ^
-wd4057 ^
-wd4100 ^
-wd4101 ^
-wd4142 ^
-wd4189 ^
-wd4204 ^
-wd4244 ^
-wd4312 ^
-wd4456 ^
-wd4700 ^
-wd4706 ^
-wd4996

set MSVC_FLAGS=^
%MSVC_COMMON_FLAGS% ^
-MT ^
-GR ^
-Od ^
-WX ^
-FC ^
-Z7 ^
%MSVC_WARNINGS%

set INCUDE_PATHS=^
-IF:\Dev\Common

rem ==========             LINKER(MSVC)               ==========     
rem ============================================================
set LINKER_FLAGS=^
-incremental:no ^
-opt:ref

set LIBRARIES=ws2_32.lib

rem **                       START BUILD                      **
rem ************************************************************

set PATH=F:\Dev\Practice\windows_programming\build;%PATH%
pushd build

cl %MSVC_FLAGS% %INCUDE_PATHS% %SOURCES% /link %LIBRARIES%

popd