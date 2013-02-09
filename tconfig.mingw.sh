###!/bin/sh 
#
#  Shell script to configure TC for MinGW and create the Inno setup 
#  (install) script.
#  This script requires a POSIX shell to execute, as well as some 
#  UN*X type utilities such as SED.
#
#  License: TinyCOBOL is covered by GNU General Public License 
#  Copyright (C) 2001-2008  David Essex
#
#  cmd: tconfig.mingw.sh [options]
#  options=hd:i:kl:mr:sv: 
#  options: 
#  -h                     Display this information
#  -b  build              Set release build (default=1)
#  -c                     Build and install format conversion utility (cobf2f)
#  -d 'YYYY/MM/DD'        Set release date (default is current date)
#  -i 'directory'         Set make file install directory (default='C:/MinGW')
#  -k                     Enable file LOCK server feature (default=off)
#  -l  language           Set language (en/es/fr/it/pt_BR/ default=en)
#  -m                     Set MF compatability option on (default=off)
#  -r                     Use readline library
#  -s                     Build Run-Time as a static library only (default=static and DLL)
#  -v 'major.minor.patch' Set release version (default is parsed from configure.in)
#
# 
e0a="invalid number of parms..."
e0b="invalid option(s) "
e0c="TC configure and Inno setup script for MinGW"  
e0d="usage: tconfig.mingw.sh [ options ]\nOptions:\n\
  -h                     Display this information\n\
  -b  build              Set release build (default=1)\n\
  -c                     Build and install format conversion utility (cobf2f)\n\
  -d 'YYYY/MM/DD'        Set release date (default is current date)\n\
  -i 'directory'         Set make file install directory (default='C:/MinGW')\n\
  -m                     Set MF compatability option on (default=off)\n\
  -r                     Use readline library (default=no)\n\
  -s                     Build Run-Time as a static library only (default=static and DLL)
  -v 'major.minor.patch' Set release version (default is parsed from version.txt)\
"  
#  -s                     Build Run-Time as a static library and DLL (default=static library only)\n\
#  -l  language           Set language (en/es/fr/it/pt_BR/ default=en)\n\
#  -k                     Enable file LOCK server feature (default=off)
#
p_print1 ()
{
 for arg in "$@"
 do
#   echo $arg >&2
   printf "$arg\n" >&2
 done
}
#
TCOB_MAJOR_VERSION=''
TCOB_MINOR_VERSION=''
TCOB_PATCH_LEVEL=''
TCOB_RELEASE_VERSION=1
TCOB_VERSION=''
TCOB_RELEASE_DATE=''
tcob_version=$TCOB_VERSION
tcob_mversion=$TCOB_VERSION
tcob_rdate=$TCOB_RELEASE_DATE
tcob_release=$TCOB_RELEASE_VERSION
#
TCOBRUN_MAJOR_VERSION=''
TCOBRUN_MINOR_VERSION=''
TCOBRUN_PATCH_LEVEL=''
TCOBRUN_VERSION=''
TCOBRUN_RELEASE_DATE=''
tcobrun_version=''
#
# os_platform@
os_platform='MinGW'
#
#@tcob_lang@
with_lang=''
tcob_lang=en
host_os=MinGW
#

# NOTE: 
# make sure that 'prefix' and 'prefix_local' are complimentary
#
# @prefix@
#prefix="C:/MinGW/local"
#prefix="C:/MinGW"
prefix="/mingw/local"
#prefix="/mingw"
#prefix=".."
#
# @prefix_local@
#prefix_local="/mingw/local"
prefix_local="/mingw"


# @drive_prefix@
drive_prefix='C:'

# @exec_prefix@
exec_prefix='${prefix}'
# @tcob_install_dir@
tcob_install_dir=${prefix}
#
# @MAKE@
#MAKE=mingw32-make
MAKE=make
#
# @CC@
CCX=gcc.exe
#
# @AS@
ASM=as.exe
#
# @COB@
#COB=htcobol.exe
COB=htcobol
#
# @WINDRES@
WINDRES=windres.exe
#
# @RANLIB@
RANLIB=ranlib.exe
# @AR@
AR=ar.exe
#
# @MV@
MV='mv.exe -f'
#MV='mv /Y'
# @RM@
#RM='rm.exe -f'
RM='rm -f'
#RM=del
#
# @MKDIR@
#MKDIR=mkdir.exe -p
MKDIR=mkdir.exe
#
# @YACC@
YACC=yacc193.exe
#YACC=bison.exe
#@LEX@flex
LEX=flex.exe
#
# @exeext@
EXEEXT=.exe
#
# @INSTALL@
#INSTALL='copy'
INSTALL='install.exe'
# @INSTALL_DATA@
INSTALL_DATA='${INSTALL}'
# @cobbin_default@
#INSTBIN="${prefix}\\\bin"
INSTBIN="${prefix}/bin"
# @cobdir_default@
#INSTRC="${prefix}\\\share\\\htcobol"
INSTRC="${prefix}/share/htcobol"
# @coblib_default@
INSTLIB="${prefix}/lib"
#
# @copybook_path@
#COPYBOOK_PATH="${prefix}/share/htcobol/copybooks;;"
COPYBOOK_PATH="$drive_prefix${prefix}/share/htcobol/copybooks"
#
# @tcob_ld_paths_default@
TCOB_LD_PATHS_DEFAULT="-L$drive_prefix${prefix}/lib -L$drive_prefix${prefix_local}/lib"
#
# @tcob_defaults_path@
TCOB_DEFAULTS_PATH="$drive_prefix${prefix}/share/htcobol"
#
# @optfile_default@
#tcob_optfile_default=htcobolrc
#
# @rtoptfile_path@
#tcob_rtoptfile_path="${prefix}/share/htcobol"
# @rtoptfile_default@
#tcob_rtoptfile_default=htrtconf
#

# @MAKEDEPEND@
MAKEDEPEND=
#

# @CCXFLAGS@
CCXFLAGS=

# @INCLUDES@ - compiler include paths
INCLUDES="-I${drive_prefix}${prefix}/include -I${drive_prefix}${prefix_local}/include -I../lib -I.."

# @LIBS@ - compiler libraries and paths
LIBS="-L${drive_prefix}${prefix}/lib"

# @LIBS@ - cobrun
LIBS_COBRUN="-L${drive_prefix}${prefix}/lib -L${drive_prefix}${prefix_local}/lib -L../lib"
#

# @LDFLAGS@
LDFLAGS=
#

# @tcob_ld_path@
TCOB_LD_PATH="-L${prefix}/lib"
#

# @tcob_ld_args_htcobol@
TCOB_LD_ARGS_HTCOBOL='-lhtcobol'
#
# @tcob_ld_args_db@
TCOB_LD_ARGS_DB='-ldb1'
#
# @tcob_ld_args_isam@
TCOB_LD_ARGS_ISAM='-lvbisam'
#
# @tcob_ld_args_curses@
TCOB_LD_ARGS_CURSES='-lpdcurses'
#
# @tcob_ld_args_m@
#TCOB_LD_ARGS_MATH='-lm'
TCOB_LD_ARGS_MATH=''
#
# @tcob_ld_args_readline@
TCOB_LD_ARGS_READLINE=''
tcob_readline_opt='0'
#
# @tcob_ld_args_dl@
TCOB_LD_ARGS_DL=''
#
# @tcob_shlib_ext@
TCOB_SHLIB_EXT='.dll'
#
# @tcob_ld_args_default@
#TCOB_LD_ARGS_DEFAULT=''
TCOB_LD_ARGS_DEFAULT="$TCOB_LD_ARGS_HTCOBOL $TCOB_LD_ARGS_DB $TCOB_LD_ARGS_ISAM $TCOB_LD_ARGS_CURSES $TCOB_LD_ARGS_READLINE $TCOB_LD_ARGS_MATH $TCOB_LD_ARGS_DL"
# @tcob_ld_args_defaults@
#TCOB_LD_ARGS_DEFAULTS=''
TCOB_LD_ARGS_DEFAULTS="$TCOB_LD_ARGS_DB $TCOB_LD_ARGS_ISAM $TCOB_LD_ARGS_CURSES $TCOB_LD_ARGS_READLINE $TCOB_LD_ARGS_MATH $TCOB_LD_ARGS_DL"
#
#
#/* #undef  USE_MF_COMPATABILITY */
tcob_mfopt='0'
tcob_mfopt1='\/\* \#undef USE_MF_COMPATABILITY \*\/'
tcob_mfopt2='\#define USE_MF_COMPATABILITY 1'
#
# @tcob_str_dash_redefine@
TCOB_STR_DASH_REDEFINE="_2D"
#
# Build Run-Time as a static library and DLL, change make file in 'lib' directory
tcob_shared_libs_opt="shared-libs" 
tcob_shared_libs_install_opt="install-shared-libs" 
#tcob_shared_libs_opt=''
#tcob_shared_libs_install_opt='' 
#
# Build cobrun using static RTL library
tcob_cobrun_build_opt="build-static"
tcob_cobrun_name1_opt='htcobrun'
tcob_cobrun_name2_opt='htcobrun2'
#
# @tcob_manfiles@ 
tcob_manfiles=''
# @tcob_htmlfiles@ 
tcob_htmlfiles='htmlfiles'
# @tcob_textfiles@
tcob_textfiles='textfiles'
#
#
tcob_manfiles=''
tcob_htmlfiles='htmlfiles'
tcob_textfiles='textfiles'
tcob_intman=''
tcob_inthtml='install-htmlfiles'
tcob_inttext='install-textfiles'
#
# @tcob_cobf2f_dir@
tcob_cobf2f_sw='0'
tcob_cobf2f_dir=''
tcob_cobf2f_dir1=''
tcob_cobf2f_man=''
tcob_cobf2f_html=''
tcob_cobf2f_text=''
tcob_cobf2f_intman=''
tcob_cobf2f_inthtml=''
tcob_cobf2f_inttext=''
#
#@mandir@
mandir=''
#@tcob_docdir@
#tcob_docdir="${prefix}/doc/htcobol-$tcob_version"
tcob_docdir=''
#
errf1=0
#
# Get information from configure.in file
#
p_set_version ()
{
#
if [ -z "$tcob_version" ] 
then
   TCOB_MAJOR_VERSION=`grep '^TCOB_MAJOR_VERSION' version.txt | cut -f2 -d'='`
   TCOB_MINOR_VERSION=`grep '^TCOB_MINOR_VERSION' version.txt | cut -f2 -d'='`
   TCOB_PATCH_LEVEL=`grep  '^TCOB_PATCH_LEVEL' version.txt | cut -f2 -d'='`
   TCOB_VERSION=$TCOB_MAJOR_VERSION.$TCOB_MINOR_VERSION.$TCOB_PATCH_LEVEL
   tcob_version=$TCOB_VERSION
   tcob_mversion=$TCOB_MAJOR_VERSION.$TCOB_MINOR_VERSION
else 
   str1=`echo "$tcob_version" | sed 's|[0-9]*\.[0-9]*\.[0-9]*||g'`
#   echo "debug: str1=$str1;"
   if [ -z "$str1" ] 
   then 
      TCOB_MAJOR_VERSION=`echo "$tcob_version" | cut -f1 -d'.'`
      TCOB_MINOR_VERSION=`echo "$tcob_version" | cut -f2 -d'.'`
      TCOB_PATCH_LEVEL=`echo "$tcob_version" | cut -f3 -d'.'`
      TCOB_VERSION=$TCOB_MAJOR_VERSION.$TCOB_MINOR_VERSION.$TCOB_PATCH_LEVEL
      tcob_version=$TCOB_VERSION
      tcob_mversion=$TCOB_VERSION
   else
      e00="error: version=$tcob_version is invalid ...aborting"
      p_print1 "$e00"
      exit 1
   fi
fi
#
#tcob_docdir="${prefix}/doc/htcobol-$tcob_version"
#
}
#
p_set_release_date ()
{
#
if [ -z "$tcob_rdate" ] 
then
#   TCOB_RELEASE_DATE=`date +%Y\\/%m\\/%d | sed 's.\/.\\\/.g'`
   TCOB_RELEASE_DATE=`date +%Y/%m/%d`
   tcob_rdate=$TCOB_RELEASE_DATE
else
   str1=`echo "$tcob_rdate" | sed 's|[12][0-9]\{3\}\/[0-9]\{1,2\}\/[0-9]\{1,2\}||g'`
   if [ -z "$str1" ] 
   then 
#      TCOB_RELEASE_DATE=`echo "$tcob_rdate" | sed 's.\/.\\\/.g'` 
      TCOB_RELEASE_DATE="$tcob_rdate"
      tcob_rdate=$TCOB_RELEASE_DATE
   else
      e00="error: release date=$tcob_rdate is invalid ...aborting"
      p_print1 "$e00"
      exit 1
   fi
fi
}
#
p_set_cobrun_version ()
{
TCOBRUN_MAJOR_VERSION=`grep '^TCOBRUN_MAJOR_VERSION' cobrun/tcrunversion.txt | cut -f2 -d'='`
TCOBRUN_MINOR_VERSION=`grep  '^TCOBRUN_MINOR_VERSION' cobrun/tcrunversion.txt | cut -f2 -d'='`
TCOBRUN_PATCH_LEVEL=`grep  '^TCOBRUN_PATCH_LEVEL' cobrun/tcrunversion.txt | cut -f2 -d'='`
TCOBRUN_VERSION=$TCOBRUN_MAJOR_VERSION.$TCOBRUN_MINOR_VERSION.$TCOBRUN_PATCH_LEVEL
TCOBRUN_RELEASE_DATE=$TCOB_RELEASE_DATE
tcobrun_version=$TCOBRUN_VERSION
tcobrun_rdate=$TCOB_RELEASE_DATE
#
}
#
# Check and set language option 
#
p_check_lang_otion ()
{
#
 case "x$with_lang" in
     x) tcob_lang='en'   ;;
     xen) tcob_lang='en' ;;
#     xes) tcob_lang='es' ;;
#     xfr) tcob_lang='fr' ;;
#     xit) tcob_lang='it' ;;
#     xpt_BR) tcob_lang='pt_BR' ;;
     *)  echo "Language option '$with_lang' not available, defaulting to language=en (English)" 
         tcob_lang='en';;
 esac
}
#
# Create cobrun version 
#
p_cobrun () 
{
#
 p_check_file_exists cobrun/tcrunversion.h
 if [ $errf1 -eq 0 ]
 then
    cat cobrun/tcrunversion.h.in | \
    sed \
     -e "s|@TCOBRUN_MAJOR_VERSION@|$TCOBRUN_MAJOR_VERSION|g" \
     -e "s|@TCOBRUN_MINOR_VERSION@|$TCOBRUN_MINOR_VERSION|g" \
     -e "s|@TCOBRUN_PATCH_LEVEL@|$TCOBRUN_PATCH_LEVEL|g" \
     -e "s|@TCOBRUN_VERSION@|$tcobrun_version|g" \
     -e "s|@TCOBRUN_RELEASE_DATE@|$tcobrun_rdate|g" \
     -e "s|@host_os@|$host_os|g" \
    > cobrun/tcrunversion.h
 fi
#
}
#
# Create main compiler version and command line help files
#
p_cob () 
{
 p_check_file_exists compiler/htversion.h
 if [ $errf1 -eq 0 ]
 then
    p_sed_version compiler/htversion.h.in compiler/htversion.h
#     cat compiler/htversion.h.in | \
#     sed \
#      -e "s|@TCOB_MAJOR_VERSION@|$TCOB_MAJOR_VERSION|g" \
#      -e "s|@TCOB_MINOR_VERSION@|$TCOB_MINOR_VERSION|g" \
#      -e "s|@TCOB_PATCH_LEVEL@|$TCOB_PATCH_LEVEL|g" \
#      -e "s|@TCOB_VERSION@|$tcob_version|g" \
#      -e "s|@TCOB_RELEASE_DATE@|$tcob_rdate|g" \
#      -e "s|@host_os@|$host_os|g" \
#     > compiler/htversion.h
 fi
#
}
#
# Create config 
# 
p_config ()
{
#
# -e "s|@tcobpp_lang@|$tcob_lang|g" 
# -e "s|@optfile_default@|$tcob_optfile_default|g" 
# -e "s|@rtoptfile_path@|$tcob_rtoptfile_path|g" 
# -e "s|@rtoptfile_default@|$tcob_rtoptfile_default|g" 
#
 p_check_file_exists htconfig.h
 if [ $errf1 -eq 0 ]
 then
    if [ $tcob_mfopt == "0" ]
    then
       tcob_mfopt2=$tcob_mfopt1
    fi
    cat htconfig.mingw.h.in | \
    sed \
      -e "s|@tcob_ld_args_default@|$TCOB_LD_ARGS_DEFAULT|g" \
      -e "s|@tcob_ld_paths_default@|$TCOB_LD_PATHS_DEFAULT|g" \
      -e "s|@tcob_lang@|$tcob_lang|g" \
      -e "s|@install_dir@|$tcob_install_dir|g" \
      -e "s|@tcob_str_dash_redefine@|$TCOB_STR_DASH_REDEFINE|" \
      -e "s|$tcob_mfopt1|$tcob_mfopt2|" \
      -e "s|@tcob_defaults_path@|$TCOB_DEFAULTS_PATH|g" \
      > htconfig.h
 fi
#
}

#
# SETUP cobf2f files
#
p_set_cobf2f ()
{
#
 tcob_cobf2f_sw='1'
# tcob_cobf2f_dir='cobf2f'
# tcob_cobf2f_dir1='utils/cobf2f'
 tcob_cobf2f_dir='utils/cobf2f'
# tcob_cobf2f_man='manfile3'
 tcob_cobf2f_html='htmlfile3'
 tcob_cobf2f_text='textfile3'
# tcob_cobf2f_intman='install-manfile3'
 tcob_cobf2f_inthtml='install-htmlfile3'
 tcob_cobf2f_inttext='install-textfile3'
#
}
#
#
# SED files
#
# -e "s|@optfile_default@|$tcob_optfile_default|g" 
# -e "s|@rtoptfile_path@|$tcob_rtoptfile_path|g" 
# -e "s|@rtoptfile_default@|$tcob_rtoptfile_default|g" 
#
p_sed ()
{
#
 cat "$1" | \
 sed \
    -e "s|@os_platform@|$os_platform|g" \
    -e "s|@SET_MAKE@||g" \
    -e "s|@prefix@|$prefix|g" \
    -e "s|@prefix_local@|$prefix_local|g" \
    -e "s|@drive_prefix@|$drive_prefix|g" \
    -e "s|@exec_prefix@|$exec_prefix|g" \
    -e "s|@AR@|$AR|g" \
    -e "s|@AS@|$ASM|g" \
    -e "s|@CC@|$CCX|g" \
    -e "s|@CCXFLAGS@|$CCXFLAGS|g" \
    -e "s|@COB@|$COB|g" \
    -e "s|@INCLUDES@|$INCLUDES|g" \
    -e "s|@INSTALL@|$INSTALL|g" \
    -e "s|@INSTALL_DATA@|$INSTALL_DATA|g" \
    -e "s|@LDFLAGS@|$LDFLAGS|g" \
    -e "s|@LEX@|$LEX|g" \
    -e "s|@LIBS@|$LIBS_COBRUN|g" \
    -e "s|@LIBS@|$LIBS|g" \
    -e "s|@MAKE@|$MAKE|g" \
    -e "s|@MAKEDEPEND@|$MAKEDEPEND|g" \
    -e "s|@MKDIR@|$MKDIR|g" \
    -e "s|@MV@|$MV|g" \
    -e "s|@RANLIB@|$RANLIB|g" \
    -e "s|@RM@|$RM|g" \
    -e "s|@WINDRES@|$WINDRES|g" \
    -e "s|@YACC@|$YACC|g" \
    -e "s|@cobbin_default@|$INSTBIN|g" \
    -e "s|@cobdir_default@|$INSTRC|g" \
    -e "s|@coblib_default@|$INSTLIB|g" \
    -e "s|@copybook_path@|$COPYBOOK_PATH|g" \
    -e "s|@exeext@|$EXEEXT|g" \
    -e "s|@tcob_ld_args_curses@|$TCOB_LD_ARGS_CURSES|g" \
    -e "s|@tcob_ld_args_db@|$TCOB_LD_ARGS_DB|g" \
    -e "s|@tcob_ld_args_isam@|$TCOB_LD_ARGS_ISAM|g" \
    -e "s|@tcob_ld_args_dl@|$TCOB_LD_ARGS_DL|g" \
    -e "s|@tcob_ld_args_htcobol@|$TCOB_LD_ARGS_HTCOBOL|g" \
    -e "s|@tcob_ld_args_m@|$TCOB_LD_ARGS_MATH|g" \
    -e "s|@tcob_ld_args_readline@|$TCOB_LD_ARGS_READLINE|g" \
    -e "s|@tcob_ld_args_default@|$TCOB_LD_ARGS_DEFAULT|g" \
    -e "s|@tcob_ld_args_defaults@|$TCOB_LD_ARGS_DEFAULTS|g" \
    -e "s|@tcob_ld_paths_default@|$TCOB_LD_PATHS_DEFAULT|g" \
    -e "s|@tcob_ld_path@|$TCOB_LD_PATH|g" \
    -e "s|@install_dir@|$tcob_install_dir|g" \
    -e "s|@tcob_defaults_path@|$TCOB_DEFAULTS_PATH|g" \
    -e "s|@tcob_shared_libs_install_opt@|$tcob_shared_libs_install_opt|g" \
    -e "s|@tcob_shared_libs_opt@|$tcob_shared_libs_opt|g" \
    -e "s|@tcob_version@|$TCOB_VERSION|g" \
    -e "s|@tcob_cobrun_build_opt@|$tcob_cobrun_build_opt|g" \
    -e "s|@tcob_cobrun_name1_opt@|$tcob_cobrun_name1_opt|g" \
    -e "s|@tcob_cobrun_name2_opt@|$tcob_cobrun_name2_opt|g" \
    -e "s|@tcob_cobf2f_dir@|$tcob_cobf2f_dir|g" \
    -e "s|@tcob_cobf2f_man@|$tcob_cobf2f_man|g" \
    -e "s|@tcob_cobf2f_html@|$tcob_cobf2f_html|g" \
    -e "s|@tcob_cobf2f_text@|$tcob_cobf2f_text|g" \
    -e "s|@tcob_cobf2f_intman@|$tcob_cobf2f_intman|g" \
    -e "s|@tcob_cobf2f_inthtml@|$tcob_cobf2f_inthtml|g" \
    -e "s|@tcob_cobf2f_inttext@|$tcob_cobf2f_inttext|g" \
    -e "s|@tcob_manfiles@|$tcob_manfiles|g" \
    -e "s|@tcob_htmlfiles@|$tcob_htmlfiles|g" \
    -e "s|@tcob_textfiles@|$tcob_textfiles|g" \
    -e "s|@tcob_lang@|$tcob_lang|g" \
    -e "s|@mandir@|$mandir|g" \
    -e "s|@tcob_docdir@|$tcob_docdir|g" \
    -e "s|@tcob_intman@|$tcob_intman|g" \
    -e "s|@tcob_inthtml@|$tcob_inthtml|g" \
    -e "s|@tcob_inttext@|$tcob_inttext|g" \
 > "$2"
#
}
#
#
# Set version and release date in resource files
#
p_sed_version ()
{
#
 cat $1 | \
 sed \
  -e "s|@TCOB_MAJOR_VERSION@|$TCOB_MAJOR_VERSION|g" \
  -e "s|@TCOB_MINOR_VERSION@|$TCOB_MINOR_VERSION|g" \
  -e "s|@TCOB_PATCH_LEVEL@|$TCOB_PATCH_LEVEL|g" \
  -e "s|@TCOB_VERSION@|$tcob_version|g" \
  -e "s|@TCOB_RELEASE_DATE@|$tcob_rdate|g" \
  -e "s|@host_os@|$host_os|g" \
 > $2
#
}
#
# Create make and WIN32 resource files
#
p_main ()
{
#
# TCOB_LD_ARGS_DEFAULT="$TCOB_LD_ARGS_DB $TCOB_LD_ARGS_ISAM $TCOB_LD_ARGS_CURSES $TCOB_LD_ARGS_READLINE $TCOB_LD_ARGS_MATH $TCOB_LD_ARGS_DL"
#
 p_check_file_exists Makefile
 if [ $errf1 -eq 0 ]
 then
    p_sed Makefile.mingw.in Makefile
 fi
#
 p_check_file_exists misclib/Makefile
 if [ $errf1 -eq 0 ]
 then
    p_sed misclib/Makefile.mingw.in misclib/Makefile
 fi
# 
 p_check_file_exists compiler/Makefile
 if [ $errf1 -eq 0 ]
 then
    p_sed compiler/Makefile.mingw.in compiler/Makefile
 fi
#
 p_check_file_exists lib/Makefile
 if [ $errf1 -eq 0 ]
 then
    p_sed lib/Makefile.mingw.in lib/Makefile
 fi

# 
 p_check_file_exists compiler/htcobolrc
 if [ $errf1 -eq 0 ]
 then
    p_sed compiler/htcobolrc.mingw.in compiler/htcobolrc
 fi
#
 p_check_file_exists lib/htcobolrt.rc
 if [ $errf1 -eq 0 ]
 then
#    p_sed lib/htcobolrt.rc.in lib/htcobolrt.rc
    p_sed_version lib/htcobolrt.rc.in lib/htcobolrt.rc
#     cat lib/htcobolrt.rc.in | \
#     sed \
#      -e "s|@TCOB_MAJOR_VERSION@|$TCOB_MAJOR_VERSION|g" \
#      -e "s|@TCOB_MINOR_VERSION@|$TCOB_MINOR_VERSION|g" \
#      -e "s|@TCOB_PATCH_LEVEL@|$TCOB_PATCH_LEVEL|g" \
#      -e "s|@TCOB_VERSION@|$tcob_version|g" \
#      -e "s|@TCOB_RELEASE_DATE@|$tcob_rdate|g" \
#      -e "s|@host_os@|$host_os|g" \
#     > lib/htcobolrt.rc
 fi
#
 p_check_file_exists cobrun/Makefile
 if [ $errf1 -eq 0 ]
 then
   p_sed cobrun/Makefile.mingw.in cobrun/Makefile
 fi
#       -e "s|@COB@|$COB|g" 
# 
#  p_check_file_exists cobrun/test.code/Makefile
#  if [ $errf1 -eq 0 ]
#  then
#    p_sed cobrun/test.code/Makefile.mingw.in cobrun/test.code/Makefile
#  fi
#  
 p_check_file_exists info/Makefile
 if [ $errf1 -eq 0 ]
 then
   p_sed info/Makefile.in info/Makefile
 fi
#  
# 
 p_check_file_exists test_suite/Makefile
 if [ $errf1 -eq 0 ]
 then
   p_sed test_suite/Makefile.in test_suite/Makefile
 fi
#   
# 
 p_check_file_exists test_suite/coboltest.inc
 if [ $errf1 -eq 0 ]
 then
   p_sed test_suite/coboltest.inc.in test_suite/coboltest.inc
 fi
#   
# 
 p_check_file_exists test_suite/nist/Makefile
 if [ $errf1 -eq 0 ]
 then
   p_sed test_suite/nist/Makefile.in test_suite/nist/Makefile
 fi
#  
# 
 p_check_file_exists test_suite/nist/makeConfig.inc
 if [ $errf1 -eq 0 ]
 then
   p_sed test_suite/nist/makeConfig.inc.in test_suite/nist/makeConfig.inc
 fi
#  
# 
 if [ $tcob_cobf2f_sw -eq 1 ]
 then
   p_check_file_exists utils/cobf2f/Makefile
   if [ $errf1 -eq 0 ]
   then
     p_sed utils/cobf2f/Makefile.in utils/cobf2f/Makefile
   fi
 fi
#  
# 
}
#
#
# Create the test.code directory make files template
# Create the test.code/copybooks directory make file
#
p_testcode () 
{
#  
 p_check_file_exists test.code/Makefile
 if [ $errf1 -eq 0 ]
 then
   p_sed test.code/Makefile.in test.code/Makefile
 fi
#  
# 
 p_check_file_exists mconfig.inc
 if [ $errf1 -eq 0 ]
 then
   p_sed test.code/mconfig.inc.in test.code/mconfig.inc
 fi
#
# p_check_file_exists test.code/copybooks/Makefile
# if [ $errf1 -eq 0 ]
# then
#   p_sed test.code/copybooks/Makefile.in test.code/copybooks/Makefile
# fi
}
#
#
# Create the Inno setup script from template
#
p_isetup () 
{
 p_check_file_exists tcobol.iss
 if [ $errf1 -eq 0 ]
 then
    t1=`echo ' ' | tr ' ' '\15'`
#   -e "s|$|$t1|" 
#   sed -c 
#    p_sed  info/isetup/tcobol.iss.in  tcobol.iss
    cat info/isetup/tcobol.iss.in | \
    sed \
        -e "s|@TCOB_VERSION@|$TCOB_MAJOR_VERSION.$TCOB_MINOR_VERSION|g" \
        -e "s|@TCOB_RELEASE_VERSION@|$tcob_release|g" \
        -e "s|$|$t1|" \
    > tcobol.iss
 fi
}
#
#
# Check if make files install directory exists
#
p_check_install_dir ()
{
#
 if [ -d "$tcob_install_dir" ]
 then
   e22="WARNING: \n\
Install directory '$tcob_install_dir' exists.\n\
Directory contents will be over-written during installation process. \n"
#
   printf "$e22"
 fi
}
#
#
# Set variables 
#
p_set_vars ()
{
#
 p_check_install_dir 
 prefix="$tcob_install_dir"
 drive_prefix="$drive_prefix"
 exec_prefix='${prefix}'
 INSTBIN="${prefix}/bin"
 INSTRC="${prefix}/share/htcobol"
 INSTLIB="${prefix}/lib"
 COPYBOOK_PATH="$drive_prefix${prefix}/share/htcobol/copybooks"
 TCOB_DEFAULTS_PATH="$drive_prefix${prefix}/share/htcobol"
 tcob_rtoptfile_path="${prefix}/share/htcobol"
 INCLUDES="-I${drive_prefix}${prefix}/include -I${drive_prefix}${prefix_local}/include -I../lib -I.."
 LIBS="-L${prefix}/lib"
 LIBS_COBRUN="-L${prefix}/lib -L${drive_prefix}${prefix_local}/lib -L../lib"
 TCOB_LD_PATH="-L${prefix}/lib"
# tcob_docdir="${prefix}/doc/htcobol-$tcob_version"
 tcob_docdir="htcobol-$tcob_mversion"
#
}
#
#
# Check if make files install directory exists
#
p_check_file_exists ()
{
#
 errf1=0
 if [ -f "$1" ]
 then
   e22="file exists, overwrite '$1' ? y/n[n]:"
   printf "$e22"
   read reply
   if [ "$reply" != "y" ]
   then
      errf1=5
   fi
 fi
}
#
#while getopts hd:i:kl:mr:sv: opt
#while getopts hd:i:kmr:sv: opt
while getopts hb:cd:i:mrsv: opt
do
  case "$opt"
  in
    h)
      p_print1 "$e0c" "$e0d"
      exit 1
      ;; 
    b)
      tcob_release=$OPTARG
      ;; 
    c)
      p_set_cobf2f
      ;; 
    d)
      tcob_rdate=$OPTARG
      ;; 
    i)
      tcob_install_dir=$OPTARG
#  sed 's.\/.\\\/.g'
#      tcob_install_dir0=`echo "$OPTARG" |  sed "s|'\'|'\\\'|g"`
#      tcob_install_dir0=`echo "$OPTARG" | sed 's|\\|\\\/|g'`
#      echo "OPTARG=$OPTARG, tcob_install_dir=$tcob_install_dir;"
#      exit 1
#      tcob_install_dir=`echo "$OPTARG" | tr '\134' '\57'`
      ;; 

#     k)
#      tcob_lockserver_opt='1'
#      ;; 

#     l)
#      with_lang=$OPTARG
#      p_check_lang_otion
#      ;; 
    m)
      tcob_mfopt='1'
      ;; 
    r)
      tcob_readline_opt='1'
      TCOB_LD_ARGS_READLINE='-lreadline'
      ;; 
# Build Run-Time as a static library and DLL
    s)
      tcob_shared_libs_opt='' 
      tcob_shared_libs_install_opt='' 
      ;; 
    v)
      tcob_version=$OPTARG
      ;; 
    \?)
#      e1="$e0b$opt ..."
      p_print1 "$e0c" "$e0d"
      exit 1
      ;; 
  esac  
done
#
#p_check_install_dir
#
p_set_release_date
p_set_version
p_set_cobrun_version
#
p_set_vars
#
p_main
#
p_config
#
p_cobrun
#
p_cob
#
p_testcode
#
p_isetup
#
