/* 
 *  Copyright (C) 1999 - 2009 Glen Colbert, David Essex, Rildo Pragana.
 *  Copyright (C) 1993, 1991  Rildo Pragana.
 * 
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this software; see the file COPYING.  If not, write to
 *  the Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 *  Boston, MA 02111-1307 USA
 */ 

#ifndef _HTGLOBALS_H
#define _HTGLOBALS_H

/* Global compiler variables  */
 
#define PATHMAX                 120
#define PATHMAX1                (1024 * 4)
#define PATHMAX2                256
#define PATHMAX3 		1024

#define CHR_SQUOTE		'\''
#define CHR_DQUOTE		'"'
#define CHR_EOS			'\0'
#define CHR_ASTERIX		'*'
#define CHR_CR			'\r'
#define CHR_LF			'\n'
#define CHR_DASH		'-'
#define CHR_UNDERSCORE		'_'
#define CHR_SLASH		'/'
#define CHR_DOLLARD_SIGN	'$'
#define CHR_PERIOD		'.'
#define CHR_SPACE		' '
#define CHR_NPOUND		'#'
#define CHR_EQUAL		'='

#define STR_DASH		"-"
#define STR_UNDERSCORE		"_"
#define STR_DEFAULT_TAB_LEN	"8"

#define DEFAULT_TAB_LEN          8

#ifndef __MINGW32__
#define STR_SEARCH_SUFFIXES	".cpy:.CPY:.cob:.COB:.cbl:.CBL::"
#define CHR_COLEN		':'
#define STR_COLEN		":"
#else
#define STR_SEARCH_SUFFIXES	".cpy;.CPY;.cob;.COB;.cbl;.CBL;;"
#define CHR_COLEN		';'
#define STR_COLEN		";"
#endif

#ifdef  DEBUG_COBPP
#define DEBUG_COBPP_PP           1 
#define DEBUG_COBPP_SCANNER      1 
#define DEBUG_COBPP_PARSER       1 
#endif

#ifndef __MINGW32__

#ifndef LT_DIRSEP_CHAR
#define LT_DIRSEP_CHAR          '/'
#endif
#ifndef LT_DIRSEP_STR
#define LT_DIRSEP_STR           "/"
#endif


# ifndef LT_PATHSEP_CHAR
#  define LT_PATHSEP_CHAR         ':'
# endif
# ifndef LT_PATHSEP_STR
#  define LT_PATHSEP_STR          ":"
# endif
# ifndef TMPDIR_DEFAULT_STR
#  define TMPDIR_DEFAULT_STR      "/tmp"
# endif

#define HTG_PGM_SUFFIXES        ".cob:.COB:.cbl:.CBL:"

#else /* __MINGW32__*/

#ifndef LT_DIRSEP_CHAR
#define LT_DIRSEP_CHAR          '/'
#endif
#ifndef LT_DIRSEP_STR
#define LT_DIRSEP_STR           "/"
#endif

# ifndef LT_PATHSEP_CHAR
#  define LT_PATHSEP_CHAR         ';'
# endif
# ifndef LT_PATHSEP_STR
#  define LT_PATHSEP_STR          ";"
# endif
# ifndef TMPDIR_DEFAULT_STR
/*#define TMPDIR_DEFAULT_STR    "C:/windows/temp" */
#  define TMPDIR_DEFAULT_STR      "G:/tmp"
# endif

# define HTG_PGM_SUFFIXES        ".cob;.COB;.cbl;.CBL;"

#endif /*__MINGW32__*/


#define SUFFIX_SEP_STR           "."
#define SUFFIX_SEP_CHAR          '.'
#define SHLIB_SEP_STR            "$"
#define SHLIB_SONAME_STR         "-soname,"

#define HTG_FILE_GAS_SUFFIX      ".s"
#define HTG_FILE_PPOUT_SUFFIX    ".i"
#define HTG_FILE_OBJECT_SUFFIX   ".o"

#define RTL_CALL(module) (emt_cobrtl_call(module, lib_prefix))

/* Resource (options) file name */
#define HTG_OPTFILE_DEFAULT     "htcobolrc"

#define HTG_COBOPT              "TCOB_OPTIONS"
#define HTG_COBDIR              "TCOB_OPTIONS_PATH"

#ifndef TRUE
#define TRUE                    1
#define FALSE                   0
#endif

#ifndef NONE
#define NONE                   -1
#endif

#ifndef NIL
#define NIL                    0
#endif

#define MAXNAMEBUF              300
#define START_STACK_ADJUST      20
#define SYMBUF_SIZE             128
#define HASHLEN                 100
#define INIT                    1

#define MAX_PROGRAMID_WORD      31
#define MAX_PROGRAMID_LITERAL   127

#define ATTRIBUTE_OPTIONS_MAX   5

#define HTG_CMDOPTION_LIST      "B:cCdDe:EFghI:kL:l:mMno:PST:tXxW:vVz"

/*
 Defines for HTG_compile_level_flag                                    
 TCB_COMPILE_LEVEL_PREPROCESS - Preprocess only                                          
 TCB_COMPILE_LEVEL_COMPILE    - Preprocess and compile (generate assembler code) only    
 TCB_COMPILE_LEVEL_ASSEMBLE   - Preprocess, compile, assemble only                       
 TCB_COMPILE_LEVEL_EXECUTABLE - Preprocess, compile, assemble, link         
*/
enum tcb_compile_levels {
  TCB_COMPILE_LEVEL,  
  TCB_COMPILE_LEVEL_PREPROCESS = 10,  
  TCB_COMPILE_LEVEL_COMPILE    = 20,  
  TCB_COMPILE_LEVEL_ASSEMBLE   = 30,  
  TCB_COMPILE_LEVEL_EXECUTABLE = 40 
};

enum tcb_compile_types {
  TCB_COMPILE_TYPE,  
  TCB_COMPILE_TYPE_PROGRAM = 50,  
  TCB_COMPILE_TYPE_MODULE  = 70
};

enum tcb_source_code_formats {
  TCB_SOURCE_CODE_FORMAT,
  TCB_SOURCE_CODE_FORMAT_FIXED = 102,
  TCB_SOURCE_CODE_FORMAT_FREE  = 120 
};

enum tcb_cmd_line_opts {
  TCB_CMDOPT_NIL,                 

  TCB_CMDOPT_BIND_MODE = 66,      /* 'B' */
  TCB_CMDOPT_CALLS_DYNAMIC = 67,  /* 'C' */
  TCB_CMDOPT_DEBUG_LINES = 68,    /* 'D' */
  TCB_CMDOPT_PREPROCESSOR = 69,   /* 'E' */
  TCB_CMDOPT_SOURCE_FIXED = 70,   /* 'F' */
  TCB_CMDOPT_INCLUDE_PATH = 73,   /* 'I' */
  TCB_CMDOPT_LIB_PATH = 76,       /* 'L' */
  TCB_CMDOPT_MAIN_ENTRY = 77,     /* 'M' */
  TCB_CMDOPT_LISTING = 80,        /* 'P' */
  TCB_CMDOPT_COMPILE = 83,        /* 'S' */
  TCB_CMDOPT_TAB_NUMBER = 84,     /* 'T' */
  TCB_CMDOPT_CURSESIO_SET = 85,   /* 'U' */
  TCB_CMDOPT_VERSION = 86,        /* 'V' */
  TCB_CMDOPT_PASS_OPTIONS = 87,   /* 'W' */
  TCB_CMDOPT_SOURCE_OPEN = 88,    /* 'X' */

  TCB_CMDOPT_ASSEMBLE = 99,       /* 'c' */
  TCB_CMDOPT_DEBUG_TRACE = 100,   /* 'd' */
  TCB_CMDOPT_ENTRY_NAME = 101,    /* 'e' */
  TCB_CMDOPT_DEBUG = 103,         /* 'g' */
  TCB_CMDOPT_HELP = 104,          /* 'h' */
  TCB_CMDOPT_LIBCOB = 107,        /* 'k' */
  TCB_CMDOPT_INCLUDE_LIB = 108,   /* 'l' */
  TCB_CMDOPT_LIB_SHARED = 109,    /* 'm' */
  TCB_CMDOPT_NORUN = 110,         /* 'n' */
  TCB_CMDOPT_OUTPUT_NAME = 111,   /* 'o' */
  TCB_CMDOPT_TESTMODE = 116,      /* 't' */
  TCB_CMDOPT_VERBOSE = 118,       /* 'v' */
  TCB_CMDOPT_EXECUTABLE = 120,    /* 'x' */
  TCB_CMDOPT_VERY_VERBOSE = 122   /* 'z' */
};

#define HTG_PGM_NAME     "TinyCOBOL"
#define HTG_COPYWR       "Copyright (C) 1991, 1993, 1999-2010 Rildo Pragana\n"
/*#define HTG_COPYWR       "Copyright (C) 1991, 1993, 1999-2010 Rildo Pragana et. al.\n" */

enum tcb_resource_option_names {
  TCB_RESOURCE_OPTION_NAME_CROSS_REFERENCE_LISTING,
  TCB_RESOURCE_OPTION_NAME_PROGRAM_LISTING_SUFFIX,
  TCB_RESOURCE_OPTION_NAME_PROGRAM_LISTING,
  TCB_RESOURCE_OPTION_NAME_INCLUDE_DEBUGGING_LINES,
  TCB_RESOURCE_OPTION_NAME_DEFAULT_COMPILE_TYPE,
  TCB_RESOURCE_OPTION_NAME_DEFAULT_COMPILE_ACTION,
  TCB_RESOURCE_OPTION_NAME_DEFAULT_SOURCE_FORMAT,
  TCB_RESOURCE_OPTION_NAME_PROGRAM_ID_TRANSFORMATION,
  TCB_RESOURCE_OPTION_NAME_SOURCE_PROGRAM_SUFFIXES,
  TCB_RESOURCE_OPTION_NAME_COPYBOOK_PATH,
  TCB_RESOURCE_OPTION_NAME_COPYBOOK_SUFFIXES,
  TCB_RESOURCE_OPTION_NAME_STOPRUN_PROCEDURE,
/* TCB_RESOURCE_OPTION_NAME_LD_LIBRARY_PATH, */
  TCB_RESOURCE_OPTION_NAME_LD_DEFAULT,
  TCB_RESOURCE_OPTION_NAME_LD_LIBRARY_PATHS_EXTRA,
  TCB_RESOURCE_OPTION_NAME_DEFAULT_SHARED_LIBRARY_NAME,
  TCB_RESOURCE_OPTION_NAME_PROGRAM_ENTRY_POINT,
  TCB_RESOURCE_OPTION_NAME_LD_LIBRARY_EXTRA,
  TCB_RESOURCE_OPTION_NAME_LD_FLAGS_EXTRA
};

enum tcb_resource_option_attributes {
  TCB_RESOURCE_OPTION_ATTRIBUTE_COMPILE_TYPE,  
  TCB_RESOURCE_OPTION_ATTRIBUTE_COMPILE_ACTION,  
  TCB_RESOURCE_OPTION_ATTRIBUTE_SOURCE_FORMAT,  
  TCB_RESOURCE_OPTION_ATTRIBUTE_PROGRAM_ID_TRANSFORMATION,  
  TCB_RESOURCE_OPTION_ATTRIBUTE_STOPRUN_PROCEDURE,
  TCB_RESOURCE_OPTION_ATTRIBUTE_PROGRAM_ENTRY_POINT 
};

enum tcb_resource_option_binary {
  TCB_RESOURCE_OPTION_BINARY_FALSE,  
  TCB_RESOURCE_OPTION_BINARY_TRUE  
};

enum tcb_resource_option_types {
  TCB_RESOURCE_OPTION_TYPE,  
  TCB_RESOURCE_OPTION_TYPE_BINARY,  
  TCB_RESOURCE_OPTION_TYPE_STRING,  
  TCB_RESOURCE_OPTION_TYPE_SUBSTRING,  
  TCB_RESOURCE_OPTION_TYPE_ATTRIBUTE  
};

enum tcb_program_id_transformations {
  TCB_PROGRAM_ID_TRANSFORMATION_NONE,  
  TCB_PROGRAM_ID_TRANSFORMATION_TOLOWER,
  TCB_PROGRAM_ID_TRANSFORMATION_TOUPPER
};

enum tcb_stoprun_procedures {
  TCB_STOPRUN_PROCEDURE,  
  TCB_STOPRUN_PROCEDURE_INTERNAL,  
  TCB_STOPRUN_PROCEDURE_EXTERNAL 
};

enum tcb_program_entry_points {
  TCB_PROGRAM_ENTRY_POINT_NONE,  
  TCB_PROGRAM_ENTRY_POINT_AUTO, 
  TCB_PROGRAM_ENTRY_POINT_ANY
};

enum tcb_name_state {
  TCB_NAME_STATE,
  TCB_NAME_STATE_FLIT_LNONE,
  TCB_NAME_STATE_FNAME_LNONE,
  TCB_NAME_STATE_FLIT_LLIT,
  TCB_NAME_STATE_FLIT_LNAME,
  TCB_NAME_STATE_FNAME_LLIT,
  TCB_NAME_STATE_FNAME_LNAME
};

typedef struct _tcb_resource_binary_options
{
 char *value;
 int  ivalue;
} tcb_resource_binary_options;

typedef struct _tcb_resource_attribute_options
{
 int  attribute;
 char *option[ATTRIBUTE_OPTIONS_MAX];
 int  ivalue[ATTRIBUTE_OPTIONS_MAX];
} tcb_resource_attribute_options;

typedef struct _tcb_resource_options
{
 char *option;
 int  type;
 int  isel;
} tcb_resource_options;

typedef struct _tcb_compile_flags {
  char compile_level_flag; 
  char compile_level_type_flag; 
  char output_type_flag;
  char compile_level_default; 
  char assemble_flag;
  char full_compile_flag;
  char make_object_flag;
  char list_flag;
  char xref_flag;
/*char    sym_flag; */
  char debug_lines_flag;
  char debug_trace_flag; 
  char offset_flag;
  char verbose_flag;
  char verbose_verbose_flag;
  char all_calls_dynamic_flag;
  char retain_symbols_flag;
  char dynamic_flag;
  char shlib_soname_flag;
  char libcob_flag;
  char programid_name_trans_flag;
  char stoprun_proc_flag;
  char cursesio_set_flag;
  char codeFormat_flag; 
  char norun_flag; 
  int  fld_desc_len; 
  int  grp_desc_len; 
} tcb_compile_flags;


extern int wrncnt;
extern int errcnt;
extern unsigned int source_lineno;
extern unsigned int source_colno;
extern char *source_filename;
extern char *include_filename;
extern char input_filename[];
extern char working_filename[];
extern char output_filename[];
extern char list_filename[];
extern char sys_buf[];

extern int   HTG_RETURN_CODE;
extern int   HTG_temporary_error_code;
extern int   HTG_temporary_severity;
extern int   HTG_tab2space;
extern short HTG_assemble_flag;
extern short HTG_full_compile_flag;
extern short HTG_make_object_flag;
extern short HTG_list_flag;
extern short HTG_xref_flag;
extern short HTG_debug_lines_flag;
extern short HTG_offset_flag;
extern short HTG_verbose_flag;
extern short HTG_verbose_verbose_flag;
extern short HTG_all_calls_dynamic;
extern short HTG_remove_source_flag;
extern short HTG_retain_symbols;
extern short HTG_dynamic_flag;
extern short HTG_shlib_soname_flag;
extern short HTG_libcob;
extern short HTG_programid_name_trans_flag;
extern short HTG_stoprun_proc_flag;
extern short HTG_cursesio_set; 
extern short HTG_codeFormat;

extern short HTG_compile_level_flag; 
extern short HTG_compile_level_type_flag; 
extern short HTG_compile_level_default; 

extern char  file_path[];
extern char *prg_name;
extern char  lib_prefix[];

extern int  HTG_prg_uses_fileio; 
extern int  HTG_prg_uses_term; 
extern int  HTG_prg_uses_dcall; 

extern int  HTG_norun; 

extern int  HTG_fld_desc_len; 
extern int  HTG_grp_desc_len; 

extern char HTG_COPYDIR[];
extern char HTG_TMPDIR[];
extern char HTG_CCX_CMD[];
extern char HTG_ASX_CMD[];
extern char HTG_ASX_CMD[];
extern char HTG_OBJECT[];
extern char HTG_EXECUTABLE[];
extern char HTG_LD_OPTIONS[];
extern char HTG_LD_PATHS[];
extern char HTG_LD_ARGS[];
extern char HTG_LD_RESOPT_ARGS[];
extern char HTG_LD_CMDLINE_ARGS[];
extern char HTG_LD_DCALL_ARGS[];
extern char HTG_LD_DEFAULTS_ARGS[];
extern char HTG_LD_LIBRARY_PATHS_EXTRA_ARGS[];

extern char HTG_LD_EXTRA_ARGS[];
extern char HTG_LD_DYNAMIC[];

extern char HTG_PCAL_RESOPT_ARGS[];
extern char HTG_SHLIB_NAME_DEFAULT[];

extern char HTG_LD_FLAGS[];

/*
short main_flag;                 // Specify main entry point action 
int main_entry_flag;             // Main entry point detected 
char main_entry_buf[MAXNAMEBUF]; // main entry point name 
*/

#if defined(__MINGW32__ )
extern char COBINSTDIR[];
#endif

extern FILE *yyin;
extern FILE *o_src;
extern FILE *o_lst;

extern char include_full_filename[];

void process_bind_options (char *arglist);
void process_verbose_options (int ac, char *av[]);
void initialize_setup (void);
void append_include_path (char *ap);
void setup_filenames (void);
void print_compiler_banner (void);
void print_copybooks_path (void);
void setup_ld_paths (void);
void print_listing_file (void);
int  process_pp (void);
int  process_compile (void);
void process_select_verify (char compile_level);
void output_select_verify (char output_type);
void pass_options_ld (char *s);
void pp_setup_scanner_state(void);

int find_copybook_file(char *fname, char *lname);
int find_copybook_file2 (char *fname, char *lname);
int find_filename_text (char *fname, char *fp, char *fs);
int find_filename_literal (char *fname, char *fp);
char *find_env_variable (char *ev);
char *find_token(char *p, const char *d, int sw);
void append_include_path(char *ap);

int verify_binary_opition(char *option, char *arg, short *value);
int verify_attribute_opition(char *option, char *arg, int attribute, short *value);

#endif /* _HTGLOBALS_H */
