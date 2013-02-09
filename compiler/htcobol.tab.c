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
#define YYPREFIX "yy"
#line 29 "htcobol.y"
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
#line 120 "htcobol.y"
typedef union {
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
} YYSTYPE;
#line 154 "htcobol.tab.c"
#define IDSTRING_WORD 257
#define IDSTRING_LITERAL 258
#define STRING 259
#define VARIABLE 260
#define VARCOND 261
#define SUBSCVAR 262
#define LABELSTR 263
#define CMD_LINE 264
#define ENVIRONMENT_VARIABLE 265
#define INKEY 266
#define CHAR 267
#define MULTIPLIER 268
#define USAGENUM 269
#define CONDITIONAL 270
#define TO 271
#define IS 272
#define ARE 273
#define THRU 274
#define THAN 275
#define NO 276
#define DIRECTION 277
#define READ 278
#define WRITE 279
#define INPUT_OUTPUT 280
#define RELEASE 281
#define NLITERAL 282
#define CLITERAL 283
#define DISK 284
#define PRINTER 285
#define DATE_TIME 286
#define POW_OP 287
#define OR 288
#define AND 289
#define NOT 290
#define ACCEPT 291
#define ACCESS 292
#define ADD 293
#define ADDRESS 294
#define ADVANCING 295
#define AFTER 296
#define ALL 297
#define ALPHABET 298
#define ALPHABETIC_TOK 299
#define ALPHABETIC_LOWER 300
#define ALPHABETIC_UPPER 301
#define ALPHANUMERIC 302
#define ALPHANUMERIC_EDITED 303
#define ALSO 304
#define ALTERNATE 305
#define ANY 306
#define AREA 307
#define AREAS 308
#define ASSIGN 309
#define AT 310
#define AUTHOR 311
#define AUTO 312
#define BACKGROUNDCOLOR 313
#define BEFORE 314
#define BELL 315
#define BLANK 316
#define BLINK 317
#define BLOCK 318
#define BOTTOM 319
#define BY 320
#define CALL 321
#define CALL_CONV_C 322
#define CALL_CONV_STDCALL 323
#define CALL_LOADLIB 324
#define CANCEL 325
#define CENTER 326
#define CF 327
#define CH 328
#define CHAIN 329
#define CHAINING 330
#define CHARACTER 331
#define CHARACTERS 332
#define CLASS 333
#define CLOSE 334
#define CODE 335
#define CODE_SET 336
#define COLLATING 337
#define COLOR 338
#define COLUMN 339
#define COLUMNS 340
#define COMMA 341
#define COMMON 342
#define COMPUTE 343
#define CONFIGURATION 344
#define CONSOLE 345
#define CONTAINS 346
#define CONTENT 347
#define CONTINUE 348
#define CONTROL 349
#define CONTROLS 350
#define CONVERTING 351
#define CORRESPONDING 352
#define COUNT 353
#define CURRENCY 354
#define CURSOR 355
#define DATA 356
#define DATE_COMPILED 357
#define DATE_WRITTEN 358
#define DE 359
#define DEBUGGING 360
#define DECIMAL_POINT 361
#define DECLARATIVES 362
#define DELETE 363
#define DELIMITED 364
#define DELIMITER 365
#define DEPENDING 366
#define DETAIL 367
#define DISPLAY 368
#define DISPLAY_SCREEN 369
#define DIVIDE 370
#define DIVISION 371
#define DOWN 372
#define DUPLICATES 373
#define DYNAMIC 374
#define ELSE 375
#define END 376
#define END_ACCEPT 377
#define END_ADD 378
#define END_CALL 379
#define END_CALL_LOADLIB 380
#define END_CHAIN 381
#define END_COMPUTE 382
#define END_DELETE 383
#define END_DISPLAY 384
#define END_DIVIDE 385
#define END_EVALUATE 386
#define END_IF 387
#define END_MULTIPLY 388
#define END_OF_PAGE 389
#define END_PERFORM 390
#define END_READ 391
#define END_RETURN 392
#define END_REWRITE 393
#define END_SEARCH 394
#define END_START 395
#define END_STRINGCMD 396
#define END_SUBTRACT 397
#define END_UNSTRING 398
#define END_WRITE 399
#define ENVIRONMENT 400
#define EOL 401
#define EOS 402
#define ERASE 403
#define ERROR_TOK 404
#define EVALUATE 405
#define EXCEPTION 406
#define EXIT 407
#define EXTEND 408
#define EXTERNAL 409
#define FALSE_TOK 410
#define FD 411
#define FILE_CONTROL 412
#define FILE_ID 413
#define FILE_TOK 414
#define FILLER 415
#define FINAL 416
#define FIRST 417
#define FOOTING 418
#define FOR 419
#define FOREGROUNDCOLOR 420
#define FROM 421
#define FULL 422
#define FUNCTION 423
#define GENERATE 424
#define GIVING 425
#define GLOBAL 426
#define GO 427
#define GOBACK 428
#define GROUP 429
#define HEADING 430
#define HIGHLIGHT 431
#define HIGHVALUES 432
#define IDENTIFICATION 433
#define IF 434
#define IGNORE 435
#define IN 436
#define INDEXED 437
#define INDICATE 438
#define INITIALIZE 439
#define INITIAL_TOK 440
#define INITIATE 441
#define INPUT 442
#define INSPECT 443
#define INSTALLATION 444
#define INTO 445
#define INVALID 446
#define I_O 447
#define I_O_CONTROL 448
#define JUSTIFIED 449
#define KEY 450
#define LABEL 451
#define LAST 452
#define LEADING 453
#define LEFT 454
#define LENGTH 455
#define LIMIT 456
#define LIMITS 457
#define LINAGE 458
#define LINE 459
#define LINES 460
#define LINKAGE 461
#define LISTSEP 462
#define LOCK 463
#define LOWER 464
#define LOWLIGHT 465
#define LOWVALUES 466
#define LPAR 467
#define MERGE 468
#define MINUS 469
#define MODE 470
#define MOVE 471
#define MULTIPLE 472
#define MULTIPLY 473
#define NATIVE 474
#define NEGATIVE 475
#define NEXT 476
#define NOECHO 477
#define NOTEXCEP 478
#define NULL_TOK 479
#define NUMBER 480
#define NUMBERS 481
#define NUMERIC 482
#define NUMERIC_EDITED 483
#define OBJECT_COMPUTER 484
#define OCCURS 485
#define OF 486
#define OFF 487
#define OMITTED 488
#define ON 489
#define ONLY 490
#define OPEN 491
#define OPTIONAL 492
#define ORDER 493
#define ORGANIZATION 494
#define OTHER 495
#define OUTPUT 496
#define OVERFLOW_TOK 497
#define PADDING 498
#define PAGE_TOK 499
#define PAGE_COUNTER 500
#define PARAGRAPH 501
#define PERFORM 502
#define PF 503
#define PH 504
#define PICTURE 505
#define PLUS 506
#define POINTER 507
#define POSITION 508
#define POSITIVE 509
#define PREVIOUS 510
#define PROCEDURE 511
#define PROCEDURES 512
#define PROCEED 513
#define PROGRAM 514
#define PROGRAM_ID 515
#define QUOTES 516
#define RANDOM 517
#define RD 518
#define READY 519
#define RECORD 520
#define RECORDS 521
#define REDEFINES 522
#define REEL 523
#define REFERENCE 524
#define REFERENCES 525
#define RELATIVE 526
#define REMAINDER 527
#define REMOVAL 528
#define RENAMES 529
#define REPLACING 530
#define REPORT 531
#define REPORTING 532
#define REPORTS 533
#define REQUIRED 534
#define RESERVE 535
#define RESET 536
#define RETURN_TOK 537
#define RETURNING 538
#define REVERSEVIDEO 539
#define REWIND 540
#define REWRITE 541
#define RF 542
#define RH 543
#define RIGHT 544
#define ROUNDED 545
#define RUN 546
#define SAME 547
#define SCREEN 548
#define SD 549
#define SEARCH 550
#define SECTION 551
#define SECURE 552
#define SECURITY 553
#define SELECT 554
#define SENTENCE 555
#define SEPARATE 556
#define SEQUENCE 557
#define SEQUENTIAL 558
#define SET 559
#define SIGN 560
#define SIZE 561
#define SORT 562
#define SORT_MERGE 563
#define SOURCE 564
#define SOURCE_COMPUTER 565
#define SPACES 566
#define SPECIAL_NAMES 567
#define STANDARD 568
#define STANDARD_1 569
#define STANDARD_2 570
#define START 571
#define STATUS 572
#define STD_ERROR 573
#define STD_INPUT 574
#define STD_OUTPUT 575
#define STOP 576
#define STRINGCMD 577
#define SUBTRACT 578
#define SUM 579
#define SYNCHRONIZED 580
#define TALLYING 581
#define TAPE 582
#define TCOBPROTO1 583
#define TCOBPROTO2 584
#define TERMINATE 585
#define TEST 586
#define THEN 587
#define TIMES 588
#define TOKDUMMY 589
#define TOP 590
#define TRACE 591
#define TRAILING 592
#define TRUE_TOK 593
#define TYPE 594
#define UNDERLINE 595
#define UNIT 596
#define UNLOCK 597
#define UNSTRING 598
#define UNTIL 599
#define UP 600
#define UPDATE 601
#define UPON 602
#define UPPER 603
#define USAGE 604
#define USE 605
#define USING 606
#define VALUE 607
#define VALUES 608
#define VARYING 609
#define WHEN 610
#define WITH 611
#define WORKING_STORAGE 612
#define ZERO 613
#define PERIOD_TOK 614
#define YYERRCODE 256
ZYshort yylhs[] = {                                        -1,
    0,  141,  141,  141,  142,  187,  142,  142,  188,  186,
  185,  193,  195,  197,  189,  171,  171,  194,  194,  194,
  199,  199,  196,  196,  200,  200,  200,  200,  200,  202,
  190,  190,  201,  201,  204,  204,  206,  205,  208,  205,
  205,  205,  209,  209,  211,  212,  212,  207,  207,  210,
  210,  210,  214,  214,  215,  215,  215,  215,  215,  215,
  215,  218,  223,  223,  222,  224,  224,  225,  225,  219,
  220,  221,  216,  216,  227,   50,  226,  226,  228,  228,
  229,  229,  217,  230,  230,  230,  230,  231,  231,  232,
  232,  232,  233,  233,  203,  203,  234,  234,  235,  236,
  236,  237,  237,  237,  241,  239,  240,  240,  242,  242,
  242,  242,  242,  242,  242,  242,  242,   49,   49,  246,
  246,  243,  243,   30,   30,   30,   30,  250,  250,  251,
  251,   31,   31,   31,   31,   53,   53,   55,   55,  248,
  248,  248,  198,  198,  252,  252,  245,  245,    3,    3,
    3,    3,    3,    4,    4,    4,    4,  238,  238,  253,
  253,  254,  254,  255,  257,  257,  257,  257,  256,  262,
  262,  263,  264,  264,  260,  260,  258,  258,  259,  259,
  136,  136,  136,  135,  135,  135,  266,  191,  191,  272,
  265,  265,  274,  267,  267,  276,  268,  268,  269,  269,
  277,  277,  279,  281,  283,  278,  280,  280,  284,  284,
  284,  284,  285,  286,  292,  292,  291,  291,  296,  296,
  287,  287,  290,  290,  290,  295,  295,  294,  294,  293,
  293,  288,  288,  289,  289,  282,  282,  299,  297,  298,
  298,  300,  300,  300,  300,  300,  300,  300,  300,  300,
  300,  300,  303,  312,  312,  314,  312,  312,  315,  312,
  312,  312,  312,  312,  316,  312,  312,  317,  312,  312,
  312,  306,  306,  320,  305,  304,  304,  307,  302,  301,
  301,  301,  301,  324,  324,  324,  324,  309,   83,   83,
   83,   83,   84,   84,   84,   84,  325,  325,  325,  326,
  310,  310,  328,  330,  310,  327,  327,  311,  311,  308,
  332,  332,  329,  329,  331,  331,  331,  334,  334,  318,
  318,  322,  322,  313,  313,  323,  323,  323,  335,  335,
  337,  270,  270,  336,  336,  339,  338,  341,   79,  342,
   79,   79,  343,   79,  344,   79,  345,   79,   79,   79,
   79,  349,   79,   79,  350,  346,  351,  346,  352,  346,
  119,  119,   80,   80,   80,   80,   80,   80,   80,   80,
   80,   80,   80,   80,   80,   80,   80,   80,   80,   80,
   80,   80,   80,   80,   80,   80,   81,   81,   82,   82,
  319,  319,  353,  353,   72,   72,   72,   72,   72,  340,
  340,  354,  355,  356,  271,  357,  358,  359,  271,  271,
  271,  146,  146,  361,   24,  360,  360,  360,  364,  363,
  147,  147,  362,  362,  362,  362,  362,  362,  362,  362,
  362,  362,  368,  362,    1,    1,    1,  103,  103,  371,
  365,  373,  374,  365,   87,   87,  370,  370,  376,  376,
  366,   10,   10,   10,  367,  347,  347,  378,  378,  379,
  379,  381,  348,  321,  321,  382,   12,   12,  173,  173,
  175,  175,  172,  172,  172,  172,  172,  172,  172,  172,
  172,  172,  174,  174,  383,  176,  176,  384,  385,  386,
  387,  389,  388,  399,  399,  400,  400,  401,  401,  403,
  403,  403,  403,  398,  398,  397,  397,  391,  391,  391,
  390,  390,  145,  145,  143,  143,  404,  404,  144,  144,
  395,  395,  396,  396,  377,  377,  369,  369,  333,  333,
  261,  261,  392,  392,  405,  405,  406,  406,  273,  273,
  275,  275,  407,  409,  192,  192,  412,  408,  408,  413,
  413,  415,  411,  411,  414,  414,  417,  414,  418,  414,
  181,  181,  181,  182,  182,  419,  419,  419,  419,  419,
  179,  179,  180,  180,  183,  184,  420,  420,  421,  421,
    2,    2,  410,  410,  422,  422,  423,  422,  424,  422,
  422,   23,   29,  425,  425,  426,  416,  416,  427,  427,
  427,  427,  427,  427,  427,  427,  427,  427,  427,  427,
  427,  427,  427,  427,  427,  427,  427,  427,  427,  427,
  427,  427,  427,  427,  427,  427,  427,  427,  427,  427,
  427,  427,  427,  427,  427,  427,  427,  427,  427,  427,
  427,  446,  471,  467,  473,  474,  467,  469,  469,  476,
  477,  468,  478,  478,  479,  118,  480,  118,  115,  115,
  115,  115,  481,  482,  122,  483,  484,  485,  122,  486,
  117,  487,  117,  117,  116,  116,  116,  116,  116,  116,
  121,  121,  489,   15,  490,  472,  491,  472,  114,  114,
  470,  470,  488,  488,  492,  493,  494,   88,  495,  497,
   89,   86,   86,  498,   92,   92,   91,   91,  501,   90,
  500,  500,  499,  496,  496,  504,  506,  502,  505,  505,
  503,  503,  507,  503,  475,  475,  466,  462,  462,  463,
  463,  459,  460,  461,  465,  465,  455,  113,  454,  168,
  168,  169,  170,  170,  509,  509,  508,  508,  111,  111,
  112,  112,  109,  109,  428,  428,  428,  428,  429,  429,
  510,  510,  511,  511,  512,  513,  513,  513,  513,  513,
  430,  430,  514,  515,  515,  431,  431,  516,  516,  516,
  134,  134,  517,  517,  432,  432,  518,  518,  518,  519,
  519,  433,  433,  520,  520,  521,  521,  434,  434,  522,
  522,  522,  522,  522,  523,  523,  435,  435,  435,  435,
  529,  524,  524,  524,  524,  524,   51,   51,  527,  527,
  527,  528,  531,  528,  525,  526,  532,  533,  534,  526,
  530,  530,  436,  436,  436,  535,  536,  537,  537,  129,
  129,  129,  130,  130,  130,  130,  130,  130,  538,  538,
  540,  541,  541,  542,  542,  161,  161,  159,  159,  160,
  160,  160,  160,  437,  437,  178,  178,    5,    5,    5,
    5,    5,  177,  177,  438,  438,  543,  543,  544,  163,
  163,  545,  545,  545,  545,  545,  162,  162,  162,  440,
  440,  546,  546,  439,  439,  549,  549,  549,   11,   11,
   11,   41,   41,   78,   78,  151,  151,  151,  551,  151,
  552,  151,  553,  150,  152,  152,  152,  554,  153,  555,
  154,  550,  550,  547,  547,  441,   43,   43,  556,  442,
   42,   42,   39,   39,   39,  557,  557,  559,  443,  560,
  560,  561,  444,  562,  562,  564,  445,  158,  158,  563,
  563,  447,  447,  165,  164,  164,  164,  566,  567,  568,
  569,  571,  450,  450,  565,  565,  565,  573,  451,  451,
  572,  572,  574,  575,  576,  578,  452,  452,  448,  448,
  448,  449,  449,  579,  579,  464,  124,  124,  125,  125,
  123,  123,  126,  126,  126,  580,  126,  581,  127,  394,
  394,  570,  570,  577,  577,  453,  582,  582,  582,  582,
  133,  133,  131,  131,  132,  132,  132,  132,  132,  128,
  128,  584,  457,  586,  458,   64,   64,   63,   63,   65,
   65,   66,   61,   61,   60,   60,   62,   62,   52,   52,
  589,  583,  592,  148,  148,  591,  591,  593,  149,  149,
  594,  588,  588,  596,  590,  590,  155,  155,  155,  155,
  597,  156,  598,  157,  595,  595,   48,   48,   58,   58,
   58,   59,   59,   47,   47,   47,  585,  585,  587,  587,
  599,  456,  456,   76,   69,   69,   68,   68,   70,   70,
   70,   70,   74,   74,   73,   73,   73,   75,   75,   71,
   71,   71,   71,   67,   67,   67,  600,  600,  100,  100,
  100,  100,  100,  100,  100,  101,  101,   13,  602,  603,
   13,  108,  108,  604,  604,  601,   14,   14,   14,   40,
   40,   98,   98,   99,   99,   93,   93,   93,   96,   96,
   97,  110,   45,  606,  607,   45,  608,  609,  610,   45,
  611,  612,  613,   45,   45,  614,   45,   45,  615,  616,
   45,   38,   38,   54,   54,  105,  105,  105,  105,  105,
  105,  105,  617,  104,  618,  605,    9,    9,  619,  137,
  137,  620,  137,  621,  137,  137,  137,  138,  138,  138,
   94,   94,   94,   95,   95,   95,   95,  107,  107,  107,
  107,  107,  107,  106,  106,  106,    7,    7,    7,    8,
  380,  380,  539,  539,  247,  247,  558,  558,  622,  622,
  622,  548,  548,  402,  402,  393,  393,  249,  249,  375,
  375,  213,  213,  372,  372,   20,   20,  244,  244,  167,
  167,  166,  166,   19,   19,  623,   19,   19,   46,   46,
   28,   28,   33,   33,   34,   34,   35,   35,   36,   36,
   36,   36,   36,   36,   77,   77,   37,   32,   32,  120,
  120,  120,   21,   21,   22,   22,   85,   26,   26,   27,
   27,  624,  102,  102,   17,   17,   17,   18,   44,  625,
   44,  139,  139,  140,  140,   57,   57,   56,   56,   56,
    6,   25,   25,   25,   25,   25,   16,   16,
};
ZYshort yylen[] = {                                         2,
    1,    1,    1,    2,    2,    0,    4,    3,    0,    4,
    4,    0,    0,    0,   12,    1,    1,    0,    3,    3,
    0,    1,    0,    2,    2,    2,    2,    2,    2,    0,
    6,    0,    4,    0,    2,    0,    0,    6,    0,    6,
    3,    1,    2,    0,    4,    1,    0,    3,    0,    0,
    2,    1,    1,    2,    1,    1,    1,    1,    1,    1,
    1,    4,    1,    0,    4,    1,    2,    1,    3,    3,
    4,    3,    0,    2,    0,    6,    4,    0,    4,    0,
    1,    0,    4,    1,    1,    1,    1,    1,    2,    1,
    3,    2,    2,    3,    4,    0,    2,    0,    3,    0,
    3,    1,    2,    0,    0,    6,    2,    0,    3,    3,
    4,    4,    4,    4,    6,    3,    1,    1,    3,    1,
    0,    1,    0,    1,    3,    2,    2,    1,    0,    1,
    1,    1,    1,    1,    1,    2,    0,    1,    0,    1,
    1,    0,    1,    0,    1,    0,    1,    0,    1,    1,
    1,    2,    1,    1,    1,    1,    1,    0,    2,    1,
    2,    1,    1,    5,    0,    1,    1,    1,    5,    1,
    2,    2,    0,    2,    1,    0,    1,    0,    1,    0,
    1,    2,    1,    1,    2,    1,    0,    9,    0,    0,
    5,    0,    0,    5,    0,    0,    5,    0,    4,    0,
    2,    0,    0,    0,    0,    8,    0,    2,    2,    2,
    1,    1,    3,    8,    0,    3,    1,    1,    0,    1,
    2,    2,    0,    2,    2,    0,    3,    0,    4,    0,
    4,    0,    1,    0,    2,    1,    2,    0,    5,    1,
    2,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    3,    2,    2,    0,    4,    1,    0,    4,
    2,    2,    1,    1,    0,    3,    1,    0,    3,    1,
    1,    5,    3,    0,    4,    3,    1,    2,    4,    5,
    4,    2,    3,    2,    3,    3,    2,    2,    3,    4,
    4,    3,    0,    1,    1,    1,    0,    1,    1,    0,
    4,    3,    0,    0,    6,    1,    1,    0,    2,    3,
    0,    1,    0,    2,    0,    2,    2,    0,    1,    1,
    1,    0,    1,    1,    1,    1,    2,    2,    1,    0,
    0,    5,    0,    2,    0,    0,    5,    0,    6,    0,
    6,    3,    0,    5,    0,    5,    0,    5,    2,    3,
    2,    0,    4,    0,    0,    3,    0,    4,    0,    3,
    0,    2,    2,    2,    2,    2,    1,    2,    1,    1,
    1,    1,    1,    2,    2,    1,    1,    1,    1,    1,
    3,    2,    2,    3,    1,    1,    3,    3,    2,    0,
    1,    0,    2,    1,    1,    1,    1,    1,    0,    2,
    0,    0,    0,    0,    9,    0,    0,    0,    9,    1,
    0,    1,    2,    0,    5,    0,    2,    2,    0,    3,
    1,    1,    1,    1,    1,    1,    1,    2,    2,    2,
    2,    3,    0,    4,    0,    1,    1,    0,    2,    0,
    5,    0,    0,   11,    4,    0,    4,    0,    1,    2,
    3,    1,    1,    1,    2,    2,    2,    1,    3,    1,
    3,    0,    4,    0,    2,    2,    0,    1,    0,    2,
    0,    2,    2,    2,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    5,    5,    9,    3,    5,    3,
    2,    3,    7,    0,    4,    0,    3,    0,    3,    0,
    1,    2,    1,    2,    2,    1,    2,    0,    1,    1,
    0,    2,    0,    3,    0,    2,    1,    0,    0,    2,
    2,    2,    1,    1,    0,    1,    0,    1,    0,    1,
    0,    1,    0,    1,    0,    1,    0,    1,    2,    0,
    0,    2,    0,    0,    9,    0,    0,    8,    0,    1,
    2,    0,    3,    1,    1,    1,    0,    3,    0,    3,
    1,    1,    1,    8,    1,    1,    1,    2,    2,    1,
    1,    1,    1,    3,    5,    5,    1,    2,    1,    2,
    0,    1,    0,    2,    1,    1,    0,    3,    0,    3,
    1,    3,    2,    1,    1,    1,    1,    2,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    2,    0,    3,    0,    0,    6,    3,    4,    0,
    0,    6,    1,    1,    0,    2,    0,    4,    1,    1,
    1,    1,    0,    0,    5,    0,    0,    0,    7,    0,
    2,    0,    4,    1,    1,    1,    1,    2,    4,    2,
    0,    1,    0,    5,    0,    2,    0,    3,    0,    1,
    0,    1,    0,    1,    0,    0,    0,    7,    0,    0,
    5,    2,    0,    0,    4,    0,    1,    2,    0,    4,
    1,    2,    3,    1,    2,    0,    0,    5,    1,    2,
    5,    5,    0,    4,    0,    1,    2,    2,    3,    2,
    2,    2,    2,    2,    2,    2,    6,    2,    7,    1,
    2,    4,    1,    2,    0,    4,    0,    1,    4,    2,
    4,    2,    1,    2,    4,    5,    6,    3,    3,    1,
    0,    2,    1,    2,    4,    1,    1,    1,    1,    1,
    3,    1,    4,    0,    1,    3,    1,    4,    5,    6,
    0,    2,    0,    1,    3,    1,    4,    6,    6,    0,
    1,    3,    1,    6,    4,    0,    1,    3,    1,    6,
    9,    9,    6,    4,    0,    1,    1,    1,    1,    1,
    0,    6,    5,    6,    5,    6,    1,    1,    0,    2,
    2,    0,    0,    5,    5,    4,    0,    0,    0,   11,
    0,    1,    1,    1,    1,    5,    4,    1,    3,    2,
    2,    2,    0,    4,    3,    4,    4,    4,    0,    1,
    3,    3,    2,    2,    2,    1,    2,    0,    2,    2,
    1,    1,    1,    2,    1,    2,    3,    1,    1,    1,
    1,    1,    1,    3,    2,    1,    1,    3,    2,    1,
    1,    3,    1,    1,    3,    3,    2,    3,    0,    3,
    1,    3,    4,    3,    1,    6,    7,    7,    0,    1,
    1,    0,    2,    0,    3,    3,    2,    1,    0,    6,
    0,    5,    0,    3,    1,    1,    2,    0,    4,    0,
    5,    0,    1,    0,    1,    3,    0,    2,    0,    7,
    0,    2,    0,    4,    3,    0,    1,    0,    6,    0,
    1,    0,    6,    0,    1,    0,    5,    1,    5,    0,
    1,    3,    6,    1,    1,    2,    3,    0,    0,    0,
    0,    0,   13,    1,    0,    1,    1,    0,    4,    1,
    1,    0,    0,    0,    0,    0,    9,    1,    1,    2,
    2,    2,    2,    1,    1,    1,    3,    4,    2,    3,
    0,    1,    0,    4,    3,    0,    8,    0,    3,    0,
    1,    0,    1,    0,    1,    2,    4,    4,    4,    5,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    0,
    2,    0,    8,    0,   10,    3,    0,    2,    4,    1,
    3,    3,    0,    3,    0,    3,    0,    3,    0,    1,
    0,    3,    0,    4,    0,    1,    1,    0,    5,    0,
    0,    4,    0,    0,    5,    0,    1,    1,    2,    0,
    0,    4,    0,    5,    1,    1,    3,    0,    1,    3,
    1,    1,    4,    1,    1,    1,    0,    1,    0,    1,
    0,    5,    3,    5,    2,    0,    4,    0,    3,    4,
    4,    0,    2,    0,    5,    3,    0,    5,    0,    1,
    1,    1,    1,    4,    4,    0,    1,    0,    1,    3,
    3,    3,    3,    3,    3,    0,    1,    0,    0,    0,
    5,    0,    2,    1,    1,    0,    0,    2,    2,    0,
    2,    3,    1,    1,    3,    1,    1,    1,    3,    1,
    1,    2,    2,    0,    0,    6,    0,    0,    0,    8,
    0,    0,    0,   15,    2,    0,    6,    4,    0,    0,
   14,    0,    2,    0,    3,    0,    2,    4,    6,    8,
   10,   12,    0,    8,    0,    2,    1,    1,    0,    4,
    2,    0,    4,    0,    4,    3,    1,    1,    2,    1,
    1,    1,    1,    1,    1,    1,    1,    2,    3,    4,
    1,    3,    3,    1,    1,    1,    1,    2,    3,    2,
    0,    1,    0,    1,    0,    1,    0,    1,    0,    1,
    1,    0,    1,    0,    1,    0,    1,    1,    1,    0,
    1,    0,    1,    0,    1,    1,    0,    0,    1,    1,
    3,    1,    3,    1,    1,    0,    6,    2,    1,    1,
    1,    1,    1,    1,    1,    1,    2,    2,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    2,    2,    1,    0,    1,    1,    1,    1,    1,    1,
    1,    0,    5,    1,    6,    1,    1,    1,    1,    0,
    5,    1,    3,    1,    1,    1,    3,    1,    3,    3,
    1,    3,    1,    1,    3,    3,    1,    1,
};
ZYshort yydefred[] = {                                      0,
    0,    0,    1,    0,    0,    0,    0,    0,    0,    5,
    0,    0,    0,    0,    8,    9,    0,    0,    0,    0,
    0,    0,    0,    0,    7,   30,    0,    0,   11,   12,
   16,   17,   10,    0,  187,  543,    0,    0,    0,    0,
    0,   13,    0,    0,   31,    0,    0,    0,    0,    0,
    0,   36,    0,    0,    0,    0, 1294, 1295, 1287, 1270,
 1269,    0,    0,    0,    0, 1262, 1263, 1264, 1261, 1259,
 1260, 1244, 1242, 1255, 1245, 1253, 1254, 1256,    0, 1268,
    0,    0,    0,    0,    0,    0,  143,    0,    0,    0,
    0,  190,    0,    0,    0, 1271, 1272, 1257, 1258,    0,
    0, 1290, 1228, 1229,    0, 1214,    0, 1131,  544,   14,
    0,    0,   42,    0,    0,    0,   35,    0,   95,    0,
    0,  193,    0,    0,    0, 1246,    0,    0, 1293, 1243,
    0,   23,   22,   20,   19,   39,   37,    0,    0,    0,
   97,  410,    0,  540,  196,    0,    0,  188,    0,    0,
 1298,    0,    0,    0,  583,    0,    0,    0,   52,    0,
    0,    0,    0,    0,    0,   41,    0,   53,    0,   56,
   57,   58,   59,   60,   61,    0,    0,  102,    0,  402,
  406,    0,  541,  202,    0, 1141,    0, 1140, 1236,    0,
    0,    0, 1291, 1212,    0,  547,    0,    0,    0,    0,
    0,    0,   24,    0,    0,    0,    0,   63,    0,    0,
    0,    0,   51,   54,    0,   74,  138,    0,  103,    0,
    0,  101,    0,  160,  162,  163,    0,    0,    0,  539,
 1301,    0,    0,  331, 1247,    0, 1285, 1299, 1300,    0,
    0,  589,    0,  591,  585,  586,  584,    0,   25,   27,
   26,   28,   29,    0,    0, 1233,    0,    0,    0,    0,
    0,   72,   70,    0,    0, 1275, 1276,  105,    0,  166,
  167,  168,    0,  159,  161,  403,  407,  414, 1273,  542,
  203,  201,  335, 1139,  554,    0,  552,    0,    0,    0,
  595,  594,  593,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  641,    0,    0,    0,  650,    0,
    0,    0,  986,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  597,  599,  600,  601,  602,  603,  604,  605,  606,  607,
  608,  609,  610,  611,  612,  613,  614,  615,  616,  617,
  618,  619,  620,  621,  622,  623,  624,  625,  626,  627,
  628,  629,  630,  631,  632,  633,  634,  635,  636,  637,
  638,  639,  640,  807,  808,  809,  833,  834,   46,   43,
    0,   40,   38,    0,   84,   85,   86,    0,   83,    0,
   88,    0,    0,   66,   62,   71,   75,  108,  175,    0,
  177,    0,  469,  471,  416,    0,    0,    0,    0,  556,
  555,    0,  550,    0,  590,  592,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  968,    0,  735,    0,
    0,    0,  877,    0,    0,    0,    0,  838,    0,    0,
    0,  655,  980,  981,  733, 1239,    0,    0,    0,    0,
 1109,    0, 1187,    0,    0,  732,    0,    0,    0,    0,
    0,    0,    0,  872,  871,  868,  869,  870,    0,    0,
    0,    0,    0,    0,  642,    0,    0,    0,    0,  730,
  731,    0,    0,    0, 1277,    0,  695,    0,  186,    0,
  184, 1012,    0,    0,    0, 1006,    0,    0,    0,  985,
  984,  982,  983, 1071,    0,    0, 1069,    0,    0,    0,
  728,    0,  734,  727,    0,  645,    0,  588,  598,    0,
   48,    0,    0,    0,   89,    0,   67,    0,    0,  532,
    0,  179,    0,    0,    0,    0,  204,    0,  334,  565,
    0,  553,  561,  563,  562,    0,    0,  551,    0,  900,
  901,    0,  923,  894,    0,    0,    0,  926,    0,    0,
    0,    0,    0,  856,    0,    0,  811,  861,  862,  863,
    0,  989,    0,    0,    0,  784,  776,  966,  967,    0,
    0,    0,    0,    0,  881,  879,    0,  880,    0,  992,
    0,    0,    0,  775,  771, 1223,  942,    0,  843,    0,
    0,    0,    0,  806,  798,    0,    0,    0,    0,    0,
    0,  952, 1282, 1181,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0, 1195, 1196, 1197, 1192, 1194, 1191,
 1193, 1204, 1206, 1205,    0, 1179, 1184, 1182,    0,    0,
  759,    0, 1088, 1081, 1083, 1235,    0,  740,    0,    0,
 1288,    0,    0,    0,  797,  792,  873,    0,    0,    0,
    0, 1144,    0,    0, 1147,    0,    0, 1143,    0, 1176,
    0,  925,  890,  938,  699,    0,    0,  726,  648,  329,
 1021,    0,    0,    0,    0,  185,    0,    0, 1066,    0,
 1065,  946,    0, 1058,    0,    0,    0,    0,    0,    0,
  791,  785,  729,    0,    0,    0,  692,  644,    0,   91,
   93,    0,   69,    0,    0,  117,    0,    0,    0,  120,
  122,    0,    0,    0,  106,  107,    0,    0,    0,    0,
  170,  183,  181,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  404,  470,  476,    0,  475,  477,  478,
  479,  480,  481,  482,    0,  408,  472,  483,  484,    0,
    0,    0,  462,  419,  433,    0,    0,  526,    0,    0,
  415,  426,    0,    0,  424,    0,  417,  418,  423,  425,
  427,    0,  207,  336,  582,    0,    0,  560,    0,  558,
    0,  932, 1178, 1177,    0,  929,  928,  854,  855,  319,
    0,    0,    0,    0,    0,  821,    0,  820,    0,    0,
    0,  832,  857,    0,  826,  373,    0,  376,    0,  370,
  380,    0,  386,  379,  371,  377,  372,  378,  385,  860,
  369,  394,    0,    0,    0,    0,  782,    0,  990,    0,
    0,  971,  969, 1119,  974,    0,    0,    0,    0,  887,
  878,  987,    0,    0,    0,  840,  842,  841,    0,  850,
  859,  837,  839,    0,    0,    0,  657,    0,  662,  661,
    0,  656,    0,    0,    0,  956,    0, 1115, 1186, 1220,
 1221, 1210,    0,    0,    0,    0,    0,    0, 1114,    0,
    0,    0,    0,    0,  694,    0,  766,  767,  769,  768,
  770,    0,  763,    0, 1251,    0, 1252,    0,    0,  741,
  748,    0,    0,    0,    0, 1240,    0,    0,    0,    0,
    0, 1302, 1306, 1305, 1175, 1163,    0,    0,    0,    0,
 1165,    0,    0,    0,    0,  649,    0,  696,    0,    0,
    0,    0,    0,    0,    0, 1216, 1061,    0, 1059,    0,
 1231,    0,    0, 1070,    0,    0,    0,    0,    0,  646,
    0,    0,   45,   94,   81,    0,    0,   76,  147,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  172,  171,
  182,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  504,  145,  505,    0,    0,  473,  474,  491,    0,  530,
    0,  436,  437,  429,    0,    0,    0,    0,  393,  428,
  456,  457,  430,  431,    0,    0,  458,    0,    0,    0,
    0,  354,    0,    0,    0,  548,    0, 1218,    0,    0,
    0,  815,  818,  817,    0,  813,  825,    0,    0,    0,
  827,  364,  363,    0,  365,  366,  375,  374,    0,  368,
  382,  383,    0,    0,    0,    0,  778,    0,    0,    0,
 1126,  975,  885,  886,  882,  888,  773,  988,    0,    0,
  836,    0,    0,  804,    0,  663,    0,    0,  957,    0,
 1199,    0, 1202, 1203,    0, 1180,    0,    0,    0,    0,
    0, 1185, 1183,  684,  764,  538,    0,    0,    0, 1097,
 1082,    0,    0,    0,  756,    0,    0,    0,  795,  874,
 1145, 1158, 1156,    0,    0,    0,  903,    0,    0,  913,
    0,  893,    0, 1225,  700,    0,  702,    0,    0, 1018,
 1017, 1016, 1019, 1249, 1250, 1015, 1007, 1266, 1265, 1009,
 1267, 1008,    0,    0,    0,    0,    0,  951,  947, 1063,
 1076, 1075, 1074, 1073, 1022,    0,    0,    0,  787, 1040,
    0,    0,    0,    0, 1030,    0,  686,    0,    0,    0,
    0,    0,  135,  128,  134,  132,  133,  110,  124,    0,
    0,    0,  140,  141,  116, 1307, 1308,  149,    0,  151,
  150,  109,  153,    0,  174,    0,  492,  521,  522,  506,
    0,  524,  523,  488, 1281,    0, 1280,    0,    0,    0,
  412,    0,    0,  432,    0,  528,  440,  464,  421,  422,
  420,    0,    0,    0,    0,  387,  388,  452,  453,  454,
  451,    0,    0,    0,    0,  205,    0,  208,  211,  212,
    0,    0,  570,  567,  566,    0,    0,    0,    0,    0,
    0,  935,    0,    0,  816,  814,    0,  381,  384,    0,
  812,    0,    0,    0,  779, 1125, 1124,  959,    0, 1120,
    0,  945,  943,    0,    0,    0,    0,    0,    0,  658,
  664,  653,  666,  654,  652,  953, 1283, 1200, 1208,    0,
    0,    0, 1106, 1092,    0,  753,    0,    0,    0,  737,
  743,    0,  757, 1241,    0,    0,    0,    0, 1175,    0,
    0,    0,    0,    0,  941,  939,    0,  704,  697, 1014,
 1013, 1010, 1227,    0,    0,    0,    0,  949, 1062,    0,
 1041,    0,    0,    0, 1028,    0,    0,    0,    0,    0,
  647,  688,   77,    0,  155,  156,  154,  111,  157,    0,
 1279,  130,  131,  126, 1278,    0,    0,  113,  114,  152,
  112,    0,    0,  507,  220,    0,    0,    0,    0,    0,
  413,    0,    0,    0,    0,  434,  461,  459,  391,  389,
  210,  221,  222,    0,    0,    0,    0,  209,  233,  234,
  359,  340,  357,  338,  352,  355,  337,    0,  349,    0,
  351,  569,  568,    0,  575,    0,  579,  576,    0,    0,
    0,  218,  934,  217,  937,  930,  828,  823,  780,    0,
  998,    0,  960, 1123,    0,  976,    0,  844,  847,  846,
  848,    0,  800,    0,  803,    0,  667, 1209,  765,    0,
    0, 1100,    0, 1103, 1101, 1102, 1099,  754,    0,    0,
  744,  794, 1146,    0,    0, 1149,    0,  906,    0,  914,
  911,  716,    0,  714,    0,    0,  536,  746,    0,    0,
  739, 1064,    0,    0, 1067,  789,  788,    0,    0,    0,
 1032,    0, 1024, 1031,   79,    0,  125,    0,  512,  509,
  510,  485,    0,    0, 1001,    0,  520,  534,  486,  489,
    0,    0,    0,  441,    0,  465,  439,  224,  225,    0,
    0,    0,  236,    0,    0,    0,    0,    0,    0,    0,
  345,  347,  343,  342,  350,    0,  578,  580,    0,    0,
    0,  897,  898,    0,  916,    0,    0,  994,    0,    0,
  961, 1134,    0, 1133,    0,    0, 1046, 1047, 1043,    0,
    0,  674,    0,    0,    0,    0,    0,    0, 1106,    0,
    0,    0,    0,    0,    0,    0,  909,    0,    0,  715,
  705,    0,  707,    0,    0, 1078, 1023,    0,    0, 1029,
 1034,    0,    0, 1041,  115,    0,  119,    0,  503,    0,
    0,    0,  517,    0,    0,  442,    0,    0,  468,  466,
    0,  238,  237,  235,  360,    0,    0,    0,    0,  353,
  356,    0,    0,    0,  572,  573,    0,    0,  905,    0,
  918,    0,  917,  829,  824,  999,    0,    0,    0, 1138,
 1136, 1137,    0, 1005,  977,    0,    0,    0,  672,  665,
  682,  690,  675,  677,  676,    0,  671,    0, 1107,    0,
    0, 1106,    0, 1106, 1106,    0,    0,  751,    0, 1150,
 1151,    0,  912,    0,    0,    0,  709,  708,  749, 1051,
 1042,    0, 1036, 1038,    0,  136,    0,  502,  493,    0,
    0,    0,  516,    0,    0,    0,    0,    0,    0,  400,
  396,  398,  397,  395,    0,    0,  358,    0,  346,  348,
  344,  564,    0,  920,    0,    0,  996,    0, 1132, 1135,
 1044,  801,  802,    0,    0,  680,    0, 1105, 1104,    0,
    0,    0,    0, 1142,    0,    0,  910,    0,  723,    0,
    0,    0,    0,    0, 1080, 1025,  495,    0,  497,    0,
    0,  445,  449,    0,    0,    0,    0,    0,    0,    0,
  277,    0,    0,  320,    0,    0,    0,  274,    0,  300,
  303,  321,    0,    0,    0,    0,    0,  240,  242,  243,
  244,  245,  246,  247,  248,  249,  250,  251,  252,    0,
    0,  341,  362,  339,  574,    0,  919,  830,    0,    0,
  962,  673,    0,  669, 1106, 1159,    0,    0,    0,    0,
  719,  718,  713,    0,  711,  710, 1052, 1054,  499,    0,
  487,  443,  450,  216,    0,    0,    0,    0,  295,  294,
    0,    0,  296,    0,    0,  312,  309,  323,  278,  298,
  299,    0,    0,  284,  287,    0,    0,    0,    0,    0,
    0,    0,    0,  288,  239,  241,    0,    0,    0,  921,
  997,    0,    0,    0,    0,    0,    0,    0,  724,  720,
  712,    0,    0,    0,    0,    0,    0,  214,  310,    0,
    0,  289,  292,  285,  286,    0,  464,    0,    0,    0,
  268,  265,    0,  267,  258,    0,  270,  264,    0,  271,
  263,  253,  276,  302,  273,  283,    0,    0, 1048, 1003,
  963,    0,    0, 1175,  722,  721, 1055,  514,  444,  231,
    0,    0,  290,  291,    0,    0,  326,  279,    0,    0,
  307,  306,  301,    0,    0,    0,  259,  256,  261,  255,
  262,  254,  281,    0,    0,    0,    0,    0, 1153,  229,
  227,  328,  327,  272,    0,    0,  325,  324,  269,  266,
    0,    0,  280, 1049, 1161,    0,    0,    0,    0,    0,
  305,  260,  257,    0,    0, 1154,  317,  316,    0,    0,
    0,    0, 1173,    0,    0,    0,    0,    0,    0,    0,
 1172,
};
ZYshort yydgoto[] = {                                       2,
 1014,  796, 1202, 1358,  479,  229, 1098,  642,  805, 1241,
  562, 1610,  855,   50,  339, 1203,   72,  660,  461,  190,
  278,  279,  287, 1221, 1667, 1364, 1216,  916,  420, 1188,
 1189,   74,   75,   76,   77,   78, 1148,  674,  806,   86,
  943,  566,  568,   79,  485, 1146, 1164, 1165, 1368,  216,
 1045, 1171, 1595,  486,  218,  152,  153,  516,  517, 1491,
 1348, 1493, 1172,  715, 1174, 1175, 1450,  918,  654, 1451,
 1457, 1705, 1305, 1111, 1572,  655, 1150, 1421, 1252,  840,
  841, 1236, 1776, 1834,  497,  948, 1513,  498,  686, 1583,
 1584, 1135, 1643,  643,  644,  187,  188, 1553, 1554,  462,
 1096,  463, 1386, 1948, 1914,  645,  646, 1278, 1307, 1668,
 1337, 1310, 1113, 1656,  882, 1657, 1563,  616, 1707,   80,
 1650, 1087,  601,  445,  434, 1067, 1432,  503,  609,  869,
 1332, 1147,  504,  585,  505,  744,  624, 1102,   81,   82,
    3,    4, 1604, 1379, 1821, 1222, 1231, 1436, 1801, 1131,
 1132, 1543, 1544, 1545,  702,  703,  704,  509,  610,  574,
  575,  595,  596,  621,  622,   83,  927,  657,  658, 1312,
   33,  755,  544,  767,  545,  756,  668,  480, 1627, 1628,
  552,  553,  554,  555,    5,   10,   11,   23,    6,   13,
   21,   29,   37,   88,   51,  156,  132,  842,  134,  203,
   39,   34,   45,   90,  117,  158,  257,  157,  255,  166,
  921,  391,  576,  167,  168,  169,  170,  171,  172,  173,
  174,  175,  209,  403,  404,  725,  538,  978,  976,  399,
  400,  401,  534,  119,  120,  141,  177,  222,  178,  539,
  408,  736,  737,  457,  980,  738,  957, 1195,  670, 1190,
 1366, 1003,  223,  224,  225,  226,  273,  412,  543,  410,
  541,  740,  741,  989,   47,   40,   56,   95,  125,  148,
  143,  121,  182,  144,  232,  183,  233,  282,  416, 1031,
  793, 1522, 1397, 1248, 1249, 1250, 1251, 1400, 1524, 1396,
 1423, 1698, 1757, 1827, 1878, 1424, 1523, 1777, 1699, 1778,
 1779, 1780, 1781, 1782, 1783, 1784, 1785, 1786, 1787, 1788,
 1789, 1902, 1959, 1962, 1961, 1936, 1935, 1790, 1390, 1847,
 1384, 1839, 1928, 1791, 1844, 1849, 1933, 1850, 1956, 1934,
 1971, 1837, 1011,  811,  691,  417,  283,  549, 1032, 1617,
 1528, 1526, 1624, 1622, 1623, 1409,  784,  785, 1529, 1530,
 1527, 1525,  786,  227,  413, 1005,  228,  414, 1009,  546,
  415,  787,  788, 1017,  789,  790,  791, 1018, 1227, 1514,
 1383, 1068, 1694, 1874, 1555, 1754,  792, 1026, 1027,  195,
 1016, 1516,  758,  759,  760,  761,  762,  763,  764, 1373,
 1502, 1509, 1334, 1506,  996, 1214, 1211,  765, 1504, 1601,
 1689, 1136, 1602, 1605, 1478, 1107,   41,  155,  131,  197,
  421,  241,  422,  423,  418,  679,  424,  556, 1257, 1418,
 1419,  247,  248,  289,  293,  680,  341,  342,  343,  344,
  345,  346,  347,  348,  349,  350,  351,  352,  353,  354,
  355,  356,  357,  358,  359,  360,  361,  362,  363,  364,
  365,  366,  367,  368,  369,  370,  371,  372,  373,  374,
  375,  376,  377,  378,  379,  380,  381,  382,  383,  718,
  527, 1651,  716, 1176,  689,  452,  878, 1295,  617, 1085,
 1291, 1446, 1447, 1565, 1727, 1564, 1724,  906,  649,  971,
  972,  687, 1138, 1476,  945, 1473, 1327, 1475, 1677, 1816,
 1742, 1474, 1675, 1579, 1812, 1740, 1809,  922,  954,  651,
  912,  913,  914,  446,  605,  435,  587,  520,  712,  473,
  666,  451,  615,  384,  385,  386,  577, 1064,  844,  825,
 1547, 1267, 1546, 1716,  387,  388,  449,  872,  107,  578,
  579,  580,  442,  443,  598,  493,  683,  607,  428,  564,
 1672, 1578, 1323, 1715, 1796, 1040, 1426, 1039,  944, 1326,
  865, 1283, 1159,  958,  590,  436, 1433, 1551, 1638, 1911,
 1863,  853,  591,  440, 1072, 1281, 1645, 1556,  513, 1799,
 1549,  506, 1483, 1341, 1587, 1594, 1746, 1589, 1484, 1681,
 1559, 1646, 1945, 1743,  705, 1872, 1157, 1340,  919, 1660,
 1280, 1071, 1435, 1279,  488,  935, 1316,  939, 1319, 1575,
 1736, 1867, 1968, 1317, 1866, 1946, 1985,  489,  902,  904,
  903,  892,  149,  887,  128,
};
ZYshort yysindex[] = {                                   -279,
 -172,    0,    0, -279, -121, -160, -146, -121,   47,    0,
 -279,  434,  560,  508,    0,    0, -185, -121,  265,  717,
  536,  465, 1199, -121,    0,    0,  517,  781,    0,    0,
    0,    0,    0,  862,    0,    0, 1199,  635,  945,  839,
 -260,    0,  656,  864,    0,  876,  687,10181,10181,  821,
 1079,    0,  824,  887,  968,  929,    0,    0,    0,    0,
    0, 1245, 1250,  287, 1278,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0, 1509,    0,
 1086,  541, 1108, 1108,   97,  963,    0,  971, -194, -136,
 1170,    0,  992, 1058, 1062,    0,    0,    0,    0, 1575,
10181,    0,    0,    0,   97,    0,10181,    0,    0,    0,
 1122, 1122,    0, 1012, 1034, 1043,    0, 1048,    0, 1193,
 1414,    0, 1067, 1134, 1142,    0, 1635,10181,    0,    0,
 1334,    0,    0,    0,    0,    0,    0, 2180, 1148, 1096,
    0,    0,   92,    0,    0, 1099, 1172,    0,10181,10181,
    0, 1280, 1365, 1111,    0,  808, 1479, 1487,    0, 1511,
 1523, 1232, 1079, 1079, 1229,    0, 1030,    0, 1556,    0,
    0,    0,    0,    0,    0, 1328, 1148,    0, -335,    0,
    0,  182,    0,    0, 1211,    0,   16,    0,    0, 1791,
10181,10181,    0,    0,10181,    0, -217, 1222, 1223, 1225,
 1228, 1233,    0, 1331, 1241, 1079, 1079,    0, 1079, 1594,
 1514, 1079,    0,    0, 1079,    0,    0,  124,    0, 1447,
  955,    0, -300,    0,    0,    0, 1603, 1613,  124,    0,
    0,  182, 1356,    0,    0,10181,    0,    0,    0, 1280,
  769,    0,   -8,    0,    0,    0,    0,49604,    0,    0,
    0,    0,    0, 1547, 1279,    0, 1288, 1543, 1385, 1623,
 1626,    0,    0, 1646, 1651,    0,    0,    0, 1347,    0,
    0,    0, 1609,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0, 1379,    0, 1064, 1326, 1327,
    0,    0,    0, 1389, 1389, 1389, 1389, 7007,    0,10181,
11109,    0, 1389, 1389,    0, 1389,10181,10181,    0,  787,
 1389, 1671,    0, 1713,10181, 1389, 1389, 1389, 6740,10181,
  654, 7317, 1352, 1355, 1389, 1389,  388, 1534, 1389, 1389,
 -150, 7580, 7892,10181,10181, 1389, 1389, 1389, 1572,47768,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 1391,    0,    0, 1480,    0,    0,    0,  989,    0,  287,
    0, 1675, 1623,    0,    0,    0,    0,    0,    0, 1606,
    0, 1537,    0,    0,    0, 1698,  182, -220,    0,    0,
    0,  732,    0,49604,    0,    0,  524, 1569, 1545, 1548,
  507,10181, 1108, 7843, 1580, 1297,    0,  287,    0,10181,
  708, 1108,    0, 1422, 1497, 1586, 1451,    0,   95, -175,
 1595,    0,    0,    0,    0,    0,  187, 1941, 1713, 1713,
    0,  685,    0, 1377,  478,    0, -247, 1498,10181, 1500,
 1717, 1674, 1614,    0,    0,    0,    0,    0, 1389,  654,
  541,  541, 1409, 1727,    0,  915, 1419, 1619,49604,    0,
    0, 1451, 1625, 1545,    0, 1749,    0, 1621,    0, 1544,
    0,    0,   97, -165,   97,    0, 1498, 1582,    2,    0,
    0,    0,    0,    0, 1678,  948,    0,10181, 8156, 1639,
    0,10181,    0,    0, 1689,    0, 1652,    0,    0, 1079,
    0,  287,  287, 1734,    0, 1773,    0, 1568,  853,    0,
 1801,    0,  666,  595, -285, 1710,    0,  124,    0,    0,
  956,    0,    0,    0,    0, 1452, 1699,    0,47951,    0,
    0, 1451,    0,    0,10181,  307,10181,    0, 1188, 1588,
 1434, 1588,  842,    0,  936, 9450,    0,    0,    0,    0,
 8643,    0,10181, 1108, 1644,    0,    0,    0,    0,10181,
 1693, 1472, 1537, 1537,    0,    0,  718,    0, 1389,    0,
 1108,  842, 1422,    0,    0,    0,    0, -193,    0,  608,
10181,10181,10181,    0,    0, 1777,  997,  541,  541,    0,
  -45,    0,    0,    0, 1324,   88,  490,  660,  842,  842,
  842,  842,  842, 1079,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0, 1794,    0,    0,    0, 1502, 1101,
    0,  108,    0,    0,    0,    0, -207,    0, 1807, 1816,
    0,10181,10181,10181,    0,    0,    0, 1108, 1389, 1831,
  645,    0,  187, 8670,    0, 1389,  307,    0,49604,    0,
 1654,    0,    0,    0,    0, 1621, 1492,    0,    0,    0,
    0, 1835, 1819, 1795, 1796,    0,  -59, 1079,    0, 1667,
    0,    0, -135,    0, 1668, 1798, 1389,10181, 8795,10181,
    0,    0,    0, 1798, 1676,    0,    0,    0, 1860,    0,
    0,  287,    0, 1550, 1633,    0, 1653, 1604, 1671,    0,
    0, 1667, 1667, 1843,    0,    0, 1079, 1557, 1629, 1801,
    0,    0,    0, 1871, 1606, 1079, 1153, 1153, 1079,  -90,
 1079, 1861, 1647,    0,    0,    0, 1027,    0,    0,    0,
    0,    0,    0,    0, 1881,    0,    0,    0,    0, 1531,
 -286,  182,    0,    0,    0, 1079, -286,    0, 1079, 1861,
    0,    0, 1042,  729,    0, -317,    0,    0,    0,    0,
    0, 1079,    0,    0,    0,  551, 1782,    0, 1530,    0,
 1654,    0,    0,    0, 1852,    0,    0,    0,    0,    0,
  842, 1774, 1292, 1774, 1774,    0, 1589,    0,  842,  842,
  649,    0,    0, 1746,    0,    0,  639,    0, 1333,    0,
    0,   39,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   12, 1498, 1389, 1422,    0,  754,    0, 1389,
 1472,    0,    0,    0,    0, 1630, 1640, 1627, 1706,    0,
    0,    0,   41, 1108,    2,    0,    0,    0, -250,    0,
    0,    0,    0, 1729, 1745,  754,    0, 1564,    0,    0,
  685,    0, 1377, 1498,  187,    0,10181,    0,    0,    0,
    0,    0, 1691, 1888,  151,  151, 1891, 1891,    0, 1691,
 1691,  842, 1260, 1260,    0,    0,    0,    0,    0,    0,
    0, 1101,    0, 1824,    0, 1910,    0, 1389, 1655,    0,
    0, 1577, 1667,10181, 1916,    0, 1108, 1763,  754, 1389,
 1108,    0,    0,    0,    0,    0, 1601,  935, 1713, 1770,
    0, 1389,  353,    2, 1883,    0,   97,    0, 1819,  881,
 1112, 1112, 1821, 1547,  791,    0,    0, 1806,    0, 1667,
    0, 7003, 1241,    0, 1389, 1771,  754, 1906, 1389,    0,
49604, 1726,    0,    0,    0, 1079, 1550,    0,    0, 1079,
 1667, 1191, 1079, 1079, 1442,  596, 1079,  182,    0,    0,
    0,  182, 1948, 1079, 1861, 1949, -277, 1597, 1602,  182,
    0,    0,    0, 1803,  182,    0,    0,    0,  182,    0,
 1605,    0,    0,    0, -230, 1079, 1337,   97,    0,    0,
    0,    0,    0,    0, 1946, 2170,    0, 1670, 1670,  251,
 -173,    0,  -95, 1695, 1498,    0, 1241,    0, 9310,    2,
  649,    0,    0,    0, 1774,    0,    0, 1774,  649,  926,
    0,    0,    0, 1615,    0,    0,    0,    0, 1935,    0,
    0,    0, 1825, 1774,  -32, 1498,    0, 1673,  754,  285,
    0,    0,    0,    0,    0,    0,    0,    0, 1850,  286,
    0, 1389, 1389,    0,  997,    0,  523,   97,    0, 1448,
    0, 1691,    0,    0,  649,    0, 1454,  842, 1947,  685,
 1377,    0,    0,    0,    0,    0, 1920,  108, 1827,    0,
    0, 1389,  253, 1389,    0,10181,10181, 1389,    0,    0,
    0,    0,    0, 1389, 1377,10181,    0, 1883, 1873,    0,
 1960,    0, 1859,    0,    0, 1880,    0, 1883,  -57,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, 1823, -197, 1990, 1389,49604,    0,    0,    0,
    0,    0,    0,    0,    0, 1759,  -32, 1389,    0,    0,
10181, 1979, 1908, -313,    0, 1652,    0, 1725, 2035, 1079,
  632, 1079,    0,    0,    0,    0,    0,    0,    0, 1940,
 2036, 2036,    0,    0,    0,    0,    0,    0, 1748,    0,
    0,    0,    0, 2036,    0, 2037,    0,    0,    0,    0,
 2048,    0,    0,    0,    0, 1853,    0, 1823, 2039, 1079,
    0,  182,  182,    0,  182,    0,    0,    0,    0,    0,
    0, 2038,  729,  729, 1989,    0,    0,    0,    0,    0,
    0,  729, 1079, 1861, 1312,    0, 1895,    0,    0,    0,
 1911, 1915,    0,    0,    0, 1231, 1818, 1389,  776, 1882,
 -212,    0, 1314, 1931,    0,    0,   97,    0,    0,   97,
    0, -183, 1780, 1934,    0,    0,    0,    0,   97,    0,
 1498,    0,    0, 2049, -223, 1422,  754, 1422,  754,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  649,
 1990,10181,    0,    0,  959,    0, 1389, 1389, 1837,    0,
    0, 1389,    0,    0,  754, 1959, 1713, 1932,    0, 1798,
 1873, 2064,49604, 1883,    0,    0, 1750,    0,    0,    0,
    0,    0,    0, 1863, 1847, 1389,  253,    0,    0,49604,
    0, 1389, -183,  754,    0, 1906, 1823, 2010, 1778, 1389,
    0,    0,    0, 2103,    0,    0,    0,    0,    0, 2036,
    0,    0,    0,    0,    0, 1741,  541,    0,    0,    0,
    0,  182, -206,    0,    0, 1241, 1808,  182, 2043, 1741,
    0, 1779, 2091, 2105,   97,    0,    0,    0,    0,    0,
    0,    0,    0, 2098, 2104,  182,  182,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, 5956,    0,  729,
    0,    0,    0, 1498,    0, 1867,    0,    0, 1389, 1079,
 -144,    0,    0,    0,    0,    0,    0,    0,    0, 1934,
    0, 2092,    0,    0, 9463,    0,  386,    0,    0,    0,
    0,  443,    0,  491,    0, 1889,    0,    0,    0,  605,
  249,    0, 2063,    0,    0,    0,    0,    0, 1389, 1079,
    0,    0,    0, 1377,10181,    0,10181,    0, 1883,    0,
    0,    0, 1750,    0,49604, 1785,    0,    0, 1079, 1389,
    0,    0, 2000, 1498,    0,    0,    0,10181, 1389, 1823,
    0, 1823,    0,    0,    0, 1241,    0, 2036,    0,    0,
    0,    0, 1982, -170,    0, 1986,    0,    0,    0,    0,
 2050, 1667, 1972,    0, 2150,    0,    0,    0,    0, 1314,
  124,  182,    0, 1389, 1389, 1950, 1515, 1950, 1515, 1515,
    0,    0,    0,    0,    0, 1893,    0,    0, 1389, -169,
 1667,    0,    0, 2131,    0,49604,49604,    0,49604, 1498,
    0,    0, 1108,    0, -262, 2045,    0,    0,    0, 1389,
 1389,    0, 2125, -109, 1889, 1991, 1991,  108,    0,  108,
  108,  108,  187, 1798, 2042, 1838,    0, 1873,   97,    0,
    0, 1515,    0, 1785,  187,    0,    0, 1937, -135,    0,
    0, 1389, 1389,    0,    0, 2065,    0, 1883,    0, 2129,
 -170, 1854,    0, 2039,  182,    0, 1079, 1798,    0,    0,
 2013,    0,    0,    0,    0, 1079,   52, 2176,   52,    0,
    0, 1515, 1515, 1515,    0,    0, 1834, 2170,    0, 1667,
    0, 2003,    0,    0,    0,    0, 1892, 1498, 9463,    0,
    0,    0,10181,    0,    0,49604, -183, -183,    0,    0,
    0,    0,    0,    0,    0, 1849,    0, 2125,    0,  108,
  108,    0,  605,    0,    0, 2130, 1727,    0,10181,    0,
    0, 1873,    0, 1079, 2165, 1236,    0,    0,    0,    0,
    0, 1498,    0,    0, 2060,    0, 1597,    0,    0, 2141,
 1597, 2043,    0, 1498, 2205,  124, 1079, 2051, 3926,    0,
    0,    0,    0,    0, 1515, 1389,    0, 1515,    0,    0,
    0,    0, 1389,    0,49604, 1774,    0, 2175,    0,    0,
    0,    0,    0, -109, 1185,    0,    0,    0,    0,  605,
  605,  605,  108,    0, 1870, 1713,    0, 2196,    0,48501,
 1515,48685,49604, 1973,    0,    0,    0, 1597,    0, 2107,
10181,    0,    0,  124,  182, 2108, 2022, 1531,  981,  676,
    0, 2041, 1938,    0,  626, 1861, 2052,    0, 1079,    0,
    0,    0, 1079, 1079, 1079,  182, 7446,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0, 1927,
   31,    0,    0,    0,    0,49604,    0,    0, 1934, 1498,
    0,    0,  842,    0,    0,    0, 1377, 1671,   97, 1930,
    0,    0,    0, 1942,    0,    0,    0,    0,    0, 1498,
    0,    0,    0,    0, 1079, 2120, 2072, 1885,    0,    0,
  676,  676,    0, 1508, 1861,    0,    0,    0,    0,    0,
    0, 1079, 1861,    0,    0, 1079, 1079, -101, 1079,10181,
 2678, 2128,  199,    0,    0,    0, 1989,  182,  813,    0,
    0, 2087, 2121,  649,  605, 1713, 2203, 1765,    0,    0,
    0,49604, 2242, 2091,  182, 1079, 1079,    0,    0, 1079,
 1861,    0,    0,    0,    0,   18,    0, 1951, 9765, 1108,
    0,    0,  923,    0,    0,  983,    0,    0, 1085,    0,
    0,    0,    0,    0,    0,    0, 2004, 2032,    0,    0,
    0, 1377, 1389,    0,    0,    0,    0,    0,    0,    0,
  182,  182,    0,    0, 2011,  182,    0,    0, 2105, 1989,
    0,    0,    0, 1909, 9649, 9649,    0,    0,    0,    0,
    0,    0,    0, 2015,49604, 2203, 2094, 2216,    0,    0,
    0,    0,    0,    0,10181, 1980,    0,    0,    0,    0,
 9649, 9649,    0,    0,    0,10181, 1389, 2135, 1108, 9773,
    0,    0,    0, 1798, 2232,    0,    0,    0,10181, 1389,
 1939, 2237,    0, 1389, 1713, 2243, 1377, 1389, 2248, 1389,
    0,
};
ZYshort yyrindex[] = {                                      0,
    0,    0,    0, 2545,   34,   90,    0, 2546,    0,    0,
    0,    0,  209,    0,    0,    0,    0, 2114,    0,    0,
   29,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   42,    0,    0,    0,    0,   96,  169,
   84,    0,    0,    0,    0,    0,  214,    0,    0, 1936,
 -227,    0,    0,    0,    0,  200,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0, 4289,    0,
 2936, 2361, 3513, 3672,    0,    0,    0,    0,    0,   43,
  308,    0,    0,    0,  142,    0,    0,    0,    0, 4759,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 1944, 1944,    0,    0,    0,    0,    0,    0,    0,  412,
   89,    0,    0,    0,  305,    0,    0,    0,    0,    0,
 1814,    0,    0,    0,    0,    0,    0,   44,   78,    0,
    0,    0,  215,    0,    0,    0,    0,    0,    0, 2507,
    0,  497,11268,    0,    0,  279,    0,    0,    0,    0,
    0,  800, 2292, 2211,    0,    0, 2294,    0, 1207,    0,
    0,    0,    0,    0,    0,  242,  337,    0,  433,    0,
    0,  363,    0,    0,    0,    0,11419,    0,    0,    0,
    0,    0,    0,    0,    0,    0, 2018,    0,    0,    0,
    0,    0,    0, 1952, -278, 1961, 2277,    0, 2277,    0,
    0, 2292,    0,    0, 2292,    0,    0,    0,    0,    0,
  -99,    0,    0,    0,    0,    0,    0,    0,15394,    0,
    0,  338,  364,    0,    0,    0,    0,    0,    0, 1446,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0, 2005,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  406,    0,
    0,    0,  477,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,49787,    0,    0,
    0,    0,    0,30444,    0,    0,30709,30974,10909,31239,
    0,11219,31504,31769,    0,    0,32034,32299,    0,32564,
    0,  869,    0,    0,32829,    0,    0,    0,    0,33094,
33359,48134,    0,    0,33624,    0,    0,    0,    0,    0,
    0,    0,33889,    0,    0,    0,    0,    0,38898,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  290,    0,  838,
    0, -159,  917,    0,    0,    0,    0,    0,    0, 2302,
    0, 1308,    0,    0,    0,    0,  410,    0,13055,    0,
    0,49787,    0,    0,    0,    0,22470,39163,24335,34154,
20716,    0, 2871, 2138,39428,11578,    0,34419,    0,    0,
13855,17445,    0,14120,    0,39693,27529,    0, 8268,    0,
39958,    0,    0,    0,    0,    0,    0, 6541,    0,    0,
    0,    0,    0,48317,11529,    0,27794, 2287,    0,    0,
    0,    0,40223,    0,    0,    0,    0,    0,    0,34684,
 9573, 9930,    0,10287,    0,    0,    0,    0,    0,    0,
    0,24600,40488,28059,    0,    0,    0,40753,    0, 1371,
    0,    0,    0,    0, -153,    0, 2287,28324,46318,    0,
    0,    0,    0,    0, 7436,11419,    0,    0,    0,41018,
    0,    0,    0,    0, 2124,    0,41283,    0,    0, 2292,
    0,    0,    0, 1584,    0,    0,    0,  731,  738,    0,
    0,    0,    0, 1051,    0, -188,    0,19517,    0,    0,
  799,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,22735,    0,    0,    0,28589,    0,    0,    0, 2040,
    0, 2040,    0,    0,21031,  582,    0,    0,    0,    0,
    0,    0,    0, 2871,    0,    0,    0,    0,    0,    0,
34949,24865,16375,16645,    0,    0,    0,    0,    0,    0,
14385,    0,14120,    0,    0,    0,    0,    0,    0,21346,
    0,    0,    0,    0,    0, 1955,    0, 8594, 8951,17710,
    0,    0,    0,    0,    0,    0, 3306,    0,    0,    0,
    0,    0,    0, 1905,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0, 3618,    0,    0,    0,48869,    0,
    0,    0,    0,    0,    0,    0, -190,    0,    0,    0,
    0,    0,35214,    0,    0,    0,    0,12586,    0,    0,
    0,    0,    0,25130,    0,    0,    0,    0, 4589,    0,
26204,    0,    0,    0,    0,40753, -238,    0,    0,    0,
    0,    0, 1396,    0,    0,    0, -179,  844,    0,49970,
    0,    0,46583,    0,    0, 7171,    0,    0,    0,    0,
    0,    0,    0,11729,    0,49053,    0,    0,    0,    0,
    0,    0,    0, 1071,  957,    0, 1133,    0, 1404,    0,
    0, 1219, 1219,    0,    0,    0,  621,    0, -203,  323,
    0,    0,    0,  874,  350, 2292,    0,    0, 1820,   22,
 2292, 2311,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0, 1958,
15858,    0,    0,    0,    0,   74,15858,    0, 1000, 1032,
    0,    0,  107,    0,    0,    0,    0,    0,    0,    0,
    0,  436,    0,    0,    0,    0,    0,    0,    0,    0,
23000,    0,    0,    0,10130,    0,    0,    0,    0,    0,
    0,41548,    0,41548,41548,    0,    0,    0,    0,    0,
19771,    0,    0,    0,    0,    0, 1958,    0,19308,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,28854,    0,14650,    0,35479,    0,    0,
23530,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,35479,14385,46318,    0,    0,    0,22205,    0,
    0,    0,    0,    0,    0,35479,    0,    0,    0,    0,
 -254,    0, -235, 1445,    0,    0,    0,    0,    0,    0,
    0,    0,    0, 3930, 5854, 6213, 5128, 5495,    0,    0,
    0, 6806,    0,    0,    0,49053,    0,    0,    0,    0,
    0,35744,    0, 2252,    0,    0,    0,29119,36009,    0,
    0,    0, 1525,    0,    0,    0,11839,    0,35479,    0,
12851,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,41813,46318, -248,    0,    0,    0,  -36,    0,
    0,    0,    0,  207,    0,    0,    0,42078,    0,49970,
    0,    0,25409,    0,    0,    0,35479, 2591,    0,    0,
    0,    0,    0,    0,    0, 2292, 1071,    0,    0,  719,
 1219, 1992, 2292, 2292, 6453,    0, 2292,    0,    0,    0,
    0,    0,    0, -199,  -43,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,15238,18068,    0,    0,    0,    0,
    0,    0,    0,    0,12149,12334,    0,18368,18368,    0,
 2147,    0,    0,    0, 1341,    0,23265,    0,    0,46318,
20086,    0,    0,    0,41548,    0,    0,41548,20401,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,41548,26469, 2014,    0,    0,35479,25674,
    0,    0,    0,    0,    0,    0,    0,    0,42343,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,11268,
    0,    0,    0,    0, 7117,    0,    0,    0, 3508, 7693,
 7958,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,50153,    0,    0, 2200,    0,    0,
42608,    0,42873,    0,    0,    0,    0, -248,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  628,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,26469,    0,    0,    0,
    0, 2133,13320,14915,    0,41283,    0,    0,    0, 2292,
    0, 2292,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0, 2652,    0,    0,    0,    0,
 7271,    0,    0,    0,    0, 7019,    0, 3749, 5804, 1820,
    0,  123,  175,    0,    0,    0,    0,    0,    0,    0,
    0,18859,    0,    0,18712,    0,    0,    0,    0,    0,
    0,    0, 1345, 1672,  699,    0,    0,    0,    0,    0,
 1664,46952,    0,    0,    0,    0,    0,    0,    0,25939,
    0,    0,29384,43138,    0,    0,    0,    0,    0,    0,
    0,35479,    0,    0,    0,    0,    0,    0,    0,    0,
26734,    0,    0,    0,21935,15180,35479,15180,35479,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0, 7382,
    0,    0,    0,    0,36274,    0,  452,    0,    0,    0,
    0,  775,    0,    0,35479,    0,    0,    0,    0,11729,
    0,43403,    0, 2200,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  245,    0,    0,    0,    0,    0,    0,
    0,    0,35479,35479,    0, 2591, 1567,13585,26999,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0, 9974, 1799,    0,    0,    0,
    0,    0, 7847,    0,    0,10167, 6367,    0, 8148,    0,
    0, 2213,13015,18964,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  582,    0,    0,
    0,    0,    0, 2280,    0,    0,    0,    0,21611, 1637,
43668,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,43933,    0,    0, -158,    0,    0,    0,    0,    0,
    0,16915,    0,16915,    0,  979,    0,    0,    0,36539,
17180,    0,    0,    0,    0,    0,    0,    0,36804,  914,
    0,    0,    0,37069,    0,    0,    0,    0, 2200,    0,
    0,    0,44198,    0,    0,    0,    0,    0,  914,  468,
    0,    0,44463,29649,    0,    0,    0,    0,    0, 1567,
    0, 1567,    0,    0,    0, 9143,    0,    0,    0,    0,
    0,    0,    0, 5445,    0, 6695,    0,    0,    0,    0,
    0, 1219,    0,    0,17853,    0,    0,    0,    0, 2663,
 8554,  236,    0, 1546,    0,  177,    0,  177,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0, 2200,
49970,    0,    0,44728,    0,    0,    0,    0,    0, 2014,
    0,    0, 9261,    0,    0,44993,    0,    0,    0,    0,
    0,    0,47400, 2001,  979, 4021, 4021,    0,    0,    0,
    0,23800,    0,11729,    0,    0,    0,    0,    0,    0,
    0,    0,    0,45258,    0,    0,    0,    0,46848,    0,
    0,    0,    0,    0,    0,    0,    0, 2006,    0, -240,
 6163,    0,    0, 5404,    0,    0, 2292,  300,    0,    0,
 1405,    0,    0,    0,    0, 1459, 1608,21685, 1608,    0,
    0,    0,    0,    0,    0,    0,    0, -151,    0,49970,
    0,    0,    0,    0,    0,    0,    0,26734, -158,    0,
    0,    0,    0,    0,    0,    0,35479,35479,    0,    0,
    0,    0,    0,    0,    0,    0,    0,47584,    0,    0,
    0,    0,15490,    0,    0,    0,27264,    0,    0,    0,
    0,    0,    0, 2312,49237,    0,    0,    0,    0,    0,
    0, 2084,    0,    0,45523,    0,    0,    0,    0,    0,
    0, 6122,    0,12204,    0,    0,  809,  898, 1969,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,41548,    0,45788,    0,    0,
    0,    0,    0, 2001,47032,    0,47400,    0,    0,15800,
16110,24070,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0, 8789,
    0,    0,    0,18989,    0,    0, 2106, 1958,  748,  817,
    0,11935,12274,    0,   60,   65,    0,    0,   74,    0,
    0,    0, 3102, 2217, 1160,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0, 2178,
    0,    0,    0,    0,    0,    0,49421, 2009,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0, 2327,
    0,    0,    0,    0,  809,    0, 1996,    0,    0,    0,
  296,  817,    0,  845,  890,    0,    0,    0,    0,    0,
    0,   71,   65,    0,    0,   30, 3890,    0,10958,    0,
    0,    0,    0,    0,    0,    0,17697,    0,10453,    0,
    0,    0,46053,47216,10597,    0,50336,    0,    0,    0,
    0,    0,    0,13015,    0,  809,  809,    0,    0,  809,
  890,    0,    0,    0,    0,    0,    0,    0,    0,12031,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,29914,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,17982,17697,
    0,    0,    0,10869,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,37334,    0,37599,    0,    0,
    0,    0,    0,    0,    0,18916,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,12103,    0,
    0,    0,    0,11729,37864,    0,    0,    0,    0,    0,
    0,38129,    0,    0,    0,38394,30179,    0,38659,    0,
    0,
};
ZYshort yygindex[] = {                                      0,
 1810,    0,    0,    0, -465, -393, 1636,  -66, 1913,    0,
    0,    0, 1737,    0,    0, 1411,  504, -569,  -48,    0,
 -522, -215, 2396, -166, -267, -129, -637,-1056, 2403,    0,
    0,  -44, -737, -237,    0,    4, -965,  937,    0,    0,
 1811, 2113,    0,  -79,    0,  975,    0, 1435,-1000,    0,
    0, 1262,    0, 1945,    0, 2416, 1731,    0, 1912,    0,
    0,    0,    0,    0,    0, 1263, -325,    0,    0,    0,
    0, 1003,    0,    0,    0,    0, 1677,    0,    0, 1217,
 2080, 1598,    0, -476, 2132,    0,    0,    0,    0, 1057,
    0, 1507,    0,    0,    0,    0, 2410,    0, 1008, -446,
    0, -318,    0,  -69,  709, -583,  980,    0, -124, 1074,
    0, 1329,    0,    0, 1583,  943, 1104,    0,    0, -174,
  952,    0, -570, -551, -116, -836,-1376, -568,    0,    0,
    0,    0,    0,    0,    0,    0, -310, 1766, 2567,    0,
    0, 2673,    0, 1083,    0, 1680,    0, 1053,    0,-1092,
 1271,    0,    0, 1150, -162,    0, 1994,    0,    0,  466,
    0, 1666,    0,    0,    0,  -47,    0, 2195,   86,    0,
 2668,    0,    0,    0,    0, 2161, 2044,    0,    0,    0,
    0,    0,    0,    0, 1665, 1622,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  -42, 2595,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 2461,    0, -187,    0, 2550,    0,    0,    0,    0,    0,
    0,    0,    0,    0, 2315,    0,    0,    0, 1742,    0,
    0, 2321,    0,    0,    0,    0,    0,    0, 2551,    0,
    0,    0,    0, -724,    0,    0, -684,    0,  -75,    0,
    0, -761,    0, 2500,    0,    0,    0,    0,  995,    0,
  479,    0, 1995,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 1210,    0,    0,    0,    0, 1516, 1239,    0,    0,  973,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, -452,    0,    0,    0,    0,  924, -950,    0,
  875,    0,    0,    0,  931,    0,    0,    0,    0,    0,
    0,    0, -802, 2191,    0,    0,    0,    0,    0, 1243,
    0,    0,    0,    0,    0,    0, 1521, 1522,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0, 1393,  903,
    0, -456,    0,    0, -693,    0,    0,    0, 1560,-1003,
    0,    0,    0,    0,    0, 2234,    0,    0,    0,    0,
    0, 1105,-1141,    0, 2053,    0,    0,    0,    0,    0,
    0, -696, 1190,    0,    0,    0,    0,    0,    0,    0,
 2558,    0,    0, 2383,    0, -131,    0,    0,    0,    0,
    0,    0,    0,    0,    0, -879, -276,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0, 1641,
    0, -625,    0,    0, 2123,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, 1339, 1004,    0,    0,    0,    0, 1862,    0,    0,
    0, 1903,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0, -784,
    0,    0,    0,    0,    0,    0,    0, 1953, -176,    0,
    0,    0,    0, 2219,    0,    0,    0,  400,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, 1237,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0, 1230,    0,    0,    0,    0, 1266,
    0,    0,    0,    0, -918,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,
};
#define YYTABLESIZE 50934
ZYshort yytable[] = {                                      73,
   73,   84,  268,  464,  982,  108,  105,  231,   89,  502,
  236,  659,  962,  625,  669,  230, 1121,  258, 1022,   98,
  968,  398, 1234,  548, 1054,  794, 1077, 1042,  546, 1046,
 1047,  848,  864,    2, 1219,  550, 1322,  292,  242, 1084,
 1225,   34,   33,   50,  894,  243, 1025,  983,  984,  659,
  659, 1303,  127, 1548,  484,  173,  235,  231,  130,  144,
   62,  876,   63,  529,  531,  280,  531,   99,  660,   48,
  747,  703,  144,   62,  144,   63, 1377,  104,  501,  151,
  525, 1232,  631,  629, 1640,  630, 1234,  632,  411,   32,
  970, 1177, 1119,  926, 1701,   96, 1702, 1234,   87,   68,
  186,  189,  297,  652,  297,  693, 1066,  146, 1211,  146,
 1211, 1211,  929,  144,  144,  144,  340, 1011,  824,  113,
  210,  211,  405,   68,  950, 1500,  821, 1224,  889,  389,
 1169,  510,  511,  870,  487, 1028,  220,  703,   68, 1599,
 1134,  200,  238,  239,  612, 1540,  151,  111,  106,  626,
   62,  866,   63,    1,  699,  863,  165,  745,  967,  165,
 1253, 1242,  398,  259,  260, 1129,  261, 1012,  192,  264,
  881,  220,  265,   68,  409, 1243, 1244, 1439, 1440,  525,
 1652,   87,  895,  896,  897,  898,  899,  186, 1230,  620,
    9, 1369,  631, 1232,   68,   68, 1653,  632,    7,  198,
  659,   68,   57, 1371,   58, 1489,  694,  165,  189,   68,
 1212,  221,  144,  195,  191,  146,  519,  618, 1011,  401,
  144,  401,  859, 1020,   62, 1020,   63,   57, 1468,   58,
   59, 1130, 1275, 1209,  750,  206,  619,  144, 1114,   12,
  659,   62,  231,   63, 1335,  112,  221,    1,  501,  433,
  860,  437,  439,  597,    9,  540,  582, 1013,  448,  450,
 1265, 1641,  745, 1266,  144,  599,   73,  465,  173,  613,
  471,  472,  611,  483, 1029, 1160, 1630, 1339,   15, 1271,
 1104,  656,  529,  515,  433,  521,  522, 1059,  144, 1600,
 1213,  699,  559, 1065,  720,  721, 1182,  256, 1069,   60,
 1654, 1541,   73,  531,  333,  656,  883,   98, 1254, 1091,
 1255,  144,   60,  274, 1501,  581, 1093, 1094,  525,  165,
  884,   34,   33,   50, 1441, 1245, 1060,  633,  766,   62,
 1066,   63,   90,  653,   90,   49,   99,  197,  293,  708,
  293,  297,  701,  173, 1642,   49,  146,  114, 1592,  501,
 1593, 1764,  144,  886, 1115,  659,   57, 1226,   58, 1496,
  256,  706,  194,  199, 1041, 1230,   47,   57,  144,   58,
   59,  703, 1049, 1050,  660,  647,  648,  745, 1015,  867,
 1139,  868,  266,  433,  551,  584,   18, 1063,  843,   60,
   61,  592,  531,   98,  531,  512,  244,   34,   33,   50,
 1466,  709,  529,  144,  546,  936,  671,  849, 1336,  332,
  173,  100, 1507, 1167,  917,  747,  885,   34,   33,   50,
  661, 1330, 1861,  692,  862,  696,  745, 1088,  115,  656,
  116, 1321,  158,  104,  695, 1429,  401,  633,  401,  401,
 1246,   99, 1020, 1470,  146,   32, 1011,  700, 1230,  618,
 1443,   96, 1445,  104,   68, 1095, 1100, 1100,  401,  401,
 1482,  546,  571,   60,  411,   32,    6,   14,  619,  433,
  584,   96, 1256,  713,   34,   33,   50,  106, 1462,  701,
   60,   61, 1393, 1655,  974, 1673,  487,  719, 1061,  809,
 1772,  930, 1057, 1925, 1272, 1387, 1025, 1597,  405,  411,
  139,  757,  180,  783, 1391,  144, 1486, 1487, 1298,  953,
  104, 1662,  600, 1664, 1665, 1666,  802,  200,  807, 1238,
 1703,  411,   32, 1926,  146,  104,  144,   50,   96,  656,
 1287, 1289,  584,  405,  847,  144, 1858, 1296,  267,   66,
 1296,  851,  290,  671,  192, 1568, 1313, 1314,   90,  411,
  409,  256,   34,   33,   50,  405,  106, 1704, 1230,  394,
   16, 1284,  873,  874,  875,  297, 1315,  293,   60,   61,
  146,   90,   90,   67,  200,  198,  144,  293, 1259, 1737,
 1569,  535, 1058,  405,  189,  409,   68,   90,  104,  195,
  191,  900, 1101, 1101, 1205, 1581, 1343,  231, 1206,  411,
   32,  192,  803, 1728, 1729,  291,   96,  409,   50, 1273,
   50,  206, 1062,  925,  661,  928, 1344, 1089, 1239,  411,
  804, 1127,   90,   69, 1713,  937, 1467, 1471, 1125,  192,
  144,  531,  198,  405,   15,  409,  411,  411,  881, 1693,
  181,  189, 1128,   90,   90,  401,  195,  191,  747,  495,
   90, 1300,  200,  405,   15,  955,  139,   73,   90,  515,
  584,  966, 1129,   98,  176,  144, 1634, 1635,  206, 1636,
  405,  405, 1535,   70,  195,  191, 1805, 1308,   15,  192,
  333, 1080,  401,   98,  496,  409,  535, 1078, 1285,  200,
  631,  629,   99,  630,  986,  632,  608, 1127,  394,  192,
  411, 1570, 1079,  993,  144,  409,  998,  999, 1001, 1276,
  198,   15,   99,  197, 1230, 1442,  192, 1444,   66,  189,
   71,   90,  409,  409,  195,  191,  631,  629, 1130,  630,
  198,  632,  178, 1019,  405,  178, 1021,  333,  194,  199,
   98,  223,  920,  223,  195,  191,  206,  198, 1309, 1030,
 1117,  176,   67,  206,  930,   90, 1296, 1240, 1296, 1296,
  890,  195,  191,   47,  891,   68, 1721,  100,   90,   99,
  197,   62, 1577,   63,  883, 1166, 1151, 1151, 1296, 1296,
  192, 1133,  920,  206,   99,  332,  409,  100,  158,   15,
  293, 1557,  293, 1296,  169,  194,  199,  427,  429,  430,
  431,  535,   69,  144,   19,   90,  441,  444,  158,  447,
 1722, 1723,  747,  231,  455,  333,  569,  231,   98,  466,
  467,  468, 1277,  194, 1437, 1151,  191, 1607,  492,  494,
  231, 1382,  507,  508,  231, 1797, 1099, 1099,  151,  523,
  524,  525,  332, 1321,  100,  570, 1033,   99,  197, 1261,
  535,  144,   70,  144, 1196,   90, 1631, 1232, 1197,  293,
 1811,  293, 1815, 1817, 1034,  158,   87, 1137,  197,  169,
  917, 1149, 1149,  194,  199,  661,  738, 1264,   26,  144,
 1669,  820, 1558,  144,   62,  197,   63,  297, 1099,  297,
 1196,  681,  750,  194, 1197,  178, 1232, 1840, 1841,   71,
 1566, 1687,   90,   90,  106, 1145, 1905,  933, 1292,  474,
  194,  199,  745, 1163, 1696,   20, 1860,  569, 1567, 1296,
  332,  742,  100,   62,  743,   63,  934,  571, 1296,  627,
  746, 1798,  146, 1179,  146,  633,  169, 1181, 1232,  106,
 1191, 1192,  144,  158, 1204, 1714,  570,  738,  603,  893,
  747, 1208,  106, 1217,  627, 1828,  628, 1536,  635,  636,
  637,  801, 1296,  750, 1226,  572,  888,  631,  629, 1560,
  630,  633,  632, 1228,  634, 1296,  103,  144, 1499, 1954,
  223,  144,  667,  635,  636,  637, 1166,  419, 1247,   78,
 1263,  870, 1917,  858,  243, 1949,  123, 1350, 1612,  560,
  123, 1829, 1520, 1521, 1845, 1355, 1464,  650, 1296,  123,
   60,   61, 1296,   57,  573,   58,   59, 1561,  670,  293,
  293,  670,   22,  670,  285,   64,  104, 1588,   78,  293,
 1299,  286, 1198,  561,  144,   57,  460,   58,   59,   62,
  823,   63,  144, 1066,  144,  748,   28,  231,  231, 1747,
  231,  742,  749, 1749, 1199, 1381, 1381,  144, 1232, 1331,
  627,  475, 1296,   78, 1408, 1964,  572,  661,  661, 1226,
 1625,   64, 1416, 1883,  146,  871,  146, 1320,   30,  144,
 1155, 1885,   64, 1868,   78,   78,  846,   27, 1299,  293,
  144,   78,  144, 1637,  581,  476,   87, 1052,  293,   78,
  477,   57,  441,   58,   59, 1842, 1843,  557,  726, 1296,
 1819,  742,  581,  144,  750,  573,  846,  256,  198, 1924,
 1226, 1200, 1345,   60,   61,  751,  297,  752, 1521, 1830,
   35, 1238, 1293,  144,  638,   87, 1294, 1354,   64, 1360,
   57,  639,   58,   59,  727, 1365,  144,  742, 1356,  478,
 1238,   36,  859, 1201,   62,  915,   63,  728,  180,  638,
   66,  729,   60,   61,  199,  200,  639,  846,  640,  230,
   87,  146,  667,  144,  123,   65,  144, 1380,  144,  940,
  860, 1437, 1232, 1459, 1226,   43, 1053, 1427, 1503, 1357,
 1428,   87,   87,  640,   67,  144,  123,  231,   87, 1434,
 1392,  753,  144, 1151,  144,   38,   87,   68,  754, 1725,
  963, 1480,  633,  846,   65,   80,  742,   78,  256, 1833,
  843,  231,  231,  992,   44, 1744,  631,  629, 1000,  630,
  593,  632,  230, 1226, 1448,  144, 1497, 1751,  670,  670,
  670,  670,  656, 1663,   69,  569,  230,  230, 1010,   65,
 1510,  201,   46, 1449,   80, 1452,   57,  458,   58,   59,
  670,  670,  532,  742,   65,  862,  730,  862,  670,   52,
   65,   65,  641,   66,  570,  670,  144,   65,   60,   61,
 1979,  144,  144, 1835,  670,   65,  459,  453, 1907,   80,
 1453, 1498,  533,   64,   70,  123,  144,  641,   55,  460,
  454, 1908,   62,  594,   63, 1517, 1829,   67, 1596,  121,
   80,   80,  822,  146,  146,  230, 1044,   80,  256,  419,
   68, 1365,  191,  230,  192,   80,  243,  160,  146,   82,
  917,  742,  917,  917,  917, 1365, 1730, 1726, 1731, 1732,
 1937,   71,   82, 1862,   78,  164,  731,  231,  444,  230,
   87,  603, 1938,  444, 1880, 1881, 1864,   69,   85, 1140,
  202, 1824,  161, 1873,  888,  631,  629, 1141,  630, 1142,
  632,   57,  732,   58,  542, 1454, 1639, 1539,  733,  603,
  742,  795, 1854,  162,  163,  742, 1552,  734,  670,   94,
  164,  148,  707,   60,  572,  148,  230, 1859,  165,  907,
 1939,  670,  908,  909,  148,  193,  879,   70,  194,  106,
  670, 1455, 1940,  330,   53,  330, 1574, 1573, 1576,   65,
  164, 1109,  917,  917,  656, 1807,   54,   62,   66,   63,
 1151,  144,  603, 1120, 1830, 1006, 1585,   91, 1020, 1590,
 1020,  144,  144,  573,  670, 1127, 1238,   57, 1238,   58,
 1023,   87, 1007, 1144,   71,   31,   32,  670, 1803,  144,
 1831, 1832,   67,  146, 1906,  144,  735, 1024,  444,  808,
  603,  633, 1173, 1143,  270,   68,  144, 1215,  144, 1865,
 1753, 1920, 1145, 1960, 1145, 1145, 1297,  164, 1297, 1297,
 1215,  194, 1927,  460,  670,  917,   62,  146,   63, 1674,
   92,  144, 1941,  144,   55,  627,  148,  628, 1972, 1973,
  146,  230,   69,  675, 1942,  144,  271,  272,   93,   57,
  458,   58,   59,  676, 1833,  634,   96, 1950, 1951,  627,
   65,   97, 1953, 1123,  635,  636,  637, 1145, 1823,   55,
  100,   60,   61, 1124,  670,  797,  256,  146,  101, 1097,
 1456,   57,  102,   58,   59, 1912,   64,   62, 1183,   63,
   55,   55,   70,  180, 1695,  144,  180,   55,  603,  106,
   80,  670,  603, 1700, 1043,   55,  109, 1145, 1145, 1145,
  231,  118,  910,  911,  110, 1286, 1288,  856,  857,  880,
 1552,  670,  124,  627, 1720,  628, 1229,  146, 1230, 1184,
 1234,  231, 1234, 1234,  144,  122,  144,  144,  123,   71,
  633,  915,  144,  634,  126, 1306,  231, 1311,  588,  589,
 1735,  444,  635,  636,  637,  136,   92, 1318,   92,   15,
  330, 1738,  330,  330, 1412,  133, 1413, 1234,   25,   62,
  140,   63, 1217,  213,  146,   15, 1217,  137,   57,  148,
   58,   59,  330,  330, 1755, 1020,  138, 1020, 1020, 1338,
 1145,  139, 1238, 1145,  647,  648,   60,   61,    8,  142,
  603,  444,  994,  995, 1987,   18,  215, 1020, 1020,  144,
  145,   24,   65,  231,  146, 1238, 1238, 1238, 1238,  147,
  148,   66,  150,  144,  144,  154, 1145,  812,  813,  814,
  231,  176, 1822, 1217, 1234, 1297, 1234, 1297, 1297,  179,
  638,  231,  184,   57,  458,   58,   59,  639,  144,  815,
  144,  144,  185,  627,  196,   67, 1848, 1297, 1297, 1674,
 1851, 1852, 1853, 1055, 1056,   60,   61,  204,   68,  215,
  144,  144, 1297,  459,  640,  205,  231,  231, 1193, 1194,
   64,  231,  460,  215,  215,   62,   57,   63,   58,   59,
  144, 1415, 1417, 1185, 1186, 1187,  602, 1394, 1395,  206,
  144, 1238, 1422, 1375,   57,   69,   58,   59,  816, 1840,
 1841,  207, 1875,   62, 1215,   63, 1215, 1215, 1916,  499,
  603,  208,  603,   57,  458,   58,   60,   61,  638, 1884,
  212,   73, 1890, 1886, 1887,  639, 1889,   62, 1904,   63,
 1458, 1306, 1238,  549,  215, 1461,   66,  213,  603,  217,
   55,  215,  215, 1915,  234,   70, 1226,  500, 1226, 1226,
  215,  237,  640, 1921, 1922,  249,  250, 1923,  251, 1306,
 1932,  252,   92,  144,  254, 1485,  253,  603,  641,  330,
   67,  256,  262, 1173,  263, 1215,  215,  330,  395,  330,
  269,  276,  144,   68,  144,   92,   92,  399, 1297,  399,
  399,  277,   71,  281, 1020,  817,   65, 1297,   60,   61,
  213,   92, 1020,  389, 1020,   66, 1958, 1958,  820,  399,
  399,   62,  392,   63,  213,  213,  144, 1975,  144,  144,
   69,  393,  394,  215,  406,  402,   73, 1969,  405,  407,
 1982, 1297, 1958, 1958, 1986,  411,   92, 1974, 1989,   67,
 1991, 1978, 1538,  232, 1297,  232,  232,  144,  409,  290,
 1981,  146,   68,  146,  146,  232,  641,   92,   92,  425,
  426,  456,  490,  146,   92,  491,  526,  530,  536,  531,
   70,  540,   92,  396,  397,  542,  547,  586,  144,  563,
  627, 1297, 1458,  330,  144,  565,  600,  604,  567,   69,
  606,  213,   57,  458,   58,   59, 1238, 1238, 1238,  614,
  623,   87,   62, 1458,   63,  662,  656,  663, 1020,  635,
  636,  637, 1591,  664,   60,   61,  672,   71,  232, 1361,
  673,  665,  459,  144,  677,  144,  146,  818,  678,   64,
  495, 1297,  232,  232,  688,   92,  682,  545,  215,   70,
  146,  146,   60,   61,   57,  770,   58, 1614, 1615,  690,
 1144,  698, 1144, 1144,  129,  711,  129,  722,  717, 1626,
  689,  706, 1629,  689,  213,  689,   60,   61, 1224,   92,
 1224, 1238,  714, 1238,  118,  723,  724,  118, 1297,  739,
  799,  118,   92, 1647, 1648,  798,   71,  810,  850,  549,
  118,  915,  852,  915,  915,  915,  549,  854,  144,  318,
  877,  901,  318,  923,  318, 1144,  924,  146,  905,  232,
  118,  549,  549,  932,  549, 1683, 1684,  146,  942,   92,
  947,  144,  144,  118,  549,  949,  549,  118,   57,  458,
   58,   59,  500,  960,  951,  952,  956,  961,  973,  977,
  969,  975,  979,  981,  985, 1144, 1144, 1144,  987,  991,
   60,   61, 1004, 1002,  549,   65,  988,  549,  549, 1008,
 1010, 1035,  549, 1036,   66,   64, 1038,  549,  474,   92,
  822, 1051,   57, 1082,   58,   59,  549, 1073,  771,  213,
 1048,  549,  232,  915,  915,  638, 1075, 1074, 1076, 1083,
  146,  118,  639, 1086,  144, 1092,  549,  633,   67, 1106,
 1108,  549, 1112,  549, 1110, 1401, 1116, 1118, 1122,  549,
 1126,   68, 1134, 1153,  772, 1168,   92,   92, 1361,  640,
 1158, 1178, 1170,  144,  144,  144, 1207, 1210, 1144, 1793,
 1218, 1144,  118,  194,  773, 1220, 1795, 1224,  549, 1233,
  549,   60,   61, 1362, 1363, 1235, 1258, 1268,   69, 1269,
 1270,  774, 1282, 1274, 1301,  118,  915,  549,  775, 1302,
  549,  549,  144,  144, 1144, 1304,  549,  549, 1130, 1324,
  129, 1325,  549, 1402,  549, 1328,  549,  118, 1333,  627,
  689,  689,  689,  689, 1224, 1342, 1346,  226, 1238,  776,
 1238,   65, 1347,  129,  129,  129,  129,  232,   70, 1352,
   66,  549,  689,  689,  549,  146,  549, 1224, 1224,  777,
 1238, 1238,  118, 1353, 1367,  587,  587,  689,  587,  318,
  475,  318,  318,  641,  549, 1370, 1374, 1372,  587, 1378,
  587, 1385, 1375,  778,   67,  549,  779,  780,  118, 1389,
 1398,  318,  318,  781,  118,   71, 1399,   68, 1414, 1425,
  226, 1420,  549,  118,  476, 1403,  318, 1431,  587,  477,
 1430,  587,  587, 1438,  226,  226,  587, 1460, 1463,  549,
  549,  587, 1465, 1469,  549, 1477,  118, 1479, 1492, 1472,
  587, 1495, 1490,  549,   69,  587, 1226, 1512, 1505, 1518,
  118, 1515,  549, 1404, 1508,  549, 1519,  228, 1537,  144,
  587, 1550, 1571, 1562,  549,  587,  144,  587,  478,  549,
  549,  549,  144,  545, 1582, 1586,  549,  549,  549, 1598,
 1292, 1292, 1292, 1292, 1292, 1292, 1603, 1292, 1608,  118,
  549,  549,  118,  144,   70, 1606, 1947, 1609, 1292,  773,
 1632,  226,  587,  689,  587, 1644,  144,  549, 1649, 1616,
 1659, 1670,  689, 1680,  144,  159, 1671, 1686, 1688,  144,
  228,  587, 1697, 1691,  587,  587, 1706, 1712, 1630, 1733,
  545,  587, 1717, 1739,  228,  228,  587, 1745,  587, 1748,
  587,   71,  318, 1752, 1800, 1808,  689, 1756, 1806, 1818,
 1947,  318, 1820, 1826, 1825, 1405,  144,  160, 1836,  689,
 1846, 1838, 1857, 1947, 1870,  587, 1876, 1947,  587, 1877,
  587, 1947, 1909, 1947,  226, 1903, 1871, 1879, 1913, 1910,
 1918, 1618, 1943, 1620, 1621,  318, 1930, 1944,  587, 1952,
 1955, 1967,  161, 1963, 1966, 1970,  689,  144,  318,  587,
 1406,  779,  780,  228, 1976,  256,  144, 1980, 1407,  144,
  144,  228, 1984,  162,  163, 1234,  587, 1983, 1988, 1234,
  164, 1234, 1234, 1990,    3,    4,    6, 1237,  165, 1130,
  144,  144,   73,  587,  587,  318, 1676,   21,  587,  144,
  531,   47,  781, 1234,  651,   44,  689,  587, 1027,  146,
  529,  537,  144,  144, 1234, 1224,  587, 1026,  527,  587,
 1234,  144,  308, 1234,  144, 1234, 1020, 1070,  587,  941,
 1156, 1359,  245,  587,  587,  587, 1709, 1710, 1711,  246,
  587,  587,  587, 1734,  228,  318,  684, 1488, 1349,  226,
  240, 1037, 1494,  689,  587,  587, 1292, 1090,  938,  964,
 1292, 1708, 1292, 1292, 1534,  782, 1237,  685, 1152, 1292,
 1292, 1292, 1292, 1039, 1292, 1039, 1292, 1292, 1292, 1292,
 1678, 1292, 1292, 1292, 1329,  284, 1719, 1292, 1292, 1292,
 1292, 1292,  318, 1292, 1965, 1741, 1292, 1292, 1679, 1292,
 1292, 1292, 1292, 1292, 1292, 1481, 1802, 1290, 1658, 1103,
 1292,  129, 1292, 1292, 1292, 1292, 1292, 1292, 1804, 1792,
 1292, 1292, 1794,   17, 1292, 1292, 1692, 1234, 1223, 1292,
 1718, 1542, 1292, 1633, 1292, 1292,  959, 1292, 1292, 1292,
 1292,  697, 1260, 1292,   42,  768,  135, 1292, 1292, 1292,
 1292, 1292,  931, 1292,  390, 1813,  214,  537, 1180,  228,
  535, 1234,  275, 1292, 1292, 1292, 1234,  219, 1292, 1611,
 1292, 1376, 1292, 1292,  990, 1292, 1292, 1292, 1292, 1292,
 1292, 1292, 1292, 1292, 1292, 1292, 1292, 1292, 1292, 1856,
 1292, 1292, 1292, 1292, 1292, 1292, 1292, 1292, 1292, 1292,
 1613, 1929,  819, 1292, 1882, 1292, 1292, 1292, 1292, 1292,
 1619, 1888, 1410, 1411, 1511, 1234, 1919, 1292,  769, 1292,
 1292, 1292, 1292, 1292, 1292, 1292, 1292, 1292, 1292, 1292,
 1690, 1292, 1292, 1388, 1292, 1292, 1750, 1292,  288, 1292,
  997, 1292, 1292, 1292,  558, 1292, 1292, 1292,  946, 1292,
 1292, 1580, 1869, 1292, 1105, 1154, 1351,  861, 1682, 1292,
 1292, 1081, 1292, 1292, 1292, 1292, 1292, 1292, 1292,    0,
 1685, 1292, 1661, 1292,    0, 1292, 1292, 1292, 1292, 1292,
    0,    0, 1292, 1292,    0, 1292,    0,    0,    0, 1292,
 1039, 1292, 1039, 1039,    0,    0, 1292, 1292,    0, 1292,
    0,    0, 1292,    0,    0, 1292,    0, 1292, 1292, 1292,
 1292,    0, 1039, 1039,    0,    0, 1292,    0,    0, 1292,
 1292,    0, 1292, 1292, 1292,    0,    0, 1292,    0, 1292,
 1292,    0,    0,    0, 1292,    0, 1292, 1292, 1292, 1292,
    0, 1292,    0,    0,    0, 1292,    0,    0,    0,    0,
 1292,    0, 1292, 1213,    0, 1213,    0, 1292,    0, 1292,
 1292, 1292, 1292,  511, 1292,    0, 1292,    0,    0,    0,
    0, 1292,    0,    0,  219,    0, 1292, 1292, 1292, 1292,
 1292, 1292,    0, 1292, 1292, 1292,    0, 1292, 1292,    0,
    0,    0, 1292,    0, 1292, 1292, 1292, 1292, 1292, 1292,
 1292, 1292, 1292, 1292, 1292,    0, 1292, 1292, 1292,  511,
 1292, 1292,    0, 1292, 1292, 1289, 1289, 1289, 1289, 1289,
 1289,    0, 1289,  511,    0,    0,    0,  511,    0,    0,
    0,    0,    0, 1289,    0,    0,    0,  219,    0,    0,
    0,    0,    0,    0, 1891, 1892,    0,  511,    0,    0,
    0,  219,  219, 1039,    0,    0,    0,    0,    0,    0,
    0,    0, 1039,    0,    0,    0, 1893,    0,    0,    0,
    0,    0,    0,    0,    0,    0, 1894,    0,    0,    0,
    0,    0,    0,    0, 1895,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0, 1039,    0,    0,    0,
  511,    0,    0,    0,    0,    0,    0,    0,    0, 1039,
    0,    0,    0,    0,    0,    0,    0,  511,    0,  219,
  219,    0,    0,    0,    0,    0,    0,    0,  219,    0,
    0,    0,  219,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  511,    0,    0,    0, 1039,    0,    0,  511,
    0,    0,    0,    0,  219,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 1213,    0, 1213, 1213,    0,    0,    0,    0,    0,    0,
    0, 1213,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, 1213, 1213,    0,    0, 1039,    0,    0,    0,
    0,  219,    0,    0,    0,    0,    0, 1213,    0,    0,
    0,  511,  511,    0,    0,    0, 1896,    0,    0,    0,
 1897, 1898,  511,    0,  511,    0,    0,    0,    0,    0,
    0, 1289,    0,    0,    0, 1289,    0, 1289, 1289,    0,
    0,    0,    0, 1039, 1289, 1289, 1289, 1289, 1899, 1289,
    0, 1289, 1289, 1289, 1289,    0, 1289, 1289, 1289, 1900,
 1901,    0, 1289, 1289, 1289, 1289, 1289,    0, 1289,    0,
    0, 1289, 1289,    0, 1289, 1289, 1289, 1289, 1289, 1289,
    0,    0,    0,    0,    0, 1289,    0, 1289, 1289, 1289,
 1289, 1289, 1289,    0,    0, 1289, 1289,    0,  511, 1289,
 1289,    0,    0,    0, 1289,  511,    0, 1289,    0, 1289,
 1289,    0, 1289, 1289, 1289, 1289,  219,    0, 1289,    0,
    0,    0, 1289, 1289, 1289, 1289, 1289,    0, 1289,    0,
    0, 1213,    0, 1213,    0, 1213,    0,    0, 1289, 1289,
 1289,    0, 1213, 1289,    0, 1289,    0, 1289, 1289,    0,
 1289, 1289, 1289, 1289, 1289, 1289, 1289, 1289, 1289, 1289,
 1289, 1289, 1289, 1289,    0, 1289, 1289, 1289, 1289, 1289,
 1289, 1289, 1289, 1289, 1289,    0, 1213,    0, 1289,    0,
 1289, 1289, 1289, 1289, 1289, 1219, 1219,    0, 1219, 1213,
 1219,    0, 1289,    0, 1289, 1289, 1289, 1289, 1289, 1289,
 1289, 1289, 1289, 1289, 1289,    0, 1289, 1289,    0, 1289,
 1289,    0, 1289,    0, 1289,    0, 1289, 1289, 1289,    0,
 1289, 1289, 1289,    0, 1289, 1289, 1213,    0, 1289,    0,
    0,    0,    0,    0, 1289, 1289,    0, 1289, 1289, 1289,
 1289, 1289,    0, 1289,    0,    0, 1289,    0, 1289,    0,
 1289, 1289, 1289, 1289, 1289,    0,    0, 1289, 1289,    0,
 1289,    0,    0,    0, 1289,    0, 1289,    0,  144,  144,
    0, 1289, 1289,    0, 1289,    0, 1213, 1289,    0,    0,
 1289,    0, 1289, 1289, 1289, 1289,    0,    0,    0,    0,
  144, 1289,    0,    0, 1289, 1289,    0, 1289, 1289, 1289,
  144,    0, 1289,    0, 1289, 1289,    0,    0,  144, 1289,
    0, 1289, 1289, 1289, 1289,    0, 1289,    0,    0,    0,
 1289,    0,    0, 1213,    0, 1289,    0, 1289,    0,    0,
    0,    0, 1289,    0, 1289, 1289, 1289, 1289,    0, 1289,
    0, 1289,    0,    0,    0,    0, 1289,    0,    0,    0,
    0, 1289, 1289, 1289, 1289, 1289, 1289,    0, 1289, 1289,
 1289,    0, 1289, 1289,    0,    0,    0, 1289,    0, 1289,
 1289, 1289, 1289, 1289, 1289, 1289, 1289, 1289, 1289, 1289,
    0, 1289, 1289, 1289,    0, 1289, 1289, 1207, 1289, 1289,
 1207,    0, 1207,    0,    0, 1213,    0, 1213,    0,    0,
    0,    0,    0,    0,    0, 1219,    0, 1219, 1219,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0, 1219, 1219,    0, 1219, 1219, 1219,    0,
    0,    0,    0, 1219, 1219, 1219, 1219,    0, 1219,    0,
  144, 1219, 1219,    0,  144,  144,    0,    0,    0, 1219,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0, 1219,    0,    0, 1219,
 1219,    0,  144,    0, 1219,    0,    0,    0,    0, 1219,
    0,    0,    0,  144,  144,    0,    0,    0, 1219,    0,
    0,    0,    0, 1219,    0,    0,    0, 1201, 1201,    0,
 1201,    0, 1201,    0,    0,    0,    0,    0, 1219,    0,
    0,    0,    0, 1219,    0, 1219,    0,    0,    0,    0,
 1219,    0, 1219, 1219, 1219,    0, 1219, 1219, 1219,    0,
 1219, 1219, 1219, 1219,    0, 1219, 1219, 1219, 1219, 1219,
 1219, 1219, 1219, 1219, 1219,    0,    0,    0,    0,    0,
 1219,    0, 1219,    0, 1213,    0, 1213,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0, 1219, 1219,
    0,    0, 1219, 1219,    0,    0,    0, 1219,    0, 1219,
    0,    0,    0,    0, 1219,    0, 1219,    0, 1219,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, 1207,    0, 1207,
 1207, 1219, 1213, 1219, 1213, 1213, 1219,    0, 1219,    0,
    0, 1219,    0, 1219, 1219,    0,    0,    0,    0, 1207,
 1207, 1226,    0, 1226, 1213, 1213, 1219,    0,    0,    0,
    0,    0,    0,    0, 1207,    0,    0, 1219,    0, 1213,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, 1219,    0,    0, 1219,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, 1219, 1219,    0,    0,    0, 1219,    0,    0,    0,
    0,    0,    0,    0,    0, 1219,    0,    0,    0,    0,
    0,    0,    0,    0, 1219,    0,    0, 1219,    0,    0,
    0, 1219,    0,    0,    0,    0, 1219, 1201,    0, 1201,
 1201, 1219, 1219, 1219,    0,    0,    0,    0, 1219, 1219,
 1219,    0, 1219,    0,    0, 1201, 1201,    0, 1201, 1201,
 1201,    0, 1219, 1219,    0,    0, 1201, 1201, 1201,    0,
 1201,    0,    0, 1201, 1201, 1219,    0,    0, 1219, 1219,
    0, 1201,    0,    0,    0,    0,    0,    0,    0,    0,
 1207, 1213,    0, 1213, 1213, 1213,    0,    0, 1201, 1207,
    0, 1201, 1201,    0, 1213,    0, 1201,    0,    0,    0,
    0, 1201,    0, 1213, 1213,    0,    0,    0,    0,    0,
 1201,    0,    0,    0,    0, 1201,    0,    0, 1213, 1198,
 1198,    0, 1198, 1207, 1198,    0,    0,    0, 1213,    0,
 1201,    0,    0,    0,    0, 1201, 1207, 1201,    0,    0,
    0, 1213, 1201,    0, 1201, 1201, 1201,    0, 1201, 1201,
 1201,    0, 1201, 1201, 1201, 1201,    0, 1201, 1201, 1201,
 1201, 1201, 1201, 1201, 1201, 1201, 1201,    0,    0, 1226,
 1226,    0, 1201, 1207, 1201,    0,    0,    0, 1213,    0,
 1226,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 1201, 1201,    0,    0, 1201, 1201,    0,    0,    0, 1201,
 1129, 1201,    0,    0,    0,    0, 1201,    0, 1201,    0,
 1201,    0,    0, 1108,    0, 1108, 1226,    0,    0,    0,
    0,    0,    0, 1207,    0,    0,    0,    0, 1213,    0,
 1226,    0,    0, 1201, 1226, 1201,    0,    0, 1201,    0,
 1201,    0,    0, 1201, 1213, 1201, 1201,    0,    0,    0,
    0,    0,    0, 1213, 1226,    0,    0,    0, 1201,    0,
    0,    0,    0,    0, 1226,    0,    0,    0,    0, 1201,
 1207,    0,    0,    0,    0, 1213, 1129,    0,    0,    0,
    0,    0,    0, 1201,    0,    0, 1201, 1213,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 1213,    0,    0, 1201, 1201,    0,  144, 1226, 1201,    0,
    0,    0,    0,    0,    0,    0,    0, 1201,    0, 1226,
    0,    0,    0,    0, 1226,    0, 1201,    0,    0, 1201,
    0,    0,    0, 1201,    0,    0,    0, 1213, 1201, 1198,
    0, 1198, 1198, 1201, 1201, 1201,    0,    0,    0, 1226,
 1201, 1201, 1201,    0, 1201,  144, 1226, 1198, 1198, 1128,
 1198, 1198, 1198,    0, 1201, 1201,    0,    0, 1198, 1198,
 1198,    0, 1198,    0,    0, 1198, 1198, 1201,  144,  144,
 1201, 1201,    0, 1198,    0,    0,    0, 1213,    0,    0,
    0, 1758,    0,    0,    0,    0,    0,    0,    0,    0,
 1198,    0,    0, 1198, 1198,    0,    0,  144, 1198,    0,
    0,    0,    0, 1198, 1759, 1760,    0,    0, 1226,    0,
    0,    0, 1198,    0,    0,    0,    0, 1198,    0, 1226,
 1108, 1226, 1108, 1108, 1213, 1128,    0,    0,    0,    0,
    0,    0, 1198, 1761,    0,    0,    0, 1198,    0, 1198,
    0,    0, 1108, 1108, 1198,    0, 1198, 1198, 1198, 1226,
 1198, 1198, 1198,    0, 1198, 1198, 1198, 1198,  144, 1198,
 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1198, 1286,
 1286, 1286, 1286, 1286, 1198, 1286, 1198,    0,  144,    0,
    0,    0,  144,    0,    0,    0, 1286,    0,  144,  144,
    0,    0, 1198, 1198, 1762, 1226, 1198, 1198,    0,    0,
    0, 1198, 1226, 1198,    0,  144,    0,    0, 1198,    0,
 1198,    0, 1198,    0, 1763,    0,    0,    0, 1764,    0,
    0,    0,    0,    0, 1765, 1766,    0,    0,    0,    0,
    0,    0,    0,    0,  144, 1198,    0, 1198,    0,    0,
 1198, 1767, 1198,    0,    0, 1198,    0, 1198, 1198,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 1198,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 1768, 1198,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0, 1198,    0,    0, 1198,  144,
    0,    0, 1108,  144,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0, 1198, 1198,    0,  144,    0,
 1198,    0,    0,    0,    0,    0,    0,    0,    0, 1198,
    0,  144,    0,  144,    0, 1769, 1108,    0, 1198, 1770,
    0, 1198,    0,  144,    0, 1198,  144,    0,    0, 1108,
 1198,    0,    0,  144, 1771, 1198, 1198, 1198,    0,    0,
    0,    0, 1198, 1198, 1198,    0, 1198, 1772,    0, 1773,
    0,    0,    0,    0,    0,    0, 1198, 1198,    0, 1774,
    0,    0, 1775,    0,    0,    0, 1108,    0,    0, 1198,
    0,    0, 1198, 1198, 1286,    0,    0,    0, 1286,    0,
 1286, 1286,    0,    0,    0,    0,    0, 1286, 1286, 1286,
 1286,    0, 1286,    0, 1286, 1286, 1286, 1286,    0, 1286,
 1286, 1286,    0,    0,    0, 1286, 1286, 1286, 1286, 1286,
    0, 1286,    0,    0, 1286, 1286, 1108, 1286, 1286, 1286,
 1286, 1286, 1286,    0,    0,    0,    0,    0, 1286,    0,
 1286, 1286, 1286, 1286, 1286, 1286,    0,    0, 1286, 1286,
    0,    0, 1286, 1286,    0,    0,    0, 1286,    0,    0,
 1286,    0, 1286, 1286,    0, 1286, 1286, 1286, 1286,    0,
    0, 1286,    0, 1108,    0, 1286, 1286, 1286, 1286, 1286,
    0, 1286,    0,    0,    0,    0,    0,    0,    0,    0,
    0, 1286, 1286, 1286,    0,    0, 1286,    0, 1286,    0,
    0, 1286,    0, 1286, 1286, 1286, 1286, 1286, 1286, 1286,
 1286, 1286, 1286, 1286, 1286, 1286, 1286,    0, 1286, 1286,
 1286, 1286, 1286, 1286, 1286, 1286, 1286, 1286,    0,    0,
    0, 1286,    0, 1286, 1286, 1286, 1286, 1286,    0,    0,
    0,    0,    0,    0,    0, 1286,    0, 1286, 1286, 1286,
 1286, 1286, 1286, 1286, 1286, 1286, 1286, 1286,    0, 1286,
 1286,    0, 1286, 1286,    0, 1286,    0, 1286,    0, 1286,
 1286, 1286,    0, 1286, 1286, 1286,    0, 1286, 1286,    0,
    0, 1286,    0,    0,    0,    0,    0, 1286, 1286,    0,
 1286, 1286, 1286, 1286, 1286,    0, 1286,    0,    0, 1286,
    0, 1286,    0, 1286, 1286, 1286, 1286, 1286,    0,    0,
 1286, 1286,    0, 1286,    0,    0,    0, 1286,    0, 1286,
    0,    0,    0,    0, 1286, 1286,    0, 1286,    0,    0,
 1286,    0,    0, 1286,    0, 1286, 1286, 1286, 1286, 1248,
 1248, 1248, 1248, 1248, 1286, 1248,    0, 1286, 1286,    0,
 1286, 1286, 1286,    0,    0, 1286, 1248, 1286, 1286,    0,
    0,    0, 1286,    0, 1286, 1286, 1286, 1286,    0, 1286,
    0,    0,    0, 1286,    0,    0,    0,    0, 1286,    0,
 1286,    0,    0,    0,    0, 1286,    0, 1286, 1286, 1286,
 1286,    0, 1286,    0, 1286,    0,    0,    0,    0, 1286,
    0,    0,    0,    0, 1286, 1286, 1286, 1286, 1286, 1286,
    0, 1286, 1286, 1286,    0, 1286, 1286,    0,  596,    0,
 1286,    0, 1286, 1286, 1286, 1286, 1286, 1286,    0, 1286,
 1286, 1286, 1286,    0, 1286, 1286, 1286,    0, 1286, 1286,
    0, 1286, 1286,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  596,    0,  596,  596,  596,    0,  596,
  596,  596,    0,  596,  596,  596,  596,    0,  596,  596,
  596,  596,  596,  596,  596,  596,  596,  596,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0, 1248,    0,
 1248, 1248,    0,    0,    0,    0,    0, 1248, 1248, 1248,
 1248,    0, 1248,    0, 1248, 1248, 1248, 1248,    0, 1248,
 1248, 1248,    0,    0,    0, 1248, 1248, 1248, 1248, 1248,
    0, 1248,    0,    0, 1248, 1248,    0, 1248, 1248, 1248,
 1248, 1248, 1248,    0,    0,    0,  596,    0, 1248,    0,
 1248,    0, 1248, 1248, 1248, 1248,    0,    0, 1248, 1248,
    0,    0, 1248, 1248,    0,    0,    0, 1248,    0,    0,
    0,    0, 1248,    0,    0,    0,    0, 1248, 1248,    0,
    0, 1248,    0,    0,    0, 1248, 1248,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, 1248, 1248,    0,    0,    0, 1248,    0, 1248,    0,
    0,    0,    0, 1248,    0, 1248, 1248, 1248, 1248, 1248,
 1248, 1248, 1248, 1248, 1248, 1248, 1248,    0, 1248, 1248,
 1248, 1248, 1248, 1248, 1248, 1248, 1248, 1248,    0,    0,
    0, 1248,    0, 1248, 1248, 1248,    0, 1248, 1110, 1110,
 1110,    0, 1110,    0, 1110,    0,    0,    0,    0, 1248,
 1248, 1248, 1248, 1248, 1248, 1248, 1248, 1248,    0, 1248,
 1248,    0, 1248,    0,    0, 1248,    0, 1248,  596, 1248,
    0, 1248,  596, 1248, 1248,    0,    0, 1248,    0,    0,
    0, 1248,    0,    0,    0,    0,    0, 1248, 1248,    0,
 1248,    0, 1248, 1248, 1248,    0, 1248,    0,    0, 1248,
    0, 1248,    0, 1248, 1248, 1248, 1248, 1248,    0,    0,
 1248, 1248,    0, 1248,    0,    0,    0, 1248,    0, 1248,
    0,    0,    0,    0,    0, 1248,    0,    0,    0,    0,
 1248,    0,    0, 1248,    0, 1248, 1248, 1248,    0,    0,
    0,    0,    0,    0, 1248,    0,    0, 1248,    0,    0,
 1248,    0, 1248,    0,    0,    0,    0, 1248, 1248,    0,
    0,    0, 1248,    0, 1248, 1248, 1248, 1248,    0, 1248,
    0,    0,    0,    0,    0,    0,    0,    0, 1248,    0,
 1248,    0,    0,    0,    0,    0,    0, 1248, 1248, 1248,
 1248,    0, 1248,    0, 1248,    0,    0,    0,    0, 1248,
    0,    0,    0,    0, 1248, 1248, 1248, 1248, 1248,    0,
    0, 1248, 1248, 1248,    0, 1248, 1248,    0,    0,    0,
 1248,    0, 1248, 1248,    0, 1248, 1248, 1248,    0, 1248,
 1248, 1248, 1248,    0, 1248, 1248, 1248,    0, 1248, 1248,
    0, 1248, 1248,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, 1110,    0, 1110,
    0, 1110,    0, 1110,    0, 1110, 1110,    0, 1110,    0,
    0,    0,    0,    0,    0, 1110, 1110, 1110, 1110,    0,
 1110,    0,    0, 1110,    0,    0, 1110, 1110, 1110,    0,
    0, 1110,    0,    0,    0,    0,    0, 1110,    0, 1110,
    0,    0, 1110, 1110, 1110,    0,    0,    0, 1110,    0,
    0, 1110, 1110,    0,    0,    0, 1110,    0,    0,    0,
    0, 1110,    0,    0,    0,    0, 1110,    0,    0,    0,
 1110,    0,    0,    0,    0, 1110,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 1110,    0,    0,    0,    0, 1110,    0, 1110,    0,    0,
    0,    0, 1110,    0, 1110, 1110, 1110,    0, 1110, 1110,
 1110, 1110, 1110, 1110, 1110, 1110,    0, 1110, 1110, 1110,
 1110, 1110, 1110, 1110, 1110, 1110, 1110,    0,    0,    0,
 1110,    0, 1110, 1110, 1110, 1111, 1111, 1111,    0, 1111,
    0, 1111,    0,    0,    0,    0,    0,    0,    0, 1110,
    0, 1110,    0,    0, 1110, 1110,    0,    0, 1110,    0,
    0, 1110,    0,    0,    0,    0, 1110,    0, 1110,    0,
 1110,    0,    0,    0,    0,    0, 1110,    0,    0,    0,
 1110,    0,    0,    0,    0,    0, 1110,    0,    0,    0,
    0, 1110, 1110,    0,    0, 1110,    0,    0, 1110,    0,
 1110,    0, 1110, 1110, 1110, 1110,    0,    0,    0, 1110,
    0,    0,    0,    0,    0,    0, 1110,    0, 1110,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0, 1110,
    0,    0,    0,    0,    0, 1110, 1110,    0,    0,    0,
    0,    0,    0,    0,    0,    0, 1110,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, 1110,    0, 1110, 1110,    0, 1110,    0, 1110,    0,
    0,    0,    0,    0,    0,  519,    0, 1110,    0, 1110,
    0,    0,    0,    0,    0,    0, 1110, 1110, 1110, 1110,
    0,    0,    0,    0,    0,    0,    0,    0, 1110,    0,
    0,    0,    0, 1110, 1110, 1110,    0,    0,    0,    0,
 1110, 1110, 1110,    0, 1110,    0,  496,    0,    0, 1110,
    0,  519, 1110,    0, 1110, 1110,    0,    0, 1110,    0,
 1110,    0,    0,    0,    0,  519,    0, 1110, 1110,  519,
 1110, 1110,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  519,
    0,    0,  496,  496, 1111,    0, 1111,    0, 1111,  519,
 1111,    0, 1111, 1111,    0, 1111,    0,    0,    0,    0,
  496,    0, 1111, 1111, 1111, 1111,    0, 1111,    0,    0,
 1111,    0,    0, 1111, 1111, 1111,    0,    0, 1111,    0,
  496,    0,    0,    0, 1111,    0, 1111,    0,    0, 1111,
 1111, 1111,  519,    0,    0, 1111,    0,    0, 1111, 1111,
    0,    0,    0, 1111,    0,    0,    0,    0, 1111,  519,
    0,    0,    0, 1111,    0,    0,    0, 1111,    0,    0,
    0,    0, 1111,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  496,  519,    0,    0, 1111,    0,    0,
    0,  519, 1111,    0, 1111,    0,    0,    0,    0, 1111,
  496, 1111, 1111, 1111,    0, 1111, 1111, 1111, 1111, 1111,
 1111, 1111, 1111,    0, 1111, 1111, 1111, 1111, 1111, 1111,
 1111, 1111, 1111, 1111, 1112,  496, 1112, 1111, 1112, 1111,
 1111, 1111,  496,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0, 1111,    0, 1111,    0,
    0, 1111, 1111,  519,    0, 1111,    0,    0, 1111,    0,
    0,    0,    0, 1111,  519, 1111,  519, 1111,    0,    0,
    0,    0,    0, 1111,    0,    0,    0, 1111,    0,    0,
    0,    0,    0, 1111,    0,    0,    0,    0, 1111, 1111,
    0,    0, 1111,    0,  496, 1111,    0, 1111,    0, 1111,
 1111, 1111, 1111,    0,    0,  496, 1111,  496,    0,    0,
    0,    0,    0, 1111,    0, 1111,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0, 1111,    0,    0,    0,
    0,    0, 1111, 1111,    0,    0,    0,    0,    0,    0,
  519,    0,    0, 1111,    0,    0,    0,  519,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0, 1111,    0,
 1111, 1111,    0, 1111,  500, 1111,    0,    0,    0,    0,
    0,    0,    0,    0, 1111,    0, 1111,    0,    0,    0,
    0,  496,    0, 1111, 1111, 1111, 1111,    0,  496,    0,
    0,    0,    0,    0,    0, 1111,    0,    0,    0,    0,
 1111, 1111, 1111,    0,    0,  519,    0, 1111, 1111, 1111,
    0, 1111,    0,    0,    0,    0, 1111,    0,    0, 1111,
    0, 1111, 1111,    0,    0, 1111,    0, 1111,    0,    0,
    0,    0,    0,    0, 1111, 1111,    0, 1111, 1111,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  519,    0, 1112,    0, 1112,    0, 1112,    0, 1112,
    0, 1112, 1112,    0, 1112,  519,    0,    0,    0,  519,
    0, 1112, 1112, 1112, 1112,    0, 1112,    0,    0, 1112,
    0,    0, 1112, 1112, 1112,    0,    0, 1112,    0,  519,
    0,    0,    0, 1112,    0, 1112,    0,    0, 1112, 1112,
 1112,    0,    0,    0, 1112,    0,    0, 1112, 1112,    0,
    0,    0, 1112,    0,    0,    0,    0, 1112,    0,    0,
    0,    0, 1112,    0,    0,    0, 1112,    0,    0,    0,
    0, 1112,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  519,    0,    0,    0, 1112,    0,    0,    0,
    0, 1112,    0, 1112,    0,    0,    0,   87, 1112,  519,
 1112, 1112, 1112,    0, 1112, 1112, 1112, 1112, 1112, 1112,
 1112, 1112,    0, 1112, 1112, 1112, 1112, 1112, 1112, 1112,
 1112, 1112, 1112, 1113,  519, 1113, 1112, 1113, 1112, 1112,
 1112,  519,    0,    0,    0,    0,    0,  826, 1531,    0,
    0,  827,  828,    0,    0, 1112,    0, 1112,    0,    0,
 1112, 1112,    0,    0, 1112,    0,    0, 1112,    0,    0,
    0,    0, 1112, 1532, 1112,    0, 1112,    0,    0,    0,
    0,    0, 1112,    0,    0,    0, 1112,    0,    0,    0,
    0,    0, 1112,    0,    0,    0,    0, 1112, 1112,    0,
    0, 1112,    0,  519, 1112,    0, 1112,    0, 1112, 1112,
 1112, 1112,    0,    0,  519, 1112,  519,    0,    0,    0,
    0,    0, 1112,    0, 1112,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0, 1112,    0,    0,  829,    0,
    0, 1112, 1112,    0,    0,    0,    0,    0,    0,    0,
    0,    0, 1112,    0,    0, 1533,    0,  830,    0,    0,
    0,    0,    0,    0,    0,    0,  831, 1112,    0, 1112,
 1112,    0, 1112,  533, 1112,    0,    0,    0,    0,    0,
    0,    0,    0, 1112,  832, 1112,    0,    0,    0, 1000,
  519, 1000, 1112, 1112, 1112, 1112,    0,  519,    0,  833,
  834,    0,    0,    0, 1112,    0,    0,    0,    0, 1112,
 1112, 1112,    0,    0,  498,    0, 1112, 1112, 1112,  533,
 1112,    0,    0,    0,    0, 1112,    0,    0, 1112,    0,
 1112, 1112,    0,    0, 1112,    0, 1112,  533,    0,    0,
    0,    0,    0, 1112, 1112,    0, 1112, 1112,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  533,    0,    0,
  498,  500, 1113,    0, 1113,    0, 1113,  533, 1113,  835,
 1113, 1113,    0, 1113,  836,    0,    0,    0,  498,    0,
 1113, 1113, 1113, 1113,    0, 1113,    0,  837, 1113,    0,
    0, 1113, 1113, 1113,    0,  776, 1113,    0,  498,    0,
    0,    0, 1113,    0, 1113,    0,    0, 1113, 1113, 1113,
  533,    0,    0, 1113,    0,    0, 1113, 1113,    0,    0,
    0, 1113,    0,    0,    0,    0, 1113,  533,    0,    0,
  838, 1113,    0,    0,    0, 1113,    0,    0,  839,    0,
 1113,    0,    0,    0,    0,    0,  256,    0,    0,    0,
    0,  498,  533,    0,    0, 1113,    0,    0,    0,  533,
 1113, 1284, 1113,    0,    0,    0,    0, 1113,  498, 1113,
 1113, 1113,    0, 1113, 1113, 1113, 1113, 1113, 1113, 1113,
 1113,    0, 1113, 1113, 1113, 1113, 1113, 1113, 1113, 1113,
 1113, 1113,    0,  498,    0, 1113,    0, 1113, 1113, 1113,
  498,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0, 1113,    0, 1113, 1000, 1000, 1113,
 1113,  533,    0, 1113,    0,    0, 1113,    0, 1000,    0,
    0, 1113,  533, 1113,  533, 1113,    0,    0,    0,    0,
    0, 1113,    0,    0,    0, 1113,    0,    0,    0,    0,
    0, 1113,    0,    0,    0,    0, 1113, 1113,    0,    0,
 1113,    0,  498, 1113, 1000, 1113,    0, 1113, 1113, 1113,
 1113,    0,    0,  498, 1113,  498,    0,    0, 1000,    0,
    0, 1113, 1000, 1113,    0,    0,    0,    0,  142,    0,
    0,  142,    0,    0, 1113,  142,    0,    0,    0,    0,
 1113, 1113, 1000,    0,  142,    0,    0,    0,  533,    0,
    0, 1113, 1000,    0,    0,  533,    0,  518,    0,  518,
    0,    0,    0,    0,  142,    0, 1113,    0, 1113, 1113,
    0, 1113,    0, 1113,    0,    0,    0,  142,    0,    0,
    0,  142, 1113,    0, 1113,    0,    0,    0,    0,  498,
    0, 1113, 1113, 1113, 1113, 1000,  498,    0,    0,    0,
    0,    0,   62, 1113,   63,    0,    0, 1000, 1113, 1113,
 1113,    0, 1000,    0,    0, 1113, 1113, 1113,    0, 1113,
    0,    0,    0,    0, 1113,    0,    0, 1113,    0, 1113,
 1113, 1284,    0, 1113,    0, 1113,    0, 1000, 1284, 1284,
    0, 1284, 1113, 1113, 1000, 1113, 1113,    0, 1284, 1284,
 1284, 1284,    0, 1284,    0,    0, 1284,    0,    0,    0,
    0,    0,    0,    0, 1284,    0, 1116,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, 1284,    0,    0, 1284, 1284,  142,    0,    0, 1284,
    0,    0,    0,    0, 1284,    0,    0,    0,    0,    0,
    0,    0,    0, 1284,    0,    0, 1000,    0, 1284,  142,
    0,    0,    0,    0,    0,    0,    0, 1000,    0, 1000,
    0,    0,    0, 1284,    0,    0,    0,    0, 1284,    0,
 1284,  142, 1284,    0,    0, 1284,    0, 1284, 1284, 1284,
    0, 1284, 1284, 1284,    0, 1284, 1284, 1284, 1284,    0,
 1284, 1284, 1284, 1284, 1284, 1284, 1284, 1284, 1284, 1284,
    0,    0,    0,    0,    0, 1284,  142, 1284,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0, 1284,  515,  515, 1284, 1284,    0,
    0,    0,  142, 1000, 1284,    0,  518,    0,  142, 1284,
 1000, 1284,    0, 1284,    0,    0,    0,  142,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   57,
    0,   58,   59,    0,    0,    0,    0,    0, 1284,    0,
  142, 1284,  515, 1284,    0,    0, 1284,    0, 1284,    0,
    0,   60,   61,    0,  142,    0,  515,    0,    0,    0,
  515, 1284,    0,    0,    0,    0,   64,    0,    0,    0,
    0,    0, 1284,    0,    0,   62,    0,   63,    0,   62,
  515,   63,    0,    0,    0,    0,    0,    0,    0, 1284,
  515,    0,    0,    0,    0,    0,  142,    0,    0,    0,
    0,    0,    0,    0,    0,    0, 1284, 1284,    0,    0,
    0, 1284,    0, 1116, 1116,    0, 1116,    0,    0,    0,
 1284,  469,    0, 1116, 1116, 1116, 1116,    0, 1116, 1284,
    0, 1116, 1284,  515,    0,    0,    0,    0,    0, 1116,
    0, 1284,    0,    0,    0,    0, 1284, 1284, 1284,    0,
  515,    0,    0, 1284, 1284, 1284, 1116, 1284,    0, 1116,
 1116,    0,    0,    0, 1116,    0,    0, 1284, 1284, 1116,
 1284,    0,    0,    0,    0,  515,    0,    0, 1116,    0,
 1284,    0,  515, 1116, 1284,    0,    0, 1117,    0,    0,
    0,    0,   65,    0,    0,    0,    0,    0, 1116,    0,
    0,   66,    0, 1116,    0, 1116,    0,    0,    0,    0,
 1116,    0, 1116, 1116, 1116,    0, 1116, 1116, 1116,    0,
 1116, 1116, 1116, 1116,  470, 1116, 1116, 1116, 1116, 1116,
 1116, 1116, 1116, 1116, 1116,   67,    0,    0,    0,    0,
 1116,    0, 1116, 1230,  515, 1230,    0,    0,   68,    0,
    0,    0,    0,    0,    0,  515,    0,  515,    0, 1116,
    0,    0, 1116, 1116,    0,    0,    0,    0,    0, 1116,
    0,    0,    0,    0, 1116,    0, 1116,    0, 1116,    0,
    0,    0,    0,    0,    0,   69,    0,    0, 1161,    0,
    0,    0,   57,    0,   58,   59,   57,    0,   58,   59,
    0,    0,    0, 1116,    0,    0, 1116,    0, 1116,    0,
    0, 1116,    0, 1116,   60,   61,    0,    0,   60,   61,
  219,    0,    0,    0,    0,    0, 1116,    0,    0,   64,
    0,  515,    0,   64,    0,   70,    0, 1116,  515,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0, 1116,    0,    0,    0,  219,    0,
    0,    0,    0,    0,    0,    0,  219,  219,    0,    0,
    0, 1116, 1116,    0,    0,    0, 1116,    0,    0,    0,
    0,    0,   71,    0,  219, 1116,    0,    0,  432,   62,
    0,   63,    0,    0, 1116,    0,    0, 1116,    0,    0,
    0,    0,    0,    0,  219,    0, 1116,    0,    0,    0,
    0, 1116, 1116, 1116,    0,    0,    0,    0, 1116, 1116,
 1116,    0, 1116,    0, 1117, 1117,    0, 1117,    0,    0,
    0,    0, 1116, 1116, 1117, 1117, 1117, 1117,    0, 1117,
    0,    0, 1117,    0,    0, 1116,    0,    0,    0, 1116,
 1117,    0, 1189,    0,    0,   65, 1230,  219,    0,   65,
 1230,    0, 1230, 1230,   66,    0,  219, 1117,   66,    0,
 1117, 1117,    0,    0,  219, 1117,    0,    0,    0,    0,
 1117,    0, 1230, 1230,    0,    0,    0,    0,    0, 1117,
    0,    0,    0,    0, 1117,    0,    0, 1230,   67,  219,
    0,    0,   67,    0,    0,    0,  219,    0, 1072, 1117,
 1072,   68,    0,    0, 1117,   68, 1117,    0,    0,    0,
    0, 1117,    0, 1117, 1117, 1117,    0, 1117, 1117, 1117,
    0, 1117, 1117, 1117, 1117,    0, 1117, 1117, 1117, 1117,
 1117, 1117, 1117, 1117, 1117, 1117,    0,    0,   69,    0,
    0, 1117,   69, 1117,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  219,    0,
 1117,    0,  490, 1117, 1117,    0,    0,    0,    0,  219,
 1117,  219,    0,    0,    0, 1117,    0, 1117,    0, 1117,
    0,    0,    0, 1162,    0,    0,    0,    0,   70,    0,
    0,    0,   70,    0,    0,    0,   57,    0,   58,  481,
    0,    0,    0,    0, 1117,    0,    0, 1117,  490, 1117,
    0,    0, 1117, 1230, 1117,    0,    0,    0,  482,   61,
    0,    0, 1230,    0,    0,    0,  490, 1117,  219,    0,
    0,    0,    0,   64,    0,   71,    0,    0, 1117,   71,
    0,    0,   62,    0,   63,  219,  490,    0,    0,  219,
    0,    0,  219,    0,    0, 1117, 1230,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0, 1230,
    0,    0, 1117, 1117,    0,    0,    0, 1117,    0, 1189,
 1189,    0, 1189,    0,    0,    0, 1117,    0,    0, 1189,
 1189, 1189, 1189,    0, 1189, 1117,    0, 1189, 1117,  490,
    0,    0,    0,    0,    0, 1189, 1230, 1117,    0,    0,
    0,    0, 1117, 1117, 1117, 1072,  490, 1072, 1072, 1117,
 1117, 1117, 1189, 1117,    0, 1189, 1189,    0,    0,    0,
 1189,    0,    0, 1117, 1117, 1189,    0, 1072, 1072,    0,
    0,  490,    0,    0, 1189,    0, 1117,    0,  490, 1189,
 1117, 1230, 1072, 1190,    0,    0, 1230,    0,    0,   65,
    0,    0,    0,    0, 1189,    0,    0,    0,   66, 1189,
    0, 1189,    0,    0,    0,    0, 1189,    0, 1189, 1189,
 1189, 1758, 1189, 1189, 1189,    0, 1189, 1189, 1189, 1189,
    0, 1189, 1189, 1189, 1189, 1189, 1189, 1189, 1189, 1189,
 1189,    0,   67, 1230, 1759, 1760, 1189,    0, 1189,    0,
  490,    0,    0,    0,    0,   68,    0,    0,    0,    0,
    0,  490,    0,  490,    0, 1189,    0,    0, 1189, 1189,
    0,    0,    0, 1761,    0, 1189,    0,    0,    0,    0,
 1189,    0, 1189,    0, 1189,    0,    0,    0,    0,    0,
    0,    0,   69,    0,    0,  514,    0,    0,    0,   57,
    0,   58,   59,    0,    0,    0,    0,    0,    0, 1189,
    0,    0, 1189,    0, 1189,    0,    0, 1189, 1072, 1189,
    0,   60,   61,    0,    0,    0,    0, 1072,    0,    0,
    0,    0, 1189,    0, 1762,    0,   64,  490,    0,    0,
 1072,    0,   70, 1189,  490,   62,    0,   63,    0,    0,
    0,    0,    0,    0, 1763,    0,    0, 1072, 1764,    0,
 1189, 1072,    0,    0, 1765, 1766,    0,    0,    0,    0,
    0,    0,    0,    0, 1072,    0,    0, 1189, 1189,    0,
    0, 1767, 1189,    0,    0,    0,    0,  256,    0,   71,
    0, 1189,    0,    0,   62,    0,   63,    0,    0,    0,
 1189,    0,    0, 1189,    0,    0,    0,    0,    0,    0,
 1768, 1072, 1189,    0,    0,    0,    0, 1189, 1189, 1189,
    0,    0,    0,    0, 1189, 1189, 1189,    0, 1189,    0,
 1190, 1190,    0, 1190,    0,    0,    0,    0, 1189, 1189,
 1190, 1190,    0, 1190,    0, 1190,    0,    0, 1190,    0,
    0, 1189,    0,    0,    0, 1189, 1190,    0, 1188,    0,
    0, 1072,   65,    0,    0, 1769,    0,    0,    0, 1770,
    0,   66,    0, 1190,    0,    0, 1190, 1190,    0,    0,
    0, 1190,    0,    0, 1771,    0, 1190,    0,    0,    0,
    0,    0,    0,    0,    0, 1190,    0, 1772,    0, 1773,
 1190,    0,    0,    0,    0,   67,    0,    0, 1072, 1774,
    0,    0, 1775,    0,    0, 1190,    0,    0,   68, 1855,
 1190,    0, 1190,    0,    0,    0,    0, 1190,    0, 1190,
 1190, 1190,    0, 1190, 1190, 1190,    0, 1190, 1190, 1190,
 1190,    0, 1190, 1190, 1190, 1190, 1190, 1190, 1190, 1190,
 1190, 1190,    0,    0,    0,   69,    0, 1190,    0, 1190,
    0,    0,   57,    0,   58,   59,    0,    0,    0,    0,
    0,    0,    0,  583,    0,    0, 1190,    0,  508, 1190,
 1190,    0,    0,    0,   60,   61, 1190,    0,    0,    0,
    0, 1190,    0, 1190,    0, 1190,    0,    0,    0,   64,
    0,    0,    0,    0,    0,   70,    0,    0,    0,    0,
    0,   57,    0,   58,   59,    0,    0,    0,    0,    0,
 1190,    0,    0, 1190,  508, 1190,    0,    0, 1190,    0,
 1190,    0,    0,   60,   61,    0,    0,    0,    0,    0,
    0,    0,  508, 1190,    0,    0,    0,    0,   64,    0,
    0,    0,   71,    0, 1190,    0,    0,    0,   62,    0,
   63,    0,  508,    0,    0,    0,    0,    0,    0,    0,
    0, 1190,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0, 1190, 1190,
    0,    0,    0, 1190,    0, 1188, 1188,    0, 1188,    0,
    0,    0, 1190,  518,    0,    0,    0, 1188, 1188,    0,
 1188, 1190,    0, 1188, 1190,  508,    0,    0,    0,    0,
    0, 1188,    0, 1190,    0,   65,    0,    0, 1190, 1190,
 1190,    0,  508,    0,   66, 1190, 1190, 1190, 1188, 1190,
    0, 1188, 1188,    0,    0,    0, 1188,    0,    0, 1190,
 1190, 1188,    0,    0,    0,    0,    0,  508,    0,    0,
 1188,    0, 1190,    0,  508, 1188, 1190,    0,   67,    0,
 1213,    0, 1213,    0,   65,    0,    0,    0,    0,    0,
 1188,   68,    0,   66,    0, 1188,    0, 1188,    0,    0,
    0,    0, 1188,    0, 1188, 1188, 1188,    0, 1188, 1188,
 1188,    0, 1188, 1188, 1188, 1188,    0, 1188, 1188, 1188,
 1188, 1188, 1188, 1188, 1188, 1188, 1188,   67,   69,    0,
    0,    0, 1188,    0, 1188,    0,  508,    0,    0,    0,
   68,    0,    0,    0,    0,    0,    0,  508,    0,  508,
    0, 1188,    0,    0, 1188, 1188,    0,    0,    0,    0,
    0, 1188,    0,    0,    0,    0, 1188,    0, 1188,    0,
 1188,    0,    0,    0,    0,    0,    0,   69,   70,    0,
    0,    0,    0,    0,    0,   57,    0,   58,   59,  533,
    0,    0,    0,    0,    0, 1188,    0,    0, 1188,    0,
 1188,    0,    0, 1188,    0, 1188,    0,   60,   61,    0,
    0,    0,    0,    0,    0,    0,    0,    0, 1188,    0,
    0,    0,   64,  508,    0,   71,    0,   70,    0, 1188,
  508,    0,    0,    0,    0,  533,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0, 1188,    0,    0,    0,
    0,    0,    0,  533,    0,    0,    0,    0,    0,    0,
    0,    0,    0, 1188, 1188,    0,    0,    0, 1188,    0,
    0,    0,    0,  533,   71,    0,    0, 1188,    0,    0,
    0,    0,    0,    0,    0,    0, 1188,    0,    0, 1188,
    0,    0,    0,    0,    0,    0,    0, 1213, 1188, 1213,
 1213,    0,    0, 1188, 1188, 1188,    0,    0,    0,  858,
 1188, 1188, 1188,  858, 1188,  858,  858,    0,  858, 1213,
 1213,    0,    0,    0, 1188, 1188,  533,  858,  858,    0,
  858,    0,    0,    0, 1213,    0,    0, 1188,    0,    0,
    0, 1188,    0,  533,    0,    0,  710,  858,   65,  858,
    0,    0,  858,  858,  858,    0,    0,   66,  858,    0,
    0,  858,  858,    0,    0,    0,  858,    0,  533,    0,
    0,  858,    0,    0,    0,  533,  858,    0,    0,    0,
  858,    0,    0,    0,    0,  858,    0,    0,    0,    0,
    0,   67,    0,    0,    0,    0,    0,    0,    0,    0,
  858,    0,    0,    0,   68,  858, 1303,  858, 1303,    0,
    0,    0,  858,    0,  858,  858,  858,    0,  858,  858,
  858,  858,  858,  858,  858,  858,    0,  858,  858,  858,
  858,  858,  858,  858,  858,  858,  858,  533,    0,    0,
  858,   69,  858,    0,  858,    0,    0,    0,  533,    0,
  533,    0,    0,    0,    0,   62,    0,   63,    0,  858,
 1213,  858,    0,    0,  858,  858,    0,    0,  858, 1213,
    0,  858,    0,    0,    0,    0,  858,    0,  858,    0,
  858,    0,   62,    0,   63,    0,  858,    0,    0,    0,
  858,   70,    0,    0,    0,    0,  858,    0,    0,    0,
    0,  858,  858, 1213,    0,  858,    0,    0,  858,    0,
  858,    0,    0,    0,  858,  858, 1213,    0,    0,    0,
    0,    0,    0,    0,  533,    0,    0,    0,  858,    0,
    0,  533,    0,    0,    0,    0,    0,    0,   71,  858,
    0,    0,    0,    0,    0,  858,    0,    0,    0,    0,
    0,    0,    0, 1213,    0,    0,  858,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  858,    0,  858,  858,    0,  858,    0,  858,    0,
    0,    0,    0,    0,    0,    0,    0,  858,    0,  858,
    0,    0,    0,    0,    0,    0,  858,  858,    0,  858,
    0,    0,    0, 1213,    0,    0,    0,   62,  858,   63,
    0,    0,    0,  858,  858,  858,    0,    0,    0,    0,
  858,  858,  858, 1303,    0, 1303, 1303,    0,    0,  858,
    0,    0,  858,    0,  858,  858,    0, 1303,  858, 1274,
  858, 1303, 1303,    0, 1303, 1303, 1303,  858,  858,    0,
 1213,  858,    0, 1303, 1303,    0, 1303,    0,    0,    0,
 1303,    0, 1274, 1274,    0,    0,    0,    0,    0,    0,
    0,    0,   57,    0,   58,   59,    0,    0,    0,    0,
    0,    0,    0,  845, 1303,    0,    0, 1303, 1303,    0,
    0, 1274, 1303,    0,   60,   61,    0, 1303,    0,   57,
    0,   58,   59,    0,    0,    0, 1303,    0,    0,   64,
    0, 1303,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   60,   61,    0,    0,    0, 1303,    0,    0, 1303,
    0, 1303,    0, 1303,    0,    0,   64,    0, 1303,    0,
 1303, 1303, 1303,    0, 1303, 1303, 1303,    0, 1303, 1303,
 1303, 1303, 1274, 1303, 1303, 1303, 1303, 1303, 1303, 1303,
 1303, 1303, 1303, 1304,    0, 1304,    0,    0, 1303,    0,
 1303,    0, 1274,    0,    0,    0, 1274,    0,    0,    0,
    0,    0, 1274, 1274,    0,    0, 1303, 1303, 1303,    0,
 1303, 1303,    0,    0,    0, 1303,    0, 1303,    0, 1274,
    0,    0, 1303,    0, 1303,    0, 1303,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   57, 1303,   58,   59, 1274, 1303,
  513, 1303,    0,    0, 1303,   65, 1303,    0,    0,    0,
    0, 1303, 1303,    0,   66,    0,   60,   61,    0,    0,
    0,    0,    0,    0, 1303,    0,    0,    0,    0, 1303,
    0,   64,   65,    0,    0, 1303,    0,    0,    0,    0,
    0,   66,    0,    0,    0,    0,  513,    0,   67, 1303,
    0,    0, 1303, 1274,    0,    0,    0, 1274,    0,    0,
    0,   68,    0,    0,  513,    0,    0,    0,    0, 1303,
 1303,    0, 1274,    0, 1303,   67,    0,    0,    0,    0,
    0,    0,    0, 1303,  513, 1274,    0, 1274,   68,    0,
    0,    0, 1303,    0,    0, 1303,    0, 1274,   69, 1303,
 1274,    0,    0,    0, 1303,    0,    0, 1274,    0, 1303,
 1303, 1303,    0,    0,    0,    0, 1303, 1303, 1303, 1303,
    0,    0,    0,    0,    0,   69,    0,    0,    0,    0,
 1303, 1303, 1303,    0,    0,    0,    0,  513,    0,    0,
    0,    0, 1303, 1303, 1303,    0, 1303, 1303,   70,    0,
 1304,    0, 1304, 1304,  513,  965,    0,   65,    0,    0,
    0,    0,    0,    0, 1304,    0,   66,    0, 1304, 1304,
    0, 1304, 1304, 1304,    0,   70,    0,    0,    0,  513,
 1304, 1304,    0, 1304,    0,    0,  513, 1304,    0,    0,
    0,    0,    0,    0,    0,   71,    0,    0,    0,    0,
   67,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, 1304,    0,   68, 1304, 1304,    0,    0,    0, 1304,
  256,    0,   71,    0, 1304,    0,    0,    0,    0,    0,
    0,    0,    0, 1304,    0,    0,    0,    0, 1304,    0,
    0,    0,    0, 1213,    0, 1213,    0,    0,  513,    0,
   69,    0,    0, 1304,    0,    0, 1304,    0, 1304,  513,
 1304,  513,    0,    0,    0, 1304,    0, 1304, 1304, 1304,
    0, 1304, 1304, 1304,    0, 1304, 1304, 1304, 1304,    0,
 1304, 1304, 1304, 1304, 1304, 1304, 1304, 1304, 1304, 1304,
    0,    0,   62,    0,   63, 1304,    0, 1304,    0,    0,
   70,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0, 1304, 1304, 1304,    0, 1304, 1304,    0,
    0,    0, 1304,    0, 1304,    0,    0,    0,    0, 1304,
    0, 1304,    0, 1304,    0,  513,    0,    0,  137,    0,
    0,  137,  513,    0,    0,  137,    0,   71,    0,    0,
    0,    0, 1304,    0,  137,    0, 1304,    0, 1304,    0,
    0, 1304,    0, 1304,    0,    0,    0,    0, 1304, 1304,
    0,    0,    0,    0,  137,    0,    0,    0,    0,    0,
    0, 1304,    0,    0,    0,    0, 1304,  137,    0,    0,
    0,  137, 1304,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0, 1304,    0,    0, 1304,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0, 1304, 1304,    0,    0,
    0, 1304,    0,    0,    0,    0,    0,    0,    0,    0,
 1304,    0,    0,    0,    0,   62,    0,   63,    0, 1304,
    0,    0, 1304,    0,    0, 1232, 1304,    0,    0,    0,
 1213, 1304, 1213, 1213,    0,    0, 1304, 1304, 1304,    0,
    0,    0,    0, 1304, 1304, 1304, 1304,    0, 1121, 1121,
    0, 1121, 1213, 1213,    0,    0,    0, 1304, 1304, 1304,
 1121, 1121,    0, 1121,    0,    0,  137, 1213,    0, 1304,
 1304, 1304,    0, 1304, 1304,    0,    0,    0,    0,   57,
    0,   58,   59,    0,    0,    0,    0,    0,    0,  137,
 1213, 1121,    0,    0, 1121, 1121,    0,    0,    0, 1121,
    0,   60,   61,    0, 1121,    0,    0,    0,    0,    0,
    0,  137,    0, 1121,    0,    0,   64, 1213, 1121,    0,
    0,    0,    0,    0,    0, 1303,    0, 1303,    0,    0,
    0,    0,    0, 1121,    0,    0,    0,    0, 1121,    0,
 1121,    0,    0,    0,    0, 1121,  137, 1121, 1121, 1121,
    0, 1121, 1121, 1121,    0, 1121, 1121, 1121, 1121,    0,
 1121, 1121, 1121, 1121, 1121, 1121, 1121, 1121, 1121, 1121,
    0,    0,  137,    0,    0, 1121, 1121, 1121,  137,    0,
    0,    0,    0,    0,    0,    0,    0,  137,    0,    0,
    0,    0,    0, 1213, 1121, 1121,    0, 1121, 1121,    0,
    0,   62, 1213,   63, 1121,    0,    0,    0,    0, 1121,
  137, 1121,    0, 1121,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  137,    0,    0,    0,    0,    0,
    0,   87,   57,    0,   58,   59, 1213,    0, 1121,    0,
    0, 1121,   65, 1121,    0,    0,    0,    0, 1121, 1213,
    0,   66,    0,    0,   60,   61,    0,    0,    0, 1121,
    0, 1121,    0,    0,    0,    0,  137, 1121,    0,   64,
    0,  826, 1121,    0,    0,  827,  828,    0,    0,    0,
    0,    0,    0,    0,    0,   67, 1213,    0,    0, 1121,
    0,    0,  961,    0, 1213,    0,    0,    0,   68,    0,
    0,    0,    0,    0,    0,    0, 1121, 1121, 1121,    0,
    0, 1121,    0,    0,    0,    0,    0,   62, 1262,   63,
 1121,    0,    0,    0,    0,   62,    0,   63,    0, 1121,
    0,    0, 1121,    0,    0,   69, 1213,    0,    0,    0,
    0, 1121, 1303,    0, 1303, 1303, 1121, 1121, 1121,    0,
    0,    0,    0, 1121, 1121, 1121, 1303,    0,    0,    0,
 1303, 1303,  829, 1303, 1303, 1303,    0, 1121, 1121,    0,
    0,    0, 1303, 1303,    0, 1303,    0, 1213,    0, 1303,
 1121,  830,    0, 1213, 1121,   70,    0,    0,    0,    0,
  831,    0,    0,    0,    0,   65,    0,    0,    0,    0,
    0,    0,    0, 1303,   66,    0, 1303, 1303,  832,    0,
    0, 1303,    0,    0,    0,    0, 1303,    0,   57,    0,
   58,   59,    0,  833,  834, 1303,    0,    0,    0,    0,
 1303,    0,   71,    0,    0,    0,    0,    0,   67,    0,
   60,   61,    0,    0,    0, 1303,    0,    0,    0,    0,
 1303,   68, 1303,    0,    0,   64,    0, 1303,    0, 1303,
 1303, 1303,    0, 1303, 1303, 1303,    0, 1303, 1303, 1303,
 1303,    0, 1303, 1303, 1303, 1303, 1303, 1303, 1303, 1303,
 1303, 1303, 1304,    0, 1304,    0,    0, 1303,   69, 1303,
    0,    0,    0,  835,    0,    0,    0,    0,  836,    0,
    0,    0,    0,    0,    0, 1303, 1303,    0,    0, 1303,
 1303,  837,    0,    0, 1303,    0, 1303,    0,    0,  776,
    0, 1303,    0, 1303,    0, 1303,    0,    0,    0,    0,
    0,    0,    0,    0,   57,    0,   58,   59,   70,    0,
    0,    0,   57,    0,   58,   59,    0,    0, 1303,    0,
 1303,    0,    0, 1303,  838, 1303,   60,   61,    0,    0,
 1303, 1303,  839,    0,   60,   61,    0,    0,    0,    0,
  256,   64,    0, 1303, 1957,    0,    0,    0,    0,   64,
    0,   65,    0,    0, 1303,   71,    0,    0,    0,    0,
   66,    0,    0,    0,    0,    0,    0,    0, 1303,    0,
    0, 1303,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0, 1303, 1303,
    0,    0,    0, 1303,   67,    0,    0,    0,    0,    0,
    0,    0, 1303,    0,    0,    0,    0,   68,    0,    0,
    0, 1303,    0,    0, 1303,    0,    0,    0, 1303,    0,
    0,    0,    0, 1303,    0,    0,    0,    0, 1303, 1303,
 1303,    0,    0,    0,    0, 1303, 1303, 1303, 1303,    0,
 1287,    0,    0,    0,   69,    0,    0,    0,    0, 1303,
 1303, 1303, 1217,    0, 1217,    0,    0,    0,    0,    0,
    0, 1303, 1303, 1303,    0, 1303, 1303,   65, 1977, 1304,
    0, 1304, 1304,    0,    0,   65,   66,    0,    0,    0,
    0,    0,    0, 1304,   66,    0,    0, 1304, 1304,    0,
 1304, 1304, 1304,    0,   70,    0,    0,    0,    0, 1304,
 1304,    0, 1304,   62,    0,   63, 1304,    0,    0,  127,
   67,    0,    0,    0,    0,    0,  127,    0,   67,    0,
    0,    0,    0,   68,    0,  127,    0,    0,    0,    0,
 1304,   68,    0, 1304, 1304,    0,    0,    0, 1304,    0,
    0,   71,    0, 1304, 1931,  127,    0,    0,    0,    0,
    0,    0, 1304,    0,    0,    0,    0, 1304,  127,    0,
   69,    0,  127,    0,    0,    0,    0,    0,   69,    0,
    0,    0, 1304,    0,    0,    0,    0, 1304,    0, 1304,
    0,    0,    0,    0, 1304,    0, 1304, 1304, 1304,    0,
 1304, 1304, 1304,    0, 1304, 1304, 1304, 1304,    0, 1304,
 1304, 1304, 1304, 1304, 1304, 1304, 1304, 1304, 1304, 1162,
   70, 1162,    0,    0, 1304,    0, 1304,    0,   70,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, 1304, 1304,    0,    0, 1304, 1304,    0,    0,
    0, 1304,    0, 1304,    0,    0,    0,    0, 1304,    0,
 1304,    0, 1304,    0,    0,    0,    0,   71,    0,    0,
    0,    0,    0,    0,    0,   71,    0,  127,    0, 1217,
    0, 1217, 1217,    0,    0, 1304,    0, 1304,    0,    0,
 1304,    0, 1304,    0,    0,    0,    0, 1304, 1304,    0,
  127, 1217, 1217,    0,    0,    0,    0,    0,    0,    0,
 1304,    0,    0,    0,    0,    0, 1217,    0,    0,    0,
    0, 1304,  127,    0,    0,    0,    0,    0,  494,    0,
   57,    0,   58,   59,    0, 1304,    0,    0, 1304,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   60,   61,    0, 1304, 1304,  127,    0,    0,
 1304,    0,    0,    0,    0,    0,  494,   64,    0, 1304,
    0,    0,    0,    0,  494,  494,    0,    0, 1304,    0,
    0, 1304,    0,  127,    0, 1304,    0,    0,    0,  127,
 1304,    0,  494,    0,    0, 1304, 1304, 1304,  127,    0,
    0,    0, 1304, 1304, 1304, 1304,    0, 1270,    0,    0,
    0,    0,  494,    0,    0,    0, 1304, 1304, 1304,    0,
    0,  127,    0,    0,    0,    0,    0,    0, 1304, 1304,
 1304,    0, 1304, 1304,    0,  127, 1162,    0, 1162, 1162,
    0,    0, 1217,    0,    0,    0,    0,    0,    0,    0,
    0, 1217,    0,    0, 1162, 1162,    0, 1162, 1162, 1162,
    0,    0,    0,    0,    0,  494, 1162, 1162,    0, 1162,
    0,    0,    0, 1162, 1232,    0,    0,  127,    0,    0,
    0,    0,  494,    0,    0, 1217,    0,    0,    0,    0,
    0,    0,    0,   65,    0,    0,    0, 1162, 1217,    0,
 1162, 1162,   66,    0,    0, 1162,    0,  494,    0,    0,
 1162,    0,    0,    0,  494,    0,  494,    0, 1217, 1162,
    0,    0,    0,    0, 1162,    0,    0,    0,    0, 1098,
    0, 1098,    0,    0,    0, 1217,   67,    0,    0, 1162,
    0,    0,    0,    0, 1162,    0, 1162,    0,    0,   68,
    0, 1162,    0, 1162, 1162, 1162,    0, 1162, 1162, 1162,
    0, 1162, 1162, 1162, 1162,    0, 1162, 1162, 1162, 1162,
 1162, 1162, 1162, 1162, 1162, 1162,  494,    0,    0,    0,
    0, 1162,    0, 1162,    0, 1217,   69,  494,    0,  494,
    0,    0,    0,    0,    0,    0,    0,    0,    0, 1162,
 1162,    0,    0, 1162, 1162,    0,    0,    0, 1162,    0,
 1162,    0,    0,    0,    0, 1162,    0, 1162,    0, 1162,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, 1217,    0,    0,    0,   70,    0,    0,    0,
    0,    0, 1162,    0, 1162,    0,  494, 1162,    0, 1162,
    0,    0,    0,    0, 1162, 1162,    0,    0,  282,    0,
    0,    0,    0,  494,    0,    0,    0, 1162,    0,    0,
  494,    0,    0,    0,    0,    0,    0,    0, 1162,    0,
    0,  282,  282,   71,    0,    0,    0,    0,    0,    0,
    0,    0, 1162,    0,    0, 1162,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  282,    0, 1162, 1162,    0,    0,    0, 1162,    0,    0,
    0,    0,    0,    0,    0,    0, 1162,    0,    0,    0,
    0,    0,    0,    0,    0, 1162,    0,    0, 1162,    0,
    0,    0, 1162,    0,    0,    0, 1098, 1162, 1098, 1098,
    0,    0, 1162, 1162, 1162,    0,    0,    0,    0, 1162,
 1162, 1162, 1162,    0, 1098, 1098,    0, 1098, 1098, 1098,
    0,  282,    0, 1162, 1162, 1162, 1098, 1098,    0, 1098,
    0,    0,    0, 1098,    0, 1162, 1162, 1162,    0, 1162,
 1162,  282,    0,    0,    0,  282,    0,    0,    0,    0,
    0,  282,  282,    0,    0,    0,    0, 1098,    0,    0,
 1098, 1098,    0,    0,    0, 1098,    0,    0, 1098,    0,
 1098,    0,    0,    0,    0,    0,    0,    0,    0, 1098,
    0,    0,    0,    0, 1098,    0,    0,    0,    0,    0,
    0,  958,    0,  958,    0,    0,    0,  282,    0, 1098,
    0,    0,    0,    0, 1098,    0, 1098,    0,    0,    0,
    0, 1098,    0, 1098, 1098, 1098,    0, 1098, 1098, 1098,
    0, 1098, 1098, 1098, 1098,    0, 1098, 1098, 1098, 1098,
 1098, 1098, 1098, 1098, 1098, 1098,    0,    0,    0,    0,
  144, 1098,  144, 1098,    0,    0,    0,    0,    0,    0,
    0,    0,  282, 1098,    0,    0,  282,    0,    0,    0,
 1098,    0,    0, 1098, 1098,    0,    0,    0, 1098,    0,
 1098,  282,    0,    0,    0, 1098,    0, 1098,    0, 1098,
    0,    0,    0,    0,  282,    0,  282,    0,    0, 1098,
    0,    0,    0,    0,    0,    0,  282,    0,    0,  282,
    0,    0, 1098,    0, 1098,    0,  282, 1098,    0, 1098,
    0,    0,    0,    0, 1098, 1098,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, 1098,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0, 1098,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, 1098,    0,    0, 1098,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, 1098, 1098,    0,    0,    0, 1098,    0,    0,
    0,    0,    0,    0,    0,    0, 1098,    0,    0,    0,
    0,   62,    0,   63,    0, 1098,    0,    0, 1098,    0,
    0,    0, 1098,    0,    0,    0,    0, 1098,  958,    0,
  958,  958, 1098, 1098, 1098,    0,    0,    0,    0, 1098,
 1098, 1098,    0,    0,  313,    0,  964,  964, 1098,  964,
  958,  958,    0, 1098, 1098,    0,    0,    0,  964,  964,
    0,  964,    0,    0,    0,  958, 1098,  313,  313, 1098,
 1098,    0,    0,    0,    0,    0,    0,  144,    0,  144,
  144,    0,    0,    0,    0,    0,    0,    0,    0,  964,
  958,  958,  964,  964,    0,    0,  313,  964,    0,  144,
  144,    0,  964,    0,    0,    0,    0,    0,    0,    0,
    0,  964,    0,    0,  144,    0,  964,    0,    0,    0,
    0,  973,    0,  973,    0,    0,    0,    0,    0,    0,
    0,  964,    0,    0,    0,    0,  964,    0,  964,    0,
    0,    0,    0,  964,    0,  964,  964,  964,    0,  964,
  964,  964,    0,  964,  964,  964,  964,  313,  964,  964,
  964,  964,  964,  964,  964,  964,  964,  964,    0,    0,
 1211,    0, 1211,  964,    0,  964,    0,  313,    0,    0,
    0,  313,    0,    0,    0,    0,    0,  313,  313,    0,
    0,  958,  964,    0,    0,  964,  964,    0,    0,    0,
  958,    0,  964,    0,  313,    0,    0,  964,    0,  964,
    0,  964,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   57,    0,
   58,   59,    0,  313,  958,    0,  964,    0,    0,  964,
  144,  964,    0,    0,    0,    0,  964,  958,    0,  144,
   60,   61,    0,    0,    0,    0,    0,    0,    0,  964,
    0,    0,    0,    0,  313,  438,    0,    0,    0,    0,
  964,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  144,  958,    0,    0,  964,  313,    0,
    0,    0,  313,    0,    0,    0,  144,    0,    0,    0,
    0,    0,    0,    0,  964,  964,    0,  313,    0,  964,
    0,    0,    0,    0,    0,    0,    0,  144,  964,    0,
  313, 1213,  313, 1213,    0,    0,    0,  964,    0,    0,
  964,    0,  313,  144,  958,  313,    0,    0,  973,  964,
  973,  973,  313,    0,  964,  964,  964,    0,    0,    0,
    0,  964,  964,  964,    0,    0,  978,  978,    0,  978,
  973,  973,    0,    0,    0,  964,  964,    0,  978,  978,
    0,  978,    0,    0,    0,  973,    0,    0,  964,    0,
    0,  958,  964,  144,    0,    0,    0, 1211,    0, 1211,
 1211,   65,    0,    0,    0,    0,    0,    0,    0,  978,
   66,    0,  978,  978,    0,    0,    0,  978,    0, 1211,
 1211,    0,  978,    0,    0,    0,    0,    0,    0,    0,
    0,  978,    0,    0, 1211,    0,  978,    0,    0,    0,
  144, 1213,    0, 1213,   67,    0,    0,    0,    0,    0,
    0,  978,    0,    0,    0,    0,  978,   68,  978,    0,
    0,    0,    0,  978,    0,  978,  978,  978,    0,  978,
  978,  978,    0,  978,  978,  978,  978,    0,  978,  978,
  978,  978,  978,  978,  978,  978,  978,  978,    0,    0,
  965,    0,  965,  978,   69,  978,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  973,  978,    0,    0,  978,  978,    0,    0,    0,
  973,    0,  978,    0,    0,    0,    0,  978,    0,  978,
    0,  978,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   70,    0,    0,    0, 1213,    0,
 1213, 1213,    0,    0,  973,    0,  978,    0,    0,  978,
 1211,  978,    0,    0,    0,    0,  978,  973,    0, 1211,
 1213, 1213,    0,    0,    0,    0,    0,    0,    0,  978,
    0,    0,    0,    0,    0, 1213,    0,    0,    0,    0,
  978,   71,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0, 1211,  973,    0,    0,  978,    0,    0,
    0,    0,    0,    0,    0,    0, 1211,    0,    0,    0,
    0,    0,    0,    0,  978,  978,    0,    0,    0,  978,
    0,    0,    0,    0,    0,    0,    0,    0,  978,    0,
    0, 1230,    0, 1230,    0,    0,    0,  978,    0,    0,
  978,    0,    0, 1211,  973,    0,    0,    0, 1213,  978,
 1213, 1213,    0,    0,  978,  978,  978,    0,    0,    0,
    0,  978,  978,  978,    0,    0,  761,  761,    0,  761,
 1213, 1213,    0,    0,    0,  978,  978,    0,  761,  761,
    0,  761,    0,    0,    0, 1213,    0,    0,  978,    0,
    0,  973,  978, 1211,    0,    0,    0,  965,    0,  965,
  965, 1213,    0,    0,    0,    0,    0,    0,    0,  761,
 1213,    0,  761,  761,    0,    0,    0,  761,    0,  965,
  965,    0,  761,    0,    0,    0,    0,    0,    0,    0,
    0,  761,    0,    0,  965,    0,  761,    0,    0,    0,
 1211, 1213,    0, 1213, 1213,    0,    0,    0,    0,    0,
    0,  761,    0,    0,    0,    0,  761, 1213,  761,    0,
    0,    0,    0,  761,    0,  761,  761,  761,    0,  761,
  761,  761,    0,  761,  761,  761,  761,    0,  761,  761,
  761,  761,  761,  761,  761,  761,  761,  761,    0,    0,
    0,    0,    0,  761, 1213,  761,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, 1213,  761,    0,    0,  761,  761,    0,    0,    0,
 1213,    0,  761,    0,    0,    0,    0,  761,    0,  761,
    0,  761,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0, 1213,    0,    0,    0, 1230,    0,
 1230, 1230,    0,    0, 1213,    0,  761,    0,    0,  761,
  965,  761,    0,    0,    0,    0,  761, 1213,    0,  965,
 1230, 1230,    0,    0,    0,    0,    0,    0,    0,  761,
    0,    0,    0,    0,    0, 1230,    0,    0,    0,    0,
  761, 1213,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  965, 1213,    0,    0,  761,    0,    0,
    0,    0,    0,    0,    0,    0,  965,    0,    0,    0,
    0,    0,    0,    0,  761,  761,    0,    0,    0,  761,
    0,    0,    0, 1213,    0, 1213,    0,    0,  761,    0,
    0,    0,    0,    0,    0,    0,    0,  761,    0,    0,
  761,    0,    0,  965, 1213,    0,    0,    0, 1213,  761,
 1213, 1213,    0,    0,  761,  761,  761,    0,    0,    0,
    0,  761,  761,  761,    0,    0,  755,  755,    0,  755,
 1213, 1213,    0,    0,    0,  761,  761,    0,  755,  755,
    0,  755,    0,    0,    0, 1213,    0,    0,  761,    0,
    0, 1213,  761,  965,    0, 1213,    0, 1213,    0,    0,
    0, 1230,    0,    0,    0,    0,    0,    0,    0,  755,
 1230,    0,  755,  755,    0,    0,    0,  755,    0,    0,
    0,    0,  755,    0,    0,    0,    0,    0,    0,    0,
    0,  755,    0,    0,    0,    0,  755,    0,    0,    0,
  965,  460,  460,  460, 1230,    0,    0,    0,    0,    0,
    0,  755,    0,    0,    0,    0,  755, 1230,  755,    0,
    0,    0,    0,  755,    0,  755,  755,  755,    0,  755,
  755,  755,    0,  755,  755,  755,  755,    0,  755,  755,
  755,  755,  755,  755,  755,  755,  755,  755,    0,    0,
    0,    0,    0,  755, 1230,  755, 1234,    0, 1234,    0,
  311,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, 1213,  755,    0,    0,  755,  755,    0,    0,    0,
 1213,    0,  755,  311,  311,    0,    0,  755,    0,  755,
    0,  755,    0,    0,    0,    0,    0,    0,    0,    0,
 1213,    0, 1213, 1213, 1230,    0,    0,    0,    0,    0,
    0,    0,  311,    0, 1213,    0,  755,    0,    0,  755,
    0,  755, 1213, 1213,    0,    0,  755, 1213,    0,    0,
    0,    0,    0,    0,    0,    0,    0, 1213,    0,  755,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  755, 1230,    0,    0,    0,    0,  304,    0,    0,    0,
    0,    0,    0,    0, 1213,    0,    0,  755,    0,    0,
    0,    0, 1213,  311, 1213, 1213,    0,    0,    0,  304,
  304,    0,    0,    0,  755,  755, 1211,    0, 1211,  755,
    0,    0,    0,  311, 1213, 1213,    0,  311,  755,    0,
    0,    0,    0,  311,  311,    0,    0,  755,  304, 1213,
  755,    0,    0,    0, 1213,    0,    0,    0,    0,  755,
  311,    0,    0,    0,  755,  755,  755,  460,  314,    0,
  460,  755,  755,  755,    0,    0,    0,    0,    0,    0,
  460,  460,    0,    0,    0,  755,  755,    0,    0,  311,
    0,  314,  314,    0,    0,  460,    0,    0,  755,    0,
    0, 1213,  755, 1213,    0,    0,    0,    0,    0,  304,
    0,    0, 1213, 1234,  460, 1234, 1234,    0,    0,    0,
  314,    0,    0,    0,    0,    0,    0,    0,    0,  304,
    0,    0,    0,  304,    0, 1234, 1234,    0,    0,  304,
  304,    0,    0,    0,  311,    0, 1213,    0,  311,    0,
 1234,    0,    0,    0,    0,    0,  304,    0,    0, 1213,
    0,    0,    0,  311,    0,    0,  460,    0,    0,    0,
    0,    0,    0,    0,    0, 1213,  311,    0,  311,    0,
    0,  314,    0,    0, 1213,  304,    0,    0,  311,    0,
    0,  311,    0,    0,    0,    0, 1213,    0,  311,    0,
    0,  314,    0,    0,    0,  314,    0,  460,    0,    0,
    0,  314,  314,    0,    0,    0,  304,    0, 1213,    0,
    0,    0,    0,    0,  460,    0,    0,    0,  314,    0,
  460, 1213,    0,    0,    0,    0,    0,    0,    0,  322,
  304,    0,    0,    0,  304,    0, 1213,  460,    0,    0,
    0,  460,  455,    0,    0,  455,    0,  314,    0,  304,
    0,    0,  322,  322,  460, 1211, 1211,    0, 1213,    0,
    0,    0,  304,    0,  304,    0, 1234,  460,    0,    0,
 1211,    0,  304,  460,  304, 1234,    0,  304,  314,    0,
    0,  322,    0, 1213,  304,    0,    0,    0,    0,  455,
    0,    0,    0,  460,    0,  460,    0,    0,    0,    0,
    0,    0,  314,    0,  460,    0,  314,    0, 1213, 1234,
  460,    0,    0,    0,    0,    0,    0,  460,    0,    0,
    0,  314, 1234,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  314,    0,  314,    0,    0,    0,
    0,  455,  322,    0,    0,    0,  314,    0,  460,  314,
    0,    0,    0,    0,  460, 1213,  314,    0,    0, 1234,
    0,    0,  322,    0,    0,    0,  322,    0,  460,    0,
    0,    0,  322,  322,    0,    0,    0,    0,    0,    0,
  460,    0,  455,    0,    0,    0,    0,    0,    0,  322,
    0,    0,  460,    0,    0,  460,  460,    0,    0,  455,
    0,  460,  460,    0,    0, 1211,    0,    0,    0, 1234,
    0,    0,    0,    0,    0,    0,    0,    0,  322,    0,
    0,    0,  455,    0,    0,    0,  455,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0, 1211,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, 1211,    0,    0,    0, 1234,    0,  455,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  322,    0,    0,    0,  322,  455,    0,
  455,  866,    0,    0,    0, 1213,    0, 1213, 1213, 1211,
    0,    0,  322,    0,    0,  455,    0,    0,    0,    0,
    0,    0,  455,  866,  866,  322,  866,  322,    0,    0,
    0,    0,    0,    0,    0,  866,  866,  322,  866,    0,
  322,    0,    0,    0,    0,    0,    0,  322,    0,    0,
    0,    0,    0,  455,    0,    0,    0,    0,    0, 1211,
    0,    0,    0,    0,    0,    0,  866,    0,    0,  866,
  866,    0,    0,  455,  866,    0,    0,    0,    0,  866,
    0,    0,    0,    0,    0,  455,    0,    0,  866,    0,
    0,    0,    0,  866,    0,    0,    0,  455,    0,    0,
  455,  455,    0,    0,    0,    0, 1211,  455,  866,    0,
    0,    0,    0,  866,    0,  866,    0,    0,    0,    0,
  866,    0,  866,  866,  866,    0,  866,  866,  866,    0,
  866,  866,  866,  866,    0,  866,  866,  866,  866,  866,
  866,  866,  866,  866,  866,    0,    0,    0,    0,    0,
  866,    0,  866,  866,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  866,
    0,    0,  866,  866,    0,    0,    0,    0,    0,  866,
    0,    0,    0,    0,  866,    0,  866,  866,  866,    0,
    0,    0,  866,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  866,    0,    0,  866,    0,  866,    0,
    0,    0,    0,  866,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  866,    0,    0,    0,
    0,  866,    0,    0,    0,    0,    0,  866,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  866,    0,  867,    0,    0,    0,
 1213,    0, 1213, 1213,    0,    0,    0,    0,    0,    0,
    0,  866,  866,    0,    0,    0,  866,    0,  867,  867,
    0,  867,    0,    0,    0,  866,    0,    0,    0,    0,
  867,  867,    0,  867,  866,    0,    0,  866,    0,    0,
    0,    0,    0,    0,    0,    0,  866,    0,    0,    0,
    0,  866,  866,  866,    0,    0,    0,    0,  866,  866,
  866,  867,    0,    0,  867,  867,    0,    0,    0,  867,
    0,    0,  866,  866,  867,    0,    0,    0,    0,    0,
    0,    0,    0,  867,    0,  866,    0,    0,  867,  866,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  867,    0,    0,    0,    0,  867,    0,
  867,    0,    0,    0,    0,  867,    0,  867,  867,  867,
    0,  867,  867,  867,    0,  867,  867,  867,  867,    0,
  867,  867,  867,  867,  867,  867,  867,  867,  867,  867,
    0,    0,    0,    0,    0,  867,    0,  867,  867,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  867,    0,    0,  867,  867,    0,
    0,    0,    0,  448,  867,    0,  448,    0,    0,  867,
    0,  867,  867,  867,    0,    0,    0,  867,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  554,    0,    0,    0,    0,    0,    0,  554,  867,    0,
    0,  867,    0,  867,    0,    0,    0,    0,  867,    0,
  448,    0,  554,  554,    0,  554,    0,    0,    0,    0,
    0,  867,    0,    0,    0,  554,  867,  554,    0,    0,
    0,    0,  867,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  867,
    0,    0,    0,    0,    0,  554,    0,    0,  554,  554,
    0,    0,  448,  554,    0,    0,  867,  867,  554,    0,
    0,  867,    0,    0,    0,    0,    0,  554,    0,    0,
  867,    0,  554,    0,    0,    0,    0,    0,    0,  867,
    0,    0,  867,    0,    0,    0,    0,  554,    0,    0,
    0,  867,  554,  448,  554,    0,  867,  867,  867,    0,
  554,    0,    0,  867,  867,  867,    0,    0,    0,    0,
  448,    0,    0,    0,    0,    0,    0,  867,  867,    0,
    0,  446,    0,    0,    0,    0,    0,    0,    0,  554,
  867,  554,    0,  448,  867,    0,    0,  448,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  554,    0,
    0,  554,  554,    0,    0,    0,    0,    0,  554,    0,
    0,    0,    0,  554,    0,  554,    0,  554,    0,  448,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  448,
    0,  448,  554,    0,    0,  554,    0,  554,    0,    0,
    0,    0,    0,    0,    0,    0,  448,    0,    0,    0,
    0,    0,    0,  448,    0,  554,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  554,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  554,  448,    0,    0,    0,    0, 1033,
    0, 1033, 1033,    0,    0,    0,    0,    0,    0,    0,
  554,  554,    0,    0,  448,  554,    0, 1033, 1033,    0,
 1033,    0,    0,    0,  554,    0,  448,    0,    0, 1033,
 1033,    0, 1033,  554,    0,    0,  554,    0,  448,    0,
    0,  448,  448,    0,    0,  554,    0,    0,  448,    0,
  554,  554,  554,    0,    0,    0,    0,  554,  554,  554,
 1033,    0,    0, 1033, 1033,    0,    0,    0, 1033,    0,
    0,  554,  554, 1033,    0,    0,    0,    0,    0,    0,
    0,    0, 1033,    0,    0,    0,    0, 1033,  559,    0,
    0,    0, 1033,    0,    0,    0,    0,    0,    0,    0,
    0,    0, 1033,    0,    0,    0,    0, 1033,    0, 1033,
    0,    0,    0,    0, 1033,    0, 1033, 1033, 1033,    0,
 1033, 1033, 1033,    0, 1033, 1033, 1033, 1033,    0, 1033,
 1033, 1033, 1033, 1033, 1033, 1033, 1033, 1033, 1033,    0,
    0,    0,    0,    0, 1033,    0, 1033,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0, 1033,    0,    0, 1033, 1033,    0,    0,
    0,    0,    0, 1033,    0,    0,    0,    0, 1033,    0,
 1033,    0, 1033,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, 1033,    0,    0,    0,    0,    0, 1033,    0,    0,
 1033,    0, 1033,    0,    0,    0,    0, 1033,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0, 1033,    0,
 1033,    0,    0,    0,    0,    0, 1033,    0,    0,    0,
    0, 1033,    0,    0,    0,    0, 1033,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0, 1033,    0,
    0,    0,    0,    0, 1035,    0, 1035, 1035,    0,    0,
    0,    0,    0,    0,    0, 1033, 1033,    0,    0,    0,
 1033,    0, 1035, 1035,    0, 1035,    0,    0,    0, 1033,
    0,    0,    0,    0, 1035, 1035,    0, 1035, 1033,    0,
    0, 1033,    0,    0,    0,    0,    0,    0,    0,    0,
 1033,    0,    0,    0,    0, 1033, 1033, 1033,    0,    0,
 1033,    0, 1033, 1033, 1033, 1035,    0,    0, 1035, 1035,
    0,    0,    0, 1035,    0,    0, 1033, 1033, 1035,    0,
    0,    0,    0,    0,    0,    0,    0, 1035,    0, 1033,
 1033,    0, 1035, 1033,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, 1035,    0,    0,
    0,    0, 1035,    0, 1035,    0,    0,    0,    0, 1035,
    0, 1035, 1035, 1035,    0, 1035, 1035, 1035,    0, 1035,
 1035, 1035, 1035,    0, 1035, 1035, 1035, 1035, 1035, 1035,
 1035, 1035, 1035, 1035,    0,    0,    0,    0,    0, 1035,
    0, 1035,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0, 1035,    0,
    0, 1035, 1035,    0,    0,    0,    0,    0, 1035,    0,
    0,    0,    0, 1035,    0, 1035,    0, 1035,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0, 1035,    0,    0,    0,
    0,    0, 1035,    0,    0, 1035,    0, 1035,    0,    0,
    0,    0, 1035,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0, 1035,    0, 1035,    0,    0,    0,    0,
    0, 1035,    0,    0,    0,    0, 1035,    0,    0,    0,
    0, 1035,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0, 1035,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  889,    0,  889,  889,    0,    0,
 1035, 1035,    0,    0,    0, 1035,    0,    0,    0,    0,
 1232,    0,  889,  889, 1035,  889,    0,    0,    0,    0,
    0,    0,    0, 1035,  889,  889, 1035,  889,    0,    0,
    0,    0,    0,    0,    0, 1035,    0,    0,    0,    0,
 1035, 1035, 1035,    0,    0, 1035,    0, 1035, 1035, 1035,
    0,    0,    0,    0,    0,  889,    0,    0,  889,  889,
    0, 1035, 1035,  889,    0,    0,    0,    0,  889,    0,
    0,    0,    0,    0, 1035, 1035,    0,  889, 1035,    0,
    0,    0,  889,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  889,    0,    0,
    0,    0,  889,    0,  889,    0,    0,    0,    0,  889,
    0,  889,  889,  889,    0,  889,  889,  889,    0,  889,
  889,  889,  889,    0,  889,  889,  889,  889,  889,  889,
  889,  889,  889,  889,    0,    0,    0,    0,    0,  889,
    0,  889,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  889,    0,
    0,  889,  889,    0,    0,    0,    0,    0,  889, 1232,
    0,    0,    0,  889,    0,  889,    0,  889,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  889, 1232,    0,    0,
    0,    0,  889,    0,    0,  889,    0,  889,    0,    0,
    0,    0,  889,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  889,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  889,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  889,    0,    0,    0,    0,    0,  991,
    0,  991,  991,    0,    0,    0,    0,    0,    0,  991,
  889,  889,    0,    0,    0,  889,    0,  991,  991,    0,
  991,    0,    0,    0,  889,    0,    0,    0,    0,  991,
  991,    0,  991,  889,    0,    0,  889,    0,    0,    0,
    0,    0,    0,    0,    0,  889,    0,    0,    0,    0,
  889,  889,  889,    0,    0,    0,    0,  889,  889,  889,
  991,    0,    0,  991,  991,    0,    0,    0,  991,    0,
    0,  889,  889,  991,    0,    0,    0,    0,    0,    0,
    0,    0,  991,    0,  889,    0,    0,  991,  889,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  991,    0,    0,    0,    0,  991,    0,  991,
    0,    0,    0,    0,  991,    0,  991,  991,  991,    0,
  991,  991,  991,    0,  991,  991,  991,  991,    0,  991,
  991,  991,  991,  991,  991,  991,  991,  991,  991,    0,
    0,    0,    0,    0,  991,    0,  991,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  991,    0,    0,  991,  991,    0,    0,
    0,    0,    0,  991,    0,    0,    0,    0,  991,    0,
  991,    0,  991,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  991,    0,    0,    0,    0,    0,  991,    0,    0,
  991,    0,  991,    0,    0,    0,    0,  991,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  991,    0,
  991,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  991,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  991,    0,
    0,    0,    0,    0, 1213,    0, 1213, 1213,    0,    0,
    0,    0,    0,    0, 1213,  991,  991,    0,    0,    0,
  991,    0, 1213, 1213,    0, 1213,    0,    0,    0,  991,
    0,    0,    0,    0, 1213, 1213,    0, 1213,  991,    0,
  991,  991,    0,    0,    0,    0,    0,    0,    0,    0,
  991,    0,    0,    0,    0,  991,  991,  991,    0,    0,
    0,    0,  991,  991,  991, 1213,    0,    0, 1213, 1213,
    0,    0,    0, 1213,    0,    0,  991,  991, 1213,    0,
    0,    0,    0,    0,    0,    0,    0, 1213,    0,  991,
    0,    0, 1213,  991,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, 1213,    0,    0,
    0,    0, 1213,    0, 1213,    0,    0,    0,    0, 1213,
    0, 1213, 1213, 1213,    0, 1213, 1213, 1213,    0, 1213,
 1213, 1213, 1213,    0, 1213, 1213, 1213, 1213, 1213, 1213,
 1213, 1213, 1213, 1213,    0,    0,    0,    0,    0, 1213,
    0, 1213,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0, 1213,    0,
    0, 1213, 1213,    0,    0,    0,    0,    0, 1213,    0,
    0,    0,    0, 1213,    0, 1213,    0, 1213,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, 1213,    0,    0, 1213,    0, 1213,    0,    0,
    0,    0, 1213,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0, 1213,    0, 1213,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0, 1213,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0, 1213,    0,    0,    0,    0,    0,  991,
    0,  991,  991,    0,    0,    0,    0,    0,    0,    0,
 1213, 1213,    0,    0,    0, 1213,    0,  991,  991, 1213,
  991,    0,    0,    0, 1213,    0,    0,    0,    0,  991,
  991,    0,  991, 1213,    0, 1213, 1213,    0,    0,    0,
    0,    0,    0,    0,    0, 1213,    0,    0,    0,    0,
 1213, 1213, 1213,    0,    0,    0,    0, 1213, 1213, 1213,
  991,    0,    0,  991,  991,    0,    0,    0,  991,    0,
    0, 1213, 1213,  991,    0,    0,    0,    0,    0,    0,
    0,    0,  991,    0, 1213,    0,    0,  991, 1213,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  991,    0,    0,    0,    0,  991,    0,  991,
    0,    0,    0,    0,  991,    0,  991,  991,  991,    0,
  991,  991,  991,    0,  991,  991,  991,  991,    0,  991,
  991,  991,  991,  991,  991,  991,  991,  991,  991,    0,
    0,    0,    0,    0,  991,    0,  991,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  991, 1244,    0,  991,  991,    0,    0,
    0,    0,    0,  991,    0,    0,    0,    0,  991,    0,
  991,    0,  991,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  991,    0,    0,    0,    0,    0,  991,    0,    0,
  991,    0,  991,    0,    0,    0,    0,  991,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  991,    0,
  991,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  991,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  991,    0,
    0,    0,    0,    0, 1213,    0, 1213, 1213,    0,    0,
    0,    0,    0,    0,    0,  991,  991,    0,    0,    0,
  991,    0, 1068, 1068,    0, 1068,    0,    0,    0,  991,
    0,    0,    0,    0, 1068, 1068,    0, 1068,  991,    0,
  991,  991,    0,    0,    0,    0,    0,    0,    0,    0,
  991,    0,    0,    0,    0,  991,  991,  991,    0,    0,
    0,    0,  991,  991,  991, 1068,    0,    0, 1068, 1068,
    0,    0,    0, 1068,    0,    0,  991,  991, 1068,    0,
    0,    0,    0,    0,    0,    0,    0, 1068,    0,  991,
    0,    0, 1068,  991,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, 1068,    0,    0,
    0,    0, 1068,    0, 1068,    0,    0,    0,    0, 1068,
    0, 1068, 1068, 1068,    0, 1068, 1068, 1068,    0, 1068,
 1068, 1068, 1068,    0, 1068, 1068, 1068, 1068, 1068, 1068,
 1068, 1068, 1068, 1068,    0,    0,    0,    0,    0, 1068,
    0, 1068,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0, 1068,    0,
    0, 1068, 1068,    0,    0,    0,    0,    0, 1068,    0,
    0,    0,    0, 1068,    0, 1068,    0, 1068,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, 1068,    0,    0, 1068,    0, 1068,    0,    0,
    0,    0, 1068,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0, 1068,    0, 1068,    0,    0,    0,    0,
    0, 1068,    0,    0,    0,    0, 1068,    0,    0,    0,
    0, 1232,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0, 1068,    0,    0,    0,    0,    0,  991,
    0,  991,  991,    0,    0,    0,    0,    0,    0,    0,
 1068, 1068,    0,    0,    0, 1068,    0,  991,  991,    0,
  991,    0,    0,    0, 1068,    0,    0,    0,    0,  991,
  991,    0,  991, 1068,    0,    0, 1068,    0,    0,    0,
    0,    0,    0,    0,    0, 1068,    0,    0,    0,    0,
 1068, 1068, 1068,    0,    0, 1068,    0, 1068, 1068, 1068,
  991,    0,    0,  991,  991,    0,  527,    0,  991,  527,
    0, 1068, 1068,  991,  527,    0,    0,    0,    0,    0,
    0,    0,  991,    0, 1068,    0,    0,  991, 1068,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  991,    0,    0,    0,    0,  991,    0,  991,
    0,    0,    0,  527,  991,    0,  991,  991,  991,    0,
  991,  991,  991,    0,  991,  991,  991,  991,    0,  991,
  991,  991,  991,  991,  991,  991,  991,  991,  991,    0,
    0,    0,    0,    0,  991,    0,  991,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  991,    0,  527,  991,  991,    0,    0,
    0,    0,    0,  991,    0,    0,    0,    0,  991,    0,
  991,    0,  991,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  991,    0,    0,    0,    0,  527,  991,    0,    0,
  991,    0,  991,    0,    0,    0,    0,  991,    0,    0,
    0,    0, 1274,  527,    0, 1274,    0,    0,  991,    0,
  991,    0,    0,    0,  527,    0,    0,    0,    0,    0,
    0,  991,    0,    0,    0,    0,  527,    0,    0,    0,
  527,    0,    0,    0,    0,    0,    0,    0,  991,    0,
    0,    0,    0,    0,    0,    0,  991,    0,    0, 1274,
    0,    0,    0,    0,    0,  991,  991,    0,    0,    0,
  991,    0,  527,    0,    0,    0,    0,    0,    0,  991,
    0,    0,    0,    0,    0,    0,    0,    0,  991,    0,
  991,  991,  527,    0,  527,    0,    0,    0,    0, 1089,
  991, 1089, 1089,    0,    0,  991,  991,  991,    0,  527,
    0, 1274,  991,  991,  991,    0,  527, 1089, 1089,    0,
 1089,    0,    0,    0,    0,    0,  991,  991,    0, 1089,
 1089,    0, 1089,    0,    0,    0, 1089,    0,    0,  991,
    0,    0,    0,  991,    0,    0,    0,  527,    0,    0,
    0,    0, 1274,    0,    0,    0,    0,    0,    0,    0,
 1089,    0,    0, 1089, 1089,    0,    0,  527, 1089, 1274,
    0, 1089,    0, 1089,    0,    0,    0,    0,    0,  527,
    0,    0, 1089,    0,    0,    0,    0, 1089,    0,    0,
    0,  527, 1274,    0,  527,  527, 1274,    0,    0,    0,
    0,  527, 1089,    0,    0,    0,    0, 1089,    0, 1089,
    0,    0,    0,    0, 1089,    0, 1089, 1089, 1089,    0,
 1089, 1089, 1089,    0, 1089, 1089, 1089, 1089, 1274, 1089,
 1089, 1089, 1089, 1089, 1089, 1089, 1089, 1089, 1089,    0,
    0,    0,    0,    0, 1089,    0, 1089,    0, 1274,    0,
 1274,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0, 1089,    0, 1274, 1089, 1089,    0,    0,
    0,    0, 1274, 1089,    0,    0,    0,    0, 1089,    0,
 1089,    0, 1089,    0,    0,    0,    0,    0,    0,    0,
    0,    0, 1089,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0, 1274,    0,    0,    0, 1089,    0,    0,
 1089,    0, 1089,    0,    0,    0,    0, 1089,    0,    0,
    0,    0,    0, 1274,    0,    0,    0,    0,    0,    0,
 1089,    0,    0,    0,    0, 1274,    0,    0,    0,    0,
    0, 1089,    0,    0,    0,    0,    0, 1274,    0,    0,
 1274, 1274,    0,    0,    0,    0,    0, 1274, 1089,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0, 1089,
    0,    0,    0,    0,    0, 1089, 1089,    0,    0,    0,
 1089,    0,    0,    0,    0,    0,    0,    0,    0, 1089,
    0,    0,    0,    0,    0,    0,    0,    0, 1089,    0,
    0, 1089,    0,    0,    0,    0,    0,    0,    0, 1090,
 1089, 1090, 1090,    0,    0, 1089, 1089, 1089,    0,    0,
    0,    0, 1089, 1089, 1089,    0,    0, 1090, 1090,    0,
 1090,    0,    0,    0,    0,    0, 1089, 1089,    0, 1090,
 1090,    0, 1090,    0,    0,    0, 1090,    0,    0, 1089,
    0,    0,    0, 1089,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 1090,    0,    0, 1090, 1090,    0,  435,    0, 1090,  435,
    0, 1090,    0, 1090,    0,    0,    0,    0,    0,    0,
    0,    0, 1090,    0,    0,    0,    0, 1090,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, 1090,    0,    0,    0,    0, 1090,    0, 1090,
    0,    0,    0,  435, 1090,    0, 1090, 1090, 1090,    0,
 1090, 1090, 1090,    0, 1090, 1090, 1090, 1090,    0, 1090,
 1090, 1090, 1090, 1090, 1090, 1090, 1090, 1090, 1090,    0,
    0,    0,    0,    0, 1090,    0, 1090,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0, 1090,    0,  435, 1090, 1090,    0,    0,
    0,    0,    0, 1090,    0,    0,    0,    0, 1090,    0,
 1090,    0, 1090,    0,    0,    0,    0,    0,    0,    0,
    0,    0, 1090,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  435, 1090,    0,    0,
 1090,    0, 1090,    0,    0,    0,    0, 1090,    0,    0,
    0,    0,    0,  435,    0,    0,    0,    0,    0,    0,
 1090,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, 1090,    0,    0,    0,    0,  435,    0,    0,    0,
  435,    0,    0,    0,    0,    0,    0,    0, 1090,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0, 1090,
    0,    0,    0,    0,    0, 1090, 1090,    0,    0,    0,
 1090,    0,  435,    0,    0,    0,    0,    0,    0, 1090,
    0,    0,    0,    0,    0,    0,    0,    0, 1090,    0,
    0, 1090,  435,    0,  435,    0,    0,    0,    0, 1091,
 1090, 1091, 1091,    0,    0, 1090, 1090, 1090,    0,  435,
    0,    0, 1090, 1090, 1090,    0,  435, 1091, 1091,    0,
 1091,    0,    0,    0,    0,    0, 1090, 1090,    0, 1091,
 1091,    0, 1091,    0,    0,    0, 1091,    0,    0, 1090,
    0,    0,    0, 1090,    0,    0,    0,  435,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 1091,    0,    0, 1091, 1091,    0,    0,  435, 1091,    0,
    0, 1091,    0, 1091,    0,    0,    0,    0,    0,  435,
    0,    0, 1091,    0,    0,    0,    0, 1091,    0,    0,
    0,  435,    0,    0,  435,  435,    0,    0,    0,    0,
    0,  435, 1091,    0,    0,    0,    0, 1091,    0, 1091,
    0,    0,    0,    0, 1091,    0, 1091, 1091, 1091,    0,
 1091, 1091, 1091,    0, 1091, 1091, 1091, 1091,    0, 1091,
 1091, 1091, 1091, 1091, 1091, 1091, 1091, 1091, 1091,    0,
    0,    0,    0,    0, 1091,    0, 1091,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0, 1091,    0,    0, 1091, 1091,    0,    0,
    0,    0,    0, 1091,    0,    0,    0,    0, 1091,    0,
 1091,    0, 1091,    0,    0,    0,    0,    0,    0,    0,
    0,    0, 1091,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, 1091,    0,    0,
 1091,    0, 1091,    0,    0,    0,    0, 1091,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 1091,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, 1091,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0, 1091,    0,
    0,    0,    0,    0,  883,    0,  883,  883,    0, 1091,
    0,    0,    0,    0,    0, 1091, 1091,    0,    0,    0,
 1091,    0,  883,  883,    0,  883,    0,    0,    0, 1091,
    0,    0,    0,    0,  883,  883,    0,  883, 1091,    0,
    0, 1091,    0,    0,    0,    0,    0,    0,    0,    0,
 1091,    0,    0,    0,    0, 1091, 1091, 1091,    0,    0,
    0,    0, 1091, 1091, 1091,  883,    0,    0,  883,  883,
    0,    0,    0,  883,    0,    0, 1091, 1091,  883,    0,
    0,    0,    0,    0,    0,    0,    0,  883,    0, 1091,
    0,    0,  883, 1091,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  883,    0,    0,
    0,    0,  883,    0,  883,    0,    0,    0,    0,  883,
    0,  883,  883,  883,    0,  883,  883,  883,    0,  883,
  883,  883,  883,    0,  883,  883,  883,  883,  883,  883,
  883,  883,  883,  883,    0,    0,    0,    0,    0,  883,
    0,  883,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  883,    0,
    0,  883,  883,    0,    0,    0,    0,    0,  883,    0,
    0,    0,    0,  883,    0,  883,    0,  883,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  883,    0,    0,    0,
    0,    0,  883,    0,    0,  883,    0,  883,    0,    0,
    0,    0,  883,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  883,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  883,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  883,    0,    0,    0,    0,    0,    0,
    0,    0,  180,    0,  884,    0,  884,  884,    0,    0,
  883,  883,    0,    0,    0,  883,    0,    0,    0,    0,
    0,    0,  884,  884,  883,  884,    0,    0,    0,    0,
    0,    0,    0,  883,  884,  884,  883,  884,    0,    0,
    0,    0,    0,    0,    0,  883,    0,    0,    0,    0,
  883,  883,  883,    0,    0,    0,    0,  883,  883,  883,
    0,    0,    0,    0,    0,  884,    0,    0,  884,  884,
    0,  883,  883,  884,    0,    0,    0,    0,  884,    0,
    0,    0,    0,    0,  883,    0,    0,  884,  883,    0,
    0,    0,  884,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  884,    0,    0,
    0,    0,  884,    0,  884,    0,    0,    0,    0,  884,
    0,  884,  884,  884,    0,  884,  884,  884,    0,  884,
  884,  884,  884,    0,  884,  884,  884,  884,  884,  884,
  884,  884,  884,  884,    0,    0,    0,    0,    0,  884,
    0,  884,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  884,    0,
    0,  884,  884,    0,    0,    0,    0,    0,  884,    0,
    0,    0,    0,  884,    0,  884,    0,  884,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  884,    0,    0,    0,
    0,    0,  884,    0,    0,  884,    0,  884,    0,    0,
    0,    0,  884,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  884,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  884,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  884,    0,    0,    0,    0,    0,    0,
    0,    0,  180,    0, 1213,    0, 1213, 1213,    0,    0,
  884,  884,    0,    0,    0,  884,    0,    0,    0,    0,
    0,    0, 1213, 1213,  884, 1213,    0,    0,    0,    0,
    0,    0,    0,  884, 1213, 1213,  884, 1213,    0,    0,
    0,    0,    0,    0,    0,  884,    0,    0,    0,    0,
  884,  884,  884,    0,    0,    0,    0,  884,  884,  884,
    0,    0,    0,    0,    0, 1213,    0,    0, 1213, 1213,
    0,  884,  884, 1213,    0,    0,    0,    0, 1213,    0,
    0,    0,    0,    0,  884,    0,    0, 1213,  884,    0,
    0,    0, 1213,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, 1213,    0,    0,
    0,    0, 1213,    0, 1213,    0,    0,    0,    0, 1213,
    0, 1213, 1213, 1213,    0, 1213, 1213, 1213,    0, 1213,
 1213, 1213, 1213,    0, 1213, 1213, 1213, 1213, 1213, 1213,
 1213, 1213, 1213, 1213,    0,    0,    0,    0,    0, 1213,
    0, 1213,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0, 1213,    0,
    0, 1213, 1213,    0,    0,    0,    0,    0, 1213,    0,
    0,    0,    0, 1213,    0, 1213,    0, 1213,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, 1213,    0,    0, 1213,    0, 1213,    0,    0,
    0,    0, 1213,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0, 1213,    0, 1213,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0, 1213,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0, 1213,    0,    0,    0,    0,    0, 1087,
    0, 1087, 1087,    0,    0,    0,    0,    0,    0,    0,
 1213, 1213,    0,    0,    0, 1213,    0, 1087, 1087,    0,
 1087,    0,    0,    0, 1213,    0,    0,    0,    0, 1087,
 1087,    0, 1087, 1213,    0, 1213, 1213,    0,    0,    0,
    0,    0,    0,    0,    0, 1213,    0,    0,    0,    0,
 1213, 1213, 1213,    0,    0,    0,    0, 1213, 1213, 1213,
 1087,    0,    0, 1087, 1087,    0,    0,    0, 1087,    0,
    0, 1213, 1213, 1087,    0,    0,    0,    0,    0,    0,
    0,    0, 1087,    0, 1213,    0,    0, 1087, 1213,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, 1087,    0,    0,    0,    0, 1087,    0, 1087,
    0,    0,    0,    0, 1087,    0, 1087, 1087, 1087,    0,
 1087, 1087, 1087,    0, 1087, 1087, 1087, 1087,    0, 1087,
 1087, 1087, 1087, 1087, 1087, 1087, 1087, 1087, 1087,    0,
    0,    0,    0,    0, 1087,    0, 1087,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0, 1087,    0,    0, 1087, 1087,    0,    0,
    0,    0,    0, 1087,    0,    0,    0,    0, 1087,    0,
 1087,    0, 1087,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, 1087,    0,    0,
 1087,    0, 1087,    0,    0,    0,    0, 1087,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 1087,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, 1087,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0, 1087,    0,
    0,    0,    0,    0, 1213,    0, 1213, 1213,    0, 1087,
    0,    0,    0,    0,    0, 1087, 1087,    0,    0,    0,
 1087,    0,  875,  875,    0,  875,    0,    0,    0, 1087,
    0,    0,    0,    0,  875,  875,    0,  875, 1087,    0,
    0, 1087,    0,    0,    0,    0,    0,    0,    0,    0,
 1087,    0,    0,    0,    0, 1087, 1087, 1087,    0,    0,
    0,    0, 1087, 1087, 1087,  875,    0,    0,  875,  875,
    0,    0,    0,  875,    0,    0, 1087, 1087,  875,    0,
    0,    0,    0,    0,    0,    0,    0,  875,    0, 1087,
    0,    0,  875, 1087,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  875,    0,    0,
    0,    0,  875,    0,  875,    0,    0,    0,    0,  875,
    0,  875,  875,  875,    0,  875,  875,  875,    0,  875,
  875,  875,  875,    0,  875,  875,  875,  875,  875,  875,
  875,  875,  875,  875,    0,    0,    0,    0,    0,  875,
    0,  875,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  875,    0,
    0,  875,  875,    0,    0,    0,    0,    0,  875,    0,
    0,    0,    0,  875,    0,  875,    0,  875,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  875,    0,    0,  875,    0,  875,    0,    0,
    0,    0,  875,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  875,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  875,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  875,    0,    0,    0,    0,    0,    0,
    0,    0,  955,    0,    0,    0,    0,    0,    0,    0,
  875,  875,    0,    0,    0,  875,    0,  954,  954,    0,
  954,  955,    0,    0,  875,    0,    0,    0,    0,  954,
  954,    0,  954,  875,    0,    0,  875,    0,    0,    0,
    0,    0,  392,    0,    0,  875,    0,    0,    0,    0,
  875,  875,  875,    0,    0,    0,    0,  875,  875,  875,
  954,    0,    0,  954,  954,  392,  392,    0,  954,    0,
    0,  875,  875,  954,    0,    0,    0,    0,    0,    0,
    0,    0,  954,    0,  875,    0,    0,  954,  875,    0,
    0,    0,    0,    0,  392,    0,    0,    0,    0,    0,
    0,    0,  954,    0,    0,  955,    0,  954,    0,  954,
    0,    0,    0,    0,  954,    0,  954,  954,  954,    0,
  954,  954,  954,    0,  954,  954,  954,  954,    0,  954,
  954,  954,  954,  954,  954,  954,  954,  954,  954,    0,
    0,    0,    0,    0,  954,    0,  954,    0,    0,  467,
    0,  467,    0,  467,  467,  392,    0,    0,  467,    0,
    0,    0,    0,  954,    0,    0,  954,  954,    0,    0,
    0,    0,    0,  954,    0,  392,    0,    0,  954,  392,
  954,    0,  954,    0,    0,  392,  392,    0,    0,    0,
    0,    0,    0,    0,  467,  467,    0,  467,  467,  467,
    0,  955,  392,    0,    0,    0,    0,  954,    0,    0,
  954,    0,  954,    0,    0,    0,    0,  954,    0,    0,
  467,  467,  467,    0,    0,    0,    0,    0,    0,    0,
  954,  392,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  954,    0,    0,    0,    0,    0,    0,    0,    0,
  467,    0,    0,    0,    0,    0,    0,    0,  954,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  954,  954,    0,    0,    0,
  954,    0,    0,    0,    0,  467,  392,    0,    0,  954,
  392,  467,    0,    0,    0,    0,    0,    0,  954,    0,
    0,  954,  467,  467,  467,  392,    0,    0,  467,    0,
  954,  467,    0,  467,    0,  954,  954,  954,  392,    0,
  392,    0,  954,  954,  954,    0,    0,  275,    0,    0,
  392,  467,    0,  392,    0,  467,  954,  954,    0,    0,
  392,  467,  467,    0,    0,    0,  467,  467,    0,  954,
  275,  275,    0,  954,    0,    0,    0,    0,  467,  467,
    0,    0,    0,    0,  144,    0,  144,  467,  144,    0,
    0,    0,    0,  144,    0,    0,    0,    0,    0,  275,
    0,    0,    0,    0,    0,    0,    0,  467,    0,  467,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  467,    0,    0,    0,    0,  144,
  144,  467,  144,  144,  144,    0,  467,    0,    0,    0,
    0,  467,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  467,  144,  144,    0,    0,    0,
  275,    0,  467,  467,    0,    0,  467,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  275,  467,  467,    0,  275,  144,    0,    0,    0,    0,
  275,  275,    0,    0,  467,    0,  467,  467,    0,    0,
    0,    0,    0,  467,    0,  467,  467,  275,  467,  467,
  467,    0,    0,  467,    0,    0,  467,    0,    0,    0,
  144,    0,    0,    0,    0,    0,  144,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  275,  144,  144,  144,
    0,    0,    0,  144,    0,    0,    0,    0,  144,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  144,    0,    0,    0,
  144,    0,    0,    0,    0,    0,  144,    0,    0,    0,
    0,  144,  144,    0,    0,    0,    0,    0,    0,    0,
    0,  275,    0,    0,  144,  275,    0,    0,    0,    0,
    0,    0,  144,    0,    0,    0,    0,    0,    0,    0,
  275,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  144,  275,  144,  275,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  275,    0,    0,  275,  144,
    0,    0,    0,    0,    0,  275,  144,    0,    0,    0,
    0,  144,    0,    0,    0,    0,  144,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  144,
    0,    0,    0,    0,    0,    0,    0,  144,  144,    0,
    0,    0,    0,    0,    0,    0,  390,    0,  390,  390,
    0,    0,    0,  390,    0,  390,  390,  144,  390,    0,
    0,    0,    0,    0,    0,    0,    0,  390,  390,  144,
  390,    0,  144,    0,    0,    0,    0,    0,  144,    0,
  144,  144,    0,  144,  144,  144,    0,  390,  144,  390,
  390,  144,  390,  390,  390,    0,    0,    0,  390,    0,
    0,  390,  390,    0,    0,    0,  390,    0,    0,    0,
    0,  390,    0,    0,    0,  390,  390,    0,    0,    0,
  390,    0,    0,    0,    0,  390,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  390,    0,    0,    0,    0,  390,    0,  390,    0,    0,
    0,    0,  390,    0,  390,  390,  390,    0,  390,  390,
  390,  390,  390,  390,  390,  390,    0,  390,  390,  390,
  390,  390,  390,  390,  390,  390,  390,    0,    0,    0,
  390,    0,  390,  390,  390,    0,  390,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  390,  390,  390,
    0,  390,    0,  390,  390,  390,    0,    0,  390,    0,
    0,  390,    0,    0,    0,    0,  390,    0,  390,    0,
  390,    0,    0,    0,    0,    0,  390,    0,    0,    0,
  390,    0,    0,    0,    0,    0,  390,    0,    0,    0,
    0,  390,  390,    0,    0,  390,    0,    0,  390,    0,
  390,    0,    0,    0,  390,  390,    0,    0,    0,    0,
    0,    0,  390,    0,    0,    0,  390,    0,  390,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  390,
    0,    0,  390,    0,  390,  390,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  390,    0,    0,  390,
    0,    0,    0,    0,    0,    0,  390,    0,    0,    0,
    0,  390,    0,  390,  390,    0,  390,    0,  390,    0,
    0,    0,    0,    0,    0,    0,    0,  390,    0,  390,
    0,    0,    0,    0,    0,    0,  390,  390,  390,  390,
    0,    0,    0,    0,    0,    0,    0,    0,  390,    0,
    0,    0,    0,  390,  390,  390,    0,  390,    0,    0,
  390,  390,  390,    0,    0,    0,    0,    0,    0,  390,
    0,    0,  390,    0,  390,  390,    0,    0,  390,    0,
  390,  390,    0,  390,  390,  390,    0,  390,  390,    0,
  392,  390,  392,  392,    0,    0,    0,  392,    0,  392,
  392,    0,  392,    0,    0,    0,    0,    0,    0,    0,
    0,  392,  392,    0,  392,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  392,    0,  392,  392,    0,  392,  392,  392,    0,
    0,    0,  392,    0,    0,  392,  392,    0,    0,    0,
  392,    0,    0,    0,    0,  392,    0,    0,    0,  392,
  392,    0,    0,    0,  392,    0,    0,    0,    0,  392,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  392,    0,    0,    0,    0,  392,
    0,  392,    0,    0,    0,    0,  392,    0,  392,  392,
  392,    0,  392,  392,  392,  392,  392,  392,  392,  392,
    0,  392,  392,  392,  392,  392,  392,  392,  392,  392,
  392,    0,    0,    0,  392,    0,  392,  392,  392,    0,
  392,    0,    0,    0,    0,    0,    0,  438,    0,    0,
  438,  392,  392,  392,    0,  392,    0,  392,  392,  392,
    0,    0,  392,    0,    0,  392,    0,    0,    0,    0,
  392,    0,  392,    0,  392,    0,    0,    0,    0,    0,
  392,    0,    0,    0,  392,    0,    0,    0,    0,    0,
  392,    0,    0,    0,  438,  392,  392,    0,    0,  392,
    0,    0,  392,    0,  392,    0,    0,    0,  392,  392,
    0,    0,    0,    0,    0,    0,  392,    0,    0,    0,
  392,    0,  392,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  392,    0,    0,  392,    0,  392,  392,
    0,    0,    0,    0,    0,    0,  438,    0,    0,    0,
  392,  315,  463,  392,  463,  463,    0,    0,    0,  463,
  392,    0,    0,    0,    0,  392,    0,  392,  392,    0,
  392,    0,  392,    0,  315,  315,    0,  447,    0,    0,
  447,  392,    0,  392,    0,    0,    0,  438,    0,    0,
  392,  392,  392,  392,    0,  463,  463,    0,  463,  463,
  463,    0,  392,  315,  438,    0,    0,  392,  392,  392,
    0,  392,    0,    0,  392,  392,  392,    0,    0,    0,
    0,  463,  463,  392,  447,    0,  392,  438,  392,  392,
    0,  438,  392,    0,  392,  392,    0,  392,  392,  392,
    0,  392,  392,    0,    0,  392,    0,    0,    0,    0,
    0,  463,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  438,  315,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  447,    0,    0,    0,
    0,    0,    0,  438,  315,  438,  463,    0,  315,    0,
    0,    0,  463,    0,  315,  315,    0,    0,    0,    0,
  438,    0,    0,  463,  463,  463,    0,  438,    0,  463,
    0,  315,    0,    0,  463,    0,    0,  447,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  463,    0,  447,    0,  463,    0,  438,    0,
  315,    0,  463,    0,    0,    0,    0,  463,  463,    0,
    0,    0,    0,    0,    0,    0,    0,  447,  438,    0,
  463,  447,    0,    0,    0,    0,    0,    0,  463,    0,
  438,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  438,    0,    0,  438,  438,    0,  463,    0,
  463,    0,  438,  447,    0,  315,    0,    0,    0,  315,
    0,    0,    0,    0,    0,  463,    0,    0,    0,    0,
    0,    0,  463,  447,  315,  447,    0,  463,    0,    0,
    0,    0,  463,    0,    0,    0,    0,  315,    0,  315,
  447,    0,    0,    0,    0,  463,    0,  447,    0,  315,
    0,    0,  315,  463,  463,    0,    0,    0,    0,  315,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  463,    0,    0,    0,    0,  447,    0,
    0,    0,    0,    0,    0,  463,    0,    0,  463,    0,
    0,    0,    0,    0,  463,    0,  463,  463,  447,  463,
  463,  463,    0,    0,  463,    0,    0,  463,  367,  367,
  447,    0,    0,  367,    0,  367,  367,    0,  367,    0,
    0,    0,  447,    0,    0,  447,  447,  367,  367,    0,
  367,    0,  447,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  367,    0,  367,
  367,    0,  367,  367,  367,    0,    0,    0,  367,    0,
    0,  367,  367,    0,    0,    0,  367,    0,    0,    0,
    0,  367,    0,    0,    0,  367,  367,    0,    0,    0,
  367,    0,    0,    0,    0,  367,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  367,    0,    0,    0,    0,  367,    0,  367,    0,    0,
    0,    0,  367,    0,  367,  367,  367,    0,  367,  367,
  367,  367,  367,  367,  367,  367,    0,  367,  367,  367,
  367,  367,  367,  367,  367,  367,  367,    0,    0,    0,
  367,    0,  367,  367,  367,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  367,  367,  367,
    0,  367,    0,    0,  367,  367,    0,    0,  367,    0,
    0,  367,    0,    0,    0,    0,  367,    0,  367,    0,
  367,    0,    0,    0,    0,    0,  367,    0,    0,    0,
  367,    0,    0,    0,    0,    0,  367,    0,    0,    0,
    0,  367,  367,    0,    0,  367,    0,    0,  367,    0,
  367,    0,    0,    0,  367,  367,    0, 1274, 1274,    0,
    0,    0, 1274,    0,    0,    0,  367,    0,  367,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  367,
    0,    0,  367,    0,    0,  367,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  367,    0, 1274, 1274,
    0, 1274, 1274, 1274,    0,    0,    0,    0,    0,    0,
    0,  367,    0,  367,  367,    0,  367,    0,  367,    0,
    0,    0,    0,    0, 1274, 1274,    0,  367,    0,  367,
    0,    0,    0,    0,    0,    0,  367,  367,  367,  367,
    0,    0,    0,    0,    0,    0,    0,    0,  367,    0,
    0,    0,    0,  367,  367,  367,    0,    0,    0,    0,
  367,  367,  367,    0,    0,    0,    0,    0,    0,  367,
    0,    0,  367,    0,  367,  367,    0,    0,  367,    0,
  367,    0,    0,  367,  367,  367,    0,  367,  367, 1274,
    0,  367,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0, 1274, 1274, 1274,    0,
    0,    0,    0,    0,    0,    0,    0, 1274,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0, 1274,    0,    0,    0, 1274,
    0,    0,    0,    0,    0, 1274,    0,    0,    0,    0,
 1274, 1274,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0, 1274,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, 1274,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  853,    0,    0,    0,  853,    0,  853,  853,
 1274,  853,    0,    0,    0, 1274,    0,    0,    0,    0,
  853,  853,    0,  853,    0,    0,    0,    0, 1274,    0,
    0,    0,    0,    0,    0,    0, 1274, 1274,    0,    0,
  853,    0,  853,    0,    0,  853,  853,  853,    0,    0,
    0,  853,    0,    0,  853,  853,    0,    0,    0,  853,
    0,    0,    0,    0,  853,    0,    0,    0, 1274,  853,
    0, 1274,    0,  853,    0,    0,    0, 1274,  853, 1274,
    0,    0, 1274, 1274, 1274,    0,    0, 1274,    0,    0,
 1274,    0,    0,  853,    0,    0,    0,    0,  853,    0,
  853,    0,    0,    0,    0,  853,    0,  853,  853,  853,
    0,  853,  853,  853,  853,  853,  853,  853,  853,    0,
  853,  853,  853,  853,  853,  853,  853,  853,  853,  853,
    0,    0,    0,  853,    0,  853,  853,  853,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  853,    0,  853,    0,    0,  853,  853,    0,
    0,  853,    0,    0,  853,    0,    0,    0,    0,  853,
    0,  853,    0,  853,    0,    0,    0,    0,    0,  853,
    0,    0,    0,  853,    0,    0,    0,    0,    0,  853,
    0,    0,    0,    0,  853,  853,    0,    0,  853,    0,
    0,  853,    0,  853,    0,    0,    0,  853,  853,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  853,
    0,  853,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  853,    0,    0,    0,    0,    0,  853,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  853,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  853,    0,  853,  853,    0,  853,
    0,  853,    0,    0,    0,    0,    0,    0,    0,    0,
  853,    0,  853,    0,    0,    0,    0,    0,    0,  853,
  853,    0,  853,    0,    0,    0,    0,    0,    0,    0,
    0,  853,    0,    0,    0,    0,  853,  853,  853,    0,
    0,    0,    0,  853,  853,  853,    0,  852,    0,    0,
    0,  852,  853,  852,  852,  853,  852,  853,  853,    0,
    0,  853,    0,  853,    0,  852,  852,    0,  852,    0,
  853,  853,    0,    0,  853,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  852,    0,  852,    0,    0,
  852,  852,  852,    0,    0,    0,  852,    0,    0,  852,
  852,    0,    0,    0,  852,    0,    0,    0,    0,  852,
    0,    0,    0,    0,  852,    0,    0,    0,  852,    0,
    0,    0,    0,  852,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  852,    0,
    0,    0,    0,  852,    0,  852,    0,    0,    0,    0,
  852,    0,  852,  852,  852,    0,  852,  852,  852,  852,
  852,  852,  852,  852,    0,  852,  852,  852,  852,  852,
  852,  852,  852,  852,  852,    0,    0,    0,  852,    0,
  852,  852,  852,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  852,    0,  852,
    0,    0,  852,  852,    0,    0,  852,    0,    0,  852,
    0,    0,    0,    0,  852,    0,  852,    0,  852,    0,
    0,    0,    0,    0,  852,    0,    0,    0,  852,    0,
    0,    0,    0,    0,  852,    0,    0,    0,    0,  852,
  852,    0,    0,  852,    0,    0,  852,    0,  852,    0,
    0,    0,  852,  852,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  852,    0,  852,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  852,    0,    0,
    0,    0,    0,  852,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  852,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  852,
    0,  852,  852,    0,  852,    0,  852,    0,    0,    0,
    0,    0,    0,    0,    0,  852,    0,  852,    0,    0,
    0,    0,    0,    0,  852,  852,    0,  852,    0,    0,
    0,    0,    0,    0,    0,    0,  852,    0,    0,    0,
    0,  852,  852,  852,    0,    0,    0,    0,  852,  852,
  852,    0,  851,    0,    0,    0,  851,  852,  851,  851,
  852,  851,  852,  852,    0,    0,  852,    0,  852,    0,
  851,  851,    0,  851,    0,  852,  852,    0,    0,  852,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  851,    0,  851,    0,    0,  851,  851,  851,    0,    0,
    0,  851,    0,    0,  851,  851,    0,    0,    0,  851,
    0,    0,    0,    0,  851,    0,    0,    0,    0,  851,
    0,    0,    0,  851,    0,    0,    0,    0,  851,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  851,    0,    0,    0,    0,  851,    0,
  851,    0,    0,    0,    0,  851,    0,  851,  851,  851,
    0,  851,  851,  851,  851,  851,  851,  851,  851,    0,
  851,  851,  851,  851,  851,  851,  851,  851,  851,  851,
    0,    0,    0,  851,    0,  851,  851,  851,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  851,    0,  851,    0,    0,  851,  851,    0,
    0,  851,    0,    0,  851,    0,    0,    0,    0,  851,
    0,  851,    0,  851,    0,    0,    0,    0,    0,  851,
    0,    0,    0,  851,    0,    0,    0,    0,    0,  851,
    0,    0,    0,    0,  851,  851,    0,    0,  851,    0,
    0,  851,    0,  851,    0,    0,    0,  851,  851,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  851,
    0,  851,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  851,    0,    0,    0,    0,    0,  851,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  851,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  851,    0,  851,  851,    0,  851,
    0,  851,    0,    0,    0,    0,    0,    0,    0,    0,
  851,    0,  851,    0,    0,    0,    0,    0,    0,  851,
  851,    0,  851,    0,    0,    0,    0,    0,    0,    0,
    0,  851,    0,    0,    0,    0,  851,  851,  851,    0,
    0,    0,    0,  851,  851,  851,    0, 1232,    0,    0,
    0, 1232,  851,  819,  819,  851,  819,  851,  851,    0,
    0,  851,    0,  851,    0,  819,  819,    0,  819,    0,
  851,  851,    0,    0,  851,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, 1232,    0,    0,
 1232, 1232, 1232,    0,    0,    0,  819,    0,    0,  819,
  819,    0,    0,    0,  819,    0,    0,    0,    0,  819,
    0,    0,    0,    0,    0,    0,    0,    0,  819,    0,
    0,    0,    0,  819,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  819,    0,
    0,    0,    0,  819,    0,  819,    0,    0,    0,    0,
  819,    0,  819,  819,  819,    0,  819,  819,  819,    0,
  819,  819,  819,  819,    0,  819,  819,  819,  819,  819,
  819,  819,  819,  819,  819,    0,    0,    0, 1232,    0,
  819,  819,  819,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, 1232,    0,  819,
    0,    0,  819,  819,    0,    0, 1232,    0,    0,  819,
    0,    0,    0,    0,  819,    0,  819,    0,  819,    0,
    0,    0,    0,    0, 1232,    0,    0,    0, 1232,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0, 1232,
 1232,    0,    0,  819,    0,    0,  819,    0,  819,    0,
    0,    0, 1232,  819,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  819,    0,  819,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  819,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  819,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0, 1232,
    0,  819,  819,    0, 1232,    0,  819,    0,    0,    0,
    0,    0,    0,    0,    0,  819,    0, 1232,    0,    0,
    0,    0,    0,    0,  819, 1232,    0,  819,    0,    0,
    0,    0,    0,    0,    0,    0,  819,    0,    0,    0,
    0,  819,  819,  819,    0,    0,    0,    0,  819,  819,
  819,    0, 1232,    0,    0,    0, 1232, 1232,  831,  831,
 1232,  831,  819,  819,    0,    0, 1232,    0, 1232,    0,
  831,  831,    0,  831,    0,  819,    0,    0,    0,  819,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, 1232,    0,    0, 1232, 1232, 1232,    0,    0,
    0,  831,    0,    0,  831,  831,    0,    0,    0,  831,
    0,    0,    0,    0,  831,    0,    0,    0,    0,    0,
    0,    0,    0,  831,    0,    0,    0,    0,  831,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  831,    0,    0,    0,    0,  831,    0,
  831,    0,    0,    0,    0,  831,    0,    0,  831,  831,
    0,  831,  831,  831,    0,  831,  831,  831,  831,    0,
  831,  831,  831,  831,  831,  831,  831,  831,  831,  831,
    0,    0,    0, 1232,    0,  831, 1234,  831,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, 1232,    0,  831,    0,    0,  831,  831,    0,
    0, 1232,    0,    0,  831,    0,    0,    0,    0,  831,
    0,  831,    0,  831,    0,    0,    0,    0,    0, 1232,
    0,    0,    0, 1232,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0, 1232, 1232,    0,    0,  831,    0,
    0,  831,    0,  831,    0,    0,    0, 1232,  831,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  831,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  831,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  831,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0, 1232,    0,  831,  831,    0, 1232,
    0,  831,    0,    0,    0,    0,    0,    0,    0,    0,
  831,    0, 1232,    0,    0,    0,    0,    0,    0,  831,
 1232,    0,  831,    0,    0,    0,    0,    0,    0,    0,
    0,  831,    0,    0,    0,    0,  831,  831,  831,    0,
    0,    0,    0,  831,  831,  831,    0, 1232,    0,    0,
    0, 1232, 1232,  849,  849, 1232,  849,  831,  831,    0,
    0, 1232,    0, 1232,    0,  849,  849,    0,  849,    0,
  831,    0,    0,    0,  831,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, 1232,    0,    0,
 1232, 1232, 1232,    0,    0,    0,  849,    0,    0,  849,
  849,    0,    0,    0,  849,    0,    0,    0,    0,  849,
    0,    0,    0,    0,    0,    0,    0,    0,  849,    0,
    0,    0,    0,  849,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  849,    0,
    0,    0,    0,  849,    0,  849,    0,    0,    0,    0,
  849,    0,  849,  849,  849,    0,  849,  849,  849,    0,
  849,  849,  849,  849,    0,  849,  849,  849,  849,  849,
  849,  849,  849,  849,  849,    0,    0,    0, 1232,    0,
  849,    0,  849,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, 1232,    0,  849,
    0,    0,  849,  849,    0,    0, 1232,    0,    0,  849,
    0,    0,    0,    0,  849,    0,  849,    0,  849,    0,
    0,    0,    0,    0, 1232,    0,    0,    0, 1232,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0, 1232,
 1232,    0,    0,  849,    0,    0,  849,    0,  849,    0,
    0,    0, 1232,  849,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  849,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  849,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  849,    0,  577,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0, 1232,
    0,  849,  849,    0, 1232,    0,  849,    0,  577,  577,
    0,  577,    0,    0,    0,  849,    0, 1232,    0,    0,
    0,  577,    0,  577,  849, 1232,    0,  849,    0,    0,
    0,    0,    0,    0,    0,    0,  849,    0,    0,    0,
    0,  849,  849,  849,    0,    0,    0,    0,  849,  849,
  849,  577,    0,    0,  577,  577,    0, 1232,    0,  577,
 1232,    0,  849,  849,  577,    0, 1232,    0, 1232,    0,
    0,    0,    0,  577,    0,  849,  361,    0,  577,  849,
  361,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  577,    0,    0,    0,    0,  577,    0,
  577,    0,    0,    0,    0,    0,  577,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  361,  361,    0,  361,
  361,  361,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  577,    0,  577,    0,    0,
    0,    0,  361,  361,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  577,    0,    0,  577,  577,    0,
    0,    0,    0,    0,  577,    0,    0,    0,    0,  577,
    0,  577,    0,  577,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  577,    0,
    0,  577,    0,  577,    0,    0,    0,  361,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  577,    0,    0,  361,  361,  361,    0,    0,    0,
    0,    0,  577,    0,    0,  361,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  577,
    0,    0,    0,  361,    0,    0,    0,  361,    0,    0,
    0,    0,    0,  361,    0,    0,  577,  577,  361,  361,
    0,  577,    0,    0,    0,    0,    0,    0,    0,    0,
  577,  361,    0,    0,    0,    0,    0,    0,    0,  577,
    0,    0,  577,    0,    0,    0,    0,    0,    0,    0,
    0,  577,    0,    0,    0,    0,  577,  577,  577,  361,
    0,    0,    0,  577,  577,  577,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  577,  577,    0,
  845,    0,  845,  845,    0,  845,    0,    0,  361,    0,
    0,    0,    0,  361,  845,  845,    0,  845,    0,    0,
    0,    0,    0,    0,    0,    0,  361,    0,    0,    0,
    0,    0,    0,    0,  361,  361,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  845,    0,    0,  845,  845,
    0,    0,    0,  845,    0,    0,    0,    0,  845,    0,
    0,    0,    0,    0,    0,    0,  361,  845,    0,  361,
    0,    0,  845,    0,    0,  361,    0,  361,    0,    0,
  361,  361,  361,    0,    0,  361,    0,  845,  361,    0,
    0,    0,  845,    0,  845,    0,    0,    0,    0,  845,
    0,  845,  845,  845,    0,  845,  845,  845,  845,  845,
  845,  845,  845,    0,  845,  845,  845,  845,  845,  845,
  845,  845,  845,  845,    0,    0,    0,  845,    0,  845,
    0,  845,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  845,    0,
    0,  845,  845,    0,    0,    0,    0,    0,  845,    0,
    0,    0,    0,  845,    0,  845,    0,  845,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  845,    0,    0,  845,    0,  845,    0,    0,
    0,    0,  845,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  845,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  845,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  845,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  845,  845,    0,    0,    0,  845,    0,    0,    0,    0,
 1232,    0,  849,  849,  845,  849,    0,    0,    0,    0,
    0,    0,    0,  845,  849,  849,  845,  849,    0,    0,
    0,    0,    0,    0,    0,  845,    0,    0,    0,    0,
  845,  845,  845,    0,    0,    0,    0,  845,  845,  845,
    0,    0,    0,    0,    0,  849,    0,    0,  849,  849,
    0,  845,  845,  849,    0,    0,    0,    0,  849,    0,
    0,    0,    0,    0,  845,  845,    0,  849,  845,    0,
    0,    0,  849,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  849,    0,    0,
    0,    0,  849,    0,  849,    0,    0,    0,    0,  849,
    0,  849,  849,  849,    0,  849,  849,  849,    0,  849,
  849,  849,  849,    0,  849,  849,  849,  849,  849,  849,
  849,  849,  849,  849,    0,    0,    0, 1232,    0,  849,
    0,  849,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  849,    0,
    0,  849,  849,    0,    0,    0,    0,    0,  849,    0,
    0,    0,    0,  849,    0,  849,    0,  849,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  849,    0,    0,  849,    0,  849,    0,    0,
    0,    0,  849,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  849,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  849,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  849,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  849,  849,    0,    0,    0,  849,    0,  899,  899,    0,
  899,    0,    0,    0,  849,    0,    0,    0,    0,  899,
  899,    0,  899,  849,    0,    0,  849,    0,    0,    0,
    0,    0,    0,    0,    0,  849,    0,    0,    0,  899,
  849,  849,  849,    0,    0,    0,    0,  849,  849,  849,
  899,    0,    0,  899,  899,    0,    0,    0,  899,    0,
    0,  849,  849,  899,    0,    0,    0,    0,    0,    0,
    0,    0,  899,    0,  849,    0,    0,  899,  849,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  899,    0,    0,    0,    0,  899,    0,  899,
    0,    0,    0,    0,  899,  899,  899,  899,  899,    0,
  899,  899,  899,    0,  899,  899,  899,  899,    0,  899,
  899,  899,  899,  899,  899,  899,  899,  899,  899,    0,
    0,    0,    0,    0,  899,    0,  899,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  899,    0,    0,  899,  899,    0,    0,
    0,    0,    0,  899,  899,    0,    0,    0,  899,    0,
  899,    0,  899,    0,  899,  899,    0,    0,    0,  899,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  899,    0,    0,    0,    0,  899,    0,    0,
  899,    0,  899,    0,    0,    0,    0,  899,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  899,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  899,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  899,  899,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  899,  899,    0,    0,    0,
  899,    0, 1222, 1222,    0, 1222,    0,    0,    0,  899,
    0,    0,    0,    0, 1222, 1222,    0, 1222,  899,    0,
    0,  899,    0,    0,    0,    0,    0,    0,    0,    0,
  899,    0,    0,    0, 1222,  899,  899,  899,    0,    0,
    0,    0,  899,  899,  899, 1222,    0,    0, 1222, 1222,
    0,    0,    0, 1222,    0,    0,  899,  899, 1222,    0,
    0,    0,    0,    0,    0,    0,    0, 1222,    0,  899,
  899,    0, 1222,  899,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, 1222,    0,    0,
    0,    0, 1222,    0, 1222,    0,    0,    0,    0, 1222,
 1222, 1222, 1222, 1222,    0, 1222, 1222, 1222,    0, 1222,
 1222, 1222, 1222,    0, 1222, 1222, 1222, 1222, 1222, 1222,
 1222, 1222, 1222, 1222,    0,    0,    0,    0,    0, 1222,
    0, 1222,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0, 1222,    0,
    0, 1222, 1222,    0,    0,    0,    0,    0, 1222, 1222,
    0,    0,    0, 1222,    0, 1222,    0, 1222,    0, 1222,
 1222,    0,    0,    0, 1222,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, 1222,    0,    0,
    0,    0, 1222,    0,    0, 1222,    0, 1222,    0,    0,
    0,    0, 1222,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0, 1222,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0, 1222,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0, 1222,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 1222, 1222,    0,    0,    0, 1222,    0,  902,  902,    0,
  902,    0,    0,    0, 1222,    0,    0,    0,    0,  902,
  902,    0,  902, 1222,    0,    0, 1222,    0,    0,    0,
    0,    0,    0,    0,    0, 1222,    0,    0,    0,  902,
 1222, 1222, 1222,    0,    0,    0,    0, 1222, 1222, 1222,
  902,    0,    0,  902,  902,    0,    0,    0,  902,    0,
    0, 1222, 1222,  902,    0,    0,    0,    0,    0,    0,
    0,    0,  902,    0, 1222, 1222,    0,  902, 1222,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  902,    0,    0,    0,    0,  902,    0,  902,
    0,    0,    0,    0,  902,  902,  902,  902,  902,    0,
  902,  902,  902,    0,  902,  902,  902,  902,    0,  902,
  902,  902,  902,  902,  902,  902,  902,  902,  902,    0,
    0,    0,    0,    0,  902,    0,  902,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  902,    0,    0,  902,  902,    0,    0,
    0,    0,    0,  902,  902,    0,    0,    0,  902,    0,
  902,    0,  902,    0,    0,  902,    0,    0,    0,  902,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  902,    0,    0,    0,    0,  902,    0,    0,
  902,    0,  902,    0,    0,    0,    0,  902,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  902,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  902,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  902,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  902,  902,    0,    0,    0,
  902,    0,  889,  889,    0,  889,    0,    0,    0,  902,
    0,    0,    0,    0,  889,  889,    0,  889,  902,    0,
    0,  902,    0,    0,    0,    0,    0,    0,    0,    0,
  902,    0,    0,    0,  889,  902,  902,  902,    0,    0,
    0,    0,  902,  902,  902,  889,    0,    0,  889,  889,
    0,    0,    0,  889,    0,    0,  902,  902,  889,    0,
    0,    0,    0,    0,    0,    0,    0,  889,    0,  902,
  902,    0,  889,  902,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  889,    0,    0,
    0,    0,  889,    0,  889,    0,    0,    0,    0,  889,
  889,  889,  889,  889,    0,  889,  889,  889,    0,  889,
  889,  889,  889,    0,  889,  889,  889,  889,  889,  889,
  889,  889,  889,  889,    0,    0,    0,    0,    0,  889,
    0,  889,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  889,    0,
    0,  889,  889,    0,    0,    0,    0,    0,  889, 1232,
    0,    0,    0,  889,    0,  889,    0,  889,    0,    0,
  889,    0,    0,    0,  889,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, 1232,    0,    0,
    0,    0,  889,    0,    0,  889,    0,  889,    0,    0,
    0,    0,  889,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  889,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  889,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  889,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  889,  889,    0,    0,    0,  889,    0, 1118, 1118,    0,
 1118,    0,    0,    0,  889,    0,    0,    0,    0, 1118,
 1118,    0, 1118,  889,    0,    0,  889,    0,    0,    0,
    0,    0,    0,    0,    0,  889,    0,    0,    0,    0,
  889,  889,  889,    0,    0,    0,    0,  889,  889,  889,
 1118,    0,    0, 1118, 1118,    0,    0,    0, 1118,    0,
    0,  889,  889, 1118,    0,    0,    0,    0,    0,    0,
    0,    0, 1118,    0,  889,    0,    0, 1118,  889,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, 1118,    0,    0,    0,    0, 1118,    0, 1118,
    0,    0,    0,    0, 1118,    0, 1118, 1118, 1118,    0,
 1118, 1118, 1118,    0, 1118, 1118, 1118, 1118,    0, 1118,
 1118, 1118, 1118, 1118, 1118, 1118, 1118, 1118, 1118,    0,
    0,    0,    0,    0, 1118, 1118, 1118,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0, 1118, 1118,    0, 1118, 1118,    0,    0,
    0,    0,    0, 1118,    0,    0,    0,    0, 1118,    0,
 1118,    0, 1118,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, 1118,    0,    0,
 1118,    0, 1118,    0,    0,    0,    0, 1118,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0, 1118,    0,
 1118,    0,    0,    0,    0,    0, 1118,    0,    0,    0,
    0, 1118,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0, 1118,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0, 1118, 1118, 1118,    0,    0,
 1118,    0,    0,    0,    0,    0,    0, 1096, 1096, 1118,
 1096,    0,    0,    0,    0,    0,    0,    0, 1118, 1096,
 1096, 1118, 1096,    0,    0,    0, 1096,    0,    0,    0,
 1118,    0,    0,    0,    0, 1118, 1118, 1118,    0,    0,
    0,    0, 1118, 1118, 1118,    0,    0,    0,    0,    0,
 1096,    0,    0, 1096, 1096,    0, 1118, 1118, 1096,    0,
    0, 1096,    0, 1096,    0,    0,    0,    0,    0, 1118,
    0,    0, 1096, 1118,    0,    0,    0, 1096,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, 1096,    0,    0,    0,    0, 1096,    0, 1096,
    0,    0,    0,    0, 1096,    0, 1096, 1096, 1096,    0,
 1096, 1096, 1096,    0, 1096, 1096, 1096, 1096,    0, 1096,
 1096, 1096, 1096, 1096, 1096, 1096, 1096, 1096, 1096,    0,
    0,    0,    0,    0, 1096,    0, 1096,    0,    0,    0,
    0,    0,    0,    0,    0,    0, 1096,    0,    0,    0,
    0,    0,    0, 1096,    0,    0, 1096, 1096,    0,    0,
    0,    0,    0, 1096,    0,    0,    0,    0, 1096,    0,
 1096,    0, 1096,    0,    0,    0,    0,    0,    0,    0,
    0,    0, 1096,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, 1096,    0,    0,
 1096,    0, 1096,    0,    0,    0,    0, 1096,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 1096,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, 1096,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0, 1096,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0, 1096, 1096,    0,    0,    0,
 1096,    0,    0,    0,    0,    0,    0, 1095, 1095, 1096,
 1095,    0,    0,    0,    0,    0,    0,    0, 1096, 1095,
 1095, 1096, 1095,    0,    0,    0, 1095,    0,    0,    0,
 1096,    0,    0,    0,    0, 1096, 1096, 1096,    0,    0,
    0,    0, 1096, 1096, 1096,    0,    0,    0,    0,    0,
 1095, 1096,    0, 1095, 1095,    0, 1096, 1096, 1095,    0,
    0, 1095,    0, 1095,    0,    0,    0,    0,    0, 1096,
    0,    0, 1095, 1096,    0,    0,    0, 1095,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, 1095,    0,    0,    0,    0, 1095,    0, 1095,
    0,    0,    0,    0, 1095,    0, 1095, 1095, 1095,    0,
 1095, 1095, 1095,    0, 1095, 1095, 1095, 1095,    0, 1095,
 1095, 1095, 1095, 1095, 1095, 1095, 1095, 1095, 1095,    0,
    0,    0,    0,    0, 1095,    0, 1095,    0,    0,    0,
    0,    0,    0,    0,    0,    0, 1095,    0,    0,    0,
    0,    0,    0, 1095,    0,    0, 1095, 1095,    0,    0,
    0,    0,    0, 1095,    0,    0,    0,    0, 1095,    0,
 1095,    0, 1095,    0,    0,    0,    0,    0,    0,    0,
    0,    0, 1095,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, 1095,    0,    0,
 1095,    0, 1095,    0,    0,    0,    0, 1095,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 1095,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, 1095,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0, 1095,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0, 1095, 1095,    0,    0,    0,
 1095,    0,  931,  931,    0,  931,    0,    0,    0, 1095,
    0,    0,    0,    0,  931,  931,    0,  931, 1095,    0,
  931, 1095,    0,    0,    0,    0,    0,    0,    0,    0,
 1095,    0,    0,    0,    0, 1095, 1095, 1095,  931,    0,
    0,    0, 1095, 1095, 1095,  931,    0,    0,  931,  931,
    0, 1095,    0,  931,    0,    0, 1095, 1095,  931,    0,
    0,    0,    0,    0,    0,    0,    0,  931,    0, 1095,
    0,    0,  931, 1095,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  931,    0,    0,
    0,    0,  931,    0,  931,    0,    0,    0,    0,  931,
    0,  931,  931,  931,    0,  931,  931,  931,    0,  931,
  931,  931,  931,    0,  931,  931,  931,  931,  931,  931,
  931,  931,  931,  931,    0,    0,    0,    0,    0,  931,
    0,  931,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  931,    0,
    0,  931,  931,    0,    0,    0,    0,    0,  931,    0,
    0,    0,    0,  931,    0,  931,    0,  931,    0,    0,
  931,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  931,    0,    0,  931,    0,  931,    0,    0,
    0,    0,  931,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  931,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  931,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  931,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  931,  931,    0,    0,    0,  931,    0, 1222, 1222,    0,
 1222,    0,    0,    0,  931,    0,    0,    0,    0, 1222,
 1222,    0, 1222,  931,    0,    0,  931,    0,    0,    0,
    0,    0,    0,    0,    0,  931,    0,    0,    0, 1222,
  931,  931,  931,    0,    0,    0,    0,  931,  931,  931,
 1222,    0,    0, 1222, 1222,    0,    0,    0, 1222,    0,
    0,  931,  931, 1222,    0,    0,    0,    0,    0,    0,
    0,    0, 1222,    0,  931,    0,    0, 1222,  931,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, 1222,    0,    0,    0,    0, 1222,    0, 1222,
    0,    0,    0,    0, 1222, 1222, 1222, 1222, 1222,    0,
 1222, 1222, 1222,    0, 1222, 1222, 1222, 1222,    0, 1222,
 1222, 1222, 1222, 1222, 1222, 1222, 1222, 1222, 1222,    0,
    0,    0,    0,    0, 1222,    0, 1222,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0, 1222,    0,    0, 1222, 1222,    0,    0,
    0,    0,    0, 1222,    0,    0,    0,    0, 1222,    0,
 1222,    0, 1222,    0, 1222,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, 1222,    0,    0,
 1222,    0, 1222,    0,    0,    0,    0, 1222,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 1222,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, 1222,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0, 1222,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0, 1222, 1222,    0,    0,    0,
 1222,    0, 1118, 1118,    0, 1118,    0,    0,    0, 1222,
    0,    0,    0,    0, 1118, 1118,    0, 1118, 1222,    0,
    0, 1222,    0,    0,    0,    0,    0,    0,    0,    0,
 1222,    0,    0,    0,    0, 1222, 1222, 1222,    0,    0,
    0,    0, 1222, 1222, 1222, 1118,    0,    0, 1118, 1118,
    0,    0,    0, 1118,    0,    0, 1222, 1222, 1118,    0,
    0,    0,    0,    0,    0,    0,    0, 1118,    0, 1222,
    0,    0, 1118, 1222,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, 1118,    0,    0,
    0,    0, 1118,    0, 1118,    0,    0,    0,    0, 1118,
    0, 1118, 1118, 1118,    0, 1118, 1118, 1118,    0, 1118,
 1118, 1118, 1118,    0, 1118, 1118, 1118, 1118, 1118, 1118,
 1118, 1118, 1118, 1118,    0,    0,    0,    0,    0, 1118,
 1118, 1118,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0, 1118,    0,
    0, 1118, 1118,    0,    0,    0,    0,    0, 1118,    0,
    0,    0,    0, 1118,    0, 1118,    0, 1118,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, 1118,    0,    0, 1118,    0, 1118,    0,    0,
    0,    0, 1118,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0, 1118,    0, 1118,    0,    0,    0,    0,
    0, 1118,    0,    0,    0,    0, 1118,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0, 1118,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 1118, 1118,    0,    0,    0, 1118,    0, 1155, 1155,    0,
 1155,    0,    0,    0, 1118,    0,    0,    0,    0, 1155,
 1155,    0, 1155, 1118,    0,    0, 1118,    0,    0,    0,
    0,    0,    0,    0,    0, 1118,    0,    0,    0,    0,
 1118, 1118, 1118,    0,    0,    0,    0, 1118, 1118, 1118,
 1155,    0,    0, 1155, 1155,    0,    0,    0, 1155,    0,
    0, 1118, 1118, 1155,    0,    0,    0,    0,    0,    0,
    0,    0, 1155,    0, 1118,    0,    0, 1155, 1118,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, 1155,    0,    0,    0,    0, 1155,    0, 1155,
    0,    0,    0,    0, 1155,    0, 1155, 1155, 1155,    0,
 1155, 1155, 1155,    0, 1155, 1155, 1155, 1155,    0, 1155,
 1155, 1155, 1155, 1155, 1155, 1155, 1155, 1155, 1155,    0,
    0,    0,    0,    0, 1155,    0, 1155,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0, 1155,    0,    0, 1155, 1155,    0,    0,
    0,    0,    0, 1155,    0,    0,    0,    0, 1155,    0,
 1155,    0, 1155,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, 1155,    0,    0,
 1155,    0, 1155,    0,    0,    0,    0, 1155,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 1155,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, 1155,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0, 1155,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0, 1155, 1155,    0,    0,    0,
 1155,    0,    0,    0,    0,    0,    0,    0,    0, 1155,
    0,    0,    0,    0,    0,    0, 1068, 1068, 1155, 1068,
    0, 1155,    0,    0,    0,    0,    0,    0, 1068, 1068,
 1155, 1068,    0,    0,    0, 1155, 1155, 1155,    0,    0,
    0,    0, 1155, 1155, 1155, 1232,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0, 1155, 1155, 1164, 1068,
    0,    0, 1068, 1068,    0,    0,    0, 1068, 1164, 1155,
    0,    0, 1068, 1155,    0,    0,    0,    0,    0,    0,
    0, 1068,    0,    0,    0,    0, 1068,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, 1068,    0,    0,    0,    0, 1068,    0, 1068,    0,
    0,    0,    0, 1068,    0, 1068, 1068, 1068,    0, 1068,
 1068, 1068,    0, 1068, 1068, 1068, 1068,    0, 1068, 1068,
 1068, 1068, 1068, 1068, 1068, 1068, 1068, 1068,    0,    0,
    0,    0,    0, 1068,    0, 1068,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, 1068,    0,    0, 1068, 1068,    0,    0,    0,
    0,    0, 1068,    0,    0,    0,    0, 1068,    0, 1068,
    0, 1068,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0, 1068,    0,    0, 1068,
    0, 1068,    0,    0,    0,    0, 1068,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, 1068,    0, 1068,
    0,    0,    0,    0,    0, 1068,    0,    0,    0,    0,
 1068,    0,    0,    0,    0, 1232,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, 1068,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0, 1068, 1068,    0,    0,    0, 1068,
    0, 1122, 1122,    0, 1122,    0,    0,    0, 1068,    0,
    0,    0,    0, 1122, 1122,    0, 1122, 1068,    0,    0,
 1068,    0,    0,    0,    0,    0,    0,    0,    0, 1068,
    0,    0,    0,    0, 1068, 1068, 1068,    0,    0,    0,
    0, 1068, 1068, 1068, 1122,    0,    0, 1122, 1122,    0,
    0,    0, 1122,    0,    0, 1068, 1068, 1122,    0,    0,
    0,    0,    0,    0,    0,    0, 1122,    0, 1068,    0,
    0, 1122, 1068,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0, 1122,    0,    0,    0,
    0, 1122,    0, 1122,    0,    0,    0,    0, 1122,    0,
 1122, 1122, 1122,    0, 1122, 1122, 1122,    0, 1122, 1122,
 1122, 1122,    0, 1122, 1122, 1122, 1122, 1122, 1122, 1122,
 1122, 1122, 1122,    0,    0,    0,    0,    0, 1122, 1122,
 1122,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, 1122,    0,    0,
 1122, 1122,    0,    0,    0,    0,    0, 1122,    0,    0,
    0,    0, 1122,    0, 1122,    0, 1122,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, 1122,    0,    0, 1122,    0, 1122,    0,    0,    0,
    0, 1122,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, 1122,    0, 1122,    0,    0,    0,    0,    0,
 1122,    0,    0,    0,    0, 1122,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, 1122,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0, 1122,
 1122,    0,    0,    0, 1122,    0,  904,  904,    0,  904,
    0,    0,    0, 1122,    0,    0,    0,    0,  904,  904,
    0,  904, 1122,    0,    0, 1122,    0,    0,    0,    0,
    0,    0,    0,    0, 1122,    0,    0,    0,  904, 1122,
 1122, 1122,    0,    0,    0,    0, 1122, 1122, 1122,  904,
    0,    0,  904,  904,    0,    0,    0,  904,    0,    0,
 1122, 1122,  904,    0,    0,    0,    0,    0,    0,    0,
    0,  904,    0, 1122,    0,    0,  904, 1122,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  904,    0,    0,    0,    0,  904,    0,  904,    0,
    0,    0,    0,  904,  904,  904,  904,  904,    0,  904,
  904,  904,    0,  904,  904,  904,  904,    0,  904,  904,
  904,  904,  904,  904,  904,  904,  904,  904,    0,    0,
    0,    0,    0,  904,    0,  904,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  904,    0,    0,  904,  904,    0,    0,    0,
    0,    0,  904,    0,    0,    0,    0,  904,    0,  904,
    0,  904,    0,    0,  904,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  904,    0,    0,  904,
    0,  904,    0,    0,    0,    0,  904,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  904,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  904,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  904,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  904,  904,    0,    0,    0,  904,
    0,  902,  902,    0,  902,    0,    0,    0,  904,    0,
    0,    0,    0,  902,  902,    0,  902,  904,    0,    0,
  904,    0,    0,    0,    0,    0,    0,    0,    0,  904,
    0,    0,    0,  902,  904,  904,  904,    0,    0,    0,
    0,  904,  904,  904,  902,    0,    0,  902,  902,    0,
    0,    0,  902,    0,    0,  904,  904,  902,    0,    0,
    0,    0,    0,    0,    0,    0,  902,    0,  904,    0,
    0,  902,  904,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  902,    0,    0,    0,
    0,  902,    0,  902,    0,    0,    0,    0,  902,  902,
  902,  902,  902,    0,  902,  902,  902,    0,  902,  902,
  902,  902,    0,  902,  902,  902,  902,  902,  902,  902,
  902,  902,  902,    0,    0,    0,    0,    0,  902,    0,
  902,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  902,    0,    0,
  902,  902,    0,    0,    0,    0,    0,  902,    0,    0,
    0,    0,  902,    0,  902,    0,  902,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  902,    0,    0,  902,    0,  902,    0,    0,    0,
    0,  902,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  902,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  902,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  902,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  902,
  902,    0,    0,    0,  902,    0,  991,  991,    0,  991,
    0,    0,    0,  902,    0,    0,    0,    0,  991,  991,
    0,  991,  902,    0,    0,  902,    0,    0,    0,    0,
    0,    0,    0,    0,  902,    0,    0,    0,    0,  902,
  902,  902,    0,    0,    0,    0,  902,  902,  902,  991,
    0,    0,  991,  991,    0,    0,    0,  991,    0,    0,
  902,  902,  991,    0,    0,    0,    0,    0,    0,    0,
    0,  991,    0,  902,    0,    0,  991,  902,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  991,    0,    0,    0,    0,  991,    0,  991,    0,
    0,    0,    0,  991,    0,  991,  991,  991,    0,  991,
  991,  991,    0,  991,  991,  991,  991,    0,  991,  991,
  991,  991,  991,  991,  991,  991,  991,  991,    0,    0,
    0,    0,    0,  991,    0,  991,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  991,    0,    0,  991,  991,    0,    0,    0,
    0,    0,  991,    0,    0,    0,    0,  991,    0,  991,
    0,  991,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  991,    0,    0,  991,
    0,  991,    0,    0,    0,    0,  991,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  991,    0,  991,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  991,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  991,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  991,  991,    0,    0,    0,  991,
    0, 1045, 1045,    0, 1045,    0,    0,    0,  991,    0,
    0,    0,    0, 1045, 1045,    0, 1045,  991,    0,  991,
  991,    0,    0,    0,    0,    0,    0,    0,    0,  991,
    0,    0,    0,    0,  991,  991,  991,    0,    0,    0,
    0,  991,  991,  991, 1045,    0,    0, 1045, 1045,    0,
    0,    0, 1045,    0,    0,  991,  991, 1045,    0,    0,
    0,    0,    0,    0,    0,    0, 1045,    0,  991,    0,
    0, 1045,  991,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0, 1045,    0,    0,    0,
    0, 1045,    0, 1045,    0,    0,    0,    0, 1045,    0,
 1045, 1045, 1045,    0, 1045, 1045, 1045,    0, 1045, 1045,
 1045, 1045,    0, 1045, 1045, 1045, 1045, 1045, 1045, 1045,
 1045, 1045, 1045,    0,    0,    0,    0,    0, 1045, 1234,
 1045,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, 1045,    0,    0,
 1045, 1045,    0,    0,    0,    0,    0, 1045,    0,    0,
    0,    0, 1045,    0, 1045,    0, 1045,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, 1045,    0,    0, 1045,    0, 1045,    0,    0,    0,
    0, 1045,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0, 1045,    0,    0,    0,    0,    0,
 1234,    0,    0,    0,    0, 1045,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, 1045,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0, 1045,
 1045,    0,    0,    0, 1045,    0, 1037, 1037,    0, 1037,
    0,    0,    0, 1045,    0,    0,    0,    0, 1037, 1037,
    0, 1037, 1045,    0,    0, 1045,    0,    0,    0,    0,
    0,    0,    0,    0, 1045,    0,    0,    0,    0, 1045,
 1045, 1045,    0,    0,    0,    0, 1045, 1045, 1045, 1037,
    0,    0, 1037, 1037,    0,    0,    0, 1037,    0,    0,
 1045, 1045, 1037,    0,    0,    0,    0,    0,    0,    0,
    0, 1037,    0, 1045,    0,    0, 1037, 1045,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, 1037,    0,    0,    0,    0, 1037,    0, 1037,    0,
    0,    0,    0, 1037,    0, 1037, 1037, 1037,    0, 1037,
 1037, 1037,    0, 1037, 1037, 1037, 1037,    0, 1037, 1037,
 1037, 1037, 1037, 1037, 1037, 1037, 1037, 1037,    0,    0,
    0,    0,    0, 1037,    0, 1037,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, 1037,    0,    0, 1037, 1037,    0,    0,    0,
    0,    0, 1037,    0,    0,    0,    0, 1037,    0, 1037,
    0, 1037,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0, 1037,    0,    0, 1037,
    0, 1037,    0,    0,    0,    0, 1037,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, 1037,    0, 1037,
    0,    0,    0,    0,    0, 1037,    0,    0,    0,    0,
 1037,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, 1037,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0, 1037, 1037,    0,    0,    0, 1037,
    0, 1162, 1162,    0, 1162,    0,    0,    0, 1037,    0,
    0,    0,    0, 1162, 1162,    0, 1162, 1037,    0,    0,
 1037,    0,    0,    0,    0,    0,    0,    0,    0, 1037,
    0,    0,    0,    0, 1037, 1037, 1037,    0,    0,    0,
    0, 1037, 1037, 1037, 1162,    0,    0, 1162, 1162,    0,
    0,    0, 1162,    0,    0, 1037, 1037, 1162,    0,    0,
    0,    0,    0,    0,    0,    0, 1162,    0, 1037,    0,
    0, 1162, 1037,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0, 1162,    0,    0,    0,
    0, 1162,    0, 1162,    0,    0,    0,    0, 1162,    0,
 1162, 1162, 1162,    0, 1162, 1162, 1162,    0, 1162, 1162,
 1162, 1162,    0, 1162, 1162, 1162, 1162, 1162, 1162, 1162,
 1162, 1162, 1162,    0,    0,    0,    0,    0, 1162,    0,
 1162,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, 1162, 1162,    0,
 1162, 1162,    0,    0,    0,    0,    0, 1162,    0,    0,
    0,    0, 1162,    0, 1162,    0, 1162,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, 1162,    0,    0, 1162,    0, 1162,    0,    0,    0,
    0, 1162,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0, 1162,    0,    0,    0,    0, 1162,
    0,    0,    0,    0,    0, 1162,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, 1162,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0, 1162,
 1162,    0,    0,    0, 1162,    0, 1222, 1222,    0, 1222,
    0,    0,    0, 1162,    0,    0,    0,    0, 1222, 1222,
    0, 1222, 1162,    0,    0, 1162,    0,    0,    0,    0,
    0,    0,    0,    0, 1162,    0,    0,    0,    0, 1162,
 1162, 1162,    0,    0,    0,    0, 1162, 1162, 1162, 1222,
    0,    0, 1222, 1222,    0,    0,    0, 1222,    0,    0,
 1162, 1162, 1222,    0,    0,    0,    0,    0,    0,    0,
    0, 1222,    0, 1162,    0,    0, 1222, 1162,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, 1222,    0,    0,    0,    0, 1222,    0, 1222,    0,
    0,    0,    0, 1222,    0, 1222, 1222, 1222,    0, 1222,
 1222, 1222,    0, 1222, 1222, 1222, 1222,    0, 1222, 1222,
 1222, 1222, 1222, 1222, 1222, 1222, 1222, 1222,    0,    0,
    0,    0,    0, 1222,    0, 1222,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, 1222,    0,    0, 1222, 1222,    0,    0,    0,
    0,    0, 1222,    0,    0,    0,    0, 1222,    0, 1222,
    0, 1222,    0,    0, 1222,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0, 1222,    0,    0, 1222,
    0, 1222,    0,    0,    0,    0, 1222,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0, 1222,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 1222,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, 1222,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0, 1222, 1222,    0,    0,    0, 1222,
    0, 1086, 1086,    0, 1086,    0,    0,    0, 1222,    0,
    0,    0,    0, 1086, 1086,    0, 1086, 1222,    0,    0,
 1222,    0,    0,    0,    0,    0,    0,    0,    0, 1222,
    0,    0,    0,    0, 1222, 1222, 1222,    0,    0,    0,
    0, 1222, 1222, 1222, 1086,    0,    0, 1086, 1086,    0,
    0,    0, 1086,    0,    0, 1222, 1222, 1086,    0,    0,
    0,    0,    0,    0,    0,    0, 1086,    0, 1222,    0,
    0, 1086, 1222,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0, 1086,    0,    0,    0,
    0, 1086,    0, 1086,    0,    0,    0,    0, 1086,    0,
 1086, 1086, 1086,    0, 1086, 1086, 1086,    0, 1086, 1086,
 1086, 1086,    0, 1086, 1086, 1086, 1086, 1086, 1086, 1086,
 1086, 1086, 1086,    0,    0,    0,    0,    0, 1086,    0,
 1086,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, 1086,    0,    0,
 1086, 1086,    0,    0,    0,    0,    0, 1086,    0,    0,
    0,    0, 1086,    0, 1086,    0, 1086,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, 1086,    0,    0, 1086,    0, 1086,    0,    0,    0,
    0, 1086,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0, 1086,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0, 1086,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, 1086,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0, 1086,    0,    0,    0,    0,    0, 1086,
 1086,    0,    0,    0, 1086,    0,  931,  931,    0,  931,
    0,    0,    0, 1086,    0,    0,    0,    0,  931,  931,
    0,  931, 1086,    0,    0, 1086,    0,    0,    0,    0,
    0,    0,    0,    0, 1086,    0,    0,    0,    0, 1086,
 1086, 1086,    0,    0,    0,    0, 1086, 1086, 1086,  931,
    0,    0,  931,  931,    0,    0,    0,  931,    0,    0,
 1086, 1086,  931,    0,    0,    0,    0,    0,    0,    0,
    0,  931,    0, 1086,    0,    0,  931, 1086,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  931,    0,    0,    0,    0,  931,    0,  931,    0,
    0,    0,    0,  931,    0,  931,  931,  931,    0,  931,
  931,  931,    0,  931,  931,  931,  931,    0,  931,  931,
  931,  931,  931,  931,  931,  931,  931,  931,    0,    0,
    0,    0,    0,  931,    0,  931,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  931,    0,    0,  931,  931,    0,    0,    0,
    0,    0,  931,    0,    0,    0,    0,  931,    0,  931,
    0,  931,    0,    0,  931,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  931,    0,    0,  931,
    0,  931,    0,    0,    0,    0,  931,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  931,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  931,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  931,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  931,  931,    0,    0,    0,  931,
    0,  948,  948,    0,  948,    0,    0,    0,  931,    0,
    0,    0,    0,  948,  948,    0,  948,  931,    0,    0,
  931,    0,    0,    0,    0,    0,    0,    0,    0,  931,
    0,    0,    0,    0,  931,  931,  931,    0,    0,    0,
    0,  931,  931,  931,  948,    0,    0,  948,  948,    0,
    0,    0,  948,    0,    0,  931,  931,  948,    0,    0,
    0,    0,    0,    0,    0,    0,  948,    0,  931,    0,
    0,  948,  931,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  948,    0,    0,    0,
    0,  948,    0,  948,    0,    0,    0,    0,  948,    0,
  948,  948,  948,    0,  948,  948,  948,    0,  948,  948,
  948,  948,    0,  948,  948,  948,  948,  948,  948,  948,
  948,  948,  948,    0,    0,    0,    0,    0,  948,    0,
  948,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  948,    0,    0,
  948,  948,    0,    0,    0,    0,    0,  948,    0,    0,
    0,    0,  948,    0,  948,    0,  948,    0,    0,  948,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  948,    0,    0,  948,    0,  948,    0,    0,    0,
    0,  948,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  948,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  948,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  948,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  948,
  948,    0,    0,    0,  948,    0,  933,  933,    0,  933,
    0,    0,    0,  948,    0,    0,    0,    0,  933,  933,
    0,  933,  948,    0,    0,  948,    0,    0,    0,    0,
    0,    0,    0,    0,  948,    0,    0,    0,    0,  948,
  948,  948,    0,    0,    0,    0,  948,  948,  948,  933,
    0,    0,  933,  933,    0,    0,    0,  933,    0,    0,
  948,  948,  933,    0,    0,    0,    0,    0,    0,    0,
    0,  933,    0,  948,    0,    0,  933,  948,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  933,    0,    0,    0,    0,  933,    0,  933,    0,
    0,    0,    0,  933,    0,  933,  933,  933,    0,  933,
  933,  933,    0,  933,  933,  933,  933,    0,  933,  933,
  933,  933,  933,  933,  933,  933,  933,  933,    0,    0,
    0,    0,    0,  933,    0,  933,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  933,    0,    0,  933,  933,    0,    0,    0,
    0,    0,  933,    0,    0,    0,    0,  933,    0,  933,
    0,  933,    0,    0,  933,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  933,    0,    0,  933,
    0,  933,    0,    0,    0,    0,  933,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  933,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  933,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  933,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  933,  933,    0,    0,    0,  933,
    0,  822,  822,    0,  822,    0,    0,    0,  933,    0,
    0,    0,    0,  822,  822,    0,  822,  933,    0,    0,
  933,    0,    0,    0,    0,    0,    0,    0,    0,  933,
    0,    0,    0,    0,  933,  933,  933,    0,    0,    0,
    0,  933,  933,  933,  822,    0,    0,  822,  822,    0,
    0,    0,  822,    0,    0,  933,  933,  822,    0,    0,
    0,    0,    0,    0,    0,    0,  822,    0,  933,    0,
    0,  822,  933,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  822,    0,    0,    0,
    0,  822,    0,  822,    0,    0,    0,    0,  822,    0,
  822,  822,  822,    0,  822,  822,  822,    0,  822,  822,
  822,  822,    0,  822,  822,  822,  822,  822,  822,  822,
  822,  822,  822,    0,    0,    0,    0,    0,  822, 1234,
  822,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  822,    0,    0,
  822,  822,    0,    0,    0,    0,    0,  822,    0,    0,
    0,    0,  822,    0,  822,    0,  822,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  822,    0,    0,  822,    0,  822,    0,    0,    0,
    0,  822,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  822,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  822,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  822,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  822,
  822,    0,    0,    0,  822,    0, 1085, 1085,    0, 1085,
    0,    0,    0,  822,    0,    0,    0,    0, 1085, 1085,
    0, 1085,  822,    0,    0,  822,    0,    0,    0,    0,
    0,    0,    0,    0,  822,    0,    0,    0,    0,  822,
  822,  822,    0,    0,    0,    0,  822,  822,  822, 1085,
    0,    0, 1085, 1085,    0,    0,    0, 1085,    0,    0,
  822,  822, 1085,    0,    0,    0,    0,    0,    0,    0,
    0, 1085,    0,  822,    0,    0, 1085,  822,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, 1085,    0,    0,    0,    0, 1085,    0, 1085,    0,
    0,    0,    0, 1085,    0, 1085, 1085, 1085,    0, 1085,
 1085, 1085,    0, 1085, 1085, 1085, 1085,    0, 1085, 1085,
 1085, 1085, 1085, 1085, 1085, 1085, 1085, 1085,    0,    0,
    0,    0,    0, 1085,    0, 1085,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, 1085,    0,    0, 1085, 1085,    0,    0,    0,
    0,    0, 1085,    0,    0,    0,    0, 1085,    0, 1085,
    0, 1085,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0, 1085,    0,    0, 1085,
    0, 1085,    0,    0,    0,    0, 1085,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0, 1085,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 1085,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, 1085,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0, 1085,    0,
    0,    0,    0,    0, 1085, 1085,    0,    0,    0, 1085,
    0,  219,  219,    0,  219,    0,    0,    0, 1085,    0,
    0,    0,    0,  219,  219,    0,  219, 1085,    0,    0,
 1085,    0,    0,    0,    0,    0,    0,    0,    0, 1085,
    0,    0,    0,    0, 1085, 1085, 1085,    0,    0,    0,
    0, 1085, 1085, 1085,  219,    0,    0,  219,  219,    0,
    0,    0,  219,    0,    0, 1085, 1085,  219,    0,    0,
    0,    0,    0,    0,    0,    0,  219,    0, 1085,    0,
    0,  219, 1085,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  219,    0,    0,    0,
    0,  219,    0,  219,    0,    0,    0,    0,  219,    0,
  219,  219,  219,    0,  219,  219,  219,    0,  219,  219,
  219,  219,    0,  219,  219,  219,  219,  219,  219,  219,
  219,  219,  219,    0,    0,    0,    0,    0,  219,    0,
  219,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  219,    0,    0,
  219,  219,    0,    0,    0,    0,    0,  219,    0,    0,
    0,    0,  219,    0,  219,    0,  219,    0,    0,  219,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  219,    0,    0,  219,    0,  219,    0,    0,    0,
    0,  219,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  219,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  219,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  219,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  219,
  219,    0,    0,    0,  219,    0, 1053, 1053,    0, 1053,
    0,    0,    0,  219,    0,    0,    0,    0, 1053, 1053,
    0, 1053,  219,    0,    0,  219,    0,    0,    0,    0,
    0,    0,    0,    0,  219,    0,    0,    0,    0,  219,
  219,  219,    0,    0,    0,    0,  219,  219,  219, 1053,
    0,    0, 1053, 1053,    0,    0,    0, 1053,    0,    0,
  219,  219, 1053,    0,    0,    0,    0,    0,    0,    0,
    0, 1053,    0,  219,    0,    0, 1053,  219,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, 1053,    0,    0,    0,    0, 1053,    0, 1053,    0,
    0,    0,    0, 1053,    0, 1053, 1053, 1053,    0, 1053,
 1053, 1053,    0, 1053, 1053, 1053, 1053,    0, 1053, 1053,
 1053, 1053, 1053, 1053, 1053, 1053, 1053, 1053,    0,    0,
    0,    0,    0, 1053,    0, 1053,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, 1053,    0,    0, 1053, 1053,    0,    0,    0,
    0,    0, 1053,    0,    0,    0,    0, 1053,    0, 1053,
    0, 1053,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0, 1053,    0,    0, 1053,
    0, 1053,    0,    0,    0,    0, 1053,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0, 1053,
    0,    0,    0,    0,    0, 1234,    0,    0,    0,    0,
 1053,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, 1053,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0, 1053, 1053,    0,    0,    0, 1053,
    0, 1160, 1160,    0, 1160,    0,    0,    0, 1053,    0,
    0,    0,    0, 1160, 1160,    0, 1160, 1053,    0, 1160,
 1053,    0,    0,    0,    0,    0,    0,    0,    0, 1053,
    0,    0,    0,    0, 1053, 1053, 1053,    0,    0,    0,
    0, 1053, 1053, 1053, 1160,    0,    0, 1160, 1160,    0,
    0,    0, 1160,    0,    0, 1053, 1053, 1160,    0,    0,
    0,    0,    0,    0,    0,    0, 1160,    0, 1053,    0,
    0, 1160, 1053,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0, 1160,    0,    0,    0,
    0, 1160,    0, 1160,    0,    0,    0,    0, 1160,    0,
 1160, 1160, 1160,    0, 1160, 1160, 1160,    0, 1160, 1160,
 1160, 1160,    0, 1160, 1160, 1160, 1160, 1160, 1160, 1160,
 1160, 1160, 1160,    0,    0,    0,    0,    0, 1160,    0,
 1160,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, 1160,    0,    0,
 1160, 1160,    0,    0,    0,    0,    0, 1160,    0,    0,
    0,    0, 1160,    0, 1160,    0, 1160,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, 1160,    0,    0, 1160,    0, 1160,    0,    0,    0,
    0, 1160,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0, 1160,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0, 1160,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, 1160,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0, 1160,
 1160,    0,    0,    0, 1160,    0, 1174, 1174,    0, 1174,
    0,    0,    0, 1160,    0,    0,    0,    0, 1174, 1174,
    0, 1174, 1160,    0, 1174, 1160,    0,    0,    0,    0,
    0,    0,    0,    0, 1160,    0,    0,    0,    0, 1160,
 1160, 1160,    0,    0,    0,    0, 1160, 1160, 1160, 1174,
    0,    0, 1174, 1174,    0,    0,    0, 1174,    0,    0,
 1160, 1160, 1174,    0,    0,    0,    0,    0,    0,    0,
    0, 1174,    0, 1160,    0,    0, 1174, 1160,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, 1174,    0,    0,    0,    0, 1174,    0, 1174,    0,
    0,    0,    0, 1174,    0, 1174, 1174, 1174,    0, 1174,
 1174, 1174,    0, 1174, 1174, 1174, 1174,    0, 1174, 1174,
 1174, 1174, 1174, 1174, 1174, 1174, 1174, 1174,    0,    0,
    0,    0,    0, 1174,    0, 1174,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, 1174,    0,    0, 1174, 1174,    0,    0,    0,
    0,    0, 1174,    0,    0,    0,    0, 1174,    0, 1174,
    0, 1174,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0, 1174,    0,    0, 1174,
    0, 1174,    0,    0,    0,    0, 1174,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0, 1174,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 1174,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, 1174,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0, 1174, 1174,    0,    0,    0, 1174,
    0,  895,  895,    0,  895,    0,    0,    0, 1174,    0,
    0,    0,    0,  895,  895,    0,  895, 1174,    0,    0,
 1174,    0,    0,    0,    0,    0,    0,    0,    0, 1174,
    0,    0,    0,    0, 1174, 1174, 1174,    0,    0,    0,
    0, 1174, 1174, 1174,  895,    0,    0,  895,  895,    0,
    0,    0,  895,    0,    0, 1174, 1174,  895,    0,    0,
    0,    0,    0,    0,    0,    0,  895,    0, 1174,    0,
    0,  895, 1174,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  895,    0,    0,    0,
    0,  895,    0,  895,    0,    0,    0,    0,  895,    0,
  895,  895,  895,    0,  895,  895,  895,    0,  895,  895,
  895,  895,    0,  895,  895,  895,  895,  895,  895,  895,
  895,  895,  895,    0,    0,    0,    0,    0,  895,    0,
  895,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  895,    0,    0,
  895,  895,    0,    0,    0,    0,    0,  895,    0,    0,
    0,    0,  895,    0,  895,    0,  895,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  895,    0,    0,  895,    0,  895,    0,    0,    0,
    0,  895,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  895,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  895,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  895,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  895,
  895,    0,    0,    0,  895,    0,  810,  810,    0,  810,
    0,    0,    0,  895,    0,    0,    0,    0,  810,  810,
    0,  810,  895,    0,    0,  895,    0,    0,    0,    0,
    0,    0,    0,    0,  895,    0,    0,    0,    0,  895,
  895,  895,    0,    0,    0,    0,  895,  895,  895,  810,
    0,    0,  810,  810,    0,    0,    0,  810,    0,    0,
  895,  895,  810,    0,    0,    0,    0,    0,    0,    0,
    0,  810,    0,  895,    0,    0,  810,  895,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  810,    0,    0,    0,    0,  810,    0,  810,    0,
    0,    0,    0,  810,    0,  810,  810,  810,    0,  810,
  810,  810,    0,  810,  810,  810,  810,    0,  810,  810,
  810,  810,  810,  810,  810,  810,  810,  810,    0,    0,
    0,    0,    0,  810,    0,  810,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  810,    0,    0,  810,  810,    0,    0,    0,
    0,    0,  810,    0,    0,    0,    0,  810,    0,  810,
    0,  810,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  810,    0,    0,  810,
    0,  810,    0,    0,    0,    0,  810,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  810,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  810,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  810,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  810,  810,    0,    0,    0,  810,
    0,  777,  777,    0,  777,    0,    0,    0,  810,    0,
    0,    0,    0,  777,  777,    0,  777,  810,    0,    0,
  810,    0,    0,    0,    0,    0,    0,    0,    0,  810,
    0,    0,    0,    0,  810,  810,  810,    0,    0,    0,
    0,  810,  810,  810,  777,    0,    0,  777,  777,    0,
    0,    0,  777,    0,    0,  810,  810,  777,    0,    0,
    0,    0,    0,    0,    0,    0,  777,    0,  810,    0,
    0,  777,  810,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  777,    0,    0,    0,
    0,  777,    0,  777,    0,    0,    0,    0,  777,    0,
  777,  777,  777,    0,  777,  777,  777,    0,  777,  777,
  777,  777,    0,  777,  777,  777,  777,  777,  777,  777,
  777,  777,  777,    0,    0,    0,    0,    0,  777,    0,
  777,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  777,    0,    0,
  777,  777,    0,    0,    0,    0,    0,  777,    0,    0,
    0,    0,  777,    0,  777,    0,  777,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  777,    0,    0,  777,    0,  777,    0,    0,    0,
    0,  777,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  777,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  777,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  777,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  777,
  777,    0,    0,    0,  777,    0,  970,  970,    0,  970,
    0,    0,    0,  777,    0,    0,    0,    0,  970,  970,
    0,  970,  777,    0,    0,  777,    0,    0,    0,    0,
    0,    0,    0,    0,  777,    0,    0,    0,    0,  777,
  777,  777,    0,    0,    0,    0,  777,  777,  777,  970,
    0,    0,  970,  970,    0,    0,    0,  970,    0,    0,
  777,  777,  970,    0,    0,    0,    0,    0,    0,    0,
    0,  970,    0,  777,    0,    0,  970,  777,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  970,    0,    0,    0,    0,  970,    0,  970,    0,
    0,    0,    0,  970,    0,  970,  970,  970,    0,  970,
  970,  970,    0,  970,  970,  970,  970,    0,  970,  970,
  970,  970,  970,  970,  970,  970,  970,  970,    0,    0,
    0,    0,    0,  970,    0,  970,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  970,    0,    0,  970,  970,    0,    0,    0,
    0,    0,  970,    0,    0,    0,    0,  970,    0,  970,
    0,  970,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  970,    0,    0,  970,
    0,  970,    0,    0,    0,    0,  970,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  970,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  970,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  970,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  970,  970,    0,    0,    0,  970,
    0,  876,  876,    0,  876,    0,    0,    0,  970,    0,
    0,    0,    0,  876,  876,    0,  876,  970,    0,    0,
  970,    0,    0,    0,    0,    0,    0,    0,    0,  970,
    0,    0,    0,    0,  970,  970,  970,    0,    0,    0,
    0,  970,  970,  970,  876,    0,    0,  876,  876,    0,
    0,    0,  876,    0,    0,  970,  970,  876,    0,    0,
    0,    0,    0,    0,    0,    0,  876,    0,  970,    0,
    0,  876,  970,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  876,    0,    0,    0,
    0,  876,    0,  876,    0,    0,    0,    0,  876,    0,
  876,  876,  876,    0,  876,  876,  876,    0,  876,  876,
  876,  876,    0,  876,  876,  876,  876,  876,  876,  876,
  876,  876,  876,    0,    0,    0,    0,    0,  876,    0,
  876,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  876,    0,    0,
  876,  876,    0,    0,    0,    0,    0,  876,    0,    0,
    0,    0,  876,    0,  876,    0,  876,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  876,    0,    0,  876,    0,  876,    0,    0,    0,
    0,  876,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  876,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  876,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  876,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  876,
  876,    0,    0,    0,  876,    0,  772,  772,    0,  772,
    0,    0,    0,  876,    0,    0,    0,    0,  772,  772,
    0,  772,  876,    0,    0,  876,    0,    0,    0,    0,
    0,    0,    0,    0,  876,    0,    0,    0,    0,  876,
  876,  876,    0,    0,    0,    0,  876,  876,  876,  772,
    0,    0,  772,  772,    0,    0,    0,  772,    0,    0,
  876,  876,  772,    0,    0,    0,    0,    0,    0,    0,
    0,  772,    0,  876,    0,    0,  772,  876,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  772,    0,    0,    0,    0,  772,    0,  772,    0,
    0,    0,    0,  772,    0,  772,  772,  772,    0,  772,
  772,  772,    0,  772,  772,  772,  772,    0,  772,  772,
  772,  772,  772,  772,  772,  772,  772,  772,    0,    0,
    0,    0,    0,  772,    0,  772,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  772,    0,    0,  772,  772,    0,    0,    0,
    0,    0,  772,    0,    0,    0,    0,  772,    0,  772,
    0,  772,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  772,    0,    0,  772,
    0,  772,    0,    0,    0,    0,  772,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  772,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  772,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  772,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  772,  772,    0,    0,    0,  772,
    0,  835,  835,    0,  835,    0,    0,    0,  772,    0,
    0,    0,    0,  835,  835,    0,  835,  772,    0,    0,
  772,    0,    0,    0,    0,    0,    0,    0,    0,  772,
    0,    0,    0,    0,  772,  772,  772,    0,    0,    0,
    0,  772,  772,  772,  835,    0,    0,  835,  835,    0,
    0,    0,  835,    0,    0,  772,  772,  835,    0,    0,
    0,    0,    0,    0,    0,    0,  835,    0,  772,    0,
    0,  835,  772,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  835,    0,    0,    0,
    0,  835,    0,  835,    0,    0,    0,    0,  835,    0,
  835,  835,  835,    0,  835,  835,  835,    0,  835,  835,
  835,  835,    0,  835,  835,  835,  835,  835,  835,  835,
  835,  835,  835,    0,    0,    0,    0,    0,  835,    0,
  835,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  835,    0,    0,
  835,  835,    0,    0,    0,    0,    0,  835,    0,    0,
    0,    0,  835,    0,  835,    0,  835,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  835,    0,    0,  835,    0,  835,    0,    0,    0,
    0,  835,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  835,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  835,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  835,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  835,
  835,    0,    0,    0,  835,    0,  799,  799,    0,  799,
    0,    0,    0,  835,    0,    0,    0,    0,  799,  799,
    0,  799,  835,    0,    0,  835,    0,    0,    0,    0,
    0,    0,    0,    0,  835,    0,    0,    0,    0,  835,
  835,  835,    0,    0,    0,    0,  835,  835,  835,  799,
    0,    0,  799,  799,    0,    0,    0,  799,    0,    0,
  835,  835,  799,    0,    0,    0,    0,    0,    0,    0,
    0,  799,    0,  835,    0,    0,  799,  835,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  799,    0,    0,    0,    0,  799,    0,  799,    0,
    0,    0,    0,  799,    0,  799,  799,  799,    0,  799,
  799,  799,    0,  799,  799,  799,  799,    0,  799,  799,
  799,  799,  799,  799,  799,  799,  799,  799,    0,    0,
    0,    0,    0,  799,    0,  799,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  799,    0,    0,  799,  799,    0,    0,    0,
    0,    0,  799,    0,    0,    0,    0,  799,    0,  799,
    0,  799,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  799,    0,    0,  799,
    0,  799,    0,    0,    0,    0,  799,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  799,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  799,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  799,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  799,  799,    0,    0,    0,  799,
    0,  979,  979,    0,  979,    0,    0,    0,  799,    0,
    0,    0,    0,  979,  979,    0,  979,  799,    0,    0,
  799,    0,    0,    0,    0,    0,    0,    0,    0,  799,
    0,    0,    0,    0,  799,  799,  799,    0,    0,    0,
    0,  799,  799,  799,  979,    0,    0,  979,  979,    0,
    0,    0,  979,    0,    0,  799,  799,  979,    0,    0,
    0,    0,    0,    0,    0,    0,  979,    0,  799,    0,
    0,  979,  799,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  979,    0,    0,    0,
    0,  979,    0,  979,    0,    0,    0,    0,  979,    0,
  979,  979,  979,    0,  979,  979,  979,    0,  979,  979,
  979,  979,    0,  979,  979,  979,  979,  979,  979,  979,
  979,  979,  979,    0,    0,    0,    0,    0,  979,    0,
  979,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  979,    0,    0,
  979,  979,    0,    0,    0,    0,    0,  979,    0,    0,
    0,    0,  979,    0,  979,    0,  979,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  979,    0,    0,  979,    0,  979,    0,    0,    0,
    0,  979,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  979,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  979,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  979,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  979,
  979,    0,    0,    0,  979,    0,  760,  760,    0,  760,
    0,    0,    0,  979,    0,    0,    0,    0,  760,  760,
    0,  760,  979,    0,    0,  979,    0,    0,    0,    0,
    0,    0,    0,    0,  979,    0,    0,    0,    0,  979,
  979,  979,    0,    0,    0,    0,  979,  979,  979,  760,
    0,    0,  760,  760,    0,    0,    0,  760,    0,    0,
  979,  979,  760,    0,    0,    0,    0,    0,    0,    0,
    0,  760,    0,  979,    0,    0,  760,  979,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  760,    0,    0,    0,    0,  760,    0,  760,    0,
    0,    0,    0,  760,    0,  760,  760,  760,    0,  760,
  760,  760,    0,  760,  760,  760,  760,    0,  760,  760,
  760,  760,  760,  760,  760,  760,  760,  760,    0,    0,
    0,    0,    0,  760,    0,  760,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  760,    0,    0,  760,  760,    0,    0,    0,
    0,    0,  760,    0,    0,    0,    0,  760,    0,  760,
    0,  760,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  760,    0,    0,  760,
    0,  760,    0,    0,    0,    0,  760,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  760,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  760,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  760,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  760,  760,    0,    0,    0,  760,
    0,  793,  793,    0,  793,    0,    0,    0,  760,    0,
    0,    0,    0,  793,  793,    0,  793,  760,    0,    0,
  760,    0,    0,    0,    0,    0,    0,    0,    0,  760,
    0,    0,    0,    0,  760,  760,  760,    0,    0,    0,
    0,  760,  760,  760,  793,    0,    0,  793,  793,    0,
    0,    0,  793,    0,    0,  760,  760,  793,    0,    0,
    0,    0,    0,    0,    0,    0,  793,    0,  760,    0,
    0,  793,  760,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  793,    0,    0,    0,
    0,  793,    0,  793,    0,    0,    0,    0,  793,    0,
  793,  793,  793,    0,  793,  793,  793,    0,  793,  793,
  793,  793,    0,  793,  793,  793,  793,  793,  793,  793,
  793,  793,  793,    0,    0,    0,    0,    0,  793,    0,
  793,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  793,    0,    0,
  793,  793,    0,    0,    0,    0,    0,  793,    0,    0,
    0,    0,  793,    0,  793,    0,  793,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  793,    0,    0,  793,    0,  793,    0,    0,    0,
    0,  793,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  793,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  793,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  793,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  793,
  793,    0,    0,    0,  793,    0,  865,  865,    0,  865,
    0,    0,    0,  793,    0,    0,    0,    0,  865,  865,
    0,  865,  793,    0,    0,  793,    0,    0,    0,    0,
    0,    0,    0,    0,  793,    0,    0,    0,    0,  793,
  793,  793,    0,    0,    0,    0,  793,  793,  793,  865,
    0,    0,  865,  865,    0,    0,    0,  865,    0,    0,
  793,  793,  865,    0,    0,    0,    0,    0,    0,    0,
    0,  865,    0,  793,    0,    0,  865,  793,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  865,    0,    0,    0,    0,  865,    0,  865,    0,
    0,    0,    0,  865,    0,  865,  865,  865,    0,  865,
  865,  865,    0,  865,  865,  865,  865,    0,  865,  865,
  865,  865,  865,  865,  865,  865,  865,  865,    0,    0,
    0,    0,    0,  865,    0,  865,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  865,    0,    0,  865,  865,    0,    0,    0,
    0,    0,  865,    0,    0,    0,    0,  865,    0,  865,
    0,  865,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  865,    0,    0,  865,
    0,  865,    0,    0,    0,    0,  865,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  865,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  865,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  865,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  865,  865,    0,    0,    0,  865,
    0,  891,  891,    0,  891,    0,    0,    0,  865,    0,
    0,    0,    0,  891,  891,    0,  891,  865,    0,    0,
  865,    0,    0,    0,    0,    0,    0,    0,    0,  865,
    0,    0,    0,    0,  865,  865,  865,    0,    0,    0,
    0,  865,  865,  865,  891,    0,    0,  891,  891,    0,
    0,    0,  891,    0,    0,  865,  865,  891,    0,    0,
    0,    0,    0,    0,    0,    0,  891,    0,  865,    0,
    0,  891,  865,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  891,    0,    0,    0,
    0,  891,    0,  891,    0,    0,    0,    0,  891,    0,
  891,  891,  891,    0,  891,  891,  891,    0,  891,  891,
  891,  891,    0,  891,  891,  891,  891,  891,  891,  891,
  891,  891,  891,    0,    0,    0,    0,    0,  891,    0,
  891,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  891,    0,    0,
  891,  891,    0,    0,    0,    0,    0,  891,    0,    0,
    0,    0,  891,    0,  891,    0,  891,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  891,    0,    0,  891,    0,  891,    0,    0,    0,
    0,  891,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  891,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  891,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  891,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  891,
  891,    0,    0,    0,  891,    0,  786,  786,    0,  786,
    0,    0,    0,  891,    0,    0,    0,    0,  786,  786,
    0,  786,  891,    0,    0,  891,    0,    0,    0,    0,
    0,    0,    0,    0,  891,    0,    0,    0,    0,  891,
  891,  891,    0,    0,    0,    0,  891,  891,  891,  786,
    0,    0,  786,  786,    0,    0,    0,  786,    0,    0,
  891,  891,  786,    0,    0,    0,    0,    0,    0,    0,
    0,  786,    0,  891,    0,    0,  786,  891,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  786,    0,    0,    0,    0,  786,    0,  786,    0,
    0,    0,    0,  786,    0,  786,  786,  786,    0,  786,
  786,  786,    0,  786,  786,  786,  786,    0,  786,  786,
  786,  786,  786,  786,  786,  786,  786,  786,    0,    0,
    0,    0,    0,  786,    0,  786,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  786,    0,    0,  786,  786,    0,    0,    0,
    0,    0,  786,    0,    0,    0,    0,  786,    0,  786,
    0,  786,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  786,    0,    0,  786,
    0,  786,    0,    0,    0,    0,  786,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  786,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  786,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  786,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  786,  786,    0,    0,    0,  786,
    0,  927,  927,    0,  927,    0,    0,    0,  786,    0,
    0,    0,    0,  927,  927,    0,  927,  786,    0,    0,
  786,    0,    0,    0,    0,    0,    0,    0,    0,  786,
    0,    0,    0,    0,  786,  786,  786,    0,    0,    0,
    0,  786,  786,  786,  927,    0,    0,  927,  927,    0,
    0,    0,  927,    0,    0,  786,  786,  927,    0,    0,
    0,    0,    0,    0,    0,    0,  927,    0,  786,    0,
    0,  927,  786,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  927,    0,    0,    0,
    0,  927,    0,  927,    0,    0,    0,    0,  927,    0,
  927,  927,  927,    0,  927,  927,  927,    0,  927,  927,
  927,  927,    0,  927,  927,  927,  927,  927,  927,  927,
  927,  927,  927,    0,    0,    0,    0,    0,  927,    0,
  927,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  927,    0,    0,
  927,  927,    0,    0,    0,    0,    0,  927,    0,    0,
    0,    0,  927,    0,  927,    0,  927,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  927,    0,    0,  927,    0,  927,    0,    0,    0,
    0,  927,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  927,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  927,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  927,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  927,
  927,    0,    0,    0,  927,    0,  736,  736,    0,  736,
    0,    0,    0,  927,    0,    0,    0,    0,  736,  736,
    0,  736,  927,    0,    0,  927,    0,    0,    0,    0,
    0,    0,    0,    0,  927,    0,    0,    0,    0,  927,
  927,  927,    0,    0,    0,    0,  927,  927,  927,  736,
    0,    0,  736,  736,    0,    0,    0,  736,    0,    0,
  927,  927,  736,    0,    0,    0,    0,    0,    0,    0,
    0,  736,    0,  927,    0,    0,  736,  927,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  736,    0,    0,    0,    0,  736,    0,  736,    0,
    0,    0,    0,  736,    0,  736,  736,  736,    0,  736,
  736,  736,    0,  736,  736,  736,  736,    0,  736,  736,
  736,  736,  736,  736,  736,  736,  736,  736,    0,    0,
    0,    0,    0,  736,    0,  736,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  736,    0,    0,  736,  736,    0,    0,    0,
    0,    0,  736,    0,    0,    0,    0,  736,    0,  736,
    0,  736,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  736,    0,    0,  736,
    0,  736,    0,    0,    0,    0,  736,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  736,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  736,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  736,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  736,  736,    0,    0,    0,  736,
    0,  864,  864,    0,  864,    0,    0,    0,  736,    0,
    0,    0,    0,  864,  864,    0,  864,  736,    0,    0,
  736,    0,    0,    0,    0,    0,    0,    0,    0,  736,
    0,    0,    0,    0,  736,  736,  736,    0,    0,    0,
    0,  736,  736,  736,  864,    0,    0,  864,  864,    0,
    0,    0,  864,    0,    0,  736,  736,  864,    0,    0,
    0,    0,    0,    0,    0,    0,  864,    0,  736,    0,
    0,  864,  736,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  864,    0,    0,    0,
    0,  864,    0,  864,    0,    0,    0,    0,  864,    0,
  864,  864,  864,    0,  864,  864,  864,    0,  864,  864,
  864,  864,    0,  864,  864,  864,  864,  864,  864,  864,
  864,  864,  864,    0,    0,    0,    0,    0,  864,    0,
  864,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  864,    0,    0,
  864,  864,    0,    0,    0,    0,    0,  864,    0,    0,
    0,    0,  864,    0,  864,    0,  864,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  864,    0,    0,  864,    0,  864,    0,    0,    0,
    0,  864,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  864,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  864,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  864,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  864,
  864,    0,    0,    0,  864,    0,  972,  972,    0,  972,
    0,    0,    0,  864,    0,    0,    0,    0,  972,  972,
    0,  972,  864,    0,    0,  864,    0,    0,    0,    0,
    0,    0,    0,    0,  864,    0,    0,    0,    0,  864,
  864,  864,    0,    0,    0,    0,  864,  864,  864,  972,
    0,    0,  972,  972,    0,    0,    0,  972,    0,    0,
  864,  864,  972,    0,    0,    0,    0,    0,    0,    0,
    0,  972,    0,  864,    0,    0,  972,  864,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  972,    0,    0,    0,    0,  972,    0,  972,    0,
    0,    0,    0,  972,    0,  972,  972,  972,    0,  972,
  972,  972,    0,  972,  972,  972,  972,    0,  972,  972,
  972,  972,  972,  972,  972,  972,  972,  972,    0,    0,
    0,    0,    0,  972,    0,  972,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  972,    0,    0,  972,  972,    0,    0,    0,
    0,    0,  972,    0,    0,    0,    0,  972,    0,  972,
    0,  972,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  972,    0,    0,  972,
    0,  972,    0,    0,    0,    0,  972,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  972,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  972,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  972,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  972,  972,    0,    0,    0,  972,
    0,  758,  758,    0,  758,    0,    0,    0,  972,    0,
    0,    0,    0,  758,  758,    0,  758,  972,    0,    0,
  972,    0,    0,    0,    0,    0,    0,    0,    0,  972,
    0,    0,    0,    0,  972,  972,  972,    0,    0,    0,
    0,  972,  972,  972,  758,    0,    0,  758,  758,    0,
    0,    0,  758,    0,    0,  972,  972,  758,    0,    0,
    0,    0,    0,    0,    0,    0,  758,    0,  972,    0,
    0,  758,  972,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  758,    0,    0,    0,
    0,  758,    0,  758,    0,    0,    0,    0,  758,    0,
  758,  758,  758,    0,  758,  758,  758,    0,  758,  758,
  758,  758,    0,  758,  758,  758,  758,  758,  758,  758,
  758,  758,  758,    0,    0,    0,    0,    0,  758,    0,
  758,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  758,    0,    0,
  758,  758,    0,    0,    0,    0,    0,  758,    0,    0,
    0,    0,  758,    0,  758,    0,  758,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  758,    0,    0,  758,    0,  758,    0,    0,    0,
    0,  758,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  758,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  758,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  758,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  758,
  758,    0,    0,    0,  758,    0,  993,  993,    0,  993,
    0,    0,    0,  758,    0,    0,    0,    0,    0,  993,
    0,  993,  758,    0,    0,  758,    0,    0,    0,    0,
    0,    0,    0,    0,  758,    0,    0,    0,    0,  758,
  758,  758,    0,    0,    0,    0,  758,  758,  758,  993,
    0,    0,  993,  993,    0,    0,    0,  993,    0,    0,
  758,  758,  993,    0,    0,    0,    0,    0,    0,    0,
    0,  993,    0,  758,    0,    0,  993,  758,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  993,    0,    0,    0,    0,  993,    0,  993,    0,
    0,    0,    0,  993,    0,  993,  993,  993,    0,  993,
  993,  993,    0,  993,  993,  993,  993,    0,  993,  993,
  993,  993,  993,  993,  993,  993,  993,  993,    0,    0,
    0,    0,    0,  993,    0,  993,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  993,    0,    0,  993,  993,    0,    0,    0,
    0,    0,  993,    0,    0,    0,    0,  993,    0,  993,
    0,  993,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  993,    0,    0,  993,
    0,  993,    0,    0,    0,    0,  993,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  993,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  993,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  993,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  993,  993,    0,    0,    0,  993,
    0,  762,  762,    0,  762,    0,    0,    0,  993,    0,
    0,    0,    0,  762,  762,    0,  762,  993,    0, 1234,
  993,    0,    0,    0,    0,    0,    0,    0,    0,  993,
    0,    0,    0,    0,  993,  993,  993,    0,    0,    0,
    0,  993,  993,  993,  762,    0,    0,  762,  762,    0,
    0,    0,  762,    0,    0,  993,  993,  762,    0,    0,
    0,    0,    0,    0,    0,    0,  762,    0,  993,    0,
    0,  762,  993,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  762,    0,    0,    0,
    0,  762,    0,  762,    0,    0,    0,    0,  762,    0,
  762,  762,  762,    0,  762,  762,  762,    0,  762,  762,
  762,  762,    0,  762,  762,  762,  762,  762,  762,  762,
  762,  762,  762,    0,    0,    0,    0,    0,  762,    0,
  762,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  762,    0,    0,
  762,  762,    0,    0,    0,    0,    0,  762,    0,    0,
    0,    0,  762,    0,  762,    0,  762,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  762,    0,    0,  762,    0,  762,    0,    0,    0,
    0,  762,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  762,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  762,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  762,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  762,
  762,    0,    0,    0,  762,    0, 1094, 1094,    0, 1094,
    0,    0,    0,  762,    0,    0,    0,    0, 1094, 1094,
    0, 1094,  762,    0,    0,  762,    0,    0,    0,    0,
    0,    0,    0,    0,  762,    0,    0,    0,    0,  762,
  762,  762,    0,    0,    0,    0,  762,  762,  762, 1094,
    0,    0, 1094, 1094,    0,    0,    0, 1094,    0,    0,
  762,  762, 1094,    0,    0,    0,    0,    0,    0,    0,
    0, 1094,    0,  762,    0,    0, 1094,  762,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, 1094,    0,    0,    0,    0, 1094,    0, 1094,    0,
    0,    0,    0, 1094,    0, 1094, 1094, 1094,    0, 1094,
 1094, 1094,    0, 1094, 1094, 1094, 1094,    0, 1094, 1094,
 1094, 1094, 1094, 1094, 1094, 1094, 1094, 1094,    0,    0,
    0,    0,    0, 1094,    0, 1094,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, 1094,    0,    0, 1094, 1094,    0,    0,    0,
    0,    0, 1094,    0,    0,    0,    0, 1094,    0, 1094,
    0, 1094,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0, 1094,    0,    0, 1094,
    0, 1094,    0,    0,    0,    0, 1094,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0, 1094,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 1094,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, 1094,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0, 1094, 1094,    0,    0,    0, 1094,
    0, 1093, 1093,    0, 1093,    0,    0,    0, 1094,    0,
    0,    0,    0, 1093, 1093,    0, 1093, 1094,    0,    0,
 1094,    0,    0,    0,    0,    0,    0,    0,    0, 1094,
    0,    0,    0,    0, 1094, 1094, 1094,    0,    0,    0,
    0, 1094, 1094, 1094, 1093,    0,    0, 1093, 1093,    0,
    0,    0, 1093,    0,    0, 1094, 1094, 1093,    0,    0,
    0,    0,    0,    0,    0,    0, 1093,    0, 1094,    0,
    0, 1093, 1094,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0, 1093,    0,    0,    0,
    0, 1093,    0, 1093,    0,    0,    0,    0, 1093,    0,
 1093, 1093, 1093,    0, 1093, 1093, 1093,    0, 1093, 1093,
 1093, 1093,    0, 1093, 1093, 1093, 1093, 1093, 1093, 1093,
 1093, 1093, 1093,    0,    0,    0,    0,    0, 1093,    0,
 1093,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, 1093,    0,    0,
 1093, 1093,    0,    0,    0,    0,    0, 1093,    0,    0,
    0,    0, 1093,    0, 1093,    0, 1093,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, 1093,    0,    0, 1093,    0, 1093,    0,    0,    0,
    0, 1093,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0, 1093,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0, 1093,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, 1093,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0, 1093,
 1093,    0,    0,    0, 1093,    0, 1084, 1084,    0, 1084,
    0,    0,    0, 1093,    0,    0,    0,    0, 1084, 1084,
    0, 1084, 1093,    0,    0, 1093,    0,    0,    0,    0,
    0,    0,    0,    0, 1093,    0,    0,    0,    0, 1093,
 1093, 1093,    0,    0,    0,    0, 1093, 1093, 1093, 1084,
    0,    0, 1084, 1084,    0,    0,    0, 1084,    0,    0,
 1093, 1093, 1084,    0,    0,    0,    0,    0,    0,    0,
    0, 1084,    0, 1093,    0,    0, 1084, 1093,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, 1084,    0,    0,    0,    0, 1084,    0, 1084,    0,
    0,    0,    0, 1084,    0, 1084, 1084, 1084,    0, 1084,
 1084, 1084,    0, 1084, 1084, 1084, 1084,    0, 1084, 1084,
 1084, 1084, 1084, 1084, 1084, 1084, 1084, 1084,    0,    0,
    0,    0,    0, 1084,    0, 1084,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, 1084,    0,    0, 1084, 1084,    0,    0,    0,
    0,    0, 1084,    0,    0,    0,    0, 1084,    0, 1084,
    0, 1084,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0, 1084,    0,    0, 1084,
    0, 1084,    0,    0,    0,    0, 1084,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0, 1084,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 1084,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, 1084,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0, 1084, 1084,    0,    0,    0, 1084,
    0,  752,  752,    0,  752,    0,    0,    0, 1084,    0,
    0,    0,    0,  752,  752,    0,  752, 1084,    0,    0,
 1084,    0,    0,    0,    0,    0,    0,    0,    0, 1084,
    0,    0,    0,    0, 1084, 1084, 1084,    0,    0,    0,
    0, 1084, 1084, 1084,  752,    0,    0,  752,  752,    0,
    0,    0,  752,    0,    0, 1084, 1084,  752,    0,    0,
    0,    0,    0,    0,    0,    0,  752,    0, 1084,    0,
    0,  752, 1084,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  752,    0,    0,    0,
    0,  752,    0,  752,    0,    0,    0,    0,  752,    0,
  752,  752,  752,    0,  752,  752,  752,    0,  752,  752,
  752,  752,    0,  752,  752,  752,  752,  752,  752,  752,
  752,  752,  752,    0,    0,    0,    0,    0,  752,    0,
  752,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  752,    0,    0,
  752,  752,    0,    0,    0,    0,    0,  752,    0,    0,
    0,    0,  752,    0,  752,    0,  752,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  752,    0,    0,  752,    0,  752,    0,    0,    0,
    0,  752,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  752,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  752,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  752,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  752,
  752,    0,    0,    0,  752,    0, 1157, 1157,    0, 1157,
    0,    0,    0,  752,    0,    0,    0,    0, 1157, 1157,
    0, 1157,  752,    0,    0,  752,    0,    0,    0,    0,
    0,    0,    0,    0,  752,    0,    0,    0,    0,  752,
  752,  752,    0,    0,    0,    0,  752,  752,  752, 1157,
    0,    0, 1157, 1157,    0,    0,    0, 1157,    0,    0,
  752,  752, 1157,    0,    0,    0,    0,    0,    0,    0,
    0, 1157,    0,  752,    0,    0, 1157,  752,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, 1157,    0,    0,    0,    0, 1157,    0, 1157,    0,
    0,    0,    0, 1157,    0, 1157, 1157, 1157,    0, 1157,
 1157, 1157,    0, 1157, 1157, 1157, 1157,    0, 1157, 1157,
 1157, 1157, 1157, 1157, 1157, 1157, 1157, 1157,    0,    0,
    0,    0,    0, 1157,    0, 1157,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, 1157,    0,    0, 1157, 1157,    0,    0,    0,
    0,    0, 1157,    0,    0,    0,    0, 1157,    0, 1157,
    0, 1157,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0, 1157,    0,    0, 1157,
    0, 1157,    0,    0,    0,    0, 1157,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0, 1157,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 1157,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, 1157,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0, 1157, 1157,    0,    0,    0, 1157,
    0, 1166, 1166,    0, 1166,    0,    0,    0, 1157,    0,
    0,    0,    0, 1166, 1166,    0, 1166, 1157,    0,    0,
 1157,    0,    0,    0,    0,    0,    0,    0,    0, 1157,
    0,    0,    0,    0, 1157, 1157, 1157,    0,    0,    0,
    0, 1157, 1157, 1157, 1166,    0,    0, 1166, 1166,    0,
    0,    0, 1166,    0,    0, 1157, 1157, 1166,    0,    0,
    0,    0,    0,    0,    0,    0, 1166,    0, 1157,    0,
    0, 1166, 1157,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0, 1166,    0,    0,    0,
    0, 1166,    0, 1166,    0,    0,    0,    0, 1166,    0,
 1166, 1166, 1166,    0, 1166, 1166, 1166,    0, 1166, 1166,
 1166, 1166,    0, 1166, 1166, 1166, 1166, 1166, 1166, 1166,
 1166, 1166, 1166,    0,    0,    0,    0,    0, 1166,    0,
 1166,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, 1166,    0,    0,
 1166, 1166,    0,    0,    0,    0,    0, 1166,    0,    0,
    0,    0, 1166,    0, 1166,    0, 1166,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, 1166,    0,    0, 1166,    0, 1166,    0,    0,    0,
    0, 1166,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0, 1166,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0, 1166,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, 1166,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0, 1166,
 1166,    0,    0,    0, 1166,    0, 1167, 1167,    0, 1167,
    0,    0,    0, 1166,    0,    0,    0,    0, 1167, 1167,
    0, 1167, 1166,    0,    0, 1166,    0,    0,    0,    0,
    0,    0,    0,    0, 1166,    0,    0,    0,    0, 1166,
 1166, 1166,    0,    0,    0,    0, 1166, 1166, 1166, 1167,
    0,    0, 1167, 1167,    0,    0,    0, 1167,    0,    0,
 1166, 1166, 1167,    0,    0,    0,    0,    0,    0,    0,
    0, 1167,    0, 1166,    0,    0, 1167, 1166,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, 1167,    0,    0,    0,    0, 1167,    0, 1167,    0,
    0,    0,    0, 1167,    0, 1167, 1167, 1167,    0, 1167,
 1167, 1167,    0, 1167, 1167, 1167, 1167,    0, 1167, 1167,
 1167, 1167, 1167, 1167, 1167, 1167, 1167, 1167,    0,    0,
    0,    0,    0, 1167,    0, 1167,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, 1167,    0,    0, 1167, 1167,    0,    0,    0,
    0,    0, 1167,    0,    0,    0,    0, 1167,    0, 1167,
    0, 1167,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0, 1167,    0,    0, 1167,
    0, 1167,    0,    0,    0,    0, 1167,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0, 1167,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 1167,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, 1167,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0, 1167, 1167,    0,    0,    0, 1167,
    0, 1168, 1168,    0, 1168,    0,    0,    0, 1167,    0,
    0,    0,    0, 1168, 1168,    0, 1168, 1167,    0,    0,
 1167,    0,    0,    0,    0,    0,    0,    0,    0, 1167,
    0,    0,    0,    0, 1167, 1167, 1167,    0,    0,    0,
    0, 1167, 1167, 1167, 1168,    0,    0, 1168, 1168,    0,
    0,    0, 1168,    0,    0, 1167, 1167, 1168,    0,    0,
    0,    0,    0,    0,    0,    0, 1168,    0, 1167,    0,
    0, 1168, 1167,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0, 1168,    0,    0,    0,
    0, 1168,    0, 1168,    0,    0,    0,    0, 1168,    0,
 1168, 1168, 1168,    0, 1168, 1168, 1168,    0, 1168, 1168,
 1168, 1168,    0, 1168, 1168, 1168, 1168, 1168, 1168, 1168,
 1168, 1168, 1168,    0,    0,    0,    0,    0, 1168,    0,
 1168,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, 1168,    0,    0,
 1168, 1168,    0,    0,    0,    0,    0, 1168,    0,    0,
    0,    0, 1168,    0, 1168,    0, 1168,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, 1168,    0,    0, 1168,    0, 1168,    0,    0,    0,
    0, 1168,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0, 1168,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0, 1168,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, 1168,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0, 1168,
 1168,    0,    0,    0, 1168,    0, 1169, 1169,    0, 1169,
    0,    0,    0, 1168,    0,    0,    0,    0, 1169, 1169,
    0, 1169, 1168,    0,    0, 1168,    0,    0,    0,    0,
    0,    0,    0,    0, 1168,    0,    0,    0,    0, 1168,
 1168, 1168,    0,    0,    0,    0, 1168, 1168, 1168, 1169,
    0,    0, 1169, 1169,    0,    0,    0, 1169,    0,    0,
 1168, 1168, 1169,    0,    0,    0,    0,    0,    0,    0,
    0, 1169,    0, 1168,    0,    0, 1169, 1168,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, 1169,    0,    0,    0,    0, 1169,    0, 1169,    0,
    0,    0,    0, 1169,    0, 1169, 1169, 1169,    0, 1169,
 1169, 1169,    0, 1169, 1169, 1169, 1169,    0, 1169, 1169,
 1169, 1169, 1169, 1169, 1169, 1169, 1169, 1169,    0,    0,
    0,    0,    0, 1169,    0, 1169,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, 1169,    0,    0, 1169, 1169,    0,    0,    0,
    0,    0, 1169,    0,    0,    0,    0, 1169,    0, 1169,
    0, 1169,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0, 1169,    0,    0, 1169,
    0, 1169,    0,    0,    0,    0, 1169,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0, 1169,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 1169,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, 1169,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0, 1169, 1169,    0,    0,    0, 1169,
    0, 1170, 1170,    0, 1170,    0,    0,    0, 1169,    0,
    0,    0,    0, 1170, 1170,    0, 1170, 1169,    0,    0,
 1169,    0,    0,    0,    0,    0,    0,    0,    0, 1169,
    0,    0,    0,    0, 1169, 1169, 1169,    0,    0,    0,
    0, 1169, 1169, 1169, 1170,    0,    0, 1170, 1170,    0,
    0,    0, 1170,    0,    0, 1169, 1169, 1170,    0,    0,
    0,    0,    0,    0,    0,    0, 1170,    0, 1169,    0,
    0, 1170, 1169,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0, 1170,    0,    0,    0,
    0, 1170,    0, 1170,    0,    0,    0,    0, 1170,    0,
 1170, 1170, 1170,    0, 1170, 1170, 1170,    0, 1170, 1170,
 1170, 1170,    0, 1170, 1170, 1170, 1170, 1170, 1170, 1170,
 1170, 1170, 1170,    0,    0,    0,    0,    0, 1170,    0,
 1170,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, 1170,    0,    0,
 1170, 1170,    0,    0,    0,    0,    0, 1170,    0,    0,
    0,    0, 1170,    0, 1170,    0, 1170,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, 1170,    0,    0, 1170,    0, 1170,    0,    0,    0,
    0, 1170,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0, 1170,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0, 1170,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, 1170,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0, 1170,
 1170,    0,    0,    0, 1170,    0, 1171, 1171,    0, 1171,
    0,    0,    0, 1170,    0,    0,    0,    0, 1171, 1171,
    0, 1171, 1170,    0,    0, 1170,    0,    0,    0,    0,
    0,    0,    0,    0, 1170,    0,    0,    0,    0, 1170,
 1170, 1170,    0,    0,    0,    0, 1170, 1170, 1170, 1171,
    0,    0, 1171, 1171,    0,    0,    0, 1171,    0,    0,
 1170, 1170, 1171,    0,    0,    0,    0,    0,    0,    0,
    0, 1171,    0, 1170,    0,    0, 1171, 1170,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, 1171,    0,    0,    0,    0, 1171,    0, 1171,    0,
    0,    0,    0, 1171,    0, 1171, 1171, 1171,    0, 1171,
 1171, 1171,    0, 1171, 1171, 1171, 1171,    0, 1171, 1171,
 1171, 1171, 1171, 1171, 1171, 1171, 1171, 1171,    0,    0,
    0,    0,    0, 1171,    0, 1171,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, 1171,    0,    0, 1171, 1171,    0,    0,    0,
    0,    0, 1171,    0,    0,    0,    0, 1171,    0, 1171,
    0, 1171,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0, 1171,    0,    0, 1171,
    0, 1171,    0,    0,    0,    0, 1171,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0, 1171,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 1171,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  643,  643, 1171,  643,    0,
    0,    0,    0,    0,    0,    0,    0,  643,  643,    0,
  643,    0,    0,    0, 1171, 1171,    0,    0,    0, 1171,
    0,    0,    0,    0,    0,    0,    0,    0, 1171,    0,
    0,    0,    0,    0,    0,    0,    0, 1171,  643,    0,
 1171,  643,  643,    0,    0,    0,  643,    0,    0, 1171,
    0,  643,    0,    0, 1171, 1171, 1171,    0,    0,    0,
  643, 1171, 1171, 1171,    0,  643,    0,    0,    0,    0,
    0,    0,    0,    0,    0, 1171, 1171,    0,    0,    0,
  643,    0,    0,    0,    0,  643,    0,  643, 1171,    0,
    0,    0, 1171,    0,  643,  643,  643,    0,  643,  643,
  643,    0,  643,  643,  643,  643,    0,  643,  643,  643,
  643,  643,  643,  643,  643,  643,  643,    0,    0,    0,
    0,    0,  643,    0,  643,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  643,    0,    0,  643,  643,    0,    0,    0,    0,
    0,  643,    0,    0,    0,    0,  643,    0,  643,    0,
  643,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  643,    0,    0,  643,    0,
  643,    0,    0,    0,    0,  643,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  643,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  643,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  643,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  643,  643,    0,    0,    0,  643,    0,
  922,  922,    0,  922,    0,    0,    0,  643,    0,    0,
    0,    0,  922,  922,    0,  922,  643,    0,    0,  643,
    0,    0,    0,    0,    0,    0,    0,    0,  643,    0,
    0,    0,    0,  643,  643,  643,    0,    0,    0,    0,
  643,  643,  643,  922,    0,    0,  922,  922,    0,    0,
    0,  922,    0,    0,  643,  643,  922,    0,    0,    0,
    0,    0,    0,    0,    0,  922,    0,  643,    0,    0,
  922,  643,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  922,    0,    0,    0,    0,
  922,    0,  922,    0,    0,    0,    0,  922,    0,  922,
  922,  922,    0,  922,  922,  922,    0,  922,  922,  922,
  922,    0,  922,    0,  922,  922,  922,  922,  922,  922,
  922,  922,    0,    0,    0,    0,    0,  922,    0,  922,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  922,    0,    0,  922,
  922,    0,    0,    0,    0,    0,  922,    0,    0,    0,
    0,  922,    0,  922,    0,  922,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  922,    0,    0,  922,    0,  922,    0,    0,    0,    0,
  922,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  922,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  922,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  922,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  922,  922,
    0,    0,    0,  922,    0,  783,  783,    0,  783,    0,
    0,    0,  922,    0,    0,    0,    0,  783,  783,    0,
  783,  922,    0,    0,  922,    0,    0,    0,    0,    0,
    0,    0,    0,  922,    0,    0,    0,    0,  922,  922,
  922,    0,    0,    0,    0,  922,  922,  922,  783,    0,
    0,  783,  783,    0,    0,    0,  783,    0,    0,  922,
  922,  783,    0,    0,    0,    0,    0,    0,    0,    0,
  783,    0,  922,    0,    0,  783,  922,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  783,    0,    0,    0,    0,  783,    0,  783,    0,    0,
    0,    0,  783,    0,  783,    0,  783,    0,  783,  783,
  783,    0,  783,  783,  783,  783,    0,  783,  783,  783,
  783,  783,  783,  783,  783,  783,  783,    0,    0,    0,
    0,    0,  783,    0,  783,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  783,    0,    0,  783,  783,    0,    0,    0,    0,
    0,  783,    0,    0,    0,    0,  783,    0,  783,    0,
  783,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  783,    0,    0,  783,    0,
  783,    0,    0,    0,    0,  783,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  783,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  783,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  783,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  783,  783,    0,    0,    0,  783,    0,
  774,  774,    0,  774,    0,    0,    0,  783,    0,    0,
    0,    0,  774,  774,    0,  774,  783,    0,    0,  783,
    0,    0,    0,    0,    0,    0,    0,    0,  783,    0,
    0,    0,    0,  783,  783,  783,    0,    0,    0,    0,
  783,  783,  783,  774,    0,    0,  774,  774,    0,    0,
    0,  774,    0,    0,  783,  783,  774,    0,    0,    0,
    0,    0,    0,    0,    0,  774,    0,  783,    0,    0,
  774,  783,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  774,    0,    0,    0,    0,
  774,    0,  774,    0,    0,    0,    0,  774,    0,  774,
  774,  774,    0,  774,    0,  774,    0,  774,  774,  774,
  774,    0,  774,  774,  774,  774,  774,  774,  774,  774,
  774,  774,    0,    0,    0,    0,    0,  774,    0,  774,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  774,    0,    0,  774,
  774,    0,    0,    0,    0,    0,  774,    0,    0,    0,
    0,  774,    0,  774,    0,  774,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  774,    0,    0,  774,    0,  774,    0,    0,    0,    0,
  774,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  774,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  774,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  774,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  774,  774,
    0,    0,    0,  774,    0,  805,  805,    0,  805,    0,
    0,    0,  774,    0,    0,    0,    0,  805,  805,    0,
  805,  774,    0,    0,  774,    0,    0,    0,    0,    0,
    0,    0,    0,  774,    0,    0,    0,    0,  774,  774,
  774,    0,    0,    0,    0,  774,  774,  774,  805,    0,
    0,  805,  805,    0,    0,    0,  805,    0,    0,  774,
  774,  805,    0,    0,    0,    0,    0,    0,    0,    0,
  805,    0,  774,    0,    0,  805,  774,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  805,    0,    0,    0,    0,  805,    0,  805,    0,    0,
    0,    0,  805,    0,  805,  805,  805,    0,  805,  805,
  805,    0,    0,  805,  805,  805,    0,  805,  805,  805,
  805,  805,  805,  805,  805,  805,  805,    0,    0,    0,
    0,    0,  805,    0,  805,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  805,    0,    0,  805,  805,    0,    0,    0,    0,
    0,  805,    0,    0,    0,    0,  805,    0,  805,    0,
  805,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  805,    0,    0,  805,    0,
  805,    0,    0,    0,    0,  805,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  805,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  805,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  805,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  805,  805,    0,    0,    0,  805,    0,
  796,  796,    0,  796,    0,    0,    0,  805,    0,    0,
    0,    0,  796,  796,    0,  796,  805,    0,    0,  805,
    0,    0,    0,    0,    0,    0,    0,    0,  805,    0,
    0,    0,    0,  805,  805,  805,    0,    0,    0,    0,
  805,  805,  805,  796,    0,    0,  796,  796,    0,    0,
    0,  796,    0,    0,  805,  805,  796,    0,    0,    0,
    0,    0,    0,    0,    0,  796,    0,  805,    0,    0,
  796,  805,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  796,    0,    0,    0,    0,
  796,    0,  796,    0,    0,    0,    0,  796,    0,  796,
  796,  796,    0,  796,  796,  796,    0,  796,  796,  796,
    0,    0,  796,  796,  796,  796,  796,  796,  796,  796,
  796,  796,    0,    0,    0,    0,    0,  796,    0,  796,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  796,    0,    0,  796,
  796,    0,    0,    0,    0,    0,  796,    0,    0,    0,
    0,  796,    0,  796,    0,  796,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  796,    0,    0,  796,    0,  796,    0,    0,    0,    0,
  796,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  796,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  796,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  796,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  796,  796,
    0,    0,    0,  796,    0,  924,  924,    0,  924,    0,
    0,    0,  796,    0,    0,    0,    0,  924,  924,    0,
  924,  796,    0,    0,  796,    0,    0,    0,    0,    0,
    0,    0,    0,  796,    0,    0,    0,    0,  796,  796,
  796,    0,    0,    0,    0,  796,  796,  796,  924,    0,
    0,  924,  924,    0,    0,    0,  924,    0,    0,  796,
  796,  924,    0,    0,    0,    0,    0,    0,    0,    0,
  924,    0,  796,    0,    0,  924,  796,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  924,    0,    0,    0,    0,  924,    0,  924,    0,    0,
    0,    0,  924,    0,  924,  924,  924,    0,  924,  924,
  924,    0,  924,  924,  924,  924,    0,  924,  924,    0,
  924,  924,  924,  924,  924,  924,  924,    0,    0,    0,
    0,    0,  924,    0,  924,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  924,    0,    0,  924,  924,    0,    0,    0,    0,
    0,  924,    0,    0,    0,    0,  924,    0,  924,    0,
  924,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  924,    0,    0,  924,    0,
  924,    0,    0,    0,    0,  924,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  924,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  924,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  924,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  924,  924,    0,    0,    0,  924,    0,
  725,  725,    0,  725,    0,    0,    0,  924,    0,    0,
    0,    0,  725,  725,    0,  725,  924,    0,    0,  924,
    0,    0,    0,    0,    0,    0,    0,    0,  924,    0,
    0,    0,    0,  924,  924,  924,    0,    0,    0,    0,
  924,  924,  924,  725,    0,    0,  725,  725,    0,    0,
    0,  725,    0,    0,  924,  924,  725,    0,    0,    0,
    0,    0,    0,    0,    0,  725,    0,  924,    0,    0,
  725,  924,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  725,    0,    0,    0,    0,
  725,    0,  725,    0,    0,    0,    0,  725,    0,  725,
  725,  725,    0,  725,  725,  725,    0,  725,  725,  725,
  725,    0,  725,  725,  725,  725,    0,  725,  725,  725,
  725,  725,    0,    0,    0,    0,    0,  725,    0,  725,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  725,    0,    0,  725,
  725,    0,    0,    0,    0,    0,  725,    0,    0,    0,
    0,  725,    0,  725,    0,  725,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  725,    0,    0,  725,    0,  725,    0,    0,    0,    0,
  725,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  725,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  725,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  725,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  725,  725,
    0,    0,    0,  725,    0,  790,  790,    0,  790,    0,
    0,    0,  725,    0,    0,    0,    0,  790,  790,    0,
  790,  725,    0,    0,  725,    0,    0,    0,    0,    0,
    0,    0,    0,  725,    0,    0,    0,    0,  725,  725,
  725,    0,    0,    0,    0,  725,  725,  725,  790,    0,
    0,  790,  790,    0,    0,    0,  790,    0,    0,  725,
  725,  790,    0,    0,    0,    0,    0,    0,    0,    0,
  790,    0,  725,    0,    0,  790,  725,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  790,    0,    0,    0,    0,  790,    0,  790,    0,    0,
    0,    0,  790,    0,  790,  790,  790,    0,  790,  790,
  790,    0,  790,  790,  790,  790,    0,  790,  790,  790,
  790,  790,  790,  790,    0,  790,  790,    0,    0,    0,
    0,    0,  790,    0,  790,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  790,    0,    0,  790,  790,    0,    0,    0,    0,
    0,  790,    0,    0,    0,    0,  790,    0,  790,    0,
  790,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  790,    0,    0,  790,    0,
  790,    0,    0,    0,    0,  790,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  790,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  790,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  790,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  790,  790,    0,    0,    0,  790,    0,
  691,  691,    0,  691,    0,    0,    0,  790,    0,    0,
    0,    0,  691,  691,    0,  691,  790,    0,    0,  790,
    0,    0,    0,    0,    0,    0,    0,    0,  790,    0,
    0,    0,    0,  790,  790,  790,    0,    0,    0,    0,
  790,  790,  790,  691,    0,    0,  691,  691,    0,    0,
    0,  691,    0,    0,  790,  790,  691,    0,    0,    0,
    0,    0,    0,    0,    0,  691,    0,  790,    0,    0,
  691,  790,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  691,    0,    0,    0,    0,
  691,    0,  691,    0,    0,    0,    0,  691,    0,  691,
  691,  691,    0,  691,  691,  691,    0,  691,  691,    0,
  691,    0,  691,  691,  691,  691,  691,  691,  691,  691,
  691,  691,    0,    0,    0,    0,    0,  691,    0,  691,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  691,    0,    0,  691,
  691,    0,    0,    0,    0,    0,  691,    0,    0,    0,
    0,  691,    0,  691,    0,  691,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  691,    0,    0,  691,    0,  691,    0,    0,    0,    0,
  691,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  691,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  691,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  691,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  691,  691,
    0,    0,    0,  691,    0,  831,  831,    0,  831,    0,
    0,    0,  691,    0,    0,    0,    0,  831,  831,    0,
  831,  691,    0,    0,  691,    0,    0,    0,    0,    0,
    0,    0,    0,  691,    0,    0,    0,    0,  691,  691,
  691,    0,    0,    0,    0,  691,  691,  691,  831,    0,
    0,  831,  831,    0,    0,    0,  831,    0,    0,  691,
  691,  831,    0,    0,    0,    0,    0,    0,    0,    0,
  831,    0,  691,    0,    0,  831,  691,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  831,    0,    0,    0,    0,  831,    0,  831,    0,    0,
    0,    0,  831,    0,    0,  831,  831,    0,  831,  831,
  831,    0,  831,  831,  831,  831,    0,  831,  831,  831,
  831,  831,  831,  831,  831,  831,  831,    0,    0,    0,
    0,    0,  831,    0,  831,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  831,    0,    0,  831,  831,    0,    0,    0,    0,
    0,  831,    0,    0,    0,    0,  831,    0,  831,    0,
  831,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  831,    0,    0,  831,    0,
  831,    0,    0,    0,    0,  831,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  831,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  831,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  831,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  831,  831,    0,    0,    0,  831,    0,
  892,  892,    0,  892,    0,    0,    0,  831,    0,    0,
    0,    0,    0,  892,    0,  892,  831,    0,    0,  831,
    0,    0,    0,    0,    0,    0,    0,    0,  831,    0,
    0,    0,    0,  831,  831,  831,    0,    0,    0,    0,
  831,  831,  831,  892,    0,    0,  892,  892,    0,    0,
    0,  892,    0,    0,  831,  831,  892,    0,    0,    0,
    0,    0,    0,    0,    0,  892,    0,  831,    0,    0,
  892,  831,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  892,    0,    0,    0,    0,
  892,    0,  892,    0,    0,    0,    0,  892,    0,  892,
  892,  892,    0,  892,  892,  892,    0,  892,  892,  892,
  892,    0,  892,  892,  892,  892,  892,  892,  892,  892,
  892,  892,    0,    0,    0,    0,    0,  892,    0,  892,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  892,    0,    0,  892,
  892,    0,    0,    0,    0,    0,  892,    0,    0,    0,
    0,  892,    0,  892,    0,  892,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  892,    0,    0,  892,    0,  892,    0,    0,    0,    0,
  892,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  892,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  892,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  892,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  892,  892,
    0,    0,    0,  892,    0,  950,  950,    0,  950,    0,
    0,    0,  892,    0,    0,    0,    0,  950,  950,    0,
  950,  892,    0,    0,  892,    0,    0,    0,    0,    0,
    0,    0,    0,  892,    0,    0,    0,    0,  892,  892,
  892,    0,    0,    0,    0,  892,  892,  892,  950,    0,
    0,  950,  950,    0,    0,    0,  950,    0,    0,  892,
  892,  950,    0,    0,    0,    0,    0,    0,    0,    0,
  950,    0,  892,    0,    0,  950,  892,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  950,    0,    0,    0,    0,  950,    0,  950,    0,    0,
    0,    0,  950,    0,  950,  950,  950,    0,  950,  950,
  950,    0,  950,  950,  950,  950,    0,  950,  950,  950,
  950,  950,    0,  950,  950,  950,  950,    0,    0,    0,
    0,    0,  950,    0,  950,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  950,    0,    0,  950,  950,    0,    0,    0,    0,
    0,  950,    0,    0,    0,    0,  950,    0,  950,    0,
  950,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  950,    0,    0,  950,    0,
  950,    0,    0,    0,    0,  950,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  950,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  950,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  950,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  950,  950,    0,    0,    0,  950,    0,
  944,  944,    0,  944,    0,    0,    0,  950,    0,    0,
    0,    0,  944,  944,    0,  944,  950,    0,    0,  950,
    0,    0,    0,    0,    0,    0,    0,    0,  950,    0,
    0,    0,    0,  950,  950,  950,    0,    0,    0,    0,
  950,  950,  950,  944,    0,    0,  944,  944,    0,    0,
    0,  944,    0,    0,  950,  950,  944,    0,    0,    0,
    0,    0,    0,    0,    0,  944,    0,  950,    0,    0,
  944,  950,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  944,    0,    0,    0,    0,
  944,    0,  944,    0,    0,    0,    0,  944,    0,  944,
  944,  944,    0,  944,  944,    0,    0,  944,  944,  944,
  944,    0,  944,  944,  944,  944,  944,  944,  944,  944,
  944,  944,    0,    0,    0,    0,    0,  944,    0,  944,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  944,    0,    0,  944,
  944,    0,    0,    0,    0,    0,  944,    0,    0,    0,
    0,  944,    0,  944,    0,  944,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  944,    0,    0,  944,    0,  944,    0,    0,    0,    0,
  944,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  944,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  944,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  944,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  944,  944,
    0,    0,    0,  944,    0,  908,  908,    0,  908,    0,
    0,    0,  944,    0,    0,    0,    0,    0,  908,    0,
  908,  944,    0,    0,  944,    0,    0,    0,    0,    0,
    0,    0,    0,  944,    0,    0,    0,    0,  944,  944,
  944,    0,    0,    0,    0,  944,  944,  944,  908,    0,
    0,  908,  908,    0,    0,    0,  908,    0,    0,  944,
  944,  908,    0,    0,    0,    0,    0,    0,    0,    0,
  908,    0,  944,    0,    0,  908,  944,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  908,    0,    0,    0,    0,  908,    0,  908,    0,    0,
    0,    0,  908,    0,  908,  908,  908,    0,  908,  908,
  908,    0,  908,  908,  908,  908,    0,  908,  908,  908,
  908,  908,  908,  908,  908,  908,  908,    0,    0,    0,
    0,    0,  908,    0,  908,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  908,    0,    0,  908,  908,    0,    0,    0,    0,
    0,  908,    0,    0,    0,    0,  908,    0,  908,    0,
  908,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  908,    0,    0,  908,    0,
  908,    0,    0,    0,    0,  908,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  908,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  908,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  908,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  908,  908,    0,    0,    0,  908,    0,
  940,  940,    0,  940,    0,    0,    0,  908,    0,    0,
    0,    0,  940,  940,    0,  940,  908,    0,    0,  908,
    0,    0,    0,    0,    0,    0,    0,    0,  908,    0,
    0,    0,    0,  908,  908,  908,    0,    0,    0,    0,
  908,  908,  908,  940,    0,    0,  940,  940,    0,    0,
    0,  940,    0,    0,  908,  908,  940,    0,    0,    0,
    0,    0,    0,    0,    0,  940,    0,  908,    0,    0,
  940,  908,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  940,    0,    0,    0,    0,
  940,    0,  940,    0,    0,    0,    0,  940,    0,  940,
  940,  940,    0,  940,  940,  940,    0,  940,  940,  940,
  940,    0,  940,  940,  940,    0,  940,  940,  940,  940,
  940,  940,    0,    0,    0,    0,    0,  940,    0,  940,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  940,    0,    0,  940,
  940,    0,    0,    0,    0,    0,  940,    0,    0,    0,
    0,  940,    0,  940,    0,  940,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  940,    0,    0,  940,    0,  940,    0,    0,    0,    0,
  940,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  940,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  940,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  940,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  940,  940,
    0,    0,    0,  940,    0,  936,  936,    0,  936,    0,
    0,    0,  940,    0,    0,    0,    0,  936,  936,    0,
  936,  940,    0,    0,  940,    0,    0,    0,    0,    0,
    0,    0,    0,  940,    0,    0,    0,    0,  940,  940,
  940,    0,    0,    0,    0,  940,  940,  940,  936,    0,
    0,  936,  936,    0,    0,    0,  936,    0,    0,  940,
  940,  936,    0,    0,    0,    0,    0,    0,    0,    0,
  936,    0,  940,    0,    0,  936,  940,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  936,    0,    0,    0,    0,  936,    0,  936,    0,    0,
    0,    0,  936,    0,  936,  936,  936,    0,  936,  936,
  936,    0,  936,  936,  936,  936,    0,  936,  936,  936,
  936,  936,  936,  936,  936,  936,    0,    0,    0,    0,
    0,    0,  936,    0,  936,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  936,    0,    0,  936,  936,    0,    0,    0,    0,
    0,  936,    0,    0,    0,    0,  936,    0,  936,    0,
  936,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  936,    0,    0,  936,    0,
  936,    0,    0,    0,    0,  936,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  936,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  936,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  936,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  936,  936,    0,    0,    0,  936,    0,
  907,  907,    0,  907,    0,    0,    0,  936,    0,    0,
    0,    0,    0,  907,    0,  907,  936,    0,    0,  936,
    0,    0,    0,    0,    0,    0,    0,    0,  936,    0,
    0,    0,    0,  936,  936,  936,    0,    0,    0,    0,
  936,  936,  936,  907,    0,    0,  907,  907,    0,    0,
    0,  907,    0,    0,  936,  936,  907,    0,    0,    0,
    0,    0,    0,    0,    0,  907,    0,  936,    0,    0,
  907,  936,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  907,    0,    0,    0,    0,
  907,    0,  907,    0,    0,    0,    0,  907,    0,  907,
  907,  907,    0,  907,  907,  907,    0,  907,  907,  907,
  907,    0,  907,  907,  907,  907,  907,  907,  907,  907,
  907,  907,    0,    0,    0,    0,    0,  907,    0,  907,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  907,    0,    0,  907,
  907,    0,    0,    0,    0,    0,  907,    0,    0,    0,
    0,  907,    0,  907,    0,  907,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  907,    0,    0,  907,    0,  907,    0,    0,    0,    0,
  907,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  907,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  907,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  907,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  907,  907,
    0,    0,    0,  907,    0,  896,  896,    0,  896,    0,
    0,    0,  907,    0,    0,    0,    0,    0,  896,    0,
  896,  907,    0,    0,  907,    0,    0,    0,    0,    0,
    0,    0,    0,  907,    0,    0,    0,    0,  907,  907,
  907,    0,    0,    0,    0,  907,  907,  907,  896,    0,
    0,  896,  896,    0,    0,    0,  896,    0,    0,  907,
  907,  896,    0,    0,    0,    0,    0,    0,    0,    0,
  896,    0,  907,    0,    0,  896,  907,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  896,    0,    0,    0,    0,  896,    0,  896,    0,    0,
    0,    0,  896,    0,  896,  896,  896,    0,  896,  896,
  896,    0,  896,  896,  896,  896,    0,  896,  896,  896,
  896,  896,  896,  896,  896,  896,  896,    0,    0,    0,
    0,    0,  896,    0,  896,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  896,    0,    0,  896,  896,    0,    0,    0,    0,
    0,  896,    0,    0,    0,    0,  896,    0,  896,    0,
  896,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  896,    0,    0,  896,    0,
  896,    0,    0,    0,    0,  896,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  896,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  896,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  896,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  896,  896,    0,    0,    0,  896,    0,
  995,  995,    0,  995,    0,    0,    0,  896,    0,    0,
    0,    0,    0,  995,    0,  995,  896,    0,    0,  896,
    0,    0,    0,    0,    0,    0,    0,    0,  896,    0,
    0,    0,    0,  896,  896,  896,    0,    0,    0,    0,
  896,  896,  896,  995,    0,    0,  995,  995,    0,    0,
    0,  995,    0,    0,  896,  896,  995,    0,    0,    0,
    0,    0,    0,    0,    0,  995,    0,  896,    0,    0,
  995,  896,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  995,    0,    0,    0,    0,
  995,    0,  995,    0,    0,    0,    0,  995,    0,  995,
  995,  995,    0,  995,  995,  995,    0,  995,  995,  995,
  995,    0,  995,  995,  995,  995,  995,  995,  995,  995,
  995,  995,    0,    0,    0,    0,    0,  995,    0,  995,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  995,    0,    0,  995,
  995,    0,    0,    0,    0,    0,  995,    0,    0,    0,
    0,  995,    0,  995,    0,  995,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  995,    0,    0,  995,    0,  995,    0,    0,    0,    0,
  995,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  995,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  995,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  995,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  995,  995,
    0,    0,    0,  995,    0,  701,  701,    0,  701,    0,
    0,    0,  995,    0,    0,    0,    0,  701,  701,    0,
  701,  995,    0,    0,  995,    0,    0,    0,    0,    0,
    0,    0,    0,  995,    0,    0,    0,    0,  995,  995,
  995,    0,    0,    0,    0,  995,  995,  995,  701,    0,
    0,  701,  701,    0,    0,    0,  701,    0,    0,  995,
  995,  701,    0,    0,    0,    0,    0,    0,    0,    0,
  701,    0,  995,    0,    0,  701,  995,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  701,    0,    0,    0,    0,  701,    0,  701,    0,    0,
    0,    0,  701,    0,  701,  701,  701,    0,  701,  701,
  701,    0,  701,  701,  701,  701,    0,  701,  701,  701,
  701,  701,  701,  701,  701,  701,  701,    0,    0,    0,
    0,    0,  701,    0,  701,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  701,    0,    0,  701,  701,    0,    0,    0,    0,
    0,  701,    0,    0,    0,    0,  701,    0,  701,    0,
  701,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  701,    0,    0,  701,    0,
  701,    0,    0,    0,    0,  701,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  701,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  701,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  701,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  701,  701,    0,    0,    0,  701,    0,
 1077, 1077,    0, 1077,    0,    0,    0,  701,    0,    0,
    0,    0, 1077, 1077,    0, 1077,  701,    0,    0,  701,
    0,    0,    0,    0,    0,    0,    0,    0,  701,    0,
    0,    0,    0,  701,  701,  701,    0,    0,    0,    0,
  701,  701,  701, 1077,    0,    0, 1077, 1077,    0,    0,
    0, 1077,    0,    0,  701,  701, 1077,    0,    0,    0,
    0,    0,    0,    0,    0, 1077,    0,    0,    0,    0,
 1077,  701,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0, 1077,    0,    0,    0,    0,
 1077,    0, 1077,    0,    0,    0,    0, 1077,    0, 1077,
 1077, 1077,    0, 1077, 1077, 1077,    0, 1077, 1077, 1077,
 1077,    0, 1077, 1077, 1077, 1077, 1077, 1077,    0, 1077,
 1077, 1077,    0,    0,    0,    0,    0, 1077,    0, 1077,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0, 1077,    0,    0, 1077,
 1077,    0,    0,    0,    0,    0, 1077,    0,    0,    0,
    0, 1077,    0, 1077,    0, 1077,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 1077,    0,    0, 1077,    0, 1077,    0,    0,    0,    0,
 1077,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0, 1077,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0, 1077,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, 1077,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0, 1077, 1077,
    0,    0,    0, 1077,    0,  915,  915,    0,  915,    0,
    0,    0, 1077,    0,    0,    0,    0,    0,  915,    0,
  915, 1077,    0,    0, 1077,    0,    0,    0,    0,    0,
    0,    0,    0, 1077,    0,    0,    0,    0, 1077, 1077,
 1077,    0,    0,    0,    0, 1077, 1077, 1077,  915,    0,
    0,  915,  915,    0,    0,    0,  915,    0,    0, 1077,
 1077,  915,    0,    0,    0,    0,    0,    0,    0,    0,
  915,    0, 1077,    0,    0,  915, 1077,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  915,    0,    0,    0,    0,  915,    0,  915,    0,    0,
    0,    0,  915,    0,  915,  915,  915,    0,  915,  915,
  915,    0,  915,  915,  915,  915,    0,  915,  915,  915,
  915,  915,  915,  915,  915,  915,  915,    0,    0,    0,
    0,    0,  915,    0,  915,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  915,    0,    0,  915,  915,    0,    0,    0,    0,
    0,  915,    0,    0,    0,    0,  915,    0,  915,    0,
  915,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  915,    0,    0,  915,    0,
  915,    0,    0,    0,    0,  915,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  915,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  915,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  915,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  915,  915,    0,    0,    0,  915,    0,
 1004, 1004,    0, 1004,    0,    0,    0,  915,    0,    0,
    0,    0, 1004, 1004,    0, 1004,  915,    0,    0,  915,
    0,    0,    0,    0,    0,    0,    0,    0,  915,    0,
    0,    0,    0,  915,  915,  915,    0,    0,    0,    0,
  915,  915,  915, 1004,    0,    0, 1004, 1004,    0,    0,
    0, 1004,    0,    0,  915,  915, 1004,    0,    0,    0,
    0,    0,    0,    0,    0, 1004,    0,  915,    0,    0,
 1004,  915,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0, 1004,    0,    0,    0,    0,
 1004,    0, 1004,    0,    0,    0,    0, 1004,    0, 1004,
 1004, 1004,    0,    0, 1004, 1004,    0, 1004, 1004, 1004,
 1004,    0, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004,
 1004, 1004,    0,    0,    0,    0,    0, 1004,    0, 1004,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0, 1004,    0,    0, 1004,
 1004,    0,    0,    0,    0,    0, 1004,    0,    0,    0,
    0, 1004,    0, 1004,    0, 1004,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 1004,    0,    0, 1004,    0, 1004,    0,    0,    0,    0,
 1004,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0, 1004,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0, 1004,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, 1004,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0, 1004, 1004,
    0,    0,    0, 1004,    0,  698,  698,    0,  698,    0,
    0,    0, 1004,    0,    0,    0,    0,  698,  698,    0,
  698, 1004,    0,    0, 1004,    0,    0,    0,    0,    0,
    0,    0,    0, 1004,    0,    0,    0,    0, 1004, 1004,
 1004,    0,    0,    0,    0, 1004, 1004, 1004,  698,    0,
    0,  698,  698,    0,    0,    0,  698,    0,    0, 1004,
 1004,  698,    0,    0,    0,    0,    0,    0,    0,    0,
  698,    0, 1004,    0,    0,  698, 1004,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  698,    0,    0,    0,    0,  698,    0,  698,    0,    0,
    0,    0,  698,    0,  698,  698,  698,    0,  698,  698,
  698,    0,  698,  698,  698,  698,    0,  698,  698,  698,
  698,  698,  698,  698,  698,  698,  698,    0,    0,    0,
    0,    0,  698,    0,  698,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  698,    0,    0,  698,  698,    0,    0,    0,    0,
    0,  698,    0,    0,    0,    0,  698,    0,  698,    0,
  698,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  698,    0,    0,  698,    0,
  698,    0,    0,    0,    0,  698,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  698,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  698,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  698,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  698,  698,    0,    0,    0,  698,    0,
 1079, 1079,    0, 1079,    0,    0,    0,  698,    0,    0,
    0,    0, 1079, 1079,    0, 1079,  698,    0,    0,  698,
    0,    0,    0,    0,    0,    0,    0,    0,  698,    0,
    0,    0,    0,  698,  698,  698,    0,    0,    0,    0,
  698,  698,  698, 1079,    0,    0, 1079, 1079,    0,    0,
    0, 1079,    0,    0,  698,  698, 1079,    0,    0,    0,
    0,    0,    0,    0,    0, 1079,    0,    0,    0,    0,
 1079,  698,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0, 1079,    0,    0,    0,    0,
 1079,    0, 1079,    0,    0,    0,    0, 1079,    0, 1079,
 1079, 1079,    0, 1079, 1079, 1079,    0, 1079, 1079, 1079,
 1079,    0, 1079, 1079, 1079, 1079, 1079, 1079, 1079, 1079,
    0, 1079,    0,    0,    0,    0,    0, 1079,    0, 1079,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0, 1079,    0,    0, 1079,
 1079,    0,    0,    0,    0,    0, 1079,    0,    0,    0,
    0, 1079,    0, 1079,    0, 1079,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 1079,    0,    0, 1079,    0, 1079,    0,    0,    0,    0,
 1079,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0, 1079,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0, 1079,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, 1079,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0, 1079, 1079,
    0,    0,    0, 1079,    0, 1050, 1050,    0, 1050,    0,
    0,    0, 1079,    0,    0,    0,    0,    0, 1050,    0,
 1050, 1079,    0,    0, 1079,    0,    0,    0,    0,    0,
    0,    0,    0, 1079,    0,    0,    0,    0, 1079, 1079,
 1079,    0,    0,    0,    0, 1079, 1079, 1079, 1050,    0,
    0, 1050, 1050,    0,    0,    0, 1050,    0,    0, 1079,
 1079, 1050,    0,    0,    0,    0,    0,    0,    0,    0,
 1050,    0, 1079,    0,    0, 1050, 1079,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 1050,    0,    0,    0,    0, 1050,    0, 1050,    0,    0,
    0,    0, 1050,    0, 1050, 1050, 1050,    0, 1050, 1050,
 1050,    0, 1050, 1050, 1050, 1050,    0, 1050, 1050, 1050,
 1050, 1050, 1050, 1050, 1050, 1050, 1050,    0,    0,    0,
    0,    0, 1050,    0, 1050,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, 1050,    0,    0, 1050, 1050,    0,    0,    0,    0,
    0, 1050,    0,    0,    0,    0, 1050,    0, 1050,    0,
 1050,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0, 1050,    0,    0, 1050,    0,
 1050,    0,    0,    0,    0, 1050,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0, 1050,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0, 1050,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0, 1050,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0, 1050, 1050,    0,    0,    0, 1050,    0,
 1002, 1002,    0, 1002,    0,    0,    0, 1050,    0,    0,
    0,    0, 1002, 1002,    0, 1002, 1050,    0,    0, 1050,
    0,    0,    0,    0,    0,    0,    0,    0, 1050,    0,
    0,    0,    0, 1050, 1050, 1050,    0,    0,    0,    0,
 1050, 1050, 1050, 1002,    0,    0, 1002, 1002,    0,    0,
    0, 1002,    0,    0, 1050, 1050, 1002,    0,    0,    0,
    0,    0,    0,    0,    0, 1002,    0, 1050,    0,    0,
 1002, 1050,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0, 1002,    0,    0,    0,    0,
 1002,    0, 1002,    0,    0,    0,    0, 1002,    0, 1002,
 1002,    0,    0, 1002, 1002, 1002,    0, 1002, 1002, 1002,
 1002,    0, 1002, 1002, 1002, 1002, 1002, 1002, 1002, 1002,
 1002, 1002,    0,    0,    0,    0,    0, 1002,    0, 1002,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0, 1002,    0,    0, 1002,
 1002,    0,    0,    0,    0,    0, 1002,    0,    0,    0,
    0, 1002,    0, 1002,    0, 1002,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 1002,    0,    0, 1002,    0, 1002,    0,    0,    0,    0,
 1002,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0, 1002,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0, 1002,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, 1002,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0, 1002, 1002,
    0,    0,    0, 1002,    0, 1060, 1060,    0, 1060,    0,
    0,    0, 1002,    0,    0,    0,    0,    0, 1060,    0,
 1060, 1002,    0,    0, 1002,    0,    0,    0,    0,    0,
    0,    0,    0, 1002,    0,    0,    0,    0, 1002, 1002,
 1002,    0,    0,    0,    0, 1002, 1002, 1002, 1060,    0,
    0, 1060, 1060,    0,    0,    0, 1060,    0,    0, 1002,
 1002, 1060,    0,    0,    0,    0,    0,    0,    0,    0,
 1060,    0, 1002,    0,    0, 1060, 1002,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 1060,    0,    0,    0,    0, 1060,    0, 1060,    0,    0,
    0,    0, 1060,    0, 1060, 1060, 1060,    0, 1060, 1060,
 1060,    0, 1060, 1060, 1060, 1060,    0, 1060, 1060, 1060,
 1060, 1060, 1060, 1060, 1060, 1060, 1060,    0,    0,    0,
    0,    0, 1060,    0, 1060,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, 1060,    0,    0, 1060, 1060,    0,    0,    0,    0,
    0, 1060,    0,    0,    0,    0, 1060,    0, 1060,    0,
 1060,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0, 1060,    0,    0, 1060,    0,
 1060,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0, 1060,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0, 1060,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0, 1060,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0, 1060, 1060,    0,    0,    0, 1060,    0,
 1057, 1057,    0, 1057,    0,    0,    0, 1060,    0,    0,
    0,    0,    0, 1057,    0, 1057, 1060,    0,    0, 1060,
    0,    0,    0,    0,    0,    0,    0,    0, 1060,    0,
    0,    0,    0, 1060, 1060, 1060,    0,    0,    0,    0,
 1060, 1060, 1060, 1057,    0,    0, 1057, 1057,    0,    0,
    0, 1057,    0,    0, 1060, 1060, 1057,    0,    0,    0,
    0,    0,    0,    0,    0, 1057,    0, 1060,    0,    0,
 1057, 1060,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0, 1057,    0,    0,    0,    0,
 1057,    0, 1057,    0,    0,    0,    0, 1057,    0, 1057,
 1057, 1057,    0, 1057, 1057, 1057,    0, 1057, 1057, 1057,
 1057,    0, 1057, 1057, 1057, 1057, 1057, 1057, 1057, 1057,
 1057, 1057,    0,    0,    0,    0,    0, 1057,    0, 1057,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0, 1057,    0,    0, 1057,
 1057,    0,    0,    0,    0,    0, 1057,    0,    0,    0,
    0, 1057,    0, 1057,    0, 1057,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 1057,    0,    0, 1057,    0, 1057,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0, 1057,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0, 1057,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, 1057,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0, 1057, 1057,
    0,    0,    0, 1057,    0, 1056, 1056,    0, 1056,    0,
    0,    0, 1057,    0,    0,    0,    0,    0, 1056,    0,
 1056, 1057,    0,    0, 1057,    0,    0,    0,    0,    0,
    0,    0,    0, 1057,    0,    0,    0,    0, 1057, 1057,
 1057,    0,    0,    0,    0, 1057, 1057, 1057, 1056,    0,
    0, 1056, 1056,    0,    0,    0, 1056,    0,    0, 1057,
 1057, 1056,    0,    0,    0,    0,    0,    0,    0,    0,
 1056,    0, 1057,    0,    0, 1056, 1057,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 1056,    0,    0,    0,    0, 1056,    0, 1056,    0,    0,
    0,    0, 1056, 1232, 1056, 1056, 1056, 1232, 1056, 1056,
 1056,    0, 1056, 1056, 1056, 1056,    0, 1056, 1056, 1056,
 1056, 1056, 1056, 1056, 1056, 1056, 1056,    0,    0,    0,
    0,    0, 1056,    0, 1056,    0,    0,    0,    0,    0,
    0,    0,    0, 1232, 1232,    0, 1232, 1232, 1232,    0,
    0, 1056,    0,    0, 1056, 1056,    0,    0,    0,    0,
    0, 1056,    0,    0,    0,    0, 1056,    0, 1056, 1232,
 1056,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  678,
  678,    0,  678,    0,    0, 1056,    0,    0, 1056,    0,
 1056,    0,  678,    0,  678,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  678,    0,    0, 1056,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0, 1056,
    0,    0,  678,    0, 1232,  678,  678,    0,    0,    0,
  678,    0,    0,    0,    0,  678, 1056,    0,    0,    0,
    0, 1232,    0, 1232,  678,    0,    0,    0,    0,  678,
    0,    0, 1232, 1056, 1056,    0,    0,    0, 1056,    0,
    0,    0,    0,    0,  678,    0,    0, 1056,    0,  678,
 1232,  678,    0,    0, 1232,    0, 1056,    0,    0, 1056,
    0,    0,    0,    0,    0, 1232, 1232,  678, 1056,    0,
    0,    0,    0, 1056, 1056, 1056,    0,    0, 1232,    0,
 1056, 1056, 1056,    0,    0,    0,  678,    0,  678,    0,
    0,    0,    0,    0, 1056, 1056,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  678,    0, 1056,  678,  678,
    0, 1056,    0,    0,    0,  678,    0,    0,    0,    0,
  678,    0,  678,    0,  678,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0, 1232,    0,    0,    0,    0,
 1232,    0,    0,  679,  679,    0,  679,    0,    0,  678,
    0,    0,  678, 1232,  678,    0,  679,  678,  679,    0,
    0, 1232,    0,    0,    0,    0,    0,    0,    0,  679,
    0,    0,  678,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  678,    0,    0,  679,    0,    0,  679,
  679,    0,    0, 1232,  679,    0, 1232,    0,    0,  679,
  678,    0, 1232,    0, 1232,    0,    0,    0,  679,    0,
    0,    0,    0,  679,    0,    0,    0,  678,  678,    0,
    0,    0,  678,    0,    0,    0,    0,    0,  679,    0,
    0,  678,    0,  679,    0,  679,    0,    0,    0,    0,
  678,    0,    0,  678,    0,    0,    0,    0,    0,    0,
    0,  679,  678,    0,    0,    0,    0,  678,  678,  678,
    0,    0,    0,    0,  678,  678,  678,    0,    0,    0,
  679,    0,  679,    0,    0,    0,    0,    0,  678,  678,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  679,
    0,  678,  679,  679,    0,  678,    0,    0,    0,  679,
    0,    0,    0,    0,  679,    0,  679,    0,  679,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  685,  685,    0,
  685,    0,    0,  679,    0,    0,  679,    0,  679,    0,
  685,  679,  685,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  679,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  679,    0,    0,
  685,    0,    0,  685,  685,    0,    0,    0,  685,    0,
    0,    0,    0,  685,  679,    0,    0,    0,    0,    0,
    0,    0,  685,    0,    0,    0,    0,  685,    0,    0,
    0,  679,  679,    0,    0,    0,  679,    0,    0,    0,
    0,    0,  685,    0,    0,  679,    0,  685,    0,  685,
    0,    0,    0,    0,  679,    0,    0,  679,    0,    0,
    0,    0,    0,    0,    0,  681,  679,    0,    0,    0,
    0,  679,  679,  679,    0,    0,    0,    0,  679,  679,
  679,    0,    0,    0,  685,    0,  685,    0,    0,    0,
    0,    0,  679,  679,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  685,    0,  679,  685,  685,    0,  679,
    0,    0,    0,  685,    0,    0,    0,    0,  685,    0,
  685,    0,  685,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  668,  668,    0,  668,    0,    0,  685,    0,    0,
  685,    0,  685,    0,  668,  687,  668,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  685,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  685,    0,    0,  668,    0,    0,  668,  668,    0,
    0,    0,  668,    0,    0,    0,    0,  668,  685,    0,
    0,    0,    0,    0,    0,    0,  668,    0,    0,    0,
    0,  668,    0,    0,    0,  685,  685,    0,    0,    0,
  685,    0,    0,    0,    0,    0,  668,    0,    0,  685,
    0,  668,    0,  668,    0,    0,    0,    0,  685,    0,
    0,  685,    0,    0,    0,    0,    0,    0,    0,  668,
  685,    0,    0,    0,    0,  685,  685,  685,    0,    0,
    0,    0,  685,  685,  685,    0,    0,    0,  668,    0,
  668,    0,    0,    0,    0,    0,  685,  685,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  668,    0,  681,
  668,  668,    0,  681,    0,    0,    0,  668,    0,    0,
    0,    0,  668,    0,  668,    0,  668,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  294,  295,    0,  296,    0,
    0,  668,    0,    0,  668,    0,  668,    0,  297,  668,
  298,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  668,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  668,    0,    0,  299,    0,
    0,  300,  301,    0,    0,    0,  302,    0,    0,    0,
    0,  303,  668,    0,    0,    0,    0,    0,    0,    0,
  304,    0,    0,    0,    0,  305,    0,    0,    0,  668,
  668,    0,    0,    0,  668,    0,    0,    0,    0,    0,
  306,    0,    0,  668,    0,  307,    0,  308,    0,    0,
    0,    0,  668,    0,    0,  668,    0,    0,    0,    0,
    0,    0,    0,    0,  668,    0,    0,    0,    0,  668,
  668,  668,    0,    0,    0,    0,  668,  668,  668,    0,
    0,    0,  309,    0,  310,    0,    0,    0,    0,    0,
  668,  668,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  311,    0,  668,  312,  313,    0,  668,    0,    0,
    0,  314,    0,    0,    0,    0,  315,    0,  316,    0,
  317,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  294,  295,
    0,  296,    0,    0,    0,  318,    0,    0,  319,    0,
  320,  297,    0,  298,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  321,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  322,
    0,  299,    0,    0,  300,  301,    0,    0,    0,  302,
    0,    0,    0,    0,  303,    0,  323,    0,    0,    0,
    0,    0,    0,  304,    0,    0,    0,    0,  305,    0,
    0,    0,    0,  324,  325,    0,    0,    0,  326,    0,
    0,    0,    0,  306,    0,    0,    0,  327,  307,    0,
  308,    0,    0,    0,    0,    0,  328,    0,    0,  329,
    0,    0,    0,    0,    0,    0,    0,    0,  330,    0,
    0,    0,    0,  331,  332,  333,    0,    0,    0,    0,
  334,  335,  336,    0,    0,  309,    0,  310,    0,    0,
    0,    0,    0,    0,  337,  338,    0,    0,    0,    0,
    0,    0,    0,    0,  311,    0,    0,  312,  313,    0,
    0,  528,    0,    0,  314,    0,    0,    0,    0,  315,
    0,  316,    0,  317,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, 1175, 1175,    0, 1175,    0,    0,    0,  318,    0,
    0,  319,    0,  320, 1175,    0, 1175,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  321,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  322,    0, 1175,    0,    0, 1175, 1175,    0,
    0,    0, 1175,    0,    0,    0,    0, 1175,    0,  323,
    0,    0,    0,    0,    0,    0, 1175,    0,    0,    0,
    0, 1175,    0,    0,    0,    0,  324,  325,    0,    0,
    0,  326,    0,    0,    0,    0, 1175,    0,    0,    0,
  327, 1175,    0, 1175,    0,    0,    0,    0,    0,  328,
    0,    0,  329,    0,    0,    0,    0,    0,    0,    0,
    0,  330,    0,    0,    0,    0,  331,  332,  333,    0,
    0,    0,    0,  334,  335,  336,    0,    0, 1175,    0,
 1175,    0,    0,    0,    0,    0,    0,  337,  338,    0,
    0,    0,    0,    0,    0,    0,    0, 1175,    0,    0,
 1175, 1175,    0,    0,  800,    0,    0, 1175,    0,    0,
    0,    0, 1175,    0, 1175,    0, 1175,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  683,  683,    0,  683,    0,    0,
    0, 1175,    0,    0, 1175,    0, 1175,  683,    0,  683,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0, 1175,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0, 1175,    0,  683,    0,    0,
  683,  683,    0,    0,    0,  683,    0,    0,    0,    0,
  683,    0, 1175,    0,    0,    0,    0,    0,    0,  683,
    0,    0,    0,    0,  683,    0,    0,    0,    0, 1175,
 1175,    0,    0,    0, 1175,    0,    0,    0,    0,  683,
    0,    0,    0, 1175,  683,    0,  683,    0,    0,    0,
    0,    0, 1175,    0,    0, 1175,    0,    0,    0,    0,
    0,    0,    0,    0, 1175,    0,    0,    0,    0, 1175,
 1175, 1175,    0,    0,    0,    0, 1175, 1175, 1175, 1232,
    0,  683,    0,  683,    0,    0,    0,    0,    0,    0,
 1175, 1175, 1164,    0,    0,    0,    0,    0,    0,    0,
  683,    0, 1164,  683,  683,    0,    0,    0,    0,    0,
  683,    0,    0,    0,    0,  683,    0,  683,    0,  683,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  294,  295,
    0,  296,    0,    0,  683,    0,    0,  683,    0,  683,
    0,  297,  683,  298,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  683,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  683,    0,
    0,  299,    0,    0,  300,  301,    0,    0,    0,  302,
    0,    0,    0,    0,  303,  683,    0,    0,    0,    0,
    0,    0,    0,  304,    0,    0,    0,    0,  305,    0,
    0,    0,  683,  683,    0,    0,    0,  683,    0,    0,
    0,    0,    0,  306,    0,    0,  683,    0,  307,    0,
  308,    0,    0,    0,    0,  683,    0,    0,  683,    0,
    0,    0,    0,    0,    0,    0,    0,  683,    0,    0,
    0,    0,  683,  683,  683,    0,    0,    0,    0,  683,
  683,  683,    0,  683,    0,  309,    0,  310,    0,    0,
    0,    0,    0,  683,  683,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  311,    0,    0,  312,  313,    0,
    0,    0,    0,    0,  314,    0,    0,    0,    0,  315,
    0,  316,    0,  317,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  294,  295,    0,  296,    0,    0,  318,    0,
    0,  319,    0,  320,    0,  297, 1810,  298,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  321,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  322,    0,    0,  299,    0,    0,  300,  301,
    0,    0,    0,  302,    0,    0,    0,    0,  303,  323,
    0,    0,    0,    0,    0,    0,    0,  304,    0,    0,
    0,    0,  305,    0,    0,    0,  324,  325,    0,    0,
    0,  326,    0,    0,    0,    0,    0,  306,    0,    0,
  327,    0,  307,    0,  308,    0,    0,    0,    0,  328,
    0,    0,  329,    0,    0,    0,    0,    0,    0,    0,
    0,  330,    0,    0,    0,    0,  331,  332,  333,    0,
    0,    0,    0,  334,  335,  336,    0,    0,    0,  309,
    0,  310,    0,    0,    0,    0,    0,  337,  338,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  311,    0,
    0,  312,  313,    0,    0,    0,    0,    0,  314,    0,
    0,    0,    0,  315,    0,  316,    0,  317,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  693,  693,    0,  693,
    0,    0,  318,    0,    0,  319,    0,  320,    0,  693,
 1814,  693,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  321,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  322,    0,    0,  693,
    0,    0,  693,  693,    0,    0,    0,  693,    0,    0,
    0,    0,  693,  323,    0,    0,    0,    0,    0,    0,
    0,  693,    0,    0,    0,    0,  693,    0,    0,    0,
  324,  325,    0,    0,    0,  326,    0,    0,    0,    0,
    0,  693,    0,    0,  327,    0,  693,    0,  693,    0,
    0,    0,    0,  328,    0,    0,  329,    0,    0,    0,
    0,    0,    0,    0,    0,  330,    0,    0,    0,    0,
  331,  332,  333,    0,    0,    0,    0,  334,  335,  336,
    0,    0,    0,  693,    0,  693,    0,    0,    0,    0,
    0,  337,  338,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  693,    0,    0,  693,  693,    0,    0,    0,
    0,    0,  693,    0,    0,    0,    0,  693,    0,  693,
    0,  693,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  685,  685,    0,  685,    0,    0,  693,    0,    0,  693,
    0,  693,    0,  685,  693,  685,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  693,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  693,    0,    0,  685,    0,    0,  685,  685,    0,    0,
    0,  685,    0,    0,    0,    0,  685,  693,    0,    0,
    0,    0,    0,    0,    0,  685,    0,    0,    0,    0,
  685,    0,    0,    0,  693,  693,    0,    0,    0,  693,
    0,    0,    0,    0,    0,  685,    0,    0,  693,    0,
  685,    0,  685,    0,    0,    0,    0,  693,    0,    0,
  693,    0,    0,    0,    0,    0,    0,    0,    0,  693,
    0,    0,    0,    0,  693,  693,  693,    0,    0,    0,
    0,  693,  693,  693,    0,    0,    0,  685,    0,  685,
    0,    0,    0,    0,    0,  693,  693,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  685,    0,    0,  685,
  685,    0,    0,    0,    0,    0,  685,    0,    0,    0,
    0,  685,    0,  685,    0,  685,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  717,  717,    0,  717,    0,    0,
  685,    0,    0,  685,    0,  685,    0,  717,  687,  717,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  685,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  685,    0,    0,  717,    0,    0,
  717,  717,    0,    0,    0,  717,    0,    0,    0,    0,
  717,  685,    0,    0,    0,    0,    0,    0,    0,  717,
    0,    0,    0,    0,  717,    0,    0,    0,  685,  685,
    0,    0,    0,  685,    0,    0,    0,    0,    0,  717,
    0,    0,  685,    0,  717,    0,  717,    0,    0,    0,
    0,  685,    0,    0,  685,    0,    0,    0,    0,    0,
    0,    0,    0,  685,    0,    0,    0,    0,  685,  685,
  685,    0,    0,    0,    0,  685,  685,  685,    0,    0,
    0,  717,    0,  717,    0,    0,    0,    0,    0,  685,
  685,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  717,    0,    0,  717,  717,    0,    0,    0,    0,    0,
  717,    0,    0,    0,    0,  717,    0,  717,    0,  717,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0, 1152, 1152,
    0, 1152,    0,    0,  717,    0,    0,  717,    0,  717,
    0, 1152,  717, 1152,    0,    0, 1152,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  717,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  717,    0,
    0, 1152,    0,    0, 1152, 1152,    0,    0,    0, 1152,
    0,    0,    0,    0, 1152,  717,    0,    0,    0,    0,
    0,    0,    0, 1152,    0,    0,    0,    0, 1152,    0,
    0,    0,  717,  717,    0,    0,    0,  717,    0,    0,
    0,    0,    0, 1152,    0,    0,  717,    0, 1152,    0,
 1152,    0,    0,    0,    0,  717,    0,    0,  717,    0,
    0,    0,    0,    0,    0,    0,    0,  717,    0,    0,
    0,    0,  717,  717,  717,    0,    0,    0,    0,  717,
  717,  717,    0,    0,    0, 1152,    0, 1152,    0,    0,
    0,    0,    0,  717,  717,    0,    0,    0,    0,    0,
    0,    0,    0,    0, 1152,    0,    0, 1152, 1152,    0,
    0,    0,    0,    0, 1152,    0,    0,    0,    0, 1152,
    0, 1152,    0, 1152,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  294,  295,    0,  296,    0,    0,    0, 1152,    0,
    0, 1152,    0, 1152,  297,    0,  298,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, 1152,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, 1152,    0,  299,    0,    0,  300,  301,    0,
    0,    0,  302,    0,    0,    0,    0,  303,    0, 1152,
    0,    0,    0,    0,    0,    0,  304,    0,    0,    0,
    0,  305,    0,    0,    0,    0, 1152, 1152,    0,    0,
    0, 1152,    0,    0,    0,    0,  306,    0,    0,    0,
 1152,  307,    0,  308,    0,    0,    0,    0,    0, 1152,
    0,    0, 1152,    0,    0,    0,    0,    0,    0,    0,
    0, 1152,    0,    0,    0,    0, 1152, 1152, 1152,    0,
    0,    0,    0, 1152, 1152, 1152,    0,    0,  309,    0,
  310,    0,    0,    0,    0,    0,    0, 1152, 1152,    0,
    0,    0,    0,    0,    0,    0,    0,  311,    0,    0,
  312,  313,    0,    0,    0,    0,    0,  314,    0,    0,
    0,    0,  315,    0,  316,    0,  317,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  557,  557,    0,  557,    0,    0,
    0,  318,    0,    0,  319,    0,  320,  557,    0,  557,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  321,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  322,    0,  557,    0,    0,
  557,  557,    0,    0,    0,  557,    0,    0,    0,    0,
  557,    0,  323,    0,    0,    0,    0,    0,    0,  557,
    0,    0,    0,    0,  557,    0,    0,    0,    0,  324,
  325,    0,    0,    0,  326,    0,    0,    0,    0,  557,
    0,    0,    0,  327,  557,    0,  557,    0,    0,    0,
    0,    0,  328,    0,    0,  329,    0,    0,    0,    0,
    0,    0,    0,    0,  330,    0,    0,    0,    0,  331,
  332,  333,    0,    0,    0,    0,  334,  335,  336,    0,
    0,  557,    0,  557,    0,    0,    0,    0,    0,    0,
  337,  338,    0,    0,    0,    0,    0,    0,    0,    0,
  557,    0,    0,  557,  557,    0,    0,    0,    0,    0,
  557,    0,    0,    0,    0,  557,    0,  557,    0,  557,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, 1215, 1215,    0,
 1215,    0,    0,    0,  557,    0,    0,  557,    0,  557,
 1215,    0, 1215,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  557,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  557,    0,
 1215,    0,    0, 1215, 1215,    0,    0,    0, 1215,    0,
    0,    0,    0, 1215,    0,  557,    0,    0,    0,    0,
    0,    0, 1215,    0,    0,    0,    0, 1215,    0,    0,
    0,    0,  557,  557,    0,    0,    0,  557,    0,    0,
    0,    0, 1215,    0,    0,    0,  557, 1215,    0, 1215,
    0,    0,    0,    0,    0,  557,    0,    0,  557,    0,
    0,    0,    0,    0,    0,    0,    0,  557,    0,    0,
    0,    0,  557,  557,  557,    0,    0,    0,    0,  557,
  557,  557,    0,    0, 1215,    0, 1215,    0,    0,    0,
    0,    0,    0,  557,  557,    0,    0,    0,    0,    0,
    0,    0,    0, 1215,    0,    0, 1215, 1215,    0,    0,
    0,    0,    0, 1215,    0,    0,    0,    0, 1215,    0,
 1215,    0, 1215,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 1148, 1148,    0, 1148,    0,    0,    0, 1215,    0,    0,
 1215,    0, 1215, 1148,    0, 1148,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 1215,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, 1215,    0, 1148,    0,    0, 1148, 1148,    0,    0,
    0, 1148,    0,    0,    0,    0, 1148,    0, 1215,    0,
    0,    0,    0,    0,    0, 1148,    0,    0,    0,    0,
 1148,    0,    0,    0,    0, 1215, 1215,    0,    0,    0,
 1215,    0,    0,    0,    0, 1148,    0,    0,    0, 1215,
 1148,    0, 1148,    0,    0,    0,    0,    0, 1215,    0,
    0, 1215,    0,    0,    0,    0,    0,    0,    0,    0,
 1215,    0,    0,    0,    0, 1215, 1215, 1215,    0,    0,
    0,    0, 1215, 1215, 1215,    0,    0, 1148,    0, 1148,
    0,    0,    0,    0,    0,    0, 1215, 1215,    0,    0,
    0,    0,    0,    0,    0,    0, 1148,    0,    0, 1148,
 1148,    0,    0,    0,    0,    0, 1148,    0,    0,    0,
    0, 1148,    0, 1148,    0, 1148,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0, 1166, 1166,    0, 1166,    0,    0,    0,
 1148,    0,    0, 1148,    0, 1148, 1166,    0, 1166,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0, 1148,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0, 1148,    0, 1166,    0,    0, 1166,
 1166,    0,    0,    0, 1166,    0,    0,    0,    0, 1166,
    0, 1148,    0,    0,    0,    0,    0,    0, 1166,    0,
    0,    0,    0, 1166,    0,    0,    0,    0, 1148, 1148,
    0,    0,    0, 1148,    0,    0,    0,    0, 1166,    0,
    0,    0, 1148, 1166,    0, 1166,    0,    0,    0,    0,
    0, 1148,    0,    0, 1148,    0,    0,    0,    0,    0,
    0,    0,    0, 1148,    0,    0,    0,    0, 1148, 1148,
 1148,    0,    0,    0,    0, 1148, 1148, 1148,    0,    0,
 1166,    0, 1166,    0,    0,    0,    0,    0,    0, 1148,
 1148,    0,    0,    0,    0,    0,    0,    0,    0, 1166,
    0,    0, 1166, 1166,    0,    0,    0,    0,    0, 1166,
    0,    0,    0,    0, 1166,    0, 1166,    0, 1166,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0, 1166,    0,    0, 1166,    0, 1166,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0, 1166,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, 1166,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0, 1166,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, 1166, 1166,    0,    0,    0, 1166,    0,    0,    0,
    0,    0,    0,    0,    0, 1166,    0,    0,    0,    0,
    0,    0,    0,    0, 1166,    0,    0, 1166,    0,    0,
    0,    0,    0,    0,    0,    0, 1166,    0,    0,    0,
    0, 1166, 1166, 1166,    0,    0,    0,    0, 1166, 1166,
 1166,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, 1166, 1166,
};
ZYshort yycheck[] = {                                      48,
   49,   49,  218,  314,  729,   85,   82,  182,   51,  328,
  187,  468,  706,  460,  480,  182,  935,  205,  780,   64,
  714,  259, 1026,  417,  827,  548,  863,  812,    0,  814,
  815,  583,  603,    0, 1000,  256, 1129,   46,  256,  876,
  271,    0,    0,    0,  628,  263,  784,  732,  733,  304,
  507, 1108,  101, 1430,  322,  259,   41,  232,  107,  259,
   43,  613,   45,  340,   43,  232,   45,   64,  304,  330,
  356,  310,   43,   43,   45,   45, 1218,    0,  319,  128,
  269,  360,   42,   43,  347,   45,  277,   47,    0,    0,
  716,  971,  929,  663,   43,    0,   45,  277,  272,  259,
  149,  150,   43,  351,   45,  271,  290,   43,  260,   45,
  262,  263,  664,   43,  342,   45,  248,  271,  575,  256,
  163,  164,    0,  283,  693,  332,  573,  376,   41,  337,
  967,  282,  283,  384,  322,  453,  472,  376,  298,  310,
  310,    0,  191,  192,  320,  290,  195,  342,  462,  460,
   43,  345,   45,  433,  290,  602,  256,  337,  710,  259,
  256,  335,  400,  206,  207,  310,  209,  454,    0,  212,
  617,  472,  215,  333,    0,  349,  350,  401,  402,  368,
  290,  272,  629,  630,  631,  632,  633,  236,  347,  457,
  376, 1192,   42,  373,  354,  355,  306,   47,  371,    0,
  657,  361,  260, 1204,  262, 1347,  372,  307,    0,  369,
  488,  547,  440,    0,    0,  259,  333,  263,  372,   43,
  409,   45,  435,  260,   43,  262,   45,  260, 1321,  262,
  263,  376, 1069,  995,  520,    0,  282,  426,  923,  400,
  697,   43,  417,   45,  442,  440,  547,  433,  328,  298,
  463,  300,  301,  441,  376,  346,  433,  544,  307,  308,
 1045,  524,  442, 1048,  453,  442,  315,  315,  472,  445,
  319,  320,  449,  322,  592,  960,  446, 1157,    0, 1064,
  906,  489,  559,  332,  333,  334,  335,  276,  488,  460,
  568,  290,  424,  845,  532,  533,  981,  611,  850,  282,
  410,  446,  259,  282,    0,  489,  617,    0,  404,  893,
  406,  282,  282,  614,  521,  432,  900,  901,  507,  419,
  366,  280,  280,  280,  548,  499,  315,  287,  614,   43,
  290,   45,   43,  581,   45,  614,    0,    0,   43,  516,
   45,  282,  478,  547,  607,  606,  282,  484, 1490,  590,
 1492,  453,  282,  621,  924,  610,  260,  588,  262, 1360,
  611,  610,    0,    0,  811,  524,  557,  260,  568,  262,
  263,  610,  819,  820,  610,  288,  289,  557,  772,  573,
  949,  575,  259,  432,  605,  434,  614,  844,  576,  282,
  283,  440,   43,  438,   45,  546,  614,  356,  356,  356,
 1319,  518,  679,  592,  376,  673,  482,  584,  606,    0,
  614,    0, 1378,  965,  652,  606,  462,  376,  376,  376,
  469,  479, 1799,  503,  601,  505,  606,  884,  565,  489,
  567, 1128,    0,  356,  600, 1272,  260,  287,  262,  263,
  614,  438,  479, 1323,  488,  356,  600,  446,  607,  263,
 1287,  356, 1289,  376,  614,  902,  903,  904,  282,  283,
 1340,  433,  614,  282,  376,  376,  433,  614,  282,  518,
  519,  376,  568,  522,  433,  433,  433,  462, 1315,  478,
  282,  283, 1244,  593,  722, 1578,  674,  530,  477,  569,
  592,  668,  454,  476, 1065, 1233, 1234, 1498,  376,  411,
  259,  544,  411,  546, 1242,  476, 1343, 1344, 1092,  697,
  433, 1568,  545, 1570, 1571, 1572,  565,  376,  567,  269,
  469,  433,  433,  506,  568,  448,  453,  484,  433,  489,
 1082, 1083,  581,  411,  583,  506,  506,   41,  415,  432,
   44,  590,  551,  619,  376,  297, 1116, 1117,  259,  461,
  376,  611,  511,  511,  511,  433,  462,  506,  259,  453,
  514,  276,  611,  612,  613,  506, 1118,  272,  282,  283,
  506,  282,  283,  466,  433,  376,  506,  282, 1035, 1672,
  332,  337,  544,  461,  376,  411,  479,  298,  511,  376,
  376,  634,  903,  904,  988, 1475, 1167,  772,  992,  511,
  511,  433,  296, 1660, 1661,  614,  511,  433,  565, 1066,
  567,  376,  601,  662,  663,  664, 1168,  885,  368,  531,
  314,  538,  333,  516, 1628,  674, 1320, 1324,  939,  461,
  609,  282,  433,  511,  356,  461,  548,  549, 1085, 1605,
  549,  433,  290,  354,  355,  469,  433,  433,  442,  262,
  361, 1098,  511,  531,  376,  698,  415,  614,  369,  708,
  709,  710,  310,  356,  259,  592, 1546, 1547,  433, 1549,
  548,  549, 1410,  566,  461,  461, 1733,  425,  400,  511,
  376,  869,  506,  376,  297,  511,  442,  864,  403,  548,
   42,   43,  356,   45,  737,   47,  602,  614,  592,  531,
  612,  453,  865,  746,  269,  531,  749,  750,  751,  425,
  511,  433,  376,  376,  415, 1286,  548, 1288,  432,  511,
  613,  432,  548,  549,  511,  511,   42,   43,  376,   45,
  531,   47,  256,  776,  612,  259,  779,  433,  376,  376,
  433,   43,  657,   45,  531,  531,  511,  548,  496,  792,
  927,  346,  466,  518,  931,  466,  260,  507,  262,  263,
  271,  548,  548,  557,  275,  479, 1646,  356,  479,  433,
  433,   43, 1469,   45, 1085,  963,  951,  952,  282,  283,
  612,  944,  697,  548,  448,  376,  612,  376,  356,  511,
   43,  406,   45,  297,  472,  433,  433,  294,  295,  296,
  297,  557,  516,  368,  371,  516,  303,  304,  376,  306,
 1647, 1648,  606,  988,  311,  511,  310,  992,  511,  316,
  317,  318,  538,  461, 1281, 1000,  612, 1512,  325,  326,
 1005, 1225,  329,  330, 1009, 1715,  903,  904,  887,  336,
  337,  338,  433, 1540,  433,  339,  296,  511,  511, 1037,
  606,   43,  566,   45,  259,  566, 1541,  276,  263,   43,
 1740,   45, 1742, 1743,  314,  433,  272,  947,  531,  547,
 1108,  951,  952,  511,  511,  924,  425, 1040,  614,  259,
 1574,   40,  497,  263,   43,  548,   45,   43,  955,   45,
  259,  492,  425,  531,  263,  419,  315,  272,  273,  613,
  296, 1598,  613,  614,  462,  950, 1857,  263,  386,  256,
  548,  548,  318,  962, 1608,  356, 1796,  310,  314,  423,
  511,  256,  511,   43,  259,   45,  282,  421,  432,  270,
  336, 1716,   43,  976,   45,  287,  614,  980, 1018,  462,
  983,  984,  507,  511,  987, 1630,  339,  496,  445,  290,
  356,  994,  462,  998,  270, 1758,  272, 1414,  299,  300,
  301,  562,  466,  496,  337,  459,   41,   42,   43,  527,
   45,  287,   47, 1016,  290,  479,  436,  259, 1372, 1930,
  282,  263,  479,  299,  300,  301, 1174,  256, 1031,  259,
 1039,  384, 1872,  276,  263, 1914,  259, 1174, 1521,  476,
  263,  326, 1396, 1397, 1766,  374, 1317,  530, 1088,  272,
  282,  283,  516,  260,  508,  262,  263,  527,   40,  272,
  273,   43,  515,   45,  256,  297,  486, 1484,  298,  282,
 1097,  263,  437,  510,  453,  260,   40,  262,  263,   43,
  575,   45,   43,  290,   45,  451,  511, 1222, 1223, 1687,
 1225,  277,  458, 1691,  459, 1222, 1223,  437,  477, 1139,
  270,  408,  566,  333, 1252, 1945,  459, 1116, 1117,  442,
 1536,  272,  297, 1835,   43,  610,   45, 1126,  614,  459,
  290, 1843,  283, 1808,  354,  355,  583,  371, 1155,  273,
  282,  361,  374, 1550,  296,  442,  259,  459,  282,  369,
  447,  260,  599,  262,  263,  480,  481,  376,  256,  613,
 1748,  337,  314,  270,  520,  508,  613,  611,  311, 1881,
  493,  526, 1171,  282,  283,  531,  282,  533, 1522,  454,
  614,  263,  610,  290,  475,  298,  614, 1180,  297, 1182,
  260,  482,  262,  263,  292, 1190,  526,  373,  517,  496,
  282,  371,  435,  558,   43,  652,   45,  305,  360,  475,
  432,  309,  282,  283,  357,  358,  482,  664,  509,  272,
  333,  282,  669,  592,  437,  259,  263, 1220,  558,  676,
  463, 1638,  601, 1308,  557,  551,  548, 1267, 1376,  558,
 1270,  354,  355,  509,  466,  282,  459, 1372,  361, 1279,
 1243,  607,   43, 1378,   45,  344,  369,  479,  614, 1656,
  707, 1336,  287,  710,  298,  259,  442,  487,  611,  544,
 1408, 1396, 1397,  745,  280, 1682,   42,   43,  750,   45,
  523,   47,  335,  606, 1301,  517, 1366, 1694,  260,  261,
  262,  263,  489, 1569,  516,  310,  349,  350,  610,  333,
 1380,  444,  414, 1302,  298,  297,  260,  261,  262,  263,
  282,  283,  274,  489,  423, 1442,  414, 1444,  290,  614,
  354,  355,  613,  432,  339,  297,  558,  361,  282,  283,
 1974,  282,  283, 1760,  306,  369,  290,  501,  476,  333,
  332, 1367,  304,  297,  566,  558,  297,  613,  612,   40,
  514,  489,   43,  596,   45, 1385,  326,  466, 1496,  572,
  354,  355,  377,  282,  283,  418,  813,  361,  611,  256,
  479, 1366,   43,  426,   45,  369,  263,  298,  297,  259,
 1568,  557, 1570, 1571, 1572, 1380, 1662, 1656, 1664, 1665,
  418,  613,  272, 1800,  614,  472,  494, 1522,  845,  452,
  272,  848,  430,  850, 1831, 1832, 1803,  516,  538,  479,
  553, 1755,  333, 1820,   41,   42,   43,  487,   45,  489,
   47,  260,  520,  262,  419,  417, 1553, 1420,  526,  876,
  606,  426, 1776,  354,  355,  611, 1435,  535,  410,  461,
  361,  259,  445,  282,  459,  263,  499, 1791,  369,  299,
  418,  423,  302,  303,  272,   41,  410,  566,   44,  462,
  432,  453,  430,   43,  551,   45, 1465, 1460, 1467,  423,
  547,  918, 1660, 1661,  489, 1736,  551,   43,  432,   45,
 1605,  432,  929,  930,  454,  409, 1479,  614,   43, 1488,
   45,  282,  283,  508,  466,  942,   43,  260,   45,  262,
  409,  614,  426,  950,  613,  257,  258,  479,  274,  409,
  480,  481,  466,  432, 1858,  466,  614,  426,  965,  282,
  967,  287,  969,  593,  520,  479,  426,  259,  479, 1805,
 1696, 1875, 1527, 1936, 1529, 1530,   41,  614,   41,   44,
  272,   44, 1886,   40,  516, 1733,   43,  466,   45, 1579,
  614,   43,  418,   45,  298,  270,  374,  272, 1961, 1962,
  479,  614,  516,  599,  430,  516,  562,  563,  551,  260,
  261,  262,  263,  609,  544,  290,  282, 1921, 1922,  270,
  614,  282, 1926,  599,  299,  300,  301, 1582, 1754,  333,
  263,  282,  283,  609,  566,  551,  611,  516,   40,  290,
  592,  260,  467,  262,  263, 1866,  297,   43,  368,   45,
  354,  355,  566,  256, 1607,  566,  259,  361, 1065,  462,
  614,  593, 1069, 1616,  283,  369,  614, 1622, 1623, 1624,
 1755,  412,  482,  483,  614, 1082, 1083,  593,  594,  593,
 1639,  613,  531,  270, 1643,  272,  260,  566,  262,  409,
  260, 1776,  262,  263,  260,  614,  262,  263,  551,  613,
  287, 1108,  613,  290,   40, 1112, 1791, 1114,  322,  323,
 1669, 1118,  299,  300,  301,  614,   43, 1124,   45,    8,
  260, 1674,  262,  263,  404,  514,  406,  297,   17,   43,
  448,   45, 1687,  614,  613,   24, 1691,  614,  260,  517,
  262,  263,  282,  283, 1697,  260,  614,  262,  263, 1156,
 1705,  614,  259, 1708,  288,  289,  282,  283,    4,  256,
 1167, 1168,  520,  521, 1985,   11,  272,  282,  283,  335,
  614,   17,  423, 1858,  551,  282,  283,  284,  285,  548,
  558,  432,   58,  349,  350,  362, 1741,  264,  265,  266,
 1875,  554, 1751, 1748,  260,  260,  262,  262,  263,  614,
  475, 1886,  614,  260,  261,  262,  263,  482,  260,  286,
  262,  263,  551,  270,  614,  466, 1769,  282,  283, 1809,
 1773, 1774, 1775,  401,  402,  282,  283,  259,  479,  335,
  282,  283,  297,  290,  509,  259, 1921, 1922,  307,  308,
  297, 1926,   40,  349,  350,   43,  260,   45,  262,  263,
  416, 1258, 1259,  573,  574,  575,  270,  456,  457,  259,
  426,  368,  459,  460,  260,  516,  262,  263,  345,  272,
  273,  259, 1825,   43,  260,   45,  262,  263, 1868,  256,
 1287,  560, 1289,  260,  261,  262,  282,  283,  475, 1842,
  572, 1850, 1850, 1846, 1847,  482, 1849,   43, 1853,   45,
 1307, 1308,  409,    0,  259, 1312,  432,  272, 1315,  492,
  614,  417,  418, 1868,  614,  566,  260,  294,  262,  263,
  426,   41,  509, 1876, 1877,  614,  614, 1880,  614, 1336,
 1889,  614,  259,  499,  514, 1342,  614, 1344,  613,  479,
  466,  611,  259, 1350,  341,  259,  452,  487,  474,  489,
  414,  259,   43,  479,   45,  282,  283,  260,  423,  262,
  263,  259,  613,  518,  479,  442,  423,  432,  282,  283,
  335,  298,  487,  337,  489,  432, 1935, 1936,   40,  282,
  283,   43,  614,   45,  349,  350,  260, 1967,  262,  263,
  516,  614,  360,  499,  259,  283, 1955, 1955,  283,  259,
 1980,  466, 1961, 1962, 1984,  307,  333, 1966, 1988,  466,
 1990, 1970, 1419,  260,  479,  262,  263,  469,  582,  551,
 1979,  260,  479,  262,  263,  272,  613,  354,  355,  614,
  614,  271,  591,  272,  361,  591,  375,  557,  274,  470,
  566,  346,  369,  569,  570,  419,  259,  378,  614,  391,
  270,  516, 1459,  593,  506,  421,  545,  382,  421,  516,
  520,  426,  260,  261,  262,  263,  573,  574,  575,  385,
   40,  272,   43, 1480,   45,  486,  489,  271,  593,  299,
  300,  301, 1489,  320,  282,  283,  588,  613,  335,  259,
  274,  388,  290,   43,  586,   45,  335,  574,  390,  297,
  262,  566,  349,  350,  394,  432,  392,    0,  614,  566,
  349,  350,  282,  283,  260,  316,  262, 1524, 1525,  486,
 1527,  450, 1529, 1530,   43,  397,   45,  304,  387, 1536,
   40,  364, 1539,   43,  499,   45,  282,  283,   43,  466,
   45,   43,  364,   45,  256,  283,  489,  259,  613,  259,
  362,  263,  479, 1560, 1561,  614,  613,  480,  425,  256,
  272, 1568,  380, 1570, 1571, 1572,  263,  606,  259,   40,
  304,  288,   43,  277,   45, 1582,  271,  416,  587,  426,
  292,  278,  279,  263,  281, 1592, 1593,  426,  445,  516,
  609,  282,  283,  305,  291,  271,  293,  309,  260,  261,
  262,  263,  294,  446,  320,  320,  450,  320,  259,  487,
  445,  572,  470,  520,  282, 1622, 1623, 1624,  572,  259,
  282,  283,  486,  273,  321,  423,  508,  324,  325,  259,
  610,  360,  329,  614,  432,  297,  295,  334,  256,  566,
  377,  406,  260,  425,  262,  263,  343,  528,  449,  614,
  572,  348,  499, 1660, 1661,  475,  540,  528,  463,  425,
  499,  373,  482,  610,  270,  288,  363,  287,  466,  356,
  271,  368,  606,  370,  530,  271,  271,  425,  588,  376,
  421,  479,  310,  373,  485,  425,  613,  614,  259,  509,
  395,  476,  297,  299,  300,  301,  259,  259, 1705, 1706,
  609, 1708,  414,   44,  505,  413, 1713,  613,  405,  274,
  407,  282,  283,  284,  285,  556,  532,  613,  516,  295,
  406,  522,  383,  561,  288,  437, 1733,  424,  529,  320,
  427,  428,  282,  283, 1741,  419,  433,  434,  376,  290,
  259,  393,  439,  339,  441,  376,  443,  459,  436,  270,
  260,  261,  262,  263,  259,  507,  288,  272,  260,  560,
  262,  423,  365,  282,  283,  284,  285,  614,  566,  555,
  432,  468,  282,  283,  471,  614,  473,  282,  283,  580,
  282,  283,  494,  259,  259,  278,  279,  297,  281,  260,
  408,  262,  263,  613,  491,  558,  259,  271,  291,  271,
  293,  274,  460,  604,  466,  502,  607,  608,  520,  331,
  426,  282,  283,  614,  526,  613,  416,  479,  511,  399,
  335,  450,  519,  535,  442,  421,  297,  404,  321,  447,
  561,  324,  325,  295,  349,  350,  329,  511,  390,  536,
  537,  334,  421,  290,  541,  493,  558,  511,  581,  610,
  343,  259,  353,  550,  516,  348,  588,  277,  561,  272,
  572,  267,  559,  459,  332,  562,  273,  272,  512,  475,
  363,  290,  320,  495,  571,  368,  482,  370,  496,  576,
  577,  578,  432,  376,  610,  396,  583,  584,  585,  418,
   40,   41,   42,   43,   44,   45,  421,   47,  437,  611,
  597,  598,  614,  509,  566,  366, 1913,  268,   58,  505,
  290,  426,  405,  423,  407,  381,  466,  614,  304,  480,
  440,  390,  432,  497,  474,  256,  599,  373,  310,  479,
  335,  424,  430,  590,  427,  428,  271,  614,  446,  320,
  433,  434,  561,  289,  349,  350,  439,  398,  441,  319,
  443,  613,  423,  259,  290,  270,  466,  417,  599,  497,
 1967,  432,  366,  452,  367,  561,  516,  298,  438,  479,
  429,  544,  556, 1980,  555,  468,  367, 1984,  471,  418,
  473, 1988,  406, 1990,  499,  368,  555,  613,  296,  379,
  259, 1527,  499, 1529, 1530,  466,  556,  476,  491,  499,
  602,  296,  333,  499,  421,  536,  516,  613,  479,  502,
  606,  607,  608,  418,  390,  611,  566,  296,  614,  569,
  570,  426,  296,  354,  355,  256,  519,  599,  296,  260,
  361,  262,  263,  296,    0,    0,  433,   41,  369,  614,
  259,  341,  259,  536,  537,  516, 1582,  614,  541,  283,
  259,  557,  425,  277,  610,  614,  566,  550,  445,  259,
  613,  320,  426,  613,  561,  376,  559,  445,  366,  562,
  497,  270,  614,  406,  368,  259,  777,  851,  571,  677,
  955, 1181,  197,  576,  577,  578, 1622, 1623, 1624,  197,
  583,  584,  585, 1667,  499,  566,  494, 1346, 1174,  614,
  195,  801, 1350,  613,  597,  598,  256,  887,  674,  708,
  260, 1619,  262,  263, 1408,  546, 1029,  496,  952,  269,
  270,  271,  272,   43,  274,   45,  276,  277,  278,  279,
 1584,  281,  282,  283, 1138,  236, 1639,  287,  288,  289,
  290,  291,  613,  293, 1946, 1676,  296,  297, 1585,  299,
  300,  301,  302,  303,  304, 1337, 1724, 1085, 1565,  904,
  310,  105,  312,  313,  314,  315,  316,  317, 1727, 1705,
  320,  321, 1708,   11,  324,  325, 1604,  408, 1009,  329,
 1638, 1421,  332, 1544,  334,  335,  703,  337,  338,  339,
  340,  507, 1037,  343,   37,  545,  112,  347,  348,  349,
  350,  351,  669,  353,  254, 1741,  167,  403,  977,  614,
  400,  442,  223,  363,  364,  365,  447,  177,  368, 1520,
  370, 1216,  372,  373,  740,  375,  376,  377,  378,  379,
  380,  381,  382,  383,  384,  385,  386,  387,  388, 1777,
  390,  391,  392,  393,  394,  395,  396,  397,  398,  399,
 1522, 1887,  572,  403, 1834,  405,  406,  407,  408,  409,
 1528, 1848, 1252, 1252, 1382,  496, 1874,  417,  545,  419,
  420,  421,  422,  423,  424,  425,  426,  427,  428,  429,
 1601,  431,  432, 1234,  434,  435, 1692,  437,  241,  439,
  748,  441,  442,  443,  422,  445,  446,  447,  686,  449,
  450, 1473, 1809,  453,  912,  954, 1176,  599, 1589,  459,
  460,  869,  462,  463,  464,  465,  466,  467,  468,   -1,
 1594,  471, 1567,  473,   -1,  475,  476,  477,  478,  479,
   -1,   -1,  482,  483,   -1,  485,   -1,   -1,   -1,  489,
  260,  491,  262,  263,   -1,   -1,  496,  497,   -1,  499,
   -1,   -1,  502,   -1,   -1,  505,   -1,  507,  508,  509,
  510,   -1,  282,  283,   -1,   -1,  516,   -1,   -1,  519,
  520,   -1,  522,  523,  524,   -1,   -1,  527,   -1,  529,
  530,   -1,   -1,   -1,  534,   -1,  536,  537,  538,  539,
   -1,  541,   -1,   -1,   -1,  545,   -1,   -1,   -1,   -1,
  550,   -1,  552,   43,   -1,   45,   -1,  557,   -1,  559,
  560,  561,  562,  272,  564,   -1,  566,   -1,   -1,   -1,
   -1,  571,   -1,   -1,  272,   -1,  576,  577,  578,  579,
  580,  581,   -1,  583,  584,  585,   -1,  587,  588,   -1,
   -1,   -1,  592,   -1,  594,  595,  596,  597,  598,  599,
  600,  601,  602,  603,  604,   -1,  606,  607,  608,  318,
  610,  611,   -1,  613,  614,   40,   41,   42,   43,   44,
   45,   -1,   47,  332,   -1,   -1,   -1,  336,   -1,   -1,
   -1,   -1,   -1,   58,   -1,   -1,   -1,  335,   -1,   -1,
   -1,   -1,   -1,   -1,  327,  328,   -1,  356,   -1,   -1,
   -1,  349,  350,  423,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  432,   -1,   -1,   -1,  349,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  359,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  367,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  466,   -1,   -1,   -1,
  409,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  479,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  426,   -1,  417,
  418,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  426,   -1,
   -1,   -1,  430,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  451,   -1,   -1,   -1,  516,   -1,   -1,  458,
   -1,   -1,   -1,   -1,  452,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  260,   -1,  262,  263,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  271,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  282,  283,   -1,   -1,  566,   -1,   -1,   -1,
   -1,  499,   -1,   -1,   -1,   -1,   -1,  297,   -1,   -1,
   -1,  520,  521,   -1,   -1,   -1,  499,   -1,   -1,   -1,
  503,  504,  531,   -1,  533,   -1,   -1,   -1,   -1,   -1,
   -1,  256,   -1,   -1,   -1,  260,   -1,  262,  263,   -1,
   -1,   -1,   -1,  613,  269,  270,  271,  272,  531,  274,
   -1,  276,  277,  278,  279,   -1,  281,  282,  283,  542,
  543,   -1,  287,  288,  289,  290,  291,   -1,  293,   -1,
   -1,  296,  297,   -1,  299,  300,  301,  302,  303,  304,
   -1,   -1,   -1,   -1,   -1,  310,   -1,  312,  313,  314,
  315,  316,  317,   -1,   -1,  320,  321,   -1,  607,  324,
  325,   -1,   -1,   -1,  329,  614,   -1,  332,   -1,  334,
  335,   -1,  337,  338,  339,  340,  614,   -1,  343,   -1,
   -1,   -1,  347,  348,  349,  350,  351,   -1,  353,   -1,
   -1,  421,   -1,  423,   -1,  425,   -1,   -1,  363,  364,
  365,   -1,  432,  368,   -1,  370,   -1,  372,  373,   -1,
  375,  376,  377,  378,  379,  380,  381,  382,  383,  384,
  385,  386,  387,  388,   -1,  390,  391,  392,  393,  394,
  395,  396,  397,  398,  399,   -1,  466,   -1,  403,   -1,
  405,  406,  407,  408,  409,   40,   41,   -1,   43,  479,
   45,   -1,  417,   -1,  419,  420,  421,  422,  423,  424,
  425,  426,  427,  428,  429,   -1,  431,  432,   -1,  434,
  435,   -1,  437,   -1,  439,   -1,  441,  442,  443,   -1,
  445,  446,  447,   -1,  449,  450,  516,   -1,  453,   -1,
   -1,   -1,   -1,   -1,  459,  460,   -1,  462,  463,  464,
  465,  466,   -1,  468,   -1,   -1,  471,   -1,  473,   -1,
  475,  476,  477,  478,  479,   -1,   -1,  482,  483,   -1,
  485,   -1,   -1,   -1,  489,   -1,  491,   -1,  327,  328,
   -1,  496,  497,   -1,  499,   -1,  566,  502,   -1,   -1,
  505,   -1,  507,  508,  509,  510,   -1,   -1,   -1,   -1,
  349,  516,   -1,   -1,  519,  520,   -1,  522,  523,  524,
  359,   -1,  527,   -1,  529,  530,   -1,   -1,  367,  534,
   -1,  536,  537,  538,  539,   -1,  541,   -1,   -1,   -1,
  545,   -1,   -1,  613,   -1,  550,   -1,  552,   -1,   -1,
   -1,   -1,  557,   -1,  559,  560,  561,  562,   -1,  564,
   -1,  566,   -1,   -1,   -1,   -1,  571,   -1,   -1,   -1,
   -1,  576,  577,  578,  579,  580,  581,   -1,  583,  584,
  585,   -1,  587,  588,   -1,   -1,   -1,  592,   -1,  594,
  595,  596,  597,  598,  599,  600,  601,  602,  603,  604,
   -1,  606,  607,  608,   -1,  610,  611,   40,  613,  614,
   43,   -1,   45,   -1,   -1,   43,   -1,   45,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  260,   -1,  262,  263,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  278,  279,   -1,  281,  282,  283,   -1,
   -1,   -1,   -1,  288,  289,  290,  291,   -1,  293,   -1,
  499,  296,  297,   -1,  503,  504,   -1,   -1,   -1,  304,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  321,   -1,   -1,  324,
  325,   -1,  531,   -1,  329,   -1,   -1,   -1,   -1,  334,
   -1,   -1,   -1,  542,  543,   -1,   -1,   -1,  343,   -1,
   -1,   -1,   -1,  348,   -1,   -1,   -1,   40,   41,   -1,
   43,   -1,   45,   -1,   -1,   -1,   -1,   -1,  363,   -1,
   -1,   -1,   -1,  368,   -1,  370,   -1,   -1,   -1,   -1,
  375,   -1,  377,  378,  379,   -1,  381,  382,  383,   -1,
  385,  386,  387,  388,   -1,  390,  391,  392,  393,  394,
  395,  396,  397,  398,  399,   -1,   -1,   -1,   -1,   -1,
  405,   -1,  407,   -1,   43,   -1,   45,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  423,  424,
   -1,   -1,  427,  428,   -1,   -1,   -1,  432,   -1,  434,
   -1,   -1,   -1,   -1,  439,   -1,  441,   -1,  443,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  260,   -1,  262,
  263,  466,  260,  468,  262,  263,  471,   -1,  473,   -1,
   -1,  476,   -1,  478,  479,   -1,   -1,   -1,   -1,  282,
  283,   43,   -1,   45,  282,  283,  491,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  297,   -1,   -1,  502,   -1,  297,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  516,   -1,   -1,  519,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  536,  537,   -1,   -1,   -1,  541,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  550,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  559,   -1,   -1,  562,   -1,   -1,
   -1,  566,   -1,   -1,   -1,   -1,  571,  260,   -1,  262,
  263,  576,  577,  578,   -1,   -1,   -1,   -1,  583,  584,
  585,   -1,  587,   -1,   -1,  278,  279,   -1,  281,  282,
  283,   -1,  597,  598,   -1,   -1,  289,  290,  291,   -1,
  293,   -1,   -1,  296,  297,  610,   -1,   -1,  613,  614,
   -1,  304,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  423,  260,   -1,  262,  263,  423,   -1,   -1,  321,  432,
   -1,  324,  325,   -1,  432,   -1,  329,   -1,   -1,   -1,
   -1,  334,   -1,  282,  283,   -1,   -1,   -1,   -1,   -1,
  343,   -1,   -1,   -1,   -1,  348,   -1,   -1,  297,   40,
   41,   -1,   43,  466,   45,   -1,   -1,   -1,  466,   -1,
  363,   -1,   -1,   -1,   -1,  368,  479,  370,   -1,   -1,
   -1,  479,  375,   -1,  377,  378,  379,   -1,  381,  382,
  383,   -1,  385,  386,  387,  388,   -1,  390,  391,  392,
  393,  394,  395,  396,  397,  398,  399,   -1,   -1,  271,
  272,   -1,  405,  516,  407,   -1,   -1,   -1,  516,   -1,
  282,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  423,  424,   -1,   -1,  427,  428,   -1,   -1,   -1,  432,
  538,  434,   -1,   -1,   -1,   -1,  439,   -1,  441,   -1,
  443,   -1,   -1,   43,   -1,   45,  318,   -1,   -1,   -1,
   -1,   -1,   -1,  566,   -1,   -1,   -1,   -1,  566,   -1,
  332,   -1,   -1,  466,  336,  468,   -1,   -1,  471,   -1,
  473,   -1,   -1,  476,  423,  478,  479,   -1,   -1,   -1,
   -1,   -1,   -1,  432,  356,   -1,   -1,   -1,  491,   -1,
   -1,   -1,   -1,   -1,  366,   -1,   -1,   -1,   -1,  502,
  613,   -1,   -1,   -1,   -1,  613,  614,   -1,   -1,   -1,
   -1,   -1,   -1,  516,   -1,   -1,  519,  466,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  479,   -1,   -1,  536,  537,   -1,  267,  409,  541,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  550,   -1,  421,
   -1,   -1,   -1,   -1,  426,   -1,  559,   -1,   -1,  562,
   -1,   -1,   -1,  566,   -1,   -1,   -1,  516,  571,  260,
   -1,  262,  263,  576,  577,  578,   -1,   -1,   -1,  451,
  583,  584,  585,   -1,  587,  316,  458,  278,  279,  538,
  281,  282,  283,   -1,  597,  598,   -1,   -1,  289,  290,
  291,   -1,  293,   -1,   -1,  296,  297,  610,  339,  340,
  613,  614,   -1,  304,   -1,   -1,   -1,  566,   -1,   -1,
   -1,  316,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  321,   -1,   -1,  324,  325,   -1,   -1,  368,  329,   -1,
   -1,   -1,   -1,  334,  339,  340,   -1,   -1,  520,   -1,
   -1,   -1,  343,   -1,   -1,   -1,   -1,  348,   -1,  531,
  260,  533,  262,  263,  613,  614,   -1,   -1,   -1,   -1,
   -1,   -1,  363,  368,   -1,   -1,   -1,  368,   -1,  370,
   -1,   -1,  282,  283,  375,   -1,  377,  378,  379,  561,
  381,  382,  383,   -1,  385,  386,  387,  388,  429,  390,
  391,  392,  393,  394,  395,  396,  397,  398,  399,   41,
   42,   43,   44,   45,  405,   47,  407,   -1,  449,   -1,
   -1,   -1,  453,   -1,   -1,   -1,   58,   -1,  459,  460,
   -1,   -1,  423,  424,  429,  607,  427,  428,   -1,   -1,
   -1,  432,  614,  434,   -1,  476,   -1,   -1,  439,   -1,
  441,   -1,  443,   -1,  449,   -1,   -1,   -1,  453,   -1,
   -1,   -1,   -1,   -1,  459,  460,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  505,  466,   -1,  468,   -1,   -1,
  471,  476,  473,   -1,   -1,  476,   -1,  478,  479,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  491,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  505,  502,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  516,   -1,   -1,  519,  560,
   -1,   -1,  432,  564,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  536,  537,   -1,  579,   -1,
  541,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  550,
   -1,  592,   -1,  594,   -1,  560,  466,   -1,  559,  564,
   -1,  562,   -1,  604,   -1,  566,  607,   -1,   -1,  479,
  571,   -1,   -1,  614,  579,  576,  577,  578,   -1,   -1,
   -1,   -1,  583,  584,  585,   -1,  587,  592,   -1,  594,
   -1,   -1,   -1,   -1,   -1,   -1,  597,  598,   -1,  604,
   -1,   -1,  607,   -1,   -1,   -1,  516,   -1,   -1,  610,
   -1,   -1,  613,  614,  256,   -1,   -1,   -1,  260,   -1,
  262,  263,   -1,   -1,   -1,   -1,   -1,  269,  270,  271,
  272,   -1,  274,   -1,  276,  277,  278,  279,   -1,  281,
  282,  283,   -1,   -1,   -1,  287,  288,  289,  290,  291,
   -1,  293,   -1,   -1,  296,  297,  566,  299,  300,  301,
  302,  303,  304,   -1,   -1,   -1,   -1,   -1,  310,   -1,
  312,  313,  314,  315,  316,  317,   -1,   -1,  320,  321,
   -1,   -1,  324,  325,   -1,   -1,   -1,  329,   -1,   -1,
  332,   -1,  334,  335,   -1,  337,  338,  339,  340,   -1,
   -1,  343,   -1,  613,   -1,  347,  348,  349,  350,  351,
   -1,  353,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  363,  364,  365,   -1,   -1,  368,   -1,  370,   -1,
   -1,  373,   -1,  375,  376,  377,  378,  379,  380,  381,
  382,  383,  384,  385,  386,  387,  388,   -1,  390,  391,
  392,  393,  394,  395,  396,  397,  398,  399,   -1,   -1,
   -1,  403,   -1,  405,  406,  407,  408,  409,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  417,   -1,  419,  420,  421,
  422,  423,  424,  425,  426,  427,  428,  429,   -1,  431,
  432,   -1,  434,  435,   -1,  437,   -1,  439,   -1,  441,
  442,  443,   -1,  445,  446,  447,   -1,  449,  450,   -1,
   -1,  453,   -1,   -1,   -1,   -1,   -1,  459,  460,   -1,
  462,  463,  464,  465,  466,   -1,  468,   -1,   -1,  471,
   -1,  473,   -1,  475,  476,  477,  478,  479,   -1,   -1,
  482,  483,   -1,  485,   -1,   -1,   -1,  489,   -1,  491,
   -1,   -1,   -1,   -1,  496,  497,   -1,  499,   -1,   -1,
  502,   -1,   -1,  505,   -1,  507,  508,  509,  510,   41,
   42,   43,   44,   45,  516,   47,   -1,  519,  520,   -1,
  522,  523,  524,   -1,   -1,  527,   58,  529,  530,   -1,
   -1,   -1,  534,   -1,  536,  537,  538,  539,   -1,  541,
   -1,   -1,   -1,  545,   -1,   -1,   -1,   -1,  550,   -1,
  552,   -1,   -1,   -1,   -1,  557,   -1,  559,  560,  561,
  562,   -1,  564,   -1,  566,   -1,   -1,   -1,   -1,  571,
   -1,   -1,   -1,   -1,  576,  577,  578,  579,  580,  581,
   -1,  583,  584,  585,   -1,  587,  588,   -1,  290,   -1,
  592,   -1,  594,  595,  596,  597,  598,  599,   -1,  601,
  602,  603,  604,   -1,  606,  607,  608,   -1,  610,  611,
   -1,  613,  614,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  375,   -1,  377,  378,  379,   -1,  381,
  382,  383,   -1,  385,  386,  387,  388,   -1,  390,  391,
  392,  393,  394,  395,  396,  397,  398,  399,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  260,   -1,
  262,  263,   -1,   -1,   -1,   -1,   -1,  269,  270,  271,
  272,   -1,  274,   -1,  276,  277,  278,  279,   -1,  281,
  282,  283,   -1,   -1,   -1,  287,  288,  289,  290,  291,
   -1,  293,   -1,   -1,  296,  297,   -1,  299,  300,  301,
  302,  303,  304,   -1,   -1,   -1,  478,   -1,  310,   -1,
  312,   -1,  314,  315,  316,  317,   -1,   -1,  320,  321,
   -1,   -1,  324,  325,   -1,   -1,   -1,  329,   -1,   -1,
   -1,   -1,  334,   -1,   -1,   -1,   -1,  339,  340,   -1,
   -1,  343,   -1,   -1,   -1,  347,  348,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  363,  364,   -1,   -1,   -1,  368,   -1,  370,   -1,
   -1,   -1,   -1,  375,   -1,  377,  378,  379,  380,  381,
  382,  383,  384,  385,  386,  387,  388,   -1,  390,  391,
  392,  393,  394,  395,  396,  397,  398,  399,   -1,   -1,
   -1,  403,   -1,  405,  406,  407,   -1,  409,   41,   42,
   43,   -1,   45,   -1,   47,   -1,   -1,   -1,   -1,  421,
  422,  423,  424,  425,  426,  427,  428,  429,   -1,  431,
  432,   -1,  434,   -1,   -1,  437,   -1,  439,  610,  441,
   -1,  443,  614,  445,  446,   -1,   -1,  449,   -1,   -1,
   -1,  453,   -1,   -1,   -1,   -1,   -1,  459,  460,   -1,
  462,   -1,  464,  465,  466,   -1,  468,   -1,   -1,  471,
   -1,  473,   -1,  475,  476,  477,  478,  479,   -1,   -1,
  482,  483,   -1,  485,   -1,   -1,   -1,  489,   -1,  491,
   -1,   -1,   -1,   -1,   -1,  497,   -1,   -1,   -1,   -1,
  502,   -1,   -1,  505,   -1,  507,  508,  509,   -1,   -1,
   -1,   -1,   -1,   -1,  516,   -1,   -1,  519,   -1,   -1,
  522,   -1,  524,   -1,   -1,   -1,   -1,  529,  530,   -1,
   -1,   -1,  534,   -1,  536,  537,  538,  539,   -1,  541,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  550,   -1,
  552,   -1,   -1,   -1,   -1,   -1,   -1,  559,  560,  561,
  562,   -1,  564,   -1,  566,   -1,   -1,   -1,   -1,  571,
   -1,   -1,   -1,   -1,  576,  577,  578,  579,  580,   -1,
   -1,  583,  584,  585,   -1,  587,  588,   -1,   -1,   -1,
  592,   -1,  594,  595,   -1,  597,  598,  599,   -1,  601,
  602,  603,  604,   -1,  606,  607,  608,   -1,  610,  611,
   -1,  613,  614,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  270,   -1,  272,
   -1,  274,   -1,  276,   -1,  278,  279,   -1,  281,   -1,
   -1,   -1,   -1,   -1,   -1,  288,  289,  290,  291,   -1,
  293,   -1,   -1,  296,   -1,   -1,  299,  300,  301,   -1,
   -1,  304,   -1,   -1,   -1,   -1,   -1,  310,   -1,  312,
   -1,   -1,  315,  316,  317,   -1,   -1,   -1,  321,   -1,
   -1,  324,  325,   -1,   -1,   -1,  329,   -1,   -1,   -1,
   -1,  334,   -1,   -1,   -1,   -1,  339,   -1,   -1,   -1,
  343,   -1,   -1,   -1,   -1,  348,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  363,   -1,   -1,   -1,   -1,  368,   -1,  370,   -1,   -1,
   -1,   -1,  375,   -1,  377,  378,  379,   -1,  381,  382,
  383,  384,  385,  386,  387,  388,   -1,  390,  391,  392,
  393,  394,  395,  396,  397,  398,  399,   -1,   -1,   -1,
  403,   -1,  405,  406,  407,   41,   42,   43,   -1,   45,
   -1,   47,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  422,
   -1,  424,   -1,   -1,  427,  428,   -1,   -1,  431,   -1,
   -1,  434,   -1,   -1,   -1,   -1,  439,   -1,  441,   -1,
  443,   -1,   -1,   -1,   -1,   -1,  449,   -1,   -1,   -1,
  453,   -1,   -1,   -1,   -1,   -1,  459,   -1,   -1,   -1,
   -1,  464,  465,   -1,   -1,  468,   -1,   -1,  471,   -1,
  473,   -1,  475,  476,  477,  478,   -1,   -1,   -1,  482,
   -1,   -1,   -1,   -1,   -1,   -1,  489,   -1,  491,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  502,
   -1,   -1,   -1,   -1,   -1,  508,  509,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  519,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  534,   -1,  536,  537,   -1,  539,   -1,  541,   -1,
   -1,   -1,   -1,   -1,   -1,  272,   -1,  550,   -1,  552,
   -1,   -1,   -1,   -1,   -1,   -1,  559,  560,  561,  562,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  571,   -1,
   -1,   -1,   -1,  576,  577,  578,   -1,   -1,   -1,   -1,
  583,  584,  585,   -1,  587,   -1,  272,   -1,   -1,  592,
   -1,  318,  595,   -1,  597,  598,   -1,   -1,  601,   -1,
  603,   -1,   -1,   -1,   -1,  332,   -1,  610,  611,  336,
  613,  614,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  356,
   -1,   -1,  318,  319,  270,   -1,  272,   -1,  274,  366,
  276,   -1,  278,  279,   -1,  281,   -1,   -1,   -1,   -1,
  336,   -1,  288,  289,  290,  291,   -1,  293,   -1,   -1,
  296,   -1,   -1,  299,  300,  301,   -1,   -1,  304,   -1,
  356,   -1,   -1,   -1,  310,   -1,  312,   -1,   -1,  315,
  316,  317,  409,   -1,   -1,  321,   -1,   -1,  324,  325,
   -1,   -1,   -1,  329,   -1,   -1,   -1,   -1,  334,  426,
   -1,   -1,   -1,  339,   -1,   -1,   -1,  343,   -1,   -1,
   -1,   -1,  348,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  409,  451,   -1,   -1,  363,   -1,   -1,
   -1,  458,  368,   -1,  370,   -1,   -1,   -1,   -1,  375,
  426,  377,  378,  379,   -1,  381,  382,  383,  384,  385,
  386,  387,  388,   -1,  390,  391,  392,  393,  394,  395,
  396,  397,  398,  399,   41,  451,   43,  403,   45,  405,
  406,  407,  458,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  422,   -1,  424,   -1,
   -1,  427,  428,  520,   -1,  431,   -1,   -1,  434,   -1,
   -1,   -1,   -1,  439,  531,  441,  533,  443,   -1,   -1,
   -1,   -1,   -1,  449,   -1,   -1,   -1,  453,   -1,   -1,
   -1,   -1,   -1,  459,   -1,   -1,   -1,   -1,  464,  465,
   -1,   -1,  468,   -1,  520,  471,   -1,  473,   -1,  475,
  476,  477,  478,   -1,   -1,  531,  482,  533,   -1,   -1,
   -1,   -1,   -1,  489,   -1,  491,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  502,   -1,   -1,   -1,
   -1,   -1,  508,  509,   -1,   -1,   -1,   -1,   -1,   -1,
  607,   -1,   -1,  519,   -1,   -1,   -1,  614,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  534,   -1,
  536,  537,   -1,  539,  590,  541,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  550,   -1,  552,   -1,   -1,   -1,
   -1,  607,   -1,  559,  560,  561,  562,   -1,  614,   -1,
   -1,   -1,   -1,   -1,   -1,  571,   -1,   -1,   -1,   -1,
  576,  577,  578,   -1,   -1,  272,   -1,  583,  584,  585,
   -1,  587,   -1,   -1,   -1,   -1,  592,   -1,   -1,  595,
   -1,  597,  598,   -1,   -1,  601,   -1,  603,   -1,   -1,
   -1,   -1,   -1,   -1,  610,  611,   -1,  613,  614,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  318,   -1,  270,   -1,  272,   -1,  274,   -1,  276,
   -1,  278,  279,   -1,  281,  332,   -1,   -1,   -1,  336,
   -1,  288,  289,  290,  291,   -1,  293,   -1,   -1,  296,
   -1,   -1,  299,  300,  301,   -1,   -1,  304,   -1,  356,
   -1,   -1,   -1,  310,   -1,  312,   -1,   -1,  315,  316,
  317,   -1,   -1,   -1,  321,   -1,   -1,  324,  325,   -1,
   -1,   -1,  329,   -1,   -1,   -1,   -1,  334,   -1,   -1,
   -1,   -1,  339,   -1,   -1,   -1,  343,   -1,   -1,   -1,
   -1,  348,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  409,   -1,   -1,   -1,  363,   -1,   -1,   -1,
   -1,  368,   -1,  370,   -1,   -1,   -1,  272,  375,  426,
  377,  378,  379,   -1,  381,  382,  383,  384,  385,  386,
  387,  388,   -1,  390,  391,  392,  393,  394,  395,  396,
  397,  398,  399,   41,  451,   43,  403,   45,  405,  406,
  407,  458,   -1,   -1,   -1,   -1,   -1,  312,  313,   -1,
   -1,  316,  317,   -1,   -1,  422,   -1,  424,   -1,   -1,
  427,  428,   -1,   -1,  431,   -1,   -1,  434,   -1,   -1,
   -1,   -1,  439,  338,  441,   -1,  443,   -1,   -1,   -1,
   -1,   -1,  449,   -1,   -1,   -1,  453,   -1,   -1,   -1,
   -1,   -1,  459,   -1,   -1,   -1,   -1,  464,  465,   -1,
   -1,  468,   -1,  520,  471,   -1,  473,   -1,  475,  476,
  477,  478,   -1,   -1,  531,  482,  533,   -1,   -1,   -1,
   -1,   -1,  489,   -1,  491,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  502,   -1,   -1,  403,   -1,
   -1,  508,  509,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  519,   -1,   -1,  420,   -1,  422,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  431,  534,   -1,  536,
  537,   -1,  539,  272,  541,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  550,  449,  552,   -1,   -1,   -1,   43,
  607,   45,  559,  560,  561,  562,   -1,  614,   -1,  464,
  465,   -1,   -1,   -1,  571,   -1,   -1,   -1,   -1,  576,
  577,  578,   -1,   -1,  272,   -1,  583,  584,  585,  318,
  587,   -1,   -1,   -1,   -1,  592,   -1,   -1,  595,   -1,
  597,  598,   -1,   -1,  601,   -1,  603,  336,   -1,   -1,
   -1,   -1,   -1,  610,  611,   -1,  613,  614,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  356,   -1,   -1,
  318,  319,  270,   -1,  272,   -1,  274,  366,  276,  534,
  278,  279,   -1,  281,  539,   -1,   -1,   -1,  336,   -1,
  288,  289,  290,  291,   -1,  293,   -1,  552,  296,   -1,
   -1,  299,  300,  301,   -1,  560,  304,   -1,  356,   -1,
   -1,   -1,  310,   -1,  312,   -1,   -1,  315,  316,  317,
  409,   -1,   -1,  321,   -1,   -1,  324,  325,   -1,   -1,
   -1,  329,   -1,   -1,   -1,   -1,  334,  426,   -1,   -1,
  595,  339,   -1,   -1,   -1,  343,   -1,   -1,  603,   -1,
  348,   -1,   -1,   -1,   -1,   -1,  611,   -1,   -1,   -1,
   -1,  409,  451,   -1,   -1,  363,   -1,   -1,   -1,  458,
  368,   41,  370,   -1,   -1,   -1,   -1,  375,  426,  377,
  378,  379,   -1,  381,  382,  383,  384,  385,  386,  387,
  388,   -1,  390,  391,  392,  393,  394,  395,  396,  397,
  398,  399,   -1,  451,   -1,  403,   -1,  405,  406,  407,
  458,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  422,   -1,  424,  271,  272,  427,
  428,  520,   -1,  431,   -1,   -1,  434,   -1,  282,   -1,
   -1,  439,  531,  441,  533,  443,   -1,   -1,   -1,   -1,
   -1,  449,   -1,   -1,   -1,  453,   -1,   -1,   -1,   -1,
   -1,  459,   -1,   -1,   -1,   -1,  464,  465,   -1,   -1,
  468,   -1,  520,  471,  318,  473,   -1,  475,  476,  477,
  478,   -1,   -1,  531,  482,  533,   -1,   -1,  332,   -1,
   -1,  489,  336,  491,   -1,   -1,   -1,   -1,  256,   -1,
   -1,  259,   -1,   -1,  502,  263,   -1,   -1,   -1,   -1,
  508,  509,  356,   -1,  272,   -1,   -1,   -1,  607,   -1,
   -1,  519,  366,   -1,   -1,  614,   -1,   43,   -1,   45,
   -1,   -1,   -1,   -1,  292,   -1,  534,   -1,  536,  537,
   -1,  539,   -1,  541,   -1,   -1,   -1,  305,   -1,   -1,
   -1,  309,  550,   -1,  552,   -1,   -1,   -1,   -1,  607,
   -1,  559,  560,  561,  562,  409,  614,   -1,   -1,   -1,
   -1,   -1,   43,  571,   45,   -1,   -1,  421,  576,  577,
  578,   -1,  426,   -1,   -1,  583,  584,  585,   -1,  587,
   -1,   -1,   -1,   -1,  592,   -1,   -1,  595,   -1,  597,
  598,  271,   -1,  601,   -1,  603,   -1,  451,  278,  279,
   -1,  281,  610,  611,  458,  613,  614,   -1,  288,  289,
  290,  291,   -1,  293,   -1,   -1,  296,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  304,   -1,   41,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  321,   -1,   -1,  324,  325,  414,   -1,   -1,  329,
   -1,   -1,   -1,   -1,  334,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  343,   -1,   -1,  520,   -1,  348,  437,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  531,   -1,  533,
   -1,   -1,   -1,  363,   -1,   -1,   -1,   -1,  368,   -1,
  370,  459,  372,   -1,   -1,  375,   -1,  377,  378,  379,
   -1,  381,  382,  383,   -1,  385,  386,  387,  388,   -1,
  390,  391,  392,  393,  394,  395,  396,  397,  398,  399,
   -1,   -1,   -1,   -1,   -1,  405,  494,  407,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  424,  271,  272,  427,  428,   -1,
   -1,   -1,  520,  607,  434,   -1,  282,   -1,  526,  439,
  614,  441,   -1,  443,   -1,   -1,   -1,  535,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  260,
   -1,  262,  263,   -1,   -1,   -1,   -1,   -1,  468,   -1,
  558,  471,  318,  473,   -1,   -1,  476,   -1,  478,   -1,
   -1,  282,  283,   -1,  572,   -1,  332,   -1,   -1,   -1,
  336,  491,   -1,   -1,   -1,   -1,  297,   -1,   -1,   -1,
   -1,   -1,  502,   -1,   -1,   43,   -1,   45,   -1,   43,
  356,   45,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  519,
  366,   -1,   -1,   -1,   -1,   -1,  614,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  536,  537,   -1,   -1,
   -1,  541,   -1,  278,  279,   -1,  281,   -1,   -1,   -1,
  550,  352,   -1,  288,  289,  290,  291,   -1,  293,  559,
   -1,  296,  562,  409,   -1,   -1,   -1,   -1,   -1,  304,
   -1,  571,   -1,   -1,   -1,   -1,  576,  577,  578,   -1,
  426,   -1,   -1,  583,  584,  585,  321,  587,   -1,  324,
  325,   -1,   -1,   -1,  329,   -1,   -1,  597,  598,  334,
  600,   -1,   -1,   -1,   -1,  451,   -1,   -1,  343,   -1,
  610,   -1,  458,  348,  614,   -1,   -1,   41,   -1,   -1,
   -1,   -1,  423,   -1,   -1,   -1,   -1,   -1,  363,   -1,
   -1,  432,   -1,  368,   -1,  370,   -1,   -1,   -1,   -1,
  375,   -1,  377,  378,  379,   -1,  381,  382,  383,   -1,
  385,  386,  387,  388,  455,  390,  391,  392,  393,  394,
  395,  396,  397,  398,  399,  466,   -1,   -1,   -1,   -1,
  405,   -1,  407,   43,  520,   45,   -1,   -1,  479,   -1,
   -1,   -1,   -1,   -1,   -1,  531,   -1,  533,   -1,  424,
   -1,   -1,  427,  428,   -1,   -1,   -1,   -1,   -1,  434,
   -1,   -1,   -1,   -1,  439,   -1,  441,   -1,  443,   -1,
   -1,   -1,   -1,   -1,   -1,  516,   -1,   -1,  256,   -1,
   -1,   -1,  260,   -1,  262,  263,  260,   -1,  262,  263,
   -1,   -1,   -1,  468,   -1,   -1,  471,   -1,  473,   -1,
   -1,  476,   -1,  478,  282,  283,   -1,   -1,  282,  283,
  272,   -1,   -1,   -1,   -1,   -1,  491,   -1,   -1,  297,
   -1,  607,   -1,  297,   -1,  566,   -1,  502,  614,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  519,   -1,   -1,   -1,  310,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  318,  319,   -1,   -1,
   -1,  536,  537,   -1,   -1,   -1,  541,   -1,   -1,   -1,
   -1,   -1,  613,   -1,  336,  550,   -1,   -1,  352,   43,
   -1,   45,   -1,   -1,  559,   -1,   -1,  562,   -1,   -1,
   -1,   -1,   -1,   -1,  356,   -1,  571,   -1,   -1,   -1,
   -1,  576,  577,  578,   -1,   -1,   -1,   -1,  583,  584,
  585,   -1,  587,   -1,  278,  279,   -1,  281,   -1,   -1,
   -1,   -1,  597,  598,  288,  289,  290,  291,   -1,  293,
   -1,   -1,  296,   -1,   -1,  610,   -1,   -1,   -1,  614,
  304,   -1,   41,   -1,   -1,  423,  256,  409,   -1,  423,
  260,   -1,  262,  263,  432,   -1,  418,  321,  432,   -1,
  324,  325,   -1,   -1,  426,  329,   -1,   -1,   -1,   -1,
  334,   -1,  282,  283,   -1,   -1,   -1,   -1,   -1,  343,
   -1,   -1,   -1,   -1,  348,   -1,   -1,  297,  466,  451,
   -1,   -1,  466,   -1,   -1,   -1,  458,   -1,   43,  363,
   45,  479,   -1,   -1,  368,  479,  370,   -1,   -1,   -1,
   -1,  375,   -1,  377,  378,  379,   -1,  381,  382,  383,
   -1,  385,  386,  387,  388,   -1,  390,  391,  392,  393,
  394,  395,  396,  397,  398,  399,   -1,   -1,  516,   -1,
   -1,  405,  516,  407,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  520,   -1,
  424,   -1,  272,  427,  428,   -1,   -1,   -1,   -1,  531,
  434,  533,   -1,   -1,   -1,  439,   -1,  441,   -1,  443,
   -1,   -1,   -1,  561,   -1,   -1,   -1,   -1,  566,   -1,
   -1,   -1,  566,   -1,   -1,   -1,  260,   -1,  262,  263,
   -1,   -1,   -1,   -1,  468,   -1,   -1,  471,  318,  473,
   -1,   -1,  476,  423,  478,   -1,   -1,   -1,  282,  283,
   -1,   -1,  432,   -1,   -1,   -1,  336,  491,  590,   -1,
   -1,   -1,   -1,  297,   -1,  613,   -1,   -1,  502,  613,
   -1,   -1,   43,   -1,   45,  607,  356,   -1,   -1,  611,
   -1,   -1,  614,   -1,   -1,  519,  466,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  479,
   -1,   -1,  536,  537,   -1,   -1,   -1,  541,   -1,  278,
  279,   -1,  281,   -1,   -1,   -1,  550,   -1,   -1,  288,
  289,  290,  291,   -1,  293,  559,   -1,  296,  562,  409,
   -1,   -1,   -1,   -1,   -1,  304,  516,  571,   -1,   -1,
   -1,   -1,  576,  577,  578,  260,  426,  262,  263,  583,
  584,  585,  321,  587,   -1,  324,  325,   -1,   -1,   -1,
  329,   -1,   -1,  597,  598,  334,   -1,  282,  283,   -1,
   -1,  451,   -1,   -1,  343,   -1,  610,   -1,  458,  348,
  614,  561,  297,   41,   -1,   -1,  566,   -1,   -1,  423,
   -1,   -1,   -1,   -1,  363,   -1,   -1,   -1,  432,  368,
   -1,  370,   -1,   -1,   -1,   -1,  375,   -1,  377,  378,
  379,  316,  381,  382,  383,   -1,  385,  386,  387,  388,
   -1,  390,  391,  392,  393,  394,  395,  396,  397,  398,
  399,   -1,  466,  613,  339,  340,  405,   -1,  407,   -1,
  520,   -1,   -1,   -1,   -1,  479,   -1,   -1,   -1,   -1,
   -1,  531,   -1,  533,   -1,  424,   -1,   -1,  427,  428,
   -1,   -1,   -1,  368,   -1,  434,   -1,   -1,   -1,   -1,
  439,   -1,  441,   -1,  443,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  516,   -1,   -1,  256,   -1,   -1,   -1,  260,
   -1,  262,  263,   -1,   -1,   -1,   -1,   -1,   -1,  468,
   -1,   -1,  471,   -1,  473,   -1,   -1,  476,  423,  478,
   -1,  282,  283,   -1,   -1,   -1,   -1,  432,   -1,   -1,
   -1,   -1,  491,   -1,  429,   -1,  297,  607,   -1,   -1,
  445,   -1,  566,  502,  614,   43,   -1,   45,   -1,   -1,
   -1,   -1,   -1,   -1,  449,   -1,   -1,  462,  453,   -1,
  519,  466,   -1,   -1,  459,  460,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  479,   -1,   -1,  536,  537,   -1,
   -1,  476,  541,   -1,   -1,   -1,   -1,  611,   -1,  613,
   -1,  550,   -1,   -1,   43,   -1,   45,   -1,   -1,   -1,
  559,   -1,   -1,  562,   -1,   -1,   -1,   -1,   -1,   -1,
  505,  516,  571,   -1,   -1,   -1,   -1,  576,  577,  578,
   -1,   -1,   -1,   -1,  583,  584,  585,   -1,  587,   -1,
  278,  279,   -1,  281,   -1,   -1,   -1,   -1,  597,  598,
  288,  289,   -1,  291,   -1,  293,   -1,   -1,  296,   -1,
   -1,  610,   -1,   -1,   -1,  614,  304,   -1,   41,   -1,
   -1,  566,  423,   -1,   -1,  560,   -1,   -1,   -1,  564,
   -1,  432,   -1,  321,   -1,   -1,  324,  325,   -1,   -1,
   -1,  329,   -1,   -1,  579,   -1,  334,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  343,   -1,  592,   -1,  594,
  348,   -1,   -1,   -1,   -1,  466,   -1,   -1,  613,  604,
   -1,   -1,  607,   -1,   -1,  363,   -1,   -1,  479,  614,
  368,   -1,  370,   -1,   -1,   -1,   -1,  375,   -1,  377,
  378,  379,   -1,  381,  382,  383,   -1,  385,  386,  387,
  388,   -1,  390,  391,  392,  393,  394,  395,  396,  397,
  398,  399,   -1,   -1,   -1,  516,   -1,  405,   -1,  407,
   -1,   -1,  260,   -1,  262,  263,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  271,   -1,   -1,  424,   -1,  272,  427,
  428,   -1,   -1,   -1,  282,  283,  434,   -1,   -1,   -1,
   -1,  439,   -1,  441,   -1,  443,   -1,   -1,   -1,  297,
   -1,   -1,   -1,   -1,   -1,  566,   -1,   -1,   -1,   -1,
   -1,  260,   -1,  262,  263,   -1,   -1,   -1,   -1,   -1,
  468,   -1,   -1,  471,  318,  473,   -1,   -1,  476,   -1,
  478,   -1,   -1,  282,  283,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  336,  491,   -1,   -1,   -1,   -1,  297,   -1,
   -1,   -1,  613,   -1,  502,   -1,   -1,   -1,   43,   -1,
   45,   -1,  356,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  519,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  536,  537,
   -1,   -1,   -1,  541,   -1,  278,  279,   -1,  281,   -1,
   -1,   -1,  550,  352,   -1,   -1,   -1,  290,  291,   -1,
  293,  559,   -1,  296,  562,  409,   -1,   -1,   -1,   -1,
   -1,  304,   -1,  571,   -1,  423,   -1,   -1,  576,  577,
  578,   -1,  426,   -1,  432,  583,  584,  585,  321,  587,
   -1,  324,  325,   -1,   -1,   -1,  329,   -1,   -1,  597,
  598,  334,   -1,   -1,   -1,   -1,   -1,  451,   -1,   -1,
  343,   -1,  610,   -1,  458,  348,  614,   -1,  466,   -1,
   43,   -1,   45,   -1,  423,   -1,   -1,   -1,   -1,   -1,
  363,  479,   -1,  432,   -1,  368,   -1,  370,   -1,   -1,
   -1,   -1,  375,   -1,  377,  378,  379,   -1,  381,  382,
  383,   -1,  385,  386,  387,  388,   -1,  390,  391,  392,
  393,  394,  395,  396,  397,  398,  399,  466,  516,   -1,
   -1,   -1,  405,   -1,  407,   -1,  520,   -1,   -1,   -1,
  479,   -1,   -1,   -1,   -1,   -1,   -1,  531,   -1,  533,
   -1,  424,   -1,   -1,  427,  428,   -1,   -1,   -1,   -1,
   -1,  434,   -1,   -1,   -1,   -1,  439,   -1,  441,   -1,
  443,   -1,   -1,   -1,   -1,   -1,   -1,  516,  566,   -1,
   -1,   -1,   -1,   -1,   -1,  260,   -1,  262,  263,  272,
   -1,   -1,   -1,   -1,   -1,  468,   -1,   -1,  471,   -1,
  473,   -1,   -1,  476,   -1,  478,   -1,  282,  283,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  491,   -1,
   -1,   -1,  297,  607,   -1,  613,   -1,  566,   -1,  502,
  614,   -1,   -1,   -1,   -1,  318,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  519,   -1,   -1,   -1,
   -1,   -1,   -1,  336,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  536,  537,   -1,   -1,   -1,  541,   -1,
   -1,   -1,   -1,  356,  613,   -1,   -1,  550,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  559,   -1,   -1,  562,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  260,  571,  262,
  263,   -1,   -1,  576,  577,  578,   -1,   -1,   -1,  272,
  583,  584,  585,  276,  587,  278,  279,   -1,  281,  282,
  283,   -1,   -1,   -1,  597,  598,  409,  290,  291,   -1,
  293,   -1,   -1,   -1,  297,   -1,   -1,  610,   -1,   -1,
   -1,  614,   -1,  426,   -1,   -1,  421,  310,  423,  312,
   -1,   -1,  315,  316,  317,   -1,   -1,  432,  321,   -1,
   -1,  324,  325,   -1,   -1,   -1,  329,   -1,  451,   -1,
   -1,  334,   -1,   -1,   -1,  458,  339,   -1,   -1,   -1,
  343,   -1,   -1,   -1,   -1,  348,   -1,   -1,   -1,   -1,
   -1,  466,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  363,   -1,   -1,   -1,  479,  368,   43,  370,   45,   -1,
   -1,   -1,  375,   -1,  377,  378,  379,   -1,  381,  382,
  383,  384,  385,  386,  387,  388,   -1,  390,  391,  392,
  393,  394,  395,  396,  397,  398,  399,  520,   -1,   -1,
  403,  516,  405,   -1,  407,   -1,   -1,   -1,  531,   -1,
  533,   -1,   -1,   -1,   -1,   43,   -1,   45,   -1,  422,
  423,  424,   -1,   -1,  427,  428,   -1,   -1,  431,  432,
   -1,  434,   -1,   -1,   -1,   -1,  439,   -1,  441,   -1,
  443,   -1,   43,   -1,   45,   -1,  449,   -1,   -1,   -1,
  453,  566,   -1,   -1,   -1,   -1,  459,   -1,   -1,   -1,
   -1,  464,  465,  466,   -1,  468,   -1,   -1,  471,   -1,
  473,   -1,   -1,   -1,  477,  478,  479,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  607,   -1,   -1,   -1,  491,   -1,
   -1,  614,   -1,   -1,   -1,   -1,   -1,   -1,  613,  502,
   -1,   -1,   -1,   -1,   -1,  508,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  516,   -1,   -1,  519,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  534,   -1,  536,  537,   -1,  539,   -1,  541,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  550,   -1,  552,
   -1,   -1,   -1,   -1,   -1,   -1,  559,  560,   -1,  562,
   -1,   -1,   -1,  566,   -1,   -1,   -1,   43,  571,   45,
   -1,   -1,   -1,  576,  577,  578,   -1,   -1,   -1,   -1,
  583,  584,  585,  260,   -1,  262,  263,   -1,   -1,  592,
   -1,   -1,  595,   -1,  597,  598,   -1,  274,  601,  316,
  603,  278,  279,   -1,  281,  282,  283,  610,  611,   -1,
  613,  614,   -1,  290,  291,   -1,  293,   -1,   -1,   -1,
  297,   -1,  339,  340,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  260,   -1,  262,  263,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  271,  321,   -1,   -1,  324,  325,   -1,
   -1,  368,  329,   -1,  282,  283,   -1,  334,   -1,  260,
   -1,  262,  263,   -1,   -1,   -1,  343,   -1,   -1,  297,
   -1,  348,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  282,  283,   -1,   -1,   -1,  363,   -1,   -1,  366,
   -1,  368,   -1,  370,   -1,   -1,  297,   -1,  375,   -1,
  377,  378,  379,   -1,  381,  382,  383,   -1,  385,  386,
  387,  388,  429,  390,  391,  392,  393,  394,  395,  396,
  397,  398,  399,   43,   -1,   45,   -1,   -1,  405,   -1,
  407,   -1,  449,   -1,   -1,   -1,  453,   -1,   -1,   -1,
   -1,   -1,  459,  460,   -1,   -1,  423,  424,  425,   -1,
  427,  428,   -1,   -1,   -1,  432,   -1,  434,   -1,  476,
   -1,   -1,  439,   -1,  441,   -1,  443,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  260,  462,  262,  263,  505,  466,
  272,  468,   -1,   -1,  471,  423,  473,   -1,   -1,   -1,
   -1,  478,  479,   -1,  432,   -1,  282,  283,   -1,   -1,
   -1,   -1,   -1,   -1,  491,   -1,   -1,   -1,   -1,  496,
   -1,  297,  423,   -1,   -1,  502,   -1,   -1,   -1,   -1,
   -1,  432,   -1,   -1,   -1,   -1,  318,   -1,  466,  516,
   -1,   -1,  519,  560,   -1,   -1,   -1,  564,   -1,   -1,
   -1,  479,   -1,   -1,  336,   -1,   -1,   -1,   -1,  536,
  537,   -1,  579,   -1,  541,  466,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  550,  356,  592,   -1,  594,  479,   -1,
   -1,   -1,  559,   -1,   -1,  562,   -1,  604,  516,  566,
  607,   -1,   -1,   -1,  571,   -1,   -1,  614,   -1,  576,
  577,  578,   -1,   -1,   -1,   -1,  583,  584,  585,  586,
   -1,   -1,   -1,   -1,   -1,  516,   -1,   -1,   -1,   -1,
  597,  598,  599,   -1,   -1,   -1,   -1,  409,   -1,   -1,
   -1,   -1,  609,  610,  611,   -1,  613,  614,  566,   -1,
  260,   -1,  262,  263,  426,  421,   -1,  423,   -1,   -1,
   -1,   -1,   -1,   -1,  274,   -1,  432,   -1,  278,  279,
   -1,  281,  282,  283,   -1,  566,   -1,   -1,   -1,  451,
  290,  291,   -1,  293,   -1,   -1,  458,  297,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  613,   -1,   -1,   -1,   -1,
  466,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  321,   -1,  479,  324,  325,   -1,   -1,   -1,  329,
  611,   -1,  613,   -1,  334,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  343,   -1,   -1,   -1,   -1,  348,   -1,
   -1,   -1,   -1,   43,   -1,   45,   -1,   -1,  520,   -1,
  516,   -1,   -1,  363,   -1,   -1,  366,   -1,  368,  531,
  370,  533,   -1,   -1,   -1,  375,   -1,  377,  378,  379,
   -1,  381,  382,  383,   -1,  385,  386,  387,  388,   -1,
  390,  391,  392,  393,  394,  395,  396,  397,  398,  399,
   -1,   -1,   43,   -1,   45,  405,   -1,  407,   -1,   -1,
  566,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  423,  424,  425,   -1,  427,  428,   -1,
   -1,   -1,  432,   -1,  434,   -1,   -1,   -1,   -1,  439,
   -1,  441,   -1,  443,   -1,  607,   -1,   -1,  256,   -1,
   -1,  259,  614,   -1,   -1,  263,   -1,  613,   -1,   -1,
   -1,   -1,  462,   -1,  272,   -1,  466,   -1,  468,   -1,
   -1,  471,   -1,  473,   -1,   -1,   -1,   -1,  478,  479,
   -1,   -1,   -1,   -1,  292,   -1,   -1,   -1,   -1,   -1,
   -1,  491,   -1,   -1,   -1,   -1,  496,  305,   -1,   -1,
   -1,  309,  502,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  516,   -1,   -1,  519,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  536,  537,   -1,   -1,
   -1,  541,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  550,   -1,   -1,   -1,   -1,   43,   -1,   45,   -1,  559,
   -1,   -1,  562,   -1,   -1,  373,  566,   -1,   -1,   -1,
  260,  571,  262,  263,   -1,   -1,  576,  577,  578,   -1,
   -1,   -1,   -1,  583,  584,  585,  586,   -1,  278,  279,
   -1,  281,  282,  283,   -1,   -1,   -1,  597,  598,  599,
  290,  291,   -1,  293,   -1,   -1,  414,  297,   -1,  609,
  610,  611,   -1,  613,  614,   -1,   -1,   -1,   -1,  260,
   -1,  262,  263,   -1,   -1,   -1,   -1,   -1,   -1,  437,
  320,  321,   -1,   -1,  324,  325,   -1,   -1,   -1,  329,
   -1,  282,  283,   -1,  334,   -1,   -1,   -1,   -1,   -1,
   -1,  459,   -1,  343,   -1,   -1,  297,  347,  348,   -1,
   -1,   -1,   -1,   -1,   -1,   43,   -1,   45,   -1,   -1,
   -1,   -1,   -1,  363,   -1,   -1,   -1,   -1,  368,   -1,
  370,   -1,   -1,   -1,   -1,  375,  494,  377,  378,  379,
   -1,  381,  382,  383,   -1,  385,  386,  387,  388,   -1,
  390,  391,  392,  393,  394,  395,  396,  397,  398,  399,
   -1,   -1,  520,   -1,   -1,  405,  406,  407,  526,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  535,   -1,   -1,
   -1,   -1,   -1,  423,  424,  425,   -1,  427,  428,   -1,
   -1,   43,  432,   45,  434,   -1,   -1,   -1,   -1,  439,
  558,  441,   -1,  443,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  572,   -1,   -1,   -1,   -1,   -1,
   -1,  272,  260,   -1,  262,  263,  466,   -1,  468,   -1,
   -1,  471,  423,  473,   -1,   -1,   -1,   -1,  478,  479,
   -1,  432,   -1,   -1,  282,  283,   -1,   -1,   -1,  489,
   -1,  491,   -1,   -1,   -1,   -1,  614,  497,   -1,  297,
   -1,  312,  502,   -1,   -1,  316,  317,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  466,  516,   -1,   -1,  519,
   -1,   -1,  320,   -1,  524,   -1,   -1,   -1,  479,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  536,  537,  538,   -1,
   -1,  541,   -1,   -1,   -1,   -1,   -1,   43,  499,   45,
  550,   -1,   -1,   -1,   -1,   43,   -1,   45,   -1,  559,
   -1,   -1,  562,   -1,   -1,  516,  566,   -1,   -1,   -1,
   -1,  571,  260,   -1,  262,  263,  576,  577,  578,   -1,
   -1,   -1,   -1,  583,  584,  585,  274,   -1,   -1,   -1,
  278,  279,  403,  281,  282,  283,   -1,  597,  598,   -1,
   -1,   -1,  290,  291,   -1,  293,   -1,  607,   -1,  297,
  610,  422,   -1,  613,  614,  566,   -1,   -1,   -1,   -1,
  431,   -1,   -1,   -1,   -1,  423,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  321,  432,   -1,  324,  325,  449,   -1,
   -1,  329,   -1,   -1,   -1,   -1,  334,   -1,  260,   -1,
  262,  263,   -1,  464,  465,  343,   -1,   -1,   -1,   -1,
  348,   -1,  613,   -1,   -1,   -1,   -1,   -1,  466,   -1,
  282,  283,   -1,   -1,   -1,  363,   -1,   -1,   -1,   -1,
  368,  479,  370,   -1,   -1,  297,   -1,  375,   -1,  377,
  378,  379,   -1,  381,  382,  383,   -1,  385,  386,  387,
  388,   -1,  390,  391,  392,  393,  394,  395,  396,  397,
  398,  399,   43,   -1,   45,   -1,   -1,  405,  516,  407,
   -1,   -1,   -1,  534,   -1,   -1,   -1,   -1,  539,   -1,
   -1,   -1,   -1,   -1,   -1,  423,  424,   -1,   -1,  427,
  428,  552,   -1,   -1,  432,   -1,  434,   -1,   -1,  560,
   -1,  439,   -1,  441,   -1,  443,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  260,   -1,  262,  263,  566,   -1,
   -1,   -1,  260,   -1,  262,  263,   -1,   -1,  466,   -1,
  468,   -1,   -1,  471,  595,  473,  282,  283,   -1,   -1,
  478,  479,  603,   -1,  282,  283,   -1,   -1,   -1,   -1,
  611,  297,   -1,  491,  416,   -1,   -1,   -1,   -1,  297,
   -1,  423,   -1,   -1,  502,  613,   -1,   -1,   -1,   -1,
  432,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  516,   -1,
   -1,  519,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  536,  537,
   -1,   -1,   -1,  541,  466,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  550,   -1,   -1,   -1,   -1,  479,   -1,   -1,
   -1,  559,   -1,   -1,  562,   -1,   -1,   -1,  566,   -1,
   -1,   -1,   -1,  571,   -1,   -1,   -1,   -1,  576,  577,
  578,   -1,   -1,   -1,   -1,  583,  584,  585,  586,   -1,
  588,   -1,   -1,   -1,  516,   -1,   -1,   -1,   -1,  597,
  598,  599,   43,   -1,   45,   -1,   -1,   -1,   -1,   -1,
   -1,  609,  610,  611,   -1,  613,  614,  423,  416,  260,
   -1,  262,  263,   -1,   -1,  423,  432,   -1,   -1,   -1,
   -1,   -1,   -1,  274,  432,   -1,   -1,  278,  279,   -1,
  281,  282,  283,   -1,  566,   -1,   -1,   -1,   -1,  290,
  291,   -1,  293,   43,   -1,   45,  297,   -1,   -1,  256,
  466,   -1,   -1,   -1,   -1,   -1,  263,   -1,  466,   -1,
   -1,   -1,   -1,  479,   -1,  272,   -1,   -1,   -1,   -1,
  321,  479,   -1,  324,  325,   -1,   -1,   -1,  329,   -1,
   -1,  613,   -1,  334,  500,  292,   -1,   -1,   -1,   -1,
   -1,   -1,  343,   -1,   -1,   -1,   -1,  348,  305,   -1,
  516,   -1,  309,   -1,   -1,   -1,   -1,   -1,  516,   -1,
   -1,   -1,  363,   -1,   -1,   -1,   -1,  368,   -1,  370,
   -1,   -1,   -1,   -1,  375,   -1,  377,  378,  379,   -1,
  381,  382,  383,   -1,  385,  386,  387,  388,   -1,  390,
  391,  392,  393,  394,  395,  396,  397,  398,  399,   43,
  566,   45,   -1,   -1,  405,   -1,  407,   -1,  566,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  423,  424,   -1,   -1,  427,  428,   -1,   -1,
   -1,  432,   -1,  434,   -1,   -1,   -1,   -1,  439,   -1,
  441,   -1,  443,   -1,   -1,   -1,   -1,  613,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  613,   -1,  414,   -1,  260,
   -1,  262,  263,   -1,   -1,  466,   -1,  468,   -1,   -1,
  471,   -1,  473,   -1,   -1,   -1,   -1,  478,  479,   -1,
  437,  282,  283,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  491,   -1,   -1,   -1,   -1,   -1,  297,   -1,   -1,   -1,
   -1,  502,  459,   -1,   -1,   -1,   -1,   -1,  272,   -1,
  260,   -1,  262,  263,   -1,  516,   -1,   -1,  519,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  282,  283,   -1,  536,  537,  494,   -1,   -1,
  541,   -1,   -1,   -1,   -1,   -1,  310,  297,   -1,  550,
   -1,   -1,   -1,   -1,  318,  319,   -1,   -1,  559,   -1,
   -1,  562,   -1,  520,   -1,  566,   -1,   -1,   -1,  526,
  571,   -1,  336,   -1,   -1,  576,  577,  578,  535,   -1,
   -1,   -1,  583,  584,  585,  586,   -1,  588,   -1,   -1,
   -1,   -1,  356,   -1,   -1,   -1,  597,  598,  599,   -1,
   -1,  558,   -1,   -1,   -1,   -1,   -1,   -1,  609,  610,
  611,   -1,  613,  614,   -1,  572,  260,   -1,  262,  263,
   -1,   -1,  423,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  432,   -1,   -1,  278,  279,   -1,  281,  282,  283,
   -1,   -1,   -1,   -1,   -1,  409,  290,  291,   -1,  293,
   -1,   -1,   -1,  297,  418,   -1,   -1,  614,   -1,   -1,
   -1,   -1,  426,   -1,   -1,  466,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  423,   -1,   -1,   -1,  321,  479,   -1,
  324,  325,  432,   -1,   -1,  329,   -1,  451,   -1,   -1,
  334,   -1,   -1,   -1,  458,   -1,  460,   -1,  499,  343,
   -1,   -1,   -1,   -1,  348,   -1,   -1,   -1,   -1,   43,
   -1,   45,   -1,   -1,   -1,  516,  466,   -1,   -1,  363,
   -1,   -1,   -1,   -1,  368,   -1,  370,   -1,   -1,  479,
   -1,  375,   -1,  377,  378,  379,   -1,  381,  382,  383,
   -1,  385,  386,  387,  388,   -1,  390,  391,  392,  393,
  394,  395,  396,  397,  398,  399,  520,   -1,   -1,   -1,
   -1,  405,   -1,  407,   -1,  566,  516,  531,   -1,  533,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  423,
  424,   -1,   -1,  427,  428,   -1,   -1,   -1,  432,   -1,
  434,   -1,   -1,   -1,   -1,  439,   -1,  441,   -1,  443,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  613,   -1,   -1,   -1,  566,   -1,   -1,   -1,
   -1,   -1,  466,   -1,  468,   -1,  590,  471,   -1,  473,
   -1,   -1,   -1,   -1,  478,  479,   -1,   -1,  316,   -1,
   -1,   -1,   -1,  607,   -1,   -1,   -1,  491,   -1,   -1,
  614,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  502,   -1,
   -1,  339,  340,  613,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  516,   -1,   -1,  519,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  368,   -1,  536,  537,   -1,   -1,   -1,  541,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  550,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  559,   -1,   -1,  562,   -1,
   -1,   -1,  566,   -1,   -1,   -1,  260,  571,  262,  263,
   -1,   -1,  576,  577,  578,   -1,   -1,   -1,   -1,  583,
  584,  585,  586,   -1,  278,  279,   -1,  281,  282,  283,
   -1,  429,   -1,  597,  598,  599,  290,  291,   -1,  293,
   -1,   -1,   -1,  297,   -1,  609,  610,  611,   -1,  613,
  614,  449,   -1,   -1,   -1,  453,   -1,   -1,   -1,   -1,
   -1,  459,  460,   -1,   -1,   -1,   -1,  321,   -1,   -1,
  324,  325,   -1,   -1,   -1,  329,   -1,   -1,  332,   -1,
  334,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  343,
   -1,   -1,   -1,   -1,  348,   -1,   -1,   -1,   -1,   -1,
   -1,   43,   -1,   45,   -1,   -1,   -1,  505,   -1,  363,
   -1,   -1,   -1,   -1,  368,   -1,  370,   -1,   -1,   -1,
   -1,  375,   -1,  377,  378,  379,   -1,  381,  382,  383,
   -1,  385,  386,  387,  388,   -1,  390,  391,  392,  393,
  394,  395,  396,  397,  398,  399,   -1,   -1,   -1,   -1,
   43,  405,   45,  407,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  560,  417,   -1,   -1,  564,   -1,   -1,   -1,
  424,   -1,   -1,  427,  428,   -1,   -1,   -1,  432,   -1,
  434,  579,   -1,   -1,   -1,  439,   -1,  441,   -1,  443,
   -1,   -1,   -1,   -1,  592,   -1,  594,   -1,   -1,  453,
   -1,   -1,   -1,   -1,   -1,   -1,  604,   -1,   -1,  607,
   -1,   -1,  466,   -1,  468,   -1,  614,  471,   -1,  473,
   -1,   -1,   -1,   -1,  478,  479,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  491,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  502,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  516,   -1,   -1,  519,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  536,  537,   -1,   -1,   -1,  541,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  550,   -1,   -1,   -1,
   -1,   43,   -1,   45,   -1,  559,   -1,   -1,  562,   -1,
   -1,   -1,  566,   -1,   -1,   -1,   -1,  571,  260,   -1,
  262,  263,  576,  577,  578,   -1,   -1,   -1,   -1,  583,
  584,  585,   -1,   -1,  316,   -1,  278,  279,  592,  281,
  282,  283,   -1,  597,  598,   -1,   -1,   -1,  290,  291,
   -1,  293,   -1,   -1,   -1,  297,  610,  339,  340,  613,
  614,   -1,   -1,   -1,   -1,   -1,   -1,  260,   -1,  262,
  263,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  321,
  322,  323,  324,  325,   -1,   -1,  368,  329,   -1,  282,
  283,   -1,  334,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  343,   -1,   -1,  297,   -1,  348,   -1,   -1,   -1,
   -1,   43,   -1,   45,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  363,   -1,   -1,   -1,   -1,  368,   -1,  370,   -1,
   -1,   -1,   -1,  375,   -1,  377,  378,  379,   -1,  381,
  382,  383,   -1,  385,  386,  387,  388,  429,  390,  391,
  392,  393,  394,  395,  396,  397,  398,  399,   -1,   -1,
   43,   -1,   45,  405,   -1,  407,   -1,  449,   -1,   -1,
   -1,  453,   -1,   -1,   -1,   -1,   -1,  459,  460,   -1,
   -1,  423,  424,   -1,   -1,  427,  428,   -1,   -1,   -1,
  432,   -1,  434,   -1,  476,   -1,   -1,  439,   -1,  441,
   -1,  443,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  260,   -1,
  262,  263,   -1,  505,  466,   -1,  468,   -1,   -1,  471,
  423,  473,   -1,   -1,   -1,   -1,  478,  479,   -1,  432,
  282,  283,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  491,
   -1,   -1,   -1,   -1,  536,  297,   -1,   -1,   -1,   -1,
  502,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  466,  516,   -1,   -1,  519,  560,   -1,
   -1,   -1,  564,   -1,   -1,   -1,  479,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  536,  537,   -1,  579,   -1,  541,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  500,  550,   -1,
  592,   43,  594,   45,   -1,   -1,   -1,  559,   -1,   -1,
  562,   -1,  604,  516,  566,  607,   -1,   -1,  260,  571,
  262,  263,  614,   -1,  576,  577,  578,   -1,   -1,   -1,
   -1,  583,  584,  585,   -1,   -1,  278,  279,   -1,  281,
  282,  283,   -1,   -1,   -1,  597,  598,   -1,  290,  291,
   -1,  293,   -1,   -1,   -1,  297,   -1,   -1,  610,   -1,
   -1,  613,  614,  566,   -1,   -1,   -1,  260,   -1,  262,
  263,  423,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  321,
  432,   -1,  324,  325,   -1,   -1,   -1,  329,   -1,  282,
  283,   -1,  334,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  343,   -1,   -1,  297,   -1,  348,   -1,   -1,   -1,
  613,   43,   -1,   45,  466,   -1,   -1,   -1,   -1,   -1,
   -1,  363,   -1,   -1,   -1,   -1,  368,  479,  370,   -1,
   -1,   -1,   -1,  375,   -1,  377,  378,  379,   -1,  381,
  382,  383,   -1,  385,  386,  387,  388,   -1,  390,  391,
  392,  393,  394,  395,  396,  397,  398,  399,   -1,   -1,
   43,   -1,   45,  405,  516,  407,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  423,  424,   -1,   -1,  427,  428,   -1,   -1,   -1,
  432,   -1,  434,   -1,   -1,   -1,   -1,  439,   -1,  441,
   -1,  443,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  566,   -1,   -1,   -1,  260,   -1,
  262,  263,   -1,   -1,  466,   -1,  468,   -1,   -1,  471,
  423,  473,   -1,   -1,   -1,   -1,  478,  479,   -1,  432,
  282,  283,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  491,
   -1,   -1,   -1,   -1,   -1,  297,   -1,   -1,   -1,   -1,
  502,  613,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  466,  516,   -1,   -1,  519,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  479,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  536,  537,   -1,   -1,   -1,  541,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  550,   -1,
   -1,   43,   -1,   45,   -1,   -1,   -1,  559,   -1,   -1,
  562,   -1,   -1,  516,  566,   -1,   -1,   -1,  260,  571,
  262,  263,   -1,   -1,  576,  577,  578,   -1,   -1,   -1,
   -1,  583,  584,  585,   -1,   -1,  278,  279,   -1,  281,
  282,  283,   -1,   -1,   -1,  597,  598,   -1,  290,  291,
   -1,  293,   -1,   -1,   -1,  297,   -1,   -1,  610,   -1,
   -1,  613,  614,  566,   -1,   -1,   -1,  260,   -1,  262,
  263,  423,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  321,
  432,   -1,  324,  325,   -1,   -1,   -1,  329,   -1,  282,
  283,   -1,  334,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  343,   -1,   -1,  297,   -1,  348,   -1,   -1,   -1,
  613,   43,   -1,   45,  466,   -1,   -1,   -1,   -1,   -1,
   -1,  363,   -1,   -1,   -1,   -1,  368,  479,  370,   -1,
   -1,   -1,   -1,  375,   -1,  377,  378,  379,   -1,  381,
  382,  383,   -1,  385,  386,  387,  388,   -1,  390,  391,
  392,  393,  394,  395,  396,  397,  398,  399,   -1,   -1,
   -1,   -1,   -1,  405,  516,  407,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  423,  424,   -1,   -1,  427,  428,   -1,   -1,   -1,
  432,   -1,  434,   -1,   -1,   -1,   -1,  439,   -1,  441,
   -1,  443,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  566,   -1,   -1,   -1,  260,   -1,
  262,  263,   -1,   -1,  466,   -1,  468,   -1,   -1,  471,
  423,  473,   -1,   -1,   -1,   -1,  478,  479,   -1,  432,
  282,  283,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  491,
   -1,   -1,   -1,   -1,   -1,  297,   -1,   -1,   -1,   -1,
  502,  613,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  466,  516,   -1,   -1,  519,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  479,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  536,  537,   -1,   -1,   -1,  541,
   -1,   -1,   -1,   43,   -1,   45,   -1,   -1,  550,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  559,   -1,   -1,
  562,   -1,   -1,  516,  566,   -1,   -1,   -1,  260,  571,
  262,  263,   -1,   -1,  576,  577,  578,   -1,   -1,   -1,
   -1,  583,  584,  585,   -1,   -1,  278,  279,   -1,  281,
  282,  283,   -1,   -1,   -1,  597,  598,   -1,  290,  291,
   -1,  293,   -1,   -1,   -1,  297,   -1,   -1,  610,   -1,
   -1,  613,  614,  566,   -1,   43,   -1,   45,   -1,   -1,
   -1,  423,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  321,
  432,   -1,  324,  325,   -1,   -1,   -1,  329,   -1,   -1,
   -1,   -1,  334,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  343,   -1,   -1,   -1,   -1,  348,   -1,   -1,   -1,
  613,   43,   44,   45,  466,   -1,   -1,   -1,   -1,   -1,
   -1,  363,   -1,   -1,   -1,   -1,  368,  479,  370,   -1,
   -1,   -1,   -1,  375,   -1,  377,  378,  379,   -1,  381,
  382,  383,   -1,  385,  386,  387,  388,   -1,  390,  391,
  392,  393,  394,  395,  396,  397,  398,  399,   -1,   -1,
   -1,   -1,   -1,  405,  516,  407,   43,   -1,   45,   -1,
  316,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  423,  424,   -1,   -1,  427,  428,   -1,   -1,   -1,
  432,   -1,  434,  339,  340,   -1,   -1,  439,   -1,  441,
   -1,  443,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  260,   -1,  262,  263,  566,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  368,   -1,  466,   -1,  468,   -1,   -1,  471,
   -1,  473,  282,  283,   -1,   -1,  478,  479,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  297,   -1,  491,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  502,  613,   -1,   -1,   -1,   -1,  316,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  516,   -1,   -1,  519,   -1,   -1,
   -1,   -1,  260,  429,  262,  263,   -1,   -1,   -1,  339,
  340,   -1,   -1,   -1,  536,  537,   43,   -1,   45,  541,
   -1,   -1,   -1,  449,  282,  283,   -1,  453,  550,   -1,
   -1,   -1,   -1,  459,  460,   -1,   -1,  559,  368,  297,
  562,   -1,   -1,   -1,  566,   -1,   -1,   -1,   -1,  571,
  476,   -1,   -1,   -1,  576,  577,  578,  269,  316,   -1,
  272,  583,  584,  585,   -1,   -1,   -1,   -1,   -1,   -1,
  282,  283,   -1,   -1,   -1,  597,  598,   -1,   -1,  505,
   -1,  339,  340,   -1,   -1,  297,   -1,   -1,  610,   -1,
   -1,  613,  614,  423,   -1,   -1,   -1,   -1,   -1,  429,
   -1,   -1,  432,  260,  316,  262,  263,   -1,   -1,   -1,
  368,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  449,
   -1,   -1,   -1,  453,   -1,  282,  283,   -1,   -1,  459,
  460,   -1,   -1,   -1,  560,   -1,  466,   -1,  564,   -1,
  297,   -1,   -1,   -1,   -1,   -1,  476,   -1,   -1,  479,
   -1,   -1,   -1,  579,   -1,   -1,  368,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  423,  592,   -1,  594,   -1,
   -1,  429,   -1,   -1,  432,  505,   -1,   -1,  604,   -1,
   -1,  607,   -1,   -1,   -1,   -1,  516,   -1,  614,   -1,
   -1,  449,   -1,   -1,   -1,  453,   -1,  409,   -1,   -1,
   -1,  459,  460,   -1,   -1,   -1,  536,   -1,  466,   -1,
   -1,   -1,   -1,   -1,  426,   -1,   -1,   -1,  476,   -1,
  432,  479,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  316,
  560,   -1,   -1,   -1,  564,   -1,  566,  449,   -1,   -1,
   -1,  453,  269,   -1,   -1,  272,   -1,  505,   -1,  579,
   -1,   -1,  339,  340,  466,  282,  283,   -1,  516,   -1,
   -1,   -1,  592,   -1,  594,   -1,  423,  479,   -1,   -1,
  297,   -1,  602,  485,  604,  432,   -1,  607,  536,   -1,
   -1,  368,   -1,  613,  614,   -1,   -1,   -1,   -1,  316,
   -1,   -1,   -1,  505,   -1,  507,   -1,   -1,   -1,   -1,
   -1,   -1,  560,   -1,  516,   -1,  564,   -1,  566,  466,
  522,   -1,   -1,   -1,   -1,   -1,   -1,  529,   -1,   -1,
   -1,  579,  479,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  592,   -1,  594,   -1,   -1,   -1,
   -1,  368,  429,   -1,   -1,   -1,  604,   -1,  560,  607,
   -1,   -1,   -1,   -1,  566,  613,  614,   -1,   -1,  516,
   -1,   -1,  449,   -1,   -1,   -1,  453,   -1,  580,   -1,
   -1,   -1,  459,  460,   -1,   -1,   -1,   -1,   -1,   -1,
  592,   -1,  409,   -1,   -1,   -1,   -1,   -1,   -1,  476,
   -1,   -1,  604,   -1,   -1,  607,  608,   -1,   -1,  426,
   -1,  613,  614,   -1,   -1,  432,   -1,   -1,   -1,  566,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  505,   -1,
   -1,   -1,  449,   -1,   -1,   -1,  453,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  466,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  479,   -1,   -1,   -1,  613,   -1,  485,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  560,   -1,   -1,   -1,  564,  505,   -1,
  507,  256,   -1,   -1,   -1,  260,   -1,  262,  263,  516,
   -1,   -1,  579,   -1,   -1,  522,   -1,   -1,   -1,   -1,
   -1,   -1,  529,  278,  279,  592,  281,  594,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  290,  291,  604,  293,   -1,
  607,   -1,   -1,   -1,   -1,   -1,   -1,  614,   -1,   -1,
   -1,   -1,   -1,  560,   -1,   -1,   -1,   -1,   -1,  566,
   -1,   -1,   -1,   -1,   -1,   -1,  321,   -1,   -1,  324,
  325,   -1,   -1,  580,  329,   -1,   -1,   -1,   -1,  334,
   -1,   -1,   -1,   -1,   -1,  592,   -1,   -1,  343,   -1,
   -1,   -1,   -1,  348,   -1,   -1,   -1,  604,   -1,   -1,
  607,  608,   -1,   -1,   -1,   -1,  613,  614,  363,   -1,
   -1,   -1,   -1,  368,   -1,  370,   -1,   -1,   -1,   -1,
  375,   -1,  377,  378,  379,   -1,  381,  382,  383,   -1,
  385,  386,  387,  388,   -1,  390,  391,  392,  393,  394,
  395,  396,  397,  398,  399,   -1,   -1,   -1,   -1,   -1,
  405,   -1,  407,  408,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  424,
   -1,   -1,  427,  428,   -1,   -1,   -1,   -1,   -1,  434,
   -1,   -1,   -1,   -1,  439,   -1,  441,  442,  443,   -1,
   -1,   -1,  447,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  468,   -1,   -1,  471,   -1,  473,   -1,
   -1,   -1,   -1,  478,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  491,   -1,   -1,   -1,
   -1,  496,   -1,   -1,   -1,   -1,   -1,  502,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  519,   -1,  256,   -1,   -1,   -1,
  260,   -1,  262,  263,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  536,  537,   -1,   -1,   -1,  541,   -1,  278,  279,
   -1,  281,   -1,   -1,   -1,  550,   -1,   -1,   -1,   -1,
  290,  291,   -1,  293,  559,   -1,   -1,  562,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  571,   -1,   -1,   -1,
   -1,  576,  577,  578,   -1,   -1,   -1,   -1,  583,  584,
  585,  321,   -1,   -1,  324,  325,   -1,   -1,   -1,  329,
   -1,   -1,  597,  598,  334,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  343,   -1,  610,   -1,   -1,  348,  614,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  363,   -1,   -1,   -1,   -1,  368,   -1,
  370,   -1,   -1,   -1,   -1,  375,   -1,  377,  378,  379,
   -1,  381,  382,  383,   -1,  385,  386,  387,  388,   -1,
  390,  391,  392,  393,  394,  395,  396,  397,  398,  399,
   -1,   -1,   -1,   -1,   -1,  405,   -1,  407,  408,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  424,   -1,   -1,  427,  428,   -1,
   -1,   -1,   -1,  269,  434,   -1,  272,   -1,   -1,  439,
   -1,  441,  442,  443,   -1,   -1,   -1,  447,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  256,   -1,   -1,   -1,   -1,   -1,   -1,  263,  468,   -1,
   -1,  471,   -1,  473,   -1,   -1,   -1,   -1,  478,   -1,
  316,   -1,  278,  279,   -1,  281,   -1,   -1,   -1,   -1,
   -1,  491,   -1,   -1,   -1,  291,  496,  293,   -1,   -1,
   -1,   -1,  502,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  519,
   -1,   -1,   -1,   -1,   -1,  321,   -1,   -1,  324,  325,
   -1,   -1,  368,  329,   -1,   -1,  536,  537,  334,   -1,
   -1,  541,   -1,   -1,   -1,   -1,   -1,  343,   -1,   -1,
  550,   -1,  348,   -1,   -1,   -1,   -1,   -1,   -1,  559,
   -1,   -1,  562,   -1,   -1,   -1,   -1,  363,   -1,   -1,
   -1,  571,  368,  409,  370,   -1,  576,  577,  578,   -1,
  376,   -1,   -1,  583,  584,  585,   -1,   -1,   -1,   -1,
  426,   -1,   -1,   -1,   -1,   -1,   -1,  597,  598,   -1,
   -1,  437,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  405,
  610,  407,   -1,  449,  614,   -1,   -1,  453,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  424,   -1,
   -1,  427,  428,   -1,   -1,   -1,   -1,   -1,  434,   -1,
   -1,   -1,   -1,  439,   -1,  441,   -1,  443,   -1,  485,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  505,
   -1,  507,  468,   -1,   -1,  471,   -1,  473,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  522,   -1,   -1,   -1,
   -1,   -1,   -1,  529,   -1,  491,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  502,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  519,  560,   -1,   -1,   -1,   -1,  260,
   -1,  262,  263,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  536,  537,   -1,   -1,  580,  541,   -1,  278,  279,   -1,
  281,   -1,   -1,   -1,  550,   -1,  592,   -1,   -1,  290,
  291,   -1,  293,  559,   -1,   -1,  562,   -1,  604,   -1,
   -1,  607,  608,   -1,   -1,  571,   -1,   -1,  614,   -1,
  576,  577,  578,   -1,   -1,   -1,   -1,  583,  584,  585,
  321,   -1,   -1,  324,  325,   -1,   -1,   -1,  329,   -1,
   -1,  597,  598,  334,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  343,   -1,   -1,   -1,   -1,  348,  614,   -1,
   -1,   -1,  353,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  363,   -1,   -1,   -1,   -1,  368,   -1,  370,
   -1,   -1,   -1,   -1,  375,   -1,  377,  378,  379,   -1,
  381,  382,  383,   -1,  385,  386,  387,  388,   -1,  390,
  391,  392,  393,  394,  395,  396,  397,  398,  399,   -1,
   -1,   -1,   -1,   -1,  405,   -1,  407,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  424,   -1,   -1,  427,  428,   -1,   -1,
   -1,   -1,   -1,  434,   -1,   -1,   -1,   -1,  439,   -1,
  441,   -1,  443,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  462,   -1,   -1,   -1,   -1,   -1,  468,   -1,   -1,
  471,   -1,  473,   -1,   -1,   -1,   -1,  478,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  489,   -1,
  491,   -1,   -1,   -1,   -1,   -1,  497,   -1,   -1,   -1,
   -1,  502,   -1,   -1,   -1,   -1,  507,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  519,   -1,
   -1,   -1,   -1,   -1,  260,   -1,  262,  263,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  536,  537,   -1,   -1,   -1,
  541,   -1,  278,  279,   -1,  281,   -1,   -1,   -1,  550,
   -1,   -1,   -1,   -1,  290,  291,   -1,  293,  559,   -1,
   -1,  562,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  571,   -1,   -1,   -1,   -1,  576,  577,  578,   -1,   -1,
  581,   -1,  583,  584,  585,  321,   -1,   -1,  324,  325,
   -1,   -1,   -1,  329,   -1,   -1,  597,  598,  334,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  343,   -1,  610,
  611,   -1,  348,  614,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  363,   -1,   -1,
   -1,   -1,  368,   -1,  370,   -1,   -1,   -1,   -1,  375,
   -1,  377,  378,  379,   -1,  381,  382,  383,   -1,  385,
  386,  387,  388,   -1,  390,  391,  392,  393,  394,  395,
  396,  397,  398,  399,   -1,   -1,   -1,   -1,   -1,  405,
   -1,  407,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  424,   -1,
   -1,  427,  428,   -1,   -1,   -1,   -1,   -1,  434,   -1,
   -1,   -1,   -1,  439,   -1,  441,   -1,  443,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  462,   -1,   -1,   -1,
   -1,   -1,  468,   -1,   -1,  471,   -1,  473,   -1,   -1,
   -1,   -1,  478,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  489,   -1,  491,   -1,   -1,   -1,   -1,
   -1,  497,   -1,   -1,   -1,   -1,  502,   -1,   -1,   -1,
   -1,  507,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  519,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  260,   -1,  262,  263,   -1,   -1,
  536,  537,   -1,   -1,   -1,  541,   -1,   -1,   -1,   -1,
  276,   -1,  278,  279,  550,  281,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  559,  290,  291,  562,  293,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  571,   -1,   -1,   -1,   -1,
  576,  577,  578,   -1,   -1,  581,   -1,  583,  584,  585,
   -1,   -1,   -1,   -1,   -1,  321,   -1,   -1,  324,  325,
   -1,  597,  598,  329,   -1,   -1,   -1,   -1,  334,   -1,
   -1,   -1,   -1,   -1,  610,  611,   -1,  343,  614,   -1,
   -1,   -1,  348,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  363,   -1,   -1,
   -1,   -1,  368,   -1,  370,   -1,   -1,   -1,   -1,  375,
   -1,  377,  378,  379,   -1,  381,  382,  383,   -1,  385,
  386,  387,  388,   -1,  390,  391,  392,  393,  394,  395,
  396,  397,  398,  399,   -1,   -1,   -1,   -1,   -1,  405,
   -1,  407,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  424,   -1,
   -1,  427,  428,   -1,   -1,   -1,   -1,   -1,  434,  435,
   -1,   -1,   -1,  439,   -1,  441,   -1,  443,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  462,  463,   -1,   -1,
   -1,   -1,  468,   -1,   -1,  471,   -1,  473,   -1,   -1,
   -1,   -1,  478,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  491,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  502,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  519,   -1,   -1,   -1,   -1,   -1,  260,
   -1,  262,  263,   -1,   -1,   -1,   -1,   -1,   -1,  270,
  536,  537,   -1,   -1,   -1,  541,   -1,  278,  279,   -1,
  281,   -1,   -1,   -1,  550,   -1,   -1,   -1,   -1,  290,
  291,   -1,  293,  559,   -1,   -1,  562,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  571,   -1,   -1,   -1,   -1,
  576,  577,  578,   -1,   -1,   -1,   -1,  583,  584,  585,
  321,   -1,   -1,  324,  325,   -1,   -1,   -1,  329,   -1,
   -1,  597,  598,  334,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  343,   -1,  610,   -1,   -1,  348,  614,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  363,   -1,   -1,   -1,   -1,  368,   -1,  370,
   -1,   -1,   -1,   -1,  375,   -1,  377,  378,  379,   -1,
  381,  382,  383,   -1,  385,  386,  387,  388,   -1,  390,
  391,  392,  393,  394,  395,  396,  397,  398,  399,   -1,
   -1,   -1,   -1,   -1,  405,   -1,  407,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  424,   -1,   -1,  427,  428,   -1,   -1,
   -1,   -1,   -1,  434,   -1,   -1,   -1,   -1,  439,   -1,
  441,   -1,  443,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  462,   -1,   -1,   -1,   -1,   -1,  468,   -1,   -1,
  471,   -1,  473,   -1,   -1,   -1,   -1,  478,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  489,   -1,
  491,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  502,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  519,   -1,
   -1,   -1,   -1,   -1,  260,   -1,  262,  263,   -1,   -1,
   -1,   -1,   -1,   -1,  270,  536,  537,   -1,   -1,   -1,
  541,   -1,  278,  279,   -1,  281,   -1,   -1,   -1,  550,
   -1,   -1,   -1,   -1,  290,  291,   -1,  293,  559,   -1,
  561,  562,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  571,   -1,   -1,   -1,   -1,  576,  577,  578,   -1,   -1,
   -1,   -1,  583,  584,  585,  321,   -1,   -1,  324,  325,
   -1,   -1,   -1,  329,   -1,   -1,  597,  598,  334,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  343,   -1,  610,
   -1,   -1,  348,  614,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  363,   -1,   -1,
   -1,   -1,  368,   -1,  370,   -1,   -1,   -1,   -1,  375,
   -1,  377,  378,  379,   -1,  381,  382,  383,   -1,  385,
  386,  387,  388,   -1,  390,  391,  392,  393,  394,  395,
  396,  397,  398,  399,   -1,   -1,   -1,   -1,   -1,  405,
   -1,  407,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  424,   -1,
   -1,  427,  428,   -1,   -1,   -1,   -1,   -1,  434,   -1,
   -1,   -1,   -1,  439,   -1,  441,   -1,  443,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  468,   -1,   -1,  471,   -1,  473,   -1,   -1,
   -1,   -1,  478,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  489,   -1,  491,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  502,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  519,   -1,   -1,   -1,   -1,   -1,  260,
   -1,  262,  263,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  536,  537,   -1,   -1,   -1,  541,   -1,  278,  279,  545,
  281,   -1,   -1,   -1,  550,   -1,   -1,   -1,   -1,  290,
  291,   -1,  293,  559,   -1,  561,  562,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  571,   -1,   -1,   -1,   -1,
  576,  577,  578,   -1,   -1,   -1,   -1,  583,  584,  585,
  321,   -1,   -1,  324,  325,   -1,   -1,   -1,  329,   -1,
   -1,  597,  598,  334,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  343,   -1,  610,   -1,   -1,  348,  614,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  363,   -1,   -1,   -1,   -1,  368,   -1,  370,
   -1,   -1,   -1,   -1,  375,   -1,  377,  378,  379,   -1,
  381,  382,  383,   -1,  385,  386,  387,  388,   -1,  390,
  391,  392,  393,  394,  395,  396,  397,  398,  399,   -1,
   -1,   -1,   -1,   -1,  405,   -1,  407,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  424,  425,   -1,  427,  428,   -1,   -1,
   -1,   -1,   -1,  434,   -1,   -1,   -1,   -1,  439,   -1,
  441,   -1,  443,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  462,   -1,   -1,   -1,   -1,   -1,  468,   -1,   -1,
  471,   -1,  473,   -1,   -1,   -1,   -1,  478,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  489,   -1,
  491,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  502,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  519,   -1,
   -1,   -1,   -1,   -1,  260,   -1,  262,  263,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  536,  537,   -1,   -1,   -1,
  541,   -1,  278,  279,   -1,  281,   -1,   -1,   -1,  550,
   -1,   -1,   -1,   -1,  290,  291,   -1,  293,  559,   -1,
  561,  562,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  571,   -1,   -1,   -1,   -1,  576,  577,  578,   -1,   -1,
   -1,   -1,  583,  584,  585,  321,   -1,   -1,  324,  325,
   -1,   -1,   -1,  329,   -1,   -1,  597,  598,  334,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  343,   -1,  610,
   -1,   -1,  348,  614,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  363,   -1,   -1,
   -1,   -1,  368,   -1,  370,   -1,   -1,   -1,   -1,  375,
   -1,  377,  378,  379,   -1,  381,  382,  383,   -1,  385,
  386,  387,  388,   -1,  390,  391,  392,  393,  394,  395,
  396,  397,  398,  399,   -1,   -1,   -1,   -1,   -1,  405,
   -1,  407,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  424,   -1,
   -1,  427,  428,   -1,   -1,   -1,   -1,   -1,  434,   -1,
   -1,   -1,   -1,  439,   -1,  441,   -1,  443,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  468,   -1,   -1,  471,   -1,  473,   -1,   -1,
   -1,   -1,  478,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  489,   -1,  491,   -1,   -1,   -1,   -1,
   -1,  497,   -1,   -1,   -1,   -1,  502,   -1,   -1,   -1,
   -1,  507,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  519,   -1,   -1,   -1,   -1,   -1,  260,
   -1,  262,  263,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  536,  537,   -1,   -1,   -1,  541,   -1,  278,  279,   -1,
  281,   -1,   -1,   -1,  550,   -1,   -1,   -1,   -1,  290,
  291,   -1,  293,  559,   -1,   -1,  562,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  571,   -1,   -1,   -1,   -1,
  576,  577,  578,   -1,   -1,  581,   -1,  583,  584,  585,
  321,   -1,   -1,  324,  325,   -1,  269,   -1,  329,  272,
   -1,  597,  598,  334,  277,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  343,   -1,  610,   -1,   -1,  348,  614,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  363,   -1,   -1,   -1,   -1,  368,   -1,  370,
   -1,   -1,   -1,  316,  375,   -1,  377,  378,  379,   -1,
  381,  382,  383,   -1,  385,  386,  387,  388,   -1,  390,
  391,  392,  393,  394,  395,  396,  397,  398,  399,   -1,
   -1,   -1,   -1,   -1,  405,   -1,  407,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  424,   -1,  368,  427,  428,   -1,   -1,
   -1,   -1,   -1,  434,   -1,   -1,   -1,   -1,  439,   -1,
  441,   -1,  443,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  462,   -1,   -1,   -1,   -1,  409,  468,   -1,   -1,
  471,   -1,  473,   -1,   -1,   -1,   -1,  478,   -1,   -1,
   -1,   -1,  269,  426,   -1,  272,   -1,   -1,  489,   -1,
  491,   -1,   -1,   -1,  437,   -1,   -1,   -1,   -1,   -1,
   -1,  502,   -1,   -1,   -1,   -1,  449,   -1,   -1,   -1,
  453,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  519,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  527,   -1,   -1,  316,
   -1,   -1,   -1,   -1,   -1,  536,  537,   -1,   -1,   -1,
  541,   -1,  485,   -1,   -1,   -1,   -1,   -1,   -1,  550,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  559,   -1,
  561,  562,  505,   -1,  507,   -1,   -1,   -1,   -1,  260,
  571,  262,  263,   -1,   -1,  576,  577,  578,   -1,  522,
   -1,  368,  583,  584,  585,   -1,  529,  278,  279,   -1,
  281,   -1,   -1,   -1,   -1,   -1,  597,  598,   -1,  290,
  291,   -1,  293,   -1,   -1,   -1,  297,   -1,   -1,  610,
   -1,   -1,   -1,  614,   -1,   -1,   -1,  560,   -1,   -1,
   -1,   -1,  409,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  321,   -1,   -1,  324,  325,   -1,   -1,  580,  329,  426,
   -1,  332,   -1,  334,   -1,   -1,   -1,   -1,   -1,  592,
   -1,   -1,  343,   -1,   -1,   -1,   -1,  348,   -1,   -1,
   -1,  604,  449,   -1,  607,  608,  453,   -1,   -1,   -1,
   -1,  614,  363,   -1,   -1,   -1,   -1,  368,   -1,  370,
   -1,   -1,   -1,   -1,  375,   -1,  377,  378,  379,   -1,
  381,  382,  383,   -1,  385,  386,  387,  388,  485,  390,
  391,  392,  393,  394,  395,  396,  397,  398,  399,   -1,
   -1,   -1,   -1,   -1,  405,   -1,  407,   -1,  505,   -1,
  507,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  424,   -1,  522,  427,  428,   -1,   -1,
   -1,   -1,  529,  434,   -1,   -1,   -1,   -1,  439,   -1,
  441,   -1,  443,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  453,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  560,   -1,   -1,   -1,  468,   -1,   -1,
  471,   -1,  473,   -1,   -1,   -1,   -1,  478,   -1,   -1,
   -1,   -1,   -1,  580,   -1,   -1,   -1,   -1,   -1,   -1,
  491,   -1,   -1,   -1,   -1,  592,   -1,   -1,   -1,   -1,
   -1,  502,   -1,   -1,   -1,   -1,   -1,  604,   -1,   -1,
  607,  608,   -1,   -1,   -1,   -1,   -1,  614,  519,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  530,
   -1,   -1,   -1,   -1,   -1,  536,  537,   -1,   -1,   -1,
  541,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  550,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  559,   -1,
   -1,  562,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  260,
  571,  262,  263,   -1,   -1,  576,  577,  578,   -1,   -1,
   -1,   -1,  583,  584,  585,   -1,   -1,  278,  279,   -1,
  281,   -1,   -1,   -1,   -1,   -1,  597,  598,   -1,  290,
  291,   -1,  293,   -1,   -1,   -1,  297,   -1,   -1,  610,
   -1,   -1,   -1,  614,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  321,   -1,   -1,  324,  325,   -1,  269,   -1,  329,  272,
   -1,  332,   -1,  334,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  343,   -1,   -1,   -1,   -1,  348,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  363,   -1,   -1,   -1,   -1,  368,   -1,  370,
   -1,   -1,   -1,  316,  375,   -1,  377,  378,  379,   -1,
  381,  382,  383,   -1,  385,  386,  387,  388,   -1,  390,
  391,  392,  393,  394,  395,  396,  397,  398,  399,   -1,
   -1,   -1,   -1,   -1,  405,   -1,  407,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  424,   -1,  368,  427,  428,   -1,   -1,
   -1,   -1,   -1,  434,   -1,   -1,   -1,   -1,  439,   -1,
  441,   -1,  443,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  453,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  409,  468,   -1,   -1,
  471,   -1,  473,   -1,   -1,   -1,   -1,  478,   -1,   -1,
   -1,   -1,   -1,  426,   -1,   -1,   -1,   -1,   -1,   -1,
  491,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  502,   -1,   -1,   -1,   -1,  449,   -1,   -1,   -1,
  453,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  519,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  530,
   -1,   -1,   -1,   -1,   -1,  536,  537,   -1,   -1,   -1,
  541,   -1,  485,   -1,   -1,   -1,   -1,   -1,   -1,  550,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  559,   -1,
   -1,  562,  505,   -1,  507,   -1,   -1,   -1,   -1,  260,
  571,  262,  263,   -1,   -1,  576,  577,  578,   -1,  522,
   -1,   -1,  583,  584,  585,   -1,  529,  278,  279,   -1,
  281,   -1,   -1,   -1,   -1,   -1,  597,  598,   -1,  290,
  291,   -1,  293,   -1,   -1,   -1,  297,   -1,   -1,  610,
   -1,   -1,   -1,  614,   -1,   -1,   -1,  560,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  321,   -1,   -1,  324,  325,   -1,   -1,  580,  329,   -1,
   -1,  332,   -1,  334,   -1,   -1,   -1,   -1,   -1,  592,
   -1,   -1,  343,   -1,   -1,   -1,   -1,  348,   -1,   -1,
   -1,  604,   -1,   -1,  607,  608,   -1,   -1,   -1,   -1,
   -1,  614,  363,   -1,   -1,   -1,   -1,  368,   -1,  370,
   -1,   -1,   -1,   -1,  375,   -1,  377,  378,  379,   -1,
  381,  382,  383,   -1,  385,  386,  387,  388,   -1,  390,
  391,  392,  393,  394,  395,  396,  397,  398,  399,   -1,
   -1,   -1,   -1,   -1,  405,   -1,  407,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  424,   -1,   -1,  427,  428,   -1,   -1,
   -1,   -1,   -1,  434,   -1,   -1,   -1,   -1,  439,   -1,
  441,   -1,  443,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  453,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  468,   -1,   -1,
  471,   -1,  473,   -1,   -1,   -1,   -1,  478,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  491,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  502,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  519,   -1,
   -1,   -1,   -1,   -1,  260,   -1,  262,  263,   -1,  530,
   -1,   -1,   -1,   -1,   -1,  536,  537,   -1,   -1,   -1,
  541,   -1,  278,  279,   -1,  281,   -1,   -1,   -1,  550,
   -1,   -1,   -1,   -1,  290,  291,   -1,  293,  559,   -1,
   -1,  562,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  571,   -1,   -1,   -1,   -1,  576,  577,  578,   -1,   -1,
   -1,   -1,  583,  584,  585,  321,   -1,   -1,  324,  325,
   -1,   -1,   -1,  329,   -1,   -1,  597,  598,  334,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  343,   -1,  610,
   -1,   -1,  348,  614,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  363,   -1,   -1,
   -1,   -1,  368,   -1,  370,   -1,   -1,   -1,   -1,  375,
   -1,  377,  378,  379,   -1,  381,  382,  383,   -1,  385,
  386,  387,  388,   -1,  390,  391,  392,  393,  394,  395,
  396,  397,  398,  399,   -1,   -1,   -1,   -1,   -1,  405,
   -1,  407,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  424,   -1,
   -1,  427,  428,   -1,   -1,   -1,   -1,   -1,  434,   -1,
   -1,   -1,   -1,  439,   -1,  441,   -1,  443,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  462,   -1,   -1,   -1,
   -1,   -1,  468,   -1,   -1,  471,   -1,  473,   -1,   -1,
   -1,   -1,  478,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  491,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  502,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  519,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  528,   -1,  260,   -1,  262,  263,   -1,   -1,
  536,  537,   -1,   -1,   -1,  541,   -1,   -1,   -1,   -1,
   -1,   -1,  278,  279,  550,  281,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  559,  290,  291,  562,  293,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  571,   -1,   -1,   -1,   -1,
  576,  577,  578,   -1,   -1,   -1,   -1,  583,  584,  585,
   -1,   -1,   -1,   -1,   -1,  321,   -1,   -1,  324,  325,
   -1,  597,  598,  329,   -1,   -1,   -1,   -1,  334,   -1,
   -1,   -1,   -1,   -1,  610,   -1,   -1,  343,  614,   -1,
   -1,   -1,  348,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  363,   -1,   -1,
   -1,   -1,  368,   -1,  370,   -1,   -1,   -1,   -1,  375,
   -1,  377,  378,  379,   -1,  381,  382,  383,   -1,  385,
  386,  387,  388,   -1,  390,  391,  392,  393,  394,  395,
  396,  397,  398,  399,   -1,   -1,   -1,   -1,   -1,  405,
   -1,  407,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  424,   -1,
   -1,  427,  428,   -1,   -1,   -1,   -1,   -1,  434,   -1,
   -1,   -1,   -1,  439,   -1,  441,   -1,  443,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  462,   -1,   -1,   -1,
   -1,   -1,  468,   -1,   -1,  471,   -1,  473,   -1,   -1,
   -1,   -1,  478,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  491,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  502,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  519,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  528,   -1,  260,   -1,  262,  263,   -1,   -1,
  536,  537,   -1,   -1,   -1,  541,   -1,   -1,   -1,   -1,
   -1,   -1,  278,  279,  550,  281,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  559,  290,  291,  562,  293,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  571,   -1,   -1,   -1,   -1,
  576,  577,  578,   -1,   -1,   -1,   -1,  583,  584,  585,
   -1,   -1,   -1,   -1,   -1,  321,   -1,   -1,  324,  325,
   -1,  597,  598,  329,   -1,   -1,   -1,   -1,  334,   -1,
   -1,   -1,   -1,   -1,  610,   -1,   -1,  343,  614,   -1,
   -1,   -1,  348,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  363,   -1,   -1,
   -1,   -1,  368,   -1,  370,   -1,   -1,   -1,   -1,  375,
   -1,  377,  378,  379,   -1,  381,  382,  383,   -1,  385,
  386,  387,  388,   -1,  390,  391,  392,  393,  394,  395,
  396,  397,  398,  399,   -1,   -1,   -1,   -1,   -1,  405,
   -1,  407,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  424,   -1,
   -1,  427,  428,   -1,   -1,   -1,   -1,   -1,  434,   -1,
   -1,   -1,   -1,  439,   -1,  441,   -1,  443,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  468,   -1,   -1,  471,   -1,  473,   -1,   -1,
   -1,   -1,  478,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  489,   -1,  491,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  502,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  519,   -1,   -1,   -1,   -1,   -1,  260,
   -1,  262,  263,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  536,  537,   -1,   -1,   -1,  541,   -1,  278,  279,   -1,
  281,   -1,   -1,   -1,  550,   -1,   -1,   -1,   -1,  290,
  291,   -1,  293,  559,   -1,  561,  562,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  571,   -1,   -1,   -1,   -1,
  576,  577,  578,   -1,   -1,   -1,   -1,  583,  584,  585,
  321,   -1,   -1,  324,  325,   -1,   -1,   -1,  329,   -1,
   -1,  597,  598,  334,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  343,   -1,  610,   -1,   -1,  348,  614,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  363,   -1,   -1,   -1,   -1,  368,   -1,  370,
   -1,   -1,   -1,   -1,  375,   -1,  377,  378,  379,   -1,
  381,  382,  383,   -1,  385,  386,  387,  388,   -1,  390,
  391,  392,  393,  394,  395,  396,  397,  398,  399,   -1,
   -1,   -1,   -1,   -1,  405,   -1,  407,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  424,   -1,   -1,  427,  428,   -1,   -1,
   -1,   -1,   -1,  434,   -1,   -1,   -1,   -1,  439,   -1,
  441,   -1,  443,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  468,   -1,   -1,
  471,   -1,  473,   -1,   -1,   -1,   -1,  478,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  491,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  502,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  519,   -1,
   -1,   -1,   -1,   -1,  260,   -1,  262,  263,   -1,  530,
   -1,   -1,   -1,   -1,   -1,  536,  537,   -1,   -1,   -1,
  541,   -1,  278,  279,   -1,  281,   -1,   -1,   -1,  550,
   -1,   -1,   -1,   -1,  290,  291,   -1,  293,  559,   -1,
   -1,  562,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  571,   -1,   -1,   -1,   -1,  576,  577,  578,   -1,   -1,
   -1,   -1,  583,  584,  585,  321,   -1,   -1,  324,  325,
   -1,   -1,   -1,  329,   -1,   -1,  597,  598,  334,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  343,   -1,  610,
   -1,   -1,  348,  614,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  363,   -1,   -1,
   -1,   -1,  368,   -1,  370,   -1,   -1,   -1,   -1,  375,
   -1,  377,  378,  379,   -1,  381,  382,  383,   -1,  385,
  386,  387,  388,   -1,  390,  391,  392,  393,  394,  395,
  396,  397,  398,  399,   -1,   -1,   -1,   -1,   -1,  405,
   -1,  407,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  424,   -1,
   -1,  427,  428,   -1,   -1,   -1,   -1,   -1,  434,   -1,
   -1,   -1,   -1,  439,   -1,  441,   -1,  443,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  468,   -1,   -1,  471,   -1,  473,   -1,   -1,
   -1,   -1,  478,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  491,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  502,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  519,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  263,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  536,  537,   -1,   -1,   -1,  541,   -1,  278,  279,   -1,
  281,  282,   -1,   -1,  550,   -1,   -1,   -1,   -1,  290,
  291,   -1,  293,  559,   -1,   -1,  562,   -1,   -1,   -1,
   -1,   -1,  316,   -1,   -1,  571,   -1,   -1,   -1,   -1,
  576,  577,  578,   -1,   -1,   -1,   -1,  583,  584,  585,
  321,   -1,   -1,  324,  325,  339,  340,   -1,  329,   -1,
   -1,  597,  598,  334,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  343,   -1,  610,   -1,   -1,  348,  614,   -1,
   -1,   -1,   -1,   -1,  368,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  363,   -1,   -1,  366,   -1,  368,   -1,  370,
   -1,   -1,   -1,   -1,  375,   -1,  377,  378,  379,   -1,
  381,  382,  383,   -1,  385,  386,  387,  388,   -1,  390,
  391,  392,  393,  394,  395,  396,  397,  398,  399,   -1,
   -1,   -1,   -1,   -1,  405,   -1,  407,   -1,   -1,  267,
   -1,  269,   -1,  271,  272,  429,   -1,   -1,  276,   -1,
   -1,   -1,   -1,  424,   -1,   -1,  427,  428,   -1,   -1,
   -1,   -1,   -1,  434,   -1,  449,   -1,   -1,  439,  453,
  441,   -1,  443,   -1,   -1,  459,  460,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  312,  313,   -1,  315,  316,  317,
   -1,  462,  476,   -1,   -1,   -1,   -1,  468,   -1,   -1,
  471,   -1,  473,   -1,   -1,   -1,   -1,  478,   -1,   -1,
  338,  339,  340,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  491,  505,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  502,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  368,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  519,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  536,  537,   -1,   -1,   -1,
  541,   -1,   -1,   -1,   -1,  403,  560,   -1,   -1,  550,
  564,  409,   -1,   -1,   -1,   -1,   -1,   -1,  559,   -1,
   -1,  562,  420,  421,  422,  579,   -1,   -1,  426,   -1,
  571,  429,   -1,  431,   -1,  576,  577,  578,  592,   -1,
  594,   -1,  583,  584,  585,   -1,   -1,  316,   -1,   -1,
  604,  449,   -1,  607,   -1,  453,  597,  598,   -1,   -1,
  614,  459,  460,   -1,   -1,   -1,  464,  465,   -1,  610,
  339,  340,   -1,  614,   -1,   -1,   -1,   -1,  476,  477,
   -1,   -1,   -1,   -1,  267,   -1,  269,  485,  271,   -1,
   -1,   -1,   -1,  276,   -1,   -1,   -1,   -1,   -1,  368,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  505,   -1,  507,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  522,   -1,   -1,   -1,   -1,  312,
  313,  529,  315,  316,  317,   -1,  534,   -1,   -1,   -1,
   -1,  539,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  552,  338,  339,   -1,   -1,   -1,
  429,   -1,  560,  561,   -1,   -1,  564,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  449,  579,  580,   -1,  453,  368,   -1,   -1,   -1,   -1,
  459,  460,   -1,   -1,  592,   -1,  594,  595,   -1,   -1,
   -1,   -1,   -1,  601,   -1,  603,  604,  476,  606,  607,
  608,   -1,   -1,  611,   -1,   -1,  614,   -1,   -1,   -1,
  403,   -1,   -1,   -1,   -1,   -1,  409,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  505,  420,  421,  422,
   -1,   -1,   -1,  426,   -1,   -1,   -1,   -1,  431,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  449,   -1,   -1,   -1,
  453,   -1,   -1,   -1,   -1,   -1,  459,   -1,   -1,   -1,
   -1,  464,  465,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  560,   -1,   -1,  477,  564,   -1,   -1,   -1,   -1,
   -1,   -1,  485,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  579,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  505,  592,  507,  594,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  604,   -1,   -1,  607,  522,
   -1,   -1,   -1,   -1,   -1,  614,  529,   -1,   -1,   -1,
   -1,  534,   -1,   -1,   -1,   -1,  539,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  552,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  560,  561,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  269,   -1,  271,  272,
   -1,   -1,   -1,  276,   -1,  278,  279,  580,  281,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  290,  291,  592,
  293,   -1,  595,   -1,   -1,   -1,   -1,   -1,  601,   -1,
  603,  604,   -1,  606,  607,  608,   -1,  310,  611,  312,
  313,  614,  315,  316,  317,   -1,   -1,   -1,  321,   -1,
   -1,  324,  325,   -1,   -1,   -1,  329,   -1,   -1,   -1,
   -1,  334,   -1,   -1,   -1,  338,  339,   -1,   -1,   -1,
  343,   -1,   -1,   -1,   -1,  348,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  363,   -1,   -1,   -1,   -1,  368,   -1,  370,   -1,   -1,
   -1,   -1,  375,   -1,  377,  378,  379,   -1,  381,  382,
  383,  384,  385,  386,  387,  388,   -1,  390,  391,  392,
  393,  394,  395,  396,  397,  398,  399,   -1,   -1,   -1,
  403,   -1,  405,  406,  407,   -1,  409,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  420,  421,  422,
   -1,  424,   -1,  426,  427,  428,   -1,   -1,  431,   -1,
   -1,  434,   -1,   -1,   -1,   -1,  439,   -1,  441,   -1,
  443,   -1,   -1,   -1,   -1,   -1,  449,   -1,   -1,   -1,
  453,   -1,   -1,   -1,   -1,   -1,  459,   -1,   -1,   -1,
   -1,  464,  465,   -1,   -1,  468,   -1,   -1,  471,   -1,
  473,   -1,   -1,   -1,  477,  478,   -1,   -1,   -1,   -1,
   -1,   -1,  485,   -1,   -1,   -1,  489,   -1,  491,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  502,
   -1,   -1,  505,   -1,  507,  508,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  519,   -1,   -1,  522,
   -1,   -1,   -1,   -1,   -1,   -1,  529,   -1,   -1,   -1,
   -1,  534,   -1,  536,  537,   -1,  539,   -1,  541,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  550,   -1,  552,
   -1,   -1,   -1,   -1,   -1,   -1,  559,  560,  561,  562,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  571,   -1,
   -1,   -1,   -1,  576,  577,  578,   -1,  580,   -1,   -1,
  583,  584,  585,   -1,   -1,   -1,   -1,   -1,   -1,  592,
   -1,   -1,  595,   -1,  597,  598,   -1,   -1,  601,   -1,
  603,  604,   -1,  606,  607,  608,   -1,  610,  611,   -1,
  269,  614,  271,  272,   -1,   -1,   -1,  276,   -1,  278,
  279,   -1,  281,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  290,  291,   -1,  293,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  310,   -1,  312,  313,   -1,  315,  316,  317,   -1,
   -1,   -1,  321,   -1,   -1,  324,  325,   -1,   -1,   -1,
  329,   -1,   -1,   -1,   -1,  334,   -1,   -1,   -1,  338,
  339,   -1,   -1,   -1,  343,   -1,   -1,   -1,   -1,  348,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  363,   -1,   -1,   -1,   -1,  368,
   -1,  370,   -1,   -1,   -1,   -1,  375,   -1,  377,  378,
  379,   -1,  381,  382,  383,  384,  385,  386,  387,  388,
   -1,  390,  391,  392,  393,  394,  395,  396,  397,  398,
  399,   -1,   -1,   -1,  403,   -1,  405,  406,  407,   -1,
  409,   -1,   -1,   -1,   -1,   -1,   -1,  269,   -1,   -1,
  272,  420,  421,  422,   -1,  424,   -1,  426,  427,  428,
   -1,   -1,  431,   -1,   -1,  434,   -1,   -1,   -1,   -1,
  439,   -1,  441,   -1,  443,   -1,   -1,   -1,   -1,   -1,
  449,   -1,   -1,   -1,  453,   -1,   -1,   -1,   -1,   -1,
  459,   -1,   -1,   -1,  316,  464,  465,   -1,   -1,  468,
   -1,   -1,  471,   -1,  473,   -1,   -1,   -1,  477,  478,
   -1,   -1,   -1,   -1,   -1,   -1,  485,   -1,   -1,   -1,
  489,   -1,  491,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  502,   -1,   -1,  505,   -1,  507,  508,
   -1,   -1,   -1,   -1,   -1,   -1,  368,   -1,   -1,   -1,
  519,  316,  269,  522,  271,  272,   -1,   -1,   -1,  276,
  529,   -1,   -1,   -1,   -1,  534,   -1,  536,  537,   -1,
  539,   -1,  541,   -1,  339,  340,   -1,  269,   -1,   -1,
  272,  550,   -1,  552,   -1,   -1,   -1,  409,   -1,   -1,
  559,  560,  561,  562,   -1,  312,  313,   -1,  315,  316,
  317,   -1,  571,  368,  426,   -1,   -1,  576,  577,  578,
   -1,  580,   -1,   -1,  583,  584,  585,   -1,   -1,   -1,
   -1,  338,  339,  592,  316,   -1,  595,  449,  597,  598,
   -1,  453,  601,   -1,  603,  604,   -1,  606,  607,  608,
   -1,  610,  611,   -1,   -1,  614,   -1,   -1,   -1,   -1,
   -1,  368,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  485,  429,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  368,   -1,   -1,   -1,
   -1,   -1,   -1,  505,  449,  507,  403,   -1,  453,   -1,
   -1,   -1,  409,   -1,  459,  460,   -1,   -1,   -1,   -1,
  522,   -1,   -1,  420,  421,  422,   -1,  529,   -1,  426,
   -1,  476,   -1,   -1,  431,   -1,   -1,  409,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  449,   -1,  426,   -1,  453,   -1,  560,   -1,
  505,   -1,  459,   -1,   -1,   -1,   -1,  464,  465,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  449,  580,   -1,
  477,  453,   -1,   -1,   -1,   -1,   -1,   -1,  485,   -1,
  592,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  604,   -1,   -1,  607,  608,   -1,  505,   -1,
  507,   -1,  614,  485,   -1,  560,   -1,   -1,   -1,  564,
   -1,   -1,   -1,   -1,   -1,  522,   -1,   -1,   -1,   -1,
   -1,   -1,  529,  505,  579,  507,   -1,  534,   -1,   -1,
   -1,   -1,  539,   -1,   -1,   -1,   -1,  592,   -1,  594,
  522,   -1,   -1,   -1,   -1,  552,   -1,  529,   -1,  604,
   -1,   -1,  607,  560,  561,   -1,   -1,   -1,   -1,  614,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  580,   -1,   -1,   -1,   -1,  560,   -1,
   -1,   -1,   -1,   -1,   -1,  592,   -1,   -1,  595,   -1,
   -1,   -1,   -1,   -1,  601,   -1,  603,  604,  580,  606,
  607,  608,   -1,   -1,  611,   -1,   -1,  614,  271,  272,
  592,   -1,   -1,  276,   -1,  278,  279,   -1,  281,   -1,
   -1,   -1,  604,   -1,   -1,  607,  608,  290,  291,   -1,
  293,   -1,  614,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  310,   -1,  312,
  313,   -1,  315,  316,  317,   -1,   -1,   -1,  321,   -1,
   -1,  324,  325,   -1,   -1,   -1,  329,   -1,   -1,   -1,
   -1,  334,   -1,   -1,   -1,  338,  339,   -1,   -1,   -1,
  343,   -1,   -1,   -1,   -1,  348,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  363,   -1,   -1,   -1,   -1,  368,   -1,  370,   -1,   -1,
   -1,   -1,  375,   -1,  377,  378,  379,   -1,  381,  382,
  383,  384,  385,  386,  387,  388,   -1,  390,  391,  392,
  393,  394,  395,  396,  397,  398,  399,   -1,   -1,   -1,
  403,   -1,  405,  406,  407,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  420,  421,  422,
   -1,  424,   -1,   -1,  427,  428,   -1,   -1,  431,   -1,
   -1,  434,   -1,   -1,   -1,   -1,  439,   -1,  441,   -1,
  443,   -1,   -1,   -1,   -1,   -1,  449,   -1,   -1,   -1,
  453,   -1,   -1,   -1,   -1,   -1,  459,   -1,   -1,   -1,
   -1,  464,  465,   -1,   -1,  468,   -1,   -1,  471,   -1,
  473,   -1,   -1,   -1,  477,  478,   -1,  271,  272,   -1,
   -1,   -1,  276,   -1,   -1,   -1,  489,   -1,  491,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  502,
   -1,   -1,  505,   -1,   -1,  508,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  519,   -1,  312,  313,
   -1,  315,  316,  317,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  534,   -1,  536,  537,   -1,  539,   -1,  541,   -1,
   -1,   -1,   -1,   -1,  338,  339,   -1,  550,   -1,  552,
   -1,   -1,   -1,   -1,   -1,   -1,  559,  560,  561,  562,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  571,   -1,
   -1,   -1,   -1,  576,  577,  578,   -1,   -1,   -1,   -1,
  583,  584,  585,   -1,   -1,   -1,   -1,   -1,   -1,  592,
   -1,   -1,  595,   -1,  597,  598,   -1,   -1,  601,   -1,
  603,   -1,   -1,  606,  607,  608,   -1,  610,  611,  403,
   -1,  614,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  420,  421,  422,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  431,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  449,   -1,   -1,   -1,  453,
   -1,   -1,   -1,   -1,   -1,  459,   -1,   -1,   -1,   -1,
  464,  465,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  477,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  505,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  272,   -1,   -1,   -1,  276,   -1,  278,  279,
  534,  281,   -1,   -1,   -1,  539,   -1,   -1,   -1,   -1,
  290,  291,   -1,  293,   -1,   -1,   -1,   -1,  552,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  560,  561,   -1,   -1,
  310,   -1,  312,   -1,   -1,  315,  316,  317,   -1,   -1,
   -1,  321,   -1,   -1,  324,  325,   -1,   -1,   -1,  329,
   -1,   -1,   -1,   -1,  334,   -1,   -1,   -1,  592,  339,
   -1,  595,   -1,  343,   -1,   -1,   -1,  601,  348,  603,
   -1,   -1,  606,  607,  608,   -1,   -1,  611,   -1,   -1,
  614,   -1,   -1,  363,   -1,   -1,   -1,   -1,  368,   -1,
  370,   -1,   -1,   -1,   -1,  375,   -1,  377,  378,  379,
   -1,  381,  382,  383,  384,  385,  386,  387,  388,   -1,
  390,  391,  392,  393,  394,  395,  396,  397,  398,  399,
   -1,   -1,   -1,  403,   -1,  405,  406,  407,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  422,   -1,  424,   -1,   -1,  427,  428,   -1,
   -1,  431,   -1,   -1,  434,   -1,   -1,   -1,   -1,  439,
   -1,  441,   -1,  443,   -1,   -1,   -1,   -1,   -1,  449,
   -1,   -1,   -1,  453,   -1,   -1,   -1,   -1,   -1,  459,
   -1,   -1,   -1,   -1,  464,  465,   -1,   -1,  468,   -1,
   -1,  471,   -1,  473,   -1,   -1,   -1,  477,  478,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  489,
   -1,  491,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  502,   -1,   -1,   -1,   -1,   -1,  508,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  519,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  534,   -1,  536,  537,   -1,  539,
   -1,  541,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  550,   -1,  552,   -1,   -1,   -1,   -1,   -1,   -1,  559,
  560,   -1,  562,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  571,   -1,   -1,   -1,   -1,  576,  577,  578,   -1,
   -1,   -1,   -1,  583,  584,  585,   -1,  272,   -1,   -1,
   -1,  276,  592,  278,  279,  595,  281,  597,  598,   -1,
   -1,  601,   -1,  603,   -1,  290,  291,   -1,  293,   -1,
  610,  611,   -1,   -1,  614,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  310,   -1,  312,   -1,   -1,
  315,  316,  317,   -1,   -1,   -1,  321,   -1,   -1,  324,
  325,   -1,   -1,   -1,  329,   -1,   -1,   -1,   -1,  334,
   -1,   -1,   -1,   -1,  339,   -1,   -1,   -1,  343,   -1,
   -1,   -1,   -1,  348,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  363,   -1,
   -1,   -1,   -1,  368,   -1,  370,   -1,   -1,   -1,   -1,
  375,   -1,  377,  378,  379,   -1,  381,  382,  383,  384,
  385,  386,  387,  388,   -1,  390,  391,  392,  393,  394,
  395,  396,  397,  398,  399,   -1,   -1,   -1,  403,   -1,
  405,  406,  407,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  422,   -1,  424,
   -1,   -1,  427,  428,   -1,   -1,  431,   -1,   -1,  434,
   -1,   -1,   -1,   -1,  439,   -1,  441,   -1,  443,   -1,
   -1,   -1,   -1,   -1,  449,   -1,   -1,   -1,  453,   -1,
   -1,   -1,   -1,   -1,  459,   -1,   -1,   -1,   -1,  464,
  465,   -1,   -1,  468,   -1,   -1,  471,   -1,  473,   -1,
   -1,   -1,  477,  478,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  489,   -1,  491,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  502,   -1,   -1,
   -1,   -1,   -1,  508,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  519,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  534,
   -1,  536,  537,   -1,  539,   -1,  541,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  550,   -1,  552,   -1,   -1,
   -1,   -1,   -1,   -1,  559,  560,   -1,  562,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  571,   -1,   -1,   -1,
   -1,  576,  577,  578,   -1,   -1,   -1,   -1,  583,  584,
  585,   -1,  272,   -1,   -1,   -1,  276,  592,  278,  279,
  595,  281,  597,  598,   -1,   -1,  601,   -1,  603,   -1,
  290,  291,   -1,  293,   -1,  610,  611,   -1,   -1,  614,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  310,   -1,  312,   -1,   -1,  315,  316,  317,   -1,   -1,
   -1,  321,   -1,   -1,  324,  325,   -1,   -1,   -1,  329,
   -1,   -1,   -1,   -1,  334,   -1,   -1,   -1,   -1,  339,
   -1,   -1,   -1,  343,   -1,   -1,   -1,   -1,  348,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  363,   -1,   -1,   -1,   -1,  368,   -1,
  370,   -1,   -1,   -1,   -1,  375,   -1,  377,  378,  379,
   -1,  381,  382,  383,  384,  385,  386,  387,  388,   -1,
  390,  391,  392,  393,  394,  395,  396,  397,  398,  399,
   -1,   -1,   -1,  403,   -1,  405,  406,  407,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  422,   -1,  424,   -1,   -1,  427,  428,   -1,
   -1,  431,   -1,   -1,  434,   -1,   -1,   -1,   -1,  439,
   -1,  441,   -1,  443,   -1,   -1,   -1,   -1,   -1,  449,
   -1,   -1,   -1,  453,   -1,   -1,   -1,   -1,   -1,  459,
   -1,   -1,   -1,   -1,  464,  465,   -1,   -1,  468,   -1,
   -1,  471,   -1,  473,   -1,   -1,   -1,  477,  478,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  489,
   -1,  491,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  502,   -1,   -1,   -1,   -1,   -1,  508,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  519,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  534,   -1,  536,  537,   -1,  539,
   -1,  541,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  550,   -1,  552,   -1,   -1,   -1,   -1,   -1,   -1,  559,
  560,   -1,  562,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  571,   -1,   -1,   -1,   -1,  576,  577,  578,   -1,
   -1,   -1,   -1,  583,  584,  585,   -1,  272,   -1,   -1,
   -1,  276,  592,  278,  279,  595,  281,  597,  598,   -1,
   -1,  601,   -1,  603,   -1,  290,  291,   -1,  293,   -1,
  610,  611,   -1,   -1,  614,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  312,   -1,   -1,
  315,  316,  317,   -1,   -1,   -1,  321,   -1,   -1,  324,
  325,   -1,   -1,   -1,  329,   -1,   -1,   -1,   -1,  334,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  343,   -1,
   -1,   -1,   -1,  348,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  363,   -1,
   -1,   -1,   -1,  368,   -1,  370,   -1,   -1,   -1,   -1,
  375,   -1,  377,  378,  379,   -1,  381,  382,  383,   -1,
  385,  386,  387,  388,   -1,  390,  391,  392,  393,  394,
  395,  396,  397,  398,  399,   -1,   -1,   -1,  403,   -1,
  405,  406,  407,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  422,   -1,  424,
   -1,   -1,  427,  428,   -1,   -1,  431,   -1,   -1,  434,
   -1,   -1,   -1,   -1,  439,   -1,  441,   -1,  443,   -1,
   -1,   -1,   -1,   -1,  449,   -1,   -1,   -1,  453,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  464,
  465,   -1,   -1,  468,   -1,   -1,  471,   -1,  473,   -1,
   -1,   -1,  477,  478,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  489,   -1,  491,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  502,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  519,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  534,
   -1,  536,  537,   -1,  539,   -1,  541,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  550,   -1,  552,   -1,   -1,
   -1,   -1,   -1,   -1,  559,  560,   -1,  562,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  571,   -1,   -1,   -1,
   -1,  576,  577,  578,   -1,   -1,   -1,   -1,  583,  584,
  585,   -1,  272,   -1,   -1,   -1,  276,  592,  278,  279,
  595,  281,  597,  598,   -1,   -1,  601,   -1,  603,   -1,
  290,  291,   -1,  293,   -1,  610,   -1,   -1,   -1,  614,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  312,   -1,   -1,  315,  316,  317,   -1,   -1,
   -1,  321,   -1,   -1,  324,  325,   -1,   -1,   -1,  329,
   -1,   -1,   -1,   -1,  334,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  343,   -1,   -1,   -1,   -1,  348,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  363,   -1,   -1,   -1,   -1,  368,   -1,
  370,   -1,   -1,   -1,   -1,  375,   -1,   -1,  378,  379,
   -1,  381,  382,  383,   -1,  385,  386,  387,  388,   -1,
  390,  391,  392,  393,  394,  395,  396,  397,  398,  399,
   -1,   -1,   -1,  403,   -1,  405,  406,  407,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  422,   -1,  424,   -1,   -1,  427,  428,   -1,
   -1,  431,   -1,   -1,  434,   -1,   -1,   -1,   -1,  439,
   -1,  441,   -1,  443,   -1,   -1,   -1,   -1,   -1,  449,
   -1,   -1,   -1,  453,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  464,  465,   -1,   -1,  468,   -1,
   -1,  471,   -1,  473,   -1,   -1,   -1,  477,  478,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  491,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  502,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  519,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  534,   -1,  536,  537,   -1,  539,
   -1,  541,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  550,   -1,  552,   -1,   -1,   -1,   -1,   -1,   -1,  559,
  560,   -1,  562,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  571,   -1,   -1,   -1,   -1,  576,  577,  578,   -1,
   -1,   -1,   -1,  583,  584,  585,   -1,  272,   -1,   -1,
   -1,  276,  592,  278,  279,  595,  281,  597,  598,   -1,
   -1,  601,   -1,  603,   -1,  290,  291,   -1,  293,   -1,
  610,   -1,   -1,   -1,  614,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  312,   -1,   -1,
  315,  316,  317,   -1,   -1,   -1,  321,   -1,   -1,  324,
  325,   -1,   -1,   -1,  329,   -1,   -1,   -1,   -1,  334,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  343,   -1,
   -1,   -1,   -1,  348,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  363,   -1,
   -1,   -1,   -1,  368,   -1,  370,   -1,   -1,   -1,   -1,
  375,   -1,  377,  378,  379,   -1,  381,  382,  383,   -1,
  385,  386,  387,  388,   -1,  390,  391,  392,  393,  394,
  395,  396,  397,  398,  399,   -1,   -1,   -1,  403,   -1,
  405,   -1,  407,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  422,   -1,  424,
   -1,   -1,  427,  428,   -1,   -1,  431,   -1,   -1,  434,
   -1,   -1,   -1,   -1,  439,   -1,  441,   -1,  443,   -1,
   -1,   -1,   -1,   -1,  449,   -1,   -1,   -1,  453,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  464,
  465,   -1,   -1,  468,   -1,   -1,  471,   -1,  473,   -1,
   -1,   -1,  477,  478,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  491,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  502,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  519,   -1,  256,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  534,
   -1,  536,  537,   -1,  539,   -1,  541,   -1,  278,  279,
   -1,  281,   -1,   -1,   -1,  550,   -1,  552,   -1,   -1,
   -1,  291,   -1,  293,  559,  560,   -1,  562,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  571,   -1,   -1,   -1,
   -1,  576,  577,  578,   -1,   -1,   -1,   -1,  583,  584,
  585,  321,   -1,   -1,  324,  325,   -1,  592,   -1,  329,
  595,   -1,  597,  598,  334,   -1,  601,   -1,  603,   -1,
   -1,   -1,   -1,  343,   -1,  610,  272,   -1,  348,  614,
  276,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  363,   -1,   -1,   -1,   -1,  368,   -1,
  370,   -1,   -1,   -1,   -1,   -1,  376,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  312,  313,   -1,  315,
  316,  317,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  405,   -1,  407,   -1,   -1,
   -1,   -1,  338,  339,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  424,   -1,   -1,  427,  428,   -1,
   -1,   -1,   -1,   -1,  434,   -1,   -1,   -1,   -1,  439,
   -1,  441,   -1,  443,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  468,   -1,
   -1,  471,   -1,  473,   -1,   -1,   -1,  403,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  491,   -1,   -1,  420,  421,  422,   -1,   -1,   -1,
   -1,   -1,  502,   -1,   -1,  431,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  519,
   -1,   -1,   -1,  449,   -1,   -1,   -1,  453,   -1,   -1,
   -1,   -1,   -1,  459,   -1,   -1,  536,  537,  464,  465,
   -1,  541,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  550,  477,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  559,
   -1,   -1,  562,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  571,   -1,   -1,   -1,   -1,  576,  577,  578,  505,
   -1,   -1,   -1,  583,  584,  585,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  597,  598,   -1,
  276,   -1,  278,  279,   -1,  281,   -1,   -1,  534,   -1,
   -1,   -1,   -1,  539,  290,  291,   -1,  293,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  552,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  560,  561,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  321,   -1,   -1,  324,  325,
   -1,   -1,   -1,  329,   -1,   -1,   -1,   -1,  334,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  592,  343,   -1,  595,
   -1,   -1,  348,   -1,   -1,  601,   -1,  603,   -1,   -1,
  606,  607,  608,   -1,   -1,  611,   -1,  363,  614,   -1,
   -1,   -1,  368,   -1,  370,   -1,   -1,   -1,   -1,  375,
   -1,  377,  378,  379,   -1,  381,  382,  383,  384,  385,
  386,  387,  388,   -1,  390,  391,  392,  393,  394,  395,
  396,  397,  398,  399,   -1,   -1,   -1,  403,   -1,  405,
   -1,  407,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  424,   -1,
   -1,  427,  428,   -1,   -1,   -1,   -1,   -1,  434,   -1,
   -1,   -1,   -1,  439,   -1,  441,   -1,  443,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  468,   -1,   -1,  471,   -1,  473,   -1,   -1,
   -1,   -1,  478,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  491,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  502,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  519,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  536,  537,   -1,   -1,   -1,  541,   -1,   -1,   -1,   -1,
  276,   -1,  278,  279,  550,  281,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  559,  290,  291,  562,  293,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  571,   -1,   -1,   -1,   -1,
  576,  577,  578,   -1,   -1,   -1,   -1,  583,  584,  585,
   -1,   -1,   -1,   -1,   -1,  321,   -1,   -1,  324,  325,
   -1,  597,  598,  329,   -1,   -1,   -1,   -1,  334,   -1,
   -1,   -1,   -1,   -1,  610,  611,   -1,  343,  614,   -1,
   -1,   -1,  348,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  363,   -1,   -1,
   -1,   -1,  368,   -1,  370,   -1,   -1,   -1,   -1,  375,
   -1,  377,  378,  379,   -1,  381,  382,  383,   -1,  385,
  386,  387,  388,   -1,  390,  391,  392,  393,  394,  395,
  396,  397,  398,  399,   -1,   -1,   -1,  403,   -1,  405,
   -1,  407,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  424,   -1,
   -1,  427,  428,   -1,   -1,   -1,   -1,   -1,  434,   -1,
   -1,   -1,   -1,  439,   -1,  441,   -1,  443,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  468,   -1,   -1,  471,   -1,  473,   -1,   -1,
   -1,   -1,  478,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  491,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  502,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  519,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  536,  537,   -1,   -1,   -1,  541,   -1,  278,  279,   -1,
  281,   -1,   -1,   -1,  550,   -1,   -1,   -1,   -1,  290,
  291,   -1,  293,  559,   -1,   -1,  562,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  571,   -1,   -1,   -1,  310,
  576,  577,  578,   -1,   -1,   -1,   -1,  583,  584,  585,
  321,   -1,   -1,  324,  325,   -1,   -1,   -1,  329,   -1,
   -1,  597,  598,  334,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  343,   -1,  610,   -1,   -1,  348,  614,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  363,   -1,   -1,   -1,   -1,  368,   -1,  370,
   -1,   -1,   -1,   -1,  375,  376,  377,  378,  379,   -1,
  381,  382,  383,   -1,  385,  386,  387,  388,   -1,  390,
  391,  392,  393,  394,  395,  396,  397,  398,  399,   -1,
   -1,   -1,   -1,   -1,  405,   -1,  407,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  424,   -1,   -1,  427,  428,   -1,   -1,
   -1,   -1,   -1,  434,  435,   -1,   -1,   -1,  439,   -1,
  441,   -1,  443,   -1,  445,  446,   -1,   -1,   -1,  450,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  463,   -1,   -1,   -1,   -1,  468,   -1,   -1,
  471,   -1,  473,   -1,   -1,   -1,   -1,  478,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  491,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  502,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  519,  520,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  536,  537,   -1,   -1,   -1,
  541,   -1,  278,  279,   -1,  281,   -1,   -1,   -1,  550,
   -1,   -1,   -1,   -1,  290,  291,   -1,  293,  559,   -1,
   -1,  562,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  571,   -1,   -1,   -1,  310,  576,  577,  578,   -1,   -1,
   -1,   -1,  583,  584,  585,  321,   -1,   -1,  324,  325,
   -1,   -1,   -1,  329,   -1,   -1,  597,  598,  334,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  343,   -1,  610,
  611,   -1,  348,  614,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  363,   -1,   -1,
   -1,   -1,  368,   -1,  370,   -1,   -1,   -1,   -1,  375,
  376,  377,  378,  379,   -1,  381,  382,  383,   -1,  385,
  386,  387,  388,   -1,  390,  391,  392,  393,  394,  395,
  396,  397,  398,  399,   -1,   -1,   -1,   -1,   -1,  405,
   -1,  407,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  424,   -1,
   -1,  427,  428,   -1,   -1,   -1,   -1,   -1,  434,  435,
   -1,   -1,   -1,  439,   -1,  441,   -1,  443,   -1,  445,
  446,   -1,   -1,   -1,  450,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  463,   -1,   -1,
   -1,   -1,  468,   -1,   -1,  471,   -1,  473,   -1,   -1,
   -1,   -1,  478,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  491,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  502,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  519,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  536,  537,   -1,   -1,   -1,  541,   -1,  278,  279,   -1,
  281,   -1,   -1,   -1,  550,   -1,   -1,   -1,   -1,  290,
  291,   -1,  293,  559,   -1,   -1,  562,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  571,   -1,   -1,   -1,  310,
  576,  577,  578,   -1,   -1,   -1,   -1,  583,  584,  585,
  321,   -1,   -1,  324,  325,   -1,   -1,   -1,  329,   -1,
   -1,  597,  598,  334,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  343,   -1,  610,  611,   -1,  348,  614,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  363,   -1,   -1,   -1,   -1,  368,   -1,  370,
   -1,   -1,   -1,   -1,  375,  376,  377,  378,  379,   -1,
  381,  382,  383,   -1,  385,  386,  387,  388,   -1,  390,
  391,  392,  393,  394,  395,  396,  397,  398,  399,   -1,
   -1,   -1,   -1,   -1,  405,   -1,  407,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  424,   -1,   -1,  427,  428,   -1,   -1,
   -1,   -1,   -1,  434,  435,   -1,   -1,   -1,  439,   -1,
  441,   -1,  443,   -1,   -1,  446,   -1,   -1,   -1,  450,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  463,   -1,   -1,   -1,   -1,  468,   -1,   -1,
  471,   -1,  473,   -1,   -1,   -1,   -1,  478,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  491,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  502,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  519,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  536,  537,   -1,   -1,   -1,
  541,   -1,  278,  279,   -1,  281,   -1,   -1,   -1,  550,
   -1,   -1,   -1,   -1,  290,  291,   -1,  293,  559,   -1,
   -1,  562,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  571,   -1,   -1,   -1,  310,  576,  577,  578,   -1,   -1,
   -1,   -1,  583,  584,  585,  321,   -1,   -1,  324,  325,
   -1,   -1,   -1,  329,   -1,   -1,  597,  598,  334,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  343,   -1,  610,
  611,   -1,  348,  614,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  363,   -1,   -1,
   -1,   -1,  368,   -1,  370,   -1,   -1,   -1,   -1,  375,
  376,  377,  378,  379,   -1,  381,  382,  383,   -1,  385,
  386,  387,  388,   -1,  390,  391,  392,  393,  394,  395,
  396,  397,  398,  399,   -1,   -1,   -1,   -1,   -1,  405,
   -1,  407,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  424,   -1,
   -1,  427,  428,   -1,   -1,   -1,   -1,   -1,  434,  435,
   -1,   -1,   -1,  439,   -1,  441,   -1,  443,   -1,   -1,
  446,   -1,   -1,   -1,  450,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  463,   -1,   -1,
   -1,   -1,  468,   -1,   -1,  471,   -1,  473,   -1,   -1,
   -1,   -1,  478,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  491,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  502,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  519,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  536,  537,   -1,   -1,   -1,  541,   -1,  278,  279,   -1,
  281,   -1,   -1,   -1,  550,   -1,   -1,   -1,   -1,  290,
  291,   -1,  293,  559,   -1,   -1,  562,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  571,   -1,   -1,   -1,   -1,
  576,  577,  578,   -1,   -1,   -1,   -1,  583,  584,  585,
  321,   -1,   -1,  324,  325,   -1,   -1,   -1,  329,   -1,
   -1,  597,  598,  334,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  343,   -1,  610,   -1,   -1,  348,  614,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  363,   -1,   -1,   -1,   -1,  368,   -1,  370,
   -1,   -1,   -1,   -1,  375,   -1,  377,  378,  379,   -1,
  381,  382,  383,   -1,  385,  386,  387,  388,   -1,  390,
  391,  392,  393,  394,  395,  396,  397,  398,  399,   -1,
   -1,   -1,   -1,   -1,  405,  406,  407,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  424,  425,   -1,  427,  428,   -1,   -1,
   -1,   -1,   -1,  434,   -1,   -1,   -1,   -1,  439,   -1,
  441,   -1,  443,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  468,   -1,   -1,
  471,   -1,  473,   -1,   -1,   -1,   -1,  478,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  489,   -1,
  491,   -1,   -1,   -1,   -1,   -1,  497,   -1,   -1,   -1,
   -1,  502,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  519,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  536,  537,  538,   -1,   -1,
  541,   -1,   -1,   -1,   -1,   -1,   -1,  278,  279,  550,
  281,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  559,  290,
  291,  562,  293,   -1,   -1,   -1,  297,   -1,   -1,   -1,
  571,   -1,   -1,   -1,   -1,  576,  577,  578,   -1,   -1,
   -1,   -1,  583,  584,  585,   -1,   -1,   -1,   -1,   -1,
  321,   -1,   -1,  324,  325,   -1,  597,  598,  329,   -1,
   -1,  332,   -1,  334,   -1,   -1,   -1,   -1,   -1,  610,
   -1,   -1,  343,  614,   -1,   -1,   -1,  348,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  363,   -1,   -1,   -1,   -1,  368,   -1,  370,
   -1,   -1,   -1,   -1,  375,   -1,  377,  378,  379,   -1,
  381,  382,  383,   -1,  385,  386,  387,  388,   -1,  390,
  391,  392,  393,  394,  395,  396,  397,  398,  399,   -1,
   -1,   -1,   -1,   -1,  405,   -1,  407,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  417,   -1,   -1,   -1,
   -1,   -1,   -1,  424,   -1,   -1,  427,  428,   -1,   -1,
   -1,   -1,   -1,  434,   -1,   -1,   -1,   -1,  439,   -1,
  441,   -1,  443,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  453,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  468,   -1,   -1,
  471,   -1,  473,   -1,   -1,   -1,   -1,  478,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  491,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  502,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  519,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  536,  537,   -1,   -1,   -1,
  541,   -1,   -1,   -1,   -1,   -1,   -1,  278,  279,  550,
  281,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  559,  290,
  291,  562,  293,   -1,   -1,   -1,  297,   -1,   -1,   -1,
  571,   -1,   -1,   -1,   -1,  576,  577,  578,   -1,   -1,
   -1,   -1,  583,  584,  585,   -1,   -1,   -1,   -1,   -1,
  321,  592,   -1,  324,  325,   -1,  597,  598,  329,   -1,
   -1,  332,   -1,  334,   -1,   -1,   -1,   -1,   -1,  610,
   -1,   -1,  343,  614,   -1,   -1,   -1,  348,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  363,   -1,   -1,   -1,   -1,  368,   -1,  370,
   -1,   -1,   -1,   -1,  375,   -1,  377,  378,  379,   -1,
  381,  382,  383,   -1,  385,  386,  387,  388,   -1,  390,
  391,  392,  393,  394,  395,  396,  397,  398,  399,   -1,
   -1,   -1,   -1,   -1,  405,   -1,  407,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  417,   -1,   -1,   -1,
   -1,   -1,   -1,  424,   -1,   -1,  427,  428,   -1,   -1,
   -1,   -1,   -1,  434,   -1,   -1,   -1,   -1,  439,   -1,
  441,   -1,  443,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  453,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  468,   -1,   -1,
  471,   -1,  473,   -1,   -1,   -1,   -1,  478,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  491,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  502,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  519,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  536,  537,   -1,   -1,   -1,
  541,   -1,  278,  279,   -1,  281,   -1,   -1,   -1,  550,
   -1,   -1,   -1,   -1,  290,  291,   -1,  293,  559,   -1,
  296,  562,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  571,   -1,   -1,   -1,   -1,  576,  577,  578,  314,   -1,
   -1,   -1,  583,  584,  585,  321,   -1,   -1,  324,  325,
   -1,  592,   -1,  329,   -1,   -1,  597,  598,  334,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  343,   -1,  610,
   -1,   -1,  348,  614,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  363,   -1,   -1,
   -1,   -1,  368,   -1,  370,   -1,   -1,   -1,   -1,  375,
   -1,  377,  378,  379,   -1,  381,  382,  383,   -1,  385,
  386,  387,  388,   -1,  390,  391,  392,  393,  394,  395,
  396,  397,  398,  399,   -1,   -1,   -1,   -1,   -1,  405,
   -1,  407,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  424,   -1,
   -1,  427,  428,   -1,   -1,   -1,   -1,   -1,  434,   -1,
   -1,   -1,   -1,  439,   -1,  441,   -1,  443,   -1,   -1,
  446,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  468,   -1,   -1,  471,   -1,  473,   -1,   -1,
   -1,   -1,  478,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  491,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  502,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  519,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  536,  537,   -1,   -1,   -1,  541,   -1,  278,  279,   -1,
  281,   -1,   -1,   -1,  550,   -1,   -1,   -1,   -1,  290,
  291,   -1,  293,  559,   -1,   -1,  562,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  571,   -1,   -1,   -1,  310,
  576,  577,  578,   -1,   -1,   -1,   -1,  583,  584,  585,
  321,   -1,   -1,  324,  325,   -1,   -1,   -1,  329,   -1,
   -1,  597,  598,  334,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  343,   -1,  610,   -1,   -1,  348,  614,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  363,   -1,   -1,   -1,   -1,  368,   -1,  370,
   -1,   -1,   -1,   -1,  375,  376,  377,  378,  379,   -1,
  381,  382,  383,   -1,  385,  386,  387,  388,   -1,  390,
  391,  392,  393,  394,  395,  396,  397,  398,  399,   -1,
   -1,   -1,   -1,   -1,  405,   -1,  407,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  424,   -1,   -1,  427,  428,   -1,   -1,
   -1,   -1,   -1,  434,   -1,   -1,   -1,   -1,  439,   -1,
  441,   -1,  443,   -1,  445,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  468,   -1,   -1,
  471,   -1,  473,   -1,   -1,   -1,   -1,  478,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  491,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  502,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  519,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  536,  537,   -1,   -1,   -1,
  541,   -1,  278,  279,   -1,  281,   -1,   -1,   -1,  550,
   -1,   -1,   -1,   -1,  290,  291,   -1,  293,  559,   -1,
   -1,  562,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  571,   -1,   -1,   -1,   -1,  576,  577,  578,   -1,   -1,
   -1,   -1,  583,  584,  585,  321,   -1,   -1,  324,  325,
   -1,   -1,   -1,  329,   -1,   -1,  597,  598,  334,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  343,   -1,  610,
   -1,   -1,  348,  614,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  363,   -1,   -1,
   -1,   -1,  368,   -1,  370,   -1,   -1,   -1,   -1,  375,
   -1,  377,  378,  379,   -1,  381,  382,  383,   -1,  385,
  386,  387,  388,   -1,  390,  391,  392,  393,  394,  395,
  396,  397,  398,  399,   -1,   -1,   -1,   -1,   -1,  405,
  406,  407,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  424,   -1,
   -1,  427,  428,   -1,   -1,   -1,   -1,   -1,  434,   -1,
   -1,   -1,   -1,  439,   -1,  441,   -1,  443,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  468,   -1,   -1,  471,   -1,  473,   -1,   -1,
   -1,   -1,  478,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  489,   -1,  491,   -1,   -1,   -1,   -1,
   -1,  497,   -1,   -1,   -1,   -1,  502,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  519,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  536,  537,   -1,   -1,   -1,  541,   -1,  278,  279,   -1,
  281,   -1,   -1,   -1,  550,   -1,   -1,   -1,   -1,  290,
  291,   -1,  293,  559,   -1,   -1,  562,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  571,   -1,   -1,   -1,   -1,
  576,  577,  578,   -1,   -1,   -1,   -1,  583,  584,  585,
  321,   -1,   -1,  324,  325,   -1,   -1,   -1,  329,   -1,
   -1,  597,  598,  334,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  343,   -1,  610,   -1,   -1,  348,  614,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  363,   -1,   -1,   -1,   -1,  368,   -1,  370,
   -1,   -1,   -1,   -1,  375,   -1,  377,  378,  379,   -1,
  381,  382,  383,   -1,  385,  386,  387,  388,   -1,  390,
  391,  392,  393,  394,  395,  396,  397,  398,  399,   -1,
   -1,   -1,   -1,   -1,  405,   -1,  407,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  424,   -1,   -1,  427,  428,   -1,   -1,
   -1,   -1,   -1,  434,   -1,   -1,   -1,   -1,  439,   -1,
  441,   -1,  443,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  468,   -1,   -1,
  471,   -1,  473,   -1,   -1,   -1,   -1,  478,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  491,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  502,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  519,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  536,  537,   -1,   -1,   -1,
  541,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  550,
   -1,   -1,   -1,   -1,   -1,   -1,  278,  279,  559,  281,
   -1,  562,   -1,   -1,   -1,   -1,   -1,   -1,  290,  291,
  571,  293,   -1,   -1,   -1,  576,  577,  578,   -1,   -1,
   -1,   -1,  583,  584,  585,  586,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  597,  598,  599,  321,
   -1,   -1,  324,  325,   -1,   -1,   -1,  329,  609,  610,
   -1,   -1,  334,  614,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  343,   -1,   -1,   -1,   -1,  348,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  363,   -1,   -1,   -1,   -1,  368,   -1,  370,   -1,
   -1,   -1,   -1,  375,   -1,  377,  378,  379,   -1,  381,
  382,  383,   -1,  385,  386,  387,  388,   -1,  390,  391,
  392,  393,  394,  395,  396,  397,  398,  399,   -1,   -1,
   -1,   -1,   -1,  405,   -1,  407,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  424,   -1,   -1,  427,  428,   -1,   -1,   -1,
   -1,   -1,  434,   -1,   -1,   -1,   -1,  439,   -1,  441,
   -1,  443,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  468,   -1,   -1,  471,
   -1,  473,   -1,   -1,   -1,   -1,  478,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  489,   -1,  491,
   -1,   -1,   -1,   -1,   -1,  497,   -1,   -1,   -1,   -1,
  502,   -1,   -1,   -1,   -1,  507,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  519,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  536,  537,   -1,   -1,   -1,  541,
   -1,  278,  279,   -1,  281,   -1,   -1,   -1,  550,   -1,
   -1,   -1,   -1,  290,  291,   -1,  293,  559,   -1,   -1,
  562,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  571,
   -1,   -1,   -1,   -1,  576,  577,  578,   -1,   -1,   -1,
   -1,  583,  584,  585,  321,   -1,   -1,  324,  325,   -1,
   -1,   -1,  329,   -1,   -1,  597,  598,  334,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  343,   -1,  610,   -1,
   -1,  348,  614,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  363,   -1,   -1,   -1,
   -1,  368,   -1,  370,   -1,   -1,   -1,   -1,  375,   -1,
  377,  378,  379,   -1,  381,  382,  383,   -1,  385,  386,
  387,  388,   -1,  390,  391,  392,  393,  394,  395,  396,
  397,  398,  399,   -1,   -1,   -1,   -1,   -1,  405,  406,
  407,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  424,   -1,   -1,
  427,  428,   -1,   -1,   -1,   -1,   -1,  434,   -1,   -1,
   -1,   -1,  439,   -1,  441,   -1,  443,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  468,   -1,   -1,  471,   -1,  473,   -1,   -1,   -1,
   -1,  478,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  489,   -1,  491,   -1,   -1,   -1,   -1,   -1,
  497,   -1,   -1,   -1,   -1,  502,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  519,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  536,
  537,   -1,   -1,   -1,  541,   -1,  278,  279,   -1,  281,
   -1,   -1,   -1,  550,   -1,   -1,   -1,   -1,  290,  291,
   -1,  293,  559,   -1,   -1,  562,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  571,   -1,   -1,   -1,  310,  576,
  577,  578,   -1,   -1,   -1,   -1,  583,  584,  585,  321,
   -1,   -1,  324,  325,   -1,   -1,   -1,  329,   -1,   -1,
  597,  598,  334,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  343,   -1,  610,   -1,   -1,  348,  614,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  363,   -1,   -1,   -1,   -1,  368,   -1,  370,   -1,
   -1,   -1,   -1,  375,  376,  377,  378,  379,   -1,  381,
  382,  383,   -1,  385,  386,  387,  388,   -1,  390,  391,
  392,  393,  394,  395,  396,  397,  398,  399,   -1,   -1,
   -1,   -1,   -1,  405,   -1,  407,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  424,   -1,   -1,  427,  428,   -1,   -1,   -1,
   -1,   -1,  434,   -1,   -1,   -1,   -1,  439,   -1,  441,
   -1,  443,   -1,   -1,  446,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  468,   -1,   -1,  471,
   -1,  473,   -1,   -1,   -1,   -1,  478,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  491,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  502,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  519,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  536,  537,   -1,   -1,   -1,  541,
   -1,  278,  279,   -1,  281,   -1,   -1,   -1,  550,   -1,
   -1,   -1,   -1,  290,  291,   -1,  293,  559,   -1,   -1,
  562,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  571,
   -1,   -1,   -1,  310,  576,  577,  578,   -1,   -1,   -1,
   -1,  583,  584,  585,  321,   -1,   -1,  324,  325,   -1,
   -1,   -1,  329,   -1,   -1,  597,  598,  334,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  343,   -1,  610,   -1,
   -1,  348,  614,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  363,   -1,   -1,   -1,
   -1,  368,   -1,  370,   -1,   -1,   -1,   -1,  375,  376,
  377,  378,  379,   -1,  381,  382,  383,   -1,  385,  386,
  387,  388,   -1,  390,  391,  392,  393,  394,  395,  396,
  397,  398,  399,   -1,   -1,   -1,   -1,   -1,  405,   -1,
  407,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  424,   -1,   -1,
  427,  428,   -1,   -1,   -1,   -1,   -1,  434,   -1,   -1,
   -1,   -1,  439,   -1,  441,   -1,  443,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  468,   -1,   -1,  471,   -1,  473,   -1,   -1,   -1,
   -1,  478,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  491,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  502,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  519,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  536,
  537,   -1,   -1,   -1,  541,   -1,  278,  279,   -1,  281,
   -1,   -1,   -1,  550,   -1,   -1,   -1,   -1,  290,  291,
   -1,  293,  559,   -1,   -1,  562,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  571,   -1,   -1,   -1,   -1,  576,
  577,  578,   -1,   -1,   -1,   -1,  583,  584,  585,  321,
   -1,   -1,  324,  325,   -1,   -1,   -1,  329,   -1,   -1,
  597,  598,  334,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  343,   -1,  610,   -1,   -1,  348,  614,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  363,   -1,   -1,   -1,   -1,  368,   -1,  370,   -1,
   -1,   -1,   -1,  375,   -1,  377,  378,  379,   -1,  381,
  382,  383,   -1,  385,  386,  387,  388,   -1,  390,  391,
  392,  393,  394,  395,  396,  397,  398,  399,   -1,   -1,
   -1,   -1,   -1,  405,   -1,  407,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  424,   -1,   -1,  427,  428,   -1,   -1,   -1,
   -1,   -1,  434,   -1,   -1,   -1,   -1,  439,   -1,  441,
   -1,  443,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  468,   -1,   -1,  471,
   -1,  473,   -1,   -1,   -1,   -1,  478,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  489,   -1,  491,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  502,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  519,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  536,  537,   -1,   -1,   -1,  541,
   -1,  278,  279,   -1,  281,   -1,   -1,   -1,  550,   -1,
   -1,   -1,   -1,  290,  291,   -1,  293,  559,   -1,  561,
  562,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  571,
   -1,   -1,   -1,   -1,  576,  577,  578,   -1,   -1,   -1,
   -1,  583,  584,  585,  321,   -1,   -1,  324,  325,   -1,
   -1,   -1,  329,   -1,   -1,  597,  598,  334,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  343,   -1,  610,   -1,
   -1,  348,  614,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  363,   -1,   -1,   -1,
   -1,  368,   -1,  370,   -1,   -1,   -1,   -1,  375,   -1,
  377,  378,  379,   -1,  381,  382,  383,   -1,  385,  386,
  387,  388,   -1,  390,  391,  392,  393,  394,  395,  396,
  397,  398,  399,   -1,   -1,   -1,   -1,   -1,  405,  406,
  407,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  424,   -1,   -1,
  427,  428,   -1,   -1,   -1,   -1,   -1,  434,   -1,   -1,
   -1,   -1,  439,   -1,  441,   -1,  443,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  468,   -1,   -1,  471,   -1,  473,   -1,   -1,   -1,
   -1,  478,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  491,   -1,   -1,   -1,   -1,   -1,
  497,   -1,   -1,   -1,   -1,  502,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  519,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  536,
  537,   -1,   -1,   -1,  541,   -1,  278,  279,   -1,  281,
   -1,   -1,   -1,  550,   -1,   -1,   -1,   -1,  290,  291,
   -1,  293,  559,   -1,   -1,  562,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  571,   -1,   -1,   -1,   -1,  576,
  577,  578,   -1,   -1,   -1,   -1,  583,  584,  585,  321,
   -1,   -1,  324,  325,   -1,   -1,   -1,  329,   -1,   -1,
  597,  598,  334,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  343,   -1,  610,   -1,   -1,  348,  614,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  363,   -1,   -1,   -1,   -1,  368,   -1,  370,   -1,
   -1,   -1,   -1,  375,   -1,  377,  378,  379,   -1,  381,
  382,  383,   -1,  385,  386,  387,  388,   -1,  390,  391,
  392,  393,  394,  395,  396,  397,  398,  399,   -1,   -1,
   -1,   -1,   -1,  405,   -1,  407,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  424,   -1,   -1,  427,  428,   -1,   -1,   -1,
   -1,   -1,  434,   -1,   -1,   -1,   -1,  439,   -1,  441,
   -1,  443,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  468,   -1,   -1,  471,
   -1,  473,   -1,   -1,   -1,   -1,  478,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  489,   -1,  491,
   -1,   -1,   -1,   -1,   -1,  497,   -1,   -1,   -1,   -1,
  502,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  519,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  536,  537,   -1,   -1,   -1,  541,
   -1,  278,  279,   -1,  281,   -1,   -1,   -1,  550,   -1,
   -1,   -1,   -1,  290,  291,   -1,  293,  559,   -1,   -1,
  562,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  571,
   -1,   -1,   -1,   -1,  576,  577,  578,   -1,   -1,   -1,
   -1,  583,  584,  585,  321,   -1,   -1,  324,  325,   -1,
   -1,   -1,  329,   -1,   -1,  597,  598,  334,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  343,   -1,  610,   -1,
   -1,  348,  614,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  363,   -1,   -1,   -1,
   -1,  368,   -1,  370,   -1,   -1,   -1,   -1,  375,   -1,
  377,  378,  379,   -1,  381,  382,  383,   -1,  385,  386,
  387,  388,   -1,  390,  391,  392,  393,  394,  395,  396,
  397,  398,  399,   -1,   -1,   -1,   -1,   -1,  405,   -1,
  407,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  424,  425,   -1,
  427,  428,   -1,   -1,   -1,   -1,   -1,  434,   -1,   -1,
   -1,   -1,  439,   -1,  441,   -1,  443,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  468,   -1,   -1,  471,   -1,  473,   -1,   -1,   -1,
   -1,  478,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  491,   -1,   -1,   -1,   -1,  496,
   -1,   -1,   -1,   -1,   -1,  502,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  519,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  536,
  537,   -1,   -1,   -1,  541,   -1,  278,  279,   -1,  281,
   -1,   -1,   -1,  550,   -1,   -1,   -1,   -1,  290,  291,
   -1,  293,  559,   -1,   -1,  562,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  571,   -1,   -1,   -1,   -1,  576,
  577,  578,   -1,   -1,   -1,   -1,  583,  584,  585,  321,
   -1,   -1,  324,  325,   -1,   -1,   -1,  329,   -1,   -1,
  597,  598,  334,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  343,   -1,  610,   -1,   -1,  348,  614,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  363,   -1,   -1,   -1,   -1,  368,   -1,  370,   -1,
   -1,   -1,   -1,  375,   -1,  377,  378,  379,   -1,  381,
  382,  383,   -1,  385,  386,  387,  388,   -1,  390,  391,
  392,  393,  394,  395,  396,  397,  398,  399,   -1,   -1,
   -1,   -1,   -1,  405,   -1,  407,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  424,   -1,   -1,  427,  428,   -1,   -1,   -1,
   -1,   -1,  434,   -1,   -1,   -1,   -1,  439,   -1,  441,
   -1,  443,   -1,   -1,  446,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  468,   -1,   -1,  471,
   -1,  473,   -1,   -1,   -1,   -1,  478,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  491,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  502,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  519,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  536,  537,   -1,   -1,   -1,  541,
   -1,  278,  279,   -1,  281,   -1,   -1,   -1,  550,   -1,
   -1,   -1,   -1,  290,  291,   -1,  293,  559,   -1,   -1,
  562,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  571,
   -1,   -1,   -1,   -1,  576,  577,  578,   -1,   -1,   -1,
   -1,  583,  584,  585,  321,   -1,   -1,  324,  325,   -1,
   -1,   -1,  329,   -1,   -1,  597,  598,  334,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  343,   -1,  610,   -1,
   -1,  348,  614,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  363,   -1,   -1,   -1,
   -1,  368,   -1,  370,   -1,   -1,   -1,   -1,  375,   -1,
  377,  378,  379,   -1,  381,  382,  383,   -1,  385,  386,
  387,  388,   -1,  390,  391,  392,  393,  394,  395,  396,
  397,  398,  399,   -1,   -1,   -1,   -1,   -1,  405,   -1,
  407,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  424,   -1,   -1,
  427,  428,   -1,   -1,   -1,   -1,   -1,  434,   -1,   -1,
   -1,   -1,  439,   -1,  441,   -1,  443,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  468,   -1,   -1,  471,   -1,  473,   -1,   -1,   -1,
   -1,  478,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  491,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  502,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  519,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  530,   -1,   -1,   -1,   -1,   -1,  536,
  537,   -1,   -1,   -1,  541,   -1,  278,  279,   -1,  281,
   -1,   -1,   -1,  550,   -1,   -1,   -1,   -1,  290,  291,
   -1,  293,  559,   -1,   -1,  562,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  571,   -1,   -1,   -1,   -1,  576,
  577,  578,   -1,   -1,   -1,   -1,  583,  584,  585,  321,
   -1,   -1,  324,  325,   -1,   -1,   -1,  329,   -1,   -1,
  597,  598,  334,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  343,   -1,  610,   -1,   -1,  348,  614,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  363,   -1,   -1,   -1,   -1,  368,   -1,  370,   -1,
   -1,   -1,   -1,  375,   -1,  377,  378,  379,   -1,  381,
  382,  383,   -1,  385,  386,  387,  388,   -1,  390,  391,
  392,  393,  394,  395,  396,  397,  398,  399,   -1,   -1,
   -1,   -1,   -1,  405,   -1,  407,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  424,   -1,   -1,  427,  428,   -1,   -1,   -1,
   -1,   -1,  434,   -1,   -1,   -1,   -1,  439,   -1,  441,
   -1,  443,   -1,   -1,  446,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  468,   -1,   -1,  471,
   -1,  473,   -1,   -1,   -1,   -1,  478,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  491,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  502,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  519,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  536,  537,   -1,   -1,   -1,  541,
   -1,  278,  279,   -1,  281,   -1,   -1,   -1,  550,   -1,
   -1,   -1,   -1,  290,  291,   -1,  293,  559,   -1,   -1,
  562,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  571,
   -1,   -1,   -1,   -1,  576,  577,  578,   -1,   -1,   -1,
   -1,  583,  584,  585,  321,   -1,   -1,  324,  325,   -1,
   -1,   -1,  329,   -1,   -1,  597,  598,  334,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  343,   -1,  610,   -1,
   -1,  348,  614,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  363,   -1,   -1,   -1,
   -1,  368,   -1,  370,   -1,   -1,   -1,   -1,  375,   -1,
  377,  378,  379,   -1,  381,  382,  383,   -1,  385,  386,
  387,  388,   -1,  390,  391,  392,  393,  394,  395,  396,
  397,  398,  399,   -1,   -1,   -1,   -1,   -1,  405,   -1,
  407,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  424,   -1,   -1,
  427,  428,   -1,   -1,   -1,   -1,   -1,  434,   -1,   -1,
   -1,   -1,  439,   -1,  441,   -1,  443,   -1,   -1,  446,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  468,   -1,   -1,  471,   -1,  473,   -1,   -1,   -1,
   -1,  478,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  491,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  502,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  519,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  536,
  537,   -1,   -1,   -1,  541,   -1,  278,  279,   -1,  281,
   -1,   -1,   -1,  550,   -1,   -1,   -1,   -1,  290,  291,
   -1,  293,  559,   -1,   -1,  562,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  571,   -1,   -1,   -1,   -1,  576,
  577,  578,   -1,   -1,   -1,   -1,  583,  584,  585,  321,
   -1,   -1,  324,  325,   -1,   -1,   -1,  329,   -1,   -1,
  597,  598,  334,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  343,   -1,  610,   -1,   -1,  348,  614,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  363,   -1,   -1,   -1,   -1,  368,   -1,  370,   -1,
   -1,   -1,   -1,  375,   -1,  377,  378,  379,   -1,  381,
  382,  383,   -1,  385,  386,  387,  388,   -1,  390,  391,
  392,  393,  394,  395,  396,  397,  398,  399,   -1,   -1,
   -1,   -1,   -1,  405,   -1,  407,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  424,   -1,   -1,  427,  428,   -1,   -1,   -1,
   -1,   -1,  434,   -1,   -1,   -1,   -1,  439,   -1,  441,
   -1,  443,   -1,   -1,  446,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  468,   -1,   -1,  471,
   -1,  473,   -1,   -1,   -1,   -1,  478,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  491,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  502,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  519,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  536,  537,   -1,   -1,   -1,  541,
   -1,  278,  279,   -1,  281,   -1,   -1,   -1,  550,   -1,
   -1,   -1,   -1,  290,  291,   -1,  293,  559,   -1,   -1,
  562,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  571,
   -1,   -1,   -1,   -1,  576,  577,  578,   -1,   -1,   -1,
   -1,  583,  584,  585,  321,   -1,   -1,  324,  325,   -1,
   -1,   -1,  329,   -1,   -1,  597,  598,  334,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  343,   -1,  610,   -1,
   -1,  348,  614,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  363,   -1,   -1,   -1,
   -1,  368,   -1,  370,   -1,   -1,   -1,   -1,  375,   -1,
  377,  378,  379,   -1,  381,  382,  383,   -1,  385,  386,
  387,  388,   -1,  390,  391,  392,  393,  394,  395,  396,
  397,  398,  399,   -1,   -1,   -1,   -1,   -1,  405,  406,
  407,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  424,   -1,   -1,
  427,  428,   -1,   -1,   -1,   -1,   -1,  434,   -1,   -1,
   -1,   -1,  439,   -1,  441,   -1,  443,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  468,   -1,   -1,  471,   -1,  473,   -1,   -1,   -1,
   -1,  478,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  491,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  502,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  519,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  536,
  537,   -1,   -1,   -1,  541,   -1,  278,  279,   -1,  281,
   -1,   -1,   -1,  550,   -1,   -1,   -1,   -1,  290,  291,
   -1,  293,  559,   -1,   -1,  562,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  571,   -1,   -1,   -1,   -1,  576,
  577,  578,   -1,   -1,   -1,   -1,  583,  584,  585,  321,
   -1,   -1,  324,  325,   -1,   -1,   -1,  329,   -1,   -1,
  597,  598,  334,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  343,   -1,  610,   -1,   -1,  348,  614,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  363,   -1,   -1,   -1,   -1,  368,   -1,  370,   -1,
   -1,   -1,   -1,  375,   -1,  377,  378,  379,   -1,  381,
  382,  383,   -1,  385,  386,  387,  388,   -1,  390,  391,
  392,  393,  394,  395,  396,  397,  398,  399,   -1,   -1,
   -1,   -1,   -1,  405,   -1,  407,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  424,   -1,   -1,  427,  428,   -1,   -1,   -1,
   -1,   -1,  434,   -1,   -1,   -1,   -1,  439,   -1,  441,
   -1,  443,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  468,   -1,   -1,  471,
   -1,  473,   -1,   -1,   -1,   -1,  478,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  491,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  502,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  519,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  530,   -1,
   -1,   -1,   -1,   -1,  536,  537,   -1,   -1,   -1,  541,
   -1,  278,  279,   -1,  281,   -1,   -1,   -1,  550,   -1,
   -1,   -1,   -1,  290,  291,   -1,  293,  559,   -1,   -1,
  562,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  571,
   -1,   -1,   -1,   -1,  576,  577,  578,   -1,   -1,   -1,
   -1,  583,  584,  585,  321,   -1,   -1,  324,  325,   -1,
   -1,   -1,  329,   -1,   -1,  597,  598,  334,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  343,   -1,  610,   -1,
   -1,  348,  614,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  363,   -1,   -1,   -1,
   -1,  368,   -1,  370,   -1,   -1,   -1,   -1,  375,   -1,
  377,  378,  379,   -1,  381,  382,  383,   -1,  385,  386,
  387,  388,   -1,  390,  391,  392,  393,  394,  395,  396,
  397,  398,  399,   -1,   -1,   -1,   -1,   -1,  405,   -1,
  407,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  424,   -1,   -1,
  427,  428,   -1,   -1,   -1,   -1,   -1,  434,   -1,   -1,
   -1,   -1,  439,   -1,  441,   -1,  443,   -1,   -1,  446,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  468,   -1,   -1,  471,   -1,  473,   -1,   -1,   -1,
   -1,  478,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  491,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  502,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  519,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  536,
  537,   -1,   -1,   -1,  541,   -1,  278,  279,   -1,  281,
   -1,   -1,   -1,  550,   -1,   -1,   -1,   -1,  290,  291,
   -1,  293,  559,   -1,   -1,  562,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  571,   -1,   -1,   -1,   -1,  576,
  577,  578,   -1,   -1,   -1,   -1,  583,  584,  585,  321,
   -1,   -1,  324,  325,   -1,   -1,   -1,  329,   -1,   -1,
  597,  598,  334,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  343,   -1,  610,   -1,   -1,  348,  614,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  363,   -1,   -1,   -1,   -1,  368,   -1,  370,   -1,
   -1,   -1,   -1,  375,   -1,  377,  378,  379,   -1,  381,
  382,  383,   -1,  385,  386,  387,  388,   -1,  390,  391,
  392,  393,  394,  395,  396,  397,  398,  399,   -1,   -1,
   -1,   -1,   -1,  405,   -1,  407,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  424,   -1,   -1,  427,  428,   -1,   -1,   -1,
   -1,   -1,  434,   -1,   -1,   -1,   -1,  439,   -1,  441,
   -1,  443,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  468,   -1,   -1,  471,
   -1,  473,   -1,   -1,   -1,   -1,  478,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  491,
   -1,   -1,   -1,   -1,   -1,  497,   -1,   -1,   -1,   -1,
  502,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  519,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  536,  537,   -1,   -1,   -1,  541,
   -1,  278,  279,   -1,  281,   -1,   -1,   -1,  550,   -1,
   -1,   -1,   -1,  290,  291,   -1,  293,  559,   -1,  296,
  562,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  571,
   -1,   -1,   -1,   -1,  576,  577,  578,   -1,   -1,   -1,
   -1,  583,  584,  585,  321,   -1,   -1,  324,  325,   -1,
   -1,   -1,  329,   -1,   -1,  597,  598,  334,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  343,   -1,  610,   -1,
   -1,  348,  614,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  363,   -1,   -1,   -1,
   -1,  368,   -1,  370,   -1,   -1,   -1,   -1,  375,   -1,
  377,  378,  379,   -1,  381,  382,  383,   -1,  385,  386,
  387,  388,   -1,  390,  391,  392,  393,  394,  395,  396,
  397,  398,  399,   -1,   -1,   -1,   -1,   -1,  405,   -1,
  407,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  424,   -1,   -1,
  427,  428,   -1,   -1,   -1,   -1,   -1,  434,   -1,   -1,
   -1,   -1,  439,   -1,  441,   -1,  443,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  468,   -1,   -1,  471,   -1,  473,   -1,   -1,   -1,
   -1,  478,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  491,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  502,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  519,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  536,
  537,   -1,   -1,   -1,  541,   -1,  278,  279,   -1,  281,
   -1,   -1,   -1,  550,   -1,   -1,   -1,   -1,  290,  291,
   -1,  293,  559,   -1,  296,  562,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  571,   -1,   -1,   -1,   -1,  576,
  577,  578,   -1,   -1,   -1,   -1,  583,  584,  585,  321,
   -1,   -1,  324,  325,   -1,   -1,   -1,  329,   -1,   -1,
  597,  598,  334,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  343,   -1,  610,   -1,   -1,  348,  614,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  363,   -1,   -1,   -1,   -1,  368,   -1,  370,   -1,
   -1,   -1,   -1,  375,   -1,  377,  378,  379,   -1,  381,
  382,  383,   -1,  385,  386,  387,  388,   -1,  390,  391,
  392,  393,  394,  395,  396,  397,  398,  399,   -1,   -1,
   -1,   -1,   -1,  405,   -1,  407,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  424,   -1,   -1,  427,  428,   -1,   -1,   -1,
   -1,   -1,  434,   -1,   -1,   -1,   -1,  439,   -1,  441,
   -1,  443,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  468,   -1,   -1,  471,
   -1,  473,   -1,   -1,   -1,   -1,  478,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  491,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  502,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  519,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  536,  537,   -1,   -1,   -1,  541,
   -1,  278,  279,   -1,  281,   -1,   -1,   -1,  550,   -1,
   -1,   -1,   -1,  290,  291,   -1,  293,  559,   -1,   -1,
  562,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  571,
   -1,   -1,   -1,   -1,  576,  577,  578,   -1,   -1,   -1,
   -1,  583,  584,  585,  321,   -1,   -1,  324,  325,   -1,
   -1,   -1,  329,   -1,   -1,  597,  598,  334,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  343,   -1,  610,   -1,
   -1,  348,  614,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  363,   -1,   -1,   -1,
   -1,  368,   -1,  370,   -1,   -1,   -1,   -1,  375,   -1,
  377,  378,  379,   -1,  381,  382,  383,   -1,  385,  386,
  387,  388,   -1,  390,  391,  392,  393,  394,  395,  396,
  397,  398,  399,   -1,   -1,   -1,   -1,   -1,  405,   -1,
  407,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  424,   -1,   -1,
  427,  428,   -1,   -1,   -1,   -1,   -1,  434,   -1,   -1,
   -1,   -1,  439,   -1,  441,   -1,  443,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  468,   -1,   -1,  471,   -1,  473,   -1,   -1,   -1,
   -1,  478,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  491,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  502,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  519,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  536,
  537,   -1,   -1,   -1,  541,   -1,  278,  279,   -1,  281,
   -1,   -1,   -1,  550,   -1,   -1,   -1,   -1,  290,  291,
   -1,  293,  559,   -1,   -1,  562,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  571,   -1,   -1,   -1,   -1,  576,
  577,  578,   -1,   -1,   -1,   -1,  583,  584,  585,  321,
   -1,   -1,  324,  325,   -1,   -1,   -1,  329,   -1,   -1,
  597,  598,  334,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  343,   -1,  610,   -1,   -1,  348,  614,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  363,   -1,   -1,   -1,   -1,  368,   -1,  370,   -1,
   -1,   -1,   -1,  375,   -1,  377,  378,  379,   -1,  381,
  382,  383,   -1,  385,  386,  387,  388,   -1,  390,  391,
  392,  393,  394,  395,  396,  397,  398,  399,   -1,   -1,
   -1,   -1,   -1,  405,   -1,  407,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  424,   -1,   -1,  427,  428,   -1,   -1,   -1,
   -1,   -1,  434,   -1,   -1,   -1,   -1,  439,   -1,  441,
   -1,  443,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  468,   -1,   -1,  471,
   -1,  473,   -1,   -1,   -1,   -1,  478,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  491,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  502,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  519,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  536,  537,   -1,   -1,   -1,  541,
   -1,  278,  279,   -1,  281,   -1,   -1,   -1,  550,   -1,
   -1,   -1,   -1,  290,  291,   -1,  293,  559,   -1,   -1,
  562,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  571,
   -1,   -1,   -1,   -1,  576,  577,  578,   -1,   -1,   -1,
   -1,  583,  584,  585,  321,   -1,   -1,  324,  325,   -1,
   -1,   -1,  329,   -1,   -1,  597,  598,  334,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  343,   -1,  610,   -1,
   -1,  348,  614,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  363,   -1,   -1,   -1,
   -1,  368,   -1,  370,   -1,   -1,   -1,   -1,  375,   -1,
  377,  378,  379,   -1,  381,  382,  383,   -1,  385,  386,
  387,  388,   -1,  390,  391,  392,  393,  394,  395,  396,
  397,  398,  399,   -1,   -1,   -1,   -1,   -1,  405,   -1,
  407,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  424,   -1,   -1,
  427,  428,   -1,   -1,   -1,   -1,   -1,  434,   -1,   -1,
   -1,   -1,  439,   -1,  441,   -1,  443,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  468,   -1,   -1,  471,   -1,  473,   -1,   -1,   -1,
   -1,  478,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  491,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  502,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  519,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  536,
  537,   -1,   -1,   -1,  541,   -1,  278,  279,   -1,  281,
   -1,   -1,   -1,  550,   -1,   -1,   -1,   -1,  290,  291,
   -1,  293,  559,   -1,   -1,  562,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  571,   -1,   -1,   -1,   -1,  576,
  577,  578,   -1,   -1,   -1,   -1,  583,  584,  585,  321,
   -1,   -1,  324,  325,   -1,   -1,   -1,  329,   -1,   -1,
  597,  598,  334,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  343,   -1,  610,   -1,   -1,  348,  614,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  363,   -1,   -1,   -1,   -1,  368,   -1,  370,   -1,
   -1,   -1,   -1,  375,   -1,  377,  378,  379,   -1,  381,
  382,  383,   -1,  385,  386,  387,  388,   -1,  390,  391,
  392,  393,  394,  395,  396,  397,  398,  399,   -1,   -1,
   -1,   -1,   -1,  405,   -1,  407,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  424,   -1,   -1,  427,  428,   -1,   -1,   -1,
   -1,   -1,  434,   -1,   -1,   -1,   -1,  439,   -1,  441,
   -1,  443,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  468,   -1,   -1,  471,
   -1,  473,   -1,   -1,   -1,   -1,  478,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  491,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  502,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  519,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  536,  537,   -1,   -1,   -1,  541,
   -1,  278,  279,   -1,  281,   -1,   -1,   -1,  550,   -1,
   -1,   -1,   -1,  290,  291,   -1,  293,  559,   -1,   -1,
  562,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  571,
   -1,   -1,   -1,   -1,  576,  577,  578,   -1,   -1,   -1,
   -1,  583,  584,  585,  321,   -1,   -1,  324,  325,   -1,
   -1,   -1,  329,   -1,   -1,  597,  598,  334,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  343,   -1,  610,   -1,
   -1,  348,  614,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  363,   -1,   -1,   -1,
   -1,  368,   -1,  370,   -1,   -1,   -1,   -1,  375,   -1,
  377,  378,  379,   -1,  381,  382,  383,   -1,  385,  386,
  387,  388,   -1,  390,  391,  392,  393,  394,  395,  396,
  397,  398,  399,   -1,   -1,   -1,   -1,   -1,  405,   -1,
  407,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  424,   -1,   -1,
  427,  428,   -1,   -1,   -1,   -1,   -1,  434,   -1,   -1,
   -1,   -1,  439,   -1,  441,   -1,  443,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  468,   -1,   -1,  471,   -1,  473,   -1,   -1,   -1,
   -1,  478,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  491,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  502,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  519,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  536,
  537,   -1,   -1,   -1,  541,   -1,  278,  279,   -1,  281,
   -1,   -1,   -1,  550,   -1,   -1,   -1,   -1,  290,  291,
   -1,  293,  559,   -1,   -1,  562,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  571,   -1,   -1,   -1,   -1,  576,
  577,  578,   -1,   -1,   -1,   -1,  583,  584,  585,  321,
   -1,   -1,  324,  325,   -1,   -1,   -1,  329,   -1,   -1,
  597,  598,  334,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  343,   -1,  610,   -1,   -1,  348,  614,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  363,   -1,   -1,   -1,   -1,  368,   -1,  370,   -1,
   -1,   -1,   -1,  375,   -1,  377,  378,  379,   -1,  381,
  382,  383,   -1,  385,  386,  387,  388,   -1,  390,  391,
  392,  393,  394,  395,  396,  397,  398,  399,   -1,   -1,
   -1,   -1,   -1,  405,   -1,  407,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  424,   -1,   -1,  427,  428,   -1,   -1,   -1,
   -1,   -1,  434,   -1,   -1,   -1,   -1,  439,   -1,  441,
   -1,  443,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  468,   -1,   -1,  471,
   -1,  473,   -1,   -1,   -1,   -1,  478,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  491,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  502,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  519,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  536,  537,   -1,   -1,   -1,  541,
   -1,  278,  279,   -1,  281,   -1,   -1,   -1,  550,   -1,
   -1,   -1,   -1,  290,  291,   -1,  293,  559,   -1,   -1,
  562,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  571,
   -1,   -1,   -1,   -1,  576,  577,  578,   -1,   -1,   -1,
   -1,  583,  584,  585,  321,   -1,   -1,  324,  325,   -1,
   -1,   -1,  329,   -1,   -1,  597,  598,  334,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  343,   -1,  610,   -1,
   -1,  348,  614,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  363,   -1,   -1,   -1,
   -1,  368,   -1,  370,   -1,   -1,   -1,   -1,  375,   -1,
  377,  378,  379,   -1,  381,  382,  383,   -1,  385,  386,
  387,  388,   -1,  390,  391,  392,  393,  394,  395,  396,
  397,  398,  399,   -1,   -1,   -1,   -1,   -1,  405,   -1,
  407,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  424,   -1,   -1,
  427,  428,   -1,   -1,   -1,   -1,   -1,  434,   -1,   -1,
   -1,   -1,  439,   -1,  441,   -1,  443,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  468,   -1,   -1,  471,   -1,  473,   -1,   -1,   -1,
   -1,  478,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  491,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  502,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  519,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  536,
  537,   -1,   -1,   -1,  541,   -1,  278,  279,   -1,  281,
   -1,   -1,   -1,  550,   -1,   -1,   -1,   -1,  290,  291,
   -1,  293,  559,   -1,   -1,  562,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  571,   -1,   -1,   -1,   -1,  576,
  577,  578,   -1,   -1,   -1,   -1,  583,  584,  585,  321,
   -1,   -1,  324,  325,   -1,   -1,   -1,  329,   -1,   -1,
  597,  598,  334,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  343,   -1,  610,   -1,   -1,  348,  614,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  363,   -1,   -1,   -1,   -1,  368,   -1,  370,   -1,
   -1,   -1,   -1,  375,   -1,  377,  378,  379,   -1,  381,
  382,  383,   -1,  385,  386,  387,  388,   -1,  390,  391,
  392,  393,  394,  395,  396,  397,  398,  399,   -1,   -1,
   -1,   -1,   -1,  405,   -1,  407,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  424,   -1,   -1,  427,  428,   -1,   -1,   -1,
   -1,   -1,  434,   -1,   -1,   -1,   -1,  439,   -1,  441,
   -1,  443,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  468,   -1,   -1,  471,
   -1,  473,   -1,   -1,   -1,   -1,  478,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  491,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  502,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  519,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  536,  537,   -1,   -1,   -1,  541,
   -1,  278,  279,   -1,  281,   -1,   -1,   -1,  550,   -1,
   -1,   -1,   -1,  290,  291,   -1,  293,  559,   -1,   -1,
  562,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  571,
   -1,   -1,   -1,   -1,  576,  577,  578,   -1,   -1,   -1,
   -1,  583,  584,  585,  321,   -1,   -1,  324,  325,   -1,
   -1,   -1,  329,   -1,   -1,  597,  598,  334,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  343,   -1,  610,   -1,
   -1,  348,  614,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  363,   -1,   -1,   -1,
   -1,  368,   -1,  370,   -1,   -1,   -1,   -1,  375,   -1,
  377,  378,  379,   -1,  381,  382,  383,   -1,  385,  386,
  387,  388,   -1,  390,  391,  392,  393,  394,  395,  396,
  397,  398,  399,   -1,   -1,   -1,   -1,   -1,  405,   -1,
  407,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  424,   -1,   -1,
  427,  428,   -1,   -1,   -1,   -1,   -1,  434,   -1,   -1,
   -1,   -1,  439,   -1,  441,   -1,  443,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  468,   -1,   -1,  471,   -1,  473,   -1,   -1,   -1,
   -1,  478,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  491,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  502,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  519,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  536,
  537,   -1,   -1,   -1,  541,   -1,  278,  279,   -1,  281,
   -1,   -1,   -1,  550,   -1,   -1,   -1,   -1,  290,  291,
   -1,  293,  559,   -1,   -1,  562,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  571,   -1,   -1,   -1,   -1,  576,
  577,  578,   -1,   -1,   -1,   -1,  583,  584,  585,  321,
   -1,   -1,  324,  325,   -1,   -1,   -1,  329,   -1,   -1,
  597,  598,  334,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  343,   -1,  610,   -1,   -1,  348,  614,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  363,   -1,   -1,   -1,   -1,  368,   -1,  370,   -1,
   -1,   -1,   -1,  375,   -1,  377,  378,  379,   -1,  381,
  382,  383,   -1,  385,  386,  387,  388,   -1,  390,  391,
  392,  393,  394,  395,  396,  397,  398,  399,   -1,   -1,
   -1,   -1,   -1,  405,   -1,  407,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  424,   -1,   -1,  427,  428,   -1,   -1,   -1,
   -1,   -1,  434,   -1,   -1,   -1,   -1,  439,   -1,  441,
   -1,  443,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  468,   -1,   -1,  471,
   -1,  473,   -1,   -1,   -1,   -1,  478,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  491,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  502,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  519,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  536,  537,   -1,   -1,   -1,  541,
   -1,  278,  279,   -1,  281,   -1,   -1,   -1,  550,   -1,
   -1,   -1,   -1,  290,  291,   -1,  293,  559,   -1,   -1,
  562,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  571,
   -1,   -1,   -1,   -1,  576,  577,  578,   -1,   -1,   -1,
   -1,  583,  584,  585,  321,   -1,   -1,  324,  325,   -1,
   -1,   -1,  329,   -1,   -1,  597,  598,  334,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  343,   -1,  610,   -1,
   -1,  348,  614,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  363,   -1,   -1,   -1,
   -1,  368,   -1,  370,   -1,   -1,   -1,   -1,  375,   -1,
  377,  378,  379,   -1,  381,  382,  383,   -1,  385,  386,
  387,  388,   -1,  390,  391,  392,  393,  394,  395,  396,
  397,  398,  399,   -1,   -1,   -1,   -1,   -1,  405,   -1,
  407,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  424,   -1,   -1,
  427,  428,   -1,   -1,   -1,   -1,   -1,  434,   -1,   -1,
   -1,   -1,  439,   -1,  441,   -1,  443,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  468,   -1,   -1,  471,   -1,  473,   -1,   -1,   -1,
   -1,  478,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  491,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  502,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  519,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  536,
  537,   -1,   -1,   -1,  541,   -1,  278,  279,   -1,  281,
   -1,   -1,   -1,  550,   -1,   -1,   -1,   -1,  290,  291,
   -1,  293,  559,   -1,   -1,  562,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  571,   -1,   -1,   -1,   -1,  576,
  577,  578,   -1,   -1,   -1,   -1,  583,  584,  585,  321,
   -1,   -1,  324,  325,   -1,   -1,   -1,  329,   -1,   -1,
  597,  598,  334,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  343,   -1,  610,   -1,   -1,  348,  614,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  363,   -1,   -1,   -1,   -1,  368,   -1,  370,   -1,
   -1,   -1,   -1,  375,   -1,  377,  378,  379,   -1,  381,
  382,  383,   -1,  385,  386,  387,  388,   -1,  390,  391,
  392,  393,  394,  395,  396,  397,  398,  399,   -1,   -1,
   -1,   -1,   -1,  405,   -1,  407,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  424,   -1,   -1,  427,  428,   -1,   -1,   -1,
   -1,   -1,  434,   -1,   -1,   -1,   -1,  439,   -1,  441,
   -1,  443,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  468,   -1,   -1,  471,
   -1,  473,   -1,   -1,   -1,   -1,  478,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  491,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  502,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  519,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  536,  537,   -1,   -1,   -1,  541,
   -1,  278,  279,   -1,  281,   -1,   -1,   -1,  550,   -1,
   -1,   -1,   -1,  290,  291,   -1,  293,  559,   -1,   -1,
  562,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  571,
   -1,   -1,   -1,   -1,  576,  577,  578,   -1,   -1,   -1,
   -1,  583,  584,  585,  321,   -1,   -1,  324,  325,   -1,
   -1,   -1,  329,   -1,   -1,  597,  598,  334,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  343,   -1,  610,   -1,
   -1,  348,  614,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  363,   -1,   -1,   -1,
   -1,  368,   -1,  370,   -1,   -1,   -1,   -1,  375,   -1,
  377,  378,  379,   -1,  381,  382,  383,   -1,  385,  386,
  387,  388,   -1,  390,  391,  392,  393,  394,  395,  396,
  397,  398,  399,   -1,   -1,   -1,   -1,   -1,  405,   -1,
  407,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  424,   -1,   -1,
  427,  428,   -1,   -1,   -1,   -1,   -1,  434,   -1,   -1,
   -1,   -1,  439,   -1,  441,   -1,  443,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  468,   -1,   -1,  471,   -1,  473,   -1,   -1,   -1,
   -1,  478,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  491,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  502,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  519,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  536,
  537,   -1,   -1,   -1,  541,   -1,  278,  279,   -1,  281,
   -1,   -1,   -1,  550,   -1,   -1,   -1,   -1,  290,  291,
   -1,  293,  559,   -1,   -1,  562,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  571,   -1,   -1,   -1,   -1,  576,
  577,  578,   -1,   -1,   -1,   -1,  583,  584,  585,  321,
   -1,   -1,  324,  325,   -1,   -1,   -1,  329,   -1,   -1,
  597,  598,  334,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  343,   -1,  610,   -1,   -1,  348,  614,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  363,   -1,   -1,   -1,   -1,  368,   -1,  370,   -1,
   -1,   -1,   -1,  375,   -1,  377,  378,  379,   -1,  381,
  382,  383,   -1,  385,  386,  387,  388,   -1,  390,  391,
  392,  393,  394,  395,  396,  397,  398,  399,   -1,   -1,
   -1,   -1,   -1,  405,   -1,  407,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  424,   -1,   -1,  427,  428,   -1,   -1,   -1,
   -1,   -1,  434,   -1,   -1,   -1,   -1,  439,   -1,  441,
   -1,  443,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  468,   -1,   -1,  471,
   -1,  473,   -1,   -1,   -1,   -1,  478,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  491,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  502,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  519,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  536,  537,   -1,   -1,   -1,  541,
   -1,  278,  279,   -1,  281,   -1,   -1,   -1,  550,   -1,
   -1,   -1,   -1,  290,  291,   -1,  293,  559,   -1,   -1,
  562,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  571,
   -1,   -1,   -1,   -1,  576,  577,  578,   -1,   -1,   -1,
   -1,  583,  584,  585,  321,   -1,   -1,  324,  325,   -1,
   -1,   -1,  329,   -1,   -1,  597,  598,  334,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  343,   -1,  610,   -1,
   -1,  348,  614,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  363,   -1,   -1,   -1,
   -1,  368,   -1,  370,   -1,   -1,   -1,   -1,  375,   -1,
  377,  378,  379,   -1,  381,  382,  383,   -1,  385,  386,
  387,  388,   -1,  390,  391,  392,  393,  394,  395,  396,
  397,  398,  399,   -1,   -1,   -1,   -1,   -1,  405,   -1,
  407,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  424,   -1,   -1,
  427,  428,   -1,   -1,   -1,   -1,   -1,  434,   -1,   -1,
   -1,   -1,  439,   -1,  441,   -1,  443,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  468,   -1,   -1,  471,   -1,  473,   -1,   -1,   -1,
   -1,  478,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  491,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  502,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  519,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  536,
  537,   -1,   -1,   -1,  541,   -1,  278,  279,   -1,  281,
   -1,   -1,   -1,  550,   -1,   -1,   -1,   -1,  290,  291,
   -1,  293,  559,   -1,   -1,  562,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  571,   -1,   -1,   -1,   -1,  576,
  577,  578,   -1,   -1,   -1,   -1,  583,  584,  585,  321,
   -1,   -1,  324,  325,   -1,   -1,   -1,  329,   -1,   -1,
  597,  598,  334,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  343,   -1,  610,   -1,   -1,  348,  614,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  363,   -1,   -1,   -1,   -1,  368,   -1,  370,   -1,
   -1,   -1,   -1,  375,   -1,  377,  378,  379,   -1,  381,
  382,  383,   -1,  385,  386,  387,  388,   -1,  390,  391,
  392,  393,  394,  395,  396,  397,  398,  399,   -1,   -1,
   -1,   -1,   -1,  405,   -1,  407,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  424,   -1,   -1,  427,  428,   -1,   -1,   -1,
   -1,   -1,  434,   -1,   -1,   -1,   -1,  439,   -1,  441,
   -1,  443,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  468,   -1,   -1,  471,
   -1,  473,   -1,   -1,   -1,   -1,  478,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  491,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  502,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  519,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  536,  537,   -1,   -1,   -1,  541,
   -1,  278,  279,   -1,  281,   -1,   -1,   -1,  550,   -1,
   -1,   -1,   -1,  290,  291,   -1,  293,  559,   -1,   -1,
  562,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  571,
   -1,   -1,   -1,   -1,  576,  577,  578,   -1,   -1,   -1,
   -1,  583,  584,  585,  321,   -1,   -1,  324,  325,   -1,
   -1,   -1,  329,   -1,   -1,  597,  598,  334,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  343,   -1,  610,   -1,
   -1,  348,  614,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  363,   -1,   -1,   -1,
   -1,  368,   -1,  370,   -1,   -1,   -1,   -1,  375,   -1,
  377,  378,  379,   -1,  381,  382,  383,   -1,  385,  386,
  387,  388,   -1,  390,  391,  392,  393,  394,  395,  396,
  397,  398,  399,   -1,   -1,   -1,   -1,   -1,  405,   -1,
  407,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  424,   -1,   -1,
  427,  428,   -1,   -1,   -1,   -1,   -1,  434,   -1,   -1,
   -1,   -1,  439,   -1,  441,   -1,  443,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  468,   -1,   -1,  471,   -1,  473,   -1,   -1,   -1,
   -1,  478,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  491,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  502,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  519,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  536,
  537,   -1,   -1,   -1,  541,   -1,  278,  279,   -1,  281,
   -1,   -1,   -1,  550,   -1,   -1,   -1,   -1,  290,  291,
   -1,  293,  559,   -1,   -1,  562,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  571,   -1,   -1,   -1,   -1,  576,
  577,  578,   -1,   -1,   -1,   -1,  583,  584,  585,  321,
   -1,   -1,  324,  325,   -1,   -1,   -1,  329,   -1,   -1,
  597,  598,  334,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  343,   -1,  610,   -1,   -1,  348,  614,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  363,   -1,   -1,   -1,   -1,  368,   -1,  370,   -1,
   -1,   -1,   -1,  375,   -1,  377,  378,  379,   -1,  381,
  382,  383,   -1,  385,  386,  387,  388,   -1,  390,  391,
  392,  393,  394,  395,  396,  397,  398,  399,   -1,   -1,
   -1,   -1,   -1,  405,   -1,  407,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  424,   -1,   -1,  427,  428,   -1,   -1,   -1,
   -1,   -1,  434,   -1,   -1,   -1,   -1,  439,   -1,  441,
   -1,  443,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  468,   -1,   -1,  471,
   -1,  473,   -1,   -1,   -1,   -1,  478,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  491,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  502,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  519,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  536,  537,   -1,   -1,   -1,  541,
   -1,  278,  279,   -1,  281,   -1,   -1,   -1,  550,   -1,
   -1,   -1,   -1,  290,  291,   -1,  293,  559,   -1,   -1,
  562,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  571,
   -1,   -1,   -1,   -1,  576,  577,  578,   -1,   -1,   -1,
   -1,  583,  584,  585,  321,   -1,   -1,  324,  325,   -1,
   -1,   -1,  329,   -1,   -1,  597,  598,  334,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  343,   -1,  610,   -1,
   -1,  348,  614,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  363,   -1,   -1,   -1,
   -1,  368,   -1,  370,   -1,   -1,   -1,   -1,  375,   -1,
  377,  378,  379,   -1,  381,  382,  383,   -1,  385,  386,
  387,  388,   -1,  390,  391,  392,  393,  394,  395,  396,
  397,  398,  399,   -1,   -1,   -1,   -1,   -1,  405,   -1,
  407,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  424,   -1,   -1,
  427,  428,   -1,   -1,   -1,   -1,   -1,  434,   -1,   -1,
   -1,   -1,  439,   -1,  441,   -1,  443,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  468,   -1,   -1,  471,   -1,  473,   -1,   -1,   -1,
   -1,  478,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  491,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  502,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  519,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  536,
  537,   -1,   -1,   -1,  541,   -1,  278,  279,   -1,  281,
   -1,   -1,   -1,  550,   -1,   -1,   -1,   -1,   -1,  291,
   -1,  293,  559,   -1,   -1,  562,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  571,   -1,   -1,   -1,   -1,  576,
  577,  578,   -1,   -1,   -1,   -1,  583,  584,  585,  321,
   -1,   -1,  324,  325,   -1,   -1,   -1,  329,   -1,   -1,
  597,  598,  334,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  343,   -1,  610,   -1,   -1,  348,  614,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  363,   -1,   -1,   -1,   -1,  368,   -1,  370,   -1,
   -1,   -1,   -1,  375,   -1,  377,  378,  379,   -1,  381,
  382,  383,   -1,  385,  386,  387,  388,   -1,  390,  391,
  392,  393,  394,  395,  396,  397,  398,  399,   -1,   -1,
   -1,   -1,   -1,  405,   -1,  407,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  424,   -1,   -1,  427,  428,   -1,   -1,   -1,
   -1,   -1,  434,   -1,   -1,   -1,   -1,  439,   -1,  441,
   -1,  443,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  468,   -1,   -1,  471,
   -1,  473,   -1,   -1,   -1,   -1,  478,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  491,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  502,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  519,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  536,  537,   -1,   -1,   -1,  541,
   -1,  278,  279,   -1,  281,   -1,   -1,   -1,  550,   -1,
   -1,   -1,   -1,  290,  291,   -1,  293,  559,   -1,  561,
  562,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  571,
   -1,   -1,   -1,   -1,  576,  577,  578,   -1,   -1,   -1,
   -1,  583,  584,  585,  321,   -1,   -1,  324,  325,   -1,
   -1,   -1,  329,   -1,   -1,  597,  598,  334,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  343,   -1,  610,   -1,
   -1,  348,  614,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  363,   -1,   -1,   -1,
   -1,  368,   -1,  370,   -1,   -1,   -1,   -1,  375,   -1,
  377,  378,  379,   -1,  381,  382,  383,   -1,  385,  386,
  387,  388,   -1,  390,  391,  392,  393,  394,  395,  396,
  397,  398,  399,   -1,   -1,   -1,   -1,   -1,  405,   -1,
  407,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  424,   -1,   -1,
  427,  428,   -1,   -1,   -1,   -1,   -1,  434,   -1,   -1,
   -1,   -1,  439,   -1,  441,   -1,  443,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  468,   -1,   -1,  471,   -1,  473,   -1,   -1,   -1,
   -1,  478,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  491,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  502,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  519,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  536,
  537,   -1,   -1,   -1,  541,   -1,  278,  279,   -1,  281,
   -1,   -1,   -1,  550,   -1,   -1,   -1,   -1,  290,  291,
   -1,  293,  559,   -1,   -1,  562,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  571,   -1,   -1,   -1,   -1,  576,
  577,  578,   -1,   -1,   -1,   -1,  583,  584,  585,  321,
   -1,   -1,  324,  325,   -1,   -1,   -1,  329,   -1,   -1,
  597,  598,  334,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  343,   -1,  610,   -1,   -1,  348,  614,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  363,   -1,   -1,   -1,   -1,  368,   -1,  370,   -1,
   -1,   -1,   -1,  375,   -1,  377,  378,  379,   -1,  381,
  382,  383,   -1,  385,  386,  387,  388,   -1,  390,  391,
  392,  393,  394,  395,  396,  397,  398,  399,   -1,   -1,
   -1,   -1,   -1,  405,   -1,  407,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  424,   -1,   -1,  427,  428,   -1,   -1,   -1,
   -1,   -1,  434,   -1,   -1,   -1,   -1,  439,   -1,  441,
   -1,  443,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  468,   -1,   -1,  471,
   -1,  473,   -1,   -1,   -1,   -1,  478,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  491,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  502,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  519,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  536,  537,   -1,   -1,   -1,  541,
   -1,  278,  279,   -1,  281,   -1,   -1,   -1,  550,   -1,
   -1,   -1,   -1,  290,  291,   -1,  293,  559,   -1,   -1,
  562,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  571,
   -1,   -1,   -1,   -1,  576,  577,  578,   -1,   -1,   -1,
   -1,  583,  584,  585,  321,   -1,   -1,  324,  325,   -1,
   -1,   -1,  329,   -1,   -1,  597,  598,  334,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  343,   -1,  610,   -1,
   -1,  348,  614,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  363,   -1,   -1,   -1,
   -1,  368,   -1,  370,   -1,   -1,   -1,   -1,  375,   -1,
  377,  378,  379,   -1,  381,  382,  383,   -1,  385,  386,
  387,  388,   -1,  390,  391,  392,  393,  394,  395,  396,
  397,  398,  399,   -1,   -1,   -1,   -1,   -1,  405,   -1,
  407,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  424,   -1,   -1,
  427,  428,   -1,   -1,   -1,   -1,   -1,  434,   -1,   -1,
   -1,   -1,  439,   -1,  441,   -1,  443,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  468,   -1,   -1,  471,   -1,  473,   -1,   -1,   -1,
   -1,  478,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  491,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  502,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  519,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  536,
  537,   -1,   -1,   -1,  541,   -1,  278,  279,   -1,  281,
   -1,   -1,   -1,  550,   -1,   -1,   -1,   -1,  290,  291,
   -1,  293,  559,   -1,   -1,  562,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  571,   -1,   -1,   -1,   -1,  576,
  577,  578,   -1,   -1,   -1,   -1,  583,  584,  585,  321,
   -1,   -1,  324,  325,   -1,   -1,   -1,  329,   -1,   -1,
  597,  598,  334,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  343,   -1,  610,   -1,   -1,  348,  614,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  363,   -1,   -1,   -1,   -1,  368,   -1,  370,   -1,
   -1,   -1,   -1,  375,   -1,  377,  378,  379,   -1,  381,
  382,  383,   -1,  385,  386,  387,  388,   -1,  390,  391,
  392,  393,  394,  395,  396,  397,  398,  399,   -1,   -1,
   -1,   -1,   -1,  405,   -1,  407,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  424,   -1,   -1,  427,  428,   -1,   -1,   -1,
   -1,   -1,  434,   -1,   -1,   -1,   -1,  439,   -1,  441,
   -1,  443,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  468,   -1,   -1,  471,
   -1,  473,   -1,   -1,   -1,   -1,  478,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  491,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  502,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  519,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  536,  537,   -1,   -1,   -1,  541,
   -1,  278,  279,   -1,  281,   -1,   -1,   -1,  550,   -1,
   -1,   -1,   -1,  290,  291,   -1,  293,  559,   -1,   -1,
  562,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  571,
   -1,   -1,   -1,   -1,  576,  577,  578,   -1,   -1,   -1,
   -1,  583,  584,  585,  321,   -1,   -1,  324,  325,   -1,
   -1,   -1,  329,   -1,   -1,  597,  598,  334,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  343,   -1,  610,   -1,
   -1,  348,  614,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  363,   -1,   -1,   -1,
   -1,  368,   -1,  370,   -1,   -1,   -1,   -1,  375,   -1,
  377,  378,  379,   -1,  381,  382,  383,   -1,  385,  386,
  387,  388,   -1,  390,  391,  392,  393,  394,  395,  396,
  397,  398,  399,   -1,   -1,   -1,   -1,   -1,  405,   -1,
  407,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  424,   -1,   -1,
  427,  428,   -1,   -1,   -1,   -1,   -1,  434,   -1,   -1,
   -1,   -1,  439,   -1,  441,   -1,  443,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  468,   -1,   -1,  471,   -1,  473,   -1,   -1,   -1,
   -1,  478,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  491,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  502,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  519,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  536,
  537,   -1,   -1,   -1,  541,   -1,  278,  279,   -1,  281,
   -1,   -1,   -1,  550,   -1,   -1,   -1,   -1,  290,  291,
   -1,  293,  559,   -1,   -1,  562,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  571,   -1,   -1,   -1,   -1,  576,
  577,  578,   -1,   -1,   -1,   -1,  583,  584,  585,  321,
   -1,   -1,  324,  325,   -1,   -1,   -1,  329,   -1,   -1,
  597,  598,  334,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  343,   -1,  610,   -1,   -1,  348,  614,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  363,   -1,   -1,   -1,   -1,  368,   -1,  370,   -1,
   -1,   -1,   -1,  375,   -1,  377,  378,  379,   -1,  381,
  382,  383,   -1,  385,  386,  387,  388,   -1,  390,  391,
  392,  393,  394,  395,  396,  397,  398,  399,   -1,   -1,
   -1,   -1,   -1,  405,   -1,  407,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  424,   -1,   -1,  427,  428,   -1,   -1,   -1,
   -1,   -1,  434,   -1,   -1,   -1,   -1,  439,   -1,  441,
   -1,  443,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  468,   -1,   -1,  471,
   -1,  473,   -1,   -1,   -1,   -1,  478,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  491,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  502,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  519,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  536,  537,   -1,   -1,   -1,  541,
   -1,  278,  279,   -1,  281,   -1,   -1,   -1,  550,   -1,
   -1,   -1,   -1,  290,  291,   -1,  293,  559,   -1,   -1,
  562,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  571,
   -1,   -1,   -1,   -1,  576,  577,  578,   -1,   -1,   -1,
   -1,  583,  584,  585,  321,   -1,   -1,  324,  325,   -1,
   -1,   -1,  329,   -1,   -1,  597,  598,  334,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  343,   -1,  610,   -1,
   -1,  348,  614,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  363,   -1,   -1,   -1,
   -1,  368,   -1,  370,   -1,   -1,   -1,   -1,  375,   -1,
  377,  378,  379,   -1,  381,  382,  383,   -1,  385,  386,
  387,  388,   -1,  390,  391,  392,  393,  394,  395,  396,
  397,  398,  399,   -1,   -1,   -1,   -1,   -1,  405,   -1,
  407,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  424,   -1,   -1,
  427,  428,   -1,   -1,   -1,   -1,   -1,  434,   -1,   -1,
   -1,   -1,  439,   -1,  441,   -1,  443,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  468,   -1,   -1,  471,   -1,  473,   -1,   -1,   -1,
   -1,  478,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  491,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  502,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  519,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  536,
  537,   -1,   -1,   -1,  541,   -1,  278,  279,   -1,  281,
   -1,   -1,   -1,  550,   -1,   -1,   -1,   -1,  290,  291,
   -1,  293,  559,   -1,   -1,  562,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  571,   -1,   -1,   -1,   -1,  576,
  577,  578,   -1,   -1,   -1,   -1,  583,  584,  585,  321,
   -1,   -1,  324,  325,   -1,   -1,   -1,  329,   -1,   -1,
  597,  598,  334,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  343,   -1,  610,   -1,   -1,  348,  614,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  363,   -1,   -1,   -1,   -1,  368,   -1,  370,   -1,
   -1,   -1,   -1,  375,   -1,  377,  378,  379,   -1,  381,
  382,  383,   -1,  385,  386,  387,  388,   -1,  390,  391,
  392,  393,  394,  395,  396,  397,  398,  399,   -1,   -1,
   -1,   -1,   -1,  405,   -1,  407,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  424,   -1,   -1,  427,  428,   -1,   -1,   -1,
   -1,   -1,  434,   -1,   -1,   -1,   -1,  439,   -1,  441,
   -1,  443,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  468,   -1,   -1,  471,
   -1,  473,   -1,   -1,   -1,   -1,  478,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  491,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  502,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  519,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  536,  537,   -1,   -1,   -1,  541,
   -1,  278,  279,   -1,  281,   -1,   -1,   -1,  550,   -1,
   -1,   -1,   -1,  290,  291,   -1,  293,  559,   -1,   -1,
  562,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  571,
   -1,   -1,   -1,   -1,  576,  577,  578,   -1,   -1,   -1,
   -1,  583,  584,  585,  321,   -1,   -1,  324,  325,   -1,
   -1,   -1,  329,   -1,   -1,  597,  598,  334,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  343,   -1,  610,   -1,
   -1,  348,  614,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  363,   -1,   -1,   -1,
   -1,  368,   -1,  370,   -1,   -1,   -1,   -1,  375,   -1,
  377,  378,  379,   -1,  381,  382,  383,   -1,  385,  386,
  387,  388,   -1,  390,  391,  392,  393,  394,  395,  396,
  397,  398,  399,   -1,   -1,   -1,   -1,   -1,  405,   -1,
  407,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  424,   -1,   -1,
  427,  428,   -1,   -1,   -1,   -1,   -1,  434,   -1,   -1,
   -1,   -1,  439,   -1,  441,   -1,  443,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  468,   -1,   -1,  471,   -1,  473,   -1,   -1,   -1,
   -1,  478,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  491,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  502,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  519,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  536,
  537,   -1,   -1,   -1,  541,   -1,  278,  279,   -1,  281,
   -1,   -1,   -1,  550,   -1,   -1,   -1,   -1,  290,  291,
   -1,  293,  559,   -1,   -1,  562,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  571,   -1,   -1,   -1,   -1,  576,
  577,  578,   -1,   -1,   -1,   -1,  583,  584,  585,  321,
   -1,   -1,  324,  325,   -1,   -1,   -1,  329,   -1,   -1,
  597,  598,  334,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  343,   -1,  610,   -1,   -1,  348,  614,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  363,   -1,   -1,   -1,   -1,  368,   -1,  370,   -1,
   -1,   -1,   -1,  375,   -1,  377,  378,  379,   -1,  381,
  382,  383,   -1,  385,  386,  387,  388,   -1,  390,  391,
  392,  393,  394,  395,  396,  397,  398,  399,   -1,   -1,
   -1,   -1,   -1,  405,   -1,  407,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  424,   -1,   -1,  427,  428,   -1,   -1,   -1,
   -1,   -1,  434,   -1,   -1,   -1,   -1,  439,   -1,  441,
   -1,  443,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  468,   -1,   -1,  471,
   -1,  473,   -1,   -1,   -1,   -1,  478,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  491,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  502,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  519,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  536,  537,   -1,   -1,   -1,  541,
   -1,  278,  279,   -1,  281,   -1,   -1,   -1,  550,   -1,
   -1,   -1,   -1,  290,  291,   -1,  293,  559,   -1,   -1,
  562,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  571,
   -1,   -1,   -1,   -1,  576,  577,  578,   -1,   -1,   -1,
   -1,  583,  584,  585,  321,   -1,   -1,  324,  325,   -1,
   -1,   -1,  329,   -1,   -1,  597,  598,  334,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  343,   -1,  610,   -1,
   -1,  348,  614,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  363,   -1,   -1,   -1,
   -1,  368,   -1,  370,   -1,   -1,   -1,   -1,  375,   -1,
  377,  378,  379,   -1,  381,  382,  383,   -1,  385,  386,
  387,  388,   -1,  390,  391,  392,  393,  394,  395,  396,
  397,  398,  399,   -1,   -1,   -1,   -1,   -1,  405,   -1,
  407,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  424,   -1,   -1,
  427,  428,   -1,   -1,   -1,   -1,   -1,  434,   -1,   -1,
   -1,   -1,  439,   -1,  441,   -1,  443,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  468,   -1,   -1,  471,   -1,  473,   -1,   -1,   -1,
   -1,  478,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  491,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  502,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  519,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  536,
  537,   -1,   -1,   -1,  541,   -1,  278,  279,   -1,  281,
   -1,   -1,   -1,  550,   -1,   -1,   -1,   -1,  290,  291,
   -1,  293,  559,   -1,   -1,  562,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  571,   -1,   -1,   -1,   -1,  576,
  577,  578,   -1,   -1,   -1,   -1,  583,  584,  585,  321,
   -1,   -1,  324,  325,   -1,   -1,   -1,  329,   -1,   -1,
  597,  598,  334,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  343,   -1,  610,   -1,   -1,  348,  614,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  363,   -1,   -1,   -1,   -1,  368,   -1,  370,   -1,
   -1,   -1,   -1,  375,   -1,  377,  378,  379,   -1,  381,
  382,  383,   -1,  385,  386,  387,  388,   -1,  390,  391,
  392,  393,  394,  395,  396,  397,  398,  399,   -1,   -1,
   -1,   -1,   -1,  405,   -1,  407,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  424,   -1,   -1,  427,  428,   -1,   -1,   -1,
   -1,   -1,  434,   -1,   -1,   -1,   -1,  439,   -1,  441,
   -1,  443,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  468,   -1,   -1,  471,
   -1,  473,   -1,   -1,   -1,   -1,  478,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  491,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  502,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  278,  279,  519,  281,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  290,  291,   -1,
  293,   -1,   -1,   -1,  536,  537,   -1,   -1,   -1,  541,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  550,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  559,  321,   -1,
  562,  324,  325,   -1,   -1,   -1,  329,   -1,   -1,  571,
   -1,  334,   -1,   -1,  576,  577,  578,   -1,   -1,   -1,
  343,  583,  584,  585,   -1,  348,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  597,  598,   -1,   -1,   -1,
  363,   -1,   -1,   -1,   -1,  368,   -1,  370,  610,   -1,
   -1,   -1,  614,   -1,  377,  378,  379,   -1,  381,  382,
  383,   -1,  385,  386,  387,  388,   -1,  390,  391,  392,
  393,  394,  395,  396,  397,  398,  399,   -1,   -1,   -1,
   -1,   -1,  405,   -1,  407,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  424,   -1,   -1,  427,  428,   -1,   -1,   -1,   -1,
   -1,  434,   -1,   -1,   -1,   -1,  439,   -1,  441,   -1,
  443,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  468,   -1,   -1,  471,   -1,
  473,   -1,   -1,   -1,   -1,  478,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  491,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  502,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  519,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  536,  537,   -1,   -1,   -1,  541,   -1,
  278,  279,   -1,  281,   -1,   -1,   -1,  550,   -1,   -1,
   -1,   -1,  290,  291,   -1,  293,  559,   -1,   -1,  562,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  571,   -1,
   -1,   -1,   -1,  576,  577,  578,   -1,   -1,   -1,   -1,
  583,  584,  585,  321,   -1,   -1,  324,  325,   -1,   -1,
   -1,  329,   -1,   -1,  597,  598,  334,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  343,   -1,  610,   -1,   -1,
  348,  614,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  363,   -1,   -1,   -1,   -1,
  368,   -1,  370,   -1,   -1,   -1,   -1,  375,   -1,  377,
  378,  379,   -1,  381,  382,  383,   -1,  385,  386,  387,
  388,   -1,  390,   -1,  392,  393,  394,  395,  396,  397,
  398,  399,   -1,   -1,   -1,   -1,   -1,  405,   -1,  407,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  424,   -1,   -1,  427,
  428,   -1,   -1,   -1,   -1,   -1,  434,   -1,   -1,   -1,
   -1,  439,   -1,  441,   -1,  443,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  468,   -1,   -1,  471,   -1,  473,   -1,   -1,   -1,   -1,
  478,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  491,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  502,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  519,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  536,  537,
   -1,   -1,   -1,  541,   -1,  278,  279,   -1,  281,   -1,
   -1,   -1,  550,   -1,   -1,   -1,   -1,  290,  291,   -1,
  293,  559,   -1,   -1,  562,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  571,   -1,   -1,   -1,   -1,  576,  577,
  578,   -1,   -1,   -1,   -1,  583,  584,  585,  321,   -1,
   -1,  324,  325,   -1,   -1,   -1,  329,   -1,   -1,  597,
  598,  334,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  343,   -1,  610,   -1,   -1,  348,  614,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  363,   -1,   -1,   -1,   -1,  368,   -1,  370,   -1,   -1,
   -1,   -1,  375,   -1,  377,   -1,  379,   -1,  381,  382,
  383,   -1,  385,  386,  387,  388,   -1,  390,  391,  392,
  393,  394,  395,  396,  397,  398,  399,   -1,   -1,   -1,
   -1,   -1,  405,   -1,  407,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  424,   -1,   -1,  427,  428,   -1,   -1,   -1,   -1,
   -1,  434,   -1,   -1,   -1,   -1,  439,   -1,  441,   -1,
  443,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  468,   -1,   -1,  471,   -1,
  473,   -1,   -1,   -1,   -1,  478,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  491,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  502,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  519,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  536,  537,   -1,   -1,   -1,  541,   -1,
  278,  279,   -1,  281,   -1,   -1,   -1,  550,   -1,   -1,
   -1,   -1,  290,  291,   -1,  293,  559,   -1,   -1,  562,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  571,   -1,
   -1,   -1,   -1,  576,  577,  578,   -1,   -1,   -1,   -1,
  583,  584,  585,  321,   -1,   -1,  324,  325,   -1,   -1,
   -1,  329,   -1,   -1,  597,  598,  334,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  343,   -1,  610,   -1,   -1,
  348,  614,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  363,   -1,   -1,   -1,   -1,
  368,   -1,  370,   -1,   -1,   -1,   -1,  375,   -1,  377,
  378,  379,   -1,  381,   -1,  383,   -1,  385,  386,  387,
  388,   -1,  390,  391,  392,  393,  394,  395,  396,  397,
  398,  399,   -1,   -1,   -1,   -1,   -1,  405,   -1,  407,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  424,   -1,   -1,  427,
  428,   -1,   -1,   -1,   -1,   -1,  434,   -1,   -1,   -1,
   -1,  439,   -1,  441,   -1,  443,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  468,   -1,   -1,  471,   -1,  473,   -1,   -1,   -1,   -1,
  478,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  491,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  502,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  519,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  536,  537,
   -1,   -1,   -1,  541,   -1,  278,  279,   -1,  281,   -1,
   -1,   -1,  550,   -1,   -1,   -1,   -1,  290,  291,   -1,
  293,  559,   -1,   -1,  562,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  571,   -1,   -1,   -1,   -1,  576,  577,
  578,   -1,   -1,   -1,   -1,  583,  584,  585,  321,   -1,
   -1,  324,  325,   -1,   -1,   -1,  329,   -1,   -1,  597,
  598,  334,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  343,   -1,  610,   -1,   -1,  348,  614,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  363,   -1,   -1,   -1,   -1,  368,   -1,  370,   -1,   -1,
   -1,   -1,  375,   -1,  377,  378,  379,   -1,  381,  382,
  383,   -1,   -1,  386,  387,  388,   -1,  390,  391,  392,
  393,  394,  395,  396,  397,  398,  399,   -1,   -1,   -1,
   -1,   -1,  405,   -1,  407,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  424,   -1,   -1,  427,  428,   -1,   -1,   -1,   -1,
   -1,  434,   -1,   -1,   -1,   -1,  439,   -1,  441,   -1,
  443,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  468,   -1,   -1,  471,   -1,
  473,   -1,   -1,   -1,   -1,  478,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  491,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  502,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  519,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  536,  537,   -1,   -1,   -1,  541,   -1,
  278,  279,   -1,  281,   -1,   -1,   -1,  550,   -1,   -1,
   -1,   -1,  290,  291,   -1,  293,  559,   -1,   -1,  562,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  571,   -1,
   -1,   -1,   -1,  576,  577,  578,   -1,   -1,   -1,   -1,
  583,  584,  585,  321,   -1,   -1,  324,  325,   -1,   -1,
   -1,  329,   -1,   -1,  597,  598,  334,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  343,   -1,  610,   -1,   -1,
  348,  614,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  363,   -1,   -1,   -1,   -1,
  368,   -1,  370,   -1,   -1,   -1,   -1,  375,   -1,  377,
  378,  379,   -1,  381,  382,  383,   -1,  385,  386,  387,
   -1,   -1,  390,  391,  392,  393,  394,  395,  396,  397,
  398,  399,   -1,   -1,   -1,   -1,   -1,  405,   -1,  407,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  424,   -1,   -1,  427,
  428,   -1,   -1,   -1,   -1,   -1,  434,   -1,   -1,   -1,
   -1,  439,   -1,  441,   -1,  443,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  468,   -1,   -1,  471,   -1,  473,   -1,   -1,   -1,   -1,
  478,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  491,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  502,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  519,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  536,  537,
   -1,   -1,   -1,  541,   -1,  278,  279,   -1,  281,   -1,
   -1,   -1,  550,   -1,   -1,   -1,   -1,  290,  291,   -1,
  293,  559,   -1,   -1,  562,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  571,   -1,   -1,   -1,   -1,  576,  577,
  578,   -1,   -1,   -1,   -1,  583,  584,  585,  321,   -1,
   -1,  324,  325,   -1,   -1,   -1,  329,   -1,   -1,  597,
  598,  334,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  343,   -1,  610,   -1,   -1,  348,  614,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  363,   -1,   -1,   -1,   -1,  368,   -1,  370,   -1,   -1,
   -1,   -1,  375,   -1,  377,  378,  379,   -1,  381,  382,
  383,   -1,  385,  386,  387,  388,   -1,  390,  391,   -1,
  393,  394,  395,  396,  397,  398,  399,   -1,   -1,   -1,
   -1,   -1,  405,   -1,  407,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  424,   -1,   -1,  427,  428,   -1,   -1,   -1,   -1,
   -1,  434,   -1,   -1,   -1,   -1,  439,   -1,  441,   -1,
  443,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  468,   -1,   -1,  471,   -1,
  473,   -1,   -1,   -1,   -1,  478,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  491,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  502,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  519,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  536,  537,   -1,   -1,   -1,  541,   -1,
  278,  279,   -1,  281,   -1,   -1,   -1,  550,   -1,   -1,
   -1,   -1,  290,  291,   -1,  293,  559,   -1,   -1,  562,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  571,   -1,
   -1,   -1,   -1,  576,  577,  578,   -1,   -1,   -1,   -1,
  583,  584,  585,  321,   -1,   -1,  324,  325,   -1,   -1,
   -1,  329,   -1,   -1,  597,  598,  334,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  343,   -1,  610,   -1,   -1,
  348,  614,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  363,   -1,   -1,   -1,   -1,
  368,   -1,  370,   -1,   -1,   -1,   -1,  375,   -1,  377,
  378,  379,   -1,  381,  382,  383,   -1,  385,  386,  387,
  388,   -1,  390,  391,  392,  393,   -1,  395,  396,  397,
  398,  399,   -1,   -1,   -1,   -1,   -1,  405,   -1,  407,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  424,   -1,   -1,  427,
  428,   -1,   -1,   -1,   -1,   -1,  434,   -1,   -1,   -1,
   -1,  439,   -1,  441,   -1,  443,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  468,   -1,   -1,  471,   -1,  473,   -1,   -1,   -1,   -1,
  478,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  491,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  502,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  519,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  536,  537,
   -1,   -1,   -1,  541,   -1,  278,  279,   -1,  281,   -1,
   -1,   -1,  550,   -1,   -1,   -1,   -1,  290,  291,   -1,
  293,  559,   -1,   -1,  562,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  571,   -1,   -1,   -1,   -1,  576,  577,
  578,   -1,   -1,   -1,   -1,  583,  584,  585,  321,   -1,
   -1,  324,  325,   -1,   -1,   -1,  329,   -1,   -1,  597,
  598,  334,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  343,   -1,  610,   -1,   -1,  348,  614,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  363,   -1,   -1,   -1,   -1,  368,   -1,  370,   -1,   -1,
   -1,   -1,  375,   -1,  377,  378,  379,   -1,  381,  382,
  383,   -1,  385,  386,  387,  388,   -1,  390,  391,  392,
  393,  394,  395,  396,   -1,  398,  399,   -1,   -1,   -1,
   -1,   -1,  405,   -1,  407,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  424,   -1,   -1,  427,  428,   -1,   -1,   -1,   -1,
   -1,  434,   -1,   -1,   -1,   -1,  439,   -1,  441,   -1,
  443,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  468,   -1,   -1,  471,   -1,
  473,   -1,   -1,   -1,   -1,  478,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  491,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  502,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  519,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  536,  537,   -1,   -1,   -1,  541,   -1,
  278,  279,   -1,  281,   -1,   -1,   -1,  550,   -1,   -1,
   -1,   -1,  290,  291,   -1,  293,  559,   -1,   -1,  562,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  571,   -1,
   -1,   -1,   -1,  576,  577,  578,   -1,   -1,   -1,   -1,
  583,  584,  585,  321,   -1,   -1,  324,  325,   -1,   -1,
   -1,  329,   -1,   -1,  597,  598,  334,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  343,   -1,  610,   -1,   -1,
  348,  614,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  363,   -1,   -1,   -1,   -1,
  368,   -1,  370,   -1,   -1,   -1,   -1,  375,   -1,  377,
  378,  379,   -1,  381,  382,  383,   -1,  385,  386,   -1,
  388,   -1,  390,  391,  392,  393,  394,  395,  396,  397,
  398,  399,   -1,   -1,   -1,   -1,   -1,  405,   -1,  407,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  424,   -1,   -1,  427,
  428,   -1,   -1,   -1,   -1,   -1,  434,   -1,   -1,   -1,
   -1,  439,   -1,  441,   -1,  443,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  468,   -1,   -1,  471,   -1,  473,   -1,   -1,   -1,   -1,
  478,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  491,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  502,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  519,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  536,  537,
   -1,   -1,   -1,  541,   -1,  278,  279,   -1,  281,   -1,
   -1,   -1,  550,   -1,   -1,   -1,   -1,  290,  291,   -1,
  293,  559,   -1,   -1,  562,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  571,   -1,   -1,   -1,   -1,  576,  577,
  578,   -1,   -1,   -1,   -1,  583,  584,  585,  321,   -1,
   -1,  324,  325,   -1,   -1,   -1,  329,   -1,   -1,  597,
  598,  334,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  343,   -1,  610,   -1,   -1,  348,  614,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  363,   -1,   -1,   -1,   -1,  368,   -1,  370,   -1,   -1,
   -1,   -1,  375,   -1,   -1,  378,  379,   -1,  381,  382,
  383,   -1,  385,  386,  387,  388,   -1,  390,  391,  392,
  393,  394,  395,  396,  397,  398,  399,   -1,   -1,   -1,
   -1,   -1,  405,   -1,  407,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  424,   -1,   -1,  427,  428,   -1,   -1,   -1,   -1,
   -1,  434,   -1,   -1,   -1,   -1,  439,   -1,  441,   -1,
  443,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  468,   -1,   -1,  471,   -1,
  473,   -1,   -1,   -1,   -1,  478,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  491,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  502,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  519,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  536,  537,   -1,   -1,   -1,  541,   -1,
  278,  279,   -1,  281,   -1,   -1,   -1,  550,   -1,   -1,
   -1,   -1,   -1,  291,   -1,  293,  559,   -1,   -1,  562,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  571,   -1,
   -1,   -1,   -1,  576,  577,  578,   -1,   -1,   -1,   -1,
  583,  584,  585,  321,   -1,   -1,  324,  325,   -1,   -1,
   -1,  329,   -1,   -1,  597,  598,  334,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  343,   -1,  610,   -1,   -1,
  348,  614,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  363,   -1,   -1,   -1,   -1,
  368,   -1,  370,   -1,   -1,   -1,   -1,  375,   -1,  377,
  378,  379,   -1,  381,  382,  383,   -1,  385,  386,  387,
  388,   -1,  390,  391,  392,  393,  394,  395,  396,  397,
  398,  399,   -1,   -1,   -1,   -1,   -1,  405,   -1,  407,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  424,   -1,   -1,  427,
  428,   -1,   -1,   -1,   -1,   -1,  434,   -1,   -1,   -1,
   -1,  439,   -1,  441,   -1,  443,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  468,   -1,   -1,  471,   -1,  473,   -1,   -1,   -1,   -1,
  478,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  491,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  502,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  519,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  536,  537,
   -1,   -1,   -1,  541,   -1,  278,  279,   -1,  281,   -1,
   -1,   -1,  550,   -1,   -1,   -1,   -1,  290,  291,   -1,
  293,  559,   -1,   -1,  562,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  571,   -1,   -1,   -1,   -1,  576,  577,
  578,   -1,   -1,   -1,   -1,  583,  584,  585,  321,   -1,
   -1,  324,  325,   -1,   -1,   -1,  329,   -1,   -1,  597,
  598,  334,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  343,   -1,  610,   -1,   -1,  348,  614,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  363,   -1,   -1,   -1,   -1,  368,   -1,  370,   -1,   -1,
   -1,   -1,  375,   -1,  377,  378,  379,   -1,  381,  382,
  383,   -1,  385,  386,  387,  388,   -1,  390,  391,  392,
  393,  394,   -1,  396,  397,  398,  399,   -1,   -1,   -1,
   -1,   -1,  405,   -1,  407,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  424,   -1,   -1,  427,  428,   -1,   -1,   -1,   -1,
   -1,  434,   -1,   -1,   -1,   -1,  439,   -1,  441,   -1,
  443,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  468,   -1,   -1,  471,   -1,
  473,   -1,   -1,   -1,   -1,  478,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  491,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  502,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  519,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  536,  537,   -1,   -1,   -1,  541,   -1,
  278,  279,   -1,  281,   -1,   -1,   -1,  550,   -1,   -1,
   -1,   -1,  290,  291,   -1,  293,  559,   -1,   -1,  562,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  571,   -1,
   -1,   -1,   -1,  576,  577,  578,   -1,   -1,   -1,   -1,
  583,  584,  585,  321,   -1,   -1,  324,  325,   -1,   -1,
   -1,  329,   -1,   -1,  597,  598,  334,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  343,   -1,  610,   -1,   -1,
  348,  614,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  363,   -1,   -1,   -1,   -1,
  368,   -1,  370,   -1,   -1,   -1,   -1,  375,   -1,  377,
  378,  379,   -1,  381,  382,   -1,   -1,  385,  386,  387,
  388,   -1,  390,  391,  392,  393,  394,  395,  396,  397,
  398,  399,   -1,   -1,   -1,   -1,   -1,  405,   -1,  407,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  424,   -1,   -1,  427,
  428,   -1,   -1,   -1,   -1,   -1,  434,   -1,   -1,   -1,
   -1,  439,   -1,  441,   -1,  443,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  468,   -1,   -1,  471,   -1,  473,   -1,   -1,   -1,   -1,
  478,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  491,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  502,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  519,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  536,  537,
   -1,   -1,   -1,  541,   -1,  278,  279,   -1,  281,   -1,
   -1,   -1,  550,   -1,   -1,   -1,   -1,   -1,  291,   -1,
  293,  559,   -1,   -1,  562,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  571,   -1,   -1,   -1,   -1,  576,  577,
  578,   -1,   -1,   -1,   -1,  583,  584,  585,  321,   -1,
   -1,  324,  325,   -1,   -1,   -1,  329,   -1,   -1,  597,
  598,  334,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  343,   -1,  610,   -1,   -1,  348,  614,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  363,   -1,   -1,   -1,   -1,  368,   -1,  370,   -1,   -1,
   -1,   -1,  375,   -1,  377,  378,  379,   -1,  381,  382,
  383,   -1,  385,  386,  387,  388,   -1,  390,  391,  392,
  393,  394,  395,  396,  397,  398,  399,   -1,   -1,   -1,
   -1,   -1,  405,   -1,  407,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  424,   -1,   -1,  427,  428,   -1,   -1,   -1,   -1,
   -1,  434,   -1,   -1,   -1,   -1,  439,   -1,  441,   -1,
  443,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  468,   -1,   -1,  471,   -1,
  473,   -1,   -1,   -1,   -1,  478,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  491,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  502,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  519,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  536,  537,   -1,   -1,   -1,  541,   -1,
  278,  279,   -1,  281,   -1,   -1,   -1,  550,   -1,   -1,
   -1,   -1,  290,  291,   -1,  293,  559,   -1,   -1,  562,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  571,   -1,
   -1,   -1,   -1,  576,  577,  578,   -1,   -1,   -1,   -1,
  583,  584,  585,  321,   -1,   -1,  324,  325,   -1,   -1,
   -1,  329,   -1,   -1,  597,  598,  334,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  343,   -1,  610,   -1,   -1,
  348,  614,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  363,   -1,   -1,   -1,   -1,
  368,   -1,  370,   -1,   -1,   -1,   -1,  375,   -1,  377,
  378,  379,   -1,  381,  382,  383,   -1,  385,  386,  387,
  388,   -1,  390,  391,  392,   -1,  394,  395,  396,  397,
  398,  399,   -1,   -1,   -1,   -1,   -1,  405,   -1,  407,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  424,   -1,   -1,  427,
  428,   -1,   -1,   -1,   -1,   -1,  434,   -1,   -1,   -1,
   -1,  439,   -1,  441,   -1,  443,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  468,   -1,   -1,  471,   -1,  473,   -1,   -1,   -1,   -1,
  478,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  491,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  502,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  519,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  536,  537,
   -1,   -1,   -1,  541,   -1,  278,  279,   -1,  281,   -1,
   -1,   -1,  550,   -1,   -1,   -1,   -1,  290,  291,   -1,
  293,  559,   -1,   -1,  562,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  571,   -1,   -1,   -1,   -1,  576,  577,
  578,   -1,   -1,   -1,   -1,  583,  584,  585,  321,   -1,
   -1,  324,  325,   -1,   -1,   -1,  329,   -1,   -1,  597,
  598,  334,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  343,   -1,  610,   -1,   -1,  348,  614,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  363,   -1,   -1,   -1,   -1,  368,   -1,  370,   -1,   -1,
   -1,   -1,  375,   -1,  377,  378,  379,   -1,  381,  382,
  383,   -1,  385,  386,  387,  388,   -1,  390,  391,  392,
  393,  394,  395,  396,  397,  398,   -1,   -1,   -1,   -1,
   -1,   -1,  405,   -1,  407,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  424,   -1,   -1,  427,  428,   -1,   -1,   -1,   -1,
   -1,  434,   -1,   -1,   -1,   -1,  439,   -1,  441,   -1,
  443,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  468,   -1,   -1,  471,   -1,
  473,   -1,   -1,   -1,   -1,  478,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  491,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  502,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  519,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  536,  537,   -1,   -1,   -1,  541,   -1,
  278,  279,   -1,  281,   -1,   -1,   -1,  550,   -1,   -1,
   -1,   -1,   -1,  291,   -1,  293,  559,   -1,   -1,  562,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  571,   -1,
   -1,   -1,   -1,  576,  577,  578,   -1,   -1,   -1,   -1,
  583,  584,  585,  321,   -1,   -1,  324,  325,   -1,   -1,
   -1,  329,   -1,   -1,  597,  598,  334,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  343,   -1,  610,   -1,   -1,
  348,  614,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  363,   -1,   -1,   -1,   -1,
  368,   -1,  370,   -1,   -1,   -1,   -1,  375,   -1,  377,
  378,  379,   -1,  381,  382,  383,   -1,  385,  386,  387,
  388,   -1,  390,  391,  392,  393,  394,  395,  396,  397,
  398,  399,   -1,   -1,   -1,   -1,   -1,  405,   -1,  407,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  424,   -1,   -1,  427,
  428,   -1,   -1,   -1,   -1,   -1,  434,   -1,   -1,   -1,
   -1,  439,   -1,  441,   -1,  443,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  468,   -1,   -1,  471,   -1,  473,   -1,   -1,   -1,   -1,
  478,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  491,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  502,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  519,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  536,  537,
   -1,   -1,   -1,  541,   -1,  278,  279,   -1,  281,   -1,
   -1,   -1,  550,   -1,   -1,   -1,   -1,   -1,  291,   -1,
  293,  559,   -1,   -1,  562,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  571,   -1,   -1,   -1,   -1,  576,  577,
  578,   -1,   -1,   -1,   -1,  583,  584,  585,  321,   -1,
   -1,  324,  325,   -1,   -1,   -1,  329,   -1,   -1,  597,
  598,  334,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  343,   -1,  610,   -1,   -1,  348,  614,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  363,   -1,   -1,   -1,   -1,  368,   -1,  370,   -1,   -1,
   -1,   -1,  375,   -1,  377,  378,  379,   -1,  381,  382,
  383,   -1,  385,  386,  387,  388,   -1,  390,  391,  392,
  393,  394,  395,  396,  397,  398,  399,   -1,   -1,   -1,
   -1,   -1,  405,   -1,  407,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  424,   -1,   -1,  427,  428,   -1,   -1,   -1,   -1,
   -1,  434,   -1,   -1,   -1,   -1,  439,   -1,  441,   -1,
  443,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  468,   -1,   -1,  471,   -1,
  473,   -1,   -1,   -1,   -1,  478,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  491,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  502,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  519,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  536,  537,   -1,   -1,   -1,  541,   -1,
  278,  279,   -1,  281,   -1,   -1,   -1,  550,   -1,   -1,
   -1,   -1,   -1,  291,   -1,  293,  559,   -1,   -1,  562,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  571,   -1,
   -1,   -1,   -1,  576,  577,  578,   -1,   -1,   -1,   -1,
  583,  584,  585,  321,   -1,   -1,  324,  325,   -1,   -1,
   -1,  329,   -1,   -1,  597,  598,  334,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  343,   -1,  610,   -1,   -1,
  348,  614,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  363,   -1,   -1,   -1,   -1,
  368,   -1,  370,   -1,   -1,   -1,   -1,  375,   -1,  377,
  378,  379,   -1,  381,  382,  383,   -1,  385,  386,  387,
  388,   -1,  390,  391,  392,  393,  394,  395,  396,  397,
  398,  399,   -1,   -1,   -1,   -1,   -1,  405,   -1,  407,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  424,   -1,   -1,  427,
  428,   -1,   -1,   -1,   -1,   -1,  434,   -1,   -1,   -1,
   -1,  439,   -1,  441,   -1,  443,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  468,   -1,   -1,  471,   -1,  473,   -1,   -1,   -1,   -1,
  478,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  491,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  502,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  519,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  536,  537,
   -1,   -1,   -1,  541,   -1,  278,  279,   -1,  281,   -1,
   -1,   -1,  550,   -1,   -1,   -1,   -1,  290,  291,   -1,
  293,  559,   -1,   -1,  562,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  571,   -1,   -1,   -1,   -1,  576,  577,
  578,   -1,   -1,   -1,   -1,  583,  584,  585,  321,   -1,
   -1,  324,  325,   -1,   -1,   -1,  329,   -1,   -1,  597,
  598,  334,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  343,   -1,  610,   -1,   -1,  348,  614,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  363,   -1,   -1,   -1,   -1,  368,   -1,  370,   -1,   -1,
   -1,   -1,  375,   -1,  377,  378,  379,   -1,  381,  382,
  383,   -1,  385,  386,  387,  388,   -1,  390,  391,  392,
  393,  394,  395,  396,  397,  398,  399,   -1,   -1,   -1,
   -1,   -1,  405,   -1,  407,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  424,   -1,   -1,  427,  428,   -1,   -1,   -1,   -1,
   -1,  434,   -1,   -1,   -1,   -1,  439,   -1,  441,   -1,
  443,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  468,   -1,   -1,  471,   -1,
  473,   -1,   -1,   -1,   -1,  478,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  491,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  502,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  519,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  536,  537,   -1,   -1,   -1,  541,   -1,
  278,  279,   -1,  281,   -1,   -1,   -1,  550,   -1,   -1,
   -1,   -1,  290,  291,   -1,  293,  559,   -1,   -1,  562,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  571,   -1,
   -1,   -1,   -1,  576,  577,  578,   -1,   -1,   -1,   -1,
  583,  584,  585,  321,   -1,   -1,  324,  325,   -1,   -1,
   -1,  329,   -1,   -1,  597,  598,  334,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  343,   -1,   -1,   -1,   -1,
  348,  614,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  363,   -1,   -1,   -1,   -1,
  368,   -1,  370,   -1,   -1,   -1,   -1,  375,   -1,  377,
  378,  379,   -1,  381,  382,  383,   -1,  385,  386,  387,
  388,   -1,  390,  391,  392,  393,  394,  395,   -1,  397,
  398,  399,   -1,   -1,   -1,   -1,   -1,  405,   -1,  407,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  424,   -1,   -1,  427,
  428,   -1,   -1,   -1,   -1,   -1,  434,   -1,   -1,   -1,
   -1,  439,   -1,  441,   -1,  443,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  468,   -1,   -1,  471,   -1,  473,   -1,   -1,   -1,   -1,
  478,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  491,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  502,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  519,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  536,  537,
   -1,   -1,   -1,  541,   -1,  278,  279,   -1,  281,   -1,
   -1,   -1,  550,   -1,   -1,   -1,   -1,   -1,  291,   -1,
  293,  559,   -1,   -1,  562,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  571,   -1,   -1,   -1,   -1,  576,  577,
  578,   -1,   -1,   -1,   -1,  583,  584,  585,  321,   -1,
   -1,  324,  325,   -1,   -1,   -1,  329,   -1,   -1,  597,
  598,  334,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  343,   -1,  610,   -1,   -1,  348,  614,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  363,   -1,   -1,   -1,   -1,  368,   -1,  370,   -1,   -1,
   -1,   -1,  375,   -1,  377,  378,  379,   -1,  381,  382,
  383,   -1,  385,  386,  387,  388,   -1,  390,  391,  392,
  393,  394,  395,  396,  397,  398,  399,   -1,   -1,   -1,
   -1,   -1,  405,   -1,  407,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  424,   -1,   -1,  427,  428,   -1,   -1,   -1,   -1,
   -1,  434,   -1,   -1,   -1,   -1,  439,   -1,  441,   -1,
  443,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  468,   -1,   -1,  471,   -1,
  473,   -1,   -1,   -1,   -1,  478,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  491,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  502,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  519,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  536,  537,   -1,   -1,   -1,  541,   -1,
  278,  279,   -1,  281,   -1,   -1,   -1,  550,   -1,   -1,
   -1,   -1,  290,  291,   -1,  293,  559,   -1,   -1,  562,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  571,   -1,
   -1,   -1,   -1,  576,  577,  578,   -1,   -1,   -1,   -1,
  583,  584,  585,  321,   -1,   -1,  324,  325,   -1,   -1,
   -1,  329,   -1,   -1,  597,  598,  334,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  343,   -1,  610,   -1,   -1,
  348,  614,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  363,   -1,   -1,   -1,   -1,
  368,   -1,  370,   -1,   -1,   -1,   -1,  375,   -1,  377,
  378,  379,   -1,   -1,  382,  383,   -1,  385,  386,  387,
  388,   -1,  390,  391,  392,  393,  394,  395,  396,  397,
  398,  399,   -1,   -1,   -1,   -1,   -1,  405,   -1,  407,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  424,   -1,   -1,  427,
  428,   -1,   -1,   -1,   -1,   -1,  434,   -1,   -1,   -1,
   -1,  439,   -1,  441,   -1,  443,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  468,   -1,   -1,  471,   -1,  473,   -1,   -1,   -1,   -1,
  478,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  491,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  502,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  519,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  536,  537,
   -1,   -1,   -1,  541,   -1,  278,  279,   -1,  281,   -1,
   -1,   -1,  550,   -1,   -1,   -1,   -1,  290,  291,   -1,
  293,  559,   -1,   -1,  562,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  571,   -1,   -1,   -1,   -1,  576,  577,
  578,   -1,   -1,   -1,   -1,  583,  584,  585,  321,   -1,
   -1,  324,  325,   -1,   -1,   -1,  329,   -1,   -1,  597,
  598,  334,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  343,   -1,  610,   -1,   -1,  348,  614,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  363,   -1,   -1,   -1,   -1,  368,   -1,  370,   -1,   -1,
   -1,   -1,  375,   -1,  377,  378,  379,   -1,  381,  382,
  383,   -1,  385,  386,  387,  388,   -1,  390,  391,  392,
  393,  394,  395,  396,  397,  398,  399,   -1,   -1,   -1,
   -1,   -1,  405,   -1,  407,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  424,   -1,   -1,  427,  428,   -1,   -1,   -1,   -1,
   -1,  434,   -1,   -1,   -1,   -1,  439,   -1,  441,   -1,
  443,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  468,   -1,   -1,  471,   -1,
  473,   -1,   -1,   -1,   -1,  478,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  491,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  502,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  519,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  536,  537,   -1,   -1,   -1,  541,   -1,
  278,  279,   -1,  281,   -1,   -1,   -1,  550,   -1,   -1,
   -1,   -1,  290,  291,   -1,  293,  559,   -1,   -1,  562,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  571,   -1,
   -1,   -1,   -1,  576,  577,  578,   -1,   -1,   -1,   -1,
  583,  584,  585,  321,   -1,   -1,  324,  325,   -1,   -1,
   -1,  329,   -1,   -1,  597,  598,  334,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  343,   -1,   -1,   -1,   -1,
  348,  614,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  363,   -1,   -1,   -1,   -1,
  368,   -1,  370,   -1,   -1,   -1,   -1,  375,   -1,  377,
  378,  379,   -1,  381,  382,  383,   -1,  385,  386,  387,
  388,   -1,  390,  391,  392,  393,  394,  395,  396,  397,
   -1,  399,   -1,   -1,   -1,   -1,   -1,  405,   -1,  407,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  424,   -1,   -1,  427,
  428,   -1,   -1,   -1,   -1,   -1,  434,   -1,   -1,   -1,
   -1,  439,   -1,  441,   -1,  443,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  468,   -1,   -1,  471,   -1,  473,   -1,   -1,   -1,   -1,
  478,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  491,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  502,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  519,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  536,  537,
   -1,   -1,   -1,  541,   -1,  278,  279,   -1,  281,   -1,
   -1,   -1,  550,   -1,   -1,   -1,   -1,   -1,  291,   -1,
  293,  559,   -1,   -1,  562,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  571,   -1,   -1,   -1,   -1,  576,  577,
  578,   -1,   -1,   -1,   -1,  583,  584,  585,  321,   -1,
   -1,  324,  325,   -1,   -1,   -1,  329,   -1,   -1,  597,
  598,  334,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  343,   -1,  610,   -1,   -1,  348,  614,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  363,   -1,   -1,   -1,   -1,  368,   -1,  370,   -1,   -1,
   -1,   -1,  375,   -1,  377,  378,  379,   -1,  381,  382,
  383,   -1,  385,  386,  387,  388,   -1,  390,  391,  392,
  393,  394,  395,  396,  397,  398,  399,   -1,   -1,   -1,
   -1,   -1,  405,   -1,  407,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  424,   -1,   -1,  427,  428,   -1,   -1,   -1,   -1,
   -1,  434,   -1,   -1,   -1,   -1,  439,   -1,  441,   -1,
  443,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  468,   -1,   -1,  471,   -1,
  473,   -1,   -1,   -1,   -1,  478,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  491,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  502,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  519,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  536,  537,   -1,   -1,   -1,  541,   -1,
  278,  279,   -1,  281,   -1,   -1,   -1,  550,   -1,   -1,
   -1,   -1,  290,  291,   -1,  293,  559,   -1,   -1,  562,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  571,   -1,
   -1,   -1,   -1,  576,  577,  578,   -1,   -1,   -1,   -1,
  583,  584,  585,  321,   -1,   -1,  324,  325,   -1,   -1,
   -1,  329,   -1,   -1,  597,  598,  334,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  343,   -1,  610,   -1,   -1,
  348,  614,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  363,   -1,   -1,   -1,   -1,
  368,   -1,  370,   -1,   -1,   -1,   -1,  375,   -1,  377,
  378,   -1,   -1,  381,  382,  383,   -1,  385,  386,  387,
  388,   -1,  390,  391,  392,  393,  394,  395,  396,  397,
  398,  399,   -1,   -1,   -1,   -1,   -1,  405,   -1,  407,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  424,   -1,   -1,  427,
  428,   -1,   -1,   -1,   -1,   -1,  434,   -1,   -1,   -1,
   -1,  439,   -1,  441,   -1,  443,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  468,   -1,   -1,  471,   -1,  473,   -1,   -1,   -1,   -1,
  478,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  491,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  502,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  519,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  536,  537,
   -1,   -1,   -1,  541,   -1,  278,  279,   -1,  281,   -1,
   -1,   -1,  550,   -1,   -1,   -1,   -1,   -1,  291,   -1,
  293,  559,   -1,   -1,  562,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  571,   -1,   -1,   -1,   -1,  576,  577,
  578,   -1,   -1,   -1,   -1,  583,  584,  585,  321,   -1,
   -1,  324,  325,   -1,   -1,   -1,  329,   -1,   -1,  597,
  598,  334,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  343,   -1,  610,   -1,   -1,  348,  614,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  363,   -1,   -1,   -1,   -1,  368,   -1,  370,   -1,   -1,
   -1,   -1,  375,   -1,  377,  378,  379,   -1,  381,  382,
  383,   -1,  385,  386,  387,  388,   -1,  390,  391,  392,
  393,  394,  395,  396,  397,  398,  399,   -1,   -1,   -1,
   -1,   -1,  405,   -1,  407,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  424,   -1,   -1,  427,  428,   -1,   -1,   -1,   -1,
   -1,  434,   -1,   -1,   -1,   -1,  439,   -1,  441,   -1,
  443,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  468,   -1,   -1,  471,   -1,
  473,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  491,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  502,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  519,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  536,  537,   -1,   -1,   -1,  541,   -1,
  278,  279,   -1,  281,   -1,   -1,   -1,  550,   -1,   -1,
   -1,   -1,   -1,  291,   -1,  293,  559,   -1,   -1,  562,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  571,   -1,
   -1,   -1,   -1,  576,  577,  578,   -1,   -1,   -1,   -1,
  583,  584,  585,  321,   -1,   -1,  324,  325,   -1,   -1,
   -1,  329,   -1,   -1,  597,  598,  334,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  343,   -1,  610,   -1,   -1,
  348,  614,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  363,   -1,   -1,   -1,   -1,
  368,   -1,  370,   -1,   -1,   -1,   -1,  375,   -1,  377,
  378,  379,   -1,  381,  382,  383,   -1,  385,  386,  387,
  388,   -1,  390,  391,  392,  393,  394,  395,  396,  397,
  398,  399,   -1,   -1,   -1,   -1,   -1,  405,   -1,  407,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  424,   -1,   -1,  427,
  428,   -1,   -1,   -1,   -1,   -1,  434,   -1,   -1,   -1,
   -1,  439,   -1,  441,   -1,  443,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  468,   -1,   -1,  471,   -1,  473,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  491,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  502,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  519,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  536,  537,
   -1,   -1,   -1,  541,   -1,  278,  279,   -1,  281,   -1,
   -1,   -1,  550,   -1,   -1,   -1,   -1,   -1,  291,   -1,
  293,  559,   -1,   -1,  562,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  571,   -1,   -1,   -1,   -1,  576,  577,
  578,   -1,   -1,   -1,   -1,  583,  584,  585,  321,   -1,
   -1,  324,  325,   -1,   -1,   -1,  329,   -1,   -1,  597,
  598,  334,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  343,   -1,  610,   -1,   -1,  348,  614,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  363,   -1,   -1,   -1,   -1,  368,   -1,  370,   -1,   -1,
   -1,   -1,  375,  272,  377,  378,  379,  276,  381,  382,
  383,   -1,  385,  386,  387,  388,   -1,  390,  391,  392,
  393,  394,  395,  396,  397,  398,  399,   -1,   -1,   -1,
   -1,   -1,  405,   -1,  407,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  312,  313,   -1,  315,  316,  317,   -1,
   -1,  424,   -1,   -1,  427,  428,   -1,   -1,   -1,   -1,
   -1,  434,   -1,   -1,   -1,   -1,  439,   -1,  441,  338,
  443,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  278,
  279,   -1,  281,   -1,   -1,  468,   -1,   -1,  471,   -1,
  473,   -1,  291,   -1,  293,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  304,   -1,   -1,  491,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  502,
   -1,   -1,  321,   -1,  403,  324,  325,   -1,   -1,   -1,
  329,   -1,   -1,   -1,   -1,  334,  519,   -1,   -1,   -1,
   -1,  420,   -1,  422,  343,   -1,   -1,   -1,   -1,  348,
   -1,   -1,  431,  536,  537,   -1,   -1,   -1,  541,   -1,
   -1,   -1,   -1,   -1,  363,   -1,   -1,  550,   -1,  368,
  449,  370,   -1,   -1,  453,   -1,  559,   -1,   -1,  562,
   -1,   -1,   -1,   -1,   -1,  464,  465,  386,  571,   -1,
   -1,   -1,   -1,  576,  577,  578,   -1,   -1,  477,   -1,
  583,  584,  585,   -1,   -1,   -1,  405,   -1,  407,   -1,
   -1,   -1,   -1,   -1,  597,  598,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  424,   -1,  610,  427,  428,
   -1,  614,   -1,   -1,   -1,  434,   -1,   -1,   -1,   -1,
  439,   -1,  441,   -1,  443,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  534,   -1,   -1,   -1,   -1,
  539,   -1,   -1,  278,  279,   -1,  281,   -1,   -1,  468,
   -1,   -1,  471,  552,  473,   -1,  291,  476,  293,   -1,
   -1,  560,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  304,
   -1,   -1,  491,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  502,   -1,   -1,  321,   -1,   -1,  324,
  325,   -1,   -1,  592,  329,   -1,  595,   -1,   -1,  334,
  519,   -1,  601,   -1,  603,   -1,   -1,   -1,  343,   -1,
   -1,   -1,   -1,  348,   -1,   -1,   -1,  536,  537,   -1,
   -1,   -1,  541,   -1,   -1,   -1,   -1,   -1,  363,   -1,
   -1,  550,   -1,  368,   -1,  370,   -1,   -1,   -1,   -1,
  559,   -1,   -1,  562,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  386,  571,   -1,   -1,   -1,   -1,  576,  577,  578,
   -1,   -1,   -1,   -1,  583,  584,  585,   -1,   -1,   -1,
  405,   -1,  407,   -1,   -1,   -1,   -1,   -1,  597,  598,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  424,
   -1,  610,  427,  428,   -1,  614,   -1,   -1,   -1,  434,
   -1,   -1,   -1,   -1,  439,   -1,  441,   -1,  443,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  278,  279,   -1,
  281,   -1,   -1,  468,   -1,   -1,  471,   -1,  473,   -1,
  291,  476,  293,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  491,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  502,   -1,   -1,
  321,   -1,   -1,  324,  325,   -1,   -1,   -1,  329,   -1,
   -1,   -1,   -1,  334,  519,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  343,   -1,   -1,   -1,   -1,  348,   -1,   -1,
   -1,  536,  537,   -1,   -1,   -1,  541,   -1,   -1,   -1,
   -1,   -1,  363,   -1,   -1,  550,   -1,  368,   -1,  370,
   -1,   -1,   -1,   -1,  559,   -1,   -1,  562,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  386,  571,   -1,   -1,   -1,
   -1,  576,  577,  578,   -1,   -1,   -1,   -1,  583,  584,
  585,   -1,   -1,   -1,  405,   -1,  407,   -1,   -1,   -1,
   -1,   -1,  597,  598,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  424,   -1,  610,  427,  428,   -1,  614,
   -1,   -1,   -1,  434,   -1,   -1,   -1,   -1,  439,   -1,
  441,   -1,  443,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  278,  279,   -1,  281,   -1,   -1,  468,   -1,   -1,
  471,   -1,  473,   -1,  291,  476,  293,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  491,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  502,   -1,   -1,  321,   -1,   -1,  324,  325,   -1,
   -1,   -1,  329,   -1,   -1,   -1,   -1,  334,  519,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  343,   -1,   -1,   -1,
   -1,  348,   -1,   -1,   -1,  536,  537,   -1,   -1,   -1,
  541,   -1,   -1,   -1,   -1,   -1,  363,   -1,   -1,  550,
   -1,  368,   -1,  370,   -1,   -1,   -1,   -1,  559,   -1,
   -1,  562,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  386,
  571,   -1,   -1,   -1,   -1,  576,  577,  578,   -1,   -1,
   -1,   -1,  583,  584,  585,   -1,   -1,   -1,  405,   -1,
  407,   -1,   -1,   -1,   -1,   -1,  597,  598,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  424,   -1,  610,
  427,  428,   -1,  614,   -1,   -1,   -1,  434,   -1,   -1,
   -1,   -1,  439,   -1,  441,   -1,  443,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  278,  279,   -1,  281,   -1,
   -1,  468,   -1,   -1,  471,   -1,  473,   -1,  291,  476,
  293,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  491,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  502,   -1,   -1,  321,   -1,
   -1,  324,  325,   -1,   -1,   -1,  329,   -1,   -1,   -1,
   -1,  334,  519,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  343,   -1,   -1,   -1,   -1,  348,   -1,   -1,   -1,  536,
  537,   -1,   -1,   -1,  541,   -1,   -1,   -1,   -1,   -1,
  363,   -1,   -1,  550,   -1,  368,   -1,  370,   -1,   -1,
   -1,   -1,  559,   -1,   -1,  562,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  571,   -1,   -1,   -1,   -1,  576,
  577,  578,   -1,   -1,   -1,   -1,  583,  584,  585,   -1,
   -1,   -1,  405,   -1,  407,   -1,   -1,   -1,   -1,   -1,
  597,  598,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  424,   -1,  610,  427,  428,   -1,  614,   -1,   -1,
   -1,  434,   -1,   -1,   -1,   -1,  439,   -1,  441,   -1,
  443,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  278,  279,
   -1,  281,   -1,   -1,   -1,  468,   -1,   -1,  471,   -1,
  473,  291,   -1,  293,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  491,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  502,
   -1,  321,   -1,   -1,  324,  325,   -1,   -1,   -1,  329,
   -1,   -1,   -1,   -1,  334,   -1,  519,   -1,   -1,   -1,
   -1,   -1,   -1,  343,   -1,   -1,   -1,   -1,  348,   -1,
   -1,   -1,   -1,  536,  537,   -1,   -1,   -1,  541,   -1,
   -1,   -1,   -1,  363,   -1,   -1,   -1,  550,  368,   -1,
  370,   -1,   -1,   -1,   -1,   -1,  559,   -1,   -1,  562,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  571,   -1,
   -1,   -1,   -1,  576,  577,  578,   -1,   -1,   -1,   -1,
  583,  584,  585,   -1,   -1,  405,   -1,  407,   -1,   -1,
   -1,   -1,   -1,   -1,  597,  598,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  424,   -1,   -1,  427,  428,   -1,
   -1,  614,   -1,   -1,  434,   -1,   -1,   -1,   -1,  439,
   -1,  441,   -1,  443,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  278,  279,   -1,  281,   -1,   -1,   -1,  468,   -1,
   -1,  471,   -1,  473,  291,   -1,  293,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  491,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  502,   -1,  321,   -1,   -1,  324,  325,   -1,
   -1,   -1,  329,   -1,   -1,   -1,   -1,  334,   -1,  519,
   -1,   -1,   -1,   -1,   -1,   -1,  343,   -1,   -1,   -1,
   -1,  348,   -1,   -1,   -1,   -1,  536,  537,   -1,   -1,
   -1,  541,   -1,   -1,   -1,   -1,  363,   -1,   -1,   -1,
  550,  368,   -1,  370,   -1,   -1,   -1,   -1,   -1,  559,
   -1,   -1,  562,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  571,   -1,   -1,   -1,   -1,  576,  577,  578,   -1,
   -1,   -1,   -1,  583,  584,  585,   -1,   -1,  405,   -1,
  407,   -1,   -1,   -1,   -1,   -1,   -1,  597,  598,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  424,   -1,   -1,
  427,  428,   -1,   -1,  614,   -1,   -1,  434,   -1,   -1,
   -1,   -1,  439,   -1,  441,   -1,  443,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  278,  279,   -1,  281,   -1,   -1,
   -1,  468,   -1,   -1,  471,   -1,  473,  291,   -1,  293,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  491,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  502,   -1,  321,   -1,   -1,
  324,  325,   -1,   -1,   -1,  329,   -1,   -1,   -1,   -1,
  334,   -1,  519,   -1,   -1,   -1,   -1,   -1,   -1,  343,
   -1,   -1,   -1,   -1,  348,   -1,   -1,   -1,   -1,  536,
  537,   -1,   -1,   -1,  541,   -1,   -1,   -1,   -1,  363,
   -1,   -1,   -1,  550,  368,   -1,  370,   -1,   -1,   -1,
   -1,   -1,  559,   -1,   -1,  562,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  571,   -1,   -1,   -1,   -1,  576,
  577,  578,   -1,   -1,   -1,   -1,  583,  584,  585,  586,
   -1,  405,   -1,  407,   -1,   -1,   -1,   -1,   -1,   -1,
  597,  598,  599,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  424,   -1,  609,  427,  428,   -1,   -1,   -1,   -1,   -1,
  434,   -1,   -1,   -1,   -1,  439,   -1,  441,   -1,  443,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  278,  279,
   -1,  281,   -1,   -1,  468,   -1,   -1,  471,   -1,  473,
   -1,  291,  476,  293,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  491,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  502,   -1,
   -1,  321,   -1,   -1,  324,  325,   -1,   -1,   -1,  329,
   -1,   -1,   -1,   -1,  334,  519,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  343,   -1,   -1,   -1,   -1,  348,   -1,
   -1,   -1,  536,  537,   -1,   -1,   -1,  541,   -1,   -1,
   -1,   -1,   -1,  363,   -1,   -1,  550,   -1,  368,   -1,
  370,   -1,   -1,   -1,   -1,  559,   -1,   -1,  562,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  571,   -1,   -1,
   -1,   -1,  576,  577,  578,   -1,   -1,   -1,   -1,  583,
  584,  585,   -1,  587,   -1,  405,   -1,  407,   -1,   -1,
   -1,   -1,   -1,  597,  598,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  424,   -1,   -1,  427,  428,   -1,
   -1,   -1,   -1,   -1,  434,   -1,   -1,   -1,   -1,  439,
   -1,  441,   -1,  443,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  278,  279,   -1,  281,   -1,   -1,  468,   -1,
   -1,  471,   -1,  473,   -1,  291,  476,  293,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  491,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  502,   -1,   -1,  321,   -1,   -1,  324,  325,
   -1,   -1,   -1,  329,   -1,   -1,   -1,   -1,  334,  519,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  343,   -1,   -1,
   -1,   -1,  348,   -1,   -1,   -1,  536,  537,   -1,   -1,
   -1,  541,   -1,   -1,   -1,   -1,   -1,  363,   -1,   -1,
  550,   -1,  368,   -1,  370,   -1,   -1,   -1,   -1,  559,
   -1,   -1,  562,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  571,   -1,   -1,   -1,   -1,  576,  577,  578,   -1,
   -1,   -1,   -1,  583,  584,  585,   -1,   -1,   -1,  405,
   -1,  407,   -1,   -1,   -1,   -1,   -1,  597,  598,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  424,   -1,
   -1,  427,  428,   -1,   -1,   -1,   -1,   -1,  434,   -1,
   -1,   -1,   -1,  439,   -1,  441,   -1,  443,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  278,  279,   -1,  281,
   -1,   -1,  468,   -1,   -1,  471,   -1,  473,   -1,  291,
  476,  293,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  491,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  502,   -1,   -1,  321,
   -1,   -1,  324,  325,   -1,   -1,   -1,  329,   -1,   -1,
   -1,   -1,  334,  519,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  343,   -1,   -1,   -1,   -1,  348,   -1,   -1,   -1,
  536,  537,   -1,   -1,   -1,  541,   -1,   -1,   -1,   -1,
   -1,  363,   -1,   -1,  550,   -1,  368,   -1,  370,   -1,
   -1,   -1,   -1,  559,   -1,   -1,  562,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  571,   -1,   -1,   -1,   -1,
  576,  577,  578,   -1,   -1,   -1,   -1,  583,  584,  585,
   -1,   -1,   -1,  405,   -1,  407,   -1,   -1,   -1,   -1,
   -1,  597,  598,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  424,   -1,   -1,  427,  428,   -1,   -1,   -1,
   -1,   -1,  434,   -1,   -1,   -1,   -1,  439,   -1,  441,
   -1,  443,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  278,  279,   -1,  281,   -1,   -1,  468,   -1,   -1,  471,
   -1,  473,   -1,  291,  476,  293,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  491,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  502,   -1,   -1,  321,   -1,   -1,  324,  325,   -1,   -1,
   -1,  329,   -1,   -1,   -1,   -1,  334,  519,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  343,   -1,   -1,   -1,   -1,
  348,   -1,   -1,   -1,  536,  537,   -1,   -1,   -1,  541,
   -1,   -1,   -1,   -1,   -1,  363,   -1,   -1,  550,   -1,
  368,   -1,  370,   -1,   -1,   -1,   -1,  559,   -1,   -1,
  562,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  571,
   -1,   -1,   -1,   -1,  576,  577,  578,   -1,   -1,   -1,
   -1,  583,  584,  585,   -1,   -1,   -1,  405,   -1,  407,
   -1,   -1,   -1,   -1,   -1,  597,  598,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  424,   -1,   -1,  427,
  428,   -1,   -1,   -1,   -1,   -1,  434,   -1,   -1,   -1,
   -1,  439,   -1,  441,   -1,  443,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  278,  279,   -1,  281,   -1,   -1,
  468,   -1,   -1,  471,   -1,  473,   -1,  291,  476,  293,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  491,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  502,   -1,   -1,  321,   -1,   -1,
  324,  325,   -1,   -1,   -1,  329,   -1,   -1,   -1,   -1,
  334,  519,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  343,
   -1,   -1,   -1,   -1,  348,   -1,   -1,   -1,  536,  537,
   -1,   -1,   -1,  541,   -1,   -1,   -1,   -1,   -1,  363,
   -1,   -1,  550,   -1,  368,   -1,  370,   -1,   -1,   -1,
   -1,  559,   -1,   -1,  562,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  571,   -1,   -1,   -1,   -1,  576,  577,
  578,   -1,   -1,   -1,   -1,  583,  584,  585,   -1,   -1,
   -1,  405,   -1,  407,   -1,   -1,   -1,   -1,   -1,  597,
  598,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  424,   -1,   -1,  427,  428,   -1,   -1,   -1,   -1,   -1,
  434,   -1,   -1,   -1,   -1,  439,   -1,  441,   -1,  443,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  278,  279,
   -1,  281,   -1,   -1,  468,   -1,   -1,  471,   -1,  473,
   -1,  291,  476,  293,   -1,   -1,  296,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  491,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  502,   -1,
   -1,  321,   -1,   -1,  324,  325,   -1,   -1,   -1,  329,
   -1,   -1,   -1,   -1,  334,  519,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  343,   -1,   -1,   -1,   -1,  348,   -1,
   -1,   -1,  536,  537,   -1,   -1,   -1,  541,   -1,   -1,
   -1,   -1,   -1,  363,   -1,   -1,  550,   -1,  368,   -1,
  370,   -1,   -1,   -1,   -1,  559,   -1,   -1,  562,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  571,   -1,   -1,
   -1,   -1,  576,  577,  578,   -1,   -1,   -1,   -1,  583,
  584,  585,   -1,   -1,   -1,  405,   -1,  407,   -1,   -1,
   -1,   -1,   -1,  597,  598,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  424,   -1,   -1,  427,  428,   -1,
   -1,   -1,   -1,   -1,  434,   -1,   -1,   -1,   -1,  439,
   -1,  441,   -1,  443,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  278,  279,   -1,  281,   -1,   -1,   -1,  468,   -1,
   -1,  471,   -1,  473,  291,   -1,  293,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  491,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  502,   -1,  321,   -1,   -1,  324,  325,   -1,
   -1,   -1,  329,   -1,   -1,   -1,   -1,  334,   -1,  519,
   -1,   -1,   -1,   -1,   -1,   -1,  343,   -1,   -1,   -1,
   -1,  348,   -1,   -1,   -1,   -1,  536,  537,   -1,   -1,
   -1,  541,   -1,   -1,   -1,   -1,  363,   -1,   -1,   -1,
  550,  368,   -1,  370,   -1,   -1,   -1,   -1,   -1,  559,
   -1,   -1,  562,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  571,   -1,   -1,   -1,   -1,  576,  577,  578,   -1,
   -1,   -1,   -1,  583,  584,  585,   -1,   -1,  405,   -1,
  407,   -1,   -1,   -1,   -1,   -1,   -1,  597,  598,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  424,   -1,   -1,
  427,  428,   -1,   -1,   -1,   -1,   -1,  434,   -1,   -1,
   -1,   -1,  439,   -1,  441,   -1,  443,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  278,  279,   -1,  281,   -1,   -1,
   -1,  468,   -1,   -1,  471,   -1,  473,  291,   -1,  293,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  491,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  502,   -1,  321,   -1,   -1,
  324,  325,   -1,   -1,   -1,  329,   -1,   -1,   -1,   -1,
  334,   -1,  519,   -1,   -1,   -1,   -1,   -1,   -1,  343,
   -1,   -1,   -1,   -1,  348,   -1,   -1,   -1,   -1,  536,
  537,   -1,   -1,   -1,  541,   -1,   -1,   -1,   -1,  363,
   -1,   -1,   -1,  550,  368,   -1,  370,   -1,   -1,   -1,
   -1,   -1,  559,   -1,   -1,  562,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  571,   -1,   -1,   -1,   -1,  576,
  577,  578,   -1,   -1,   -1,   -1,  583,  584,  585,   -1,
   -1,  405,   -1,  407,   -1,   -1,   -1,   -1,   -1,   -1,
  597,  598,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  424,   -1,   -1,  427,  428,   -1,   -1,   -1,   -1,   -1,
  434,   -1,   -1,   -1,   -1,  439,   -1,  441,   -1,  443,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  278,  279,   -1,
  281,   -1,   -1,   -1,  468,   -1,   -1,  471,   -1,  473,
  291,   -1,  293,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  491,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  502,   -1,
  321,   -1,   -1,  324,  325,   -1,   -1,   -1,  329,   -1,
   -1,   -1,   -1,  334,   -1,  519,   -1,   -1,   -1,   -1,
   -1,   -1,  343,   -1,   -1,   -1,   -1,  348,   -1,   -1,
   -1,   -1,  536,  537,   -1,   -1,   -1,  541,   -1,   -1,
   -1,   -1,  363,   -1,   -1,   -1,  550,  368,   -1,  370,
   -1,   -1,   -1,   -1,   -1,  559,   -1,   -1,  562,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  571,   -1,   -1,
   -1,   -1,  576,  577,  578,   -1,   -1,   -1,   -1,  583,
  584,  585,   -1,   -1,  405,   -1,  407,   -1,   -1,   -1,
   -1,   -1,   -1,  597,  598,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  424,   -1,   -1,  427,  428,   -1,   -1,
   -1,   -1,   -1,  434,   -1,   -1,   -1,   -1,  439,   -1,
  441,   -1,  443,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  278,  279,   -1,  281,   -1,   -1,   -1,  468,   -1,   -1,
  471,   -1,  473,  291,   -1,  293,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  491,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  502,   -1,  321,   -1,   -1,  324,  325,   -1,   -1,
   -1,  329,   -1,   -1,   -1,   -1,  334,   -1,  519,   -1,
   -1,   -1,   -1,   -1,   -1,  343,   -1,   -1,   -1,   -1,
  348,   -1,   -1,   -1,   -1,  536,  537,   -1,   -1,   -1,
  541,   -1,   -1,   -1,   -1,  363,   -1,   -1,   -1,  550,
  368,   -1,  370,   -1,   -1,   -1,   -1,   -1,  559,   -1,
   -1,  562,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  571,   -1,   -1,   -1,   -1,  576,  577,  578,   -1,   -1,
   -1,   -1,  583,  584,  585,   -1,   -1,  405,   -1,  407,
   -1,   -1,   -1,   -1,   -1,   -1,  597,  598,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  424,   -1,   -1,  427,
  428,   -1,   -1,   -1,   -1,   -1,  434,   -1,   -1,   -1,
   -1,  439,   -1,  441,   -1,  443,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  278,  279,   -1,  281,   -1,   -1,   -1,
  468,   -1,   -1,  471,   -1,  473,  291,   -1,  293,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  491,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  502,   -1,  321,   -1,   -1,  324,
  325,   -1,   -1,   -1,  329,   -1,   -1,   -1,   -1,  334,
   -1,  519,   -1,   -1,   -1,   -1,   -1,   -1,  343,   -1,
   -1,   -1,   -1,  348,   -1,   -1,   -1,   -1,  536,  537,
   -1,   -1,   -1,  541,   -1,   -1,   -1,   -1,  363,   -1,
   -1,   -1,  550,  368,   -1,  370,   -1,   -1,   -1,   -1,
   -1,  559,   -1,   -1,  562,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  571,   -1,   -1,   -1,   -1,  576,  577,
  578,   -1,   -1,   -1,   -1,  583,  584,  585,   -1,   -1,
  405,   -1,  407,   -1,   -1,   -1,   -1,   -1,   -1,  597,
  598,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  424,
   -1,   -1,  427,  428,   -1,   -1,   -1,   -1,   -1,  434,
   -1,   -1,   -1,   -1,  439,   -1,  441,   -1,  443,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  468,   -1,   -1,  471,   -1,  473,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  491,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  502,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  519,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  536,  537,   -1,   -1,   -1,  541,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  550,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  559,   -1,   -1,  562,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  571,   -1,   -1,   -1,
   -1,  576,  577,  578,   -1,   -1,   -1,   -1,  583,  584,
  585,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  597,  598,
};
#define YYFINAL 2
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 614
#if YYDEBUG
char *yyname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,"'('","')'","'*'","'+'","','","'-'","'.'","'/'",0,0,0,0,0,0,0,0,0,0,
"':'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,"IDSTRING_WORD","IDSTRING_LITERAL","STRING","VARIABLE","VARCOND","SUBSCVAR",
"LABELSTR","CMD_LINE","ENVIRONMENT_VARIABLE","INKEY","CHAR","MULTIPLIER",
"USAGENUM","CONDITIONAL","TO","IS","ARE","THRU","THAN","NO","DIRECTION","READ",
"WRITE","INPUT_OUTPUT","RELEASE","NLITERAL","CLITERAL","DISK","PRINTER",
"DATE_TIME","POW_OP","OR","AND","NOT","ACCEPT","ACCESS","ADD","ADDRESS",
"ADVANCING","AFTER","ALL","ALPHABET","ALPHABETIC_TOK","ALPHABETIC_LOWER",
"ALPHABETIC_UPPER","ALPHANUMERIC","ALPHANUMERIC_EDITED","ALSO","ALTERNATE",
"ANY","AREA","AREAS","ASSIGN","AT","AUTHOR","AUTO","BACKGROUNDCOLOR","BEFORE",
"BELL","BLANK","BLINK","BLOCK","BOTTOM","BY","CALL","CALL_CONV_C",
"CALL_CONV_STDCALL","CALL_LOADLIB","CANCEL","CENTER","CF","CH","CHAIN",
"CHAINING","CHARACTER","CHARACTERS","CLASS","CLOSE","CODE","CODE_SET",
"COLLATING","COLOR","COLUMN","COLUMNS","COMMA","COMMON","COMPUTE",
"CONFIGURATION","CONSOLE","CONTAINS","CONTENT","CONTINUE","CONTROL","CONTROLS",
"CONVERTING","CORRESPONDING","COUNT","CURRENCY","CURSOR","DATA","DATE_COMPILED",
"DATE_WRITTEN","DE","DEBUGGING","DECIMAL_POINT","DECLARATIVES","DELETE",
"DELIMITED","DELIMITER","DEPENDING","DETAIL","DISPLAY","DISPLAY_SCREEN",
"DIVIDE","DIVISION","DOWN","DUPLICATES","DYNAMIC","ELSE","END","END_ACCEPT",
"END_ADD","END_CALL","END_CALL_LOADLIB","END_CHAIN","END_COMPUTE","END_DELETE",
"END_DISPLAY","END_DIVIDE","END_EVALUATE","END_IF","END_MULTIPLY","END_OF_PAGE",
"END_PERFORM","END_READ","END_RETURN","END_REWRITE","END_SEARCH","END_START",
"END_STRINGCMD","END_SUBTRACT","END_UNSTRING","END_WRITE","ENVIRONMENT","EOL",
"EOS","ERASE","ERROR_TOK","EVALUATE","EXCEPTION","EXIT","EXTEND","EXTERNAL",
"FALSE_TOK","FD","FILE_CONTROL","FILE_ID","FILE_TOK","FILLER","FINAL","FIRST",
"FOOTING","FOR","FOREGROUNDCOLOR","FROM","FULL","FUNCTION","GENERATE","GIVING",
"GLOBAL","GO","GOBACK","GROUP","HEADING","HIGHLIGHT","HIGHVALUES",
"IDENTIFICATION","IF","IGNORE","IN","INDEXED","INDICATE","INITIALIZE",
"INITIAL_TOK","INITIATE","INPUT","INSPECT","INSTALLATION","INTO","INVALID",
"I_O","I_O_CONTROL","JUSTIFIED","KEY","LABEL","LAST","LEADING","LEFT","LENGTH",
"LIMIT","LIMITS","LINAGE","LINE","LINES","LINKAGE","LISTSEP","LOCK","LOWER",
"LOWLIGHT","LOWVALUES","LPAR","MERGE","MINUS","MODE","MOVE","MULTIPLE",
"MULTIPLY","NATIVE","NEGATIVE","NEXT","NOECHO","NOTEXCEP","NULL_TOK","NUMBER",
"NUMBERS","NUMERIC","NUMERIC_EDITED","OBJECT_COMPUTER","OCCURS","OF","OFF",
"OMITTED","ON","ONLY","OPEN","OPTIONAL","ORDER","ORGANIZATION","OTHER","OUTPUT",
"OVERFLOW_TOK","PADDING","PAGE_TOK","PAGE_COUNTER","PARAGRAPH","PERFORM","PF",
"PH","PICTURE","PLUS","POINTER","POSITION","POSITIVE","PREVIOUS","PROCEDURE",
"PROCEDURES","PROCEED","PROGRAM","PROGRAM_ID","QUOTES","RANDOM","RD","READY",
"RECORD","RECORDS","REDEFINES","REEL","REFERENCE","REFERENCES","RELATIVE",
"REMAINDER","REMOVAL","RENAMES","REPLACING","REPORT","REPORTING","REPORTS",
"REQUIRED","RESERVE","RESET","RETURN_TOK","RETURNING","REVERSEVIDEO","REWIND",
"REWRITE","RF","RH","RIGHT","ROUNDED","RUN","SAME","SCREEN","SD","SEARCH",
"SECTION","SECURE","SECURITY","SELECT","SENTENCE","SEPARATE","SEQUENCE",
"SEQUENTIAL","SET","SIGN","SIZE","SORT","SORT_MERGE","SOURCE","SOURCE_COMPUTER",
"SPACES","SPECIAL_NAMES","STANDARD","STANDARD_1","STANDARD_2","START","STATUS",
"STD_ERROR","STD_INPUT","STD_OUTPUT","STOP","STRINGCMD","SUBTRACT","SUM",
"SYNCHRONIZED","TALLYING","TAPE","TCOBPROTO1","TCOBPROTO2","TERMINATE","TEST",
"THEN","TIMES","TOKDUMMY","TOP","TRACE","TRAILING","TRUE_TOK","TYPE",
"UNDERLINE","UNIT","UNLOCK","UNSTRING","UNTIL","UP","UPDATE","UPON","UPPER",
"USAGE","USE","USING","VALUE","VALUES","VARYING","WHEN","WITH",
"WORKING_STORAGE","ZERO","PERIOD_TOK",
};
char *yyrule[] = {
"$accept : root_",
"root_ : program_sequences",
"program_sequences : program",
"program_sequences : program_sequence",
"program_sequences : program_sequence program",
"program_sequence : program end_program",
"$$1 :",
"program_sequence : program $$1 program_sequence end_program",
"program_sequence : program_sequence program end_program",
"$$2 :",
"end_program : END PROGRAM $$2 programid_string",
"program : identification_division environment_division_opt data_division_opt procedure_division_opt",
"$$3 :",
"$$4 :",
"$$5 :",
"identification_division : IDENTIFICATION DIVISION PERIOD_TOK PROGRAM_ID PERIOD_TOK $$3 programid_string $$4 programid_opts_opt PERIOD_TOK $$5 identification_division_options_opt",
"programid_string : IDSTRING_WORD",
"programid_string : IDSTRING_LITERAL",
"programid_opts_opt :",
"programid_opts_opt : is_opt INITIAL_TOK programid_program_opt",
"programid_opts_opt : is_opt COMMON programid_program_opt",
"programid_program_opt :",
"programid_program_opt : PROGRAM",
"identification_division_options_opt :",
"identification_division_options_opt : identification_division_options_opt identification_division_option",
"identification_division_option : AUTHOR PERIOD_TOK",
"identification_division_option : DATE_WRITTEN PERIOD_TOK",
"identification_division_option : DATE_COMPILED PERIOD_TOK",
"identification_division_option : INSTALLATION PERIOD_TOK",
"identification_division_option : SECURITY PERIOD_TOK",
"$$6 :",
"environment_division_opt : ENVIRONMENT DIVISION PERIOD_TOK $$6 configuration_opt input_output_opt",
"environment_division_opt :",
"configuration_opt : CONFIGURATION SECTION PERIOD_TOK configuration_section",
"configuration_opt :",
"configuration_section : configuration_section configuration_option",
"configuration_section :",
"$$7 :",
"configuration_option : SOURCE_COMPUTER PERIOD_TOK $$7 STRING debug_mode_opt PERIOD_TOK",
"$$8 :",
"configuration_option : OBJECT_COMPUTER PERIOD_TOK $$8 STRING program_collating_opt PERIOD_TOK",
"configuration_option : SPECIAL_NAMES PERIOD_TOK special_names_opt",
"configuration_option : error",
"program_collating_opt : PROGRAM collating_sequence",
"program_collating_opt :",
"collating_sequence : collating_opt SEQUENCE is_opt STRING",
"collating_opt : COLLATING",
"collating_opt :",
"debug_mode_opt : with_opt DEBUGGING MODE",
"debug_mode_opt :",
"special_names_opt :",
"special_names_opt : special_names PERIOD_TOK",
"special_names_opt : error",
"special_names : special_name",
"special_names : special_names special_name",
"special_name : switches_details_list",
"special_name : alphabet_details",
"special_name : currency_details",
"special_name : decimal_point_details",
"special_name : screen_status_details",
"special_name : cursor_details",
"special_name : special_name_class",
"currency_details : CURRENCY sign_opt is_opt CLITERAL",
"sign_opt : SIGN",
"sign_opt :",
"special_name_class : CLASS STRING is_opt special_name_class_item_list",
"special_name_class_item_list : special_name_class_item",
"special_name_class_item_list : special_name_class_item_list special_name_class_item",
"special_name_class_item : CLITERAL",
"special_name_class_item : CLITERAL THRU CLITERAL",
"decimal_point_details : DECIMAL_POINT is_opt COMMA",
"screen_status_details : DISPLAY_SCREEN STATUS is_opt STRING",
"cursor_details : CURSOR is_opt STRING",
"switches_details_list :",
"switches_details_list : switches_details_list switches_details",
"$$9 :",
"switches_details : STRING is_opt STRING $$9 switch_on_opt switch_off_opt",
"switch_on_opt : ON status_opt is_opt STRING",
"switch_on_opt :",
"switch_off_opt : OFF status_opt is_opt STRING",
"switch_off_opt :",
"status_opt : STATUS",
"status_opt :",
"alphabet_details : ALPHABET STRING is_opt alphabet_type",
"alphabet_type : NATIVE",
"alphabet_type : STANDARD_1",
"alphabet_type : STANDARD_2",
"alphabet_type : alphabet_literal_list",
"alphabet_literal_list : alphabet_literal_item",
"alphabet_literal_list : alphabet_literal_list alphabet_literal_item",
"alphabet_literal_item : without_all_literal",
"alphabet_literal_item : without_all_literal THRU without_all_literal",
"alphabet_literal_item : without_all_literal alphabet_also_list",
"alphabet_also_list : ALSO without_all_literal",
"alphabet_also_list : alphabet_also_list ALSO without_all_literal",
"input_output_opt : INPUT_OUTPUT SECTION PERIOD_TOK input_output_section",
"input_output_opt :",
"input_output_section : file_control_paragraph i_o_control_paragraph",
"input_output_section :",
"file_control_paragraph : FILE_CONTROL PERIOD_TOK file_control",
"i_o_control_paragraph :",
"i_o_control_paragraph : I_O_CONTROL PERIOD_TOK i_o_control_opt",
"file_control : file_select",
"file_control : file_control file_select",
"file_control :",
"$$10 :",
"file_select : SELECT optional_opt def_name $$10 select_clauses PERIOD_TOK",
"select_clauses : select_clauses select_clause",
"select_clauses :",
"select_clause : organization_opt is_opt organization_options",
"select_clause : ASSIGN to_opt assign_clause",
"select_clause : ACCESS mode_opt is_opt access_options",
"select_clause : file_opt STATUS is_opt strings",
"select_clause : RECORD key_opt is_opt strings",
"select_clause : RELATIVE key_opt is_opt strings",
"select_clause : ALTERNATE RECORD key_opt is_opt strings with_duplicates",
"select_clause : RESERVE NLITERAL areas_opt",
"select_clause : error",
"strings : STRING",
"strings : STRING in_of strings",
"file_opt : FILE_TOK",
"file_opt :",
"organization_opt : ORGANIZATION",
"organization_opt :",
"assign_clause : assign_clause_standard_files",
"assign_clause : assign_clause_external_opt assign_clause_device filename",
"assign_clause : assign_clause_external_opt filename",
"assign_clause : assign_clause_external_opt assign_clause_device",
"assign_clause_external_opt : EXTERNAL",
"assign_clause_external_opt :",
"assign_clause_device : DISK",
"assign_clause_device : PRINTER",
"assign_clause_standard_files : STD_INPUT",
"assign_clause_standard_files : STD_OUTPUT",
"assign_clause_standard_files : STD_ERROR",
"assign_clause_standard_files : DISPLAY",
"with_duplicates : with_opt DUPLICATES",
"with_duplicates :",
"optional_opt : OPTIONAL",
"optional_opt :",
"areas_opt : AREA",
"areas_opt : AREAS",
"areas_opt :",
"is_opt : IS",
"is_opt :",
"are_opt : ARE",
"are_opt :",
"mode_opt : MODE",
"mode_opt :",
"organization_options : INDEXED",
"organization_options : SEQUENTIAL",
"organization_options : RELATIVE",
"organization_options : LINE SEQUENTIAL",
"organization_options : anystring",
"access_options : SEQUENTIAL",
"access_options : DYNAMIC",
"access_options : RANDOM",
"access_options : anystring",
"i_o_control_opt :",
"i_o_control_opt : i_o_control_list PERIOD_TOK",
"i_o_control_list : i_o_control_clause",
"i_o_control_list : i_o_control_list i_o_control_clause",
"i_o_control_clause : i_o_control_same_clause",
"i_o_control_clause : i_o_control_multiple_file_tape_clause",
"i_o_control_same_clause : SAME same_clause_options are_opta for_opt string_list",
"same_clause_options :",
"same_clause_options : RECORD",
"same_clause_options : SORT",
"same_clause_options : SORT_MERGE",
"i_o_control_multiple_file_tape_clause : MULTIPLE FILE_TOK tape_opt contains_opt i_o_control_multiple_file_list",
"i_o_control_multiple_file_list : i_o_control_multiple_file",
"i_o_control_multiple_file_list : i_o_control_multiple_file_list i_o_control_multiple_file",
"i_o_control_multiple_file : STRING i_o_control_multiple_file_position_opt",
"i_o_control_multiple_file_position_opt :",
"i_o_control_multiple_file_position_opt : POSITION integer",
"tape_opt : TAPE",
"tape_opt :",
"are_opta : AREA",
"are_opta :",
"for_opt : FOR",
"for_opt :",
"string_list : STRING",
"string_list : string_list STRING",
"string_list : error",
"name_list : variable",
"name_list : name_list variable",
"name_list : error",
"$$11 :",
"data_division_opt : DATA DIVISION PERIOD_TOK $$11 file_section_opt working_storage_opt linkage_section_opt report_section_opt screen_section_opt",
"data_division_opt :",
"$$12 :",
"file_section_opt : FILE_TOK SECTION PERIOD_TOK $$12 file_section",
"file_section_opt :",
"$$13 :",
"working_storage_opt : WORKING_STORAGE SECTION PERIOD_TOK $$13 working_storage_section",
"working_storage_opt :",
"$$14 :",
"linkage_section_opt : LINKAGE SECTION PERIOD_TOK $$14 linkage_section",
"linkage_section_opt :",
"report_section_opt : REPORT SECTION PERIOD_TOK report_sections",
"report_section_opt :",
"report_sections : report_sections report_section",
"report_sections :",
"$$15 :",
"$$16 :",
"$$17 :",
"report_section : RD $$15 STRING $$16 report_controls PERIOD_TOK $$17 report_description",
"report_controls :",
"report_controls : report_controls report_control",
"report_control : is_opt GLOBAL",
"report_control : CODE gliteral",
"report_control : report_controls_control",
"report_control : report_controls_page",
"report_controls_control : control_is_are final_opt report_break_list",
"report_controls_page : PAGE_TOK limit_is_are_opt integer line_lines_opt heading_opt first_detail_opt last_detail_opt footing_opt",
"heading_opt :",
"heading_opt : HEADING is_opt integer",
"line_lines_opt : lines_opt",
"line_lines_opt : LINE",
"lines_opt :",
"lines_opt : LINES",
"control_is_are : CONTROL is_opt",
"control_is_are : CONTROLS are_opt",
"limit_is_are_opt :",
"limit_is_are_opt : LIMIT IS",
"limit_is_are_opt : LIMITS ARE",
"footing_opt :",
"footing_opt : FOOTING is_opt integer",
"last_detail_opt :",
"last_detail_opt : LAST DETAIL is_opt integer",
"first_detail_opt :",
"first_detail_opt : FIRST DETAIL is_opt integer",
"final_opt :",
"final_opt : FINAL",
"report_break_list :",
"report_break_list : report_break_list name",
"report_description : report_item",
"report_description : report_description report_item",
"$$18 :",
"report_item : integer def_name_opt $$18 report_clauses PERIOD_TOK",
"report_clauses : report_clause",
"report_clauses : report_clauses report_clause",
"report_clause : report_clause_line",
"report_clause : report_clause_next_group",
"report_clause : report_clause_type",
"report_clause : report_clause_usage_display",
"report_clause : report_clause_picture",
"report_clause : report_clause_sign_is",
"report_clause : report_clause_justified",
"report_clause : report_clause_blank_zero",
"report_clause : report_clause_column",
"report_clause : report_clause_svs",
"report_clause : report_clause_group_indicate",
"report_clause_type : TYPE is_opt report_clause_type2",
"report_clause_type2 : REPORT HEADING",
"report_clause_type2 : PAGE_TOK HEADING",
"$$19 :",
"report_clause_type2 : CONTROL HEADING $$19 name_final_opt",
"report_clause_type2 : DETAIL",
"$$20 :",
"report_clause_type2 : CONTROL FOOTING $$20 name_final_opt",
"report_clause_type2 : PAGE_TOK FOOTING",
"report_clause_type2 : REPORT FOOTING",
"report_clause_type2 : RH",
"report_clause_type2 : PH",
"$$21 :",
"report_clause_type2 : CH $$21 name_final_opt",
"report_clause_type2 : DE",
"$$22 :",
"report_clause_type2 : CF $$22 name_final_opt",
"report_clause_type2 : PF",
"report_clause_type2 : RF",
"report_clause_sign_is : SIGN is_opt leading_trailing SEPARATE character_opt",
"report_clause_sign_is : leading_trailing SEPARATE character_opt",
"$$23 :",
"report_clause_picture : PICTURE $$23 is_opt picture",
"report_clause_usage_display : USAGE is_opt DISPLAY",
"report_clause_usage_display : DISPLAY",
"report_clause_justified : JUSTIFIED right_opt",
"report_clause_next_group : NEXT GROUP is_opt integer_on_next_page",
"report_clause_line : report_clause_line_is integer ON NEXT PAGE_TOK",
"report_clause_line : report_clause_line_is integer NEXT PAGE_TOK",
"report_clause_line : report_clause_line_is integer",
"report_clause_line : report_clause_line_is PLUS integer",
"report_clause_line_is : LINE is_are_opt",
"report_clause_line_is : LINE NUMBER is_opt",
"report_clause_line_is : LINE NUMBERS are_opt",
"report_clause_line_is : LINES are_opt",
"report_clause_column : report_clause_column_is integer",
"report_clause_column_is : COLUMN report_clause_column_orientation is_are_opt",
"report_clause_column_is : COLUMN NUMBER report_clause_column_orientation is_opt",
"report_clause_column_is : COLUMN NUMBERS report_clause_column_orientation are_opt",
"report_clause_column_is : COLUMNS report_clause_column_orientation are_opt",
"report_clause_column_orientation :",
"report_clause_column_orientation : LEFT",
"report_clause_column_orientation : CENTER",
"report_clause_column_orientation : RIGHT",
"is_are_opt :",
"is_are_opt : IS",
"is_are_opt : ARE",
"$$24 :",
"report_clause_svs : SOURCE $$24 is_opt gname_page_counter",
"report_clause_svs : VALUE is_opt literal",
"$$25 :",
"$$26 :",
"report_clause_svs : SUM $$25 gname_list $$26 upon_opt reset_opt",
"gname_page_counter : gname",
"gname_page_counter : PAGE_COUNTER",
"report_clause_group_indicate :",
"report_clause_group_indicate : GROUP indicate_opt",
"report_clause_blank_zero : BLANK when_opt ZERO",
"indicate_opt :",
"indicate_opt : INDICATE",
"upon_opt :",
"upon_opt : UPON gname_list",
"reset_opt :",
"reset_opt : RESET gname",
"reset_opt : RESET FINAL",
"number_opt :",
"number_opt : NUMBER",
"leading_trailing : LEADING",
"leading_trailing : TRAILING",
"right_opt :",
"right_opt : RIGHT",
"name_final_opt : gname",
"name_final_opt : FINAL",
"integer_on_next_page : integer",
"integer_on_next_page : PLUS integer",
"integer_on_next_page : NEXT PAGE_TOK",
"of_opt : OF",
"of_opt :",
"$$27 :",
"screen_section_opt : SCREEN SECTION PERIOD_TOK $$27 screen_section",
"screen_section_opt :",
"screen_section : screen_section screen_item",
"screen_section :",
"$$28 :",
"screen_item : integer def_name_opt $$28 screen_clauses PERIOD_TOK",
"$$29 :",
"screen_clauses : screen_clauses LINE $$29 number_is_opt plus_minus_opt name_or_lit",
"$$30 :",
"screen_clauses : screen_clauses COLUMN $$30 number_is_opt plus_minus_opt name_or_lit",
"screen_clauses : screen_clauses with_opt screen_attrib",
"$$31 :",
"screen_clauses : screen_clauses with_opt FOREGROUNDCOLOR $$31 name_or_lit",
"$$32 :",
"screen_clauses : screen_clauses with_opt BACKGROUNDCOLOR $$32 name_or_lit",
"$$33 :",
"screen_clauses : screen_clauses with_opt COLOR $$33 name_or_lit",
"screen_clauses : screen_clauses screen_source_destination",
"screen_clauses : screen_clauses value_is_are gliteral",
"screen_clauses : screen_clauses pictures",
"$$34 :",
"screen_clauses : screen_clauses SIZE $$34 name_or_lit",
"screen_clauses :",
"$$35 :",
"screen_source_destination : USING $$35 name_or_lit",
"$$36 :",
"screen_source_destination : FROM $$36 name_or_lit screen_to_name",
"$$37 :",
"screen_source_destination : TO $$37 name",
"screen_to_name :",
"screen_to_name : TO name",
"screen_attrib : BLANK SCREEN",
"screen_attrib : BLANK LINE",
"screen_attrib : ERASE EOL",
"screen_attrib : ERASE EOS",
"screen_attrib : ERASE",
"screen_attrib : with_opt BELL",
"screen_attrib : sign_clause",
"screen_attrib : FULL",
"screen_attrib : REQUIRED",
"screen_attrib : SECURE",
"screen_attrib : AUTO",
"screen_attrib : JUSTIFIED RIGHT",
"screen_attrib : JUSTIFIED LEFT",
"screen_attrib : BLINK",
"screen_attrib : REVERSEVIDEO",
"screen_attrib : UNDERLINE",
"screen_attrib : LOWLIGHT",
"screen_attrib : HIGHLIGHT",
"screen_attrib : BLANK when_opt ZERO",
"screen_attrib : with_opt NOECHO",
"screen_attrib : with_opt UPDATE",
"screen_attrib : with_opt NO ADVANCING",
"screen_attrib : UPPER",
"screen_attrib : LOWER",
"sign_clause : sign_is_opt LEADING separate_opt",
"sign_clause : sign_is_opt TRAILING separate_opt",
"separate_opt : SEPARATE character_opt",
"separate_opt :",
"character_opt : CHARACTER",
"character_opt :",
"sign_is_opt : SIGN is_opt",
"sign_is_opt : is_opt",
"plus_minus_opt : PLUS",
"plus_minus_opt : '+'",
"plus_minus_opt : MINUS",
"plus_minus_opt : '-'",
"plus_minus_opt :",
"number_is_opt : NUMBER is_opt",
"number_is_opt :",
"$$38 :",
"$$39 :",
"$$40 :",
"file_section : file_section FD $$38 STRING $$39 file_description_fd_clauses PERIOD_TOK $$40 file_description",
"$$41 :",
"$$42 :",
"$$43 :",
"file_section : file_section SD $$41 STRING $$42 file_description_sd_clauses PERIOD_TOK $$43 file_description",
"file_section : error",
"file_section :",
"file_description : field_description",
"file_description : file_description field_description",
"$$44 :",
"field_description : integer def_name_opt $$44 data_clauses PERIOD_TOK",
"data_clauses :",
"data_clauses : data_clauses data_clause",
"data_clauses : data_clauses redefines_clause",
"$$45 :",
"redefines_clause : REDEFINES $$45 redefines_var",
"redefines_var : VARIABLE",
"redefines_var : SUBSCVAR",
"data_clause : array_options",
"data_clause : pictures",
"data_clause : usage_option",
"data_clause : sign_clause",
"data_clause : value_option",
"data_clause : SYNCHRONIZED sync_options",
"data_clause : JUSTIFIED sync_options",
"data_clause : is_opt EXTERNAL",
"data_clause : is_opt GLOBAL",
"data_clause : BLANK when_opt ZERO",
"$$46 :",
"data_clause : RENAMES $$46 variable thru_gname_opt",
"sync_options :",
"sync_options : LEFT",
"sync_options : RIGHT",
"thru_gname_opt :",
"thru_gname_opt : THRU variable",
"$$47 :",
"array_options : OCCURS integer times_opt $$47 indexed_by_opt",
"$$48 :",
"$$49 :",
"array_options : OCCURS integer TO integer times_opt DEPENDING $$48 on_opt gname $$49 indexed_by_opt",
"key_is_opt : DIRECTION key_opt is_opt STRING",
"key_is_opt :",
"indexed_by_opt : key_is_opt INDEXED by_opt index_name_list",
"indexed_by_opt :",
"index_name_list : def_name",
"index_name_list : index_name_list def_name",
"usage_option : usage_opt is_opt usage",
"usage : USAGENUM",
"usage : DISPLAY",
"usage : POINTER",
"value_option : value_is_are value_list",
"value_is_are : VALUE is_opt",
"value_is_are : VALUES are_opt",
"value_list : value",
"value_list : value_list comma_opt value",
"value : gliteral",
"value : gliteral THRU gliteral",
"$$50 :",
"pictures : PICTURE $$50 is_opt picture",
"picture :",
"picture : picture pic_elem",
"pic_elem : CHAR multiplier_opt",
"multiplier_opt :",
"multiplier_opt : MULTIPLIER",
"file_description_fd_clauses :",
"file_description_fd_clauses : file_description_fd_clauses file_description_fd_clause",
"file_description_sd_clauses :",
"file_description_sd_clauses : file_description_sd_clauses file_description_sd_clause",
"file_description_fd_clause : is_opt EXTERNAL",
"file_description_fd_clause : is_opt GLOBAL",
"file_description_fd_clause : file_description_clause_block",
"file_description_fd_clause : file_description_clause_record",
"file_description_fd_clause : file_description_clause_label",
"file_description_fd_clause : file_description_clause_value",
"file_description_fd_clause : file_description_clause_data",
"file_description_fd_clause : file_description_clause_report",
"file_description_fd_clause : file_description_clause_linage",
"file_description_fd_clause : file_description_clause_code_set",
"file_description_sd_clause : file_description_clause_record",
"file_description_sd_clause : file_description_clause_data",
"file_description_clause_block : BLOCK contains_opt integer to_integer_opt chars_or_recs_opt",
"file_description_clause_record : RECORD contains_opt nliteral to_rec_varying_opt character_opts",
"file_description_clause_record : RECORD is_opt VARYING in_opt size_opt from_rec_varying_opt to_rec_varying_opt character_opts depend_rec_varying_opt",
"file_description_clause_label : LABEL record_is_are std_or_omitt",
"file_description_clause_value : VALUE OF FILE_ID is_opt filename",
"file_description_clause_data : DATA record_is_are var_strings",
"file_description_clause_report : report_is_are STRING",
"file_description_clause_code_set : CODE_SET is_opt STRING",
"file_description_clause_linage : LINAGE is_opt data_name lines_opt file_description_clause_linage_footing file_description_clause_linage_top file_description_clause_linage_bottom",
"file_description_clause_linage_footing :",
"file_description_clause_linage_footing : with_opt FOOTING at_opt data_name",
"file_description_clause_linage_top :",
"file_description_clause_linage_top : lines_at_opt TOP data_name",
"file_description_clause_linage_bottom :",
"file_description_clause_linage_bottom : lines_at_opt BOTTOM data_name",
"lines_at_opt :",
"lines_at_opt : LINES",
"lines_at_opt : LINES AT",
"lines_at_opt : AT",
"report_is_are : REPORT is_opt",
"report_is_are : REPORTS are_opt",
"var_strings : STRING",
"var_strings : var_strings STRING",
"chars_or_recs_opt :",
"chars_or_recs_opt : CHARACTERS",
"chars_or_recs_opt : RECORDS",
"to_integer_opt :",
"to_integer_opt : TO integer",
"depend_rec_varying_opt :",
"depend_rec_varying_opt : DEPENDING on_opt STRING",
"from_rec_varying_opt :",
"from_rec_varying_opt : from_opt nliteral",
"from_opt : FROM",
"from_opt :",
"to_rec_varying_opt :",
"to_rec_varying_opt : TO nliteral",
"record_is_are : RECORD is_opt",
"record_is_are : RECORDS are_opt",
"std_or_omitt : STANDARD",
"std_or_omitt : OMITTED",
"usage_opt :",
"usage_opt : USAGE",
"times_opt :",
"times_opt : TIMES",
"when_opt :",
"when_opt : WHEN",
"contains_opt :",
"contains_opt : CONTAINS",
"character_opts :",
"character_opts : CHARACTERS",
"order_opt :",
"order_opt : ORDER",
"data_opt :",
"data_opt : DATA",
"working_storage_section : working_storage_section field_description",
"working_storage_section :",
"linkage_section :",
"linkage_section : linkage_section field_description",
"$$51 :",
"$$52 :",
"procedure_division_opt : PROCEDURE DIVISION $$51 procedure_division_using_chaining_opt procedure_division_returning_opt PERIOD_TOK $$52 declaratives_opt procedure_list",
"procedure_division_opt :",
"$$53 :",
"declaratives_opt : DECLARATIVES PERIOD_TOK $$53 declaratives_procedure declaratives_procedures END DECLARATIVES PERIOD_TOK",
"declaratives_opt :",
"declaratives_procedures : declaratives_decl",
"declaratives_procedures : declaratives_procedures declaratives_decl",
"$$54 :",
"declaratives_procedure : procedure_section $$54 use_statements",
"declaratives_procedure : error",
"declaratives_decl : declaratives_procedure",
"declaratives_decl : paragraph",
"$$55 :",
"declaratives_decl : $$55 statements PERIOD_TOK",
"$$56 :",
"declaratives_decl : error $$56 PERIOD_TOK",
"use_statements : use_exception",
"use_statements : use_debugging",
"use_statements : use_reporting",
"use_exception : USE use_global_opt AFTER use_exception_error PROCEDURE on_opt use_exception_option PERIOD_TOK",
"use_exception : error",
"use_exception_error : EXCEPTION",
"use_exception_error : ERROR_TOK",
"use_exception_error : STANDARD EXCEPTION",
"use_exception_error : STANDARD ERROR_TOK",
"use_exception_error : error",
"use_exception_option : use_exception_option_names",
"use_exception_option : open_mode",
"use_exception_option_names : name",
"use_exception_option_names : use_exception_option_names comma_opt name",
"use_reporting : USE use_global_opt BEFORE REPORTING name",
"use_debugging : USE for_opt DEBUGGING on_opt use_debugging_options",
"use_debugging_options : use_debugging_options_procedure_names",
"use_debugging_options : ALL PROCEDURES",
"use_debugging_options_procedure_names : name",
"use_debugging_options_procedure_names : use_debugging_options_procedure_names name",
"use_global_opt :",
"use_global_opt : GLOBAL",
"procedure_list :",
"procedure_list : procedure_list procedure_decl",
"procedure_decl : procedure_section",
"procedure_decl : paragraph",
"$$57 :",
"procedure_decl : $$57 statements PERIOD_TOK",
"$$58 :",
"procedure_decl : error $$58 PERIOD_TOK",
"procedure_decl : PERIOD_TOK",
"procedure_section : LABELSTR SECTION PERIOD_TOK",
"paragraph : LABELSTR dot_or_eos",
"dot_or_eos : '.'",
"dot_or_eos : PERIOD_TOK",
"statement_list : statements",
"statements : statement",
"statements : statements statement",
"statement : move_statement",
"statement : initialize_statement",
"statement : compute_statement",
"statement : add_statement",
"statement : subtract_statement",
"statement : multiply_statement",
"statement : divide_statement",
"statement : accept_statement",
"statement : display_statement",
"statement : open_statement",
"statement : close_statement",
"statement : read_statement",
"statement : return_statement",
"statement : release_statement",
"statement : write_statement",
"statement : rewrite_statement",
"statement : delete_statement",
"statement : start_statement",
"statement : perform_statement",
"statement : goto_statement",
"statement : exit_statement",
"statement : stop_statement",
"statement : call_statement",
"statement : call_loadlib_statement",
"statement : chain_statement",
"statement : set_statement",
"statement : sort_statement",
"statement : merge_statement",
"statement : inspect_statement",
"statement : string_statement",
"statement : unstring_statement",
"statement : initiate_statement",
"statement : generate_statement",
"statement : terminate_statement",
"statement : proto_statement",
"statement : trace_statement",
"statement : goback_statement",
"statement : cancel_statement",
"statement : unlock_statement",
"statement : if_statement",
"statement : evaluate_statement",
"statement : search_statement",
"statement : CONTINUE",
"perform_statement : PERFORM perform_options",
"$$59 :",
"if_statement : if_part $$59 end_if_opt",
"$$60 :",
"$$61 :",
"if_statement : if_part ELSE $$60 conditional_statement $$61 end_if_opt",
"search_statement : SEARCH search end_search_opt",
"search_statement : SEARCH ALL search_all end_search_opt",
"$$62 :",
"$$63 :",
"evaluate_statement : EVALUATE $$62 selection_subject_set $$63 when_case_list end_evaluate_or_eos",
"end_evaluate_or_eos : END_EVALUATE",
"end_evaluate_or_eos : PERIOD_TOK",
"$$64 :",
"selection_subject_set : $$64 selection_subject",
"$$65 :",
"selection_subject_set : selection_subject_set ALSO $$65 selection_subject",
"selection_subject : expr",
"selection_subject : condition",
"selection_subject : TRUE_TOK",
"selection_subject : FALSE_TOK",
"$$66 :",
"$$67 :",
"when_case_list : WHEN $$66 $$67 when_case sentence_or_nothing",
"$$68 :",
"$$69 :",
"$$70 :",
"when_case_list : when_case_list WHEN $$68 $$69 when_case $$70 sentence_or_nothing",
"$$71 :",
"when_case : $$71 selection_object",
"$$72 :",
"when_case : when_case ALSO $$72 selection_object",
"when_case : OTHER",
"selection_object : ANY",
"selection_object : TRUE_TOK",
"selection_object : FALSE_TOK",
"selection_object : not_opt expr",
"selection_object : not_opt expr THRU expr",
"selection_object : not_opt cond_name",
"sentence_or_nothing :",
"sentence_or_nothing : conditional_statement",
"$$73 :",
"if_part : IF condition $$73 end_then_opt conditional_statement",
"$$74 :",
"conditional_statement : $$74 statement_list",
"$$75 :",
"conditional_statement : $$75 NEXT SENTENCE",
"not_opt :",
"not_opt : NOT",
"end_if_opt :",
"end_if_opt : END_IF",
"end_then_opt :",
"end_then_opt : THEN",
"$$76 :",
"$$77 :",
"$$78 :",
"search : variable_indexed $$76 search_varying_opt $$77 search_at_end $$78 search_when_list",
"$$79 :",
"$$80 :",
"search_all : variable_indexed $$79 search_at_end $$80 search_all_when_list",
"search_varying_opt : VARYING variable",
"search_varying_opt :",
"$$81 :",
"search_at_end : at_opt END $$81 statement_list",
"search_at_end :",
"search_when_list : search_when",
"search_when_list : search_when_list search_when",
"$$82 :",
"search_when : WHEN search_when_conditional $$82 search_when_statement",
"search_when_statement : statement_list",
"search_when_statement : NEXT SENTENCE",
"search_when_conditional : name_or_lit extended_cond_op name_or_lit",
"search_all_when_list : search_all_when",
"search_all_when_list : search_all_when_list search_all_when",
"$$83 :",
"$$84 :",
"search_all_when : WHEN $$83 search_all_when_conditional $$84 search_all_when_statement",
"search_all_when_statement : statement_list",
"search_all_when_statement : NEXT SENTENCE",
"search_all_when_conditional : variable is_opt CONDITIONAL to_opt variable",
"search_all_when_conditional : variable is_opt CONDITIONAL to_opt literal",
"$$85 :",
"search_all_when_conditional : search_all_when_conditional AND $$85 search_all_when_conditional",
"end_search_opt :",
"end_search_opt : END_SEARCH",
"unlock_statement : UNLOCK name",
"proto_statement : TCOBPROTO1 gname",
"proto_statement : TCOBPROTO2 gname gname",
"trace_statement : READY TRACE",
"trace_statement : RESET TRACE",
"initiate_statement : INITIATE name",
"generate_statement : GENERATE name",
"terminate_statement : TERMINATE name",
"cancel_statement : CANCEL gname",
"cancel_statement : CANCEL ALL",
"merge_statement : MERGE name sort_keys sort_collating_opt merge_using sort_output",
"merge_using : USING sort_file_list",
"sort_statement : SORT name sort_keys sort_duplicates_opt sort_collating_opt sort_input sort_output",
"sort_keys : sort_key",
"sort_keys : sort_keys sort_key",
"sort_key : on_opt DIRECTION key_opt sort_keys_names",
"sort_keys_names : name",
"sort_keys_names : sort_keys_names name",
"sort_duplicates_opt :",
"sort_duplicates_opt : with_opt DUPLICATES in_opt order_opt",
"sort_collating_opt :",
"sort_collating_opt : collating_sequence",
"sort_input : INPUT PROCEDURE is_opt perform_range",
"sort_input : USING sort_file_list",
"sort_output : OUTPUT PROCEDURE is_opt perform_range",
"sort_output : GIVING sort_file_list",
"sort_file_list : name",
"sort_file_list : sort_file_list name",
"move_statement : MOVE gname TO name_var_list",
"move_statement : MOVE CORRESPONDING name_var TO name_var",
"move_statement : MOVE LENGTH OF gname TO name_var",
"move_statement : MOVE gname TO",
"initialize_statement : INITIALIZE gname_list initialize_replacing_opt",
"initialize_statement : INITIALIZE",
"initialize_replacing_opt :",
"initialize_replacing_opt : REPLACING initialize_replacing_lists",
"initialize_replacing_lists : initialize_replacing_list",
"initialize_replacing_lists : initialize_replacing_lists initialize_replacing_list",
"initialize_replacing_list : initialize_type_list data_opt BY gname",
"initialize_type_list : ALPHABETIC_TOK",
"initialize_type_list : ALPHANUMERIC",
"initialize_type_list : NUMERIC",
"initialize_type_list : ALPHANUMERIC_EDITED",
"initialize_type_list : NUMERIC_EDITED",
"compute_statement : COMPUTE compute_body end_compute_opt",
"compute_statement : COMPUTE",
"compute_body : var_list_name CONDITIONAL expr on_size_error_opt",
"end_compute_opt :",
"end_compute_opt : END_COMPUTE",
"add_statement : ADD add_body end_add_opt",
"add_statement : ADD",
"add_body : var_list_gname TO var_list_name on_size_error_opt",
"add_body : var_list_gname add_to_opt GIVING var_list_name on_size_error_opt",
"add_body : CORRESPONDING var_list_gname TO var_list_name rounded_opt on_size_error_opt",
"add_to_opt :",
"add_to_opt : TO gname",
"end_add_opt :",
"end_add_opt : END_ADD",
"subtract_statement : SUBTRACT subtract_body end_subtract_opt",
"subtract_statement : SUBTRACT",
"subtract_body : var_list_gname FROM var_list_name on_size_error_opt",
"subtract_body : var_list_gname FROM gname GIVING var_list_name on_size_error_opt",
"subtract_body : CORRESPONDING var_list_gname FROM var_list_name rounded_opt on_size_error_opt",
"end_subtract_opt :",
"end_subtract_opt : END_SUBTRACT",
"multiply_statement : MULTIPLY multiply_body end_multiply_opt",
"multiply_statement : MULTIPLY",
"multiply_body : gname BY gname GIVING var_list_name on_size_error_opt",
"multiply_body : gname BY var_list_name on_size_error_opt",
"end_multiply_opt :",
"end_multiply_opt : END_MULTIPLY",
"divide_statement : DIVIDE divide_body end_divide_opt",
"divide_statement : DIVIDE",
"divide_body : gname BY gname GIVING var_list_name on_size_error_opt",
"divide_body : gname BY gname GIVING name rounded_opt REMAINDER name on_size_error_opt",
"divide_body : gname INTO gname GIVING name rounded_opt REMAINDER name on_size_error_opt",
"divide_body : gname INTO gname GIVING var_list_name on_size_error_opt",
"divide_body : gname INTO var_list_name on_size_error_opt",
"end_divide_opt :",
"end_divide_opt : END_DIVIDE",
"accept_statement : accept_hardware",
"accept_statement : accept_chronological",
"accept_statement : accept_screen",
"accept_statement : ACCEPT",
"$$86 :",
"accept_hardware : ACCEPT name accept_from_opt $$86 on_exception_opt end_accept_opt",
"accept_hardware : ACCEPT name FROM INKEY end_accept_opt",
"accept_hardware : ACCEPT name FROM INPUT STATUS end_accept_opt",
"accept_hardware : ACCEPT name FROM CMD_LINE end_accept_opt",
"accept_hardware : ACCEPT name FROM ENVIRONMENT_VARIABLE accept_hardware_env_var end_accept_opt",
"accept_hardware_env_var : name",
"accept_hardware_env_var : CLITERAL",
"accept_from_opt :",
"accept_from_opt : FROM STD_INPUT",
"accept_from_opt : FROM CONSOLE",
"on_exception_opt :",
"$$87 :",
"on_exception_opt : on_opt EXCEPTION variable $$87 statement_list",
"accept_chronological : ACCEPT name FROM DATE_TIME end_accept_opt",
"accept_screen : ACCEPT name accept_options end_accept_opt",
"$$88 :",
"$$89 :",
"$$90 :",
"accept_screen : ACCEPT name accept_options on_opt EXCEPTION $$88 variable $$89 statement_list $$90 end_accept_opt",
"end_accept_opt :",
"end_accept_opt : END_ACCEPT",
"display_statement : display_line",
"display_statement : display_screen",
"display_statement : DISPLAY",
"display_line : DISPLAY display_varlist display_upon display_line_options end_display_opt",
"display_screen : DISPLAY display_varlist accept_display_options end_display_opt",
"display_varlist : gname",
"display_varlist : display_varlist sep_opt gname",
"display_upon : UPON CONSOLE",
"display_upon : UPON STD_OUTPUT",
"display_upon : UPON STD_ERROR",
"display_line_options :",
"display_line_options : display_line_options with_opt NO ADVANCING",
"display_line_options : display_line_options with_opt ERASE",
"display_line_options : display_line_options with_opt ERASE EOS",
"display_line_options : display_line_options with_opt ERASE EOL",
"display_line_options : display_line_options with_opt ERASE SCREEN",
"end_display_opt :",
"end_display_opt : END_DISPLAY",
"scr_line : LINE number_opt expr",
"scr_position : COLUMN number_opt expr",
"scr_position : POSITION expr",
"scr_line_position : AT NLITERAL",
"scr_line_position : AT variable",
"accept_options : accept_display_option",
"accept_options : accept_options accept_display_option",
"accept_display_options :",
"accept_display_options : accept_display_options accept_display_option",
"accept_display_option : with_opt screen_attrib",
"accept_display_option : scr_line",
"accept_display_option : scr_position",
"accept_display_option : scr_line_position",
"open_statement : OPEN open_options",
"open_statement : OPEN",
"open_options : open_mode open_varlist",
"open_options : open_options open_mode open_varlist",
"open_mode : INPUT",
"open_mode : I_O",
"open_mode : OUTPUT",
"open_mode : EXTEND",
"open_mode : error",
"open_varlist : name",
"open_varlist : open_varlist sep_opt name",
"close_statement : CLOSE close_files",
"close_statement : CLOSE",
"close_files : close_file",
"close_files : close_files sep_opt close_file",
"close_file : name close_options_opt",
"close_options_opt : close_options",
"close_options_opt : with_lock_opt",
"close_options : with_opt NO REWIND",
"close_options : REEL",
"close_options : UNIT",
"close_options : REEL for_opt REMOVAL",
"close_options : UNIT for_opt REMOVAL",
"with_lock_opt : with_opt LOCK",
"with_lock_opt : with_opt IGNORE LOCK",
"with_lock_opt :",
"return_statement : RETURN_TOK return_body end_return_opt",
"return_statement : RETURN_TOK",
"return_body : name record_opt read_into_opt",
"return_body : name record_opt read_into_opt read_at_end_opt",
"read_statement : READ read_body end_read_opt",
"read_statement : READ",
"read_body : name read_next_opt record_opt read_into_opt with_lock_opt read_key_opt",
"read_body : name read_next_opt record_opt read_into_opt with_lock_opt read_key_opt read_at_end_opt",
"read_body : name read_next_opt record_opt read_into_opt with_lock_opt read_key_opt read_invalid_key_opt",
"read_next_opt :",
"read_next_opt : NEXT",
"read_next_opt : PREVIOUS",
"read_into_opt :",
"read_into_opt : INTO name",
"read_key_opt :",
"read_key_opt : KEY is_opt name",
"read_at_end_opt : NOT at_opt on_end",
"read_at_end_opt : AT on_end",
"read_at_end_opt : on_end",
"$$91 :",
"read_at_end_opt : AT on_end NOT at_opt $$91 on_end",
"$$92 :",
"read_at_end_opt : on_end NOT at_opt $$92 on_end",
"$$93 :",
"on_end : END $$93 statement_list",
"read_invalid_key_opt : read_invalid_key",
"read_invalid_key_opt : read_not_invalid_key",
"read_invalid_key_opt : read_invalid_key read_not_invalid_key",
"$$94 :",
"read_invalid_key : INVALID key_opt $$94 statement_list",
"$$95 :",
"read_not_invalid_key : NOT INVALID key_opt $$95 statement_list",
"end_read_opt :",
"end_read_opt : END_READ",
"end_return_opt :",
"end_return_opt : END_RETURN",
"release_statement : RELEASE name release_from_opt",
"release_from_opt :",
"release_from_opt : FROM gname",
"$$96 :",
"write_statement : WRITE name write_from_opt write_options $$96 invalid_key_opt end_write_opt",
"write_from_opt :",
"write_from_opt : FROM gname",
"write_options :",
"write_options : before_after advancing_opt gname line_lines_opt",
"write_options : before_after advancing_opt PAGE_TOK",
"end_write_opt :",
"end_write_opt : END_WRITE",
"$$97 :",
"rewrite_statement : REWRITE name write_from_opt $$97 invalid_key_opt end_rewrite_opt",
"end_rewrite_opt :",
"end_rewrite_opt : END_REWRITE",
"$$98 :",
"delete_statement : DELETE name record_opt $$98 invalid_key_opt end_delete_opt",
"end_delete_opt :",
"end_delete_opt : END_DELETE",
"$$99 :",
"start_statement : START start_body invalid_key_opt $$99 end_start_opt",
"start_body : name",
"start_body : name KEY is_opt cond_op name",
"end_start_opt :",
"end_start_opt : END_START",
"goto_statement : GO to_opt goto_label",
"goto_statement : GO to_opt goto_label_list DEPENDING on_opt variable",
"goto_label : label",
"goto_label_list : label",
"goto_label_list : goto_label_list label",
"goto_label_list : goto_label_list LISTSEP label",
"$$100 :",
"$$101 :",
"$$102 :",
"$$103 :",
"$$104 :",
"call_statement : CALL $$100 call_convention_opt gname using_options returning_options $$101 $$102 $$103 on_exception_or_overflow on_not_exception $$104 end_call_opt",
"call_statement : CALL",
"call_convention_opt :",
"call_convention_opt : CALL_CONV_C",
"call_convention_opt : CALL_CONV_STDCALL",
"$$105 :",
"call_loadlib_statement : CALL_LOADLIB gname $$105 end_call_loadlib_opt",
"call_loadlib_statement : CALL_LOADLIB",
"end_call_loadlib_opt : END_CALL_LOADLIB",
"end_call_loadlib_opt :",
"$$106 :",
"$$107 :",
"$$108 :",
"$$109 :",
"chain_statement : CHAIN $$106 gname using_options $$107 $$108 on_exception_or_overflow $$109 end_chain_opt",
"chain_statement : CHAIN",
"exit_statement : EXIT",
"exit_statement : EXIT PARAGRAPH",
"exit_statement : EXIT PROGRAM",
"stop_statement : STOP RUN",
"stop_statement : STOP stop_literal",
"stop_literal : CLITERAL",
"stop_literal : NLITERAL",
"goback_statement : GOBACK",
"var_list_name : name rounded_opt sep_opt",
"var_list_name : var_list_name name rounded_opt sep_opt",
"var_list_gname : gname sep_opt",
"var_list_gname : var_list_gname gname sep_opt",
"rounded_opt :",
"rounded_opt : ROUNDED",
"on_size_error_opt :",
"on_size_error_opt : NOT on_opt SIZE on_size_error",
"on_size_error_opt : on_opt SIZE on_size_error",
"$$110 :",
"on_size_error_opt : on_opt SIZE on_size_error NOT on_opt SIZE $$110 on_size_error",
"$$111 :",
"on_size_error : ERROR_TOK $$111 statement_list",
"size_opt :",
"size_opt : SIZE",
"end_call_opt :",
"end_call_opt : END_CALL",
"end_chain_opt :",
"end_chain_opt : END_CHAIN",
"set_statement : SET set_list",
"set_list : set_target TO address_of_opt set_variable_or_nlit",
"set_list : set_target UP BY var_or_nliteral",
"set_list : set_target DOWN BY var_or_nliteral",
"set_list : address_of_opt variable TO address_of_opt set_variable",
"set_target : name_list",
"set_target : cond_name",
"set_variable : variable",
"set_variable : NULL_TOK",
"set_variable_or_nlit : name_or_lit",
"set_variable_or_nlit : ON",
"set_variable_or_nlit : OFF",
"set_variable_or_nlit : NULL_TOK",
"set_variable_or_nlit : TRUE_TOK",
"address_of_opt :",
"address_of_opt : ADDRESS of_opt",
"$$112 :",
"string_statement : STRINGCMD string_from_list INTO name string_with_pointer $$112 on_overflow_opt end_stringcmd_opt",
"$$113 :",
"unstring_statement : UNSTRING name unstring_delimited INTO unstring_destinations string_with_pointer unstring_tallying $$113 on_overflow_opt end_unstring_opt",
"unstring_delimited : DELIMITED by_opt unstring_delimited_vars",
"unstring_delimited :",
"unstring_delimited_vars : all_opt gname",
"unstring_delimited_vars : unstring_delimited_vars OR all_opt gname",
"unstring_destinations : unstring_dest_var",
"unstring_destinations : unstring_destinations sep_opt unstring_dest_var",
"unstring_dest_var : name unstring_delim_opt unstring_count_opt",
"unstring_delim_opt :",
"unstring_delim_opt : DELIMITER in_opt name",
"unstring_count_opt :",
"unstring_count_opt : COUNT in_opt name",
"unstring_tallying :",
"unstring_tallying : TALLYING in_opt name",
"all_opt :",
"all_opt : ALL",
"$$114 :",
"on_overflow_opt : $$114 on_overflow on_not_overflow",
"$$115 :",
"on_exception_or_overflow : on_opt exception_or_overflow $$115 statement_list",
"on_exception_or_overflow :",
"exception_or_overflow : EXCEPTION",
"exception_or_overflow : OVERFLOW_TOK",
"$$116 :",
"on_not_exception : NOT on_opt EXCEPTION $$116 statement_list",
"on_not_exception :",
"$$117 :",
"on_overflow : on_opt OVERFLOW_TOK $$117 statement_list",
"on_overflow :",
"$$118 :",
"on_not_overflow : not_excep on_opt OVERFLOW_TOK $$118 statement_list",
"on_not_overflow :",
"invalid_key_opt : invalid_key_sentence",
"invalid_key_opt : not_invalid_key_sentence",
"invalid_key_opt : invalid_key_sentence not_invalid_key_sentence",
"invalid_key_opt :",
"$$119 :",
"invalid_key_sentence : INVALID key_opt $$119 statement_list",
"$$120 :",
"not_invalid_key_sentence : not_excep INVALID key_opt $$120 statement_list",
"not_excep : NOTEXCEP",
"not_excep : NOT",
"string_with_pointer : with_opt POINTER name",
"string_with_pointer :",
"string_from_list : string_from",
"string_from_list : string_from_list sep_opt string_from",
"string_from_list : error",
"string_from : gname",
"string_from : gname DELIMITED by_opt delimited_by",
"delimited_by : gname",
"delimited_by : SIZE",
"delimited_by : error",
"end_stringcmd_opt :",
"end_stringcmd_opt : END_STRINGCMD",
"end_unstring_opt :",
"end_unstring_opt : END_UNSTRING",
"$$121 :",
"inspect_statement : INSPECT name tallying_clause $$121 replacing_clause",
"inspect_statement : INSPECT name converting_clause",
"converting_clause : CONVERTING noallname TO noallname inspect_before_after",
"tallying_clause : TALLYING tallying_list",
"tallying_clause :",
"tallying_list : tallying_list name FOR tallying_for_list",
"tallying_list :",
"tallying_for_list : tallying_for_list CHARACTERS inspect_before_after",
"tallying_for_list : tallying_for_list ALL noallname inspect_before_after",
"tallying_for_list : tallying_for_list LEADING noallname inspect_before_after",
"tallying_for_list :",
"replacing_clause : REPLACING replacing_list",
"replacing_clause :",
"replacing_list : replacing_list CHARACTERS BY noallname inspect_before_after",
"replacing_list : replacing_list replacing_kind replacing_by_list",
"replacing_list :",
"replacing_by_list : replacing_by_list noallname BY noallname inspect_before_after",
"replacing_by_list :",
"replacing_kind : ALL",
"replacing_kind : LEADING",
"replacing_kind : TRAILING",
"replacing_kind : FIRST",
"inspect_before_after : inspect_before_after BEFORE initial_opt noallname",
"inspect_before_after : inspect_before_after AFTER initial_opt noallname",
"inspect_before_after :",
"initial_opt : INITIAL_TOK",
"initial_opt :",
"expr : gname",
"expr : expr '*' expr",
"expr : expr '/' expr",
"expr : expr '+' expr",
"expr : expr '-' expr",
"expr : expr POW_OP expr",
"expr : '(' expr ')'",
"expr_opt :",
"expr_opt : expr",
"using_options :",
"$$122 :",
"$$123 :",
"using_options : USING $$122 dummy $$123 parm_list",
"returning_options :",
"returning_options : returning_options1 variable",
"returning_options1 : RETURNING",
"returning_options1 : GIVING",
"dummy :",
"procedure_division_using_chaining_opt :",
"procedure_division_using_chaining_opt : USING gname_list",
"procedure_division_using_chaining_opt : CHAINING gname_list",
"procedure_division_returning_opt :",
"procedure_division_returning_opt : RETURNING variable",
"parm_list : parm_list sep_opt parameter",
"parm_list : parameter",
"parameter : gname",
"parameter : by_opt parm_type gname",
"parm_type : REFERENCE",
"parm_type : VALUE",
"parm_type : CONTENT",
"intrinsic_parm_list : intrinsic_parm_list sep_opt intrinsic_parm",
"intrinsic_parm_list : intrinsic_parm",
"intrinsic_parm : gname",
"perform_range : label perform_thru_opt",
"perform_options : perform_statements END_PERFORM",
"$$124 :",
"$$125 :",
"perform_options : gname TIMES $$124 perform_statements $$125 END_PERFORM",
"$$126 :",
"$$127 :",
"$$128 :",
"perform_options : with_test_opt UNTIL $$126 condition $$127 perform_statements $$128 END_PERFORM",
"$$129 :",
"$$130 :",
"$$131 :",
"perform_options : with_test_opt VARYING name FROM gname by_opt gname UNTIL $$129 condition $$130 perform_after_opt perform_statements $$131 END_PERFORM",
"perform_options : label perform_thru_opt",
"$$132 :",
"perform_options : label perform_thru_opt with_test_opt UNTIL $$132 condition",
"perform_options : label perform_thru_opt gname TIMES",
"$$133 :",
"$$134 :",
"perform_options : label perform_thru_opt with_test_opt VARYING name FROM gname by_opt gname UNTIL $$133 condition $$134 perform_after_opt",
"perform_thru_opt :",
"perform_thru_opt : THRU label",
"with_test_opt :",
"with_test_opt : with_opt TEST before_after",
"perform_after_opt :",
"perform_after_opt : AFTER perform_after",
"perform_after_opt : AFTER perform_after AFTER perform_after",
"perform_after_opt : AFTER perform_after AFTER perform_after AFTER perform_after",
"perform_after_opt : AFTER perform_after AFTER perform_after AFTER perform_after AFTER perform_after",
"perform_after_opt : AFTER perform_after AFTER perform_after AFTER perform_after AFTER perform_after AFTER perform_after",
"perform_after_opt : AFTER perform_after AFTER perform_after AFTER perform_after AFTER perform_after AFTER perform_after AFTER perform_after",
"$$135 :",
"perform_after : name FROM gname by_opt gname UNTIL $$135 condition",
"$$136 :",
"perform_statements : $$136 statement_list",
"before_after : BEFORE",
"before_after : AFTER",
"$$137 :",
"condition : expr extended_cond_op $$137 expr_opt",
"condition : NOT condition",
"$$138 :",
"condition : condition AND $$138 implied_op_condition",
"$$139 :",
"condition : condition OR $$139 implied_op_condition",
"condition : '(' condition ')'",
"condition : cond_name",
"implied_op_condition : condition",
"implied_op_condition : cond_op expr",
"implied_op_condition : expr",
"sign_condition : POSITIVE",
"sign_condition : NEGATIVE",
"sign_condition : ZERO",
"class_condition : NUMERIC",
"class_condition : ALPHABETIC_TOK",
"class_condition : ALPHABETIC_LOWER",
"class_condition : ALPHABETIC_UPPER",
"extended_cond_op : IS ext_cond",
"extended_cond_op : IS NOT ext_cond",
"extended_cond_op : IS ext_cond OR ext_cond",
"extended_cond_op : ext_cond",
"extended_cond_op : NOT is_opt ext_cond",
"extended_cond_op : ext_cond OR ext_cond",
"ext_cond : conditional",
"ext_cond : class_condition",
"ext_cond : sign_condition",
"cond_op : conditional",
"cond_op : NOT conditional",
"cond_op : conditional OR conditional",
"conditional : CONDITIONAL than_to_opt",
"comma_opt :",
"comma_opt : ','",
"sep_opt :",
"sep_opt : LISTSEP",
"key_opt :",
"key_opt : KEY",
"advancing_opt :",
"advancing_opt : ADVANCING",
"than_to_opt :",
"than_to_opt : TO",
"than_to_opt : THAN",
"record_opt :",
"record_opt : RECORD",
"at_opt :",
"at_opt : AT",
"in_opt :",
"in_opt : IN",
"in_of : IN",
"in_of : OF",
"by_opt :",
"by_opt : BY",
"with_opt :",
"with_opt : WITH",
"on_opt :",
"on_opt : ON",
"gname_opt : gname",
"gname_opt :",
"to_opt :",
"to_opt : TO",
"name_var_list : name_var",
"name_var_list : name_var_list sep_opt name_var",
"gname_list : gname",
"gname_list : gname_list sep_opt gname",
"gname : name",
"gname : gliteral",
"$$140 :",
"gname : FUNCTION LABELSTR '(' $$140 intrinsic_parm_list ')'",
"gname : FUNCTION LABELSTR",
"name_or_lit : name",
"name_or_lit : literal",
"noallname : name",
"noallname : without_all_literal",
"gliteral : without_all_literal",
"gliteral : all_literal",
"without_all_literal : literal",
"without_all_literal : special_literal",
"all_literal : ALL literal",
"all_literal : ALL special_literal",
"special_literal : SPACES",
"special_literal : ZERO",
"special_literal : QUOTES",
"special_literal : HIGHVALUES",
"special_literal : LOWVALUES",
"special_literal : NULL_TOK",
"var_or_nliteral : variable",
"var_or_nliteral : nliteral",
"nliteral : signed_nliteral",
"literal : signed_nliteral",
"literal : CLITERAL",
"signed_nliteral : NLITERAL",
"signed_nliteral : '+' NLITERAL",
"signed_nliteral : '-' NLITERAL",
"def_name_opt : def_name",
"def_name_opt :",
"def_name : STRING",
"def_name : FILLER",
"variable_indexed : SUBSCVAR",
"filename : literal",
"filename : STRING",
"data_name : literal",
"data_name : STRING",
"$$141 :",
"cond_name : VARCOND '(' $$141 subscripts ')'",
"cond_name : VARCOND",
"name : variable '(' gname ':' gname_opt ')'",
"name : variable",
"name : LABELSTR",
"name_var : gname",
"variable : qualified_var",
"$$142 :",
"variable : qualified_var LPAR $$142 subscripts ')'",
"qualified_var : unqualified_var",
"qualified_var : unqualified_var in_of qualified_var",
"unqualified_var : VARIABLE",
"unqualified_var : SUBSCVAR",
"subscripts : subscript",
"subscripts : subscripts comma_opt subscript",
"subscript : gname",
"subscript : subscript '+' gname",
"subscript : subscript '-' gname",
"integer : signed_nliteral",
"label : LABELSTR in_of LABELSTR",
"label : LABELSTR",
"label : NLITERAL",
"label : NLITERAL in_of NLITERAL",
"label : NLITERAL in_of LABELSTR",
"anystring : STRING",
"anystring : LABELSTR",
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
#line 4611 "htcobol.y"

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
#line 13282 "htcobol.tab.c"
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
case 1:
#line 331 "htcobol.y"
{ gen_main_rtn(); }
break;
case 2:
#line 334 "htcobol.y"
{ pgm_segment++; yyval.ival=1; }
break;
case 3:
#line 335 "htcobol.y"
{ yyval.ival=1 ; }
break;
case 4:
#line 336 "htcobol.y"
{ yyval.ival=1 ; }
break;
case 5:
#line 345 "htcobol.y"
{ pgm_segment++ ; yyval.ival = 1; }
break;
case 6:
#line 346 "htcobol.y"
{ pgm_segment++ ; nested_flag = 1; }
break;
case 7:
#line 346 "htcobol.y"
{ yyval.ival = 1; }
break;
case 8:
#line 347 "htcobol.y"
{pgm_segment++ ; nested_flag = 1; yyval.ival = 1; }
break;
case 9:
#line 359 "htcobol.y"
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
break;
case 10:
#line 377 "htcobol.y"
{ curr_division = CDIV_COMMENT; }
break;
case 12:
#line 393 "htcobol.y"
{
     curr_division = CDIV_IDENT;
    }
break;
case 13:
#line 397 "htcobol.y"
{
     curr_division = CINITIAL;
     if (pgm_header(yyvsp[0].strty.str, yyvsp[0].strty.type) != 0) {
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
break;
case 14:
#line 415 "htcobol.y"
{
     define_special_fields();
    }
break;
case 16:
#line 422 "htcobol.y"
{ 
     yyval.strty.str=yyvsp[0].str;  
     yyval.strty.type=1;
    }
break;
case 17:
#line 427 "htcobol.y"
{
     yyval.strty.str=yyvsp[0].str;  
     yyval.strty.type=2;
    }
break;
case 19:
#line 434 "htcobol.y"
{ initial_flag=1; }
break;
case 20:
#line 435 "htcobol.y"
{ UNIMPLEMENTED("PROGRAM-ID ... COMMON clause") }
break;
case 22:
#line 438 "htcobol.y"
{  }
break;
case 25:
#line 445 "htcobol.y"
{ curr_division = CDIV_COMMENT1; }
break;
case 26:
#line 446 "htcobol.y"
{ curr_division = CDIV_COMMENT1; }
break;
case 27:
#line 447 "htcobol.y"
{ curr_division = CDIV_COMMENT1; }
break;
case 28:
#line 448 "htcobol.y"
{ curr_division = CDIV_COMMENT1; }
break;
case 29:
#line 449 "htcobol.y"
{ curr_division = CDIV_COMMENT1; }
break;
case 30:
#line 456 "htcobol.y"
{
     curr_division = CDIV_ENVIR;
    }
break;
case 31:
#line 461 "htcobol.y"
{
     curr_division = CINITIAL;
    }
break;
case 35:
#line 474 "htcobol.y"
{ }
break;
case 36:
#line 475 "htcobol.y"
{ }
break;
case 37:
#line 479 "htcobol.y"
{ envdiv_bypass_save_sw=1; }
break;
case 38:
#line 481 "htcobol.y"
{ envdiv_bypass_save_sw=0; }
break;
case 39:
#line 483 "htcobol.y"
{ envdiv_bypass_save_sw=1; }
break;
case 40:
#line 485 "htcobol.y"
{ envdiv_bypass_save_sw=0; }
break;
case 42:
#line 487 "htcobol.y"
{ yyerror("invalid format in CONFIGURATION SECTION"); }
break;
case 46:
#line 496 "htcobol.y"
{ }
break;
case 47:
#line 497 "htcobol.y"
{ }
break;
case 48:
#line 500 "htcobol.y"
{ stabs_on_sw = 1; }
break;
case 49:
#line 501 "htcobol.y"
{ }
break;
case 52:
#line 506 "htcobol.y"
{ yyerror("invalid format in SPECIAL-NAMES clause");}
break;
case 62:
#line 526 "htcobol.y"
{
                currency_symbol = yyvsp[0].lval->name[0];
                }
break;
case 65:
#line 535 "htcobol.y"
{}
break;
case 66:
#line 538 "htcobol.y"
{}
break;
case 67:
#line 539 "htcobol.y"
{}
break;
case 68:
#line 542 "htcobol.y"
{}
break;
case 69:
#line 543 "htcobol.y"
{}
break;
case 70:
#line 547 "htcobol.y"
{
                decimal_comma=1; }
break;
case 71:
#line 552 "htcobol.y"
{ screen_status_field=yyvsp[0].sval; }
break;
case 72:
#line 556 "htcobol.y"
{ cursor_field=yyvsp[0].sval; }
break;
case 75:
#line 563 "htcobol.y"
{if (yyvsp[-2].sval->name[0] != 'S' || yyvsp[-2].sval->name[1] != 'W')
       yyerror("Invalid switch name");
    define_switch_field(yyvsp[0].sval, yyvsp[-2].sval);}
break;
case 76:
#line 567 "htcobol.y"
{ close_fields();}
break;
case 77:
#line 570 "htcobol.y"
{save_switch_value(yyvsp[0].sval, 1);}
break;
case 79:
#line 574 "htcobol.y"
{save_switch_value(yyvsp[0].sval, 0);}
break;
case 83:
#line 583 "htcobol.y"
{ 
     yyvsp[-2].sval->defined=1;
     UNIMPLEMENTED("Alphabet clause")
    }
break;
case 84:
#line 589 "htcobol.y"
{ }
break;
case 85:
#line 590 "htcobol.y"
{ }
break;
case 86:
#line 591 "htcobol.y"
{ }
break;
case 87:
#line 592 "htcobol.y"
{ }
break;
case 90:
#line 599 "htcobol.y"
{ }
break;
case 91:
#line 600 "htcobol.y"
{ }
break;
case 92:
#line 601 "htcobol.y"
{ }
break;
case 95:
#line 611 "htcobol.y"
{ }
break;
case 97:
#line 615 "htcobol.y"
{ }
break;
case 99:
#line 620 "htcobol.y"
{ }
break;
case 101:
#line 623 "htcobol.y"
{ }
break;
case 105:
#line 637 "htcobol.y"
{
     curr_file=file_select_clause_init(yyvsp[0].sval, yyvsp[-1].ival); 
    }
break;
case 106:
#line 641 "htcobol.y"
{
     if (file_select_clause_verify(curr_file) != 0) 
        YYABORT;
    }
break;
case 109:
#line 652 "htcobol.y"
{ curr_file->uval1.organization=yyvsp[0].ival; }
break;
case 110:
#line 653 "htcobol.y"
{ curr_file->uval7.filenamevar=yyvsp[0].sval; }
break;
case 111:
#line 654 "htcobol.y"
{ curr_file->uval3.access_mode=yyvsp[0].ival; }
break;
case 112:
#line 655 "htcobol.y"
{ curr_file->parent=yyvsp[0].sval; }
break;
case 113:
#line 656 "htcobol.y"
{ curr_file->ix_desc=yyvsp[0].sval; }
break;
case 114:
#line 657 "htcobol.y"
{ curr_file->ix_desc=yyvsp[0].sval; }
break;
case 115:
#line 659 "htcobol.y"
{ add_alternate_key(yyvsp[-1].sval,yyvsp[0].ival); }
break;
case 117:
#line 661 "htcobol.y"
{ yyerror("invalid clause in select"); }
break;
case 118:
#line 664 "htcobol.y"
{ yyval.sval=yyvsp[0].sval; }
break;
case 119:
#line 666 "htcobol.y"
{
     yyvsp[0].sval->parent=yyvsp[-2].sval; yyval.sval=yyvsp[0].sval;
     /* fprintf(stderr, "parent=%s, child=%s;\n", $3->name, $1->name);  */
    }
break;
case 122:
#line 676 "htcobol.y"
{ }
break;
case 124:
#line 679 "htcobol.y"
{ yyval.sval=yyvsp[0].sval; }
break;
case 125:
#line 680 "htcobol.y"
{ yyval.sval=yyvsp[0].sval; }
break;
case 126:
#line 681 "htcobol.y"
{ yyval.sval=yyvsp[0].sval; }
break;
case 127:
#line 682 "htcobol.y"
{ yyval.sval=NULL; }
break;
case 128:
#line 686 "htcobol.y"
{ curr_file->flags.file_external = 1; }
break;
case 130:
#line 691 "htcobol.y"
{ }
break;
case 131:
#line 692 "htcobol.y"
{ curr_file->flags.file_printer = 1; }
break;
case 132:
#line 696 "htcobol.y"
{ curr_file->flags.file_stdin  = 1; yyval.sval=define_std_filename(0); }
break;
case 133:
#line 697 "htcobol.y"
{ curr_file->flags.file_stdout = 1; yyval.sval=define_std_filename(1); }
break;
case 134:
#line 698 "htcobol.y"
{ curr_file->flags.file_stderr = 1; yyval.sval=define_std_filename(2); }
break;
case 135:
#line 699 "htcobol.y"
{ curr_file->flags.file_stdout = 1; yyval.sval=define_std_filename(0); }
break;
case 136:
#line 703 "htcobol.y"
{ yyval.ival=1; }
break;
case 137:
#line 704 "htcobol.y"
{ yyval.ival=0; }
break;
case 138:
#line 707 "htcobol.y"
{ yyval.ival=1; }
break;
case 139:
#line 708 "htcobol.y"
{ yyval.ival=0; }
break;
case 143:
#line 715 "htcobol.y"
{ }
break;
case 145:
#line 719 "htcobol.y"
{ }
break;
case 149:
#line 727 "htcobol.y"
{ yyval.ival=1; }
break;
case 150:
#line 728 "htcobol.y"
{ yyval.ival=2; }
break;
case 151:
#line 729 "htcobol.y"
{ yyval.ival=3; }
break;
case 152:
#line 730 "htcobol.y"
{ yyval.ival=4; }
break;
case 153:
#line 731 "htcobol.y"
{ yyerror("invalid option, %s",yyvsp[0].sval->name); }
break;
case 154:
#line 734 "htcobol.y"
{ yyval.ival=1; }
break;
case 155:
#line 735 "htcobol.y"
{ yyval.ival=2; }
break;
case 156:
#line 736 "htcobol.y"
{ yyval.ival=3; }
break;
case 157:
#line 738 "htcobol.y"
{ yyerror("invalid access option, %s", yyvsp[0].sval->name); }
break;
case 159:
#line 743 "htcobol.y"
{ UNIMPLEMENTED("I-O-CONTROL paragraph") }
break;
case 166:
#line 758 "htcobol.y"
{  }
break;
case 167:
#line 759 "htcobol.y"
{  }
break;
case 168:
#line 760 "htcobol.y"
{  }
break;
case 172:
#line 770 "htcobol.y"
{ }
break;
case 174:
#line 773 "htcobol.y"
{ }
break;
case 181:
#line 788 "htcobol.y"
{ yyval.sval = yyvsp[0].sval; }
break;
case 182:
#line 789 "htcobol.y"
{ yyval.sval = yyvsp[0].sval; }
break;
case 183:
#line 790 "htcobol.y"
{ yyerror("string expected"); }
break;
case 184:
#line 793 "htcobol.y"
{ yyval.sval = (struct sym *)chain_var(yyvsp[0].sval); }
break;
case 185:
#line 794 "htcobol.y"
{ yyval.sval = (struct sym *)chain_var(yyvsp[0].sval); }
break;
case 186:
#line 795 "htcobol.y"
{ yyerror("variable expected"); }
break;
case 187:
#line 804 "htcobol.y"
{ curr_division = CDIV_DATA; }
break;
case 188:
#line 810 "htcobol.y"
{ curr_division = CINITIAL; }
break;
case 190:
#line 817 "htcobol.y"
{ curr_field=NULL; }
break;
case 191:
#line 818 "htcobol.y"
{ close_fields();  }
break;
case 193:
#line 825 "htcobol.y"
{ curr_field=NULL; }
break;
case 194:
#line 826 "htcobol.y"
{ close_fields(); }
break;
case 196:
#line 833 "htcobol.y"
{ at_linkage=1; curr_field=NULL; has_linkage++; }
break;
case 197:
#line 834 "htcobol.y"
{ close_fields(); at_linkage=0; }
break;
case 199:
#line 850 "htcobol.y"
{  }
break;
case 203:
#line 859 "htcobol.y"
{ /*curr_division = CDIV_FD;*/ }
break;
case 204:
#line 861 "htcobol.y"
{ 
     yyvsp[0].sval->type='W'; 
     yyvsp[0].sval->uval9.picstr = 0;
     yyvsp[0].sval->parent = 0;
     yyvsp[0].sval->clone  = 0;
     yyvsp[0].sval->times  = -1;
     curr_division = CDIV_PROC;
     UNIMPLEMENTED("Report Section")
    }
break;
case 205:
#line 871 "htcobol.y"
{ 
     curr_division = CDIV_DATA; 
    }
break;
case 206:
#line 875 "htcobol.y"
{
     /* update_report_field($4); */   
     /* define_field(1,$4); */ 
    }
break;
case 209:
#line 883 "htcobol.y"
{ }
break;
case 210:
#line 884 "htcobol.y"
{ }
break;
case 211:
#line 885 "htcobol.y"
{ }
break;
case 212:
#line 886 "htcobol.y"
{ }
break;
case 235:
#line 935 "htcobol.y"
{ yyvsp[0].sval->defined=1; }
break;
case 238:
#line 943 "htcobol.y"
{
     if (yyvsp[0].sval == NULL) {
            yyvsp[0].sval = alloc_filler();
            picix=piccnt=v_flag=n_flag=decimals=pscale=0;
            picture[picix]=0;
     }
     define_field(yyvsp[-1].ival,yyvsp[0].sval); 
     curr_division = CDIV_DATA; 
    }
break;
case 239:
#line 953 "htcobol.y"
{ 
     update_report_field(yyvsp[-3].sval); 
     curr_division = CDIV_DATA; 
    }
break;
case 242:
#line 963 "htcobol.y"
{  }
break;
case 243:
#line 964 "htcobol.y"
{  }
break;
case 244:
#line 965 "htcobol.y"
{  }
break;
case 245:
#line 966 "htcobol.y"
{  }
break;
case 246:
#line 967 "htcobol.y"
{  }
break;
case 247:
#line 968 "htcobol.y"
{  }
break;
case 248:
#line 969 "htcobol.y"
{  }
break;
case 249:
#line 970 "htcobol.y"
{  }
break;
case 250:
#line 971 "htcobol.y"
{  }
break;
case 251:
#line 972 "htcobol.y"
{  }
break;
case 252:
#line 973 "htcobol.y"
{  }
break;
case 253:
#line 976 "htcobol.y"
{  }
break;
case 254:
#line 979 "htcobol.y"
{  }
break;
case 255:
#line 980 "htcobol.y"
{  }
break;
case 256:
#line 981 "htcobol.y"
{ curr_division = CDIV_PROC;  }
break;
case 257:
#line 982 "htcobol.y"
{ curr_division = CDIV_DATA;  }
break;
case 258:
#line 983 "htcobol.y"
{ }
break;
case 259:
#line 984 "htcobol.y"
{ curr_division = CDIV_PROC;  }
break;
case 260:
#line 985 "htcobol.y"
{ curr_division = CDIV_DATA;  }
break;
case 261:
#line 986 "htcobol.y"
{  }
break;
case 262:
#line 987 "htcobol.y"
{  }
break;
case 263:
#line 988 "htcobol.y"
{  }
break;
case 264:
#line 989 "htcobol.y"
{  }
break;
case 265:
#line 990 "htcobol.y"
{ curr_division = CDIV_PROC;  }
break;
case 266:
#line 991 "htcobol.y"
{ curr_division = CDIV_DATA;  }
break;
case 267:
#line 992 "htcobol.y"
{  }
break;
case 268:
#line 993 "htcobol.y"
{ curr_division = CDIV_PROC;  }
break;
case 269:
#line 994 "htcobol.y"
{ curr_division = CDIV_DATA;  }
break;
case 270:
#line 995 "htcobol.y"
{  }
break;
case 271:
#line 996 "htcobol.y"
{  }
break;
case 272:
#line 999 "htcobol.y"
{  }
break;
case 273:
#line 1000 "htcobol.y"
{  }
break;
case 274:
#line 1004 "htcobol.y"
{
     curr_division = CDIV_PIC;
    }
break;
case 275:
#line 1007 "htcobol.y"
{ curr_division = CDIV_DATA;  }
break;
case 276:
#line 1010 "htcobol.y"
{  }
break;
case 277:
#line 1011 "htcobol.y"
{  }
break;
case 280:
#line 1020 "htcobol.y"
{  }
break;
case 281:
#line 1021 "htcobol.y"
{  }
break;
case 282:
#line 1022 "htcobol.y"
{  }
break;
case 283:
#line 1023 "htcobol.y"
{  }
break;
case 288:
#line 1032 "htcobol.y"
{  }
break;
case 289:
#line 1035 "htcobol.y"
{ yyval.ival=yyvsp[-1].ival; }
break;
case 290:
#line 1036 "htcobol.y"
{ yyval.ival=yyvsp[-1].ival; }
break;
case 291:
#line 1037 "htcobol.y"
{ yyval.ival=yyvsp[-1].ival; }
break;
case 292:
#line 1038 "htcobol.y"
{ yyval.ival=yyvsp[-1].ival; }
break;
case 293:
#line 1041 "htcobol.y"
{ yyval.ival=0; }
break;
case 294:
#line 1042 "htcobol.y"
{ yyval.ival=0; }
break;
case 295:
#line 1043 "htcobol.y"
{ yyval.ival=1; }
break;
case 296:
#line 1044 "htcobol.y"
{ yyval.ival=2; }
break;
case 298:
#line 1048 "htcobol.y"
{ }
break;
case 299:
#line 1049 "htcobol.y"
{ }
break;
case 300:
#line 1052 "htcobol.y"
{ curr_division = CDIV_PROC; }
break;
case 301:
#line 1054 "htcobol.y"
{ curr_division = CDIV_DATA;  }
break;
case 302:
#line 1055 "htcobol.y"
{  }
break;
case 303:
#line 1056 "htcobol.y"
{ curr_division = CDIV_PROC;  }
break;
case 304:
#line 1057 "htcobol.y"
{ curr_division = CDIV_DATA;  }
break;
case 305:
#line 1058 "htcobol.y"
{ }
break;
case 306:
#line 1060 "htcobol.y"
{  }
break;
case 307:
#line 1061 "htcobol.y"
{  }
break;
case 309:
#line 1064 "htcobol.y"
{  }
break;
case 310:
#line 1067 "htcobol.y"
{  }
break;
case 312:
#line 1070 "htcobol.y"
{  }
break;
case 314:
#line 1073 "htcobol.y"
{  }
break;
case 316:
#line 1076 "htcobol.y"
{  }
break;
case 317:
#line 1077 "htcobol.y"
{  }
break;
case 319:
#line 1080 "htcobol.y"
{ }
break;
case 320:
#line 1083 "htcobol.y"
{ }
break;
case 321:
#line 1084 "htcobol.y"
{ }
break;
case 323:
#line 1087 "htcobol.y"
{ }
break;
case 324:
#line 1090 "htcobol.y"
{ }
break;
case 325:
#line 1091 "htcobol.y"
{ }
break;
case 326:
#line 1094 "htcobol.y"
{ }
break;
case 327:
#line 1095 "htcobol.y"
{ }
break;
case 328:
#line 1096 "htcobol.y"
{ }
break;
case 331:
#line 1110 "htcobol.y"
{
      screen_io_enable++;
      curr_field=NULL;
      HTG_prg_uses_term = 1;
    }
break;
case 332:
#line 1115 "htcobol.y"
{ close_fields(); }
break;
case 336:
#line 1138 "htcobol.y"
{
      if (yyvsp[0].sval == NULL) {
         yyvsp[0].sval = alloc_filler();
      }
      picix=piccnt=v_flag=n_flag=decimals=pscale=0;
      picture[picix]=0;
      define_field(yyvsp[-1].ival,yyvsp[0].sval);
    }
break;
case 337:
#line 1146 "htcobol.y"
{ update_screen_field(yyvsp[-3].sval,yyvsp[-1].sival); }
break;
case 338:
#line 1149 "htcobol.y"
{ curr_division = CDIV_PROC; }
break;
case 339:
#line 1152 "htcobol.y"
{ curr_division = CDIV_DATA; 
                                  scr_set_line(yyvsp[-5].sival,yyvsp[0].sval,yyvsp[-1].ival); yyval.sival=yyvsp[-5].sival; }
break;
case 340:
#line 1154 "htcobol.y"
{ curr_division = CDIV_PROC; }
break;
case 341:
#line 1157 "htcobol.y"
{ curr_division = CDIV_DATA; 
                                  scr_set_column(yyvsp[-5].sival,yyvsp[0].sval,yyvsp[-1].ival); yyval.sival=yyvsp[-5].sival; }
break;
case 342:
#line 1160 "htcobol.y"
{ yyvsp[-2].sival->attr |= yyvsp[0].ival; yyval.sival=yyvsp[-2].sival; }
break;
case 343:
#line 1161 "htcobol.y"
{ curr_division = CDIV_PROC; }
break;
case 344:
#line 1162 "htcobol.y"
{ curr_division = CDIV_DATA; 
                                          yyvsp[-4].sival->color = NULL;
                                          yyvsp[-4].sival->foreground = yyvsp[0].sval; yyval.sival=yyvsp[-4].sival; }
break;
case 345:
#line 1165 "htcobol.y"
{ curr_division = CDIV_PROC; }
break;
case 346:
#line 1166 "htcobol.y"
{ curr_division = CDIV_DATA; 
                                          yyvsp[-4].sival->color = NULL;
                                          yyvsp[-4].sival->background = yyvsp[0].sval; yyval.sival=yyvsp[-4].sival; }
break;
case 347:
#line 1169 "htcobol.y"
{ curr_division = CDIV_PROC; }
break;
case 348:
#line 1170 "htcobol.y"
{ curr_division = CDIV_DATA; 
                                          yyvsp[-4].sival->foreground = NULL;  
                                          yyvsp[-4].sival->background = NULL; 
                                          yyvsp[-4].sival->color = yyvsp[0].sval; yyval.sival=yyvsp[-4].sival; }
break;
case 350:
#line 1177 "htcobol.y"
{ curr_field->value = yyvsp[0].lval; yyval.sival=yyvsp[-2].sival; }
break;
case 352:
#line 1179 "htcobol.y"
{ curr_division = CDIV_PROC; }
break;
case 353:
#line 1180 "htcobol.y"
{ curr_division = CDIV_DATA; 
                                yyvsp[-3].sival->size = yyvsp[0].sval; yyval.sival=yyvsp[-3].sival; }
break;
case 354:
#line 1182 "htcobol.y"
{ yyval.sival = alloc_scr_info(); }
break;
case 355:
#line 1185 "htcobol.y"
{ curr_division = CDIV_PROC; }
break;
case 356:
#line 1186 "htcobol.y"
{
                        curr_division = CDIV_DATA;
                        yyvsp[-3].sival->from = yyvsp[-3].sival->to = yyvsp[0].sval;
                }
break;
case 357:
#line 1190 "htcobol.y"
{ curr_division = CDIV_PROC; }
break;
case 358:
#line 1192 "htcobol.y"
{
                        curr_division = CDIV_DATA;
                        yyvsp[-4].sival->from = yyvsp[-1].sval; yyvsp[-4].sival->to = yyvsp[0].sval;
                }
break;
case 359:
#line 1196 "htcobol.y"
{ curr_division = CDIV_PROC; }
break;
case 360:
#line 1197 "htcobol.y"
{
                        curr_division = CDIV_DATA;
                        yyvsp[-3].sival->from = NULL; yyvsp[-3].sival->to = yyvsp[0].sval;
                }
break;
case 361:
#line 1203 "htcobol.y"
{ yyval.sval=NULL; }
break;
case 362:
#line 1204 "htcobol.y"
{ yyval.sval = yyvsp[0].sval; }
break;
case 363:
#line 1207 "htcobol.y"
{ yyval.ival = SCR_BLANK_SCREEN; }
break;
case 364:
#line 1208 "htcobol.y"
{ yyval.ival = SCR_BLANK_LINE; }
break;
case 365:
#line 1209 "htcobol.y"
{ yyval.ival = SCR_ERASE_EOL; }
break;
case 366:
#line 1210 "htcobol.y"
{ yyval.ival = SCR_ERASE_EOS; }
break;
case 367:
#line 1211 "htcobol.y"
{ yyval.ival = SCR_ERASE_EOL; }
break;
case 368:
#line 1212 "htcobol.y"
{ yyval.ival = SCR_BELL; }
break;
case 369:
#line 1213 "htcobol.y"
{ yyval.ival = yyvsp[0].ival; }
break;
case 370:
#line 1214 "htcobol.y"
{ yyval.ival = SCR_FULL; }
break;
case 371:
#line 1215 "htcobol.y"
{ yyval.ival = SCR_REQUIRED; }
break;
case 372:
#line 1216 "htcobol.y"
{ yyval.ival = SCR_SECURE; }
break;
case 373:
#line 1217 "htcobol.y"
{ yyval.ival = SCR_AUTO; }
break;
case 374:
#line 1218 "htcobol.y"
{ yyval.ival = SCR_JUST_RIGHT; }
break;
case 375:
#line 1219 "htcobol.y"
{ yyval.ival = SCR_JUST_LEFT; }
break;
case 376:
#line 1220 "htcobol.y"
{ yyval.ival = SCR_BLINK; }
break;
case 377:
#line 1221 "htcobol.y"
{ yyval.ival = SCR_REVERSE_VIDEO; }
break;
case 378:
#line 1222 "htcobol.y"
{ yyval.ival = SCR_UNDERLINE; }
break;
case 379:
#line 1223 "htcobol.y"
{ yyval.ival = SCR_LOWLIGHT; }
break;
case 380:
#line 1224 "htcobol.y"
{ yyval.ival = SCR_HIGHLIGHT; }
break;
case 381:
#line 1225 "htcobol.y"
{ yyval.ival = SCR_BLANK_WHEN_ZERO; }
break;
case 382:
#line 1226 "htcobol.y"
{ yyval.ival = SCR_NOECHO; }
break;
case 383:
#line 1227 "htcobol.y"
{ yyval.ival = SCR_UPDATE; }
break;
case 384:
#line 1228 "htcobol.y"
{ yyval.ival = SCR_NO_ADVANCING; }
break;
case 385:
#line 1229 "htcobol.y"
{ yyval.ival = SCR_UPPER; }
break;
case 386:
#line 1230 "htcobol.y"
{ yyval.ival = SCR_LOWER; }
break;
case 387:
#line 1234 "htcobol.y"
{ yyval.ival = SCR_SIGN_LEADING | yyvsp[0].ival; }
break;
case 388:
#line 1236 "htcobol.y"
{ yyval.ival = yyvsp[0].ival; }
break;
case 389:
#line 1239 "htcobol.y"
{ yyval.ival = SCR_SIGN_SEPARATE; }
break;
case 390:
#line 1240 "htcobol.y"
{ yyval.ival = 0; }
break;
case 395:
#line 1251 "htcobol.y"
{ yyval.ival = 1; }
break;
case 396:
#line 1252 "htcobol.y"
{ yyval.ival = 1; }
break;
case 397:
#line 1253 "htcobol.y"
{ yyval.ival = -1; }
break;
case 398:
#line 1254 "htcobol.y"
{ yyval.ival = -1; }
break;
case 399:
#line 1255 "htcobol.y"
{ yyval.ival = 0; }
break;
case 402:
#line 1268 "htcobol.y"
{ curr_division = CDIV_FD; }
break;
case 403:
#line 1270 "htcobol.y"
{ curr_division = CDIV_DATA; }
break;
case 404:
#line 1272 "htcobol.y"
{
      curr_field=NULL;
      if (yyvsp[-3].sval->uval7.filenamevar == NULL) {
         yyerror("External file name not defined for file %s", yyvsp[-3].sval->name);
      }
     }
break;
case 405:
#line 1279 "htcobol.y"
{
      /*
      close_fields();
      alloc_file_entry($4, 0);
      gen_fdesc($4,$9);
      */
      gen_fsd(yyvsp[-5].sval, yyvsp[0].sval, yyvsp[-3].fdentry, 0);
     }
break;
case 406:
#line 1287 "htcobol.y"
{ curr_division = CDIV_FD; }
break;
case 407:
#line 1288 "htcobol.y"
{ curr_division = CDIV_DATA; }
break;
case 408:
#line 1290 "htcobol.y"
{
       yyvsp[-3].sval->uval1.organization=TCB_FILE_ORGANIZATION_SORT;
       curr_field=NULL;
      }
break;
case 409:
#line 1295 "htcobol.y"
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
       gen_fsd(yyvsp[-5].sval, yyvsp[0].sval, yyvsp[-3].fdentry, 1); 
      }
break;
case 410:
#line 1307 "htcobol.y"
{ yyerror("missing or invalid file description entry"); }
break;
case 412:
#line 1312 "htcobol.y"
{ 
     yyvsp[0].sval->flags.isfilerecord = 1; 
     yyval.sval=yyvsp[0].sval; 
    }
break;
case 413:
#line 1317 "htcobol.y"
{
     /* Define a record for each FD/SD */
     if ((yyvsp[0].sval != NULL) && (yyvsp[0].sval->level == 1)) { 
        yyvsp[0].sval->flags.isfilerecord = 1; 
        yyval.sval=file_description_append_rec(yyvsp[-1].sval, yyvsp[0].sval); 
     }
     else {
        yyvsp[-1].sval->flags.isfilerecord = 1; 
        yyval.sval=yyvsp[-1].sval;
     }
    }
break;
case 414:
#line 1335 "htcobol.y"
{
     picix=piccnt=v_flag=n_flag=decimals=pscale=0;
     if ((yyvsp[-1].ival == 78) || (yyvsp[-1].ival == 66)) {
        if (yyvsp[-1].ival == 78) 
           yyerror("level 78 are not supported");
        if (yyvsp[-1].ival == 66) 
           yyerror("level 66 are not supported");
     } 
     else {
        if (yyvsp[0].sval==NULL) 
           define_field(yyvsp[-1].ival,alloc_filler());
        else 
           define_field(yyvsp[-1].ival,yyvsp[0].sval);
     } 
    }
break;
case 415:
#line 1351 "htcobol.y"
{
     yyval.sval=yyvsp[-3].sval;
     if ((yyval.sval == NULL) || (yyval.sval->level != 66))
        update_field(curr_field);
     if (curr_field != NULL) { 
       if ((curr_field->occurs_flg != 0) && 
         ((yyvsp[-4].ival == 1) || (yyvsp[-4].ival == 77) || (yyvsp[-4].ival == 66) || (yyvsp[-4].ival == 88)))
         yyerror("OCCURS clause not permitted for data item '%s' with level number 01/77/66/88", curr_field->name);
     }
    }
break;
case 419:
#line 1369 "htcobol.y"
{ curr_division = CDIV_PROC; /* parsing variable */ }
break;
case 420:
#line 1371 "htcobol.y"
{
      curr_division = CDIV_DATA;
      curr_field->uval6.redefines = lookup_for_redefines(yyvsp[0].sval);
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
break;
case 421:
#line 1386 "htcobol.y"
{ yyval.sval=yyvsp[0].sval; }
break;
case 422:
#line 1387 "htcobol.y"
{ yyval.sval=yyvsp[0].sval; }
break;
case 426:
#line 1393 "htcobol.y"
{
        curr_field->flags.separate_sign = (yyvsp[0].ival & SCR_SIGN_SEPARATE) ? 1 : 0;
        curr_field->flags.leading_sign  = (yyvsp[0].ival & SCR_SIGN_LEADING) ? 1 : 0; }
break;
case 428:
#line 1397 "htcobol.y"
{curr_field->flags.sync=1;}
break;
case 429:
#line 1398 "htcobol.y"
{if (yyvsp[0].ival != 2) curr_field->flags.just_r=1;}
break;
case 430:
#line 1399 "htcobol.y"
{save_named_sect(curr_field);}
break;
case 431:
#line 1400 "htcobol.y"
{}
break;
case 432:
#line 1401 "htcobol.y"
{ curr_field->flags.blank=1; }
break;
case 433:
#line 1402 "htcobol.y"
{ curr_division = CDIV_PROC /* for parsing variable */; }
break;
case 434:
#line 1404 "htcobol.y"
{ curr_division = CDIV_DATA;
                    update_renames_field(yyvsp[-1].sval, yyvsp[0].sval);}
break;
case 435:
#line 1408 "htcobol.y"
{yyval.ival=0;}
break;
case 436:
#line 1409 "htcobol.y"
{yyval.ival=2;}
break;
case 437:
#line 1410 "htcobol.y"
{yyval.ival=1;}
break;
case 438:
#line 1412 "htcobol.y"
{ yyval.sval = NULL;}
break;
case 439:
#line 1413 "htcobol.y"
{ yyval.sval = yyvsp[0].sval;}
break;
case 440:
#line 1419 "htcobol.y"
{ 
       curr_field->times = yyvsp[-1].ival; 
       curr_field->occurs_flg++; 
      }
break;
case 442:
#line 1425 "htcobol.y"
{ curr_division = CDIV_PROC; /* needed for parsing variable */ }
break;
case 443:
#line 1427 "htcobol.y"
{       
       curr_division = CDIV_DATA;
       create_occurs_info(yyvsp[-7].ival,yyvsp[-5].ival,yyvsp[0].sval);
      }
break;
case 445:
#line 1435 "htcobol.y"
{
     yyvsp[0].sval->level=0;
     if (yyvsp[-3].ival == ASCENDING) {
             yyvsp[0].sval->level=-1;
     }
     if (yyvsp[-3].ival == DESCENDING) {
             yyvsp[0].sval->level=-2;
     }
     yyval.sval=yyvsp[0].sval;
    }
break;
case 446:
#line 1445 "htcobol.y"
{ yyval.sval=NULL; }
break;
case 447:
#line 1449 "htcobol.y"
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
break;
case 449:
#line 1464 "htcobol.y"
{ 
      define_implicit_field(yyvsp[0].sval, yyvsp[-3].sval, curr_field->times);
      /* Fix Me: Does not work, thus dup vars can be defined
      if ($4->defined) {
         yyerror("variable redefined, '%s'",$4->name);
         $4->defined=1;
      }
      else { 
         define_implicit_field($4, $1, curr_field->times);
      } */
     }
break;
case 450:
#line 1476 "htcobol.y"
{
        define_implicit_field(yyvsp[0].sval,yyvsp[-4].sval,curr_field->times);
       }
break;
case 451:
#line 1484 "htcobol.y"
{ set_usage(curr_field, yyvsp[0].ival); }
break;
case 452:
#line 1487 "htcobol.y"
{ yyval.ival=yyvsp[0].ival; }
break;
case 453:
#line 1488 "htcobol.y"
{ yyval.ival=USAGE_DISPLAY; }
break;
case 454:
#line 1489 "htcobol.y"
{ yyval.ival=USAGE_POINTER; }
break;
case 460:
#line 1506 "htcobol.y"
{ set_variable_values(yyvsp[0].lval,yyvsp[0].lval); }
break;
case 461:
#line 1508 "htcobol.y"
{
      set_variable_values(yyvsp[-2].lval,yyvsp[0].lval);
     }
break;
case 462:
#line 1517 "htcobol.y"
{ 
     curr_division = CDIV_PIC;
     /* first pic char found */
     picix=piccnt=v_flag=n_flag=decimals=pscale=0;
     picture[picix]=0;
    }
break;
case 463:
#line 1524 "htcobol.y"
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
break;
case 466:
#line 1542 "htcobol.y"
{
     if (!save_pic_char ( yyvsp[-1].ival, yyvsp[0].ival )) {
        yyerror("invalid char in picture");
        YYERROR;
     }
    }
break;
case 467:
#line 1550 "htcobol.y"
{ yyval.ival = 1; }
break;
case 468:
#line 1551 "htcobol.y"
{ yyval.ival = yyvsp[0].ival; }
break;
case 469:
#line 1555 "htcobol.y"
{ yyval.fdentry=NULL; }
break;
case 470:
#line 1557 "htcobol.y"
{ yyval.fdentry=set_fd_clause(yyvsp[-1].fdentry, yyvsp[0].fdentry); }
break;
case 471:
#line 1559 "htcobol.y"
{ yyval.fdentry=NULL; }
break;
case 472:
#line 1561 "htcobol.y"
{ /* $$=NULL; */ yyval.fdentry=set_fd_clause(yyvsp[-1].fdentry, yyvsp[0].fdentry); }
break;
case 473:
#line 1565 "htcobol.y"
{ yyval.fdentry=set_fd_clause_external(); }
break;
case 474:
#line 1566 "htcobol.y"
{ yyval.fdentry=set_fd_clause_global(); }
break;
case 475:
#line 1567 "htcobol.y"
{ yyval.fdentry=NULL; }
break;
case 476:
#line 1568 "htcobol.y"
{ yyval.fdentry=set_fd_clause_record(yyvsp[0].fdrec); }
break;
case 477:
#line 1569 "htcobol.y"
{ yyval.fdentry=NULL; }
break;
case 478:
#line 1570 "htcobol.y"
{ yyval.fdentry=NULL; }
break;
case 479:
#line 1571 "htcobol.y"
{ yyval.fdentry=NULL; }
break;
case 480:
#line 1572 "htcobol.y"
{ yyval.fdentry=NULL; }
break;
case 481:
#line 1573 "htcobol.y"
{ yyval.fdentry=NULL; }
break;
case 482:
#line 1574 "htcobol.y"
{ yyval.fdentry=NULL; }
break;
case 483:
#line 1577 "htcobol.y"
{ /* $$=NULL; */ yyval.fdentry=set_fd_clause_record(yyvsp[0].fdrec); }
break;
case 484:
#line 1578 "htcobol.y"
{ yyval.fdentry=NULL; }
break;
case 485:
#line 1584 "htcobol.y"
{ /* clause is ignored on x86 platform */ }
break;
case 486:
#line 1590 "htcobol.y"
{ 
     if (yyvsp[-1].lval != NULL)
        yyval.fdrec=set_file_record_clause(yyvsp[-1].lval, yyvsp[-2].lval, NULL, TCB_TYPE_RECORD_VARIABLE); 
     else 
        yyval.fdrec=set_file_record_clause(yyvsp[-2].lval, NULL, NULL, TCB_TYPE_RECORD_FIXED); 
    }
break;
case 487:
#line 1599 "htcobol.y"
{ 
       yyval.fdrec=set_file_record_clause(yyvsp[-2].lval, yyvsp[-3].lval, yyvsp[0].sval, TCB_TYPE_RECORD_VARIABLE); 
      }
break;
case 488:
#line 1605 "htcobol.y"
{ /* obsolete */ }
break;
case 489:
#line 1610 "htcobol.y"
{  
      if (yyvsp[-7].sval->uval7.filenamevar != NULL) {
         yyerror("Re-defining file name defined in SELECT statement");
      }
      else {
         yyvsp[-7].sval->uval7.filenamevar = yyvsp[0].sval;
      }
    }
break;
case 490:
#line 1621 "htcobol.y"
{ /* obsolete */ }
break;
case 491:
#line 1625 "htcobol.y"
{ save_report( yyvsp[0].sval,yyvsp[-2].sval ); }
break;
case 492:
#line 1630 "htcobol.y"
{ UNIMPLEMENTED ("Code-set is alphabet") /* unimplemented */ }
break;
case 493:
#line 1638 "htcobol.y"
{ UNIMPLEMENTED ("Linage is clause") /* unimplemented */ }
break;
case 495:
#line 1642 "htcobol.y"
{ /* unimplemented */ }
break;
case 497:
#line 1646 "htcobol.y"
{ /* unimplemented */ }
break;
case 499:
#line 1650 "htcobol.y"
{ /* unimplemented */ }
break;
case 506:
#line 1663 "htcobol.y"
{ }
break;
case 507:
#line 1664 "htcobol.y"
{ }
break;
case 512:
#line 1672 "htcobol.y"
{ }
break;
case 513:
#line 1674 "htcobol.y"
{ yyval.sval = NULL; }
break;
case 514:
#line 1675 "htcobol.y"
{ yyval.sval = yyvsp[0].sval; }
break;
case 515:
#line 1678 "htcobol.y"
{ yyval.lval = NULL; }
break;
case 516:
#line 1679 "htcobol.y"
{ yyval.lval = yyvsp[0].lval; }
break;
case 519:
#line 1686 "htcobol.y"
{ yyval.lval = NULL; }
break;
case 520:
#line 1687 "htcobol.y"
{ yyval.lval = yyvsp[0].lval; }
break;
case 543:
#line 1745 "htcobol.y"
{
     curr_division = CDIV_PROC;
    }
break;
case 544:
#line 1751 "htcobol.y"
{
     if ((yyvsp[-2].ival == 2) && (yyvsp[-1].sval != NULL)) {
        yyerror("Invalid clause RETURNING used in PROCEDURE DIVISION with CHAINING clause");        
     }
     proc_header(yyvsp[-2].ival);
    }
break;
case 545:
#line 1759 "htcobol.y"
{
     /* close procedure_division sections & paragraphs */
     close_section(); /* this also closes paragraph */
     resolve_labels();
     proc_trail(yyvsp[-5].ival, yyvsp[-4].sval);
    }
break;
case 547:
#line 1771 "htcobol.y"
{
      decl_lbl=loc_label++;
      gen_jmplabel(decl_lbl);
     }
break;
case 548:
#line 1778 "htcobol.y"
{ 
      close_section(); 
      gen_decl_select(declaratives_list, decl_lbl);
      gen_dstlabel(decl_lbl);
      curr_paragr=NULL;
      curr_section=NULL; 
      /* UNIMPLEMENTED ("Declaratives") */
     }
break;
case 552:
#line 1795 "htcobol.y"
{
     close_section();
     open_section(yyvsp[0].sval);
    }
break;
case 553:
#line 1800 "htcobol.y"
{ 
     append_declaratives_list(yyvsp[-2].sval, yyvsp[0].udecl);    
    }
break;
case 554:
#line 1803 "htcobol.y"
{ yyerror("declaratives section name expected"); }
break;
case 556:
#line 1807 "htcobol.y"
{ close_paragr(); open_paragr(yyvsp[0].sval); }
break;
case 557:
#line 1808 "htcobol.y"
{free_expr_list(); stabs_line();}
break;
case 559:
#line 1809 "htcobol.y"
{ yyerror("unknown or wrong statement"); }
break;
case 561:
#line 1813 "htcobol.y"
{ yyval.udecl=yyvsp[0].udecl; }
break;
case 562:
#line 1814 "htcobol.y"
{ yyval.udecl=yyvsp[0].udecl; }
break;
case 563:
#line 1815 "htcobol.y"
{ yyval.udecl=yyvsp[0].udecl; }
break;
case 564:
#line 1821 "htcobol.y"
{  
     /* mark_decl_list($6); */ 
     yyval.udecl = define_declarative(TCB_DECLARATIVE_USE_TYPE_EXCEPTION, yyvsp[-1].deceo, yyvsp[-6].ival);
    }
break;
case 565:
#line 1825 "htcobol.y"
{ yyerror("use statement expected"); }
break;
case 570:
#line 1832 "htcobol.y"
{ 
      yyerror("Invalid use statement exception option"); 
     }
break;
case 571:
#line 1838 "htcobol.y"
{ yyval.deceo = yyvsp[0].deceo; }
break;
case 572:
#line 1840 "htcobol.y"
{
       yyval.deceo = set_declarative_exception_option_mode(yyvsp[0].ival);
     }
break;
case 573:
#line 1847 "htcobol.y"
{ 
     yyval.deceo = set_declarative_exception_option_name(yyvsp[0].sval, NULL); 
    }
break;
case 574:
#line 1851 "htcobol.y"
{
      yyval.deceo = set_declarative_exception_option_name(yyvsp[0].sval, yyvsp[-2].deceo);
     }
break;
case 575:
#line 1857 "htcobol.y"
{
     yyval.udecl=NULL;  
     UNIMPLEMENTED ("Declaratives - use reporting") 
    }
break;
case 576:
#line 1865 "htcobol.y"
{
     yyval.udecl=NULL;  
     UNIMPLEMENTED ("Declaratives - use debugging") 
    }
break;
case 581:
#line 1879 "htcobol.y"
{ yyval.ival=TCB_DECLARATIVE_USE_OPTION_NONE; }
break;
case 582:
#line 1880 "htcobol.y"
{ yyval.ival=TCB_DECLARATIVE_USE_OPTION_GLOBAL; }
break;
case 585:
#line 1887 "htcobol.y"
{ close_section(); open_section(yyvsp[0].sval); }
break;
case 586:
#line 1888 "htcobol.y"
{ close_paragr(); open_paragr(yyvsp[0].sval); }
break;
case 587:
#line 1889 "htcobol.y"
{free_expr_list(); stabs_line();}
break;
case 589:
#line 1891 "htcobol.y"
{ yyerror("unknown or wrong statement"); }
break;
case 591:
#line 1892 "htcobol.y"
{ }
break;
case 592:
#line 1899 "htcobol.y"
{
     struct sym *lab=yyvsp[-2].sval;
     if (lab->defined != 0) {
        lab = install(lab->name,SYTB_LAB,2);
     }
     lab->defined = 1;
     yyval.sval=lab;
    }
break;
case 593:
#line 1910 "htcobol.y"
{
     struct sym *lab=yyvsp[-1].sval;
     if (lab->defined != 0) {
             if ((lab=lookup_label(lab,curr_section))==NULL) {
                        lab = install(yyvsp[-1].sval->name,SYTB_LAB,2);
             }
     }
     lab->parent = curr_section;
     lab->defined=1;
     yyval.sval=lab;
    }
break;
case 596:
#line 1932 "htcobol.y"
{ }
break;
case 641:
#line 1981 "htcobol.y"
{ stabs_line(); }
break;
case 643:
#line 1991 "htcobol.y"
{ gen_dstlabel(yyvsp[0].dval); }
break;
case 645:
#line 1993 "htcobol.y"
{ yyval.dval=gen_passlabel(); gen_dstlabel(yyvsp[-1].dval); }
break;
case 646:
#line 1995 "htcobol.y"
{ gen_dstlabel(yyvsp[-1].dval); }
break;
case 650:
#line 2004 "htcobol.y"
{ yyval.ival = gen_evaluate_start(); }
break;
case 651:
#line 2006 "htcobol.y"
{ compute_subject_set_size(yyvsp[0].ssbjval); }
break;
case 652:
#line 2009 "htcobol.y"
{ release_sel_subject(yyvsp[-4].ival,yyvsp[-3].ssbjval); }
break;
case 655:
#line 2016 "htcobol.y"
{ yyval.sval=NULL; /* to store non-numeric symbols */ }
break;
case 656:
#line 2017 "htcobol.y"
{ yyval.ssbjval=save_sel_subject(yyvsp[0].ival,NULL,yyvsp[-1].sval); }
break;
case 657:
#line 2019 "htcobol.y"
{ yyval.sval=NULL; /* to store non-numeric symbols */ }
break;
case 658:
#line 2021 "htcobol.y"
{ yyval.ssbjval=save_sel_subject(yyvsp[0].ival,yyvsp[-3].ssbjval,yyvsp[-1].sval); }
break;
case 659:
#line 2025 "htcobol.y"
{
     if (push_expr(yyvsp[0].sval))
        yyval.ival=SSUBJ_EXPR;
     else {
        yyvsp[-1].sval = yyvsp[0].sval;
        yyval.ival=SSUBJ_STR;
     }
    }
break;
case 660:
#line 2033 "htcobol.y"
{ push_condition(); yyval.ival=SSUBJ_COND; }
break;
case 661:
#line 2034 "htcobol.y"
{ yyval.ival=SSUBJ_TRUE; }
break;
case 662:
#line 2035 "htcobol.y"
{ yyval.ival=SSUBJ_FALSE; }
break;
case 663:
#line 2038 "htcobol.y"
{ yyval.ival = loc_label++; /* mark end of "when" case */ }
break;
case 664:
#line 2039 "htcobol.y"
{ yyval.ssbjval=yyvsp[-3].ssbjval; /* store inherited subject set */ }
break;
case 665:
#line 2042 "htcobol.y"
{ yyval.ival=gen_end_when(yyvsp[-7].ival,yyvsp[-3].ival,yyvsp[0].ival); }
break;
case 666:
#line 2043 "htcobol.y"
{ yyval.ival = loc_label++; }
break;
case 667:
#line 2044 "htcobol.y"
{ yyval.ssbjval=yyvsp[-4].ssbjval; }
break;
case 668:
#line 2046 "htcobol.y"
{ gen_bypass_when_case(yyvsp[-4].ival); }
break;
case 669:
#line 2048 "htcobol.y"
{ yyval.ival=gen_end_when(yyvsp[-9].ival,yyvsp[-4].ival,yyvsp[0].ival); }
break;
case 670:
#line 2051 "htcobol.y"
{ yyval.sval = NULL; }
break;
case 671:
#line 2053 "htcobol.y"
{
      gen_when_check(0,yyvsp[-2].ssbjval,yyvsp[0].ival,yyvsp[-3].ival,yyvsp[-1].sval);
      yyval.ival=0;
    }
break;
case 672:
#line 2058 "htcobol.y"
{ yyval.sval = NULL; }
break;
case 673:
#line 2060 "htcobol.y"
{
       gen_when_check(yyvsp[-3].ival+1,yyvsp[-4].ssbjval,yyvsp[0].ival,yyvsp[-5].ival,yyvsp[-1].sval);
       yyval.ival=yyvsp[-3].ival+1;
      }
break;
case 674:
#line 2064 "htcobol.y"
{ yyval.ival=-1; }
break;
case 675:
#line 2067 "htcobol.y"
{ yyval.ival=SOBJ_ANY; }
break;
case 676:
#line 2068 "htcobol.y"
{ yyval.ival=SOBJ_TRUE; }
break;
case 677:
#line 2069 "htcobol.y"
{ yyval.ival=SOBJ_FALSE; }
break;
case 678:
#line 2071 "htcobol.y"
{
       if (push_expr(yyvsp[0].sval)) {
          if (yyvsp[-1].ival)
            yyval.ival=SOBJ_NEGEXPR;
          else
            yyval.ival=SOBJ_EXPR;
       }
       else {
          /* non-numeric comparation */
          yyvsp[-2].sval = yyvsp[0].sval;
          if (yyvsp[-1].ival)
            yyval.ival=SOBJ_NEGSTR;
          else
            yyval.ival=SOBJ_STR;
       }
      }
break;
case 679:
#line 2088 "htcobol.y"
{
       if (push_expr(yyvsp[0].sval) && push_expr(yyvsp[-2].sval)) {
          if (yyvsp[-3].ival)
             yyval.ival=SOBJ_NEGRANGE;
          else
             yyval.ival=SOBJ_RANGE;
       }
       else {
          yyerror("ranges only accepted for numeric variables");
       }
      }
break;
case 680:
#line 2100 "htcobol.y"
{
       gen_condition(yyvsp[0].sval);
       if (yyvsp[-1].ival)
          yyval.ival=SOBJ_NEGCOND;
       else
          yyval.ival=SOBJ_COND; 
     }
break;
case 681:
#line 2110 "htcobol.y"
{ yyval.ival = 0; }
break;
case 682:
#line 2111 "htcobol.y"
{ yyval.ival = 1; }
break;
case 683:
#line 2116 "htcobol.y"
{ yyval.dval=gen_testif(); }
break;
case 684:
#line 2118 "htcobol.y"
{ yyval.dval=yyvsp[-2].dval; }
break;
case 685:
#line 2126 "htcobol.y"
{ stabs_line(); }
break;
case 687:
#line 2127 "htcobol.y"
{ stabs_line(); }
break;
case 689:
#line 2134 "htcobol.y"
{ yyval.ival=0; }
break;
case 690:
#line 2135 "htcobol.y"
{ yyval.ival=1; }
break;
case 695:
#line 2145 "htcobol.y"
{
      yyval.dval=loc_label++; /* determine END label name */
      gen_marklabel(); 
      /* yydebug=1; */
    }
break;
case 696:
#line 2151 "htcobol.y"
{
      yyval.dval=loc_label++; /* determine search loop start label */
      if (yyvsp[0].sval == NULL) {
            yyvsp[0].sval=determine_table_index_name(yyvsp[-2].sval);
            if (yyvsp[0].sval == NULL) {
               yyerror("Unable to determine search index for table '%s'", yyvsp[-2].sval->name);
            }
      }
      gen_jmplabel(yyval.dval); /* generate GOTO search loop start  */
    }
break;
case 697:
#line 2162 "htcobol.y"
{
      gen_jmplabel(yyvsp[-3].dval); /* generate GOTO END  */
      gen_dstlabel(yyvsp[-1].dval); /* generate search loop start label */
      yyval.dval = yyvsp[-3].dval;
    }
break;
case 698:
#line 2168 "htcobol.y"
{
      /* increment loop index, check for end */
      gen_SearchLoopCheck(yyvsp[-2].dval, yyvsp[-4].sval, yyvsp[-6].sval);

      gen_jmplabel(yyvsp[-3].dval); /* generate goto search loop start label */
      gen_dstlabel(yyvsp[-5].dval); /* generate END label */
    }
break;
case 699:
#line 2178 "htcobol.y"
{
        lbend=loc_label++; /* determine END label name */
        gen_marklabel();

        lbstart=loc_label++; /* determine search_all loop start label */

        yyval.sval=determine_table_index_name(yyvsp[0].sval);
        if (yyval.sval == NULL) {
           yyerror("Unable to determine search index for table '%s'", yyvsp[0].sval->name);
        }
        else {
          /* Initilize and store search table index boundaries */
          Initialize_SearchAll_Boundaries(yyvsp[0].sval, yyval.sval);
        }

        gen_jmplabel(lbstart); /* generate GOTO search_all loop start  */
     }
break;
case 700:
#line 2196 "htcobol.y"
{
        gen_jmplabel(lbend); /* generate GOTO END  */
        gen_dstlabel(lbstart); /* generate search loop start label */
     }
break;
case 701:
#line 2201 "htcobol.y"
{
        /* adjust loop index, check for end */
        gen_SearchAllLoopCheck(yyvsp[-2].dval, yyvsp[-3].sval, yyvsp[-4].sval, curr_field, lbstart, lbend);
     }
break;
case 702:
#line 2208 "htcobol.y"
{  yyval.sval=yyvsp[0].sval; }
break;
case 703:
#line 2209 "htcobol.y"
{ yyval.sval=NULL; }
break;
case 704:
#line 2214 "htcobol.y"
{
       yyval.dval=loc_label++; /* determine ATEND label name */
       gen_dstlabel(yyval.dval); /* determine ATEND label name */
     }
break;
case 705:
#line 2219 "htcobol.y"
{
       yyval.dval=yyvsp[-1].dval;
     }
break;
case 706:
#line 2223 "htcobol.y"
{
       yyval.dval=loc_label++; /* determine ATEND label name */
       gen_dstlabel(yyval.dval); /* determine ATEND label name */
     }
break;
case 707:
#line 2230 "htcobol.y"
{ yyval.dval=yyvsp[0].dval; }
break;
case 708:
#line 2231 "htcobol.y"
{ yyval.dval=yyvsp[-1].dval; }
break;
case 709:
#line 2236 "htcobol.y"
{ yyval.dval=gen_testif(); }
break;
case 710:
#line 2238 "htcobol.y"
{
        yyval.dval = yyvsp[-4].dval;
        gen_jmplabel(yyval.dval); /* generate GOTO END  */
        gen_dstlabel(yyvsp[-1].dval);
     }
break;
case 713:
#line 2260 "htcobol.y"
{ gen_compare(yyvsp[-2].sval,yyvsp[-1].ival,yyvsp[0].sval); }
break;
case 716:
#line 2268 "htcobol.y"
{ curr_field = NULL; }
break;
case 717:
#line 2270 "htcobol.y"
{ yyval.dval=gen_testif(); }
break;
case 718:
#line 2272 "htcobol.y"
{
        gen_jmplabel(lbend); /* generate GOTO END  */
        gen_dstlabel(yyvsp[-1].dval);
     }
break;
case 721:
#line 2289 "htcobol.y"
{
      if (yyvsp[-2].ival != EQUAL)
         yyerror("Only = conditional allowed in search all statement");
      if (curr_field == NULL)
         curr_field = yyvsp[-4].sval;
      gen_compare(yyvsp[-4].sval,yyvsp[-2].ival,yyvsp[0].sval);
    }
break;
case 722:
#line 2297 "htcobol.y"
{
        if (yyvsp[-2].ival != EQUAL)
           yyerror("Only = conditional allowed in search all statement");
        if (curr_field == NULL)
           curr_field = yyvsp[-4].sval;
        gen_compare(yyvsp[-4].sval,yyvsp[-2].ival,(struct sym *)yyvsp[0].lval);
      }
break;
case 723:
#line 2304 "htcobol.y"
{ yyval.dval=gen_andstart(); }
break;
case 724:
#line 2305 "htcobol.y"
{ gen_dstlabel(yyvsp[-1].dval); }
break;
case 727:
#line 2314 "htcobol.y"
{ 
     gen_unlock(yyvsp[0].sval); 
     UNIMPLEMENTED ("UNLOCK clause") 
    }
break;
case 728:
#line 2320 "htcobol.y"
{ gen_tcob_proto1( yyvsp[0].sval ); }
break;
case 729:
#line 2321 "htcobol.y"
{ gen_tcob_proto2( yyvsp[-1].sval,yyvsp[0].sval ); }
break;
case 730:
#line 2324 "htcobol.y"
{ gen_trace_stm(1); }
break;
case 731:
#line 2325 "htcobol.y"
{ gen_trace_stm(0); }
break;
case 735:
#line 2337 "htcobol.y"
{ gen_cancel(yyvsp[0].sval); }
break;
case 736:
#line 2338 "htcobol.y"
{ gen_cancel(NULL); }
break;
case 737:
#line 2347 "htcobol.y"
{
     sort_keys_append(yyvsp[-4].sval, yyvsp[-3].glistval); 
     gen_sort(yyvsp[-4].sval, yyvsp[-1].sncval, yyvsp[0].sncval); 
    }
break;
case 738:
#line 2355 "htcobol.y"
{ yyval.sncval = alloc_node_container(TCB_SORT_NODE_TYPE_FILE, yyvsp[0].snval); }
break;
case 739:
#line 2364 "htcobol.y"
{
     sort_keys_append(yyvsp[-5].sval, yyvsp[-4].glistval); 
     gen_sort(yyvsp[-5].sval, yyvsp[-1].sncval, yyvsp[0].sncval); 
    }
break;
case 740:
#line 2371 "htcobol.y"
{ yyval.glistval=sort_keys_list_append(NULL, yyvsp[0].glistval); }
break;
case 741:
#line 2372 "htcobol.y"
{ yyval.glistval=sort_keys_list_append(yyvsp[-1].glistval, yyvsp[0].glistval);  }
break;
case 742:
#line 2377 "htcobol.y"
{ yyval.glistval=sort_key_list_create(yyvsp[0].glistval, yyvsp[-2].ival); }
break;
case 743:
#line 2381 "htcobol.y"
{ yyval.glistval = gvar_list_append(NULL, yyvsp[0].sval, source_lineno); }
break;
case 744:
#line 2382 "htcobol.y"
{ yyval.glistval = gvar_list_append(yyvsp[-1].glistval, yyvsp[0].sval, source_lineno); }
break;
case 746:
#line 2387 "htcobol.y"
{ 
       UNIMPLEMENTED ("SORT with duplicates in order clause") 
       /* unimplemented */ 
      }
break;
case 748:
#line 2395 "htcobol.y"
{ UNIMPLEMENTED ("SORT/MERGE collating sequence clause") /* unimplemented */ }
break;
case 749:
#line 2401 "htcobol.y"
{ yyval.sncval = alloc_node_container(TCB_SORT_NODE_TYPE_PROC, yyvsp[0].snval); }
break;
case 750:
#line 2403 "htcobol.y"
{ yyval.sncval = alloc_node_container(TCB_SORT_NODE_TYPE_FILE, yyvsp[0].snval); }
break;
case 751:
#line 2407 "htcobol.y"
{ yyval.sncval = alloc_node_container(TCB_SORT_NODE_TYPE_PROC, yyvsp[0].snval); }
break;
case 752:
#line 2409 "htcobol.y"
{ yyval.sncval = alloc_node_container(TCB_SORT_NODE_TYPE_FILE, yyvsp[0].snval); }
break;
case 753:
#line 2413 "htcobol.y"
{ yyval.snval = alloc_sortfile_node(yyvsp[0].sval); }
break;
case 754:
#line 2415 "htcobol.y"
{ yyval.snval = append_sortfile_node(TCB_SORT_NODE_TYPE_FILE, yyvsp[-1].snval, yyvsp[0].sval); }
break;
case 755:
#line 2420 "htcobol.y"
{ gen_moves(yyvsp[-2].sval, yyvsp[0].glistval); }
break;
case 756:
#line 2421 "htcobol.y"
{ gen_movecorr(yyvsp[-2].sval, yyvsp[0].sval); }
break;
case 757:
#line 2422 "htcobol.y"
{ gen_movelength(yyvsp[-2].sval, yyvsp[0].sval); }
break;
case 758:
#line 2423 "htcobol.y"
{ yyerror("Expected variable"); }
break;
case 759:
#line 2427 "htcobol.y"
{ gen_initializes(yyvsp[-1].glistval); }
break;
case 760:
#line 2428 "htcobol.y"
{ yyerror("INITIALIZE: expected a variable name");}
break;
case 762:
#line 2432 "htcobol.y"
{ UNIMPLEMENTED ("INITIALIZE ... REPLACING clause") }
break;
case 765:
#line 2439 "htcobol.y"
{ /* not implimented */ }
break;
case 766:
#line 2441 "htcobol.y"
{ }
break;
case 767:
#line 2442 "htcobol.y"
{ }
break;
case 768:
#line 2443 "htcobol.y"
{ }
break;
case 769:
#line 2444 "htcobol.y"
{ }
break;
case 770:
#line 2445 "htcobol.y"
{ }
break;
case 772:
#line 2451 "htcobol.y"
{ yyerror(err_msg_bad_form, "COMPUTE");}
break;
case 773:
#line 2455 "htcobol.y"
{
      if (yyvsp[-2].ival != EQUAL)
        yyerror("= expected");
      else if (yyvsp[0].mose == NULL)
        gen_compute1(yyvsp[-3].mval, yyvsp[-1].sval);
      else
        gen_compute2(yyvsp[-3].mval, yyvsp[-1].sval, yyvsp[0].mose);
      delete_mathvar_info(yyvsp[-3].mval);
      if (yyvsp[0].mose != NULL)
        tmose = NULL;
    }
break;
case 777:
#line 2475 "htcobol.y"
{ yyerror(err_msg_bad_form, "ADD");}
break;
case 778:
#line 2479 "htcobol.y"
{
        gen_add1(yyvsp[-3].mval, yyvsp[-1].mval, yyvsp[0].mose);
        delete_mathvar_info(yyvsp[-3].mval);
        delete_mathvar_info(yyvsp[-1].mval);
        if (yyvsp[0].mose != NULL)	
          tmose = NULL;
    }
break;
case 779:
#line 2487 "htcobol.y"
{
        gen_add2(yyvsp[-4].mval, yyvsp[-1].mval, yyvsp[-3].sval, yyvsp[0].mose);
        delete_mathvar_info(yyvsp[-4].mval);
        delete_mathvar_info(yyvsp[-1].mval);
        if (yyvsp[0].mose != NULL)	
          tmose = NULL;
      }
break;
case 780:
#line 2495 "htcobol.y"
{
        gen_addcorr1(yyvsp[-4].mval, yyvsp[-2].mval, yyvsp[-1].ival, yyvsp[0].mose);
        delete_mathvar_info(yyvsp[-4].mval);
        delete_mathvar_info(yyvsp[-2].mval);
        if (yyvsp[0].mose != NULL)	
          tmose = NULL;
      }
break;
case 781:
#line 2504 "htcobol.y"
{ yyval.sval = NULL; }
break;
case 782:
#line 2505 "htcobol.y"
{ yyval.sval = yyvsp[0].sval; }
break;
case 786:
#line 2516 "htcobol.y"
{ yyerror(err_msg_bad_form, "SUBTRACT");}
break;
case 787:
#line 2520 "htcobol.y"
{
        gen_subtract1(yyvsp[-3].mval, yyvsp[-1].mval, yyvsp[0].mose);
        delete_mathvar_info(yyvsp[-3].mval);
        delete_mathvar_info(yyvsp[-1].mval);
        if (yyvsp[0].mose != NULL)
          tmose = NULL;
      }
break;
case 788:
#line 2528 "htcobol.y"
{
        assert_numeric_sy(yyvsp[-3].sval);
        gen_subtract2(yyvsp[-5].mval, yyvsp[-1].mval, yyvsp[-3].sval, yyvsp[0].mose);
        delete_mathvar_info(yyvsp[-5].mval);
        delete_mathvar_info(yyvsp[-1].mval);
        if (yyvsp[0].mose != NULL)
          tmose = NULL;
      }
break;
case 789:
#line 2537 "htcobol.y"
{
        gen_subtractcorr1(yyvsp[-4].mval, yyvsp[-2].mval, yyvsp[-1].ival, yyvsp[0].mose);
        delete_mathvar_info(yyvsp[-4].mval);
        delete_mathvar_info(yyvsp[-2].mval);
        if (yyvsp[0].mose != NULL)
          tmose = NULL;
      }
break;
case 793:
#line 2553 "htcobol.y"
{ yyerror(err_msg_bad_form, "MULTIPLY");}
break;
case 794:
#line 2557 "htcobol.y"
{
        assert_numeric_sy(yyvsp[-5].sval);
        assert_numeric_sy(yyvsp[-3].sval);
        gen_multiply2(yyvsp[-1].mval, yyvsp[-5].sval, yyvsp[-3].sval, yyvsp[0].mose);
        delete_mathvar_info(yyvsp[-1].mval);
        if (yyvsp[0].mose != NULL)
          tmose = NULL;
      }
break;
case 795:
#line 2566 "htcobol.y"
{
        assert_numeric_sy(yyvsp[-3].sval);
        gen_multiply1(yyvsp[-1].mval, yyvsp[-3].sval, yyvsp[0].mose);
        delete_mathvar_info(yyvsp[-1].mval);
        if (yyvsp[0].mose != NULL)
          tmose = NULL;
      }
break;
case 799:
#line 2583 "htcobol.y"
{ yyerror(err_msg_bad_form, "DIVIDE");}
break;
case 800:
#line 2587 "htcobol.y"
{
        assert_numeric_sy(yyvsp[-5].sval);
        assert_numeric_sy(yyvsp[-3].sval);
        gen_divide2(yyvsp[-1].mval, yyvsp[-5].sval, yyvsp[-3].sval, yyvsp[0].mose);
        delete_mathvar_info(yyvsp[-1].mval);
        if (yyvsp[0].mose != NULL)
          tmose = NULL;
      }
break;
case 801:
#line 2596 "htcobol.y"
{
        assert_numeric_sy(yyvsp[-8].sval);
        assert_numeric_sy(yyvsp[-6].sval);
        assert_numeric_dest_sy(yyvsp[-4].sval);
        gen_divide4(yyvsp[-8].sval, yyvsp[-6].sval, yyvsp[-4].sval, yyvsp[-1].sval, yyvsp[-3].ival, yyvsp[0].mose);
        if (yyvsp[0].mose != NULL)
          tmose = NULL;
      }
break;
case 802:
#line 2605 "htcobol.y"
{
        assert_numeric_sy(yyvsp[-8].sval);
        assert_numeric_sy(yyvsp[-6].sval);
        assert_numeric_dest_sy(yyvsp[-4].sval);
        gen_divide4(yyvsp[-6].sval, yyvsp[-8].sval, yyvsp[-4].sval, yyvsp[-1].sval, yyvsp[-3].ival, yyvsp[0].mose);
        if (yyvsp[0].mose != NULL)
          tmose = NULL;
      }
break;
case 803:
#line 2614 "htcobol.y"
{
        assert_numeric_sy(yyvsp[-5].sval);
        assert_numeric_sy(yyvsp[-3].sval);
        gen_divide2(yyvsp[-1].mval, yyvsp[-3].sval, yyvsp[-5].sval, yyvsp[0].mose);
        delete_mathvar_info(yyvsp[-1].mval);
        if (yyvsp[0].mose != NULL)
          tmose = NULL;
      }
break;
case 804:
#line 2623 "htcobol.y"
{
        assert_numeric_sy(yyvsp[-3].sval);
        gen_divide1(yyvsp[-1].mval, yyvsp[-3].sval, yyvsp[0].mose);
        delete_mathvar_info(yyvsp[-1].mval);
        if (yyvsp[0].mose != NULL)
          tmose = NULL;
      }
break;
case 810:
#line 2641 "htcobol.y"
{ yyerror(err_msg_bad_form, "ACCEPT");}
break;
case 811:
#line 2644 "htcobol.y"
{ gen_accept(yyvsp[-1].sval, 0, 1); }
break;
case 813:
#line 2645 "htcobol.y"
{  gen_accept_from_inkey(yyvsp[-3].sval); }
break;
case 814:
#line 2646 "htcobol.y"
{  gen_accept_from_inkey(yyvsp[-4].sval); }
break;
case 815:
#line 2647 "htcobol.y"
{  gen_accept_from_cmdline(yyvsp[-3].sval); }
break;
case 816:
#line 2649 "htcobol.y"
{
      gen_accept_env_var(yyvsp[-4].sval, yyvsp[-1].sval);
    }
break;
case 817:
#line 2653 "htcobol.y"
{ yyval.sval=yyvsp[0].sval; }
break;
case 818:
#line 2655 "htcobol.y"
{
      save_literal(yyvsp[0].lval,'X');
      yyvsp[0].lval->all=0;
      yyval.sval=(struct sym *)yyvsp[0].lval;
     }
break;
case 823:
#line 2667 "htcobol.y"
{ 
      gen_store_fnres(yyvsp[0].sval); 
      yyval.dval = gen_check_zero();
    }
break;
case 824:
#line 2671 "htcobol.y"
{ gen_dstlabel(yyvsp[-1].dval); }
break;
case 825:
#line 2675 "htcobol.y"
{
       gen_accept_from_chron(yyvsp[-3].sval, yyvsp[-1].ival, 0);
    }
break;
case 826:
#line 2681 "htcobol.y"
{ 
                          gen_accept(yyvsp[-2].sval, yyvsp[-1].ival, 1); 
                        }
break;
case 827:
#line 2685 "htcobol.y"
{ 
                          screen_io_enable++; 
                          HTG_prg_uses_term = 1; 
                          gen_accept(yyvsp[-3].sval, yyvsp[-2].ival, 1); 
                        }
break;
case 828:
#line 2690 "htcobol.y"
{ 
                          gen_store_fnres(yyvsp[0].sval); 
                          yyval.dval = gen_check_zero();
                        }
break;
case 829:
#line 2694 "htcobol.y"
{ gen_dstlabel(yyvsp[-1].dval); }
break;
case 835:
#line 2706 "htcobol.y"
{ yyerror(err_msg_bad_form, "DISPLAY");}
break;
case 836:
#line 2710 "htcobol.y"
{ gen_display_line(yyvsp[-2].ival, yyvsp[-1].ival); }
break;
case 837:
#line 2714 "htcobol.y"
{ gen_display_screen(yyvsp[-1].ival); }
break;
case 838:
#line 2717 "htcobol.y"
{ put_disp_list(yyvsp[0].sval); }
break;
case 839:
#line 2718 "htcobol.y"
{ put_disp_list(yyvsp[0].sval); }
break;
case 840:
#line 2721 "htcobol.y"
{ yyval.ival = 1; }
break;
case 841:
#line 2722 "htcobol.y"
{ yyval.ival = 1; }
break;
case 842:
#line 2723 "htcobol.y"
{ yyval.ival = 2; }
break;
case 843:
#line 2726 "htcobol.y"
{ yyval.ival = 0; }
break;
case 844:
#line 2727 "htcobol.y"
{ yyval.ival = yyvsp[-3].ival | SCR_NO_ADVANCING; }
break;
case 845:
#line 2728 "htcobol.y"
{ yyval.ival = yyvsp[-2].ival | SCR_ERASE_EOL; }
break;
case 846:
#line 2729 "htcobol.y"
{ yyval.ival = yyvsp[-3].ival | SCR_ERASE_EOS; }
break;
case 847:
#line 2730 "htcobol.y"
{ yyval.ival = yyvsp[-3].ival | SCR_ERASE_EOL; }
break;
case 848:
#line 2731 "htcobol.y"
{ yyval.ival = yyvsp[-3].ival | SCR_ERASE_EOS; }
break;
case 851:
#line 2744 "htcobol.y"
{
      screen_io_enable++;
      HTG_prg_uses_term = 1;
      push_expr(yyvsp[0].sval);
      gen_gotoy_expr();
     }
break;
case 852:
#line 2753 "htcobol.y"
{
      screen_io_enable++;
      HTG_prg_uses_term = 1; 
      push_expr(yyvsp[0].sval);
      gen_gotox_expr();
     }
break;
case 853:
#line 2760 "htcobol.y"
{
      screen_io_enable++;
      HTG_prg_uses_term = 1; 
      push_expr(yyvsp[0].sval);
      gen_gotox_expr();
     }
break;
case 854:
#line 2769 "htcobol.y"
{
      screen_io_enable++;
      HTG_prg_uses_term = 1; 
      scr_push_display_position(yyvsp[0].lval);
     }
break;
case 855:
#line 2775 "htcobol.y"
{
      screen_io_enable++;
      HTG_prg_uses_term = 1; 
      scr_push_display_position(yyvsp[0].sval);
     }
break;
case 856:
#line 2782 "htcobol.y"
{ yyval.ival = yyvsp[0].ival; }
break;
case 857:
#line 2783 "htcobol.y"
{ yyval.ival = yyvsp[-1].ival | yyvsp[0].ival; }
break;
case 858:
#line 2786 "htcobol.y"
{ yyval.ival = 0; }
break;
case 859:
#line 2787 "htcobol.y"
{ yyval.ival = yyvsp[-1].ival | yyvsp[0].ival; }
break;
case 860:
#line 2790 "htcobol.y"
{ yyval.ival = yyvsp[0].ival; }
break;
case 861:
#line 2791 "htcobol.y"
{ yyval.ival = 0; }
break;
case 862:
#line 2792 "htcobol.y"
{ yyval.ival = 0; }
break;
case 863:
#line 2793 "htcobol.y"
{ yyval.ival = 0; }
break;
case 864:
#line 2799 "htcobol.y"
{ 
     HTG_prg_uses_fileio = 1;
     gen_open_stm(yyvsp[0].fopenl); 
    }
break;
case 865:
#line 2803 "htcobol.y"
{ yyerror(err_msg_bad_form, "OPEN");}
break;
case 866:
#line 2806 "htcobol.y"
{ yyval.fopenl=set_file_open_stm_list(yyvsp[-1].ival, yyvsp[0].fopenl, NULL); }
break;
case 867:
#line 2807 "htcobol.y"
{ yyval.fopenl=set_file_open_stm_list(yyvsp[-1].ival, yyvsp[0].fopenl, yyvsp[-2].fopenl); }
break;
case 868:
#line 2810 "htcobol.y"
{ yyval.ival=TCB_FILE_OPEN_MODE_INPUT; }
break;
case 869:
#line 2811 "htcobol.y"
{ yyval.ival=TCB_FILE_OPEN_MODE_IO; }
break;
case 870:
#line 2812 "htcobol.y"
{ yyval.ival=TCB_FILE_OPEN_MODE_OUTPUT; }
break;
case 871:
#line 2813 "htcobol.y"
{ yyval.ival=TCB_FILE_OPEN_MODE_EXTEND; }
break;
case 872:
#line 2815 "htcobol.y"
{ 
      yyval.ival=TCB_FILE_OPEN_MODE_NONE;
      yyerror("invalid or missing file OPEN mode"); 
     }
break;
case 873:
#line 2821 "htcobol.y"
{ yyval.fopenl=set_file_open_stm(yyvsp[0].sval, NULL); }
break;
case 874:
#line 2822 "htcobol.y"
{ yyval.fopenl=set_file_open_stm(yyvsp[0].sval, yyvsp[-2].fopenl); }
break;
case 876:
#line 2828 "htcobol.y"
{ yyerror(err_msg_bad_form, "CLOSE");}
break;
case 879:
#line 2835 "htcobol.y"
{ gen_close(yyvsp[-1].sval); }
break;
case 880:
#line 2839 "htcobol.y"
{ 
     yyval.ival=0; 
     UNIMPLEMENTED ("CLOSE options clause") 
    }
break;
case 881:
#line 2843 "htcobol.y"
{ yyval.ival=yyvsp[0].ival; }
break;
case 882:
#line 2846 "htcobol.y"
{  }
break;
case 883:
#line 2847 "htcobol.y"
{  }
break;
case 884:
#line 2848 "htcobol.y"
{  }
break;
case 885:
#line 2849 "htcobol.y"
{  }
break;
case 886:
#line 2850 "htcobol.y"
{  }
break;
case 887:
#line 2854 "htcobol.y"
{ 
     yyval.ival=1; 
     UNIMPLEMENTED ("WITH LOCK clause") 
    }
break;
case 888:
#line 2859 "htcobol.y"
{ 
      yyval.ival=2; 
      UNIMPLEMENTED ("IGNORE LOCK clause") 
     }
break;
case 889:
#line 2863 "htcobol.y"
{ yyval.ival=0; }
break;
case 891:
#line 2870 "htcobol.y"
{ yyerror(err_msg_bad_form, "RETURN");}
break;
case 892:
#line 2876 "htcobol.y"
{    
     if (gen_reads(yyvsp[-2].sval, yyvsp[0].sval, NULL, 1, 4, 0) != 0) {
        YYABORT;
     }
    }
break;
case 893:
#line 2885 "htcobol.y"
{    
     if (gen_reads(yyvsp[-3].sval, yyvsp[-1].sval, NULL, 1, 5, 0) != 0) {
        YYABORT;
     }
     else {
        ginfo_container4(yyvsp[0].gic);
        gic = NULL;
     }
    }
break;
case 894:
#line 2899 "htcobol.y"
{ }
break;
case 895:
#line 2900 "htcobol.y"
{ yyerror(err_msg_bad_form, "READ");}
break;
case 896:
#line 2909 "htcobol.y"
{
     if (gen_reads(yyvsp[-5].sval, yyvsp[-2].sval, yyvsp[0].sval, yyvsp[-4].ival, 0, yyvsp[-1].ival) != 0) {
        YYABORT;
     }
     else {
        gen_perform_decl(yyvsp[-5].sval, NULL);
     }
    }
break;
case 897:
#line 2924 "htcobol.y"
{    
     if (gen_reads(yyvsp[-6].sval, yyvsp[-3].sval, yyvsp[-1].sval, yyvsp[-5].ival, 1, yyvsp[-2].ival) != 0) {
        YYABORT;
     }
     else {
        ginfo_container4(yyvsp[0].gic);
        gen_perform_decl(yyvsp[-6].sval, (void*)yyvsp[0].gic);
        gic = NULL;
     }
    }
break;
case 898:
#line 2941 "htcobol.y"
{    
     if (gen_reads(yyvsp[-6].sval, yyvsp[-3].sval, yyvsp[-1].sval, yyvsp[-5].ival, 2, yyvsp[-2].ival) != 0) {
        YYABORT;
     }
     else {
       gen_test_invalid_keys (yyvsp[0].iks, yyvsp[-6].sval, TCB_STATUS_23_KEY_NOT_EXISTS);
       gen_perform_decl(yyvsp[-6].sval, (void*)yyvsp[0].iks); 
     }
    }
break;
case 899:
#line 2952 "htcobol.y"
{ yyval.ival = 0; }
break;
case 900:
#line 2953 "htcobol.y"
{ yyval.ival = 1; }
break;
case 901:
#line 2954 "htcobol.y"
{ yyval.ival = 2; }
break;
case 902:
#line 2957 "htcobol.y"
{ yyval.sval = NULL; }
break;
case 903:
#line 2958 "htcobol.y"
{ yyval.sval = yyvsp[0].sval; }
break;
case 904:
#line 2961 "htcobol.y"
{ yyval.sval = NULL; }
break;
case 905:
#line 2962 "htcobol.y"
{ yyval.sval = yyvsp[0].sval; }
break;
case 906:
#line 2966 "htcobol.y"
{
      ginfo_container2(yyvsp[0].gic, 2);
      yyval.gic=ginfo_container3(yyvsp[0].gic, 2);
     }
break;
case 907:
#line 2971 "htcobol.y"
{
      ginfo_container2(yyvsp[0].gic, 1);
      yyval.gic=ginfo_container3(yyvsp[0].gic, 1);
     }
break;
case 908:
#line 2976 "htcobol.y"
{
      ginfo_container2(yyvsp[0].gic, 1);
      yyval.gic=ginfo_container3(yyvsp[0].gic, 1);
     }
break;
case 909:
#line 2981 "htcobol.y"
{ 
      ginfo_container2(yyvsp[-2].gic, 1);
     }
break;
case 910:
#line 2985 "htcobol.y"
{ 
      ginfo_container2(yyvsp[0].gic, 2);
      yyval.gic=ginfo_container3(yyvsp[0].gic, 3);
     }
break;
case 911:
#line 2990 "htcobol.y"
{ 
      ginfo_container2(yyvsp[-2].gic, 1);
     }
break;
case 912:
#line 2994 "htcobol.y"
{ 
      ginfo_container2(yyvsp[0].gic, 2);
      yyval.gic=ginfo_container3(yyvsp[0].gic, 3);
     }
break;
case 913:
#line 3001 "htcobol.y"
{ 
      if ( gic == NULL ) {
         gic=ginfo_container0();
      }
      yyval.gic=ginfo_container1(gic);
      stabs_line();
    }
break;
case 914:
#line 3009 "htcobol.y"
{ 
      yyval.gic=yyvsp[-1].gic;
    }
break;
case 915:
#line 3014 "htcobol.y"
{ yyval.iks = gen_invalid_keys (yyvsp[0].ike, NULL); }
break;
case 916:
#line 3015 "htcobol.y"
{ yyval.iks = gen_invalid_keys (NULL, yyvsp[0].ike); }
break;
case 917:
#line 3016 "htcobol.y"
{ yyval.iks = gen_invalid_keys (yyvsp[-1].ike, yyvsp[0].ike); }
break;
case 918:
#line 3019 "htcobol.y"
{ yyval.ike = gen_before_invalid_key (); }
break;
case 919:
#line 3020 "htcobol.y"
{ yyval.ike = gen_after_invalid_key (yyvsp[-1].ike); }
break;
case 920:
#line 3023 "htcobol.y"
{ yyval.ike = gen_before_invalid_key (); }
break;
case 921:
#line 3024 "htcobol.y"
{ yyval.ike = gen_after_invalid_key (yyvsp[-1].ike); }
break;
case 926:
#line 3039 "htcobol.y"
{
      gen_release(yyvsp[-1].sval, yyvsp[0].sval);
    }
break;
case 927:
#line 3044 "htcobol.y"
{ yyval.sval = NULL; }
break;
case 928:
#line 3045 "htcobol.y"
{ yyval.sval = yyvsp[0].sval; }
break;
case 929:
#line 3052 "htcobol.y"
{ }
break;
case 930:
#line 3065 "htcobol.y"
{
     if (yyvsp[-5].sval->level != 1) {
        yyerror("Identifier %s may not be used in WRITE statement", yyvsp[-5].sval->name);
     }
     else {
        if (write_advancing_sw == 0) 
           gen_write(yyvsp[-5].sval, yyvsp[-3].sval, yyvsp[-4].sval); 
        else
           gen_write_adv(yyvsp[-5].sval, yyvsp[-3].sval, yyvsp[-4].sval, write_advancing_sw); 
        gen_test_invalid_keys(yyvsp[-1].iks, yyvsp[-5].sval, TCB_STATUS_22_KEY_EXISTS);
        if (yyvsp[-5].sval->ix_desc != NULL)         
          gen_perform_decl(yyvsp[-5].sval->ix_desc, (void*)yyvsp[-1].iks);
        else 
          yyerror("Unknown error : file name not found for WRITE variable %s", yyvsp[-5].sval->name);
     }
    }
break;
case 931:
#line 3083 "htcobol.y"
{ yyval.sval = NULL; }
break;
case 932:
#line 3084 "htcobol.y"
{ yyval.sval = yyvsp[0].sval; }
break;
case 933:
#line 3087 "htcobol.y"
{ yyval.sval = NULL; write_advancing_sw = 0; }
break;
case 934:
#line 3089 "htcobol.y"
{ 
       /* gen_loadvar($3); */
       yyval.sval = yyvsp[-1].sval; 
       write_advancing_sw = yyvsp[-3].ival; 
     }
break;
case 935:
#line 3095 "htcobol.y"
{ 
       write_advancing_sw = -yyvsp[-2].ival;
       yyval.sval = NULL; 
      }
break;
case 938:
#line 3109 "htcobol.y"
{ }
break;
case 939:
#line 3116 "htcobol.y"
{
     if (yyvsp[-4].sval->level != 1) {
        yyerror("Identifier %s may not be used in REWRITE statement", yyvsp[-4].sval->name);
     }
     else {
        gen_rewrite(yyvsp[-4].sval, yyvsp[-3].sval);
        gen_test_invalid_keys (yyvsp[-1].iks, yyvsp[-4].sval, TCB_STATUS_22_KEY_EXISTS);
        if (yyvsp[-4].sval->ix_desc != NULL)         
           gen_perform_decl(yyvsp[-4].sval->ix_desc, (void*)yyvsp[-1].iks);
        else 
           yyerror("Unknown error : file name not found for REWRITE variable %s", yyvsp[-4].sval->name);
     }
    }
break;
case 942:
#line 3139 "htcobol.y"
{ 
     gen_delete(yyvsp[-1].sval); 
    }
break;
case 943:
#line 3144 "htcobol.y"
{
     gen_test_invalid_keys (yyvsp[-1].iks, yyvsp[-4].sval, TCB_STATUS_23_KEY_NOT_EXISTS);
     gen_perform_decl(yyvsp[-4].sval, (void*)yyvsp[-1].iks);
    }
break;
case 946:
#line 3159 "htcobol.y"
{
     gen_test_invalid_keys (yyvsp[0].iks, yyvsp[-1].sval, TCB_STATUS_23_KEY_NOT_EXISTS);
     gen_perform_decl(yyvsp[-1].sval, (void*)yyvsp[0].iks);
    }
break;
case 948:
#line 3167 "htcobol.y"
{
     gen_start(yyvsp[0].sval, 0, NULL); 
     yyval.sval = yyvsp[0].sval;
    }
break;
case 949:
#line 3172 "htcobol.y"
{ 
     gen_start(yyvsp[-4].sval, yyvsp[-1].ival, yyvsp[0].sval); 
     yyval.sval = yyvsp[-4].sval;
    }
break;
case 952:
#line 3189 "htcobol.y"
{ gen_goto(yyvsp[0].lstval); }
break;
case 953:
#line 3191 "htcobol.y"
{
    	if (is_numeric_sy(yyvsp[0].sval))
      gen_goto_depending(yyvsp[-3].lstval, yyvsp[0].sval);
     else yyerror("variable '%s' must be numeric", yyvsp[0].sval->name);
    }
break;
case 954:
#line 3197 "htcobol.y"
{ yyval.lstval = insert_list(NULL, yyvsp[0].sval); }
break;
case 955:
#line 3200 "htcobol.y"
{ yyval.lstval = insert_list(NULL, yyvsp[0].sval); }
break;
case 956:
#line 3201 "htcobol.y"
{ yyval.lstval = insert_list(yyvsp[-1].lstval, yyvsp[0].sval); }
break;
case 957:
#line 3202 "htcobol.y"
{ yyval.lstval = insert_list(yyvsp[-2].lstval, yyvsp[0].sval); }
break;
case 958:
#line 3207 "htcobol.y"
{ curr_call_mode=CM_REF; }
break;
case 959:
#line 3212 "htcobol.y"
{ yyval.ival = loc_label++; /* exception check */ }
break;
case 960:
#line 3213 "htcobol.y"
{ yyval.ival = loc_label++; /* not exception check */ }
break;
case 961:
#line 3214 "htcobol.y"
{ 
      yyval.ival = emt_call((struct lit *)yyvsp[-4].sval, yyvsp[-3].ival, yyvsp[-1].ival, yyvsp[0].ival, yyvsp[-2].sval); 
      /* gen_store_fnres($6); */
      /* If paramater is a variable then dynamic link libs are required */
/*
      if ($4->litflag == 0 ) {
         HTG_prg_uses_dcall = 1;
      }				 
*/
    }
break;
case 962:
#line 3225 "htcobol.y"
{ check_call_except(yyvsp[-1].ival, yyvsp[0].ival, yyvsp[-4].ival, yyvsp[-3].ival, yyvsp[-2].ival); }
break;
case 964:
#line 3227 "htcobol.y"
{ yyerror(err_msg_bad_form, "CALL"); }
break;
case 965:
#line 3230 "htcobol.y"
{ curr_call_convention = 0; }
break;
case 966:
#line 3231 "htcobol.y"
{ curr_call_convention = 0; }
break;
case 967:
#line 3232 "htcobol.y"
{ curr_call_convention = 1; }
break;
case 968:
#line 3240 "htcobol.y"
{
     emt_call_loadlib((struct lit *)yyvsp[0].sval); 
    }
break;
case 970:
#line 3244 "htcobol.y"
{ yyerror(err_msg_bad_form, "CALL-LOADLIB"); }
break;
case 971:
#line 3248 "htcobol.y"
{ }
break;
case 972:
#line 3249 "htcobol.y"
{ }
break;
case 973:
#line 3254 "htcobol.y"
{ curr_call_mode=CM_CHAIN; }
break;
case 974:
#line 3256 "htcobol.y"
{ yyval.ival = loc_label++; /* exception check */ }
break;
case 975:
#line 3257 "htcobol.y"
{ yyval.ival = gen_chain(yyvsp[-2].sval,yyvsp[-1].ival,yyvsp[0].ival); }
break;
case 976:
#line 3259 "htcobol.y"
{/* check_call_except($9,$10,$<ival>6,$<ival>7,$<ival>8);*/ }
break;
case 978:
#line 3261 "htcobol.y"
{ yyerror(err_msg_bad_form, "CHAIN"); }
break;
case 979:
#line 3266 "htcobol.y"
{ gen_exit(0); }
break;
case 980:
#line 3267 "htcobol.y"
{ gen_exit(0); }
break;
case 981:
#line 3268 "htcobol.y"
{ gen_exit(1); }
break;
case 982:
#line 3273 "htcobol.y"
{ gen_stoprun(); }
break;
case 983:
#line 3275 "htcobol.y"
{
      struct sym *sy;
      gen_display_line(2, SCR_NO_ADVANCING);
      sy = define_temp_field(DTYPE_ALPHANUMERIC,1);
      gen_accept(sy, 0, 1);
     }
break;
case 984:
#line 3284 "htcobol.y"
{
      save_literal(yyvsp[0].lval,'X');
      yyvsp[0].lval->all=0;
      put_disp_list((struct sym *)yyvsp[0].lval);
    }
break;
case 985:
#line 3290 "htcobol.y"
{
      save_literal(yyvsp[0].lval,'X');
      yyvsp[0].lval->all=0;
      put_disp_list((struct sym *)yyvsp[0].lval);
     }
break;
case 986:
#line 3299 "htcobol.y"
{ gen_goback(); }
break;
case 987:
#line 3303 "htcobol.y"
{
      yyval.mval = create_mathvar_info(NULL, yyvsp[-2].sval, yyvsp[-1].ival);
     }
break;
case 988:
#line 3307 "htcobol.y"
{
      yyval.mval = create_mathvar_info(yyvsp[-3].mval, yyvsp[-2].sval, yyvsp[-1].ival);
     }
break;
case 989:
#line 3313 "htcobol.y"
{
      yyval.mval = create_mathvar_info(NULL, yyvsp[-1].sval, 0);
     }
break;
case 990:
#line 3317 "htcobol.y"
{
      yyval.mval = create_mathvar_info(yyvsp[-2].mval, yyvsp[-1].sval, 0);
     }
break;
case 991:
#line 3323 "htcobol.y"
{ yyval.ival=0; }
break;
case 992:
#line 3324 "htcobol.y"
{ yyval.ival=1; }
break;
case 993:
#line 3329 "htcobol.y"
{
       yyval.mose=NULL;
      }
break;
case 994:
#line 3334 "htcobol.y"
{
       yyval.mose=math_on_size_error4(yyvsp[0].mose, 2);
      }
break;
case 995:
#line 3339 "htcobol.y"
{
       yyval.mose=math_on_size_error4(yyvsp[0].mose, 1);
      }
break;
case 996:
#line 3345 "htcobol.y"
{
       yyvsp[-3].mose->lbl1=yyvsp[-3].mose->ose;
      }
break;
case 997:
#line 3349 "htcobol.y"
{
       yyval.mose=math_on_size_error4(yyvsp[0].mose, 3);
      }
break;
case 998:
#line 3356 "htcobol.y"
{
      if ( tmose == NULL ) {
         tmose=math_on_size_error0();
         yyval.mose=math_on_size_error1(tmose);
      }
      else {
        yyval.mose=math_on_size_error1(tmose);
      }
        stabs_line();
         }
break;
case 999:
#line 3367 "htcobol.y"
{
      math_on_size_error2(tmose);
      yyval.mose=yyvsp[-1].mose;
     }
break;
case 1007:
#line 3391 "htcobol.y"
{ gen_set_list(yyvsp[-3].sval,SET_TO,yyvsp[0].sval,0,yyvsp[-1].ival); }
break;
case 1008:
#line 3393 "htcobol.y"
{ gen_set_list(yyvsp[-3].sval,SET_UP_BY,yyvsp[0].sval,0,0); }
break;
case 1009:
#line 3395 "htcobol.y"
{ gen_set_list(yyvsp[-3].sval,SET_DOWN_BY,yyvsp[0].sval,0,0); }
break;
case 1010:
#line 3397 "htcobol.y"
{ gen_set(yyvsp[-3].sval,SET_TO,yyvsp[0].sval,yyvsp[-4].ival,yyvsp[-1].ival); }
break;
case 1011:
#line 3402 "htcobol.y"
{ yyval.sval = yyvsp[0].sval; }
break;
case 1012:
#line 3403 "htcobol.y"
{ yyval.sval = (struct sym *)chain_var(yyvsp[0].sval); }
break;
case 1013:
#line 3407 "htcobol.y"
{ yyval.sval = yyvsp[0].sval; }
break;
case 1014:
#line 3408 "htcobol.y"
{ yyval.sval = NULL; }
break;
case 1015:
#line 3412 "htcobol.y"
{ yyval.sval = yyvsp[0].sval; }
break;
case 1016:
#line 3413 "htcobol.y"
{ yyval.sval = (struct sym *)define_num_lit(1); }
break;
case 1017:
#line 3414 "htcobol.y"
{ yyval.sval = (struct sym *)spe_lit_ZE; }
break;
case 1018:
#line 3415 "htcobol.y"
{ yyval.sval = NULL; }
break;
case 1019:
#line 3417 "htcobol.y"
{ 
    yyval.sval = (struct sym *)1; 
    /* no (struct sym *) may have this value! */ 
   }
break;
case 1020:
#line 3424 "htcobol.y"
{ yyval.ival = 0; }
break;
case 1021:
#line 3425 "htcobol.y"
{ yyval.ival = 1; }
break;
case 1022:
#line 3432 "htcobol.y"
{
                gen_stringcmd( yyvsp[-3].sfval, yyvsp[-1].sval, yyvsp[0].sval );
            }
break;
case 1024:
#line 3443 "htcobol.y"
{
                gen_unstring( yyvsp[-5].sval, yyvsp[-4].udval, yyvsp[-2].udstval, yyvsp[-1].sval, yyvsp[0].sval );
            }
break;
case 1026:
#line 3450 "htcobol.y"
{ yyval.udval=yyvsp[0].udval; }
break;
case 1027:
#line 3451 "htcobol.y"
{ yyval.udval=NULL; }
break;
case 1028:
#line 3454 "htcobol.y"
{ yyval.udval=alloc_unstring_delimited(yyvsp[-1].ival,yyvsp[0].sval); }
break;
case 1029:
#line 3455 "htcobol.y"
{
            struct unstring_delimited *ud;
            ud=alloc_unstring_delimited(yyvsp[-1].ival,yyvsp[0].sval);
            ud->next = yyvsp[-3].udval;
            yyval.udval=ud;
        }
break;
case 1030:
#line 3463 "htcobol.y"
{ yyval.udstval=yyvsp[0].udstval; }
break;
case 1031:
#line 3465 "htcobol.y"
{
            yyvsp[0].udstval->next = yyvsp[-2].udstval;
            yyval.udstval = yyvsp[0].udstval;
        }
break;
case 1032:
#line 3471 "htcobol.y"
{
            yyval.udstval = alloc_unstring_dest( yyvsp[-2].sval, yyvsp[-1].sval, yyvsp[0].sval );
        }
break;
case 1033:
#line 3476 "htcobol.y"
{ yyval.sval=NULL; }
break;
case 1034:
#line 3477 "htcobol.y"
{ yyval.sval=yyvsp[0].sval; }
break;
case 1035:
#line 3480 "htcobol.y"
{ yyval.sval=NULL; }
break;
case 1036:
#line 3481 "htcobol.y"
{ yyval.sval=yyvsp[0].sval; }
break;
case 1037:
#line 3484 "htcobol.y"
{ yyval.sval=NULL; }
break;
case 1038:
#line 3485 "htcobol.y"
{ yyval.sval=yyvsp[0].sval; }
break;
case 1039:
#line 3488 "htcobol.y"
{ yyval.ival=0; }
break;
case 1040:
#line 3489 "htcobol.y"
{ yyval.ival=1; }
break;
case 1041:
#line 3492 "htcobol.y"
{ curr_division = CDIV_EXCEPTION; }
break;
case 1042:
#line 3495 "htcobol.y"
{ curr_division = CDIV_PROC; }
break;
case 1043:
#line 3498 "htcobol.y"
{ yyval.ival = begin_on_except(); }
break;
case 1044:
#line 3499 "htcobol.y"
{ gen_jmplabel(yyvsp[-4].dval); yyval.ival=yyvsp[-1].ival; }
break;
case 1045:
#line 3500 "htcobol.y"
{ yyval.ival = 0; }
break;
case 1048:
#line 3507 "htcobol.y"
{ yyval.ival = begin_on_except(); }
break;
case 1049:
#line 3508 "htcobol.y"
{ gen_jmplabel(yyvsp[-6].dval); yyval.ival=yyvsp[-1].ival; }
break;
case 1050:
#line 3509 "htcobol.y"
{ yyval.ival = 0; }
break;
case 1051:
#line 3512 "htcobol.y"
{ yyval.dval = gen_at_end(1); }
break;
case 1052:
#line 3513 "htcobol.y"
{ gen_dstlabel(yyvsp[-1].dval); }
break;
case 1054:
#line 3517 "htcobol.y"
{ yyval.dval = gen_at_end(0); }
break;
case 1055:
#line 3518 "htcobol.y"
{ gen_dstlabel(yyvsp[-1].dval); }
break;
case 1057:
#line 3523 "htcobol.y"
{yyval.iks = gen_invalid_keys(yyvsp[0].ike, NULL);}
break;
case 1058:
#line 3524 "htcobol.y"
{yyval.iks = gen_invalid_keys(NULL, yyvsp[0].ike);}
break;
case 1059:
#line 3526 "htcobol.y"
{yyval.iks = gen_invalid_keys(yyvsp[-1].ike, yyvsp[0].ike);}
break;
case 1060:
#line 3527 "htcobol.y"
{ yyval.iks = NULL;}
break;
case 1061:
#line 3530 "htcobol.y"
{ yyval.ike = gen_before_invalid_key();  }
break;
case 1062:
#line 3531 "htcobol.y"
{ yyval.ike = gen_after_invalid_key(yyvsp[-1].ike); }
break;
case 1063:
#line 3534 "htcobol.y"
{ yyval.ike = gen_before_invalid_key();  }
break;
case 1064:
#line 3535 "htcobol.y"
{ yyval.ike = gen_after_invalid_key(yyvsp[-1].ike); }
break;
case 1067:
#line 3542 "htcobol.y"
{ yyval.sval = yyvsp[0].sval; }
break;
case 1068:
#line 3543 "htcobol.y"
{ yyval.sval = NULL; }
break;
case 1069:
#line 3546 "htcobol.y"
{ yyval.sfval = yyvsp[0].sfval; }
break;
case 1070:
#line 3547 "htcobol.y"
{
            yyvsp[0].sfval->next = yyvsp[-2].sfval;
            yyval.sfval = yyvsp[0].sfval;
        }
break;
case 1071:
#line 3551 "htcobol.y"
{ yyerror("variable expected"); }
break;
case 1072:
#line 3554 "htcobol.y"
{
    /* Item with no DELIMITED BY section implies use delimiter of next item */
                yyval.sfval = alloc_string_from( yyvsp[0].sval, (struct sym *)-1 );
            }
break;
case 1073:
#line 3558 "htcobol.y"
{
                yyval.sfval = alloc_string_from( yyvsp[-3].sval, yyvsp[0].sval );
            }
break;
case 1074:
#line 3563 "htcobol.y"
{ yyval.sval=yyvsp[0].sval; }
break;
case 1075:
#line 3564 "htcobol.y"
{ yyval.sval=NULL; }
break;
case 1076:
#line 3565 "htcobol.y"
{ yyerror("SIZE or identifier expected"); }
break;
case 1081:
#line 3580 "htcobol.y"
{ gen_inspect(yyvsp[-1].sval,(void *)yyvsp[0].tlval,0); }
break;
case 1082:
#line 3581 "htcobol.y"
{ gen_inspect(yyvsp[-3].sval,(void *)yyvsp[0].repval,1); }
break;
case 1083:
#line 3584 "htcobol.y"
{ gen_inspect(yyvsp[-1].sval,(void *)yyvsp[0].cvval,2); }
break;
case 1084:
#line 3588 "htcobol.y"
{
            yyval.cvval = alloc_converting_struct(yyvsp[-3].sval,yyvsp[-1].sval,yyvsp[0].baval); 
                }
break;
case 1085:
#line 3593 "htcobol.y"
{ yyval.tlval=yyvsp[0].tlval; }
break;
case 1086:
#line 3594 "htcobol.y"
{ yyval.tlval=NULL; }
break;
case 1087:
#line 3598 "htcobol.y"
{
            yyval.tlval = alloc_tallying_list(yyvsp[-3].tlval,yyvsp[-2].sval,yyvsp[0].tfval); }
break;
case 1088:
#line 3600 "htcobol.y"
{ yyval.tlval = NULL; }
break;
case 1089:
#line 3604 "htcobol.y"
{
            yyval.tfval = alloc_tallying_for_list(yyvsp[-2].tfval,INSPECT_CHARACTERS,NULL,yyvsp[0].baval); }
break;
case 1090:
#line 3607 "htcobol.y"
{
            yyval.tfval = alloc_tallying_for_list(yyvsp[-3].tfval,INSPECT_ALL,yyvsp[-1].sval,yyvsp[0].baval); }
break;
case 1091:
#line 3610 "htcobol.y"
{
            yyval.tfval = alloc_tallying_for_list(yyvsp[-3].tfval,INSPECT_LEADING,yyvsp[-1].sval,yyvsp[0].baval); }
break;
case 1092:
#line 3612 "htcobol.y"
{ yyval.tfval = NULL; }
break;
case 1093:
#line 3616 "htcobol.y"
{ yyval.repval = yyvsp[0].repval; }
break;
case 1094:
#line 3617 "htcobol.y"
{ yyval.repval = NULL; }
break;
case 1095:
#line 3621 "htcobol.y"
{
            yyval.repval = alloc_replacing_list(yyvsp[-4].repval,INSPECT_CHARACTERS,NULL,yyvsp[-1].sval,yyvsp[0].baval); }
break;
case 1096:
#line 3624 "htcobol.y"
{
            yyval.repval = alloc_replacing_list(yyvsp[-2].repval,yyvsp[-1].ival,yyvsp[0].rbval,NULL,NULL); }
break;
case 1097:
#line 3626 "htcobol.y"
{ yyval.repval = NULL; }
break;
case 1098:
#line 3630 "htcobol.y"
{
            yyval.rbval = alloc_replacing_by_list(yyvsp[-4].rbval,yyvsp[-3].sval,yyvsp[-1].sval,yyvsp[0].baval); }
break;
case 1099:
#line 3632 "htcobol.y"
{ yyval.rbval = NULL; }
break;
case 1100:
#line 3635 "htcobol.y"
{ yyval.ival = INSPECT_ALL; }
break;
case 1101:
#line 3636 "htcobol.y"
{ yyval.ival = INSPECT_LEADING; }
break;
case 1102:
#line 3637 "htcobol.y"
{ yyval.ival = INSPECT_TRAILING; }
break;
case 1103:
#line 3638 "htcobol.y"
{ yyval.ival = INSPECT_FIRST; }
break;
case 1104:
#line 3643 "htcobol.y"
{ yyval.baval = alloc_inspect_before_after(yyvsp[-3].baval,1,yyvsp[0].sval); }
break;
case 1105:
#line 3646 "htcobol.y"
{ yyval.baval = alloc_inspect_before_after(yyvsp[-3].baval,2,yyvsp[0].sval); }
break;
case 1106:
#line 3647 "htcobol.y"
{ yyval.baval = alloc_inspect_before_after(NULL,0,NULL); }
break;
case 1109:
#line 3655 "htcobol.y"
{ yyval.sval = yyvsp[0].sval; }
break;
case 1110:
#line 3656 "htcobol.y"
{ yyval.sval =
                (struct sym *)create_expr('*',(struct expr *)yyvsp[-2].sval,(struct expr *)yyvsp[0].sval); }
break;
case 1111:
#line 3658 "htcobol.y"
{ yyval.sval =
                (struct sym *)create_expr('/',(struct expr *)yyvsp[-2].sval,(struct expr *)yyvsp[0].sval); }
break;
case 1112:
#line 3660 "htcobol.y"
{ yyval.sval =
                (struct sym *)create_expr('+',(struct expr *)yyvsp[-2].sval,(struct expr *)yyvsp[0].sval); }
break;
case 1113:
#line 3662 "htcobol.y"
{ yyval.sval =
                (struct sym *)create_expr('-',(struct expr *)yyvsp[-2].sval,(struct expr *)yyvsp[0].sval); }
break;
case 1114:
#line 3664 "htcobol.y"
{ yyval.sval =
                (struct sym *)create_expr('^',(struct expr *)yyvsp[-2].sval,(struct expr *)yyvsp[0].sval); }
break;
case 1115:
#line 3666 "htcobol.y"
{ yyval.sval=yyvsp[-1].sval; }
break;
case 1116:
#line 3671 "htcobol.y"
{ yyval.sval = (struct sym *)-1; }
break;
case 1117:
#line 3672 "htcobol.y"
{ yyval.sval = yyvsp[0].sval; }
break;
case 1118:
#line 3675 "htcobol.y"
{ yyval.ival=0; }
break;
case 1119:
#line 3676 "htcobol.y"
{ yyval.ival=0; /* to save how many parameters */ }
break;
case 1120:
#line 3677 "htcobol.y"
{ yyval.ival=CALL; }
break;
case 1121:
#line 3678 "htcobol.y"
{ yyval.ival=yyvsp[-3].ival; }
break;
case 1122:
#line 3681 "htcobol.y"
{ yyval.sval=NULL; }
break;
case 1123:
#line 3683 "htcobol.y"
{ 
      if (yyvsp[0].sval->type == 'B') {
         yyval.sval=yyvsp[0].sval; 
      }
      else { 
         yyerror("Identifier in CALL RETURNING clause must be of BINARY/COMP/POINTER type");
         yyval.sval=NULL; 
      }
     }
break;
case 1127:
#line 3699 "htcobol.y"
{ yyval.ival=0; }
break;
case 1128:
#line 3700 "htcobol.y"
{ gen_save_usings(yyvsp[0].glistval); yyval.ival=1; }
break;
case 1129:
#line 3701 "htcobol.y"
{ gen_save_chainings(yyvsp[0].glistval); yyval.ival=2; }
break;
case 1130:
#line 3705 "htcobol.y"
{ yyval.sval=NULL; }
break;
case 1131:
#line 3707 "htcobol.y"
{ 
      if (yyvsp[0].sval->type == 'B') {
         yyval.sval=yyvsp[0].sval; 
      }
      else { 
         yyerror("Identifier in PROCEDURE DIVISION RETURNING clause must be of BINARY/COMP/POINTER type");
         yyval.sval=NULL; 
      }
     }
break;
case 1132:
#line 3720 "htcobol.y"
{   if (yyvsp[-3].ival == USING)
                gen_save_using(yyvsp[0].sval);
            else if (yyvsp[-3].ival == CALL) {
                gen_push_using(yyvsp[0].sval);
            }
        }
break;
case 1133:
#line 3727 "htcobol.y"
{   if (yyvsp[-1].ival == USING)
                gen_save_using(yyvsp[0].sval);
            else if (yyvsp[-1].ival == CALL) {
                gen_push_using(yyvsp[0].sval);
            }
        }
break;
case 1134:
#line 3736 "htcobol.y"
{
     /* $$=$1; */
     if (yyvsp[0].sval->litflag == 1) {
        struct lit *lp=(struct lit *)yyvsp[0].sval;
        lp->call_mode=curr_call_mode;
     }
     else {
/*      if (!need_subscripts) */
        /* fprintf(stderr, "debug : htcobol.y 3639 : curr_call_mode=%d\n", curr_call_mode);  */
        /* $1->uval3.call_mode=curr_call_mode; */
        struct sym *sy=(struct sym *)yyvsp[0].sval;
        sy->uval3.call_mode=curr_call_mode;
     }
     yyval.sval=yyvsp[0].sval;
    }
break;
case 1135:
#line 3753 "htcobol.y"
{ if ( curr_call_mode == CM_CHAIN )
            yyerror("parameter types not allowed on CHAIN");
          else
          {
            yyval.sval=yyvsp[0].sval;
            curr_call_mode=yyvsp[-1].ival;
            if (yyval.sval->litflag==1) {
               struct lit *lp=(struct lit *)yyval.sval;
               lp->call_mode=curr_call_mode;
               }
            else
               yyval.sval->uval3.call_mode=curr_call_mode;
          }
        }
break;
case 1136:
#line 3773 "htcobol.y"
{yyval.ival=CM_REF;}
break;
case 1137:
#line 3774 "htcobol.y"
{yyval.ival=CM_VAL;}
break;
case 1138:
#line 3775 "htcobol.y"
{yyval.ival=CM_CONT;}
break;
case 1139:
#line 3780 "htcobol.y"
{ gen_push_using(yyvsp[0].sval); }
break;
case 1140:
#line 3781 "htcobol.y"
{ gen_push_using(yyvsp[0].sval); }
break;
case 1141:
#line 3785 "htcobol.y"
{
     yyval.sval=yyvsp[0].sval;
     if (yyval.sval->litflag==1) {
        struct lit *lp=(struct lit *)yyval.sval;
        lp->call_mode=CM_REF;
     }
     else
       yyval.sval->uval3.call_mode=CM_REF;
    }
break;
case 1142:
#line 3797 "htcobol.y"
{
     yyval.snval = alloc_sortfile_node2(yyvsp[-1].sval, yyvsp[0].sval);
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
break;
case 1143:
#line 3811 "htcobol.y"
{ yyval.sval = NULL; }
break;
case 1144:
#line 3813 "htcobol.y"
{
        gen_push_int(yyvsp[-1].sval);
        yyval.dval=gen_marklabel();
        gen_perform_test_counter(yyval.dval);
      }
break;
case 1145:
#line 3819 "htcobol.y"
{
        gen_perform_times(yyvsp[-1].dval);
      }
break;
case 1146:
#line 3822 "htcobol.y"
{ yyval.sval = NULL; }
break;
case 1147:
#line 3824 "htcobol.y"
{
        if (yyvsp[-1].ival == 2) {
        	yyval.ddval.lb2=gen_passlabel();
		}
        yyval.ddval.lb1=gen_marklabel();
      }
break;
case 1148:
#line 3831 "htcobol.y"
{
        yyval.ddval.lb1=gen_orstart();
        if (yyvsp[-3].ival == 2) {
           yyval.ddval.lb2=gen_passlabel();
           gen_dstlabel(yyvsp[-1].ddval.lb2);
        }
      }
break;
case 1149:
#line 3839 "htcobol.y"
{
        if (yyvsp[-5].ival == 2) {
           gen_jmplabel(yyvsp[-3].ddval.lb1);
           gen_dstlabel(yyvsp[-1].ddval.lb2);
           gen_jmplabel(yyvsp[-3].ddval.lb2);
           gen_dstlabel(yyvsp[-1].ddval.lb1);
        }
        else {
           gen_jmplabel(yyvsp[-3].ddval.lb1);
           gen_dstlabel(yyvsp[-1].ddval.lb1);
        }
      }
break;
case 1150:
#line 3851 "htcobol.y"
{ yyval.sval = NULL; }
break;
case 1151:
#line 3853 "htcobol.y"
{
        /* 
        Check if initailization of the 'VARYING identifier' is required.
        Initailization of the 'VARYING identifier' is not neccessary if
        it is the same as the 'FROM identifier'.
        */
        if (yyvsp[-3].sval->litflag == '1') {
          gen_move(yyvsp[-3].sval,yyvsp[-5].sval);
        }
        else {
          if(strcmp(yyvsp[-3].sval->name, yyvsp[-5].sval->name) != 0) {
            gen_move(yyvsp[-3].sval,yyvsp[-5].sval);
          }       
        }
        /* BEFORE=1 AFTER=2 */
        if (yyvsp[-7].ival == 2) {
           yyval.ddval.lb2=gen_passlabel();
        }
        yyval.ddval.lb1=gen_marklabel();
      }
break;
case 1152:
#line 3874 "htcobol.y"
{
        yyval.dval=gen_orstart();
        /* BEFORE=1 AFTER=2 */
        if (yyvsp[-9].ival == 2) {
           gen_add(yyvsp[-3].sval,yyvsp[-7].sval,0);
           gen_dstlabel(yyvsp[-1].ddval.lb2);
        }
      }
break;
case 1153:
#line 3884 "htcobol.y"
{
        int i;
        struct perf_info *rf;
        /*struct perform_info *rpi;*/
        char *vn;

        /* Check for duplicate variables in VARYING/AFTER */
        if (yyvsp[-1].pfvals != NULL) {
           if ((vn = check_perform_variables(yyvsp[-10].sval, yyvsp[-1].pfvals)) != NULL) {
              yyerror("Duplicate variable '%s' in VARYING/AFTER clause", vn);
           }
        }

        if (yyvsp[-12].ival == 2) {
           if (yyvsp[-1].pfvals != NULL) {
              for (i=5; i>=0; i--) {
                 rf = yyvsp[-1].pfvals->pf[i];
                 if (rf != NULL) {
                    gen_jmplabel(rf->ljmp);
                    gen_dstlabel(rf->lend);
                 }
              }
           }
           gen_jmplabel(yyvsp[-4].ddval.lb1);
           gen_dstlabel(yyvsp[-2].dval);
        }
        else {
           if (yyvsp[-1].pfvals != NULL) {
              for (i=5; i>=0; i--) {
                 rf = yyvsp[-1].pfvals->pf[i];
                 if (rf != NULL) {
                    gen_add(rf->pname1, rf->pname2, 0);
                    gen_jmplabel(rf->ljmp);
                    gen_dstlabel(rf->lend);
                 }
              }
           }
           gen_add(yyvsp[-6].sval,yyvsp[-10].sval,0);
           gen_jmplabel(yyvsp[-4].ddval.lb1);
           gen_dstlabel(yyvsp[-2].dval);
        }
      }
break;
case 1154:
#line 3926 "htcobol.y"
{ yyval.sval = NULL; }
break;
case 1155:
#line 3928 "htcobol.y"
{
        gen_perform_thru(yyvsp[-1].sval,yyvsp[0].sval);
        yyval.sval = NULL;
      }
break;
case 1156:
#line 3933 "htcobol.y"
{
        yyval.dval=gen_marklabel();
        /* BEFORE=1 AFTER=2 */
        if (yyvsp[-1].ival == 2) {
        gen_perform_thru(yyvsp[-3].sval,yyvsp[-2].sval);
        }
      }
break;
case 1157:
#line 3941 "htcobol.y"
{
        unsigned long lbl;
        lbl=gen_orstart();
        /* BEFORE=1 AFTER=2 */
        if (yyvsp[-3].ival == 1) {
        gen_perform_thru(yyvsp[-5].sval,yyvsp[-4].sval);
        }
        gen_jmplabel(yyvsp[-1].dval);
        gen_dstlabel(lbl);
      }
break;
case 1158:
#line 3952 "htcobol.y"
{
        unsigned long lbl;      
        gen_push_int(yyvsp[-1].sval);
        lbl = gen_marklabel();
        gen_perform_test_counter(lbl);
        gen_perform_thru(yyvsp[-3].sval,yyvsp[-2].sval);
        gen_perform_times(lbl);
      }
break;
case 1159:
#line 3962 "htcobol.y"
{
        /* 
        Check if initailization of the 'VARYING identifier' is required.
        Initailization of the 'VARYING identifier' is not neccessary if
        it is the same as the 'FROM identifier'.
        */
        if (yyvsp[-3].sval->litflag == '1') {
          gen_move(yyvsp[-3].sval,yyvsp[-5].sval);
        }
        else {
          if(strcmp(yyvsp[-3].sval->name, yyvsp[-5].sval->name) != 0) {
            gen_move(yyvsp[-3].sval,yyvsp[-5].sval);
          }       
        }
        if (yyvsp[-7].ival == 2) {
           yyval.ddval.lb2=gen_passlabel();
        }
        yyval.ddval.lb1 = gen_marklabel();
      }
break;
case 1160:
#line 3982 "htcobol.y"
{
        yyval.dval = gen_orstart();
        /* BEFORE=1 AFTER=2 */
        if (yyvsp[-9].ival == 2) {
           gen_add(yyvsp[-3].sval,yyvsp[-7].sval, 0);
           gen_dstlabel(yyvsp[-1].ddval.lb2);
        }
      }
break;
case 1161:
#line 3991 "htcobol.y"
{
        int i;
        struct perf_info *rf;
        /*struct perform_info *rpi;*/
        char *vn = NULL;

        /* Check for duplicate varaibles in VARYING/AFTER */
        if (yyvsp[0].pfvals != NULL) {
           if ((vn = check_perform_variables(yyvsp[-9].sval, yyvsp[0].pfvals)) != NULL) {
              yyerror("Duplicate variable '%s' in VARYING/AFTER clause", vn);
           }
        }
        gen_perform_thru(yyvsp[-13].sval,yyvsp[-12].sval);
        /* BEFORE=1 AFTER=2 */
        if (yyvsp[-11].ival == 2) {
           if (yyvsp[0].pfvals != NULL) {
              for (i=5; i>=0; i--) {
                 rf = yyvsp[0].pfvals->pf[i];
                 if (rf != NULL) {
                    gen_jmplabel(rf->ljmp);
                    gen_dstlabel(rf->lend);
                 }
              }
           }
           gen_jmplabel(yyvsp[-3].dval);
           gen_dstlabel(yyvsp[-1].dval);
        }
        else {
           if (yyvsp[0].pfvals != NULL) {
              for (i=5; i>=0; i--) {
                 rf = yyvsp[0].pfvals->pf[i];
                 if (rf != NULL) {
                    gen_add(rf->pname1, rf->pname2, 0);
                    gen_jmplabel(rf->ljmp);
                    gen_dstlabel(rf->lend);
                 }
              }
           }
           gen_add(yyvsp[-5].sval,yyvsp[-9].sval,0);
           gen_jmplabel(yyvsp[-3].dval);
           gen_dstlabel(yyvsp[-1].dval);
        }
        yyval.sval = NULL;
      }
break;
case 1162:
#line 4038 "htcobol.y"
{ yyval.sval = NULL; }
break;
case 1163:
#line 4039 "htcobol.y"
{ yyval.sval = yyvsp[0].sval;}
break;
case 1164:
#line 4041 "htcobol.y"
{ yyval.ival=1; perform_after_sw=1; }
break;
case 1165:
#line 4043 "htcobol.y"
{
       yyval.ival=yyvsp[0].ival;
       perform_after_sw=yyvsp[0].ival;
      }
break;
case 1166:
#line 4048 "htcobol.y"
{ yyval.pfvals=NULL; }
break;
case 1167:
#line 4050 "htcobol.y"
{
      yyval.pfvals=create_perform_info();
      yyval.pfvals->pf[0] = yyvsp[0].pfval;
      yyval.pfvals=yyval.pfvals;
     }
break;
case 1168:
#line 4056 "htcobol.y"
{
      yyval.pfvals=create_perform_info();
      yyval.pfvals->pf[0] = yyvsp[-2].pfval;
      yyval.pfvals->pf[1] = yyvsp[0].pfval;
      yyval.pfvals=yyval.pfvals;
     }
break;
case 1169:
#line 4064 "htcobol.y"
{
      yyval.pfvals=create_perform_info();
      yyval.pfvals->pf[0] = yyvsp[-4].pfval;
      yyval.pfvals->pf[1] = yyvsp[-2].pfval;
      yyval.pfvals->pf[2] = yyvsp[0].pfval;
      yyval.pfvals=yyval.pfvals;
     }
break;
case 1170:
#line 4073 "htcobol.y"
{
      yyval.pfvals=create_perform_info();
      yyval.pfvals->pf[0] = yyvsp[-6].pfval;
      yyval.pfvals->pf[1] = yyvsp[-4].pfval;
      yyval.pfvals->pf[2] = yyvsp[-2].pfval;
      yyval.pfvals->pf[3] = yyvsp[0].pfval;
      yyval.pfvals=yyval.pfvals;
     }
break;
case 1171:
#line 4083 "htcobol.y"
{
      yyval.pfvals=create_perform_info();
      yyval.pfvals->pf[0] = yyvsp[-8].pfval;
      yyval.pfvals->pf[1] = yyvsp[-6].pfval;
      yyval.pfvals->pf[2] = yyvsp[-4].pfval;
      yyval.pfvals->pf[3] = yyvsp[-2].pfval;
      yyval.pfvals->pf[4] = yyvsp[0].pfval;
      yyval.pfvals=yyval.pfvals;
     }
break;
case 1172:
#line 4094 "htcobol.y"
{
      yyval.pfvals=create_perform_info();
      yyval.pfvals->pf[0] = yyvsp[-10].pfval;
      yyval.pfvals->pf[1] = yyvsp[-8].pfval;
      yyval.pfvals->pf[2] = yyvsp[-6].pfval;
      yyval.pfvals->pf[3] = yyvsp[-4].pfval;
      yyval.pfvals->pf[4] = yyvsp[-2].pfval;
      yyval.pfvals->pf[5] = yyvsp[0].pfval;
      yyval.pfvals=yyval.pfvals;
     }
break;
case 1173:
#line 4107 "htcobol.y"
{
      /* 
      Check if initailization of the 'VARYING identifier' is required.
      Initailization of the 'VARYING identifier' is not neccessary if
      it is the same as the 'FROM identifier'.
      */
      if (yyvsp[-3].sval->litflag == '1') {
        gen_move(yyvsp[-3].sval,yyvsp[-5].sval);
      }
      else {
        if(strcmp(yyvsp[-3].sval->name, yyvsp[-5].sval->name) != 0) {
          gen_move(yyvsp[-3].sval,yyvsp[-5].sval);
        }	
      }
      /* BEFORE=1 AFTER=2 */
      if (perform_after_sw == 2) {
             yyval.ddval.lb2=gen_passlabel();
      }
      yyval.ddval.lb1 = gen_marklabel();
    }
break;
case 1174:
#line 4128 "htcobol.y"
{
      unsigned long lbl;
      lbl=gen_orstart();
      /* BEFORE=1 AFTER=2 */
      if (perform_after_sw == 2) {
             gen_add(yyvsp[-3].sval,yyvsp[-7].sval,0);
             gen_dstlabel(yyvsp[-1].ddval.lb2);
             yyval.pfval = create_perf_info(yyvsp[-3].sval, yyvsp[-7].sval, yyvsp[-1].ddval.lb1, lbl);
      }
      else {
             yyval.pfval = create_perf_info(yyvsp[-3].sval, yyvsp[-7].sval, yyvsp[-1].ddval.lb1, lbl);
      }
    }
break;
case 1175:
#line 4142 "htcobol.y"
{stabs_line();}
break;
case 1177:
#line 4148 "htcobol.y"
{ yyval.ival=1; }
break;
case 1178:
#line 4149 "htcobol.y"
{ yyval.ival=2; }
break;
case 1179:
#line 4153 "htcobol.y"
{
      if (yyvsp[0].ival & COND_UNARY) {
              if (yyvsp[0].ival & COND_CLASS) {
            gen_class_check(yyvsp[-1].sval,yyvsp[0].ival);
              }
              else {
                struct sym *sy = (struct sym *)save_special_literal('0','9', "%ZEROS%");
                gen_compare(yyvsp[-1].sval,yyvsp[0].ival&~COND_UNARY,sy);
              }
      }
    }
break;
case 1180:
#line 4165 "htcobol.y"
{
      if (yyvsp[-2].ival & COND_UNARY) {
        if ((int)yyvsp[0].sval != -1) {
           yyerror("class or sign conditions are unary");
        }
      }
      else {
        if ((int)yyvsp[0].sval == -1) {
           yyerror("expression expected in a binary condition");
        }
        else {
           gen_compare(yyvsp[-3].sval,yyvsp[-2].ival,yyvsp[0].sval);
        }
      }
      yyval.condval.sy=yyvsp[-3].sval; /* for implied operands */
      yyval.condval.oper=yyvsp[-2].ival;
    }
break;
case 1181:
#line 4182 "htcobol.y"
{ gen_not(); yyval.condval=yyvsp[0].condval; }
break;
case 1182:
#line 4185 "htcobol.y"
{ yyval.dval=gen_andstart(); }
break;
case 1183:
#line 4187 "htcobol.y"
{ gen_dstlabel(yyvsp[-1].dval); yyval.condval=yyvsp[0].condval; }
break;
case 1184:
#line 4190 "htcobol.y"
{ yyval.dval=gen_orstart(); }
break;
case 1185:
#line 4192 "htcobol.y"
{ gen_dstlabel(yyvsp[-1].dval); yyval.condval=yyvsp[0].condval; }
break;
case 1186:
#line 4193 "htcobol.y"
{ yyval.condval = yyvsp[-1].condval; }
break;
case 1187:
#line 4195 "htcobol.y"
{
       /*if ($1->level != 88)
               yyerror("condition unknown");*/
       gen_condition(yyvsp[0].sval);
       yyval.condval.sy=NULL;
       yyval.condval.oper=0;
     }
break;
case 1188:
#line 4204 "htcobol.y"
{ yyval.condval = yyvsp[0].condval; }
break;
case 1189:
#line 4206 "htcobol.y"
{
       if (yyvsp[-4].condval.sy == NULL) {
              yyerror("invalid implied condition");
       }
       else {
              gen_compare(yyvsp[-4].condval.sy,yyvsp[-1].ival,yyvsp[0].sval);
       }
       yyval.condval.sy = yyvsp[-4].condval.sy;
       yyval.condval.oper = yyvsp[-1].ival;
     }
break;
case 1190:
#line 4217 "htcobol.y"
{ /* implied both the first operand and the operator */
      if ((yyvsp[-3].condval.sy == NULL)||
              (yyvsp[-3].condval.oper & COND_UNARY)) {
             yyerror("invalid implied condition");
      }
      else {
             gen_compare(yyvsp[-3].condval.sy,yyvsp[-3].condval.oper,yyvsp[0].sval);
      }
      yyval.condval.sy = yyvsp[-3].condval.sy;
      yyval.condval.oper = yyvsp[-3].condval.oper;
     }
break;
case 1191:
#line 4230 "htcobol.y"
{ yyval.ival=GREATER; }
break;
case 1192:
#line 4231 "htcobol.y"
{ yyval.ival=LESS;    }
break;
case 1193:
#line 4232 "htcobol.y"
{ yyval.ival=EQUAL;   }
break;
case 1194:
#line 4235 "htcobol.y"
{ yyval.ival=CLASS_NUMERIC; }
break;
case 1195:
#line 4236 "htcobol.y"
{ yyval.ival=CLASS_ALPHABETIC; }
break;
case 1196:
#line 4237 "htcobol.y"
{ yyval.ival=CLASS_ALPHABETIC_LOWER; }
break;
case 1197:
#line 4238 "htcobol.y"
{ yyval.ival=CLASS_ALPHABETIC_UPPER; }
break;
case 1198:
#line 4241 "htcobol.y"
{ yyval.ival = yyvsp[0].ival; }
break;
case 1199:
#line 4242 "htcobol.y"
{ yyval.ival = yyvsp[0].ival ^ 7; }
break;
case 1200:
#line 4243 "htcobol.y"
{ yyval.ival = yyvsp[-2].ival | yyvsp[0].ival; }
break;
case 1201:
#line 4244 "htcobol.y"
{ yyval.ival = yyvsp[0].ival; }
break;
case 1202:
#line 4245 "htcobol.y"
{ yyval.ival = yyvsp[0].ival ^ 7; }
break;
case 1203:
#line 4246 "htcobol.y"
{ yyval.ival = yyvsp[-2].ival | yyvsp[0].ival; }
break;
case 1204:
#line 4249 "htcobol.y"
{ yyval.ival = yyvsp[0].ival; }
break;
case 1205:
#line 4250 "htcobol.y"
{ yyval.ival = yyvsp[0].ival | COND_UNARY | COND_CLASS; }
break;
case 1206:
#line 4251 "htcobol.y"
{ yyval.ival = yyvsp[0].ival | COND_UNARY; }
break;
case 1207:
#line 4254 "htcobol.y"
{ yyval.ival = yyvsp[0].ival; }
break;
case 1208:
#line 4255 "htcobol.y"
{ yyval.ival = yyvsp[0].ival ^ 7; }
break;
case 1209:
#line 4256 "htcobol.y"
{ yyval.ival = yyvsp[-2].ival | yyvsp[0].ival; }
break;
case 1210:
#line 4259 "htcobol.y"
{ yyval.ival = yyvsp[-1].ival; }
break;
case 1220:
#line 4287 "htcobol.y"
{ }
break;
case 1221:
#line 4288 "htcobol.y"
{ }
break;
case 1236:
#line 4316 "htcobol.y"
{ yyval.sval = yyvsp[0].sval; }
break;
case 1237:
#line 4317 "htcobol.y"
{ yyval.sval = NULL; }
break;
case 1239:
#line 4320 "htcobol.y"
{ }
break;
case 1240:
#line 4323 "htcobol.y"
{ yyval.glistval = gvar_list_append(NULL, yyvsp[0].sval, source_lineno); }
break;
case 1241:
#line 4325 "htcobol.y"
{ yyval.glistval = gvar_list_append(yyvsp[-2].glistval, yyvsp[0].sval, source_lineno); }
break;
case 1242:
#line 4328 "htcobol.y"
{ yyval.glistval = gvar_list_append(NULL, yyvsp[0].sval, source_lineno); }
break;
case 1243:
#line 4330 "htcobol.y"
{ yyval.glistval = gvar_list_append(yyvsp[-2].glistval, yyvsp[0].sval, source_lineno); }
break;
case 1244:
#line 4332 "htcobol.y"
{
    /*if (!is_variable($1)) {
         yyerror("The symbol \"%s\" is not an allowed argument here", $1->name);
    }*/
      yyval.sval = yyvsp[0].sval; }
break;
case 1245:
#line 4337 "htcobol.y"
{ yyval.sval = (struct sym *)yyvsp[0].lval;}
break;
case 1246:
#line 4338 "htcobol.y"
{
                                yyvsp[-1].sval->type = 'f'; /* function type */
                                yyval.ival=CALL;
                        }
break;
case 1247:
#line 4342 "htcobol.y"
{
                 yyval.sval = gen_intrinsic_call((struct sym *)yyvsp[-4].sval);
                 }
break;
case 1248:
#line 4345 "htcobol.y"
{
            yyvsp[0].sval->type = 'f'; /* function type */
            yyval.ival=CALL;
            yyval.sval = gen_intrinsic_call((struct sym *)yyvsp[0].sval);
                 }
break;
case 1249:
#line 4352 "htcobol.y"
{ yyval.sval = yyvsp[0].sval; }
break;
case 1250:
#line 4353 "htcobol.y"
{ yyval.sval = (struct sym *)yyvsp[0].lval; }
break;
case 1251:
#line 4356 "htcobol.y"
{ yyval.sval = yyvsp[0].sval; }
break;
case 1252:
#line 4357 "htcobol.y"
{ yyval.sval = (struct sym *)yyvsp[0].lval; }
break;
case 1255:
#line 4364 "htcobol.y"
{ yyval.lval=yyvsp[0].lval; }
break;
case 1256:
#line 4365 "htcobol.y"
{ yyval.lval=yyvsp[0].lval; }
break;
case 1257:
#line 4368 "htcobol.y"
{ yyvsp[0].lval->all=1; yyval.lval=yyvsp[0].lval; }
break;
case 1258:
#line 4369 "htcobol.y"
{ yyval.lval=yyvsp[0].lval; }
break;
case 1259:
#line 4372 "htcobol.y"
{ yyval.lval=spe_lit_SP; }
break;
case 1260:
#line 4373 "htcobol.y"
{ yyval.lval=spe_lit_ZE; }
break;
case 1261:
#line 4374 "htcobol.y"
{ yyval.lval=spe_lit_QU; }
break;
case 1262:
#line 4375 "htcobol.y"
{ yyval.lval=spe_lit_HV; }
break;
case 1263:
#line 4376 "htcobol.y"
{ yyval.lval=spe_lit_LV; }
break;
case 1264:
#line 4377 "htcobol.y"
{ yyval.lval=spe_lit_ZE; }
break;
case 1265:
#line 4380 "htcobol.y"
{ yyval.sval = yyvsp[0].sval; }
break;
case 1266:
#line 4381 "htcobol.y"
{ yyval.sval = (struct sym *)yyvsp[0].lval; }
break;
case 1267:
#line 4384 "htcobol.y"
{ save_literal(yyvsp[0].lval,'9'); yyvsp[0].lval->all = 0; yyval.lval=yyvsp[0].lval; }
break;
case 1268:
#line 4387 "htcobol.y"
{ save_literal(yyvsp[0].lval,'9'); yyvsp[0].lval->all=0; yyval.lval=yyvsp[0].lval; }
break;
case 1269:
#line 4388 "htcobol.y"
{ save_literal(yyvsp[0].lval,'X'); yyvsp[0].lval->all=0; yyval.lval=yyvsp[0].lval; }
break;
case 1270:
#line 4391 "htcobol.y"
{ check_decimal_point(yyvsp[0].lval); yyval.lval=yyvsp[0].lval; }
break;
case 1271:
#line 4392 "htcobol.y"
{ check_decimal_point(yyvsp[0].lval); yyval.lval=yyvsp[0].lval; }
break;
case 1272:
#line 4394 "htcobol.y"
{
      check_decimal_point(yyvsp[0].lval);
      invert_literal_sign( yyvsp[0].lval );
      yyval.lval=yyvsp[0].lval;
     }
break;
case 1273:
#line 4401 "htcobol.y"
{ yyval.sval = yyvsp[0].sval; }
break;
case 1274:
#line 4402 "htcobol.y"
{ yyval.sval = NULL; }
break;
case 1275:
#line 4406 "htcobol.y"
{
     if (yyvsp[0].sval->defined)
         yyerror("variable redefined, %s",yyvsp[0].sval->name);
     yyvsp[0].sval->defined=1;
     yyval.sval=yyvsp[0].sval;
    }
break;
case 1276:
#line 4412 "htcobol.y"
{ yyval.sval=alloc_filler(); }
break;
case 1277:
#line 4416 "htcobol.y"
{
      if (yyvsp[0].sval->occurs_flg == 0)
         yyerror("\"%s\" is not an indexed variable ", yyvsp[0].sval->name);
      yyval.sval=yyvsp[0].sval;
    }
break;
case 1278:
#line 4441 "htcobol.y"
{ yyval.sval=(struct sym *)yyvsp[0].lval; }
break;
case 1279:
#line 4442 "htcobol.y"
{yyval.sval=yyvsp[0].sval; }
break;
case 1280:
#line 4445 "htcobol.y"
{ yyval.sval=(struct sym *)yyvsp[0].lval; }
break;
case 1281:
#line 4446 "htcobol.y"
{yyval.sval=yyvsp[0].sval; }
break;
case 1282:
#line 4449 "htcobol.y"
{  curr_division = CDIV_SUBSCRIPTS; }
break;
case 1283:
#line 4450 "htcobol.y"
{
                  curr_division = CDIV_PROC;
                  yyval.sval = (struct sym *)create_subscripted_var( yyvsp[-4].sval, yyvsp[-1].rval );
                    /*check_subscripts($$);*/
            }
break;
case 1284:
#line 4455 "htcobol.y"
{ yyval.sval=yyvsp[0].sval; }
break;
case 1285:
#line 4458 "htcobol.y"
{
     yyval.sval=(struct sym *)create_refmoded_var(yyvsp[-5].sval, yyvsp[-3].sval, yyvsp[-1].sval); check_refmods((struct sym *)yyval.sval);
     is_var=1;
     }
break;
case 1286:
#line 4462 "htcobol.y"
{ is_var=1; }
break;
case 1287:
#line 4463 "htcobol.y"
{ yyerror("Invalid argument expecting variable"); is_var=2; }
break;
case 1288:
#line 4466 "htcobol.y"
{
      if (!is_var)
        yyerror("Invalid argument expecting variable");
      is_var=0;
    }
break;
case 1289:
#line 4494 "htcobol.y"
{
     yyval.sval=yyvsp[0].sval;
     if (need_subscripts) {
            yyerror("identifier \'%s\' must be subscripted or indexed", yyvsp[0].sval->name);
            need_subscripts=0;
     }
    }
break;
case 1290:
#line 4502 "htcobol.y"
{ curr_division = CDIV_SUBSCRIPTS; }
break;
case 1291:
#line 4504 "htcobol.y"
{
       curr_division = CDIV_PROC;
       yyval.sval = (struct sym *)create_subscripted_var( yyvsp[-4].sval, yyvsp[-1].rval );
                check_subscripts(yyval.sval);
     }
break;
case 1292:
#line 4512 "htcobol.y"
{
      yyval.sval=yyvsp[0].sval;
      if (yyvsp[0].sval->clone != 0)
      yyerror("identifier \'%s\' must be qualified", yyvsp[0].sval->name);
    }
break;
case 1293:
#line 4518 "htcobol.y"
{
    yyval.sval=lookup_parent(yyvsp[-2].sval,yyvsp[0].sval);
    if (yyval.sval == NULL) {
       yyerror("identifier \'%s\' is not defined in '%s'", yyvsp[-2].sval->name, yyvsp[0].sval->name);
       yyval.sval=yyvsp[-2].sval;
    }
    }
break;
case 1294:
#line 4528 "htcobol.y"
{
      if ((yyvsp[0].sval->defined == 0) && (yyvsp[0].sval->type == 0))
      {
             yyerror("Undefined variable \'%s\' found", yyvsp[0].sval->name);
      }
      yyval.sval=yyvsp[0].sval;
     }
break;
case 1295:
#line 4535 "htcobol.y"
{ need_subscripts=1; yyval.sval=yyvsp[0].sval; }
break;
case 1296:
#line 4538 "htcobol.y"
{ yyval.rval = yyvsp[0].rval; }
break;
case 1297:
#line 4539 "htcobol.y"
{ yyval.rval = add_subscript( yyvsp[-2].rval, yyvsp[0].rval ); }
break;
case 1298:
#line 4542 "htcobol.y"
{ yyval.rval = create_subscript( yyvsp[0].sval ); }
break;
case 1299:
#line 4543 "htcobol.y"
{ yyval.rval = add_subscript_item( yyvsp[-2].rval, '+', yyvsp[0].sval ); }
break;
case 1300:
#line 4544 "htcobol.y"
{ yyval.rval = add_subscript_item( yyvsp[-2].rval, '-', yyvsp[0].sval ); }
break;
case 1301:
#line 4548 "htcobol.y"
{
     char *s;
     yyval.ival=0;
     s=yyvsp[0].lval->name;
     while (isdigit(*s))
       yyval.ival = yyval.ival * 10 + *s++ - '0';
     if (*s)
       yyerror("only integers accepted here");
    }
break;
case 1302:
#line 4560 "htcobol.y"
{
      struct sym *lab=yyvsp[-2].sval;
      struct sym *sec=yyvsp[0].sval;
      if (sec->defined == 0) {
          sec->defined = 2;
          sec->parent = NULL;
      } else {
          if ((sec=lookup_label(yyvsp[0].sval,NULL))==NULL) {
                  sec = install(yyvsp[0].sval->name,SYTB_LAB,2);
                  sec->defined=2;
                  sec->parent = NULL;
          }
      }

      if (lab->defined == 0) {
          lab->defined = 2;
          lab->parent = yyvsp[0].sval;
      } else {
          if ((lab=lookup_label(yyvsp[-2].sval,yyvsp[0].sval))==NULL) {
             lab = install(yyvsp[-2].sval->name,SYTB_LAB,2);
             lab->defined=2;
             lab->parent = yyvsp[0].sval;
          }
      }
      yyval.sval = lab;
    }
break;
case 1303:
#line 4587 "htcobol.y"
{
     struct sym *lab=yyvsp[0].sval;
     if (lab->defined == 0) {
                  lab->defined = 2;
                  lab->parent = curr_section;
     }
     else {
                if ((lab=lookup_label(lab,curr_section))==NULL) {
                   lab = install(yyvsp[0].sval->name,SYTB_LAB,2);
                   lab->defined=2;
                   lab->parent = curr_section;
                }
     }
     yyval.sval = lab;
    }
break;
case 1304:
#line 4602 "htcobol.y"
{yyval.sval=define_label((struct sym *)yyvsp[0].lval,1,NULL,0);}
break;
case 1305:
#line 4603 "htcobol.y"
{yyval.sval=define_label((struct sym *)yyvsp[-2].lval,1,(struct sym *)yyvsp[0].lval,1);}
break;
case 1306:
#line 4604 "htcobol.y"
{yyval.sval=define_label((struct sym *)yyvsp[-2].lval,1,yyvsp[0].sval,0);}
break;
#line 18435 "htcobol.tab.c"
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
