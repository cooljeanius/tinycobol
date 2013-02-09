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
typedef union {
    char *str;  /* string */
    int  ival;  /* int */
} YYSTYPE;
extern YYSTYPE pp_yylval;
