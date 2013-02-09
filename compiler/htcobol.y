/*
 * Copyright (C) 2007-2010 Rildo Pragana, David Essex. 
 * Copyright (C) 1999-2006 Rildo Pragana,
 *               Bernard Giroud, David Essex, Jim Noeth.
 * Copyright (C) 1991,1993 Rildo Pragana.
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 * Boston, MA 02111-1307 USA 

 *
 * TinyCOBOL parser 
 *

*/

%{
#define YYDEBUG 1 
#define YYMAXDEPTH 1000 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdarg.h>
#if defined(SunOS)
va_list __builtin_va_alist;
#endif

#include <ctype.h>

#include "htcoboly.h"
#include "htcoblib.h"
#include "htglobals.h"

/* #if 1 */
#if USE_PARSER_TEST_MODE
#define UNIMPLEMENTED(xyz)
#else
#define UNIMPLEMENTED(xyz)   yyerror("`%s' is/are not currently implemented", xyz);
#endif

extern int screen_io_enable, scr_line,scr_column;
extern int decimal_comma;
extern char currency_symbol;
extern int has_linkage;
extern int module_flag;
extern int nested_flag;
extern FILE *lexin;
extern FILE *o_src;
extern struct sym *screen_status_field; /*  pointer to the screen status */
extern struct sym *cursor_field; /*  pointer to the cursor field */
extern struct sym *curr_paragr,*curr_section;
extern struct sym *curr_field;
extern short curr_call_mode;
extern short curr_call_convention;
extern struct sym *pgm_id;
extern unsigned stack_offset;   /* offset das variaveis na pilha */
extern unsigned global_offset;  /* offset das variaveis globais (DATA) */
extern int paragr_num;
extern int loc_label;
extern char picture[];
extern int picix,piccnt,decimals,sign,v_flag,n_flag,pscale;
extern int at_linkage,stack_plus;
extern char *toktext;
extern int yylex(void);
extern struct index_to_table_list *index2table;
extern int pgm_segment;
extern int initial_flag;
extern struct lit *spe_lit_ZE;
extern struct lit *spe_lit_SP;
extern struct lit *spe_lit_LV;
extern struct lit *spe_lit_HV;
extern struct lit *spe_lit_QU;

struct sym *curr_file;
struct sym *alloc_filler( void );
int curr_division=0;
int need_subscripts=0;
static int is_var=0;
struct tcb_declarative_list *declarative_list=NULL;
/* struct tcb_declaratives_lists *declaratives_lists=NULL; */
struct tcb_declaratives_list *declaratives_list=NULL;
extern char *yytext;
extern int envdiv_bypass_save_sw;

extern int stabs_on_sw;
extern int HTG_prg_uses_fileio; 
extern int HTG_prg_uses_term; 
/* extern int HTG_prg_uses_dcall; */

extern short HTG_cursesio_set; 

unsigned long lbend, lbstart;
unsigned int perform_after_sw;

int write_advancing_sw;
int decl_lbl;

/* struct math_var *vl1, *vl2; */
struct math_ose *tmose=NULL;
struct ginfo    *gic=NULL;

static void assert_numeric_sy (struct sym *sy);
static void assert_numeric_dest_sy (struct sym *sy);

static char err_msg_bad_form[] = "ill-formed %s statement";
%}
%union {
    struct sym *sval;       /* symbol */
    int ival;               /* int */
    struct coord_pair pval; /* lin,col */
    struct lit *lval;       /* literal */
    unsigned long dval;     /* label definition, compacted */
    struct ddval {	    /* dual label definition */
	int lb1,lb2;
    } ddval;
    struct strty {	    /* string and type */
      int type;
      char *str;
    } strty;
    char *str;
    struct vref *rval;      /* variable reference (with subscripts) */
    struct refmod *rmval;   /* variable with RefMod specifier */
    struct string_from *sfval; /* variable list in string statement */
    struct unstring_delimited *udval;
    struct unstring_destinations *udstval;
    struct tallying_list *tlval;
    struct tallying_for_list *tfval;
    struct replacing_list *repval;
    struct replacing_by_list *rbval;
    struct converting_struct *cvval;
    struct inspect_before_after *baval;
    struct scr_info *sival;
    struct perf_info *pfval;
    struct perform_info *pfvals;
    struct sortfile_node *snval;
    struct sort_node_container *sncval;
    struct selsubject *ssbjval;
    struct math_var *mval;           /* math variables container list */
    struct math_ose *mose;           /* math ON SIZE ERROR variables container */
    struct ginfo    *gic;            /* generic container */
    struct invalid_keys *iks;        /* [NOT] INVALID KEY */
    struct invalid_key_element *ike; /* [NOT] INVALID KEY */
    struct condition condval;
    struct list *lstval;             /* generic container list */
    struct gvar_list *glistval;      /* generic variable list */
    struct file_description_entry *fdentry;  /* file description clauses */
    struct file_description_record *fdrec;   /* file record description clause */
    struct file_open_statement_list *fopenl; /* file open statement list */
    struct tcb_declarative_exception_option *deceo; /* declarative exception option */
    struct tcb_declarative *udecl;            /* declarative - USE options */
}

/* %nonassoc LOW_PREC */

%token <str>  IDSTRING_WORD IDSTRING_LITERAL
/* %token <strty>  IDSTRING_WORD IDSTRING_LITERAL */
%token <sval> STRING VARIABLE VARCOND SUBSCVAR
%token <sval> LABELSTR CMD_LINE ENVIRONMENT_VARIABLE INKEY
%token <ival> CHAR MULTIPLIER
%token <ival> USAGENUM CONDITIONAL
%token <ival> TO IS ARE THRU THAN NO
%token <ival> DIRECTION READ WRITE INPUT_OUTPUT RELEASE
%token <lval> NLITERAL CLITERAL
%token <ival> DISK PRINTER DATE_TIME

%left   '+' '-'
%left   '*' '/'
%left   POW_OP

%left  OR
%left  AND
%right NOT

%token ACCEPT ACCESS ADD ADDRESS ADVANCING AFTER ALL ALPHABET
%token ALPHABETIC_TOK ALPHABETIC_LOWER ALPHABETIC_UPPER ALPHANUMERIC
%token ALPHANUMERIC_EDITED ALSO ALTERNATE ANY AREA AREAS ASSIGN
%token AT AUTHOR AUTO 
%token BACKGROUNDCOLOR BEFORE BELL BLANK BLINK BLOCK BOTTOM BY
%token CALL CALL_CONV_C CALL_CONV_STDCALL CALL_LOADLIB CANCEL CENTER CF CH 
%token CHAIN CHAINING CHARACTER CHARACTERS CLASS CLOSE 
%token CODE CODE_SET COLLATING COLOR COLUMN COLUMNS COMMA COMMON COMPUTE CONFIGURATION
%token CONSOLE CONTAINS CONTENT CONTINUE CONTROL CONTROLS CONVERTING
%token CORRESPONDING COUNT CURRENCY CURSOR
%token DATA DATE_COMPILED DATE_WRITTEN DE DEBUGGING DECIMAL_POINT 
%token DECLARATIVES DELETE DELIMITED DELIMITER DEPENDING DETAIL DISPLAY
%token DISPLAY_SCREEN DIVIDE DIVISION DOWN DUPLICATES DYNAMIC
%token ELSE END END_ACCEPT END_ADD END_CALL END_CALL_LOADLIB END_CHAIN END_COMPUTE END_DELETE
%token END_DISPLAY END_DIVIDE END_EVALUATE END_IF END_MULTIPLY END_OF_PAGE
%token END_PERFORM END_READ END_RETURN END_REWRITE END_SEARCH END_START
%token END_STRINGCMD END_SUBTRACT END_UNSTRING END_WRITE ENVIRONMENT
%token EOL EOS ERASE ERROR_TOK EVALUATE EXCEPTION EXIT EXTEND
%token EXTERNAL
%token FALSE_TOK FD FILE_CONTROL FILE_ID FILE_TOK FILLER FINAL FIRST
%token FOOTING FOR FOREGROUNDCOLOR FROM FULL FUNCTION
%token GENERATE GIVING GLOBAL GO GOBACK GROUP
%token HEADING HIGHLIGHT HIGHVALUES
%token IDENTIFICATION IF IGNORE IN INDEXED INDICATE INITIALIZE INITIAL_TOK
%token INITIATE INPUT INSPECT INSTALLATION INTO INVALID I_O I_O_CONTROL
%token JUSTIFIED
%token KEY
%token LABEL LAST LEADING LEFT LENGTH LIMIT LIMITS LINAGE LINE LINES LINKAGE LISTSEP
%token LOCK LOWER LOWLIGHT LOWVALUES LPAR
%token MERGE MINUS MODE MOVE MULTIPLE MULTIPLY
%token NATIVE NEGATIVE NEXT NOECHO NOT NOTEXCEP NULL_TOK NUMBER NUMBERS
%token NUMERIC NUMERIC_EDITED
%token OBJECT_COMPUTER OCCURS OF OFF OMITTED ON ONLY OPEN OPTIONAL ORDER
%token ORGANIZATION OTHER OUTPUT OVERFLOW_TOK
%token PADDING PAGE_TOK PAGE_COUNTER PARAGRAPH PERFORM PF PH PICTURE PLUS POINTER POSITION
%token POSITIVE PREVIOUS PROCEDURE PROCEDURES PROCEED PROGRAM PROGRAM_ID
%token QUOTES
%token RANDOM RD READY RECORD RECORDS REDEFINES REEL REFERENCE REFERENCES RELATIVE
%token REMAINDER REMOVAL RENAMES REPLACING REPORT REPORTING REPORTS REQUIRED RESERVE RESET
%token RETURN_TOK RETURNING REVERSEVIDEO REWIND REWRITE RF RH RIGHT ROUNDED RUN
%token SAME SCREEN SD SEARCH SECTION SECURE SECURITY SELECT SENTENCE SEPARATE
%token SEQUENCE SEQUENTIAL SET SIGN SIZE SORT SORT_MERGE SOURCE SOURCE_COMPUTER
%token SPACES SPECIAL_NAMES STANDARD STANDARD_1 STANDARD_2 START STATUS
%token STD_ERROR STD_INPUT STD_OUTPUT STOP STRINGCMD SUBTRACT SUM SYNCHRONIZED
%token TALLYING TAPE TCOBPROTO1 TCOBPROTO2 TERMINATE TEST THEN TIMES TOKDUMMY
%token TOP TRACE TRAILING TRUE_TOK TYPE
%token UNDERLINE UNIT UNLOCK UNSTRING UNTIL UP UPDATE UPON UPPER USAGE USE USING
%token VALUE VALUES VARYING
%token WHEN WITH WORKING_STORAGE
%token ZERO

%right OF
%nonassoc PERIOD_TOK

%type <ival> sync_options /* use_exception_error */ use_global_opt
%type <ival> organization_options access_options open_mode
%type <ival> integer cond_op conditional before_after
%type <ival> IF ELSE usage read_next_opt
%type <ival> multiplier_opt using_options 
%type <ival> procedure_division_using_chaining_opt
%type <dval> if_part
%type <sval> anystring name name_var gname gname_opt def_name_opt def_name procedure_section
%type <sval> field_description label filename data_name noallname paragraph 
%type <sval> assign_clause assign_clause_standard_files
%type <lval> literal gliteral without_all_literal all_literal special_literal
%type <lval> nliteral
%type <sval> perform_thru_opt write_options procedure_division_returning_opt
%type <sval> read_into_opt write_from_opt release_from_opt
%type <sval> variable perform_options name_or_lit delimited_by
%type <sval> string_with_pointer strings
%type <sval> switches_details accept_hardware_env_var
%type <ival> all_opt with_duplicates with_test_opt optional_opt
%type <rval> subscript subscripts
%type <sfval> string_from_list string_from
%type <sval> unstring_count_opt unstring_delim_opt unstring_tallying
%type <udval> unstring_delimited_vars unstring_delimited
%type <udstval> unstring_destinations unstring_dest_var
%type <baval> inspect_before_after
%type <tlval> tallying_list  tallying_clause
%type <tfval> tallying_for_list
%type <ival> replacing_kind plus_minus_opt
%type <repval> replacing_list  replacing_clause
%type <rbval> replacing_by_list
%type <cvval> converting_clause
%type <sval> var_or_nliteral read_key_opt
%type <sival> screen_clauses
%type <ival> /*screen_attribs */screen_attrib sign_clause separate_opt
%type <ival> report_clause_column_is report_clause_column_orientation
%type <sval> variable_indexed search_varying_opt key_is_opt
%type <dval> search search_all search_when search_when_list search_at_end
%type <ival> parm_type sign_condition class_condition
%type <sval> intrinsic_parm_list intrinsic_parm
%type <sval> parm_list parameter expr expr_opt
%type <sval> cond_name thru_gname_opt
%type <pfval> perform_after
%type <pfvals> perform_after_opt
%type <ival> ext_cond extended_cond_op
%type <sval> returning_options
%type <snval> sort_file_list perform_range
%type <sncval> sort_input sort_output merge_using
%type <ival> not_opt selection_subject selection_object when_case
%type <ssbjval> selection_subject_set
%type <sval> screen_to_name 
%type <lval> signed_nliteral
%type <ival> sentence_or_nothing when_case_list
%type <ival> rounded_opt
%type <mval> var_list_name  var_list_gname
%type <mose> on_size_error_opt on_size_error
%type <ival> address_of_opt display_upon display_line_options
%type <sval> set_variable set_variable_or_nlit set_target add_to_opt
%type <sval> name_list string_list
%type <condval> condition implied_op_condition
%type <sval> qualified_var unqualified_var
/*%type <ival> end_program_opt program_sequence nested_program*/
%type <ival> program_sequences program_sequence
%type <lval> from_rec_varying_opt to_rec_varying_opt
%type <sval> depend_rec_varying_opt
%type <sval> file_description redefines_var
%type <ival> on_exception_or_overflow on_not_exception
%type <gic>  on_end read_at_end_opt
%type <iks>  read_invalid_key_opt
%type <ike>  read_invalid_key  read_not_invalid_key
%type <iks>  invalid_key_opt
%type <ike>  invalid_key_sentence not_invalid_key_sentence
%type <sval> start_body
%type <ival> accept_display_options accept_display_option accept_options
%type <ival> with_lock_opt close_options_opt 
%type <lstval> goto_label_list goto_label
%type <glistval> gname_list name_var_list  
%type <glistval> sort_keys sort_key sort_keys_names
%type <strty> programid_string
%type <fdentry> file_description_fd_clause file_description_fd_clauses
%type <fdentry> file_description_sd_clause file_description_sd_clauses
%type <fdrec> file_description_clause_record
%type <fopenl> open_varlist open_options
%type <deceo> use_exception_option use_exception_option_names
%type <udecl> use_statements use_exception use_reporting use_debugging

%%

/************   Parser for Cobol Source  **************/
/*
   COMPILATION UNIT STRUCTURE
*/
root_: program_sequences { gen_main_rtn(); }
        ;
program_sequences:
        program { pgm_segment++; $$=1; }
        | program_sequence { $$=1 ; }
        | program_sequence program { $$=1 ; }
/*
          program_sequence program_sequence end_program_opt
                           { pgm_segment++; if (!($1|$3)) yyerror("END PROGRAM expected"); $$=$3; }
        | program_sequence program_sequence
                           { pgm_segment++; if ($1) yyerror("too many END PROGRAM"); $$=1; }
*/
        ;
program_sequence:
        program end_program { pgm_segment++ ; $$ = 1; }
        | program { pgm_segment++ ; nested_flag = 1; } program_sequence end_program { $$ = 1; }
        | program_sequence program end_program {pgm_segment++ ; nested_flag = 1; $$ = 1; }
/*
        | program_sequence program { yyerror("aaaaaaa");  $$ = 1; }
        | program program_sequence { yyerror("aaaaaaaaaa") ; $$ = 1; }
*/
        ;
/*end_program_opt:
        * nothing * { $$=0; }
        | end_program { $$=1; }
        ;*/
end_program:
        END PROGRAM
        { 
         clear_symtab(); 
         clear_offsets();
/*
         screen_io_enable = 0; 
         HTG_prg_uses_term = 0; 

         if (HTG_cursesio_set == 1) {
            screen_io_enable=1;
            HTG_prg_uses_term = 1;
         }
         else {
            screen_io_enable=0;
         }
*/
         curr_division= CDIV_IDENT; 
        }
         programid_string
        { curr_division = CDIV_COMMENT; }
        ;
/*
 * MAIN PROGRAM STRUCTURE
 */
program:
         identification_division
         environment_division_opt
         data_division_opt
         procedure_division_opt
        ;
/*
 * IDENTIFICATION DIVISION
 */
identification_division: IDENTIFICATION DIVISION PERIOD_TOK
    PROGRAM_ID PERIOD_TOK
    {
     curr_division = CDIV_IDENT;
    }
    programid_string
    {
     curr_division = CINITIAL;
     if (pgm_header($7.str, $7.type) != 0) {
        yyerror("Invalid PROGRAM-ID name");
        /* YYABORT; */
     }
/*
     if(HTG_cursesio_set == 1) {
       screen_io_enable++;
       curr_field=NULL;
       HTG_prg_uses_term = 1;
     } 
     else {
       screen_io_enable = 0;
     }
*/
    }
    programid_opts_opt PERIOD_TOK
    {
     define_special_fields();
    }
    identification_division_options_opt
    ;
programid_string:
    IDSTRING_WORD 
    { 
     $$.str=$1;  
     $$.type=1;
    }
    | IDSTRING_LITERAL 
    {
     $$.str=$1;  
     $$.type=2;
    } 
    ;
programid_opts_opt:
    /*nothing */
    | is_opt INITIAL_TOK programid_program_opt { initial_flag=1; }
    | is_opt COMMON programid_program_opt { UNIMPLEMENTED("PROGRAM-ID ... COMMON clause") }
    ;
programid_program_opt:
    | PROGRAM {  }
    ;
identification_division_options_opt:
    /*nothing */
    | identification_division_options_opt identification_division_option
    ;
identification_division_option:
    AUTHOR PERIOD_TOK          { curr_division = CDIV_COMMENT1; }
    | DATE_WRITTEN PERIOD_TOK  { curr_division = CDIV_COMMENT1; }
    | DATE_COMPILED PERIOD_TOK { curr_division = CDIV_COMMENT1; }
    | INSTALLATION PERIOD_TOK  { curr_division = CDIV_COMMENT1; }
    | SECURITY PERIOD_TOK      { curr_division = CDIV_COMMENT1; }
    ;
/*
 * ENVIRONMENT DIVISION
 */
environment_division_opt:
    ENVIRONMENT DIVISION PERIOD_TOK
    {
     curr_division = CDIV_ENVIR;
    }
    configuration_opt
    input_output_opt
    {
     curr_division = CINITIAL;
    }
    | /*nothing */
    ;
/*
 * CONFIGURATION SECTION
 */
configuration_opt:
    CONFIGURATION SECTION PERIOD_TOK configuration_section
    | /*nothing */
    ;
configuration_section:
    configuration_section configuration_option  { }
    | /* nothing */                 { }
    ;
configuration_option:
    SOURCE_COMPUTER PERIOD_TOK
      { envdiv_bypass_save_sw=1; }
      STRING debug_mode_opt PERIOD_TOK
      { envdiv_bypass_save_sw=0; }
    | OBJECT_COMPUTER PERIOD_TOK
      { envdiv_bypass_save_sw=1; }
      STRING program_collating_opt PERIOD_TOK
      { envdiv_bypass_save_sw=0; }
    | SPECIAL_NAMES PERIOD_TOK special_names_opt
    | error { yyerror("invalid format in CONFIGURATION SECTION"); }
    ;
program_collating_opt:
    PROGRAM collating_sequence
    | /* nothing */
    ;
collating_sequence:
    collating_opt SEQUENCE is_opt STRING
    ;
collating_opt: COLLATING  { }
    | /* nothing */   { }
    ;
debug_mode_opt:
    with_opt DEBUGGING MODE { stabs_on_sw = 1; }
    | /* nothing */   { }
    ;
special_names_opt:
    /* nothing */
    | special_names PERIOD_TOK
    | error { yyerror("invalid format in SPECIAL-NAMES clause");}
    ;
special_names:
    special_name
    | special_names special_name
    ;
special_name:
    /*special_name_opt*/
    /*symbolic_characters_opt*/
    switches_details_list
    | alphabet_details /* parsed but unimplemented */
    | currency_details
    | decimal_point_details
    | screen_status_details
    | cursor_details
    | special_name_class
/*    | error { yyerror("invalid format in SPECIAL-NAMES clause");} */
/*    | DATA DIVISION { yyerror("missing period in SPECIAL-NAMES clause");} */
    ;
currency_details:
    CURRENCY sign_opt is_opt CLITERAL {
                currency_symbol = $<lval>4->name[0];
                }
    ;
sign_opt:
    SIGN
    | /* nothing */
    ;
special_name_class:
    CLASS STRING is_opt special_name_class_item_list {}
    ;
special_name_class_item_list:
    special_name_class_item {}
    | special_name_class_item_list special_name_class_item {}
    ;
special_name_class_item:
    CLITERAL {}
    | CLITERAL THRU CLITERAL {}
    ;

decimal_point_details:
    DECIMAL_POINT is_opt COMMA {
                decimal_comma=1; }
    ;
screen_status_details:
    DISPLAY_SCREEN STATUS is_opt STRING 
    { screen_status_field=$4; }
    ;
cursor_details:
    CURSOR is_opt STRING 
    { cursor_field=$3; }
    ;
switches_details_list:
    | switches_details_list switches_details
    ;
switches_details:
    STRING is_opt STRING
    {if ($1->name[0] != 'S' || $1->name[1] != 'W')
       yyerror("Invalid switch name");
    define_switch_field($3, $1);}
        switch_on_opt switch_off_opt
    { close_fields();}
    ;
switch_on_opt:
    ON status_opt is_opt STRING {save_switch_value($4, 1);}
    | /* nothing */
    ;
switch_off_opt:
    OFF status_opt is_opt STRING {save_switch_value($4, 0);}
    | /* nothing */
    ;
status_opt:
    STATUS
    | /* nothing */
    ;
alphabet_details:
    ALPHABET STRING is_opt alphabet_type 
    { 
     $2->defined=1;
     UNIMPLEMENTED("Alphabet clause")
    }
    ;
alphabet_type:
    NATIVE { }
    | STANDARD_1 { }
    | STANDARD_2 { }
    | alphabet_literal_list { }
    ;
alphabet_literal_list:
    alphabet_literal_item
    | alphabet_literal_list alphabet_literal_item
    ;
alphabet_literal_item:
    without_all_literal { }
    | without_all_literal THRU without_all_literal { }
    | without_all_literal alphabet_also_list { }
    ;
alphabet_also_list:
    ALSO without_all_literal
    | alphabet_also_list ALSO without_all_literal
    ;
/*
 * INPUT OUTPUT SECTION
 */
input_output_opt:
    INPUT_OUTPUT SECTION PERIOD_TOK input_output_section { }
    | /*nothing */
    ;
input_output_section:
    file_control_paragraph i_o_control_paragraph { }
    | /*nothing */
    /* | error { yyerror("INPUT-OUTPUT SECTION format wrong"); } */
    ;
file_control_paragraph:
    FILE_CONTROL PERIOD_TOK file_control { }
    ;
i_o_control_paragraph: /* nothing */ 
    | I_O_CONTROL PERIOD_TOK i_o_control_opt { }
    ;

/*
 * FILE CONTROL ENTRY
 */
file_control:
    file_select
    | file_control file_select
    | /*nothing */
    ;

file_select:
    SELECT optional_opt def_name 
    {
     curr_file=file_select_clause_init($3, $2); 
    }
    select_clauses PERIOD_TOK 
    {
     if (file_select_clause_verify(curr_file) != 0) 
        YYABORT;
    }
    ;
select_clauses:
    select_clauses select_clause
    | /* nothing */
    ;
select_clause:
    organization_opt is_opt organization_options
                { curr_file->uval1.organization=$3; }
    | ASSIGN to_opt assign_clause { curr_file->uval7.filenamevar=$3; }
    | ACCESS mode_opt is_opt access_options { curr_file->uval3.access_mode=$4; }
    | file_opt STATUS is_opt strings  { curr_file->parent=$4; }
    | RECORD key_opt is_opt strings   { curr_file->ix_desc=$4; }
    | RELATIVE key_opt is_opt strings { curr_file->ix_desc=$4; }
    | ALTERNATE RECORD key_opt is_opt strings
        with_duplicates { add_alternate_key($5,$6); }
    | RESERVE NLITERAL areas_opt
    | error { yyerror("invalid clause in select"); }
    ;
strings:
    STRING { $$=$1; }
    | STRING in_of strings
    {
     $3->parent=$1; $$=$3;
     /* fprintf(stderr, "parent=%s, child=%s;\n", $3->name, $1->name);  */
    }
    ;
file_opt:
    FILE_TOK
    | /* nothing */
    ;
organization_opt:
    ORGANIZATION { }
    | /* nothing */
    ;
assign_clause: assign_clause_standard_files { $$=$1; }
    | assign_clause_external_opt assign_clause_device filename { $$=$3; }
    | assign_clause_external_opt filename { $$=$2; }
    | assign_clause_external_opt assign_clause_device { $$=NULL; }
    ;
    
assign_clause_external_opt: 
    EXTERNAL { curr_file->flags.file_external = 1; }
    | /* nothing */ 
    ;

assign_clause_device: 
    DISK { }
    | PRINTER { curr_file->flags.file_printer = 1; }
    ;

assign_clause_standard_files:
    STD_INPUT  { curr_file->flags.file_stdin  = 1; $$=define_std_filename(0); }
    | STD_OUTPUT { curr_file->flags.file_stdout = 1; $$=define_std_filename(1); }
    | STD_ERROR  { curr_file->flags.file_stderr = 1; $$=define_std_filename(2); }
    | DISPLAY    { curr_file->flags.file_stdout = 1; $$=define_std_filename(0); }
    ;

with_duplicates:
    with_opt DUPLICATES { $$=1; }
    | /* nothing */     { $$=0; }
    ;
optional_opt:
    OPTIONAL            { $$=1; }
    | /* nothing */     { $$=0; }
    ;
areas_opt: AREA 
    | AREAS 
    | /* nothing */
    ;
is_opt:
    IS { }
    | /* nothing */
    ;
are_opt:
    ARE { }
    | /* nothing */
    ;
mode_opt:
    MODE
    | /* nothing */
    ;
organization_options:
    INDEXED      { $$=1; }
    | SEQUENTIAL { $$=2; }
    | RELATIVE   { $$=3; }
    | LINE SEQUENTIAL { $$=4; }
    | anystring { yyerror("invalid option, %s",$1->name); }
    ;
access_options:
    SEQUENTIAL  { $$=1; }
    | DYNAMIC   { $$=2; }
    | RANDOM    { $$=3; }
    | anystring 
     { yyerror("invalid access option, %s", $1->name); }
    ;

/* I-O CONTROL paragraph */
i_o_control_opt: /* nothing */
    | i_o_control_list PERIOD_TOK { UNIMPLEMENTED("I-O-CONTROL paragraph") }

    ;
i_o_control_list:
    i_o_control_clause
    | i_o_control_list i_o_control_clause
    ;
i_o_control_clause:
     i_o_control_same_clause
    | i_o_control_multiple_file_tape_clause
    ;
i_o_control_same_clause:
    SAME same_clause_options are_opta for_opt string_list 
    ;
same_clause_options: /* nothing */
    | RECORD     {  }
    | SORT       {  }
    | SORT_MERGE {  }
    ;
i_o_control_multiple_file_tape_clause:
    MULTIPLE FILE_TOK tape_opt contains_opt i_o_control_multiple_file_list
    ;
i_o_control_multiple_file_list:
    i_o_control_multiple_file
    | i_o_control_multiple_file_list i_o_control_multiple_file
    ;
i_o_control_multiple_file:
    STRING i_o_control_multiple_file_position_opt { }
    ;
i_o_control_multiple_file_position_opt:
    | POSITION integer { }
    ;
tape_opt: 
    TAPE
    | /* nothing */
    ;
are_opta: 
    AREA 
    | /* nothing */
    ;
for_opt: 
    FOR 
    | /* nothing */
    ;
string_list:
    STRING { $$ = $1; }
    | string_list STRING { $$ = $2; }
    | error { yyerror("string expected"); }
    ;
name_list:
    variable { $$ = (struct sym *)chain_var($1); }
    | name_list variable { $$ = (struct sym *)chain_var($2); }
    | error { yyerror("variable expected"); }
    ;
/* end enviroment division */

/*
 * DATA DIVISION
 */
data_division_opt: 
    DATA DIVISION PERIOD_TOK 
    { curr_division = CDIV_DATA; }
    file_section_opt
    working_storage_opt
    linkage_section_opt
    report_section_opt
    screen_section_opt       
    { curr_division = CINITIAL; }
    | /* nothing */
;
/*
 *  FILE SECTION
 */
file_section_opt:
    FILE_TOK SECTION PERIOD_TOK  { curr_field=NULL; }
    file_section   { close_fields();  }
    | /* nothing */
    ;
/*
 *  WORKING STORAGE SECTION
 */
working_storage_opt:
    WORKING_STORAGE SECTION PERIOD_TOK { curr_field=NULL; }
    working_storage_section { close_fields(); }
    | /* nothing */
    ;
/*
 * LINKAGE SECTION
 */
linkage_section_opt:
    LINKAGE SECTION PERIOD_TOK { at_linkage=1; curr_field=NULL; has_linkage++; }
    linkage_section            { close_fields(); at_linkage=0; }
    | /* nothing */
    ;

/*
 * COMMUNICATION SECTION
 */

/* Not Implemented */

/*
 * REPORT SECTION
 */
/* Work in progress - not finished */
report_section_opt:
    REPORT SECTION PERIOD_TOK
    report_sections {  }
    | /* nothing */
    ;
report_sections: 
    report_sections report_section 
    | /* nothing */
    ;
report_section:
    RD 
    { /*curr_division = CDIV_FD;*/ }
    STRING 
    { 
     $3->type='W'; 
     $3->uval9.picstr = 0;
     $3->parent = 0;
     $3->clone  = 0;
     $3->times  = -1;
     curr_division = CDIV_PROC;
     UNIMPLEMENTED("Report Section")
    }
    report_controls PERIOD_TOK
    { 
     curr_division = CDIV_DATA; 
    }
    report_description
    {
     /* update_report_field($4); */   
     /* define_field(1,$4); */ 
    } 
    ;
report_controls:   /* nothing  */ 
    | report_controls report_control
    ;
report_control:  is_opt GLOBAL { } 
    | CODE gliteral { } 
    | report_controls_control { } 
    | report_controls_page { }
    ;
report_controls_control:
    control_is_are final_opt report_break_list
    ;
report_controls_page:
    PAGE_TOK limit_is_are_opt integer line_lines_opt
      heading_opt
      first_detail_opt last_detail_opt
      footing_opt
    ;
heading_opt:   /* nothing */ 
    | HEADING is_opt integer
    ;
line_lines_opt:
    lines_opt
    | LINE
    ;
lines_opt:
    /* nothing */
    | LINES
    ;
control_is_are:
    CONTROL is_opt
    | CONTROLS are_opt
    ;
limit_is_are_opt:
    /* nothing */
    | LIMIT IS
    | LIMITS ARE
    ;
footing_opt:
    /* nothing */
    | FOOTING is_opt integer
    ;
last_detail_opt:
    /* nothing */
    | LAST DETAIL is_opt integer
    ;
first_detail_opt:
    /* nothing */
    | FIRST DETAIL is_opt integer
    ;
final_opt:
    /* nothing */
    | FINAL
    ;
report_break_list:
    /* nothing */
    | report_break_list name { $2->defined=1; }
    ;
report_description:
    report_item
    | report_description report_item
    ;
report_item:
    integer def_name_opt 
    {
     if ($2 == NULL) {
            $2 = alloc_filler();
            picix=piccnt=v_flag=n_flag=decimals=pscale=0;
            picture[picix]=0;
     }
     define_field($1,$2); 
     curr_division = CDIV_DATA; 
    }
    report_clauses PERIOD_TOK
    { 
     update_report_field($2); 
     curr_division = CDIV_DATA; 
    }
    ;
report_clauses:
     report_clause 
    | report_clauses report_clause
    ;
report_clause:
    report_clause_line {  }
    | report_clause_next_group {  }
    | report_clause_type {  }
    | report_clause_usage_display {  }
    | report_clause_picture {  }
    | report_clause_sign_is {  }
    | report_clause_justified {  }
    | report_clause_blank_zero {  }
    | report_clause_column {  }
    | report_clause_svs {  }
    | report_clause_group_indicate {  }
    ;
report_clause_type:
    TYPE is_opt report_clause_type2 {  }
    ;
report_clause_type2:
    REPORT HEADING {  }
    | PAGE_TOK HEADING {  }
    | CONTROL HEADING { curr_division = CDIV_PROC;  } 
      name_final_opt  { curr_division = CDIV_DATA;  }
    | DETAIL { }
    | CONTROL FOOTING { curr_division = CDIV_PROC;  } 
      name_final_opt { curr_division = CDIV_DATA;  }
    | PAGE_TOK FOOTING {  }
    | REPORT FOOTING {  }
    | RH {  }
    | PH {  }
    | CH { curr_division = CDIV_PROC;  }  
      name_final_opt { curr_division = CDIV_DATA;  }
    | DE {  }
    | CF { curr_division = CDIV_PROC;  }  
      name_final_opt { curr_division = CDIV_DATA;  }
    | PF {  }
    | RF {  }
    ;
report_clause_sign_is:
    SIGN is_opt leading_trailing SEPARATE character_opt {  }
    | leading_trailing SEPARATE character_opt {  }
    ;
report_clause_picture:
    PICTURE 
    {
     curr_division = CDIV_PIC;
    }
    is_opt picture { curr_division = CDIV_DATA;  }
    ;
report_clause_usage_display:
    USAGE is_opt DISPLAY {  }
    | DISPLAY {  }
    ;
report_clause_justified:
    JUSTIFIED right_opt
    ;
report_clause_next_group:
    NEXT GROUP is_opt integer_on_next_page
    ;
report_clause_line:
    report_clause_line_is integer ON NEXT PAGE_TOK {  }
    | report_clause_line_is integer NEXT PAGE_TOK {  }
    | report_clause_line_is integer {  }
    | report_clause_line_is PLUS integer {  }
    ;
report_clause_line_is:
    LINE is_are_opt
    | LINE NUMBER is_opt
    | LINE NUMBERS are_opt
    | LINES are_opt
    ;
report_clause_column: 
    report_clause_column_is integer {  }
    ;
report_clause_column_is:
    COLUMN report_clause_column_orientation is_are_opt        { $$=$2; }
    | COLUMN NUMBER report_clause_column_orientation is_opt   { $$=$3; }
    | COLUMN NUMBERS report_clause_column_orientation are_opt { $$=$3; }
    | COLUMNS report_clause_column_orientation are_opt        { $$=$2; }
    ;
report_clause_column_orientation:
    /* nothing */ { $$=0; }
    | LEFT   { $$=0; }
    | CENTER { $$=1; }
    | RIGHT  { $$=2; }
    ;
is_are_opt:
    /* nothing */
    | IS { }
    | ARE { }
    ;
report_clause_svs: SOURCE 
      { curr_division = CDIV_PROC; }
      is_opt gname_page_counter 
      { curr_division = CDIV_DATA;  }
    | VALUE is_opt literal {  }
    | SUM { curr_division = CDIV_PROC;  }
      gname_list { curr_division = CDIV_DATA;  }
      upon_opt reset_opt { }
    ;
gname_page_counter: gname {  }
    | PAGE_COUNTER {  }
    ;
report_clause_group_indicate:
    | GROUP indicate_opt {  }
    ;
report_clause_blank_zero:
    BLANK when_opt ZERO {  }
    ;
indicate_opt:
    | INDICATE {  }
    ;
upon_opt:
    | UPON gname_list {  }
    ;
reset_opt:
    | RESET gname {  }
    | RESET FINAL {  }
    ;
number_opt:
    | NUMBER { }
    ;
leading_trailing:
    LEADING    { }
    | TRAILING { }
    ;
right_opt:
    | RIGHT { }
    ;
name_final_opt:
    gname { }
    | FINAL { }
    ;
integer_on_next_page:
    integer         { }
    | PLUS integer  { }
    | NEXT PAGE_TOK { }
    ;             
of_opt:
    OF
    | /* nothing */
    ;
/* end report section */

/*
 *  SCREEN SECTION
 */

screen_section_opt:
    SCREEN SECTION PERIOD_TOK  
    {
      screen_io_enable++;
      curr_field=NULL;
      HTG_prg_uses_term = 1;
    }
    screen_section  { close_fields(); }
    | 
    /* nothing
    {
      // This aproach does not work properly 
      if (HTG_cursesio_set == TRUE) {
        //screen_io_enable++;
        //curr_field=NULL;
        HTG_prg_uses_term = 1;
      }
    }
    */
    ;

/*
 *  SCREEN SECTION DESCRIPTION ENTRY
 */
screen_section:
    screen_section screen_item
    | /* nothing */
    ;
screen_item:
    integer def_name_opt    
    {
      if ($2 == NULL) {
         $2 = alloc_filler();
      }
      picix=piccnt=v_flag=n_flag=decimals=pscale=0;
      picture[picix]=0;
      define_field($1,$2);
    }
    screen_clauses PERIOD_TOK  { update_screen_field($2,$4); }
    ;
screen_clauses:
    screen_clauses LINE         { curr_division = CDIV_PROC; } 
        number_is_opt
        plus_minus_opt
        name_or_lit             { curr_division = CDIV_DATA; 
                                  scr_set_line($1,$6,$5); $$=$1; } 
    | screen_clauses COLUMN     { curr_division = CDIV_PROC; }
        number_is_opt
        plus_minus_opt
        name_or_lit             { curr_division = CDIV_DATA; 
                                  scr_set_column($1,$6,$5); $$=$1; }
    | screen_clauses
        with_opt screen_attrib          { $1->attr |= $3; $$=$1; }
    | screen_clauses with_opt FOREGROUNDCOLOR    { curr_division = CDIV_PROC; }
        name_or_lit                     { curr_division = CDIV_DATA; 
                                          $1->color = NULL;
                                          $1->foreground = $5; $$=$1; }
    | screen_clauses with_opt BACKGROUNDCOLOR    { curr_division = CDIV_PROC; }
        name_or_lit                     { curr_division = CDIV_DATA; 
                                          $1->color = NULL;
                                          $1->background = $5; $$=$1; }
    | screen_clauses with_opt COLOR              { curr_division = CDIV_PROC; }
        name_or_lit                     { curr_division = CDIV_DATA; 
                                          $1->foreground = NULL;  
                                          $1->background = NULL; 
                                          $1->color = $5; $$=$1; }
    | screen_clauses
        screen_source_destination
    | screen_clauses
        value_is_are gliteral { curr_field->value = $3; $$=$1; }
    | screen_clauses pictures
    | screen_clauses SIZE     { curr_division = CDIV_PROC; }
                name_or_lit   { curr_division = CDIV_DATA; 
                                $1->size = $4; $$=$1; }
    | /* nothing */         { $$ = alloc_scr_info(); }
    ;
screen_source_destination:
    USING                    { curr_division = CDIV_PROC; }
                name_or_lit     {
                        curr_division = CDIV_DATA;
                        $<sival>0->from = $<sival>0->to = $3;
                }
    | FROM                    { curr_division = CDIV_PROC; }
                name_or_lit
                screen_to_name  {
                        curr_division = CDIV_DATA;
                        $<sival>0->from = $3; $<sival>0->to = $4;
                }
    | TO { curr_division = CDIV_PROC; }
                name {
                        curr_division = CDIV_DATA;
                        $<sival>0->from = NULL; $<sival>0->to = $3;
                }            
    ;
screen_to_name:
    /* nothing */ { $$=NULL; }
    | TO name { $$ = $2; }
    ;
screen_attrib:
    BLANK SCREEN                    { $$ = SCR_BLANK_SCREEN; }
    | BLANK LINE                    { $$ = SCR_BLANK_LINE; }
    | ERASE EOL                     { $$ = SCR_ERASE_EOL; }
    | ERASE EOS                     { $$ = SCR_ERASE_EOS; }
    | ERASE                            { $$ = SCR_ERASE_EOL; }
    | with_opt BELL                    { $$ = SCR_BELL; }
    | sign_clause                    { $$ = $1; }
    | FULL                            { $$ = SCR_FULL; }
    | REQUIRED                      { $$ = SCR_REQUIRED; }
    | SECURE                            { $$ = SCR_SECURE; }
    | AUTO                            { $$ = SCR_AUTO; }
    | JUSTIFIED RIGHT                    { $$ = SCR_JUST_RIGHT; }
    | JUSTIFIED LEFT                    { $$ = SCR_JUST_LEFT; }
    | BLINK                            { $$ = SCR_BLINK; }
    | REVERSEVIDEO                    { $$ = SCR_REVERSE_VIDEO; }
    | UNDERLINE                     { $$ = SCR_UNDERLINE; }
    | LOWLIGHT                      { $$ = SCR_LOWLIGHT; }
    | HIGHLIGHT                     { $$ = SCR_HIGHLIGHT; }
    | BLANK when_opt ZERO            { $$ = SCR_BLANK_WHEN_ZERO; }
    | with_opt NOECHO                    { $$ = SCR_NOECHO; }
    | with_opt UPDATE                    { $$ = SCR_UPDATE; }
    | with_opt NO ADVANCING            { $$ = SCR_NO_ADVANCING; }
    | UPPER                            { $$ = SCR_UPPER; }
    | LOWER                            { $$ = SCR_LOWER; }
    ;
sign_clause:
    sign_is_opt LEADING separate_opt
            { $$ = SCR_SIGN_LEADING | $3; }
    | sign_is_opt TRAILING separate_opt
            { $$ = $3; }
    ;
separate_opt:
    SEPARATE character_opt  { $$ = SCR_SIGN_SEPARATE; }
    | /* nothing */         { $$ = 0; }
    ;
character_opt:
    CHARACTER
    | /* nothing */
    ;
sign_is_opt:
    SIGN is_opt
    | is_opt
    ;
plus_minus_opt:
    PLUS            { $$ = 1; }
    | '+'           { $$ = 1; }
    | MINUS         { $$ = -1; }
    | '-'           { $$ = -1; }
    | /* nothing */ { $$ = 0; }
    ;
number_is_opt:
    NUMBER is_opt
    | /* nothing */
    ;
/* end screen section */

/*
 * File description entry
*/
file_section:
    file_section FD 
     { curr_division = CDIV_FD; }
     STRING 
     { curr_division = CDIV_DATA; }
     file_description_fd_clauses PERIOD_TOK
     {
      curr_field=NULL;
      if ($4->uval7.filenamevar == NULL) {
         yyerror("External file name not defined for file %s", $4->name);
      }
     }
     file_description        
     {
      /*
      close_fields();
      alloc_file_entry($4, 0);
      gen_fdesc($4,$9);
      */
      gen_fsd($4, $9, $6, 0);
     }
    | file_section SD { curr_division = CDIV_FD; }
      STRING { curr_division = CDIV_DATA; }
      file_description_sd_clauses PERIOD_TOK
      {
       $4->uval1.organization=TCB_FILE_ORGANIZATION_SORT;
       curr_field=NULL;
      }
      file_description    
      {
       /*
       close_fields();
       alloc_file_entry($4, 1);
       //
       //alloc_file_entry($4);
       //$4->uval10.sort_file = 1;
       //
       gen_fdesc($4,$9);
       */
       gen_fsd($4, $9, $6, 1); 
      }
    | error { yyerror("missing or invalid file description entry"); }
    | /* nothing */
    ;
file_description:
    field_description 
    { 
     $1->flags.isfilerecord = 1; 
     $$=$1; 
    }
    | file_description field_description 
    {
     /* Define a record for each FD/SD */
     if (($2 != NULL) && ($2->level == 1)) { 
        $2->flags.isfilerecord = 1; 
        $$=file_description_append_rec($1, $2); 
     }
     else {
        $1->flags.isfilerecord = 1; 
        $$=$1;
     }
    }
    ;

/*
 * DATA DESCRIPTION ENTRY
 */
field_description:
    integer def_name_opt 
    {
     picix=piccnt=v_flag=n_flag=decimals=pscale=0;
     if (($1 == 78) || ($1 == 66)) {
        if ($1 == 78) 
           yyerror("level 78 are not supported");
        if ($1 == 66) 
           yyerror("level 66 are not supported");
     } 
     else {
        if ($2==NULL) 
           define_field($1,alloc_filler());
        else 
           define_field($1,$2);
     } 
    } 
    data_clauses PERIOD_TOK 
    {
     $$=$2;
     if (($$ == NULL) || ($$->level != 66))
        update_field(curr_field);
     if (curr_field != NULL) { 
       if ((curr_field->occurs_flg != 0) && 
         (($1 == 1) || ($1 == 77) || ($1 == 66) || ($1 == 88)))
         yyerror("OCCURS clause not permitted for data item '%s' with level number 01/77/66/88", curr_field->name);
     }
    }
    ;
data_clauses:
    /* nothing */
    | data_clauses data_clause
    | data_clauses redefines_clause
    ;
redefines_clause:
    REDEFINES
    { curr_division = CDIV_PROC; /* parsing variable */ }
    redefines_var
    {
      curr_division = CDIV_DATA;
      curr_field->uval6.redefines = lookup_for_redefines($3);
      /*
      if ($<sval>-2 != NULL) {
         $<sval>-2->uval6.redefines = lookup_for_redefines($3);
      }
      // An unnamed field can be an implicit FILLER 
      else {
         yywarn("cannot redefine an unnamed field");
      }
      */
    }
    ;
redefines_var:
    VARIABLE    { $$=$1; }
    | SUBSCVAR  { $$=$1; }
    ;
data_clause:
    array_options
    | pictures
    | usage_option
    | sign_clause {
        curr_field->flags.separate_sign = ($1 & SCR_SIGN_SEPARATE) ? 1 : 0;
        curr_field->flags.leading_sign  = ($1 & SCR_SIGN_LEADING) ? 1 : 0; }
    | value_option
    | SYNCHRONIZED sync_options {curr_field->flags.sync=1;}
    | JUSTIFIED sync_options {if ($2 != 2) curr_field->flags.just_r=1;}
    | is_opt EXTERNAL {save_named_sect(curr_field);}
    | is_opt GLOBAL {}
    | BLANK when_opt ZERO { curr_field->flags.blank=1; }
    | RENAMES { curr_division = CDIV_PROC /* for parsing variable */; }
                variable thru_gname_opt
                    { curr_division = CDIV_DATA;
                    update_renames_field($3, $4);}
    ;
sync_options:
    /* nothing */ {$$=0;}
    | LEFT        {$$=2;}
    | RIGHT        {$$=1;}
    ;
thru_gname_opt: /* nothing */ { $$ = NULL;}
    | THRU variable { $$ = $2;}
    ;

/* OCCURS clause */
array_options:
      OCCURS integer times_opt
      { 
       curr_field->times = $2; 
       curr_field->occurs_flg++; 
      }
      indexed_by_opt
    | OCCURS integer TO integer times_opt DEPENDING
      { curr_division = CDIV_PROC; /* needed for parsing variable */ }
      on_opt gname
      {       
       curr_division = CDIV_DATA;
       create_occurs_info($2,$4,$9);
      }
      indexed_by_opt
    ;
key_is_opt:
    DIRECTION key_opt is_opt STRING
    {
     $4->level=0;
     if ($1 == ASCENDING) {
             $4->level=-1;
     }
     if ($1 == DESCENDING) {
             $4->level=-2;
     }
     $$=$4;
    }
    | { $$=NULL; }
    ;
indexed_by_opt: 
    key_is_opt INDEXED by_opt index_name_list
    { 
      /*define_implicit_field($4, $1, curr_field->times);*/
      /* Fix Me: Does not work, thus dup vars can be defined
      if ($4->defined) {
              yyerror("variable redefined, '%s'",$4->name);
              $4->defined=1;
      }
      else {
              define_implicit_field($4, $1, curr_field->times);
      } */
    }
    | /* nothing */
    ;
index_name_list:
     def_name        
     { 
      define_implicit_field($1, $<sval>-2, curr_field->times);
      /* Fix Me: Does not work, thus dup vars can be defined
      if ($4->defined) {
         yyerror("variable redefined, '%s'",$4->name);
         $4->defined=1;
      }
      else { 
         define_implicit_field($4, $1, curr_field->times);
      } */
     }   
     | index_name_list def_name 
       {
        define_implicit_field($2,$<sval>-2,curr_field->times);
       }  
     ;

/* USAGE clause */

usage_option :
    usage_opt is_opt usage { set_usage(curr_field, $3); }
    ;
usage:
    USAGENUM    { $$=$1; }
    | DISPLAY   { $$=USAGE_DISPLAY; }
    | POINTER   { $$=USAGE_POINTER; }
    ;

/* VALUE clause */

value_option:
    value_is_are value_list
    ;
value_is_are:
    VALUE is_opt
    | VALUES are_opt
    ;
value_list:
        value                           
        | value_list comma_opt value
        ;
value:
    gliteral    { set_variable_values($1,$1); }
    | gliteral THRU gliteral
     {
      set_variable_values($1,$3);
     }
    ;

/* Pictures clause */

pictures:
    PICTURE 
    { 
     curr_division = CDIV_PIC;
     /* first pic char found */
     picix=piccnt=v_flag=n_flag=decimals=pscale=0;
     picture[picix]=0;
    }
    is_opt picture 
    {
      /* finish picture */
      picture[picix+2]=0;
      curr_field->uval1.decimals=decimals;
      curr_field->pscale=pscale;
      if (curr_field->type == DTYPE_DISPLAY && piccnt > 18) {
         yyerror("Maximum elementary numeric item size of %s > 18 digits exceeded", curr_field->name);
      }
      if (curr_field->type == DTYPE_ALPHANUMERIC && piccnt > 12750) {
         yyerror("Maximum elementary alphanumeric item size of %s > 12750 exceeded", curr_field->name);
      }
    }
    ;
picture: /* nothing */
    | picture pic_elem 
    ;
pic_elem:
    CHAR multiplier_opt 
    {
     if (!save_pic_char ( $1, $2 )) {
        yyerror("invalid char in picture");
        YYERROR;
     }
    }        
    ;
multiplier_opt:
    /* nothing */ { $$ = 1; }
    | MULTIPLIER { $$ = $1; }
    ;

/* File description entry  */
file_description_fd_clauses: { $$=NULL; }
    | file_description_fd_clauses file_description_fd_clause
     { $$=set_fd_clause($1, $2); }
    ;
file_description_sd_clauses: { $$=NULL; }
    | file_description_sd_clauses file_description_sd_clause 
     { /* $$=NULL; */ $$=set_fd_clause($1, $2); }
    ;

file_description_fd_clause:
    is_opt EXTERNAL                    { $$=set_fd_clause_external(); }
    | is_opt GLOBAL                    { $$=set_fd_clause_global(); }
    | file_description_clause_block    { $$=NULL; }
    | file_description_clause_record   { $$=set_fd_clause_record($1); }
    | file_description_clause_label    { $$=NULL; }
    | file_description_clause_value    { $$=NULL; }
    | file_description_clause_data     { $$=NULL; }
    | file_description_clause_report   { $$=NULL; } 
    | file_description_clause_linage   { $$=NULL; }
    | file_description_clause_code_set { $$=NULL; }
    ;
file_description_sd_clause:
    file_description_clause_record { /* $$=NULL; */ $$=set_fd_clause_record($1); }  
    | file_description_clause_data { $$=NULL; }  
    ;

file_description_clause_block:
    BLOCK contains_opt integer
    to_integer_opt chars_or_recs_opt 
    { /* clause is ignored on x86 platform */ }
    ;

file_description_clause_record:
    RECORD contains_opt nliteral
    to_rec_varying_opt character_opts 
    { 
     if ($4 != NULL)
        $$=set_file_record_clause($4, $3, NULL, TCB_TYPE_RECORD_VARIABLE); 
     else 
        $$=set_file_record_clause($3, NULL, NULL, TCB_TYPE_RECORD_FIXED); 
    }
    | RECORD is_opt VARYING in_opt size_opt
      from_rec_varying_opt to_rec_varying_opt character_opts
      depend_rec_varying_opt
      { 
       $$=set_file_record_clause($7, $6, $9, TCB_TYPE_RECORD_VARIABLE); 
      }
    ;

file_description_clause_label: 
    LABEL record_is_are std_or_omitt { /* obsolete */ }
    ;

file_description_clause_value: 
    VALUE OF FILE_ID is_opt filename 
    {  
      if ($<sval>-2->uval7.filenamevar != NULL) {
         yyerror("Re-defining file name defined in SELECT statement");
      }
      else {
         $<sval>-2->uval7.filenamevar = $<sval>5;
      }
    }
    ;

file_description_clause_data: 
    DATA record_is_are var_strings { /* obsolete */ }  
    ;

file_description_clause_report: 
    report_is_are STRING { save_report( $2,$<sval>0 ); }
    ;

file_description_clause_code_set:
    CODE_SET is_opt STRING 
    { UNIMPLEMENTED ("Code-set is alphabet") /* unimplemented */ }
    ;

file_description_clause_linage:
    LINAGE is_opt data_name lines_opt
    file_description_clause_linage_footing 
    file_description_clause_linage_top 
    file_description_clause_linage_bottom
    { UNIMPLEMENTED ("Linage is clause") /* unimplemented */ }
    ;

file_description_clause_linage_footing:
    | with_opt FOOTING at_opt data_name { /* unimplemented */ }
    ;

file_description_clause_linage_top:
    | lines_at_opt TOP data_name { /* unimplemented */ }
    ;

file_description_clause_linage_bottom:
    | lines_at_opt BOTTOM data_name { /* unimplemented */ }
    ;

lines_at_opt:  /* nothing */
    | LINES
    | LINES AT
    | AT
    ;

report_is_are: REPORT is_opt
    | REPORTS are_opt
    ;

var_strings: STRING { }
    | var_strings STRING { }
    ; 
chars_or_recs_opt:
    /* nothing */
    | CHARACTERS
    | RECORDS
    ;
to_integer_opt: /* nothing */
    | TO integer { }
    ;
depend_rec_varying_opt: { $$ = NULL; }
    | DEPENDING on_opt STRING { $$ = $3; }
    ;
from_rec_varying_opt:
    /* nothing */ { $$ = NULL; }
    | from_opt nliteral { $$ = $2; }
    ;
from_opt: 
    FROM 
    | /* nothing */
    ;             
to_rec_varying_opt:
    /* nothing */ { $$ = NULL; }
    | TO nliteral { $$ = $2; }
    ;
record_is_are:
    RECORD is_opt
    | RECORDS are_opt
    ;
std_or_omitt:
    STANDARD
    | OMITTED
    ;
usage_opt:
    /* nothing */
    | USAGE
    ;
times_opt:
    /* nothing */
    | TIMES
    ;
when_opt:
    /* nothing */
    | WHEN
    ;
contains_opt:
    /* nothing */
    | CONTAINS
    ;
character_opts:
    /* nothing */
    | CHARACTERS
    ;
order_opt:
    /* nothing */
    | ORDER
    ;
data_opt:
    /* nothing */
    | DATA
    ;
/*
 * DATA DIVISION - working storage section
 */    
working_storage_section:
    working_storage_section
     field_description
    | /* nothing */
    ;
/*
 * DATA DIVISION - linkage section
 */    
linkage_section:
    /* nothing */
    | linkage_section
        field_description
    ;

/* PROCEDURE DIVISION */
procedure_division_opt:
    PROCEDURE DIVISION
    {
     curr_division = CDIV_PROC;
    }
     procedure_division_using_chaining_opt 
     procedure_division_returning_opt 
     PERIOD_TOK 
    {
     if (($4 == 2) && ($5 != NULL)) {
        yyerror("Invalid clause RETURNING used in PROCEDURE DIVISION with CHAINING clause");        
     }
     proc_header($4);
    }
     declaratives_opt
     procedure_list
    {
     /* close procedure_division sections & paragraphs */
     close_section(); /* this also closes paragraph */
     resolve_labels();
     proc_trail($4, $5);
    }
    | /* nothing */
    ;

/* Procedure Division Declaratives */
declaratives_opt: 
     DECLARATIVES PERIOD_TOK
     {
      decl_lbl=loc_label++;
      gen_jmplabel(decl_lbl);
     }
     declaratives_procedure
     declaratives_procedures
     END DECLARATIVES PERIOD_TOK
     { 
      close_section(); 
      gen_decl_select(declaratives_list, decl_lbl);
      gen_dstlabel(decl_lbl);
      curr_paragr=NULL;
      curr_section=NULL; 
      /* UNIMPLEMENTED ("Declaratives") */
     }
     | /* nothing */
    ;

declaratives_procedures: declaratives_decl  
    | declaratives_procedures declaratives_decl 
    ;

declaratives_procedure:
    procedure_section
    {
     close_section();
     open_section($1);
    }
    use_statements 
    { 
     append_declaratives_list($1, $3);    
    }
    | error { yyerror("declaratives section name expected"); }
    ;

declaratives_decl: declaratives_procedure
    | paragraph { close_paragr(); open_paragr($1); }
    | {free_expr_list(); stabs_line();} statements PERIOD_TOK
    | error { yyerror("unknown or wrong statement"); } PERIOD_TOK
    ;

use_statements:
    use_exception   { $$=$1; }
    | use_debugging { $$=$1; }
    | use_reporting { $$=$1; }
    ;

use_exception: 
    USE use_global_opt AFTER use_exception_error 
    PROCEDURE on_opt use_exception_option PERIOD_TOK
    {  
     /* mark_decl_list($6); */ 
     $$ = define_declarative(TCB_DECLARATIVE_USE_TYPE_EXCEPTION, $7, $2);
    }
    | error { yyerror("use statement expected"); }
    ;
use_exception_error: EXCEPTION 
    | ERROR_TOK 
    | STANDARD EXCEPTION 
    | STANDARD ERROR_TOK 
    | error 
     { 
      yyerror("Invalid use statement exception option"); 
     }
    ;
use_exception_option:
    /* name { $$ = set_declarative_exception_option($1, TCB_FILE_OPEN_MODE_NONE); } */
    use_exception_option_names { $$ = $1; }
    | open_mode
     {
       $$ = set_declarative_exception_option_mode($1);
     }
    ;

use_exception_option_names:
    name 
    { 
     $$ = set_declarative_exception_option_name($1, NULL); 
    }
    | use_exception_option_names comma_opt name 
     {
      $$ = set_declarative_exception_option_name($3, $1);
     }
    ;

use_reporting: USE use_global_opt BEFORE REPORTING name 
    {
     $$=NULL;  
     UNIMPLEMENTED ("Declaratives - use reporting") 
    }
    ;

use_debugging: USE for_opt DEBUGGING on_opt
    use_debugging_options
    {
     $$=NULL;  
     UNIMPLEMENTED ("Declaratives - use debugging") 
    }
    ;
use_debugging_options: use_debugging_options_procedure_names
    /* gname_list // procedure-name-1 ... */
    /* name // procedure-name-1 */
    | ALL PROCEDURES
    ;
use_debugging_options_procedure_names: name
    | use_debugging_options_procedure_names name
    ;

use_global_opt: { $$=TCB_DECLARATIVE_USE_OPTION_NONE; }
    | GLOBAL { $$=TCB_DECLARATIVE_USE_OPTION_GLOBAL; }
    ;

procedure_list:
    | procedure_list procedure_decl
    ;
procedure_decl:
    procedure_section { close_section(); open_section($1); }
    | paragraph { close_paragr(); open_paragr($1); }
    | {free_expr_list(); stabs_line();} statements PERIOD_TOK
/*    | {free_expr_list(); stabs_line();} statements */
    | error { yyerror("unknown or wrong statement"); } PERIOD_TOK
    | PERIOD_TOK { }
    ;

/* Procedure division sections and paragraphs */

procedure_section:
    LABELSTR SECTION PERIOD_TOK
    {
     struct sym *lab=$1;
     if (lab->defined != 0) {
        lab = install(lab->name,SYTB_LAB,2);
     }
     lab->defined = 1;
     $$=lab;
    }
    ;
paragraph:
    LABELSTR dot_or_eos
    {
     struct sym *lab=$1;
     if (lab->defined != 0) {
             if ((lab=lookup_label(lab,curr_section))==NULL) {
                        lab = install($1->name,SYTB_LAB,2);
             }
     }
     lab->parent = curr_section;
     lab->defined=1;
     $$=lab;
    }
    ;
dot_or_eos:
    '.'
    | PERIOD_TOK
    ;

/*
 * PROCEDURE DIVISION - COBOL verbs
 */

statement_list:
    statements { }
    ;
statements:
    statement
    | statements statement
    ;
statement:
      move_statement
    | initialize_statement
    | compute_statement
    | add_statement
    | subtract_statement
    | multiply_statement
    | divide_statement
    | accept_statement
    | display_statement
    | open_statement
    | close_statement
    | read_statement
    | return_statement
    | release_statement
    | write_statement
    | rewrite_statement
    | delete_statement
    | start_statement
    | perform_statement
    | goto_statement
    | exit_statement
    | stop_statement
    | call_statement
    | call_loadlib_statement
    | chain_statement
    | set_statement
    | sort_statement
    | merge_statement
    | inspect_statement
    | string_statement
    | unstring_statement
    | initiate_statement
    | generate_statement
    | terminate_statement
    | proto_statement
    | trace_statement
    | goback_statement
    | cancel_statement
    | unlock_statement
    | if_statement
    | evaluate_statement
    | search_statement
    | CONTINUE { stabs_line(); }
/*
    | NEXT SENTENCE { stabs_line(); }
*/
    ;

perform_statement:
    PERFORM perform_options
    ;
if_statement:
    if_part { gen_dstlabel($1); } end_if_opt
    | if_part ELSE
    { $<dval>$=gen_passlabel(); gen_dstlabel($1); }
     /* sentence { gen_dstlabel($<dval>3); } */
    conditional_statement { gen_dstlabel($<dval>3); }
    end_if_opt
    ;
search_statement:
    SEARCH search end_search_opt
    | SEARCH ALL search_all end_search_opt
    ;
evaluate_statement:
    EVALUATE
    { $<ival>$ = gen_evaluate_start(); }
    selection_subject_set
    { compute_subject_set_size($3); }
    when_case_list
    end_evaluate_or_eos
    { release_sel_subject($<ival>2,$3); }
    ;
end_evaluate_or_eos:
    END_EVALUATE
    | PERIOD_TOK
    ;
selection_subject_set:
    { $<sval>$=NULL; /* to store non-numeric symbols */ }
    selection_subject { $$=save_sel_subject($2,NULL,$<sval>1); }
    | selection_subject_set ALSO
     { $<sval>$=NULL; /* to store non-numeric symbols */ }
     selection_subject
     { $$=save_sel_subject($4,$1,$<sval>3); }
    ;
selection_subject:
    expr    /* this already includes identifiers and literals */
    {
     if (push_expr($1))
        $$=SSUBJ_EXPR;
     else {
        $<sval>0 = $1;
        $$=SSUBJ_STR;
     }
    }
    | condition { push_condition(); $$=SSUBJ_COND; }
    | TRUE_TOK  { $$=SSUBJ_TRUE; }
    | FALSE_TOK { $$=SSUBJ_FALSE; }
    ;
when_case_list:
    WHEN { $<ival>$ = loc_label++; /* mark end of "when" case */ }
    { $<ssbjval>$=$<ssbjval>-1; /* store inherited subject set */ }
    when_case
    sentence_or_nothing
    { $$=gen_end_when($<ival>-2,$<ival>2,$5); }
    | when_case_list WHEN { $<ival>$ = loc_label++; }
      { $<ssbjval>$=$<ssbjval>-1; }
      when_case
      { gen_bypass_when_case($1); }
      sentence_or_nothing
      { $$=gen_end_when($<ival>-2,$<ival>3,$7); }
    ;
when_case:
    { $<sval>$ = NULL; }
    selection_object 
    {
      gen_when_check(0,$<ssbjval>0,$2,$<ival>-1,$<sval>1);
      $$=0;
    }
    | when_case ALSO
      { $<sval>$ = NULL; }
      selection_object 
      {
       gen_when_check($1+1,$<ssbjval>0,$4,$<ival>-1,$<sval>3);
       $$=$1+1;
      }
    | OTHER { $$=-1; }
    ;
selection_object:
    ANY         { $$=SOBJ_ANY; }
    | TRUE_TOK  { $$=SOBJ_TRUE; }
    | FALSE_TOK { $$=SOBJ_FALSE; }
    | not_opt expr
     {
       if (push_expr($2)) {
          if ($1)
            $$=SOBJ_NEGEXPR;
          else
            $$=SOBJ_EXPR;
       }
       else {
          /* non-numeric comparation */
          $<sval>0 = $2;
          if ($1)
            $$=SOBJ_NEGSTR;
          else
            $$=SOBJ_STR;
       }
      }
    | not_opt expr THRU expr
      {
       if (push_expr($4) && push_expr($2)) {
          if ($1)
             $$=SOBJ_NEGRANGE;
          else
             $$=SOBJ_RANGE;
       }
       else {
          yyerror("ranges only accepted for numeric variables");
       }
      }
    | not_opt cond_name 
     {
       gen_condition($2);
       if ($1)
          $$=SOBJ_NEGCOND;
       else
          $$=SOBJ_COND; 
     }
    ;

sentence_or_nothing:
    /* nothing */               { $$ = 0; }
    | conditional_statement     { $$ = 1; }
    ;

if_part:
    IF  condition  
    { $<dval>$=gen_testif(); }
    end_then_opt
    conditional_statement { $<dval>$=$<dval>3; }
    /* sentence   { $<dval>$=$<dval>3; }*/
    ;

/*
  Fix me: This does not conform to the ANSI85 standard.
  However, it does reduce the number of conflicts.
*/
conditional_statement: { stabs_line(); } statement_list
    |  { stabs_line(); } NEXT SENTENCE
/*
    |  { stabs_line(); } CONTINUE 
*/
    ;

not_opt:
    /* nothing */ { $$=0; }
    | NOT { $$=1; }
    ;
end_if_opt:
    | END_IF
    ;
end_then_opt:
    | THEN
    ;
search:
    variable_indexed
    {
      $<dval>$=loc_label++; /* determine END label name */
      gen_marklabel(); 
      /* yydebug=1; */
    }
    search_varying_opt
    {
      $<dval>$=loc_label++; /* determine search loop start label */
      if ($3 == NULL) {
            $3=determine_table_index_name($1);
            if ($3 == NULL) {
               yyerror("Unable to determine search index for table '%s'", $1->name);
            }
      }
      gen_jmplabel($<dval>$); /* generate GOTO search loop start  */
    }
    search_at_end
    {
      gen_jmplabel($<dval>2); /* generate GOTO END  */
      gen_dstlabel($<dval>4); /* generate search loop start label */
      $$ = $<dval>2;
    } 
    search_when_list
    {
      /* increment loop index, check for end */
      gen_SearchLoopCheck($5, $3, $1);

      gen_jmplabel($<dval>4); /* generate goto search loop start label */
      gen_dstlabel($<dval>2); /* generate END label */
    }
    ;
search_all:
     variable_indexed
     {
        lbend=loc_label++; /* determine END label name */
        gen_marklabel();

        lbstart=loc_label++; /* determine search_all loop start label */

        $<sval>$=determine_table_index_name($1);
        if ($<sval>$ == NULL) {
           yyerror("Unable to determine search index for table '%s'", $1->name);
        }
        else {
          /* Initilize and store search table index boundaries */
          Initialize_SearchAll_Boundaries($1, $<sval>$);
        }

        gen_jmplabel(lbstart); /* generate GOTO search_all loop start  */
     }
     search_at_end
     {
        gen_jmplabel(lbend); /* generate GOTO END  */
        gen_dstlabel(lbstart); /* generate search loop start label */
     }
     search_all_when_list
     {
        /* adjust loop index, check for end */
        gen_SearchAllLoopCheck($3, $<sval>2, $1, curr_field, lbstart, lbend);
     }
    ;

search_varying_opt:
    VARYING variable {  $$=$2; }
    | { $$=NULL; }
    ;

search_at_end:
     at_opt END
     {
       $<dval>$=loc_label++; /* determine ATEND label name */
       gen_dstlabel($<dval>$); /* determine ATEND label name */
     }
     statement_list
     {
       $<dval>$=$<dval>3;
     }
    |
     {
       $<dval>$=loc_label++; /* determine ATEND label name */
       gen_dstlabel($<dval>$); /* determine ATEND label name */
     }
    ;

search_when_list:
     search_when { $$=$1; }
     | search_when_list search_when { $$=$1; }
     ;
search_when:
     WHEN
     search_when_conditional
     { $<dval>$=gen_testif(); }
     search_when_statement
     {
        $$ = $<dval>0;
        gen_jmplabel($$); /* generate GOTO END  */
        gen_dstlabel($<dval>3);
     }
     ;

search_when_statement:
    statement_list   
    |  NEXT SENTENCE
/*
    |  CONTINUE 
*/
    ;

search_when_conditional:
/*    name cond_op name { gen_compare($1,$2,$3); }
    | name cond_op nliteral { gen_compare($1,$2,(struct sym *)$3); }
    | name extended_cond_op name_or_lit { gen_compare($1,$2,$3); }
    | name_or_lit extended_cond_op name { gen_compare($1,$2,$3); }
    | nliteral cond_op nliteral {
                gen_compare((struct sym *)$1,$2,(struct sym*)$3); } */
    name_or_lit extended_cond_op name_or_lit { gen_compare($1,$2,$3); }
    ;

search_all_when_list:
     search_all_when
     | search_all_when_list search_all_when
     ;
search_all_when:
     WHEN { curr_field = NULL; }
     search_all_when_conditional
     { $<dval>$=gen_testif(); }
     search_all_when_statement
     {
        gen_jmplabel(lbend); /* generate GOTO END  */
        gen_dstlabel($<dval>4);
     }
    ;

search_all_when_statement:
    statement_list   
/*    statement */
    |  NEXT SENTENCE
/*
    |  CONTINUE 
*/
    ;

search_all_when_conditional:
    variable is_opt CONDITIONAL to_opt variable 
    {
      if ($3 != EQUAL)
         yyerror("Only = conditional allowed in search all statement");
      if (curr_field == NULL)
         curr_field = $1;
      gen_compare($1,$3,$5);
    }
    | variable is_opt CONDITIONAL to_opt literal
      {
        if ($3 != EQUAL)
           yyerror("Only = conditional allowed in search all statement");
        if (curr_field == NULL)
           curr_field = $1;
        gen_compare($1,$3,(struct sym *)$5);
      }
    | search_all_when_conditional AND { $<dval>$=gen_andstart(); }
      search_all_when_conditional  { gen_dstlabel($<dval>3); }
    ;

end_search_opt:
    | END_SEARCH
    ;

unlock_statement:
    UNLOCK name 
    { 
     gen_unlock($2); 
     UNIMPLEMENTED ("UNLOCK clause") 
    }
    ;
proto_statement:
    TCOBPROTO1 gname { gen_tcob_proto1( $2 ); }
    | TCOBPROTO2 gname gname { gen_tcob_proto2( $2,$3 ); }
    ;
trace_statement:
    READY TRACE { gen_trace_stm(1); }
    | RESET TRACE { gen_trace_stm(0); }
    ;
initiate_statement:
    INITIATE name
    ;
generate_statement:
    GENERATE name
    ;
terminate_statement:
    TERMINATE name
    ;
cancel_statement:
    CANCEL gname { gen_cancel($2); }
    | CANCEL ALL { gen_cancel(NULL); }
    ;
        
/* MERGE statement */
merge_statement:
    MERGE name sort_keys 
    sort_collating_opt 
    merge_using 
    sort_output 
    {
     sort_keys_append($2, $3); 
     gen_sort($2, $5, $6); 
    }
    ;

merge_using:
    USING sort_file_list 
    { $$ = alloc_node_container(TCB_SORT_NODE_TYPE_FILE, $2); }
    ;

/* SORT statement */
sort_statement:
    SORT name sort_keys 
    sort_duplicates_opt sort_collating_opt 
    sort_input
    sort_output 
    {
     sort_keys_append($2, $3); 
     gen_sort($2, $6, $7); 
    }
    ;

sort_keys:
    sort_key { $$=sort_keys_list_append(NULL, $1); }
    | sort_keys sort_key { $$=sort_keys_list_append($1, $2);  }
    ;

sort_key:
    on_opt DIRECTION key_opt sort_keys_names
    { $$=sort_key_list_create($4, $2); }
    ;

sort_keys_names:
    name { $$ = gvar_list_append(NULL, $1, source_lineno); }
    | sort_keys_names name { $$ = gvar_list_append($1, $2, source_lineno); }
    ;

sort_duplicates_opt:
    | with_opt DUPLICATES in_opt order_opt 
      { 
       UNIMPLEMENTED ("SORT with duplicates in order clause") 
       /* unimplemented */ 
      }
    ;

sort_collating_opt:
    | collating_sequence 
     { UNIMPLEMENTED ("SORT/MERGE collating sequence clause") /* unimplemented */ }
    ;

/* SORT and MERGE statement clauses */  
sort_input:
    INPUT PROCEDURE is_opt perform_range 
     { $$ = alloc_node_container(TCB_SORT_NODE_TYPE_PROC, $4); }
    | USING sort_file_list 
     { $$ = alloc_node_container(TCB_SORT_NODE_TYPE_FILE, $2); }
    ;       
sort_output:
    OUTPUT PROCEDURE is_opt perform_range 
     { $$ = alloc_node_container(TCB_SORT_NODE_TYPE_PROC, $4); }
    | GIVING sort_file_list 
     { $$ = alloc_node_container(TCB_SORT_NODE_TYPE_FILE, $2); }
    ;

sort_file_list:  name 
     { $$ = alloc_sortfile_node($1); }
    | sort_file_list name
     { $$ = append_sortfile_node(TCB_SORT_NODE_TYPE_FILE, $1, $2); }
    ;
        
/* MOVE statement */
move_statement:
      MOVE gname TO name_var_list { gen_moves($2, $4); }
    | MOVE CORRESPONDING name_var TO name_var { gen_movecorr($3, $5); }
    | MOVE LENGTH OF gname TO name_var { gen_movelength($4, $6); }
    | MOVE gname TO { yyerror("Expected variable"); }
    ;
/* INITIALIZE statement */
initialize_statement:
    INITIALIZE  gname_list initialize_replacing_opt { gen_initializes($2); }
    | INITIALIZE { yyerror("INITIALIZE: expected a variable name");}
    ;
initialize_replacing_opt:
    | REPLACING initialize_replacing_lists 
     { UNIMPLEMENTED ("INITIALIZE ... REPLACING clause") }
    ;
initialize_replacing_lists:
    initialize_replacing_list
    | initialize_replacing_lists initialize_replacing_list 
    ;
initialize_replacing_list:
    initialize_type_list data_opt BY gname { /* not implimented */ }
    ;
initialize_type_list: ALPHABETIC_TOK { }
    | ALPHANUMERIC { }
    | NUMERIC { }
    | ALPHANUMERIC_EDITED { }
    | NUMERIC_EDITED { }
    ;
     
/* Compute statement */
compute_statement:
    COMPUTE compute_body end_compute_opt
    | COMPUTE { yyerror(err_msg_bad_form, "COMPUTE");}
    ;
compute_body:
    var_list_name CONDITIONAL expr on_size_error_opt
    {
      if ($2 != EQUAL)
        yyerror("= expected");
      else if ($4 == NULL)
        gen_compute1($1, $3);
      else
        gen_compute2($1, $3, $4);
      delete_mathvar_info($1);
      if ($4 != NULL)
        tmose = NULL;
    }
    ;
end_compute_opt:
    /* nothing */
    | END_COMPUTE
    ;

/* Add statement */
add_statement:
    ADD add_body end_add_opt
    | ADD   { yyerror(err_msg_bad_form, "ADD");}
    ;
add_body:
    var_list_gname TO var_list_name on_size_error_opt
    {
        gen_add1($1, $3, $4);
        delete_mathvar_info($1);
        delete_mathvar_info($3);
        if ($4 != NULL)	
          tmose = NULL;
    }
    | var_list_gname add_to_opt GIVING var_list_name on_size_error_opt
      {
        gen_add2($1, $4, $2, $5);
        delete_mathvar_info($1);
        delete_mathvar_info($4);
        if ($5 != NULL)	
          tmose = NULL;
      }
    | CORRESPONDING var_list_gname TO var_list_name rounded_opt on_size_error_opt
      {
        gen_addcorr1($2, $4, $5, $6);
        delete_mathvar_info($2);
        delete_mathvar_info($4);
        if ($6 != NULL)	
          tmose = NULL;
      }
    ;
add_to_opt:
    /* nothing */ { $$ = NULL; }
    | TO gname    { $$ = $2; }
    ;
end_add_opt:
    /* nothing */
    | END_ADD
    ;

/* Subtract statement */

subtract_statement:
    SUBTRACT subtract_body end_subtract_opt
    | SUBTRACT { yyerror(err_msg_bad_form, "SUBTRACT");}
    ;
subtract_body:
    var_list_gname FROM var_list_name on_size_error_opt
      {
        gen_subtract1($1, $3, $4);
        delete_mathvar_info($1);
        delete_mathvar_info($3);
        if ($4 != NULL)
          tmose = NULL;
      }
    | var_list_gname FROM gname GIVING var_list_name on_size_error_opt
      {
        assert_numeric_sy($3);
        gen_subtract2($1, $5, $3, $6);
        delete_mathvar_info($1);
        delete_mathvar_info($5);
        if ($6 != NULL)
          tmose = NULL;
      }
    | CORRESPONDING var_list_gname FROM var_list_name rounded_opt on_size_error_opt
      {
        gen_subtractcorr1($2, $4, $5, $6);
        delete_mathvar_info($2);
        delete_mathvar_info($4);
        if ($6 != NULL)
          tmose = NULL;
      }
    ;
end_subtract_opt:
    | END_SUBTRACT
    ;

/* Multiply statement */

multiply_statement:
    MULTIPLY multiply_body end_multiply_opt
    | MULTIPLY { yyerror(err_msg_bad_form, "MULTIPLY");}
    ;
multiply_body:
    gname BY gname GIVING var_list_name on_size_error_opt
      {
        assert_numeric_sy($1);
        assert_numeric_sy($3);
        gen_multiply2($5, $1, $3, $6);
        delete_mathvar_info($5);
        if ($6 != NULL)
          tmose = NULL;
      }
    | gname BY var_list_name on_size_error_opt
      {
        assert_numeric_sy($1);
        gen_multiply1($3, $1, $4);
        delete_mathvar_info($3);
        if ($4 != NULL)
          tmose = NULL;
      }
    ;
end_multiply_opt:
    /* nothing */
    | END_MULTIPLY
    ;

/* Divide statement */

divide_statement:
    DIVIDE divide_body end_divide_opt
    | DIVIDE { yyerror(err_msg_bad_form, "DIVIDE");}
    ;
divide_body:
    gname BY gname GIVING var_list_name on_size_error_opt
      {
        assert_numeric_sy($1);
        assert_numeric_sy($3);
        gen_divide2($5, $1, $3, $6);
        delete_mathvar_info($5);
        if ($6 != NULL)
          tmose = NULL;
      }
    | gname BY gname GIVING name rounded_opt REMAINDER name on_size_error_opt
      {
        assert_numeric_sy($1);
        assert_numeric_sy($3);
        assert_numeric_dest_sy($5);
        gen_divide4($1, $3, $5, $8, $6, $9);
        if ($9 != NULL)
          tmose = NULL;
      }
    | gname INTO gname GIVING name rounded_opt REMAINDER name on_size_error_opt
      {
        assert_numeric_sy($1);
        assert_numeric_sy($3);
        assert_numeric_dest_sy($5);
        gen_divide4($3, $1, $5, $8, $6, $9);
        if ($9 != NULL)
          tmose = NULL;
      }
    | gname INTO gname GIVING var_list_name on_size_error_opt
      {
        assert_numeric_sy($1);
        assert_numeric_sy($3);
        gen_divide2($5, $3, $1, $6);
        delete_mathvar_info($5);
        if ($6 != NULL)
          tmose = NULL;
      }
    | gname INTO var_list_name on_size_error_opt
      {
        assert_numeric_sy($1);
        gen_divide1($3, $1, $4);
        delete_mathvar_info($3);
        if ($4 != NULL)
          tmose = NULL;
      }
    ;
end_divide_opt:
    /* nothing */
    | END_DIVIDE
    ;

/* Accept statement */
accept_statement:
    accept_hardware            /* Accept format 1 (hardware)      */ 
    | accept_chronological     /* Accept format 2 (chronological) */
    | accept_screen            /* Accept format 3 (screen)        */
    | ACCEPT { yyerror(err_msg_bad_form, "ACCEPT");}
    ;
accept_hardware:
      ACCEPT name accept_from_opt { gen_accept($2, 0, 1); } on_exception_opt end_accept_opt
    | ACCEPT name FROM INKEY        end_accept_opt {  gen_accept_from_inkey($2); }
    | ACCEPT name FROM INPUT STATUS end_accept_opt {  gen_accept_from_inkey($2); }
    | ACCEPT name FROM CMD_LINE     end_accept_opt {  gen_accept_from_cmdline($2); } 
    | ACCEPT name FROM ENVIRONMENT_VARIABLE accept_hardware_env_var end_accept_opt  
    {
      gen_accept_env_var($2, $5);
    }
    ;
accept_hardware_env_var: name { $$=$1; }
    | CLITERAL   
     {
      save_literal($1,'X');
      $1->all=0;
      $$=(struct sym *)$1;
     }
    ;
accept_from_opt:
    | FROM STD_INPUT
    | FROM CONSOLE
    ;
on_exception_opt:
    | on_opt EXCEPTION variable 
    { 
      gen_store_fnres($3); 
      $<dval>$ = gen_check_zero();
    }
      statement_list    { gen_dstlabel($<dval>4); }
    ;
accept_chronological:
    ACCEPT name FROM DATE_TIME end_accept_opt       
    {
       gen_accept_from_chron($2, $4, 0);
    }
    ;
accept_screen:
    ACCEPT name accept_options end_accept_opt
                        { 
                          gen_accept($2, $3, 1); 
                        } 
    | ACCEPT name accept_options 
      on_opt EXCEPTION  { 
                          screen_io_enable++; 
                          HTG_prg_uses_term = 1; 
                          gen_accept($2, $3, 1); 
                        } 
      variable          { 
                          gen_store_fnres($7); 
                          $<dval>$ = gen_check_zero();
                        }
      statement_list    { gen_dstlabel($<dval>8); }
      end_accept_opt         
    ;
end_accept_opt:
     /* Nothing */
     | END_ACCEPT 
     ;

/* Display statement */
display_statement:
    display_line 
    | display_screen 
    | DISPLAY { yyerror(err_msg_bad_form, "DISPLAY");}
    ;
display_line:
    DISPLAY display_varlist display_upon display_line_options end_display_opt
      { gen_display_line($3, $4); }
    ;
display_screen:
    DISPLAY display_varlist accept_display_options end_display_opt
    { gen_display_screen($3); }
    ;
display_varlist:
    gname                           { put_disp_list($1); }
    | display_varlist sep_opt gname { put_disp_list($3); }
    ;
display_upon:
    UPON CONSOLE       { $$ = 1; }
    | UPON STD_OUTPUT  { $$ = 1; }
    | UPON STD_ERROR   { $$ = 2; }
    ;
display_line_options:
     /* nothing */                               { $$ = 0; } 
    | display_line_options with_opt NO ADVANCING { $$ = $1 | SCR_NO_ADVANCING; }
    | display_line_options with_opt ERASE        { $$ = $1 | SCR_ERASE_EOL; }
    | display_line_options with_opt ERASE EOS    { $$ = $1 | SCR_ERASE_EOS; }
    | display_line_options with_opt ERASE EOL    { $$ = $1 | SCR_ERASE_EOL; }
    | display_line_options with_opt ERASE SCREEN { $$ = $1 | SCR_ERASE_EOS; }
    ;
end_display_opt:
     /* Nothing */
     | END_DISPLAY
     ;
/* common options for display and accept */
/*line_position:    
    | at_opt scr_line  scr_position  {   }
    | scr_line_position        {   }
    ;*/
scr_line:    
    LINE number_opt expr
     {
      screen_io_enable++;
      HTG_prg_uses_term = 1;
      push_expr($3);
      gen_gotoy_expr();
     }
    ;
scr_position:    
     COLUMN number_opt expr 
     {
      screen_io_enable++;
      HTG_prg_uses_term = 1; 
      push_expr($3);
      gen_gotox_expr();
     }
    | POSITION expr 
     {
      screen_io_enable++;
      HTG_prg_uses_term = 1; 
      push_expr($2);
      gen_gotox_expr();
     }
    ;
scr_line_position:
    AT NLITERAL
     {
      screen_io_enable++;
      HTG_prg_uses_term = 1; 
      scr_push_display_position($2);
     } 
    | AT variable
     {
      screen_io_enable++;
      HTG_prg_uses_term = 1; 
      scr_push_display_position($2);
     } 
    ;
accept_options:
    accept_display_option { $$ = $1; }
    | accept_options accept_display_option { $$ = $1 | $2; }
    ;
accept_display_options:
    /* nothing */                  { $$ = 0; } 
    | accept_display_options accept_display_option { $$ = $1 | $2; }
    ;
accept_display_option:
    with_opt  screen_attrib     { $$ = $2; }
    | scr_line                  { $$ = 0; }
    | scr_position              { $$ = 0; }
    | scr_line_position         { $$ = 0; }
    ;

/* Open statement */
open_statement:
    OPEN open_options 
    { 
     HTG_prg_uses_fileio = 1;
     gen_open_stm($2); 
    }
    | OPEN { yyerror(err_msg_bad_form, "OPEN");}
    ;
open_options:
    open_mode open_varlist { $$=set_file_open_stm_list($1, $2, NULL); }
    | open_options open_mode open_varlist { $$=set_file_open_stm_list($2, $3, $1); }
    ;
open_mode:
    INPUT    { $$=TCB_FILE_OPEN_MODE_INPUT; }
    | I_O    { $$=TCB_FILE_OPEN_MODE_IO; }
    | OUTPUT { $$=TCB_FILE_OPEN_MODE_OUTPUT; }
    | EXTEND { $$=TCB_FILE_OPEN_MODE_EXTEND; }
    | error  
     { 
      $$=TCB_FILE_OPEN_MODE_NONE;
      yyerror("invalid or missing file OPEN mode"); 
     }
    ;
open_varlist:
      name { $$=set_file_open_stm($1, NULL); }
    | open_varlist sep_opt name { $$=set_file_open_stm($3, $1); }
    ;

/* Close statement */
close_statement:
    CLOSE close_files
    | CLOSE { yyerror(err_msg_bad_form, "CLOSE");}
    ;
close_files:
      close_file
    | close_files sep_opt close_file
    ;
close_file:
    name close_options_opt { gen_close($1); }
    ;
close_options_opt:
    close_options   
    { 
     $$=0; 
     UNIMPLEMENTED ("CLOSE options clause") 
    }
    | with_lock_opt { $$=$1; }
    ;
close_options:
    with_opt NO REWIND {  }
    | REEL         {  }
    | UNIT         {  }
    | REEL for_opt REMOVAL {  }
    | UNIT for_opt REMOVAL {  }
    ;
with_lock_opt:
    with_opt LOCK          
    { 
     $$=1; 
     UNIMPLEMENTED ("WITH LOCK clause") 
    }
    | with_opt IGNORE LOCK 
     { 
      $$=2; 
      UNIMPLEMENTED ("IGNORE LOCK clause") 
     }
    | /* nothing */        { $$=0; }
    ;

/* Return statements */

return_statement: 
    RETURN_TOK return_body end_return_opt
    | RETURN_TOK { yyerror(err_msg_bad_form, "RETURN");}
    ;
return_body:
    name
    record_opt
    read_into_opt
    {    
     if (gen_reads($1, $3, NULL, 1, 4, 0) != 0) {
        YYABORT;
     }
    }
    | name
    record_opt
    read_into_opt
    read_at_end_opt
    {    
     if (gen_reads($1, $3, NULL, 1, 5, 0) != 0) {
        YYABORT;
     }
     else {
        ginfo_container4($4);
        gic = NULL;
     }
    }
    ;

/* Read statements */

read_statement: 
    READ read_body end_read_opt { }
    | READ { yyerror(err_msg_bad_form, "READ");}
    ;
read_body: 
    name
    read_next_opt
    record_opt
    read_into_opt
    with_lock_opt
    read_key_opt
    {
     if (gen_reads($1, $4, $6, $2, 0, $5) != 0) {
        YYABORT;
     }
     else {
        gen_perform_decl($1, NULL);
     }
    }
    | name
    read_next_opt
    record_opt
    read_into_opt
    with_lock_opt
    read_key_opt
    read_at_end_opt
    {    
     if (gen_reads($1, $4, $6, $2, 1, $5) != 0) {
        YYABORT;
     }
     else {
        ginfo_container4($7);
        gen_perform_decl($1, (void*)$7);
        gic = NULL;
     }
    }
   | name
    read_next_opt
    record_opt 
    read_into_opt
    with_lock_opt
    read_key_opt
    read_invalid_key_opt 
    {    
     if (gen_reads($1, $4, $6, $2, 2, $5) != 0) {
        YYABORT;
     }
     else {
       gen_test_invalid_keys ($7, $1, TCB_STATUS_23_KEY_NOT_EXISTS);
       gen_perform_decl($1, (void*)$7); 
     }
    }
    ;
read_next_opt:
    /* nothing */       { $$ = 0; }
    | NEXT              { $$ = 1; }  
    | PREVIOUS          { $$ = 2; }  
    ;
read_into_opt:
    /* nothing */       { $$ = NULL; }
    | INTO name         { $$ = $2; }
    ;
read_key_opt:
    /* nothing */       { $$ = NULL; }
    | KEY is_opt name   { $$ = $3; }
    ;
read_at_end_opt:
    NOT at_opt on_end       
     {
      ginfo_container2($3, 2);
      $$=ginfo_container3($3, 2);
     }
    | AT on_end 
     {
      ginfo_container2($2, 1);
      $$=ginfo_container3($2, 1);
     }
    | on_end
     {
      ginfo_container2($1, 1);
      $$=ginfo_container3($1, 1);
     }
    | AT on_end NOT at_opt 
     { 
      ginfo_container2($2, 1);
     } 
     on_end 
     { 
      ginfo_container2($6, 2);
      $$=ginfo_container3($6, 3);
     }
    | on_end NOT at_opt 
     { 
      ginfo_container2($1, 1);
     } 
     on_end 
     { 
      ginfo_container2($5, 2);
      $$=ginfo_container3($5, 3);
     }
    ;
on_end:
    END
    { 
      if ( gic == NULL ) {
         gic=ginfo_container0();
      }
      $$=ginfo_container1(gic);
      stabs_line();
    }
    statement_list
    { 
      $$=$<gic>2;
    }
    ;
read_invalid_key_opt:
    read_invalid_key { $$ = gen_invalid_keys ($1, NULL); }
    | read_not_invalid_key { $$ = gen_invalid_keys (NULL, $1); }
    | read_invalid_key read_not_invalid_key { $$ = gen_invalid_keys ($1, $2); }
    ;
read_invalid_key:
    INVALID key_opt     { $<ike>$ = gen_before_invalid_key (); }
    statement_list            { $$ = gen_after_invalid_key ($<ike>3); }
    ;
read_not_invalid_key:
    NOT INVALID key_opt { $<ike>$ = gen_before_invalid_key (); }
    statement_list            { $$ = gen_after_invalid_key ($<ike>4); }
    ;
end_read_opt:
    /* nothing */
    | END_READ
    ;
end_return_opt:
    /* nothing */
    | END_RETURN
    ;

/* Release statement */

release_statement:
    RELEASE name release_from_opt
    {
      gen_release($2, $3);
    }
    ;
release_from_opt:
    /* nothing */       { $$ = NULL; }
    | FROM gname        { $$ = $2; }
    ;

/* Write statement */

write_statement:
    WRITE name write_from_opt write_options
    { } /*
      if ($2->level != 1) {
        yyerror("Identifier %s may not be used in WRITE statement", $2->name);
      }
      else {
        if (write_advancing_sw == 0) 
           gen_write($2, $4, $3); 
        else
           gen_write_adv($2, $4, $3, write_advancing_sw); 
      }
    }*/
    invalid_key_opt
    end_write_opt 
    {
     if ($2->level != 1) {
        yyerror("Identifier %s may not be used in WRITE statement", $2->name);
     }
     else {
        if (write_advancing_sw == 0) 
           gen_write($2, $4, $3); 
        else
           gen_write_adv($2, $4, $3, write_advancing_sw); 
        gen_test_invalid_keys($6, $2, TCB_STATUS_22_KEY_EXISTS);
        if ($2->ix_desc != NULL)         
          gen_perform_decl($2->ix_desc, (void*)$6);
        else 
          yyerror("Unknown error : file name not found for WRITE variable %s", $2->name);
     }
    }
    ;
write_from_opt:
    /* nothing */       { $$ = NULL; }
    | FROM gname        { $$ = $2; }
    ;
write_options:
    /* nothing */       { $$ = NULL; write_advancing_sw = 0; }
    | before_after advancing_opt gname line_lines_opt
      { 
       /* gen_loadvar($3); */
       $$ = $3; 
       write_advancing_sw = $1; 
     }
    | before_after advancing_opt PAGE_TOK
      { 
       write_advancing_sw = -$1;
       $$ = NULL; 
      }
    ;
end_write_opt:
    /* nothing */
    | END_WRITE
    ;

/* Rewrite statement */

rewrite_statement:
    REWRITE name write_from_opt
    { } /*
     if ($2->level != 1)
        yyerror("Identifier %s may not be used in REWRITE statement", $2->name);
     gen_rewrite($2, $3);
    } */
    invalid_key_opt
    end_rewrite_opt 
    {
     if ($2->level != 1) {
        yyerror("Identifier %s may not be used in REWRITE statement", $2->name);
     }
     else {
        gen_rewrite($2, $3);
        gen_test_invalid_keys ($5, $2, TCB_STATUS_22_KEY_EXISTS);
        if ($2->ix_desc != NULL)         
           gen_perform_decl($2->ix_desc, (void*)$5);
        else 
           yyerror("Unknown error : file name not found for REWRITE variable %s", $2->name);
     }
    }
    ;
end_rewrite_opt:
    /* nothing */
    | END_REWRITE
    ;

/* Delete statement */

delete_statement:
    DELETE name record_opt 
    { 
     gen_delete($2); 
    }
    invalid_key_opt
    end_delete_opt 
    {
     gen_test_invalid_keys ($5, $2, TCB_STATUS_23_KEY_NOT_EXISTS);
     gen_perform_decl($2, (void*)$5);
    }
    ;
end_delete_opt:
    /* nothing */
    | END_DELETE
    ;

/* Start statement */

start_statement:
    START start_body
    invalid_key_opt 
    {
     gen_test_invalid_keys ($3, $2, TCB_STATUS_23_KEY_NOT_EXISTS);
     gen_perform_decl($2, (void*)$3);
    }
    end_start_opt
    ;
start_body:
    name 
    {
     gen_start($1, 0, NULL); 
     $$ = $1;
    }
    | name KEY is_opt cond_op name 
    { 
     gen_start($1, $4, $5); 
     $$ = $1;
    }
    ;
end_start_opt:
    /* nothing */
    | END_START
    ;

/* 
 GO TO statements 
 Format 1: Unconditional
 Format 2: Conditional  (DEPENDING ON)
 Format 3: Altered (Paragraph-name. GO TO.) - not implemented 
*/
goto_statement:
    GO to_opt goto_label { gen_goto($3); }
    | GO to_opt goto_label_list DEPENDING on_opt variable
    {
    	if (is_numeric_sy($6))
      gen_goto_depending($3, $6);
     else yyerror("variable '%s' must be numeric", $6->name);
    }
    ;
goto_label: label { $$ = insert_list(NULL, $1); }
    ;
goto_label_list:
      label                             { $$ = insert_list(NULL, $1); }
    | goto_label_list label             { $$ = insert_list($1, $2); }
    | goto_label_list LISTSEP label     { $$ = insert_list($1, $3); }
    ;

/* CALL statement */
call_statement:
    CALL  { curr_call_mode=CM_REF; }
    call_convention_opt
    gname
    using_options       
    returning_options 
    { $<ival>$ = loc_label++; /* exception check */ }
    { $<ival>$ = loc_label++; /* not exception check */ } 
    { 
      $<ival>$ = emt_call((struct lit *)$4, $5, $<ival>7, $<ival>8, $6); 
      /* gen_store_fnres($6); */
      /* If paramater is a variable then dynamic link libs are required */
/*
      if ($4->litflag == 0 ) {
         HTG_prg_uses_dcall = 1;
      }				 
*/
    }
    on_exception_or_overflow 
    on_not_exception { check_call_except($10, $11, $<ival>7, $<ival>8, $<ival>9); }
    end_call_opt
    | CALL { yyerror(err_msg_bad_form, "CALL"); }
    ;

call_convention_opt: { curr_call_convention = 0; }
    | CALL_CONV_C { curr_call_convention = 0; }
    | CALL_CONV_STDCALL { curr_call_convention = 1; }
/*    | CALL_CONV_STDCALL { yyerror("STDCALL (WINAPI) convention is not implimented"); }*/
    ;

/* CALL-LOADLIB statement */
call_loadlib_statement:
    CALL_LOADLIB
    gname
    {
     emt_call_loadlib((struct lit *)$2); 
    }
    end_call_loadlib_opt
    | CALL_LOADLIB { yyerror(err_msg_bad_form, "CALL-LOADLIB"); }
    ;

/* END-CALL-LOADLIB  */
end_call_loadlib_opt: END_CALL_LOADLIB { }
    | { }
    ;

/* CHAIN statement */        
chain_statement:        
    CHAIN  { curr_call_mode=CM_CHAIN; }
    gname
    using_options   { $<ival>$ = loc_label++; /* exception check */ }
    { $<ival>$ = gen_chain($3,$4,$<ival>5); }
    on_exception_or_overflow 
    {/* check_call_except($9,$10,$<ival>6,$<ival>7,$<ival>8);*/ }
    end_chain_opt
    | CHAIN { yyerror(err_msg_bad_form, "CHAIN"); }
    ;

/* EXIT statement */
exit_statement:
      EXIT           { gen_exit(0); }
    | EXIT PARAGRAPH { gen_exit(0); }
    | EXIT PROGRAM   { gen_exit(1); }
    ;

/* Stop statement */
stop_statement:
    STOP RUN { gen_stoprun(); }
    | STOP stop_literal
     {
      struct sym *sy;
      gen_display_line(2, SCR_NO_ADVANCING);
      sy = define_temp_field(DTYPE_ALPHANUMERIC,1);
      gen_accept(sy, 0, 1);
     }
    ;
stop_literal:
    CLITERAL
    {
      save_literal($1,'X');
      $1->all=0;
      put_disp_list((struct sym *)$1);
    }
    | NLITERAL
    {
      save_literal($1,'X');
      $1->all=0;
      put_disp_list((struct sym *)$1);
     }
    ;

/* Goback statement */
goback_statement:
    GOBACK { gen_goback(); }
    ;

var_list_name: name rounded_opt sep_opt
     {
      $$ = create_mathvar_info(NULL, $1, $2);
     }
    | var_list_name name rounded_opt sep_opt
     {
      $$ = create_mathvar_info($1, $2, $3);
     }
    ;

var_list_gname: gname sep_opt
     {
      $$ = create_mathvar_info(NULL, $1, 0);
     }
    | var_list_gname gname sep_opt
     {
      $$ = create_mathvar_info($1, $2, 0);
     }
    ;

rounded_opt:
    /* Nothing */  { $$=0; }
    | ROUNDED      { $$=1; }
    ;

on_size_error_opt:
    /* nothing */
      {
       $$=NULL;
      }
    | NOT on_opt SIZE
      on_size_error
      {
       $$=math_on_size_error4($4, 2);
      }
    | on_opt SIZE
      on_size_error
      {
       $$=math_on_size_error4($3, 1);
      }
    | on_opt SIZE
      on_size_error
      NOT on_opt SIZE
      {
       $3->lbl1=$3->ose;
      }
      on_size_error
      {
       $$=math_on_size_error4($8, 3);
      }
    ;

on_size_error:
     ERROR_TOK
     {
      if ( tmose == NULL ) {
         tmose=math_on_size_error0();
         $$=math_on_size_error1(tmose);
      }
      else {
        $$=math_on_size_error1(tmose);
      }
        stabs_line();
         }
     statement_list
     {
      math_on_size_error2(tmose);
      $$=$<mose>2;
     }
    ;

size_opt:
    /* nothing */
    | SIZE
    ;
end_call_opt:
    /* nothing */
    | END_CALL
    ;
end_chain_opt:
    /* nothing */
    | END_CHAIN
    ;
    
/* SET statement */  
set_statement:
    SET set_list ;
set_list: 
    set_target TO address_of_opt set_variable_or_nlit
       { gen_set_list($1,SET_TO,$4,0,$3); }
  | set_target UP BY var_or_nliteral   
       { gen_set_list($1,SET_UP_BY,$4,0,0); }
  | set_target DOWN BY var_or_nliteral 
       { gen_set_list($1,SET_DOWN_BY,$4,0,0); }
  | address_of_opt variable TO address_of_opt set_variable 
       { gen_set($2,SET_TO,$5,$1,$4); }
  ;

set_target:
/*    variable  { $$ = $1; } */
    name_list  { $$ = $1; }
  | cond_name { $$ = (struct sym *)chain_var($1); }
  ;

set_variable:
   variable           { $$ = $1; }
  | NULL_TOK           { $$ = NULL; }
  ;

set_variable_or_nlit:
  name_or_lit          { $$ = $1; }
  | ON                  { $$ = (struct sym *)define_num_lit(1); }
  | OFF                  { $$ = (struct sym *)spe_lit_ZE; }
  | NULL_TOK          { $$ = NULL; }
  | TRUE_TOK          
   { 
    $$ = (struct sym *)1; 
    /* no (struct sym *) may have this value! */ 
   }
  ;

address_of_opt:
  /* nothing */ { $$ = 0; }
  | ADDRESS of_opt { $$ = 1; }
  ;
        
/* String and Unstring statements */

string_statement:
    STRINGCMD string_from_list
        INTO name string_with_pointer {
                gen_stringcmd( $2, $4, $5 );
            }
        on_overflow_opt
        end_stringcmd_opt
    ;
unstring_statement:
    UNSTRING name
        unstring_delimited
        INTO unstring_destinations
        string_with_pointer
        unstring_tallying {
                gen_unstring( $2, $3, $5, $6, $7 );
            }
        on_overflow_opt
        end_unstring_opt
    ;
unstring_delimited:
    DELIMITED by_opt unstring_delimited_vars { $$=$3; }
    | /* nothing */                          { $$=NULL; }
    ;
unstring_delimited_vars:
    all_opt gname       { $$=alloc_unstring_delimited($1,$2); }
    | unstring_delimited_vars OR all_opt gname {
            struct unstring_delimited *ud;
            ud=alloc_unstring_delimited($3,$4);
            ud->next = $1;
            $$=ud;
        }
    ;
unstring_destinations:
    unstring_dest_var       { $$=$1; }
    | unstring_destinations sep_opt
        unstring_dest_var   {
            $3->next = $1;
            $$ = $3;
        }
    ;
unstring_dest_var:
    name unstring_delim_opt unstring_count_opt {
            $$ = alloc_unstring_dest( $1, $2, $3 );
        }
    ;
unstring_delim_opt:
    /* nothing */           { $$=NULL; }
    | DELIMITER in_opt name { $$=$3; }
    ;
unstring_count_opt:
    /* nothing */           { $$=NULL; }
    | COUNT in_opt name   { $$=$3; }
    ;
unstring_tallying:
    /* nothing */           { $$=NULL; }
    | TALLYING in_opt name  { $$=$3; }
    ;
all_opt:
    /* nothing */           { $$=0; }
    | ALL                   { $$=1; }
    ;
on_overflow_opt:
    { curr_division = CDIV_EXCEPTION; }
    on_overflow
    on_not_overflow
    { curr_division = CDIV_PROC; }
    ;
on_exception_or_overflow:
    on_opt exception_or_overflow { $<ival>$ = begin_on_except(); } 
        statement_list            { gen_jmplabel($<dval>0); $$=$<ival>3; }
    | /* nothing */ { $$ = 0; }
    ;
exception_or_overflow:
    EXCEPTION
    | OVERFLOW_TOK
    ;
on_not_exception:
    NOT on_opt EXCEPTION    { $<ival>$ = begin_on_except(); } 
        statement_list            { gen_jmplabel($<dval>-1); $$=$<ival>4; }
    | /* nothing */ { $$ = 0; }
    ;
on_overflow:
    on_opt OVERFLOW_TOK       { $<dval>$ = gen_at_end(1); }
        statement_list            { gen_dstlabel($<dval>3); }
    | /* nothing */
    ;
on_not_overflow:
    not_excep on_opt OVERFLOW_TOK   { $<dval>$ = gen_at_end(0); }
        statement_list            { gen_dstlabel($<dval>4); }
    | /* nothing */
    ;
    
invalid_key_opt:
    invalid_key_sentence {$$ = gen_invalid_keys($1, NULL);}
    | not_invalid_key_sentence {$$ = gen_invalid_keys(NULL, $1);}
    | invalid_key_sentence not_invalid_key_sentence
        {$$ = gen_invalid_keys($1, $2);}
    | { $$ = NULL;}
    ;
invalid_key_sentence:
    INVALID key_opt  { $<ike>$ = gen_before_invalid_key();  }
    statement_list   { $$ = gen_after_invalid_key($<ike>3); }
    ;
not_invalid_key_sentence:
    not_excep INVALID key_opt { $<ike>$ = gen_before_invalid_key();  }
    statement_list            { $$ = gen_after_invalid_key($<ike>4); }
    ;
not_excep:
    NOTEXCEP
    | NOT
    ;
string_with_pointer:
    with_opt POINTER name  { $$ = $3; }
    | /* nothing */        { $$ = NULL; }
    ;
string_from_list:
    string_from             { $$ = $1; }
    | string_from_list sep_opt string_from  {
            $3->next = $1;
            $$ = $3;
        }
    | error { yyerror("variable expected"); }
    ;
string_from:
    gname   {
    /* Item with no DELIMITED BY section implies use delimiter of next item */
                $$ = alloc_string_from( $1, (struct sym *)-1 );
            }
    | gname DELIMITED by_opt delimited_by {
                $$ = alloc_string_from( $1, $4 );
            }
    ;
delimited_by:
    gname     { $$=$1; }
    | SIZE    { $$=NULL; }
    | error { yyerror("SIZE or identifier expected"); }
    ;
end_stringcmd_opt:
    /* nothing */
    | END_STRINGCMD
    ;
end_unstring_opt:
    /* nothing */
    | END_UNSTRING
    ;

/* INSPECT statement */
inspect_statement:
    INSPECT
        name
        tallying_clause     { gen_inspect($2,(void *)$3,0); }
        replacing_clause    { gen_inspect($2,(void *)$5,1); }
    | INSPECT
        name
        converting_clause   { gen_inspect($2,(void *)$3,2); }
    ;
converting_clause:
        CONVERTING 
        noallname TO noallname inspect_before_after {
            $$ = alloc_converting_struct($2,$4,$5); 
                }
        ;
tallying_clause:
    TALLYING tallying_list { $$=$2; }
    | /* nothing */        { $$=NULL; }
    ;
tallying_list:
    tallying_list
        name FOR tallying_for_list  {
            $$ = alloc_tallying_list($1,$2,$4); }
    | /* nothing */     { $$ = NULL; }
    ;
tallying_for_list:
    tallying_for_list
        CHARACTERS inspect_before_after {
            $$ = alloc_tallying_for_list($1,INSPECT_CHARACTERS,NULL,$3); }
    | tallying_for_list
        ALL noallname inspect_before_after {
            $$ = alloc_tallying_for_list($1,INSPECT_ALL,$3,$4); }
    | tallying_for_list
        LEADING noallname inspect_before_after {
            $$ = alloc_tallying_for_list($1,INSPECT_LEADING,$3,$4); }
    | /* nothing */     { $$ = NULL; }
    ;
replacing_clause:
    REPLACING
        replacing_list      { $$ = $2; }
    | /* nothing */         { $$ = NULL; }
    ;
replacing_list:
    replacing_list
        CHARACTERS BY noallname inspect_before_after {
            $$ = alloc_replacing_list($1,INSPECT_CHARACTERS,NULL,$4,$5); }
    | replacing_list
        replacing_kind replacing_by_list {
            $$ = alloc_replacing_list($1,$2,$3,NULL,NULL); }
    | /* nothing */     { $$ = NULL; }
    ;
replacing_by_list:
    replacing_by_list
        noallname BY noallname inspect_before_after {
            $$ = alloc_replacing_by_list($1,$2,$4,$5); }
    | /* nothing */         { $$ = NULL; }
    ;
replacing_kind:
    ALL         { $$ = INSPECT_ALL; }
    | LEADING   { $$ = INSPECT_LEADING; }
    | TRAILING  { $$ = INSPECT_TRAILING; }
    | FIRST     { $$ = INSPECT_FIRST; }
    ;
inspect_before_after:
    inspect_before_after
        BEFORE initial_opt noallname
            { $$ = alloc_inspect_before_after($1,1,$4); }
    | inspect_before_after
        AFTER initial_opt noallname
            { $$ = alloc_inspect_before_after($1,2,$4); }
    | /* nothing */  { $$ = alloc_inspect_before_after(NULL,0,NULL); }
    ;
initial_opt:
    INITIAL_TOK
    | /* nothing */
    ;
    
expr:
    gname   { $$ = $1; }
    | expr '*' expr { $$ =
                (struct sym *)create_expr('*',(struct expr *)$1,(struct expr *)$3); }
    | expr '/' expr { $$ =
                (struct sym *)create_expr('/',(struct expr *)$1,(struct expr *)$3); }
    | expr '+' expr { $$ =
                (struct sym *)create_expr('+',(struct expr *)$1,(struct expr *)$3); }
    | expr '-' expr { $$ =
                (struct sym *)create_expr('-',(struct expr *)$1,(struct expr *)$3); }
    | expr POW_OP expr { $$ =
                (struct sym *)create_expr('^',(struct expr *)$1,(struct expr *)$3); }
    | '(' expr ')'  { $$=$2; }
    ;
/* expr_opt will be NULL or a (struct sym *) pointer if the expression
        was given, otherwise it will be valued -1 */
expr_opt:
        /* nothing */   { $$ = (struct sym *)-1; }
        | expr                  { $$ = $1; }
        ;
using_options:
    /* nothing */   { $$=0; }
    | USING     { $<ival>$=0; /* to save how many parameters */ }
      dummy     { $<ival>$=CALL; }
      parm_list  { $$=$<ival>2; } /* modified to signal calling pgm */
    ;
returning_options:
    /* nothing */   { $$=NULL; }
    | returning_options1 variable 
     { 
      if ($2->type == 'B') {
         $$=$2; 
      }
      else { 
         yyerror("Identifier in CALL RETURNING clause must be of BINARY/COMP/POINTER type");
         $$=NULL; 
      }
     }
    ;
returning_options1: RETURNING 
    | GIVING 
    ;
dummy: /* nothing */ ;

procedure_division_using_chaining_opt:   /* defined at procedure division */
    /* nothing */         { $$=0; }
    | USING gname_list    { gen_save_usings($2); $$=1; }
    | CHAINING gname_list { gen_save_chainings($2); $$=2; }
    ;

procedure_division_returning_opt:   /* defined at procedure division */
    /* nothing */        { $$=NULL; }
    | RETURNING variable 
     { 
      if ($2->type == 'B') {
         $$=$2; 
      }
      else { 
         yyerror("Identifier in PROCEDURE DIVISION RETURNING clause must be of BINARY/COMP/POINTER type");
         $$=NULL; 
      }
     }
    ;

parm_list:
    parm_list sep_opt parameter
        {   if ($<ival>0 == USING)
                gen_save_using($<sval>3);
            else if ($<ival>0 == CALL) {
                gen_push_using($<sval>3);
            }
        }
        | parameter
        {   if ($<ival>0 == USING)
                gen_save_using($<sval>1);
            else if ($<ival>0 == CALL) {
                gen_push_using($<sval>1);
            }
        }
    ;
parameter:
    gname 
    {
     /* $$=$1; */
     if ($1->litflag == 1) {
        struct lit *lp=(struct lit *)$1;
        lp->call_mode=curr_call_mode;
     }
     else {
/*      if (!need_subscripts) */
        /* fprintf(stderr, "debug : htcobol.y 3639 : curr_call_mode=%d\n", curr_call_mode);  */
        /* $1->uval3.call_mode=curr_call_mode; */
        struct sym *sy=(struct sym *)$1;
        sy->uval3.call_mode=curr_call_mode;
     }
     $$=$1;
    }
    /*| BY parm_type gname*/
    | by_opt parm_type gname
        { if ( curr_call_mode == CM_CHAIN )
            yyerror("parameter types not allowed on CHAIN");
          else
          {
            $$=$3;
            curr_call_mode=$<ival>2;
            if ($$->litflag==1) {
               struct lit *lp=(struct lit *)$$;
               lp->call_mode=curr_call_mode;
               }
            else
               $$->uval3.call_mode=curr_call_mode;
          }
        }
 /*   | OMITTED
        {   $$=save_special_literal('0','9', "%ZEROS%");
            $$->uval3.call_mode=CM_VAL;
        } */
    ;
parm_type:
    REFERENCE {$$=CM_REF;}
    | VALUE {$$=CM_VAL;}
    | CONTENT {$$=CM_CONT;}
/*    | DESCRIPTOR {$$=CM_CONT;}*/
    ;
intrinsic_parm_list:
    intrinsic_parm_list sep_opt intrinsic_parm
    { gen_push_using($<sval>3); }
    | intrinsic_parm { gen_push_using($<sval>1); }
    ;
intrinsic_parm:
    gname 
    {
     $$=$1;
     if ($$->litflag==1) {
        struct lit *lp=(struct lit *)$$;
        lp->call_mode=CM_REF;
     }
     else
       $$->uval3.call_mode=CM_REF;
    }
    ;

perform_range: label perform_thru_opt
    {
     $$ = alloc_sortfile_node2($1, $2);
     /*
     if ($2 != NULL) {
        $$ = append_sortfile_node(TCB_SORT_NODE_TYPE_PROC, $3, $2);
     }
     */
     /*
     gen_perform_thru($1,$2);
     $$ = ($2 == NULL) ? $1 : $2;
     */
    }
    ;

perform_options: perform_statements END_PERFORM { $$ = NULL; }
    | gname TIMES
      {
        gen_push_int($1);
        $<dval>$=gen_marklabel();
        gen_perform_test_counter($<dval>$);
      }
      perform_statements
      {
        gen_perform_times($<dval>3);
      }
      END_PERFORM { $$ = NULL; }
    | with_test_opt UNTIL
      {
        if ($1 == 2) {
        	$<ddval>$.lb2=gen_passlabel();
		}
        $<ddval>$.lb1=gen_marklabel();
      }
      condition
      {
        $<ddval>$.lb1=gen_orstart();
        if ($1 == 2) {
           $<ddval>$.lb2=gen_passlabel();
           gen_dstlabel($<ddval>3.lb2);
        }
      }
      perform_statements
      {
        if ($1 == 2) {
           gen_jmplabel($<ddval>3.lb1);
           gen_dstlabel($<ddval>5.lb2);
           gen_jmplabel($<ddval>3.lb2);
           gen_dstlabel($<ddval>5.lb1);
        }
        else {
           gen_jmplabel($<ddval>3.lb1);
           gen_dstlabel($<ddval>5.lb1);
        }
      }
      END_PERFORM { $$ = NULL; }
    | with_test_opt VARYING name FROM gname by_opt gname UNTIL
      {
        /* 
        Check if initailization of the 'VARYING identifier' is required.
        Initailization of the 'VARYING identifier' is not neccessary if
        it is the same as the 'FROM identifier'.
        */
        if ($5->litflag == '1') {
          gen_move($5,$3);
        }
        else {
          if(strcmp($5->name, $3->name) != 0) {
            gen_move($5,$3);
          }       
        }
        /* BEFORE=1 AFTER=2 */
        if ($1 == 2) {
           $<ddval>$.lb2=gen_passlabel();
        }
        $<ddval>$.lb1=gen_marklabel();
      }
      condition
      {
        $<dval>$=gen_orstart();
        /* BEFORE=1 AFTER=2 */
        if ($1 == 2) {
           gen_add($7,$3,0);
           gen_dstlabel($<ddval>9.lb2);
        }
      }
      perform_after_opt
      perform_statements
      {
        int i;
        struct perf_info *rf;
        /*struct perform_info *rpi;*/
        char *vn;

        /* Check for duplicate variables in VARYING/AFTER */
        if ($12 != NULL) {
           if ((vn = check_perform_variables($3, $12)) != NULL) {
              yyerror("Duplicate variable '%s' in VARYING/AFTER clause", vn);
           }
        }

        if ($1 == 2) {
           if ($12 != NULL) {
              for (i=5; i>=0; i--) {
                 rf = $12->pf[i];
                 if (rf != NULL) {
                    gen_jmplabel(rf->ljmp);
                    gen_dstlabel(rf->lend);
                 }
              }
           }
           gen_jmplabel($<ddval>9.lb1);
           gen_dstlabel($<dval>11);
        }
        else {
           if ($12 != NULL) {
              for (i=5; i>=0; i--) {
                 rf = $12->pf[i];
                 if (rf != NULL) {
                    gen_add(rf->pname1, rf->pname2, 0);
                    gen_jmplabel(rf->ljmp);
                    gen_dstlabel(rf->lend);
                 }
              }
           }
           gen_add($7,$3,0);
           gen_jmplabel($<ddval>9.lb1);
           gen_dstlabel($<dval>11);
        }
      }
      END_PERFORM { $$ = NULL; }
    | label perform_thru_opt
      {
        gen_perform_thru($1,$2);
        $$ = NULL;
      }
    | label perform_thru_opt with_test_opt UNTIL
      {
        $<dval>$=gen_marklabel();
        /* BEFORE=1 AFTER=2 */
        if ($3 == 2) {
        gen_perform_thru($1,$2);
        }
      }
      condition
      {
        unsigned long lbl;
        lbl=gen_orstart();
        /* BEFORE=1 AFTER=2 */
        if ($3 == 1) {
        gen_perform_thru($1,$2);
        }
        gen_jmplabel($<dval>5);
        gen_dstlabel(lbl);
      }
    | label perform_thru_opt gname TIMES
      {
        unsigned long lbl;      
        gen_push_int($3);
        lbl = gen_marklabel();
        gen_perform_test_counter(lbl);
        gen_perform_thru($1,$2);
        gen_perform_times(lbl);
      }
    | label perform_thru_opt with_test_opt VARYING name
      FROM gname by_opt gname UNTIL
      {
        /* 
        Check if initailization of the 'VARYING identifier' is required.
        Initailization of the 'VARYING identifier' is not neccessary if
        it is the same as the 'FROM identifier'.
        */
        if ($7->litflag == '1') {
          gen_move($7,$5);
        }
        else {
          if(strcmp($7->name, $5->name) != 0) {
            gen_move($7,$5);
          }       
        }
        if ($3 == 2) {
           $<ddval>$.lb2=gen_passlabel();
        }
        $<ddval>$.lb1 = gen_marklabel();
      }
      condition
      {
        $<dval>$ = gen_orstart();
        /* BEFORE=1 AFTER=2 */
        if ($3 == 2) {
           gen_add($9,$5, 0);
           gen_dstlabel($<ddval>11.lb2);
        }
      }
      perform_after_opt
      {
        int i;
        struct perf_info *rf;
        /*struct perform_info *rpi;*/
        char *vn = NULL;

        /* Check for duplicate varaibles in VARYING/AFTER */
        if ($14 != NULL) {
           if ((vn = check_perform_variables($5, $14)) != NULL) {
              yyerror("Duplicate variable '%s' in VARYING/AFTER clause", vn);
           }
        }
        gen_perform_thru($1,$2);
        /* BEFORE=1 AFTER=2 */
        if ($3 == 2) {
           if ($14 != NULL) {
              for (i=5; i>=0; i--) {
                 rf = $14->pf[i];
                 if (rf != NULL) {
                    gen_jmplabel(rf->ljmp);
                    gen_dstlabel(rf->lend);
                 }
              }
           }
           gen_jmplabel($<dval>11);
           gen_dstlabel($<dval>13);
        }
        else {
           if ($14 != NULL) {
              for (i=5; i>=0; i--) {
                 rf = $14->pf[i];
                 if (rf != NULL) {
                    gen_add(rf->pname1, rf->pname2, 0);
                    gen_jmplabel(rf->ljmp);
                    gen_dstlabel(rf->lend);
                 }
              }
           }
           gen_add($9,$5,0);
           gen_jmplabel($<dval>11);
           gen_dstlabel($<dval>13);
        }
        $$ = NULL;
      }
    ;

perform_thru_opt: 
    /* nothing */ { $$ = NULL; }
    | THRU label { $$ = $2;}
    ;
with_test_opt: { $<ival>$=1; perform_after_sw=1; }
    | with_opt TEST before_after
      {
       $$=$3;
       perform_after_sw=$3;
      }
    ;
perform_after_opt:   /* nothing */ { $$=NULL; }
    | AFTER perform_after
     {
      $<pfvals>$=create_perform_info();
      $<pfvals>$->pf[0] = $2;
      $$=$<pfvals>$;
     }
    | AFTER perform_after AFTER perform_after
     {
      $<pfvals>$=create_perform_info();
      $<pfvals>$->pf[0] = $2;
      $<pfvals>$->pf[1] = $4;
      $$=$<pfvals>$;
     }
    | AFTER perform_after AFTER perform_after
      AFTER perform_after
     {
      $<pfvals>$=create_perform_info();
      $<pfvals>$->pf[0] = $2;
      $<pfvals>$->pf[1] = $4;
      $<pfvals>$->pf[2] = $6;
      $$=$<pfvals>$;
     }
    | AFTER perform_after AFTER perform_after
      AFTER perform_after AFTER perform_after
     {
      $<pfvals>$=create_perform_info();
      $<pfvals>$->pf[0] = $2;
      $<pfvals>$->pf[1] = $4;
      $<pfvals>$->pf[2] = $6;
      $<pfvals>$->pf[3] = $8;
      $$=$<pfvals>$;
     }
    | AFTER perform_after AFTER perform_after AFTER perform_after
      AFTER perform_after AFTER perform_after
     {
      $<pfvals>$=create_perform_info();
      $<pfvals>$->pf[0] = $2;
      $<pfvals>$->pf[1] = $4;
      $<pfvals>$->pf[2] = $6;
      $<pfvals>$->pf[3] = $8;
      $<pfvals>$->pf[4] = $10;
      $$=$<pfvals>$;
     }
    | AFTER perform_after AFTER perform_after AFTER perform_after
      AFTER perform_after AFTER perform_after AFTER perform_after
     {
      $<pfvals>$=create_perform_info();
      $<pfvals>$->pf[0] = $2;
      $<pfvals>$->pf[1] = $4;
      $<pfvals>$->pf[2] = $6;
      $<pfvals>$->pf[3] = $8;
      $<pfvals>$->pf[4] = $10;
      $<pfvals>$->pf[5] = $12;
      $$=$<pfvals>$;
     }
    ;
perform_after: name FROM gname
    by_opt gname UNTIL
    {
      /* 
      Check if initailization of the 'VARYING identifier' is required.
      Initailization of the 'VARYING identifier' is not neccessary if
      it is the same as the 'FROM identifier'.
      */
      if ($3->litflag == '1') {
        gen_move($3,$1);
      }
      else {
        if(strcmp($3->name, $1->name) != 0) {
          gen_move($3,$1);
        }	
      }
      /* BEFORE=1 AFTER=2 */
      if (perform_after_sw == 2) {
             $<ddval>$.lb2=gen_passlabel();
      }
      $<ddval>$.lb1 = gen_marklabel();
    }
    condition
    {
      unsigned long lbl;
      lbl=gen_orstart();
      /* BEFORE=1 AFTER=2 */
      if (perform_after_sw == 2) {
             gen_add($5,$1,0);
             gen_dstlabel($<ddval>7.lb2);
             $$ = create_perf_info($5, $1, $<ddval>7.lb1, lbl);
      }
      else {
             $$ = create_perf_info($5, $1, $<ddval>7.lb1, lbl);
      }
    }
    ;
perform_statements: {stabs_line();} statement_list
/*
    | { stabs_line(); } CONTINUE 
*/
    ;
before_after:
    BEFORE  { $$=1; }
    | AFTER { $$=2; }
    ;
condition:
    expr  extended_cond_op 
    {
      if ($2 & COND_UNARY) {
              if ($2 & COND_CLASS) {
            gen_class_check($1,$2);
              }
              else {
                struct sym *sy = (struct sym *)save_special_literal('0','9', "%ZEROS%");
                gen_compare($1,$2&~COND_UNARY,sy);
              }
      }
    }
    expr_opt 
    {
      if ($2 & COND_UNARY) {
        if ((int)$4 != -1) {
           yyerror("class or sign conditions are unary");
        }
      }
      else {
        if ((int)$4 == -1) {
           yyerror("expression expected in a binary condition");
        }
        else {
           gen_compare($1,$2,$4);
        }
      }
      $$.sy=$1; /* for implied operands */
      $$.oper=$2;
    }
    | NOT condition { gen_not(); $$=$2; }
    | condition 
      AND 
      { $<dval>$=gen_andstart(); }
      implied_op_condition 
      { gen_dstlabel($<dval>3); $$=$4; }
    | condition 
      OR      
      { $<dval>$=gen_orstart(); }
      implied_op_condition 
      { gen_dstlabel($<dval>3); $$=$4; }
    | '(' condition ')' { $$ = $2; }
    | cond_name 
     {
       /*if ($1->level != 88)
               yyerror("condition unknown");*/
       gen_condition($1);
       $$.sy=NULL;
       $$.oper=0;
     }
    ;
implied_op_condition: 
    condition  { $$ = $1; }
    | cond_op expr  
     {
       if ($<condval>-2.sy == NULL) {
              yyerror("invalid implied condition");
       }
       else {
              gen_compare($<condval>-2.sy,$1,$2);
       }
       $$.sy = $<condval>-2.sy;
       $$.oper = $1;
     }
    | expr            
     { /* implied both the first operand and the operator */
      if (($<condval>-2.sy == NULL)||
              ($<condval>-2.oper & COND_UNARY)) {
             yyerror("invalid implied condition");
      }
      else {
             gen_compare($<condval>-2.sy,$<condval>-2.oper,$1);
      }
      $$.sy = $<condval>-2.sy;
      $$.oper = $<condval>-2.oper;
     }
    ;
sign_condition:
      POSITIVE      { $$=GREATER; }
    | NEGATIVE      { $$=LESS;    }
    | ZERO          { $$=EQUAL;   }
    ;
class_condition:
    NUMERIC                  { $$=CLASS_NUMERIC; }
    | ALPHABETIC_TOK         { $$=CLASS_ALPHABETIC; }
    | ALPHABETIC_LOWER       { $$=CLASS_ALPHABETIC_LOWER; }
    | ALPHABETIC_UPPER       { $$=CLASS_ALPHABETIC_UPPER; }
    ;            
extended_cond_op:
    IS ext_cond               { $$ = $2; }
    | IS NOT ext_cond         { $$ = $3 ^ 7; }
    | IS ext_cond OR ext_cond { $$ = $2 | $4; }
    | ext_cond                { $$ = $1; }
    | NOT is_opt ext_cond     { $$ = $3 ^ 7; }
    | ext_cond OR ext_cond    { $$ = $1 | $3; }
    ;
ext_cond:
    conditional       { $$ = $1; }
    | class_condition { $$ = $1 | COND_UNARY | COND_CLASS; }
    | sign_condition  { $$ = $1 | COND_UNARY; }
    ;
cond_op:
    conditional          { $$ = $1; }
    | NOT conditional    { $$ = $2 ^ 7; }
    | conditional OR conditional { $$ = $1 | $3; }
    ;
conditional:
    CONDITIONAL than_to_opt { $$ = $1; }
    ;
comma_opt: /* nothing */
    | ','
    ;
sep_opt:
    /* nothing */
    | LISTSEP
    ;
/* this token doesn't really exists, but forces look ahead 
   to keep line numbers synchronized with our position
   because we need to generate correct debug stabs */
/*
dummy_opt:
    / nothing /
    | TOKDUMMY
    ;
*/
key_opt:
        /* nothing */
        | KEY
        ;
advancing_opt:
    /* nothing */
    | ADVANCING
    ;
than_to_opt:
    /* nothing */
    | TO { }
    | THAN { }
    ;
record_opt:
    /* nothing */
    | RECORD
    ;
at_opt: /* nothing */
    | AT
    ;
in_opt: /* nothing */
    | IN
    ;
in_of:
    IN
    | OF
    ;
by_opt: /* nothing */
    | BY
    ;
with_opt:
    /* nothing */
    | WITH
    ;
on_opt:
    /* nothing */
    | ON
    ;
gname_opt:
    gname           { $$ = $1; }
    | /* nothing */ { $$ = NULL; }
    ;
to_opt: /* nothing */
    | TO { }
    ;
name_var_list:
      name_var { $$ = gvar_list_append(NULL, $1, source_lineno); }
    | name_var_list sep_opt name_var
      { $$ = gvar_list_append($1, $3, source_lineno); }
    ;
gname_list:
      gname { $$ = gvar_list_append(NULL, $1, source_lineno); }
    | gname_list sep_opt gname
      { $$ = gvar_list_append($1, $3, source_lineno); }
    ;
gname: name {
    /*if (!is_variable($1)) {
         yyerror("The symbol \"%s\" is not an allowed argument here", $1->name);
    }*/
      $$ = $1; }
    | gliteral  { $$ = (struct sym *)$1;}
    | FUNCTION LABELSTR '(' {
                                $2->type = 'f'; /* function type */
                                $<ival>$=CALL;
                        }
                intrinsic_parm_list ')' {
                 $$ = gen_intrinsic_call((struct sym *)$2);
                 }
    | FUNCTION LABELSTR {
            $2->type = 'f'; /* function type */
            $<ival>$=CALL;
            $$ = gen_intrinsic_call((struct sym *)$2);
                 }
    ;
name_or_lit:
    name      { $$ = $1; }
    | literal { $$ = (struct sym *)$1; }
    ;
noallname:
    name      { $$ = $1; }
    | without_all_literal { $$ = (struct sym *)$1; }
    ;
gliteral:
    without_all_literal
    | all_literal
    ;
without_all_literal:
    literal             { $$=$1; }
    | special_literal   { $$=$1; }
    ;
all_literal:
    ALL literal { $2->all=1; $$=$2; }
    | ALL special_literal { $$=$2; }
    ;
special_literal:
    SPACES          { $$=spe_lit_SP; }
    | ZERO          { $$=spe_lit_ZE; }
    | QUOTES        { $$=spe_lit_QU; }
    | HIGHVALUES    { $$=spe_lit_HV; }
    | LOWVALUES     { $$=spe_lit_LV; }
    | NULL_TOK      { $$=spe_lit_ZE; }
    ;
var_or_nliteral:
    variable        { $$ = $1; }
    | nliteral      { $$ = (struct sym *)$1; }
    ;
nliteral:
    signed_nliteral { save_literal($1,'9'); $1->all = 0; $$=$1; }
    ;
literal:
    signed_nliteral { save_literal($1,'9'); $1->all=0; $$=$1; }
    | CLITERAL      { save_literal($1,'X'); $1->all=0; $$=$1; }
    ;
signed_nliteral:
    NLITERAL        { check_decimal_point($1); $$=$1; }
    | '+' NLITERAL  { check_decimal_point($2); $$=$2; }
    | '-' NLITERAL
     {
      check_decimal_point($2);
      invert_literal_sign( $2 );
      $$=$2;
     }
    ;
def_name_opt:
    def_name        { $$ = $1; }
    | /* nothing */ { $$ = NULL; }
    ;
def_name:
    STRING
    {
     if ($1->defined)
         yyerror("variable redefined, %s",$1->name);
     $1->defined=1;
     $$=$1;
    }
    | FILLER    { $<sval>$=alloc_filler(); }
    ;
variable_indexed:
    SUBSCVAR
    {
      if ($1->occurs_flg == 0)
         yyerror("\"%s\" is not an indexed variable ", $1->name);
      $$=$1;
    }
    ;

/*variable:
    VARIABLE {  $$=$1; }
  | VARIABLE in_of subs_var {
            struct sym *v;
                        v=lookup_variable($1,$3);
            if ($$==NULL)
                yyerror("\"%s\" is not child of \"%s\"",$1,$3);
                if ($3->litflag==2) {
                                ((struct vref *)$3)->sym = v;
                                $$ = $3;
                        }
                        else {
                                $$ = v;
                        }
                }
        | LABELSTR { yyerror("%s is not a defined variable",$1->name); }
    ; */
filename:
    literal { $$=(struct sym *)$1; }
    | STRING {$$=$1; }
    ;
data_name:
    literal { $$=(struct sym *)$1; }
    | STRING {$$=$1; }
    ;
cond_name:
    VARCOND '(' {  curr_division = CDIV_SUBSCRIPTS; }
        subscripts  ')' {
                  curr_division = CDIV_PROC;
                  $$ = (struct sym *)create_subscripted_var( $1, $4 );
                    /*check_subscripts($$);*/
            }
    | VARCOND  { $<sval>$=$1; }
    ;
name:
    variable '(' gname ':' gname_opt ')' {
     $$=(struct sym *)create_refmoded_var($1, $3, $5); check_refmods((struct sym *)$$);
     is_var=1;
     }
    | variable { is_var=1; }
    | LABELSTR  { yyerror("Invalid argument expecting variable"); is_var=2; }
    ;
name_var:
      gname {
      if (!is_var)
        yyerror("Invalid argument expecting variable");
      is_var=0;
    }
            ;
/*subs_var:
    variable
    | subscripted_variable
    ;
subscripted_variable:
    SUBSCVAR '(' { curr_division = CDIV_SUBSCRIPTS; }
        subscripts ')' {
                    curr_division = CDIV_PROC;
                    $$ = (struct sym *)create_subscripted_var( $1, $4 );
                      check_subscripts($$);
            }
        | SUBSCVAR in_of subs_var '(' { curr_division = CDIV_SUBSCRIPTS; }
        subscripts ')' {
                    curr_division = CDIV_PROC;
                    $$ = (struct sym *)create_subscripted_var(
                                                lookup_variable($1,$3), $6 );
                      check_subscripts($$);
            }
        ;
*/
variable:
    qualified_var
    {
     $$=$1;
     if (need_subscripts) {
            yyerror("identifier \'%s\' must be subscripted or indexed", $1->name);
            need_subscripts=0;
     }
    }
    | qualified_var LPAR
     { curr_division = CDIV_SUBSCRIPTS; }
     subscripts ')'
     {
       curr_division = CDIV_PROC;
       $$ = (struct sym *)create_subscripted_var( $1, $4 );
                check_subscripts($$);
     }
    ;
qualified_var:
    unqualified_var
    {
      $$=$1;
      if ($1->clone != 0)
      yyerror("identifier \'%s\' must be qualified", $1->name);
    }
    | unqualified_var in_of qualified_var
    {
    $$=lookup_parent($1,$3);
    if ($$ == NULL) {
       yyerror("identifier \'%s\' is not defined in '%s'", $1->name, $3->name);
       $$=$1;
    }
    }
    ;
unqualified_var:
    VARIABLE
     {
      if (($1->defined == 0) && ($1->type == 0))
      {
             yyerror("Undefined variable \'%s\' found", $1->name);
      }
      $$=$1;
     }
    | SUBSCVAR      { need_subscripts=1; $$=$1; }
    ;
subscripts:
    subscript   { $$ = $1; }
    | subscripts comma_opt subscript { $$ = add_subscript( $1, $3 ); }
    ;
subscript:
    gname                   { $$ = create_subscript( $1 ); }
    | subscript '+' gname   { $$ = add_subscript_item( $1, '+', $3 ); }
    | subscript '-' gname   { $$ = add_subscript_item( $1, '-', $3 ); }
    ;
integer:
    signed_nliteral
    {
     char *s;
     $$=0;
     s=$1->name;
     while (isdigit(*s))
       $$ = $$ * 10 + *s++ - '0';
     if (*s)
       yyerror("only integers accepted here");
    }
    ;
label:
    LABELSTR in_of LABELSTR
    {
      struct sym *lab=$1;
      struct sym *sec=$3;
      if (sec->defined == 0) {
          sec->defined = 2;
          sec->parent = NULL;
      } else {
          if ((sec=lookup_label($3,NULL))==NULL) {
                  sec = install($3->name,SYTB_LAB,2);
                  sec->defined=2;
                  sec->parent = NULL;
          }
      }

      if (lab->defined == 0) {
          lab->defined = 2;
          lab->parent = $3;
      } else {
          if ((lab=lookup_label($1,$3))==NULL) {
             lab = install($1->name,SYTB_LAB,2);
             lab->defined=2;
             lab->parent = $3;
          }
      }
      $$ = lab;
    }
    | LABELSTR
    {
     struct sym *lab=$1;
     if (lab->defined == 0) {
                  lab->defined = 2;
                  lab->parent = curr_section;
     }
     else {
                if ((lab=lookup_label(lab,curr_section))==NULL) {
                   lab = install($1->name,SYTB_LAB,2);
                   lab->defined=2;
                   lab->parent = curr_section;
                }
     }
     $$ = lab;
    }
    | NLITERAL {$$=define_label((struct sym *)$1,1,NULL,0);}
    | NLITERAL in_of NLITERAL {$$=define_label((struct sym *)$1,1,(struct sym *)$3,1);}
    | NLITERAL in_of LABELSTR {$$=define_label((struct sym *)$1,1,$3,0);}
    ;
anystring:
    STRING
        | LABELSTR
    ;
%%

/*
**  Yacc auxiliary routines
*/

/* ***********************************************
   * hterror is called where yyerror is normally *
   * called within the parser, but it also passes*
   * an error number and severity.  The error    *
   * number identifies the longer description of *
   * the error message in the compiler document- *
   * ation.  The severity is used to set the     *
   * return code that the compiler will return.  *
   ***********************************************/
void hterror(int erno, int severity, char *s,...)
{
 HTG_temporary_error_code = erno;
 HTG_temporary_severity = severity;

 yyerror(s);

 HTG_temporary_error_code = 256;
 HTG_temporary_severity = 8;
 return;
}

void yywarn(char *s,...)
{
  char buff0[BUFSIZ];
  va_list ap;
  
/*
  va_start (ap, s);
   HTG_temporary_severity = 4;
   yyerror(s);
   va_end(ap);
   HTG_temporary_severity = 8;
*/
  /* Build the error message */
  va_start(ap, s);
  vsprintf (buff0, s, ap);
  va_end (ap);

  HTG_temporary_severity = TCOB_SEVERITY_WARN;
/*  yyerror(s); */
  yyerror(buff0);
  HTG_temporary_severity = TCOB_SEVERITY_ERROR;

}


extern FILE *o_lst;

void yyerror(char *s,...)
{
  char buff1[BUFSIZ], buff2[BUFSIZ];
  const char *label;
  va_list argptr;
  int slen=0;

  /* Determine the type of the error */
  switch (HTG_temporary_severity)
    {
    case TCOB_SEVERITY_INFO:
      label = "info: ";
      break;

    case TCOB_SEVERITY_WARN:
      label = "warning: ";
/*
      if (HTG_RETURN_CODE < 4)
         HTG_RETURN_CODE = 2;
*/
      wrncnt++;
      break;

    case TCOB_SEVERITY_ERROR:
      label = "error: ";
      if (HTG_RETURN_CODE < 8)
       HTG_RETURN_CODE = 8;
      errcnt++;
      break;

    default:
      label = "error: ";
      if (HTG_RETURN_CODE < HTG_temporary_severity)
        HTG_RETURN_CODE = HTG_temporary_severity;
      errcnt++;
      break;
    }
  /* Build the error message */
  va_start(argptr,s);
  vsprintf (buff1, s, argptr);
  va_end (argptr);

  /* Display the error */
  slen = strlen(yytext);
  if (slen != 0) {
     sprintf (buff2, "%s:%6d: %s%s, on or before \'%s\'\n",
           source_filename, source_lineno, label, buff1, yytext);     
  }
  else {
     sprintf (buff2, "%s:%6d: %s%s\n",
           source_filename, source_lineno, label, buff1);          
  }
  fputs (buff2, stderr);
  if (HTG_list_flag)
     fprintf(o_lst, "%s", buff2);
/*    fputs (buff2, o_lst); */

}

void yyerror1(char *s,...)
{
  char buff1[BUFSIZ], buff2[BUFSIZ];
  const char *label;
  va_list argptr;

  /* Determine the type of the error */
  switch (HTG_temporary_severity)
    {
    case TCOB_SEVERITY_INFO:
      label = "info: ";
      break;

    case TCOB_SEVERITY_WARN:
      label = "warning: ";
      if (HTG_RETURN_CODE < 4)
       HTG_RETURN_CODE = 4;
      wrncnt++;
      break;

    case TCOB_SEVERITY_ERROR:
      label = "error: ";
      if (HTG_RETURN_CODE < 8)
       HTG_RETURN_CODE = 8;
      errcnt++;
      break;

    default:
      label = "error: ";
      if (HTG_RETURN_CODE < HTG_temporary_severity)
        HTG_RETURN_CODE = HTG_temporary_severity;
      errcnt++;
      break;
    }
  /* Build the error message */
  va_start(argptr,s);
  vsprintf (buff1, s, argptr);
  va_end (argptr);

  /* Display the error */
  sprintf (buff2, "%s:%6d: %s%s %s\n",
           source_filename, source_lineno, label, buff1, yytext);     
  fputs (buff2, stderr);
  if (HTG_list_flag)
/*    fputs (buff2, o_lst); */
    fprintf(o_lst, "%s", buff2);

}

static void
assert_numeric_sy (struct sym *sy)
{
  if (!is_numeric_sy(sy))
    yyerror("invalid (non numeric) variable or literal \'%s\' used in arithmetic verb", sy->name);
}

static void
assert_numeric_dest_sy (struct sym *sy)
{
  if (!is_numeric_dest_sy(sy))
    yyerror("invalid destination variable \'%s\' used in arithmetic verb", sy->name);
}
