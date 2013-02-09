Abstract:

Program (htcobrun) to enable TC COBOL (sub)programs, or modules, 
compiled with TC as shared libraries (DLL's), to be dynamically loaded 
and run.

The shared library files, which can contain one or more modules, are generally
stored in a directory.

The TC run-time will use the 'TCOB_LD_LIBRARY_PATH' and 'LD_LIBRARY_PATH' 
environment variables, to locate the requested (sub)program or module name.

Note that the (sub)programs, or module name, is the 'PROGRAM-ID' name, not 
the actual shared library file name.
The actual file (shared library) may contain one or more modules.


Why use 'htcobrun':

The 'htcobrun' program can be compiled to fully include the full run-time 
(static) library (Not available on MinGW version). 
This approach yields substantial runtime performance improvements. 

The COBOL (sub)programs can be built as shared libraries, which may contain 
one or more modules, and are loaded and run dynamically. 

Problems in using this approach:
Currently, there is no support for passing 'LINKAGE SECTION' parameters to
sub-programs. 

>---------------------------------------------------------------------------<

How to build the program:
make 
Modify the 'htcobrun.sh' as required.
make install (su required)

>---------------------------------------------------------------------------<

How to run an application:

You can use the 'htcobrun' program directly or use the sample
shell script 'htcobrun.sh' provided.

To use the 'htcobrun' program directly, first set the modules location(s).

Example:
$LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
$TCOB_LD_LIBRARY_PATH=.
$export TCOB_LD_LIBRARY_PATH LD_LIBRARY_PATH
$htcobrun dyntest

To use the sample shell script 'htcobrun.sh', edit the script and set
the modules location(s).

Example:
$edit tcobrun.sh
...
LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
TCOB_LD_LIBRARY_PATH=.
export TCOB_LD_LIBRARY_PATH LD_LIBRARY_PATH
...
$htcobrun.sh dyntest

>---------------------------------------------------------------------------<

Notes:

The current version of TC will substitute a 'main' entry point, for the 
name of the COBOL program, if it does not detect a 'USING' clause in 
the 'PROCEDURE DIVISION'.


Win32:
The MinGW version can only be compiled and run using the TC run-time as a 
DLL (not static).
Also the 'ACCEPT identifier FROM COMMAND-LINE' statement, will not work.

>---------------------------------------------------------------------------<

Original OpenCOBOL mailing-list posting:

Subject: [open-cobol-list] Open Cobol Optimization
Date: Sun, 16 Nov 2003 17:16:22 +0100

Keisuke asked me to post this info - so here it is.
Note - Applies to Linux

In an effort to get the same performance as MF, I noticed
that we are heavily bouncing in and out of the shared libs.
So I came up with this. "cobcrun" is a driver prog used to
call the Cobol prog. 
(This is equivalent to MF's "cobrun" and ACU's "runcbl"). 
It pulls in the complete static versions of libcob and libgmp. 

The difference in runtime performance is astounding !

This also has a useful side effect in that all Cobol progs 
can be compiled as modules. 
(And therefore we do not need to work out which are main progs
 and which are sub-progs for the compile)
(Note in cobcrun, that I move out argv0, otherwise we would
 have to do some fancy checking for the command line accept)
(Note this is a quick and dirty, must do more checking)

In addition, with GCC > 3, you can tweak a bit more by passing
CFLAGS="-march=pentium3 -minline-all-stringops" (for P3 - arch=pentium4 for P4)
into the Open Cobol configure and also into the program compiles.

Here's cobcrun.c :
#include        <stdio.h>
extern void *cob_resolve (const char *name);
extern void cob_call_error (void);
int
main (int argc, char **argv)
{
         int ret;
         int (*func)();
         char    *argn[64];

         if ( argc <= 1 ) {
                 fprintf(stderr, "No parameters specified\n");
                 return 1;
         }
         for ( ret = 1; ret < argc; ret++ ) {
                 argn[ret - 1] = argv[ret];
         }
         cob_init (argc - 1, argn);
         func = cob_resolve (argn[0]);
         if (func == NULL) {
                 cob_call_error ();
         } else {
                 ret = func ();
         }
         return ret;
}

And here's the compile/link for it :
gcc -rdynamic -Wl,-export-dynamic -O2 -o cobcrun \
cobcrun.c -Wl,-whole-archive /usr/local/lib/libcob.a \
/usr/lib/libgmp.a -Wl,-no-whole-archive -lltdl -ldb -lncurses -lm

Keisuke has indicated that something like this will be included in the next 
release.

Comments welcome.

Regards

Roger While
