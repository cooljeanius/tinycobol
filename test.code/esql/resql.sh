#!/bin/bash - 
#
#  Shell script to run sample COBOL ESQL program using the Firebird SQL database 
#  cmd: resql.sh { all | esql.create | esql.insert | esql.list | esql.rollback | esql.table | esql.trans }
#  David Essex		September 2007
#
e0a="invalid number of parms..."
e0b="invalid option(s) "
e0c="Shell script to run sample COBOL ESQL program using the Firebird SQL database"  
e0d="cmd: resql.sh { all | esql.create | esql.insert | esql.list | esql.rollback | esql.table | esql.trans }"  
#
p_print1 ()
{
for arg in "$@"
do
   echo $arg >&2
done
}
#
if [ "$#" -eq 0 ]
then
   p_print1 "$e0a" "$e0c" "$e0d"
   exit 1
fi
#
export INTERBASE=/opt/interbase
export ISC_USER=SYSDBA
export ISC_PASSWORD=masterkey
#
fl01='esql.create esql.table esql.insert esql.trans esql.rollback esql.list'
#
p_run_prg () 
{
 for p0 in $@
 do
   echo "program $p0"
   ./$p0
 done 
}
#
opt=''
while [ "$#" -gt 0 ]
do
  opt="$1"
  case "$opt"
  in
    all)
      p_run_prg "$fl01"
      ;; 
    esql.create)
      p_run_prg $opt
      ;; 
    esql.table)
      p_run_prg $opt
      ;; 
    esql.insert)
      p_run_prg $opt
      ;; 
    esql.trans)
      p_run_prg $opt
      ;; 
    esql.rollback)
      p_run_prg $opt
      ;; 
    esql.list)
      p_run_prg $opt
      ;; 
    *)
      e1="Invalid option(s) '$opt' entered" 
      p_print1 "$e1" "$e0c" "$e0d"
      exit 1
      ;; 
  esac  
  shift
done
#
