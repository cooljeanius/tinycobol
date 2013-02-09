TinyCOBOL Cygwin (POSIX/UN*X emulation layer) edition for Win32

As of version 0.62, TinyCOBOL Cygwin edition is no longer supported.

The TinyCOBOL MinGW (Mingw32) edition can be used. It provides the same 
features without the emulation layer over-head.

The source code should compile with Cygwin, but has not been tested. 

-----------------------------------------------------------------------------
How to build and install the TinyCOBOL Cygwin edition from the source code
- The Cygwin POSIX emulation layer from Cygnus.
- GCC Cygwin version.
- make (make).
- flex (flex). 
- Bison or Berkeley's YACC (byacc) version 1.9.3.
  Earlier versions of Berkeley's YACC will not work.
- The Curses library (ncurses) Cygwin version.
  Required by the SCREEN SECTION and some types of DISPLAY statements.
- Berkeley's DB library (version db-1.85.4 or later) Cygwin version. 
  Required for the COBOL SORT verb file I/O.
- VB-ISAM library (Cygwin) version 2.0. 
  Required for indexed file I/O.

How to configure and compile TinyCOBOL Cygwin edition.
- Extract 'tinycobol-x.xx-x' TAR/GZIP archive.
- Run the configure script 'configure' (1).
- Type 'make' to compile the compiler and run-time (2).

How to install TinyCOBOL Cygwin edition.
- Configure and compile TinyCOBOL Cygwin edition.
- Type 'make install' to install the compiler and run-time.

Example:
 ./configure
 make
 make install

- Edit the compiler resource file 'htcobolrc'.
  Example (set your paths):
  LD_PATH: -L/usr/lib -L/usr/local/lib 
- Set the TinyCOBOL environment variables.
  Example (DOS or CMD window):
  set TCOB_OPTIONS_PATH=C:\cygwin\usr\local\share\htcobol
  set TCOB_RTCONFIG_PATH=C:\cygwin\usr\local\share\htcobol
  Example (shell resource file):
  export TCOB_OPTIONS_PATH=/usr/local/share/htcobol
  export TCOB_RTCONFIG_PATH=/usr/local/share/htcobol

Notes:
1)
 Use these variables to override the choices made by `configure' or to help
 it to find libraries and programs with nonstandard names/locations.
 Some influential environment variables:
  LDFLAGS     linker flags, e.g. -L<lib dir> if you have libraries in a
              nonstandard directory <lib dir>
  CPPFLAGS    C/C++ preprocessor flags, e.g. -I<include dir> if you have
              headers in a nonstandard directory <include dir>
2)
 To build shared libraries (DLL) use 'make devel'. 
 Note that this has not been tested for the Cygwin platform
 and will require manual modifications to the make file
 in the 'lib' directory. 


Release notes
-----------------------------------------------------------------------------
To run the TinyCOBOL regression test suite for the Win32 Cygwin release 
requires the following to be installed on your system.
- Perl 5.x


Links
-----------------------------------------------------------------------------
1) TinyCOBOL
http://tiny-cobol.sourceforge.net/download.html
http://sourceforge.net/projects/tiny-cobol/files/
