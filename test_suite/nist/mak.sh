#!/bin/bash
#
#  This shell script will run make and create trace.txt
#  cmd: mak.sh [filename(s)]
#  David Essex		April 2001
#
e0a="invalid number of parms..."
e0b="invalid option(s) "
e0c="This shell script will run make and create trace.txt"  
e0d="cmd: mak.sh [filename(s)]"  
#
p_print1 ()
{
for arg in "$@"
do
   echo $arg >&2
done
}
#
PATH=../../compiler:$PATH
TCOB_OPTIONS_PATH=$PWD/../../compiler
TCOB_RTCONFIG_PATH=$PWD/../../lib
export TCOB_OPTIONS_PATH TCOB_RTCONFIG_PATH
#
#prglst=''
prglst=`make programlist`
prg=''
#
p_main () 
{
 make clean  
 for prg in "$@"
 do
    make $prg 2>$prg.run.err.trace.txt | tee -a $prg.run.trace.txt 
#   echo "make for $prg"
 done
}
#
if [ "$#" -eq 0 ]
then
   p_main $prglst
#   echo "prglst="$prglst
else
   p_main "$@"
#   echo "prglst="$prglst
fi
#
