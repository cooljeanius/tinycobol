#!/bin/bash - 
#
#  This shell script will create COBOL tables
#  cmd: mktab.sh -[a|d] n1 n2 n3 {a=ascending d=descending n1=start n2=end n3=increment numbers}
#  David Essex		April 2000
#
e0a="invalid number of parms..."
e0b="invalid option(s) "
e0c="This shell script will create COBOL tables"  
e0d="cmd: mktab.sh -[a|d] n1 n2 n3 {a=ascending d=descending n1=start n2=end n3=increment numbers}"  
#
p_print1 ()
{
for arg in "$@"
do
   echo $arg >&2
done
}
#
if [ "$#" -ne 4 ]
then
   p_print1 "$e0a" "$e0c" "$e0d"
   exit 1
fi
#
num=0
nend=0
inum=1
#
p_asc () 
{
#
 num=$1
 nend=$2
 inum=$3
#
# echo " 01 WS-TABLE1-ENTRIES."
 while [ $num -le $nend ]
 do
#   printf "    05  FILLER  PIC X(20) VALUE '%03dDEPT%03d          '.\n" $num $num
   printf "    05  FILLER  PIC X(10) VALUE '%03dDEPT%03d'.\n" $num $num
   num=`expr $num + $inum`
 done
#
}
#
#
p_desc () 
{
#
 num=$2
 nend=$1
 inum=$3
#
# echo " 01 WS-TABLE1-ENTRIES."
 while [ $num -ge $nend ]
 do
#   printf "    05  FILLER  PIC X(20) VALUE '%03dDEPT%03d          '.\n" $num $num
   printf "    05  FILLER  PIC X(10) VALUE '%03dDEPT%03d'.\n" $num $num
   num=`expr $num - $inum`
 done
#
}
#
case "$1"
in
  -a)
    shift 1
    p_asc $@ 
    ;; 
  -d)
    shift 1
    p_desc $@ 
    ;; 
  *)
   e1="$e0b '$1'"
   p_print1 "$e1" "$e0c" "$e0d"
   ;; 
esac
#
