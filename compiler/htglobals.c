/* 
 *  Copyright (C) 1999 - 2009 Glen Colbert, David Essex, Bernard Giroud,
 *                            Rildo Pragana.
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
 * 

   This portion of the compiler processes the
   compiler options files, compiler environment
   variables, and processes the command line for
   flags and options used to determine the 
   compiler behavior.

 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#if defined(__MINGW32__)
#include "gnugetopt.h"
/*
//#ifndef getopt_long_only
//#define getopt_long_only getopt_long
//#endif
*/
#else
#include <getopt.h>
#endif

#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "htconfig.h"
#include "htcoboly.h"
#include "htversion.h"
#include "hthelp.h"
#include "htglobals.h"
#include "mwindows.h"

#if defined(__MINGW32__)
/* #include <windows.h> */
#include <process.h>
#else
#include <sys/wait.h>
#endif

/* #define DEBUG_COMPILER_LEVEL    1 */
/* #define DEBUG_COMPILER_LEVEL1   1 */
/* #define DEBUG_COMPILER_LEVEL2   1 */ 

extern int module_flag;
extern int use_screen_io;


short main_flag = 0;                  // Specify main entry point action */
int main_entry_flag = 0;              // Main entry point detected */
char main_entry_buf[MAXNAMEBUF] = ""; // main entry point name */


/* command line options */
static char short_option_list[] = { HTG_CMDOPTION_LIST };

static struct option long_option_list[] = {
  {"fixed", no_argument, NULL, 'F'},
  {"free", no_argument, NULL, 'X'},
  {"help", no_argument, NULL, 'h'},
  {"version", no_argument, NULL, 'V'},
  {NULL, 0, NULL, 0}
};

tcb_resource_binary_options binary_options[] =
{
 { "FALSE", TCB_RESOURCE_OPTION_BINARY_FALSE },
 { "TRUE",  TCB_RESOURCE_OPTION_BINARY_TRUE  },
 { NULL,  NONE}
};

tcb_resource_attribute_options attribute_options[] =
{
 { TCB_RESOURCE_OPTION_ATTRIBUTE_COMPILE_TYPE, 
  { "PROGRAM", "MODULE", NULL, NULL, NULL },
  { TCB_COMPILE_TYPE_PROGRAM, TCB_COMPILE_TYPE_MODULE, NONE, NONE, NONE }
  },
 { TCB_RESOURCE_OPTION_ATTRIBUTE_COMPILE_ACTION, 
  { "PREPROCESS", "COMPILE", "ASSEMBLE", "EXECUTABLE", NULL },
  { TCB_COMPILE_LEVEL_PREPROCESS, TCB_COMPILE_LEVEL_COMPILE, TCB_COMPILE_LEVEL_ASSEMBLE, TCB_COMPILE_LEVEL_EXECUTABLE, NONE }
  },
 { TCB_RESOURCE_OPTION_ATTRIBUTE_SOURCE_FORMAT, 
  { "FREE", "FIXED", NULL, NULL, NULL },
  { TCB_SOURCE_CODE_FORMAT_FREE, TCB_SOURCE_CODE_FORMAT_FIXED, NONE, NONE, NONE }
  },
 { TCB_RESOURCE_OPTION_ATTRIBUTE_PROGRAM_ID_TRANSFORMATION, 
  { "NONE", "TOLOWER", "TOUPPER", NULL, NULL },
  { TCB_PROGRAM_ID_TRANSFORMATION_NONE, TCB_PROGRAM_ID_TRANSFORMATION_TOLOWER, TCB_PROGRAM_ID_TRANSFORMATION_TOUPPER, NONE, NONE }
  },
 { TCB_RESOURCE_OPTION_ATTRIBUTE_STOPRUN_PROCEDURE, 
  { "INTERNAL", "EXTERNAL", NULL, NULL, NULL },
  { TCB_STOPRUN_PROCEDURE_INTERNAL, TCB_STOPRUN_PROCEDURE_EXTERNAL, NONE, NONE, NONE }
  },
 { TCB_RESOURCE_OPTION_ATTRIBUTE_PROGRAM_ENTRY_POINT, 
  { "NONE", "AUTO", NULL, NULL, NULL },
  { TCB_PROGRAM_ENTRY_POINT_NONE, TCB_PROGRAM_ENTRY_POINT_AUTO, NONE, NONE, NONE }
  },
 { NONE, 
  { NULL, NULL, NULL, NULL, NULL },
  { NONE, NONE, NONE, NONE, NONE }
  }
};

tcb_resource_options resource_options[] =
{
 { "CROSS-REFERENCE-LISTING", TCB_RESOURCE_OPTION_TYPE_BINARY, NONE },
 { "PROGRAM-LISTING-SUFFIX", TCB_RESOURCE_OPTION_TYPE_STRING,  NONE },
 { "PROGRAM-LISTING", TCB_RESOURCE_OPTION_TYPE_BINARY,         NONE },
 { "INCLUDE-DEBUGGING-LINES", TCB_RESOURCE_OPTION_TYPE_BINARY, NONE },
 { "DEFAULT-COMPILE-TYPE", TCB_RESOURCE_OPTION_TYPE_ATTRIBUTE, TCB_RESOURCE_OPTION_ATTRIBUTE_COMPILE_TYPE },
 { "DEFAULT-COMPILE-ACTION", TCB_RESOURCE_OPTION_TYPE_ATTRIBUTE, TCB_RESOURCE_OPTION_ATTRIBUTE_COMPILE_ACTION },
 { "DEFAULT-SOURCE-FORMAT", TCB_RESOURCE_OPTION_TYPE_ATTRIBUTE,  TCB_RESOURCE_OPTION_ATTRIBUTE_SOURCE_FORMAT },
 { "PROGRAM-ID-TRANSFORMATION", TCB_RESOURCE_OPTION_TYPE_ATTRIBUTE, TCB_RESOURCE_OPTION_ATTRIBUTE_PROGRAM_ID_TRANSFORMATION },
 { "SOURCE-PROGRAM-SUFFIXES", TCB_RESOURCE_OPTION_TYPE_STRING, NONE },
 { "COPYBOOK-PATH", TCB_RESOURCE_OPTION_TYPE_STRING, NONE },
 { "COPYBOOK-SUFFIXES", TCB_RESOURCE_OPTION_TYPE_STRING, NONE },
 { "STOPRUN-PROCEDURE", TCB_RESOURCE_OPTION_TYPE_ATTRIBUTE, TCB_RESOURCE_OPTION_ATTRIBUTE_STOPRUN_PROCEDURE },
/* { "LD-LIBRARY-PATH", TCB_RESOURCE_OPTION_TYPE_STRING, NONE }, */
 { "LD-DEFAULTS", TCB_RESOURCE_OPTION_TYPE_STRING, NONE },
 { "LD-LIBRARY-PATHS-EXTRA", TCB_RESOURCE_OPTION_TYPE_STRING, NONE },
 { "DEFAULT-SHARED-LIBRARY-NAME", TCB_RESOURCE_OPTION_TYPE_SUBSTRING, NONE },
 { "PROGRAM-ENTRY-POINT", TCB_RESOURCE_OPTION_TYPE_ATTRIBUTE, TCB_RESOURCE_OPTION_ATTRIBUTE_PROGRAM_ENTRY_POINT },
 { "LD-LIBRARY-EXTRA", TCB_RESOURCE_OPTION_TYPE_STRING, NONE },
 { "LD-FLAGS-EXTRA", TCB_RESOURCE_OPTION_TYPE_STRING, NONE },
 { NULL, NONE, NONE }
};

/* Define flags and storage for global compiler options  */
int wrncnt = 0;
int errcnt = 0;
unsigned int source_lineno = 0;
unsigned int source_colno  = 0;
char *source_filename = NULL;
char *include_filename = NULL;
char input_filename[PATHMAX];
char working_filename[PATHMAX];
char output_filename[PATHMAX];
char list_filename[PATHMAX];
char sys_buf[300];

int   HTG_RETURN_CODE = 0;
int   HTG_temporary_error_code = 0;
int   HTG_temporary_severity = 0;
short HTG_compile_level_flag = 0; 
short HTG_compile_level_default = 0; 
short HTG_compile_level_type_flag = 0; 
short HTG_compile_level_type_default = 0; 
short HTG_assemble_flag = 0;
short HTG_full_compile_flag = 0;
short HTG_make_object_flag = 0;
short HTG_list_flag = 0;
short HTG_xref_flag = 0;
short HTG_debug_lines_flag = 0;
short HTG_debug_trace_flag = 0; 
short HTG_offset_flag = 0;
short HTG_verbose_flag = 0;
short HTG_verbose_verbose_flag = 0;
short HTG_all_calls_dynamic = 0;
short HTG_retain_symbols_flag = 0;
short HTG_dynamic_flag = 0;
short HTG_shlib_soname_flag = 0;
short HTG_libcob = 0;
short HTG_programid_name_trans_flag = 0;
short HTG_stoprun_proc_flag = 0;
short HTG_cursesio_set = 0; 
short HTG_codeFormat;

char  HTG_COPYDIR[PATHMAX1 + 2] = "";
char  HTG_TMPDIR[PATHMAX];
char  HTG_CCX_CMD[PATHMAX];
char  HTG_ASX_CMD[PATHMAX];

char  HTG_OBJECT[PATHMAX];
char  HTG_EXECUTABLE[PATHMAX];
char  HTG_LIBNAME[PATHMAX];
char  HTG_LD_OPTIONS[120] = "";
char  HTG_LD_PATHS[120] = "";
char  HTG_LD_ARGS[PATHMAX2] = "";
char  HTG_LD_RESOPT_ARGS[PATHMAX2] = "";
char  HTG_LD_CMDLINE_ARGS[PATHMAX2] = "";
char  HTG_LD_DYNAMIC[10] = "";
char  HTG_LD_DEFAULTS_ARGS[PATHMAX2] = "";
char  HTG_LD_LIBRARY_PATHS_EXTRA_ARGS[PATHMAX2] = "";

char  HTG_LD_EXTRA_ARGS[120] = "";
char  HTG_LD_DCALL_ARGS[120] = "";

char  HTG_PCAL_RESOPT_ARGS[PATHMAX] = "";
char  HTG_SHLIB_NAME_DEFAULT[120] = "";

char  HTG_LD_FLAGS[256] = "";

char  file_path[PATHMAX];
char  file_base[PATHMAX];
char  file_ext[PATHMAX];
char  ofile[PATHMAX];
char  COBFLAGS[64];
char  COBLDFLAGS[64];
char  file_pgmlist_suffix[PATHMAX] = ".lis";
char  lib_prefix[PATHMAX] = "tcob";
int   HTG_grp_desc_len = FLD_DESC_SIZE0;
int   HTG_fld_desc_len = FLD_DESC_SIZE1;

char  COBDIR[PATHMAX];
char  COBOPT[PATHMAX];
char  PWD[PATHMAX];

#if defined(__MINGW32__ )
char  COBINSTDIR[PATHMAX];
#endif

char  cmdstr[PATHMAX + PATHMAX1 + 1];

char  cobpp_flag_E;
char  cobpp_tabs[10];
int   HTG_tab2space;
char  *cobpp_fpath;
char  HTG_process_level;

char HTG_FNAME_SUFFIX[PATHMAX3] = "";
char fpath[PATHMAX1 + 2] = ""; 
char fsuffix[PATHMAX] = ""; 

FILE *yyin;
FILE *o_src=NULL;
FILE *o_lst=NULL;

extern FILE *pp_yyin;
extern FILE *pp_yyout;
/* extern FILE *pp_yylist; */
extern char *pp_filename;

extern int pp_yyparse(void);

/* Internal function declarations */
int check_option (char *, char *);
static void init_env (char *buf, const char *env, const char *def);
void process_verbose_options (int ac, char *av[]);
void process_bind_options (char *arglist);
void initialize_setup (void);
void append_include_path(char *ap);
void setup_filenames(void);
void print_compiler_banner(void);
void print_copybooks_path(void);
void setup_ld_paths(void);
void print_listing_file(void);
int  process_pp(void);
int  process_compile (void);
void process_select_verify(char compile_level);
void output_select_verify (char output_type);
int  find_source_file(void);
void copytrip (char *sout, char *sin);
void pass_options_ld (char *s);

char OPTFILE[PATHMAX];
char argtmp[PATHMAX];
char *prg_name;
char pgm_suffixes[PATHMAX] = HTG_PGM_SUFFIXES;

/* All libraries are now required by the RTL */ 
int  HTG_prg_uses_fileio = 1; 
/* Curses library is required by the run-unit termination routines */ 
int  HTG_prg_uses_term   = 1; 
int  HTG_prg_uses_dcall  = 0; 

int  HTG_norun_flag = 0; 

/* Command line options */
//tcb_compile_flags tcb_compile_flags_cmdline; 
/* Resource file options  */
//tcb_compile_flags tcb_compile_flags_fres; 

extern int stabs_on_sw;
extern int read_compiler_options(void);


int process_command_line (int argc, char *argv[], int *nidx)
{
  int sw, idx=0, i, r=0;

  /* Parse the command line, determining what features have been selected */
  while ((sw = getopt_long_only (argc, argv, short_option_list, long_option_list, &i)) >= 0) {

#ifdef DEBUG_COMPILER_LEVEL2
    printf("# htglobals: process_command_line: switch: %c\n", sw); 
#endif

    switch (sw)  {
      
      case TCB_CMDOPT_NIL:
        break;
      case TCB_CMDOPT_DEBUG_TRACE: 
        HTG_debug_trace_flag = 1; 
        break;
      case TCB_CMDOPT_DEBUG_LINES: 
        HTG_debug_lines_flag = 1; 
        break;
      case TCB_CMDOPT_BIND_MODE:
        process_bind_options(optarg);
        break;
      case TCB_CMDOPT_OUTPUT_NAME:
        strcpy (ofile, optarg);
        break;
      case TCB_CMDOPT_INCLUDE_PATH:
        if (idx == 0) {
           strcpy (HTG_COPYDIR, "");
           idx = 1;
        }
        append_include_path(optarg);
        break;
      case TCB_CMDOPT_LISTING:
        HTG_list_flag = TRUE;
        break;
      case TCB_CMDOPT_DEBUG:
        stabs_on_sw = 1;
        strcat (HTG_LD_OPTIONS, "-g ");
        break;
      /* Set entry module to call from main */
/*
OLD:
      none (0) - Do NOT generate any program entry point. 
      auto (1) - Use the first encountered 'STOP RUN' statement, 
                 and if found, generate a program entry point.
       any (2) - Use the first encountered 'STOP RUN' statement, 
                 if NOT found, use the first encountered 'PROGRAM-ID' statement,
                 and generate a program entry point.
  specific (3) - Specific program entry point defined using 
                 the '-e' CMD line option. 
NEW:
      none (0) - Do NOT generate any program entry point. 
      auto (1) - Use the first encountered 'PROGRAM-ID' statement.
  specific (3) - Specific program entry point defined using 
                 the '-e entry-name' CMD line option. 

*/
      /* Specify main entry point name */
      case TCB_CMDOPT_ENTRY_NAME:
        if (main_flag != 3) {          
           main_flag = 3;
           strcpy(main_entry_buf, optarg);
        }
        else {
           fprintf (stderr, "Multiple entry point name \'%s\' entered ... ignoring\n", optarg);           
        }
        break;

      /* Specify the main entry point action */
      case TCB_CMDOPT_MAIN_ENTRY:
        if ((main_flag == 0) || (main_flag == 1)) {
           main_flag = 2;
        }
        break;

      /* Define as shared library or module  */
      case TCB_CMDOPT_LIB_SHARED:
        output_select_verify (TCB_CMDOPT_LIB_SHARED);
        HTG_compile_level_type_flag = TCB_COMPILE_TYPE_MODULE;
	module_flag = TRUE;
        strcat (HTG_LD_OPTIONS, "-shared ");
        main_entry_flag = FALSE;
        main_flag = FALSE;         
        break;

      case TCB_CMDOPT_EXECUTABLE:
        output_select_verify (TCB_CMDOPT_EXECUTABLE);
        HTG_compile_level_type_flag = TCB_COMPILE_TYPE_PROGRAM;
        break;

      case TCB_CMDOPT_SOURCE_OPEN:
        HTG_codeFormat = TCB_SOURCE_CODE_FORMAT_FREE;
        break;

      case TCB_CMDOPT_SOURCE_FIXED:
        HTG_codeFormat = TCB_SOURCE_CODE_FORMAT_FIXED;
        break;

      case TCB_CMDOPT_PREPROCESSOR:
        process_select_verify (TCB_CMDOPT_PREPROCESSOR);
        HTG_compile_level_flag = TCB_COMPILE_LEVEL_PREPROCESS;
        cobpp_flag_E = '1';
        break;

      case TCB_CMDOPT_COMPILE:
        process_select_verify (TCB_CMDOPT_COMPILE);
        HTG_compile_level_flag = TCB_COMPILE_LEVEL_COMPILE;
        HTG_assemble_flag = TRUE;
        break;

      case TCB_CMDOPT_TAB_NUMBER:
        strncpy (cobpp_tabs, optarg, 10);
        cobpp_tabs[9] = '\0';
        sscanf(cobpp_tabs, "%d", &HTG_tab2space);
        break;

      case TCB_CMDOPT_ASSEMBLE:
        process_select_verify (TCB_CMDOPT_ASSEMBLE);
        HTG_make_object_flag = TRUE;
        HTG_compile_level_flag = TCB_COMPILE_LEVEL_ASSEMBLE;
        break;

/*    TCB_CMDOPT_INCLUDE_LIB         'l' */
      case TCB_CMDOPT_INCLUDE_LIB:
        strcat (HTG_LD_CMDLINE_ARGS, "-l");
        strcat (HTG_LD_CMDLINE_ARGS, optarg);
        strcat (HTG_LD_CMDLINE_ARGS, " ");
        break;

/*    TCB_CMDOPT_LIB_PATH            'L' */
      case TCB_CMDOPT_LIB_PATH:
/*
//        strcat (HTG_LD_CMDLINE_ARGS, "-L");
//        strcat (HTG_LD_CMDLINE_ARGS, optarg);
//        strcat (HTG_LD_CMDLINE_ARGS, " ");
*/
        strcat (HTG_LD_PATHS, " ");
        strcat (HTG_LD_PATHS, "-L"); 
        strcat (HTG_LD_PATHS, optarg); 
        strcat (HTG_LD_PATHS, " ");
        break;

/*     TCB_CMDOPT_PASS_OPTIONS   'W' */
      case TCB_CMDOPT_PASS_OPTIONS:
        if (optarg != NULL) {
           if (*optarg != 'l' ) {
              fprintf (stderr, "Invalid sub-option \'%c\' selected ... ignoring", *optarg);
           }
           else {
              pass_options_ld (optarg);
           }
        }
        break;

      case TCB_CMDOPT_VERY_VERBOSE:
        HTG_verbose_verbose_flag = TRUE; 
        HTG_verbose_flag = TRUE; 
        break;

      case TCB_CMDOPT_VERBOSE:
        HTG_verbose_flag = TRUE; 
        break;

      case TCB_CMDOPT_TESTMODE:
        HTG_retain_symbols_flag = TRUE;
        break;

      case TCB_CMDOPT_NORUN:
        HTG_norun_flag = TRUE;
        HTG_verbose_flag = TRUE; 
        break;

      case TCB_CMDOPT_CALLS_DYNAMIC:
        HTG_all_calls_dynamic = TRUE;
	    break;

      case TCB_CMDOPT_LIBCOB:
        HTG_libcob = TRUE;
	strcpy(lib_prefix, "cob");
	printf("Lib cob option on (%s)!!\n", lib_prefix);
	HTG_grp_desc_len = CFLD_DESC_SIZE0;
	HTG_fld_desc_len = CFLD_DESC_SIZE1;
	    break;
/*            
      case TCB_CMDOPT_CURSESIO_SET: 
        HTG_cursesio_set = TRUE; 
        HTG_prg_uses_term = 1; 
	    break;
*/
      case TCB_CMDOPT_VERSION: 
        fprintf (stdout, "%s %s\n", HTG_PGM_NAME, TCOB_PGM_VERSION);
        fprintf (stdout, "%s", HTG_COPYWR);
        //exit (0);
        r++;
        break;

      case TCB_CMDOPT_HELP:
      default:
        {
         int i=0;
         fprintf (stdout, "Usage: %s [options] file\n", argv[0]);
         while (htg_options_string[i].s != NULL) {
           fprintf (stdout, "%s\n", htg_options_string[i].s);           
           i++;
         }
        }
        r++;
        //exit (0);
        break;
    }
  }
  
  /* Check for conflicting command line options  */
  /*    fprintf (stderr, "%s: *** Multiple and/or conflicting command line options, '%c' and '%c', selected. Abort.\n", prg_name, compile_level_0, compile_level); */

    
  if (HTG_compile_level_flag == TCB_COMPILE_LEVEL) {
     if (HTG_compile_level_default == TCB_COMPILE_LEVEL) 
        HTG_compile_level_flag = TCB_COMPILE_LEVEL_EXECUTABLE;
     else 
        HTG_compile_level_flag = HTG_compile_level_default;
  }

#ifdef DEBUG_COMPILER_LEVEL2
  fprintf (stderr, "debug: process_command_line 8: HTG_compile_level_flag=%d, HTG_compile_level_default=%d;\n", HTG_compile_level_flag, HTG_compile_level_default); 
#endif

  if (HTG_compile_level_type_flag == TCB_COMPILE_TYPE) {
     if (HTG_compile_level_type_default == TCB_COMPILE_TYPE) 
        HTG_compile_level_type_flag = TCB_COMPILE_TYPE_PROGRAM;
     else 
        HTG_compile_level_type_flag = HTG_compile_level_type_default;
  }

#ifdef DEBUG_COMPILER_LEVEL2
  fprintf (stderr, "debug: process_command_line 9: HTG_compile_level_type_flag=%d, HTG_compile_level_type_default=%d;\n", HTG_compile_level_type_flag, HTG_compile_level_type_default); 
#endif
   
  *nidx = optind;
  return r;
}

/* **********************************************
 * * Clean up working files as needed.          *
 * **********************************************/
void do_file_cleanup ()
{
  if (HTG_retain_symbols_flag != TRUE) {
     switch (HTG_compile_level_flag)  {

        case TCB_COMPILE_LEVEL_PREPROCESS:
          break;

        case TCB_COMPILE_LEVEL_COMPILE:
          remove (working_filename);
          break;
      
        case TCB_COMPILE_LEVEL_ASSEMBLE:
          remove (working_filename);
          remove (output_filename);
          break;
      
        case TCB_COMPILE_LEVEL_EXECUTABLE:
          remove (working_filename);
          remove (output_filename);
          remove (HTG_OBJECT);
          break;
      
     }    
  }
}

/* **********************************************
 * * Execute assembler to generate object file  *
 * **********************************************/
int process_assemble (void)
{
  int rc=0;

  if (stabs_on_sw == 1) {
/* 
 *  Note: The '--gstabs' will not work properly
 *  It will generate stabs in the assembler and override the TC ones.
 *     sprintf (sys_buf, "%s -D --gstabs -o %s %s", HTG_ASX_CMD, HTG_OBJECT, output_filename);
*/
     sprintf (sys_buf, "%s -D -o %s %s", HTG_ASX_CMD, HTG_OBJECT, output_filename);  
  }
  else {
     sprintf (sys_buf, "%s -o %s %s", HTG_ASX_CMD, HTG_OBJECT, output_filename);  
  }
  
  if (HTG_verbose_flag == TRUE)
     printf ("%s\n", sys_buf);

  if (HTG_verbose_verbose_flag == TRUE)
     printf ("Compiler assembly phase ... ");
  
  if (HTG_norun_flag == 0) 
     rc = system (sys_buf);

  if (HTG_verbose_verbose_flag == TRUE ) 
     printf ("return code = %2d\n", rc);

  if (rc > 0) 
     return (8);

  return rc;
}


/* Generate executable file  */
int process_ld (void)
{
  int rc=0;

  setup_ld_paths();
  
  sprintf (sys_buf, "%s ", HTG_CCX_CMD);
  if (strlen(HTG_LD_OPTIONS) > 0)
     strcat(sys_buf, HTG_LD_OPTIONS);

  strcat(sys_buf, "-o ");
  strcat(sys_buf, HTG_EXECUTABLE);
  strcat(sys_buf, " ");
  strcat(sys_buf, HTG_OBJECT);
  strcat(sys_buf, " ");
  
  if (strlen(HTG_LD_DYNAMIC) > 0) {
     strcat(sys_buf, HTG_LD_DYNAMIC);
     strcat(sys_buf, " ");
  }

  if (strlen(HTG_LD_FLAGS) > 0) {
     strcat(sys_buf, HTG_LD_FLAGS);
     strcat(sys_buf, " ");
  }
  

  if (strlen(HTG_LD_CMDLINE_ARGS) > 0)
     strcat(sys_buf, HTG_LD_CMDLINE_ARGS);


  if (strlen(HTG_LD_RESOPT_ARGS) > 0) {
     strcat(sys_buf, HTG_LD_RESOPT_ARGS);
     strcat(sys_buf, " ");
  }
  
  if (HTG_verbose_flag == TRUE)
      printf ("%s\n", sys_buf);

  if (HTG_verbose_verbose_flag == TRUE)
     printf ("linking %s ... ", HTG_EXECUTABLE);

  if (HTG_norun_flag == 0) 
     rc = system (sys_buf);

  if (HTG_verbose_verbose_flag == TRUE)
     printf ("return code = %2d\n", rc);

  if (rc > 0)
      return (12);

  return rc;
}

/* Execute link edit to generate shared library   */
int process_shlib_ld(void)
{
  int rc=0;

  sprintf (sys_buf, "%s ", HTG_CCX_CMD);
  if (strlen(HTG_LD_OPTIONS) > 0)
     strcat(sys_buf, HTG_LD_OPTIONS);
/*
 ${CCX} -shared -Wl,--out-implib,${lib_name1}.dll.a -o ${SHARED_LIB1} $(OBJD1) ${LIBS}
 ${CCX} -shared -Wl,--out-implib,${lib_name2}.dll.a,--output-def,${lib_name2}.def -o ${SHARED_LIB2} $(OBJS2) ${LIBS}
 ${CCX} -shared -Wl,-soname,lib${lib_name1}.so.0 -o ${SHARED_LIB1} $(OBJD1) ${LIBS} 
*/
  if (HTG_shlib_soname_flag == 0) {
#ifndef WIN32
     strcat(sys_buf, "-Wl,-soname,");
     strcat(sys_buf, HTG_LIBNAME);     
#else
     strcat(sys_buf, "-Wl,--enable-auto-import,--out-implib,");
     strcat(sys_buf, HTG_LIBNAME);     
     strcat(sys_buf, ".a,--output-def,");     
     strcat(sys_buf, file_base);     
     strcat(sys_buf, ".def");
#endif
  }
  
  strcat(sys_buf," -o ");
  strcat(sys_buf, HTG_EXECUTABLE);  	
  strcat(sys_buf, " ");
  strcat(sys_buf, HTG_OBJECT);
  strcat(sys_buf, " ");
  strcat(sys_buf, HTG_LD_PATHS);
  strcat(sys_buf, " ");
/* TC run-time not required in link step for ELF modules */
#ifdef WIN32
  strcat(sys_buf, TCOB_LD_ARGS_HTCOBOL);    
  strcat(sys_buf, " "); 
#endif
/*  strcat(HTG_LD_ARGS, HTG_LD_HT2_ARGS); */
/*  strcat(sys_buf, " "); */

  if (strlen(HTG_LD_CMDLINE_ARGS) > 0)
     strcat(sys_buf, HTG_LD_CMDLINE_ARGS);
  
  if (HTG_verbose_flag == TRUE)
      printf ("%s\n", sys_buf);

  if (HTG_verbose_verbose_flag == TRUE)
     printf ("linking %s ... ", HTG_EXECUTABLE);

  if (HTG_norun_flag == 0) 
     rc = system (sys_buf);

  if (HTG_verbose_verbose_flag == TRUE)
     printf ("return code = %2d\n", rc);

  if (rc > 0)
      return (12);

  return rc;
}

/* --- Removed as compiler option - DE
  Execute link edit to generate static library   
int process_lib_ld (void)
{
  int rc=0;

  sprintf (sys_buf, "%s cr %s %s ", HTG_ARX_CMD, HTG_EXECUTABLE, HTG_OBJECT);
  
  if (HTG_verbose_flag == TRUE)
      printf ("%s\n", sys_buf);

  if (HTG_verbose_verbose_flag == TRUE)
     printf ("creating archive %s ... ", HTG_EXECUTABLE);

  if (HTG_norun_flag == 0) 
     rc = system (sys_buf);

  if (HTG_verbose_verbose_flag == TRUE)
     printf ("return code = %2d\n", rc);

  if (rc > 0)
      return (12);

  sprintf (sys_buf, "%s %s ", HTG_RANLIBX_CMD, HTG_EXECUTABLE);
  
  if (HTG_verbose_flag == TRUE)
      printf ("%s\n", sys_buf);

  if (HTG_verbose_verbose_flag == TRUE)
     printf ("ranlib archive %s ... ", HTG_EXECUTABLE);

  if (HTG_norun_flag == 0) 
     rc = system (sys_buf);

  if (HTG_verbose_verbose_flag == TRUE)
     printf ("return code = %2d\n", rc);

  if (rc > 0)
      return (12);

  return rc;
}
*/

/* Read resource file (htcobolrc) compiler options */
int read_compiler_options (void)
{
  FILE *cobopt;
  char optbfr[PATHMAX2 + 1];
  char optstr[PATHMAX2 + 1];
  char optarg[PATHMAX2 + 1];
  int i, j, len, r=0;

  i = 0;
  j = 0;

  if ((cobopt = fopen (OPTFILE, "r")) == NULL)  {
      fprintf (stderr, "warning: TinyCOBOL compiler resource file '%s' not found - using internal defaults\n", OPTFILE);
      return (1);
  }
  
  if (HTG_verbose_verbose_flag == TRUE) {
     printf ("Processing compiler options file parameters\n");
  }
  
  i = 0;
  j = 0;
  optstr[0] = 0;
  optarg[0] = 0;
  fgets (optbfr, PATHMAX2, cobopt);

  while (!feof (cobopt))  {

    len = strlen (optbfr);
    if (len > 1) 
       optbfr[len - 1] = 0;
    len--;
    if (len > 1 && optbfr[0] != CHR_NPOUND)  {
      /* Scan and extract property before EQUAL sign */
      while (optbfr[i] != CHR_EQUAL && i < len) {
          if (optbfr[i] != CHR_SPACE) {
             optstr[j] = optbfr[i];
             j++;
             optstr[j] = 0;
          }
          i++;
      }
      i++; /* Skip EQUAL sign */
      /* Skip any blanks after equal sign */
      while (optbfr[i] == CHR_SPACE && i < len) 
         i++;
      j = 0;
      /* len = strlen (optbfr); */
      if (i < len) {
         /* Check for literals using single or double quote */
         if ((optbfr[i] == CHR_DQUOTE) || (optbfr[i] == CHR_SQUOTE)) {
            char quote = optbfr[i];
            i++;
            /* Extract literal value */
            while ((optbfr[i] != quote) && (i < len))  {
                optarg[j] = optbfr[i];
                i++;
                j++;
                optarg[j] = 0;
            }
         }
         else {
            /* Extract value removing trailing spaces */
            while (i < len)  {
                optarg[j] = optbfr[i];
                i++;
                j++;
            }
            optarg[j] = 0;
            len = strlen(optarg);
            i = len - 1;
            /* Removing trailing spaces */
            while (i >= 0)  {
              if (optbfr[i] != CHR_SPACE) 
                 break;
              optarg[j] = 0;
              i--;
            }
         }
      }
/*      
      if (strlen (optarg) == 0)  {
          optstr[strlen (optstr) - 1] = 0;
      }
      else {
          optarg[strlen (optarg) - 1] = 0;
      }
#if 0
      len = strlen (optstr);
      if (len > 0 && optstr[0] != CHR_NPOUND)  {
          check_option (optstr, optarg);
      }
#endif
*/
#ifdef DEBUG_COMPILER_LEVEL2
      fprintf (stderr, "debug: read_compiler_options 0: optstr=%s, optarg=%s;\n", optstr, optarg); 
#endif
      r += check_option (optstr, optarg);

    }
    i = 0;
    j = 0;
    optstr[0] = 0;
    optarg[0] = 0;
    fgets (optbfr, PATHMAX2, cobopt);
  }
  fclose (cobopt);
  return r;
}


int check_option (char *option_in, char *arg)
{

  int i, j=NONE, prop=NONE, type=NONE, r=0;

#ifdef DEBUG_COMPILER_LEVEL2
  fprintf (stderr, "debug: check_option 0: option_in=%s, arg=%s;\n", option_in, arg); 
#endif

  for (i=0; resource_options[i].option != NULL; i++) {
      if (strcasecmp(resource_options[i].option, option_in) == 0) {
          type = resource_options[i].type;
          prop = resource_options[i].isel;
          j = i;
          break;
      }
  }

#ifdef DEBUG_COMPILER_LEVEL2
  fprintf (stderr, "debug: check_option 1: prop=%d, type=%d, j=%d;\n", prop, type, j); 
#endif

  switch (j)    
  {
    case TCB_RESOURCE_OPTION_NAME_CROSS_REFERENCE_LISTING:
      r = verify_binary_opition(option_in, arg, &HTG_xref_flag);
      break;

    case TCB_RESOURCE_OPTION_NAME_PROGRAM_LISTING_SUFFIX:
      strcpy(file_pgmlist_suffix, arg);
      break;

    case TCB_RESOURCE_OPTION_NAME_PROGRAM_LISTING:
      r = verify_binary_opition(option_in, arg, &HTG_list_flag);
      break;

    case TCB_RESOURCE_OPTION_NAME_INCLUDE_DEBUGGING_LINES:
      r = verify_binary_opition(option_in, arg, &HTG_debug_lines_flag);
      break;

    case TCB_RESOURCE_OPTION_NAME_DEFAULT_COMPILE_TYPE:
      r = verify_attribute_opition(option_in, arg, prop, &HTG_compile_level_type_default);
#ifdef DEBUG_COMPILER_LEVEL2
      fprintf (stderr, "debug: check_option 1: HTG_compile_level_flag=%d, HTG_compile_level_type_flag=%d;\n", HTG_compile_level_flag, HTG_compile_level_type_flag);
#endif
      if (HTG_compile_level_type_default == TCB_COMPILE_TYPE_MODULE) {
         module_flag = TRUE;
         main_flag = FALSE;
         strcat (HTG_LD_OPTIONS, "-shared ");
         main_entry_flag = FALSE;
      }
      break;

    case TCB_RESOURCE_OPTION_NAME_DEFAULT_COMPILE_ACTION:
      r = verify_attribute_opition(option_in, arg, prop, &HTG_compile_level_default);
#ifdef DEBUG_COMPILER_LEVEL2
      fprintf (stderr, "debug: check_option 2: HTG_compile_level_flag=%d, HTG_compile_level_type_flag=%d;\n", HTG_compile_level_flag, HTG_compile_level_type_flag);
#endif
      break;

    case TCB_RESOURCE_OPTION_NAME_DEFAULT_SOURCE_FORMAT:
      r = verify_attribute_opition(option_in, arg, prop, &HTG_codeFormat);
      break;

    case TCB_RESOURCE_OPTION_NAME_PROGRAM_ID_TRANSFORMATION:
      r = verify_attribute_opition(option_in, arg, prop, &HTG_programid_name_trans_flag);
      break;

    case TCB_RESOURCE_OPTION_NAME_SOURCE_PROGRAM_SUFFIXES:
      strcpy(pgm_suffixes, arg);
      break;

    case TCB_RESOURCE_OPTION_NAME_COPYBOOK_PATH:
      strcpy(HTG_COPYDIR, arg);
      break;
/*
//    case TCB_RESOURCE_OPTION_NAME_COPYBOOK_SUFFIXES:
//      break;
*/
    case TCB_RESOURCE_OPTION_NAME_STOPRUN_PROCEDURE:
      r = verify_attribute_opition(option_in, arg, prop, &HTG_stoprun_proc_flag);
      break;
/*
    case TCB_RESOURCE_OPTION_NAME_LD_LIBRARY_PATH:
      break;
*/

    case TCB_RESOURCE_OPTION_NAME_LD_DEFAULT:
      strcpy(HTG_LD_DEFAULTS_ARGS, arg);
      break;

    case TCB_RESOURCE_OPTION_NAME_LD_LIBRARY_PATHS_EXTRA:
      strcpy(HTG_LD_LIBRARY_PATHS_EXTRA_ARGS, arg);
      break;

    case TCB_RESOURCE_OPTION_NAME_DEFAULT_SHARED_LIBRARY_NAME:
      strcpy(HTG_SHLIB_NAME_DEFAULT, arg);
      break;

    case TCB_RESOURCE_OPTION_NAME_PROGRAM_ENTRY_POINT:
      r = verify_attribute_opition(option_in, arg, prop, &main_flag);
#ifdef DEBUG_COMPILER_LEVEL2
      fprintf (stderr, "debug: check_option 4: main_flag=%d;\n", main_flag);
#endif
      break;

    case TCB_RESOURCE_OPTION_NAME_LD_LIBRARY_EXTRA:
      strcpy(HTG_LD_EXTRA_ARGS, arg);
      break;

    case TCB_RESOURCE_OPTION_NAME_LD_FLAGS_EXTRA:
      strcpy(HTG_LD_FLAGS, arg);
      break;

    default:
      fprintf (stderr, "%s: WARNING - Ignoring unknown resource file option '%s'.\n", prg_name, option_in);
      r = 4;
      break;
  }

  return r;
}

int verify_attribute_opition(char *option, char *arg, int attribute, short *value)
{
  int r = NONE, i, optidx=NONE;
  
#ifdef DEBUG_COMPILER_LEVEL2
  fprintf (stderr, "debug: verify_attribute_opition 0: option=%s, arg=%s, attribute=%d;\n", option, arg, attribute);  
#endif

  /* Scan for the relative index */
  for (i=0; attribute_options[i].attribute != NONE; i++) {
#ifdef DEBUG_COMPILER_LEVEL2
      fprintf (stderr, "debug: verify_attribute_opition 1: i=%d, attribute=%d;\n", i, attribute_options[i].attribute);  
#endif
      if (attribute_options[i].attribute == attribute) {
          optidx = i;
          break;
      }
  }
   
  if (optidx != NONE) {
     for (i=0; attribute_options[optidx].option[i] != NULL; i++) {
#ifdef DEBUG_COMPILER_LEVEL2
         fprintf (stderr, "debug: verify_attribute_opition 2: i=%d, optidx=%d;\n", i, optidx);  
#endif
         if (strcasecmp(attribute_options[optidx].option[i], arg) == 0) {
             *value = attribute_options[optidx].ivalue[i];
#ifdef DEBUG_COMPILER_LEVEL2
             fprintf (stderr, "debug: verify_attribute_opition 3: i=%d, value=%d;\n", i, *value);  
#endif
             r = 0;
             break;
         }
     }
  }
   
  if (r != 0) 
     fprintf (stderr, "Error: Invalid value '%s' for option '%s' found in TinyCOBOL compiler resource file\n", arg, option);
  
  return r;
}

int verify_binary_opition(char *option, char *arg, short *value)
{
  int r=NONE, i;
  
#ifdef DEBUG_COMPILER_LEVEL2
  fprintf (stderr, "debug: verify_binary_opition 0: option=%s, arg=%s;\n", option, arg); 
#endif

  for (i=0; binary_options[i].value != NULL; i++) {
      if (strcasecmp(binary_options[i].value, arg) == 0) {
#ifdef DEBUG_COMPILER_LEVEL2
          fprintf (stderr, "debug: verify_binary_opition 1: arg=%s, ivalue=%d;\n", arg, binary_options[i].ivalue);  
#endif
          *value = binary_options[i].ivalue;
          r = 0;
          break;
      }
  }
   
  if (r != 0) 
     fprintf (stderr, "Error: Invalid value '%s' for option '%s' found in TinyCOBOL compiler resource file\n", arg, option);
  
  return r;
}

void copytrip(char *sout, char *sin)
{
  char *pt1, *pt2;
  int len, i;
  
  pt1=NULL;
  pt2=NULL;
    
#ifdef DEBUG_COMPILER_LEVEL2
  fprintf (stderr, "debug: copytrip 0: sin=%s;\n", sin); 
#endif

  len = strlen(sin);
  for (i=0; i<len; i++) {
    if (sin[i] != ' ') {
       if (pt1 == NULL) {
    	 pt1 = sin + i;
    	 pt2 = sin + i;
       }
       else {
    	 pt2 = sin + i;
       }
    }
  }
  
  if (pt1 != NULL) {
    if ((i = pt2 - pt1) >= 0) {
       strncpy(sout, pt1, i+1);
       sout[i+1] = '\0';
    }
  }
  
#ifdef DEBUG_COMPILER_LEVEL2
  fprintf (stderr, "debug: copytrip 9: sin=%s, sout=%s;\n", sin, sout); 
#endif

}

int find_source_file(void) 
{
  int rc = 1; 
  char del[2] = LT_PATHSEP_STR, *pt, fpath[PATHMAX2];
  struct stat sbuf;
  

  /* Check using full path file name */
  if (strlen (file_ext) != 0) {     
     sprintf(input_filename, "%s%s%s", file_path, file_base, file_ext);
     if (stat(input_filename, &sbuf) == 0) {
        rc = 0;
     }
     return rc;
  }

  strcpy(fpath, pgm_suffixes);
  pt = strtok(fpath, del); 
  while (pt != NULL) {
    sprintf(input_filename, "%s%s%s", file_path, file_base, pt);
    if (HTG_verbose_verbose_flag == TRUE ) {
       printf("Checking for source filename (fullpath) =%s\n", input_filename);
    } 
    if (stat(input_filename, &sbuf) == 0) {
       if (HTG_verbose_verbose_flag == TRUE ) {
          printf("Found source filename (fullpath) =%s\n", input_filename);
       } 
       strcpy (file_ext, pt);
       rc = 0;
       pt = NULL;
    }
    else {
       pt = strtok(NULL, del);
    }
  }
     
  return rc;
}

void init_env(char *buf, const char *env, const char *def)
{
  char *s = getenv (env);
  if (s)
    strcpy (buf, s);
  else
    strcpy (buf, def);
}

int pexec(char *cmdstr) 
{
  int rc=0, i, pid, argcexe;
  char *argvexe[256], *tmpt; 
  
  argcexe = 0;
  tmpt = strtok(cmdstr, " ");
  while (tmpt != NULL) {
       argvexe[argcexe] = malloc(strlen(tmpt)+1);
       strcpy(argvexe[argcexe], tmpt);
#ifdef DEBUG_COMPILER_LEVEL2
       fprintf(stderr, "htglobals debug: argvexe[%d]:%s:\n", argcexe, argvexe[argcexe]); 
#endif
       argcexe++;   
       tmpt = strtok(NULL, " ");
  }
  argvexe[argcexe] = NULL;
       
#ifndef __MINGW32__
     
  switch (pid = fork())
  {
    case NONE:
      fprintf(stderr, "fork failed... aborting\n");
      exit(1);
      break;

    case NIL:
      execv(argvexe[0], argvexe);
/*      fprintf(stderr, "Cannot spawn \"%s\" execv failed\n", argvexe[0]); */
      fprintf(stderr, "error: Failed to spawn pre-processor \"%s\"\n", argvexe[0]);
      exit(12);
      break;
  }
  
/*  waitpid(pid, &rc, 0); */
  wait(&rc);

#ifdef DEBUG_COMPILER_LEVEL2
  fprintf(stderr, "debug: htglobals: exec \'%s\' return status=%d\n", argvexe[0], rc); 
#endif

#else

  pid = spawnv (1, argvexe[0], argvexe);
  pid = cwait (&rc, pid, WAIT_CHILD);

#endif

  for (i = 0; i < argcexe; i++) {
       free(argvexe[i]);
  }
  
  return rc;
}

void process_bind_options(char *arglist)
{
  if (strcmp (arglist, "static") == 0) {
     HTG_dynamic_flag = 1;
     strcpy (HTG_LD_DYNAMIC, "-static");
     strcat (HTG_LD_DYNAMIC, " ");    
  }
  else {
     if (strcmp (arglist, "dynamic") == 0)  {
         strcpy (HTG_LD_DYNAMIC, "-dynamic");
         strcat (HTG_LD_DYNAMIC, " ");    
         HTG_dynamic_flag = 2;
     }
     else {
         fprintf (stderr, "Unknown bind option %s specified, (static,dynamic) ignoring\n", arglist);
     }
  }
}

void process_verbose_options(int ac, char *av[])
{  
  int i;
  char *pt, op;
  
  for (i=1; i<ac; i++) {  
#ifdef DEBUG_COMPILER_LEVEL2
    fprintf (stderr, "htglobals debug 1: process_verbose_options: av[%d]=%s;\n", i, av[i]); 
#endif
    pt = av[i];
    if (*pt == '-') {
       op = *(pt + 1);    
#ifdef DEBUG_COMPILER_LEVEL2
       fprintf (stderr, "htglobals debug 2: process_verbose_options: op=%c\n", op); 
#endif
       switch (op) {
         case TCB_CMDOPT_VERY_VERBOSE:
            HTG_verbose_verbose_flag = TRUE;
            HTG_verbose_flag = TRUE;
            break;
         case TCB_CMDOPT_VERBOSE:
            HTG_verbose_flag = TRUE; 
            break;
          default:
            break;
       }
    }
  }
#ifdef DEBUG_COMPILER_LEVEL2
  fprintf (stderr, "htglobals debug 3: process_verbose_options: HTG_verbose_flag=%d, HTG_verbose_verbose_flag=%d;\n", 
                    HTG_verbose_flag, HTG_verbose_verbose_flag); 
#endif
}

void initialize_setup(void)
{  
  int i;

  HTG_codeFormat = TCB_SOURCE_CODE_FORMAT_FREE;
  cobpp_flag_E   = '0';
  strcpy(cobpp_tabs, STR_DEFAULT_TAB_LEN);
  HTG_tab2space = DEFAULT_TAB_LEN;
  cobpp_fpath   = NULL;

  strcpy (HTG_CCX_CMD, TCOB_CCX_CMD);
  strcpy (HTG_ASX_CMD, TCOB_ASX_CMD);

  strcpy(HTG_SHLIB_NAME_DEFAULT, TCOB_SHLIB_EXT);

  /* Set compiler options default */
  HTG_list_flag = FALSE;
  HTG_xref_flag = FALSE;
  HTG_offset_flag = FALSE;
  HTG_assemble_flag = FALSE;
  HTG_full_compile_flag = FALSE;
  HTG_verbose_flag = FALSE;
  HTG_verbose_verbose_flag = FALSE;
  HTG_retain_symbols_flag = FALSE;
  HTG_dynamic_flag = 0;
  HTG_shlib_soname_flag = 0;

  HTG_compile_level_default = TCB_COMPILE_LEVEL_EXECUTABLE;
  HTG_compile_level_type_default = TCB_COMPILE_TYPE_PROGRAM;

  HTG_RETURN_CODE = 0;
  HTG_temporary_error_code = 256;
  HTG_temporary_severity = 12;

  stabs_on_sw = 0;

/*
 Clear out all of the name spaces just to    
 be sure that core garbage dosen't get us.   
 This only happens once, so there shouldn't  
 be any real performance issues.             
*/
  for (i = 0; i < PATHMAX; i++)  {
      input_filename[i] = 0;
      output_filename[i] = 0;
      ofile[i] = 0;
      list_filename[i] = 0;
      file_path[i] = 0;
      file_base[i] = 0;
      file_ext[i] = 0;
      HTG_TMPDIR[i] = 0;
      COBDIR[i] = 0;
      COBOPT[i] = 0;
      PWD[i] = 0;
  }

  strcpy(HTG_COPYDIR, "");

/* --- NOT USED ---

  // Extract relevent environment variables     
  init_env (COBFLAGS, "COBFLAGS", "");
  init_env (COBLDFLAGS, "COBFLAGS", "");
  init_env (HTG_TMPDIR, "TMPDIR", TMPDIR_DEFAULT_STR);

  if (HTG_TMPDIR[strlen (HTG_TMPDIR) - 1] != LT_DIRSEP_CHAR)
    {
      strcat (HTG_TMPDIR, LT_DIRSEP_STR);
    }
*/

#ifndef __MINGW32__
  init_env (COBDIR, HTG_COBDIR, TCOB_DEFAULTS_PATH);
#else
  /*init_env (COBDIR, HTG_COBDIR, COBINSTDIR);*/
  init_env (COBDIR, HTG_COBDIR, TCOB_DEFAULTS_PATH);
#endif 

#ifdef DEBUG_COMPILER_LEVEL2
  fprintf (stderr, "debug 10: initialize_setup: COBDIR=%s;\n", COBDIR); 
#endif

  strcpy (OPTFILE, COBDIR);
  strcat (OPTFILE, LT_DIRSEP_STR);
  strcat (OPTFILE, HTG_OPTFILE_DEFAULT);

#ifdef DEBUG_COMPILER_LEVEL2
  fprintf (stderr, "debug: initialize_setup 15: OPTFILE=%s;\n", OPTFILE);  
#endif

  init_env (PWD, "PWD", TCOB_DEFAULTS_PATH);
  
  HTG_LD_OPTIONS[0] = 0;
  HTG_LD_DYNAMIC[0] = 0;

}

void setup_filenames(void)
{
  int i, j, x, rc=0;
  char *tp, HTG_WORK[100];

  /* Isolate the base name of the file from  the path */
  i = strlen (file_path);
  while (i > 0 && file_path[i] != LT_DIRSEP_CHAR) 
      i--;
  if (i > 0) 
      i++;
  j = 0;
  x = strlen (file_path);
  while (i < x && i < PATHMAX)  {
      file_base[j++] = file_path[i];
      file_path[i++] = 0;
  }
  file_base[i] = 0;

  /* We have basename, now look for suffix   */
  while (i > 0 && file_base[i] != SUFFIX_SEP_CHAR)  
      i--;
  
  if (file_base[i - 1] == SUFFIX_SEP_CHAR)
     i++;

  j = 0;
  x = strlen (file_base);

  while (i < x && i < PATHMAX) {
      file_ext[j++] = file_base[i];
      file_base[i++] = 0;
  }

  file_ext[i] = 0;
  if (strlen (file_base) <= 0) {
      strcpy (file_base, file_ext);
      file_ext[0] = 0;
  }

  if (HTG_verbose_verbose_flag == TRUE)
      printf ("file path:%s; base name:%s; extention:%s;\n", file_path, file_base, file_ext);
/*      printf ("GEC=> path: (%s) base (%s) ext: (%s)\n", file_path, file_base, file_ext); */

/* Fumble around for file extension                
   Force an extension to prevent overwriting exe   */
  if (find_source_file() != 0) {
      rc=8;
      fprintf (stderr, "%s: Could not find input file for '%s%s%s' using search suffixes '%s'. Abort.\n", 
                       prg_name, file_path, file_base, file_ext, pgm_suffixes);
      exit(rc);
  }

  strcpy (working_filename, file_base);
  strcat (working_filename, HTG_FILE_PPOUT_SUFFIX);

  strcpy (list_filename, file_base);
  strcat (list_filename, file_pgmlist_suffix);

  strcpy (output_filename, file_base);
  strcat (output_filename, HTG_FILE_GAS_SUFFIX);

  strcpy (HTG_OBJECT, file_base);
  strcat (HTG_OBJECT, HTG_FILE_OBJECT_SUFFIX);

  switch (HTG_compile_level_flag)  
  {
    case TCB_COMPILE_LEVEL_ASSEMBLE:
      if (strlen (ofile) > 0)	{
  	 strcpy (HTG_OBJECT, ofile); 
      }
      break;

    case TCB_COMPILE_LEVEL_EXECUTABLE:
    default:
      /* PROGRAM type */
      if (HTG_compile_level_type_flag == TCB_COMPILE_TYPE_PROGRAM) {
         if (strlen (ofile) > 0)	{
  	    strcpy (HTG_EXECUTABLE, ofile); 
         }
         else  {
  	    strcpy(HTG_EXECUTABLE, file_base);
         }
      }
      /* MODULE type */
      else {
         if (strlen (ofile) > 0)	{
  	    strcpy (HTG_EXECUTABLE, ofile); 
  	    strcpy (HTG_LIBNAME, ofile); 
         }
         else  {
            strcpy (HTG_WORK, HTG_SHLIB_NAME_DEFAULT);
            strtok(HTG_WORK, SHLIB_SEP_STR);
            tp = strtok(NULL, SHLIB_SEP_STR);
            if (tp == NULL) {
  	       strcpy(HTG_LIBNAME, file_base); 
               tp = HTG_WORK;
               tp++;
  	       strcat(HTG_LIBNAME, tp);	      
            }
            else {
  	       strcpy(HTG_LIBNAME, HTG_WORK);
  	       strcat(HTG_LIBNAME, file_base);   
  	       strcat(HTG_LIBNAME, tp);
            }
  	    strcpy(HTG_EXECUTABLE, HTG_LIBNAME);
         }
      }
      break;
  }	       

#ifdef DEBUG_COMPILER_LEVEL2
  printf ("debug: htglobals (775): file_base=%s, output_filename=%s\n", file_base, output_filename); 
  printf ("debug: htglobals (777): file_base=%s, HTG_SHLIB_NAME_DEFAULT=%s, HTG_LIBNAME=%s\n", file_base, HTG_SHLIB_NAME_DEFAULT, HTG_LIBNAME); 
#endif
}

void print_compiler_banner(void)
{
  /* Print compiler banner */
  if (HTG_verbose_verbose_flag == TRUE )  { 
      fprintf (stdout, "%s - %s\n", HTG_PGM_NAME, TCOB_PGM_VERSION);
      fprintf (stdout, "%s", HTG_COPYWR);
  }
}

void print_copybooks_path(void)
{ 
  if (HTG_verbose_verbose_flag == TRUE )  {
      printf ("Processing '%s'\n", input_filename);
      printf ("Full include (copybooks) search path '%s'\n", HTG_COPYDIR);
/*      printf ("Output file '%s'\n", output_filename); */
  }
}

/* Use configure defaults to set linkage arguments */
void setup_ld_paths(void)
{ 
  int i;

#ifdef DEBUG_COMPILER_LEVEL2
  {
  int j = strlen(HTG_LD_ARGS); 
  fprintf (stderr, "debug: setup_ld_paths 0: HTG_prg_uses_term=%d, HTG_LD_ARGS=%s, j=%d;\n", 
                    HTG_prg_uses_term, HTG_LD_ARGS, j); 
  }
#endif

  /* gcc -g -o dyntest dyntest.o  -rdynamic -L. -lhtcobol -lm -ldl */
#ifndef __MINGW32__	  
  if (HTG_prg_uses_dcall == 1) {
     strcpy (HTG_LD_DYNAMIC, "-rdynamic");
     strcat (HTG_LD_DYNAMIC, " ");    
  }
#endif     

  if ((i=strlen(HTG_LD_DEFAULTS_ARGS)) > 0) {
     strcpy(HTG_LD_ARGS, HTG_LD_DEFAULTS_ARGS);    
  }
  else {
     strcat (HTG_LD_ARGS, TCOB_LD_PATHS_DEFAULT);
     strcat (HTG_LD_ARGS, " ");    
     strcat (HTG_LD_ARGS, TCOB_LD_ARGS_DEFAULT);
     strcat (HTG_LD_ARGS, " ");    
  }

  if ((i=strlen(HTG_LD_LIBRARY_PATHS_EXTRA_ARGS)) > 0) {
     strcat(HTG_LD_ARGS, " ");    
     strcat(HTG_LD_ARGS, HTG_LD_LIBRARY_PATHS_EXTRA_ARGS);    
  }

  if ((i=strlen(HTG_LD_EXTRA_ARGS)) > 0) {
     strcat(HTG_LD_ARGS, " ");    
     strcat(HTG_LD_ARGS, HTG_LD_EXTRA_ARGS);    
  }

#ifdef DEBUG_COMPILER_LEVEL2
  fprintf (stderr, "debug: setup_ld_paths 1: HTG_prg_uses_term=%d, HTG_LD_ARGS=%s, i=%d;\n", 
                    HTG_prg_uses_term, HTG_LD_ARGS, i); 
#endif 

  if (strlen (HTG_LD_PATHS) > 0) {
      strcpy (HTG_LD_RESOPT_ARGS, HTG_LD_PATHS);
      strcat(HTG_LD_ARGS, " ");    
  }

  strcat (HTG_LD_RESOPT_ARGS, HTG_LD_ARGS);

#ifdef DEBUG_COMPILER_LEVEL2
  fprintf (stderr, "debug: setup_ld_paths 9: HTG_LD_ARGS=%s, HTG_prg_uses_dcall=%d, HTG_prg_uses_term=%d, HTG_prg_uses_fileio=%d, i=%d;\n", 
                    HTG_LD_ARGS, HTG_prg_uses_dcall, HTG_prg_uses_term, HTG_prg_uses_fileio, i); 
#endif

}
  
void print_listing_file(void)
{ 
  if ((strlen (ofile) > 0) && (HTG_compile_level_flag == TCB_COMPILE_LEVEL_COMPILE))
     strcpy (output_filename, ofile); 
  if (HTG_verbose_verbose_flag == TRUE )  
     printf ("Output assembler file '%s'\n", output_filename);
  if ((o_src = fopen (output_filename, "w")) == NULL)
    {
      fprintf (stderr, "Output file '%s' could not be opened for writing ... aborting\n", output_filename);
      exit (12);
    }

  /* o_src = stderr; */
  if (HTG_list_flag)
    {
      if (HTG_verbose_verbose_flag == TRUE ) 
        {
          printf ("Listing file '%s'\n", list_filename);
        }
/*
      if ((o_lst = fopen (list_filename, "a")) == NULL)
        {
          fprintf (stderr, "* WARNING * Listings file %s could not be opened for writing ...\n", list_filename);
          HTG_list_flag = FALSE;
          HTG_RETURN_CODE = 4;
        }
      else 
       {
*/
         fprintf (o_lst, "\n\nError(s) listing:\n\n");
/*       } */
    }
}

int process_pp(void)
{
  int rc=0;

#ifdef DEBUG_COMPILER_LEVEL2
  fprintf (stderr, "htglobals debug 5: process_pp: HTG_verbose_flag=%d, HTG_verbose_verbose_flag=%d\n", 
                    HTG_verbose_flag, HTG_verbose_verbose_flag); 
#endif

  if (HTG_verbose_verbose_flag == TRUE)
     printf("Pre-processing '%s'\n", input_filename);

  /* Open input file */
  pp_filename = strdup (input_filename);
  pp_yyin = fopen(input_filename, "r");
  if ( pp_yyin == NULL ) {
      fprintf(stderr, "Error opening input file: %s\n", input_filename);
      rc = 3;
      return rc;
  }
  
#ifdef DEBUG_COMPILER_LEVEL2
  fprintf (stderr, "htglobals.c debug 4: working_filename=%s\n", working_filename); 
#endif

  /* Open output file */
  if (cobpp_flag_E == '0') {
     if (HTG_verbose_flag == TRUE)  
        printf ("Pre-processing '%s' into '%s'\n", input_filename, working_filename);
     if (HTG_verbose_verbose_flag == TRUE )  
        printf ("Output intermidiate file '%s'\n", working_filename);
     pp_yyout = fopen(working_filename, "w");
     if ( pp_yyout == NULL ) {
	  fprintf(stderr, "Error opening output file: %s\n", working_filename);
     	  fclose(pp_yyin);
     	  rc = 9;
	  return rc;
     }
  }
  else {
     if (strlen (ofile) > 0) {
  	strcpy (working_filename, ofile); 
        if (HTG_verbose_flag == TRUE)  
           printf ("Pre-processing '%s' into '%s'\n", input_filename, working_filename);
        if (HTG_verbose_verbose_flag == TRUE )  
           printf ("Output intermidiate file '%s'\n", working_filename);
        pp_yyout = fopen(working_filename, "w");
        if (pp_yyout == NULL) {
	     fprintf(stderr, "Error opening output file: %s\n", working_filename);
        	  fclose(pp_yyin);
        	  rc = 9;
	     return rc;
        }
     }
     else {
        pp_yyout = stdout;
     }
  }

  /* Open listing file */
  if (HTG_list_flag == TRUE) {
     o_lst = fopen(list_filename, "w");
     if ( o_lst == NULL ) {
	  fprintf(stderr, "Error opening listing file: %s\n", list_filename );
     	  fclose(pp_yyin);
     	  if (pp_yyout != stdout) {
     	     fclose(pp_yyout);
     	  }
     	  rc = 11;
	  return rc;
     }
  }

  pp_setup_scanner_state();

  rc = pp_yyparse(); 

#ifdef DEBUG_COMPILER_LEVEL2
 fprintf(stderr, "process_pp debug: pre-processor return status=%d\n", rc); 
#endif

  if ((pp_yyin != NULL) && (pp_yyin != stdin)) {
     fclose(pp_yyin);
     pp_yyin = NULL;
  }

  if ((pp_yyout != NULL) && (pp_yyout != stdout)) {
     fclose(pp_yyout);
     pp_yyout = NULL;
  }

  if (o_lst != NULL) {
     fflush(o_lst);
/*     fclose(o_lst); */
/*     o_lst = NULL; */
  }

  return rc;
} 

int process_compile(void) 
{
  int rc=0;

  if (HTG_norun_flag != 0)
      return rc; 

  if ((yyin = fopen (working_filename, "r")) == NULL)   {
     printf ("Input file '%s' not found or not readable\n", working_filename);
/*   exit (12); */
     rc = 12;
     return rc; 
  }
  
/*  print_compiler_banner(); */

  print_copybooks_path();
  
  print_listing_file();

  if (rc > 4) { 
     return rc; 
  }

  if (HTG_verbose_flag == TRUE )
     printf("Generating assembler output file '%s' from input '%s'\n", output_filename, working_filename);
  if (HTG_verbose_verbose_flag == TRUE )
     printf("Processing '%s'\n", input_filename);

  install_reserved();

  if (HTG_verbose_verbose_flag == TRUE )
     printf("Begining compile process ...\n");

/* yydebug=1; */
  rc= yyparse();
  rc = HTG_RETURN_CODE;
/* dcs(); */ /* this is to test the copy statement replacements */

  if (HTG_verbose_verbose_flag == TRUE ) {
#if 0
             printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
             printf("+                                                            +\n");
             printf("+                    COMPILER SUMMARY                        +\n");
             printf("+                                                            +\n");
             printf("+ Lines compiled        : %4d                               +\n",source_lineno);
             printf("+ Number of warnings    : %4d                               +\n",wrncnt);
             printf("+ Number of errors found: %4d                               +\n",errcnt);
             printf("+                                                            +\n");
             printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
             printf("Writing listing tables...");
#endif

     printf("Compiler summary:\n");
     printf("Lines compiled        : %4d\n",source_lineno);
     printf("Number of warnings    : %4d\n",wrncnt);
     printf("Number of errors found: %4d\n",errcnt);
     printf("Writing listing tables ... \n");
  }

/*dump_symbols();*/

#if 0
   if (HTG_verbose_verbose_flag == TRUE ) {
       printf("(done)\nUsed stack words: %d\n",stack_offset/2);
   }
#endif

  if (HTG_list_flag) {
     fflush(o_lst);
     fclose(o_lst);
     o_lst=NULL;
  }
  fflush(o_src);
  fclose(o_src);
  fclose(yyin);

  if (source_lineno < 1) {
     rc = 16;
  }

  return rc;
}


void process_select_verify(char compile_level) 
{
  char compile_level_0 = '1';
  
  if (HTG_compile_level_flag != TCB_COMPILE_LEVEL) {
    switch (HTG_compile_level_flag)  {

      case TCB_COMPILE_LEVEL_PREPROCESS:
        compile_level_0 = 'E';
        break;
      
      case TCB_COMPILE_LEVEL_COMPILE:
        compile_level_0 = 'S';
        break;
      
      case TCB_COMPILE_LEVEL_ASSEMBLE:
        compile_level_0 = 'c';
        break;

   }    
    fprintf (stderr, "%s: Multiple and/or conflicting command line options, '%c' and '%c', selected.\n", prg_name, compile_level_0, compile_level);
    exit (16);
  }
}

void output_select_verify(char output_type) 
{
  char output_type_0 = '1';
  
  if (HTG_compile_level_type_flag != TCB_COMPILE_TYPE) {
    switch (HTG_compile_level_type_flag)  {
            
      case TCB_COMPILE_TYPE_PROGRAM:
        output_type_0 = 'x';
        break;
            
       case TCB_COMPILE_TYPE_MODULE:
        output_type_0 = 'm';
        break;
      
    }    
    fprintf (stderr, "%s: Multiple and/or conflicting command line options, '%c' and '%c', selected.\n", prg_name, output_type_0, output_type);
    exit (16);
  }
}

void pass_options_ld(char *s)
{
  char *tp = NULL;
    
  strcat(HTG_LD_OPTIONS, "-W");
  strcat(HTG_LD_OPTIONS, s);
  strcat(HTG_LD_OPTIONS, " ");

  tp = strstr(s, SHLIB_SONAME_STR);
  if (tp != NULL) {
     HTG_shlib_soname_flag = TRUE;
  }
  
#ifdef DEBUG_COMPILER_LEVEL2
  fprintf (stderr, "debug: pass_options: TCB_CMDOPT_PASS_OPTIONS=%s:\n", s); 
#endif
}

int find_copybook_file(char *fname, char *lname)
{
  int r = 1, len, sw = 0;  
  char *pt, 
       tpath[PATHMAX1], 
       fname1[PATHMAX], 
       lname1[PATHMAX1];
       
  if (lname == NULL) {
     if ((*fname == CHR_SQUOTE) || (*fname == CHR_DQUOTE)) {
        sw = TCB_NAME_STATE_FLIT_LNONE;
        strcpy(fname1, fname+1);
        len = strlen(fname1);
        fname1[len - 1] = CHR_EOS;
        r = find_filename_literal(fname1, HTG_COPYDIR);

     }
     else {
        sw = TCB_NAME_STATE_FNAME_LNONE;
        strcpy(fname1, fname);
        strcpy(HTG_FNAME_SUFFIX, STR_SEARCH_SUFFIXES);
        r = find_filename_text(fname1, HTG_COPYDIR, HTG_FNAME_SUFFIX);
     }
  }
  else {
     if ((*lname == CHR_SQUOTE) || (*lname == CHR_DQUOTE)) {
        strcpy(lname1, lname+1);
        len = strlen(lname1);
        lname1[len - 1] = CHR_EOS;
        strcpy(tpath, lname1);
	len = strlen(tpath);
	if (len > 0) {
	  if (tpath[len - 1] != CHR_COLEN) {
	     strcat(tpath, STR_COLEN);
	  }
	}
        if ((*fname == CHR_SQUOTE) || (*fname == CHR_DQUOTE)) {
            sw = TCB_NAME_STATE_FLIT_LLIT;
            strcpy(fname1, fname+1);
            len = strlen(fname1);
            fname1[len - 1] = CHR_EOS;
            r = find_filename_literal(fname1, tpath);
         }
         else {
            sw = TCB_NAME_STATE_FNAME_LLIT;
            strcpy(fname1, fname);
            strcpy(HTG_FNAME_SUFFIX, STR_SEARCH_SUFFIXES);
            r = find_filename_text(fname1, tpath, HTG_FNAME_SUFFIX);
         }
     }
     else {
        if ((*fname == CHR_SQUOTE) || (*fname == CHR_DQUOTE)) {
            sw = TCB_NAME_STATE_FLIT_LNAME;
            strcpy(fname1, fname+1);
            len = strlen(fname1);
            fname1[len - 1] = CHR_EOS;
            strcpy(lname1, lname);
            pt = find_env_variable(lname1);
            if (pt != NULL) {
               strcpy(tpath, pt);
            }
            else {
               strcpy(tpath, "");
            }
	    len = strlen(tpath);
	    if (len > 0) {
	      if (tpath[len - 1] != CHR_COLEN) {
		 strcat(tpath, STR_COLEN);
	      }
	    }
            r = find_filename_literal(fname1, tpath);
         }
         else {
            sw = TCB_NAME_STATE_FNAME_LNAME;
            strcpy(fname1, fname);
            strcpy(lname1, lname);
            strcpy(HTG_FNAME_SUFFIX, STR_SEARCH_SUFFIXES);
            pt = find_env_variable(lname1);
            if (pt != NULL) {
               strcpy(tpath, pt);
            }
            else {
               strcpy(tpath, "");
            }
	    len = strlen(tpath);
	    if (len > 0) {
	      if (tpath[len - 1] != CHR_COLEN) {
		 strcat(tpath, STR_COLEN);
	      }
	    }
            r = find_filename_text(fname1, tpath, HTG_FNAME_SUFFIX);
         }
     }     
  }
  
  return r;
}

int find_filename_literal(char *fname, char *fp)
{
  int r = 1, len, sw1=0;
  char *pt1;
  struct stat sbuf;
        
  strcpy(fpath, fp);

  len = strlen(fpath);
  if (len == 0) {
     sprintf(include_full_filename, "%s", fname);
     if (stat(include_full_filename, &sbuf) == 0) {
     	 if (S_ISREG(sbuf.st_mode) && 
     	    ((S_IRUSR & sbuf.st_mode) || (S_IRGRP & sbuf.st_mode) || (S_IROTH & sbuf.st_mode))) {
     	    r = 0;
            if(HTG_verbose_flag == TRUE) {
     	       printf("found copybook name \'%s\'\n", include_full_filename);
     	    }
     	 }
         else {
            if(HTG_verbose_flag == TRUE) {
               printf("copybook file \'%s\' not readable\n", include_full_filename);
            }
         }
     }
     else {
        if(HTG_verbose_flag == TRUE) {
     	   printf("copybook file \'%s\' not found\n", include_full_filename);
     	}
     }
  }
  else {
     /* If filename is an absolute path ignore library path */
     if (*fname == CHR_SLASH) {
         if(HTG_verbose_flag == TRUE) {
            printf("warning: ignoring other search path(s) in absolute path copybook name \'%s\'\n", fname);
         }
         sprintf(include_full_filename, "%s", fname);
         if (stat(include_full_filename, &sbuf) == 0) {
             if (S_ISREG(sbuf.st_mode) && 
         	((S_IRUSR & sbuf.st_mode) || (S_IRGRP & sbuf.st_mode) || (S_IROTH & sbuf.st_mode))) {
         	r = 0;
                if(HTG_verbose_flag == TRUE) {
         	   printf("found copybook name \'%s\'\n", include_full_filename);
         	}
             }
             else {
                if(HTG_verbose_flag == TRUE) {
         	   printf("copybook file \'%s\' not readable\n", include_full_filename);
         	}
             }
         }
         else {
            if(HTG_verbose_flag == TRUE) {
               printf("copybook file \'%s\' not found\n", include_full_filename);
            }
         }
     }
     else {
         sw1 = 0;
         strcpy(fpath, fp);
         pt1 = find_token(fpath, STR_COLEN, 0);
         if (pt1 == NULL) {
            pt1 = fpath;
         }
         while (sw1 == 0) {
            sprintf(include_full_filename, "%s", pt1);
            if (stat(include_full_filename, &sbuf) == 0) {
               if (S_ISDIR(sbuf.st_mode) && 
                  ((S_IRUSR & sbuf.st_mode) || (S_IRGRP & sbuf.st_mode) || (S_IROTH & sbuf.st_mode))) {
                   if(HTG_verbose_flag == TRUE) {
            	      printf("searching directory path \'%s\'\n", include_full_filename);
                   }
                   sprintf(include_full_filename, "%s/%s", pt1, fname);
                   if (stat(include_full_filename, &sbuf) == 0) {
                       if (S_ISREG(sbuf.st_mode) && 
                   	  ((S_IRUSR & sbuf.st_mode) || (S_IRGRP & sbuf.st_mode) || (S_IROTH & sbuf.st_mode))) {
                   	  r = 0;
                          if(HTG_verbose_flag == TRUE) {
                   	     printf("found copybook name \'%s\'\n", include_full_filename);
                   	  }
                   	  sw1 = 1;
                       }
                       else {
                          if(HTG_verbose_flag == TRUE) {
                   	     printf("copybook file \'%s\' not readable\n", include_full_filename);
                   	  }
                       }
                   }
                   else {
                      if(HTG_verbose_flag == TRUE) {
             	   	 printf("copybook file \'%s\' not found\n", include_full_filename);
                      }
                   }
               }
               else {
                   if(HTG_verbose_flag == TRUE) {
            	       printf("directory path \'%s\' not readable\n", include_full_filename);
                   }
               }
            }
            else {
                 if(HTG_verbose_flag == TRUE) {
                    printf("directory path \'%s\' not found\n", include_full_filename);
                 }
            }
            pt1 = find_token(pt1, STR_COLEN, 1);
            if (pt1 == NULL) {
                sw1 = 1;
            }
         }
     }
  }

  return r;
}

int find_filename_text(char *fname, char *fp, char *fs)
{
  int r = 1, len, sw1, sw2;
  char *pt1, *pt2;
  struct stat sbuf;
        
  strcpy(fpath, fp);
  strcpy(fsuffix, fs);

  len = strlen(fpath);
  if (len == 0) {
     sw1 = 0;
     pt1 = find_token(fsuffix, STR_COLEN, 0);
     if (pt1 == NULL) {
         pt1 = fsuffix;
     }
     while (sw1 == 0) {
           sprintf(include_full_filename, "%s%s", fname, pt1);
           if (stat(include_full_filename, &sbuf) == 0) {
               if (S_ISREG(sbuf.st_mode) && 
                  ((S_IRUSR & sbuf.st_mode) || (S_IRGRP & sbuf.st_mode) || (S_IROTH & sbuf.st_mode))) {
                  r = 0;
                  if(HTG_verbose_flag == TRUE) {
                     printf("found copybook name \'%s\'\n", include_full_filename);
                  }
                  sw1 = 1;
               }
               else {
                  if(HTG_verbose_flag == TRUE) {
                     printf("copybook file \'%s\' not readable\n", include_full_filename);
                  }
               }
               sw1 = 1;
           }
           else {
              if(HTG_verbose_flag == TRUE) {
             	 printf("copybook file \'%s\' not found\n", include_full_filename);
              }
           }
           pt1 = find_token(pt1, STR_COLEN, 1);
           if (pt1 == NULL) {
               sw1 = 1;
           }
     }
  }
  else {
     sw1 = 0;
     sw2 = 0;
     strcpy(fpath, fp);
     strcpy(fsuffix, fs);
     pt1 = find_token(fpath, STR_COLEN, 0);
     if (pt1 == NULL) {
     	 pt1 = fpath;
     }
     while (sw1 == 0) {
        sprintf(include_full_filename, "%s", pt1);
        if (stat(include_full_filename, &sbuf) == 0) {
           if (S_ISDIR(sbuf.st_mode) && 
              ((S_IRUSR & sbuf.st_mode) || (S_IRGRP & sbuf.st_mode) || (S_IROTH & sbuf.st_mode))) {
               if(HTG_verbose_flag == TRUE) {
            	  printf("searching directory path \'%s\'\n", include_full_filename);
               }
               strcpy(fsuffix, fs);
               sw2 = 0;
               pt2 = find_token(fsuffix, STR_COLEN, 0);
               while (sw2 == 0) {
                     sprintf(include_full_filename, "%s/%s%s", pt1, fname, pt2);
                     if (stat(include_full_filename, &sbuf) == 0) {
                         if (S_ISREG(sbuf.st_mode) && 
                            ((S_IRUSR & sbuf.st_mode) || (S_IRGRP & sbuf.st_mode) || (S_IROTH & sbuf.st_mode))) {
                            r = 0;
                            if(HTG_verbose_flag == TRUE) {
                               printf("found copybook name \'%s\'\n", include_full_filename);
                            }
                   	    sw1 = 1;
                   	    sw2 = 1;
                         }
                         else {
                            if(HTG_verbose_flag == TRUE) {
                               printf("copybook file \'%s\' not readable\n", include_full_filename);
                            }
                         }
                         sw2 = 1;
                     }
                     else {
                        if(HTG_verbose_flag == TRUE) {
             	           printf("copybook file \'%s\' not found\n", include_full_filename);
                        }
                     }
                     pt2 = find_token(pt2, STR_COLEN, 1);
                     if (pt2 == NULL) {
                        sw2 = 1;
                     }
               }
           }
           else {
               if(HTG_verbose_flag == TRUE) {
            	  printf("directory path \'%s\' not readable\n", include_full_filename);
               }
           }
        }
        else {
             if(HTG_verbose_flag == TRUE) {
                printf("directory path \'%s\' not found\n", include_full_filename);
             }
        }
        pt1 = find_token(pt1, STR_COLEN, 1);
        if (pt1 == NULL) {
            sw1 = 1;
        }
     }
  }

  return r;
}

char *find_env_variable(char *ev)
{
  char *pt, ev1[PATHMAX]; 
  int i, len;
  
  len = strlen(ev);  
  for (i=0; i<len; i++) {
      if (*(ev+i) == CHR_DASH) {
         *(ev1+i) = CHR_UNDERSCORE;
      }
      else {
         *(ev1+i) = *(ev+i);
      }
  }
  *(ev1+len) = CHR_EOS;
  
  pt = getenv(ev1);
  if (pt != NULL) {
     if(HTG_verbose_flag == TRUE) {
  	 printf("envoromental variable \'%s\' found, setting search path(s) to \'%s\'\n", ev1, pt);
     }
     return pt;
  }
  
  if(HTG_verbose_flag == TRUE) {
      printf("warning: envoromental variable \'%s\' not found\n", ev1);
  }

  return NULL;
}

char *find_token(char *p, const char *d, int sw)
{
  int i, len;
   
  if (sw == 0) {
    len = strlen(p);
    *(p+len+1) = CHR_EOS;
    for (i=0; i<len; i++) {
        if (*(p+i) == *d) {
           *(p+i) = CHR_EOS;           
           return p;
        }
    }
    return NULL;
  }
  else {
    len = strlen(p);
    p = p + len + 1;
    if (*p != CHR_EOS) {
       len = strlen(p);
       for (i=0; i<len; i++) {
           if (*(p+i) == *d) {
              *(p+i) = CHR_EOS;               
              return p;
           }
       }
    }
    return NULL;
  }
 
}

void append_include_path(char *ap)
{
 int len1, len2, len3, rc=0;
 
 len1 = strlen(HTG_COPYDIR);
 len2 = strlen(ap);
 len3 = len1 + len2;

 if (len1 == 0)  {
    if (len2 < (PATHMAX1 + 1)) {  
       strcpy (HTG_COPYDIR, ap);
       strcat (HTG_COPYDIR, STR_COLEN);
    }
    else {
       rc = 16;
    }
 }
 else {
    if (len3 < PATHMAX1) {  
       strcat (HTG_COPYDIR, ap);
       strcat (HTG_COPYDIR, STR_COLEN);
    }
    else {
       rc = 16;
    }
 }

 if(HTG_verbose_flag == TRUE) {
    fprintf (stdout, "Appending '%s' to include (copybooks) search path\n", ap);
 }

 if (rc != 0) { 
    fprintf (stderr, "%s: *** Buffer overflow error while appending '%s' to include (copybooks) search path. Abort.\n", prg_name, ap);
    exit(rc);
 }

}
