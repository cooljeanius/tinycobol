TinyCOBOL MinGW (Mingw32) edition for Win32
-----------------------------------------------------------------------------

As of version 0.64, TinyCOBOL MinGW edition is set up to install in the
MinGW subdirectories.

Beginning with version 0.65, TC will use the VB-ISAM [3] library, version 2,
for all indexed file IO.

To run TinyCOBOL MinGW edition the following must be installed on your system:
- MinGW (includes GCC, binutils, etc.).
- Berkeley's DB library (MinGW) version 1.85. 
- VB-ISAM library (MinGW) version 2.0. 
- PDcurses library (MinGW) version 2.4 or later.


-----------------------------------------------------------------------------
Quick install and setup for TinyCOBOL MinGW edition 

Installation using the ZIP archive (Requires a program to unpack a ZIP archive):
- Download the ZIP ALL archive (ex: tinycobol-0.65-1-ALL.mingw.zip).
- Unpack the enclosed ZIP archives in the root MinGW directory (C:\MinGW).
  This will create the 'local' subdirectory structures.
- Setup the paths and environment variables as described below.
- Change the TinyCOBOL compiler resource to suit your needs as described below.
- Open a DOS or CMD window and test compiler (ex: htcobol -V) and then
  perform a test compile.
- Optional: Download the sample code found in the 'test.code' directory of
  the ZIP source archive (ex: tinycobol-0.65.src.zip).
  See notes below.

-----------------------------------------------------------------------------
How to install and setup TinyCOBOL MinGW edition 

Installation using the ZIP archive (Requires a program to unpack a ZIP archive):
- Unpack the ZIP archive in the root MinGW directory.

Installation using INNO setup:
- Run the INNO setup (ex: tinycobol-0.65-1.mingw.exe) and install TC
  in the root MinGW directory.

How to setup TinyCOBOL paths and environment variables:
- Create a DOS or CMD window shortcut.
- Set the TinyCOBOL and PATH environment variables.

  Win9x/ME users (DOS):
  Use the enclosed batch file 'tcobol.bat' as a template.
  Set the initial environment memory to 4096. 

  Example:
  set TCOB_OPTIONS_PATH=C:\mingw\local\share\htcobol
  set TCOB_RTCONFIG_PATH=C:\mingw\local\share\htcobol
  set PATH=%PATH%;C:\mingw\local\bin;C:\mingw\bin

  NT/W2K/XP users (CMD):
  The environment variables are set in the registry on a global or 
  per user basis.
  Use the properties sheet to set the environment variables values.  

  Example (W2K user level):
  Left-click 'My Computer', select 'properties',  select Advanced on the 
  System properties tab, select 'Environment Variables' option.
  Add 'TCOB_*' (with paths) to the user variables.
  Change the 'PATH' System variables and append the TC binary path.

  TCOB_OPTIONS_PATH=C:\mingw\local\share\htcobol
  TCOB_RTCONFIG_PATH=C:\mingw\local\share\htcobol
  PATH=%PATH%;C:\mingw\local\bin;C:\mingw\bin

How to setup the compiler resource to suit your needs:
  The resource file is used define some compiler defaults.
  Note that the command line options will override these defaults.
  
  The most common options used are input COBOL file format, FREE or FIXED,
  and output file, PROGRAM or MODULE (DLL).
  
  The input COBOL file format is set by the 'DEFAULT-SOURCE-FORMAT' option
  which is set to 'FREE' as a default.

  The output file is set by the 'DEFAULT-COMPILE-TYPE' option
  which is set to 'PROGRAM' as a default.
  
Optional sample code:
  Some sample code can be found in the 'test.code' directory of
  the ZIP source archive (ex: tinycobol-0.65.src.zip).
  The make files have been generated, using 'mconfig.sh'. To build just 
  type 'make' (mingw32-make on some versions of MinGW). This will build 
  the program or DLL.
  examples: 
    cd t12
    make
    test12a.exe ... test12n.exe
    
    cd cobrun
    make
    tcobrun.bat dyntest01 dyntest.exe

-----------------------------------------------------------------------------
How to build and install the TinyCOBOL MinGW edition from the source code

To build TinyCOBOL Win32 MinGW release requires the following to be 
installed on your system.
- MSYS or some sort of POSIX shell.
- MinGW.
- make (make).
- flex (flex). 
- Bison or Berkeley's YACC (byacc) version 1.9.3.
  Earlier versions of Berkeley's YACC will not work.
- Berkeley's DB library (MinGW) version 1.85 or later. 
  Required for the COBOL SORT verb file I/O.
- PDcurses library (MinGW) version 2.4 or later.
  Required by the SCREEN SECTION and some types of DISPLAY/ACCEPT statements.
- VB-ISAM library (MinGW) version 2.0. 
  Required for indexed file I/O.

How to configure and compile TinyCOBOL MinGW edition.
ZIP archive (DOS/CMD):
- Extract 'tinycobol-x.xx.src.zip' ZIP archive.
- Use the 'tcbuild.mingw.bat' file to compile the compiler and run-time.
TAR/BZ2 archive (MSYS):
- Extract 'tinycobol-x.xx.tar.bz2' TAR/BZ2 archive.
- Run the MinGW configure script 'tconfig.mingw.sh' using the '-i' option
  to set the install directory (1) (2).
  Example:
  sh tconfig.mingw.sh -i 'D:/mingw/local'
- Type 'make' to compile the compiler and run-time (3).

How to install TinyCOBOL MinGW edition.
ZIP archive (DOS/CMD):
- Compile TinyCOBOL MinGW edition.
- Use 'tcobol.iss' file to build setup or 
TAR/BZ2 archive (MSYS):
- Configure and compile TinyCOBOL MinGW edition.
- Set the 'DESTDIR' environment variable (export DESTDIR=C:/wk/tmp).
- Type 'make install' to install the compiler and run-time (4).


Notes:
1) Default install directory is 'C:/mingw/local'.
2) Running the UN*X 'configure' script on MSYS
   will not properly setup all the variables.
3) To build the TC run-time as a static library and DLL use 'make'. 
4) The install directory is set in the configure, step 1.
5) Optional: Set (export) Bison resources and temporary directory
Example:
SET BISON_SIMPLE=C:\MINGW\usr\local\share\bison.simple
SET BISON_HAIRY=C:\MINGW\usr\local\share\bison.hairy
SET TEMP=C:\temp
SET TMPDIR=C:\temp 


How to create the TinyCOBOL MinGW edition INNO setup executable from the source code
-----------------------------------------------------------------------------

- Configure and compile TinyCOBOL MinGW edition as described above.
- Use the INNO setup script 'tcobol.iss' to create the INNO setup executable.

Release notes
-----------------------------------------------------------------------------
To run the TinyCOBOL regression test suite for the Win32 MinGW release 
requires the following to be installed on your system.
- Perl 5.x

Binaries for BDB and PDcurses can be downloaded from the TinyCOBOL [1] or GNUwin32 [2] pages.

The following are not included in binary distribution.
- Regression test suite sources.
- Utility programs binaries. 
- Sample COBOL code sources.

Links
-----------------------------------------------------------------------------
1) TinyCOBOL
http://tiny-cobol.sourceforge.net/download.html
http://sourceforge.net/projects/tiny-cobol/files/

2) GNUwin32 - PDCurses
http://gnuwin32.sourceforge.net/
http://gnuwin32.sourceforge.net/packages/pdcurses.htm

3) VB-ISAM version 2 - vbisam-2.0.mingw.zip
http://sourceforge.net/projects/tiny-cobol/files/
