@echo off
rem  Win32 CMD script to set the DLL paths to search for 
rem  the (sub)programs or modules
rem  David Essex         October 2006

rem  Set the DLL paths to search for the (sub)programs or modules
 
set TCOB_LD_LIBRARY_PATH=C:\tinycobol\test.code\cobrun
set PATH=%PATH%;C:\mingw\bin;C:\tinycobol\test.code\cobrun

rem tcobrun.bat dyntest01 dyntest.exe

rem echo "cmd: htcobrun2 %1%"
echo "cmd: htcobrun %1%"
htcobrun.exe %1% abc ddd ee

echo "cmd: %2%"
.\%2%
