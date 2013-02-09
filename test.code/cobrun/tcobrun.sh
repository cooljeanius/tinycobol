#!/bin/sh
#
#  Shell script to run htcobrun modules (programs)
#  cmd: tcobrun.sh [ module-name {default=dyntest01} ] [ program-name ]
#  David Essex		April 2005
#
e0a="invalid number of parms..."
e0b="invalid option(s) "
e0c="Shell script to run htcobrun modules (programs)"  
e0d="cmd: tcobrun.sh [ module-name {default=dyntest01} ] [ program-name ]"  
#
p_print1 ()
{
for arg in "$@"
do
   echo $arg >&2
done
}
#
if [ "$#" -gt 2 ]
then
   p_print1 "$e0a" "$e0c" "$e0d"
   exit 1
fi
#
prg_name=../../cobrun/htcobrun
#prg_name=htcobrun
#prg=htcobrun2
mod_name=''
#
# Export shared library paths
export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
export TCOB_LD_LIBRARY_PATH=.
#export TCOB_LD_LIBRARY_PATH LD_LIBRARY_PATH
#
if [ "$#" -eq 0 ]
then
  mod_name=dyntest01
else 
  mod_name="$1"
fi
#
echo "cmd: $prg_name $mod_name"
$prg_name $mod_name 
echo "return code=$?"
#
# This code is strictly optional
if [ "$#" -eq 2 ]
then
  echo "cmd: ./$2"
  ./$2
  echo "return code=$?"
fi
#
