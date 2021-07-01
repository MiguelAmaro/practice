@echo off
if not exist build mkdir build

rem REFERENCES 
rem Flags: https://docs.microsoft.com/en-us/cpp/assembler/masm/ml-and-ml64-command-line-reference?view=msvc-160


set SOURCE= ..\src\assembly\main.asm


rem SET MASM64="F:\Dev_Tools\Visual_Studio_Build_Tools\VC\Tools\MSVC\14.28.29333\bin\HostX64\x64\ml64.exe"

set MASM_FLAGS=^
-nologo ^
-Zi ^
-Zf

set LINKER_FLAGS=^
-nodefaultlib ^
-subsystem:console

pushd build

ml64 %MASM_FLAGS% -Fe practice.exe %SOURCE% -link %LINKER_FLAGS%

popd
