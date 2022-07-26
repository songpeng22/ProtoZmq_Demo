@echo off
rem **************************************************
rem * Datei: build_protocol_buffers_c++.cmd
rem * Datum: 20.09.2017
rem * Parameter:
rem * Bemerkung:
rem **************************************************

SETLOCAL

for %%i in (%0) do set curpath=%%~dpi
cd /d %curpath%
SET PROTOC=protoc.exe

:START
%PROTOC% --cpp_out=..\src uposcashdrawer.proto

:EXIT
echo "FINISH"
pause

ENDLOCAL
