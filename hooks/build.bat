@echo off
if not exist build mkdir build
rem REFERENCES:https://docs.microsoft.com/en-us/cpp/build/reference/compiler-options-listed-alphabetically?view=vs-2019

set OPTION=%1

rem PROJECT/FILES
rem ============================================================
set PROJECT_NAME=main
set SOURCES= %cd%\src\%PROJECT_NAME%.c

rem COMPILER(MSVC)
rem ============================================================
set MSVC_WARNINGS=-std:c11 -W4 -wd4057 -wd4152 -wd4100
set MSVC_FLAGS= %MSVC_WARNINGS% ^
-nologo -MT -GR -Od -WX -FC -Z7 -Facs

set INCUDE_PATHS=
set LINKER_FLAGS=-incremental:no -opt:ref
set LIBRARIES=

rem START BUILD
rem ============================================================
set PATH=F:\Dev\Practice\build;%PATH%

pushd build
cl %MSVC_FLAGS% %INCUDE_PATHS% %SOURCES% /link %LIBRARIES%
popd