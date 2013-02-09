#!/bin/bash - 
#
#  Shell script will run cobol_test.pl 
#  and create a trace file and rename the log file
#  cmd: rp.sh 
#  David Essex		June 2001
#
e0a="invalid number of parms..."
e0b="invalid option(s) "
e0c="Shell script will run cobol_test.pl and create a trace file and rename the log file"  
e0d="cmd: rp.sh"  
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
reply=n
dt=`date +%y%m%d`
sv=0
ft0='cobol_test.trace2.temp.$$.txt'
ft1=''
ft2=''
sv=`ls -1 w/cobol_test.trace.$dt*txt 2>/dev/null | grep -v log | wc -l`
sv=`echo "$sv" | tr -d ' '`
sv=`expr $sv + 1`
flog=''
#
#ft1=cobol_test.trace.$dt.$sv.txt
ft1=`printf "cobol_test.trace.%s.%03d.txt" $dt $sv`
#echo "ft1=$ft1"
#exit
#
if [ -f "$ft1" ]
then
   e1="error: filename $1 exists ... abort"
   p_print1 "$e1" "$e0c" "$e0d"
   exit 1
fi
#
#./cobol_test.pl 2>w/$ft0 | tee w/$ft1
./cobol_test.pl 1>w/$ft1 2>w/$ft0
#./cobol_test.2.pl 1>w/$ft1 2>w/$ft0
#echo "./cobol_test.pl 1>w/$ft1 2>w/$ft0"
#
flog=`ls test*log`
#
#ft2=cobol_test.trace.$dt.$sv.$flog.txt
ft2=`printf "cobol_test.trace.%s.%03d.%s.txt" $dt $sv $flog`
#
mv -i $flog w/$ft2
#
echo "------------------- std-error begin ----------------------" >> w/$ft1
cat w/$ft0 >> w/$ft1
rm -f w/$ft0
#
make clean
#
w/tsf.sh
#
