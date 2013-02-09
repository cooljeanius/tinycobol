/* 
 * Copyright (C) 2005 - 2009  David Essex, Rildo Pragana.
 * Copyright (C) 2003, Rildo Pragana, Bernard Giroud.
 * Copyright (C) 2002, Rildo Pragana, Jim Noeth, Bernard Giroud.
 * Copyright (C) 2001, 2000, 1999,  Rildo Pragana, Jim Noeth, 
 *               David Essex, Glen Colbert.
 * Copyright (C) 1993, 1991  Rildo Pragana.
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

 * Assembler Code Generator for TinyCOBOL Compiler
 * 
 * Ideally this module should only contain functions which
 * are assembler dependent.

*/

/*
#define DEBUG_COMPILER_LEVEL    1 
#define DEBUG_COMPILER_LEVEL1   1 
#define DEBUG_COMPILER_LEVEL2   1 
*/

#include "htconfig.h"
#include "htversion.h"
#include "htcoboly.h"
#include "htcoblib.h"
#include "htglobals.h"
#include "mwindows.h"


#define decimal_char() (decimal_comma ? ',' : '.')
extern int pgm_segment;
extern int screen_io_enable;
extern int decimal_comma;
extern char currency_symbol;
char sch_convert_buf[512];

extern struct sym *screen_status_field;  /* variable of crt status */
extern struct sym *cursor_field;         /* variable of cursor */
extern struct lit *program_name_literal; /* literal thar holds the program name */ 
        
extern int stabs_on_sw;

extern struct lextab literal;
extern int yydebug;
extern struct sym *curr_file;

extern struct sym *curr_paragr,*curr_section;
extern struct sym *curr_field;
extern short curr_call_mode;
extern short curr_call_convention;
extern unsigned stack_offset;        /* offset for variables on the stack */
/*#define SAVED_EBX_OFFSET 4*/        /* relative to %ebp */
extern unsigned stack_plus;
extern unsigned global_offset;        /* offset for global variables (DATA) */
/*unsigned file_offset=0;*/
extern unsigned literal_offset;
#undef SEC_WORKING
#define SEC_WORKING SEC_DATA
#define SEC_RETURN_CODE SEC_DATA
extern unsigned data_offset;
/*#define data_offset global_offset*/
extern unsigned linkage_offset;
extern unsigned using_offset;
/* tmpvar_offset: for storage of temporary variables, 
with space reclaimed after the current instruction*/
extern unsigned tmpvar_offset;        
extern unsigned tmpvar_max;

extern unsigned last_lineno;
extern short at_procedure;
extern short refmod_slots;
static char name_buf[MAXNAMEBUF];

extern int has_linkage;
extern int module_flag;
extern int nested_flag;

extern short HTG_debug_trace_flag; 

extern short main_flag;       /* Does it have an main entry point */
extern int main_entry_flag;   /* Main entry point detected */
extern char main_entry_buf[]; /* main entry point name */

extern short HTG_stoprun_proc_flag;

extern struct lit *spe_lit_ZE;
extern struct lit *spe_lit_01;
extern struct lit *spe_lit_SP;
extern struct lit *spe_lit_LV;
extern struct lit *spe_lit_HV;
extern struct lit *spe_lit_QU;

extern struct list *expr_list;
extern struct list *files_list;
extern struct list *disp_list;
extern struct parm_list *parameter_list;
extern struct list *fields_list;
extern struct list *last_field;
extern struct index_to_table_list *index2table;
extern struct named_sect *named_sect_list;
extern struct list *switches_list;
extern struct list *vars_list;
extern short next_available_sec_no;
extern short default_sec_no;
extern short curr_sec_no;

extern struct parm_list *chaining_list;  /* chaining variables */

extern int screen_label;
extern int para_label;
extern int block_label;
extern int line_label;
extern int paragr_num;
extern int loc_label;
extern unsigned char picture[100];        /* for max 50 signs and counts */
extern int picix,piccnt,decimals,sign,v_flag,n_flag,digits,pscale;
extern int filler_num;
extern int active[37];
extern int at_linkage;
extern int stackframe_cnt;
extern int inner_stack_size;

#if !defined(__WINDOWS__)
/* char program_id[120] = "main"; */
/* char *pgm_label = "main";  */
char program_id[120] = "zzz"; 
char *pgm_label = "xxx"; 
#else
char program_id[120] = "_main";
char *pgm_label = "_main"; 
#endif
/*
extern char program_id[120];
extern char *pgm_label; 
*/
extern int initial_flag;
extern struct list *report_list;
static int need_desc_length_cleanup=0;
extern int stabs_started;

extern struct sym *vartab[ HASHLEN ];
extern struct sym *labtab[ HASHLEN ];
extern struct lit *littab[ HASHLEN ];
extern struct _dtracedata dtracedata;


/* convert control characters to don't corrupt the assembly output */
char * 
sch_convert( char *s ) {
        int n=0;
        char *d=sch_convert_buf;
        while (*s && n++<45) {
                if (*s >= ' ' && *s < '\x7f') {
                        *d++=*s++;
                }
                else {
                        *d++ = (*s++ & 0x0f) + ' ';
                }
        }
        if (n>=45) {
                sprintf(sch_convert_buf+40,"...");
        }
        else {
                *d=0;
        }
        return sch_convert_buf;
}

/*
**        Code Generating Routines
*/
static char *sec_name( short sec_no ) {
        struct named_sect *nsp;

        for (nsp=named_sect_list;nsp!=NULL;) {
                if (nsp->sec_no == sec_no)
                        return nsp->os_name;
                nsp=nsp->next;
        }
        return (char *)nsp;
}

static char memref_buf[128];
char *memref( struct sym *sy ) {
        if (sy->sec_no < SEC_FIRST_NAMED) {
                switch (sy->sec_no) {
                case SEC_CONST:
                        /* sprintf(memref_buf,"$c_base%d+%d", pgm_segment,sy->uval2.location); */
                        sprintf(memref_buf,"$c_base%d_%d", pgm_segment, sy->uval2.location);
                        break;
                case SEC_DATA:
                        {
                         /*
                         {
                          if(sy->parent != NULL) {
                            fprintf(stderr, "debug memref 1 : name %s, parent name=%s;\n", sy->name, sy->parent->name);
                            if(sy->parent->parent != NULL) 
                               fprintf(stderr, "debug memref 2 : name %s, parent name=%s;\n", sy->parent->name, sy->parent->parent->name);
                          }
                         }
                         */
                         /* sprintf(memref_buf,"$w_base%d+%d", pgm_segment, sy->uval2.location); */
                         /* sprintf(memref_buf,"$w_base%d_%d", pgm_segment, sy->uval2.location); */
                         if (sy->offset_mloc == 0) 
                            sprintf(memref_buf, "$w_base%d_%d", pgm_segment, sy->uval2.location);
                         else 
                            sprintf(memref_buf, "$w_base%d_%d+%d", pgm_segment, sy->offset_mloc, sy->uval2.location - sy->offset_mloc); 
                         /*
                         char *vname = convert_variable_name(sy); 
                         if (sy->flags.isfilerecord != 1) {
                           if (sy->offset_mloc == 0) 
                               sprintf(memref_buf, "$%s.%d", vname, pgm_segment); 
                           else 
                               sprintf(memref_buf, "$%s.%d+%d", vname, pgm_segment, sy->uval2.location - sy->offset_mloc); 
                         }
                         else {
                           struct sym *sy1 = sy->uval6.recordsym;
                           if (sy->offset_mloc == 0) 
                               sprintf(memref_buf, "$%s.%d", vname, pgm_segment);
                           else 
                               sprintf(memref_buf, "$%s.%d+%d", vname, pgm_segment, sy->uval2.location - sy->offset_mloc);
                         }
                         */
                        }
                        break;
                case SEC_STACK:
                case SEC_ARGS:
                        sprintf(memref_buf,"-%d(%%ebp)", sy->uval2.location);
                        break;
                case SEC_TEMPS:
                        sprintf(memref_buf,"-%u(%%esp)", sy->uval2.location);
                        break;
                default:
                        /* Make sure we have an error at assembly stage */
                        sprintf(memref_buf,"$ww_base%d+%d #sec:%d", pgm_segment,
                                sy->uval2.location, sy->sec_no);
                        yyerror("undefined variable %s",sy->name);
                }
        }
        else {
                sprintf(memref_buf,"$%s+%d", sec_name(sy->sec_no), sy->uval2.location);
        }
        return memref_buf;
}

char *memrefat( struct sym *sy ) {
        switch (sy->sec_no) {
        case SEC_CONST:
                /* sprintf(memref_buf,"c_base%d+%d", pgm_segment,sy->uval2.location); */
                sprintf(memref_buf,"c_base%d_%d", pgm_segment, sy->uval2.location);
                break;
        case SEC_DATA:
                {
                /* sprintf(memref_buf,"w_base%d+%d", pgm_segment,sy->uval2.location);  */
                /* sprintf(memref_buf,"w_base%d_%d", pgm_segment, sy->uval2.location); */
                /* char *vname = convert_variable_name(sy); */
                if (sy->offset_mloc == 0) 
                   /* sprintf(memref_buf,"%s.%d", vname, pgm_segment); */
                   sprintf(memref_buf,"w_base%d_%d", pgm_segment, sy->uval2.location); 
                else 
                   /* sprintf(memref_buf,"%s.%d+%d", vname, pgm_segment, sy->uval2.location - sy->offset_mloc); */
                   sprintf(memref_buf,"w_base%d_%d+%d", pgm_segment, sy->offset_mloc, sy->uval2.location - sy->offset_mloc);
                }
                break;
        case SEC_STACK:
        case SEC_ARGS:
                sprintf(memref_buf,"-%d(%%ebp)", sy->uval2.location);
        case SEC_TEMPS:
                sprintf(memref_buf,"-%u(%%esp)", sy->uval2.location);
                break;
        default:
                /* Make sure we have an error at assembly stage */
                sprintf(memref_buf,"ww_base%d+%d #sec:%d", pgm_segment,
                        sy->uval2.location, sy->sec_no);
        }
        return memref_buf;
}

char *memrefd( struct sym *sy ) {
        /* sprintf(memref_buf,"$c_base%d+%d", pgm_segment,sy->descriptor); */
        sprintf(memref_buf,"$c_base%d_%d", pgm_segment, sy->descriptor);
        return memref_buf;
}

void emit_lit( char *s, int len ) {
int bcnt = 0;
        while (len) {
                if (!(bcnt++ % 8)) {
                        if (bcnt > 1)
                                putc('\n',o_src);
                        fprintf(o_src,"\t.byte\t%d",*s++);
                }
                else {
                        fprintf(o_src,",%d",*s++);
                }
                len--;
        }
}

void emit_lit_fill( int c, int len ) {
int bcnt = 0;
        while (len) {
                if (!(bcnt++ % 8)) {
                        if (bcnt > 1)
                                putc('\n',o_src);
                        fprintf(o_src,"\t.byte\t%d",c);
                }
                else {
                        fprintf(o_src,",%d",c);
                }
                len--;
        }
}

void gen_init_value( struct lit *sy, int var_len ) {
int bcnt = 0;
int len, start_len;
char *s;
char pad;

        if (sy->nick) {
           s=sy->nick;
           len=1;
           pad=sy->nick[0];
           }
        else {
           s=sy->name;
           /*len=strlen(s);*/
           len = sy->len;
           pad=' ';
           }
        if (len > var_len)
           len = var_len;
        start_len=len;   
        while (len) {
                if (!(bcnt++ % 8)) {
                        if (bcnt > 1)
                                putc('\n',o_src);
                        fprintf(o_src,"\t.byte\t%d",*s++);
                }
                else {
                        fprintf(o_src,",%d",*s++);
                }
                len--;
        }
        putc('\n',o_src);
        if (start_len < var_len) {
                len = var_len - start_len;
                bcnt=0;
                while (len) {
                        if (!(bcnt++ % 8)) {
                                if (bcnt > 1)
                                        putc('\n',o_src);
                                fprintf(o_src,"\t.byte\t%d",pad);
                        }
                        else {
                                fprintf(o_src,",%d",pad);
                        }
                        len--;
                }
                putc('\n',o_src);
        }
}

void stabs_line ()
{
  static char *last_source_filename = NULL;
  static unsigned int last_source_lineno = 0;
  int new_file = TRUE; /* Is this line on a new file ? */
        
  if (!stabs_on_sw)
    return;

  
  if (last_source_filename){  /* if equals new_file = 0 */
        new_file = strcmp(last_source_filename,source_filename);
  }  

  if ((!new_file) && (source_lineno == last_source_lineno))
    return;


  if (new_file)
    fprintf (o_src, ".stabs\t\"%s\",132,0,0,.LS%d\n",
             source_filename, line_label);
  
  fprintf (o_src, ".stabn\t68,0,%d,.LS%d-Ltext_%s\n",
           source_lineno, line_label, pgm_label);
  fprintf (o_src,".LS%d:\n", line_label++);

  if (new_file) {
      free(last_source_filename);
      last_source_filename = strdup(source_filename);
  }
  last_source_lineno = source_lineno;
}

void stabs_block( int end ) {
/*        I just can't get this working. Let's forget it for some time. */
        if (!end) {
                fprintf(o_src,".stabs\t\".LSB%d:F(0,1)\",36,0,1,.LSB%d\n",
                        block_label,block_label);
                fprintf(o_src,".LSB%d:\n",block_label);
        }
        else {
                fprintf(o_src,".LSE%d:\n",block_label);
                fprintf(o_src,".stabs\t\"\",100,0,0,.LSE%d-.LSB%d\n",
                        block_label,block_label);
        }
}

int gen_main_rtn(void) {
  int r=0;

#if !defined(__WINDOWS__)
  char main_pgm_label[] = "main";
#else
  char main_pgm_label[] = "_main";
#endif

/* 
 The program 'main' options 
 none (0) 
 - Do NOT generate a program 'main' entry point. 
 auto (1) 
 - If a 'STOP RUN' statement is encountered, 
   generate a program 'main' (entry point) and set it as the first 
   COBOL (sub)program to execute.
 any (2, 5) 
 - Generate a program 'main' (entry point) and set a 
   COBOL (sub)program to execute.
   If a 'STOP RUN' statement is encountered, use it, otherwise
   use the first encountered 'PROGRAM-ID' name.
   State five (5) is a temporary indicator that the first 'PROGRAM-ID' name is set.
 specific (3) 
 - Generate a program 'main' (entry point) and set the first 
   COBOL (sub)program to execute as defined in the '-e' CMD line option. 
*/

        if ((main_flag == 3) && (main_entry_flag == FALSE))  {
            yyerror1("Main-program entry point '%s' not found in program sequence", main_entry_buf);
        }
/*
        if ((main_flag == 1) && (main_entry_flag == FALSE))  {
            yyerror1("No 'STOP RUN' statement encountered, no program 'main' entry point defined");
        }
*/
        if ((main_flag == 5) && (main_entry_flag == FALSE))  {
            main_entry_flag = TRUE;
        }
        if (main_entry_flag == TRUE)  {
                strcpy(program_id, main_entry_buf);
                fprintf(o_src,".text\n");
                fprintf(o_src,"\t.align 4\n");

#if !defined(__WINDOWS__)
                fprintf(o_src,".globl %s\n\t.type\t%s,@function\n", main_pgm_label, main_pgm_label);
#else
                fprintf(o_src,".globl %s\n", main_pgm_label);
                fprintf(o_src,"\t.def\t%s;\t.scl\t2;\t.type\t32;\t.endef\n", main_pgm_label);
#endif
                fprintf(o_src,"%s:\n",main_pgm_label);
                fprintf(o_src,"\tpushl\t%%ebp\n\tmovl\t%%esp, %%ebp\n");
                fprintf(o_src,"\tsubl\t$4,%%esp\n\tmovl\t$0,-4(%%ebp)\n");
                fprintf(o_src,"\tmovl\t12(%%ebp),%%eax\n\tpushl\t%%eax\n");
                fprintf(o_src,"\tmovl\t8(%%ebp),%%eax\n\tpushl\t%%eax\n");
                asm_call("tcob_init");
                fprintf(o_src,"\taddl\t$8,%%esp\n");
                asm_call(program_id);
                fprintf(o_src, "\tmovl\t%%eax,%%eax\n\tmovl\t%%eax,-4(%%ebp)\n");
                if (screen_io_enable != 0) {
                   asm_call("tcob_do_scrio_finish");
                }
                asm_call("tcob_stop_run");
                fprintf(o_src,"\tmovl\t-4(%%ebp),%%edx\n\tmovl\t%%edx,%%eax\n");

/*
//	jmp .L1
//	.align 4
//.L1:

//              fprintf(o_src,"\tjmp\t.L1\n\t.align\t4\n.L1:\n");
//                fprintf(o_src,"\tret\n");
*/
                fprintf(o_src,"\tleave\n\tret\n");

                /********** generate .Lfe statement   ************/
                fprintf(o_src,".Lfe1:\n");
#if !defined(__WINDOWS__)
                fprintf(o_src,"\t.size\t%s,.Lfe1-%s\n",main_pgm_label,main_pgm_label);
#endif

        }

        fprintf(o_src,"\n\t.ident\t\"%s: %s\"\n", HTG_PGM_NAME, TCOB_PGM_VERSION);

        return r;

}

int pgm_name_validate(char *sin, char *sout, int idtype) {
  int r=0, i, j, len, alpha_sw=0, pid_trans_len=0;
  char idstr[SYMBUF_SIZE], *sp;

  sp=sin;
  len = strlen(sp);
  idstr[0] = CHR_EOS;

/*  fprintf(stderr, "htcobemt debug 11 : in-name=%s, len=%d;\n", sp, len); */

  /* 
   Type 0: user-defined-word or literal
   Validity check for PROGRAM-ID WORD or LITERAL name  
   '[a-zA-Z0-9]-_$.'
   No '-' at begging or end.
   At least one aphabetic character in string
  */
  if (idtype == 0) {
     /* Name can NOT begin nor end with a DASH ('-'). */
     if (*sp == CHR_DASH )  
           {
        r++;
        yyerror1("Invalid first character '%c' in PROGRAM name", *sp);
     }
     if ( *(sp + len - 1) == CHR_DASH )  
           {
        r++;
        yyerror1("Invalid last character '%c' in PROGRAM name", *(sp + len - 1));
     }
     pid_trans_len = strlen(TCOB_STR_DASH_REDEFINE) - 1;
     for (i=0, j=0; i<len; i++, j++) {
       sp = sin + i;
       if ( isalnum(*sp) || 
            (*sp == CHR_DOLLARD_SIGN) ||
            (*sp == CHR_PERIOD) ||
            (*sp == CHR_DASH) ||
            (*sp == CHR_UNDERSCORE) 
          ) 
          {
          /* Substitute for DASH ('-'). */
          if (*sp == CHR_DASH) { 
             strcat(idstr, TCOB_STR_DASH_REDEFINE);
             j = j + pid_trans_len;
          }
          else {
             idstr[j] = *sp;
             idstr[j+1] = CHR_EOS;
          }
       }
       else {
         r++;
         yyerror1("Invalid character '%c' in PROGRAM name", *sp);
       }
     }
  } /* idtype == 0, user-defined-word or literal */


  /* 
   Type 1: user-defined-word
   Validity check for PROGRAM-ID WORD name  
   '[a-zA-Z0-9]_-' 
   No '-' or '_' at begging or end.
   At least one aphabetic character in string
  */
  if (idtype == 1) {
     /* Max LITERAL Length is MAX_PROGRAMID_WORD */
     if ((len > MAX_PROGRAMID_WORD) || (len < 1)) {
         yyerror1("Invalid length (max %d) '%d' in PROGRAM-ID WORD name", MAX_PROGRAMID_WORD, len);
         r++;
     }
     /* Check for valid characters in WORD name */
     /* First characters can not be a DASH or UNDERSCORE */
     if ((*sp == CHR_DASH) ||
         (*sp == CHR_UNDERSCORE)
         )
       {
       r++;
       yyerror1("Invalid first character '%c' in PROGRAM-ID WORD name", *sp);
     }
     sp = sin + len - 1;
     /* Last characters can not be a DASH or UNDERSCORE */
     if ((*sp == CHR_DASH) ||
         (*sp == CHR_UNDERSCORE)
         )
       {
       r++;
       yyerror1("Invalid last character '%c' in PROGRAM-ID WORD name", *sp);
     }
     pid_trans_len = strlen(TCOB_STR_DASH_REDEFINE) - 1;
     for (i=0, j=0; i<len; i++, j++) {
        sp = sin + i;
        /* At least one aphabetic character in string */
        if (isalpha(*sp))
            alpha_sw = 1;
        if ( ! ( isalnum(*sp) || 
                 (*sp == CHR_DASH) ||
                 (*sp == CHR_UNDERSCORE) 
               ) 
           )
          {
          r++;
          yyerror1("Invalid character '%c' in PROGRAM-ID WORD name", *sp);
        } 
        else {
          /* 
            user-defined-words are case insensitive so
            convert characters to ALL upper, ALL lower,
            or leave it as is (TC extention) depending 
            on compile time option.
          */
          if ( !(*sp == CHR_DASH)) {
             switch (HTG_programid_name_trans_flag)
             {
               case 2:
                 idstr[j] = (char)tolower(*sp);
                 break;
               
               case 1:
                 idstr[j] = (char)toupper(*sp);
                 break;
               
               case 0:
               default:
                 idstr[j] = *sp;
                 break;
             }
             idstr[j+1] = CHR_EOS;
          } 
          else {         
             strcat(idstr, TCOB_STR_DASH_REDEFINE);
             j = j + pid_trans_len;
          } 
        } 
     }       
     if ( alpha_sw == 0) {
          r++;
          yyerror1("At least one character in PROGRAM-ID WORD name must be alphabetic");
     }       

  } /* idtype == 1, WORD name */

  /* 
   Type 2: literal  
   FIXME: Must contain only valid GNU x86 assembler characters
   Validity check for PROGRAM-ID LITERAL name  
   '[a-zA-Z0-9]_$.'
  */
  if (idtype == 2) {
     /* Max LITERAL Length is MAX_PROGRAMID_LITERAL */
     if ((len > MAX_PROGRAMID_LITERAL) || (len < 1)) {
         yyerror1("Invalid length (max %d) '%d' in PROGRAM-ID LITERAL name", MAX_PROGRAMID_LITERAL, len);
         r++;
     /*    return (r++); */
     }
     /* Check for valid characters in LITERAL name */
     if (! ( isalpha(*sp) || 
             (*sp == CHR_UNDERSCORE) 
           ) 
         )
        {
        r++;
        yyerror1("Invalid first character '%c' in PROGRAM-ID LITERAL name", *sp);
     }
     else {
        for (i=1; i<len; i++) {
          sp = sin + i;
          if ( ! ((isalnum(*sp)) || 
                  (*sp == CHR_DOLLARD_SIGN) ||
                  (*sp == CHR_PERIOD) ||
                  (*sp == CHR_UNDERSCORE) 
                 ) 
             )
            {
            r++;
            yyerror1("Invalid character '%c' in PROGRAM-ID LITERAL name", *sp);
          }          
        }       
     }
  
     strncpy(idstr, sin, SYMBUF_SIZE - 1);
     idstr[SYMBUF_SIZE - 1] = CHR_EOS;

  } /* idtype == 2, LITERAL name */

  strcpy(sout, idstr);

  return r;

}

int pgm_header(char *id, int idtype) {
  int r=0;
  char idstr[SYMBUF_SIZE];

#ifdef DEBUG_COMPILER_LEVEL2
  fprintf(stderr, "debug : htcobemt 11 : in-name=%s;\n", id); 
#endif

  idstr[0] = CHR_EOS;
  r = pgm_name_validate(id, idstr, idtype);

#ifdef DEBUG_COMPILER_LEVEL2
  fprintf(stderr, "debug : htcobemt 55 : out-name=%s;\n", idstr); 
#endif

  strcpy(program_id, idstr);
  
/* 
 The program 'main' options 
 none (0) 
 - Do NOT generate a program 'main' entry point. 
 auto (1) 
 - If a 'STOP RUN' statement is encountered, 
   generate a program 'main' (entry point) and set it as the first 
   COBOL (sub)program to execute.
 any (2 5) 
 - Generate a program 'main' (entry point) and set a 
   COBOL (sub)program to execute.
   If a 'STOP RUN' statement is encountered, use it, otherwise
   use the first encountered 'PROGRAM-ID' name.
   State five (5) is a temporary indicator that the first 'PROGRAM-ID' name is set.
 specific (3) 
 - Generate a program 'main' (entry point) and set the first 
   COBOL (sub)program to execute as defined in the '-e' CMD line option. 
*/

#ifdef DEBUG_COMPILER_LEVEL2
  fprintf(stderr, "debug : htcobemt 75 : main_flag=%d, main_entry_flag=%d;\n", main_flag, main_entry_flag); 
#endif

  if ((main_flag == 3) && (main_entry_flag == FALSE)) {
     /* 
       Bug fix:
       The 'strcmp' will cause a seg-fault under certain conditions
      */
     if (strcmp(main_entry_buf, id) == 0) {
         main_entry_buf[0] = '\0';
         strcpy(main_entry_buf, program_id);
#ifdef DEBUG_COMPILER_LEVEL2
         fprintf(stderr, "htcobemt debug 77 : program_id=%s, main_entry_buf=%s;\n", program_id, main_entry_buf); 
#endif
         main_entry_flag = TRUE;
     }
  }
  if ((main_flag == 2) && (main_entry_flag == FALSE))  {
     strcpy(main_entry_buf, program_id);
#ifdef DEBUG_COMPILER_LEVEL2
     fprintf(stderr, "htcobemt debug 87 : program_id=%s, main_entry_buf=%s;\n", program_id, main_entry_buf); 
#endif
/*     main_entry_flag = TRUE; */
     main_flag = 5;
  }

  return r;
}

void data_trail( void ) {
/*        fprintf(o_src,"_DATA        ends\n\n");*/
        if (refmod_slots > 0)
                fprintf(o_src,"rf_base%d:\t.space\t%d\n",
                        pgm_segment,refmod_slots*8);
}

/* using values : 0 = normal, 1 = using , 2 = chaining */
void proc_header( int using ) {
        struct sym *sy,*sy1;
        int i;
        int stabs_type='3';
        char file_filename[SYMBUF_SIZE], *fnamept=NULL;

        /* chg_underline(program_id); */
        if (( using == 1 )/*|| ((using == 0 ) && (has_linkage))*/) { /* Is a routine */
                if (!has_linkage) {
                        hterror(105,TCOB_SEVERITY_ERROR,"Using parameters should be on linkage section");
                }
                module_flag = TRUE;
        }
        if ( module_flag || nested_flag ) {
                pgm_label = program_id;
        }
/*        if ((using == 2 ) && (has_linkage)) {
                hterror(106,TCOB_SEVERITY_ERROR,"A main program cannot have linkage section");
        }        */

        /* Initilize display trace */
        if (HTG_debug_trace_flag == TRUE) 
           trace_display_expand(HASHLEN*10);

        /*clear_symtab();*/
        if (!pgm_segment) {
           /* 
            Remove directory path delimiters from file name
           */
           strncpy(file_filename, input_filename, SYMBUF_SIZE - 1);
           file_filename[SYMBUF_SIZE - 1] = CHR_EOS;
           fnamept = strrchr(file_filename, LT_DIRSEP_CHAR);
           if (fnamept == NULL) {
              fprintf(o_src,"\t.file\t\"%s\"\n", file_filename);             
           }
           else {
              fprintf(o_src,"\t.file\t\"%s\"\n", fnamept + 1);
           }
/*           fprintf(o_src,"\t.file\t\"%s\"\n", input_filename); */
           fprintf(o_src,"\t.version\t\"01.01\"\ntinycobol_compiled.:\n");
/*           fprintf(o_src,"\t.version\t\"%s\"\ntiny_cobol_compiled.:\n", PGM_VERSION); */
/*          fprintf(o_src,"\t.version\t\"01.01\"\ntiny_cobol_compiled.:\n"); */
        }

/*        if (!pgm_segment) */
/*           gen_main_rtn(); */

        fprintf(o_src,".text\n");
        fprintf(o_src,"Ltext_%s:\n", pgm_label);
/*
        if (!pgm_segment) {
           fprintf(o_src,"\t.align 16\n");
        }
*/
        fprintf(o_src,"\t.align 16\n");

#if !defined(__WINDOWS__)
        fprintf(o_src,".globl %s\n\t.type\t%s,@function\n", pgm_label, pgm_label);
        fprintf(o_src,"%s:\n", pgm_label);
#else
        fprintf(o_src,".globl _%s\n", pgm_label);
        fprintf(o_src,"\t.def\t_%s;\t.scl\t2;\t.type\t32;\t.endef\n", pgm_label);
        fprintf(o_src,"_%s:\n",pgm_label);
#endif
        fprintf(o_src,"\tpushl\t%%ebp\n\tmovl\t%%esp, %%ebp\n");
        if (stack_offset & 1) stack_offset++;

        /*  
        Extra 16 bytes holds search all temporary data 
        EOT switch, min, max boundaries and saved ebx.
        Note: extra 4 bytes is to remove memory corruption problem
        found in test20c.cob, probably due to boundary alignment problem. 
        */
        stack_offset = stack_offset + START_STACK_ADJUST; 
        /* add space for linkage section variables that are
                not arguments of the calling program */
        /*if (using)*/
                stack_offset += adjust_linkage_vars( START_STACK_ADJUST );
        

        fprintf(o_src,"\tsubl\t$%u, %%esp\n",stack_offset);
/*        fprintf(o_src,"\tmovl\t%%ebx, -%d(%%ebp)\n",SAVED_EBX_OFFSET); */
        fprintf(o_src,"\tmovl\t%%ebx, -%d(%%ebp)\n",stack_offset - 16);

        fprintf(o_src,".Linit_%s:\n",pgm_label);

/* Begin enter runelement */

        if (decimal_comma) {
/*                fprintf(o_src,"\tcall\tsetDecimalComma\n"); */
/*                fprintf(o_src,"\txorl\t$1,%%eax\n"); */
#if !defined(__WINDOWS__)
/*                fprintf(o_src,"\tmovl\t%%eax,bDecimalComma\n"); */
           fprintf(o_src,"\tcall\tsetDecimalComma\n");
#else        
/*                fprintf(o_src,"\tmovl\t%%eax,_bDecimalComma\n"); */
           fprintf(o_src,"\tcall\t_setDecimalComma\n");
#endif        

        }
        if (currency_symbol != CHR_DOLLARD_SIGN) {
#if !defined(__WINDOWS__)
           fprintf(o_src,"\tmovb\t$%d,cCurrencySymbol\n", currency_symbol);
#else        
           fprintf(o_src,"\tmovb\t$%d,_cCurrencySymbol\n", currency_symbol);
#endif        
        }
        /*
         * If defined SCREEN STATUS, inform the reference in the field on the
         *  library 
         */ 
        if (screen_status_field!=NULL) {
                if (!(screen_status_field->defined)) {
                        yyerror("SCREEN STATUS field '%s' not defined",
                                         screen_status_field->name);        
                }
                if (screen_status_field->len < 4) {
                        yyerror("SCREEN STATUS field '%s' must have a size of 4",
                                         screen_status_field->name);        
                }
                loadloc_to_eax(screen_status_field);
                #if !defined(__WINDOWS__)
                   fprintf(o_src,"\tmovl\t%%eax, screen_status\n");
                #else        
                   fprintf(o_src,"\tmovl\t%%eax,_screen_status\n");
                #endif        
        }
        /*
         * If defined CURSOR, inform the reference in the field on the
         *  library 
         */ 
        if (cursor_field!=NULL) {
                if (!(cursor_field->defined)) {
                        yyerror("CURSOR field '%s' not defined",
                                         cursor_field->name);        
                }
                if (cursor_field->len < 6) {
                        yyerror("CURSOR field '%s' must have a size of 6",
                                         cursor_field->name);        
                }
                loadloc_to_eax(cursor_field);
                #if !defined(__WINDOWS__)
                   fprintf(o_src,"\tmovl\t%%eax, screen_cursor\n");
                #else        
                   fprintf(o_src,"\tmovl\t%%eax,_screen_cursor\n");
                #endif        
        }
/*
        // This should be generated after initialization 
        if ( using == 2 ) { // PROCEDURE DIVISION CHAINING 
            // get chaining values 
            struct sym *cp;
            struct parm_list *list,*tmp;

            push_immed(0);
            for (list=chaining_list;list!=NULL;) {
                    cp=(struct sym *)list->var;
                    gen_loadvar( cp );
                    tmp=list;
                    list=list->next;
                    free(tmp);
                    tmp=NULL;
            }                
            asm_call("tcob_chaining");
            chaining_list=NULL;
        }
*/
        /* 
         * we save the name of the program as a literal
         * for identify the run unit
         */
        program_name_literal = install_lit(program_id,strlen(program_id),0);
        save_literal(program_name_literal,DTYPE_DISPLAY);
        /* 
         * Indicate the runtime that we enter a run element
         * to save / restore runtime values
         */
        gen_enter_runelement(TCB_RUN_ELEMENT_ENTER);

        fprintf(o_src,"\tmovl\t$s_base%d+0, %%eax\n", pgm_segment);
        if (!initial_flag) {
           fprintf(o_src,"\tcmpl\t$0, 0(%%eax)\n");
           fprintf(o_src,"\tjne\t.Linite_%s\n",pgm_label);
           fprintf(o_src,"\tmovl\t$1, 0(%%eax)\n");
        }
        
        if (HTG_libcob) RTL_CALL("module_init");
        /********** initialize all VALUES of fields **********/

        do_init_val(); 

        if ( using == 2 ) { /* PROCEDURE DIVISION CHAINING  */
           /* get chaining values  */
           struct sym *cp;
           struct parm_list *list,*tmp;

           push_immed(0);
           for (list=chaining_list;list!=NULL;) {
                   cp=(struct sym *)list->var;
                   gen_loadvar( cp );
                   tmp=list;
                   list=list->next;
                   free(tmp);
                   tmp=NULL;
           }                
           asm_call("tcob_chaining");
           chaining_list=NULL;
        }
        

        if (switches_list != NULL) gen_get_switches();

        /********** dump stabs for local variables **********/
        for (i=0;i<HASHLEN;i++)
          for (sy1=vartab[i];sy1!=NULL;sy1=sy1->next)
                for (sy=sy1;sy!=NULL;sy=sy->clone)
                  if (sy->type!='F' && sy->type!='8' && 
                      sy->type!='K' && sy->type!='J' ) {

                                      if (stabs_on_sw && sy->sec_no == SEC_STACK) {

                                           if (sy->type == DTYPE_BININT) {
                                                           switch (symlen(sy)) {
                                                        case 1: stabs_type='6'; break;
                                                        case 2: stabs_type='5'; break;
                                                        case 4: stabs_type='3'; break;
                                                        case 8: stabs_type='7'; break;
                                                        }
                                                   fprintf(o_src,".stabs\t\"%s:%c\",128,0,0,-%d\n",
                                                        sy->name,stabs_type,sy->uval2.location);
                                                }
                                           else if (sy->type == DTYPE_PACKED)
                                                   fprintf(o_src,".stabs\t\"%s:(1,%d)=ar3;1;%d;4\",128,0,0,-%d\n",
                                                        sy->name,sy->len,sy->len,sy->uval2.location);
                                           else
                                                   fprintf(o_src,".stabs\t\"%s:(1,%d)=ar3;1;%d;2\",128,0,0,-%d\n",
                                                   sy->name,sy->len,sy->len,sy->uval2.location);
                                        }
                  }

        fprintf(o_src,".Linite_%s:\n",pgm_label);
        if (stabs_on_sw) {
            fprintf(o_src,".stabn\t192,0,0,.LS%d-Ltext_%s\n",
                        line_label,pgm_label);
            fprintf(o_src,".stabn\t224,0,0,.LSend_%s-Ltext_%s\n",
                        pgm_label,pgm_label);
        
        }
        
#if !defined(__WINDOWS__)
        fprintf(o_src,"\tleal\t%s, %%eax\n",pgm_label);
#else        
        fprintf(o_src,"\tleal\t_%s, %%eax\n",pgm_label);
#endif        
        fprintf(o_src,"\tpushl\t%%eax\n");
        fprintf(o_src,"\tleal\t.Lend_pgm_%s, %%eax\n",pgm_label);
        fprintf(o_src,"\tpushl\t%%eax\n");
        stack_offset += 8;                /* length of the 2 pushes above */


        at_procedure++;
        stabs_started++;
        stabs_line();
}

void dump_descriptor_lit(struct lit *v, int len, int tmplen) {

        unsigned int loc;
        
        fprintf(o_src,"\t.long\t%d\n",
                (v->decimals) ? len-1 : len);
        if (HTG_libcob) {
                /* fprintf(o_src,"\t.long\tc_base%d+%d\n", */
                fprintf(o_src,"\t.long\tc_base%d_%d\n",
                        pgm_segment, v->location);  /* data pointer */
                /* fprintf(o_src,"\t.long\tc_base%d+%d\n", */
                fprintf(o_src,"\t.long\tc_base%d_%d\n",
                        pgm_segment, v->descriptor+CFLD_DESC_SIZE0);  /* desc pointer */
                fprintf(o_src,"\t.byte\t'%c',%d,%d,%d\n",
                        v->type,v->decimals,0,v->all);
                /* fprintf(o_src,"\t.long\tc_base%d+%d\n", */
                fprintf(o_src,"\t.long\tc_base%d_%d\n",
                        pgm_segment,v->descriptor+CFLD_DESC_SIZE1);  /* picture picture */
                }
        else {
                fprintf(o_src,"\t.byte\t'%c',%d,%d,%d\n",
                        v->type,v->decimals,0,v->all);
                /* pointer to the picture */
                loc = v->location + len + 1 + FLD_DESC_SIZE1;
/*
#ifdef DEBUG_COMPILER
                // fprintf(o_src,"\t.long\tc_base%d+%d\t# c_base%d+%x(hex)\n", 
                //        pgm_segment, v->descriptor+FLD_DESC_SIZE1,
                //        pgm_segment, v->descriptor+FLD_DESC_SIZE1); 
#else
                // fprintf(o_src,"\t.long\tc_base%d+%d\n", 
                // fprintf(o_src,"\t.long\tc_base%d_%d\n",
                //        pgm_segment, v->descriptor+FLD_DESC_SIZE1);  
                //fprintf(o_src,"\t.long\tc_base%d_%d\n",
                //        pgm_segment, loc);  
#endif
*/
                fprintf(o_src,"\t.long\tc_base%d_%d\n", pgm_segment, loc);  
        }

                fprintf(o_src,"c_base%d_%d:\n", pgm_segment, loc);
                if (v->decimals) {
                        if (v->name[v->len-1] > '9') /* signed too? */
                                fprintf(o_src,"\t.byte\t'S',1,'9',%d,'V',1,'9',%d,0\n",
                                        len-v->decimals-1, v->decimals);
                        else
                                fprintf(o_src,"\t.byte\t'9',%d,'V',1,'9',%d,0\n",
                                        len-v->decimals-1, v->decimals);
                } else if ((v->type == DTYPE_DISPLAY) && (v->name[v->len-1] > '9')) {
                        /* this is a signed literal, so reflect into its picture too */
                        fprintf(o_src,"\t.byte\t'S',1,'9',%d,0\n",len);
                }
                else {
                        tmplen = len;
                        while (tmplen > 255) {
                                fprintf(o_src,"\t.byte\t\'%c\',%d\n",
                                        v->type,255);
                                tmplen -= 255;
                        }
                        fprintf(o_src,"\t.byte\t\'%c\',%d,0\n",
                                v->type,tmplen);

                }
}
        
void dump_descriptor_fld(struct sym *sy) {
        char flag;

#ifdef DEBUG_COMPILER
        fprintf(o_src,"# Field: %s, Mem loc: %s, Desc: c_base%d+%d\n",
                sy->name, memref(sy), pgm_segment, sy->descriptor );
        fprintf(o_src,"# Field: New Mem loc: w_base%d_%d, New Desc: c_base%d_%d\n",
                pgm_segment, sy->uval2.location,
                pgm_segment, sy->descriptor);
#endif
                
        fprintf(o_src,"c_base%d_%d:\n", pgm_segment, sy->descriptor);
        if (sy->uval6.redefines != NULL)
                sy->uval2.location = sy->uval6.redefines->uval2.location;
        fprintf(o_src,"\t.long\t%d\n",sy->len);

        if (HTG_libcob) {
                /* fprintf(o_src,"\t.long\tw_base%d+%d\n", */
                /* char *vname = convert_variable_name(sy);*/
                /* fprintf(o_src,"\t.long\t%s.%d\n", vname, pgm_segment);*/
                fprintf(o_src,"\t.long\tw_base%d_%d\n",
                          pgm_segment, sy->uval2.location);  /* data pointer */
                /* fprintf(o_src,"\t.long\tc_base%d+%d\n", */
                fprintf(o_src,"\t.long\tc_base%d_%d\n",
                        pgm_segment,sy->descriptor+CFLD_DESC_SIZE0);  /* desc pointer */
                flag = sy->flags.just_r ? 2 : 0;
                flag |= (sy->flags.separate_sign ? 4 : 0);
                flag |= (sy->flags.leading_sign ? 8 : 0);
                flag |= (sy->flags.blank ? 16 : 0);
                fprintf(o_src,"\t.byte\t'%c',%d,%d,%d\n",
                        sy->type,sy->uval1.decimals,0,flag);
                }
        else {
                flag = sy->flags.just_r ? 2 : 0;
                flag |= (sy->flags.separate_sign ? 4 : 0);
                flag |= (sy->flags.leading_sign ? 8 : 0);
                flag |= (sy->flags.blank ? 16 : 0);
                fprintf(o_src,"\t.byte\t'%c',%d,%d,%d\n",
                        sy->type,sy->uval1.decimals,sy->pscale,flag);
                }
                //if ((sy->type != DTYPE_GROUP) && (sy->type != 'R')) {
                if (sy->type!=DTYPE_GROUP) {
/* 
#ifdef DEBUG_COMPILER
                        // fprintf(o_src,"\t.long\tc_base%d+%d\t# c_base%d+%x(hex)\n", 
                        //fprintf(o_src,"\t.long\tc_base%d_%d\t# c_base%d_%x(hex)\n",
                        //        pgm_segment, sy->uval5.pic, pgm_segment, sy->uval5.pic);
#else
                        // fprintf(o_src,"\t.long\tc_base%d+%d\n",pgm_segment,sy->uval5.pic); 
                        //fprintf(o_src,"\t.long\tc_base%d_%d\n",pgm_segment,sy->uval5.pic);
#endif
*/
                        fprintf(o_src,"\t.long\tc_base%d_%d\n",pgm_segment, sy->uval5.pic);

                        fprintf(o_src,"c_base%d_%d:\n", pgm_segment, sy->uval5.pic);

                        if (sy->stype == 'X') { /* for COMP-X generate a generic
                                                picture */
                           fprintf(o_src,"\t.byte\t'9',%d\n",sym_min_pic(sy));
                        }
                        else {
                                unsigned int i;
                                for (i=0;i<strlen(sy->uval9.picstr);i+=2)
                                        fprintf(o_src,"\t.byte\t\'%c\',%d\n",
                    *(sy->uval9.picstr+i),*((unsigned char *)sy->uval9.picstr+i+1));
                            }
                        fprintf(o_src,"\t.byte\t0\n");
                }
}

/* 
 procedure division:
 using/chaining option : using (0 = none, 1 = using, 2 = chaining)
 returning variable : syr (NULL = none)
*/
void proc_trail(int using,  struct sym *syret) {
        struct lit *v;
        struct list *list;
        struct sym *sy;
        /*char s[9];*/
/*
#if !defined(__WINDOWS__)
        char *pgm_label = "main";
#else
        char *pgm_label = "_main";
#endif
*/
#if 0
        if (( using == 1 )/* || ((using == 0 ) && (has_linkage))*/) { /* Is a routine */
                pgm_label = program_id;
        }
#endif
        if ( module_flag || nested_flag ) {
                pgm_label = program_id;
        }
        fprintf(o_src,".Lend_pgm_%s:\n",pgm_label);

/*
        The 'stop run' statement requires a RTL clean-up 
        The code can be generated in the program 'main' (entry point),
        or from within the COBOL program itself.
        This option is set in the resource file using the following options:
        STOPRUN_PROC_EXTERNAL - external, usually in the program 'main'
        STOPRUN_PROC_INTERNAL - within the COBOL program
       
*/ 
        if (HTG_stoprun_proc_flag == 1) {

          /* Screen section io cleanup (curses library). */
          if (screen_io_enable != 0) {
             asm_call("tcob_do_scrio_finish");
          }        

          asm_call("tcob_stop_run");

        }

/*      
        Note:
        The variable RETURN-CODE is a extention to the 
        standard, since ANSI COBOL 85 does not support it.

        Program (function) return code is stored in register %eax

        If the PROCEDURE DIVISION ... RETURNING identifier-n clause is used,
        then identifier-n is used as return value.
        Else RETURN-CODE is used as return value (default). 

        If the CALL ... RETURNING identifier-n clause is used,
        then the return value is moved to identifier-n.
        Else the return value is moved to RETURN-CODE.  

        When niether a 'PROCEDURE DIVISION/CALL ... RETURNING' clauses are used,
        then the value of the sub-program RETURN-CODE is moved to RETURN-CODE
        in the main program.
        This can cause problems with C 'void' type function calls, as the contents
        of register %eax are used as a return value.
*/ 
/*
        // PROCEDURE DIVISION ... RETURNING identifier-n  
        // Since identifier-n is not defined, return RETURN-CODE. 
*/
        if (syret == NULL) {
           if ((sy = lookup(SVAR_RETURN_CODE, SYTB_VAR)) == NULL) {
#ifdef DEBUG_COMPILER
              fprintf(o_src, "# Since 'RETURN-CODE' is not defined, set the return value to 0 in register eax\n");
#endif
              fprintf(o_src,"\tmovl\t$0, %%eax\n");
           }
           else {
#ifdef DEBUG_COMPILER
              fprintf(o_src, "# Use 'RETURN-CODE' to set the return value in register eax\n");
#endif
              if (sy->sec_no == SEC_STACK) {
                 fprintf(o_src,"\tleal\t-%d(%%ebp), %%edx\n",sy->uval2.location);
              }
              else {
                 /* fprintf(o_src,"\tmovl\t$w_base+%d, %%edx\n",sy->uval2.location); */
                 /* fprintf(o_src,"\tleal\tw_base%d+%d, %%edx\n", pgm_segment,sy->uval2.location); */
                 fprintf(o_src,"\tleal\tw_base%d_%d, %%edx\n", pgm_segment, sy->uval2.location);
                 /* char *vname = convert_variable_name(sy); */
                 /* fprintf(o_src,"\tleal\t%s.%d, %%edx\n", vname, pgm_segment); */
              }
              fprintf(o_src,"\tmovl\t(%%edx), %%eax\n");
           }
        }
        else {
        /* Identifier-n is defined, return value of Identifier-n.  */
           sy = syret;
           if (sy->sec_no == SEC_STACK) {
              fprintf(o_src,"\tleal\t-%d(%%ebp), %%edx\n",sy->uval2.location);
              fprintf(o_src,"\tmovl\t(%%edx), %%eax\n");
           }
           else {
              if (sy->linkage_flg == 0) {
                 /* fprintf(o_src,"\tleal\tw_base%d+%d, %%edx\n", pgm_segment,sy->uval2.location);  */
                 fprintf(o_src,"\tleal\tw_base%d_%d, %%edx\n", pgm_segment, sy->uval2.location);
                 /* char *vname = convert_variable_name(sy); */
                 /* fprintf(o_src,"\tleal\t%s.%d, %%edx\n", vname, pgm_segment); */
                 fprintf(o_src,"\tmovl\t(%%edx), %%eax\n");
              }
              else {
/*
                 //  FIXME or find a better hack !!
                 //  Memory for LINKAGE SECTION identifiers is defined on the STACK.
                 //  However it can contain pointers to the data, or the actual data. 
                 //  For example, when a 'PROCEDURE DIVISION ... RETURNING identifier-n' 
                 //  clause is used, identifier-n is defined in the LINKAGE SECTION.
                 //  The contents of identifier-n is defined on the STACK.
                 //  For example, when a 'PROCEDURE DIVISION USING ... identifier-n ...' 
                 //  clause is used, identifier-n is defined in the LINKAGE SECTION.
                 //  A pointer to the contents of identifier-n is defined on the STACK,
                 //  as defined by the calling program.
                 //  When the variable 'linkage_flg' contains a positive value, it is assummed
                 //  to be defined by the calling program, and contains a pointer to the data.
                 //  When the 'linkage_flg' variable contains a negative value, it is assummed
                 //  to be defined within the program, and contains the actual data.
                 //  
*/
#ifdef DEBUG_COMPILER
                 fprintf(o_src,"# Use '%s' to set the return value stored in eax, linkage_flg=%d\n", sy->name, sy->linkage_flg);
#endif
                 if (sy->linkage_flg > 0) {
                    fprintf(o_src,"\tmovl\t%d(%%ebp), %%edx\n", sy->linkage_flg);
                    fprintf(o_src,"\tmovl\t(%%edx), %%eax\n");
                 }
                 else {
                    fprintf(o_src,"\tmovl\t%%ebp, %%edx\n");
                    fprintf(o_src,"\taddl\t$%d, %%edx\n", sy->linkage_flg);
                    fprintf(o_src,"\tmovl\t(%%edx), %%eax\n");
                 }
              }

           }
        }

        /* See 'stop run' notes above */ 
        if (HTG_stoprun_proc_flag == 1) {
           fprintf(o_src,"\tjmp\t.LSend_%s\n",pgm_label);
           fprintf(o_src,"\t.align 16\n");
           fprintf(o_src,".LSend_%s:\n",pgm_label);

           fprintf(o_src,"\tpushl\t%%eax\n");
           asm_call("exit");
           fprintf(o_src,"\taddl\t$4,%%esp\n");
        }

/*        fprintf(o_src,"\tmovl\t-%d(%%ebp), %%ebx\n",SAVED_EBX_OFFSET); */
/*        fprintf(o_src,"\tmovl\t-%d(%%ebp), %%ebx\n",stack_offset -8 - 16); */
        fprintf(o_src,"\tmovl\t-%d(%%ebp), %%ebx\n",stack_offset - 24);
        fprintf(o_src,"\tmov\t%%ebp,%%esp\n");
        fprintf(o_src,"\tpopl\t%%ebp\n");
        fprintf(o_src,"\tret\n");

        /******* screen section field processing *********/
          /* dump_scr_proc();         */
        
        /********** generate .Lfe statement   ************/
        fprintf(o_src,".Lfe1_%s:\n",pgm_label);
        #if !defined(__WINDOWS__)
        fprintf(o_src,"\t.size\t%s,.Lfe1_%s-%s\n",pgm_label,pgm_label,pgm_label);
        #endif


        /********** generate data for literals & fields ************/
        /* Generate then clear display and ready trace data */
        if (HTG_debug_trace_flag == TRUE) {
           dump_trace_display();
           trace_display_clear();
        }
        fprintf(o_src,".data\n\t.align 4\n");
        /* fprintf(o_src,".data\n");*/
        /* generate static working storage */
        dump_working();
        
        /* FIXME: 
         This should be READ-ONLY data, but for some unknown reason, does not work properly.
        */
        /* predefined data for special literals */
        /* fprintf(o_src,"\t.section\t.rodata\n\t.align 4\n"); */
        /* fprintf(o_src,"\t.section\t.rodata\n"); */
        fprintf(o_src,"\t.align 4\nv_base%d:\nc_base%d:\n", pgm_segment, pgm_segment); 
        /* fprintf(o_src,"v_base%d:\n\t.section\t.rodata\n\t.align 4\nc_base%d:\n", pgm_segment, pgm_segment); */ 
        /**************** generate data for fields *****************/
        for (list=fields_list;list!=NULL;list=list->next) {
                
                        
                if ( ((struct sym *)list->var)->type=='F' ) { /* sort files */
                        char sl[21];        /* para inverter a lista */
                        char *s;
                        s=sl;
                        *s++=0;        /* final da lista invertida */
                        sy=(struct sym *)list->var;
        #ifdef DEBUG_COMPILER
                        fprintf(o_src,"# File: %s, Data loc: v_base+%d, Desc: c_base%d+%d\n",
                                sy->name,sy->uval2.location,pgm_segment,sy->descriptor );
                        fprintf(o_src,"# File: New Data loc: v_base%d_%d, New Desc: c_base%d_%d\n",
                                pgm_segment, sy->uval2.location, pgm_segment, sy->descriptor);
        #endif
                        fprintf(o_src,"c_base%d_%d:\n", pgm_segment, sy->descriptor);
                        
                        /* sy=(struct sym *)sy->sort_data; */
                        sy=sy->uval4.sort_data;
                        while (sy!=NULL) {
                                *s++ = (unsigned char)sy->uval3.direction;
                                *s++ = (unsigned char)sy->len;
                                sy = sy->uval4.sort_data;
                        }
                        s--;
                        while (*s) {
                                fprintf(o_src,"\t.byte\t%u,%u\n",*(s-1),*s);
                                s -= 2;
                        }
                        fprintf(o_src,"\t.byte\t0\n");
                } /* end sort file */
                else if (((struct sym *)list->var)->litflag) { /***** it is a literal *****/
                int len,tmplen;
                v=(struct lit *)list->var;
                /*len = v->nick ? 1 : strlen(v->name);*/
                len = v->nick ? 1 : v->len;
#ifdef DEBUG_COMPILER
                fprintf(o_src,"# Literal: %s, Data loc: c_base%d+%d, Desc: c_base%d+%d\n",
                         sch_convert(v->name), pgm_segment, v->location, 
                         pgm_segment, v->descriptor);
                fprintf(o_src,"# Literal: New Data loc: c_base%d_%d, New Desc: c_base%d_%d\n",
                         pgm_segment, v->location, 
                         pgm_segment, v->descriptor);
#endif
                fprintf(o_src,"c_base%d_%d:\n", pgm_segment, v->location);
                if (!v->decimals)
                        {       /* print literal string, w/special chars */
                                int i;
                                char *s;
                                if (v->nick) {
                                        s = v->nick;
                                        i = 1;
                                }
                                else {
                                        s = v->name;
                                        i = v->len;
                                }
                                emit_lit(s,i);
                                if (i) {
                                        fprintf(o_src,",0\n");
                                }
                                else { /* null string? */
                                        fprintf(o_src,"\t.byte\t0\n");
                                }
                        }
                else {
                        char *s;
                        s=v->name;
                        fprintf(o_src,"\t.byte\t");
                        while (*s &&(*s!=decimal_char()))
                                fprintf(o_src,"%d,",*s++);
                                s++;
                        while (*s)
                                fprintf(o_src,"%d,",*s++);
                        fprintf(o_src,"0\n");
                }
                fprintf(o_src,"c_base%d_%d:\n", pgm_segment, v->descriptor);
                dump_descriptor_lit(v, len, tmplen);
        } /* end literals */
        else /*if ( ((struct sym *)list->var)->type!='D' )*/ {
        /********* it is a normal field ****************/
                sy=(struct sym *)list->var;
                dump_descriptor_fld(sy);
        } /* end normal field */
        } /* end for */

/* generate data for files */
        dump_fdesc();
        /* dump_scr_data(); */
        data_trail();
/*         fprintf(o_src,"\n\t.ident\t\"TinyCOBOL: %s\"\n", PGM_VERSION); */
/*         fprintf(o_src,"\n\t.ident\t\"%s: %s\"\n", HTG_PGM_NAME, TCOB_PGM_VERSION); */
        dump_symbols();
} /* proc_trail */


/* generate display and ready trace data */
void dump_trace_display() 
{
  int i;
/*
//  struct _dtracedata {
//        unsigned int size;
//        char **name; 
// };
*/

  fprintf(o_src,".section\t.rodata\n");
/*
//.LC_INITIALISATION_0:
//.string "program return code: %d\n"
*/
  fprintf(o_src,".LC_DTENTER_%s:\n\t.string \"%%s ENTER\\n\"\n", pgm_label);
  fprintf(o_src,".LC_DTEXIT_%s:\n\t.string \"%%s EXIT\\n\"\n", pgm_label);
  
  for (i=0; i<dtracedata.size; i++) {
      if (dtracedata.name[i] == NULL) 
         break;
      fprintf(o_src,".LC%04d_%s:\n\t.string \"%s\"\n", i, pgm_label, dtracedata.name[i]);
  }

}

/* 
** dump all static working storage
*/
void dump_working() {

        struct sym *v, *sy, *fv, *fvr;
        struct list *list, *flist /*,*visited*/;
        int fld_len, fpos;
        int stabs_type='3';
        short cur_sec_no=SEC_WORKING;
        
        /* fprintf(o_src,".data\n\t.align 4\n"); */
        /* fprintf(o_src,"w_base:\t.long\t0\n"); */
        fprintf(o_src,"w_base%d:\n", pgm_segment);

        /* HACK: Setup for file space insert - common to all file records */
        flist = files_list;
        fpos = 0; 
        if (flist != NULL) {
           fv=(struct sym *)flist->var;
           if (fv != NULL) {
              fvr = fv->uval6.recordsym;
              if (fvr != NULL) {
                 fpos = fvr->uval2.location;
#ifdef DEBUG_COMPILER
                fprintf(o_src,"# htcobemt: dump_working xyz: Field %s, Data Loc: %d == %d\n",
                                fv->name, fpos, fvr->uval2.location);
#endif
              }
           }
        }

        /* HACK: Generate memory allocation for files and WS identifiers */
        for (list = fields_list; list != NULL; list = list->next) {
                v=(struct sym *)list->var;
                sy=v;
                if (v->litflag) continue;
#ifdef DEBUG_COMPILER_LEVEL2
                fprintf(o_src, "# htcobemt: dump_working 1: Name: %s, FldLength: %d(x %d), Type: %c, sec_no: %d, linkage_flg: %d\n", 
                                v->name, fld_len, v->times, v->type, v->sec_no, v->linkage_flg); 
#endif
                if (v->sec_no == SEC_STACK) continue;
                if (v->type== 'F' || v->type=='R') continue;
/*                fld_len = set_field_length(v,1); */
                fld_len = set_field_length(v,1) * v->times;
#ifdef DEBUG_COMPILER_LEVEL2
                fprintf(o_src, "# htcobemt: dump_working 2: Name: %s, FldLength: %d(x %d), Type: %c, sec_no: %d, linkage_flg: %d\n", 
                                v->name, fld_len, v->times, v->type, v->sec_no, v->linkage_flg); 
#endif
                if (v->linkage_flg != 0) continue; 
                if (v->sec_no != cur_sec_no && v->sec_no >= SEC_FIRST_NAMED) {  /* switch of sections */
                   if (v->sec_no >= SEC_FIRST_NAMED) {
                      fprintf(o_src,"\t.comm\t%s,%d\n",sec_name(v->sec_no), fld_len);
/*                         Fix for GCC 3.x 
                           fprintf(o_src,"\t.comm\t%s,%d,4\n",sec_name(v->sec_no), fld_len);
*/
                   }
                   else {
                      fprintf(o_src,".text\n");
                   }        
                   cur_sec_no = v->sec_no;
                }
#ifdef DEBUG_COMPILER
                fprintf(o_src,"# Field %s, Data Loc: %d(hex: %x), length: %d, type: %c\n",
                                v->name,v->uval2.location,v->uval2.location,v->len,v->type);
#endif
                if (stabs_on_sw) {
                   if (sy->type == DTYPE_BININT) {
                       switch (symlen(sy)) 
                       {
                        case 1: stabs_type='6'; break;
                        case 2: stabs_type='5'; break;
                        case 4: stabs_type='3'; break;
                        case 8: stabs_type='7'; break;
                       }
                       fprintf(o_src,".stabs\t\"%s:V%c\",38,0,0,w_base%d+%d\n",
                                      sy->name,stabs_type,pgm_segment,sy->uval2.location);
                   }
                   else 
                       if (sy->type == DTYPE_PACKED)
                           fprintf(o_src, ".stabs\t\"%s:V(1,%d)=ar3;1;%d;4\",38,0,0,w_base%d+%d\n",
                                          sy->name,sy->len,sy->len,pgm_segment,0);
/*                                        sy->name,sy->len,sy->len,sy->uval2.location); */
                       else
                           fprintf(o_src, ".stabs\t\"%s:V(1,%d)=ar3;1;%d;2\",38,0,0,w_base%d+%d\n",
                                           sy->name,sy->len,sy->len,pgm_segment,sy->uval2.location);
                }
                
                if (v->parent) continue;
/*                if ((v->ix_desc  != NULL) && (v->uval6.redefines != NULL)) continue; */
                if (v->level == 66) continue;
                
                /* External identifiers */
                if (v->flags.external == 1) continue;

                /* Redifined identifiers */
                if (v->flags.in_redefinition == 1) continue;

                /* Fix for programs with more than one file */
                if (v->flags.isfilerecord != 1) {
#ifdef DEBUG_COMPILER_LEVEL2
                   fprintf(o_src,"# htcobemt: dump_working 3: Field %s, Data Loc: %d(hex: %x), length: %d, type: %c\n",
                                v->name,v->uval2.location,v->uval2.location,v->len,v->type);
#endif
                   /* don't alloc dummy (zero storage) symbols */
                   if (fld_len) { 
#ifdef DEBUG_COMPILER_LEVEL2
                       fprintf(o_src,"# w_base%d_%d: debug 1 loc=%d\n", pgm_segment, v->uval2.location, v->uval2.location);
#endif
                       fprintf(o_src,"w_base%d_%d:\n", pgm_segment, v->uval2.location);
                       def_field_storage(v, fld_len);
                       /* fprintf(o_src,"\t.space\t%d\n",fld_len); */
                   } 
                   else {
                       /* empty fields on screen are allowed to set line/column or color
                          or erase line or screen */
                       if (v->type != DTYPE_ACCEPT_DISPLAY) 
                          yyerror("Invalid picture in %s,type %c,%d,%d",v->name,v->type,fld_len,symlen(v));
                   }

                }

#ifdef DEBUG_COMPILER_LEVEL2
                fprintf(o_src,"# htcobemt: dump_working xxx: Field %s, Data Loc: %d == %d\n",
                                v->name, fpos, v->uval2.location+fld_len);
#endif
                /* HACK: Insert file space - common to all file records */
                if (flist != NULL) {
                   if (fpos == v->uval2.location + fld_len) {
#ifdef DEBUG_COMPILER_LEVEL2
                       fprintf(o_src,"# w_base%d_%d: debug 2 loc=%d\n", pgm_segment, v->uval2.location+fld_len, v->uval2.location+fld_len);
#endif
                       fprintf(o_src,"w_base%d_%d:\n", pgm_segment, v->uval2.location+fld_len);
                       def_field_storage(fv, fv->len);
                       flist = flist->next;
                       if (flist != NULL) {
                          fv=(struct sym *)flist->var;
                          if (fv != NULL) {
                             fvr = fv->uval6.recordsym;
                             if (fvr != NULL) 
                                fpos = fvr->uval2.location;
                          }
                       }
                   }
                }

#if 0
                if (v->uval7.son) continue;                /* no space reserved for groups */
                  if (v->value != NULL) {
                        gen_init_value(v->value,fld_len);
                        }
                else        
                        fprintf(o_src,"\t.ds\t%d\n",fld_len);
#endif
        }
        /* output tmpvar storage */
        if (tmpvar_max > 0) {
           fprintf(o_src,"tv_base%d:\n",pgm_segment);
#ifdef DEBUG_COMPILER_LEVEL2
           fprintf(o_src,"# htcobemt: dump_working 4: Temp space allocation size %d\n", tmpvar_max);
#endif
           fprintf(o_src,"\t.space\t%d\n",tmpvar_max);
        }
}

/* 
** Use push_eax and push_ebx to generate code for
** passing parameters to the runtime functions.
** Use asm_call to call the runtime and
** automatically clean the stack.
*/
void push_immed( int i ) {
        stackframe_cnt += 4;
        fprintf(o_src,"\tpushl\t$%d\n",i);
}
void push_eax() {
        stackframe_cnt += 4;
        fprintf(o_src,"\tpushl\t%%eax\n");
}

void push_edx() {
        stackframe_cnt += 4;
        fprintf(o_src,"\tpushl\t%%edx\n");
}

void pop_eax() {
        stackframe_cnt -= 4;
        fprintf(o_src,"\tpopl\t%%eax\n");
}

void push_ebx() {
        stackframe_cnt += 4;
        fprintf(o_src,"\tpushl\t%%ebx\n");
}

void push_at_ebx(struct sym *sy) {
#ifdef DEBUG_COMPILER
        fprintf(o_src, "#   push_at_ebx:\n");
#endif
        stackframe_cnt += 4;
        if (sy->type == DTYPE_BININT) { 
                if (symlen(sy)==8) {
                        fprintf(o_src,"\tmovl\t4(%%ebx), %%edx\n");
                        fprintf(o_src,"\tmovl\t0(%%ebx), %%eax\n");
                        fprintf(o_src,"\tpushl\t%%edx\n");
                        stackframe_cnt += 4;
                        }
                else if (symlen(sy)>=4)
                        fprintf(o_src,"\tmovl\t0(%%ebx), %%eax\n");
                else
                        fprintf(o_src,"\tmovs%cl\t0(%%ebx), %%eax\n",varsize_ch(sy));
        }
        else
                fprintf(o_src,"\tmovl\t0(%%ebx), %%eax\n");
        fprintf(o_src,"\tpushl\t%%eax\n");
}

void push_at_eax(struct sym *sy) {
#ifdef DEBUG_COMPILER
        fprintf(o_src, "#   push_at_eax:\n");
#endif
        stackframe_cnt += 4;
        if (sy->type == DTYPE_BININT || sy->type == DTYPE_FLOAT) { 
                if (symlen(sy)==8) {
                        fprintf(o_src,"\tmovl\t4(%%eax), %%edx\n");
                        fprintf(o_src,"\tmovl\t0(%%eax), %%eax\n");
                        fprintf(o_src,"\tpushl\t%%edx\n");
                        stackframe_cnt += 4;
                        }
                else if (symlen(sy)>=4)
                        fprintf(o_src,"\tmovl\t0(%%eax), %%eax\n");
                else
                        fprintf(o_src,"\tmovs%cl\t0(%%eax), %%eax\n",varsize_ch(sy));
        }
        else
                fprintf(o_src,"\tmovl\t0(%%eax), %%eax\n");
        fprintf(o_src,"\tpushl\t%%eax\n");
}

void load_at_eax(struct sym *sy) {
#ifdef DEBUG_COMPILER
        fprintf(o_src, "#   load_at_eax:\n");
#endif
        if (sy->type == DTYPE_BININT || sy->type == DTYPE_FLOAT) { 
                if (symlen(sy)==8) {
                        fprintf(o_src,"\tmovl\t4(%%eax), %%edx\n");
                        fprintf(o_src,"\tmovl\t0(%%eax), %%eax\n");
                        }
                else if (symlen(sy)>=4)
                        fprintf(o_src,"\tmovl\t0(%%eax), %%eax\n");
                else
                        fprintf(o_src,"\tmovs%cl\t0(%%eax), %%eax\n",varsize_ch(sy));
        }
        else
                fprintf(o_src,"\tmovl\t0(%%eax), %%eax\n");
}

void cleanup_rt_stack() {
        /* generate stack cleanup only if there is something to clean */
        if (stackframe_cnt==1)
                fprintf(o_src,"\tpopl\t%%ecx\n");
        else if (stackframe_cnt)
                fprintf(o_src,"\taddl\t$%d, %%esp\n",stackframe_cnt);
        stackframe_cnt = 0;
        if (need_desc_length_cleanup) {
                /*#if !defined(__WINDOWS__)
                  fprintf(o_src,"\tcall\tcob_free_desc_list\n");
                #else
                  fprintf(o_src,"\tcall\t_cob_free_desc_list\n");
                #endif*/
                tmpvar_offset = 0; /* reuse this storage area */
                need_desc_length_cleanup = 0;
        }
}

void asm_call( char *s ) {
        #if !defined(__WINDOWS__)
          fprintf(o_src,"\tcall\t%s\n",s);
        #else
          fprintf(o_src,"\tcall\t_%s\n",s);
        #endif
        cleanup_rt_stack();
        /* 
          FIXME: 
          Temporary fix for seg-fault !!! 
          Removing this will result in a corrupt literal list
          and cause a seg-fault only if the '-P option is not used !?!
        */
        fflush(o_src);
}

/* as asm_call but without stack cleaning */
void asm_call1( char *s ) {
        #if !defined(__WINDOWS__)
          fprintf(o_src,"\tcall\t%s\n",s);
        #else
          fprintf(o_src,"\tcall\t_%s\n",s);
        #endif
}

void emt_cobrtl_call( char *s, char *prefix ) {
        #if !defined(__WINDOWS__)
          fprintf(o_src,"\tcall\t%s_%s\n",prefix,s);
        #else
          fprintf(o_src,"\tcall\t_%s_%s\n",prefix,s);
        #endif
        cleanup_rt_stack();
}

int
varsize_ch( struct sym *sy ) {
        switch (symlen(sy)) {
        case 1: return 'b';
        case 2: return 'w';
        default: return 'l';
        }
}
int find_son( struct sym  *parent ,struct sym  *son){
    struct sym  *tmp;
    for(tmp=son;tmp!=NULL;tmp=tmp->parent)
    {
        if (tmp->parent == parent)
            return TRUE;
    }
    return FALSE;
}

void gen_call_scr_process(struct sym *sy) {
        
        static struct sym *temp_color = NULL;       /* temporay fields for     */
        static struct sym *temp_background = NULL;  /* screen location and     */
        static struct sym *temp_foreground = NULL;  /* colors, to be sure that */
        static struct sym *temp_line = NULL;        /* we call the function    */
        static struct sym *temp_column = NULL;      /* pushing integers        */
        static struct sym *temp_size = NULL;        /*                         */ 
        
        struct sym *temp_parent = NULL;
        struct sym *temp_son = NULL;
            
        if ((sy->scr->line_sign != 0) ||
            ((sy->scr->line==0) && (sy->scr->line_var==NULL))){ 
                                        /* when we have a line +/-, we have to */
                                        /* put the cursor on the correct position */
            if (! temp_line ) temp_line=define_temp_field(DTYPE_BININT,4);
            /* && (temp_parent->scr->line_sign !=0)*/
            for( temp_parent=sy;temp_parent->parent;temp_parent=temp_parent->parent) /*find the top level*/
            {
                if ((temp_parent->scr->line_sign == 0) &&
                    ((temp_parent->scr->line != 0) || (temp_parent->scr->line_var!=NULL)))
                 {
                   break;
                 }
            }
            if(temp_parent->scr->line_sign != 0)
                yyerror("structure not suported '%s', invalid line",temp_parent->name);
            
            while(temp_parent)
            {
                
                if (temp_parent->scr->line_var) {
                    gen_move(temp_parent->scr->line_var,temp_line);
                    push_immed(temp_parent->scr->line_sign);
                    value_to_eax(temp_line);
                    push_eax();
                    asm_call("tcob_go_y");
                } else {
                    if (temp_parent->scr->line)
                    {
                       push_immed(temp_parent->scr->line_sign);
                       push_immed(temp_parent->scr->line);
                       asm_call("tcob_go_y");
                    }
                }
                
                if (find_son(temp_parent,sy))
                {
                    temp_parent=temp_parent->uval7.son;
                }
                else
                {
                    temp_parent=temp_parent->uval8.brother;
                }
                if (temp_parent == sy)    
                    temp_parent=NULL;
            }
        }
        temp_parent = NULL;
        temp_son = NULL;
        if (sy->scr->column_sign != 0) { /* when we have a line +/-, we have to */
                                         /* put the cursor on the correct positiona */
            if (! temp_column ) temp_column = define_temp_field(DTYPE_BININT,4);

            temp_son = (sy->parent)->uval7.son;
            
            if(temp_son->scr->column_sign != 0)
                yyerror("structure not suported '%s', invalid column",temp_son->name);
            
            if((temp_son->scr->column == 0 )&&(temp_son->scr->column_var==NULL))
                temp_son->scr->column = 1;
            
            for( ;temp_son!=sy;temp_son=temp_son->uval8.brother)
            {
                if ((temp_son->scr->column == 0) && (temp_son->scr->column_var == NULL))
                {
                    temp_son->scr->column_sign=1;
                    temp_son->scr->column=1;
                }
                if (temp_son->scr->column)
                {
                    push_immed(temp_son->scr->column_sign);
                    push_immed(temp_son->scr->column + temp_son->len -1);
                    asm_call("tcob_go_x");
                    
                }
                if(temp_son->scr->column_var)
                {
                    gen_move(temp_son->scr->column_var,temp_column);
                    
                    value_to_eax(temp_column);
                    fprintf(o_src,"\taddl\t$%d, %%eax\n",temp_son->len - 1);
                    push_immed(temp_son->scr->column_sign);
                    push_eax();
                    asm_call("tcob_go_x");
                }
            }
            
        }
            
        if (sy->scr->color)
        {
                if (! temp_color) temp_color=define_temp_field(DTYPE_BININT,4);
                gen_move(sy->scr->color,temp_color);
        }
        if (sy->scr->background)
        {
                if (! temp_background ) temp_background=define_temp_field(DTYPE_BININT,4);
                gen_move(sy->scr->background,temp_background);
        }
        if (sy->scr->foreground)
        {
                if (! temp_foreground ) temp_foreground=define_temp_field(DTYPE_BININT,4);
                gen_move(sy->scr->foreground,temp_foreground);
        }
        if (sy->scr->line_var)
        {
                if (! temp_line ) temp_line=define_temp_field(DTYPE_BININT,4);
                gen_move(sy->scr->line_var,temp_line);
        }
        if (sy->scr->column_var)
        {
                if (! temp_column ) temp_column=define_temp_field(DTYPE_BININT,4);
                gen_move(sy->scr->column_var,temp_column);
        }
        if (sy->scr->size)
        {
                if (! temp_size ) temp_size=define_temp_field(DTYPE_BININT,4);
                gen_move(sy->scr->size,temp_size);
        }


        gen_loadvar(sy->scr->to);         /* to field */
        gen_loadvar(sy->scr->from);       /* from field */
        gen_loadvar(sy);                  /* screen field */

        
        if (sy->scr->size)
        {
          value_to_eax(temp_size);  /* size */
          push_eax();
        } 
        else
        {
            push_immed(-1);
        }
        
        if (sy->scr->background)
        {
          value_to_eax(temp_background);  /* background color */
          push_eax();
        } 
        else
        {
          if (sy->scr->color) 
          {
            value_to_eax(temp_color);
            fprintf(o_src,"\tand\t$0x000000F0,%%eax\n"); /* bits 4-7 */
                                                         /* color = 16 * fore-color */
            fprintf(o_src,"\tshr\t$4,%%eax\n");
            push_eax();
          } 
          else
          {
            push_immed(-1); 
          }
        }

        if (sy->scr->foreground) {
          value_to_eax(temp_foreground);  /* foreground color */
          push_eax();
        } else {
          if (sy->scr->color) {
            value_to_eax(temp_color);
            fprintf(o_src,"\tand\t$0x0000000F,%%eax\n"); /* bits 0-3 of color */
            push_eax();
          } 
          else
            push_immed(-1); 
        }
        push_immed(sy->scr->column_sign); /* column sign */
        /* push_immed(0); */ /* column sign */
        if (sy->scr->column_var)          /* column */
        {
          value_to_eax(temp_column);
          push_eax();
        }
        else
        {
          push_immed(sy->scr->column);
        }
        push_immed(sy->scr->line_sign);   /* line sign */
        /*push_immed(0);*/ /* line sign */
        if (sy->scr->line_var)            /* line */
        {
          value_to_eax(temp_line);
          push_eax();
        }
        else
        {
          push_immed(sy->scr->line);
        }

        if (sy->scr->color)
        {
          fprintf(o_src,"\tmov\t$%d,%%ebx\n",sy->scr->attr);
          value_to_eax(temp_color);
          fprintf(o_src,"\tand\t$0x0000FF00,%%eax\n");   /* bits 8-15 */
          fprintf(o_src,"\tshr\t$8,%%eax\n");
          fprintf(o_src,"\tor\t%%ebx,%%eax\n");
          push_eax();                    /* attributes */

        }
        else
        {
          push_immed(sy->scr->attr);     /* attributes */
        }
        asm_call("tcob_scr_process");
}

struct math_ose *
math_on_size_error0(void) {
        struct math_ose *v;
        v = malloc(sizeof(struct math_ose)); 
        v->ose=0;              /* type of option */
        v->lbl1=0;             /* call label name 1 - on_size */
        v->lbl2=0;             /* call label name 2 - not_on_size */
        v->lbl4=loc_label++;   /* determine bypass label name */
        fprintf(o_src,"\tmovl\t$0,%%eax\n\tpushl\t%%eax\n");        /* reset ose cnt */
        gen_jmplabel(v->lbl4); /* generate bypass jump */
        return v;
}

struct math_ose *
math_on_size_error1(struct math_ose *v) {
        v->ose=loc_label++;            
        fprintf(o_src,".L%d:\n",(int)v->ose);
        return v;
}

void math_on_size_error2(struct math_ose *v) {
        fprintf(o_src,"\tjmp\t.L%ldR\n",v->ose);
}

void math_on_size_error3( struct math_ose *v, char end ) {

        if (v == (struct math_ose *)NULL)
           return;
        
        /* 
         Set the overflow error flag for the math routines,  
         found on the generated ASM code stack.
         Since math intermidiate results are stored on the generated 
         ASM code stack using double (float), the stack is not cleaned
         until the last assignment (double to COBOL struct). 
         This causes the overflow error flag stack location to vary. 
         The following code adjusts this problem.
        */ 
        if (end == '1') 
           fprintf(o_src,"\torl\t%%eax, (%%esp)\n"); 
        else
           fprintf(o_src,"\torl\t%%eax, 8(%%esp)\n"); 
}

struct math_ose *
math_on_size_error4(struct math_ose *v, unsigned long ty) {
        
        /* ose=ty;     type of option */
        /* lbl1        call label name 1 - on_size */
        /* lbl2        call label name 2 - not_on_size */

        switch (ty)
        {
          case 1:
           v->lbl1=v->ose;
           v->ose=ty;    
           break;
          
          case 2:
           v->lbl2=v->ose;
           v->ose=ty;    
            break;
          
          case 3:
           v->lbl2=v->ose;
           v->ose=ty;    
            break;
          
          default:
            break;
        }
        
        return v;
}


void math_on_size_error5( struct math_ose *v ) {
        unsigned long lbl1, lbl2;
        
        if (v == (struct math_ose *)NULL)
                return;
        
        lbl1=loc_label++;

        fprintf(o_src,"\tpopl\t%%eax\n");
        switch (v->ose)
        {
          case 1:
            fprintf(o_src,"\tcmpl\t$0, %%eax\n");
            fprintf(o_src,"\tje\t.L%ld\n",lbl1);
            gen_jmplabel(v->lbl1); 
            fprintf(o_src,"\t.align 16\n");
            fprintf(o_src,".L%ldR:\n", v->lbl1);        
            fprintf(o_src,".L%ld:\n",lbl1);        
            break;
          
          case 2:
            fprintf(o_src,"\tcmpl\t$0, %%eax\n");
            fprintf(o_src,"\tjne\t.L%ld\n",lbl1);
            gen_jmplabel(v->lbl2); 
            fprintf(o_src,"\t.align 16\n");
            fprintf(o_src,".L%ldR:\n", v->lbl2);        
            fprintf(o_src,".L%ld:\n",lbl1);        
            break;
          
          default:
            lbl2=loc_label++;
            fprintf(o_src,"\tcmpl\t$0, %%eax\n");
            fprintf(o_src,"\tje\t.L%ld\n",lbl1);
            gen_jmplabel(v->lbl1); 
            fprintf(o_src,"\t.align 16\n");
            fprintf(o_src,".L%ldR:\n", v->lbl1);        
            gen_jmplabel(lbl2); 
            fprintf(o_src,".L%ld:\n",lbl1);        
            gen_jmplabel(v->lbl2); 
            fprintf(o_src,"\t.align 16\n");
            fprintf(o_src,".L%ldR:\n", v->lbl2);        
            fprintf(o_src,".L%ld:\n",lbl2);        
            break;
        }
}

/******** generic structure allocation and code genertion ***********/
struct ginfo *ginfo_container0(void) {
        struct ginfo *v;
        v = malloc(sizeof(struct ginfo)); 
        v->sel=0;              /* type of option */
        v->lbl1=0;             /* call label name 1 - true */
        v->lbl2=0;             /* call label name 2 - not true */
        v->lbl3=loc_label++;   /* End of statement label name */
        v->lbl4=0;             /* not used */
        v->lbl5=loc_label++;   /* determine test  bypass label name */
        gen_jmplabel(v->lbl5); /* generate test bypass jump */
        return v;
}

struct ginfo *ginfo_container1(struct ginfo *v) {
        v->sel=loc_label++;            
        fprintf(o_src,".L%d:\n",(int)v->sel);
        return v;
}

void ginfo_container2(struct ginfo *v, unsigned long ty) {

        switch (ty)
        {
          case 1:
            v->lbl1=v->sel;
            v->sel=0; 
            /*v->lbl3=loc_label++;    return 1 label name */
           /* gen_jmplabel(v->lbl3);  generate return 1 label jump */
            break;
          
          case 2:
            v->lbl2=v->sel;
            v->sel=0; 
            /*v->lbl4=loc_label++;    return 2 label name */
            /*gen_jmplabel(v->lbl4); generate return 2 label jump */
            break;
        }
        gen_jmplabel(v->lbl3); /* generate end label jump */
}

struct ginfo *
ginfo_container3(struct ginfo *v, unsigned long ty) {
        
        /* sel=ty;     type of option */
        /* lbl1        call label name 1 - true  */
        /* lbl2        call label name 2 - not true */

        switch (ty)
        {
          case 1:
           v->sel=ty;    
           break;
          
          case 2:
           v->sel=ty;    
            break;
          
          case 3:
           v->sel=ty;    
            break;
          
          default:
            break;
        }

        fprintf(o_src,"\t.align 16\n");
        fprintf(o_src,".L%d:\n",(int)v->lbl5);
        
        return v;
}

void ginfo_container4( struct ginfo *v ) {

        switch (v->sel)
        {
          case 1:
#ifdef DEBUG_COMPILER
            fprintf (o_src, "# Test for At End ...\n");
#endif
            fprintf(o_src,"\tcmpl\t$10, %%eax\n");
            fprintf(o_src,"\tje\t.L%ld\n",v->lbl1);
            /* gen_jmplabel(v->lbl1); */
            fprintf(o_src,"\t.align 16\n");
            fprintf(o_src,".L%ld:\n",v->lbl3);        
            break;
          
          case 2:
#ifdef DEBUG_COMPILER
            fprintf (o_src, "# Test for Not At End ...\n");
#endif
            fprintf(o_src,"\tcmpl\t$10, %%eax\n");
            fprintf(o_src,"\tjne\t.L%ld\n",v->lbl2);
            /* gen_jmplabel(v->lbl2);  */
            fprintf(o_src,"\t.align 16\n");
            fprintf(o_src,".L%ld:\n",v->lbl3);        
            break;
          
          default:
#ifdef DEBUG_COMPILER
            fprintf (o_src, "# Test for At End ... Not At End ...\n");
#endif
            fprintf(o_src,"\tcmpl\t$10, %%eax\n");
            fprintf(o_src,"\tjne\t.L%ld\n",v->lbl2);
            gen_jmplabel(v->lbl1); 
            fprintf(o_src,"\t.align 16\n");
            fprintf(o_src,".L%ld:\n",v->lbl3);        
            /* gen_jmplabel(v->lbl2);  */
            /* fprintf(o_src,"\t.align 16\n"); */
            /* fprintf(o_src,".L%ld:\n",v->lbl4); */        
            break;
        }
        
}

void gen_test_invalid_keys (struct invalid_keys *p, struct sym *f, int fs)
{

  if (p == NULL) return;
  if (p->invalid_key) {
    int lbl = loc_label++;
#ifdef DEBUG_COMPILER
    fprintf (o_src, "# Test for INVALID KEY\n");
#endif
    fprintf (o_src, "\tcmp\t$%d, %%eax\n", fs);
    fprintf (o_src, "\tjnz\t.L%d\n", lbl);
    gen_jmplabel (p->invalid_key->lbl2);
    fprintf (o_src, "\t.align 16\n");
    fprintf (o_src, ".L%d:\n", lbl);
  }

  if (p->not_invalid_key) {
    int lbl = loc_label++;
#ifdef DEBUG_COMPILER
    fprintf (o_src, "# Test for NOT INVALID KEY\n");
#endif
    fprintf (o_src, "\tcmp\t$%d, %%eax\n", fs);
    fprintf (o_src, "\tjz\t.L%d\n", lbl);
    gen_jmplabel (p->not_invalid_key->lbl2);
    fprintf (o_src, "\t.align 16\n");
    fprintf (o_src, ".L%d:\n", lbl);
  }

  if (p->invalid_key)
    gen_dstlabel (p->invalid_key->lbl3);
  if (p->not_invalid_key)
    gen_dstlabel (p->not_invalid_key->lbl3);

  /* gen_perform_decl(f); */

  if (p->invalid_key)
    free (p->invalid_key);
  if (p->not_invalid_key)
    free (p->not_invalid_key);
  free (p);
  p=NULL;
}

void gen_subscripted( struct vref *subs ) {
        struct vref *ref;
        struct sym *sy,*var;
        int outer_pushed,eax_in_use;
        char op;
        int stack_save;

        ref = subs->next;                         /* here start the subscripts */
        var = sy = subs->sym;                 /* here our array */
        op = ref->litflag;
        fprintf(o_src,"# gen_subscripted\n");
        outer_pushed=0;
        eax_in_use=0;
        while (ref) {
                if (((struct sym *)(ref->sym))->type == DTYPE_BININT
                        && symlen(ref->sym) > 4)
                                yywarn("binary long long subscript truncated to long");
                if (eax_in_use && !outer_pushed) {        
                        fprintf(o_src,"\tpushl\t%%eax\t# outer_pushed\n"); /* accumulate offsets here */
                        outer_pushed++;
                }
                eax_in_use=1;
                value_to_eax( ref->sym );
                if (((struct sym *)(ref->sym))->type == DTYPE_BININT
                        && symlen(ref->sym) > 4) {
                        /* the following code is not strictly necessary: we could use %eax directly
                           but if a runtime check is needed, it is probably easier to implement
                           in the routine cob_cnv_ll2int! */
                        stack_save=stackframe_cnt;
                        stackframe_cnt = 0;
                        push_edx();
                        push_eax();
                        asm_call("tcob_cnv_ll2i");
                        stackframe_cnt = stack_save;
                        }
                fprintf(o_src,"\tpushl\t%%eax\n");
                while ( ref->litflag != ',') {
                                op = ref->litflag;
                                ref=ref->next;
                                value_to_eax(ref->sym);
                                if (symlen(ref->sym) > 4) {
                                        yywarn("binary long long subscript truncated to long");
                                        stack_save=stackframe_cnt;
                                        stackframe_cnt = 0;
                                        push_edx();
                                        push_eax();
                                        asm_call("tcob_cnv_ll2i");
                                        stackframe_cnt = stack_save;
                                }
                                if (op=='+')
                                        fprintf(o_src,"\taddl\t%%eax,0(%%esp)\n");
                                else
                                        fprintf(o_src,"\tsubl\t%%eax,0(%%esp)\n"); 
                }
                /* find the first parent var that needs subscripting */
                while (sy && !sy->occurs_flg) 
                        sy = sy->parent;
                fprintf(o_src,"\tpopl\t%%eax\n");
                fprintf(o_src,"\tdecl\t%%eax\n"); /* subscript start at 1 */
                if (sy->len != 1) {
                        fprintf(o_src,"\tmovl\t$%d, %%edx\n",symlen(sy));
                        fprintf(o_src,"\timull\t%%edx\n");
                }
                if (outer_pushed) {
                        fprintf(o_src,"\taddl\t%%eax,0(%%esp)\n");
                }
                if (sy) sy = sy->parent;
                ref = ref->next;
        }
        /*stackframe_cnt += 4;*/        /* update our stack frame counter */
        if (outer_pushed)
                fprintf(o_src,"\tpopl\t%%eax\n"); /* return offset in %eax */
}


void gen_temp_storage( int size ) {
        stackframe_cnt += 4;
        /* fprintf(o_src,"\tpushl\t$tv_base%d+%d\n",pgm_segment,tmpvar_offset); */
        fprintf(o_src,"\tpushl\t$tv_base%d_%d\n", pgm_segment, tmpvar_offset);
        tmpvar_offset += size;
        if (tmpvar_offset > tmpvar_max) {
                tmpvar_max = tmpvar_offset;
        }
}

void value_to_eax ( struct sym *sy ) {
        long long value;
        long value2;
        int stack_save;
#ifdef DEBUG_COMPILER
        if (sy) fprintf(o_src,"# value_to_eax %s\n",sy->name);
#endif
        if (sy == NULL) {
                fprintf(o_src,"\txorl\t%%eax,%%eax\n");
                return;        
        }
        if (sy->litflag) {
                int i, bSign=0;
                char cDigit;
                /* if it's an integer, compute it now, not at runtime! */
                value = 0;
                /* integer's name is just it's value in ascii */
                for (i=0; (cDigit = sy->name[i]); i++) {
                        if (cDigit=='}') {
                                cDigit = 0;
                        } else if (cDigit=='{') {
                                cDigit = 0;
                                bSign = 1;
                        } else if ((cDigit >= 'A') && (cDigit <= 'I')) {
                                cDigit -= 'A'-1;
                        } else if ((cDigit >= 'J') && (cDigit <= 'R')) {
                                cDigit -= 'J'-1;
                                bSign = 1;
                        } else {
                                cDigit -= '0';
                        }
                        value = value * 10 + cDigit;
                }
                if (bSign)
                        value = -value;
                fprintf(o_src,"\tmovl\t$%d,%%eax\n",(int)value);
                value2 = value >> 32;
                if ((value2!=0) && (value2!=-1))
                        fprintf(o_src,"\tmovl\t$%d,%%edx\n",(int)value2);
        } else if (sy->type == DTYPE_BININT || sy->type == DTYPE_FLOAT) { 
                /* load binary (comp) value directly */
                /* %eax doesn't hold greater than 4 bytes binary types
                        so we use %edx to get the most significant part */
                if (symlen(sy) > 4) {
                        fprintf(o_src,"\tleal\t%s, %%eax\n",memrefat(sy));
                        fprintf(o_src,"\tmovl\t4(%%eax), %%edx\n");
                        fprintf(o_src,"\tmovl\t0(%%eax), %%eax\n");
                } else {
                        if (symlen(sy)>=4) {
                                switch (sy->sec_no) {
                                case SEC_CONST:
                                        /* fprintf(o_src,"\tmovl\tc_base%d+%d, %%eax\n", */
                                        fprintf(o_src,"\tmovl\tc_base%d_%d, %%eax\n",
                                                pgm_segment, sy->uval2.location);
                                        break;
                                case SEC_DATA:
                                        {
                                        /* fprintf(o_src,"\tmovl\tw_base%d+%d, %%eax\n", 
                                                   pgm_segment, sy->uval2.location); */
                                        /* char *vname = convert_variable_name(sy);*/
                                        if (sy->offset_mloc == 0) 
                                           /* fprintf(o_src,"\tmovl\t%s.%d, %%eax\n", vname, pgm_segment);*/
                                           fprintf(o_src,"\tmovl\tw_base%d_%d, %%eax\n", 
                                                   pgm_segment, sy->uval2.location);
                                        else 
                                           /* fprintf(o_src,"\tmovl\t%s.%d+%d, %%eax\n", vname, pgm_segment, sy->uval2.location - sy->offset_mloc);*/ 
                                           fprintf(o_src,"\tmovl\tw_base%d_%d+%d, %%eax\n", 
                                                   pgm_segment, sy->offset_mloc, sy->uval2.location - sy->offset_mloc);
                                        }
                                        break;
                                case SEC_STACK:
                                        fprintf(o_src,"\tmovl\t-%d(%%ebp), %%eax\n",sy->uval2.location);
                                        break;
                                        break;
                                }
                        } else { 
                                switch (sy->sec_no) {
                                case SEC_CONST:
                                        /* fprintf(o_src,"\tmovs%cl\tc_base%d+%d, %%eax\n", */
                                        fprintf(o_src,"\tmovs%cl\tc_base%d_%d, %%eax\n",
                                                varsize_ch(sy), pgm_segment, sy->uval2.location);
                                        break;
                                case SEC_DATA:
                                        {
                                        /* fprintf(o_src,"\tmovs%cl\tw_base%d+%d, %%eax\n",
                                                varsize_ch(sy),pgm_segment,sy->uval2.location); */
                                        /* char *vname = convert_variable_name(sy); */
                                        if (sy->offset_mloc == 0) 
                                           /* fprintf(o_src,"\tmovs%cl\t%s.%d, %%eax\n", 
                                                   varsize_ch(sy), vname, pgm_segment);  */
                                           fprintf(o_src,"\tmovs%cl\tw_base%d_%d, %%eax\n", 
                                                   varsize_ch(sy), pgm_segment, sy->uval2.location);
                                        else 
                                           /* fprintf(o_src,"\tmovs%cl\t%s.%d+%d, %%eax\n", 
                                                   varsize_ch(sy), vname, pgm_segment, sy->uval2.location - sy->offset_mloc); */
                                           fprintf(o_src,"\tmovs%cl\tw_base%d_%d+%d, %%eax\n", 
                                                   varsize_ch(sy), pgm_segment, sy->offset_mloc, sy->uval2.location - sy->offset_mloc); 
                                        }
                                        break;
                                case SEC_STACK:
                                        fprintf(o_src,"\tmovs%cl\t-%d(%%ebp), %%eax\n",
                                                varsize_ch(sy),sy->uval2.location);
                                        break;
                                }
                        }
                }
        } else {
                fprintf(o_src,"#val to eax complex $c_base+%u, %%eax\n",
                        sy->descriptor);
                stack_save=stackframe_cnt;
                stackframe_cnt = 0;
                gen_loadvar( sy );
                fprintf(o_src,"#\tmovl\t$c_base+%u, %%eax\n",
                        sy->descriptor);
                asm_call("tcob_get_index");
                stackframe_cnt=stack_save;
        }
}

void value_to_eax_at_eax ( struct sym *sy ) {
        long long value;
        long value2;
        int stack_save;
#ifdef DEBUG_COMPILER
        if (sy) fprintf(o_src,"# value_to_eax_at_eax %s\n",sy->name);
#endif
        if (sy == NULL) {
                fprintf(o_src,"\txorl\t%%eax,%%eax\n");
                return;        
        }
        if (sy->litflag) {
                int i, bSign=0;
                char cDigit;
                /* if it's an integer, compute it now, not at runtime! */
                value = 0;
                /* integer's name is just it's value in ascii */
                for (i=0; (cDigit = sy->name[i]); i++) {
                        if (cDigit=='}') {
                                cDigit = 0;
                        } else if (cDigit=='{') {
                                cDigit = 0;
                                bSign = 1;
                        } else if ((cDigit >= 'A') && (cDigit <= 'I')) {
                                cDigit -= 'A'-1;
                        } else if ((cDigit >= 'J') && (cDigit <= 'R')) {
                                cDigit -= 'J'-1;
                                bSign = 1;
                        } else {
                                cDigit -= '0';
                        }
                        value = value * 10 + cDigit;
                }
                if (bSign)
                        value = -value;
                fprintf(o_src,"\tmovl\t$%d,%%eax\n",(int)value);
                value2 = value >> 32;
                if ((value2!=0) && (value2!=-1))
                        fprintf(o_src,"\tmovl\t$%d,%%edx\n",(int)value2);
        } else if (sy->type == DTYPE_BININT || sy->type == DTYPE_FLOAT) { 
                /* load binary (comp) value directly */
                /* %eax doesn't hold greater than 4 bytes binary types
                        so we use %edx to get the most significant part */
                if (symlen(sy) > 4) {
                        fprintf(o_src,"\tmovl\t4(%%eax), %%edx\n");
                        fprintf(o_src,"\tmovl\t0(%%eax), %%eax\n");
                } else {
                        if (symlen(sy)>=4) {
                                switch (sy->sec_no) {
                                case SEC_CONST:
                                        /* fprintf(o_src,"\tmovl\tc_base%d+%d, %%eax\n", */
                                        fprintf(o_src,"\tmovl\tc_base%d_%d, %%eax\n",
                                                pgm_segment, sy->uval2.location);
                                        break;
                                case SEC_DATA:
                                        {
                                        /* fprintf(o_src,"\tmovl\tw_base%d+%d, %%eax\n",
                                                pgm_segment,sy->uval2.location); */
                                        /* char *vname = convert_variable_name(sy); */
                                        if (sy->offset_mloc == 0) 
                                           /* fprintf(o_src,"\tmovl\t%s.%d, %%eax\n", vname, pgm_segment); */
                                           fprintf(o_src,"\tmovl\tw_base%d_%d, %%eax\n", 
                                                   pgm_segment, sy->uval2.location);
                                        else 
                                           /* fprintf(o_src,"\tmovl\t%s%d+%d, %%eax\n", vname, pgm_segment, sy->uval2.location - sy->offset_mloc); */
                                           fprintf(o_src,"\tmovl\tw_base%d_%d+%d, %%eax\n", 
                                                   pgm_segment, sy->offset_mloc, sy->uval2.location - sy->offset_mloc);
                                        }
                                        break;
                                case SEC_STACK:
                                        fprintf(o_src,"\tmovl\t-%d(%%ebp), %%eax\n",sy->uval2.location);
                                        break;
                                        break;
                                }
                        } else { 
                                switch (sy->sec_no) {
                                case SEC_CONST:
                                        /* fprintf(o_src,"\tmovs%cl\tc_base%d+%d, %%eax\n", */
                                        fprintf(o_src,"\tmovs%cl\tc_base%d_%d, %%eax\n",
                                                varsize_ch(sy), pgm_segment, sy->uval2.location);
                                        break;
                                case SEC_DATA:
                                        {
                                        /* fprintf(o_src,"\tmovs%cl\tw_base%d+%d, %%eax\n",
                                                varsize_ch(sy),pgm_segment,sy->uval2.location); */
                                        /* char *vname = convert_variable_name(sy); */
                                        if (sy->offset_mloc == 0) 
                                           /* fprintf(o_src,"\tmovs%cl\t%s.%d, %%eax\n", varsize_ch(sy), vname, pgm_segment); */
                                           fprintf(o_src,"\tmovs%cl\tw_base%d_%d, %%eax\n", 
                                                   varsize_ch(sy), pgm_segment, sy->uval2.location);
                                        else 
                                           /* fprintf(o_src,"\tmovs%cl\t%s.%d+%d, %%eax\n", varsize_ch(sy), vname, pgm_segment, sy->uval2.location - sy->offset_mloc); */
                                           fprintf(o_src,"\tmovs%cl\tw_base%d_%d+%d, %%eax\n", 
                                                   varsize_ch(sy), pgm_segment, sy->offset_mloc, sy->uval2.location - sy->offset_mloc);
                                        }
                                        break;
                                case SEC_STACK:
                                        fprintf(o_src,"\tmovs%cl\t-%d(%%ebp), %%eax\n",
                                                varsize_ch(sy),sy->uval2.location);
                                        break;
                                }
                        }
                }
        } else {
                fprintf(o_src,"#val to eax complex $c_base+%u, %%eax\n",
                        sy->descriptor);
                stack_save=stackframe_cnt;
                stackframe_cnt = 0;
/*                gen_loadvar(sy); */
                push_eax();
                gen_loaddesc(sy);
                asm_call("tcob_get_index");
                stackframe_cnt=stack_save;
        }
}

/* load address for normal (file/working-storage) or linkage variable */
void load_address( struct sym *var ) {
        unsigned base,locoff;
        struct sym *tmp;
        if (!var->litflag && var->linkage_flg) {
                tmp=var;
                while (tmp->linkage_flg==1) tmp=tmp->parent;
                if (tmp==0)
                        hterror(103,8,"linkage section broken");
                base = tmp->linkage_flg;
                locoff = tmp->uval2.location - var->uval2.location;
/*
                //  FIXME or find a better hack !!
                //  Memory for LINKAGE SECTION identifiers is defined on the STACK.
                //  However it can contain pointers to the data, or the actual data. 
                //  For example, when a 'PROCEDURE DIVISION ... RETURNING identifier-n' 
                //  clause is used, identifier-n is defined in the LINKAGE SECTION.
                //  The contents of identifier-n is defined on the STACK.
                //  For example, when a 'PROCEDURE DIVISION USING ... identifier-n ...' 
                //  clause is used, identifier-n is defined in the LINKAGE SECTION.
                //  A pointer to the contents of identifier-n is defined on the STACK,
                //  as defined by the calling program.
                //  When the variable 'linkage_flg' contains a positive value, it is assumed
                //  to be defined by the calling program, and contains a pointer to the data.
                //  When the 'linkage_flg' variable contains a negative value, it is assumed
                //  to be defined within the program, and contains the actual data.
                //  
//              fprintf(o_src,"\tmovl\t%d(%%ebp), %%eax\n",base);
//              if (locoff) 
//                 fprintf(o_src,"\taddl\t$%d, %%eax\n",locoff);
*/
                if (tmp->linkage_flg > 0) {
                   fprintf(o_src,"\tmovl\t%d(%%ebp), %%eax\n", base);
                   if (locoff) 
                      fprintf(o_src,"\taddl\t$%d, %%eax\n", locoff);
                }
                else {
                   fprintf(o_src,"\tmovl\t%%ebp, %%edx\n");
                   fprintf(o_src,"\taddl\t$%d, %%edx\n", base);
                   if (locoff) 
                      fprintf(o_src,"\taddl\t$%d, %%edx\n", locoff);
                   fprintf(o_src,"\tmovl\t%%edx, %%eax\n");
                }
        }
/*        else if (!var->litflag) { */
        else if (var->sec_no == SEC_STACK) {
                fprintf(o_src,"\tleal\t%s, %%eax\n",memref(var));
        }
        else {
                if (var->sec_no == SEC_DATA)
#if 0
                        fprintf(o_src,"\tlea%c\tw_base+%d, %%ebx\n", 
                        The result is expected in %eax not %ebx
                        fprintf(o_src,"\tlea%c\tw_base+%d, %%eax\n", 
                                varsize_ch(var),var->uval2.location);
#endif
                        fprintf(o_src,"\tleal\tw_base%d+%d, %%eax\n",
                                pgm_segment, var->uval2.location);
                else if (var->sec_no == SEC_CONST)
#if 0
                        fprintf(o_src,"\tlea%c\tc_base+%d, %%ebx\n", 
                        fprintf(o_src,"\tlea%c\tc_base+%d, %%eax\n", 
                                varsize_ch(var),var->uval2.location);
#endif
                        /* fprintf(o_src,"\tleal\tc_base%d+%d, %%eax\n", */
                        fprintf(o_src,"\tleal\tc_base%d_%d, %%eax\n", 
                                pgm_segment, var->uval2.location);
                /* this is not the same! I need an address here, not the value.
                        fprintf(o_src,"\tmovl\t%s, %%eax\n",memref(var));*/
        }
}

/* load in cpureg ("eax","ebx"...) location for normal 
        (file/working-storage) or linkage variable */
void load_location( struct sym *var, char *cpureg ) {
        unsigned base,locoff;
        struct sym *tmp;
        if (var == NULL) {
                fprintf(o_src,"\txorl\t%%%s,%%%s\n",cpureg,cpureg);
                return;        
        }
        if (!var->litflag && var->linkage_flg) {
                tmp=var;
                while (tmp->linkage_flg==1) tmp=tmp->parent;
                if (tmp==0)
                        hterror(103,8,"linkage section broken");
                base = tmp->linkage_flg;
                locoff = var->uval2.location - tmp->uval2.location;
/*
//              fprintf(o_src,"\tmovl\t%d(%%ebp), %%%s\n",base,cpureg);
//              if (locoff) 
//                 fprintf(o_src,"\taddl\t$%d, %%%s\n",locoff,cpureg);
*/
/*
                //  FIXME or find a better hack !!
                //  Memory for LINKAGE SECTION identifiers is defined on the STACK.
                //  However it can contain pointers to the data, or the actual data. 
                //  For example, when a 'PROCEDURE DIVISION ... RETURNING identifier-n' 
                //  clause is used, identifier-n is defined in the LINKAGE SECTION.
                //  The contents of identifier-n is defined on the STACK.
                //  For example, when a 'PROCEDURE DIVISION USING ... identifier-n ...' 
                //  clause is used, identifier-n is defined in the LINKAGE SECTION.
                //  A pointer to the contents of identifier-n is defined on the STACK,
                //  as defined by the calling program.
                //  When the variable 'linkage_flg' contains a positive value, it is assummed
                //  to be defined by the calling program, and contains a pointer to the data.
                //  When the 'linkage_flg' variable contains a negative value, it is assummed
                //  to be defined within the program, and contains the actual data.
                //  
*/
                if (tmp->linkage_flg > 0) {
                   fprintf(o_src,"\tmovl\t%d(%%ebp), %%%s\n", base, cpureg);
                   if (locoff) 
                      fprintf(o_src,"\taddl\t$%d, %%%s\n", locoff, cpureg);
                }
                else {
                   fprintf(o_src,"\tmovl\t%%ebp, %%%s\n", cpureg);
                   fprintf(o_src,"\taddl\t$%d, %%%s\n", base, cpureg);
                   if (locoff) 
                      fprintf(o_src,"\taddl\t$%d, %%%s\n", locoff, cpureg);
/*                 fprintf(o_src,"\tmovl\t(%%%s), %%%s\n", cpureg, cpureg); */
                }
        }
/*        else if (!var->litflag) { */
        else if (var->sec_no == SEC_STACK) {
                fprintf(o_src,"\tleal\t%s, %%%s\n",memref(var),cpureg);
        }
        else {
                fprintf(o_src,"\tmovl\t%s, %%%s\n",memref(var),cpureg);

        }
}

void loadloc_to_eax( struct sym *sy_p ) {
        unsigned base,locoff;
        struct sym *sy = sy_p,*var,*tmp;
        if (sy == NULL) {
                hterror(104,8,"*** fatal error: variable undefined!\n");
                return;
        }
#ifdef DEBUG_COMPILER
        if (sy->litflag == 0)
           fprintf(o_src,"# NAME: '%s' litflg %d, linkage_flg %d\n", sy->name, sy->litflag, sy->linkage_flg);
         else
           fprintf(o_src,"# NAME: '%s' litflg %d\n", sy->name, sy->litflag);
#endif        
        if (sy->litflag == 4)
                sy=((struct refmod *)sy)->sym; /* temp bypass */
        if (sy->litflag == 2) {
                gen_subscripted( (struct vref *)sy );
                var = (struct sym *)((struct vref *)sy)->sym;
                if (var->linkage_flg) {
                        tmp=var;
                        while (tmp->linkage_flg==1) tmp=tmp->parent;
                        if (tmp==0)
                                yyerror("linkage section broken");
                        base = tmp->linkage_flg;
                        /*locoff = tmp->uval2.location - var->uval2.location;*/
                        locoff = var->uval2.location - tmp->uval2.location;
/*
                        //  FIXME or find a better hack !!
                        //  Memory for LINKAGE SECTION identifiers is defined on the STACK.
                        //  However it can contain pointers to the data, or the actual data. 
                        //  For example, when a 'PROCEDURE DIVISION ... RETURNING identifier-n' 
                        //  clause is used, identifier-n is defined in the LINKAGE SECTION.
                        //  The contents of identifier-n is defined on the STACK.
                        //  clause is used, identifier-n is defined in the LINKAGE SECTION.
                        //  For example, when a 'PROCEDURE DIVISION USING ... identifier-n ...' 
                        //  clause is used, identifier-n is defined in the LINKAGE SECTION.
                        //  A pointer to the contents of identifier-n is defined on the STACK,
                        //  as defined by the calling program.
                        //  When the variable 'linkage_flg' contains a positive value, it is assumed
                        //  to be defined by the calling program, and contains a pointer to the data.
                        //  When the 'linkage_flg' variable contains a negative value, it is assumed
                        //  to be defined within the program, and contains the actual data.
                        //  
*/
/*
                        if (symlen(var)>=4)
                           fprintf(o_src,"\tmovl\t%d(%%ebp), %%ebx\n",base);
                        else 
                           fprintf(o_src,"\tmovs%cl %d(%%ebp), %%ebx\n",varsize_ch(var),base);
*/
/*
//                      fprintf(o_src,"\tmovl\t%d(%%ebp), %%ebx\n", base);
//                      if (locoff)
//                         fprintf(o_src,"\taddl\t$%d, %%ebx\n", locoff);
//                      fprintf(o_src,"\taddl\t%%ebx, %%eax\n");
*/
                        if (tmp->linkage_flg > 0) {
                           fprintf(o_src,"\tmovl\t%d(%%ebp), %%ebx\n", tmp->linkage_flg);
                           if (locoff)
                              fprintf(o_src,"\taddl\t$%d, %%ebx\n", locoff);
                        }
                        else {
                           fprintf(o_src,"\tmovl\t%%ebp, %%ebx\n");
                           fprintf(o_src,"\taddl\t$%d, %%ebx\n", tmp->linkage_flg);
                           if (locoff)
                              fprintf(o_src,"\taddl\t$%d, %%ebx\n", locoff);
                        }
                        fprintf(o_src,"\taddl\t%%ebx, %%eax\n");
                }
                else {
                        if (var->sec_no == SEC_STACK)
                                fprintf(o_src,"\tleal\t%s, %%ebx\n", memref(var));
                        else {
                                if (var->sec_no == SEC_DATA) {
                                        /*  fprintf(o_src,"\tlea%c\tw_base+%d, %%ebx\n", 
                                                varsize_ch(var),var->uval2.location); */
                                        /* fprintf(o_src,"\tleal\tw_base%d+%d, %%ebx\n", 
                                                pgm_segment,var->uval2.location); */
                                        /* char *vname = convert_variable_name(var); */
                                        if (var->offset_mloc == 0) {
                                           /* fprintf(o_src,"\tleal\t%s.%d, %%ebx\n", vname, pgm_segment); */
                                           fprintf(o_src,"\tleal\tw_base%d_%d, %%ebx\n", 
                                                   pgm_segment, var->uval2.location);
                                        
                                        } 
                                        else {
                                           /* fprintf(o_src,"\tleal\t%s.%d+%d, %%ebx\n",  vname, pgm_segment, var->uval2.location - var->offset_mloc); */
                                           fprintf(o_src,"\tleal\tw_base%d_%d+%d, %%ebx\n", 
                                                   pgm_segment, var->offset_mloc, var->uval2.location - var->offset_mloc);
                                        }
                                }
                                else if (var->sec_no == SEC_CONST)
                                        /*  fprintf(o_src,"\tlea%c\tc_base+%d, %%ebx\n", 
                                                varsize_ch(var),var->uval2.location); */
                                        /*fprintf(o_src,"\tleal\tc_base%d+%d, %%ebx\n", */ 
                                        fprintf(o_src,"\tleal\tc_base%d_%d, %%ebx\n", 
                                                pgm_segment, var->uval2.location);
                        }
                                
                        fprintf(o_src,"\taddl\t%%ebx,%%eax\n");
                }
        }
        else {
                load_location( sy,"eax" );
        }
/*        At that stage, the address is ready in %eax; do we need
          to correct it because of RefMod's? */
        if (sy_p->litflag == 4) { /* should avoid all that if literal 1 */
                struct refmod * rfp = (struct refmod *)sy_p;
                fprintf(o_src,"\tmovl\t%%eax, %%ebx\n");
                value_to_eax((rfp->off));
                fprintf(o_src,"\tdecl\t%%eax\n");
                fprintf(o_src,"\taddl\t%%ebx, %%eax\n");
        }
}
/*
  store variable pointer in eax to sy.
  sy must be a pointer or a linkage section 01/77 variable 
*/
void set_ptr(struct sym *sy) {
        /*unsigned base;*/
        if (sy->litflag==0 && sy->linkage_flg) {
                if (sy->linkage_flg==1) { 
                        yyerror("only level 01 or 77 linkage vars may be set");
                        return;
                }
/*
                //  FIXME or find a better hack !!
                //  Memory for LINKAGE SECTION identifiers is defined on the STACK.
                //  However it can contain pointers to the data, or the actual data. 
                //  For example, when a 'PROCEDURE DIVISION ... RETURNING identifier-n' 
                //  clause is used, identifier-n is defined in the LINKAGE SECTION.
                //  The contents of identifier-n is defined on the STACK.
                //  For example, when a 'PROCEDURE DIVISION USING ... identifier-n ...' 
                //  clause is used, identifier-n is defined in the LINKAGE SECTION.
                //  A pointer to the contents of identifier-n is defined on the STACK,
                //  as defined by the calling program.
                //  When the variable 'linkage_flg' contains a positive value, it is assummed
                //  to be defined by the calling program, and contains a pointer to the data.
                //  When the 'linkage_flg' variable contains a negative value, it is assummed
                //  to be defined within the program, and contains the actual data.
                //  
*/
                if (sy->linkage_flg > 0) {
                   fprintf(o_src,"\tmovl\t%%eax, %d(%%ebp)\n", sy->linkage_flg);
                }
                else {
                   fprintf(o_src,"\tmovl\t%%ebp, %%edx\n");
                   fprintf(o_src,"\taddl\t$%d, %%edx\n", sy->linkage_flg);
                   fprintf(o_src,"\tmovl\t%%eax, (%%edx)\n");
                }
                return;
        }
        else {
                if (sy->litflag==0) {
                        load_location(sy,"ebx");
                        fprintf(o_src,"\tmovl\t%%eax,0(%%ebx)\n");
                }
                else {
                        fprintf(o_src,"\tpushl\t%%eax\t# saving ptr value\n");
                        loadloc_to_eax(sy);
                        fprintf(o_src,"\tmovl\t%%eax,%%ebx\n");
                        fprintf(o_src,"\tpopl\t%%eax\n");
                        fprintf(o_src,"\tmovl\t%%eax,0(%%ebx)\n");
                }
        }
}

void gen_loaddesc1( struct sym *sy, int variable_length ) {
        struct sym *var;
        var = sy;
        if (var->litflag == 2 || var->litflag == 4) {
                var = ((struct vref *)var)->sym;
                if (var->litflag == 2) {
                        var = ((struct vref *)var)->sym;
                }
        }
        if (sy->litflag == 4) {
                struct refmod * rflp = (struct refmod *)sy;
                struct sym * syl = rflp->len;
                if (syl == NULL) {
                        fprintf(o_src,"#  corrected length EOV\n");
                                value_to_eax(rflp->off);
                        fprintf(o_src,"\tnegl\t%%eax\n");
                        fprintf(o_src,"\taddl\t$%d, %%eax\n", symlen(var));
                        fprintf(o_src,"\tincl\t%%eax\n");
                        fprintf(o_src,"\tmovl\t%%eax, rf_base%d+%d\n", 
                                pgm_segment, rflp->slot*8);
                }
                else {
                   fprintf(o_src,"#  corrected length %s\n",syl->name);
                   if (syl->litflag == 1) {
                        /* the statement below does not always work if the literal
                           begins with a zero: as thinks it is an octal number.
                                We should really convert the "name" into a proper
                           value. (See bug #704519)*/
                           /*fprintf(o_src,"\tmovl\t$%s, rf_base%d+%d\n", 
                                           syl->name,pgm_segment, rflp->slot*8);*/
                           value_to_eax(syl);
                           fprintf(o_src,"\tmovl\t%%eax, rf_base%d+%d\n", 
                                           pgm_segment, rflp->slot*8);
                        }
                   else {
                           value_to_eax(syl);
                           fprintf(o_src,"\tmovl\t%%eax, rf_base%d+%d\n", 
                                           pgm_segment, rflp->slot*8);
                   }
                }
/*                fprintf(o_src,"\tmovl\t$'%c', rf_base%d+%d\n", 'G', */
                fprintf(o_src,"\tmovl\t$'%c', rf_base%d+%d\n", 'X', 
                        pgm_segment, rflp->slot*8+4);
                fprintf(o_src,"\tmovl\t$rf_base%d+%d, %%eax\n", 
                        pgm_segment, rflp->slot*8);
        }
/*
        // FIXME: This code does NOT work properly, for some reason.
        // When the INITIALIZE verb is used with an OCCURS ... DEPENDING clause,
        // it will cause a run-time seg fault in the 'tcob_adjust_length' 
        // (adjust_desc_length) function.
        // An easy fix is to INITIALIZE the array from 1 TO MAX value.
        // This is a code equivalent to a OCCURS N TIMES clause. 
        else {
        // adjust its length if there is a variable size item inside 
        if (variable_length && (get_variable_item(sy) != NULL)) {
                adjust_desc_length(sy);
        }
*/
        else {
#ifdef DEBUG_COMPILER
                        fprintf(o_src,"\tmovl\t%s, %%eax\t# descriptor of [%s]\n",
                                memrefd(var),sch_convert(var->name));
#else
                        fprintf(o_src,"\tmovl\t%s, %%eax\n",memrefd(var));
#endif
        }
        push_eax();
}

void gen_loadval( struct sym *sy ) {
        unsigned base,locoff;
        struct sym *var;
        struct sym *tmp = sy;
        
#ifdef DEBUG_COMPILER
        fprintf(o_src,"#gen_loadval\n");
#endif        
        if (sy == NULL) {
                hterror(104,8,"*** fatal error: variable undefined!\n");
                return;
        }
        if (sy->litflag == 2) {
                gen_subscripted( (struct vref *)sy );
                var = (struct sym *)((struct vref *)sy)->sym;
                if (var->linkage_flg) {
                   tmp=var;
                   while (tmp->linkage_flg==1) tmp=tmp->parent;
                   if (tmp==0)
                           yyerror("linkage section broken");
                   base = tmp->linkage_flg;
                   locoff = tmp->uval2.location - var->uval2.location;
/*
                   //  FIXME or find a better hack !!
                   //  Memory for LINKAGE SECTION identifiers is defined on the STACK.
                   //  However it can contain pointers to the data, or the actual data. 
                   //  For example, when a 'PROCEDURE DIVISION ... RETURNING identifier-n' 
                   //  clause is used, identifier-n is defined in the LINKAGE SECTION.
                   //  The contents of identifier-n is defined on the STACK.
                   //  For example, when a 'PROCEDURE DIVISION USING ... identifier-n ...' 
                   //  clause is used, identifier-n is defined in the LINKAGE SECTION.
                   //  A pointer to the contents of identifier-n is defined on the STACK,
                   //  as defined by the calling program.
                   //  When the variable 'linkage_flg' contains a positive value, it is assumed
                   //  to be defined by the calling program, and contains a pointer to the data.
                   //  When the 'linkage_flg' variable contains a negative value, it is assumed
                   //  to be defined within the program, and contains the actual data.
                   //  
*/
/*
                // if (symlen(var)>=4)
                //    fprintf(o_src,"\tmovl\t%d(%%ebp), %%ebx\n", base);
                // else
                //    fprintf(o_src,"\tmovs%cl %d(%%ebp), %%ebx\n", varsize_ch(var), base);
                // if (locoff)
                //    fprintf(o_src,"\taddl\t$%d, %%ebx\n",locoff);
                // fprintf(o_src,"\taddl\t%%eax, %%ebx\n");
                // fprintf(o_src,"\tmovl\t%%ebx, %%eax\n");
*/
                   if (tmp->linkage_flg > 0) {
                      if (symlen(var)>=4) 
                         fprintf(o_src,"\tmovl\t%d(%%ebp), %%ebx\n", base);
                      else
                         fprintf(o_src,"\tmovs%cl %d(%%ebp), %%ebx\n", varsize_ch(var), base);
                      if (locoff)
                         fprintf(o_src,"\taddl\t$%d, %%ebx\n", locoff);
                      fprintf(o_src,"\taddl\t%%eax, %%ebx\n");
                      fprintf(o_src,"\tmovl\t%%ebx, %%eax\n");
                   }
                   else {
                      if (symlen(var)>=4) {
                         fprintf(o_src,"\tmovl\t%%ebp, %%ebx\n");
                         fprintf(o_src,"\taddl\t$%d, %%ebx\n", base);
                      }
                      else {
/*                         fprintf(o_src,"\tmovs%cl %d(%%ebp), %%ebx\n", varsize_ch(var), base); */
                         fprintf(o_src,"\tmovl\t%%ebp, %%edx\n");
                         fprintf(o_src,"\taddl\t$%d, %%edx\n", base);
                         fprintf(o_src,"\tmovs%cl %%edx, %%ebx\n", varsize_ch(var));
                      }
                      if (locoff)
                         fprintf(o_src,"\taddl\t$%d, %%ebx\n", locoff);
                      fprintf(o_src,"\taddl\t%%eax, %%ebx\n");
                      fprintf(o_src,"\tmovl\t%%ebx, %%eax\n");
                   }
                   tmp = var;
                }
                else {
                   fprintf(o_src,"\tleal\t%s, %%ebx\n", memrefat(var));
                   fprintf(o_src,"\taddl\t%%ebx,%%eax\n");
                   tmp = var;
                }
        }
        else if (sy->litflag==0) {
                tmp = sy;
                load_address( tmp );
        }
        if (tmp->type == DTYPE_DISPLAY) {
                value_to_eax_at_eax(tmp);
                return;
                }
        if (sy->litflag==1)
                value_to_eax(sy);
        else
                load_at_eax(tmp);
}

void gen_pushval( struct sym *sy ) {
        unsigned base,locoff;
        struct sym *var,*tmp;
        if (sy == NULL) {
                hterror(104,8,"*** fatal error: variable undefined!\n");
                return;
        }
        if (sy->litflag == 2) {
                gen_subscripted( (struct vref *)sy );
                var = (struct sym *)((struct vref *)sy)->sym;
                if (var->linkage_flg) {
                        tmp=var;
                        while (tmp->linkage_flg==1) tmp=tmp->parent;
                        if (tmp==0)
                                yyerror("linkage section broken");
                        base = tmp->linkage_flg;
                        locoff = tmp->uval2.location - var->uval2.location;
/*
                        //  FIXME or find a better hack !!
                        //  Memory for LINKAGE SECTION identifiers is defined on the STACK.
                        //  However it can contain pointers to the data, or the actual data. 
                        //  For example, when a 'PROCEDURE DIVISION ... RETURNING identifier-n' 
                        //  clause is used, identifier-n is defined in the LINKAGE SECTION.
                        //  The contents of identifier-n is defined on the STACK.
                        //  For example, when a 'PROCEDURE DIVISION USING ... identifier-n ...' 
                        //  clause is used, identifier-n is defined in the LINKAGE SECTION.
                        //  A pointer to the contents of identifier-n is defined on the STACK,
                        //  as defined by the calling program.
                        //  When the variable 'linkage_flg' contains a positive value, it is assumed
                        //  to be defined by the calling program, and contains a pointer to the data.
                        //  When the 'linkage_flg' variable contains a negative value, it is assumed
                        //  to be defined within the program, and contains the actual data.
                        //  
*/
                        if (symlen(var)>=4) {
/*                         fprintf(o_src,"\tmovl\t%d(%%ebp), %%ebx\n",  base); */
                           if (tmp->linkage_flg > 0) {
                              fprintf(o_src,"\tmovl\t%d(%%ebp), %%ebx\n", base);
                           }
                           else {
                              fprintf(o_src,"\tmovl\t%%ebp, %%ebx\n");
                              fprintf(o_src,"\taddl\t$%d, %%ebx\n", base);
                           }
                        }
                        else {
/*                         fprintf(o_src,"\tmovs%cl\t%d(%%ebp), %%ebx\n", varsize_ch(var), base); */
                           if (tmp->linkage_flg > 0) {
                              fprintf(o_src,"\tmovs%cl\t%d(%%ebp), %%ebx\n", varsize_ch(var), base);
                           }
                           else {
                              fprintf(o_src,"\tmovl\t%%ebp, %%edx\n");
                              fprintf(o_src,"\taddl\t$%d, %%edx\n", base);
                              fprintf(o_src,"\tmovs%cl\t%%edx, %%ebx\n", varsize_ch(var));
                           }
                        }
                        if (locoff) {
                           fprintf(o_src,"\taddl\t$%d, %%ebx\n",locoff);
                        }
                        fprintf(o_src,"\taddl\t%%eax, %%ebx\n");
                        push_ebx();
                }
                else {
                        fprintf(o_src,"\tleal\t-%d(%%ebp), %%ebx\n", var->uval2.location);
                        fprintf(o_src,"\taddl\t%%ebx,%%eax\n");
                        push_at_eax(var);
                }
        }
        else if (sy->litflag==0) {
                load_address( sy );
                push_at_eax(sy);
        }
        else {
                /*value_to_eax(sy);*/
        } 
}

void gen_store_fnres(struct sym *sy) {
   struct sym *sy1;

   /* 
    CALL return value is stored in register 'eax'.
    If return variable given, move return value to variable.
    If return variable not given, move return value to RETURN-CODE.  
   */
   if (sy == NULL) {
      if ((sy1 = lookup(SVAR_RETURN_CODE, SYTB_VAR)) != NULL) {
#ifdef DEBUG_COMPILER
         fprintf(o_src, "# Use 'RETURN-CODE' to set the return value in register eax\n");
#endif
         if (sy1->sec_no == SEC_STACK) {
            fprintf(o_src,"\tleal\t-%d(%%ebp), %%edx\n", sy1->uval2.location);
         }
         else {
            /* fprintf(o_src,"\tleal\tw_base%d+%d, %%edx\n", pgm_segment, sy1->uval2.location); */
            /* char *vname = convert_variable_name(sy1); */
            if (sy1->offset_mloc == 0) 
               /* fprintf(o_src,"\tleal\t%s.%d, %%edx\n", vname, pgm_segment); */
               fprintf(o_src,"\tleal\tw_base%d_%d, %%edx\n", pgm_segment, sy1->uval2.location);
            else 
               /* fprintf(o_src,"\tleal\t%s.%d+%d, %%edx\n", vname, pgm_segment, sy1->uval2.location - sy1->offset_mloc);*/
               fprintf(o_src,"\tleal\tw_base%d_%d+%d, %%edx\n", pgm_segment, sy1->offset_mloc, sy1->uval2.location - sy1->offset_mloc);
         }
         fprintf(o_src,"\tmovl\t%%eax, (%%edx)\n");
      }
   }
   else {
#ifdef DEBUG_COMPILER
      fprintf(o_src, "# Use '%s' to set the return value in register eax\n", sy->name);
#endif
      switch(sy->type) {
      case DTYPE_BININT:
         switch(symlen(sy)) {
         case 4:
            fprintf(o_src, "\tmovl\t%%eax, %s\n", memrefat(sy));
            break;
         case 2:
            fprintf(o_src, "\tmov\t%%ax, %s\n", memrefat(sy));
            break;
         };
         break;
      default:
         break;
      };        
   }
}

/* The following functions will be activated when we change from
   defining the outermost group to define each elementary item. */
/*void init_field_val( struct sym *sy ) {
        struct lit *val=(struct lit *)sy->value;
        / *if (val->type != 'X' || sy->type != 'X' || val->nick != NULL) {* /
                / * can't call gen_move passing a NULL pointer! 
                   This happens because it is a PROCEDURE DIVISION USING VAR ...* /
        / *        if (val != NULL)
                        gen_move_init((struct sym *)val,sy);
        / *}* /
/ *}*/

void def_field_storage(struct sym *sy, int fld_len) 
{
/*
  char *vname;

  struct lit *val=(struct lit *)sy->value;
  int vlen;

  if (val == NULL || 
          val->type != 'X' || sy->type != 'X' || val->nick != NULL) {
                  fprintf(o_src,"\t.space\t%d\n",fld_len);
  }
  else {
          vlen = strlen(val->name);
          if (vlen < fld_len) {
             emit_lit( val->name, vlen );
             fprintf(o_src,"\n");
             emit_lit_fill( ' ', fld_len - vlen );
             fprintf(o_src,"\n");
          }
          else {
             emit_lit( val->name, fld_len );
             fprintf(o_src,"\n");
          }
  }
*/

  fprintf(o_src,"\t.space\t%d\n", fld_len);
/*
  // Define space allocation 
  // .local IDX.1
  // .comm IDX.1,4
  
  vname = convert_variable_name(sy);
  fprintf(o_src,"\t.local\t%s.%d\n\t.comm\t%s.%d,%d\n", vname, pgm_segment, vname, pgm_segment, fld_len);
*/
}

char *convert_variable_name(struct sym *sy)
{
  static char vname[PATHMAX3 + 1];
  char *pt;
  int i, j=0, vlen;

  vlen = strlen(sy->name);
  pt = sy->name;
  vname[0] = '\0';
  for (i=0; i<vlen; i++) {
     if (*pt == CHR_DASH) {
        strcat(vname, TCOB_STR_DASH_REDEFINE);
        j = j + 3;
     }
     else {
        vname[j] = *pt;
        j++;
        vname[j] = '\0';
     }
     pt++;        
  }
  return vname;
}

void gen_set( struct sym *idx, int which, struct sym *var,
        int adrof_idx, int adrof_var ) {
        struct vref *ref;
        struct vrange *vr;
        struct sym *sy=idx;

        if (idx->litflag == 4)
                sy = ((struct refmod *)idx)->sym;
        else if (idx->litflag == 2) 
                sy = (struct sym *)((struct vref *)idx)->sym;
        
        if (sy->type == '8') { /* conditional? */
                vr=sy->refmod_redef.vr;
/*
   If 88 level value has more than one entry,
   default to first value entry.
   
                if ((vr!=NULL) || (sy->uval4.value2 != sy->value)) {
                        yyerror("conditional is not unique");
                        return;
                }
*/
                if (idx->litflag==2) {
                        ref=malloc(sizeof(struct vref));
                        ref->litflag = 2;
                        ref->sym = sy->parent;
                        ref->next = ((struct vref *)idx)->next;
                        gen_move((struct sym *)sy->value,(struct sym *)ref);
                        free(ref);
                        ref=NULL;
                }
                else {
                        gen_move((struct sym *)sy->value,sy->parent);
                }
                return;
        }
        /* we are setting a value to true but is not a level 88 */
        if ((int)var == 1){
                yyerror("not a level 88 '%s'",sy->name);
                return;
        }

        if (sy->type == DTYPE_BININT && sy->ix_desc != NULL) { /* switch? */
                gen_set_switch(var, sy);
                return;
        }

        if (sy->flags.is_pointer || adrof_idx) { /* pointer? */ 
#ifdef DEBUG_COMPILER
                fprintf(o_src,"# set %s to %s\n",idx?idx->name:"(null)",
                        var?var->name:"(null)");
                fprintf(o_src,"# adrof_idx: %d, adrof_var: %d\n",
                        adrof_idx, adrof_var);
#endif
                if (which != SET_TO) {
                        yyerror("only SET TO work with pointers");
                        return;
                }
                if (adrof_idx && !(idx->linkage_flg)) {
                        yyerror("only linkage variables may be set to a new address");
                        return;        
                }
                if (adrof_var) {
                        /*load_location(var,"eax");*/
                        loadloc_to_eax(var);
                        set_ptr(idx);
                } 
                else {
                        /* value_to_eax(var); <-- this is not working! */
                        if (var == NULL) {
                                fprintf(o_src,"\txorl\t%%eax,%%eax\n");
                        } 
                        else {
                                load_location(var,"ebx");
                                fprintf(o_src,"\tmovl\t0(%%ebx),%%eax\n");
                        }
                        set_ptr(idx);
                }
                return;
        }

        /******** it is not a pointer, so must be an index ********/
        
        /* first get the second operand */
        /* if (idx->type != DTYPE_BININT) { */
        if (sy->type != DTYPE_BININT) {
                gen_set_complex(var, which, idx);
                return;
        }
#ifdef DEBUG_COMPILER
        fprintf(o_src,"# SET %s \n",idx->name);
#endif
        
        if (symlen(idx) > 4) 
                yywarn("index variable truncated to long");
        
        gen_loadval(var);

        switch (which) {
            case SET_TO: /* just move this value */
                fprintf(o_src,"\tmov%c\t%%eax, %s\n",
                        varsize_ch(idx),memrefat(idx));
                break;
            case SET_UP_BY: /* we need to add this value to the index */
                fprintf(o_src,"\tadd%c\t%%eax, %s\n",
                        varsize_ch(idx),memrefat(idx));
                break;        
            case SET_DOWN_BY:
                fprintf(o_src,"\tsub%c\t%%eax, %s\n",
                        varsize_ch(idx),memrefat(idx));
                break;
            default: 
                yyerror("SET option unavailable");
        }
}

int
push_selection_subject_copy ( int level, struct selsubject *ssbj, 
                int stkadd, int objtype ) {
        struct selsubject *p;

        /* find the target subject */
        while (level--)
          ssbj=ssbj->next;

        /* calculate the subject address */
        for (p=ssbj->next; p; p=p->next) {
                if (ssbj->type == SSUBJ_EXPR) {
                        stkadd += 8;
                }
                else if (ssbj->type == SSUBJ_COND) {
                        stkadd += 4;
                }
        }

        /* push expressions to the stack, conditions in %eax */
        switch (ssbj->type) {
        case SSUBJ_COND:
                fprintf(o_src,"\tmovl        %d(%%esp),%%eax\n",stkadd);
                break;
        case SSUBJ_EXPR:
                fprintf(o_src,"\tpushl        %d(%%esp)\n",stkadd+4);
                fprintf(o_src,"\tpushl        %d(%%esp)\n",stkadd+4);
                break;
        case SSUBJ_STR:
                gen_loadvar(ssbj->var);
                break;
        case FALSE:
                return 1;
        }
        return 0;
}

void gen_when_check( int level, struct selsubject *ssbj, int type, 
        int endcase, struct sym *var) {
        int invert=0;
        int stkadd=0;
        int cleanup,bypass;
        fprintf(o_src,"# WHEN check: level=%d, subject->type=%d, object type=%d\n",
                level, ssbj->type, type);
        stkadd += selection_object_size(type);

        /* check if compatible subject/object found */
        switch (selection_subject_type(level,ssbj)) {
        case SSUBJ_STR:
                if ((type!=SOBJ_STR)&&(type!=SOBJ_NEGSTR)&&(type!=SOBJ_ANY)) {
                                yyerror("incompatible selection object");
                }
                break;
        case SSUBJ_EXPR:
                if ((type!=SOBJ_EXPR)&&(type!=SOBJ_NEGEXPR)&&
                        (type!=SOBJ_RANGE)&&(type!=SOBJ_NEGRANGE)&&
                        (type!=SOBJ_COND)&&(type!=SOBJ_NEGCOND)&&
                        (type!=SOBJ_ANY)) {
                                yyerror("incompatible selection object");
                }
                break;
        case SSUBJ_COND:
                if ((type!=SOBJ_TRUE)&&(type!=SOBJ_FALSE)&&
                        (type!=SOBJ_ANY)) {
                                yyerror("incompatible selection object");
                }
                break;
        case SSUBJ_FALSE:
                invert=1;
        case SSUBJ_TRUE:
                if ((type!=SOBJ_COND)&&(type!=SOBJ_NEGCOND)&&
                        (type!=SOBJ_ANY)) {
                                yyerror("incompatible selection object");
                }
        }
        
        /* perform the actual tests */
        switch (type) {
        case SOBJ_STR:
        case SOBJ_NEGSTR:
                fprintf(o_src,"# SOBJ_STR or SOBJ_NEGSTR\n");
                push_selection_subject_copy(level,ssbj,stkadd,type);
                gen_loadvar(var);
                asm_call("tcob_compare");
                fprintf(o_src,"\tand\t%%eax,%%eax\n"); /* equal */
                if (type == SOBJ_STR) 
                        fprintf(o_src,"\tjnz\t.L%d\n",endcase);
                else
                        fprintf(o_src,"\tjz\t.L%d\n",endcase);
                break;
        case SOBJ_EXPR:
        case SOBJ_NEGEXPR:
                fprintf(o_src,"# SOBJ_EXPR or SOBJ_NEGEXPR\n");
                push_selection_subject_copy(level,ssbj,stkadd,type);
                gen_compare_exp(EQUAL);        
                if (type == SOBJ_EXPR) 
                        fprintf(o_src,"\tjnz\t.L%d\n",endcase);
                else
                        fprintf(o_src,"\tjz\t.L%d\n",endcase);
                break;
        case SOBJ_RANGE:
        case SOBJ_NEGRANGE:
                cleanup = loc_label++;
                bypass = loc_label++;
                fprintf(o_src,"# SOBJ_RANGE or SOBJ_NEGRANGE\n");
                push_selection_subject_copy(level,ssbj,stkadd,type);
                gen_compare_exp(LESS);
                if (type == SOBJ_RANGE) 
                        fprintf(o_src,"\tjz\t.L%d\n",cleanup);
                else
                        fprintf(o_src,"\tjnz\t.L%d\n",cleanup);
                stkadd -= 8;
                push_selection_subject_copy(level,ssbj,stkadd,type);
                gen_compare_exp(GREATER);
                if (type == SOBJ_RANGE) 
                        fprintf(o_src,"\tjz\t.L%d\n",endcase);
                else
                        fprintf(o_src,"\tjnz\t.L%d\n",endcase);
                /* cleanup unused double at stack */
                fprintf(o_src,"\tjmp\t.L%d\n",bypass); 
                fprintf(o_src,".L%d:\taddl\t$8, %%esp\n",cleanup);
                fprintf(o_src,"\tjmp\t.L%d\n",endcase); 
                fprintf(o_src,".L%d:\n",bypass);
                break;
        case SOBJ_COND:
        case SOBJ_NEGCOND:
                /*invert=push_selection_subject_copy(level,ssbj,stkadd,type);*/
                if (type == SOBJ_COND) 
                        fprintf(o_src,"\tjnz\t.L%d\n",endcase);
                else
                        fprintf(o_src,"\tjz\t.L%d\n",endcase);
                break;
        case SOBJ_ANY: /* no tests needed, just accept */
                break;
        case SOBJ_TRUE:
                invert=push_selection_subject_copy(level,ssbj,stkadd,type);
                fprintf(o_src,"\tand\t%%eax,%%eax\n");
                if (invert)
                        fprintf(o_src,"\tjz\t.L%d\n",endcase);
                else
                        fprintf(o_src,"\tjnz\t.L%d\n",endcase);
                break;
        case SOBJ_FALSE:
                invert=push_selection_subject_copy(level,ssbj,stkadd,type);
                fprintf(o_src,"\tand\t%%eax,%%eax\n");
                if (invert)
                        fprintf(o_src,"\tjnz\t.L%d\n",endcase);
                else
                        fprintf(o_src,"\tjz\t.L%d\n",endcase);
                break;
        }
}

void gen_bypass_when_case( int bypass ) {
        if (bypass) {
                fprintf(o_src,".L%d:\n",bypass);
        }
}

int gen_end_when( int n, int endcase, int sentence ) {
        int lab;
        if (sentence) {
                fprintf(o_src,"\tjmp\t.L%d\t# end WHEN\n",n);
                lab = 0;
        } else {
                lab = loc_label++;
                fprintf(o_src,"\tjmp\t.L%d\t# bypass WHEN test\n",lab);
        }
        fprintf(o_src,".L%d:\n",endcase);
        return lab;
}

void push_condition() {
        fprintf(o_src,"\tpushl\t%%eax\t# push_condition\n");
}

void gen_goto_depending( struct list *l, struct sym *sy ) {
        struct list *tmp;
         struct sym *var;

        var = sy;
        if (var->litflag == 2 || var->litflag == 4) {
                var = ((struct vref *)var)->sym;
                if (var->litflag == 2)
                        var = ((struct vref *)var)->sym;
        }
        if (!HTG_libcob) 
           gen_loadloc( sy );
        gen_loaddesc( sy );

        asm_call("tcob_get_index"); /* this will return %eax with var's value */
        for (tmp=l;tmp!=NULL;tmp=tmp->next) {
                fprintf(o_src,"\tdecl\t%%eax\n");
                fprintf(o_src,"\tjz\t.LB_%s\n",label_name((struct sym *)tmp->var));
        }
        free_list(l);
}

void gen_goto( struct list *l ) {
        struct sym *sy = (struct sym *)l->var;
        if (inner_stack_size) {
                fprintf(o_src,"\taddl\t$%d, %%esp\n",inner_stack_size);
        }
        fprintf(o_src,"\tjmp\t.LB_%s\n",label_name(sy));
        if (l->next) {
                yyerror("GOTO only allows one target");
        }
        free_list(l);
}

int gen_check_zero() {
        int i=loc_label++;
        fprintf(o_src,"\tand\t%%eax,%%eax\n");
        fprintf(o_src,"\tjz\t.L%d\n",i);
        stabs_line();
        return i;
}

unsigned long gen_at_end( int status ) {
        int i,j;
        union label_def label;
        i=loc_label++;
        j=loc_label++;

        fprintf(o_src,"\tcmp\t$%d, %%eax\n",status);
        fprintf(o_src,"\tjz\t.L%d\n",j);
        fprintf(o_src,"\tjmp\t.L%d\n",i);

/*         fprintf(o_src,"L%d:\n",j); */
        fprintf(o_src,"\t.align 16\n");
        fprintf(o_src,".L%d:\n",j);

        stabs_line();
        label.l.n = i;
        label.l.off = label.l.defined = 0;
        return label.x;
}

unsigned long gen_testif( void ) {
        int i,j;
        union label_def label;
        i=loc_label++;
        j=loc_label++;
        fprintf(o_src,"\tjz\t.L%d\n",j);
        fprintf(o_src,"\tjmp\t.L%d\n",i);

/*         fprintf(o_src,"L%d:\n",j); */
        fprintf(o_src,"\t.align 16\n");
        fprintf(o_src,".L%d:\n",j);

    stabs_line(); 

        label.l.n = i;
        label.l.off = label.l.defined = 0;
        return label.x;
}

void gen_not( void ) {
        int i,j;
        i=loc_label++;
        j=loc_label++;

        fprintf(o_src,"\tjz\t.L%d\n",i);
        fprintf(o_src,"\txorl\t%%eax,%%eax\n");
        fprintf(o_src,"\tjmp\t.L%d\n",j);
        fprintf(o_src,".L%d:\tincl\t%%eax\n",i);

/*         fprintf(o_src,"L%d:\n",j); */
        fprintf(o_src,"\t.align 16\n");
        fprintf(o_src,".L%d:\n",j);

        stabs_line(); 
}

unsigned long gen_andstart( void ) {
        int i;
        union label_def label;
        i=loc_label++;
        fprintf(o_src,"\tjnz\t.L%d\n",i);
        label.l.n = i;
        label.l.off = label.l.defined = 0;
        return label.x;
}

unsigned long gen_orstart( void ) {
        int i;
        union label_def label;
        i=loc_label++;
        fprintf(o_src,"\tjz\t.L%d\n",i);
        label.l.n = i;
        label.l.off = label.l.defined = 0;
        return label.x;
}

void gen_dstlabel( unsigned long lbl ) {
        char slab[32];
        union label_def label;
        label.x = lbl;
        sprintf( slab,".L%d",label.l.n );
        fprintf(o_src,".L%d:\n",label.l.n);
    stabs_line(); 
}

unsigned long gen_passlabel( void ) {
        int i;
        union label_def label;
        i=loc_label++;
        fprintf(o_src,"\tjmp\t.L%d\n",i);
        label.l.off = label.l.defined = 0;
        label.l.n = i;
        return label.x;
}

unsigned long gen_marklabel( void ) {
        int i;
        union label_def label;
        i=loc_label++;
        fprintf(o_src,".L%d:\n",i);
    stabs_line(); 
        label.l.defined = 1;
        label.l.n = i;
        return label.x;
}

void gen_jmplabel( unsigned long lbl ) {
        union label_def label;
        label.x = lbl;
        fprintf(o_src,"\tjmp\t.L%d\n",label.l.n);
}

void gen_push_int( struct sym *sy ) {
/*        gen_loadloc( sy ); */
/*/        fprintf(o_src,"\tmovl\t$c_base%d+%u, %%eax\n",
                  pgm_segment,sy->descriptor); */
        gen_loadvar(sy);
        asm_call("tcob_get_index");
        /* this must be done without calling push_eax */
        fprintf(o_src,"\tpushl\t%%eax\n");
}

void gen_perform_test_counter( unsigned long lbl ) {
        union label_def label;
        label.x = lbl;
        fprintf(o_src,"\tcmpl\t$0,0(%%esp)\n");
        fprintf(o_src,"\tjle\t.L%dE\n",label.l.n);
}

void gen_perform_times( unsigned long lbl ) {
        union label_def label;
        label.x = lbl;
        fprintf(o_src,"\tdecl\t0(%%esp)\n");
        fprintf(o_src,"\tjnz\t.L%d\n",label.l.n);
        fprintf(o_src,".L%dE:\tpopl\t%%ecx\n",label.l.n);
}

void gen_perform_thru( struct sym *s1, struct sym *s2 ) {
        /*stabs_block(0);*/
        if (s2 == NULL) 
            s2 = s1;
        fprintf(o_src,"\tleal\t.L%d, %%eax\n",loc_label);
        fprintf(o_src,"\tpushl\t%%eax\n");
        fprintf(o_src,"\tleal\t.LB_%s, %%eax\n",label_name(s1));
        fprintf(o_src,"\tpushl\t%%eax\n");
        fprintf(o_src,"\tleal\t.LE_%s, %%eax\n",label_name(s2));
/*        fprintf(o_src,"\tpushl\t%%ax\n");*/
        fprintf(o_src,"\tpushl\t%%eax\n");
        fprintf(o_src,"\tjmp\t.LB_%s\n",label_name(s1));

        fprintf(o_src,"\t.align 16\n");
        fprintf(o_src,".L%d:\n",loc_label++);
        /*stabs_block(1);*/
    /*stabs_line();*/
}

/* increment loop index, check for end */
void gen_SearchLoopCheck(unsigned long lbl5, struct sym *syidx, struct sym *sytbl)
{

   /*struct sym *sy1, *sy2;*/
   struct lit *v;
   char tblmax[21];

   strcpy(tblmax, "1");
   v = (struct lit *)install(tblmax,SYTB_LIT,0);
   save_literal(v, DTYPE_DISPLAY);

   gen_add((struct sym *)v, syidx, 0);

   sprintf(tblmax, "%d", sytbl->times);
   v = (struct lit *)install(tblmax,SYTB_LIT,0);
   save_literal(v, DTYPE_DISPLAY);

   gen_compare(syidx, GREATER, (struct sym *)v);
   fprintf(o_src,"\tjz\t.L%ld\n",lbl5);

   stabs_line(); 
}

void gen_SearchAllLoopCheck(unsigned long lbl3, struct sym *syidx, struct sym *sytbl, 
                            struct sym *syvar, unsigned long lstart, unsigned long lend)
{

   struct sym *sy1;
   struct vref *vr1;
   struct index_to_table_list *it1, *it2;
   unsigned long l1, l2, l3, l4, l5, l6;

   l1=loc_label++;
   l2=loc_label++;
   l3=loc_label++;
   l4=loc_label++;
   l5=loc_label++;
   l6=loc_label++;

   it1 = index2table;
   it2 = NULL;
   while (it1 != NULL) {
     if (strcmp(it1->tablename, sytbl->name) == 0) {
        it2 = it1;
        it1 = NULL;
     }
     else {
        it1 = it1->next;
     }
   }
   
   if (it2 == NULL ) {
      return;
   }

   if ((it2->seq != '1' ) && (it2->seq != '2' )) {
      return;
   }

#ifdef DEBUG_COMPILER
   if (it2->seq == '1') {
      fprintf(o_src,"#gen_SearchAllLoopCheck: sequence for table %s is %c=ASCENDING\n", 
              sytbl->name, it2->seq);
   }
   if (it2->seq == '2') {
      fprintf(o_src,"#gen_SearchAllLoopCheck: sequence for table %s is %c=DESCENDING\n", 
              sytbl->name, it2->seq);
   }
   fprintf(o_src,"#gen_SearchAllLoopCheck: l1=L%lu, l2=L%lu, l3=L%lu, l4=L%lu, l5=L%lu, l6=L%lu\n",
           l1, l2, l3, l4, l5, l6); 
#endif

   vr1 = create_subscript( syidx );
   sy1 = (struct sym *)create_subscripted_var(sytbl,  vr1); 

   /* table sort sequence: '0' = none, '1' = ASCENDING, '2' = DESCENDING */

   /*    if ((bu - bl) > 1) */
      fprintf(o_src,"\tmovl\t-%d(%%ebp), %%eax\n", stack_offset - 12);
      fprintf(o_src,"\tsubl\t-%d(%%ebp), %%eax\n", stack_offset - 8);

      fprintf(o_src,"\tcmpl\t$1, %%eax\n");
      fprintf(o_src,"\tjle .L%ld\n", l1);

      fprintf(o_src,"\t.align 16\n");

/*    if (itbl1 > in) { */ /* '2' = DESCENDING */
      if (it2->seq == '2') {
         gen_compare(sy1, GREATER, syvar);
         fprintf(o_src,"\tjnz\t.L%ld\n",l2);
      }
      else {
         gen_compare(sy1, LESS, syvar);
         fprintf(o_src,"\tjnz\t.L%ld\n",l2);
      }
      fprintf(o_src,"\t.align 16\n");

/*    bl  = idx + 1; */
/*    fprintf(o_src,"\tmovl\t-%d(%%ebp), %%eax\n", syidx->uval2.location); */
      fprintf(o_src,"\tmovl\t%s, %%eax\n", memrefat(syidx));
      fprintf(o_src,"\taddl\t$1, %%eax\n");
      fprintf(o_src,"\tmovl\t%%eax, -%d(%%ebp)\n", stack_offset - 8);

      gen_jmplabel(l3);           
      fprintf(o_src,"\t.align 16\n");

/*    else { */
      gen_dstlabel(l2);

/*    bu  = idx - 1; */
/*    fprintf(o_src,"\tmovl\t-%d(%%ebp), %%eax\n", syidx->uval2.location); */
      fprintf(o_src,"\tmovl\t%s, %%eax\n", memrefat(syidx));
      fprintf(o_src,"\tsubl\t$1, %%eax\n");
      fprintf(o_src,"\tmovl\t%%eax, -%d(%%ebp)\n", stack_offset - 12);

      gen_dstlabel(l3);

/*    idx = ((bu - bl)/2 + bl); */
      fprintf(o_src,"\tmovl\t-%d(%%ebp), %%eax\n", stack_offset - 12);
      fprintf(o_src,"\tsubl\t-%d(%%ebp), %%eax\n", stack_offset - 8);
      fprintf(o_src,"\tmovl\t%%eax, %%edx\n");
      fprintf(o_src,"\tsarl\t$31, %%edx\n");
      fprintf(o_src,"\tmovl\t%%edx, %%ecx\n");
      fprintf(o_src,"\tsarl\t$31, %%ecx\n");
      fprintf(o_src,"\tleal\t(%%ecx,%%eax), %%edx\n");
      fprintf(o_src,"\tmovl\t%%edx, %%eax\n");
      fprintf(o_src,"\tsarl\t$1, %%eax\n");
      fprintf(o_src,"\taddl\t-%d(%%ebp), %%eax\n", stack_offset - 8);
/*    fprintf(o_src,"\tmovl\t%%eax, -%d(%%ebp)\n", syidx->uval2.location); */
      fprintf(o_src,"\tmovl\t%%eax, %s\n", memrefat(syidx));

      gen_jmplabel(l6);
      fprintf(o_src,"\t.align 16\n");

/*    else { */ /* l1 */
      gen_dstlabel(l1);

      if (it2->seq == '2') {
/*       if (itbl1 > in) { */
         gen_compare(sy1, GREATER, syvar);
         fprintf(o_src,"\tjnz\t.L%ld\n",l4);
      }
      else {
/*       if (itbl1 < in) { */
         gen_compare(sy1, LESS, syvar);
         fprintf(o_src,"\tjnz\t.L%ld\n",l4);
      }
      fprintf(o_src,"\t.align 16\n");


/*    if (bu > idx) { */
/*    fprintf(o_src,"\tmovl\t-%d(%%ebp), %%eax\n", syidx->uval2.location); */
      fprintf(o_src,"\tmovl\t%s, %%eax\n", memrefat(syidx));
      fprintf(o_src,"\tcmpl\t%%eax, -%d(%%ebp)\n", stack_offset - 12);

      fprintf(o_src,"\tjle\t.L%ld\n",l5);
      fprintf(o_src,"\t.align 16\n");


/*    idx = bu; */
      fprintf(o_src,"\tmovl\t-%d(%%ebp), %%eax\n", stack_offset - 12);
/*    fprintf(o_src,"\tmovl\t%%eax, -%d(%%ebp)\n", syidx->uval2.location); */
      fprintf(o_src,"\tmovl\t%%eax, %s\n", memrefat(syidx));

      gen_jmplabel(l6);
      fprintf(o_src,"\t.align 16\n");

/*    else { */
      gen_dstlabel(l5);


/*    r++; */
      fprintf(o_src,"\taddl\t$1, -%d(%%ebp)\n", stack_offset - 4);

      gen_jmplabel(l6); 
      fprintf(o_src,"\t.align 16\n");

/*       } */
/*    } */
/*    else { */
      gen_dstlabel(l4);

/*    r++; */
      fprintf(o_src,"\taddl\t$1, -%d(%%ebp)\n", stack_offset - 4);

      gen_dstlabel(l6);

      fprintf(o_src,"\tmovl\t-%d(%%ebp), %%eax\n", stack_offset - 4);
      fprintf(o_src,"\tcmpl\t$1, %%eax\n");
      fprintf(o_src,"\tjz\t.L%ld\n",lbl3);


      gen_jmplabel(lstart);
      fprintf(o_src,"\t.align 16\n");
      gen_dstlabel(lend);  

      stabs_line(); 
}

void Initialize_SearchAll_Boundaries(struct sym *sy, struct sym *syidx) 
{
   int i;
   struct lit *v;
   char tblmax[21];
   struct index_to_table_list *i2t1, *i2t2;
        
   i = sy->times / 2;

   sprintf(tblmax, "%d", i);
   v = (struct lit *)install(tblmax,SYTB_LIT,0);
#ifdef DEBUG_COMPILER
   if (v->type) { /* not already saved */
      fprintf(o_src,"#Initialize_SearchAll_Boundaries: literal is saved: %s\n", tblmax);
    }
    else {
      fprintf(o_src,"#Initialize_SearchAll_Boundaries: literal not saved: %s\n", tblmax);
    }
#endif

   save_literal(v, DTYPE_DISPLAY);
   gen_move((struct sym *)v, syidx);

   fprintf(o_src,"\tmovl\t$0, %%eax\n");
   fprintf(o_src,"\tmovl\t%%eax,-%d(%%ebp)\n", stack_offset - 4);

   fprintf(o_src,"\tmovl\t$1, %%eax\n");
   fprintf(o_src,"\tmovl\t%%eax,-%d(%%ebp)\n", stack_offset - 8);

   fprintf(o_src,"\tmovl\t$%d, %%eax\n", sy->times);
   fprintf(o_src,"\tmovl\t%%eax,-%d(%%ebp)\n", stack_offset - 12);

   i2t2 = NULL;
   i2t1 = index2table;
   while (i2t1 != NULL) {
     if ( strcmp(i2t1->tablename, sy->name) == 0) {
        if (i2t1->seq != '0') {
           i2t2 = i2t1;
        }        
        i2t1 = NULL;
     }
     else {
        i2t1 = i2t1->next;
     }
   }
   
   if (i2t2 == NULL) {
      yyerror("Undefined sort order and key for table");
   }
      
}

void resolve_labels() {
        struct sym *sy=NULL,*sy1=NULL,*sy2=NULL;
        int i,def;
        fprintf(o_src,"# resolving paragraphs/sections labels\n");
        for (i=0;i<HASHLEN;i++) {
                for (sy=labtab[i];sy!=NULL;sy=sy->next) {
                        fprintf(o_src,"## 1 %d,%d\n",HASHLEN,i);
                        
                        if (sy == NULL) continue;
                                
                        fprintf(o_src,"## 2\n");
                        fprintf(o_src,"## %s\n",sy->name);
                        if (sy->type == 'f') continue;
                        sy1 = sy;
                        while (sy1) {
                                if (sy1->defined == 2) {   /*Labels used but not defined */
                                        /*        fprintf(stderr,"%s of %s: used but not defined \n",sy1->name,(sy1->parent)?sy1->parent->name:NULL); */
                                        def=0;
                                        sy2 = sy;
                                        /* find if we have already defined the label on
                                           the same section (same parent) */
                                        while (sy2) {
                                                if ((sy2->defined == 1 ) && (sy1->parent ) && 
                                                    (sy2->parent) && (sy1->parent->name) && (sy2->parent->name)) { 
                                                    if(!strcmp(sy1->parent->name,sy2->parent->name)) {
                                                        def++;
                                                        /*fprintf(stderr,"%s of %s: found on the same section \n",sy2->name,(sy2->parent)?sy2->parent->name:NULL);*/
                                                        break;
                                                    }
                                                }
                                                sy2=sy2->clone;
                                        }
                                        /* find if defined on another section */
                                        if (!def) {
                                                sy2 = sy;
                                                /*fprintf(stderr,"%s of %s: look on the program\n",sy1->name,(sy1->parent)?sy1->parent->name:NULL); */
                                                while (sy2) {
                                                        /*fprintf(stderr,"%s of %s: compare with %s of %s\n",*/
                                                /*                sy1->name,(sy1->parent)?sy1->parent->name:NULL, */
                                                /*                sy2->name,(sy2->parent)?sy2->parent->name:NULL); */
                                                
                                                        /* look for it on another section or look if it is a
                                                           section  (not a paragraph) */
                                                        if ((sy2->defined == 1 && sy2->parent != sy1->parent) ||
                                                           (sy2->defined == 1 && sy2->parent == NULL && sy2->parent == NULL)){
                                                                /* If we have found it,  
                                                                   it needs a cast or the cast is incorrect */
                                                                if (def) {
                                                                        yyerror("procedure name not unique: %s",sy1->name);
                                                                } else {
                                                                  char pt01[256], pt02[256];
                                                                  strcpy(pt01, label_name(sy1));
                                                                  strcpy(pt02, label_name(sy2));
                                                                  if (strcmp(pt01, pt02) == 0) {
                                                                     fprintf(o_src,"##.LB_%s = ", label_name(sy1));
                                                                     fprintf(o_src,".LB_%s\n", label_name(sy2));
                                                                     fprintf(o_src,"##.LE_%s = ", label_name(sy1));
                                                                     fprintf(o_src,".LE_%s\n", label_name(sy2));
                                                                  }
                                                                  else {
                                                                     fprintf(o_src,".LB_%s = ", label_name(sy1));
                                                                     fprintf(o_src,".LB_%s\n", label_name(sy2));
                                                                     fprintf(o_src,".LE_%s = ", label_name(sy1));
                                                                     fprintf(o_src,".LE_%s\n", label_name(sy2));
                                                                  }
                                                                  def++;
                                                                }
                                                                /*break;*/
                                                        }
                                                        sy2=sy2->clone;
                                                } /* while sy2 */
                                        } /* if(!def) */
                                        if(!def) { /* really not defined, print an error */
                                                yyerror("undefined procedure: %s",sy1->name);
                                                
                                        }
                                                
                                } /* if (sy1->defined == 2) */
                                sy1=sy1->clone;
                        } /* while (sy1) */
                } /* for */
        } /* for */
        fprintf(o_src,"# finish resolving paragraphs/sections labels\n");
}

void open_section(struct sym *sect) {
     sect->type='S';
     fprintf(o_src,".LB_%s:\n",label_name(sect));
/*     fprintf(o_src,".LB_%s:\n",sect->name); */
     curr_section=sect;
#ifdef DEBUG_COMPILER_LEVEL1
     printf("# htcobemt.c: open_section: section=%s, HTG_debug_trace_flag=%d\n", sect->name, HTG_debug_trace_flag); 
#endif
     if (HTG_debug_trace_flag == TRUE) 
        gen_debug_trace(sect, TCB_DEBUG_TRACE_SECTION_ENTER);     

}

void close_section(void) {
        close_paragr();
        if (curr_section) {
#ifdef DEBUG_COMPILER_LEVEL1
        printf("# htcobemt.c: open_section: section=%s, HTG_debug_trace_flag=%d\n", curr_section->name, HTG_debug_trace_flag); 
#endif
          if (HTG_debug_trace_flag == TRUE) 
             gen_debug_trace(curr_section, TCB_DEBUG_TRACE_SECTION_EXIT);     
             fprintf(o_src,".LE_%s:\n",label_name(curr_section));
/*                fprintf(o_src,".LE_%s:\n",curr_section->name); */
             gen_exit(0);
        }
}

char * label_name ( struct sym *lab ) {
        if (lab->parent) { 
           sprintf(name_buf,"%s__%s_%d",
                   lab->name, lab->parent->name, pgm_segment);
           chg_underline(name_buf);
           /*fprintf(stderr,"# label_name: %s\n",name_buf);*/
           return name_buf;
        }
        sprintf(name_buf,"%s_%d",lab->name,pgm_segment);
        chg_underline(name_buf);
        /*fprintf(stderr,"# label_name: %s\n",name_buf);*/
        return name_buf;
}

void close_paragr(void) {
  if (curr_paragr) {
#ifdef DEBUG_COMPILER_LEVEL1
     printf("# htcobemt.c: close_paragr: para=%s, HTG_debug_trace_flag=%d\n", curr_paragr->name, HTG_debug_trace_flag); 
#endif
     if (HTG_debug_trace_flag == TRUE) 
        gen_debug_trace(curr_paragr,TCB_DEBUG_TRACE_PARAGRAPH_EXIT);     
     fprintf(o_src,".LE_%s:\n", label_name( curr_paragr ) );
     /*fprintf(o_src,".stabn\t192,0,0,.LB_%s-main\n",
             label_name( curr_paragr ));
     #if !defined(__WINDOWS__)
     fprintf(o_src,".stabn\t224,0,0,.LE_%s-main\n",
     #else
     fprintf(o_src,".stabn\t224,0,0,.LE_%s-_main\n",
     #endif
             label_name( curr_paragr ));*/
     gen_exit(0);
     curr_paragr=NULL;
  }
}

void open_paragr(struct sym *paragr) {
  paragr->type='P';
  curr_paragr=paragr;
  fprintf(o_src,".LB_%s:\n", label_name( paragr ) );
#ifdef DEBUG_COMPILER_LEVEL1
  printf("# htcobemt.c: open_paragr: para=%s, HTG_debug_trace_flag=%d\n", paragr->name, HTG_debug_trace_flag); 
#endif
  if (HTG_debug_trace_flag == TRUE) 
     gen_debug_trace(paragr, TCB_DEBUG_TRACE_PARAGRAPH_ENTER);     

}

void gen_debug_trace(struct sym *secpara, int type) {
  
  int idx, l1;
  struct sym *sy;

  idx = trace_display_install(secpara->name);
  l1 = loc_label++; /* by-pass label name */

  if ((sy = lookup(SVAR_TRACE_DISPLAY, SYTB_VAR)) != NULL) {
     if (sy->sec_no == SEC_STACK) {
        fprintf(o_src,"\tleal\t-%d(%%ebp), %%edx\n", sy->uval2.location);
        fprintf(o_src, "\tcmpl\t$1, (%%edx)\n");
        fprintf(o_src, "\tjne\t.L%d\n", l1);
        fprintf(o_src,"\tpushl\t$.LC%04d_%s\n", idx, pgm_label);

        switch (type)
        {
          case TCB_DEBUG_TRACE_SECTION_ENTER:
            fprintf(o_src,"\tpushl\t$.LC_DTENTER_%s\n", pgm_label);
            break;
    
          case TCB_DEBUG_TRACE_SECTION_EXIT:
            fprintf(o_src,"\tpushl\t$.LC_DTEXIT_%s\n", pgm_label);
            break;
    
          case TCB_DEBUG_TRACE_PARAGRAPH_ENTER:
            fprintf(o_src,"\tpushl\t$.LC_DTENTER_%s\n", pgm_label);
            break;
    
          case TCB_DEBUG_TRACE_PARAGRAPH_EXIT:
            fprintf(o_src,"\tpushl\t$.LC_DTEXIT_%s\n", pgm_label);
            break;
    
          default:
            break;
        }
        fprintf(o_src,"\tpushl\tstderr\n");
        fprintf(o_src,"\tcall\tfprintf\n");
        fprintf(o_src,"\taddl\t$12, %%esp\n");

        fprintf(o_src,".L%d:\n", l1);
     }
  }
} 

void gen_trace_stm(int traceSw)
{
  struct sym *sy;

  if (HTG_debug_trace_flag == FALSE) {
     /*yyerror("Display trace option is not enabled ...statement ignored");*/
     yywarn("Display trace option is not enabled ...statement ignored");
     return;
  }
  if ((sy = lookup(SVAR_TRACE_DISPLAY, SYTB_VAR)) != NULL) {
     if (sy->sec_no == SEC_STACK) {
        fprintf(o_src,"\tleal\t-%d(%%ebp), %%edx\n", sy->uval2.location);
        if (traceSw == 1) 
           fprintf(o_src, "\tmovl\t$1, (%%edx)\n");
        else 
           fprintf(o_src, "\tmovl\t$0, (%%edx)\n");
     }
  }
}

void gen_stoprun(void) {

        if ((main_flag == 1) && (main_entry_flag == FALSE))  {
            strcpy(main_entry_buf, pgm_label);
            main_entry_flag = TRUE;
        }

        if ((main_flag == 5) && (main_entry_flag == FALSE))  {
            strcpy(main_entry_buf, pgm_label);
            main_entry_flag = TRUE;
            main_flag = 2;
        }

        fprintf(o_src,"\tleal\t.Lend_pgm_%s, %%eax\n",pgm_label);
        fprintf(o_src,"\tpushl\t%%eax\n");
        fprintf(o_src,"\tjmp\t.Lend_pgm_%s\n",pgm_label);        
}

void gen_exit( int code ) {
        int l1,l2;
        struct list *list;
        struct sym *f;

        if (code) {
                if (initial_flag) {
                        /* ensure all files are closed and initialized */
                        for (list=files_list;list!=NULL;list=list->next) {
                                f=(struct sym *)list->var;
                                /* gen_save_filevar( f,NULL ); - removed unused char* record (NULL) */
                                gen_save_filedesc(f);
                                asm_call("tcob_file_init");
                                }
                        }
                        
/*
//                fprintf(o_src,"\tmovl\t-%d(%%ebp), %%ebx\n",stack_offset - 16);
                fprintf(o_src,"\tmovl\t-%d(%%ebp), %%ebx\n",stack_offset - 24);
                fprintf(o_src,"\tmov\t%%ebp,%%esp\n");
                fprintf(o_src,"\tpop\t%%ebp\n");
//                fprintf(o_src,"\tleave\n");
                fprintf(o_src,"\tret\n");
*/


                fprintf(o_src,"\tleal\t.Lend_pgm_%s, %%eax\n",pgm_label);
                fprintf(o_src,"\tpushl\t%%eax\n");
                fprintf(o_src,"\tjmp\t.Lend_pgm_%s\n",pgm_label);        


/*
                Temporary code for cobrun (modules)
                
                if ((main_flag == 1) && (main_entry_flag == FALSE))  {
                   strcpy(main_entry_buf, pgm_label);
                   main_entry_flag = TRUE;
                }
*/

        }
        else {
                /*fprintf(o_src,"\tleal\t.LE_%s, %%eax\n",label_name(curr_paragr));*/
                /*push_eax();*/
                /*asm_call("exit_paragraph");*/
                l1 = loc_label++;
                l2 = loc_label++;
                if (curr_paragr != NULL) {
                        fprintf(o_src,"\tleal\t.LE_%s, %%eax\n",label_name(curr_paragr));
                }
                else {
                        fprintf(o_src,"\tleal\t.LE_%s, %%eax\n",label_name(curr_section));
                }
                /*fprintf(o_src,"\tcmpl\t4(%%esp), %%eax\n");*/
                /*fprintf(o_src,"\tjb\t\t.L%d\n",l1);*/
                fprintf(o_src,"\tcmpl\t0(%%esp), %%eax\n");
                /*fprintf(o_src,"\tjb\t\t.L%d\n",l2);*/
                fprintf(o_src,"\tjne\t\t.L%d\n",l2);
                fprintf(o_src,".L%d:\n",l1);
                fprintf(o_src,"\taddl\t$8,%%esp\n");
                inner_stack_size = 0;
                fprintf(o_src,"\tret\n");
                fprintf(o_src,".L%d:\n",l2);
/*
                fprintf(o_src,"\tleal\t.Lend_pgm_%s, %%eax\n",pgm_label);
                fprintf(o_src,"\tpushl\t%%eax\n");
                fprintf(o_src,"\tjmp\t.Lend_pgm_%s\n",pgm_label);        
*/
        }
}

void gen_condition( struct sym *sy ) {
        struct vrange *vr;
        struct vref *ref;
        struct sym *sy1=sy;
        /*fprintf(o_src,"# 88 condition (top): (%s , %s)\n",
                sy->value->name,sy->uval4.value2->name);*/ 
        /* is this an indexed condition ? */
        if (sy->litflag == 2) {
                sy1 = (struct sym *)((struct vref *)sy)->sym;
        }
        gen_loadvar((struct sym *) NULL);        
        gen_loadvar((struct sym *)sy1->uval4.value2);
        gen_loadvar((struct sym *)sy1->value);
        vr=sy1->refmod_redef.vr;
        while (vr) {
                /*fprintf(o_src,"# 88 condition: (%s , %s)\n",
                        vr->value->name,vr->value2->name);*/ 
                gen_loadvar((struct sym *)vr->value2);
                gen_loadvar((struct sym *)vr->value);
                vr=vr->next;
        }
        if (sy->litflag==2) {
                /* alloc a tmp node for condition parent 
                   so gen_loadvar will be happy */
                ref=malloc(sizeof(struct vref));
                ref->litflag = 2;
                ref->sym = sy1->parent;
                ref->next = ((struct vref *)sy)->next;
                gen_loadvar((struct sym *)ref);
                free(ref);
                ref=NULL;
        }
        else {
                gen_loadvar(sy->parent);
        }
        asm_call("tcob_check_condition");
        fprintf(o_src,"\tand\t%%eax,%%eax\n");
}

/* compare for already stacked expressions */
void gen_compare_exp ( int value ) {
        stackframe_cnt += 16; /* must pop everything after comparing */
        asm_call("tcob_compare_doubles");
        switch (value) {
        case 0: fprintf(o_src,"\txor\t%%eax,%%eax\n\tinc\t%%eax\n"); /* false */
                break;
        case 1: fprintf(o_src,"\tand\t%%eax,%%eax\n"); /* equal */
                break;
        case 2: fprintf(o_src,"\tinc\t%%eax\n"); /* less */
                break;
        case 3: fprintf(o_src,"\tdec\t%%eax\n"); /* less or equal */
                gen_not();
                break;
        case 4:        fprintf(o_src,"\tdec\t%%eax\n"); /* greater */
                break;
        case 5: fprintf(o_src,"\tinc\t%%eax\n"); /* greater or equal */
                gen_not();
                break;
        case 6: fprintf(o_src,"\tand\t%%eax,%%eax\n"); /* not equal */
                gen_not();
                break;
        case 7:        fprintf(o_src,"\txor\t%%eax,%%eax\n"); /* true */
                break;
        }
}

void gen_compare( struct sym *s1, int value, struct sym *s2 ) {
        /* if any of sy1 or sy2 is an expression, we must 
                compare full expressions */
        if ((s1->litflag == 5) || (s2->litflag == 5)) {
                push_expr(s2);
                push_expr(s1);
                gen_compare_exp(value);
        }
        else {
                gen_loadvar(s2);
                gen_loadvar(s1);
                asm_call("tcob_compare");
                switch (value) {
                case 0: fprintf(o_src,"\txor\t%%eax,%%eax\n\tinc\t%%eax\n"); /* false */
                        break;
                case 1: fprintf(o_src,"\tand\t%%eax,%%eax\n"); /* equal */
                        break;
                case 2: fprintf(o_src,"\tinc\t%%eax\n"); /* less */
                        break;
                case 3: fprintf(o_src,"\tdec\t%%eax\n"); /* less or equal */
                        gen_not();
                        break;
                case 4:        fprintf(o_src,"\tdec\t%%eax\n"); /* greater */
                        break;
                case 5: fprintf(o_src,"\tinc\t%%eax\n"); /* greater or equal */
                        gen_not();
                        break;
                case 6: fprintf(o_src,"\tand\t%%eax,%%eax\n"); /* not equal */
                        gen_not();
                        break;
                case 7:        fprintf(o_src,"\txor\t%%eax,%%eax\n"); /* true */
                        break;
                }
        }
}

int
push_subexpr( struct sym *sy ) {
        if (sy==NULL)
                return 0;
        /* generate code to compute expr */
        if (sy->litflag==5) { 
                push_subexpr((struct sym *)((struct expr *)sy)->left);
                push_subexpr((struct sym *)((struct expr *)sy)->right);
                switch (((struct expr *)sy)->op) {
                case '+': add_expr(); break;
                case '-': subtract_expr(); break;
                case '*': multiply_expr(); break;
                case '/': divide_expr(); break;
                case '^': pow_expr(); break;
                default: yyerror("unknown expression operator");
                }
        }
        /* sy is really a symbol, not expr */
        else { 
#ifdef DEBUG_COMPILER
                fprintf(o_src,"# push_subexpr: %s\n",sy->name);
#endif
                if (sy) {  /*only if not yet pushed*/ 
                        if (is_numeric_sy(sy)) {
                                fprintf(o_src,"\tsubl\t$%d, %%esp\n",sizeof(double));
                                fprintf(o_src,"\tleal\t0(%%esp),%%eax\n");
                                push_eax();
                                gen_loadvar( sy );
                                asm_call("tcob_fldtod");
                        }
                        else {
                                return 0;
                        }
                }
        }
        return 1;
}

void add_expr( void ) {
        fprintf(o_src,"\tleal\t8(%%esp),%%eax\n");
        push_eax();
        asm_call("tcob_add_double");
        fprintf(o_src,"\taddl\t$8, %%esp\n");
}

void subtract_expr( void ) {
        fprintf(o_src,"\tleal\t8(%%esp),%%eax\n");
        push_eax();
        asm_call("tcob_subtract_double");
        fprintf(o_src,"\taddl\t$8, %%esp\n");
}

void multiply_expr( void ) {
        fprintf(o_src,"\tleal\t8(%%esp),%%eax\n");
        push_eax();
        asm_call("tcob_multiply_double");
        fprintf(o_src,"\taddl\t$8, %%esp\n");
}

void divide_expr( void ) {
        fprintf(o_src,"\tleal\t8(%%esp),%%eax\n");
        push_eax();
        asm_call("tcob_divide_double");
        fprintf(o_src,"\taddl\t$8, %%esp\n");
}

void pow_expr( void ) {
        fprintf(o_src,"\tleal\t8(%%esp),%%eax\n");
        push_eax();
        asm_call("tcob_pow_double");
        fprintf(o_src,"\taddl\t$8, %%esp\n");
}

void gen_save_filevar(struct sym *f, struct sym *buf) 
{
  if (!(f->uval6.recordsym)) { 
     yyerror("No FD/SD for file %s\n", f->name);
     return;
  }                
  
  if (buf != NULL) {
     gen_loadloc(buf);
     /* gen_loaddesc(buf); */
  }
  else {
#ifdef DEBUG_COMPILER
     fprintf(o_src,"# File '%s' Record Description Stack Location\n",f->name);
#endif
     /* fprintf(o_src, "\tleal\t-u(%%ebp), %%eax\n", f->uval5.record); */
     fprintf(o_src, "\tmovl\t%s, %%eax\n", memref(f->uval6.recordsym));
     push_eax();
  }
  
  if (f->type=='K') {
     fprintf(o_src,"\tmovl\t$_%s, %%eax\n", f->name);
  }
  else {
#ifdef DEBUG_COMPILER
     fprintf(o_src,"# File name '%s', Record name '%s'\n",f->name, f->uval6.recordsym->name);
#endif
     /* fprintf(o_src,"\tmovl\t$s_base%d+%u, %%eax\n", pgm_segment, f->uval2.location); */
     fprintf(o_src,"\tmovl\t$s_base%d_%u, %%eax\n", pgm_segment, f->uval2.location);
  }
  push_eax();
}

void gen_save_filevar2(struct sym *f) 
{
  if (!(f->uval6.recordsym)) { 
     yyerror("No FD/SD for file %s\n", f->name);
     return;
  }                

#ifdef DEBUG_COMPILER
     fprintf(o_src,"# File '%s' Record Description Stack Location\n", f->name);
#endif

  /* Generate FILE structure 'file_desc' */
  if (f->type=='K') {
     fprintf(o_src,"\tmovl\t$_%s, %%eax\n", f->name);
  }
  else {
#ifdef DEBUG_COMPILER
     fprintf(o_src,"# File name '%s', Record name '%s'\n", f->name, f->uval6.recordsym->name);
#endif
     /* fprintf(o_src,"\tmovl\t$s_base%d+%u, %%eax\n", pgm_segment, f->uval2.location); */
     fprintf(o_src,"\tmovl\t$s_base%d_%u, %%eax\n", pgm_segment, f->uval2.location);
  }
  push_eax();
}

void gen_save_filedesc (struct sym *f) {

  if (f->type=='K') {
     fprintf(o_src,"\tmovl\t$_%s, %%eax\n",f->name);
  }
  else {
#ifdef DEBUG_COMPILER
  {
   if (f->uval6.recordsym != NULL) 
     fprintf(o_src,"# File name '%s', Record name '%s'\n",f->name, f->uval6.recordsym->name);
  }
#endif
     /* fprintf(o_src,"\tmovl\t$s_base%d+%u, %%eax\n", pgm_segment, f->uval2.location); */
     fprintf(o_src,"\tmovl\t$s_base%d_%u, %%eax\n", pgm_segment, f->uval2.location);
  }
  push_eax();
}

/*static void gen_prtvar( struct sym *r, struct sym *buf ) {
        struct sym *f;
        f=r->ix_desc;
        if (buf!=NULL)
                gen_loadloc( buf );
        fprintf(o_src,"\tleal\t-%d(%%ebp), %%eax\n",f->uval5.record);
        push_eax();
        if (buf != NULL)
                fprintf(o_src,"\tmovl\t$%d, %%eax\n",buf->len);
        else
                fprintf(o_src,"\tmovl\t$%d, %%eax\n",r->len);
        push_eax();
}*/

void gen_save_sort_fields(struct sym *f, struct sym *buf) 
{
 struct sym *datafld;
 struct rec_varying *rv;
 int iNull=0;

 if (f == NULL)
     return;

 /* datafld = (struct sym *)f->sort_data;*/
 datafld = f->uval4.sort_data;
 rv = f->uval9.rec_varying;

 while (datafld!=NULL) {
         gen_loadloc( datafld );
         datafld=datafld->uval4.sort_data;
 }
/* fprintf(o_src,"\tmovl\t$c_base%d+%u, %%eax\n",pgm_segment,f->descriptor);*/
 fprintf(o_src, "\tmovl\t$c_base%d_%u, %%eax\n", pgm_segment, f->descriptor);
 push_eax();
 if (rv != NULL) {
    gen_loadvar(rv->reclen);
 }
 else {
    push_immed(iNull);
    push_immed(iNull);
 }
 gen_save_filevar(f, buf);
 /* returns number of stack levels used in storing fields */
}

/* The function 'dump_alternate_keys' is obsolete */
void dump_alternate_keys(struct sym *r, struct sym *f, struct alternate_list *alt) 
{
        struct alternate_list *tmp;
        struct sym *key;
        int idx=1, floc=0;
        
        floc = f->uval2.location + sizeof(struct file_desc);
#ifdef DEBUG_COMPILER
        fprintf(o_src,"# Alternate keys begin for file: %s, Record: %s, Data Loc: %d(hex: %x)\n",
                        f->name, r->name, floc, floc);
#endif
        while (alt) {
                key = alt->key;
#ifdef DEBUG_COMPILER
                fprintf(o_src,"# alternate key %s\n", key->name);
#endif
                fprintf(o_src,
                        "\t.long\t%d\n\t.long\tc_base%d+%d\n\t.word\t%d,%d\n",
                        /*r->uval2.location - key->uval2.location,*/
                        key->uval2.location-r->uval2.location, pgm_segment,
                        key->descriptor, alt->duplicates, idx);
                tmp = alt;
                alt = alt->next;
                /* free(tmp); */
                /* tmp=NULL;  */
                idx++;
        }
        fprintf(o_src,"# end of alternate keys\n\t.long\t-1\n");
}

/* 
** dump all file descriptors in file_list
*/
void dump_fdesc() {

  struct sym *f, *r, *sy1;
  struct list *list/*,*visited*/;
  union {
    struct file_flags fflags;
    unsigned short usfflags;
  }ufflags;                       /* File struct flags  */
  unsigned char file_std_flag;    /* Standard-in/out/error indicator */
  unsigned int loc = 0;           /* Record buffer location */
  
  ufflags.usfflags = 0;        
  
  file_std_flag=0;              

  /* fprintf(o_src,".data\n\t.align 4\n"); */
  /* fprintf(o_src,"s_base%d:\n\t.long\t0\n",pgm_segment); */
  /*
  if (files_list != NULL) 
     // fprintf(o_src,"s_base:\n"); 
     fprintf(o_src,".data\n\t.align 4\ns_base%d:\n\t.long\t0\n", pgm_segment); 
  */
  /* Do NOT remove - location is used as initialization flag */
#ifdef DEBUG_COMPILER
  fprintf(o_src,"# First 4 bytes of 's_base' are used as an initialization flag\n");
#endif
  fprintf(o_src,".data\n\t.align 4\ns_base%d:\n\t.long\t0\n", pgm_segment); 

  for (list=files_list;list!=NULL;list=list->next) {
     f=(struct sym *)list->var;
     r=f->uval6.recordsym;
#ifdef DEBUG_COMPILER
/*      fprintf(o_src,"# FILE DESCRIPTOR, File: %s, Record: %s, Data Loc: %d(%x)\n",
                      f->name,r->name,global_offset); */
/*     fprintf(o_src,"# FILE DESCRIPTOR, File: %s, Record: %s, Data Loc: %d(hex: %x)\n",
                     f->name,r->name,f->uval2.location,f->uval2.location);
     fprintf(o_src,"# FILE DESCRIPTOR2, opt: %x\n", f->flags.optional);*/

     fprintf(o_src,"# FILE DESCRIPTOR Name: %s, Data Loc: %d(hex: %x), len: %d, flags.optional(hex): %x\n",
                     f->name, f->uval2.location, f->uval2.location, f->len, f->flags.optional);
#endif
       sy1=f->uval6.recordsym;
       if (sy1 != NULL) 
          loc = sy1->uval2.location;
#ifdef DEBUG_COMPILER
       while (sy1 != NULL) {
          fprintf(o_src,"# RECORD Name: %s, Data Loc: %d(hex: %x), len: %d\n", 
                        sy1->name, sy1->uval2.location, sy1->uval2.location, sy1->len);
          sy1 = sy1->uval6.recordsym;
       }
#endif
     if (f->uval7.filenamevar==NULL) {
             yyerror("No file name assigned to %s.",f->name);
             continue;
     }
     if (f->type=='K') {
             fprintf(o_src,"\t.extern\t_%s:far\n",f->name);
             continue;
     }
     if (f->type=='J') {
             fprintf(o_src,"\tpublic\t_%s\n",f->name);
             fprintf(o_src,"_%s\tlabel\tbyte\n",f->name);
     }
     
     
    fprintf(o_src,"s_base%d_%d:\n", pgm_segment, f->uval2.location);

     fprintf(o_src,"\t.byte\t%u\n",RTL_FILE_VERSION);
     /* fprintf(o_src,"\t.long\tc_base%d+%u\n", */
     fprintf(o_src,"\t.long\tc_base%d_%u\n",
             pgm_segment, f->uval7.filenamevar->descriptor);
     
     /* reclen : max record length */
     /* reclen_min : min record length - zero means fixed length  */
     int minreclen = 0; 
     fprintf(o_src,"\t.long\t%u\n", f->len); 
     if (f->len != f->minlen) 
        minreclen = f->minlen; 
     fprintf(o_src,"\t.long\t%u\n", minreclen); 
      
     fprintf(o_src,"\t.byte\t%d,%d\n",f->uval1.organization,f->uval3.access_mode);
     fprintf(o_src,"\t.byte\t0\n");   /* open_mode */
     fprintf(o_src,"\t.space\t2\n");  /* file_status */
     /* fprintf(o_src,"\t.space\t2\n");  // char file_status_ext[2] - unused feature  */

     /* char *filename - Resolved file name */
     fprintf(o_src,"\t.long\t0\n"); 
     
     /* void *dbp - File handle (FILE/fileid-int/handle) */
     fprintf(o_src,"\t.long\t0\n"); 

     /* char *record - Pointer to file data storage */
     /* fprintf(o_src,"\t.long\tw_base%d+%d\n", pgm_segment, f->uval2.location); */ 
     fprintf(o_src,"\t.long\tw_base%d_%d\n", pgm_segment, loc); 
     /* char *vname = convert_variable_name(f); */
     /* fprintf(o_src,"\t.long\t%s\n", vname); */
  
     /* fflags = f->flags.optional; */
     ufflags.fflags.optional = f->flags.optional;
     ufflags.fflags.file_external = f->flags.file_external;
     ufflags.fflags.file_isvariable = f->flags.file_isvariable;
     ufflags.fflags.file_printer = f->flags.file_printer;
     fprintf(o_src,"\t.word\t%#x\n", ufflags.usfflags); /* file flags */

     /* unsigned char file_std_flag;    // Standard in/out/error indicator */
     /* NONE=0, INPUT=1, OUTPUT=2, ERROR=3 */
     if ((f->flags.file_stdin == 1)  || 
         (f->flags.file_stdout == 1) ||
         (f->flags.file_stderr == 1) 
        )  {
        if (f->flags.file_stdin == 1) 
           file_std_flag = 1;              
        if (f->flags.file_stdout == 1) 
           file_std_flag = 2;              
        if (f->flags.file_stderr == 1) 
           file_std_flag = 3;              
     }
     fprintf(o_src,"\t.byte\t%d\n", file_std_flag);  
          
     if (f->uval1.organization != TCB_FILE_ORGANIZATION_INDEXED) {  
        /* Number of keys  */
        fprintf(o_src,"\t.word\t0\n");     /* 2 x 1 = 2 bytes (nulls)  */

        /* tcob_file_keys *keys   */
        fprintf(o_src,"\t.long\t0\n");     /* 4 x 1 =  4 bytes (nulls) */ 
     }
     else {
        int nkeys=0;
        int file_key_offset=0;
        if (f->ix_desc) {
           nkeys = get_number_of_index_keys(f->ix_desc, f->uval8.alternate); 
           fprintf(o_src,"\t.word\t%d\n", nkeys); // Number of keys 
           /* file_key_offset = f->uval2.location + sizeof(struct file_desc); */
           /* FIXME: Hack to ensure label is unique - should be in the c_base section */
           file_key_offset = f->uval2.location; 
           /*// fprintf(o_src,"\t.long\ts_base%d+%d\n", pgm_segment, file_key_offset); */    
           /* fprintf(o_src,"\t.long\ts_base%d_%d\n", pgm_segment, file_key_offset); */     
           /* fprintf(o_src,"s_base%d_%d:\n", pgm_segment, file_key_offset);  */    
           /* FIXME: Hack to ensure label is unique - should be in the c_base section */
           fprintf(o_src,"\t.long\tk_base%d_%d\n", pgm_segment, file_key_offset);     
           fprintf(o_src,"k_base%d_%d:\n", pgm_segment, file_key_offset);     
           dump_key_indexes(r, f->ix_desc, nkeys, f->uval8.alternate); 
        }
        else {
           /* no key field was given for this file */
           fprintf(o_src,"\t.word\t0\n");     /* Number of keys 2 x 1 = 2 bytes (nulls) */
           fprintf(o_src,"\t.long\t0\n");     /* struct tcob_file_keys *keys  */
        }
     }
  }
}

int get_number_of_index_keys(struct sym *pidx, struct alternate_list *alt) 
{
  int nkeys=0;
  struct alternate_list *w1, *w2;
  
  if (pidx == NULL) 
     return nkeys;
  
  nkeys++;
#ifdef DEBUG_COMPILER
    fprintf(o_src,"# Primary key %d name %s\n", nkeys, pidx->name);
#endif
  
  w1 = alt;
  while (w1 != NULL) {
     nkeys++;
#ifdef DEBUG_COMPILER
    fprintf(o_src,"# Secondary key %d name %s\n", nkeys, w1->key->name);
#endif
     w2 = w1;
     w1 = w2->next;
  }
  
  return nkeys;
}


void dump_key_indexes(struct sym *r, struct sym *pidx, int nkeys, struct alternate_list *alt) 
{
  struct alternate_list *w1, *w2;
  struct sym *key;
  int idx=0, oflag=0;

#ifdef DEBUG_COMPILER
  fprintf(o_src,"# Number of key indexes is %d for %s\n", nkeys, r->name);
#endif
 
#ifdef DEBUG_COMPILER
  fprintf(o_src,"# Primary key[%d] %s for %s\n", idx, pidx->name, r->name);
#endif

  /* fprintf(o_src, "\t.long\tc_base%d+%d\n\t.long\t%d\n\t.long\t%d\n", */
  fprintf(o_src, "\t.long\tc_base%d_%d\n\t.long\t%d\n\t.long\t%d\n",
                 pgm_segment, pidx->descriptor, oflag, pidx->uval2.location - r->uval2.location);

  w1 = alt;
  while (w1 != NULL) {
     idx++;
     w2 = w1;
     key = w2->key;
     oflag = w2->duplicates;
#ifdef DEBUG_COMPILER
  fprintf(o_src,"# Secondary key[%d] %s for %s\n", idx, key->name, r->name);
#endif
     /* fprintf(o_src, "\t.long\tc_base%d+%d\n\t.long\t%d\n\t.long\t%d\n", */
     fprintf(o_src, "\t.long\tc_base%d_%d\n\t.long\t%d\n\t.long\t%d\n",
             pgm_segment, key->descriptor, 
             oflag, key->uval2.location - r->uval2.location);
     w1 = w2->next;
  }

  fprintf(o_src,"# end of keys for %s\n", r->name);
}


unsigned long int emt_call(struct lit *v, int stack_size, int exceplabel, 
                           int notexceplabel,struct sym *ret) {
        struct parm_list *list,*tmp;
        struct sym *cp;
        struct lit *lp;
        int len, totlen=0, err=0;
        int saved_stack_offset=stack_offset;
        int stack_save;
        int endlabel;
        char callname[128], call_winapi[8];
/*        char *sp = '\0'; */
        
        /******** prepare all parameters which are passed by content ********/
        for (list=parameter_list;list!=NULL;list=list->next) {
                cp=(struct sym *)list->var;
                if (cp->litflag!=1) {
                        if (cp->uval3.call_mode == CM_CONT) {
                                len = symlen(cp);        /* should we round to 4? */
                                totlen += len;
                                list->sec_no = SEC_STACK;
                                list->location = stack_offset + len;
                                stack_offset += len;
                                fprintf(o_src, "\tsubl\t$%d, %%esp\n", len);
                                push_immed(len);        /* length */
                                gen_loadloc(cp);        /* src address */
                                fprintf(o_src, "\tleal\t-%d(%%ebp), %%eax\n", list->location);
                                push_eax();                        /* dest address ie on stack */
                                asm_call("memcpy");                                
                                }
                        }
        }
        /******** get the parameters from the parameter list ********/
        for (list=parameter_list;list!=NULL;) {
                cp=(struct sym *)list->var;
                if (cp->litflag==1) {
                   lp = (struct lit*)cp;
#ifdef DEBUG_COMPILER
                    fprintf(o_src, "#call %s by %d\n", lp->name,lp->call_mode);
#endif
                    if (lp->call_mode == CM_REF) 
                            gen_loadloc((struct sym *)list->var);
                   else if (lp->call_mode == CM_VAL) {
                          value_to_eax(cp);
                          if (symlen(cp) > 4)
                                        push_edx();
                          push_eax();
                      }
                    /* else    
                       gen_loadvar((struct sym *)list->var)*/;
                    }
                else {
#ifdef DEBUG_COMPILER
                        fprintf(o_src, "#call %s by %d\n", cp->name,cp->uval3.call_mode);
#endif
                    if (cp->uval3.call_mode == CM_REF) 
                            gen_loadloc((struct sym *)list->var);
                    else if (cp->uval3.call_mode == CM_VAL) {
                       gen_pushval((struct sym *)list->var);
                       }   
                      else if (cp->uval3.call_mode == CM_CONT) {
                                fprintf(o_src, "\tleal\t-%d(%%ebp), %%eax\n", list->location);
                                push_eax();
                              }
                      else   
                       gen_loadvar((struct sym *)list->var);
                    }
                tmp=list; 
                list=list->next;
                free(tmp);
                tmp=NULL;
        }
        parameter_list=NULL;
        if ((v->litflag == 1)&&(!HTG_all_calls_dynamic)) {
                /* call literal (static) routine */
                
               /* 
                 Validate name and convert the DASH ('-') characters in program name 
               */
               err = pgm_name_validate(v->name, callname, 0);
               /* 
                 check for valid characters in program name 
               */
/*
               sp = v->name;
                if (! ( isalpha(*sp) || (*sp == '_') ) ) {
                     err++;
                     yyerror("Invalid character '%c' in program name '%s'", *sp, v->name);
                }
                sp++;    
                while (*sp != '\0') {
                  if (! ( isalnum(*sp) || 
                          (*sp == '$') ||
                          (*sp == '.') ||
                          (*sp == '_') 
                        ) 
                      ) {
                    err++;
                    yyerror("Invalid character '%c' in program name '%s'", *sp, v->name);
                  }
                  sp++;    
                }
*/
                if (err != 0) {
                  return 0;
                }
                
                /* use standard C call convention */
                if(curr_call_convention == 0) 
                   /* asm_call(v->name); */
                   asm_call(callname);
                else {
                /* 
                   When the PASCAL (WINAPI) call convention is used
                   stack pointer is reset by called function 
                */
                   stack_save = stackframe_cnt;
                /* set the Win32 (MinGW) naming convention (function_name@arg_length) */ 
                   /* sprintf(callname, "%s@%d", v->name, stack_save);  */
                   sprintf(call_winapi, "@%d", stack_save);
                   strcat(callname, call_winapi);
                   asm_call(callname);
                /* reset the stack pointer */ 
                   fprintf(o_src,"\tsubl\t$%d, %%esp\n", stack_save);
                }
                endlabel=0;
                gen_store_fnres(ret);
                gen_enter_runelement(TCB_RUN_ELEMENT_RETURN);
        }
        else {
                /* call dynamic routine (call by name) */
                stack_save = stackframe_cnt;
                stackframe_cnt = 0;

                if(curr_call_convention == 0) 
                    fprintf(o_src,"\tpushl\t$0\n");
                else {
                     fprintf(o_src,"\tpushl\t$%d\n", stack_save + 1);
                }
                stackframe_cnt = stackframe_cnt + 4;

                gen_loadvar((struct sym *)v);
                asm_call("tcob_resolve_subr");

                /*
                PROBLEM CODE - FIX ME ? --------------------- 
                
                With the 'static call' the call paramaters are 
                pushed on to the stack, then the CALL function 
                is called. No problem here.
                
                With the 'dynamic call' the call paramaters are 
                pushed on to the stack, then the 'tcob_resolve_subr' 
                paramaters are pushed on to the stack, then the 
                'tcob_resolve_subr' function is called. 
                If the 'tcob_resolve_subr' function is true then
                the pointer to the function is called. If false
                then the CALL is by-passed (jump).
                
                Problem: 
                When the CALL is by-passed the stack pointer
                is not reset. 
                
                Temporary fix: 
                Reset the stack pointer before the compare and jump.
                Then reset the stack pointer back before the function
                call.
                */
                stackframe_cnt = stack_save;

                /* Reset the stack pointer in case 'tcob_resolve_subr' fails */
                fprintf(o_src,"\taddl\t$%d, %%esp\n", stack_save);

                fprintf(o_src,"\tand\t%%eax,%%eax\n");
                fprintf(o_src,"\tjz\t.L%d\n",exceplabel);

                /* Reset the stack pointer when 'tcob_resolve_subr' succeeds */
                fprintf(o_src,"\tsubl\t$%d, %%esp\n", stack_save);
                fprintf(o_src,"\tcall\t*%%eax\n");

                if(curr_call_convention == 0) 
                  cleanup_rt_stack();

                endlabel = loc_label++;
                gen_store_fnres(ret);
                gen_enter_runelement(TCB_RUN_ELEMENT_RETURN);
                fprintf(o_src,"\tjmp\t.L%d\n",notexceplabel);

                HTG_prg_uses_dcall = 1; /* mark we use dynamic calls for the linker step */
        }
        /*fprintf(o_src,"\taddl\t$%d, %%esp\n",stack_size*2);*/
        if (totlen != 0)
                fprintf(o_src,"\taddl\t$%d, %%esp\n",totlen);
        stack_offset=saved_stack_offset;
        return endlabel;        
}

unsigned long int
emt_call_loadlib(struct lit *v) {
        
        gen_loadvar((struct sym *)v);
        asm_call("tcob_call_loadlib");
        return 0;        
}

int begin_on_except() {
        int lab=loc_label++;
        fprintf(o_src,".L%d:\t# begin_on_except\n",lab);
        stabs_line();
        return lab;
}

void check_call_except( int excep, int notexcep, int exceplabel, int notexceplabel, int endlabel) {

        /* generate code only if was "call <identifier>" */
        if (endlabel!=0) {
                fprintf(o_src,".L%d:\t# exceplabel\n",exceplabel);
                if (excep) {
                        fprintf(o_src,"\tjmp\t.L%d\n",excep);
                }
                /* if no exception phrase was given */
                if (excep==0) { 
/*                        fprintf(o_src,"\tcall\ttcob_resolve_subr_error\n"); */
                        asm_call("tcob_resolve_subr_error");
                        fprintf(o_src,"\tjmp\t.L%d\n",endlabel);
                }
                fprintf(o_src,".L%d:\t# notexceplabel\n",notexceplabel);
                if (notexcep) {
                        fprintf(o_src,"\tjmp\t.L%d\n",notexcep);
                }
                fprintf(o_src,".L%d:\t# endlabel\n",endlabel);
        }
}

/* Generates code for inline intrinsic functions,
   returns a field containing the return value of the intrinsic functions */
struct sym *gen_inline_intrinsic( struct sym *v ) {
        struct parm_list *list,*tmp;
        struct sym *temporary;
        static struct lit *when_compiled = NULL;
        struct sym *cp = NULL;
        if ( parameter_list ) 
                cp = (struct sym *)parameter_list->var;


        if (strcasecmp("LENGTH",v->name) == 0) {
                temporary=define_temp_field(DTYPE_BININT,sizeof(int));
                fprintf(o_src, "\tmovl\t$%d, %s #%s\n", set_field_length(cp, 1), memrefat(temporary), cp->name);
        }
        else if (strcasecmp("ORD",v->name) == 0) {
                temporary=define_temp_field(DTYPE_BININT,sizeof(int));
                fprintf(o_src, "\tmovsbl\t%s, %%eax\n", memrefat(cp));
                fprintf(o_src, "\taddl\t$1, %%eax\n"/*, memrefat(cp),
                        memrefat(temporary), cp->name*/);
                fprintf(o_src, "\tmovl\t%%eax, %s\n", memrefat(temporary));
        }
        else if (strcasecmp("CHAR",v->name) == 0) {
                temporary=define_temp_field(DTYPE_ALPHANUMERIC,1);
                gen_loadval(cp);
                fprintf(o_src, "\tsubl\t$1, %%eax\n" /*,memrefat(cp),
                        memrefat(temporary), cp->name*/);
                fprintf(o_src, "\tmovb\t%%al, %s\n", memrefat(temporary));
        }
        else if (strcasecmp("WHEN-COMPILED",v->name) == 0) { 
                if (when_compiled == NULL){ /* If first time, create the literal */
                   char now_str[22];
                   time_t now;
                   now = time(NULL);
                   /* Needs fix to fill positions 15 to 21 */
                   /* (milliseconds and diff between local and Univeral Time) */
                   strftime(now_str,22,"%Y%m%d%H%M%S0000000",localtime(&now));
                   when_compiled = install_lit(now_str,22,0);
                   save_literal(when_compiled,DTYPE_DISPLAY);
#ifdef DEBUG_COMPILER
                   fprintf(o_src,"#Creating compile time literal:%s\n",now_str);
#endif
                }
                temporary = (struct sym *)when_compiled;
        } 
        else {
                yyerror("inline Intrinsic function type not yet implemented");
        }
                
        /* Free parameter list */
        for (list=parameter_list;list!=NULL;) {
                tmp=list;
                list=list->next;
                free(tmp);
                tmp=NULL;
        }
        parameter_list=NULL;
        return temporary;
}

/*
 * Makes a call to an intrinsic function using the parameter list. 
 * Returns a pointer to a temporaty field that contains the value returned by
 * the function.
 *
 * This function does not use anything platform dependent,
 * and may be trasferred to htcobgen
 */
struct sym *gen_intrinsic_call( struct sym *v ) {
        struct parm_list *list,*tmp;
        struct sym *cp;
        char intrinsic_name[50] = "tcob_intrinsic_";
        unsigned short inp;
        struct sym *temporary=NULL; 
        struct intrinsic_function *function=NULL;

/*        fprintf(stderr,"in:%s\n",v->name); */
#ifdef DEBUG_COMPILER
                fprintf(o_src, "#call intrinsic %s \n", v->name);
#endif
        /* Look for data types of intrinsic function */
        function = lookup_intrinsic_function(v->name);
        if (function == NULL) {
                yyerror("Intrinsic function type not recognized");
                return NULL;
        }
        /* Define a temporaty field as needed */
        switch(function->function_type) {
                case ITYPE_FLOAT:
                        temporary=define_temp_field(DTYPE_FLOAT,sizeof(double));
                        break;
                case ITYPE_DATE: /* Date fields defined as PIC 9(8) */
                        temporary=define_temp_field(DTYPE_DISPLAY,8);
                        break;
                case ITYPE_INT:
                        temporary=define_temp_field(DTYPE_BININT,sizeof(int));
                        break;
                case ITYPE_DATETIME:        
                        temporary=define_temp_field(DTYPE_ALPHANUMERIC,21);
                        break;
                case ITYPE_JULIANDATE:        
                        temporary=define_temp_field(DTYPE_DISPLAY,7);
                        break;
                case ITYPE_YEAR:        
                        temporary=define_temp_field(DTYPE_DISPLAY,4);
                        break;
                case ITYPE_ALPHA:
                        /* Maximmum length supported is 255 chars */
                        /* Is the maximum supported by define_temp_field */
                        temporary=define_temp_field(DTYPE_ALPHANUMERIC,255);
                        break;
                case ITYPE_INLINE:
                        return gen_inline_intrinsic(v);
                        break;
                default:
                        yyerror("Intrinsic function type not recognized");
                        return NULL;
        }
        /* construct the routine name */
        strcat(intrinsic_name, v->name);
        /* Force to lowercase, change - to _ */
        for (inp=15;inp <= (strlen(v->name)+15);inp++) {
                if (intrinsic_name[inp] >= 'A' && intrinsic_name[inp] <= 'Z') intrinsic_name[inp] += 32;
                if (intrinsic_name[inp] == '-') intrinsic_name[inp] = '_';        
        }
        /* First we push a NULL to mark end of parameters */
        push_immed(0);
        /******** get the parameters from the parameter list ********/
        /* Intrinsics are always called by reference */
        inp=0;  /* used to count number of args */
        for (list=parameter_list;list!=NULL;) {
                cp=(struct sym *)list->var;
#ifdef DEBUG_COMPILER
                fprintf(o_src, "#call intrinsic parameter %s \n", cp->name);
#endif
                 gen_loadvar(cp);
                tmp=list;
                list=list->next;
                free(tmp);
                tmp=NULL;
                inp++;
        }
        parameter_list=NULL;
        /* check number of args */
        if ((function->args != ANY_NUMBER) && (function->args != inp)) {
                yyerror("Invalid number of args calling intrinsic %s",v->name);
        }
        
        /* push the destination field */
        gen_loadvar(temporary);
        asm_call(intrinsic_name);
        /*gen_store_fnres(temporary);*/
        
        return temporary;
}

/* end of HTCOBEMT.C */
