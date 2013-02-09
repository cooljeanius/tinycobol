#ifndef lint
/*static char yysccsid[] = "from: @(#)yaccpar	1.9 (Berkeley) 02/21/93";*/
/*static char yyrcsid[] = "$Id: skeleton.c,v 1.2 1997/06/23 02:51:17 tdukes Exp $";*/
static char yyrcsid[] = "from: Version 1.9.3 (Berkeley) 07/23/2001";
#endif
#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 3
#define yyclearin (yychar=(-1))
#define yyerrok (yyerrflag=0)
#define YYRECOVERING (yyerrflag!=0)

typedef int ZYshort;
#define yyparse pp_yyparse
#define yylex pp_yylex
#define yyerror pp_yyerror
#define yychar pp_yychar
#define yyval pp_yyval
#define yylval pp_yylval
#define yydebug pp_yydebug
#define yynerrs pp_yynerrs
#define yyerrflag pp_yyerrflag
#define yyss pp_yyss
#define yyssp pp_yyssp
#define yyvs pp_yyvs
#define yyvsp pp_yyvsp
#define yylhs pp_yylhs
#define yylen pp_yylen
#define yydefred pp_yydefred
#define yydgoto pp_yydgoto
#define yysindex pp_yysindex
#define yyrindex pp_yyrindex
#define yygindex pp_yygindex
#define yytable pp_yytable
#define yycheck pp_yycheck
#define yyname pp_yyname
#define yyrule pp_yyrule
#define YYPREFIX "pp_yy"
#line 24 "pp_parser.y"

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

#line 76 "pp_parser.y"
typedef union {
    char *str;  /* string */
    int  ival;  /* int */
} YYSTYPE;
#line 98 "pp_parser.tab.c"
#define TOK_PSEUDO_TEXT 257
#define TOK_IDENTIFIER 258
#define TOK_LITERAL 259
#define TOK_WORD 260
#define ERROR 261
#define YYERROR_VERBOSE 262
#define TOK_COPY 263
#define TOK_PERIOD 264
#define TOK_OFF 265
#define TOK_BY 266
#define TOK_OF 267
#define TOK_IN 268
#define TOK_REPLACING 269
#define TOK_REPLACE 270
#define TOK_MISC 271
#define TOK_COMMA 272
#define TOK_SOURCE_COMPUTER 273
#define TOK_WITH 274
#define TOK_DEBUGGING 275
#define TOK_MODE 276
#define YYERRCODE 256
ZYshort pp_yylhs[] = {                                        -1,
    0,    0,    8,    8,   11,    9,   13,    9,    9,    9,
    9,    9,    9,    9,    9,   15,   12,   12,   16,   16,
   17,    7,    7,    7,    7,    6,    6,   14,   14,   20,
    5,    5,    1,    2,    3,    4,   19,   19,   18,   18,
   10,   10,   21,   21,   22,   22,
};
ZYshort pp_yylen[] = {                                         2,
    1,    0,    1,    2,    0,    4,    0,    4,    3,    3,
    1,    1,    1,    1,    1,    0,    5,    2,    1,    2,
    4,    1,    1,    1,    1,    2,    0,    1,    2,    4,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    0,
    3,    0,    3,    0,    1,    0,
};
ZYshort pp_yydefred[] = {                                      0,
   13,   14,   15,    7,    0,    0,   12,   11,    0,    0,
    3,    0,   33,    0,    0,    0,    0,    5,    4,   34,
   35,   32,   31,    0,    0,   10,    0,    9,   29,    0,
   37,   38,    0,    0,    8,    0,    0,    6,    0,   26,
   39,   30,   45,    0,    0,    0,   41,    0,   36,   22,
   23,   24,   25,    0,   17,    0,   43,    0,   20,    0,
   21,
};
ZYshort pp_yydgoto[] = {                                       9,
   50,   51,   52,   53,   24,   33,   54,   10,   11,   38,
   30,   25,   12,   16,   39,   55,   56,   42,   34,   17,
   44,   45,
};
ZYshort pp_yysindex[] = {                                   -247,
    0,    0,    0,    0, -252, -254,    0,    0,    0, -247,
    0, -251,    0, -243, -238, -228, -219,    0,    0,    0,
    0,    0,    0, -249, -218,    0, -219,    0,    0, -213,
    0,    0,    0, -251,    0, -225, -226,    0, -220,    0,
    0,    0,    0, -214, -224, -216,    0, -223,    0,    0,
    0,    0,    0, -212,    0, -216,    0, -216,    0, -225,
    0,
};
ZYshort pp_yyrindex[] = {                                     52,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   55,
    0,    0,    0,    0,    0,    0, -228,    0,    0,    0,
    0,    0,    0, -230,    0,    0,    0,    0,    0,    1,
    0,    0, -229,    0,    0, -253, -258,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0, -208,    0,    0,    0, -227,
    0,
};
ZYshort pp_yygindex[] = {                                      0,
   -5,  -10,   -9,    0,   23,    0,    2,    0,   48,    0,
    0,    0,    0,   42,    0,    5,    0,    3,    0,    0,
    0,    0,
};
#define YYTABLESIZE 277
ZYshort pp_yytable[] = {                                      15,
   42,   22,   23,   40,   13,   44,   20,   21,    1,   18,
   40,   15,   14,    2,    3,    4,   46,   31,   32,   37,
   26,   36,    5,   22,   23,    6,    7,   27,    8,   40,
   40,   40,   40,   27,   18,   28,   40,   13,   27,   16,
   13,   20,   21,   49,   20,   35,   41,   43,   46,   47,
   48,    2,   57,   58,    1,   19,   40,   19,   29,   60,
   59,    0,   61,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   42,    0,    0,    0,
    0,   42,   42,   42,    0,    0,    0,    0,    0,    0,
   42,    0,    0,   42,   42,    0,   42,
};
ZYshort pp_yycheck[] = {                                       5,
    0,   12,   12,  257,  257,  264,  258,  259,  256,  264,
  264,   17,  265,  261,  262,  263,  275,  267,  268,   30,
  264,   27,  270,   34,   34,  273,  274,  266,  276,  257,
  258,  259,  260,  264,  264,  264,  264,  257,  269,  269,
  257,  258,  259,  260,  258,  264,  272,  274,  269,  264,
  275,    0,  276,  266,    0,  264,   34,   10,   17,   58,
   56,   -1,   60,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  256,   -1,   -1,   -1,
   -1,  261,  262,  263,   -1,   -1,   -1,   -1,   -1,   -1,
  270,   -1,   -1,  273,  274,   -1,  276,
};
#define YYFINAL 9
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 276
#if YYDEBUG
char *pp_yyname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"TOK_PSEUDO_TEXT",
"TOK_IDENTIFIER","TOK_LITERAL","TOK_WORD","ERROR","YYERROR_VERBOSE","TOK_COPY",
"TOK_PERIOD","TOK_OFF","TOK_BY","TOK_OF","TOK_IN","TOK_REPLACING","TOK_REPLACE",
"TOK_MISC","TOK_COMMA","TOK_SOURCE_COMPUTER","TOK_WITH","TOK_DEBUGGING",
"TOK_MODE",
};
char *pp_yyrule[] = {
"$accept : root",
"root : statements",
"root :",
"statements : statement",
"statements : statements statement",
"$$1 :",
"statement : TOK_SOURCE_COMPUTER TOK_PERIOD $$1 identifier_debug_mode_opt",
"$$2 :",
"statement : TOK_COPY $$2 copy_statement TOK_PERIOD",
"statement : TOK_REPLACE replace_statement TOK_PERIOD",
"statement : TOK_REPLACE TOK_OFF TOK_PERIOD",
"statement : TOK_MODE",
"statement : TOK_WITH",
"statement : error",
"statement : ERROR",
"statement : YYERROR_VERBOSE",
"$$3 :",
"copy_statement : name library_name_opt $$3 TOK_REPLACING replacing_statement",
"copy_statement : name library_name_opt",
"replacing_statement : replacing_statements",
"replacing_statement : replacing_statements replacing_statement",
"replacing_statements : replacing_text TOK_BY replacing_text comma_delimiter_opt",
"replacing_text : pseudo_text",
"replacing_text : identifier",
"replacing_text : literal",
"replacing_text : word",
"library_name_opt : of_in name",
"library_name_opt :",
"replace_statement : replace_statements",
"replace_statement : replace_statements replace_statement",
"replace_statements : pseudo_text TOK_BY pseudo_text comma_delimiter_opt",
"name : literal",
"name : identifier",
"pseudo_text : TOK_PSEUDO_TEXT",
"identifier : TOK_IDENTIFIER",
"literal : TOK_LITERAL",
"word : TOK_WORD",
"of_in : TOK_OF",
"of_in : TOK_IN",
"comma_delimiter_opt : TOK_COMMA",
"comma_delimiter_opt :",
"identifier_debug_mode_opt : identifier debugging_mode_opt TOK_PERIOD",
"identifier_debug_mode_opt :",
"debugging_mode_opt : with_opt TOK_DEBUGGING TOK_MODE",
"debugging_mode_opt :",
"with_opt : TOK_WITH",
"with_opt :",
};
#endif
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 500
#define YYMAXDEPTH 500
#endif
#endif
int yydebug;
int yynerrs;
int yyerrflag;
int yychar;
ZYshort *yyssp;
YYSTYPE *yyvsp;
YYSTYPE yyval;
YYSTYPE yylval;
ZYshort yyss[YYSTACKSIZE];
YYSTYPE yyvs[YYSTACKSIZE];
#define yystacksize YYSTACKSIZE
#line 252 "pp_parser.y"


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
#line 368 "pp_parser.tab.c"
#define YYABORT goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab
#ifdef __cplusplus
extern "C" { 
char * getenv();
int yylex();
int yyparse();
}

#endif
int
#if defined(__STDC__)
yyparse(void)
#else
yyparse()
#endif
{
    register int yym, yyn, yystate;
#if YYDEBUG
    register char *yys;
#ifndef __cplusplus
    extern char *getenv();
#endif

    if (yys = getenv("YYDEBUG"))
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = (-1);

    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yyssp >= yyss + yystacksize - 1)
        {
            goto yyoverflow;
        }
        *++yyssp = yystate = yytable[yyn];
        *++yyvsp = yylval;
        yychar = (-1);
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;
    yyerror("syntax error");
#ifdef lint
    goto yyerrlab;
#endif
yyerrlab:
    ++yynerrs;
yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yyss + yystacksize - 1)
                {
                    goto yyoverflow;
                }
                *++yyssp = yystate = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = (-1);
        goto yyloop;
    }
yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    yyval = yyvsp[1-yym];
    switch (yyn)
    {
case 5:
#line 103 "pp_parser.y"
{
       DEBUGYY_RTN_STR1("yytrace: TOK_SOURCE_COMPUTER TOK_PERIOD\n") 
      }
break;
case 6:
#line 107 "pp_parser.y"
{ 
       identifier_scan_sw--; 
      }
break;
case 7:
#line 111 "pp_parser.y"
{
       DEBUGYY_RTN_STR1("yytrace: TOK_COPY\n") 
      }
break;
case 8:
#line 115 "pp_parser.y"
{ 
       copy_state_sw--;
       copy_start_sw++;
       identifier_scan_sw--;
      }
break;
case 9:
#line 121 "pp_parser.y"
{ 
       replace_state_sw--;  
       replace_start_sw++;
       identifier_scan_sw--;
      }
break;
case 10:
#line 127 "pp_parser.y"
{ 
       replace_state_sw--;  
       replace_start_sw--;
       identifier_scan_sw--;
      }
break;
case 11:
#line 132 "pp_parser.y"
{ }
break;
case 12:
#line 133 "pp_parser.y"
{ }
break;
case 13:
#line 135 "pp_parser.y"
{
/*        globalEnvPtr->errFlag = 11; */
        errcnt++;
        return 11; 
      }
break;
case 14:
#line 141 "pp_parser.y"
{
/*        globalEnvPtr->errFlag = 12; */
        errcnt++;
        return 12; 
      }
break;
case 15:
#line 147 "pp_parser.y"
{
/*        globalEnvPtr->errFlag = 13; */
        errcnt++;
        return 13; 
      }
break;
case 16:
#line 155 "pp_parser.y"
{ 
     /*include_filename = $1; */ 
     include_cpybook  = yyvsp[-1].str;
     include_cpylib   = yyvsp[0].str;
     DEBUGYY_RTN_STR15("yytrace: copy_statement: name=%s, lib=%s;\n", include_cpybook, include_cpylib) 
    }
break;
case 18:
#line 163 "pp_parser.y"
{ 
     /*include_filename = $1;*/
     include_cpybook  = yyvsp[-1].str;
     include_cpylib   = yyvsp[0].str;
     DEBUGYY_RTN_STR15("yytrace: copy_statement: name=%s, lib=%s;\n", include_cpybook, include_cpylib) 
    }
break;
case 21:
#line 176 "pp_parser.y"
{
       add_copy_replacement(yyvsp[-3].str,yyvsp[-1].str); 
       DEBUGYY_RTN_STR15("yytrace: replacing_statements: \'%s\' BY \'%s\':\n", yyvsp[-3].str, yyvsp[-1].str) 
      }
break;
case 22:
#line 182 "pp_parser.y"
{ yyval.str=yyvsp[0].str; }
break;
case 23:
#line 183 "pp_parser.y"
{ yyval.str=yyvsp[0].str; }
break;
case 24:
#line 184 "pp_parser.y"
{ yyval.str=yyvsp[0].str; }
break;
case 25:
#line 185 "pp_parser.y"
{ yyval.str=yyvsp[0].str; }
break;
case 26:
#line 188 "pp_parser.y"
{ yyval.str=yyvsp[0].str; }
break;
case 27:
#line 189 "pp_parser.y"
{ yyval.str=NULL;  }
break;
case 30:
#line 197 "pp_parser.y"
{ 
       add_replace_replacement(yyvsp[-3].str,yyvsp[-1].str); 
     }
break;
case 31:
#line 202 "pp_parser.y"
{ yyval.str=yyvsp[0].str; }
break;
case 32:
#line 203 "pp_parser.y"
{ yyval.str=yyvsp[0].str; }
break;
case 33:
#line 206 "pp_parser.y"
{ yyval.str=yyvsp[0].str; }
break;
case 34:
#line 210 "pp_parser.y"
{ 
       DEBUGYY_RTN_STR3("yytrace: identifier: \'%s\'\n", yyvsp[0].str) 
       yyval.str=yyvsp[0].str; 
     }
break;
case 35:
#line 216 "pp_parser.y"
{ yyval.str=yyvsp[0].str; }
break;
case 36:
#line 219 "pp_parser.y"
{ yyval.str=yyvsp[0].str; }
break;
case 41:
#line 231 "pp_parser.y"
{
      DEBUGYY_RTN_STR1("yytrace: identifier debugging_mode_opt TOK_PERIOD\n") 
     }
break;
case 43:
#line 239 "pp_parser.y"
{ 
/*       globalEnv.IncDebugLines = 1;  */
       HTG_debug_lines_flag = TRUE;
       DEBUGYY_RTN_STR1("yytrace: with_opt TOK_DEBUGGING TOK_MODE \n") 
     }
break;
#line 689 "pp_parser.tab.c"
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yyssp, yystate);
#endif
    if (yyssp >= yyss + yystacksize - 1)
    {
        goto yyoverflow;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;
    goto yyloop;
yyoverflow:
    yyerror("yacc stack overflow");
yyabort:
    return (1);
yyaccept:
    return (0);
}
