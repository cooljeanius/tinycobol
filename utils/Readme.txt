Set of COBOL utility programs.

------------------------------------------------------------------------------

cobf2f: by David Essex 

Utility program that will convert from/to fixed to/from free-form COBOL formats.

Usage: htcobf2f [<options>] [-i input file ] [-o output file ]
where <options> are:
      -h            This help screen
      -V            Print out version
      -x            Convert source to X/Open free format (Default)
      -f            Convert source to Standard fixed column format
      -m <num>      Fixed format line number multiplier (Default = 10)
      -i <filename> Input  filename (Default is standard input)
      -o <filename> Output filename (Default is standard output)

      Note: Tab expandtion not supported (Hint: Use expand utility).

------------------------------------------------------------------------------

viscomp.tcl: by Rildo Pragana

Visual parser tool for stepping through compiler operation and general use gdb
frontend.

------------------------------------------------------------------------------

dispcv.tcl: by Rildo Pragana

A tcl script to convert "DISPLAY (X, Y) ..." syntax to our supported syntax 
"DISPLAY LINE/POS ...". 
