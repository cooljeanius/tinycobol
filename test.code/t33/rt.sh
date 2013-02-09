#!/bin/bash
#
#  This shell script will run test program
#  cmd: rt.sh 
#  David Essex		April 2001
#
prg=dyntest
#
# Note: required if htcobol are shared libraries
export LD_LIBRARY_PATH=.:../../lib:$LD_LIBRARY_PATH
#export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
#
export TCOB_LD_LIBRARY_PATH=.
#export TCOB_LD_LIBRARY_PATH LD_LIBRARY_PATH
#
./$prg
#
