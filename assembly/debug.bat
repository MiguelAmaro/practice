@ECHO OFF

SET DEBUG_FILE= .\debug\practice.rdbg
SET EXECUTABLE= .\build\practice.exe


SET OPTION=%1

call F:\Dev_Tools\RemedyBG\release_0.3.5.0\remedybg.exe %DEBUG_FILE%

PAUSE



