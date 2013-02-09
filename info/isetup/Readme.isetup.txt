TinyCOBOL MinGW edition:

TinyCOBOL MinGW edition assumes that the following is installed on your system:
- MinGW (includes GCC, etc.).
- Berkeley's DB library version 1.85. (1)
- VB-ISAM library (MinGW) version 2.0. (1) 
- PDcurses library version 2.4 or later. (1)

1) MinGW versions of these libraries are available on SF [2].

Installation using the setup binary:
- Run the INNO setup (ex: tinycobol-0.65-1.mingw.exe) binary.
- Create a DOS or CMD window shortcut.
- Set the TinyCOBOL and PATH environment variables.

  Win9x/ME users (DOS):
  Use the enclosed batch file 'tcobol.bat' as a template.
  Set the initial environment memory to 4096. 
  Example:
  set TCOB_OPTIONS_PATH=C:\mingw\local\share\htcobol
  set TCOB_RTCONFIG_PATH=C:\mingw\local\share\htcobol
  set PATH=C:\TinyCOBOL;C:\mingw\local\bin;%PATH%

  NT/Win2K/XP users (CMD):
  The enviroment variables are set in the registery on a global or 
  per user basis.
  Use the properties sheet to set the enviroment variables values.  

  Example (W2K user level):
  Left-click 'My Computer', select 'properties',  select Advanced on the 
  System properties tab, select 'Enviroment Variables' option.
  Add 'TCOB_*' (with paths) to the user variables.
  Change the 'PATH' System variables and append the TC binary path.

  TCOB_OPTIONS_PATH=C:\mingw\local\share\htcobol
  TCOB_RTCONFIG_PATH=C:\mingw\local\share\htcobol
  PATH=%PATH%;C:\mingw\bin

Binaries for BDB and PDcurses can be downloaded from the TinyCOBOL web page.

Note that the following are not included in distribution.
- Regression test suite sources.
- Utility programs binaries. 
- Sample COBOL code sources.

2) TC files on SF
http://sourceforge.net/projects/tiny-cobol/files/
