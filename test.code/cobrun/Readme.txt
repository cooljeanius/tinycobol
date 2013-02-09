Abstract:

Sample application on how to build and run (sub)programs or modules,
using the 'htcobrun' program.

Note:
The (sub)programs or module name is the 'PROGRAM-ID' name, not the actual 
file name.
The actual file (shared library) may contain one or more modules.

>---------------------------------------------------------------------------<

How to build the sample application:
make 

>---------------------------------------------------------------------------<

How to run an application:

You can use the 'htcobrun' program directly or use the sample
shell script 'tcobrun.sh' (tcobrun.bat) provided.

To use the 'htcobrun' program directly, first set the modules location(s).

Example:
$LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
$TCOB_LD_LIBRARY_PATH=.
$export TCOB_LD_LIBRARY_PATH LD_LIBRARY_PATH
$htcobrun dyntest

To use the sample shell script, edit the script and set
the modules location(s).

Example:
$edit tcobrun.sh
...
LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
TCOB_LD_LIBRARY_PATH=.
export TCOB_LD_LIBRARY_PATH LD_LIBRARY_PATH
...
$tcobrun.sh dyntest

