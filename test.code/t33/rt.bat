@echo off

rem  This shell script will run test program
rem  cmd: rt.bat 
rem  David Essex		August 2010
rem  Note: 
rem  Reverse function calls, meaning calling fuctions
rem  found in the original calling DLL or binary,
rem  will work when using ELF (UN*X), but
rem  will NOT work when using PE-COFF (Win32).

set PRG=dyntest.exe

rem Note: required if htcobol are shared libraries
set PATH=.;C:/MinGW/local/bin;%PATH%

set LD_LIBRARY_PATH=.;%LD_LIBRARY_PATH%
set TCOB_LD_LIBRARY_PATH=.

.\%PRG%

