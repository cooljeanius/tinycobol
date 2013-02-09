/* 
 *  Copyright (C) 2002, 2001, 2000, 1999 David Essex
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

%option caseless
/*%option noyywrap*/
%option never-interactive
%option yylineno

%{

/*#undef yywrap*/
#include <stdio.h>
#include <string.h>
#include <assert.h>

/*#include "cobpp.h"*/
#include "htglobals.h"
/* definitions from YACC */
#include "pp_parser.tab.h"  

/* #define DEBUG_COBPP_SCANNER            1 */

#define MAX_COPY_DEPTH                 25

#ifndef YY_READ_BUF_SIZE
#define YY_READ_BUF_SIZE               1024 
/* #define YY_READ_BUF_SIZE               1024 * 8 */
#endif

#define MAX_COPY_DEPTH                 25
#define MAX_CPYNAME_LEN                65
#define MAXLINEBUF                     YY_READ_BUF_SIZE
#define MAXBUF                         1025

#define FIXFORM_6                      6
#define FIXFORM_7                      7
#define FIXFORM_65                     65
#define FIXFORM_71                     71
#define FIXFORM_72                     72
#define FIXFORM_73                     73
#define FIXFORM_81                     81

#define lexchar input

static struct fstack {
        YY_BUFFER_STATE buffer;
        char *filename;
        int lineno;
        struct copy_symbols *last_symbol;
} file_stack[MAX_COPY_DEPTH];
 
static struct copy_symbols {
        struct copy_symbols *next;
        char *value;
        char *replacement;
} *copy_symbols=NULL;
struct copy_symbols *append_copy_symbols=NULL;
struct copy_symbols *append_replace_symbols=NULL;

char *include_cpybook;
char *include_cpylib;

char include_full_filename[MAXBUF];
char toktext[MAXLINEBUF+1];
char ibuf[MAXLINEBUF+1];

/* extern FILE *pp_yylist; */
/* FILE *pp_yylist=NULL; */
extern FILE *o_lst;

static int fsp=0;
int i,j;
unsigned int ret_token;
int copy_state_sw = 0;
int copy_start_sw = 0;
int replace_state_sw = 0;
int replace_start_sw = 0;
int identifier_scan_sw = 0;
int initial_state = 0;
int lf_add = 0;
int quote_sw = 0;
unsigned int columnCount = 0;
static unsigned int lineNumber = 0;
static unsigned int lineNumber_prev = 0;
unsigned int lineCount = 1;
int lineno = 1;
static int zzlineno = 0;
/* static int lineno_prev = 1; */
static int zzlineno_prev = 1;
static int result_prev = 0;
static int fsp_prev = 0;
char *pp_filename=NULL;

void tabExpand(char *s1, char *s2);
/*void lexError( char * msg ); */
char *savename2(const char *s, int x1, int x2);
void adjust_counters(void);

#ifdef DEBUG_COBPP_SCANNER

char errbuf[MAXLINEBUF+1];

void debug_rtn (const char *s, unsigned long Ccnt, unsigned long Lcnt, int Len, const char *s1);
void debug_rtn_sssd (const char *s1, const char *s2, const char *s3, int z, int sw);
void debug_rtn2 (const char *s1, const char *s2, int sw1, int sw2, int sw3, int sw);
void debug_rtn_dump (const char *s, const char *s1, int fsln, int fsi, int gln);

#define DEBUG_RTN(msg) debug_rtn (msg, columnCount, lineCount, yyleng, pp_yytext);
#define DEBUG_RTN1(msg) debug_rtn (msg, columnCount, lineCount, yyleng, pp_yytext+1);
#define DEBUG_RTN_NL(msg) debug_rtn (msg, columnCount, lineCount, yyleng, "<NL>");
#define DEBUG_RTN_DUMP(msg, msg1) debug_rtn_dump (msg, msg1, lineno, fsp, lineCount);
#define DEBUG_RTN_FSP(msg) \
        if (fsp > 0) { \
           debug_rtn_sssd (msg, NULL, NULL, fsp, 7); \
        }
#define DEBUG_RTN_FSP1(msg) debug_rtn_sssd (msg, NULL, NULL, fsp, 7);
#define DEBUG_RTN_STR1(msg) debug_rtn_sssd (msg, NULL, NULL, 0, 1);
#define DEBUG_RTN_STR2(msg1, msg2) debug_rtn_sssd (msg1, msg2, NULL, 0, 3);
#define DEBUG_RTN_STR3(msg1, msg2, msg3) debug_rtn_sssd (msg1, msg2, msg3, 0, 15);
#define DEBUG_RTN_RLIST() \
        for (cs=copy_symbols, i=0; cs != NULL; cs=cs->next, i++) { \
             fprintf(stderr, "lextrace: Replace list (%02d) :%s: by :%s:\n", \
                             i, \
                             cs->value, \
                             cs->replacement); \
        }
#define DEBUG_RTN_RLIST2() \
           for (tmp = append_copy_symbols,i=0; tmp!=NULL; tmp=tmp->next, i++) { \
               fprintf(stderr, "lextrace: dump2 copy_symbols(%d) value=%s replacement=%s\n", \
                      i, \
                      tmp->value, \
                      tmp->replacement  \
                      ); \
           }
#define DEBUG_RTN_RLIST3() \
           for (tmp = file_stack[fsp].last_symbol, i=0; tmp!=NULL; tmp=tmp->next, i++) { \
               fprintf(stderr, "lextrace: dump3(%d) level=%d, value=%s, replacement=%s\n", \
                         i, \
                         fsp, \
                         tmp->value, \
                         tmp->replacement \
                         ); \
           }               
#define DEBUG_RTN_RLIST4() \
       for (tmp = append_copy_symbols, i=0; tmp!=NULL; tmp=tmp->next, i++) { \
    	    fprintf(stderr, "lextrace: add_copy_replacement dump4(%d): value=%s replacement=%s\n", \
    		     i, \
    		     tmp->value, \
    		     tmp->replacement \
    		     ); \
       }
#define DEBUG_RTN_RLIST5() \
       for (tmp = append_copy_symbols, i=0; tmp!=NULL; tmp=tmp->next, i++) { \
    	    fprintf(stderr, "lextrace: add_replace_replacement dump4(%d): value=%s replacement=%s\n", \
    		     i, \
    		     tmp->value, \
    		     tmp->replacement \
    		     ); \
       }
#define DEBUG_RTN_DLIST(msg1, msg2, msg3) debug_rtn_sssd (msg1, msg2, msg3, fsp, 106);
#define DEBUG_RTN_FIXLEN(msg1, zz, msg2) debug_rtn_sssd (msg1, msg2, NULL, zz, 26);


#define DEBUG_RTN_LEX1() \
       for (tmp = copy_symbols, i=0; tmp!=NULL; tmp=tmp->next, i++) { \
           fprintf(stderr, "lextrace: <FREE>{blank}*{eol}  copy_symbols(%d) value=%s replacement=%s\n", \
                   i, \
                   tmp->value, \
                   tmp->replacement  \
                   ); \
       }
#define DEBUG_RTN_LEX2() \
       if (copy_state_sw != 0) { \
           fprintf(stderr,  \
        	   "lextrace: TOK_PSEUDO_TEXT :%s: copy_state_sw=%d\n",  \
        	   pp_yytext, copy_state_sw); \
       } \
       else{ \
           fprintf(stderr,  \
        	   "lextrace: TOK_PSEUDO_TEXT :%s: replace_state_sw=%d\n",  \
        	   pp_yytext, replace_state_sw); \
       }

#define DEBUG_RTN_LEX3(msg1, msg2) debug_rtn2 (msg1, msg2, 0, 0, 0, 3);
#define DEBUG_RTN_LEX15(msg1, msg2, i1) debug_rtn2 (msg1, msg2, i1, 0, 0, 15);
#define DEBUG_RTN_LEX35(msg1, i1, i2) debug_rtn2 (msg1, NULL, i1, i2, 0, 35);
#define DEBUG_RTN_LEX105(msg1, msg2, i1, i2) debug_rtn2 (msg1, msg2, i1, i2, 0, 105);
#define DEBUG_RTN_LEX385(msg1, i1, i2, i3) debug_rtn2 (msg1, NULL, i1, i2, i3, 385);

#else

#define DEBUG_RTN(msg) 
#define DEBUG_RTN0(msg) 
#define DEBUG_RTN1(msg) 
#define DEBUG_RTN_NL(msg) 
#define DEBUG_RTN_DUMP(msg, msg1) 
#define DEBUG_RTN_FSP(msg) 
#define DEBUG_RTN_FSP1(msg) 
#define DEBUG_RTN_STR1(msg)
#define DEBUG_RTN_STR2(msg1, msg2)
#define DEBUG_RTN_STR3(msg1, msg2, msg3)
#define DEBUG_RTN_RLIST() 
#define DEBUG_RTN_DLIST(msg1, msg2, msg3)
#define DEBUG_RTN_RLIST2()
#define DEBUG_RTN_RLIST3()
#define DEBUG_RTN_RLIST4()
#define DEBUG_RTN_RLIST5()
#define DEBUG_RTN_FIXLEN(msg1, zz, msg2)
#define DEBUG_RTN_LEX1() 
#define DEBUG_RTN_LEX2() 
#define DEBUG_RTN_LEX3(msg1, msg2) 
#define DEBUG_RTN_LEX15(msg1, msg2, i1)
#define DEBUG_RTN_LEX35(msg1, i1, i2) 
#define DEBUG_RTN_LEX105(msg1, msg2, i1, i2) 
#define DEBUG_RTN_LEX385(msg1, i1, i2, i3) 

#endif

void pp_setup_scanner_state(void);
void set_scanner_state(int i0, int i1);

void copy_switch(void);
/* void copy_do_replacements(char *buffer); */
void do_copy_replacements(char *buffer);
void do_replace_replacements(char *buffer);
int lex_fgets(char *buf, int maxsize);


#define YY_INPUT(buf,result,max_size) \
        { \
           result = pp_lex_fgets( buf, max_size ); \
        }

%}

cr           [\r]
lf           [\n]
eol          {lf}
tab          [\t]
blank        [ ]
Quote        ['"]
NoQuoteEol   [^'"\n]
NoSQuoteEol  [^'\n]
NoDQuoteEol  [^"\n]
NoDQuote     [^"]
DQuote       \"
SQuote       \'
ws           [ \n]
Period       \.
Comma        [,]
Alpha        [A-Za-z]
AlphaNum     [A-Za-z0-9\-]
Numeric      [0-9]
AnyNoDQuote  [^"\t\n]
AnyNoSQuote  [^'\t\n]
EqSign       [=]
EqSign2      "=="
NoEqSign     [^\n=]
NoEqSign2    [^\n=]/[^\n=]
invalid7     [^*/D$ \n]

%x FREE FIXED_7 FIXED_AB COMMENT DQ_LITERAL_FIXED DQ_LITERAL_FREE SQ_LITERAL_FIXED SQ_LITERAL_FREE PSEUDO_TEXT COMMENT_ENTRY

%%

%{
      struct copy_symbols *tmp=NULL;
%}


<FIXED_7,FREE>{

  "*>" |
  ^"$" |
  ^"/" |
  ^"*" { 

        DEBUG_RTN ("^* ^/ ^$ *>")

        columnCount = columnCount + yyleng;
        BEGIN(COMMENT);
  }
}

<FREE>{ 
  
  ^"D " { 
        
        DEBUG_RTN ("D ")

        columnCount = columnCount + yyleng;
/*        if (globalEnvPtr->IncDebugLines == 0) {*/
        if(HTG_debug_lines_flag == FALSE) {
           BEGIN(COMMENT);
        }
        else {
           fprintf(pp_yyout, "  ");
        } 
  }
  ^"-" { 
        
        DEBUG_RTN ("-")

        columnCount = columnCount + yyleng;
        fprintf(pp_yyout, " ");
  }
}

<FIXED_AB,FREE>{

  COPY {

        DEBUG_RTN ("COPY")

        columnCount = columnCount + yyleng;
        copy_state_sw++;
        identifier_scan_sw++;

        DEBUG_RTN_LEX35("lextrace: TOK_COPY=%d, copy_state_sw=%d;\n", TOK_COPY, copy_state_sw)

        return TOK_COPY;
  }

  OF {

        DEBUG_RTN ("OF")

        columnCount = columnCount + yyleng;

        DEBUG_RTN_LEX35("lextrace: TOK_OF=%d, copy_state_sw=%d;\n", TOK_OF, copy_state_sw) 

        if (copy_state_sw != 0) {
            return TOK_OF;
        }
        else {
            ECHO;
        }
  }

  OFF {

        DEBUG_RTN ("OFF")

        columnCount = columnCount + yyleng;

        DEBUG_RTN_LEX35("lextrace: TOK_OFF=%d, replace_state_sw=%d;\n", TOK_OFF, replace_state_sw)

        if (replace_state_sw != 0) {
            return TOK_OFF;
        }
        else {
            ECHO;
        }
  }

  IN {

        DEBUG_RTN ("IN")

        columnCount = columnCount + yyleng;

        DEBUG_RTN_LEX35("lextrace: TOK_IN=%d, copy_state_sw=%d;\n", TOK_IN, copy_state_sw) 

        if (copy_state_sw != 0) {
            return TOK_IN;
        }
        else {
            ECHO;
        }
  }

  BY {

        DEBUG_RTN ("BY")

        columnCount = columnCount + yyleng;

        DEBUG_RTN_LEX385("lextrace: TOK_BY=%d, copy_state_sw=%d, replace_state_sw=%d;\n" , TOK_BY, copy_state_sw, replace_state_sw)

        if ((copy_state_sw != 0) || (replace_state_sw != 0)) {
            return TOK_BY;
        }
        else {
            ECHO;
        }
  }

  REPLACE {

        DEBUG_RTN ("REPLACE")

        columnCount = columnCount + yyleng;
        replace_state_sw++;
        identifier_scan_sw++;

        DEBUG_RTN_LEX35("lextrace: TOK_REPLACE=%d, replace_state_sw=%d;\n", TOK_REPLACE, replace_state_sw)

        return TOK_REPLACE;
  }

  REPLACING {

        DEBUG_RTN ("REPLACING")

        columnCount = columnCount + yyleng;

        DEBUG_RTN_LEX35("lextrace: TOK_REPLACING=%d, copy_state_sw=%d;\n", TOK_REPLACING, copy_state_sw)

        if (copy_state_sw != 0) {
            return TOK_REPLACING;
        }
        else {
            ECHO;
        }
  }

  SOURCE\-COMPUTER {

        DEBUG_RTN ("SOURCE-COMPUTER")

        identifier_scan_sw++; 
        columnCount = columnCount + yyleng;
        ECHO;
        return TOK_SOURCE_COMPUTER;
  }

  ^{blank}{0,4}AUTHOR{blank}*{Period} {

        DEBUG_RTN ("^{blank}{0,4}AUTHOR{blank}*{Period}")

        columnCount = columnCount + yyleng;
        /* ECHO; */
        BEGIN(COMMENT_ENTRY);
  }

  {blank}{0,4}INSTALLATION{blank}*{Period} {
        
        DEBUG_RTN ("^{blank}{0,4}INSTALLATION{blank}*{Period}")

        columnCount = columnCount + yyleng;
        /* ECHO; */
        BEGIN(COMMENT_ENTRY);
  }

  {blank}{0,4}DATE\-WRITTEN{blank}*{Period} {

        DEBUG_RTN ("^{blank}{0,4}DATE-WRITTEN{blank}*{Period}")

        columnCount = columnCount + yyleng;
        /* ECHO; */
        BEGIN(COMMENT_ENTRY);
  }

  {blank}{0,4}DATE\-COMPILED{blank}*{Period} {

        DEBUG_RTN ("^{blank}{0,4}DATE-COMPILED{blank}*{Period}")

        columnCount = columnCount + yyleng;
        /* ECHO; */
        BEGIN(COMMENT_ENTRY);
  }

  {blank}{0,4}SECURITY{blank}*{Period} {

        DEBUG_RTN ("^{blank}{0,4}SECURITY{blank}*{Period}")

        columnCount = columnCount + yyleng;
        /* ECHO; */
        BEGIN(COMMENT_ENTRY);
  }

  WITH {

        DEBUG_RTN ("WITH")

        columnCount = columnCount + yyleng;
        ECHO;
        return TOK_WITH;
  }

  DEBUGGING/{blank}{0,40}MODE {

        DEBUG_RTN ("DEBUGGING")

        columnCount = columnCount + yyleng;
        ECHO;
        return TOK_DEBUGGING;
  }

  MODE {

        DEBUG_RTN ("MODE")

        columnCount = columnCount + yyleng;
        ECHO;
        return TOK_MODE;
  }

  {blank}+   {
        
        DEBUG_RTN ("{blank}+")
        
        columnCount = columnCount + yyleng;
        ECHO; 
  }

  {DQuote} {

        DEBUG_RTN ("{DQuote}")

        columnCount++;
        quote_sw = 2;
        if (copy_state_sw != 0) {
           strncpy(toktext, pp_yytext, MAXBUF);   
        }
        else {
           ECHO; 
        }
        set_scanner_state(DQ_LITERAL_FIXED, DQ_LITERAL_FREE);
  }

  {SQuote} {

        DEBUG_RTN ("{SQuote}")

        columnCount++;
        quote_sw = 1;
        if (copy_state_sw != 0) {
           strncpy(toktext, pp_yytext, MAXBUF);   
        }
        else {
           ECHO; 
        }
        set_scanner_state(SQ_LITERAL_FIXED, SQ_LITERAL_FREE);
  }

  {Numeric}{1,18} {

        DEBUG_RTN ("{Numeric}")

        columnCount = columnCount + yyleng;
        if (copy_state_sw != 0) {
           strncpy(toktext, pp_yytext, MAXBUF);   
           pp_yylval.str = savename2(toktext, 0, 0);
           return(TOK_LITERAL);
        }
        else {
           ECHO; 
        }

  }

  {EqSign2}  {
  
        DEBUG_RTN ("{EqSign2}")

        columnCount = columnCount + yyleng;
        if ((copy_state_sw != 0) || (replace_state_sw != 0)) {

           DEBUG_RTN_LEX2() 

           strncpy(toktext, pp_yytext, MAXBUF);   
           /*pp_yylval.str = savename2(toktext, 2, 2);*/
           /*return(TOK_PSEUDO_TEXT);*/
           BEGIN(PSEUDO_TEXT);
        }
        else {
           ECHO; 
        }
  }

  {Period}/[ \n]  {

         DEBUG_RTN ("{Period}")

         columnCount++;
         /*if ((copy_state_sw != 0) || (replace_state_sw != 0) || (identifier_scan_sw != 0)) {*/
         if ((copy_state_sw != 0) || (replace_state_sw != 0)) {
            return(TOK_PERIOD);
         }
         else {
           ECHO; 
           if (identifier_scan_sw != 0) {
              return(TOK_PERIOD);
           }
         }
  }

  ({AlphaNum}*{Alpha}+{AlphaNum}*){1,30} {

        DEBUG_RTN ("({AlphaNum}*{Alpha}+{AlphaNum}*){1,30}") 

        columnCount = columnCount + yyleng;

        if (identifier_scan_sw != 0) {

           DEBUG_RTN_LEX15("lextrace: TOK_IDENTIFIER :%s: identifier_scan_sw=%d\n", pp_yytext, identifier_scan_sw)


           strncpy(toktext, pp_yytext, MAXBUF);   
           pp_yylval.str = savename2(toktext, 0, 0);
        }
        
        if ((copy_state_sw != 0) || (replace_state_sw != 0)) {
           return(TOK_IDENTIFIER);
        }
        else {
           ECHO; 
           if (identifier_scan_sw != 0) {
              return(TOK_IDENTIFIER);
           }
        }

  } 

  {Comma} {

        DEBUG_RTN ("COMMA")

        columnCount = columnCount + yyleng;

        DEBUG_RTN_LEX35("lextrace: TOK_IN=%d, copy_state_sw=%d;\n", TOK_COMMA, copy_state_sw)

        if (copy_state_sw != 0) {
            return TOK_COMMA;
        }
        else {
            ECHO;
        }
  } 

  "*>" {
        
        DEBUG_RTN ("*>")
        
        columnCount = columnCount + yyleng; 
        /* comment line remove */ 
        BEGIN(COMMENT);
  }

  . { 
        
        DEBUG_RTN (".")
        
        columnCount++;
         if ((copy_state_sw != 0) || (replace_state_sw != 0)) {
            return(0);
         }
         else {
            ECHO;
         }
  }        

}

<COMMENT_ENTRY>{

  "*>" |
  ^"*" { 

        DEBUG_RTN ("^* *>")

        columnCount = columnCount + yyleng;
        BEGIN(COMMENT);
  }

  {blank}{0,4}REMARKS{blank}*{Period} {
              
        DEBUG_RTN ("{blank}{0,4}REMARKS{blank}*{Period}")

        columnCount = columnCount + yyleng;
        ECHO;
        set_scanner_state(FIXED_AB, FREE);
  }

  {blank}{0,4}ENVIRONMENT{blank}+DIVISION{blank}*{Period} {
              
        DEBUG_RTN ("{blank}{0,4}ENVIRONMENT{blank}+DIVISION{blank}*{Period}")

        columnCount = columnCount + yyleng;
        ECHO;
        set_scanner_state(FIXED_AB, FREE);
  }

  {blank}{0,4}CONFIGURATION{blank}+SECTION{blank}*{Period} {
              
        DEBUG_RTN ("")

        columnCount = columnCount + yyleng;
        ECHO;
        set_scanner_state(FIXED_AB, FREE);
  }

  {blank}{0,4}INPUT\-OUTPUT{blank}+SECTION{blank}*{Period} {
              
        DEBUG_RTN ("{blank}{0,4}INPUT-OUTPUT{blank}+SECTION{blank}*{Period}")

        columnCount = columnCount + yyleng;
        ECHO;
        set_scanner_state(FIXED_AB, FREE);
  }

  {blank}{0,4}DATA{blank}+DIVISION{blank}*{Period} {

        DEBUG_RTN ("{blank}{0,4}DATA{blank}+DIVISION{blank}*{Period}")

        columnCount = columnCount + yyleng;
        ECHO;
        set_scanner_state(FIXED_AB, FREE);
  }

  {blank}{0,4}FILE{blank}+SECTION{blank}*{Period} {
              
        DEBUG_RTN ("{blank}{0,4}FILE{blank}+SECTION{blank}*{Period}")

        columnCount = columnCount + yyleng;
        ECHO;
        set_scanner_state(FIXED_AB, FREE);
  }

  {blank}{0,4}WORKING\-STORAGE{blank}+SECTION{blank}*{Period} {
              
        DEBUG_RTN ("{blank}{0,4}WORKING-STORAGE{blank}+SECTION{blank}*{Period}")

        columnCount = columnCount + yyleng;
        ECHO;
        set_scanner_state(FIXED_AB, FREE);
  }

  {blank}{0,4}LINKAGE{blank}+SECTION{blank}*{Period} {
              
        DEBUG_RTN ("{blank}{0,4}LINKAGE{blank}+SECTION{blank}*{Period}")

        columnCount = columnCount + yyleng;
        ECHO;
        set_scanner_state(FIXED_AB, FREE);
  }

  {blank}{0,4}COMMUNICATION{blank}+SECTION{blank}*{Period} {
              
        DEBUG_RTN ("{blank}{0,4}COMMUNICATION{blank}+SECTION{blank}*{Period}")

        columnCount = columnCount + yyleng;
        ECHO;
        set_scanner_state(FIXED_AB, FREE);
  }

  {blank}{0,4}REPORT{blank}+SECTION{blank}*{Period} {
              
        DEBUG_RTN ("{blank}{0,4}REPORT{blank}+SECTION{blank}*{Period}")

        columnCount = columnCount + yyleng;
        ECHO;
        set_scanner_state(FIXED_AB, FREE);
  }

  {blank}{0,4}SCREEN{blank}+SECTION{blank}*{Period} {
              
        DEBUG_RTN ("{blank}{0,4}SCREEN{blank}+SECTION{blank}*{Period}")

        columnCount = columnCount + yyleng;
        ECHO;
        set_scanner_state(FIXED_AB, FREE);
  }

  {blank}{0,4}PROCEDURE{blank}+DIVISION{blank}*{Period} {

        DEBUG_RTN ("{blank}{0,4}PROCEDURE{blank}+DIVISION{blank}*{Period}")

        columnCount = columnCount + yyleng;
        ECHO;
        set_scanner_state(FIXED_AB, FREE);
  }
  
  {eol} { 

        DEBUG_RTN_NL ("{eol}")

        lineno++;
        lineCount++;
        columnCount=7; 
        ECHO;
  }
  
  . { 
        
        DEBUG_RTN (".")
        
        columnCount++;
  }        
}
        
<FIXED_AB>{
  {blank}*{eol}"-"{blank}{4,65} { 
        
        DEBUG_RTN1 ("{blank}*{eol}-{blank}{4,65}")
        
        /* Continuation line remove */ 
        lineno++;
        lineCount++;
        columnCount = yyleng - 1; 
        lf_add++; 
  }

  {blank}*{eol} { 

        DEBUG_RTN_NL ("{blank}*{eol}")

        lineno++;
        lineCount++;
        columnCount=7; 
        /*ECHO; */
        fprintf(pp_yyout, "\n"); 

        DEBUG_RTN_LEX385("debug FIXED_AB - {blank}*{eol}(%lu,%lu): lf_add=%d,\n", lineCount, columnCount, lf_add)

        for (i=0; i<lf_add; i++) {
            fprintf(pp_yyout, "\n"); 
        }
        lf_add=0;
        
        if (copy_start_sw != 0) {
            copy_switch();
        } 
        
        BEGIN(FIXED_7);
  }
}

<FREE>{blank}*{eol}  { 
        
        DEBUG_RTN_NL ("{blank}*{eol}")
        
        lineno++;
        lineCount++;
        columnCount=0; 
        /*ECHO; */
        fprintf(pp_yyout, "\n"); 

        for (i=0; i<lf_add; i++) {
            fprintf(pp_yyout, "\n"); 
        }
        lf_add=0;
        
        if (copy_start_sw != 0) {

            DEBUG_RTN_LEX1() 

            copy_switch();
        } 
}

<FIXED_7>{ 

  "D" { 
        
        DEBUG_RTN ("D")

        columnCount++;
/*        if (globalEnvPtr->IncDebugLines == 0) { */
        if(HTG_debug_lines_flag == FALSE) {
           BEGIN(COMMENT);			
        }
        else {
           fprintf(pp_yyout, " ");
           BEGIN(FIXED_AB);
        } 
  }

  {blank} { 

        DEBUG_RTN ("{blank}")

        columnCount = columnCount + yyleng;
        ECHO;
        BEGIN(FIXED_AB);
  }

  {invalid7} { 

        DEBUG_RTN ("{invalid7}")

/*	globalEnvPtr->errFlag++; */
        errcnt++;
	fprintf(stderr,
		 "%s:%d:(3) Invaild character (%c) in column %d.\n",
	         pp_filename,
	         lineCount,
	         pp_yytext[0],
	         columnCount
	        );

        columnCount = columnCount + yyleng;
        BEGIN(COMMENT);			
  }

  {eol} { 

        DEBUG_RTN_NL ("{eol}")

        lineno++;
        lineCount++;
        columnCount=7; 
        ECHO;

        DEBUG_RTN_LEX385("debug FIXED_7 - {eol}(%lu,%lu): lf_add=%d,\n", lineCount, columnCount, lf_add)

        for (i=0; i<lf_add; i++) {
            fprintf(pp_yyout, "\n"); 
        }
        lf_add=0;
        
        if (copy_start_sw != 0) {
            copy_switch();
        } 
        
        BEGIN(FIXED_7);
  }
}

<PSEUDO_TEXT>{

  [^\n=]+ {

        DEBUG_RTN ("[^<NL>=]+")

        columnCount = columnCount + yyleng;

        DEBUG_RTN_LEX2() 

        strncat(toktext, pp_yytext, MAXBUF);   
  }

  {EqSign}/[^\n=]+ {

        DEBUG_RTN ("{EqSign}/[^<NL>=]+")

        columnCount = columnCount + yyleng;

        DEBUG_RTN_LEX2() 

        strncat(toktext, pp_yytext, MAXBUF);   
  }

  {EqSign2}  {
  
        DEBUG_RTN ("{EqSign2}")

        columnCount = columnCount + yyleng;

        DEBUG_RTN_LEX2() 

        strncat(toktext, pp_yytext, MAXBUF);   
        pp_yylval.str = savename2(toktext, 2, 2);
        set_scanner_state(FIXED_AB, FREE);
        return(TOK_PSEUDO_TEXT);
  }

  {eol}"-"{blank}{4,65}{DQuote} { 
        
        DEBUG_RTN1 ("{eol}-{blank}{4,65}{DQuote}")
        
        /* Continuation line remove */ 
        /* lineno_prev = lineno; */ 
        /* yylineno_prev = lineNumber; */ 
        lineno++;
        lineCount++;
        columnCount = yyleng - 1; 
        lf_add++; 
        /*BEGIN(DQ_LITERAL_FIXED); */
  }

}

<DQ_LITERAL_FIXED,DQ_LITERAL_FREE>{

  {DQuote}{blank}*{eol}?{blank}*"&"{blank}*{eol}?{blank}*{DQuote} { 
        
        DEBUG_RTN ("{DQuote}{blank}*{eol}?{blank}*&{blank}*{eol}?{blank}*{DQuote}")
        
        adjust_counters();
  }

  {eol}"-"{blank}{4,65}{DQuote} { 
        
        DEBUG_RTN1 ("{eol}-{blank}{4,65}{DQuote}")
        
        /* Continuation line remove */ 
        /* lineno_prev = lineno; */ 
        /* yylineno_prev = lineNumber; */ 
        lineno++;
        lineCount++;
        columnCount = yyleng - 1; 
        lf_add++; 
        /*BEGIN(DQ_LITERAL_FIXED); */
  }

  \"/[^"] {

        DEBUG_RTN ("{DQuote}/{NoDQuote}")

        columnCount = columnCount + yyleng;

        DEBUG_RTN_LEX105("lextrace: DQuote :%s: copy_state_sw=%d, quote_sw=%d\n", pp_yytext, copy_state_sw, quote_sw)

        if (copy_state_sw != 0) {
           strcat(toktext, pp_yytext);   
           /* pp_yylval.str = savename2(toktext, 1, 1); */
           pp_yylval.str = savename2(toktext, 0, 0);
           quote_sw = 0;
           set_scanner_state(FIXED_AB, FREE);
           return(TOK_LITERAL);
        }
        else {
           ECHO; 
           quote_sw = 0;
           set_scanner_state(FIXED_AB, FREE);
        }
  }

  {DQuote}{2} {

        DEBUG_RTN ("{DQuote}{2}")

        columnCount = columnCount + yyleng;

        if (copy_state_sw != 0) {
           strcat(toktext, pp_yytext);
        }
        else {
           ECHO; 
        }

  }

  {DQuote} {

        DEBUG_RTN ("{DQuote}")

        columnCount = columnCount + yyleng;

        DEBUG_RTN_LEX105("lextrace: SQuote :%s: copy_state_sw=%d, quote_sw=%d\n", pp_yytext, copy_state_sw, quote_sw)

        if (copy_state_sw != 0) {
           strcat(toktext, pp_yytext);
           if (quote_sw == 1) {
               /* pp_yylval.str = savename2(toktext, 1, 1); */
               pp_yylval.str = savename2(toktext, 0, 0);
               quote_sw = 0;
               set_scanner_state(FIXED_AB, FREE);
               return(TOK_LITERAL);
           }
        }
        else {
           ECHO; 
           if (quote_sw == 1) {
              quote_sw = 0;
              set_scanner_state(FIXED_AB, FREE);
           }
        }
  }

  {NoDQuoteEol}+ {

        DEBUG_RTN ("{NoQuoteEol}+")

        /*columnCount++;*/
        columnCount = columnCount + yyleng;

        if (copy_state_sw != 0) {
           strcat(toktext, pp_yytext);
        }
        else {
           ECHO; 
        }

  }

  {eol} {

        DEBUG_RTN ("{eol}")

        columnCount=0;
        lineCount++; 
        lineno++;

        if (copy_state_sw != 0) {

           DEBUG_RTN_LEX15("lextrace: TOK_LITERAL :%s: copy_state_sw=%d\n", pp_yytext, copy_state_sw)

        }
        else {
           set_scanner_state(FIXED_7, FREE);
        }
  }

}        
           
<SQ_LITERAL_FIXED,SQ_LITERAL_FREE>{

  {SQuote}{blank}*{eol}?{blank}*"&"{blank}*{eol}?{blank}*{SQuote} { 
        
        DEBUG_RTN ("{SQuote}{blank}*{eol}?{blank}*&{blank}*{eol}?{blank}*{SQuote}")
        
        adjust_counters();
  }

  {eol}"-"{blank}{4,65}{SQuote} { 
        
        DEBUG_RTN1 ("{eol}-{blank}{4,65}{SQuote}")
        
        /* Continuation line remove */ 
        /* lineno_prev = lineno;  */ 
        /* yylineno_prev = lineNumber; */ 
        lineno++;
        lineCount++;
        columnCount = yyleng - 1; 
        lf_add++; 
        /* BEGIN(SQ_LITERAL_FIXED); */
  }

  \'/[^'] {

        DEBUG_RTN ("{SQuote}/{NoSQuote}")

        columnCount = columnCount + yyleng;

        DEBUG_RTN_LEX105("lextrace: SQuote :%s: copy_state_sw=%d, quote_sw=%d\n", pp_yytext, copy_state_sw, quote_sw)

        if (copy_state_sw != 0) {
           strcat(toktext, pp_yytext);   
           /* pp_yylval.str = savename2(toktext, 1, 1); */
           pp_yylval.str = savename2(toktext, 0, 0);
           quote_sw = 0;
           set_scanner_state(FIXED_AB, FREE);
           return(TOK_LITERAL);
        }
        else {
           ECHO; 
           quote_sw = 0;
           set_scanner_state(FIXED_AB, FREE);
        }
  }

  {SQuote}{2} {

        DEBUG_RTN ("{SQuote}{2}")

        columnCount = columnCount + yyleng;

        if (copy_state_sw != 0) {
           strcat(toktext, pp_yytext);
        }
        else {
           ECHO; 
        }

  }

  {SQuote} {

        DEBUG_RTN ("{SQuote}")

        columnCount = columnCount + yyleng;

        DEBUG_RTN_LEX105("lextrace: SQuote :%s: copy_state_sw=%d, quote_sw=%d\n", pp_yytext, copy_state_sw, quote_sw)

        if (copy_state_sw != 0) {
           strcat(toktext, pp_yytext);
           if (quote_sw == 1) {
               /* pp_yylval.str = savename2(toktext, 1, 1); */
               pp_yylval.str = savename2(toktext, 0, 0);
               quote_sw = 0;
               set_scanner_state(FIXED_AB, FREE);
               return(TOK_LITERAL);
           }
        }
        else {
           ECHO; 
           if (quote_sw == 1) {
              quote_sw = 0;
              set_scanner_state(FIXED_AB, FREE);
           }
        }
  }

  {NoSQuoteEol}+ {

        DEBUG_RTN ("{NoSQuoteEol}+")

        columnCount = columnCount + yyleng;

        if (copy_state_sw != 0) {
           strcat(toktext, pp_yytext);
        }
        else {
           ECHO; 
        }

  }

  {eol} {

        DEBUG_RTN ("{eol}")

        columnCount=0;
        lineCount++; 
        lineno++;

        if (copy_state_sw != 0) {

           DEBUG_RTN_LEX15("lextrace: TOK_LITERAL :%s: copy_state_sw=%d\n", pp_yytext, copy_state_sw)

        }
        else {
           set_scanner_state(FIXED_7, FREE);
        }
  }

}        
           
<COMMENT>{ 
  
  .+ { 
        
        DEBUG_RTN (".+")
        
        columnCount = columnCount + yyleng;
  }

  {eol} { 
        
        DEBUG_RTN_NL ("COMMENT - {eol} ")
        
        lineno++;
        lineCount++;
        columnCount=0; 
        ECHO;
        set_scanner_state(FIXED_7, FREE);
  }
}

<<EOF>> {
        struct copy_symbols *cs=NULL,*cs1=NULL;
        if (fsp == 0) {

           DEBUG_RTN_FSP1("lextrace: receiving <<EOF>> for fsp = %d:\n") 

           yyterminate();
        }
        else {
/*
//            tmp = lineno;
//            yy_delete_buffer( YY_CURRENT_BUFFER );
//            yy_switch_to_buffer( file_stack[fsp].buffer );
//            lineno = file_stack[ fsp  ].line;
*/
           /* free all replacements in this dead context */

           DEBUG_RTN_FSP1("lextrace: begin delete fsp = %d:\n") 

           cs1 = file_stack[fsp].last_symbol;
           cs = copy_symbols;
           if (cs == cs1)
           	   copy_symbols = NULL;
           while (cs) {
           	   if (cs->next == cs1)
           		   break;
           	   cs = cs->next;
           }
           if (cs)
              cs->next = NULL; 
           if (cs1) {
               while (cs1) {

                  DEBUG_RTN_DLIST("lextrace: delete fsp=%d, value=%s, replacement=%s:\n", cs1->value, cs1->replacement)

                  if (cs1->value) free( cs1->value );
                  if (cs1->replacement) free( cs1->replacement );
                  cs = cs1->next;
                  cs1->next = NULL;
                  free( cs1 );
                  cs1 = cs;
                  cs = NULL;
               }
           }
           yy_delete_buffer( YY_CURRENT_BUFFER );
           fsp--;
           yy_switch_to_buffer( file_stack[fsp].buffer );
	   if (pp_filename) { free (pp_filename); pp_filename=NULL;}
           pp_filename = file_stack[fsp].filename;
           lineno   = file_stack[fsp].lineno;
           zzlineno = file_stack[fsp].lineno;
           fprintf (pp_yyout, "# %d \"%s\"\n", lineno, pp_filename); 

        }
}

%%


/* Expand tabs to spaces */
void tabExpand(char *s1, char *s2) {
  int i, j, k, y, len, sw=0;
  char delm = '0';
  
  len = strlen(s2);
  
  for (i=0, j=0; i<len; i++) {
     if ((s2[i] == '\'') || (s2[i] == '"')) {
        if (sw == 0) {
           sw = 1;
           delm = s2[i];
        }
        else {
           if (s2[i] == delm) {
              sw = 0;
              delm = '0';
           }
        }       
     }
     if ((s2[i] == '\t') && (sw == 0)) { 
/*       k = ( globalEnvPtr->tab2space * ((j/globalEnvPtr->tab2space) + 1)) - j; */
        k = ( HTG_tab2space * ((j/HTG_tab2space) + 1)) - j;
        y = j + k;
        for (j=j; j<y; j++) {
            s1[j] = ' '; 
        }
     }
     else {
        s1[j] = s2[i];
        j++; 
     }
  }
  s1[j] = CHR_EOS;

}
/*
void lexError( char * msg ) {

        (void)fprintf(stderr,
                "%s:%d: %s\n"
                ,pp_filename
                ,lineCount
                ,msg
        );
//        globalEnvPtr->errFlag++; 
        errcnt++;
        return;
}
*/

int yywrap(void) {
/* 
// yywrap will be called to open files from the List of Files in the
// Global Env struct.
//
*/
   return 1;
}


char *savename2(const char *s, int x1, int x2) {
  char *ap=NULL, *s1;
  int len;

  len = strlen(s);
  len = len - x1 - x2;
  
  if (len > 0) {    
     ap = (char *) malloc(len + 1);
     if (ap != NULL) {
        strncpy(ap, s + x1, len);
        s1 = ap + len;
        *s1 = '\0';

        DEBUG_RTN_LEX3("lextrace: savename2 :%s:\n", ap)
     }
  }
  return(ap);
}

int pp_lex_fgets(char *buf, int maxsize) {
        int result, len;
        char *s;
/*      char ibuf[MAXLINEBUF]; */
/*        char ibuf[YY_READ_BUF_SIZE]; */

        if ((o_lst != NULL) && (lineNumber > 0) && (result_prev != YY_NULL)) { 
           fprintf(o_lst, "%6d %6d [%02d]: %s", lineNumber_prev, zzlineno_prev, fsp_prev, ibuf); 
           fflush(o_lst);
           len = strlen(ibuf);
/*
//           if (len > 0) {
//             fprintf(o_lst, "%6d %6d : %s", yylineno_prev, lineno_prev, ibuf); 
//              if (copy_state_sw != 0) {
//  //                fprintf(o_lst, "%6d %6d * %s", lineCount - 1, lineno_prev, ibuf);              
//                  fprintf(o_lst, "%6d %6d * %s", yylineno_prev, lineno_prev, ibuf);              
//               }
//               else {
//                  fprintf(o_lst, "%6d %6d : %s", yylineno_prev, lineno_prev, ibuf); 
// //                 fprintf(o_lst, "%6d %6d : %s", lineCount - 1, lineno_prev, ibuf); 
// //               fprintf(o_lst, "%06d : %s", lineNumber - 1, ibuf);
//               }
//           }
*/
        }

        s = fgets(buf, maxsize, pp_yyin);
/*        lineNumber++; */

        if (s == NULL) {
/*           strcpy(ibuf, "\n"); */
           strcpy(ibuf, "");
           /* lineno_prev = lineno; */
           zzlineno_prev = zzlineno;
           lineNumber_prev = lineNumber;
           fsp_prev = fsp; 
           result_prev = YY_NULL;
           result = YY_NULL;
           return result;
        }

        result = strlen(s);
        result_prev = result;
        lineNumber++;
        zzlineno++;
        
/*        result = (s==NULL) ? YY_NULL: strlen(s); */
/*
//         if (o_lst != NULL) { 
//            fprintf(o_lst, "%6d %s", lineCount, ibuf);
//         }
*/
        /* Remove tabs from line */
        strcpy(ibuf, buf);
        tabExpand(buf, ibuf);

        s = buf;
/*        result = (s==NULL) ? YY_NULL: strlen(s); */
        result = strlen(s);
/*
//         if (globalEnvPtr->debugFlag != 0 ) {
//               fprintf(stderr, "lextrace: result[%d]=%d;\n", lineCount, result);
//         }
*/
/*      This code will remove the <CR> from buffer, as found in DOS format files */

        if (result > 1) {
/*
//             if (globalEnvPtr->debugFlag != 0 ) {
//                   fprintf(stderr,"lextrace: buf(%d) before: |%s|\n", strlen(buf), buf);
//                }
*/
            if (buf[result - 2] == CHR_CR) {
                buf[result - 2] = CHR_LF;
                buf[result - 1] = CHR_EOS;
/*              result = (s==NULL) ? YY_NULL: strlen(s); */
                result = strlen(s);
            }
/*
//             if (globalEnvPtr->debugFlag != 0 ) {
//                   fprintf(stderr,"lextrace: buf(%d)  after: |%s|\n", strlen(buf), buf);
//                fprintf(stderr, "lextrace: result[%d]=%d;\n", lineCount, result);
//                }
*/
        }
        
        DEBUG_RTN_FSP("lextrace: fsp = %d:\n")
        
        if ((result) && (fsp > 0)) {

           DEBUG_RTN_DUMP("lextrace: dump{%d, %d, %d, %d} - before do_copy_replacements |%s<NL>|\n", buf)

           do_copy_replacements(buf); 

           result = strlen(buf);

           DEBUG_RTN_DUMP("lextrace: dump{%d, %d, %d, %d} after do_copy_replacements |%s<NL>|\n", buf)

        }
/*        
//         if (o_lst != NULL) { 
//            //fprintf(o_lst, "%6d : %s", lineCount, buf); 
//            // free == 1, fixed == 0 
//            if ((globalEnvPtr->codeFormat == 0) && (result > FIXFORM_81)) {
//               fprintf(o_lst, "%6d * %s", lineNumber, buf);
//            }
//            else {
// //              fprintf(o_lst, "%6d : %s", lineNumber, buf);
//               fprintf(o_lst, "%06d : %s", lineNumber, buf);
//            }
//         }
*/
        strcpy(ibuf, buf);
        /* lineno_prev = lineno;; */
        /* yylineno_prev = yylineno; */
        /* yylineno_prev = lineNumber; */
        fsp_prev = fsp;
        zzlineno_prev = zzlineno;
        lineNumber_prev = lineNumber;

        result = strlen(buf);

        /* free == 1, fixed == 0 */
        /* if ( globalEnvPtr->codeFormat == 0 ) { */
        if ( HTG_codeFormat == TCB_SOURCE_CODE_FORMAT_FIXED ) {
           if (result > FIXFORM_81) {
           }
           if (result < FIXFORM_7) {
              strcpy(buf, "\n");
           }
           if (result > FIXFORM_6) {
              if (result < FIXFORM_73) {
                 strcpy(buf, ibuf+FIXFORM_6);
              }
              if (result > FIXFORM_72) {
                 strncpy(buf, ibuf+FIXFORM_6, FIXFORM_65+1);
                 buf[FIXFORM_65+1] = '\n';
                 buf[FIXFORM_65+2] = CHR_EOS;
              }
           }
        }

        result = strlen(buf);
        s = buf;

        return result;
}

void set_scanner_state(int i0, int i1) {

/*    pp_filename = strdup (input_filename); */
/*    if (globalEnvPtr->codeFormat == TCB_SOURCE_CODE_FORMAT_FREE) { */
    if (HTG_codeFormat == TCB_SOURCE_CODE_FORMAT_FREE) {
       BEGIN(i1);
    }
    
/*    if (globalEnvPtr->codeFormat == TCB_SOURCE_CODE_FORMAT_FIXED) { */
    if (HTG_codeFormat == TCB_SOURCE_CODE_FORMAT_FIXED) {
    	BEGIN(i0);
    }

}

void pp_setup_scanner_state () {

    /*  free == 1, fixed == 0 */

/*    if (globalEnvPtr->codeFormat == TCB_SOURCE_CODE_FORMAT_FREE) { */
    if (HTG_codeFormat == TCB_SOURCE_CODE_FORMAT_FREE) {
       BEGIN(FREE) ;
    }
    else {
/*       if (globalEnvPtr->codeFormat == TCB_SOURCE_CODE_FORMAT_FIXED) { */
       if (HTG_codeFormat == TCB_SOURCE_CODE_FORMAT_FIXED) {
           BEGIN(FIXED_7) ;
       }
       else {
           assert(1);
       }
    }

    fprintf (pp_yyout, "# %d \"%s\"\n", lineno, pp_filename);
}

void copy_switch(void) {

        struct copy_symbols *tmp=NULL;

        if (fsp>=MAX_COPY_DEPTH) {
                /* yyerror("Impossible to redirect input!"); */
                fprintf(stderr, "Copy nested too deeply (max=%d)\n", MAX_COPY_DEPTH);
                exit(1);
        }
        file_stack[ fsp ].buffer = YY_CURRENT_BUFFER;
        file_stack[ fsp ].filename = pp_filename;
        /* file_stack[ fsp ].lineno = lineno; */
        file_stack[ fsp ].lineno = zzlineno;
        zzlineno = 0;
/*         file_stack[ fsp ].copybook = include_cpybook; */
/*         file_stack[ fsp ].copylib = include_cpylib; */

        DEBUG_RTN_RLIST2()

        copy_symbols = NULL;

        fsp++;
        file_stack[ fsp ].last_symbol = append_copy_symbols;
        append_copy_symbols = NULL;

        DEBUG_RTN_DLIST("lextrace: fsp=%d, copybook=%s copylib=%s\n", include_cpybook, include_cpylib)
        DEBUG_RTN_RLIST3()
        if (find_copybook_file(include_cpybook, include_cpylib) != 0) {

           fprintf(stderr, "error: copybook file %s not found\n", include_cpybook);

           exit(16);
        }     
           
        pp_yyin = fopen( include_full_filename, "r" );
	
        if (pp_yyin == NULL) {
                fprintf(stderr, "Cannot open copy file %s\n", include_full_filename);
                exit(1);
        }

        yy_switch_to_buffer( yy_create_buffer(pp_yyin,YY_BUF_SIZE) );
        pp_filename = strdup (include_full_filename);
        lineno   = 1; 
        fprintf (pp_yyout, "# %d \"%s\"\n", lineno, pp_filename); 

        copy_start_sw--;

}

void add_copy_replacement(char *orig_value, char *replacement) {

    struct copy_symbols *cs=NULL,*tmp=NULL;
    int i;

    DEBUG_RTN_STR3("lextrace: add_copy_replacement - %s will be replaced by %s\n", orig_value, replacement)

    cs = malloc(sizeof(struct copy_symbols));
    cs->value = orig_value;
    cs->replacement = replacement;
    cs->next = NULL;
    if (append_copy_symbols==NULL) 
    	    append_copy_symbols = cs;
    else {
    	    tmp=append_copy_symbols;
    	    while (tmp->next) 
    		    tmp=tmp->next;
    	    tmp->next = cs;
    }

    DEBUG_RTN_RLIST4()

}

void do_copy_replacements(char *buffer) {

    struct copy_symbols *cs;
    char *s, *s1, *tmp = NULL;
    int len, end, i, sw, cnt;
        
    DEBUG_RTN_FSP("lextrace: do_copy_replacements fsp = %d:\n")
    
    /* Replacement table empty */
    copy_symbols = file_stack[fsp].last_symbol;
    if (file_stack[fsp].last_symbol == NULL) {

       DEBUG_RTN_STR1("lextrace: Empty replace list \n")

       return;
    }
    
    DEBUG_RTN_STR1("lextrace: Replace list is NOT empty \n")
    DEBUG_RTN_RLIST()
     
    
     /* ignore comments */
/*    if (globalEnvPtr->codeFormat == 1) { */
    if (HTG_codeFormat == TCB_SOURCE_CODE_FORMAT_FREE) {
     	if (*buffer == CHR_ASTERIX)  {

           DEBUG_RTN_DUMP("lextrace: dump{%d, %d, %d, %d} Ignoring comment line |%s<NL>|\n", buffer)

     	   return;
     	}
     }
     len = strlen(buffer);
     if (len > FIXFORM_7) {
     	if (*(buffer + FIXFORM_6) == CHR_ASTERIX)  {
            /* comment */

            DEBUG_RTN_DUMP("lextrace: dump{%d, %d, %d, %d} Ignoring comment line |%s<NL>|\n", buffer)

            return;
     	}
     } 
     else {
     	/* empty line */

        DEBUG_RTN_STR2("lextrace: Ignoring empty fixed format line :%s:\n", buffer)

     	return;
     }
        
     DEBUG_RTN_DUMP("lextrace: dump{%d, %d, %d, %d} After comment check, Before copy replace : |%s<NL>|\n", buffer)
        
     /*tmp = malloc(MAXLINEBUF);*/
     tmp = malloc(YY_READ_BUF_SIZE);
     /*tmp = malloc(500); */
     /*strcpy(tmp, ""); */
     tmp[0]='\0';
     s  = buffer;
     s1 = tmp;
     len = strlen(buffer);
/*     if (globalEnvPtr->codeFormat == 0) { */
     if (HTG_codeFormat == TCB_SOURCE_CODE_FORMAT_FIXED) {
     	 /*fixed format */
     	 for (i=0; i<FIXFORM_7; i++) {
     	    *s1++ = *s++;
     	 }
         *(s1+1) = '\0';
     	 i = FIXFORM_7;
     	 if (len > FIXFORM_72) {
     	    /*end = len - (len - FIXFORM_72); */
     	    end = FIXFORM_72;
     	 } 
     	 else {
     	    end = len;
     	 }
     } 
     else {
     	 /* free format */
     	 i = 0;
     	 end = len;
     }

    copy_symbols = file_stack[fsp].last_symbol;

    cnt = 0;
    for (i=i; i<end; ) {
        if (*s && (*s == ' ' || *s == '\t')) {
            *s1 = *s;
            s1++;
            *s1 = '\0';
            s++;
            i++;
        } 
        else {
            sw = 0;
            for (cs=copy_symbols; cs != NULL; ) {
        	if (!strncmp(s, cs->value, strlen(cs->value))) {
        	    strcat(s1, cs->replacement);
        	    cnt++;
        	    s  += strlen(cs->value);
        	    i  += strlen(cs->value); 
        	    s1 += strlen(cs->replacement);

                    DEBUG_RTN_STR3("lextrace: Now replacing :%s: by :%s:\n", cs->value, cs->replacement)

        	    cs = NULL;
        	    sw = 1;
        	} 
        	else {
        	    cs=cs->next;
        	}
            }
            if (sw == 0) {
               *s1 = *s;
               s++;
               s1++;
               *s1 = '\0';
               i++;
            }
        }
     }

     if (cnt != 0) {
        /* Try to fix 73-80 cols.      */    
/*        if (globalEnvPtr->codeFormat == 0) { // fixed format */
        if (HTG_codeFormat == TCB_SOURCE_CODE_FORMAT_FIXED) { /* fixed format */
           len = strlen(tmp);

           DEBUG_RTN_FIXLEN("lextrace: Before 73-80 cols fix len=%d :%s:\n", len, tmp)

           if (len > FIXFORM_72) {
              sw = 0;
              for (i=len-1; i>=FIXFORM_71; i--) {
                  s1 = tmp + i;
                  if (*s1 != ' ') {
                      sw++;
                      i = 0;
                   } 
                   else {
                      s1 = tmp + i;
                      *s1 = '\0';
                   }
              }
              s1 = buffer + FIXFORM_71;
              strcat(tmp, s1);
           } 
           else {
           	if (len < FIXFORM_72) {
           	   for (i=len - 1; i<FIXFORM_72; i++) {
           		s1 = tmp + i;
           		*s1 = ' ';
           		*(s1+1) = '\0';
           	   }
           	}
           	s1 = buffer + FIXFORM_72;
           	strcat(tmp, s1);
           }
        }
        strcpy(buffer, tmp);
     }
    
/*  strcat(buffer, "\n"); */

    if (tmp) {free(tmp); tmp=NULL;}

    DEBUG_RTN_DUMP("lextrace: dump{%d, %d, %d, %d} After copy replace loop : |%s<NL>|\n", buffer)

}

void add_replace_replacement(char *orig_value, char *replacement) {

    struct copy_symbols *cs,*tmp;
    int i;

    DEBUG_RTN_STR3("lextrace: add_replace_replacement - %s will be replaced by %s\n", orig_value, replacement)

    cs = malloc(sizeof(struct copy_symbols));
    cs->value = orig_value;
    cs->replacement = replacement;
    cs->next = NULL;
    if (append_replace_symbols==NULL) 
    	append_replace_symbols = cs;
    else {
    	    tmp=append_replace_symbols;
    	    while (tmp->next) 
    		    tmp=tmp->next;
    	    tmp->next = cs;
    }

    DEBUG_RTN_RLIST5()

}

void do_replace_replacements(char *buffer) {

    struct copy_symbols *cs;
    char *s, *s1, *tmp = NULL;
    int len, end, i, sw, cnt;
        
    DEBUG_RTN_FSP("lextrace: do_replace_replacements fsp = %d:\n")
    
    /* Replacement table empty */
    copy_symbols = file_stack[fsp].last_symbol;
    if (file_stack[fsp].last_symbol == NULL) {

       DEBUG_RTN_STR1("lextrace: Empty replace list \n")

       return;
    }
    
    DEBUG_RTN_STR1("lextrace: Replace list is NOT empty \n")
    DEBUG_RTN_RLIST()
     
    
    /* ignore comments */
/*    if (globalEnvPtr->codeFormat == 1) { */
    if (HTG_codeFormat == TCB_SOURCE_CODE_FORMAT_FREE) {
     	if (*buffer == CHR_ASTERIX)  {

           DEBUG_RTN_DUMP("lextrace: dump{%d, %d, %d, %d} Ignoring comment line |%s<NL>|\n", buffer)

     	   return;
     	}
     }
     len = strlen(buffer);
     if (len > FIXFORM_7) {
     	if (*(buffer + FIXFORM_6) == CHR_ASTERIX)  {
            /* comment */

            DEBUG_RTN_DUMP("lextrace: dump{%d, %d, %d, %d} Ignoring comment line |%s<NL>|\n", buffer)

            return;
     	}
     } 
     else {
     	/* empty line */

        DEBUG_RTN_STR2("lextrace: Ignoring empty fixed format line :%s:\n", buffer)

     	return;
     }
        
     DEBUG_RTN_DUMP("lextrace: dump{%d, %d, %d, %d} After comment check, Before copy replace : |%s<NL>|\n", buffer)
        
     /*tmp = malloc(MAXLINEBUF);*/
     tmp = malloc(YY_READ_BUF_SIZE);
     /*strcpy(tmp, ""); */
     tmp[0]='\0';
     s  = buffer;
     s1 = tmp;
     len = strlen(buffer);
/*     if (globalEnvPtr->codeFormat == 0) { */
     if (HTG_codeFormat == TCB_SOURCE_CODE_FORMAT_FIXED) {
     	 /*fixed format */
     	 for (i=0; i<FIXFORM_7; i++) {
     	    *s1++ = *s++;
     	 }
         *(s1+1) = '\0';
     	 i = FIXFORM_7;
     	 if (len > FIXFORM_72) {
     	    /*end = len - (len - FIXFORM_72); */
     	    end = FIXFORM_72;
     	 } 
     	 else {
     	    end = len;
     	 }
     } 
     else {
     	 /* free format */
     	 i = 0;
     	 end = len;
     }

    copy_symbols = file_stack[fsp].last_symbol;

    cnt = 0;
    for (i=i; i<end; ) {
        if (*s && (*s == ' ' || *s == '\t')) {
            *s1 = *s;
            s1++;
            *s1 = '\0';
            s++;
            i++;
        } 
        else {
            sw = 0;
            for (cs=copy_symbols; cs != NULL; ) {
        	if (!strncmp(s, cs->value, strlen(cs->value))) {
        	    strcat(s1, cs->replacement);
        	    cnt++;
        	    s  += strlen(cs->value);
        	    i  += strlen(cs->value); 
        	    s1 += strlen(cs->replacement);

                    DEBUG_RTN_STR3("lextrace: Now replacing :%s: by :%s:\n", cs->value, cs->replacement)

        	    cs = NULL;
        	    sw = 1;
        	} 
        	else {
        	    cs=cs->next;
        	}
            }
            if (sw == 0) {
               *s1 = *s;
               s++;
               s1++;
               *s1 = '\0';
               i++;
            }
        }
     }

     if (cnt != 0) {
        /* Try to fix 73-80 cols.       */   
/*        if (globalEnvPtr->codeFormat == 0) { // fixed format */
        if (HTG_codeFormat == TCB_SOURCE_CODE_FORMAT_FIXED) { /* fixed format */
           len = strlen(tmp);

           DEBUG_RTN_FIXLEN("lextrace: Before 73-80 cols fix len=%d :%s:\n", len, tmp)

           if (len > FIXFORM_72) {
              sw = 0;
              for (i=len-1; i>=FIXFORM_71; i--) {
                  s1 = tmp + i;
                  if (*s1 != ' ') {
                      sw++;
                      i = 0;
                   } 
                   else {
                      s1 = tmp + i;
                      *s1 = '\0';
                   }
              }
              s1 = buffer + FIXFORM_71;
              strcat(tmp, s1);
           } 
           else {
           	if (len < FIXFORM_72) {
           	   for (i=len - 1; i<FIXFORM_72; i++) {
           		s1 = tmp + i;
           		*s1 = ' ';
           		*(s1+1) = '\0';
           	   }
           	}
           	s1 = buffer + FIXFORM_72;
           	strcat(tmp, s1);
           }
        }
        strcpy(buffer, tmp);
     }
    
/*  strcat(buffer, "\n"); */

    DEBUG_RTN_DUMP("lextrace: dump{%d, %d, %d, %d} After copy replace loop : |%s<NL>|\n", buffer)

    if (tmp) { free(tmp); tmp=NULL; }
}

void adjust_counters(void) {
    
    int i, l=0, c=0, sw=0;
    
    for (i=yyleng-1; i>=0; i--) {
        if (pp_yytext[i] == CHR_LF) {
           l++;
           sw=1;
        }
        if (sw == 0) {
           c++;
        }
    }
    lineno = lineno + l;
    lineCount = lineCount + l;
    lf_add = lf_add + l; 
    columnCount = c; 
        
}

#ifdef DEBUG_COBPP_SCANNER

void debug_rtn (const char *s, unsigned long Ccnt, unsigned long Lcnt, int Len, const char *s1) {
  

  char scstate[50];
  
  switch (YYSTATE)
  {
    case FREE:
      strcpy(scstate, "FREE");
      break;
    
    case FIXED_7:
      strcpy(scstate, "FIXED_7");
      break;
    
    case FIXED_AB:
      strcpy(scstate, "FIXED_AB");
      break;
    
    case COMMENT:
      strcpy(scstate, "COMMENT");
      break;
    
    case DQ_LITERAL_FIXED:
      strcpy(scstate, "DQ_LITERAL_FIXED");
      break;
    
    case DQ_LITERAL_FREE:
      strcpy(scstate, "DQ_LITERAL_FREE");
      break;
    
    case SQ_LITERAL_FIXED:
      strcpy(scstate, "SQ_LITERAL_FIXED");
      break;
    
    case SQ_LITERAL_FREE:
      strcpy(scstate, "SQ_LITERAL_FREE");
      break;
    
    default:
      strcpy(scstate, "none");
      break;
  }
  
     fprintf(stderr, 
             "debug lex %s - %s (%lu,%lu): length=%d, :%s:\n", 
             scstate,
             s,
             Lcnt, 
             Ccnt, 
             Len,
             s1
             );   
}

void debug_rtn2 (const char *s1, const char *s2, int sw1, int sw2, int sw3, int sw)
{
   switch (sw)
   {
     case 3:
       sprintf(errbuf, s1, s2);
       break;
     
     case 5:
       sprintf(errbuf, s1, sw1);
       break;
     
     case 7:
       sprintf(errbuf, s1, sw2);
       break;
     
     case 11:
       sprintf(errbuf, s1, sw3);
       break;
     
     case 15:
       sprintf(errbuf, s1, s2, sw1);
       break;

     case 21:
       sprintf(errbuf, s1, s2, sw2);
       break;

     case 33:
       sprintf(errbuf, s1, s2, sw3);
       break;

     case 35:
       sprintf(errbuf, s1, sw1, sw2);
       break;

     case 105:
       sprintf(errbuf, s1, s2, sw1, sw2);
       break;

     case 385:
       sprintf(errbuf, s1, sw1, sw2, sw3);
       break;

     default:
       sprintf(errbuf, "%s", s1);
       break;
   }

   fprintf(stderr, "%s", errbuf);
}

void debug_rtn_sssd (const char *s1, const char *s2, const char *s3, int z, int sw)
{
   switch (sw)
   {
     case 3:
       sprintf(errbuf, s1, s2);
       break;
     
     case 5:
       sprintf(errbuf, s1, s3);
       break;
     
     case 7:
       sprintf(errbuf, s1, z);
       break;
     
     case 15:
       sprintf(errbuf, s1, s2, s3);
       break;
     
     case 21:
       sprintf(errbuf, s1, s2, z);
       break;
     
     case 22:
       sprintf(errbuf, s1, z, s2);
       break;
     
     case 105:
       sprintf(errbuf, s1, s2, s3, z);
       break;

     case 106:
       sprintf(errbuf, s1, z, s2, s3);
       break;
     
     default:
       sprintf(errbuf, "%s", s1);
       break;
   }
   
   fprintf(stderr, "%s", errbuf);
}

void debug_rtn_dump (const char *s, const char *s1, int fsln, int fsi, int gln)
{
  char wkbuf[MAXLINEBUF+1];
  int ln, idx;
  
  strcpy(wkbuf, s1);
  ln = strlen(wkbuf);
  idx = ln - 1;
  if (wkbuf[idx] == CHR_LF) {
      wkbuf[idx] = CHR_EOS;    
  }  
  fprintf(stderr, s, fsi, fsln, gln, ln, wkbuf);
}

#endif
