@echo off
rem **************************************************
rem * Datei: build_protocol_buffers_java.cmd
rem * Datum: 17.05.2016
rem * Parameter:
rem * Bemerkung:
rem **************************************************

SETLOCAL

rem get path of calling command
for %%i in (%0) do set curpath=%%~dpi
cd /d %curpath%
SET PROTOC=protoc.exe

:START
%PROTOC% --java_out=../../../../CashDrawer/src/main/java uposcashdrawer.proto

:EXIT

echo "FINISH"
pause

ENDLOCAL
