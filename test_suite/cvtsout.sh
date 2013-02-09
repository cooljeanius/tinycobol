#!/bin/bash - 
#
#  Shell script to convert ouput from test programs to format found in test.baseline file
#  cmd: cvtsout.sh 
#  David Essex		November 2009
#
#  NOTE: 
#  Read notes at bottom on how to update test.baseline file using this script.
#
e0a="invalid number of parms..."
e0b="invalid option(s) "
e0c="Shell script to convert ouput from test programs to format found in test.baseline file"  
e0d="cmd: cvtsout.sh"  
#
p_print1 ()
{
for arg in "$@"
do
   echo $arg >&2
done
}
#
if [ "$#" -ne 0 ]
then
   p_print1 "$e0a" "$e0c" "$e0d"
   exit 1
fi
#
# Enter test script name  
#if01='test.script'
if01='test.script.txt'
#
# Enter program list 
#fl01="idxio01 idxio08 idxio09 idxio10"
fl01="idxio01 idxio08"
#
# Enter directory 
d01='idxio_tests'
#
pname01=''
pdesc01=''
testdir01=''
#
p_getnames () 
{
 pname01=`cat $if01 | grep -v '^#' | grep $1 | cut -f1 -d':'`
# echo "pname01=$pname01" 
 pdesc01=`cat $if01 | grep -v '^#' | grep $1 | cut -f3 -d':'`
# echo "pdesc01=$pdesc01" 
}
#
p_fprint () 
{
# echo "p_main $pname01 $pdesc01"
awk -F':' -v pname01=$pname01 -v pdesc01="$pdesc01" -v testdir01="$testdir01" '
#
BEGIN {
  s1 = "########################################################################";
  s2 = "                                                                        ";
  totLen = length(s1);
  botLen = 77;
  pdesc01Len = length(pdesc01);
  testdir01Len = length(testdir01);
  pname01Len = length(pname01);
  filler01Len = totLen - pdesc01Len - 3;
  filler01 = substr(s2, 1, filler01Len);
  filler02Len = 44 - testdir01Len - 18;
  filler02 = substr(s2, 1, filler02Len);
  filler03Len = totLen - testdir01Len - filler02Len - pname01Len - 29;
  filler03 = substr(s2, 1, filler03Len);
  filler04Len = botLen - pdesc01Len - 10;
  filler04 = substr(s2, 1, filler04Len);

#  printf "########################################################################\n";
#  printf "# %s                                  #\n", pdesc01;
#  printf "# Test Directory: %s               Test File %s          #\n", testdir01, pname01;
#  printf "########################################################################\n\n";

#  printf "debug : totLen=%d, pdesc01Len=%d, testdir01Len=%d, pname01Len=%d, filler01Len=%d, filler02Len=%d, filler03Len=%d, filler04Len=%d\n", 
#          totLen, pdesc01Len, testdir01Len, pname01Len, filler01Len, filler02Len, filler03Len, filler04Len;

  printf "%s\n", s1;
  printf "# %s%s#\n", pdesc01, filler01;
  printf "# Test Directory: %s%sTest File %s%s#\n", testdir01, filler02, pname01, filler03;
  printf "%s\n\n", s1;
}
#
# RLO1:(00):(00):RELATIVE WRITE OPEN
# RLO1:  PASS RELATIVE SEQUENTIAL OUTPUT OPEN STATUS : Expecting (00) got (00)
{
  printf " %s:  PASS %s : Expecting %s got %s\n", $1, $4, $2, $3;
}
#
END {
#  printf "  %s                               : PASSED\n\n", pdesc01;
  printf "  %s%s: PASSED\n\n", pdesc01, filler04;
}
'
#
}
#
p_main () 
{
 testdir01="$1"
 for arg in $fl01
 do
   pname01=''
   pdesc01=''
#   echo "main $arg"
   p_getnames $arg
   if [ \( -n "$pname01" \) -a \( -n "$pdesc01" \) ]
   then
     $pname01 | p_fprint 
   else
     e1="Error : file name or description not found for $arg" 
     p_print1 "$e1" "$e0c" "$e0d"
     exit 1
   fi
 done
}
#
p_main $d01
#
exit
#
# How to update test.baseline file using this script.
# ----------------------------------------------------------------------------
# Build all program, including programs which produce input to other programs.
# Enter the program list fl01 (Ex: fl01="idxio01 idxio08 idxio09 idxio10").
# Enter the test directory d01 (Ex: d01='idxio_tests').
# Enter the test.script file name (Ex: if01='test.script').
# Run script in the test directory and redirect output to file (cvtsout.sh > t01.txt).
# Insert output into test.baseline file as required.
# 
# 
# Sample output for relio01
#RLO1:(00):(00):RELATIVE WRITE OPEN
#RL01:(001):(001):RELATIVE FILE WRITE
#RL01:(002):(002):RELATIVE FILE WRITE
#RL01:(003):(003):RELATIVE FILE WRITE
#RL01:(004):(004):RELATIVE FILE WRITE
#RL01:(005):(005):RELATIVE FILE WRITE
#RL01:(006):(006):RELATIVE FILE WRITE
#RL01:(007):(007):RELATIVE FILE WRITE
#RL01:(008):(008):RELATIVE FILE WRITE
#RL01:(009):(009):RELATIVE FILE WRITE
#RLC1:(00):(00):RELATIVE WRITE CLOSE
# Expected transformation
########################################################################
# Relative file sequential mode write                                  #
# Test Directory: relio_tests               Test File relio01          #
########################################################################
#
# RLO1:  PASS RELATIVE SEQUENTIAL OUTPUT OPEN STATUS : Expecting (00) got (00)
# RL01:  PASS RELATIVE FILE WRITE : Expecting (001) got (001)
# RL01:  PASS RELATIVE FILE WRITE : Expecting (002) got (002)
# RL01:  PASS RELATIVE FILE WRITE : Expecting (003) got (003)
# RL01:  PASS RELATIVE FILE WRITE : Expecting (004) got (004)
# RL01:  PASS RELATIVE FILE WRITE : Expecting (005) got (005)
# RL01:  PASS RELATIVE FILE WRITE : Expecting (006) got (006)
# RL01:  PASS RELATIVE FILE WRITE : Expecting (007) got (007)
# RL01:  PASS RELATIVE FILE WRITE : Expecting (008) got (008)
# RL01:  PASS RELATIVE FILE WRITE : Expecting (009) got (009) 
# RLC1:  PASS RELATIVE SEQUENTIAL OUTPUT CLOSE STATUS : Expecting (00) got (00)
#  Relative file sequential mode write                                : PASSED
#
