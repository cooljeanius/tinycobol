/* 
 *  Copyright (C) 2001, 2000, 1999,  Rildo Pragana, David Essex. 
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

#include "htcoboly.h"
#include "htcobol.tab.h"
#include "reswords.h"
#include "htcoblib.h"

struct reserved_symbol reserved_symbols[] = {
  {"<",                     CONDITIONAL,            LESS,           TCOB_KW_STD},
  {"<=",                    CONDITIONAL,            LEQ,            TCOB_KW_STD85},
  {"<>",                    CONDITIONAL,            NEQ,            TCOB_KW_STD},
  {"=",                     CONDITIONAL,            EQUAL,          TCOB_KW_STD},
  {">",                     CONDITIONAL,            GREATER,        TCOB_KW_STD},
  {">=",                    CONDITIONAL,            GEQ,            TCOB_KW_STD85},
  {"ACCEPT",                ACCEPT,                 0,              TCOB_KW_STD},
  {"ACCESS",                ACCESS,                 0,              TCOB_KW_STD},
  {"ADD",                   ADD,                    0,              TCOB_KW_STD},
  {"ADDRESS",               ADDRESS,                0,              TCOB_KW_STD85},
  {"ADVANCING",             ADVANCING,              0,              TCOB_KW_STD},
  {"AFTER",                 AFTER,                  0,              TCOB_KW_STD},
  {"ALL",                   ALL,                    0,              TCOB_KW_STD},
  {"ALPHABET",              ALPHABET,               0,              TCOB_KW_STD85},
  {"ALPHABETIC",            ALPHABETIC_TOK,         0,              TCOB_KW_STD},
  {"ALPHABETIC-LOWER",      ALPHABETIC_LOWER,       0,              TCOB_KW_STD},
  {"ALPHABETIC-UPPER",      ALPHABETIC_UPPER,       0,              TCOB_KW_STD},
  {"ALPHANUMERIC",          ALPHANUMERIC,           0,              TCOB_KW_STD85},
  {"ALPHANUMERIC-EDITED",   ALPHANUMERIC_EDITED,    0,              TCOB_KW_STD85},
  {"ALSO",                  ALSO,                   0,              TCOB_KW_STD},
  {"ALTERNATE",             ALTERNATE,              0,              TCOB_KW_STD},
  {"AND",                   AND,                    0,              TCOB_KW_STD},
  {"ANY",                   ANY,                    0,              TCOB_KW_STD85},
  {"ARE",                   ARE,                    0,              TCOB_KW_STD},
  {"AREA",                  AREA,                   0,              TCOB_KW_STD},
  {"AREAS",                 AREAS,                  0,              TCOB_KW_STD},
  {"ASCENDING",             DIRECTION,              ASCENDING,      TCOB_KW_STD},
  {"ASSIGN",                ASSIGN,                 0,              TCOB_KW_STD},
  {"AT",                    AT,                     0,              TCOB_KW_STD},
  {"AUTHOR",                AUTHOR,                 0,              TCOB_KW_STD},
  {"AUTO",                  AUTO,                   0,              TCOB_KW_STD},
  {"BACKGROUND-COLOR",      BACKGROUNDCOLOR,        0,              TCOB_KW_STD},
  {"BEFORE",                BEFORE,                 0,              TCOB_KW_STD},
  {"BELL",                  BELL,                   0,              TCOB_KW_STD85},
  {"BINARY",                USAGENUM,               USAGE_COMP,     TCOB_KW_STD85},
  {"BINARY-CHAR",           USAGENUM,               USAGE_BINARY_CHAR,   TCOB_KW_STD2},                
  {"BINARY-DOUBLE",         USAGENUM,               USAGE_BINARY_DOUBLE, TCOB_KW_STD2},
  {"BINARY-LONG",           USAGENUM,               USAGE_BINARY_LONG,   TCOB_KW_STD2},                
  {"BINARY-SHORT",          USAGENUM,               USAGE_BINARY_SHORT,  TCOB_KW_STD2},
  {"BLANK",                 BLANK,                  0,              TCOB_KW_STD},
  {"BLINK",                 BLINK,                  0,              TCOB_KW_STD},
  {"BLOCK",                 BLOCK,                  0,              TCOB_KW_STD},
  {"BOTTOM",                BOTTOM,                 0,              TCOB_KW_STD},
  {"BY",                    BY,                     0,              TCOB_KW_STD},
  {"CALL",                  CALL,                   0,              TCOB_KW_STD},
  {"CALL-LOADLIB",          CALL_LOADLIB,           0,              TCOB_KW_TCEXT},
  {"CANCEL",                CANCEL,                 0,              TCOB_KW_STD},
  {"CDECL",                 CALL_CONV_C,            0,              TCOB_KW_TCEXT},
  {"CENTER",                CENTER,                 0,              TCOB_KW_STD2},
  {"CF",                    CF,                     0,              TCOB_KW_STD},
  {"CH",                    CH,                     0,              TCOB_KW_STD},
  {"CHAIN",                 CHAIN,                  0,              TCOB_KW_TCEXT},
  {"CHAINING",              CHAINING,               0,              TCOB_KW_STD85},
  {"CHARACTER",             CHARACTER,              0,              TCOB_KW_STD},
  {"CHARACTERS",            CHARACTERS,             0,              TCOB_KW_STD},
  {"CLASS",                 CLASS,                  0,              TCOB_KW_STD85},
  {"CLOSE",                 CLOSE,                  0,              TCOB_KW_STD},
  {"CODE",                  CODE,                   0,              TCOB_KW_STD},
  {"CODE-SET",              CODE_SET,               0,              TCOB_KW_STD},
  {"COL",                   COLUMN,                 0,              TCOB_KW_STD},
  {"COLS",                  COLUMNS,                0,              TCOB_KW_STD2},
  {"COLLATING",             COLLATING,              0,              TCOB_KW_STD},
  {"COLOR",                 COLOR,                  0,              TCOB_KW_STD},
  {"COLUMN",                COLUMN,                 0,              TCOB_KW_STD},
  {"COLUMNS",               COLUMNS,                0,              TCOB_KW_STD2},
 /* {"COM1",                  PORTNUM,                8,              TCOB_KW_TCEXT}, */
 /*  {"COM2",                  PORTNUM,                1,              TCOB_KW_TCEXT}, */
 /*  {"COM3",                  PORTNUM,                2,              TCOB_KW_TCEXT}, */
 /*  {"COM4",                  PORTNUM,                3,              TCOB_KW_TCEXT}, */
  {"COMMA",                 COMMA,                  0,              TCOB_KW_STD},
  {"COMMAND-LINE",          CMD_LINE,               0,              TCOB_KW_TCEXT},
  {"COMMON",                COMMON,                 0,              TCOB_KW_STD85},
  {"COMP",                  USAGENUM,               USAGE_COMP,     TCOB_KW_STD},
  {"COMP-1",                USAGENUM,               USAGE_COMP1,    TCOB_KW_STD},
  {"COMP-2",                USAGENUM,               USAGE_COMP2,    TCOB_KW_STD},
  {"COMP-3",                USAGENUM,               USAGE_COMP3,    TCOB_KW_TCEXT},
  {"COMP-5",                USAGENUM,               USAGE_COMP5,    TCOB_KW_TCEXT},
  {"COMP-X",                USAGENUM,               USAGE_COMPX,    TCOB_KW_STD},
  {"COMPUTATIONAL",         USAGENUM,               USAGE_COMP,     TCOB_KW_STD},
  {"COMPUTATIONAL-1",       USAGENUM,               USAGE_COMP1,    TCOB_KW_STD},
  {"COMPUTATIONAL-2",       USAGENUM,               USAGE_COMP2,    TCOB_KW_STD},
  {"COMPUTATIONAL-3",       USAGENUM,               USAGE_COMP3,    TCOB_KW_TCEXT},
  {"COMPUTATIONAL-5",       USAGENUM,               USAGE_COMP5,    TCOB_KW_TCEXT},
  {"COMPUTATIONAL-X",       USAGENUM,               USAGE_COMPX,    TCOB_KW_STD},
  {"COMPUTE",               COMPUTE,                0,              TCOB_KW_STD},
  {"CONFIGURATION",         CONFIGURATION,          0,              TCOB_KW_STD},
  {"CONSOLE",               CONSOLE,                0,              TCOB_KW_STD},
  {"CONTAINS",              CONTAINS,               0,              TCOB_KW_STD},
  {"CONTENT",               CONTENT,                0,              TCOB_KW_STD85},
  {"CONTINUE",              CONTINUE,               0,              TCOB_KW_STD85},
  {"CONTROL",               CONTROL,                0,              TCOB_KW_STD},
  {"CONTROLS",              CONTROLS,               0,              TCOB_KW_STD},
  {"CONVERTING",            CONVERTING,             0,              TCOB_KW_STD85},
/*{"COPY",                  COPY,                   0,              TCOB_KW_STD}, used by pre-processor only */
  {"CORR",                  CORRESPONDING,          0,              TCOB_KW_STD},
  {"CORRESPONDING",         CORRESPONDING,          0,              TCOB_KW_STD},
  {"COUNT",                 COUNT,                  0,              TCOB_KW_STD},
  {"CRT",                   DISPLAY_SCREEN,         0,              TCOB_KW_TCEXT},
  {"CURRENCY",              CURRENCY,               0,              TCOB_KW_STD},
  {"CURSOR",                CURSOR,                 0,              TCOB_KW_STD},
/*{"DARK",                  DARK,                   0,              TCOB_KW_TCEXT}, not used */
  {"DATA",                  DATA,                   0,              TCOB_KW_STD},
  {"DATE",                  DATE_TIME,              DATE,           TCOB_KW_STD},
  {"DATE-COMPILED",         DATE_COMPILED,          0,              TCOB_KW_STD},
  {"DATE-WRITTEN",          DATE_WRITTEN,           0,              TCOB_KW_STD},
  {"DAY",                   DATE_TIME,              DAY,            TCOB_KW_STD},
  {"DAY-OF-WEEK",           DATE_TIME,              DAY_OF_WEEK,    TCOB_KW_STD85},
  {"DE",                    DE,                     0,              TCOB_KW_STD},
  {"DEBUGGING",             DEBUGGING,              0,              TCOB_KW_STD},
  {"DECIMAL-POINT",         DECIMAL_POINT,          0,              TCOB_KW_STD},
  {"DECLARATIVES",          DECLARATIVES,           0,              TCOB_KW_STD},
  {"DELETE",                DELETE,                 0,              TCOB_KW_STD},
  {"DELIMITED",             DELIMITED,              0,              TCOB_KW_STD},
  {"DELIMITER",             DELIMITER,              0,              TCOB_KW_STD},
  {"DEPENDING",             DEPENDING,              0,              TCOB_KW_STD},
  {"DESCENDING",            DIRECTION,              DESCENDING,     TCOB_KW_STD},
  {"DETAIL",                DETAIL,                 0,              TCOB_KW_STD},
  {"DISK",                  DISK,                0,              TCOB_KW_STD},
  {"DISPLAY",               DISPLAY,                0,              TCOB_KW_STD},
  {"DIVIDE",                DIVIDE,                 0,              TCOB_KW_STD},
  {"DIVISION",              DIVISION,               0,              TCOB_KW_STD},
  {"DOWN",                  DOWN,                   0,              TCOB_KW_STD},
  {"DUPLICATES",            DUPLICATES,             0,              TCOB_KW_STD},
  {"DYNAMIC",               DYNAMIC,                0,              TCOB_KW_STD},
/*{"ECHO",                  ECHOT,                  0,              TCOB_KW_TCEXT}, not used */
  {"ELSE",                  ELSE,                   0,              TCOB_KW_STD},
  {"END",                   END,                    0,              TCOB_KW_STD},
  {"END-ACCEPT",            END_ACCEPT,             0,              TCOB_KW_STD85},
  {"END-ADD",               END_ADD,                0,              TCOB_KW_STD85},
  {"END-CALL-LOADLIB",      END_CALL_LOADLIB,       0,              TCOB_KW_TCEXT},
  {"END-CALL",              END_CALL,               0,              TCOB_KW_STD85},
  {"END-CHAIN",             END_CHAIN,              0,              TCOB_KW_STD85},
  {"END-COMPUTE",           END_COMPUTE,            0,              TCOB_KW_STD85},
  {"END-DELETE",            END_DELETE,             0,              TCOB_KW_STD85},
  {"END-DISPLAY",           END_DISPLAY,            0,              TCOB_KW_STD85},
  {"END-DIVIDE",            END_DIVIDE,             0,              TCOB_KW_STD85},
  {"END-EVALUATE",          END_EVALUATE,           0,              TCOB_KW_STD85},
  {"END-IF",                END_IF,                 0,              TCOB_KW_STD85},
  {"END-MULTIPLY",          END_MULTIPLY,           0,              TCOB_KW_STD85},
  {"END-OF-PAGE",           END_OF_PAGE,            0,              TCOB_KW_STD},
  {"END-PERFORM",           END_PERFORM,            0,              TCOB_KW_STD85},
  {"END-READ",              END_READ,               0,              TCOB_KW_STD85},
  {"END-RETURN",            END_RETURN,             0,              TCOB_KW_STD85},
  {"END-REWRITE",           END_REWRITE,            0,              TCOB_KW_STD85},
  {"END-SEARCH",            END_SEARCH,             0,              TCOB_KW_STD85},
  {"END-START",             END_START,              0,              TCOB_KW_STD85},
  {"END-STRING",            END_STRINGCMD,          0,              TCOB_KW_STD85},
  {"END-SUBTRACT",          END_SUBTRACT,           0,              TCOB_KW_STD85},
  {"END-UNSTRING",          END_UNSTRING,           0,              TCOB_KW_STD85},
  {"END-WRITE",             END_WRITE,              0,              TCOB_KW_STD85},
  {"ENVIRONMENT",           ENVIRONMENT,            0,              TCOB_KW_STD},
  {"ENVIRONMENT-VARIABLE",  ENVIRONMENT_VARIABLE,   0,              TCOB_KW_TCEXT},
  {"EOL",                   EOL,                    0,              TCOB_KW_TCEXT},
  {"EOP",                   END_OF_PAGE,            0,              TCOB_KW_STD},
  {"EOS",                   EOS,                    0,              TCOB_KW_TCEXT},
  {"EQUAL",                 CONDITIONAL,            EQUAL,          TCOB_KW_STD},
  {"ERASE",                 ERASE,                  0,              TCOB_KW_STD},
  {"ERROR",                 ERROR_TOK,              0,              TCOB_KW_STD},
  {"EVALUATE",              EVALUATE,               0,              TCOB_KW_STD85},
  {"EXCEPTION",             EXCEPTION,              0,              TCOB_KW_STD},
  {"EXIT",                  EXIT,                   0,              TCOB_KW_STD},
  {"EXTEND",                EXTEND,                 0,              TCOB_KW_STD},
  {"EXTERNAL",              EXTERNAL,               0,              TCOB_KW_STD85},
  {"FALSE",                 FALSE_TOK,              0,              TCOB_KW_STD85},
  {"FD",                    FD,                     0,              TCOB_KW_STD},
  {"FILE",                  FILE_TOK,               0,              TCOB_KW_STD},
  {"FILE-CONTROL",          FILE_CONTROL,           0,              TCOB_KW_STD},
  {"FILE-ID",               FILE_ID,                0,              TCOB_KW_STD},
  {"FILLER",                FILLER,                 0,              TCOB_KW_STD},
  {"FINAL",                 FINAL,                  0,              TCOB_KW_STD},
  {"FIRST",                 FIRST,                  0,              TCOB_KW_STD},
  {"FLOAT-LONG",            USAGENUM,               USAGE_COMP2,    TCOB_KW_STD2},
  {"FLOAT-SHORT",           USAGENUM,               USAGE_COMP1,    TCOB_KW_STD2},
  {"FOOTING",               FOOTING,                0,              TCOB_KW_STD},
  {"FOR",                   FOR,                    0,              TCOB_KW_STD},
  {"FOREGROUND-COLOR",      FOREGROUNDCOLOR,        0,              TCOB_KW_STD85},
  {"FROM",                  FROM,                   0,              TCOB_KW_STD},
  {"FULL",                  FULL,                   0,              TCOB_KW_STD},
  {"FUNCTION",              FUNCTION,               0,              TCOB_KW_STD85},
  {"GENERATE",              GENERATE,               0,              TCOB_KW_STD},
  {"GIVING",                GIVING,                 0,              TCOB_KW_STD},
  {"GLOBAL",                GLOBAL,                 0,              TCOB_KW_STD85},
  {"GO",                    GO,                     0,              TCOB_KW_STD},
  {"GOBACK",                GOBACK,                 0,              TCOB_KW_TCEXT},
  {"GREATER",               CONDITIONAL,            GREATER,        TCOB_KW_STD},
  {"GROUP",                 GROUP,                  0,              TCOB_KW_STD},
  {"HEADING",               HEADING,                0,              TCOB_KW_STD},
  {"HIGH-VALUE",            HIGHVALUES,             0,              TCOB_KW_STD},
  {"HIGH-VALUES",           HIGHVALUES,             0,              TCOB_KW_STD},
  {"HIGHLIGHT",             HIGHLIGHT,              0,              TCOB_KW_TCEXT},
  {"I-O",                   I_O,                    0,              TCOB_KW_STD},
  {"I-O-CONTROL",           I_O_CONTROL,            0,              TCOB_KW_STD},
  {"IDENTIFICATION",        IDENTIFICATION,         0,              TCOB_KW_STD},
  {"IF",                    IF,                     0,              TCOB_KW_STD},
  {"IGNORE",                IGNORE,                 0,              TCOB_KW_TCEXT},
  {"IN",                    IN,                     0,              TCOB_KW_STD},
  {"INDEX",                 USAGENUM,               USAGE_INDEX,    TCOB_KW_STD},
  {"INDEXED",               INDEXED,                0,              TCOB_KW_STD},
  {"INDICATE",              INDICATE,               0,              TCOB_KW_STD},
  {"INITIAL",               INITIAL_TOK,            0,              TCOB_KW_STD},
  {"INITIALIZE",            INITIALIZE,             0,              TCOB_KW_STD85},
  {"INITIATE",              INITIATE,               0,              TCOB_KW_STD},
  {"INKEY",                 INKEY,                  0,              TCOB_KW_TCEXT},
  {"INPUT",                 INPUT,                  0,              TCOB_KW_STD},
  {"INPUT-OUTPUT",          INPUT_OUTPUT,           0,              TCOB_KW_STD},
  {"INSPECT",               INSPECT,                0,              TCOB_KW_STD},
  {"INSTALLATION",          INSTALLATION,           0,              TCOB_KW_STD},
  {"INTO",                  INTO,                   0,              TCOB_KW_STD},
  {"INVALID",               INVALID,                0,              TCOB_KW_STD},
  {"IS",                    IS,                     0,              TCOB_KW_STD},
  {"JUST",                  JUSTIFIED,              0,              TCOB_KW_STD},
  {"JUSTIFIED",             JUSTIFIED,              0,              TCOB_KW_STD},
  {"KEY",                   KEY,                    0,              TCOB_KW_STD},
  {"KEYBOARD",              STD_INPUT,              0,              TCOB_KW_TCEXT},
  {"LABEL",                 LABEL,                  0,              TCOB_KW_STD},
  {"LAST",                  LAST,                   0,              TCOB_KW_STD},
  {"LEADING",               LEADING,                0,              TCOB_KW_STD},
  {"LEFT",                  LEFT,                   0,              TCOB_KW_STD},
  {"LENGTH",                LENGTH,                 0,              TCOB_KW_STD},
  {"LESS",                  CONDITIONAL,            LESS,           TCOB_KW_STD},
  {"LIMIT",                 LIMIT,                  0,              TCOB_KW_STD},
  {"LIMITS",                LIMITS,                 0,              TCOB_KW_STD},
  {"LINAGE",                LINAGE,                 0,              TCOB_KW_STD},
  {"LINE",                  LINE,                   0,              TCOB_KW_STD},
  {"LINES",                 LINES,                  0,              TCOB_KW_STD},
  {"LINKAGE",               LINKAGE,                0,              TCOB_KW_STD},
  {"LOCK",                  LOCK,                   0,              TCOB_KW_STD},
  {"LOW-VALUE",             LOWVALUES,              0,              TCOB_KW_STD},
  {"LOW-VALUES",            LOWVALUES,              0,              TCOB_KW_STD},
  {"LOWER",                 LOWER,                  0,              TCOB_KW_STD},
  {"LOWLIGHT",              LOWLIGHT,               0,              TCOB_KW_STD},
/*  {"LPT1",                  PORTNUM,                4,              TCOB_KW_TCEXT}, */
/*  {"LPT2",                  PORTNUM,                5,              TCOB_KW_TCEXT}, */
/*  {"LPT3",                  PORTNUM,                6,              TCOB_KW_TCEXT}, */
/*  {"LPT4",                  PORTNUM,                7,              TCOB_KW_TCEXT}, */
  {"MERGE",                 MERGE,                  0,              TCOB_KW_STD},
  {"MINUS",                 MINUS,                  0,              TCOB_KW_STD},
  {"MODE",                  MODE,                   0,              TCOB_KW_STD},
  {"MOVE",                  MOVE,                   0,              TCOB_KW_STD},
  {"MULTIPLE",              MULTIPLE,               0,              TCOB_KW_STD},
  {"MULTIPLY",              MULTIPLY,               0,              TCOB_KW_STD},
  {"NATIVE",                NATIVE,                 0,              TCOB_KW_STD},
  {"NEGATIVE",              NEGATIVE,               0,              TCOB_KW_STD},
  {"NEXT",                  NEXT,                   0,              TCOB_KW_STD},
  {"NO",                    NO,                     0,              TCOB_KW_STD},
  {"NO-ECHO",               NOECHO,                 0,              TCOB_KW_TCEXT},
  {"NOT",                   NOT,                    0,              TCOB_KW_STD},
  {"NULL",                  NULL_TOK,               0,              TCOB_KW_STD},
  {"NUMBER",                NUMBER,                 0,              TCOB_KW_STD},
  {"NUMBERS",               NUMBERS,                0,              TCOB_KW_STD},
  {"NUMERIC",               NUMERIC,                0,              TCOB_KW_STD},
  {"NUMERIC-EDITED",        NUMERIC_EDITED,         0,              TCOB_KW_STD},
  {"OBJECT-COMPUTER",       OBJECT_COMPUTER,        0,              TCOB_KW_STD},
  {"OCCURS",                OCCURS,                 0,              TCOB_KW_STD},
  {"OF",                    OF,                     0,              TCOB_KW_STD},
  {"OFF",                   OFF,                    0,              TCOB_KW_STD},
  {"OMITTED",               OMITTED,                0,              TCOB_KW_STD},
  {"ON",                    ON,                     0,              TCOB_KW_STD},
  {"ONLY",                  ONLY,                   0,              TCOB_KW_STD},
  {"OPEN",                  OPEN,                   0,              TCOB_KW_STD},
  {"OPTIONAL",              OPTIONAL,               0,              TCOB_KW_STD},
  {"OR",                    OR,                     0,              TCOB_KW_STD},
  {"ORDER",                 ORDER,                  0,              TCOB_KW_STD85},
  {"ORGANIZATION",          ORGANIZATION,           0,              TCOB_KW_STD},
  {"OTHER",                 OTHER,                  0,              TCOB_KW_STD85},
  {"OUTPUT",                OUTPUT,                 0,              TCOB_KW_STD},
  {"OVERFLOW",              OVERFLOW_TOK,           0,              TCOB_KW_STD},
  {"PACKED-DECIMAL",        USAGENUM,               USAGE_COMP3,    TCOB_KW_STD85},
  {"PADDING",               PADDING,                0,              TCOB_KW_STD85},
  {"PAGE",                  PAGE_TOK,               0,              TCOB_KW_STD},
  {"PAGE-COUNTER",          PAGE_COUNTER,           0,              TCOB_KW_STD},
  {"PARAGRAPH",             PARAGRAPH,              0,              TCOB_KW_STD2},
  {"PERFORM",               PERFORM,                0,              TCOB_KW_STD},
  {"PF",                    PF,                     0,              TCOB_KW_STD},
  {"PH",                    PH,                     0,              TCOB_KW_STD},
  {"PIC",                   PICTURE,                0,              TCOB_KW_STD},
  {"PICTURE",               PICTURE,                0,              TCOB_KW_STD},
  {"PLUS",                  PLUS,                   0,              TCOB_KW_STD},
  {"POINTER",               POINTER,                0,              TCOB_KW_STD},
  {"POSITION",              POSITION,               0,              TCOB_KW_STD},
  {"POSITIVE",              POSITIVE,               0,              TCOB_KW_STD},
  {"PREV",                  PREVIOUS,               0,              TCOB_KW_STD},
  {"PREVIOUS",              PREVIOUS,               0,              TCOB_KW_STD},
  {"PRINTER",               PRINTER,                0,              TCOB_KW_STD},
  {"PROCEDURE",             PROCEDURE,              0,              TCOB_KW_STD},
  {"PROCEDURES",            PROCEDURES,             0,              TCOB_KW_STD},
  {"PROCEED",               PROCEED,                0,              TCOB_KW_STD},
  {"PROGRAM",               PROGRAM,                0,              TCOB_KW_STD},
  {"PROGRAM-ID",            PROGRAM_ID,             0,              TCOB_KW_STD},
  {"QUOTE",                 QUOTES,                 0,              TCOB_KW_STD},
  {"QUOTES",                QUOTES,                 0,              TCOB_KW_STD},
  {"RANDOM",                RANDOM,                 0,              TCOB_KW_STD},
  {"RD",                    RD,                     0,              TCOB_KW_STD},
  {"READ",                  READ,                   0,              TCOB_KW_STD},
  {"READY",                 READY,                  0,              TCOB_KW_STD},
  {"RECORD",                RECORD,                 0,              TCOB_KW_STD},
  {"RECORDS",               RECORDS,                0,              TCOB_KW_STD},
  {"REDEFINES",             REDEFINES,              0,              TCOB_KW_STD},
  {"REFERENCE",             REFERENCE,              0,              TCOB_KW_STD85},
  {"REFERENCES",            REFERENCES,             0,              TCOB_KW_STD85},
  {"REEL",                  REEL,                   0,              TCOB_KW_STD},
  {"RELATIVE",              RELATIVE,               0,              TCOB_KW_STD},
  {"RELEASE",               RELEASE,                0,              TCOB_KW_STD},
  {"REMAINDER",             REMAINDER,              0,              TCOB_KW_STD},
  {"REMOVAL",               REMOVAL,                0,              TCOB_KW_STD},
  {"RENAMES",               RENAMES,                0,              TCOB_KW_STD},
  {"REPLACING",             REPLACING,              0,              TCOB_KW_STD},
  {"REPORT",                REPORT,                 0,              TCOB_KW_STD},
  {"REPORTING",             REPORTING,              0,              TCOB_KW_STD},
  {"REPORTS",               REPORTS,                0,              TCOB_KW_STD},
  {"REQUIRED",              REQUIRED,               0,              TCOB_KW_STD},
  {"RESERVE",               RESERVE,                0,              TCOB_KW_STD},
  {"RESET",                 RESET,                  0,              TCOB_KW_STD},
  {"RETURN",                RETURN_TOK,             0,              TCOB_KW_STD},
  {"RETURNING",             RETURNING,              0,              TCOB_KW_STD},
  {"REVERSE-VIDEO",         REVERSEVIDEO,           0,              TCOB_KW_TCEXT},
  {"REWIND",                REWIND,                 0,              TCOB_KW_STD},
  {"REWRITE",               REWRITE,                0,              TCOB_KW_STD},
  {"RF",                    RF,                     0,              TCOB_KW_STD},
  {"RH",                    RH,                     0,              TCOB_KW_STD},
  {"RIGHT",                 RIGHT,                  0,              TCOB_KW_STD},
  {"ROUNDED",               ROUNDED,                0,              TCOB_KW_STD},
  {"RUN",                   RUN,                    0,              TCOB_KW_STD},
  {"SAME",                  SAME,                   0,              TCOB_KW_STD},
  {"SCREEN",                SCREEN,                 0,              TCOB_KW_STD},
  {"SD",                    SD,                     0,              TCOB_KW_STD},
  {"SEARCH",                SEARCH,                 0,              TCOB_KW_STD},
  {"SECTION",               SECTION,                0,              TCOB_KW_STD},
  {"SECURE",                SECURE,                 0,              TCOB_KW_STD},
  {"SECURITY",              SECURITY,               0,              TCOB_KW_STD},
  {"SELECT",                SELECT,                 0,              TCOB_KW_STD},
  {"SENTENCE",              SENTENCE,               0,              TCOB_KW_STD},
  {"SEPARATE",              SEPARATE,               0,              TCOB_KW_STD},
  {"SEQUENCE",              SEQUENCE,               0,              TCOB_KW_STD},
  {"SEQUENTIAL",            SEQUENTIAL,             0,              TCOB_KW_STD},
  {"SET",                   SET,                    0,              TCOB_KW_STD},
  {"SIGN",                  SIGN,                   0,              TCOB_KW_STD},
  {"SIZE",                  SIZE,                   0,              TCOB_KW_STD},
  {"SORT",                  SORT,                   0,              TCOB_KW_STD},
  {"SORT-MERGE",            SORT_MERGE,             0,              TCOB_KW_STD},
  {"SOURCE",                SOURCE,                 0,              TCOB_KW_STD},
  {"SOURCE-COMPUTER",       SOURCE_COMPUTER,        0,              TCOB_KW_STD},
  {"SPACE",                 SPACES,                 0,              TCOB_KW_STD},
  {"SPACES",                SPACES,                 0,              TCOB_KW_STD},
  {"SPECIAL-NAMES",         SPECIAL_NAMES,          0,              TCOB_KW_STD},
  {"STANDARD",              STANDARD,               0,              TCOB_KW_STD},
  {"STANDARD-1",            STANDARD_1,             0,              TCOB_KW_STD},
  {"STANDARD-2",            STANDARD_2,             0,              TCOB_KW_STD85},
  {"STANDARD-ERROR",        STD_ERROR,              0,              TCOB_KW_TCEXT},
  {"STANDARD-INPUT",        STD_INPUT,              0,              TCOB_KW_TCEXT},
  {"STANDARD-OUTPUT",       STD_OUTPUT,             0,              TCOB_KW_TCEXT},
  {"START",                 START,                  0,              TCOB_KW_STD},
  {"STATUS",                STATUS,                 0,              TCOB_KW_STD},
  {"STDCALL",               CALL_CONV_STDCALL,      0,              TCOB_KW_TCEXT},
  {"STD-ERROR",             STD_ERROR,              0,              TCOB_KW_TCEXT},
  {"STD-INPUT",             STD_INPUT,              0,              TCOB_KW_TCEXT},
  {"STD-OUTPUT",            STD_OUTPUT,             0,              TCOB_KW_TCEXT},
  {"STOP",                  STOP,                   0,              TCOB_KW_STD},
  {"STRING",                STRINGCMD,              0,              TCOB_KW_STD},
  {"SUBTRACT",              SUBTRACT,               0,              TCOB_KW_STD},
  {"SUM",                   SUM,                    0,              TCOB_KW_STD},
  {"SYNC",                  SYNCHRONIZED,           0,              TCOB_KW_STD},
  {"SYNCHRONIZED",          SYNCHRONIZED,           0,              TCOB_KW_STD},
/* {"SYSERR",                STD_ERROR,              0,              TCOB_KW_TCEXT}, */
/* {"SYSIN",                 STD_INPUT,              0,              TCOB_KW_TCEXT}, */
/* {"SYSIPT",                STD_INPUT,              0,              TCOB_KW_TCEXT}, */
/* {"SYSOUT",                STD_OUTPUT,             0,              TCOB_KW_TCEXT}, */
  {"TALLYING",              TALLYING,               0,              TCOB_KW_STD},
  {"TAPE",                  TAPE,                   0,              TCOB_KW_STD},
  {"TCOB-PROTOTYPE1",       TCOBPROTO1,             0,              TCOB_KW_TCEXT},
  {"TCOB-PROTOTYPE2",       TCOBPROTO2,             0,              TCOB_KW_TCEXT},
  {"TERMINATE",             TERMINATE,              0,              TCOB_KW_STD},
  {"TEST",                  TEST,                   0,              TCOB_KW_STD},
  {"THAN",                  THAN,                   0,              TCOB_KW_STD},
  {"THEN",                  THEN,                   0,              TCOB_KW_STD},
  {"THROUGH",               THRU,                   0,              TCOB_KW_STD},
  {"THRU",                  THRU,                   0,              TCOB_KW_STD},
  {"TIME",                  DATE_TIME,              TIME,           TCOB_KW_STD},
  {"TIMES",                 TIMES,                  0,              TCOB_KW_STD},
  {"TO",                    TO,                     0,              TCOB_KW_STD},
  {"TOP",                   TOP,                    0,              TCOB_KW_STD},
  {"TRACE",                 TRACE,                  0,              TCOB_KW_STD},
  {"TRAILING",              TRAILING,               0,              TCOB_KW_STD},
  {"TRUE",                  TRUE_TOK,               0,              TCOB_KW_STD},
  {"TYPE",                  TYPE,                   0,              TCOB_KW_STD},
  {"UNDERLINE",             UNDERLINE,              0,              TCOB_KW_TCEXT},
  {"UNIT",                  UNIT,                   0,              TCOB_KW_STD},
  {"UNLOCK",                UNLOCK,                 0,              TCOB_KW_STD},
  {"UNSIGNED-CHAR",         USAGENUM,               USAGE_BINARY_UCHAR,   TCOB_KW_STD2},                
  {"UNSIGNED-DOUBLE",       USAGENUM,               USAGE_BINARY_UDOUBLE, TCOB_KW_STD2},
  {"UNSIGNED-LONG",         USAGENUM,               USAGE_BINARY_ULONG,   TCOB_KW_STD2},                
  {"UNSIGNED-SHORT",        USAGENUM,               USAGE_BINARY_USHORT,  TCOB_KW_STD2},
  {"UNSTRING",              UNSTRING,               0,              TCOB_KW_STD},
  {"UNTIL",                 UNTIL,                  0,              TCOB_KW_STD},
  {"UP",                    UP,                     0,              TCOB_KW_STD},
  {"UPDATE",                UPDATE,                 0,              TCOB_KW_STD},
  {"UPON",                  UPON,                   0,              TCOB_KW_STD},
  {"UPPER",                 UPPER,                  0,              TCOB_KW_STD},
  {"USAGE",                 USAGE,                  0,              TCOB_KW_STD},
  {"USE",                   USE,                    0,              TCOB_KW_STD},
  {"USING",                 USING,                  0,              TCOB_KW_STD},
  {"VALUE",                 VALUE,                  0,              TCOB_KW_STD},
  {"VALUES",                VALUES,                 0,              TCOB_KW_STD},
  {"VARYING",               VARYING,                0,              TCOB_KW_STD},
  {"WHEN",                  WHEN,                   0,              TCOB_KW_STD},
  {"WINAPI",                CALL_CONV_STDCALL,      0,              TCOB_KW_TCEXT},
  {"WITH",                  WITH,                   0,              TCOB_KW_STD},
  {"WORKING-STORAGE",       WORKING_STORAGE,        0,              TCOB_KW_STD},
  {"WRITE",                 WRITE,                  0,              TCOB_KW_STD},
  {"ZERO",                  ZERO,                   0,              TCOB_KW_STD},
  {"ZEROES",                ZERO,                   0,              TCOB_KW_STD},
  {"ZEROS",                 ZERO,                   0,              TCOB_KW_STD},
  {"",0,0,0}
};


struct intrinsic_function intrinsic_functions[] = {
{"ABS",ITYPE_FLOAT,1},
{"ACOS",ITYPE_FLOAT,1},
{"ANNUITY",ITYPE_FLOAT,2},
{"ASIN",ITYPE_FLOAT,1},
{"ATAN",ITYPE_FLOAT,1}, 
{"CHAR",ITYPE_INLINE,1}, /* inline */
{"COS",ITYPE_FLOAT,1}, 
{"CURRENT-DATE",ITYPE_DATETIME,0},
{"DATE-OF-INTEGER",ITYPE_DATE,1},
{"DATE-TO-YYYYMMDD",ITYPE_DATE,ANY_NUMBER}, /* params can be 1 or 2 */
{"DAY-OF-INTEGER",ITYPE_JULIANDATE,1},
{"DAY-TO-YYYYDDD",ITYPE_JULIANDATE,ANY_NUMBER}, /* params can be 1 or 2 */
{"FACTORIAL",ITYPE_INT,1}, 
{"INTEGER",ITYPE_INT,1}, 
{"INTEGER-OF-DATE",ITYPE_INT,1}, 
{"INTEGER-OF-DAY",ITYPE_INT,1}, 
{"INTEGER-PART",ITYPE_INT,1}, 
{"LENGTH",ITYPE_INLINE,1}, /* inline */
{"LOG",ITYPE_FLOAT,1},
{"LOG10",ITYPE_FLOAT,1},
{"LOWER-CASE",ITYPE_ALPHA,1},
{"MAX",ITYPE_FLOAT,ANY_NUMBER}, 
{"MEAN",ITYPE_FLOAT,ANY_NUMBER},
{"MEDIAN",ITYPE_FLOAT,ANY_NUMBER},
{"MIDRANGE",ITYPE_FLOAT,ANY_NUMBER},
{"MIN",ITYPE_FLOAT,ANY_NUMBER},
{"MOD",ITYPE_INT,2}, 
{"NUMVAL",ITYPE_FLOAT,1},
{"NUMVAL-C",ITYPE_FLOAT,ANY_NUMBER},
{"ORD",ITYPE_INLINE,1},    /* inline */
{"ORD-MAX",ITYPE_INT,ANY_NUMBER},
{"ORD-MIN",ITYPE_INT,ANY_NUMBER},
{"PRESENT-VALUE",ITYPE_FLOAT,ANY_NUMBER},
{"RANDOM",ITYPE_FLOAT,ANY_NUMBER}, /* really 1 or 0 params */
{"RANGE",ITYPE_FLOAT,ANY_NUMBER},
{"REM",ITYPE_INT,2},
{"REVERSE",ITYPE_ALPHA,1},
{"SIN",ITYPE_FLOAT,1},
{"SQRT",ITYPE_FLOAT,1}, 
{"STANDARD-DEVIATION",ITYPE_FLOAT,ANY_NUMBER},
{"SUM",ITYPE_FLOAT,ANY_NUMBER},
{"TAN",ITYPE_FLOAT,1}, 
{"TEST-DATE-YYYYMMDD",ITYPE_INT,1},
{"TEST-DAY-YYYYDDD",ITYPE_INT,1},
{"UPPER-CASE",ITYPE_ALPHA,1},
{"VARIANCE",ITYPE_FLOAT,ANY_NUMBER},
{"WHEN-COMPILED",ITYPE_INLINE,0}, /* inline (we should save the date at compile time) */
{"YEAR-TO-YYYY",ITYPE_YEAR,1},
{"",0,0}
};

static struct reserved_sym *reserved_tab[ HASHLEN ]={NULL};

static struct intrinsic_sym *intrinsic_tab[ HASHLEN ]={NULL};

struct reserved_sym *lookup_reserved( char *s ) {
        struct reserved_sym *as;
        for ( as = reserved_tab[ hash(s) ] ; as != NULL ; as = as->next )
                if ( strcasecmp( s, as->name ) == 0 ) {
                        return( as );
                }
        return( NULL );
}

void install_reserved( void ) {
        struct reserved_sym *as = NULL;
        struct intrinsic_sym *is = NULL;
        int val,i;
        for (i=0;strcmp(reserved_symbols[i].name,"");i++) {
                as = (struct reserved_sym *)
                        malloc( sizeof(struct reserved_sym) );
                as->name = savename( reserved_symbols[i].name );
                val = hash( as->name );
                as->next = reserved_tab[ val ];
                reserved_tab[ val ] = as;
                as->i=i;
        }
        for (i=0;strcmp(intrinsic_functions[i].name,"");i++) {
                is = (struct intrinsic_sym *)
                        malloc( sizeof(struct intrinsic_sym) );
                is->name = savename( intrinsic_functions[i].name );
                val = hash( is->name );
                is->next = intrinsic_tab[ val ];
                intrinsic_tab[ val ] = is;
                is->i=i;
        }
}

int reserved( char *s ) {
        struct reserved_sym *r;
        if ((r=lookup_reserved(s))!=NULL) {
                        yylval.ival=reserved_symbols[r->i].minor;
                        return reserved_symbols[r->i].token;
        }
        return 0;
}

struct intrinsic_sym *lookup_intrinsic_sym( char *s ) {
        struct intrinsic_sym *is;
        for ( is = intrinsic_tab[ hash(s) ] ; is != NULL ; is = is->next )
                if ( strcasecmp( s, is->name ) == 0 ) {
                        return( is );
                }
        return( NULL );
}
struct intrinsic_function *lookup_intrinsic_function( char *s ) {
	struct intrinsic_sym *is;
        for ( is = intrinsic_tab[ hash(s) ] ; is != NULL ; is = is->next )
                if ( strcasecmp( s, is->name ) == 0 ) {
                        return & ( intrinsic_functions[is->i] );
                }
        return( NULL );
}
