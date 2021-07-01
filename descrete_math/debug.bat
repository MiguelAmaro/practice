@ECHO OFF

SET DEBUG_FILE= .\debug\practice.rdbg
SET EXECUTABLE= .\build\practice.exe


SET OPTION=%1

IF [%OPTION%] EQU [--injected] (CALL :INJECTED)
IF [%OPTION%] EQU []           (CALL :DEFAULT )

EXIT /B 0

:DEFAULT
CALL F:\Dev_Tools\RemedyBG\release_0.3.5.0\remedybg.exe %DEBUG_FILE%
EXIT

:INJECTED
CALL F:\Dev_Tools\RemedyBG\release_0.3.5.0\remedybg.exe .\debug\injected.rdbg
EXIT

PAUSE



