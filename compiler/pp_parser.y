/* 
  Copyright (C) 1999-2004 David Essex
 
  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2, or (at your option)
  any later version.
  
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with this software; see the file COPYING.  If not, write to
  the Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA 02111-1307 USA

  TinyCOBOL pre-processor parser

*/

%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <stdarg.h>
#include <ctype.h>

/*#include "cobpp.h" */
#include "htcoboly.h"
#include "htcoblib.h"
#include "htglobals.h"

/*#define YYDEBUG 1 */
/* #define DEBUG_COBPP_PARSER            1 */

#define yyerror   pp_yyerror

extern unsigned long lineCount;
extern unsigned long columnCount;
extern int copy_state_sw;
extern int copy_start_sw;
extern int replace_state_sw;
extern int replace_start_sw;
extern int identifier_scan_sw;
/*extern char *include_filename; */
extern char *include_cpybook;
extern char *include_cpylib;

extern int  pp_yylex(void);
extern char *pp_yytext;
extern void add_copy_replacement(char *, char *);
extern void add_replace_replacement(char *, char *); 

#ifdef DEBUG_COBPP_PARSER

char erryybuf[1024*8];

void debug_yy_rtn (const char *s1, const char *s2, const char *s3, int sw);

#define DEBUGYY_RTN_STR1(msg1) debug_yy_rtn (msg1, NULL, NULL, 1);
#define DEBUGYY_RTN_STR3(msg1, msg2) debug_yy_rtn (msg1, msg2, NULL, 3);
#define DEBUGYY_RTN_STR15(msg1, msg2, msg3) debug_yy_rtn (msg1, msg2, msg3, 15);

#else

#define DEBUGYY_RTN_STR1(msg1) 
#define DEBUGYY_RTN_STR3(msg1, msg2) 
#define DEBUGYY_RTN_STR15(msg1, msg2, msg3) 

#endif

%}
%union {
    char *str;  /* string */
    int  ival;  /* int */
}

%token <str> TOK_PSEUDO_TEXT TOK_IDENTIFIER TOK_LITERAL TOK_WORD
%token <ival> ERROR YYERROR_VERBOSE

%token TOK_COPY TOK_PERIOD TOK_OFF TOK_BY TOK_OF TOK_IN
%token TOK_REPLACING TOK_REPLACE
%token TOK_MISC TOK_COMMA
%token TOK_SOURCE_COMPUTER TOK_WITH TOK_DEBUGGING TOK_MODE 

%type <str> pseudo_text identifier literal word name library_name_opt replacing_text


%%

root: statements
    | /* nill */
    ;

statements: statement
    | statements statement
    ;

statement: TOK_SOURCE_COMPUTER TOK_PERIOD 
      {
       DEBUGYY_RTN_STR1("yytrace: TOK_SOURCE_COMPUTER TOK_PERIOD\n") 
      } 
      identifier_debug_mode_opt 
      { 
       identifier_scan_sw--; 
      }
    | TOK_COPY 
      {
       DEBUGYY_RTN_STR1("yytrace: TOK_COPY\n") 
      } 
      copy_statement TOK_PERIOD
      { 
       copy_state_sw--;
       copy_start_sw++;
       identifier_scan_sw--;
      }
    | TOK_REPLACE replace_statement TOK_PERIOD
      { 
       replace_state_sw--;  
       replace_start_sw++;
       identifier_scan_sw--;
      }
    | TOK_REPLACE TOK_OFF TOK_PERIOD
      { 
       replace_state_sw--;  
       replace_start_sw--;
       identifier_scan_sw--;
      }
    | TOK_MODE { }
    | TOK_WITH { }
    | error
      {
/*        globalEnvPtr->errFlag = 11; */
        errcnt++;
        return 11; 
      }
    | ERROR
      {
/*        globalEnvPtr->errFlag = 12; */
        errcnt++;
        return 12; 
      }
    | YYERROR_VERBOSE
      {
/*        globalEnvPtr->errFlag = 13; */
        errcnt++;
        return 13; 
      }
    ;

copy_statement: name library_name_opt 
    { 
     /*include_filename = $1; */ 
     include_cpybook  = $1;
     include_cpylib   = $2;
     DEBUGYY_RTN_STR15("yytrace: copy_statement: name=%s, lib=%s;\n", include_cpybook, include_cpylib) 
    }
    TOK_REPLACING replacing_statement
    | name library_name_opt
    { 
     /*include_filename = $1;*/
     include_cpybook  = $1;
     include_cpylib   = $2;
     DEBUGYY_RTN_STR15("yytrace: copy_statement: name=%s, lib=%s;\n", include_cpybook, include_cpylib) 
    }
    ;

replacing_statement: replacing_statements
    | replacing_statements  replacing_statement
    ;

replacing_statements: replacing_text TOK_BY replacing_text comma_delimiter_opt
      {
       add_copy_replacement($1,$3); 
       DEBUGYY_RTN_STR15("yytrace: replacing_statements: \'%s\' BY \'%s\':\n", $1, $3) 
      }
    ;

replacing_text: pseudo_text { $$=$1; }
    | identifier { $$=$1; }
    | literal { $$=$1; }
    | word { $$=$1; }
    ;

library_name_opt: of_in name { $$=$2; }
    | { $$=NULL;  }
    ;

replace_statement: replace_statements
    | replace_statements  replace_statement
    ;

replace_statements: pseudo_text TOK_BY pseudo_text comma_delimiter_opt 
     { 
       add_replace_replacement($1,$3); 
     }
    ;

name: literal { $$=$1; }
    | identifier { $$=$1; }
    ;

pseudo_text: TOK_PSEUDO_TEXT { $$=$1; }
    ;

identifier: TOK_IDENTIFIER 
     { 
       DEBUGYY_RTN_STR3("yytrace: identifier: \'%s\'\n", $1) 
       $$=$1; 
     }
    ;

literal: TOK_LITERAL { $$=$1; }
    ;

word: TOK_WORD { $$=$1; }
    ;

of_in: TOK_OF
    | TOK_IN
    ;

comma_delimiter_opt: TOK_COMMA
    | /* no comma */
    ;

identifier_debug_mode_opt: identifier debugging_mode_opt TOK_PERIOD
     {
      DEBUGYY_RTN_STR1("yytrace: identifier debugging_mode_opt TOK_PERIOD\n") 
     }
    | /* empty */
    ;

debugging_mode_opt: with_opt TOK_DEBUGGING 
     TOK_MODE 
     { 
/*       globalEnv.IncDebugLines = 1;  */
       HTG_debug_lines_flag = TRUE;
       DEBUGYY_RTN_STR1("yytrace: with_opt TOK_DEBUGGING TOK_MODE \n") 
     }
    | /* empty */
    ;

with_opt: TOK_WITH
    | /* no with */
    ;

%%


void pp_yyerror(char *s, ...)
{
  char buf1[PATHMAX3];
  va_list argptr;

  va_start(argptr, s);
  vsprintf (buf1, s, argptr);
  va_end (argptr);

/*  fprintf(stderr, "ini_yyerror(%d, %d): %s\n", lineNum, rowNum, buf1); */
  fprintf(stderr, "htcobolpp: yyerror (%lu, %lu): %s \'%s\'\n", lineCount, columnCount, buf1, pp_yytext);

  /* return 0; */
}

#ifdef DEBUG_COBPP_PARSER

void debug_yy_rtn (const char *s1, const char *s2, const char *s3, int sw)
{
   switch (sw)
   {
     case 3:
       sprintf(erryybuf, s1, s2);
       break;
     
     case 5:
       sprintf(erryybuf, s1, s3);
       break;
     
     case 15:
       sprintf(erryybuf, s1, s2, s3);
       break;
     
     default:
       sprintf(erryybuf, "%s", s1);
       break;
   }
   
   fprintf(stderr, "%s", erryybuf);
}

#endif
