/* 
 *  Copyright (C) 2001, 2000, 1999,  Rildo Pragana. 
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

/*
**  COBOL scanner 
**  Scanner para o Compilador COBOL
*/

%option caseless
%option never-interactive

%{
/*
#include "htcoblib.h"
#include "htglobals.h"
#include <ctype.h>
*/
/* #define DEBUG_SCANNER            1 */

#define MAX_COPY_DEPTH          10
#define MAX_CPYNAME_LEN         65
#define MAXLINEBUF              256

void scdebug( char *fmt, ... );
char *savename1(int, int);

#define lexchar input

/* extern int lexgetc(void); */

int source_debug=0;
int envdiv_bypass_save_sw=0;
int stabs_started=0;

/* extern FILE *o_lst; */

int lex_fgets( char *buf, int maxsize );

#define YY_INPUT(buf,result,max_size) \
        { \
                result = lex_fgets( buf, max_size ); \
        }
/*
 Redefines the lexer so that we define yylex to call yylex2 
 and save the token returned by the real lexer (yylex2)
 FIX for FLEX versions greater than 2.5.4 
*/
int prev_token=0;

#ifdef YY_USE_PROTOS
#define YY_DECL int yylex2 YY_PROTO((void))
#else
#define YY_PROTO(proto) (void)
#define YY_DECL int yylex2(void)
#endif

%}

AnyNoDQuote  [^"\t\n]
AnyNoSQuote  [^'\t\n]
cobword [A-Za-z0-9\-_\$]
letters [A-Za-z]
alphanum [A-Za-z0-9]
ident {alphanum}(({alphanum}|-|_|$)*{alphanum}+)?
exletter {letters}|-
digit [0-9]
pic_ch [9XVSBZAP.,-+*/$]
relop [<>=]
white [\r\t ]
white_nl [\r\t \n]
lpar \(
rpar \)
sdelim \"
ldelim \'
lhexa [xXhH]
any [!-~£]
int {digit}({digit})*
decdelim [.,]
sign [+-]
notperiod [^.\n]
period [.]

%{
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "htglobals.h"
#include "htcoboly.h"
#include "htcobol.tab.h"    /* definitions from YACC */
#include "htcoblib.h"
#include "reswords.h"

#define TOKTEXT_SIZE 1024

char toktext[TOKTEXT_SIZE];
char *tp;
unsigned char hnum[512];
unsigned int varnumber;
int reserved_token;
int previous_state = 0;
short function_seen = 0;
int eos_detect=0;

#define svtoken() strncpy(toktext,yytext,sizeof(toktext))  

%}

%x IDENT_ST ENVIR_ST DATA_ST COMMENT_ST FD_ST REDEF_ST
%x SUBSCRIPTS_ST EXCEPTION_ST PIC_ST PIC_ST2 COMMENT1_ST

%%
%{
        extern int curr_division;
        extern int need_subscripts;
/*        struct copy_symbols *tmp = NULL; */

        switch (curr_division) {
        case CDIV_IDENT:
                scdebug("-> IDENT_ST\n");
                BEGIN IDENT_ST;
                break;
        case CDIV_ENVIR:
                scdebug("-> ENVIR_ST\n");
                BEGIN ENVIR_ST;
                break;
        case CDIV_DATA:
                scdebug("-> DATA_ST\n");
                BEGIN DATA_ST;
                break;
        case CDIV_PROC:
                /* stabs_started=1; */
                scdebug("-> INITIAL\n");
                BEGIN INITIAL;
                break;
        case CDIV_COMMENT:
                scdebug("-> COMMENT_ST\n");
                BEGIN COMMENT_ST;
                break;
        case CDIV_COMMENT1:
                scdebug("-> COMMENT1_ST\n");
                BEGIN COMMENT1_ST;
                break;
        case CDIV_FD:
                scdebug("-> FD_ST\n");
                BEGIN FD_ST;
                break;
        case CDIV_REDEF:
                scdebug("-> REDEF_ST\n");
                BEGIN REDEF_ST;
                break;
        case CDIV_SUBSCRIPTS:
                scdebug("-> SUBSCRIPTS_ST\n");
                BEGIN SUBSCRIPTS_ST;
                break;
        case CDIV_EXCEPTION:
                scdebug("-> EXCEPTION_ST\n");
                BEGIN EXCEPTION_ST;
                break;
        case CDIV_PIC:
                scdebug("-> PIC_ST\n");
                BEGIN PIC_ST;
                break;
        case CINITIAL:
                scdebug("-> INITIAL\n");
                BEGIN INITIAL;
                break;
        }
        curr_division=0; /* avoid new state switch */
%}

<*>^"#".* {
  char *endp;
  source_lineno = strtol (yytext + 2, &endp, 10);
  if (source_lineno > 0)
    source_lineno--;
  if (source_filename)
    free (source_filename);
  source_filename = strdup (strchr (endp, '"') + 1);
  strrchr (source_filename, '"')[0] = '\0';
  scdebug("NEW FILE/LINE : %s,%d\n", source_filename,source_lineno);
}

<*>"EJECT"|"SKIP1"|"SKIP2"|"SKIP3" { /* throw away this */ }

<*>^[ \t]?"*".*$ { 
    /* allow floating comment line */  
    scdebug("<comment>: %s:\n", yytext);
}

<*>^"D ".*      { 
                if (!source_debug)
                        scdebug("<comment>: %s:\n", yytext);
                else
                        yyless(2);
        }

";" { }
"," { }

{lpar} {
                if (need_subscripts) {
                        scdebug("<LPAR>:\n");
                        need_subscripts=0;
                        return(LPAR);
                }
                else {
                        return('('); 
                }
        }
{white}+ { }

<INITIAL,SUBSCRIPTS_ST>{ident} { {
                struct sym *symbol;
                svtoken();
                if (is_integer_token(toktext) && prev_token == PERIOD_TOK) {
                        yylval.sval=install(toktext,SYTB_LAB,0); 
                        scdebug("<LABELSTR>: %s\n", toktext);
                        return(LABELSTR);
                } 
                /* if (is_integer_token(toktext) && !eos_detect) {*/
                if (is_integer_token(toktext)) {
                        scdebug("<NLITERAL>: %s\n", toktext);
                        yylval.lval = (struct lit *)install_lit(toktext,0,0);
                        return(NLITERAL);
                }
                eos_detect=0;
                if (!is_valid_identifier(toktext)) {
                        yylval.sval=install(toktext,SYTB_LAB,0); 
                        scdebug("<LABELSTR>: %s\n", toktext);
                        return(LABELSTR);
                } 
                else {
                        if ((reserved_token=reserved(toktext))!=0) 
                        {
                                if (reserved_token == FUNCTION) function_seen=TRUE;
                                /* special case of 4 intrinsics which are also reserved */
                                if (function_seen && lookup_intrinsic_sym(toktext) != NULL)
                                {
                                        yylval.sval=install(toktext,SYTB_LAB,0); 
                                        scdebug(" <LABELSTR>: %s\n", toktext);
                                        return(LABELSTR);
                                }
                                scdebug(" <reserved>: %s\n", toktext);
                                return reserved_token;
                        }
                        /* if symbol was defined at the data division */
                        if (symbol=lookup(toktext,2)) {
                                yylval.sval=symbol;
                                if (symbol->type == '8') {
                                        scdebug("<VARCOND>: %s\n",toktext);
                                        update_xreflist(yylval.sval); 
                                        return(VARCOND);
                                }
                                else {
                                        if (is_subscripted(symbol)) {
                                                        scdebug("<SUBSCVAR>: %s\n",toktext);
                                                        return(SUBSCVAR);
                                        }
                                        scdebug("<VARIABLE>: %s\n", toktext);
                                        update_xreflist(yylval.sval); 
                                        return(VARIABLE);
                                }
                        } 
                        /* otherwise, it should be a label */
                        else {
                                yylval.sval=install(toktext,SYTB_LAB,0); 
                                scdebug("<LABELSTR>: %s\n", toktext);
                                return(LABELSTR);
                        }
                }
        } }

<ENVIR_ST>{ident} {
                svtoken();
                if (is_integer_token(toktext)) {
                        scdebug("<NLITERAL>: %s\n", toktext);
                        yylval.lval = (struct lit *)install_lit(toktext,0,0);
                        return(NLITERAL);
                }
                if (!is_valid_identifier(toktext)) {
                        yylval.sval=install(toktext,SYTB_LAB,0); 
                        scdebug("<LABELSTR>: %s\n", toktext);
                        return(LABELSTR);
                }
                else {
                      if ((reserved_token=reserved(toktext))!=0) 
                      {
                         scdebug(" <reserved>: %s\n", toktext);
                         return reserved_token;
                      }
                      scdebug("<STRING>: %s\n", toktext);
                      if (envdiv_bypass_save_sw == 0) {
                         yylval.sval=install(toktext,SYTB_VAR,0);
                         update_xreflist(yylval.sval); 
                      }
                      return(STRING);
                }

}

<EXCEPTION_ST>{ident} { {
                struct sym *symbol;
                svtoken();
                if (is_integer_token(toktext)) {
                        scdebug("<NLITERAL>: %s\n", toktext);
                        yylval.lval = (struct lit *)install_lit(toktext,0,0);
                        return(NLITERAL);
                }
                if (!is_valid_identifier(toktext)) {
                        yylval.sval=install(toktext,SYTB_LAB,0); 
                        scdebug("<LABELSTR>: %s\n", toktext);
                        return(LABELSTR);
                }
                else {
                        if ((reserved_token=reserved(toktext))!=0) 
                        {
                                scdebug(" <reserved>: %s\n", toktext);
                                if (reserved_token == NOT)
                                        reserved_token = NOTEXCEP;
                                return reserved_token;
                        }
                        /* if symbol was defined at the data division */
                        if (symbol=lookup(toktext,2)) {
                                yylval.sval=symbol;
                                if (symbol->type == '8') {
                                        scdebug("<VARCOND>: %s\n",toktext);
                                        update_xreflist(yylval.sval); 
                                        return(VARCOND);
                                }
                                else {
                                        scdebug("<VARIABLE>: %s\n", toktext);
                                        update_xreflist(yylval.sval); 
                                        return(VARIABLE);
                                }

                        } 
                        /* otherwise, it should be a label */
                        else {
                                yylval.sval=install(toktext,SYTB_LAB,0);
                                scdebug("<LABELSTR>: %s\n", toktext);
                                return(LABELSTR);
                        }
                }
        } }

<FD_ST>{
{ident} {
                svtoken();
                if (is_integer_token(toktext)) {
                        scdebug("<NLITERAL>: %s\n", toktext);
                        yylval.lval = (struct lit *)install_lit(toktext,0,0);
                        return(NLITERAL);
                }
                if (!is_valid_identifier(toktext)) {
                        yylval.sval=install(toktext,SYTB_LAB,0); 
                        scdebug("<LABELSTR>: %s\n", toktext);
                        return(LABELSTR);
                }
                else {
                        if ((reserved_token=reserved(toktext))!=0) 
                        {
                                scdebug(" <reserved>: %s\n", toktext);
                                return reserved_token;
                        }
                        scdebug("<STRING>: %s\n", toktext);
                        /* install w/clone if neccessary */
                        if ((yylval.sval=lookup(toktext,SYTB_VAR))==NULL)
                                yyerror("undefined %s at FD/SD",toktext); 
                        return(STRING);
                }
        }
[ \t]* { }
}

<REDEF_ST>{ident} {
                svtoken();
                if (is_integer_token(toktext)) {
                        scdebug("<NLITERAL>: %s\n", toktext);
                        yylval.lval = (struct lit *)install_lit(toktext,0,0);
                        return(NLITERAL);
                }
                if (!is_valid_identifier(toktext)) {
                        yylval.sval=install(toktext,SYTB_LAB,0); 
                        scdebug("<LABELSTR>: %s\n", toktext);
                        return(LABELSTR);
                }
                else {
                        if ((reserved_token=reserved(toktext))!=0) 
                        {
                                scdebug(" <reserved>: %s\n", toktext);
                                return reserved_token;
                        }
                        scdebug("<STRING>: %s\n", toktext);
                        /* don't clone redefined var */
                        yylval.sval=install(toktext,SYTB_VAR,0); 
                        update_xreflist(yylval.sval); 
                        return(STRING);
                }
        }

<DATA_ST>{ident} {
                svtoken();
                if (is_integer_token(toktext)) {
                        scdebug("<NLITERAL>: %s\n", toktext);
                        yylval.lval = (struct lit *)install_lit(toktext,0,0);
                        return(NLITERAL);
                }
                if (!is_valid_identifier(toktext)) {
                        yylval.sval=install(toktext,SYTB_LAB,0); 
                        scdebug("<LABELSTR>: %s\n", toktext);
                        return(LABELSTR);
                }
                else {
                        if ((reserved_token=reserved(toktext))!=0) 
                        {
                                scdebug(" <reserved>: %s\n", toktext);
                                return reserved_token;
                        }
                        scdebug("<STRING>: %s\n", toktext);
                        /* install w/clone if neccessary */
                        yylval.sval=install(toktext,SYTB_VAR,1);
                        update_xreflist(yylval.sval); 
                        return(STRING);
                }
        }

<SUBSCRIPTS_ST>{
";" { }
"+"{int} {
                svtoken();
                scdebug("<NLITERAL>: %s\n", toktext);
                yylval.lval = (struct lit *)install_lit(&toktext[1],0,0);
                return(NLITERAL);
	} 

{any}   {
                svtoken();
                scdebug("<0: any>: %s\n", toktext);
                return(toktext[0]); 
        }
{white}+ { }
}       

<IDENT_ST>{
[ \t]* { }
\./[ \t\n]+ { 
                scdebug("<PERIOD_TOK>:\n");
                return(PERIOD_TOK); 
        }
{sdelim}{AnyNoDQuote}+{sdelim} {
                svtoken();
                scdebug(" <IDSTRING_LITERAL>: %s\n", toktext);
                yylval.str=savename1(1, 1);
                return IDSTRING_LITERAL;
        }
{ldelim}{AnyNoSQuote}+{ldelim} {
                svtoken();
                scdebug(" <IDSTRING_LITERAL>: %s\n", toktext);
                yylval.str=savename1(1, 1);
                return IDSTRING_LITERAL;
        }
[^\r\t \n\.]+ {
                svtoken();
                scdebug(" <IDSTRING_WORD>: %s\n", toktext);
                yylval.str=toktext;
                return IDSTRING_WORD;
        }
{any}   {
                svtoken();
                scdebug("<0: any>: %s\n", toktext);
                return(toktext[0]); 
        }
"\n" { }
} /* end of <IDENT_ST> */

<INITIAL,ENVIR_ST,DATA_ST,REDEF_ST,EXCEPTION_ST>{

";" { }
\./[ \t\n]+ { 
                scdebug("<PERIOD_TOK>:\n");
                eos_detect++;
                return(PERIOD_TOK); 
        }

{sdelim}        {
                tp=toktext;
                while(1) {
                        while((*tp=lexchar())!='"') {
                                if (tp >= toktext+TOKTEXT_SIZE) {
                                        yyerror("scanner error: token too large");
                                        while(lexchar()!='"') ;
                                        *tp=0;
                                        scdebug("<CLITERAL>: %s\n", toktext);
                                        yylval.lval = (struct lit *)install_lit(toktext,0,0);
                                        return(CLITERAL);
                                }
                                tp++;
                        }
                        /* replace two consecutives '"' by one and continue */
                        if ((*tp=lexchar())=='"') {
                                tp++;
                                continue;
                        }
                        else {
                                unput(*tp);
                                break;
                        }
                }
                *tp=0;
                scdebug("<CLITERAL>: %s\n", toktext);
                yylval.lval = (struct lit *)install_lit(toktext,0,0);
                return(CLITERAL);
        }

{lhexa}{ldelim} { 
       {
                unsigned char *s=hnum;
                int len;
                tp=toktext;
                while((*tp=toupper(lexchar()))!='\'') {
                                if (tp >= toktext+TOKTEXT_SIZE) {
                                        yyerror("scanner error: token too large");
                                        while(lexchar()!='\'') ;
                                        *tp=0;
                                        scdebug("<CLITERAL>: %s\n", toktext);
                                        yylval.lval = (struct lit *)install_lit(toktext,0,0);
                                        return(CLITERAL);
                                }
                        *s = (*tp > '9') ?
                                (*tp - 'A' + 0x0a) : (*tp - '0');
                        if ((*tp=toupper(lexchar()))=='\'') {
                                break;
                        }
                        *s++ = *s * 0x10 + ((*tp > '9') ? 
                                (*tp - 'A' + 0x0a) : (*tp - '0'));
                }
                len = (int) (s - hnum);
                yylval.lval = (struct lit *)install_lit(hnum,len,0);
                scdebug("<CLITERAL>: %s\n", hnum);
                return(CLITERAL);
       } 
}

{lhexa}{sdelim} { 
       {
                unsigned char *s=hnum;
                int len;
                tp=toktext;
                while((*tp=toupper(lexchar()))!='\"') {
                                if (tp >= toktext+TOKTEXT_SIZE) {
                                        yyerror("scanner error: token too large");
                                        while(lexchar()!='\"') ;
                                        *tp=0;
                                        scdebug("<CLITERAL>: %s\n", toktext);
                                        yylval.lval = (struct lit *)install_lit(toktext,0,0);
                                        return(CLITERAL);
                                }
                        *s = (*tp > '9') ?
                                (*tp - 'A' + 0x0a) : (*tp - '0');
                        if ((*tp=toupper(lexchar()))=='\"') {
                                break;
                        }
                        *s++ = *s * 0x10 + ((*tp > '9') ?
                                (*tp - 'A' + 0x0a) : (*tp - '0'));
                }
                len = (int) (s - hnum);
                yylval.lval = (struct lit *)install_lit(hnum,len,0);
                scdebug("<CLITERAL>: %s\n", hnum);
                return(CLITERAL);
       } 
}

{ldelim}        {
                tp=toktext;
                while(1) {
                        while((*tp=lexchar())!='\'') { 
                                if (tp >= toktext+TOKTEXT_SIZE) {
                                        yyerror("scanner error: token too large");
                                        while(lexchar()!='\'') ;
                                        *tp=0;
                                        scdebug("<CLITERAL>: %s\n", toktext);
                                        yylval.lval = (struct lit *)install_lit(toktext,0,0);
                                        return(CLITERAL);
                                }
                                tp++;
                        }
                        /* replace two consecutives '\'' by one and continue */
                        if ((*tp=lexchar())=='\'') {
                                tp++;
                                continue;
                        }
                        else {
                                unput(*tp);
                                break;
                        }
                }
                *tp=0;
                yylval.lval = (struct lit *)install_lit(toktext,0,0);
                scdebug("<CLITERAL>: %s\n", toktext);
                return(CLITERAL);
        }

{digit}*{decdelim}?{int}+       {
                svtoken();
                scdebug("<NLITERAL>: %s\n", toktext);
                yylval.lval = (struct lit *)install_lit(toktext,0,0);
                return(NLITERAL);
        }
%{ /*
{digit}({exletter}|{digit})* { 
        svtoken();
        scdebug("<LABELSTR>: %s\n", toktext);
        yylval.sval=install(toktext,SYTB_LAB,0);
        return(LABELSTR); 
        }
*/ 
%}

{white}+ { }


{relop}{relop}? {
                svtoken();
                if ((reserved_token=reserved(toktext))!=0) {
                        scdebug(" <reserved>: %s\n", toktext);
                        return reserved_token;
                }
                yyerror("relational operator unknown");
        }

{lpar}  {
                svtoken();
                if (function_seen) {
                        function_seen=FALSE;
                        }
                scdebug("<0: lpar>: %s\n", toktext);
                return(toktext[0]); 
        }
"**"    {
                svtoken();
                scdebug("<0: POW_OP>: %s\n", toktext);
                return(POW_OP); 
        }
"," { }
";" { }
{any}   {
                svtoken();
                scdebug("<0: any>: %s\n", toktext);
                return(toktext[0]); 
        }

"\n"   { }      

} /* end of <INITIAL,DATA_ST,ENVIR_ST> */

<COMMENT_ST>{
.*     { 
         svtoken();
         scdebug(" <COMMENT_ST>: %s\n", toktext);
       }
"\n"   { BEGIN INITIAL; }
} /* end of COMMENT_ST */

<COMMENT1_ST>{
{notperiod}* { 
         svtoken();
         scdebug(" <COMMENT1_ST>:>>%s<<:\n", toktext);
        }
"."" "*/"\n"   { 
         svtoken();
         scdebug(" <COMMENT1_ST>:>>%s<<:\n", toktext);
         BEGIN INITIAL; 
       }
"."    { 
         svtoken();
         scdebug(" <COMMENT1_ST>:>>%s<<:\n", toktext);
       }
"\n"   { 
         svtoken();
         scdebug(" <COMMENT1_ST>:<NL>:\n");
       }
} /* end of COMMENT1_ST */

<PIC_ST>{white_nl}* { 
                BEGIN PIC_ST2;
                scdebug("<PICS -> PIC_ST2>:\n");
        }

<PIC_ST2>{
{white_nl}* { 
                BEGIN DATA_ST;
                scdebug("<PICS -> DATA_ST>:\n");
        }
\./[ \t\n]+ { 
                BEGIN DATA_ST;
                scdebug("<PICS -> DATA_ST>: PERIOD_TOK\n");
                return PERIOD_TOK;
        }
}

<PIC_ST,PIC_ST2>{
{lpar}{digit}({digit})*{rpar} { 
                { 
                char *s;
                yylval.ival = 0;
                s = yytext+1; /* bypass lpar */
                while (*s!=')')
                        yylval.ival = 10 * yylval.ival + *s++ - '0';
                scdebug("<PICS: MULTIPLIER>: %d\n", yylval.ival);
                return(MULTIPLIER); 
                } 
        }
{ident} {
                svtoken();
                if ((reserved_token=reserved(toktext))!=0) 
                {
                        scdebug(" <reserved>: %s\n", toktext);
                        BEGIN PIC_ST;
                        scdebug("<PIC_ST2-> PIC_ST>:\n");
                        return reserved_token;
                }
                REJECT;
        }
";" { }
{any}   { 
                scdebug("<PICS: any char>: %c\n", yytext[0]);
                yylval.ival=(int)yytext[0];
                return(CHAR); }
"\n" { }
} /* end of PICS */

<<EOF>> {
        yyterminate();
}

.	{svtoken();
         scdebug("invalid character:>>%x<<:\n", (unsigned char)toktext[0]);
         yyerror("invalid character:>>%x<<:\n", (unsigned char)toktext[0]);
	}
%%

int yylex YY_PROTO((void))
{
	prev_token = yylex2();
	/*printf("tok:%x\n", prev_token);*/
	return prev_token;
}

int is_integer_token( char *tok ) {
        while (isdigit(*tok)) tok++;
        if (*tok=='\0') return 1;
        return 0;
}

int is_valid_identifier( char *tok ) {
        while (*tok && !isalpha(*tok)) tok++;
        if (*tok=='\0') {
                return 0;
        }
        return 1;
}

int lex_fgets( char *buf, int maxsize ) {
        int result;
        char *s;
        s = fgets( buf,maxsize,yyin );
        result = (s==NULL) ? YY_NULL: strlen(s);
/*	result = fread( buf, 1, maxsize, yyin); */
        if (result) { 
                result = strlen(buf);
                ++source_lineno; 
        } 
        return result;
}

char *savename1(int x1, int x2) {
  char *s2, *s1;
  int len;
  
  s1 = toktext;
  len = strlen(s1);
  if (len - x1 - x2 > 0) {
    s2 = s1 + len - x2;
    *s2 = '\0';
    s1 = toktext;
    s2 = s1 + x1;
    while (*s1 != '\0') {
      *s1 = *s2;
      s1++;
      s2++;
    }
  }
  return(toktext);
}

/*
char *savename( char *name );
int hash( char *name );
*/

#if defined(SunOS)
va_list __builtin_va_alist;
#endif

void scdebug( char *fmt, ... ) {
        va_list args;
        va_start(args,fmt);
#ifdef DEBUG_SCANNER
        fprintf(stderr,"SCAN(%4d):",source_lineno);
        vfprintf(stderr,fmt,args);
#endif
        va_end(args);
}

int yywrap() { return 1; }

/* end of scan.l */
