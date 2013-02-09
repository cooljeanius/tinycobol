#!/bin/bash -
#
#  Shell script to generate make files from in files
#  cmd: mconfig.sh [ dir-1 ... dir-n ]
#  David Essex		January 2007
#
e0a="invalid number of parms..."
e0b="invalid option(s) "
e0c="Shell script to generate make files from in files"  
e0d="cmd: mconfig.sh [ dir-1 ... dir-n ]"  
#
p_print1 ()
{
for arg in "$@"
do
   echo $arg >&2
done
}
#
if [ "$#" -gt 0 ]
then
  dl01="$@"
else
#
dl02="t00 t01 t02 t03 t04 t05 t06 t07 t08 t09 t10 t11 t12 t13 t14 t15 t16 t17 t18 t19 t20 \
t21 t22 t23 t24 t25 t26 t27 t28 t29 t30 t31 t32 t33 t34 t35 t36"
#
dl03="tdb01 tdb02 tdb03 tgui01 tgui02 ReportGen esql cobrun"
#
dl01="$dl02 $dl03"
#
fi
#
fm1=''
fm2=''
#
#f1="Makefile"
##f1="Makefile.mingw"
#f3="Makefile.in"
##f3="Makefile.mingw.in"
#
f1="Makefile"
f2="Makefile.in"
f3="Makefile.mingw.in"
#
errf1=0
#
. ./mconfig.inc
#
#echo "mc_prefix=${mc_prefix};"
#echo "dl01=$dl01;"
#exit
#
p_check_file_exists ()
{
#
 errf1=0
 if [ -f "$1" ]
 then
    errf1=5
 fi
}
#
p_mgen () 
{
 sed \
 -e "s|@prefix@|$mc_prefix|" \
 -e "s|@exec_prefix@|$mc_exec_prefix|" \
 -e "s|@g_includes@|$mc_g_includes|g" \
 -e "s|@g_libraries@|$mc_g_libraries|" \
 -e "s|@CCX@|$mc_CCX|" \
 -e "s|@COB@|$mc_COB|" \
 -e "s|@ASM@|$mc_ASM|" \
 -e "s|@RANLIB@|$mc_RANLIB|" \
 -e "s|@AR@|$mc_AR|" \
 -e "s|@LIBS@|$mc_LIBS $mc_tcob_ld_args_libs|" \
 -e "s|@INCLUDES@|$mc_INCLUDES|" \
 -e "s|@COPYBOOKS@|$mc_copybook_path|" \
 -e "s|@exeext@|$mc_exeext|" \
 -e "s|@LDFLAGS@|$mc_LDFLAGS|" \
 -e "s|@COBFLAGS@|$mc_COBFLAGS|" \
 -e "s|@ASMFLAGS@|$mc_ASMFLAGS|" \
 -e "s|@CCXFLAGS@|$mc_CCXFLAGS|" \
 < $2 > $1
#
}
#
p_genfile () 
{
 cd $1
 echo -n "Generating $fm1 from $fm2 in $1 ..."
 p_check_file_exists $fm1
 if [ $errf1 -eq 0 ]
 then
    p_mgen $fm1 $fm2
    echo    "(done)"
 else
    echo "make file $fm1 exists (ignoring)"
 fi
 cd ..
}
#
p_main () 
{
 for d0 in $dl01
 do
   errf1=0
   fm1=$f1
   fm2=$f2
#   echo "d0=$d0, fm1=$fm1, fm2=$fm2;"
   if [ "$mc_os_platform" = 'MinGW' ]
   then
     p_check_file_exists $d0/$f3
     if [ $errf1 -ne 0 ]
     then
       fm2=$f3
       p_genfile $d0 
     else
       p_check_file_exists $d0/$f2
       if [ $errf1 -ne 0 ]
       then
         fm2=$f2
         p_genfile $d0 
       else
         echo "No make files ($f2 or $f3) found in $d0 ...(ignoring)"
       fi
     fi
   else
#     echo "d0=$d0, fm1=$fm1, fm2=$fm2;"
     p_check_file_exists $d0/$f2
     if [ $errf1 -ne 0 ]
     then
       fm2=$f2
       p_genfile $d0 
     else
       echo "No make-in files ($f2) found in $d0 ...(ignoring)"
     fi
   fi
 done
}
#
p_main 
#
