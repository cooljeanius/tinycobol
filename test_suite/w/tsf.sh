#!/bin/bash - 
#
#  This shell script will select the latest 2 test_suite log file to compare using xcdiff
#  cmd: tsf.sh  [version-refrence1 version-refrence2]
#  David Essex		January 2002
#
e0a="invalid number of parms..."
e0b="invalid option(s) "
e0c="This shell script will select the latest 2 test_suite log file to compare using xcdiff"  
e0d="cmd: tsf.sh [version-refrence1 version-refrence2]"  
#
p_print1 ()
{
for arg in "$@"
do
   echo $arg >&2
done
}
#
if [ \( "$#" -ne 0 \) -a \( "$#" -ne 2 \) ]
then
   p_print1 "$e0a" "$e0c" "$e0d"
   exit 1
fi
#
fl1=`ls w/cobol_test.trace*txt | grep -v log | sort -r`
fl2=`ls w/cobol_test.trace*log.txt | sort -r`
#
wcnt1=`echo $fl1 | wc -w | tr -d ' '`
wcnt2=`echo $fl2 | wc -w | tr -d ' '`
#echo "debug: cobol_test.trace files: wcnt1=$wcnt1 and wcnt2=$wcnt2"
#
if [ "$wcnt1" -ne "$wcnt2" ]
then
   e1="cobol_test.trace files are out of sequence $wcnt1 -ne $wcnt2"
   p_print1 "$e1" "$e0c" "$e0d"
   exit 2 
fi
#
if [ "$wcnt1" -lt 2 ]
then
   e1="Insufficient cobol_test.trace files to compare $wcnt1 -lt 2"
   p_print1 "$e1" "$e0c" "$e0d"
   exit 3 
fi
#
p_main () 
{
# echo "p_main - 0: all=$@;"
# echo "p_main - 1: file1=$1, file2=$2;"
 xcdiff $2 $1 &
# vimdiff $2 $1 
}
#
p_locate () 
{
#
 i0=1
 i1=$1
 i2=$2
 shift 2
#
if [ \( "$i1" -gt "$wcnt2" \) -o \( "$i2" -gt "$wcnt2" \) ]
then
   e1="Relative number 1=$i1 or 2=$i2 is out bounds, max is $wcnt1"
   p_print1 "$e1" "$e0c" "$e0d"
   exit 21 
fi
#
if [ "$i2" -eq "$i1" ]
then
   e1="Relative number 1=$i1 or 2=$i2 must be different, max is $wcnt1"
   p_print1 "$e1" "$e0c" "$e0d"
   exit 22 
fi
#
 fl0=$@
 f1=''
 f2=''
#
# echo "p_locate - 1: fl0=$fl0;"
#  for t0 in $fl10
#  do
# #   echo "p_locate - for loop: i0=$i0, i1=$i1, i2=$i2;"
#    if [ $i0 -eq $i1 ]
#    then
#       f1="$t0"    
#    fi
#    if [ $i0 -eq $i2 ]
#    then
#       f2="$t0"    
#    fi
#    i0=`expr $i0 + 1`
#  done 
#
# echo "p_locate - 2: f1=$f1, f2=$f2;"
 f1=`echo $fl0 | cut -d' ' -f$i1`
 f2=`echo $fl0 | cut -d' ' -f$i2`
# echo "p_locate - 3: f1=$f1, f2=$f2;"
#
 p_main $f1 $f2
}
#
case "$#"
in
  0)
    p_main $fl1
    p_main $fl2
    ;; 
  2)
    p_locate $1 $2 $fl1
    p_locate $1 $2 $fl2
    ;; 
  *)
   e1="$e0b$opts ..."
   p_print1 "$e1" "$e0c" "$e0d"
   p_print1 
   ;; 
esac
#
