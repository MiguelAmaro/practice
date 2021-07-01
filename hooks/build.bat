@echo off
if not exist build MKDIR build

rem REFERENCES:https://docs.microsoft.com/en-us/cpp/build/reference/compiler-options-listed-alphabetically?view=vs-2019

rem ************************************************************
rem ************************************************************
rem **                                                        **
rem **                       DEFINITIONS                      **
rem **                                                        **
rem ************************************************************
rem ************************************************************

set OPTION=%1

rem ==========              PROJECT/FILES             ==========     
rem ============================================================
set PROJECT_NAME=main
set SOURCES=^
..\src\%PROJECT_NAME%.c

rem ==========              COMPILER(MSVC)            ==========     
rem ============================================================
set MSVC_COMMON_FLAGS=^
-nologo

rem TODO(MIGUEL): ENABLE WARNINGS ONE BY ONE AND RESOLVE
set MSVC_WARNINGS=^
-wd4057 ^
-wd4013 ^
-wd4057 ^
-wd4100 ^
-wd4101 ^
-wd4189 ^
-wd4204 ^
-wd4244 ^
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

set INCUDE_PATHS=

rem ==========             LINKER(MSVC)               ==========     
rem ============================================================
set LINKER_FLAGS=^
-incremental:no ^
-opt:ref

set LIBRARIES=


rem ************************************************************
rem ************************************************************
rem **                                                        **
rem **                       START BUILD                      **
rem **                                                        **
rem ************************************************************
rem ************************************************************

set PATH=F:\Dev\Practice\build;%PATH%
pushd build

cl %MSVC_FLAGS% %INCUDE_PATHS% %SOURCES% /link %LIBRARIES%

popd