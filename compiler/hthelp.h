/* 
 *  Copyright (C) 2001, 2000, 1999 David Essex
 * 
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this software; see the file COPYING.  If not, write to
 *  the Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 *  Boston, MA 02111-1307 USA
 *


    -o <file>      Specify output file name (default name a.out)\n
    -fpic          Generate position independent code, if possible
*/

#ifndef _HTHELP_H
#define _HTHELP_H

struct _help_string {
  char  *s;
};

/*#define TCOB_LANGUAGE_@tcob_lang@       1  */

#ifdef TCOB_LANGUAGE_en

struct _help_string htg_options_string[] = {
  { " Compiler specific options:" },
  { "   -h, --help     Help - display this message" },
  { "   -B <mode>      Specify libraries binding mode (static or dynamic)" },
  { "   -c             Preprocess, compile and assemble, but do not link" },
  { "   -E             Preprocessor only; do not compile, assemble or link" },
  { "   -g             Generate compiler debugging output" },
  { "   -l <name>      Add library name to link step" },
  { "   -L <dir>       Add directory to library search path" },
  { "   -m             Build a shared library (DLL) or module" },
  { "   -n             Don't actually run any commands; just print them" },
  { "   -o <file>      Specify output file name" },
  { "   -S             Preprocess, compile (generate assembler code) only; do not assemble or link" },
  { "   -t             Don't remove intermediate files (pre-processed COBOL file, assembly file, etc.)" },
  { "   -v             Generate verbose compiler output" },
  { "   -V, --version  Display compiler version information and exit" },
  { "   -Wl,<options>  Pass comma-separated <options> on to the linker" },
  { "   -x             Build an executable program (Default)" },
  { "   -z             Generate very verbose compiler output" },
  { " COBOL specific options:" },
  { "   -C             Make all COBOL calls dynamic " },
  { "   -d             Generate display SECTION/PARAGRAPH trace code " },
  { "   -D             Include COBOL source debugging lines " },
  { "   -e <name>      Specify entry point name (first program to execute)" },
  { "   -F, --fixed    Input source is in standard fixed column format" },
  { "   -I <dir>       Add path to the include (copybooks) search paths" },
  { "   -M             Generate entry point and use PROGRAM-ID of first program with STOP RUN (Default: first PROGRAM-ID)" },
  { "   -P             Generate output listing file" },
  { "   -T <num>       Expand tabs to number of space(s) (default T=8)" },
  { "   -X, --free     Input source is in free format" },
  { NULL }
};

/*
#define HTG_OPTIONS     "Compiler specific options:\n"\
"  -h, --help     Help - display this message\n"\
"  -a             Create static library; Preprocess, compile, assemble and archive\n"\
"  -B <mode>      Specify libraries binding mode ( static or dynamic )\n"\
"  -c             Preprocess, compile and assemble, but do not link\n"\
"  -E             Output preprocessor to standard output only; do not compile, assemble or link\n"\
"  -g             Generate compiler debugging output\n"\
"  -l <name>      Add library name to link step\n"\
"  -L <dir>       Add directory to library search path\n"\
"  -m <name>      Create shared library (DLL); Preprocess, compile, assemble and link\n"\
"  -n             Don't actually run any commands; just print them\n"\
"  -o <file>      Specify output file name\n"\
"  -S             Preprocess, compile (generate assembler code) only; do not assemble or link\n"\
"  -t             Don't remove the intermediary files (assembly file, pre-processed COBOL file)\n"\
"  -v             Generate verbose compiler output\n"\
"  -V, --version  Display compiler version information and exit\n"\
"  -Wl,<options>  Pass comma-separated <options> on to the linker\n"\
"  -x             Create executable; Preprocess, compile, assemble and link\n"\
"  -z             Generate very verbose compiler output\n"\
"COBOL specific options:\n"\
"  -C             Make all COBOL calls dynamic \n"\
"  -d             Generate display SECTION/PARAGRAPH trace code \n"\
"  -D             Include COBOL source debugging lines \n"\
"  -e <name>      Specify entry point name (first program to execute)\n"\
"  -F, --fixed    Input source is in standard fixed column format\n"\
"  -I <dir>       Add path to the include (copybooks) search paths\n"\
"  -M             Generate entry point and use PROGRAM-ID of first program with STOP RUN (Default: first PROGRAM-ID)\n"\
"  -P             Generate output listing file\n"\
"  -T <num>       Expand tabs to number of space(s) (default T=8)\n"\
"  -X, --free     Input source is in free format\n"\
"\n"
*/
/*
"  -U             Use curses mode for all ACCEPT/DISPLAY statements (EXPERIMENTAL)\n"\
*/
#endif
#endif
