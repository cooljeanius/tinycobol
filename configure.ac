#
# TinyCOBOL.
#
# Process this file with autoconf to produce a configure script.
#

# Minimum Autoconf version required.
AC_PREREQ([2.10])
AC_INIT([TinyCOBOL],[0.63.109],[tiny-cobol-users@lists.sourceforge.net],[tinycobol-0.64.tar.gz])
AC_CONFIG_SRCDIR([htconfig.h.in])
AC_CONFIG_MACRO_DIR([m4])

TCOB_MAJOR_VERSION=0
TCOB_MINOR_VERSION=0
TCOB_PATCH_LEVEL=0
TCOB_MAJOR_VERSION=`grep '^TCOB_MAJOR_VERSION' version.txt | cut -f2 -d'='`
TCOB_MINOR_VERSION=`grep  '^TCOB_MINOR_VERSION' version.txt | cut -f2 -d'='`
TCOB_PATCH_LEVEL=`grep  '^TCOB_PATCH_LEVEL' version.txt | cut -f2 -d'='`
#
TCOB_VERSION=$TCOB_MAJOR_VERSION.$TCOB_MINOR_VERSION.$TCOB_PATCH_LEVEL
TCOB_RELEASE_DATE=2003/09/11
TCOB_RELEASE_DATE=`date +%Y/%m/%d`
tcob_version=$TCOB_VERSION
#
TCOBRUN_MAJOR_VERSION=`grep '^TCOBRUN_MAJOR_VERSION' cobrun/tcrunversion.txt | cut -f2 -d'='`
TCOBRUN_MINOR_VERSION=`grep  '^TCOBRUN_MINOR_VERSION' cobrun/tcrunversion.txt | cut -f2 -d'='`
TCOBRUN_PATCH_LEVEL=`grep  '^TCOBRUN_PATCH_LEVEL' cobrun/tcrunversion.txt | cut -f2 -d'='`
TCOBRUN_VERSION=$TCOBRUN_MAJOR_VERSION.$TCOBRUN_MINOR_VERSION.$TCOBRUN_PATCH_LEVEL
TCOBRUN_RELEASE_DATE=$TCOB_RELEASE_DATE
#

AC_CONFIG_HEADER([htconfig.h])

# 
# Check for System OS name
AC_CANONICAL_SYSTEM
# Checks for host/OS name
AC_CANONICAL_HOST
AC_CANONICAL_TARGET
AC_DEFINE_UNQUOTED(OS_TYPE, "$host_os")
AC_EXEEXT
AM_INIT_AUTOMAKE

COB='htcobol'
os_platform=''

LIBS_BK="$LIBS -L../../lib"
INCLUDES_BK="$INCLUDES -I../lib -I../"
exeext=''
shared_lib_extension='.so'
need_underscode='no'
tcob_ld_args_m='m'
curses_header='ncurses.h'
curses_library='ncurses'
LIBS="$LIBS_BK"
INCLUDES="$INCLUDES_BK"
drive_prefix=''

# Check for executable suffix
# Set include and libraries paths
# Set curses include and library 
# Set math library
# Set executable extention (exeext), if any 
# Set shared library extension
#
case "$host_os" in
  *cygwin) 
        tcob_ld_args_m="cygwin" 
        exeext='.exe'
        shared_lib_extension='.dll'
        need_underscode='yes'
        os_platform='Cygwin'
        drive_prefix='c:/'
        ;;
  *mingw32)
        curses_header='pdcurses.h'
        curses_library='pdcurses'
        exeext='.exe'
        shared_lib_extension='.dll'
        need_underscode='yes'
        os_platform='MinGW'
        drive_prefix='c:/'
        ;;
   *mingw)
        curses_header='pdcurses.h'
        curses_library='pdcurses'
        exeext='.exe'
        shared_lib_extension='.dll'
        need_underscode='yes'
        os_platform='MinGW'
        drive_prefix='c:/'
        ;;
esac
#

LIBS_M="$LIBS"
INCLUDES_M="$INCLUDES"

echo  "OS host host_os=${host_os};"

# Display build version
AC_MSG_CHECKING(build version)
AC_MSG_RESULT($TCOB_VERSION)
AC_MSG_NOTICE(build version is $TCOB_VERSION)

# Set the compiler language option
#      [  --with-lang=[ARG]         set language [en/fr/it/pt_BR/es default=en]],
# Option removed due to lack of translations
tcob_lang=''
tcob_lang='en'
AC_ARG_WITH(with-lang,
      [  --with-lang=[ARG]         set language [(en/pt_BR default=en)]],
      ,
      ,
)
echo "debug 0a: with_lang=$with_lang, tcob_lang=$tcob_lang" 
case "x$with_lang" in
     x) tcob_lang='en';;
     xen) tcob_lang='en';;
     xfr) tcob_lang='fr';;
     xit) tcob_lang='it';;
     xpt_BR) tcob_lang='pt_BR';;
     xes) tcob_lang='es';;
     *)  echo "Language option '$with_lang' not available, defaulting to language=en (English)" 
         tcob_lang='en';;
esac
echo "debug 0b: with_lang=$with_lang, tcob_lang=$tcob_lang" 

# Set the compiler 
c_compiler="gcc"
AC_ARG_WITH(with-C-compiler,
      [  --with-C-compiler=[ARG]   use C compiler [(default=gcc)]],
      ,
      ,
)
#      c_compiler="gcc",
#      c_compiler=$with_compiler
echo "debug 1: compiler c_compiler:${c_compiler}: with_compiler:${with_compiler}:" 
if test "x$with_C_compiler" = "x"; then
      c_compiler="gcc"
else
      c_compiler=$with_C_compiler
fi
echo "debug 2: compiler c_compiler:${c_compiler}: with_compiler:${with_compiler}:" 

# the prefix
# ==========
#
# move this earlier in the script... anyone know why this is handled
# in such a bizarre way?
test "x$prefix" = xNONE && prefix=$ac_default_prefix
dnl Let make expand exec_prefix.
test "x$exec_prefix" = xNONE && exec_prefix='${prefix}'
if test "x$prefix" = xNONE && prefix=$ac_default_prefix ; then
   prefix_local="/usr"
else
   prefix_local=$ac_default_prefix
fi

# Checks for required programs
#
AC_PROG_AWK
AC_PROG_CC
AC_CHECK_PROG(CC, "$c_compiler", "$c_compiler", no)
echo "debug 3a: compiler c_compiler:${c_compiler}: ccx:$ccx: CC:$CC:" 
if test "${CC}" = "no" ; then
   AC_MSG_ERROR(C compiler not found... aborting)
fi
echo "debug 3b: compiler c_compiler:${c_compiler}: ccx:$ccx: CC:$CC:" 
AC_PROG_CXX
# 
AM_PROG_AS
AC_CHECK_PROG(AS, as, as, as)

asx_cmd="${AS}"
ccx_cmd="${CC}"

AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET

AC_PROG_RANLIB
AC_CHECK_PROG(RANLIB, ranlib, ranlib, ranlib)
AC_CHECK_PROG(AR, ar, ar, ar)
AC_PROG_LIBTOOL
AC_LIBTOOL_WIN32_DLL

ranlibx_cmd="${RANLIB}"
arx_cmd="${AR}"

AC_PROG_LEX
lex_name="flex"
AC_ARG_WITH(with-lex,
      [  --with-lex=[ARG]          use LEX [(default=flex)]],
      ,
      ,
)
if test "x$with_lex" != "x"; then
      lex_name=$with_lex
fi
AC_CHECK_PROG(FLEX, flex, flex, no)
AC_CHECK_PROG(LEX, "$lex_name", "$lex_name", no)
if test "${LEX}" = "no" ; then
   AC_MSG_ERROR(required program not found... aborting)
fi

# 
yacc_name="bison"
yacc_prefix_compiler="htcobol"
AC_ARG_WITH(with-yacc,
      [  --with-yacc=[ARG]         use YACC [(default=bison)]],
      ,
      ,
)
if test "x$with_yacc" = "x"; then
      yacc_name="bison"
else
      yacc_name=$with_yacc
fi
#
AC_PROG_YACC
AC_CHECK_PROG(YACC, "$yacc_name", "$yacc_name", no)
#
if test "${YACC}" = "no" ; then
   AC_MSG_ERROR(Compiler compiler (i.e. Berkeley's YACC version 1.9.3 or Bison) not found... aborting)
else
   if test "${YACC}" = "yacc193" ; then
      yacc_prefix_compiler="y"
   fi
fi
#

# no longer used to expand tabs 
AC_CHECK_PROG(EXPAND, expand, expand, no) 
#   AC_MSG_ERROR(program not found required by pre-processor... aborting)
AC_PATH_PROG(expand_cmd_path, expand, no) 
if test "${expand_cmd_path}" = "no" ; then
   echo "warning: cobf2f utility may not work properly without tab expand utility"
fi

# Checks for libraries.
# FIXME: Replace `main' with a function in `-lX11':
AC_CHECK_LIB([X11], [main])
AC_PATH_X
# FIXME: Replace `main' with a function in `-lcrypt':
AC_CHECK_LIB([crypt], [main])
# FIXME: Replace `main' with a function in `-lgds':
AC_CHECK_LIB([gds], [main])
# FIXME: Replace `main' with a function in `-lhtcobol':
AC_CHECK_LIB([htcobol], [main])
# FIXME: Replace `main' with a function in `-lpq':
AC_CHECK_LIB([pq], [main])
# FIXME: Replace `main' with a function in `-ltcl':
AC_CHECK_LIB([tcl], [main])
# AX_* macros require the autoconf-archive package
AX_PROG_TCL
# FIXME: Replace `main' with a function in `-ltestz1':
AC_CHECK_LIB([testz1], [main])
# FIXME: Replace `main' with a function in `-ltestz2':
AC_CHECK_LIB([testz2], [main])
# FIXME: Replace `main' with a function in `-ltk':
AC_CHECK_LIB([tk], [main])

dnl Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([alloca.h ctype.h dlfcn.h errno.h fcntl.h float.h getopt.h libintl.h limits.h malloc.h stdio.h stdlib.h string.h strings.h sys/param.h sys/stat.h sys/time.h sys/types.h termios.h unistd.h utime.h wchar.h])

# Intialize for ltdl library tests.
use_ltdl_lib="0"
ltdl_default="0"
## Check for libltdl header files.
ltdl_header="0"
AC_CHECK_HEADERS(ltdl.h, ltdl_header="1")

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_C_CONST
AC_TYPE_OFF_T
AC_TYPE_SIZE_T
AC_STRUCT_TM
# gt_* macros require gettext
gt_TYPE_WCHAR_T

# Checks for library functions.
AC_FUNC_FORK
AC_FUNC_MALLOC
AC_FUNC_MKTIME
AC_FUNC_REALLOC
AC_FUNC_MEMCMP
AC_FUNC_ALLOCA
AC_FUNC_VPRINTF
AC_CHECK_FUNCS([atexit dup2 fcntl gettimeofday memmove memset pow putenv regcomp setlocale sqrt strerror strcasecmp strchr strrchr strcspn strdup strerror strncasecmp strspn strstr strtol])

# Set Evaluate debugging options.
#--enable-feature
# 
#feature_abc="0"
#AC_ARG_ENABLE(abc,
#	[  --enable-abc=ARG          set fature abc on or off ],
##        debug_default="1"
#        echo  "enable-abc=$enable_abc;"
#)

# Evaluate debugging options.

# Set debug compile switches 
debug_default="0"
AC_ARG_ENABLE(debug,
	[  --enable-debug          set C compiler debug option on [-g] ],
        debug_default="1"
)

AC_ARG_ENABLE(debug-all,
	[  --enable-debug-all      enable all debug options],
	AC_DEFINE(DEBUG_COMPILER)
	AC_DEFINE(PICTURE_TESTING)
	AC_DEFINE(DEBUG_SCANNER)
	AC_DEFINE(DEBUG_RTS)
	AC_DEFINE(DEBUG_MOVE_RTS)
        debug_default="1"
)

# Evaluate debugging options.
AC_ARG_ENABLE(debug-comp,
	[  --enable-debug-comp     enable compiler and scanner debug options],
	AC_DEFINE(DEBUG_COMPILER)
	AC_DEFINE(PICTURE_TESTING)
	AC_DEFINE(DEBUG_SCANNER)
	AC_DEFINE(DEBUG_RTS)
        debug_default="1"
)

AC_ARG_ENABLE(debug-compiler,
	[  --enable-debug-compiler enable compiler debug option],
	AC_DEFINE(DEBUG_COMPILER)
        debug_default="1"
)

AC_ARG_ENABLE(debug-scanner,
	[  --enable-debug-scanner  enable scanner debug option],
	AC_DEFINE(DEBUG_SCANNER)
        debug_default="1"
)

AC_ARG_ENABLE(debug-rts,
	[  --enable-debug-rts      enable debug Run-Time option],
	AC_DEFINE(DEBUG_RTS)
	AC_DEFINE(DEBUG_MOVE_RTS)
        debug_default="1"
)

AC_ARG_ENABLE(debug-rts-move,
	[  --enable-debug-rts-move enable debug Run-Time Move routines option],
	AC_DEFINE(DEBUG_MOVE_RTS)
        debug_default="1"
)

AC_ARG_ENABLE(debug-pp,
	[  --enable-debug-pp       enable debug pre-processor option],
	AC_DEFINE(DEBUG_COBPP)
        debug_default="1"
)

# Set MF compatibility features 
#mf_compatibility="0"
AC_ARG_ENABLE(mfcomp,
	[  --enable-mfcomp         enable MF compatibility features  ],
	AC_DEFINE(USE_MF_COMPATABILITY)
)

# Enable file LOCK server feature option  
#
#lockserv_default="0"
# tcob_lockserv_make_file=''
# tcob_lockserv_dir=''
# tcob_use_lockserver_opt1=''
# tcob_use_lockserver_opt2=''
# AC_ARG_ENABLE(lockserv,
# 	[  --enable-lockserv       enable file LOCK server feature  ],
# 	AC_DEFINE(USE_LOCKSERVER)
#         tcob_lockserv_make_file="lockserver/Makefile"
#         tcob_lockserv_dir="lockserver"
#         tcob_use_lockserver_opt1='$(SRC2:.c=.o)'
#         tcob_use_lockserver_opt2='$(SRC2:.c=.lo)'
# )


# Enable file SYNC server feature option  
#
#lockserv_default="0"
# AC_ARG_ENABLE(sync,
# 	[  --enable-sync           enable file SYNC server feature  ],
# 	AC_DEFINE(USE_SYNC)
# )

# Enable Test-mode and set compiler and RTL locations option  
#
tcob_test_mode_opt="false"
AC_ARG_ENABLE(test-mode,
	[  --enable-test-mode      enable Test Mode features  ],
        tcob_test_mode_opt="true"
)

#AC_ARG_WITH(with-yacc,
#      [  --with-yacc=[ARG]       use YACC [yacc193 default=bison]],
#      ,
#      ,
#)
#if test "x$with_yacc" = "x"; then
#      yacc_name="bison"
#else
#      yacc_name=$with_yacc
#fi
#
#
#

if test "${debug_default}" = "1"; then 
  CCXFLAGS="-g"
  ACXFLAGS="-D -as"
else
#  CCXFLAGS="-O2"
  CCXFLAGS=""
  ACXFLAGS="-as"
fi

# Checks for libraries and lib includes.
tcob_cobrun_name1_opt=''
tcob_cobrun_name2_opt=''

#
# Build Run-Time as a shared library, change make file in 'lib' directory
#
tcob_shared_libs_opt='' 
tcob_shared_libs_install_opt=''
AC_MSG_CHECKING(whether to build shared libraries)
AC_ARG_ENABLE(shared,
	[  --enable-shared=ARG     build shared libraries (default=yes) ],
        [enable_shared=$enableval],
        [enable_shared='yes']
)
AC_MSG_RESULT($enable_shared)
#
case "$enable_shared" in
  yes)
     tcob_shared_libs_opt="shared-libs" 
     tcob_shared_libs_install_opt="install-shared-libs" 
     tcob_shared_libs_uninstall_opt="uninstall-shared-libs" 
     ;;
   no) 
     tcob_shared_libs_opt='' 
     tcob_shared_libs_install_opt=''
     tcob_shared_libs_uninstall_opt='' 
     ;;
    *)
     AC_MSG_ERROR(Invalid build shared libraries option... aborting)
     ;;
esac
#

#
# Build Run-Time as a static library, change make file in 'lib' directory
#
AC_MSG_CHECKING(whether to build static libraries)
AC_ARG_ENABLE(static,
	[  --enable-static=ARG     build static libraries (default=yes) ],
        [enable_static=$enableval],
        [enable_static='yes'],
)
AC_MSG_RESULT($enable_static)
#
case "$enable_static" in
  yes)
     tcob_static_libs_opt="static-libs" 
     tcob_static_libs_install_opt="install-static-libs" 
     tcob_static_libs_uninstall_opt="uninstall-static-libs" 
     ;;
   no) 
     tcob_static_libs_opt='' 
     tcob_static_libs_install_opt=''
     tcob_static_libs_uninstall_opt='' 
     ;;
    *)
     AC_MSG_ERROR(Invalid build static libraries option... aborting)
     ;;
esac
#

#
# Determine which version of cobrun to build (static/shared)
#
if test "$enable_static" = "yes"; then
   tcob_cobrun_build_opt="build-static"
   tcob_cobrun_name1_opt='htcobrun'
   tcob_cobrun_name2_opt='htcobrun2'
fi
if test "$enable_static" = "no" && test "$enable_shared" = "yes"; then
   tcob_cobrun_build_opt="build-shared"
   tcob_cobrun_name1_opt='htcobrun1'
   tcob_cobrun_name2_opt='htcobrun'
fi

#
# Check for conflicting build libraries options
#
#test "x$prefix" = xNONE && prefix=$ac_default_prefix
if test "$enable_static" = "no" && test "$enable_shared" = "no"; then
   AC_MSG_ERROR(Conflicting options for shared and static libraries build... aborting)
fi
tcob_libs_opt="$tcob_static_libs_opt $tcob_shared_libs_opt" 
tcob_libs_install_opt="$tcob_static_libs_install_opt $tcob_shared_libs_install_opt" 
tcob_libs_uninstall_opt="$tcob_static_libs_uninstall_opt $tcob_shared_libs_uninstall_opt" 

# check for math library 
have_lib_m="no"

#AC_CHECK_LIB("$tcob_ld_args_m", asin, 
AC_CHECK_LIB($tcob_ld_args_m, asin, 
             have_lib_m="yes",
             AC_MSG_ERROR(Math library "$tcob_ld_args_m" is required to create COBOL executable)
             )
#
if test "${have_lib_m}" = "yes" ; then
   tcob_ld_args_m="-l$tcob_ld_args_m"
#   M_LIBS="$tcob_ld_args_m $M_LIBS"  
fi

#
tcob_ld_args_htcobol="-lhtcobol"
tcob_ld_args_default=""
tcob_ld_args_defaults=""
tcob_ld_args_curses=""
tcob_ld_args_db=""
tcob_ld_args_readline=""
tcob_ld_args_dl=""
tcob_ld_args_isam=""


# check for dynamic loading functionality and library dl  
# 
#
define_dl="no"
define_libdl="no"
AC_CHECK_LIB(c, dlopen, 
             define_dl="yes",          
)
if test "${define_dl}" = "no" ; then
  AC_CHECK_LIB(dl, dlopen, 
               [define_libdl="yes" define_dl="yes"], 
  )
fi
if test "${define_libdl}" = "yes" ; then
#   define_dl="yes" 
   tcob_ld_args_dl="-ldl"
   AC_DEFINE(HAVE_LIBDL)
fi
#os_platform='Cygwin'
#os_platform='MinGW'
#if test x"$os_platform" = "x"; then
#   if test "${define_dl}" = "no" ; then
if test x"$os_platform" = "x" && test "${define_dl}" = "no"; then
   AC_MSG_ERROR(dynamic loader not found... aborting)
fi

# Check for ltdl library availability
#
# if test "${use_ltdl_lib}" = "0" ; then
#    echo  "Setting RTS to use internal TC dynamic load routines "
# fi
# #
# if test "${use_ltdl_lib}" = "1" && test "${ltdl_header}" = "0" ; then
#      echo  "Header files for ltdl library not found... "
#      echo  "Defaulting RTS ... "
#      use_ltdl_lib="0"
# fi
# #
# tcob_ld_args_ltdl=""
# if test "${use_ltdl_lib}" = "1" ; then
#    AC_CHECK_LIB(ltdl, lt_dlgetsearchpath,
#              tcob_ld_args_ltdl="-lltdl",
#              AC_MSG_ERROR(Dynamic load library ltdl not found... aborting),
#              )
# fi
# Set use ltdl library option.
#
#AC_ARG_WITH(libltdl,
#	[  --with-libltdl          use LTDL library for Run-Time dynamic load routines],
#        ltdl_default="1" ,
#        ,
#        )
#
#AC_ARG_WITH(no-libltdl,
#	[  --with-no-libltdl       use internal Run-Time dynamic load routines ],
#        ltdl_default="0" ,
#        ,
#        )
#
#if test "${ltdl_default}" = "1" && test "${ltdl_header}" = "1" ; then
#     use_ltdl_lib="1"
#fi



# check for curses header and library 
# 

define_with_curses="no"
AC_CHECK_HEADERS(${curses_header},
                 ,     
                 [ AC_MSG_ERROR(header "${curses_header}" not found... aborting) ]
                 ) 
AC_CHECK_LIB(${curses_library}, addch,  
             define_with_curses="yes",
#             M_LIBS="$M_LIBS", 
             AC_MSG_ERROR(curses library is required by run-time... aborting)
            )

if test "${define_with_curses}" = "yes" ; then
#   M_LIBS="$M_LIBS" 
   AC_DEFINE(HAVE_LIBCURSES) 
   tcob_ld_args_curses="-l${curses_library}"
fi

# Check for color_set function availability
curses_with_color_set="no"
if test "${define_with_curses}" = "yes" ; then
  AC_MSG_CHECKING(for color_set in -l${curses_library})
  LIBS="-l${curses_library}"
AC_TRY_LINK(#include <${curses_header}>
short si1;
void  *vp;
,  color_set(si1, vp); ,
            [ AC_MSG_RESULT(yes); curses_with_color_set="yes" ], 
            [ AC_MSG_RESULT(no) ] 
            ) 
fi
#
if test "${curses_with_color_set}" = "yes" ; then
   AC_DEFINE(CURSES_HAS_COLOR_SET) 
fi

#LIBS="$LIBS_BK"
#INCLUDES="$INCLUDES_BK"
# check for header and library for readline
#define_with_readline="no"
#        [ define_with_readline="yes" ]
#             "-lncurses")
##        [ define_with_readline="$enableval" ]
#        [ define_with_readline="$with_readline" ]
AC_ARG_WITH(readline,
	[  --with-readline         use readline library ],
        , 
        ,
)
#if test "${define_with_readline}" = "yes" ; then
if test "${with_readline}" = "yes" ; then
   AC_CHECK_HEADERS("readline/readline.h", 
     [],
     [
      AC_MSG_ERROR(header readline.h for readline library not found... aborting)
     ]
     )
   AC_CHECK_LIB(readline, rl_tilde_expand, 
     [],
     [
      AC_MSG_ERROR(readline library not found... aborting)
     ]
   )
   define_with_readline="$with_readline" 
   tcob_ld_args_readline="-lreadline"
   AC_DEFINE(WITH_LIBREADLINE) 
   AC_DEFINE(HAVE_LIBREADLINE) 
   AC_DEFINE(WANT_READLINE)
fi

#  ISAM I/O (VB-ISAM) check
# 
AC_CHECK_HEADERS("vbisam.h", 
   [],
   [
     echo "header vbisam.h for VB-ISAM library vbisam not found..."
#    AC_MSG_ERROR(header vbisam.h for VB-ISAM library vbisam not found... aborting)
   ]
) 
AC_CHECK_LIB(vbisam, isopen,  
   [ 
    tcob_ld_args_isam="-lvbisam"
    AC_DEFINE(HAVE_LIBVBISAM)  
   ],
   [
     echo "VB-ISAM library vbisam not found..."
#    AC_MSG_ERROR(VB-ISAM library vbisam not found... aborting)
   ]
)
#

echo  "DB library db_version state is ${db_version}"

# DB_VERSION_MAJOR   2
# DB_VERSION_MINOR   4
# DB_VERSION_PATCH  14
# DB_VERSION_STRING "PeePeeCat Software ..."

# Step 1000: check for library db headers db.h or db_185.h
echo  "debug: Beginning BDB library search sequence "
db_header="0"
db_version="0"
db_libdb="0"
db_version_minor=""
db_lib_name=""
#
# Force the use of library DB library version 1, 2, 3, 4
AC_ARG_WITH(with-libdb,
	[  --with-libdb=[ARG]        use DB library versions 1.85-4.6 (ARG=1,2,3,4) ],
        ,
        ,
)
echo  "debug 1005: DB library header option with_libdb:$with_libdb:"
if test "x$with_libdb" != "x"; then
  if test "x$with_libdb" != "x1" && 
     test "x$with_libdb" != "x2" && 
     test "x$with_libdb" != "x3" && 
     test "x$with_libdb" != "x4"; 
  then
     AC_MSG_ERROR(invalid library db option selected... aborting)
  else
     db_version="$with_libdb" 
  fi
fi
echo  "debug 1010: DB library header option with_libdb:$with_libdb:"
if test "x$with_libdb" = "x1" -o "$db_version" = "0"
then
   AC_CHECK_HEADERS("db_185.h",
	[ db_header="101"  ], 
	[ db_header="100"  ] 
   )
   if test "$db_header" = "100"
   then
      AC_CHECK_HEADERS("db.h",
	[ db_header="100"  ], 
	[ db_header="101"  ] 
      )
   fi
   if test "$db_header" = "101"
   then
      AC_CHECK_HEADERS("db1/db.h", 
           [db_header="101" ],
           [db_header="0" ]
      ) 
   fi
   if test "x$with_libdb" = "x1" && 
      test "$db_header" = "0" 
   then
	echo "header for library db version 1.x not found..."
#       AC_MSG_ERROR(header for library db version 1.x not found... aborting)
   fi
   if test "$db_header" = "100"
   then
      AC_CHECK_LIB([db1], 
         [dbopen],
         [db_version="1" db_lib_name="-ldb1"],
	echo "header for library db version 1.x not found..."
#       AC_MSG_ERROR(header for library db version 1.x not found... aborting)
      )
   fi
   if test "$db_header" = "101"
   then
      AC_CHECK_LIB([db1], 
         [dbopen],
         [db_version="1" db_lib_name="-ldb1"],
         [db_version="0"],
      )
   fi

   if test "x$with_libdb" = "x1" && 
      test "$db_version" = "0"; 
   then
	echo "header for library db version 1.x not found..."
#       AC_MSG_ERROR(header for library db version 1.x not found... aborting)
   fi
fi

echo  "debug 1020: BDB library header option with_libdb:$with_libdb:"
if test "$db_header" != "1"; 
then
	echo "debug: db_header is $db_header"
fi
#
if test "x$with_libdb" = "x2"; then
   AC_CHECK_HEADERS("db2/db_185.h", 
           [db_header="2" ],
            echo "header db2/db_185.h for library db version 2.x not found..."
#           AC_MSG_ERROR(header db2/db_185.h for library db version 2.x not found... aborting)
   ) 
fi
#
if test "x$with_libdb" = "x3"; then
   AC_CHECK_HEADERS("db3/db_185.h", 
           [db_header="3" ],
#           AC_MSG_ERROR(header db3/db_185.h for library db version 3.x not found... aborting)
   ) 
fi
#
if test "x$with_libdb" = "x4"; then
echo  "Debug: Beginning DB library db4 header search sequence "
   AC_CHECK_HEADERS("db4/db_185.h", 
           [db_header="4"], 
           [], [],
#           AC_MSG_ERROR(header db4/db_185.h for library db version 4.x not found... aborting)
   )
fi
#
if test "x$with_libdb" = "x4.1"; then
echo  "Debug: Beginning DB library db4.1 header search sequence db_header=$db_header;"
    if test $db_header = "0"; then
        echo  "Debug: Start DB library db4.1 header search sequence "
        AC_CHECK_HEADERS("db4.1/db_185.h", 
           [db_header="41" ],
           [], [],
#           AC_MSG_ERROR(header db4.1/db_185.h for library db version 4.1 not found... aborting)
    ) 
    fi
fi
#
if test "x$with_libdb" = "x4.2"; then
echo  "Debug: Beginning DB library db4.2 header search sequence db_header=$db_header;"
    if test $db_header = "0"; then
        AC_CHECK_HEADERS("db4.2/db_185.h", 
           [db_header="42" ],
           [], [], 
#           AC_MSG_ERROR(header db4.2/db_185.h for library db version 4.2 not found... aborting)
    ) 
    fi
fi
#
echo  "Debug: Beginning DB library db4.3 header search sequence db_header=$db_header;"
if test "x$with_libdb" = "x4.3"; then
if test $db_header = "0"; then
   AC_CHECK_HEADERS("db4.3/db_185.h", 
           [db_header="43" ],
           [], [],
#           AC_MSG_ERROR(header db4.3/db_185.h for library db version 4.3 not found... aborting)
   ) 
fi
#
echo  "Debug: Beginning DB library db4.4 header search sequence db_header=$db_header;"
if test "x$with_libdb" = "x4.4"; then
    if test $db_header = "0"; then
        AC_CHECK_HEADERS("db4.4/db_185.h", 
           [db_header="44" ],
           [], [],
#           AC_MSG_ERROR(header db4.4/db_185.h for library db version 4.5 not found... aborting)
    ) 
    fi
fi
#
echo  "Debug: Beginning DB library db4.5 header search sequence db_header=$db_header;"
if test "x$with_libdb" = "x4.5"; then
if test $db_header = "0"; then
   AC_CHECK_HEADERS("db4.5/db_185.h", 
           [db_header="45" ],
           [], [],
#           AC_MSG_ERROR(header db4.5/db_185.h for library db version 4.5 not found... aborting)
   ) 
fi
echo  "Debug: Beginning DB library db4.6 header search sequence db_header=$db_header;"
if test "x$with_libdb" = "x4.6"; then
    if test $db_header = "0"; then
        AC_CHECK_HEADERS("db46/db_185.h", 
           [db_header="46" ],
           [], [],
#           AC_MSG_ERROR(header db4.5/db_185.h for library db version 4.5 not found... aborting)
    ) 
    fi
    if test $db_header = "0"; then
        AC_MSG_ERROR(No header db_185.h for library db version 4.x not found... aborting)
    fi
fi

echo  "debug 10.0: DB library header option with_libdb:$with_libdb:"
if test "x$with_libdb" = "x"; then
# Step 1: check for library db header db_185.h for version 2.x, 3.x, 4.x
if test "${db_header}" = "0" ; then
   AC_CHECK_HEADERS("db_185.h",
	[ db_header="23"  ], 
	)
fi

# Step 10.234: if header db_185.h not found check for header db.h for version 1.x
if test "${db_header}" = "0" ; then
   AC_CHECK_HEADERS("db.h", 
        [ db_header="10" ],
        ) 
fi

#  Step 10.1: if header db.h not found check for header db1/db.h for version 1.x
if test "${db_header}" = "0" ; then
   AC_CHECK_HEADERS("db1/db.h", 
        [ db_header="1" ],
        ) 
fi

# Step 2: if header "db1/db.h" not found check for header db2/db_185.h for version 2.x
if test "${db_header}" = "0" ; then
   AC_CHECK_HEADERS("db2/db_185.h", 
                   [db_header="2" ],
                   ) 
fi

# Step 3.0: if header "db2/db_185.h" not found check for header db3/db_185.h for version 3.x
if test "${db_header}" = "0" ; then
   AC_CHECK_HEADERS("db3/db_185.h", 
                   [db_header="3" ],
                   ) 
fi
# Step 4.0: if header "db3/db_185.h" not found check for header db4/db_185.h for version 4
if test "${db_header}" = "0" ; then
   AC_CHECK_HEADERS("db4/db_185.h", 
        [db_header="4" ],
        ) 
fi

# Step 4.1: if header "db4/db.h" not found check for header db4.1/db_185.h for version 4.1
if test "${db_header}" = "0" ; then
   AC_CHECK_HEADERS("db4.1/db_185.h", 
        [db_header="41" ],
        ) 
fi

# Step 4.2: if header "db4.1/db.h" not found check for header db4.2/db_185.h for version 4.2
if test "${db_header}" = "0" ; then
   AC_CHECK_HEADERS("db4.2/db_185.h", 
                   [db_header="42" ],
                   ) 
fi

# Step 4.3: if header "db4.2/db.h" not found check for header db4.3/db_185.h for version 4.3
if test "${db_header}" = "0" ; then
   AC_CHECK_HEADERS("db4.3/db_185.h", 
                   [db_header="43" ],
                   ) 
fi

# Step 4.4: if header "db4.3/db.h" not found check for header db4.4/db_185.h for version 4.4
if test "${db_header}" = "0" ; then
   AC_CHECK_HEADERS("db4.4/db_185.h", 
                   [db_header="44" ],
                   ) 
fi

# Step 4.5: if header "db4.4/db.h" not found check for header db4.5/db_185.h for version 4.5
if test "${db_header}" = "0" ; then
   AC_CHECK_HEADERS("db4.5/db_185.h", 
                   [db_header="45" ],
                   ) 
fi

# Step 4.6: if header "db4.5/db.h" not found check for header db46/db_185.h for version 4.6
if test "${db_header}" = "0" ; then
   AC_CHECK_HEADERS("db46/db_185.h", 
                   [db_header="46" ],
                   ) 
fi

# Step 10: if no DB headers found abort
if test "${db_header}" = "0" ; then
   AC_MSG_ERROR(library headers (db.h or db_185.h) not found... aborting)
else
  echo  "DB library header found db_header state is ${db_header}"
fi
fi

# Step 11: If header db.h found check library db is version 1.x (1.85 <= 1.x < 2.0)
echo  "Debug: Beginning DB library test link sequence "
if test "${db_header}" = "10" ; then

  AC_MSG_CHECKING(if db.h header belongs to version 1.x)
  AC_EGREP_HEADER([dbopen], [db.h],
                 [ AC_MSG_RESULT(yes) ],
                 [ AC_MSG_RESULT(no); 
                   AC_MSG_ERROR(header db.h for library db version 1.x not found... aborting) ]
                 ) 
                 
  AC_CHECK_LIB(db, dbopen,  
               db_version="10",
  )
#               M_LIBS="$M_LIBS"; db_version="10",
fi
# 

# Step 12: If header db.h found check library db is version 1.x (1.85 <= 2.0)
if test "${db_header}" = "1" ; then

  AC_MSG_CHECKING(if db1/db.h header belongs to version 1.x)
  AC_EGREP_HEADER([dbopen], [db1/db.h],
                 [ AC_MSG_RESULT(yes) ],
                 [ AC_MSG_RESULT(no); 
                   AC_MSG_ERROR(header db.h for library db version 1.x not found... aborting) ]
  ) 
                 
  AC_CHECK_LIB(db1, dbopen,  
               db_version="1", 
  )
fi
#               M_LIBS="$M_LIBS"; db_version="1", 
# 

# Step 18: If header db_185.h found check library db is version 2.x
if test "${db_header}" = "2" ; then
  printf "checking for -ldb2 (with 1.85 API compatibility)..."
  AC_MSG_CHECKING(for -ldb2 with 1.85 API compatibility)
  LIBS="-ldb2"
AC_TRY_LINK(#define DB_LIBRARY_COMPATIBILITY_API 1
#include <db2/db_185.h>
const char *c1;
int i1;
int i2;
DBTYPE dbv1;
const void *vv;
,  dbopen(c1, i1, i2, dbv1, vv); ,
            [ AC_MSG_RESULT(yes); db_version="2" ], 
            [ AC_MSG_RESULT(no);  db_header="21" ] 
            ) 
fi

# Step 19a: If header db_185.h found check library db is version 3.x
if test "${db_header}" = "3" ; then
printf "checking for -ldb-3 (with 1.85 API compatibility)..."
  AC_MSG_CHECKING(for -ldb-3 with 1.85 API compatibility)
  LIBS="-ldb-3"
#  LIBS="$LIBS_BK -ldb-3"
#  INCLUDES="$INCLUDES_BK"
AC_TRY_LINK(#define DB_LIBRARY_COMPATIBILITY_API 1
#include <db3/db_185.h>
const char *c1;
int i1;
int i2;
DBTYPE dbv1;
const void *vv;
,  dbopen(c1, i1, i2, dbv1, vv); ,
            [ AC_MSG_RESULT(yes); db_version="3" ], 
            [ AC_MSG_RESULT(no);  db_header="32" ] 
            ) 
fi
if test "${db_header}" = "32" ; then
printf "checking for -ldb3 (with 1.85 API compatibility)..."
  AC_MSG_CHECKING(for -ldb3 with 1.85 API compatibility)
  LIBS="-ldb3"
#  LIBS="$LIBS_BK -ldb3"
#  INCLUDES="$INCLUDES_BK"
AC_TRY_LINK(#define DB_LIBRARY_COMPATIBILITY_API 1
#include <db3/db_185.h>
const char *c1;
int i1;
int i2;
DBTYPE dbv1;
const void *vv;
,  dbopen(c1, i1, i2, dbv1, vv); ,
            [ AC_MSG_RESULT(yes); db_version="3" ], 
            [ AC_MSG_RESULT(no);  db_header="31" ] 
            ) 
fi

# Step 19b: If header 'db4/db_185.h' found check library db is version 4.x
if test "${db_header}" = "4" ; then
#  echo -n "checking for -ldb-4 (with 1.85 API compatibility)..."
  AC_MSG_CHECKING(for -ldb-4 with 1.85 API compatibility)
  LIBS="-ldb-4"
#  LIBS="$LIBS_BK -ldb-4"
#  INCLUDES="$INCLUDES_BK"
AC_TRY_LINK(#define DB_LIBRARY_COMPATIBILITY_API 1
#include <db4/db_185.h>
const char *c1;
int i1;
int i2;
DBTYPE dbv1;
const void *vv;
,  dbopen(c1, i1, i2, dbv1, vv); ,
            [ AC_MSG_RESULT(yes); db_version="4" ], 
            [ AC_MSG_RESULT(no);  db_header="41" ] 
            ) 
fi

# Step 19b: If header 'db4.1/db_185.h' found check library db is version 4.x
if test "${db_header}" = "41" ; then
printf "checking for -ldb-4.1 (with 1.85 API compatibility)..."
  AC_MSG_CHECKING(for -ldb-4.1 with 1.85 API compatibility)
  LIBS="-ldb-4.1"
#  LIBS="$LIBS_BK -ldb-4.1"
#  INCLUDES="$INCLUDES_BK"
AC_TRY_LINK(#define DB_LIBRARY_COMPATIBILITY_API 1
#include <db4.1/db_185.h>
const char *c1;
int i1;
int i2;
DBTYPE dbv1;
const void *vv;
,  dbopen(c1, i1, i2, dbv1, vv); ,
            [ AC_MSG_RESULT(yes); db_version="41" ], 
            [ AC_MSG_RESULT(no);  db_header="42" ] 
            ) 
fi

# Step 19b: If header 'db4.2/db_185.h' found check library db is version 4.x
if test "${db_header}" = "42" ; then
printf "checking for -ldb-4.2 (with 1.85 API compatibility)..."
  AC_MSG_CHECKING(for -ldb-4.2 with 1.85 API compatibility)
  LIBS="-ldb-4.2"
#  LIBS="$LIBS_BK -ldb-4.2"
#  INCLUDES="$INCLUDES_BK"
AC_TRY_LINK(#define DB_LIBRARY_COMPATIBILITY_API 1
#include <db4.2/db_185.h>
const char *c1;
int i1;
int i2;
DBTYPE dbv1;
const void *vv;
,  dbopen(c1, i1, i2, dbv1, vv); ,
            [ AC_MSG_RESULT(yes); db_version="42" ], 
            [ AC_MSG_RESULT(no);  db_header="43" ] 
            ) 
fi

# Step 19b: If header 'db4.3/db_185.h' found check library db is version 4.x
if test "${db_header}" = "43" ; then
printf "checking for -ldb-4.3 (with 1.85 API compatibility)..."
  AC_MSG_CHECKING(for -ldb-4.3 with 1.85 API compatibility)
  LIBS="-ldb-4.3"
#  LIBS="$LIBS_BK -ldb-4.3"
#  INCLUDES="$INCLUDES_BK"
AC_TRY_LINK(#define DB_LIBRARY_COMPATIBILITY_API 1
#include <db4.3/db_185.h>
const char *c1;
int i1;
int i2;
DBTYPE dbv1;
const void *vv;
,  dbopen(c1, i1, i2, dbv1, vv); ,
            [ AC_MSG_RESULT(yes); db_version="43" ], 
            [ AC_MSG_RESULT(no);  db_header="44" ] 
            ) 
fi

# Step 19b: If header 'db4/db_185.h' found check library db is version 4.x
if test "${db_header}" = "44" ; then
printf "checking for -ldb-4.4 (with 1.85 API compatibility)..."
  AC_MSG_CHECKING(for -ldb-4.4 with 1.85 API compatibility)
  LIBS="-ldb-4.4"
#  LIBS="$LIBS_BK -ldb-4.4"
#  INCLUDES="$INCLUDES_BK"
AC_TRY_LINK(#define DB_LIBRARY_COMPATIBILITY_API 1
#include <db4.4/db_185.h>
const char *c1;
int i1;
int i2;
DBTYPE dbv1;
const void *vv;
,  dbopen(c1, i1, i2, dbv1, vv); ,
            [ AC_MSG_RESULT(yes); db_version="44" ], 
            [ AC_MSG_RESULT(no);  db_header="45" ] 
            ) 
fi

# Step 19b: If header 'db4.5/db_185.h' found check library db is version 4.x
if test "${db_header}" = "45" ; then
#  echo -n "checking for -ldb-4.5 (with 1.85 API compatibility)..."
  AC_MSG_CHECKING(for -ldb-4.5 with 1.85 API compatibility)
  LIBS="-ldb-4.5"
#  LIBS="$LIBS_BK -ldb-4.5"
#  INCLUDES="$INCLUDES_BK"
AC_TRY_LINK(#define DB_LIBRARY_COMPATIBILITY_API 1
#include <db4.5/db_185.h>
const char *c1;
int i1;
int i2;
DBTYPE dbv1;
const void *vv;
,  dbopen(c1, i1, i2, dbv1, vv); ,
            [ AC_MSG_RESULT(yes); db_version="45" ], 
            [ AC_MSG_RESULT(no);  db_header="46" ] 
            ) 
fi

# Step 19b: If header 'db46/db_185.h' found check library db is version 4.x
if test "${db_header}" = "46" ; then
printf "checking for -ldb-4.6 (with 1.85 API compatibility)..."
  AC_MSG_CHECKING(for -ldb-4.6 with 1.85 API compatibility)
  LIBS="-ldb-4.6"
#  LIBS="$LIBS_BK -ldb-4.6"
#  INCLUDES="$INCLUDES_BK"
AC_TRY_LINK(#define DB_LIBRARY_COMPATIBILITY_API 1
#include <db46/db_185.h>
const char *c1;
int i1;
int i2;
DBTYPE dbv1;
const void *vv;
,  dbopen(c1, i1, i2, dbv1, vv); ,
            [ AC_MSG_RESULT(yes); db_version="46" ], 
            [ AC_MSG_RESULT(no);  db_header="41" ] 
            ) 
fi

# Step 10: If header db_185.h found check if library db is version 2.x
if test "${db_header}" = "23" ; then
printf "checking for -ldb (versions 2.x 3.x 4.x with 1.85 API compatibility)..."
  AC_MSG_CHECKING(for -ldb versions 2.x 3.x 4.x with 1.85 API compatibility)
  LIBS="-ldb"
#  LIBS="$LIBS_BK -ldb"
#  INCLUDES="$INCLUDES_BK"
AC_TRY_LINK(#define DB_LIBRARY_COMPATIBILITY_API 1
#include <db_185.h>
const char *c1;
int i1;
int i2;
DBTYPE dbv1;
const void *vv;
,  dbopen(c1, i1, i2, dbv1, vv); ,
            [ AC_MSG_RESULT(yes); db_version="23" ], 
            [ AC_MSG_RESULT(no);  db_header="41" ] 
            ) 
fi

# Step 10a: If header db_185.h found check if library db is version 4.x
if test "${db_header}" = "41" ; then
#  echo -n "checking for -ldb-4 (with 1.85 API compatibility)..."
  AC_MSG_CHECKING(for -ldb-4 with 1.85 API compatibility)
  LIBS="-ldb-4"
#  LIBS="$LIBS_BK -ldb-4"
#  INCLUDES="$INCLUDES_BK"
AC_TRY_LINK(#define DB_LIBRARY_COMPATIBILITY_API 1
#include <db_185.h>
const char *c1;
int i1;
int i2;
DBTYPE dbv1;
const void *vv;
,  dbopen(c1, i1, i2, dbv1, vv); ,
            [ AC_MSG_RESULT(yes); db_version="41" ], 
            [ AC_MSG_RESULT(no);  db_header="32" ] 
            ) 
fi

# Step 10b: If header db_185.h found check if library db is version 3.x
if test "${db_header}" = "32" ; then
printf "checking for -ldb3 (with 1.85 API compatibility)..."
  AC_MSG_CHECKING(for -ldb3 with 1.85 API compatibility)
  LIBS="-ldb3"
#  LIBS="$LIBS_BK -ldb3"
#  INCLUDES="$INCLUDES_BK"
AC_TRY_LINK(#define DB_LIBRARY_COMPATIBILITY_API 1
#include <db_185.h>
const char *c1;
int i1;
int i2;
DBTYPE dbv1;
const void *vv;
,  dbopen(c1, i1, i2, dbv1, vv); ,
            [ AC_MSG_RESULT(yes); db_version="32" ], 
            [ AC_MSG_RESULT(no);  db_header="123" ] 
            ) 
fi

# Step 10c: If header db_185.h found check if library db is version 2.x or 3.x called db1
if test "${db_header}" = "123" ; then
printf "checking for -ldb2 (with 1.85 API compatibility)..."
  AC_MSG_CHECKING(for -ldb2 with 1.85 API compatibility)
  LIBS="-ldb2"
#  LIBS="$LIBS_BK -ldb2"
#  INCLUDES="$INCLUDES_BK"
AC_TRY_LINK(#define DB_LIBRARY_COMPATIBILITY_API 1
#include <db_185.h>
const char *c1;
int i1;
int i2;
DBTYPE dbv1;
const void *vv;
,  dbopen(c1, i1, i2, dbv1, vv); ,
            [ AC_MSG_RESULT(yes); db_version="123" ], 
            [ AC_MSG_RESULT(no); AC_MSG_ERROR(library test link failed for db3 or db2 and/or compatibility API to version 1.85 not found... aborting) ] 
            ) 
fi

# Step 11: If header db_185.h found check if library db is version 3.x
if test "${db_header}" = "31" ; then
#  echo -n "checking for -ldb (version 3.x with 1.85 API compatibility)..."
  AC_MSG_CHECKING(for -ldb version 3.x with 1.85 API compatibility)
  LIBS="-ldb"
#  LIBS="$LIBS_BK -ldb"
#  INCLUDES="$INCLUDES_BK"
AC_TRY_LINK(#define DB_LIBRARY_COMPATIBILITY_API 1
#include <db3/db_185.h>
const char *c1;
int i1;
int i2;
DBTYPE dbv1;
const void *vv;
,  dbopen(c1, i1, i2, dbv1, vv); ,
            [ AC_MSG_RESULT(yes); db_version="31" ], 
            [ AC_MSG_RESULT(no); AC_MSG_ERROR(library test link failed for db and/or compatibility API to version 1.85 not found... aborting) ] 
            ) 
fi

# Step 12: If header db_185.h found check if library db is version 3.x
if test "${db_header}" = "21" ; then
printf "checking for -ldb (version 2.x with 1.85 API compatibility)..."
  AC_MSG_CHECKING(for -ldb version 2.x with 1.85 API compatibility)
  LIBS="-ldb"
#  LIBS="$LIBS_BK -ldb"
#  INCLUDES="$INCLUDES_BK"
AC_TRY_LINK(#define DB_LIBRARY_COMPATIBILITY_API 1
#include <db2/db_185.h>
const char *c1;
int i1;
int i2;
DBTYPE dbv1;
const void *vv;
,  dbopen(c1, i1, i2, dbv1, vv); ,
            [ AC_MSG_RESULT(yes); db_version="21" ], 
            [ AC_MSG_RESULT(no); AC_MSG_ERROR(library test link failed for db and/or compatibility API to version 1.85 not found... aborting) ] 
            ) 
fi

# Step 13: Define which header to use 
echo  "DB library db_version state is ${db_version}"
if test "${db_version}" = "1" ; then
  AC_DEFINE(USE_DB_1) 
  tcob_ld_args_db="-ldb1"
fi

if test "${db_version}" = "2" ; then
  AC_DEFINE(USE_DB_2) 
  tcob_ld_args_db="-ldb2"
fi

if test "${db_version}" = "23" ; then
  AC_DEFINE(USE_DB_23) 
  tcob_ld_args_db="-ldb"
fi

if test "${db_version}" = "3x" ; then
  AC_DEFINE(USE_DB_3) 
  tcob_ld_args_db="$db_lib_name"
fi

if test "${db_version}" = "3" ; then
  AC_DEFINE(USE_DB_3) 
  tcob_ld_args_db="-ldb3"
fi

if test "${db_version}" = "4" ; then
  AC_DEFINE(USE_DB_4) 
  tcob_ld_args_db="-ldb-4"
fi

if test "${db_version}" = "32" ; then
  AC_DEFINE(USE_DB_23) 
  tcob_ld_args_db="-ldb3"
fi

if test "${db_version}" = "10" ; then
  AC_DEFINE(USE_DB) 
  tcob_ld_args_db="-ldb"
fi

if test "${db_version}" = "123" ; then
  AC_DEFINE(USE_DB_234) 
  tcob_ld_args_db="-ldb"
fi

if test "${db_version}" = "21" ; then
  AC_DEFINE(USE_DB_2) 
  tcob_ld_args_db="-ldb"
fi

if test "${db_version}" = "31" ; then
  AC_DEFINE(USE_DB_3) 
  tcob_ld_args_db="-ldb"
fi

if test "${db_version}" = "41" ; then
  AC_DEFINE(USE_DB_41) 
  tcob_ld_args_db="-ldb-4.1"
fi

if test "${db_version}" = "42" ; then
  AC_DEFINE(USE_DB_42) 
  tcob_ld_args_db="-ldb-4.2"
fi

if test "${db_version}" = "43" ; then
  AC_DEFINE(USE_DB_43) 
  tcob_ld_args_db="-ldb-4.3"
fi

if test "${db_version}" = "44" ; then
  AC_DEFINE(USE_DB_44) 
  tcob_ld_args_db="-ldb-4.3"
fi

if test "${db_version}" = "45" ; then
  AC_DEFINE(USE_DB_45) 
  tcob_ld_args_db="-ldb-4.5"
fi

if test "${db_version}" = "46" ; then
  AC_DEFINE(USE_DB_46) 
  tcob_ld_args_db="-ldb-4.6"
fi

#
# Build using experimental math RT using fixlib - disabled
#tcob_math_functions='mcmath.c'
#AC_ARG_WITH(fixlib,
#	[  --with-fixlib           build experimental math RT using fixlib    ],
#        [tcob_math_functions='fixnumeric.c imath.c' ],
#        ,
#)

#
# Build fixed/free format conversion utility.
# Change make file in '.' directory
#
tcob_manfiles='manfiles'
tcob_htmlfiles='htmlfiles'
tcob_textfiles='textfiles'
tcob_intman='install-manfiles'
tcob_inthtml='install-htmlfiles'
tcob_inttext='install-textfiles'
#
tcob_cobf2f_dir=''
tcob_cobf2f_dir1=''
tcob_cobf2f_man=''
tcob_cobf2f_html=''
tcob_cobf2f_text=''
tcob_cobf2f_intman=''
tcob_cobf2f_inthtml=''
tcob_cobf2f_inttext=''
AC_ARG_WITH(cobf2f,
	[  --with-cobf2f           build and install format conversion utility (cobf2f) ],
        ,
        ,
)
if test "${with_cobf2f}" = "yes" ; then
   tcob_cobf2f_dir='cobf2f'
   tcob_cobf2f_dir1='utils/cobf2f'
   tcob_cobf2f_man='manfile3'
   tcob_cobf2f_html='htmlfile3'
   tcob_cobf2f_text='textfile3'
   tcob_cobf2f_intman='install-manfile3'
   tcob_cobf2f_inthtml='install-htmlfile3'
   tcob_cobf2f_inttext='install-textfile3'
fi

# Set the DASH ('-') transformation characters
# Default is "_2D"
tcob_str_dash_redefine=''
AC_ARG_WITH(with-dash-redefine,
	[  --with-dash-redefine=[ARG] Set the dash ('-') transformation characters (default=_2D) ],
        ,
        ,
)
if test "x$with_dash_redefine" = "x"; then
   tcob_str_dash_redefine="_2D"
else
   tcob_str_dash_redefine=$with_dash_redefine
fi

# Restore library and include paths
LIBS="$LIBS_BK"
INCLUDES="$INCLUDES_BK"

# Set the default directories
# pre-processor (htcobolpp) and options file directory
#
tcob_default=""
optfile_dir=""
cobcpy_default=""
#

# set default directories
#
if test "${tcob_test_mode_opt}" = "true" ; then
  tcob_ld_paths_default="-L${PWD}/lib -L${prefix}/lib"
else
  tcob_ld_paths_default="-L${prefix}/lib"
fi


# set variables for install
#
tcob_default="${prefix}/share/htcobol"
optfile_dir="${prefix}/share/htcobol"
copybook_path="${prefix}/share/htcobol/copybooks"
tcob_docdir="htcobol-$TCOB_MAJOR_VERSION.$TCOB_MINOR_VERSION"

# set variables for config file
#
optfile_default='htcobolrc'
rtoptfile_default='htrtconf'
tcob_default_config="${prefix}/share/htcobol"
#
if test "${define_with_readline}" = "yes" ; then
  tcob_ld_args_default="${tcob_ld_args_htcobol} ${tcob_ld_args_db} ${tcob_ld_args_isam} ${tcob_ld_args_readline} ${tcob_ld_args_curses}"
  tcob_ld_args_defaults="${tcob_ld_args_db} ${tcob_ld_args_isam} ${tcob_ld_args_readline} ${tcob_ld_args_curses}"
else
  tcob_ld_args_default="${tcob_ld_args_htcobol} ${tcob_ld_args_db} ${tcob_ld_args_isam} ${tcob_ld_args_curses}"
  tcob_ld_args_defaults="${tcob_ld_args_db} ${tcob_ld_args_isam} ${tcob_ld_args_curses}"
fi
#
tcob_ld_args_default="${tcob_ld_args_default} ${tcob_ld_args_m} ${tcob_ld_args_dl}"
tcob_ld_args_defaults="${tcob_ld_args_defaults} ${tcob_ld_args_m} ${tcob_ld_args_dl}"
#
tcob_ld_args_defaults="${tcob_ld_args_defaults}"
#
CCX=$CC
#
AC_DEFINE(HAVE_LIBM) 
AC_SUBST(LEX)
AC_SUBST(YACC)
AC_SUBST(CCX)
AC_SUBST(COB)
AC_SUBST(INCLUDES)
AC_SUBST(CCXFLAGS)
AC_SUBST(ACXFLAGS)
AC_SUBST(exeext)
AC_SUBST(tcob_default)
AC_SUBST(cobcpy_default)
AC_SUBST(yacc_prefix_compiler)
AC_SUBST(copybook_path)
AC_SUBST(tcob_docdir)
mandir = @mandir@
os_platform= @os_platform@
AC_SUBST(os_platform)

AC_SUBST(TCOB_MAJOR_VERSION)
AC_SUBST(TCOB_MINOR_VERSION)
AC_SUBST(TCOB_PATCH_LEVEL)
AC_SUBST(TCOB_VERSION)
AC_SUBST(TCOB_RELEASE_DATE)
AC_SUBST(tcob_version)
AC_SUBST(host_os)

AC_SUBST(prefix_local)
AC_SUBST(drive_prefix)

AC_SUBST(TCOBRUN_MAJOR_VERSION)
AC_SUBST(TCOBRUN_MINOR_VERSION)
AC_SUBST(TCOBRUN_PATCH_LEVEL)
AC_SUBST(TCOBRUN_VERSION)
AC_SUBST(TCOBRUN_RELEASE_DATE)

# shared-libs
# Build Run-Time as a shared library, change make file in 'lib' directory
# define_with_shared_lib="no"
AC_SUBST(tcob_libs_opt)
AC_SUBST(tcob_libs_install_opt)
AC_SUBST(tcob_libs_uninstall_opt)
AC_SUBST(tcob_cobrun_build_opt)
AC_SUBST(tcob_cobrun_name1_opt)
AC_SUBST(tcob_cobrun_name2_opt)

AC_SUBST(tcob_manfiles)
AC_SUBST(tcob_htmlfiles)
AC_SUBST(tcob_textfiles)
AC_SUBST(tcob_intman)
AC_SUBST(tcob_inthtml)
AC_SUBST(tcob_inttext)

AC_SUBST(tcob_cobf2f_dir)
AC_SUBST(tcob_cobf2f_dir1)
AC_SUBST(tcob_cobf2f_man)
AC_SUBST(tcob_cobf2f_html)
AC_SUBST(tcob_cobf2f_text)
AC_SUBST(tcob_cobf2f_intman)
AC_SUBST(tcob_cobf2f_inthtml)
AC_SUBST(tcob_cobf2f_inttext)

AC_SUBST(tcob_math_functions)

AC_SUBST(tcob_lockserv_dir)
AC_SUBST(tcob_use_lockserver_opt1)
AC_SUBST(tcob_use_lockserver_opt2)

AC_SUBST(tcob_ld_args_htcobol)
AC_SUBST(tcob_ld_args_m)
AC_SUBST(tcob_ld_args_db)
AC_SUBST(tcob_ld_args_isam)
AC_SUBST(tcob_ld_args_ltdl)
AC_SUBST(tcob_ld_args_dl)
AC_SUBST(tcob_ld_args_curses)
AC_SUBST(tcob_ld_args_readline)
AC_SUBST(tcob_ld_paths_default)
AC_SUBST(tcob_ld_args_default)
AC_SUBST(tcob_ld_args_defaults)

AC_SUBST(asx_cmd)
AC_SUBST(ccx_cmd)
AC_SUBST(ranlibx_cmd)
AC_SUBST(arx_cmd)

#echo "debug 10a: with_lang=$with_lang, tcob_lang=$tcob_lang" 
AC_SUBST(tcob_lang)
AC_DEFINE(TCOB_LANGUAGE_en)
# case "x$tcob_lang" in
#      xen) AC_DEFINE(TCOB_LANGUAGE_en)
#          ;;
#      xfr) AC_DEFINE(TCOB_LANGUAGE_fr) 
#          ;;
#      xit) AC_DEFINE(TCOB_LANGUAGE_it) 
#          ;;
#      xpt_BR) AC_DEFINE(TCOB_LANGUAGE_pt_BR) 
#          ;;
#      xes) AC_DEFINE(TCOB_LANGUAGE_es) 
#          ;;
# esac
echo "debug 10b: with_lang=$with_lang, tcob_lang=$tcob_lang" 

AC_DEFINE_UNQUOTED(TCOB_STR_DASH_REDEFINE, "${tcob_str_dash_redefine}")

AC_DEFINE_UNQUOTED(TCOB_CCX_CMD, "${CC}")
AC_DEFINE_UNQUOTED(TCOB_ASX_CMD, "${AS}")
AC_DEFINE_UNQUOTED(TCOB_COB_CMD, "${COB}")

AC_DEFINE_UNQUOTED(TCOB_DEFAULTS_PATH, "${tcob_default_config}")
AC_DEFINE_UNQUOTED(OPTFILE_DEFAULT, "${optfile_default}")
AC_DEFINE_UNQUOTED(RTOPTFILE_DEFAULT, "${rtoptfile_default}")

AC_DEFINE_UNQUOTED(TCOB_LD_PATHS_DEFAULT, "${tcob_ld_paths_default}")

AC_DEFINE_UNQUOTED(TCOB_LD_ARGS_MATH, "$tcob_ld_args_m")
AC_DEFINE_UNQUOTED(TCOB_LD_ARGS_HTCOBOL, "$tcob_ld_args_htcobol")
AC_DEFINE_UNQUOTED(TCOB_LD_ARGS_DB, "$tcob_ld_args_db")
AC_DEFINE_UNQUOTED(TCOB_LD_ARGS_ISAM, "$tcob_ld_args_isam")
AC_DEFINE_UNQUOTED(TCOB_LD_ARGS_CURSES, "$tcob_ld_args_curses")
AC_DEFINE_UNQUOTED(TCOB_LD_ARGS_READLINE, "$tcob_ld_args_readline")
AC_DEFINE_UNQUOTED(TCOB_LD_ARGS_DL, "$tcob_ld_args_dl")

AC_DEFINE_UNQUOTED(TCOB_SHLIB_EXT, "$shared_lib_extension")

if test "${need_underscode}" = "yes" ; then
   AC_DEFINE(NEED_USCORE)
fi

if test "${use_ltdl_lib}" = "1" ; then
    AC_DEFINE(USE_LTDL_LIB)
    AC_DEFINE_UNQUOTED(TCOB_LD_ARGS_LTDL, "$tcob_ld_args_ltdl")
fi

AC_DEFINE_UNQUOTED(TCOB_LD_ARGS_DEFAULT, "$tcob_ld_args_default")

AC_OUTPUT(Makefile compiler/Makefile compiler/htversion.h \
	compiler/htcobolrc lib/Makefile \
	cobrun/Makefile cobrun/tcrunversion.h \
	utils/Makefile utils/cobf2f/Makefile \
	test.code/Makefile test.code/mconfig.inc test.code/copybooks/Makefile \
	info/Makefile info/slackware/SlackBuild \
        test_suite/Makefile test_suite/coboltest.inc \
        test_suite/nist/makeConfig.inc test_suite/nist/Makefile \
        lib/htcobolrt.rc )

#        $tcob_lockserv_make_file test_suite/coboltest.inc test.code/mconfig.inc 
#	test.code/copybooks/Makefile info/Makefile lockserver/Makefile)
#	cobpp/Makefile cobpp/tcppversion.h 
#	cobrun/Makefile cobrun/tcrunversion.h cobrun/test.code/Makefile 
