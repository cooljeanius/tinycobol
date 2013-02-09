/*
 * Copyright (C) 2007-2008 Rildo Pragana, David Essex. 
 * Copyright (C) 1999-2006 Rildo Pragana, Jim Noeth, 
 *               David Essex, Glen Colbert.
 * Copyright (C) 1993,1991 Rildo Pragana.
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
*/

#ifndef __HTCOBOL_H
#define __HTCOBOL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/time.h>

/* Replaced by union 
//#define organization decimals
//#define fdesc location
//#define direction access_mode
//#define call_mode access_mode
//#define sort_data value2
//#define record pic
//#define recordsym redefines
//#define filenamevar son
//#define alternate brother
//#define scrinfo index - ???
//#define rec_varying picstr
//#define sort_file sign
*/

/* File READ phrases */
enum tcb_file_read_phrases {
  TCB_FILE_READ_PHRASE_NONE,  
  TCB_FILE_READ_PHRASE_AT_END,  
  TCB_FILE_READ_PHRASE_INVALID_KEY  
};

/* current division (cobol source) */
#define CDIV_IDENT            1
#define CDIV_ENVIR            2
#define CDIV_DATA             3
#define CDIV_PROC             4
#define CDIV_COMMENT          5
#define CDIV_FD               6
#define CDIV_REDEF            7
#define CDIV_SUBSCRIPTS       8
#define CDIV_COPY             9
#define CDIV_COPYFILE         10 
#define CDIV_EXCEPTION        11
#define CDIV_PIC              12
#define CINITIAL              15
#define CDIV_COMMENT1         16

/* symbol table selector */
#define SYTB_LIT 1
#define SYTB_VAR 2
#define SYTB_LAB 3

/* set operations */
#define SET_TO 1
#define SET_UP_BY 2
#define SET_DOWN_BY 3

/* call modes */
#define CM_REF 1
#define CM_VAL 2
#define CM_CONT 3
#define CM_DESC 4
#define CM_CHAIN 5

/* asm sections or pseudo-sections */
#define SEC_CODE 1
#define SEC_CONST 2
#define SEC_DATA 3
#define SEC_STACK 4
#define SEC_ARGS 5
#define SEC_TEMPS 6
#define SEC_WORKING SEC_DATA
#define SEC_RETURN_CODE SEC_DATA
#define SEC_FIRST_NAMED 7

/* selection subject types (evaluate statement) */
#define SSUBJ_FALSE 0
#define SSUBJ_TRUE 1
#define SSUBJ_EXPR 2
#define SSUBJ_COND 3
#define SSUBJ_STR 4

/* selection object types (evaluate statement) */
#define SOBJ_FALSE 0
#define SOBJ_TRUE 1
#define SOBJ_ANY 2
#define SOBJ_EXPR 3
#define SOBJ_NEGEXPR 4
#define SOBJ_RANGE 5
#define SOBJ_NEGRANGE 6
#define SOBJ_COND 7
#define SOBJ_NEGCOND 8
#define SOBJ_NEGSTR 9
#define SOBJ_STR 10

#define FLD_DESC_SIZE0 8
#define FLD_DESC_SIZE1 FLD_DESC_SIZE0 + 4
#define CFLD_DESC_SIZE0 12
#define CFLD_DESC_SIZE1 CFLD_DESC_SIZE0 + 8

/* math verb options */ 
#define MATH_OPT_ON_SIZE_ERROR 2

/* Severity codes dor hterror & yyerror */
#define TCOB_SEVERITY_INFO          0
#define TCOB_SEVERITY_WARN          4 
/*#define TCOB_SEVERITY_WARN          2 */
#define TCOB_SEVERITY_ERROR         8

/*
 * expression nodes
 */
struct expr {
        char litflag; /* 5 for expr */
        char op;
        struct expr *left;
        struct expr *right;
};

/*
 * Storage for subscripted variable references.
 * First node is the variable, other are subscripts as 
 * variable/literals with operations.
 * For instance: VAR ( SUB1 - 5, SUB2 + 3 ) is represented as
 * 5 nodes: (sy,op) = (VAR,0) (SUB1,'-') (5,',') (SUB2,'+') (3,',')
 * where the numbers are (struct lit *) pointers and the variables
 * are (struct sym *) pointers.
 */
struct vref {
        char litflag;              /* ',' = end of subscript, 
                                     '+','-' = subscript arith */        
        struct vref *next;         /* link to next in list or NULL */
        void *sym;                 /* variable/literal at this node */
};

/* Node for refmod's */
struct refmod {
        char litflag;              /* 4 = refmod */
        struct sym *off;           /* offset from normal start address */
        struct sym *sym;           /* pointer to original var: must be at the same relative offset as sym in vref */
        struct sym *len;           /* corrected length */ 
        short slot;                /* slot in the data section */
};

/*
 * compile-time list for value ranges of 88-level variables.
 * the first range is stored at the "struct sym", with sym->vr
 * being a pointer to the remaining "struct vrange" nodes.
 */
struct vrange {
        struct vrange *next;       /* pointer to next range of values (88 var) */
        struct lit *value;         /* pointer to literal with initial value */
        struct lit *value2;        /* pointer to first/next key (sort files) */
};
        
/*
 * Node for external data (named sections).
 */
struct named_sect {
        struct named_sect *next;   /* pointer to next named section */
        short sec_no;              /* key: section id */
        char *os_name;             /* name of 01 or 77 data as known by OS */
};

/*        
struct _label {
        unsigned short segment;    // Program segment 
        unsigned short location;   // Label location - part of name 
        unsigned short offset;     // Label location offset 
};
*/        

/* note: "sym" and "lit" must share the same structure */
struct lit {
        char litflag;              /* 1 for literals */
        struct lit *next;          /* next in literals list */
        char *name;                /* name (value) of literal */
        char type;
        int  decimals;
        unsigned location;         /* data area for literal @lit+n */
        unsigned descriptor;       /* descriptor @lit+n */
        short sec_no;              /* asm section number */
        unsigned char all;
        char *nick;
        /* int access_mode;           // ie call_mode */
        int call_mode;             /* call_mode */
        int len;                   /* length of (possibly including NULLs) string */
        char filler[102];          /* Padding to ensure "sym" and "lit" structures are the same size */
};

/* note: "sym" and "lit" must share the same structure */
struct sym {
        char litflag;              /* 1 for literals, 2 for variables */
        struct sym *next;          /* pointer to next symbol with same hash */
        char *name;                /* symbol (variable) name */
        char type;                 /* label or elementary item or group item 
                                      9,A,X,B,C=elem; G=group;
                                      F=file; R=record; S=screen */
        /* int decimals;              // decimal places or organization (files ) */
        union {                        
          int decimals;            /* decimal places  */
          int organization;        /* organization (files ) */
        } uval1;        
                                      
        /* unsigned location;      // offset of variable in stack area 
                                   // or offset file descriptor in data area */
        union {                     
          unsigned int location;   /* offset of variable in stack area */
          unsigned int fdesc;      /* offset file descriptor in data area */
        } uval2;        

        unsigned descriptor;       /* field descriptor offset in data seg */
                                   /* or index field descriptor (files) */
        short sec_no;              /* asm section number */
        struct sym *clone;         /* NULL if this symbol is unique
                                      otherwise, it must be further qualified */        
        int times;                 /* occurs times */

        /* char *picstr;           // pointer to picture string saved or 
                                   // pointer to rec_varying (files) */
        union {                     
          char *picstr;            /* pointer to picture string */
          struct rec_varying *rec_varying; /* pointer to rec_varying (files) */
        } uval9;        

        struct sym *parent;        /* pointer to parent node (level)
                                      pointer to STATUS var (files) */
        /* struct sym *son;        // used in field hierarchy
                                      for files this is the assign 
                                      variable (filename) */
        union {                     
          struct sym *son;         /* used in field hierarchy */
          struct sym *filenamevar; /* files this is the assign variable (filename) */
        } uval7;        


        /* struct sym *brother;    // field variable at the same level or
                                   //   alternate key list pointer (for indexed files) */
        union {                     
          struct sym *brother;     /* field variable at the same level */
          struct alternate_list *alternate; /* obsolete - alternate key list pointer (for indexed files) */
        } uval8;        

        struct sym *ix_desc;       /* key variable (in file descriptor)
                                      pointer to fdesc (in record) */
        struct scr_info *scr;      /* screen info in screen items */
        struct report_info *ri;    /* report info in report items */
        struct lit *value;         /* pointer to literal with initial value */

        /* struct lit *value2;     // pointer to first/next key (sort files) */
        union {                     
          struct lit *value2;      /*  */
          struct sym *sort_data;   /* pointer to first/next key (sort files) */
        } uval4;        

        union {
        struct vrange *vr;         /* pointer to next range of values (88 var) */
        struct refmod *rfm;        /* offset and length of refmod */                
        struct sym *declarative;   /* declarative section */                
        } refmod_redef;        
        int level;                 /* level of field 
                                      or ASSIGN TO DISK/PRINTER (files) */
        /* int access_mode;        // access mode (files) 
                                   // or direction (sort files data ) 
                                   // or call_mode for variables */
        union {                        
          int access_mode;         /* access mode (files)  */
          int direction;           /* direction (sort files dat ) */
          int call_mode;           /* call_mode for variables */
        } uval3;        

        /* int sign;               // sign type (0=no sign,1=trailing) or sort file */
        union {                     
          int sign;                /* sign type (0=no sign,1=trailing) */
          int sort_file;           /* sort file type */
        } uval10;        

        int len;                   /* length of item or max file length (files) */
        unsigned int minlen;       /* min file length (files) */
        char defined;              /* first time defined? */

        /* unsigned pic;           // picture offset in data segment 
                                   // or record offset in stack (files) */
        union {                     
          unsigned int pic;        /* picture offset in data segment */
          unsigned int record;     /* record offset in stack (files) */
        } uval5;        

        int occurs_flg;            /* field occurs */
        int linkage_flg;

        /* struct sym *redefines;     // points to a redefined field or record symbol (files) */
        union {                     
          struct sym *redefines;   /* points to a redefined field */
          struct sym *recordsym;   /* points to a record symbol (files) */
        } uval6;        

        struct {
          unsigned int just_r:1;
          unsigned int is_pointer:1;
          unsigned int blank:1;
          unsigned int spec_value:1;
          unsigned int value:1;
          unsigned int sync:1;
          unsigned int in_redefinition:1;
          unsigned int separate_sign:1;
          unsigned int leading_sign:1;
          unsigned int optional:1;
          unsigned int external:1;
          unsigned int file_external:1;
          unsigned int file_printer:1;
          unsigned int file_stdin:1;
          unsigned int file_stdout:1;
          unsigned int file_stderr:1;
          unsigned int file_isvariable:1;
          unsigned int isfilerecord:1;
          unsigned int is_index:1;
          unsigned int reserved:13;
        } flags;

        unsigned char slack;       /* slack bytes inserted */
        struct xref {              /* xrefrence line number structure */
          unsigned short size;     /* array size */
          unsigned short pos;      /* current free array position  */
          unsigned int *lineno;    /* line numbers array */
        } xrefs;
        struct occurs *occurs;     /* for DEPENDING ON or null if fixed table */
        char pscale;               /* number of 'P's in picture */
        char stype;                /* subtype for type 'B': 5, X, B */

        unsigned int offset_mloc;  /* Memory location offset for 2-49 level items */
        
        /*
        unsigned int psize;        // Size (length) of memory for specific item 
        struct _label  label;      // Label location - part of name 
        
        struct _label {
        unsigned short segment;    // Program segment 
        unsigned short location;   // Label location - part of name 
        unsigned short offset;     // Label location offset 
        } label;
        */
};

/* this (struct rd) is aliased with (struct sym), so tail data is garbage! */
struct rd {
        char litflag;
        struct rd *next;
        char *name;
        char type;                 /* 'W' for report (RD) */
        struct sym *file;          /* file for writing this report */
        struct list *controls;     /* list of controls (listing breaks) */
        struct list *items;        /* list of all report items */
        int page_limit;
        int heading;
        int footing;
        int first_detail;
        int last_detail;
        char filler[98];           /* Padding to ensure "sym" and "rd" structures are the same size */
};

/* additional information for report items */
struct report_info {
        int line;
        int line_offset;           /* PLUS <offset> given */ 
        int column;
        int value_source;          /* SUM, SOURCE (from a variable), literal */
        /* the actual source symbol is in (struct sym *)->value */
};

/* file open_mode clause list */
struct file_open_statement_list {
   int mode;
   struct sym *fname;
   struct file_open_statement_list *next; 
};

enum tcb_file_description_record_clause_type {
        TCB_TYPE_RECORD_NONE,  
        TCB_TYPE_RECORD_FIXED,  
        TCB_TYPE_RECORD_VARIABLE 
};

enum tcb_file_description_clause_type {
        TCB_TYPE_FD_EXTERNAL,  
        TCB_TYPE_FD_GLOBAL,   
        TCB_TYPE_FD_RECORD   
/*      Ignore the rest of the clauses
        TCB_TYPE_FD_BLOCK,    
        TCB_TYPE_FD_LABEL,    
        TCB_TYPE_FD_VALUE,   
        TCB_TYPE_FD_DATA,     
        TCB_TYPE_FD_REPORT,   
        TCB_TYPE_FD_LINAGE,  
        TCB_TYPE_FD_CODE_SET 
*/
};

/* file description entry clauses */
struct fd_entry {
   char ftype;
   struct file_description_record *recd; 
};

/* file description entry clauses */
struct file_description_entry {
        int type;
          union _fd {
          struct file_description_record *recd;
          int global;
          int external;
        } fd;
        struct file_description_entry *next;
};

/* file description record clause 
   record(min, max) and VARYING DEPENDING ON data description */
struct file_description_record {
/*        struct lit *lmin;  */
/*        struct lit *lmax; */ 
        int imin;
        int imax;
        struct sym *lrec;
        int      rectype; /* record type FIXED or VARIABLE  */
};

/* varying record range and actual size */
struct rec_varying {
/*        struct lit *lmin;  */
/*        struct lit *lmax;  */
/*        unsigned int imin; */
/*        unsigned int imax; */
        int imin;
        int imax;
        struct sym *reclen;
};

/* Used to generate display SECTION/PARAGRAPH trace code */
enum tcb_debug_trace_type {
        TCB_DEBUG_TRACE_NONE, 
        TCB_DEBUG_TRACE_SECTION_ENTER, 
        TCB_DEBUG_TRACE_SECTION_EXIT, 
        TCB_DEBUG_TRACE_PARAGRAPH_ENTER, 
        TCB_DEBUG_TRACE_PARAGRAPH_EXIT 
};

/* used to generate variable record length writes */
enum tcb_file_record_varlen_type {
        TCB_RECORD_VARLEN_FORMAT0,  /* No type */
        TCB_RECORD_VARLEN_FORMAT1,  /* RECORD CONTAINS ... or RECORD IS VARYING ... (no DEPENDING clause) */
        TCB_RECORD_VARLEN_FORMAT2,  /* RECORD IS VARYING ... DEPENDING ON ... */
        TCB_RECORD_VARLEN_FORMAT3   /* OCCURS ... DEPENDING ON */
};

/* used to generate variable record length writes */
struct file_record_varlen {
        int type;
        struct lit *lrec;
        struct lit *ulen;
        struct sym *vdepon;
};

/* selection subject set (evaluate statement) */
struct selsubject {
        struct selsubject *next;
        struct sym *var; /* non-numeric variables */
        int type;
};

enum tcb_sortfile_node_type {
        TCB_SORT_NODE_TYPE_NONE,  
        TCB_SORT_NODE_TYPE_FILE,  
        TCB_SORT_NODE_TYPE_PROC  
};

/* sort file list for using/giving clauses*/
struct sortfile_node {
        struct sortfile_node *next;
        struct sym *sy;
};

struct sort_node_container {
        struct sortfile_node *sn;
        int type;
};

/* struct symbol (sym) list */
struct sym_list {
   struct sym *sy;
   struct sym_list *next; 
};

/* Declaratives container type - supports USE exception only */
enum tcb_declarative_use_type {
        TCB_DECLARATIVE_USE_TYPE_NONE,  
        TCB_DECLARATIVE_USE_TYPE_EXCEPTION  
        /* TCB_DECLARATIVE_USE_TYPE_USE_DEBUGGING, */            
        /* TCB_DECLARATIVE_USE_TYPE_USE_REPORTING  */           
};

/* Declaratives container - supports USE exception only */
enum tcb_declarative_use_option {
        TCB_DECLARATIVE_USE_OPTION_NONE,  
        TCB_DECLARATIVE_USE_OPTION_EXCEPTION, 
        TCB_DECLARATIVE_USE_OPTION_ERROR,  
        TCB_DECLARATIVE_USE_OPTION_GLOBAL  
};

enum tcb_declarative_use_options {
        TCB_DECLARATIVE_USE_OPTIONS_NONE,  
        TCB_DECLARATIVE_USE_OPTIONS_FILE_NAME, 
        TCB_DECLARATIVE_USE_OPTIONS_FILE_OPENMODE
};

/* Declaratives USE exception option 
   NOTE: One USE statement can have one or more file names (fname) */
struct tcb_declarative_exception_option {
        int type;
        union  {
          struct sym *fname;
          int omode;
        } u;
        struct sym_list *next;
};

/* Declaratives container - supports USE exception only */
/* Used by NESTED and a SEQUENCE of programs */
struct tcb_declarative {
        int utype; /* Declarative USE statement TYPE */ 
        struct tcb_declarative_exception_option *deo;
        /* int otype; // USE exception option EXCEPTION or ERROR */ 
        int gtype; /* USE exception GLOBAL option - TRUE or FALSE */ 
        struct sym *secname; /* Section name */
};

/* Declaratives list - used by NESTED and a SEQUENCE of programs */
struct tcb_declarative_list {
        struct tcb_declarative *d;
        struct tcb_declarative_list *next;
};

/* Declaratives list container - used by NESTED and a SEQUENCE of programs */
struct tcb_declaratives_list {
        struct tcb_declarative_list *dl; /* List of struct tcb_declarative_list */
        short size;                      /* Number of declaratives in list */
        short modsize;                   /* Number of declaratives of open mode type in list */
};

/* Declaratives lists - used by ALL programs */
struct tcb_declaratives_lists {
        int size;
        struct tcb_declaratives_list *level;
        struct tcb_declaratives_list *next;
};

/* information required by the 'perform ... varying ... after' statements */
struct perf_info { 
        struct sym *pname1;        /* symbol name */
        struct sym *pname2;        /* symbol name */
        unsigned long ljmp;        /* jump label  */
        unsigned long lend;        /* end  label  */
};

struct perform_info { 
       struct perf_info *pf[6]; 
};

/* information required by the math verbs statements */
struct math_var { 
        struct sym *sname;         /* symbol name */
/*        unsigned int rounded;  rounded option: 0=false, 1=true */ 
        unsigned int opts;         /* options: 0=none, 1=rounded, 2=on_size_error, 3=both */ 
        struct math_var *next;
};

/* information required by the math ON SIZE ERROR statement */
struct math_ose { 
        unsigned long ose;   /* 1=on_size, 2=not_on_size, 3=both */ 
        unsigned long lbl1;  /* call label name 1 - on_size */
        unsigned long lbl2;  /* call label name 2 - not_on_size */
        unsigned long lbl4;  /* bypass label name  */
};

/* generic information container used by the [NOT] AT END cluases */
struct ginfo { 
        unsigned long sel;   /* 1=true, 2=not true, 3=both */ 
        unsigned long lbl1;  /* call label name 1 - true */
        unsigned long lbl2;  /* call label name 2 - not true */
        unsigned long lbl3;  /* retrun 1 label name  */
        unsigned long lbl4;  /* retrun 2 label name  */
        unsigned long lbl5;  /* test bypass label name  */
};

/* information required by [NOT] INVALID KEY clauses */
struct invalid_key_element {
        unsigned long lbl1;  /* skip label */
        unsigned long lbl2;  /* start label */
        unsigned long lbl3;  /* finish label */
};

struct invalid_keys {
        struct invalid_key_element *invalid_key;
        struct invalid_key_element *not_invalid_key;
};

/******* supplemental information for screen items **********/
/* this is linked at the sym->index (aliased scrinfo) */
struct scr_info { 
        int attr;
        int line;
        int column;
        struct sym *foreground;
        struct sym *background;
        struct sym *from;
        struct sym *to;
        int label;
        struct sym *line_var;        
        struct sym *column_var;        
        short int line_sign;        
        short int column_sign;        
        struct sym *foreground_var;        
        struct sym *background_var;        
        struct sym *color;        
        struct sym *size;        
};

struct converting_struct {
        struct sym *fromvar;
        struct sym *tovar;
        struct inspect_before_after *before_after;
};

struct tallying_list {
        struct tallying_list *next;
        struct tallying_for_list *tflist;
        struct sym *count;
};

struct tallying_for_list {
        struct tallying_for_list *next;
        int options;
        struct sym *forvar;
        struct inspect_before_after *before_after;
};

struct replacing_list {
        struct replacing_list *next;
        int options;
        struct sym *byvar;
        struct replacing_by_list *replbylist;
        struct inspect_before_after *before_after;
};

struct replacing_by_list {
        struct replacing_by_list *next;
        struct sym *replvar;
        struct sym *byvar;
        struct inspect_before_after *before_after;
};

struct inspect_before_after {
        struct sym *before;
        struct sym *after;
};

struct alternate_list {
        struct alternate_list *next;
        struct sym *key;
        int duplicates;
};

struct unstring_delimited {
        struct unstring_delimited *next;
        short int all;
        struct sym *var;
};

struct unstring_destinations {
        struct unstring_destinations *next;
        struct sym *var;
        struct sym *delim;
        struct sym *count;
};

struct string_from {
        struct string_from *next;
        struct sym *var;
        struct sym *delim;
};

struct parm_list {
        struct parm_list *next;
        void *var;
        unsigned location;
        short sec_no;
};

struct coord_pair {
        int lin;
        int col;
};

struct index_to_table_list {
        struct index_to_table_list *next;
        char *idxname;
        char *tablename;
        char *keyname;
        char seq; /* '0' = none, '1' = ASCENDING, '2' = DESCENDING */
};

union label_def {
        struct {
                unsigned n:31;
                unsigned defined:1;
                unsigned off;
        }l;
        unsigned long x;
};

struct condition {
        struct sym *sy;        /* implied first operand */
        int oper;                /* operator */
};

struct init_str {           /* structure to hold initialization sequence */
        struct sym *sy;     /* pointer on symbol */
        char type;          /* type of symbol */
        int len;            /* size of symbol */
        unsigned location;  /* location of occurence of symbol */
        struct lit *value;  /* original value of symbol */
};

struct init_str_tab {
   struct init_str ent[1];
};

struct list {
        struct list *next;
        void *var;
};

/* Generic variable list for literals, identifiers */
struct gvar_list {
        union gvar {
              struct gvar_list *gvar;     
              struct sym *sym;          /* name variable  */
              void *var;
        }u;
        unsigned int attribute;         /* attribute */
        struct gvar_list *next;     
};

/* OCCURS ... DEPENDING ON info */
struct occurs {
        struct sym *depend;
        int min,max;
};

struct _ldata {
        int imin;
        int imax;
}ldata;
 
struct _vrdata {
        int type;
        unsigned int lrec;
        struct occurs *oc;
        unsigned int oculen;
        struct _vrdata *next; 
};
 
struct _dtracedata {
        unsigned int size;
        char **name; 
/*        char *name[]; */
};
 
/* standard field classes */
#define CLASS_NUMERIC                0
#define CLASS_ALPHABETIC             1
#define CLASS_ALPHABETIC_LOWER       2
#define CLASS_ALPHABETIC_UPPER       3

/* extended condition flags */
#define COND_UNARY                0x10
#define COND_CLASS                0x20

/* minor token numbers */

/* USAGETOK - USAGENUM */
#define USAGE_COMP                   0
#define USAGE_COMP1                  1
#define USAGE_COMP2                  2
#define USAGE_COMP3                  3
#define USAGE_INDEX                  4
#define USAGE_BINARY_CHAR            5
#define USAGE_BINARY_SHORT           6
#define USAGE_BINARY_LONG            7
#define USAGE_BINARY_DOUBLE          8
#define USAGE_BINARY_UCHAR           9
#define USAGE_BINARY_USHORT         10
#define USAGE_BINARY_ULONG          11
#define USAGE_BINARY_UDOUBLE        12
#define USAGE_DISPLAY               13
#define USAGE_POINTER               14
#define USAGE_COMP5                 15
#define USAGE_COMPX                 16

/*  DISPLAY  e' um token independente deste grupo */

/* DATE-TIME */
#define DATE                         0
#define TIME                         1
#define DAY                          2
#define DAY_OF_WEEK                  3

/* OPENMD */
/*
#define INPUT                        1
#define I_O                          2
#define OUTPUT                       3
#define EXTEND                       4
*/
/* ZERONUM */
/*
#define ZERO                         0
#define ZEROS                        1
#define ZEROES                       2
*/
/* DIVISNUM */
/*
#define IDENTIFICATION               0
#define ENVIRONMENT                  1
#define DATA                         2
#define PROCEDURE                    3
*/

/* CONDITIONAL */
#define EQUAL                        1
#define LESS                         2
#define GREATER                      4
#define GEQ                          5
#define LEQ                          3
#define NEQ                          6

/* COMMENTING */
/*
#define SOURCE_COMPUTER              1
#define OBJECT_COMPUTER              2
#define AUTHOR                       3
#define DATE_WRITTEN                 4
#define DATE_COMPILED                5
#define INSTALLATION                 6
#define SECURITY                     7
*/

/* DIRECTION */
#define ASCENDING                    1
#define DESCENDING                   2

/* SPECIAL VARIABLES  */
#define SVAR_RETURN_CODE             "RETURN-CODE"
#define SVAR_TRACE_DISPLAY           "%TRACE_DISPLAY%"

/* htcobgen.c */
extern int hash(char *s);
extern char *savename(char *s);
extern char *upcase(char *s, char *buf);
extern void update_xreflist(struct sym *as);
extern struct sym *lookup(char *s, int tab);
extern struct sym *install(char *name, int tab, int cloning);
extern struct lit *install_lit(char *name, int length, int all);
extern struct sym *lookup_label(struct sym *sy, struct sym *parent);
extern struct sym *lookup_variable(struct sym *sy, struct sym *parent);
extern struct sym *lookup_parent(struct sym *sy, struct sym *parent);
extern struct sym *lookup_for_redefines(struct sym *sy);
extern void clear_symtab(void);
extern void clear_offsets(void);
extern char sign_to_char(int digit);
extern void invert_literal_sign(struct lit *sy);
extern void check_decimal_point(struct lit *lit);
extern char *sch_convert(char *s);
extern int is_variable(struct sym *sy);
extern int is_subscripted(struct sym *sy);
extern void emit_lit(char *s, int len);
extern void emit_lit_fill(int c, int len);
extern void gen_init_value(struct lit *sy, int var_len);
extern void stabs_line(void);
extern void stabs_block(int end);
extern int gen_main_rtn(void);
extern int pgm_header(char *id, int type);
extern void data_trail(void);
extern int adjust_linkage_vars(int start_offset);
extern void do_init_val(void);
extern void proc_header(int using);
extern void proc_trail(int using, struct sym *syret);
extern void dump_working(void);
extern void save_field_in_list(struct sym *sy);
extern void save_literal(struct lit *v, int type);
extern void save_named_sect(struct sym *sy);
extern struct lit *save_special_literal(char val, char picc, char *nick);
extern void define_switch_field(struct sym *sy, struct sym *sy2);
extern struct lit *define_num_lit(int value);
extern void save_switch_value(struct sym *sy, int value);
extern void put_disp_list(struct sym *sy);
extern char *memref(struct sym *sy);
extern char *memrefat(struct sym *sy);
extern char *memrefd(struct sym *sy);
extern void push_immed(int i);
extern void push_eax(void);
extern void push_edx(void);
extern void pop_eax(void);
extern void push_ebx(void);
extern void push_at_ebx(struct sym *sy);
extern void push_at_eax(struct sym *sy);
extern void load_at_eax(struct sym *sy);
extern void cleanup_rt_stack(void);
extern void asm_call(char *s);
extern void asm_call1(char *s);
extern void emt_cobrtl_call(char *s, char *prefix);
extern int pic_digits(struct sym *sy, char target);
extern int get_max_edt_len(struct sym *sy);
extern int query_comp_len(struct sym *sy);
extern int symlen(struct sym *sy);
extern int sym_min_pic(struct sym *sy);
extern int varsize_ch(struct sym *sy);
extern void gen_call_scr_process(struct sym *sy);
extern void add_alternate_key(struct sym *sy, int duplicates);
extern struct list *insert_list(struct list *l, void *item);
extern void free_list(struct list *l);
extern void mark_decl_list(struct list *l);
extern struct scr_info *alloc_scr_info(void);
extern struct inspect_before_after *alloc_inspect_before_after(struct inspect_before_after *ba, int before_after, struct sym *var);
extern struct converting_struct *alloc_converting_struct(struct sym *fromvar, struct sym *tovar, struct inspect_before_after *ba);
extern struct tallying_list *alloc_tallying_list(struct tallying_list *tl, struct sym *count, struct tallying_for_list *tfl);
extern struct tallying_for_list *alloc_tallying_for_list(struct tallying_for_list *tfl, int options, struct sym *forvar, struct inspect_before_after *ba);
extern struct replacing_list *alloc_replacing_list(struct replacing_list *rl, int options, struct replacing_by_list *rbl, struct sym *byvar, struct inspect_before_after *ba);
extern struct replacing_by_list *alloc_replacing_by_list(struct replacing_by_list *rbl, struct sym *replvar, struct sym *byvar, struct inspect_before_after *ba);
extern struct unstring_delimited *alloc_unstring_delimited(short int all, struct sym *var);
extern struct unstring_destinations *alloc_unstring_dest(struct sym *var, struct sym *delim, struct sym *count);
extern struct string_from *alloc_string_from(struct sym *var, struct sym *delim);
extern void gen_unstring(struct sym *var, struct unstring_delimited *delim, struct unstring_destinations *dest, struct sym *ptr, struct sym *tally);
extern void gen_stringcmd(struct string_from *sf, struct sym *sy, struct sym *ptr);
extern void gen_display_screen(int nl);
extern void gen_display_line(int dupon, int nl);
extern void gen_gotoxy_expr(void);
extern void gen_accept(struct sym *sy, int echo, int main);
extern void gen_accept_from_chron(struct sym *sy, int date_fmt, int is_yyyy);
extern void gen_accept_from_inkey(struct sym *sy);
extern void gen_accept_from_cmdline(struct sym *sy);
extern void gen_accept_env_var(struct sym *sy, struct sym *v);
extern struct perf_info *create_perf_info(struct sym *sy1, struct sym *sy2, unsigned long lj, unsigned long le);
extern struct perform_info *create_perform_info(void);
extern char *check_perform_variables(struct sym *sy1, struct perform_info *pi1);
extern struct expr *create_expr(char op, struct expr *left, struct expr *right);
extern void free_expr(struct expr *e);
extern void free_expr_list(void);
extern struct math_var *create_mathvar_info(struct math_var *mv, struct sym *sy, unsigned int opt);
extern void delete_mathvar_info(struct math_var *mv);
extern struct math_ose *math_on_size_error0(void);
extern struct math_ose *math_on_size_error1(struct math_ose *v);
extern void math_on_size_error2(struct math_ose *v);
extern void math_on_size_error3(struct math_ose *v, char end);
extern struct math_ose *math_on_size_error4(struct math_ose *v, unsigned long ty);
extern void math_on_size_error5(struct math_ose *v);
extern void gen_add(struct sym *s1, struct sym *s2, int rnd);
extern void gen_subtract(struct sym *s1, struct sym *s2, int rnd);
extern void gen_multiply(struct sym *s1, struct sym *s2, struct sym *s3, int rnd);
extern void gen_compute1(struct math_var *vl1, struct sym *sy1);
extern void gen_compute2(struct math_var *vl1, struct sym *sy1, struct math_ose *v1);
extern void gen_add1(struct math_var *vl0, struct math_var *vl2, struct math_ose *v1);
extern void gen_add2(struct math_var *vl1, struct math_var *vl2, struct sym *sy1, struct math_ose *v1);
extern void gen_add3(struct math_var *vl1, struct math_var *vl2, struct math_ose *v1);
extern void gen_subtract1(struct math_var *vl0, struct math_var *vl2, struct math_ose *v1);
extern void gen_subtract2(struct math_var *vl1, struct math_var *vl2, struct sym *sy1, struct math_ose *v1);
extern void gen_subtract3(struct math_var *vl1, struct math_var *vl2, struct math_ose *v1);
extern void gen_multiply1(struct math_var *vl1, struct sym *sy1, struct math_ose *v1);
extern void gen_multiply2(struct math_var *vl1, struct sym *sy1, struct sym *sy2, struct math_ose *v1);
extern void gen_divide1(struct math_var *vl1, struct sym *sy1, struct math_ose *v1);
extern void gen_divide2(struct math_var *vl1, struct sym *sy1, struct sym *sy2, struct math_ose *v1);
extern void gen_divide4(struct sym *s1, struct sym *s2, struct sym *s3, struct sym *s4, int rnd, struct math_ose *v1);
extern struct vref *create_subscripted_var(struct sym *sy, struct vref *subs);
extern struct vref *create_subscript(struct sym *sy);
extern struct vref *add_subscript_item(struct vref *subs, char op, struct sym *item);
extern struct vref *add_subscript(struct vref *ref, struct vref *subs);
extern int check_subscripts(struct sym *subs);
extern void create_occurs_info(int min, int max, struct sym *depend);
extern struct refmod *create_refmoded_var(struct sym *sy, struct sym *syoff, struct sym *sylen);
extern int check_refmods(struct sym *var);
extern void gen_subscripted(struct vref *subs);
extern struct sym *get_variable_item(struct sym *sy);
extern void gen_temp_storage(int size);
extern void adjust_desc_length(struct sym *sy);
extern void value_to_eax(struct sym *sy);
extern void load_address(struct sym *var);
extern void load_location(struct sym *var, char *cpureg);
extern void loadloc_to_eax(struct sym *sy_p);
extern void gen_loadloc(struct sym *sy_p);
extern void set_ptr(struct sym *sy);
extern void gen_loaddesc1(struct sym *sy, int variable_length);
extern void gen_loaddesc(struct sym *sy);
extern void gen_loadvar(struct sym *sy);
extern void gen_loadval(struct sym *sy);
extern void gen_pushval(struct sym *sy);
extern void gen_store_fnres(struct sym *sy);
extern int is_numeric_sy(struct sym *sy);
extern int is_numeric_dest_sy(struct sym *sy);
extern void gen_class_check(struct sym *sy, int class);
extern void gen_inspect(struct sym *var, void *list, int operation);
extern void gen_tcob_proto1(struct sym *sy);
extern void gen_tcob_proto2(struct sym *sy1, struct sym *sy2);
extern void gen_move(struct sym *sy_src, struct sym *sy_dst);
extern void gen_moves(struct sym *sy_src, struct gvar_list *gsylst);
extern struct gvar_list *gvar_list_append(struct gvar_list *l, struct sym *item, int linenum);
extern void gen_save_chainings(struct gvar_list *gsylst);
extern void gen_save_chaining(struct sym *sy);
extern void gen_save_usings(struct gvar_list *gsylst);
extern void gen_initialize(struct sym *sy_start);
extern void gen_initializes(struct gvar_list *gsylst);
extern struct gvar_list *sort_key_list_create (struct gvar_list *item, int atrbt);
extern struct gvar_list *sort_keys_list_append (struct gvar_list *l, struct gvar_list *item);
extern void gen_movelength(struct sym *sy1, struct sym *sy2);
extern void gen_move_init(struct sym *sy_src, struct sym *sy_dst);
extern void init_field_val(struct sym *sy);
extern int check_fields(struct sym *sy);
extern void def_field_storage(struct sym *sy, int fld_len);
extern struct sym *define_label(struct sym *sy, int lab_type, struct sym
        *parent, int parent_type);
extern void gen_movecorr(struct sym *sy1, struct sym *sy2);
extern void gen_addcorr(struct sym *sy1, struct sym *sy2, int rnd);
extern void gen_addcorr1(struct math_var *mv1, struct math_var *mv2, int rnd, struct math_ose *v1);
extern void gen_subtractcorr(struct sym *sy1, struct sym *sy2, int rnd);
extern void gen_subtractcorr1(struct math_var *mv1, struct math_var *mv2, int rnd, struct math_ose *v1);
extern void gen_set_complex( struct sym *idx, int which, struct sym * var);
extern void gen_set(struct sym *idx, int which, struct sym *var, int adrof_idx, int adrof_var);
extern int gen_evaluate_start(void);
extern int subject_set_size(struct selsubject *ssbj);
extern int selection_object_size(int type);
extern int push_selection_subject_copy(int level, struct selsubject *ssbj, int stkadd, int objtype);
extern int selection_subject_type(int level, struct selsubject *ssbj);
extern void gen_when_check(int level, struct selsubject *ssbj, int type, int endcase, struct sym *var);
extern void gen_bypass_when_case(int bypass);
extern int gen_end_when(int n, int endcase, int sentence);
extern void push_condition(void);
extern void gen_goto_depending(struct list *l, struct sym *sy);
extern void gen_goto(struct list *l);
extern int gen_check_zero(void);
extern unsigned long gen_at_end(int status);
extern unsigned long gen_testif(void);
extern void gen_not(void);
extern unsigned long gen_andstart(void);
extern unsigned long gen_orstart(void);
extern void gen_dstlabel(unsigned long lbl);
extern unsigned long gen_passlabel(void);
extern unsigned long gen_marklabel(void);
extern void gen_jmplabel(unsigned long lbl);
extern void gen_push_int(struct sym *sy);
extern void gen_perform_test_counter(unsigned long lbl);
extern void gen_perform_times(unsigned long lbl);
extern void gen_perform_thru(struct sym *s1, struct sym *s2);
extern void gen_perform(struct sym *sy);
extern void set_usage(struct sym *sy, int usage);
extern void gen_picture(void);
extern int save_pic_char(char c, int i);
extern void gen_SearchLoopCheck(unsigned long lbl5, struct sym *syidx, struct sym *sytbl);
extern void gen_SearchAllLoopCheck(unsigned long lbl3, struct sym *syidx, struct sym *sytbl, struct sym *syvar, unsigned long lstart, unsigned long lend);
extern void define_special_fields(void);
extern struct sym *define_temp_field(char desired_type, int desired_len);
extern int define_implicit_field(struct sym *sy, struct sym *sykey, int idxlen);
extern void Initialize_SearchAll_Boundaries(struct sym *sy, struct sym *syidx);
extern struct sym *determine_table_index_name(struct sym *sy);
extern void define_field(int level, struct sym *sy);
extern struct sym *alloc_filler(void);
extern struct selsubject *save_sel_subject(int type, struct selsubject *ssubj, struct sym *sy);
extern void release_sel_subject(int label, struct selsubject *ssbj);
extern void compute_subject_set_size(struct selsubject *ssbj);
extern int set_field_value_sw(struct sym *sy, int times);
extern int set_field_length(struct sym *sy, int times);
extern unsigned field_alignment(struct sym *sy, unsigned location);
extern void set_field_location(struct sym *sy, unsigned location);
extern void scr_set_column(struct scr_info *si, struct sym *sy, int plus_minus);
extern void scr_set_line(struct scr_info *si, struct sym *sy, int plus_minus);
extern void save_report(struct sym *rep, struct sym *file);
extern void update_report_field(struct sym *sy);
extern void update_screen_field(struct sym *sy, struct scr_info *si);
extern void update_renames_field(struct sym *sy1, struct sym *sy2);
extern void update_field(struct sym *sy);
extern void close_fields(void);
extern void resolve_labels(void);
extern void open_section(struct sym *sect);
extern void close_section(void);
extern char *label_name(struct sym *lab);
extern char *var_name(struct sym *sy);
extern void close_paragr(void);
extern void open_paragr(struct sym *paragr);
extern void gen_stoprun(void);
extern void gen_exit(int code);
extern void set_variable_values(struct lit *v1, struct lit *v2);
extern void gen_condition(struct sym *sy);
extern void gen_compare_exp(int value);
extern void gen_compare(struct sym *s1, int value, struct sym *s2);
extern void assign_expr(struct sym *sy, int opt, char end);
extern int push_expr(struct sym *sy);
extern int push_subexpr(struct sym *sy);
extern void add_expr(void);
extern void subtract_expr(void);
extern void multiply_expr(void);
extern void divide_expr(void);
extern void pow_expr(void);
extern void gen_save_filedesc(struct sym *f);
extern void alloc_file_entry(struct sym *f, int opt);
extern void dump_alternate_keys(struct sym *r, struct sym *f, struct alternate_list *alt);
extern void dump_fdesc(void);
extern void gen_fdesc(struct sym *f, struct sym *r);
extern int  gen_fsd(struct sym *f, struct sym *fdesc, struct file_description_entry *fd, int iflag);
extern void gen_status(struct sym *f);
extern void gen_perform_decl(struct sym *f, void *poption);
extern void gen_file_exception(struct sym *f, int imode, int option);

extern struct sym *create_status_register(char *name);

extern struct sortfile_node *alloc_sortfile_node(struct sym *sy);
extern struct sortfile_node *alloc_sortfile_node2(struct sym *sy1, struct sym *sy2);
extern struct sortfile_node *append_sortfile_node(int type, struct sortfile_node *sn, struct sym *sy);
extern struct sort_node_container *alloc_node_container(int type, struct sortfile_node *sn);
extern void sort_keys_append(struct sym *fname, struct gvar_list *l);

extern void gen_sort_using(struct sym *f, struct sortfile_node *sn);
extern void gen_sort_giving(struct sym *f, struct sortfile_node *sn);
/* extern void gen_sort(struct sym *f); */
extern void gen_sort(struct sym *f, struct sort_node_container *snc1, struct sort_node_container *snc2); 

extern void gen_save_filevar(struct sym *f, struct sym *buf);
/* Same as 'gen_save_filevar' but without the record (buf) */
extern void gen_save_filevar2(struct sym *f); 

extern void gen_save_sort_fields( struct sym *f, struct sym *buf );
extern void gen_open(int mode, struct sym *f);
extern void gen_close_sort(struct sym *f);
extern void gen_close(struct sym *f);
extern int  gen_reads(struct sym *f, struct sym *buf, struct sym *key, 
        int next_prev, int sel, int withlock );
extern void gen_return_stmt(struct sym *f, struct sym *buf);
extern void gen_read(struct sym *f, struct sym *buf, struct sym *key,
        int ikey, int withlock);
extern void gen_read_next(struct sym *f, struct sym *buf, int next_prev,
        int withlock);
extern void gen_release(struct sym *r, struct sym *buf);
extern void gen_write(struct sym *r, struct sym *advar, struct sym *buf);
extern void gen_write_adv(struct sym *r, struct sym *advar, struct sym *buf, int opt);
extern void gen_rewrite(struct sym *r, struct sym *buf);
extern void gen_start(struct sym *f, int cond, struct sym *key);
extern void gen_delete(struct sym *f);
extern void set_rec_varying_info(struct sym *f, unsigned int imin, unsigned int imax, struct sym *reclen);
extern struct file_description_record *set_file_record_clause(struct lit *lrecmax, 
       struct lit *lrecmin, struct sym *lrec, int rectype);
extern struct file_description_entry *set_fd_clause(struct file_description_entry *fd1, struct file_description_entry *fd2);
extern struct file_description_entry *set_fd_clause_external(void);
extern struct file_description_entry *set_fd_clause_global(void);
extern struct file_description_entry *set_fd_clause_record(struct file_description_record *fdrec);

extern void gen_get_switches();
extern void gen_set_switch(struct sym *var, struct sym *sy);
extern struct list *chain_var(struct sym *sy);
extern void gen_push_using(struct sym *sy);
extern void gen_save_using(struct sym *sy);

extern void gen_enter_runelement();

extern unsigned long int emt_call(struct lit *v, int stack_size, int exceplabel, int notexceplabel,struct sym *ret);
extern unsigned long int emt_call_loadlib(struct lit *v);
extern int begin_on_except(void);
extern void check_call_except(int excep, int notexcep, int exceplabel, int notexceplabel, int endlabel);
/*extern void gen_inline_intrinsic(struct sym *v, short name_len, struct sym *temporary);*/
extern struct sym *gen_intrinsic_call(struct sym *v);
extern short get_std_val(struct sym *sy);
extern int get_nb_fields(struct sym *sy, int sw_val);
extern int build_init_str(struct sym *sy, int nb_fields);
extern void gen_from_init_str(int nb_fields);
extern void gen_init_str(struct sym *sy, char init_ctype, int len);
extern void mark_actives(int first, int last);
extern void dump_symbols(void);
extern void chg_underline(char *s);
extern struct ginfo *ginfo_container0(void);
extern struct ginfo *ginfo_container1(struct ginfo *v);
extern void   ginfo_container2(struct ginfo *v, unsigned long ty);
extern struct ginfo *ginfo_container3(struct ginfo *v, unsigned long ty);
extern void   ginfo_container4(struct ginfo *v);
extern struct invalid_key_element * gen_before_invalid_key ();
extern struct invalid_key_element * gen_after_invalid_key (struct invalid_key_element *p);
extern struct invalid_keys * gen_invalid_keys (struct invalid_key_element *p1, struct invalid_key_element *p2);
extern void gen_test_invalid_keys (struct invalid_keys *p, struct sym *f, int fs);
extern int sort_exref_compare(const void *z1, const void *z2);
extern int pgm_name_validate(char *sin, char *sout, int idtype);
extern struct sym *define_std_filename(int value);
extern struct file_open_statement_list *set_file_open_stm_list(int mode, struct file_open_statement_list *fo1, struct file_open_statement_list *fo2);
extern struct file_open_statement_list *set_file_open_stm(struct sym *f, struct file_open_statement_list *fol);
extern int gen_read_key_validate(struct sym *f,  struct sym *k); 
extern int gen_start_key_validate(struct sym *f,  struct sym *k);

extern void dump_key_indexes(struct sym *r, struct sym *idx, int nkeys, struct alternate_list *alt); 
extern int get_number_of_index_keys(struct sym *pidx, struct alternate_list *alt); 

extern void gen_debug_trace(struct sym *secpara, int type); 
extern void dump_trace_display(void); 
extern int trace_display_install(char *name);
extern int trace_display_expand(int zsize);
extern void trace_display_clear(void);
extern void gen_trace_stm(int traceSw);

extern int file_select_clause_verify(struct sym *sy);
extern struct sym* file_select_clause_init(struct sym *sy, int flag_optional); 
extern struct sym* file_description_append_rec(struct sym *sy1, struct sym *sy2); 

void append_declaratives_list(struct sym *secname, struct tcb_declarative *d);
extern struct tcb_declarative *define_declarative(int utype, struct tcb_declarative_exception_option *deo, int gtype);
extern struct tcb_declarative_exception_option *set_declarative_exception_option_mode(int mode);
extern struct tcb_declarative_exception_option *set_declarative_exception_option_name(struct sym *fname, struct tcb_declarative_exception_option *ideo);

extern char *convert_variable_name(struct sym *sy);

extern int main(int argc, char *argv[]);


/* htcobol.c */
extern void opt_is(int i);
extern void hterror(int erno, int severity, char *s, ...);
extern void yywarn(char *s, ...);
extern void yyerror(char *s, ...);
extern int yyparse(void);
extern void yyerror1(char *s, ...);

/* pp_parser.tab.c */
extern void pp_yyerror(char *s, ...);
extern int pp_yyparse(void);

/* htglobals.c */
extern int process_command_line(int argc, char *argv[], int *nidx);
extern void do_file_cleanup(void);
extern int process_assemble(void);
extern int process_ld(void);
extern int process_shlib_ld(void);
/* extern int process_lib_ld(void);*/
extern int read_compiler_options(void);
extern int check_option(char *option_in, char *arg);
extern void turn_on_list_mode(void);
extern void turn_off_list_mode(void);
extern void turn_on_xref(void);
extern void turn_off_xref(void);
extern void pass_options (char *optlst);
extern int pexec(char *cmdstr);
extern void process_verbose_options (int ac, char *av[]);
extern int find_copybook_file(char *fname, char *lname);

/* scan.c */
extern int yylex(void);
extern void yyrestart(FILE *input_file);
extern int is_integer_token(char *tok);
extern int is_valid_identifier(char *tok);
extern int lex_fgets(char *buf, int maxsize);
extern void dcs(void);
extern char *copy_strip_spaces(char *s);
extern void add_copy_replacement(char *orig_value, char *replacement);
extern void copy_do_replacements(char *buffer);
extern void copy_switch(char *filename);
extern struct reserved_sym *lookup_reserved(char *s);
extern void install_reserved(void);
extern int reserved(char *s);
extern struct intrinsic_sym *lookup_intrinsic(char *s);
extern void scdebug(char *fmt, ...);
extern int yywrap(void);

/* reswords.c */
/* Enumerate the types of intrinsic functions */
enum {
        ITYPE_FLOAT,
        ITYPE_INT,
        ITYPE_DATE,
        ITYPE_DATETIME,
        ITYPE_JULIANDATE,
        ITYPE_YEAR,
        ITYPE_ALPHA,
        ITYPE_INLINE
};

struct intrinsic_function {
        char *name;
        char function_type;
        short args;
};
struct intrinsic_function *lookup_intrinsic_function( char *s );

#define ANY_NUMBER 32767        

#endif
