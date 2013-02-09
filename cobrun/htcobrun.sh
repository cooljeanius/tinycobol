#!/bin/bash
#
#  Shell script to load and run TC (sub)programs or modules
#  cmd: htcobrun.sh module-name [ command-line-arg1 ... command-line-argN ]
#  David Essex		April 2005
#
prg=/home/user1/w/cobol/tc/development/cobrun/htcobrun
#prg=../htcobrun2
#
# Add the shared library paths to search
# for the (sub)programs or modules
#
LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
TCOB_LD_LIBRARY_PATH=.
export TCOB_LD_LIBRARY_PATH LD_LIBRARY_PATH
#
$prg $@
#
