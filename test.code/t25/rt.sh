#!/bin/bash
#
#  This shell script will run test programs
#  cmd: rt.sh 
#  David Essex		August 2004
#
prg1='test25z1'
prg2='test25z2'
#
#LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH 
#
if [ -z $LD_LIBRARY_PATH ]
then
 LD_LIBRARY_PATH=.
else
 LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH 
fi
#
export LD_LIBRARY_PATH
#
echo "Program $prg1 begin ..."
./$prg1
echo "Program $prg2 begin ..."
./$prg2
#
