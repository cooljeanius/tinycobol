/*
 * Copyright (C) 2006-2009 David Essex, Rildo Pragana.
 * Copyright (C) 1999-2006 Rildo Pragana, Jim Noeth, Bernard Giroud, 
 *               David Essex, Glen Colbert, Andrew Cameron.
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
 *

 * 
 * TinyCOBOL GNU assembler code generator 
 * 

*/ 

/*
#define DEBUG_COMPILER_LEVEL 1 
#define DEBUG_COMPILER_LEVEL2 1
*/

#include "htconfig.h"
#include "htversion.h"
#include "htcoboly.h"
#include "htcoblib.h"
#include "htglobals.h"
#include "mwindows.h"

int pgm_segment = 0;               /* # of program in source file */ 
int screen_io_enable=0;            /* use screen routines or not for accept/display */
int use_screen_io=0;               /* use screen routines for accept/display */

int decimal_comma=0;                  /* decimal char 1 = ',' ; 0 ='.' */
#define decimal_char() (decimal_comma ? ',' : '.')

char currency_symbol=CHR_DOLLARD_SIGN;             
char sch_convert_buf[512];

struct sym *screen_status_field=NULL; /* variable of crt status */
struct sym *cursor_field=NULL;        /* variable of cursor */
struct lit *program_name_literal=NULL;/* literal thar holds the program name */ 

int stabs_on_sw=0;

extern struct lextab literal;
extern int yydebug;
extern struct sym *curr_file;
extern struct tcb_declaratives_list *declaratives_list;

struct sym *curr_paragr=NULL,*curr_section=NULL;
struct sym *curr_field;
short curr_call_mode = 0;
short curr_call_convention = 0;
unsigned stack_offset=0;        /* offset for variables on the stack */
/*#define SAVED_EBX_OFFSET 4*/        /* relative to %ebp */
unsigned stack_plus=0;

/* offset for global variables (DATA) */
unsigned global_offset=4;        
unsigned file_offset=0;
unsigned literal_offset=0;
unsigned data_offset=0;
/*#define data_offset global_offset*/
unsigned linkage_offset=0;
unsigned using_offset=8;
/* tmpvar_offset: for storage of temporary variables, 
with space reclaimed after the current instruction*/
unsigned tmpvar_offset = 0;        
unsigned tmpvar_max = 0;

unsigned last_lineno = 0;
short at_procedure = 0;
short refmod_slots = 0;
static char name_buf[MAXNAMEBUF];

struct lit *spe_lit_ZE = NULL;                /* figurative constant ZERO */
struct lit *spe_lit_01 = NULL;                /* figurative constant ONE */
struct lit *spe_lit_SP = NULL;                /* figurative constant SPACE */
struct lit *spe_lit_LV = NULL;                /* figurative constant LOW-VALUE */
struct lit *spe_lit_HV = NULL;                /* figurative constant HIGH-VALUE */
struct lit *spe_lit_QU = NULL;                /* figurative constant QUOTE */
static char init_ctype;                                /* hold homogenous type */
static short init_val;                                /* hold homogenous value */
static struct init_str_tab *istrp;
static unsigned curr_01_location;        /* hold current root father when set_field_location */

struct list *expr_list=NULL;
struct list *files_list=NULL;
struct list *disp_list=NULL;
struct parm_list *parameter_list=NULL;
struct list *fields_list=NULL;
struct list *last_field=NULL;
struct index_to_table_list *index2table = NULL;
struct named_sect *named_sect_list=NULL;
struct list *switches_list=NULL;
struct list *vars_list=NULL;
short next_available_sec_no=SEC_FIRST_NAMED;
short default_sec_no=SEC_WORKING;
short curr_sec_no=SEC_WORKING;

struct parm_list *chaining_list=NULL;  /* chaining variables */

int screen_label=0;
int para_label=0;
int block_label=0;
int line_label=0;
int paragr_num=1;
int loc_label=1;
unsigned char picture[100];                /* for max 50 signs and counts */
int picix,piccnt,decimals,sign,v_flag,n_flag,digits,pscale;
int filler_num=1;
int active[37];
int at_linkage=0;
int stackframe_cnt=0;
int inner_stack_size=0;

extern char *pgm_label; 

int initial_flag=0;
struct list *report_list=NULL;
static int need_desc_length_cleanup=0;
extern int stabs_started;
extern short HTG_debug_trace_flag;

extern short main_flag;       /* Does it have an main entry point */
extern int main_entry_flag;   /* Specify main entry point */
extern char main_entry_buf[]; /* main entry point name */

int module_flag = 1;  /* All (sub)programs are modules (routines) */
int nested_flag = 0;  /* Is this program nested inside another program */
int has_linkage = 0;  /* Has linkage section ? */
/*
**        Symbol table management routines
*/

struct sym *vartab[ HASHLEN ]={NULL};
struct sym *labtab[ HASHLEN ]={NULL};
struct lit *littab[ HASHLEN ]={NULL};
struct _dtracedata dtracedata={0, NULL};

int hash( char *s ) {
        int val;
        for ( val = 0 ; *s != '\0'; )
                val += toupper(*s++);
        return( val % HASHLEN );
}

char *savename( char *s ) {
        char *ap;
        if ((ap = (char *) malloc( strlen(s) + 1 )) != NULL)
                strcpy(ap,s);
        return( ap );
}

char *upcase( char *s, char *buf ) {
        char *t;
        int n=SYMBUF_SIZE-1;
        t = buf;
        while (*s && n--) {
                *t++ = toupper(*s++);
        }
        if (n<=0) {
                yyerror("Too large symbol");
        }
        *t=0;
        return buf;
}

void update_xreflist(struct sym *as) {
        if ((as->xrefs.pos > 0) && 
            (as->xrefs.lineno[as->xrefs.pos - 1] == source_lineno))
           return;

        if (as->xrefs.size <= as->xrefs.pos) {
          as->xrefs.size += 10;
          as->xrefs.lineno = realloc (as->xrefs.lineno, sizeof(int) * as->xrefs.size);
        }
        as->xrefs.lineno[as->xrefs.pos] = source_lineno;
        as->xrefs.pos++;
}

/*
 * struct _dtracedata {
 *         unsigned int size;
 *         char **name; 
 * };
 *   idx = install_display_trace(secpara->name);
 *     fprintf(o_src,".LC%04d_%s:\n\t.string \"%s\"\n", pgm_label, dtracedata.name[i]);
 */

int trace_display_install(char *name)
{
  int i, len;
  
#ifdef DEBUG_COMPILER_LEVEL2       
  fprintf(stderr, "debug : trace_display_install : 0205.100 : name=%s;\n", name);
#endif
  for (i=0; i<dtracedata.size; i++) {
    if (dtracedata.name[i] != NULL) {
       if (strcmp(name, dtracedata.name[i]) == 0)
          break;
    }
    else {   
       len = strlen(name);
       /* dtracedata.name[i] = malloc(sizeof(char[len + 1])); */
       dtracedata.name[i] = malloc(sizeof(char) * (len + 1));
       strncpy(dtracedata.name[i], name, len);
       dtracedata.name[i][len] = '\0';
#ifdef DEBUG_COMPILER_LEVEL2       
       fprintf(stderr, "debug : trace_display_install : 0205.300 : len=%d, name[%d]=%s;\n", len, i, dtracedata.name[i]);
#endif
       break;
    }
  }
  if (dtracedata.size == i) {
     i = trace_display_expand(dtracedata.size * 2);
     len = strlen(name);
     dtracedata.name[i] = malloc(sizeof(char) * (len + 1));
     strncpy(dtracedata.name[i], name, len);
     dtracedata.name[i][len] = '\0';
#ifdef DEBUG_COMPILER_LEVEL2       
     fprintf(stderr, "debug : trace_display_install : 0205.100 : len=%d, name[%d]=%s;\n", len, i, dtracedata.name[i]);
#endif
  }
  
  return i;
}

int trace_display_expand(int zsize)
{
  int wsize=0, i, j;
  char **wname=NULL;
  
  if (dtracedata.size != 0) {
     wsize = dtracedata.size;
     wname = dtracedata.name;
     dtracedata.name = NULL;
  }

  dtracedata.name = malloc(sizeof(char**)*zsize);
  dtracedata.size = zsize;
  for (i=0; i<wsize; i++) {
     dtracedata.name[i] = wname[i];
     wname[i] = NULL;
  }
  if (wname != NULL)
     free(wname);
  for (j=i; j<dtracedata.size; j++) {
     dtracedata.name[j] = NULL;
  }
  
  return wsize;
}

void trace_display_clear()
{
  int i;

  for (i=0; i<dtracedata.size; i++) {
     if (dtracedata.name[i] != NULL) {
       free(dtracedata.name[i]);
       dtracedata.name[i] = NULL;
     }
  }
  free(dtracedata.name);
  dtracedata.name = NULL;
  dtracedata.size=0;
}

struct sym *lookup( char *s, int tab ) {
        char sbuf[SYMBUF_SIZE];
        if (tab==SYTB_LIT) { /* literals tab */
                struct lit *as;
                for ( as = littab[ hash(s) ] ; as != NULL ; as = as->next )
                        if ( strcmp( s, as->name ) == 0 )
                                return( (struct sym *)as );
                return( NULL );
        }
        else {
                struct sym *as;
                s = upcase(s,sbuf);
                if (tab==SYTB_VAR) 
                        as = vartab[ hash(s) ];
                else
                        as = labtab[ hash(s) ];
                for ( ; as != NULL ; as = as->next )
                        if ( strcmp( s, as->name ) == 0 )
                                return( as );
                        return( NULL );
        }
}

struct sym *install( char *name, int tab, int cloning ) {
        char sbuf[SYMBUF_SIZE];
        struct sym *clone;
        struct sym *as;
        struct lit *al;
        int val;

        if (tab==SYTB_LIT) {
                al = (struct lit *) malloc( sizeof(struct lit) );
                if (al==NULL)
                        return NULL;
                if ( (al->name = savename( name ) )  == NULL )
                        return NULL;
                val = hash( al->name );
                al->next = littab[ val ];
                littab[ val ] = al;
                al->type = 0;
                al->all = 0;
                al->litflag=1;
                al->nick = NULL;
                al->len = strlen(name);
                return( (struct sym *)al );
    }
    else {
                name = upcase(name,sbuf);
                if ( ( as = lookup(name,tab) ) == NULL ) {
                        as = (struct sym *) malloc( sizeof(struct sym) );
                        memset(as,0,sizeof(struct sym) );
                        if (as==NULL)
                                return NULL;
                        if ( (as->name = savename( name ) )  == NULL )
                                return NULL;
                        val = hash( as->name );
                        if (tab==SYTB_VAR) { 
/* fprintf(stderr,"install: creating %s -> 0x%x\n",as->name,as); */
                                as->next = vartab[ val ];
                                vartab[ val ] = as;
                        }
                        else {
                                as->next = labtab[ val ];
                                labtab[ val ] = as;
                        }
                        as->type = 0;
                        as->flags.is_pointer=0;
                        as->flags.just_r=0;
                        as->flags.separate_sign=0;
                        as->flags.leading_sign=0;
                        as->flags.blank=0;
                        as->flags.sync=0;
                        as->slack=0;
                        as->pscale=0;
                        as->defined = 0;
                        as->value = NULL;
                        as->uval4.sort_data = NULL;
                        as->linkage_flg = 0;
                        as->litflag=0;
                        as->scr = NULL;
                        as->clone = as->parent = NULL;
                        as->uval7.son = NULL;
                        as->occurs = NULL;
                        as->xrefs.size = 1;
                        as->xrefs.pos = 0;
                        as->xrefs.lineno = malloc( sizeof(int) );
                        as->xrefs.lineno[0] = 0;
                } else if ( (cloning && (as->defined==1)) || (cloning == 2) ) { 
                                /* install clone (cloning==2 -> force) */
/* fprintf(stderr,"install: cloning %s -> 0x%x\n",as->name,as); */
                        clone = (struct sym *) malloc( sizeof(struct sym) );
                        memset(clone,0,sizeof(struct sym) );        
                        if (clone==NULL)
                                return NULL;
                        clone->name = as->name;
                        clone->type = 0;
                        clone->flags.is_pointer=0;
                        clone->flags.just_r=0;
                        clone->flags.separate_sign=0;
                        clone->flags.leading_sign=0;
                        clone->flags.blank=0;
                        clone->flags.sync=0;
                        clone->slack=0;
                        clone->pscale=0;
                        clone->defined = 0;
                        clone->value = NULL;
                        clone->uval4.sort_data = NULL;
                        clone->linkage_flg = 0;
                        clone->litflag=0;
                        clone->scr = NULL;
                        clone->parent = NULL;
                        clone->occurs = NULL;
                        clone->clone = as->clone;
                        as->clone = clone;
                        as = clone;
                }
                return( as );
    }
}

struct lit *
install_lit( char *name, int length, int all ) {
        struct lit *al;
        int val;

        /* if length was not given, take the length from the name string */
        if (length == 0) {
                length = strlen(name);
        }
        al = (struct lit *) malloc( sizeof(struct lit) );
        if (al==NULL)
                return NULL;
        /* it is safer to null terminate it, so alloc one char more */
        al->name = malloc(length+1); 
        if (al->name == NULL) {
                return NULL;
        }
        memcpy(al->name,name,length);
        *(al->name+length) = 0;

        val = hash( al->name );
        al->next = littab[ val ];
        littab[ val ] = al;
        al->type = 0;
        al->all = all;
        al->litflag=1;
        al->nick = NULL;
        al->len = length;
        return al;
}

struct sym *lookup_label( struct sym *sy, struct sym *parent ) {

#if 0
#ifdef DEBUG_COMPILER
       fprintf(stderr,"lookup_label: %s",sy->name);
#endif
#endif
        while (sy->clone && (sy->parent != parent))
                sy = sy->clone;
        if (sy->parent == parent) {
#if 0
#ifdef DEBUG_COMPILER
                if (sy->parent != NULL)
                        fprintf(stderr," found -> %s\n",sy->parent->name);
                else
                        fprintf(stderr," found\n");
#endif
#endif
                return sy;
        } 
        else {
#if 0
#ifdef DEBUG_COMPILER
                fprintf(stderr," not found\n");
#endif
#endif
                return NULL;
        }
}

struct sym *lookup_variable( struct sym *sy, struct sym *parent ) {
        struct sym *tmp;
        /* sy = lookup(sy->name,SYTB_VAR); */
        if (parent->litflag == 2) {
                parent = (struct sym *)((struct vref *)parent)->sym;
        }
        while (1) {
                tmp = sy;
                while (tmp && tmp->parent != parent)
                        tmp=tmp->parent;
                if (tmp && tmp->parent == parent)
                        break;
                if (sy->clone == NULL)
                        break;
                sy = sy->clone;
        }
        return sy;
}

struct sym *lookup_parent( struct sym *sy, struct sym *parent ) {
        struct sym *tmp;
        if (parent->litflag == 2) {
                parent = (struct sym *)((struct vref *)parent)->sym;
        }
        while (sy) {
                tmp = sy;
                while (tmp && tmp->parent != parent)
                        tmp=tmp->parent;
                if (tmp && tmp->parent == parent)
                        break;
                sy = sy->clone;
        }
        return sy;
}

struct sym *lookup_for_redefines( struct sym *sy ) {
        struct sym *tmp;
        if (curr_field->parent == NULL) {
                tmp = lookup(sy->name,SYTB_VAR);
        }
        else {
                tmp = lookup_variable(sy,curr_field->parent);
        }
        return tmp;
}

void clear_symtab() {
        struct sym *sy,*sy1,*tmp;
        /* struct lit *lt,*lt1,*ltmp; */
        int i;
        for (i=0;i<HASHLEN;i++) {
            for (sy1=vartab[i];sy1!=NULL;) {
                        for (sy=sy1->clone;sy;) {
                                if (sy) {
                                        tmp = sy;
                                        sy = sy->clone;
                                        free(tmp);
                                }
                        }
                        tmp = sy1;
                        sy1 = sy1->next;
                        free(tmp);
            }
                vartab[i] = NULL;
        }
        for (i=0;i<HASHLEN;i++) {
            for (sy1=labtab[i];sy1!=NULL;) {
                        for (sy=sy1->clone;sy;) {
                                if (sy) {
                                        tmp = sy;
                                        sy = sy->clone;
                                        free(tmp);
                                }
                        }
                        tmp = sy1;
                        sy1 = sy1->next;
                        free(tmp);
            }
                labtab[i] = NULL;
        }
        /*for (i=0;i<HASHLEN;i++) {
            for (lt1=littab[i];lt1!=NULL;) {
                        ltmp = lt1;
                        lt1 = lt1->next;
                        free(ltmp);
            }
                littab[i] = NULL;
        }*/
}

/* clear_offset() is called when starting a new program segment */
void clear_offsets() {
        stack_offset=0;        
        global_offset=4;        
        literal_offset=0;
        data_offset=0;
        linkage_offset=0;
        using_offset=8;
        refmod_slots = 0;
        free_list(fields_list);
        fields_list=NULL;
        free_list(files_list);
        files_list=NULL;
        /* clear all current paragraphs/sections and fields */
        curr_paragr=NULL;
        curr_section=NULL;
        curr_field=NULL;
        /* free tmpvar storage */
        tmpvar_offset = 0;
        tmpvar_max = 0;
        stabs_started=0;
}

/*** we need this because the literal string is already stored ***/
char sign_to_char( int digit ) {
        char cDigit;
        if (!digit)
                cDigit = '}';
        else if (digit==0x80)
                cDigit = '{';
        else if (digit>0)
                cDigit = (char)('A'+digit-1);
        else
                cDigit = (char)('J'-digit-1);
        return cDigit;
}

int char_to_sign( char ch ) {
        if (ch=='{') 
           return 0;
        if (ch=='}') 
           return 0x80;
        if (ch<'J') 
           return (int)(ch-'A'+1);
        return (-(int)(ch-'J'+1));
}

void invert_literal_sign( struct lit *sy ) {
        char *s = sy->name;
        int off = strlen(sy->name) - 1;
        s[off] = sign_to_char(-(s[off]-'0'));
}

void check_decimal_point( struct lit *lit ) {
        char *s=lit->name;
        if ((decimal_comma && strchr(s,'.')) || 
                (!decimal_comma && strchr(s,','))) {
                        yyerror("wrong decimal point character in numeric literal");
        }
}

int is_variable ( struct sym *sy ) {
        int r=0;
        if (sy->litflag == 0) {
                switch (sy->type) {
                case '8': /* 88 field */
                case DTYPE_DISPLAY: /* numeric */
                case DTYPE_ALPHA: /* alpha */
                case DTYPE_BININT: /* binary (comp/computational) */
                case DTYPE_PACKED: /* compacted (comp-3/comptational-3) */
                case DTYPE_ACCEPT_DISPLAY: /* screen data */
                case DTYPE_EDITED: /* edited */
                case DTYPE_GROUP: /* group */
                case DTYPE_FLOAT: /* float(comp-1 4 bytes) / double(comp-2 8 bytes) */
                case DTYPE_ALPHANUMERIC: /* alphanum */
                        r = 1;
                        break;
                default:
                        r = 0;
                        break;
                }
        }
        return r;
}

int is_subscripted ( struct sym *sy ) {
        if (sy->occurs_flg) /* the item itself "occurs" */
                return 1;
        while (sy->parent != NULL) { /* some parenr "occurs" */
                sy=sy->parent;
                if (sy->occurs_flg)
                        return 1;
        }
        return 0;
}

int adjust_linkage_vars(int start_offset) {
        struct sym *sy,*sy1;
        int i;
        int offset = start_offset;
        
        for (i=0;i<HASHLEN;i++) {
            for (sy1=vartab[i];sy1!=NULL;sy1=sy1->next) {
                        for (sy=sy1;sy;sy=sy->clone) {
                                if (sy->parent == NULL && sy->linkage_flg == 1) {
                                        sy->linkage_flg = -offset;
                                        offset += 4;
                                }
                        }
            }
        }
        return offset;
}

/*
 *   Put a field to its initial value.
 *   It can be a value specified by 'value' or an initialization value
 *   If it is a group field, initialize all the fields under it. 
 */
static void set_initial_value(struct sym *sy) {
        int j,nb_fields;
        struct init_str init_templ;

        if (sy->uval6.redefines) return;
#ifdef DEBUG_COMPILER
        if (sy->value)
                fprintf(o_src,"#  initial value to field '%s' = '%s' \n",
                        sy->name,sy->value->name);
        else
                fprintf(o_src,"#  initial value to field '%s', INITIALIZED \n",
                        sy->name);
#endif
        /* Initialize a non-group field */
        if (sy->level == 77 || (sy->level == 1 && sy->uval7.son == NULL)) {
                if (sy->value)
                        gen_move_init((struct sym *)sy->value,sy); /* initial value */
                else
                        gen_initialize(sy);  /* initialize at spaces or 0 */
                return;
        }

        /* Initialize a group to zero or blank */
        init_ctype = ' '; init_val = -1;
        nb_fields = get_nb_fields(sy, 1);
        if (init_ctype != '&' && init_ctype != ' ' && init_val > 1) {
                gen_init_str(sy, init_ctype, symlen(sy));
                return;
        }

        /* Initialize a group's fields one by one */
#ifdef DEBUG_COMPILER
        fprintf(o_src,"#  istrp = malloc(%d) nb_fields = %d\n",
                nb_fields * sizeof(init_templ),nb_fields);
#endif
        istrp = malloc(nb_fields * sizeof(init_templ));
        build_init_str(sy, nb_fields);
        for(j=0;j<nb_fields;j++) {
                if (istrp->ent[j].value != NULL) {
                        unsigned saved_loc = istrp->ent[j].sy->uval2.location;
                        istrp->ent[j].sy->uval2.location = istrp->ent[j].location;
                        gen_move_init((struct sym *)istrp->ent[j].sy->value
                                    ,istrp->ent[j].sy);
                        istrp->ent[j].sy->uval2.location = saved_loc;
                        }
                }
        free(istrp);
        istrp=NULL;
        return;
}

/*
// Initialize all the variables at the beginig of the program
*/
void do_init_val() {
  struct sym *sy,*sy1,*v;
  int i;
  char typ;
  for (i=0;i<HASHLEN;i++)
     for (sy1=vartab[i];sy1!=NULL;sy1=sy1->next)
         for (sy=sy1;sy!=NULL;sy=sy->clone)
            if (sy->type!='F' && sy->type!='8' && 
                sy->type!='K' && sy->type!='J' ) {
                v=sy;
                typ = v->type;
                if (typ=='F' || typ=='R' || typ=='K' || typ=='J'
                        || typ=='8')
                        continue;
                /* Here only work with level 1 and 77 */
                if (v->level != 1 && v->level != 77) continue;
                /* Don't initialize fields in linkage */
                if (v->linkage_flg) continue;
                        
                set_initial_value(v);
            }
}

void save_field_in_list(struct sym *sy) {

 struct list *list;

 if (fields_list==NULL) {
    list = (struct list *)malloc(sizeof(struct list));
    last_field = fields_list = list;
    list->next = NULL;
    list->var = sy;
 }
 else {
    list = (struct list *)malloc(sizeof(struct list));
    list->var = sy;
    list->next = NULL;
    last_field->next = list;
    last_field = list;
 }
}

void save_literal( struct lit *v, int type ) {
        char *s;
        char *dp;
        int piclen;
        /* if (v->type) return; */ /* already saved */
        s=v->name;
        piclen=3; /* assume 'X'-only literal */
        if ((type==DTYPE_DISPLAY) && (*(v->name+v->len-1) > '9')) {
                piclen+=2; /* we need space for the sign picture char */
        }
        if (type!=DTYPE_ALPHANUMERIC && (dp=strchr(s,decimal_char()))!=NULL) {
                piclen += 4; /* reserve space for 'V' and decimal part */
                v->decimals=v->len-(int)(dp-s)-1;
        }
        else v->decimals=0;
/*        v->pscale=0; */
        if (type==DTYPE_ALPHANUMERIC && v->len > 255) {
                piclen += (v->len / 255)*2;
        }
        v->type = type;
        /****** save literal in fields list for later *******/
        save_field_in_list( (struct sym *)v );
        /******** save address of const string ************/
        v->location = literal_offset;
        v->sec_no = SEC_CONST;
        if (v->decimals)
                literal_offset += v->len;
                        /* it's already one chr larger (decimal point) */
        else
                literal_offset += v->len+1;
        /******** save address of field descriptor ********/
        v->descriptor = literal_offset;
        literal_offset += HTG_fld_desc_len + piclen;
        /* printf("save_literal: name=%s, type=%c, offset=%x, piclen=%d\n",
                v->name, v->type, v->descriptor, piclen); */
}

void save_named_sect( struct sym *sy ) {
        /*char *s;
        char *dp;*/
        struct named_sect *nsp;

        nsp = (struct named_sect *)malloc(sizeof(struct named_sect));
        sy->flags.external=1;
        nsp->sec_no = next_available_sec_no++;
        nsp->os_name = sy->name;
        nsp->os_name = (char *)malloc(strlen(nsp->os_name)+1);
        strcpy(nsp->os_name,sy->name);
        chg_underline(nsp->os_name);
        nsp->next = named_sect_list;
        named_sect_list = nsp;
        curr_sec_no = nsp->sec_no;
        sy->sec_no = curr_sec_no;
}

struct lit *save_special_literal( char val, char picc, char *nick ) {
        struct lit *v;
        v = (struct lit *)install(nick,SYTB_LIT,0);        
        if (v->type) return NULL; /* already saved */
        v->decimals = 0;
/*        v->pscale=0; */
        v->type = picc;
        v->nick = (char *)malloc(2);
        v->nick[0] = val;
        v->nick[1] = 0;
        v->len = 1;
        v->all = 0;
        save_field_in_list( (struct sym *)v );
        v->location = literal_offset;
        v->sec_no = SEC_CONST;
        literal_offset += 2; /* we have only 1-char special literals */
        v->descriptor = literal_offset;
        literal_offset += (HTG_fld_desc_len + 3);
        return v;
}

void define_switch_field( struct sym *sy, struct sym *sy2) 
{
   
        curr_field = NULL;
        define_field(77, sy);
        curr_field->len=2; curr_field->type=DTYPE_BININT; curr_field->uval1.decimals=0;
        picture[0] = '9';
        picture[1] = 4;
        picture[2] = 0;
        curr_field->ix_desc = sy2;
        update_field(curr_field);
        sy2->defined=1;                /* switch number is implicitly defined */
        switches_list = insert_list(switches_list, sy);
}


struct sym *define_std_filename(int value)
{
   char stdname[64];
   struct lit *v;
   
/*   sprintf(stdname, "%%STD_FILE_NUM%d%%", value);*/  
/*   sprintf(stdname, "STD_FILE_NUM%02d", value);  */  

   switch ( value)
   {
     case 0:
/*       sprintf(stdname, "STANDARD_INPUT");  */    
       sprintf(stdname, "%%STANDARD_INPUT%%");    
       break;
     
     case 1:
/*       sprintf(stdname, "STANDARD_OUTPUT");  */    
       sprintf(stdname, "%%STANDARD_OUTPUT%%");    
       break;
     
     case 2:
     default:
/*       sprintf(stdname, "STANDARD_ERROR");  */    
       sprintf(stdname, "%%STANDARD_ERROR%%");    
       break;
   }
   
   
#if 0
#ifdef DEBUG_COMPILER
   fprintf(stderr, "debug : define_std_filename : file-name=%s\n", stdname);   
#endif   
#endif   

/*  v = (struct lit *)install(stdname, SYTB_LIT, 0); 
    save_literal(v, DTYPE_DISPLAY); */
   v = save_special_literal(' ','X', stdname); 
   v->all=0;
 
   return ((struct sym*)v);
}

struct lit *define_num_lit( int value ) {
   char tblmax[21];
   struct lit *v;
   
   sprintf(tblmax, "%d", value);
   v = (struct lit *)install(tblmax,SYTB_LIT,0);
   save_literal(v, DTYPE_DISPLAY);
   return v;
}

void save_switch_value( struct sym *sy, int value ) {
   struct lit *v;
   
   v = define_num_lit(value);
   define_field(88, sy);
   sy->value = v; sy->uval4.value2 = v;
}

void put_disp_list( struct sym *sy ) {
        struct list *list,*tmp;
#if 0
        if ( (!(sy->defined)) && (sy->litflag!=1) )
        {
          yyerror("variable %s not defined",sy->name);
        }
#ifdef DEBUG_COMPILER
        /* fprintf(o_src,"# put_disp_list: %s\n",sy->name); */
        fprintf(stderr, "debug : put_disp_list 0800 : name='%s'\n", sy->name); 
#endif
#endif
        list = (struct list *)malloc(sizeof(struct list));
        list->var = sy;
        list->next=NULL;
        if (disp_list==NULL)
                disp_list = list;
        else {
                tmp=disp_list;
                while (tmp->next != NULL) 
                    tmp=tmp->next;
                tmp->next = list;
        }
}

int pic_digits ( struct sym *sy, char target ) {
        char *p=NULL;
        int len=0;
        if (sy == NULL)
                return 0;
        if (sy->litflag) {
                len = strlen(sy->name);
                if (strchr(sy->name,decimal_char())) len--;
                if (strchr(sy->name,'+')) len--;
                if (strchr(sy->name,'-')) len--;
                /* printf("pic_digits: %s -> %d\n",sy->name,len); */
                return len;
        }
        else {
                p = sy->uval9.picstr;
                while (*p) {
                        if (*p++==target) {
                                len += *p++;
                        }
                        else
                                p++;
                }
        }
        /* printf("pic_digits: %s -> %d\n",sy->name,len); */
        return len;
}

/* Return the maximum length which might be occupied by a corresponding value */
int get_max_edt_len( struct sym * sy ) {
        int plen=0;
        
#ifdef DEBUG_COMPILER_LEVEL2       
        fprintf(o_src, "# htcobgen: get_max_edt_len: Name: %s, Length: %d, Type: %c, Pic[0]: %d\n", 
                       sy->name, sy->len, sy->type, sy->uval9.picstr[0]); 
#endif
        switch (sy->type)
        {
          case DTYPE_ALPHANUMERIC:
          case DTYPE_ALPHA:
          case DTYPE_EDITED:
          case DTYPE_GROUP:
          case DTYPE_ALPHANUMERICL:
          case DTYPE_ACCEPT_DISPLAY:
            plen=sy->len;
            break;

          case DTYPE_BININT:
          default:
            if (sy->uval9.picstr[0] == 0) {
                if (sy->len == 1) plen=2;
                if (sy->len == 2) plen=4;
                if (sy->len == 4) plen=18;
            }
            else {
                plen=pic_digits(sy, '9');
                if (sy->uval9.picstr[0] == 'S') plen++;
                if (sy->uval1.decimals > 0) plen++;
                if (sy->pscale != 0) plen=plen + abs(sy->pscale);
            }
            break;
        }
        return plen;                
}

int query_comp_len( struct sym * sy ) {
        int plen;
        char target = '9';
        
        if (sy->stype == 'X') {
                target = 'X';
                plen=pic_digits(sy, 'X');
                /* for the time being, picture is altered just before output
                   in htcobemt.c */
                /* strcpy(sy->uval9.picstr,"9\xa"); */ /* max picture for 4 bytes */
                return plen;                
        }
        else {
        if ((plen=pic_digits(sy, '9')) <= 2)
                return 1;
        if (plen <= 4)
                return 2;
        if (plen <= 9)
                return 4;
        return 8;
        }
}

int symlen(struct sym *sy) 
{
  int rlen;
  /*
  if (sy->type == DTYPE_PACKED) {
     rlen = (sy->len / 2) + 1;
  }
  else { */
    if (sy->litflag == 1)
       rlen = ((struct lit *)sy)->len;
    else
       rlen = sy->len;
  //}

  return rlen;
}

/* Returns the minimum number of 9 to hold a complete value */
int sym_min_pic( struct sym *sy ) {

        if (sy->type != DTYPE_BININT) 
                return sy->len;
        if (sy->stype != 'X')
                return pic_digits(sy, '9');
        switch (symlen(sy)) {
        case 1: return 3;
        case 2: return 5;
        case 4: return 10;
        case 8: return 19;
        }
        return pic_digits(sy, '9');
}

/* Initialize file structure 'struct sym*' */
struct sym* file_select_clause_init(struct sym *sy, int flag_optional) 
{
  sy->type='F';                      /* mark as file variable */
  sy->uval5.pic=0;                   /* suppose not indexed yet */
  sy->defined=1;
  sy->parent=NULL;                   /* assume no STATUS yet this is "file status" var in files */
  sy->uval1.organization = 2;
  sy->uval3.access_mode = 1;
  sy->times=-1;
  sy->uval8.alternate=NULL;          /* reset alternate key list */
  sy->flags.optional=flag_optional;  /* according to keyword */
  sy->refmod_redef.declarative=NULL; /* no declarative yet */
  
  return sy;
}

/* Note: input 'struct sym *sy' is actually 'curr_file' or current file */
int file_select_clause_verify(struct sym *sy)
{
  int r=0;
  
  if ((sy->flags.file_printer == 1) &&
      ((sy->uval1.organization != TCB_FILE_ORGANIZATION_SEQUENTIAL) && (sy->uval1.organization != TCB_FILE_ORGANIZATION_LINESEQUENTIAL))) {
     yyerror("Files defined as PRINTER must be of SEQUENTIAL or LINE-SEQUENTIAL organization type");
     return (1);
  }

  if (((sy->flags.file_stdin == 1)  || 
       (sy->flags.file_stdout == 1) ||
       (sy->flags.file_stderr == 1)) &&
      ((sy->uval1.organization != TCB_FILE_ORGANIZATION_SEQUENTIAL) && (sy->uval1.organization != TCB_FILE_ORGANIZATION_LINESEQUENTIAL)) 
     )  {
     yyerror("Standard INPUT/OUTPUT/ERROR files must be of SEQUENTIAL or LINE-SEQUENTIAL organization type");
     return (2);
  }

  if ((sy->uval1.organization==TCB_FILE_ORGANIZATION_INDEXED) && !(sy->ix_desc)) {
     yyerror("indexed file must have a record key");
     return (3);
  }

  /* Redefine Standard INPUT/OUTPUT/ERROR and PRINTER files as organization LINE-SEQUENTIAL */
  if ((sy->flags.file_stdin == 1)  || 
      (sy->flags.file_stdout == 1) ||
      (sy->flags.file_stderr == 1) ||
      (sy->flags.file_printer == 1)
     )  {
     sy->uval1.organization = TCB_FILE_ORGANIZATION_LINESEQUENTIAL;
  }

  return r;
} 

void add_alternate_key(struct sym *sy, int duplicates) 
{
  struct sym *f = curr_file;
  struct alternate_list *alt, *new; 
  
  new = malloc(sizeof(struct alternate_list));
  new->key = sy;
  new->duplicates = duplicates;
  new->next = NULL;
  
//  alt = (struct alternate_list *)f->uval8.alternate;
//  if (alt == NULL) {
  if (f->uval8.alternate == NULL) {
     // new->next = NULL; //
     /* f->uval8.alternate = (struct sym *)new;  */   
     f->uval8.alternate = new;     
  }
  else {
     alt = f->uval8.alternate;     
     while (alt->next != NULL) {
     //while (alt != NULL) {
         alt = alt->next;      
     }
     // new->next = NULL; //
     alt->next = new;                
  }
  
/*  

  alt = f->uval8.alternate;
  new = malloc(sizeof(struct alternate_list));
  new->next = alt;
  new->key = sy;
  new->duplicates = duplicates;
  f->uval8.alternate = new;
*/  

}

struct list *
insert_list( struct list *l, void *item ) {
        struct list *tmp;
        if (l==NULL) {
                l=malloc(sizeof(struct list));
                l->var = item;
                l->next = NULL;
        }
        else {
                for (tmp=l; tmp->next != NULL; tmp=tmp->next) ;
                tmp->next = malloc(sizeof(struct list));
                tmp->next->var = item;
                tmp->next->next = NULL;
        }
        return l;
}

struct gvar_list *
gvar_list_append (struct gvar_list *l, struct sym *item, int linenum) {
        struct gvar_list *tmp;

#if 0
#ifdef DEBUG_COMPILER
        fprintf(stderr, "debug : gvar_list_append 0965 : l=%ld, name='%s'\n", l, item->name); 
/*        fprintf(stderr, "debug : gvar_list_append 0965 :\n");  */
#endif   
#endif   

        if (l==NULL) {
           tmp=malloc(sizeof(struct gvar_list));
           tmp->u.sym = item;
           tmp->attribute = linenum;
           tmp->next = NULL;
        }
        else {
           for (tmp=l; tmp->next != NULL; tmp=tmp->next) ;
           tmp->next = malloc(sizeof(struct gvar_list));
           tmp=tmp->next;
           tmp->u.sym = item;
           tmp->attribute = linenum;
           tmp->next = NULL;
           tmp=l;
        }

        return tmp;
}

void sort_keys_append(struct sym *fname, struct gvar_list *l)
{
   struct gvar_list *gvar_w1, *gvar_w2;
   struct sym *sym_wk;

     for(gvar_w1=l; gvar_w1 != NULL; gvar_w1=gvar_w1->next) {
        for(gvar_w2=gvar_w1->u.gvar; gvar_w2 != NULL; gvar_w2=gvar_w2->next) {
           sym_wk = gvar_w2->u.sym;
           sym_wk->uval3.direction = gvar_w1->attribute;
           sym_wk->uval4.sort_data = fname->uval4.sort_data; 
           /* fname->uval4.sort_data = sym_wk; */
           /* fname->uval4.sort_data = (void *) sym_wk; */
           fname->uval4.sort_data = sym_wk; 
        }
     }
}

struct gvar_list *
sort_key_list_create (struct gvar_list *item, int atrbt) {
        struct gvar_list *l;

        l=malloc(sizeof(struct gvar_list));
        l->u.gvar    = item;
        l->attribute = atrbt;
        l->next      = NULL;

        return l;
}

struct gvar_list *sort_keys_list_append (struct gvar_list *l, struct gvar_list *item) {
        struct gvar_list *tmp;

        if (l == NULL) {
            l = item;
         }
         else {
           for (tmp=l; tmp->next != NULL; tmp=tmp->next) ;
           tmp->next = item;
        }

        return l;
}

void free_list( struct list *l ) {
        struct list *tmp;
        while(l!=NULL) {
                tmp = l->next;
                free(l);
                l=tmp;
        }
        l=NULL;
}

void mark_decl_list( struct list *l ) {
        struct list *tmp;
        while(l!=NULL) {
                ((struct sym *)l->var)->refmod_redef.declarative = curr_section;
                tmp = l->next;
                free(l);
                l=tmp;
        }
}

struct scr_info *
alloc_scr_info() {
        struct scr_info *new;
        struct scr_info *parent_info = NULL;
        
        if (curr_field && curr_field->parent)
           parent_info = curr_field->parent->scr;

        new = malloc(sizeof(struct scr_info));
        new->attr = 0;
        new->line = 0;
        new->column = 0;
        new->foreground = NULL;
        new->background = NULL;
        new->color = NULL;
        new->line_var = NULL;
        new->column_var = NULL;
        new->from = NULL;
        new->to = NULL;
        new->line_sign = 0;
        new->column_sign = 0;
        new->size = NULL;
        
        if (parent_info) /* If exists copy information from parent field */
        {
         new->attr = parent_info->attr;
         new->foreground = parent_info->foreground;
         new->background = parent_info->background;
         new->color = parent_info->color;
         /* new->line = parent_info->line; */
         /* new->column = parent_info->column; */
         /* new->line_var = parent_info->line_var; */
         /* new->column_var = parent_info->column_var; */
         /* new->line_sign = parent_info->line_sign; */
         /* new->column_sign = parent_info->column_sign; */
        }
        if (parent_info && curr_field->parent->uval7.son != curr_field)
        {
          new->line = new->column = 0; 
          new->line_var = new->column_var = NULL; 
          new->line_sign = new->column_sign = 0 ; 
        }
        return new;
}

struct inspect_before_after *
alloc_inspect_before_after( struct inspect_before_after *ba,
        int before_after, struct sym *var ) {
        if (ba == NULL) {
                ba = malloc(sizeof(struct inspect_before_after));        
                ba->before = ba->after = NULL;
        }
        if (before_after == 1) { /* before given */
                if (ba->before) {
                        yyerror("only one BEFORE phrase can be given");
                }
                else {
                        ba->before = var;
                }
        }
        else if (before_after == 2) { /* after given */
                if (ba->after) {
                        yyerror("only one AFTER phrase can be given");
                }
                else {
                        ba->after = var;
                }
        }
        return ba;
}

struct converting_struct *
alloc_converting_struct( struct sym *fromvar, struct sym *tovar,
        struct inspect_before_after *ba ) {
        struct converting_struct *new;
        new = malloc(sizeof(struct converting_struct));
        new->fromvar = fromvar;
        new->tovar = tovar;
        new->before_after = ba;
        return new;
}

struct tallying_list *
alloc_tallying_list( struct tallying_list *tl, struct sym *count,
        struct tallying_for_list *tfl) {
        struct tallying_list *new;
        new = malloc(sizeof(struct tallying_list));
        new->next = tl;
        new->tflist = tfl;
        new->count = count;
        return new;
}

struct tallying_for_list *
alloc_tallying_for_list( struct tallying_for_list *tfl, int options,
        struct sym *forvar, struct inspect_before_after *ba ) {
        struct tallying_for_list *new;
        new = malloc(sizeof(struct tallying_for_list));
        new->next = tfl;
        new->options = options;
        new->forvar = forvar;
        new->before_after = ba;
        return new;
}

struct replacing_list *
alloc_replacing_list( struct replacing_list *rl, int options,
        struct replacing_by_list *rbl, struct sym *byvar,
        struct inspect_before_after *ba) {

        struct replacing_list *new;
        new = malloc(sizeof(struct replacing_list));
        new->next = rl;
        new->options = options;
        new->replbylist = rbl;
        new->byvar = byvar;
        new->before_after = ba;
        return new;        
}

struct replacing_by_list *
alloc_replacing_by_list( struct replacing_by_list *rbl,
        struct sym *replvar, struct sym *byvar,
        struct inspect_before_after *ba) {
        struct replacing_by_list *new;
        new = malloc(sizeof(struct replacing_by_list));
        new->next = rbl;
        new->replvar = replvar;
        new->byvar = byvar;
        new->before_after = ba;
        return new;
}


struct unstring_delimited *
alloc_unstring_delimited ( short int all, struct sym *var ) {
        struct unstring_delimited *ud;
        ud = malloc(sizeof(struct unstring_delimited));
        ud->next = NULL;
        ud->var = var;
        ud->all = all;
        return ud;
}

struct unstring_destinations *alloc_unstring_dest( struct sym *var, struct sym *delim, struct sym *count ) {
        struct unstring_destinations *ud;
        ud = malloc(sizeof(struct unstring_destinations));
        ud->next = NULL;
        ud->var = var;
        ud->delim = delim;
        ud->count = count;
        return ud;
}

struct string_from *alloc_string_from( struct sym *var, struct sym *delim ) {
        struct string_from *sf;
        sf = malloc(sizeof(struct string_from));
        sf->next = NULL;
        sf->var = var;
        sf->delim=delim;
        return sf;
}

void gen_unstring( struct sym *var, struct unstring_delimited *delim,
        struct unstring_destinations *dest, struct sym *ptr,
        struct sym *tally ) {
        
        struct unstring_destinations *dest1;
        struct unstring_delimited *delim1;
        
        fprintf(o_src,"# UNSTRING %s\n",var->name);
        gen_loadvar( (struct sym *)NULL ); /* mark the end of destinations */
        while (dest)  {
                gen_loadvar( dest->count );
                gen_loadvar( dest->delim );
                gen_loadvar( dest->var );
                dest1 = dest;
                dest = dest->next;
                free(dest1);
        }
        gen_loadvar( (struct sym *)NULL ); /* mark the end of delimiters */
        while (delim)  {
                push_immed(delim->all);        /* push "all" flag */
                gen_loadvar( delim->var );
                delim1 = delim;
                delim = delim->next;
                free(delim1);
        }
        gen_loadvar(tally);
        gen_loadvar(ptr);
        gen_loadvar(var);
        asm_call("tcob_unstring");
}

void gen_stringcmd( struct string_from *sf, struct sym *sy, struct sym *ptr ) {
        struct string_from *sf1;
        fprintf(o_src,"# STRING into %s\n",sy->name);
        gen_loadvar( (struct sym *)NULL ); /* mark the end of variables */
        /* DELIMITED BY SIZE implied at end of source list */
        if (sf && (sf->delim == (struct sym *)-1))
                sf->delim = (struct sym *)NULL;
        /* Load the string_from source list */
        while (sf)  {
                gen_loadvar( sf->delim );
                gen_loadvar( sf->var );
                sf1 = sf;
                sf = sf->next;
                /* Delimiter of -1 means use previous delimiter */
                if (sf && (sf->delim == (struct sym *)-1))
                        sf->delim = sf1->delim;
                free(sf1);
        }
        gen_loadvar(ptr);
        gen_loadvar(sy);
        asm_call("tcob_stringcmd");
}

static void gen_display_screen_item(struct sym *sy, int main) {
        struct sym *tmp, *var = sy;
        struct list *tmpl;

        if (var->litflag == 2 || var->litflag == 4) {
                var = ((struct vref *)var)->sym;
                if (var->litflag == 2)
                        var = ((struct vref *)var)->sym;
        }
        if ( (!(var->defined)) && (var->litflag!=1) ) {
          yyerror("variable %s not defined",var->name);
        }
        if (main) {
          fprintf(o_src, "#                      Screen Section: %s\n", var->name);
        } 
        if (var->uval7.son == NULL) {
          fprintf(o_src, "#                      Screen Field: %s\n", var->name);
          gen_call_scr_process(var);
        }
        else {
                for (tmp=var->uval7.son;tmp!=NULL;tmp=tmp->uval8.brother) {
                        gen_display_screen_item(tmp,0);        
                }
        }
        if (main) {
                asm_call("tcob_display_screen");
                if (disp_list->next) {
                        yyerror("we do not handle more than one screen");
                }
                tmpl=disp_list;
                disp_list=disp_list->next;
                free(tmpl);
        }
}

void gen_display_screen(int nl) {
        gen_display_line(1,nl);
}

void gen_display_line(int dupon, int nl) {
        struct list *tmp;
        /*int len;*/
        int dspflags;
        int first=1, nlst, i, opts=1;
        struct sym *sy, **arlist;

        if (disp_list) {
                /* separate screen displays from display of regular variables */
                sy = (struct sym *)disp_list->var;
                if (disp_list && sy->litflag!=1) {
                        if (sy->litflag != 4 && sy->litflag != 2 && sy->scr) {
                                gen_display_screen_item(disp_list->var,1);
                                return;
                        }
                }
                /* continue w/a regular variable display */
                if (nl & SCR_ERASE_EOL) {
                        if (screen_io_enable == 0) {
                                push_immed(dupon);
                                asm_call("tcob_display_erase");
                        }
                }
        }

        if (screen_io_enable == 0) {
           nlst = 0;
           tmp = disp_list;
           while (tmp != NULL) {
             nlst++;
             tmp = tmp->next;
           } 
/*           arlist = (struct sym **)malloc((sizeof(struct sym *) * nlst) + 1); */
           arlist = (struct sym **)malloc( sizeof(struct sym *) * (nlst + 1) );
           for (i=0; i<= nlst; i++) {
              arlist[i] = NULL;
           }           
        }
        i=0;       
        while (disp_list != NULL) {
                sy=disp_list->var;
        
                /* if ( (!(sy->defined)) && (sy->litflag==0) ) */
                if ( (sy->litflag==0) && (!(sy->defined)) )
                {
                  yyerror("variable %s not defined,%d",sy->name,sy->litflag);
                }
                
                if (screen_io_enable == 0) {
                       arlist[i] = sy;
                       i++;
                }
                else {
                        dspflags = nl;
                        if (first) {
                                first=0;
                        }
                        else {
                                dspflags &= ~2; /* avoid erasing from now on */
                        }
                        if (disp_list->next != NULL) {
                                dspflags |= 1; /* allow newline only at the last item */
                        }
                        push_immed(dspflags);
                        gen_loadvar( sy );
                        asm_call("tcob_display_curses");
                }

                tmp=disp_list;
                disp_list=disp_list->next;
                free(tmp);
                tmp=NULL;

        }

        if (screen_io_enable == 0) {
           gen_loadvar((struct sym *) NULL); 
           /* Push the variables on the stack in reverse order */
           for (i = nlst - 1; i >= 0; i--) {
               sy=arlist[i];
               gen_loadvar(sy);
               arlist[i]=NULL;
           }
           /* Add the stdout/stderr and newline options */
           push_immed(dupon);
           if (!(nl & SCR_NO_ADVANCING))
              opts = 2;
           push_immed(opts);
           free(arlist);
           asm_call("tcob_vdisplay");
        }
}
/* 
 * Call the function to set the display or accept position 
 */
void gen_gotoxy_expr( ) {
        stackframe_cnt += 16; /* eliminate the coords expressions */
        asm_call("tcob_goxy_expr");
}
void gen_gotox_expr( ) {
        stackframe_cnt += 8; /* eliminate the coord expressions */
        asm_call("tcob_gox_expr");
}
void gen_gotoy_expr( ) {
        stackframe_cnt += 8; /* eliminate the coord expressions */
        asm_call("tcob_goy_expr");
}

void gen_accept( struct sym *sy, int echo, int main ) 
{
        struct sym *tmp, *var = sy;
        int not_screen_mask = SCR_ERASE_EOL | SCR_ERASE_EOS | SCR_NO_ADVANCING;

        if ((echo & not_screen_mask) != echo) { /* determine if the options require curses */
           screen_io_enable++;
           HTG_prg_uses_term=1;
        }

#ifdef DEBUG_COMPILER_LEVEL2       
        fprintf(stderr, "debug : gen_accept : 1550.100 : var->name=%s, var->litflag=%d;\n", var->name, var->litflag);
#endif
        /* This method will not work for indexed identifiers */
        if (var->litflag == 2 || var->litflag == 4) {
           var = ((struct vref *)var)->sym;
#ifdef DEBUG_COMPILER_LEVEL2       
           fprintf(stderr, "debug : gen_accept : 1550.200 : var->name=%s, var->litflag=%d;\n", var->name, var->litflag);
#endif
           if (var->litflag == 2) {
               var = ((struct vref *)var)->sym;
#ifdef DEBUG_COMPILER_LEVEL2       
               fprintf(stderr, "debug : gen_accept : 1550.300 : var->name=%s, var->litflag=%d;\n", var->name, var->litflag);
#endif
           }
        }

        if (var->scr) { /* screen or screen-item accept */
           if (main) {
              fprintf(o_src, "#                      Screen Section: %s\n", var->name);
           }
           if (var->uval7.son == NULL) {
              fprintf(o_src, "#                      Screen Field: %s\n", var->name);
              gen_call_scr_process(var);
           } 
           else {
              for (tmp=var->uval7.son;tmp!=NULL;tmp=tmp->uval8.brother) {
                 gen_accept(tmp,echo,0);        
              }
           }
           if (main)
              asm_call("tcob_accept_screen");
        } 
        else {
           push_immed(echo);
           if (screen_io_enable == 0) {
              gen_loaddesc(sy);
              if (!HTG_libcob) 
                 gen_loadloc(sy);
              asm_call("tcob_accept_std");
           }
           else {
              fprintf(o_src,"\tmovl\t$c_base%d+%u, %%eax\n", pgm_segment,var->descriptor);
              push_eax();
              /* This will not work for indexed identifiers 
              gen_loadloc(var); 
              */
              gen_loadloc(sy);
              asm_call("tcob_accept_curses");
           }
        }
}

void gen_accept_from_chron( struct sym *sy, int date_fmt, int is_yyyy ) {
        push_immed( is_yyyy );
        push_immed( date_fmt );
        gen_loadvar( sy );
        asm_call("tcob_accept_chron");
}

void gen_accept_from_inkey( struct sym *sy ) {
        gen_loadloc( sy );
        asm_call("tcob_accept_inkey");
}

void gen_accept_from_cmdline( struct sym *sy ) {

        struct sym *sy1;

        gen_loadvar( sy );
/*
        fprintf(o_src,"\tmovl\t12(%%ebp), %%eax\n");
        push_eax();
        fprintf(o_src,"\tmovl\t8(%%ebp), %%eax\n");
        push_eax();
*/
        asm_call("tcob_accept_cmd_line");

/*      Set RETURN-CODE with the value returned by
 *      the "accept_cmd_line" function, which is stored
 *      in register %eax
*/

        if ((sy1 = lookup(SVAR_RETURN_CODE, SYTB_VAR)) != NULL) {
           if (sy1->sec_no == SEC_STACK) {
               fprintf(o_src,"\tleal\t-%d(%%ebp), %%edx\n",sy1->uval2.location);
           }
           else {
              /* fprintf(o_src,"\tleal\tw_base%d+%d, %%edx\n", */
              fprintf(o_src,"\tleal\tw_base%d_%d, %%edx\n",
                          pgm_segment, sy1->uval2.location);
           }
           fprintf(o_src,"\tmovl\t%%eax, (%%edx)\n");
        }
}

void gen_accept_env_var( struct sym *sy, struct sym *v) 
{        
        struct sym *sy2;
                
        gen_loadvar(v);
        gen_loadvar(sy);
        asm_call("tcob_accept_env_var");

/*      Set RETURN-CODE with the value returned by
 *      the "accept_env_var" function, which is stored
 *      in register %eax
 */

        if ((sy2 = lookup(SVAR_RETURN_CODE, SYTB_VAR)) != NULL) {
           if (sy2->sec_no == SEC_STACK) {
               fprintf(o_src,"\tleal\t-%d(%%ebp), %%edx\n",sy2->uval2.location);
           }
           else {
              /* fprintf(o_src,"\tleal\tw_base%d+%d, %%edx\n", */
              fprintf(o_src,"\tleal\tw_base%d_%d, %%edx\n",
                          pgm_segment, sy2->uval2.location);
           }
           fprintf(o_src,"\tmovl\t%%eax, (%%edx)\n");
        }

}

/******** structure allocation for perform info(s) ***********/

struct perf_info *
create_perf_info(struct sym *sy1, struct sym *sy2, unsigned long lj, unsigned long le) {
        struct perf_info *rf;
        rf = malloc(sizeof(struct perf_info)); 
        rf->pname1 = sy1; 
        rf->pname2 = sy2;  
        rf->ljmp = lj;
        rf->lend = le;
        return rf;
}

struct perform_info *
create_perform_info(void) {
        struct perform_info *rf;
        rf = malloc(sizeof(struct perform_info)); 
        rf->pf[0] = NULL;
        rf->pf[1] = NULL;
        rf->pf[2] = NULL;
        rf->pf[3] = NULL;
        rf->pf[4] = NULL;
        rf->pf[5] = NULL;
        return rf;
}

char *check_perform_variables(struct sym *sy1, struct perform_info *pi1) {

        int i, j, k;
                 
         j=0;
        for (i=0; i<6; i++) {
            if (pi1->pf[i] != NULL) {
                j++;
#if 0
#ifdef DEBUG_COMPILER
               fprintf(stderr,
                       "debug trace: check_perform_variables: var(%d:%d) '%s'\n", 
                       i, j, pi1->pf[i]->pname2->name); 
#endif
#endif
            }
        }
        
        for (i=0; i<j ; i++) {
#if 0
#ifdef DEBUG_COMPILER
            fprintf(stderr,
                    "debug trace: check_perform_variables: var1='%s' var2(%d)='%s'\n", 
                     sy1->name, 
                     i, pi1->pf[i]->pname2->name); 
#endif
#endif
            if (strcmp(sy1->name, pi1->pf[i]->pname2->name) == 0) {
               return sy1->name;
            }
        }
        
        for (i=0; i<j ; i++) {
            for (k=i+1; k<j; k++) {

#if 0
#ifdef DEBUG_COMPILER
               fprintf(stderr,
                       "debug trace: check_perform_variables: var1(%d)='%s' var2(%d)='%s'\n", 
                       i, pi1->pf[i]->pname2->name, 
                       k, pi1->pf[k]->pname2->name); 
#endif
#endif
                if (strcmp(pi1->pf[i]->pname2->name, pi1->pf[k]->pname2->name) == 0) {
                   return pi1->pf[i]->pname2->name;
                }
            }
        }

        return NULL;
}

/******** structure allocation for math verbs variables ***********/

struct expr *
create_expr( char op, struct expr *left, struct expr *right ) {
        struct expr *e=malloc(sizeof(struct expr));
        struct list *list = (struct list *)malloc(sizeof(struct list));
        e->litflag=5;
#ifdef DEBUG_COMPILER
        fprintf(o_src,"#create_expr: [0x%x] %c ",(int)e,op);
        if (left->litflag < 2) {
                fprintf(o_src,"%s ",((struct sym *)left)->name);
        }
        else {
                fprintf(o_src,"0x%x ",(int)left);
        }
        if (right->litflag < 2) {
                fprintf(o_src,"%s\n",((struct sym *)right)->name);
        }
        else {
                fprintf(o_src,"0x%x\n",(int)right);
        }
#endif
        e->op=op;
        e->left=left;
        e->right=right;
        expr_list = list;
        list->next = NULL;
        list->var = e;
        return e;
}

void free_expr( struct expr *e ) {
        if ((e != NULL) && (e->litflag == 5)) {
#ifdef DEBUG_COMPILER
        fprintf(o_src,"#free_expr: %c (%d,%d) ",e->op,
                e->left->litflag,e->right->litflag);
        if (e->left->litflag < 2) {
                fprintf(o_src,"%s ",((struct sym *)e->left)->name);
        }
        else {
                fprintf(o_src,"0x%x ",(int)e->left);
        }
        if (e->right->litflag < 2) {
                fprintf(o_src,"%s\n",((struct sym *)e->right)->name);
        }
        else {
                fprintf(o_src,"0x%x\n",(int)e->right);
        }
#endif
                free_expr(e->right);
                free_expr(e->left);
                free(e);
        }
        e=NULL;
}

void free_expr_list() {
        struct list *list;
        struct expr *e;
        for (list=expr_list;list!=NULL;list=list->next) {
                e=(struct expr *)list->var;
                free_expr(e);
        }
        expr_list = NULL;
}

struct math_var *
create_mathvar_info(struct math_var *mv, struct sym *sy, unsigned int opt) {
        
        struct math_var *rf, *tmp1, *tmp2;

/*        if (is_numeric_sy(sy) == 0) {
           yyerror("invalid (non numeric) variable or literal \'%s\' used in arithmetic verb", sy->name);
           return mv;
        }
*/                
        rf = malloc(sizeof(struct math_var)); 
        rf->sname = sy; 
/*        rf->rounded = opt; */
        rf->opts = opt;
        rf->next = NULL;

#if 0
#ifdef DEBUG_COMPILER
        fprintf(stderr,
                "debug trace : create_mathvar_info 0: sy->name=%s;\n", 
                sy->name); 
        fprintf(stderr,
                "debug trace : create_mathvar_info 1: rf->sname->name=%s;\n", 
                rf->sname->name); 
#endif
#endif

        if (mv == NULL) {
           tmp2=rf;
           tmp1=rf;
        }
        else {
           tmp1=mv; 
           tmp2=mv; 
           while(tmp1->next != NULL) {
#if 0
#ifdef DEBUG_COMPILER
              fprintf(stderr,
                "debug trace : create_mathvar_info 2: tmp1->sname->name=%s;\n", 
                tmp1->sname->name); 
#endif
#endif
              tmp1=tmp1->next;
           }
           tmp1->next = rf;
        }

#if 0
#ifdef DEBUG_COMPILER
        fprintf(stderr,
                "debug trace : create_mathvar_info 3: tmp1->sname->name=%s;\n", 
                tmp1->sname->name); 
#endif
#endif

#if 0
#ifdef DEBUG_COMPILER
           tmp1=tmp2; 
           while(tmp1 != NULL) {
              fprintf(stderr,
                "debug trace : create_mathvar_info 4: tmp1->sname->name=%s;\n", 
                tmp1->sname->name); 
              tmp1=tmp1->next;
           }
#endif
#endif

        return tmp2;
}

void delete_mathvar_info(struct math_var *mv) {
        
        struct math_var *tmp1, *tmp2;

        tmp1=mv; 
        while(tmp1 != NULL) {
#if 0
#ifdef DEBUG_COMPILER
              fprintf(stderr,
                "debug trace : delete_mathvar_info 1: tmp1->sname->name=%s;\n", 
                tmp1->sname->name); 
#endif
#endif
              tmp2=tmp1->next;
              tmp1->next  = NULL;
              tmp1->sname = NULL;
              free(tmp1);
              tmp1 = tmp2;
        }
}

struct invalid_key_element *
gen_before_invalid_key ()
{
  struct invalid_key_element *p = malloc (sizeof (struct invalid_key_element));
  p->lbl1 = loc_label++;
  p->lbl2 = loc_label++;
  p->lbl3 = loc_label++;
  gen_jmplabel (p->lbl1);
  gen_dstlabel (p->lbl2);
  return p;
}

struct invalid_key_element *
gen_after_invalid_key (struct invalid_key_element *p)
{
  gen_jmplabel (p->lbl3);
  return p;
}

struct invalid_keys *
gen_invalid_keys (struct invalid_key_element *p1, struct invalid_key_element *p2)
{
  struct invalid_keys *p = malloc (sizeof (struct invalid_keys));
  p->invalid_key = p1;
  p->not_invalid_key = p2;
  if (p1) gen_dstlabel (p1->lbl1);
  if (p2) gen_dstlabel (p2->lbl1);
  return p;
}

/******** functions to generate math verbs ***********/

void gen_add( struct sym *s1, struct sym *s2, int rnd ) {
        push_immed(rnd);
        gen_loadvar( s2 );
        gen_loadvar( s1 );
        asm_call("tcob_add");
}

void gen_subtract( struct sym *s1, struct sym *s2, int rnd ) {
        push_immed(rnd);
        gen_loadvar( s2 );
        gen_loadvar( s1 );
        asm_call("tcob_subtract");
}

void gen_multiply( struct sym *s1, struct sym *s2, struct sym *s3, int rnd  ) {
        push_immed(rnd);
        gen_loadvar( s3 );
        gen_loadvar( s2 );
        gen_loadvar( s1 );
        asm_call("tcob_multiply");
}

void gen_compute1(struct math_var *vl1, struct sym *sy1)
{
       push_expr(sy1);
       while (vl1->next != NULL) {
         assign_expr(vl1->sname, vl1->opts, '0'); 
         vl1 = vl1->next;
       }
       assign_expr(vl1->sname, vl1->opts, '1'); 

}

void gen_compute2(struct math_var *vl1, struct sym *sy1, struct math_ose *v1)
{
       /* option flags: 1=rounded, 2=on_size_error */ 
       int opts;
       opts = vl1->opts | MATH_OPT_ON_SIZE_ERROR;
       
       gen_dstlabel(v1->lbl4); /* generate bypass jump label */
       push_expr(sy1);
       while (vl1->next != NULL) {
         assign_expr(vl1->sname, opts, '0'); 
         math_on_size_error3(v1, '0');
         vl1 = vl1->next;
       }
       assign_expr(vl1->sname, opts, '1'); 
       math_on_size_error3(v1, '1');
       math_on_size_error5(v1);
}

void gen_add1(struct math_var *vl0, struct math_var *vl2, struct math_ose *v1)
{
       struct math_var *vl1;
       /* option flags: 1=rounded, 2=on_size_error */ 
       int opts;

       /* ON SIZE ERROR option only */
       if (v1 != NULL) {
          /* generate bypass jump label */
          gen_dstlabel(v1->lbl4);
       }
       while (vl2 != NULL) {
         push_expr(vl2->sname);
         vl1=vl0;
         while (vl1 != NULL) {
            push_expr(vl1->sname);
            add_expr();
            vl1 = vl1->next;
         }
         if (v1 != NULL) {
            opts = vl2->opts | MATH_OPT_ON_SIZE_ERROR;
         }
         else {
            opts = vl2->opts;
         }
         assign_expr(vl2->sname, opts, '1'); 
         /* ON SIZE ERROR option only */
         math_on_size_error3(v1, '1');
         vl2 = vl2->next;
       }
       math_on_size_error5(v1);
       
}

void gen_add2(struct math_var *vl1, struct math_var *vl2, struct sym *sy1, struct math_ose *v1)
{
       int i=0;
       /* option flags: 1=rounded, 2=on_size_error */ 
       int opts;
       
       /* ON SIZE ERROR option only */
       if (v1 != NULL) {
          /* generate bypass jump label */
          gen_dstlabel(v1->lbl4); /* generate bypass jump label */
       }
       if (sy1 != NULL) {
          push_expr(sy1);
          while (vl1 != NULL) {
               push_expr(vl1->sname);
               add_expr();
               vl1 = vl1->next;
          }
       }
       else {
          push_expr(vl1->sname);
          vl1 = vl1->next;
          i = 1;
          while (vl1 != NULL) {
               push_expr(vl1->sname);
               add_expr();
               vl1 = vl1->next;
               i++;
          }
          if (i < 2) {
             yyerror("At least 2 variables and/or numeric literals required in ADD statement");
          }
       }
       while (vl2->next != NULL) {
         if (v1 != NULL) {
            opts = vl2->opts | MATH_OPT_ON_SIZE_ERROR;
         }
         else {
            opts = vl2->opts;
         }
         assign_expr(vl2->sname, opts, '0'); 
         /* ON SIZE ERROR option only */
         math_on_size_error3(v1, '0');
         vl2 = vl2->next;
       }
       if (v1 != NULL) {
          opts = vl2->opts | MATH_OPT_ON_SIZE_ERROR;
       }
       else {
          opts = vl2->opts;
       }
       assign_expr(vl2->sname, opts, '1'); 
       /* ON SIZE ERROR option only */
       math_on_size_error3(v1, '1');
       math_on_size_error5(v1);
}

void gen_add3(struct math_var *vl0, struct math_var *vl2, struct math_ose *v1)
{
       struct math_var *vl1;
       /* option flags: 1=rounded, 2=on_size_error */ 
       int opts;

       while (vl2 != NULL) {
         push_expr(vl2->sname);
         vl1=vl0;
         while (vl1 != NULL) {
            push_expr(vl1->sname);
            add_expr();
            vl1 = vl1->next;
         }
         if (v1 != NULL) {
            opts = vl2->opts | MATH_OPT_ON_SIZE_ERROR;
         }
         else {
            opts = vl2->opts;
         }
         assign_expr(vl2->sname, opts, '1'); 
         /* ON SIZE ERROR option only */
         math_on_size_error3(v1, '1');
         vl2 = vl2->next;
       }
       
}

void gen_subtract1(struct math_var *vl0, struct math_var *vl2, struct math_ose *v1)
{
       struct math_var *vl1;
       /* option flags: 1=rounded, 2=on_size_error */ 
       int opts;

       /* ON SIZE ERROR option only */
       if (v1 != NULL) {
          /* generate bypass jump label */
          gen_dstlabel(v1->lbl4); 
       }
       while (vl2 != NULL) {
         push_expr(vl2->sname);
         vl1=vl0;
         while (vl1 != NULL) {
            push_expr(vl1->sname);
            subtract_expr();
            vl1 = vl1->next;
         }
         if (v1 != NULL) {
            opts = vl2->opts | MATH_OPT_ON_SIZE_ERROR;
         }
         else {
            opts = vl2->opts;
         }
         assign_expr(vl2->sname, opts, '1'); 
         /* ON SIZE ERROR option only */
         math_on_size_error3(v1, '1');
         vl2 = vl2->next;
       }
       math_on_size_error5(v1);
}

void gen_subtract2(struct math_var *vl1, struct math_var *vl2, struct sym *sy1, struct math_ose *v1)
{
       /* option flags: 1=rounded, 2=on_size_error */ 
       int opts;

       /* ON SIZE ERROR option only */
       if (v1 != NULL) {
          /* generate bypass jump label */
          gen_dstlabel(v1->lbl4); 
       }
       push_expr(sy1);
       while (vl1 != NULL) {
            push_expr(vl1->sname);
            subtract_expr();
            vl1 = vl1->next;
       }
       while (vl2->next != NULL) {
         if (v1 != NULL) {
            opts = vl2->opts | MATH_OPT_ON_SIZE_ERROR;
         }
         else {
            opts = vl2->opts;
         }
         assign_expr(vl2->sname, opts, '0'); 
         /* ON SIZE ERROR option only */
         math_on_size_error3(v1, '0');
         vl2 = vl2->next;
       }
       if (v1 != NULL) {
          opts = vl2->opts | MATH_OPT_ON_SIZE_ERROR;
       }
       else {
          opts = vl2->opts;
       }       
       assign_expr(vl2->sname, opts, '1'); 
       /* ON SIZE ERROR option only */
       math_on_size_error3(v1, '1');
       math_on_size_error5(v1);
}

void gen_subtract3(struct math_var *vl0, struct math_var *vl2, struct math_ose *v1)
{
       struct math_var *vl1;
       /* option flags: 1=rounded, 2=on_size_error */ 
       int opts;

       while (vl2 != NULL) {
         push_expr(vl2->sname);
         vl1=vl0;
         while (vl1 != NULL) {
            push_expr(vl1->sname);
            subtract_expr();
            vl1 = vl1->next;
         }
         if (v1 != NULL) {
            opts = vl2->opts | MATH_OPT_ON_SIZE_ERROR;
         }
         else {
            opts = vl2->opts;
         }
         assign_expr(vl2->sname, opts, '1'); 
         /* ON SIZE ERROR option only */
         math_on_size_error3(v1, '1');
         vl2 = vl2->next;
       }
}

void gen_multiply1(struct math_var *vl1, struct sym *sy1, struct math_ose *v1)
{
       /* option flags: 1=rounded, 2=on_size_error */ 
       int opts;

       /* ON SIZE ERROR option only */
       if (v1 != NULL) {
          /* generate bypass jump */
          gen_dstlabel(v1->lbl4);
       }
       while (vl1->next != NULL) {
         push_expr(sy1);
         push_expr(vl1->sname);
         multiply_expr();
         if (v1 != NULL) {
            opts = vl1->opts | MATH_OPT_ON_SIZE_ERROR;
         }
         else {
            opts = vl1->opts;
         }
         assign_expr(vl1->sname, opts, '1'); 
         /* ON SIZE ERROR option only */
         math_on_size_error3(v1, '1');
         vl1 = vl1->next;
       }
       push_expr(sy1);
       push_expr(vl1->sname);
       multiply_expr();
       if (v1 != NULL) {
          opts = vl1->opts | MATH_OPT_ON_SIZE_ERROR;
       }
       else {
          opts = vl1->opts;
       }
       assign_expr(vl1->sname, opts, '1'); 
       /* ON SIZE ERROR option only */
       math_on_size_error3(v1, '1');
       math_on_size_error5(v1);
}

void gen_multiply2(struct math_var *vl1, struct sym *sy1, struct sym *sy2, struct math_ose *v1)
{
       /* option flags: 1=rounded, 2=on_size_error */ 
       int opts;

       /* ON SIZE ERROR option only */
       if (v1 != NULL) {
          /* generate bypass jump label */
          gen_dstlabel(v1->lbl4);
       }
       push_expr(sy1);
       push_expr(sy2);
       multiply_expr();
       while (vl1->next != NULL) {
         if (v1 != NULL) {
            opts = vl1->opts | MATH_OPT_ON_SIZE_ERROR;
         }
         else {
            opts = vl1->opts;
         }
         assign_expr(vl1->sname, opts, '0'); 
         /* ON SIZE ERROR option only */
         math_on_size_error3(v1, '0');
         vl1 = vl1->next;
       }
       if (v1 != NULL) {
          opts = vl1->opts | MATH_OPT_ON_SIZE_ERROR;
       }
       else {
          opts = vl1->opts;
       }
       assign_expr(vl1->sname, opts, '1'); 
       /* ON SIZE ERROR option only */
       math_on_size_error3(v1, '1');
       math_on_size_error5(v1);
}

void gen_divide1(struct math_var *vl1, struct sym *sy1, struct math_ose *v1)
{
       /* option flags: 1=rounded, 2=on_size_error */ 
       int opts;

       /* ON SIZE ERROR option only */
       if (v1 != NULL) {
          /* generate bypass jump */
          gen_dstlabel(v1->lbl4);
       }
       while (vl1 != NULL) {
         push_expr(vl1->sname);
         push_expr(sy1);
         divide_expr();
         if (v1 != NULL) {
            opts = vl1->opts | MATH_OPT_ON_SIZE_ERROR;
         }
         else {
            opts = vl1->opts;
         }
         assign_expr(vl1->sname, opts, '1'); 
         /* ON SIZE ERROR option only */
         math_on_size_error3(v1, '1');
         vl1 = vl1->next;
       }
       math_on_size_error5(v1);
}

void gen_divide2(struct math_var *vl1, struct sym *sy1, struct sym *sy2, struct math_ose *v1)
{
       /* option flags: 1=rounded, 2=on_size_error */ 
       int opts;

       /* ON SIZE ERROR option only */
       if (v1 != NULL) {
          /* generate bypass jump label */
          gen_dstlabel(v1->lbl4);
       }
       push_expr(sy1);
       push_expr(sy2);
       divide_expr();
       while (vl1->next != NULL) {
         if (v1 != NULL) {
            opts = vl1->opts | MATH_OPT_ON_SIZE_ERROR;
         }
         else {
            opts = vl1->opts;
         }
         assign_expr(vl1->sname, opts, '0'); 
         /* ON SIZE ERROR option only */
         math_on_size_error3(v1, '0');
         vl1 = vl1->next;
       }
       if (v1 != NULL) {
          opts = vl1->opts | MATH_OPT_ON_SIZE_ERROR;
       }
       else {
          opts = vl1->opts;
       }
       assign_expr(vl1->sname, opts, '1'); 
       /* ON SIZE ERROR option only */
       math_on_size_error3(v1, '1');
       math_on_size_error5(v1);
}

void gen_divide4( struct sym *s1, struct sym *s2, struct sym *s3, struct sym *s4, int rnd, struct math_ose *v1 ) {

      /* [NOT]ON SIZE ERROR option */
      if (v1 != NULL) {
          /* generate bypass jump */
          gen_dstlabel(v1->lbl4);
      }
      push_immed(rnd);
      gen_loadvar( s4 );
      gen_loadvar( s3 );
      gen_loadvar( s2 );
      gen_loadvar( s1 );
      asm_call("tcob_divide1");
      math_on_size_error3(v1, '0');
      math_on_size_error5(v1);
}


/******** functions for subscripted var manipulation ***********/
struct vref *
create_subscripted_var( struct sym * sy, struct vref *subs ) {
        struct vref *ref;
        ref = malloc(sizeof(struct vref)); 
        ref->litflag = 2;
        ref->sym = sy;
        ref->next = subs;
        return ref;
}

struct vref *
create_subscript( struct sym *sy ) {
        struct vref *ref;
        ref = malloc(sizeof(struct vref)); 
        ref->litflag = ',';                /* the end of subscript is here */
         ref->sym = sy;                        /* this is the actual variable */
        ref->next = NULL;
        return ref;
}

struct vref *
add_subscript_item( struct vref *subs, char op, struct sym *item ) {
        struct vref *ref,*tmp;
        ref = malloc(sizeof(struct vref)); 
        tmp = subs;
        while (tmp->next) tmp=tmp->next;
        tmp->next = ref;
        ref->litflag = ',';
         ref->sym = item;        
        ref->next = NULL;
        tmp->litflag = op;
        return subs;
}

struct vref *
add_subscript( struct vref *ref, struct vref *subs ) {
        struct vref *tmp;
        tmp = subs;
        while (tmp->next) tmp=tmp->next;
        tmp->next = ref;
        return subs;
}

int
check_subscripts( struct sym *subs ) {
        struct vref *ref;
        struct sym *sy;
        sy = ((struct vref *)subs)->sym;
        for (ref=(struct vref *)subs;ref;ref=ref->next) {

#ifdef DEBUG_COMPILER
                fprintf(o_src,"#check_subscripts: symbol: %s, op: '%c'\n",
                        ((struct sym *)ref->sym)->name, 
                        ref->litflag == 2 ? 2 : ref->litflag );
#endif

                if (ref->litflag == ',') {
                        while (sy && !sy->occurs_flg) {
#ifdef DEBUG_COMPILER
                fprintf(o_src,"#check_subscripts: symbol: %s\n",
                        sy->name);
#endif
                                sy = sy->parent;
                        }
                        if (!sy) {
                                hterror(102,4,"check_subscripts: no parent found");
                                return 0; /* excess subscripts, error */
                        }
                        sy = sy->parent;
                }
        }
        while (sy && !sy->occurs_flg) /* any other subscripts needed ? */
                sy = sy->parent;
        return (sy == NULL) ? 1 : 0; 
}

void create_occurs_info(int min, int max, struct sym *depend) 
{
  curr_field->occurs = (struct occurs *)malloc(sizeof(struct occurs));
  curr_field->occurs->min = min;
  curr_field->occurs->max = max;
  curr_field->occurs->depend = depend;
  curr_field->times = max; 
  curr_field->occurs_flg++;
}

/******** functions for refmoded var manipulation ***********/
struct refmod *create_refmoded_var( struct sym * sy, struct sym *syoff, struct sym *sylen ) {
        struct refmod *ref;
        ref = malloc(sizeof(struct refmod)); 
        ref->litflag = 4;
        ref->sym = sy;
        ref->off = syoff;
        ref->len = sylen;
        ref->slot = refmod_slots++;
        return ref;
}

int check_refmods( struct sym *var ) {
        struct refmod *ref = (struct refmod *)var;
        struct sym *sy = ref->sym;

        if (sy->litflag == 2) sy=((struct vref *)sy)->sym;

        return (sy == NULL) ? 1 : 0;
}

struct sym *get_variable_item( struct sym *sy ) {
        struct sym *son,*item;
        if (sy->litflag != 0)
                return NULL;
        if (sy->occurs != NULL)
                return sy;
        for (son = sy->uval7.son; son != NULL; son = son->uval8.brother) {
                if ((item=get_variable_item(son)))
                        return item;
        }
        return NULL;
}

void adjust_desc_length ( struct sym *sy ) {
        int stack_save=stackframe_cnt;
        struct sym *item;
        stackframe_cnt = 0;
        item = get_variable_item(sy);
        /* push_immed(0); */
        gen_temp_storage(sizeof(struct fld_desc));
        gen_loaddesc1( item,0 );
        gen_loaddesc1( sy,0 );
        push_immed( item->occurs->max );
        push_immed( item->occurs->min );
        gen_loadvar( item->occurs->depend );
        asm_call("tcob_adjust_length");
        stackframe_cnt=stack_save;
        need_desc_length_cleanup=1;
}

void gen_loadloc( struct sym *sy_p ) {
        loadloc_to_eax( sy_p );
        push_eax();
}

void gen_loaddesc( struct sym *sy ) {
        gen_loaddesc1(sy,1);
}

void gen_loadvar( struct sym *sy ) {
         struct sym *var;
        if (sy == NULL) {
                push_immed(0);
        } else {
                var = sy;
                if (var->litflag == 2 || var->litflag == 4) {
                        var = ((struct vref *)var)->sym;
                        if (var->litflag == 2)
                                var = ((struct vref *)var)->sym;
                }
                if (!HTG_libcob) 
                   gen_loadloc( sy );
                gen_loaddesc( sy );
        }
}

int is_numeric_sy ( struct sym *sy ) {
        char type;
        if (sy->litflag == 2) { /* subscripted ? */
                sy = ((struct vref *)sy)->sym;
        }
        type = sy->type;
        if ((type==DTYPE_DISPLAY)||(type==DTYPE_BININT)
         || (type==DTYPE_PACKED) ||(type==DTYPE_FLOAT))
                return 1;
        return 0;
}

int is_numeric_dest_sy ( struct sym *sy ) {
        char type;
        if (sy->litflag == 2) { /* subscripted ? */
                sy = ((struct vref *)sy)->sym;
        }
        type = sy->type;
        if ((type==DTYPE_DISPLAY)
          ||(type==DTYPE_BININT)
          ||(type==DTYPE_PACKED)
          ||(type==DTYPE_FLOAT)
          ||(type==DTYPE_EDITED))
                return 1;
        return 0;
}

void gen_class_check ( struct sym *sy, int class ) {
        int invert=0;
        class &= ~(COND_UNARY | COND_CLASS);
        if (class & 4) { /* was it inverted (NOT) ? */
                class ^= 7;
                invert++;
        }
        if (class == CLASS_NUMERIC) {        
                /*if (!sy || is_numeric_sy(sy)) {
                */
                        if (sy)  /* don't save already pushed variable */
                                gen_loadvar(sy);
                        else 
                                stackframe_cnt += 8;
                        asm_call("tcob_check_numeric");
                        fprintf(o_src,"\tand\t%%eax,%%eax\n");
                /*}
                else {
                        yyerror("invalid NUMERIC class check");
                }*/
        }
        else {
                /* from now on, only alphabetic tests are allowed */
                /*if (is_numeric_sy(sy)) {
                        yyerror("invalid ALPHABETIC class check");
                }*/
                gen_loadvar(sy);
                switch (class) {
                case CLASS_ALPHABETIC:
                        asm_call("tcob_check_alphabetic");
                        break;
                case CLASS_ALPHABETIC_UPPER:
                        asm_call("tcob_check_upper");
                        break;
                case CLASS_ALPHABETIC_LOWER:
                        asm_call("tcob_check_lower");
                        break;
                default:
                        yyerror("unknown class condition");
                        break;
                }
                fprintf(o_src,"\tand\t%%eax,%%eax\n");
        }
        if (invert)
                gen_not();
}

void gen_inspect( struct sym *var, void *list, int operation ) {
        /*struct inspect_before_after *ba,*ba1;*/
        struct tallying_list *tl,*tl1;
        struct tallying_for_list *tfl,*tfl1;
        struct replacing_list *rl,*rl1;
        struct replacing_by_list *rbl,*rbl1;
        struct converting_struct *cv;

        if (!operation) {
                if (!list) return;
                fprintf(o_src,"# INSPECT TALLYING %s\n",var->name);
                gen_loadvar((struct sym *) NULL);
                tl = (struct tallying_list *)list;
                while (tl) {
                        tfl = tl->tflist;
                        push_immed(0);
                        while (tfl) {
                                gen_loadvar(tfl->before_after->after);
                                gen_loadvar(tfl->before_after->before);
                                if (tfl->options != INSPECT_CHARACTERS){
                                        gen_loadvar(tfl->forvar);
                                }                
                                push_immed(tfl->options);
                                free(tfl->before_after);
                                 tfl1 = tfl;
                                tfl = tfl->next;
                                free(tfl1);
                        }
                        gen_loadvar(tl->count);
                        tl1 = tl;
                        tl = tl->next;
                        free(tl1);
                        tl1=NULL;
                }
                gen_loadvar(var);
                asm_call("tcob_inspect_tallying");
        }
        else if (operation == 1) {
                if (!list) return;
                fprintf(o_src,"# INSPECT REPLACING %s\n",var->name);
                rl = (struct replacing_list *)list;
                push_immed(0);
                while (rl) {
                        if (rl->options == INSPECT_CHARACTERS) {
                                gen_loadvar(rl->before_after->after);
                                gen_loadvar(rl->before_after->before);
                                gen_loadvar(rl->byvar);
                                push_immed(rl->options);
                        }
                        else {
                                rbl = rl->replbylist;
                                while (rbl) {
                                        gen_loadvar(rbl->before_after->after);
                                        gen_loadvar(rbl->before_after->before);
                                        gen_loadvar(rbl->byvar);
                                        gen_loadvar(rbl->replvar);
                                        free(rbl->before_after);
                                        rbl1 = rbl;
                                        rbl = rbl->next;
                                        free(rbl1);
                                        push_immed(rl->options);
                                }
                        }
                        rl1 = rl;
                        rl = rl->next;
                        free(rl1);
                        rl1=NULL;
                }
                gen_loadvar(var);
                asm_call("tcob_inspect_replacing");
        } 
        else {
                fprintf(o_src,"# INSPECT CONVERTING %s\n",var->name);
                cv = (struct converting_struct *)list;
                gen_loadvar(cv->before_after->after);
                gen_loadvar(cv->before_after->before);
                gen_loadvar(cv->tovar);
                gen_loadvar(cv->fromvar);
                gen_loadvar(var);
                asm_call("tcob_inspect_converting");
        }
}

void gen_tcob_proto1( struct sym *sy ) {
        gen_loadvar(sy);
        asm_call("tcob_proto1");
}

void gen_tcob_proto2( struct sym *sy1, struct sym *sy2 ) {
        gen_loadvar(sy2);
        gen_loadvar(sy1);
        asm_call("tcob_proto2");
}

void gen_moves(struct sym *sy_src, struct gvar_list *gsylst) {
   struct gvar_list *sy_dst;
        
   for (sy_dst=gsylst; sy_dst->next != NULL; sy_dst=sy_dst->next) 
   {        
     gen_move (sy_src, sy_dst->u.sym);
   }        
   gen_move (sy_src, sy_dst->u.sym);
}

void gen_move( struct sym *sy_src, struct sym *sy_dst ) {
   long tmplabel=0;
   struct sym *var;
           
#ifdef DEBUG_COMPILER
        {
        struct sym *esys = sy_src, *esyd = sy_dst;
        if (esys->litflag == 4)
                esys = ((struct refmod *)esys)->sym;
        if (esyd->litflag == 4)
                esyd = ((struct refmod *)esyd)->sym;
        fprintf(o_src,"# MOVE %s --> ",sch_convert(esys->name));
        fprintf(o_src,"        %s\n",sch_convert(esyd->name));
        }
#endif
/*        Make sure BLANK test is done on a sym struct, and not a vref struct */
        var = sy_dst;
        if (var->litflag == 2 || var->litflag == 4) {
                var = ((struct vref *)var)->sym;
                if (var->litflag == 2)
                        var = ((struct vref *)var)->sym;
        }
/*        A blank when zero field is treated here instead of the RTS */
        if (var->flags.blank) {
           tmplabel=loc_label++;
           gen_compare(sy_src, EQUAL, (struct sym *)spe_lit_ZE);
           fprintf(o_src,"\tjnz\t.L%ld\n",tmplabel);
           gen_loadvar(sy_dst);
           gen_loadvar((struct sym *)spe_lit_SP);
           asm_call("tcob_move_x_x");
           gen_jmplabel(tmplabel+1);
           fprintf(o_src,".L%ld:\n",tmplabel);
        }
        /* default move */
        gen_loadvar( sy_dst );
        gen_loadvar( sy_src );
        /* an initial value of a literal X field into an numeric edited field
           should move straight instead of going thru an edition */
/*        if (sy_src->type == DTYPE_ALPHANUMERIC && sy_dst->type == DTYPE_EDITED) {
                asm_call("tcob_move_x_x");
                }
        else { */
                RTL_CALL("move");
/*                } */
#ifdef TODO
        if (sy_src->type == DTYPE_ALPHANUMERIC && sy_dst->type == DTYPE_EDITED) {
                asm_call("tcob_move_x_x");
        } else {
                asm_call("tcob_move");
        }
#endif
        if (tmplabel) {
                tmplabel=loc_label++;
                fprintf(o_src,".L%ld:\n",tmplabel);
        }
}

void gen_movelength( struct sym *sy1, struct sym *sy2 ) {
        if (sy1->litflag==1) {
                push_immed(((struct lit *)sy1)->len);
        }
        else {
                push_immed(sy1->len);
        }
        gen_loadvar( sy2 );
        asm_call("tcob_assign_int");
}

void gen_move_init( struct sym *sy_src, struct sym *sy_dst ) {
#ifdef DEBUG_COMPILER
        {
        struct sym *esys = sy_src, *esyd = sy_dst;
        fprintf(o_src,"# MOVE_INIT %s --> ",sch_convert(esys->name));
        fprintf(o_src,"        %s\n",sch_convert(esyd->name));
        }
#endif
        /* default move */
        gen_loadvar( sy_dst );
        gen_loadvar( sy_src );
        /* an initial value of a literal X field into an numeric edited field
           should move straight instead of going thru an edition */
        if (sy_src->type == DTYPE_ALPHANUMERIC && sy_dst->type == DTYPE_EDITED) {
                asm_call("tcob_move_x_x");
                }
        else {
                RTL_CALL("move");
                }
}

void gen_movecorr( struct sym *sy1, struct sym *sy2 ) {
        struct sym *t1,*t2;
        if (sy1->litflag || sy2->litflag) {
                yyerror("sorry we don't handle this case yet!");
                return;
        }
#ifdef DEBUG_COMPILER
    fprintf(o_src,"# MOVE CORR %s --> %s\n",sy1->name,sy2->name);
#endif
        t1 = sy1->uval7.son;
        /* repeat for all sons of sy1 */
        while (t1 != NULL) {
                if (!t1->uval6.redefines && t1->times==1) {
                        t2 = sy2->uval7.son;
                        /* repeat for all sons of sy2 */
                        while (t2 != NULL) {
                                if (!t2->uval6.redefines && t2->times==1) {
                                        if (strcmp(t1->name,t2->name) == 0) {
                                                if ((t1->type != DTYPE_GROUP)
                                                 || (t2->type != DTYPE_GROUP)) {
                                                        gen_move(t1,t2);
                                                }
                                                else {
                                                        gen_movecorr(t1,t2);
                                                }
                                        }
                                }
                                t2 = t2->uval8.brother;
                        }
                }
                t1 = t1->uval8.brother;
        }
}

struct sym *define_label( struct sym *lab, int lab_type,
        struct sym *parent, int parent_type ) {
        
        struct sym *tlab=lab;
        struct lit *tlit;
        struct sym *tparent;
        
        if (parent == NULL) {
                tparent = curr_section;
        }
        else {
                tparent = parent;
        }
        if (lab_type == 1) { 
            tlit = (struct lit *)lab;
            tlab=install(tlit->name,SYTB_LAB,0);
            }
        else {
            tlab=lab;
            }
            
        if (tlab->defined == 0) {
            tlab->defined = 2;
            tlab->parent = tparent;
            }
        else {
            if (parent_type == 1) { 
               tlit = (struct lit *)parent;
               tlab=install(tlit->name,SYTB_LAB,0);
               }
            if ((tlab=lookup_label(tlab,tparent))==NULL) {
               tlab = install(tlab->name,SYTB_LAB,2);
               tlab->defined=2;
               tlab->parent = tparent;
               }
            }
        return tlab;
}

void gen_addcorr( struct sym *sy1, struct sym *sy2, int rnd ) {
        struct sym *t1,*t2;
        if (sy1->litflag || sy2->litflag) {
                yyerror("sorry we don't handle this case yet!");
        }
#ifdef DEBUG_COMPILER
    fprintf(o_src,"# ADD CORR %s --> %s\n",sy1->name,sy2->name);
#endif
        t1 = sy1->uval7.son;
        /* repeat for all sons of sy1 */
        while (t1 != NULL) {
                if (!t1->uval6.redefines && t1->times==1) {
                        t2 = sy2->uval7.son;
                        /* repeat for all sons of sy2 */
                        while (t2 != NULL) {
                                if (!t2->uval6.redefines && t2->times==1) {
                                        if (strcmp(t1->name,t2->name) == 0) {
                                                if ((t1->type != DTYPE_GROUP)
                                                 && (t2->type != DTYPE_GROUP)) {
                                                        gen_add(t1,t2,rnd);
                                                }
                                                else {
                                                        gen_addcorr(t1,t2,rnd);
                                                }
                                        }
                                }
                                t2 = t2->uval8.brother;
                        }
                }
                t1 = t1->uval8.brother;
        }
}

void gen_addcorr1( struct math_var *mv1, struct math_var *mv2, int rnd, struct math_ose
*v1 ) {
        struct sym *sy1,*sy2;
        struct sym *t1,*t2;
        struct math_var *tmv1, *tmv2;
        static int addcorr_level = 0;
        
        if (mv1->sname->litflag || mv2->sname->litflag) {
                yyerror("sorry we don't handle this case yet!");
        }
#ifdef DEBUG_COMPILER
    fprintf(o_src,"# ADD CORR %s --> %s, lv %d\n",
      mv1->sname->name,mv2->sname->name,addcorr_level);
#endif
        /* ON SIZE ERROR option only */
        if (addcorr_level == 0 && v1 != NULL) {
          /* generate bypass jump label */
          gen_dstlabel(v1->lbl4);
        }
        addcorr_level++;
        sy1 = mv1->sname; sy2 = mv2->sname;
        t1 = sy1->uval7.son;
        /* repeat for all sons of sy1 */
        while (t1 != NULL) {
                if (!t1->uval6.redefines && t1->times==1) {
                        t2 = sy2->uval7.son;
                        /* repeat for all sons of sy2 */
                        while (t2 != NULL) {
                                if (!t2->uval6.redefines && t2->times==1) {
                                        if (strcmp(t1->name,t2->name) == 0) {
                                                tmv1 = create_mathvar_info(NULL, t1, 0);
                                                tmv2 = create_mathvar_info(NULL, t2, 0);
                                                if ((t1->type != DTYPE_GROUP)
                                                 && (t2->type != DTYPE_GROUP)) {
                                                  gen_add3(tmv1,tmv2,v1);
                                                }
                                                else {
                                                  gen_addcorr1(tmv1,tmv2,rnd,v1);
                                                }
                                                delete_mathvar_info(tmv1);
                                                delete_mathvar_info(tmv2);
                                        }
                                }
                                t2 = t2->uval8.brother;
                        }
                }
                t1 = t1->uval8.brother;
        }
        addcorr_level--;
        if (addcorr_level == 0) {
          math_on_size_error5(v1);
        }

}

void gen_subtractcorr( struct sym *sy1, struct sym *sy2, int rnd ) {
        struct sym *t1,*t2;
        if (sy1->litflag || sy2->litflag) {
                yyerror("sorry we don't handle this case yet!");
        }
#ifdef DEBUG_COMPILER
    fprintf(o_src,"# SUB CORR %s --> %s\n",sy1->name,sy2->name);
#endif
        t1 = sy1->uval7.son;
        /* repeat for all sons of sy1 */
        while (t1 != NULL) {
                if (!t1->uval6.redefines && t1->times==1) {
                        t2 = sy2->uval7.son;
                        /* repeat for all sons of sy2 */
                        while (t2 != NULL) {
                                if (!t2->uval6.redefines && t2->times==1) {
                                        if (strcmp(t1->name,t2->name) == 0) {
                                                if ((t1->type != DTYPE_GROUP)
                                                 && (t2->type != DTYPE_GROUP)) {
                                                        gen_subtract(t1,t2,rnd);
                                                }
                                                else {
                                                        gen_subtractcorr(t1,t2,rnd);
                                                }
                                        }
                                }
                                t2 = t2->uval8.brother;
                        }
                }
                t1 = t1->uval8.brother;
        }
}

void gen_subtractcorr1( struct math_var *mv1, struct math_var *mv2, int rnd,
                struct math_ose *v1 ) {
        struct sym *sy1,*sy2;
        struct sym *t1,*t2;
        struct math_var *tmv1, *tmv2;
        static int subcorr_level = 0;

        if (mv1->sname->litflag || mv2->sname->litflag) {
                yyerror("sorry we don't handle this case yet!");
        }
#ifdef DEBUG_COMPILER
    fprintf(o_src,"# SUB CORR %s --> %s, lv %d\n",
      mv1->sname->name,mv2->sname->name,subcorr_level);
#endif
        /* ON SIZE ERROR option only */
        if (subcorr_level == 0 && v1 != NULL) {
          /* generate bypass jump label */
          gen_dstlabel(v1->lbl4);
        }
        subcorr_level++;
        sy1 = mv1->sname; sy2 = mv2->sname;
        t1 = sy1->uval7.son;
        /* repeat for all sons of sy1 */
        while (t1 != NULL) {
                if (!t1->uval6.redefines && t1->times==1) {
                        t2 = sy2->uval7.son;
                        /* repeat for all sons of sy2 */
                        while (t2 != NULL) {
                                if (!t2->uval6.redefines && t2->times==1) {
                                        if (strcmp(t1->name,t2->name) == 0) {
                                                tmv1 = create_mathvar_info(NULL, t1, 0);
                                                tmv2 = create_mathvar_info(NULL, t2, 0);
                                                if ((t1->type != DTYPE_GROUP)
                                                 && (t2->type != DTYPE_GROUP)) {
                                                        gen_subtract3(tmv1,tmv2,v1);
                                                }
                                                else {
                                                        gen_subtractcorr1(tmv1,tmv2,rnd,v1);
                                                delete_mathvar_info(tmv1);
                                                delete_mathvar_info(tmv2);
                                                }
                                        }
                                }
                                t2 = t2->uval8.brother;
                        }
                }
                t1 = t1->uval8.brother;
        }
        subcorr_level--;
        if (subcorr_level == 0) {
          math_on_size_error5(v1);
        }
}

void gen_set_complex( struct sym *idx, int which, struct sym * var)
{
#ifdef DEBUG_COMPILER
        fprintf(o_src,"# set complex %s to %s\n",idx?idx->name:"(null)",
                var?var->name:"(null)");
#endif
        switch (which) {
        case SET_TO: /* just move this value */
                gen_move(idx, var);
                break;
        case SET_UP_BY: /* we need to add this value to the index */
                gen_add(idx,(struct sym *)define_num_lit(1),0);
                break;        
        case SET_DOWN_BY:
                gen_subtract(idx,(struct sym *)define_num_lit(1),0);
                break;
        default: 
                yyerror("SET option unavailable");
        }
}

void gen_set_list( struct list *idx, int which, struct sym *var,
        int adrof_idx, int adrof_var ) {
        struct sym * svar;
        
        while (idx != NULL) {
                svar = idx->var;
#ifdef DEBUG_COMPILER
                fprintf(o_src,"# SET %s \n",svar->name);
#endif
                gen_set(idx->var, which, var, adrof_idx, adrof_var);
                idx = idx->next;
        }
        vars_list = NULL;
}

/******* short-circuit conditional evaluators ********/
int 
gen_evaluate_start() {
        int i=loc_label++;
        fprintf(o_src,"# EVALUATE statement\n");
        return i;
}

int
subject_set_size(struct selsubject *ssbj) {
        int size=0;
        while (ssbj != NULL) {
                size++;
                ssbj=ssbj->next;
        }
        return size;
}

int
selection_object_size( int type ) {
        switch(type) {
        case SOBJ_EXPR:
        case SOBJ_NEGEXPR:
                return 8;
        case SOBJ_RANGE:
        case SOBJ_NEGRANGE:
                return 16;
        default:
                return 0;
        }
}

int
selection_subject_type(int level, struct selsubject *ssbj) {
        while (level--) { 
                ssbj=ssbj->next;
        }
        return ssbj->type;
}

void gen_perform( struct sym *sy ) {
        gen_perform_thru( sy, sy );
}
/*
// FIXME: BINARY (UN)SIGNED CHAR/SHORT/LONG/DOUBLE types 
// are not bounded by length but by size (ex: 9(3) > UNSIGNED-CHAR 0-255 > 9(2) )
*/
void set_usage( struct sym *sy, int usage ) {
    sy->stype=' ';
    switch (usage) {
        case USAGE_COMP1:
                sy->len = 4;
                sy->uval1.decimals=7;
                sy->type='U';
                sy->uval10.sign=1;
                /* default picture is 14 digits "S9(7)V9(7)" */
                strcpy((char *)picture,"S\x01\x39\x07\x56\x01\x39\x07");
                break;
        case USAGE_COMP2:
                sy->len = 8;
                sy->uval1.decimals=15;
                sy->type='U';
                sy->uval10.sign=1;
                /* default picture is 30 digits "S9(15)V9(15)" */
                strcpy((char *)picture,"\x39\x0f\x56\x01\x39\x0f");
                break;
        case USAGE_COMP3:
                sy->type='C';
                /* sy->len = (sy->len / 2) + 1; */
                sy->len = 0;
                break;
        case USAGE_COMP: 
                sy->stype='B'; 
                /* field length computed by query_comp_length() */
                sy->len = 0;
                sy->type='B'; /* binary field */
                break;
        case USAGE_COMP5:
                sy->stype='5'; 
                sy->len = 0;
                sy->type='B'; /* binary field */
                break;
        case USAGE_COMPX: 
                sy->stype='X'; 
                sy->len = 0;
                sy->type='B'; /* binary field */
                break;
        case USAGE_POINTER: /* POINTER */
                sy->len=4;
                sy->uval1.decimals=0;
                sy->type='B'; /* pointers are binary fields */
                /* pointer default picture: "9(10)" */
                strcpy((char *)picture,"9\x0a");
                sy->flags.is_pointer=1;
                break;
        case USAGE_BINARY_CHAR:
                sy->len = 1;
                sy->type='B'; 
                /* Picture is "S9(02)" */
                strcpy((char *)picture,"\x53\x01\x39\x02");
                break; 
        case USAGE_BINARY_UCHAR:
                sy->len = 1;
                sy->type='B'; 
                /* Picture is "9(02)" */
                strcpy((char *)picture,"\x39\x02");
                break; 
        case USAGE_BINARY_SHORT:
                sy->len = 2;
                sy->type='B'; 
                /* Picture is "S9(04)" */
                strcpy((char *)picture,"\x53\x01\x39\x04");
                break; 
        case USAGE_BINARY_USHORT:
                sy->len = 2;
                sy->type='B'; 
                /* Picture is "9(04)" */
                strcpy((char *)picture,"\x39\x04");
                break; 
        case USAGE_BINARY_LONG:
                sy->len = 4;
                sy->type='B'; 
                /* Picture is "S9(10)" */
                strcpy((char *)picture,"\x53\x01\x39\x0a");
                break; 
         case USAGE_BINARY_ULONG:
                sy->len = 4;
                sy->type='B'; 
                /* Picture is "9(10)" */
                strcpy((char *)picture,"\x39\x0a");
                break; 
       case USAGE_BINARY_DOUBLE:
                sy->len = 8;
                sy->type='B'; 
                /* Picture is "S9(18)" */
                strcpy((char *)picture,"\x53\x01\x39\x12");
               break; 
       case USAGE_BINARY_UDOUBLE:
                sy->len = 8;
                sy->type='B'; 
                /* Picture is "9(18)" */
                strcpy((char *)picture,"\x39\x12");
               break; 
        case USAGE_INDEX:
                sy->len = 4;
                sy->type='B'; 
                /* Picture is "S9(10)" */
                strcpy((char *)picture,"\x53\x01\x39\x0a");
                sy->uval1.decimals=0;
                sy->flags.is_index=1;
                break; 
    }
}

void gen_picture( void ) {
        if (curr_field->type!=DTYPE_GROUP) {
                curr_field->uval9.picstr = (char *)malloc(strlen((char *)picture)+1);
                strcpy(curr_field->uval9.picstr,(char *)picture);
        }
}

int save_pic_char ( char c, int i ) {
        char c1 = (char)toupper(c);
        unsigned int n;

        switch(c1) {
        case 'A':
                piccnt += i;
                if (curr_field->type != DTYPE_ALPHANUMERIC
                 && curr_field->type != DTYPE_EDITED)
                        curr_field->type = DTYPE_ALPHA;
                break;
        case 'X':
                piccnt += i;
                if (curr_field->type == DTYPE_DISPLAY)
                        curr_field->type = DTYPE_ALPHANUMERIC;
                break;
        case 'Z':
                curr_field->type=DTYPE_EDITED;
        case '9':
                piccnt += i;
                if (v_flag) decimals += i;
                n_flag=1;
                break;
        case 'V':
                if (v_flag)
                        yyerror("invalid picture: V already given");
                v_flag=1;
                break;
        case 'P':
                piccnt += i;
                if (!n_flag) 
                        v_flag=1; /* implicit V just before the first P */
                if (v_flag) {
                        decimals += i;
                        pscale += i;
                } else
                        pscale -= i;
                break;
        case 'S':
                sign=1;
                break;
        case '.':
        case ',':
        case '0':
        case 'B':
        case '/':
        case '+':
        case '-':
        case '*':
        case 'C':
        case 'R':
        case 'D':
                curr_field->type=DTYPE_EDITED;
                piccnt += i;
                break;
        default:
                if (c1==currency_symbol) {
                        curr_field->type=DTYPE_EDITED;
                        piccnt += i;
                        break;
                } else
                        return 0;
        } /* switch(c1) */
        
        if (picture[picix] == 0) { /* first char in PIC string? */
                picture[picix] = c1;
                picture[picix+1] = 0;
        }
        if (((char)picture[picix] != c1) || (picture[picix+1] == 255)) {
                picix += 2;
                picture[picix] = c1;
                picture[picix+1] = 0;
        }
        for (n = i + picture[picix+1]; n > 255; n -= 255) {
                picture[picix+1] = 255;
                picture[picix+2] = picture[picix];
                picix += 2;
        }
        picture[picix+1] = n;

        return 1;
}

void define_special_fields() 
{

        struct sym *sy, *tmp;
        struct lit *ly;

        sy   = install (SVAR_RETURN_CODE, SYTB_VAR, 0); 
        spe_lit_SP = save_special_literal(' ','X', "%SPACES%");
        spe_lit_LV = save_special_literal('\0','X', "%LOW-VALUES%");
        spe_lit_HV = save_special_literal('\xff','X', "%HIGH-VALUES%");
        spe_lit_ZE = save_special_literal('0','9', "%ZEROS%");
        spe_lit_01 = save_special_literal('1','9', "%ONE%");
        spe_lit_QU = save_special_literal('"','X', "%QUOTES%");
        spe_lit_SP->all=1;
        spe_lit_LV->all=1;
        spe_lit_HV->all=1;
        spe_lit_ZE->all=1;
        spe_lit_QU->all=1;

        ly = spe_lit_ZE;
                
/*        sy->len=5; */
        sy->len=4; 
        sy->uval1.decimals=0; 
        sy->pscale=0;
        sy->level=1;
        sy->defined=1;
        sy->type=DTYPE_BININT; /* assume numeric "usage is comp" item */
        sy->uval6.redefines = NULL;
        sy->linkage_flg=at_linkage;
        sy->sec_no=SEC_RETURN_CODE;
        sy->times=1;
        sy->occurs_flg=0;
        sy->flags.just_r=0;
        sy->flags.separate_sign=0;
        sy->flags.leading_sign=0;
        sy->flags.blank=0;
        sy->flags.value=1;
        sy->uval8.brother = NULL;
        sy->uval7.son = NULL;
        picture[0] = 'S';
        picture[1] = 1;
        picture[2] = '9';
        picture[3] = 6;
        picture[4] = 0;
        tmp=curr_field;
        curr_field = sy;

        curr_field->value=ly;
        curr_field->uval4.value2=ly;

        update_field(curr_field);
        close_fields();
        curr_field=tmp;

        /* Display trace on/off switch used by READY/RESET TRACE */
        if (HTG_debug_trace_flag == TRUE) {
           sy = install (SVAR_TRACE_DISPLAY, SYTB_VAR, 0); 

           sy->len=4; 
           sy->uval1.decimals=0; 
           sy->pscale=0;
           sy->level=1;
           sy->defined=1;
           sy->type=DTYPE_BININT; /* assume numeric "usage is comp" item */
           sy->uval6.redefines = NULL;
           sy->linkage_flg=at_linkage;
           sy->sec_no=SEC_STACK;
           sy->times=1;
           sy->occurs_flg=0;
           sy->flags.just_r=0;
           sy->flags.separate_sign=0;
           sy->flags.leading_sign=0;
           sy->flags.blank=0;
           sy->flags.value=1;
           sy->uval8.brother = NULL;
           sy->uval7.son = NULL;
           picture[0] = 'S';
           picture[1] = 1;
           picture[2] = '9';
           picture[3] = 6;
           picture[4] = 0;
           tmp=curr_field;
           curr_field = sy;

           curr_field->value=ly;
           curr_field->uval4.value2=ly;

           update_field(curr_field);
           close_fields();
           curr_field=tmp;
        }

        tmp=NULL;
        ly=NULL;

}


/*
 * Define a temp field of the desired type and desired lenght
 */
struct sym *define_temp_field(char desired_type, int desired_len) 
{
        struct sym *sy, *tmp;
/*        fprintf(stderr,"begin define temp %c\n",desired_type); */
#ifdef DEBUG_COMPILER
        fprintf(o_src,"#define_temp_field:%c,%d,SO:%d\n", 
                desired_type, desired_len, stack_offset);
#endif
        sy = malloc(sizeof(struct sym));
        memset(sy,0,sizeof(struct sym));
        sy->litflag=0;
        sy->name="%noname%";
        sy->len=desired_len; 
        sy->uval1.decimals=0; /* suppose no decimals yet */
        sy->pscale=0;
        sy->level=1;
        sy->type=desired_type;
        sy->uval6.redefines = NULL;
        sy->parent=NULL;
        sy->linkage_flg=0;
        sy->sec_no=SEC_DATA; /* not optimal; should be in stack */
        /* sy->sec_no=SEC_STACK; */
        sy->times=1;
        sy->occurs_flg=0;
        sy->occurs=NULL;
        sy->flags.just_r=0;
        sy->flags.separate_sign=0;
        sy->flags.leading_sign=0;
        sy->flags.blank=0;
        sy->uval8.brother = NULL;
        sy->uval7.son = NULL;
        switch(desired_type) {
                case DTYPE_ALPHANUMERIC:
                        picture[0] = 'X';
                        picture[1] = (char)sy->len; /* this make the max 255 */
                        picture[2] = 0;
                        break;
                case DTYPE_BININT: /* Make it signed */
                        picture[0] = 'S';
                        picture[1] = 1;
                        picture[2] = '9';
                        picture[3] = 9;
                        picture[4] = 0;
                        break;
                default:
                        picture[0] = '9';
                        picture[1] = (char)sy->len; /* this make the max 255 */
                        picture[2] = 0;
                        break;
        }
        tmp=curr_field;
        curr_field = sy;
        
        piccnt = sy->len;
        update_field(curr_field);
        close_fields();
        curr_field=tmp;
        tmp=NULL;
        
/*        fprintf(stderr,"end define_temp_field: %c\n",desired_type); */
        return sy;                
}

int  define_implicit_field(struct sym *sy, struct sym *sykey, int idxlen) 
{
        int i=1, /*m=0, d,*/ r=0;
        struct sym *tmp=NULL;
        char tmp_picture[3];
        struct index_to_table_list *i2t;
        
/*  Fix me: 
 *  This is a fix to ensure that indexes are defined as int (4 bytes) 
 *  For some reason if defined otherwise (1, 2 bytes) the search all 
 *  will not work.
 */

#if 0
        for (i=1; i<idxlen; i=i*10) {
           m++;
        }
        d = idxlen;
        while (d != 0) {
           m++;
           i=i*10;
           d = idxlen / i;
        }
#endif
        
/*  Fix me: 
 *  This is a fix to ensure that indexes are defined as int (4 bytes) 
 */
        /* sy->len=m; */
        sy->len=4; 

        sy->uval1.decimals=0; /* suppose no decimals yet */
        sy->pscale=0;
        sy->level=1;
        sy->type=DTYPE_BININT; /* assume numeric "usage is comp" item */
        sy->uval6.redefines = NULL;
        sy->flags.is_index=1; /* It is an index and should be initialized to ONE */
        sy->linkage_flg=0; /* should not go in the linkage section, never! */
/*        sy->sec_no=SEC_STACK; */
        sy->sec_no=default_sec_no;
        sy->times=1;
        sy->occurs_flg=0;
        sy->uval8.brother = NULL;
        sy->uval7.son = NULL;
        sy->flags.is_pointer = 0;
        sy->flags.blank = 0;
        
        memcpy (tmp_picture, picture, 3);
        picture[0] = '9';

/*  Fix me: 
 *  This is a fix to ensure that indexes are defined as int (4 bytes) 
 */
        /* picture[1] = (char)m; */
        picture[1] = (char)8;
        picture[2] = 0;
        tmp=curr_field;
        curr_field = sy;
        update_field(curr_field);
        close_fields();
        curr_field=tmp;
        memcpy (picture, tmp_picture, 3);
        tmp=NULL;
        
        i2t = malloc(sizeof(struct index_to_table_list));
        if (i2t == NULL) {
           return 0;
        }
        i2t->next = NULL;
        
        i = strlen(sy->name);
        i2t->idxname = malloc(i + 1);
        if (i2t->idxname == NULL) {
           free(i2t);
           i2t=NULL;
           return 0;
        }
        strcpy(i2t->idxname, sy->name); 

        i = strlen(curr_field->name);
        i2t->tablename = malloc(i + 1);
        if (i2t->tablename == NULL) {
           free(i2t->idxname);
           free(i2t);
           i2t=NULL;         
           return 0;
        }
        strcpy(i2t->tablename, curr_field->name); 
        
        i2t->seq = '0'; /* no sort sequence is yet defined for the table */
        i2t->keyname = NULL;
        if (sykey != NULL) {

           if (sykey->level == -1) {
              i2t->seq = '1';
           }

           if (sykey->level == -2) {
              i2t->seq = '2';
           }

           i = strlen(sykey->name);
           i2t->keyname = malloc(i + 1);
           if (i2t->keyname == NULL) {
              free(i2t->idxname);
              free(i2t->tablename);
              free(i2t);
              return 0;
           }
           strcpy(i2t->keyname, sykey->name); 
        }
                   
        if (index2table == NULL) {
          index2table = i2t;
        }
        else {
          i2t->next = index2table;
          index2table = i2t;
        }

#ifdef DEBUG_COMPILER
      fprintf(o_src, "#trace (define_implicit_field): index '%s' table '%s' tablekey '%s' sequence '%c'\n", 
                     i2t->idxname,
                     i2t->tablename,
                     i2t->keyname,
                     i2t->seq
                     );
#endif

        i2t = NULL;

        return r;                
}

struct sym* determine_table_index_name(struct sym *sy) 
{
        struct sym *rsy = NULL;
        struct index_to_table_list *i2t;

        i2t=index2table;
        while (i2t != NULL) {
            if (strcmp(i2t->tablename, sy->name) == 0) 
            {
              rsy = lookup(i2t->idxname, SYTB_VAR);
              i2t = NULL;
            }
            else {
              i2t=i2t->next;
            }
        }

#ifdef DEBUG_COMPILER
      if (rsy == NULL) {
           fprintf(o_src, "#trace (determine_table_index_name): table name '%s' index name '(NULL)'\n", 
                     sy->name
                     );
      }
      else {
           fprintf(o_src, "#trace (determine_table_index_name): table name '%s' index name '%s'\n", 
                     sy->name,
                     rsy->name
                     );
      }
#endif
        return rsy;
}


void define_field(int level, struct sym *sy) 
{
        struct sym *tmp;
        struct sym *tmp1=sy;
        struct sym *tmp2;
        
        if (sy == NULL) {
                sy = malloc(sizeof(struct sym));
                sy->name = "%noname%";
        }
#ifdef DEBUG_COMPILER_LEVEL
        fprintf(stderr, "# debug 1310.000 : define_field: name: %s, level: %d\n", sy->name, level); 
#endif
        if (level == 88) {
                sy->type='8';
                sy->defined=1;
                sy->len=0;
                sy->uval1.decimals=0;
                sy->pscale=0;
                sy->level=level;
                sy->linkage_flg=at_linkage;
                sy->sec_no=0;
                sy->times=1;
                sy->occurs_flg=0;
                sy->flags.just_r=0;
                sy->flags.separate_sign=0;
                sy->flags.leading_sign=0;
                sy->flags.blank=0;
                sy->uval8.brother=NULL;
                sy->uval7.son=NULL;
                if (curr_field->level==88) {
                   curr_field->uval8.brother=sy;
                   sy->parent=curr_field->parent;
                } else
                   sy->parent=curr_field;
                curr_field=sy;
                /* check_fields(sy); */
                return;
        }
        if (level == 1 || level == 77 || level == 66) 
           curr_sec_no = default_sec_no;
        sy->len=0;
        sy->uval1.decimals=0; /* suppose no decimals yet */
        sy->pscale=0;
        sy->level=level;
        sy->uval6.redefines = NULL;
        sy->linkage_flg=at_linkage;
        sy->sec_no=(at_linkage ? SEC_ARGS : curr_sec_no);
        sy->times=1;
        sy->occurs_flg=0;
        sy->flags.just_r=0;
        sy->flags.blank=0;
        sy->uval8.brother = NULL;
        sy->uval7.son = NULL;
        sy->uval9.picstr = NULL;

        /* Determine location in hierarchy */
        tmp=curr_field;
        if (tmp && ((level == 1) || (level == 77) || (level == 66)))
           close_fields();
        if (!tmp && (level > 1) && (level < 49)) {
           yyerror("data field hierarchy broken");
        }
        if (level != 77 && level != 66) {
                while (tmp != NULL && tmp->level > level) {
                        tmp1=tmp;
                        tmp=tmp->parent;
                }
                if (tmp == NULL)
                        sy->parent = NULL;
                else if (tmp->level < level) {
                        sy->parent=tmp;
                        if (tmp->uval7.son == NULL)
                                tmp->uval7.son = sy;
                        /*else
                                yyerror("malformed data hierarchy");*/
                        else {
                                tmp1->uval8.brother = sy;
                                sy->parent = tmp;
                                sy->level = tmp1->level;
                        }        
                } else {
                        tmp->uval8.brother = sy;
                        sy->parent = tmp->parent;
                }
        }
        
        /* is it already defined ? */
        if ((tmp2 = lookup(sy->name,SYTB_VAR)) != NULL) {
                if (tmp2 != sy && tmp2->parent == NULL && sy->parent == NULL)
                        yyerror("Variable %s already defined", tmp2->name);
        }

        /* Set initial values of inheritable fields */
        if (sy->parent) {
                struct sym *syp = sy->parent;
                sy->type                = syp->type;
                sy->flags.separate_sign = syp->flags.separate_sign;
                sy->flags.leading_sign  = syp->flags.leading_sign;
        } else {
                sy->type                = DTYPE_DISPLAY;
                sy->flags.separate_sign = 0;
                sy->flags.leading_sign  = 0;
        }

        curr_field=sy;
}

void update_renames_field(struct sym *sy1, struct sym *sy2) {
        struct sym *sy = curr_field;

        sy->uval7.son = NULL;
        sy->parent = sy1->parent;
        sy->uval6.redefines = sy1;
        if (sy2 == NULL) {
                sy->type = sy1->type;
                sy->uval2.location = sy1->uval2.location;
                sy->len = sy1->len;
                if (sy1->type == DTYPE_GROUP) {
                        sy->uval5.pic = 0;
                        sy->descriptor = literal_offset;
                        literal_offset += FLD_DESC_SIZE0;
                }
                else {
                        /* We should really reuse the original descriptor */
                        /* sy->descriptor = sy1->descriptor; */
                        sy->uval9.picstr = sy1->uval9.picstr;
                        sy->descriptor = literal_offset;
                        literal_offset += FLD_DESC_SIZE1;
                        sy->uval5.pic = literal_offset;
                        literal_offset += (strlen(sy1->uval9.picstr)+1);
                }
        }
        else {
                sy->type = DTYPE_GROUP;
                sy->uval2.location = sy1->uval2.location;
                sy->len = sy2->uval2.location - sy1->uval2.location + sy2->len;
                sy->uval5.pic = 0;
                sy->descriptor = literal_offset;
                literal_offset += FLD_DESC_SIZE0;
        }
        /* save_field_in_list(sy); */
        /* curr_field=NULL;        // so that close_fields won't be invoked */
}

struct sym *alloc_filler( void ) {
        char s[15];
        struct sym *sy;
        sprintf(s,"FIL$%05d",filler_num++);
        sy = install(s,SYTB_VAR,0);
        sy->defined=1;
        return sy;
}

struct selsubject *
save_sel_subject( int type, struct selsubject *ssubj, struct sym *sy ) {
        struct selsubject *tmp=malloc(sizeof(struct selsubject));
        struct selsubject *tmp1;
        tmp->type = type;
        tmp->var = sy;
        tmp->next = NULL;
        if (ssubj!=NULL) {
                tmp1 = ssubj;
                while (tmp1->next) 
                        tmp1=tmp1->next;
                tmp1->next = tmp;
                return ssubj;
        }
        return tmp;
}

void compute_subject_set_size(struct selsubject *ssbj) {
        int stack_adjust=0;
        while (ssbj != NULL) {
                if (ssbj->type == SSUBJ_EXPR) {
                        stack_adjust += 8;
                }
                else if (ssbj->type == SSUBJ_COND) {
                        stack_adjust += 4;
                }
                ssbj=ssbj->next;
        }
        inner_stack_size += stack_adjust;
}

void release_sel_subject( int label, struct selsubject *ssbj ) {
        struct selsubject *tmp;
        int stack_adjust=0;
        fprintf(o_src,".L%d:\t# EVALUATE end\n",label);
        while (ssbj != NULL) {
                if (ssbj->type == SSUBJ_EXPR) {
                        stack_adjust += 8;
                }
                else if (ssbj->type == SSUBJ_COND) {
                        stack_adjust += 4;
                }
                tmp=ssbj;
                ssbj=ssbj->next;
                free(tmp);
        }
        if (stack_adjust)
                fprintf(o_src,"\taddl\t$%d, %%esp\n",stack_adjust);
        /* we're leaving this level of stack frame */
        inner_stack_size -= stack_adjust;
}

int check_fields(struct sym *sy) 
{
        struct sym *tmp;
        int len;
        int elen;

        /* Only fields that are signed, class numeric, and usage DISPLAY may
         * leave the sign flags on. */
        if ((sy->type != DTYPE_DISPLAY) || (sy->uval9.picstr[0] != 'S')) {
                sy->flags.separate_sign = 0;
                sy->flags.leading_sign = 0;
        }
        /* Recursively check children */
        if (sy->uval7.son != NULL) {
                len = 0;
                for (tmp=sy->uval7.son; tmp!=NULL; tmp=tmp->uval8.brother) {
                     check_fields(tmp);
                }
        }
/*      
        These tests are done in YACC
        
        if (sy->type == DTYPE_DISPLAY && sy->len > 18) {
           yyerror("Maximum elementary numeric item size of %s > 18 digits exceeded", sy->name);
        }
        if (sy->type == DTYPE_ALPHANUMERIC && sy->len > 12750)
                yyerror("Maximum elementary alphanumeric item size of %s > 12750 exceeded", sy->name);
*/
        // Storage for GROUP items is defined at end of group defenition and may have 88 levels 
        if (sy->level == 88) {
                if ((sy->parent->len == 0) && (sy->parent->type != DTYPE_GROUP)) {
#ifdef DEBUG_COMPILER_LEVEL2       
        fprintf(stderr, "# debug 4010.020 : check_fields: sy->name=%s, sy->len=%d, times=%d, sy->type=%c, sy->parent->type=%c\n", 
                                                  sy->name, sy->len, sy->times, sy->type, sy->parent->type); 
#endif
                        yyerror("Parent variable of 88 has no storage");
                }
        }

        if (sy->value != NULL) {
                if (sy->value->len > (elen=get_max_edt_len(sy))) {
                        HTG_temporary_severity=4;
                        yyerror("Value (length %d) of symbol %s is greater than it's picture (%d)",
                                sy->value->len, sy->name, elen);
                        HTG_temporary_severity=8;
                }
                if (sy->value->type == DTYPE_ALPHANUMERIC &&
                        (sy->type == DTYPE_DISPLAY || sy->type == DTYPE_BININT))
                        if (!sy->flags.blank)
                                yyerror("Invalid value type for symbol %s", sy->name);
        }
        return 0;
}

int set_field_value_sw( struct sym *sy, int times ) {
        struct sym *tmp;
        unsigned int res;
        struct {unsigned int v:1,sv:1,tmpv:1,tmpsv:1;}f;
        
        f.v = 0; f.sv = 0;
        if (sy->uval7.son != NULL) {
                for (tmp=sy->uval7.son;tmp!=NULL;tmp=tmp->uval8.brother) {
                        res = set_field_value_sw( tmp, times );
                        f.v = f.v || res;
                }
        }
        sy->flags.value = f.v = f.v || sy->value != NULL;
        sy->flags.spec_value = f.sv = f.v;
        
        /* fprintf(stderr,"set_field_value_sw: %s -> %d,%d\n",sy->name,f.v,f.sv); */
/*        return f.v*2 + f.sv; */
        return f.v;
}

int set_field_length( struct sym *sy, int times ) {
        struct sym *tmp;
        int len,tmplen;

#ifdef DEBUG_COMPILER_LEVEL2       
        fprintf(stderr, "# debug 4010.020 : set_field_length: sy->name=%s, sy->len=%d, times=%d, sy->type=%c\n", 
                                                  sy->name, sy->len, times, sy->type); 
#endif

        if (sy->uval7.son != NULL) {
                len = 0;
                sy->type = DTYPE_GROUP;
                for (tmp=sy->uval7.son;tmp!=NULL;tmp=tmp->uval8.brother) {
                        tmplen = tmp->times * set_field_length( tmp, times );
                        if (tmp->uval6.redefines == NULL)
                                len += tmplen;
                }
                sy->len = len;
        }
        len = symlen(sy) + sy->slack;
#ifdef DEBUG_COMPILER_LEVEL2       
        fprintf(o_src, "# htcobgen: set_field_length: Name: %s, Length: %d(%d x %d), Type: %c\n", sy->name, len*times, len, times, sy->type); 
#endif
#ifdef DEBUG_COMPILER_LEVEL      
        fprintf(stderr, "# debug 4010.060 : set_field_length: Name: %s, Length: %d(%d x %d), Type: %c\n", sy->name, len*times, len, times, sy->type); 
#endif
        return len * times;
}

unsigned field_alignment( struct sym *sy, unsigned location ) {
        unsigned slack_bytes = 0, mod_loc;
                
        if (sy->flags.sync == 0) return 0;
        switch (sy->type) {
        case DTYPE_BININT:
                mod_loc = (location - curr_01_location)% symlen(sy);
                slack_bytes = (mod_loc == 0 ? 0 : symlen(sy) - mod_loc);
                break;
        }
#if 0
#ifdef DEBUG_COMPILER        
        fprintf(o_src,"#fa: %d, %d, %d, %d, %d\n", curr_01_location, location, symlen(sy), mod_loc, slack_bytes);
#endif        
#endif

#ifdef DEBUG_COMPILER_LEVEL       
        fprintf(stderr,"# debug 4010.080 : set_field_length : curr_01_location=%d, location=%d, symlen(sy->name=%s)=%d, mod_loc=%d, slack_bytes=%d\n", curr_01_location, location, sy->name, symlen(sy), mod_loc, slack_bytes);
#endif        
        return slack_bytes;
}

void set_field_location(struct sym *sy, unsigned location) {
  struct sym *tmp;

#ifdef DEBUG_COMPILER_LEVEL
  fprintf(stderr,"# debug 4045.000 : set_field_location: sy->name=%s, sy->len=%d, location=%d, curr_01_location=%d, sy->sec_no=%d\n", sy->name, sy->len, location, curr_01_location, sy->sec_no); 
#endif

//  if (sy->level == 1) 
  if ((sy->level == 1) && (sy->uval6.redefines == NULL)) 
        curr_01_location = location;
  
  /********* allocate field descriptor *************/
  sy->descriptor = literal_offset;

  if (HTG_libcob) {
     literal_offset += (sy->type==DTYPE_GROUP ? CFLD_DESC_SIZE0 : CFLD_DESC_SIZE1);
  }
  else {
     literal_offset += (sy->type==DTYPE_GROUP ? FLD_DESC_SIZE0 : FLD_DESC_SIZE1);
  }

  /********* generate picture for field ************/
  if (sy->type != DTYPE_GROUP) {
     sy->uval5.pic = literal_offset;
     literal_offset += (strlen(sy->uval9.picstr) + 1);
  }
  else {
     sy->uval1.decimals = sy->uval5.pic = 0;
  }

  save_field_in_list(sy);

  if (sy->uval6.redefines != NULL) {
     location = sy->uval6.redefines->uval2.location;
     sy->slack = 0;
     sy->flags.in_redefinition = 1;
  }
  else {
     sy->slack = field_alignment(sy, location);
     location += sy->slack;
     sy->flags.in_redefinition = 0;
  }
  
  if (sy->parent != NULL && sy->parent->flags.in_redefinition) 
     sy->flags.in_redefinition = 1;
  sy->uval2.location = location;
  if ((sy->level == 1) || (sy->level == 77))
     sy->offset_mloc = 0;
  else
     sy->offset_mloc = curr_01_location;
  
#ifdef DEBUG_COMPILER_LEVEL
  fprintf(stderr,"# debug 4045.060 : set_field_location: Name=%s, len=%d, location=%d, curr_01_location=%d, sy->offset_mloc=%d\n", 
                 sy->name, sy->len, location, curr_01_location, sy->offset_mloc); 
#endif
    
  for (tmp=sy->uval7.son;tmp!=NULL;tmp=tmp->uval8.brother) {
#ifdef DEBUG_COMPILER_LEVEL
      fprintf(stderr,"# debug 4045.065 : set_field_location: Name=%s, len=%d, location=%d, curr_01_location=%d, tmp->offset_mloc=%d\n", 
                     tmp->name, tmp->len, location, curr_01_location, tmp->offset_mloc); 
#endif
      set_field_location(tmp, location);
#ifdef DEBUG_COMPILER_LEVEL
      fprintf(stderr,"# debug 4045.075 : set_field_location: Name=%s, len=%d, location=%d, curr_01_location=%d, tmp->offset_mloc=%d\n", 
                     tmp->name, tmp->len, location, curr_01_location, tmp->offset_mloc); 
#endif
      if (tmp->uval6.redefines == NULL) {
          if (tmp->sec_no == SEC_STACK) {
             location -= (symlen(tmp) + tmp->slack) * tmp->times;        
             /* negative for it's at the stack */
          }
          else {
             location += (symlen(tmp) + tmp->slack) * tmp->times;
          }
      }
#ifdef DEBUG_COMPILER_LEVEL
      fprintf(stderr,"# debug 4045.080 : set_field_location: Name=%s, len=%d, location=%d, curr_01_location=%d, tmp->offset_mloc=%d, symlen(tmp)=%d, tmp->slack=%d, tmp->times=%d\n", 
                     tmp->name, tmp->len, location, curr_01_location, tmp->offset_mloc, symlen(tmp), tmp->slack, tmp->times); 
#endif
  }
}

void scr_set_column( struct scr_info *si, struct sym *sy, int plus_minus) {
        int val;
        si->column = 0;
        si->column_var = NULL;
        si->column_sign = plus_minus;
        if (sy->litflag == 1)
        {
                si->column_var=NULL;
                val = atoi(sy->name);
                if (val == 0)
                        yyerror("line could not be 0");
                si->column = val;
        }
        else
        {
          if (!(sy->defined))
                 yyerror("variable not defined %s ",sy->name);
          if(sy->type == DTYPE_ALPHANUMERIC )
                 yyerror("variable %s must be numeric",sy->name);
          si->column_var = sy;
        }
}
void scr_set_line( struct scr_info *si, struct sym *sy, int plus_minus) {
        int val;
        si->line = 0;
        si->line_var = NULL;
        si->line_sign = plus_minus;
        if (sy->litflag == 1)
        {
                si->line_var=NULL;
                val = atoi(sy->name);
                if (val == 0)
                        yyerror("line could not be 0");
                si->line = val;
        }
        else
        {
          if (!(sy->defined))
                 yyerror("variable not defined %s ",sy->name);
          if(sy->type == DTYPE_ALPHANUMERIC )
                 yyerror("variable %s must be numeric",sy->name);

          si->line_var = sy;
        }
}

/*void scr_push_display_position(struct lit *lit)*/
void scr_push_display_position(struct sym *sy)
{
        int len=0,pos,lin,col;
        struct lit *literal;
        
        if (sy->litflag) {
            /* is a literal */
            literal = (struct lit *)sy;
            len=strlen(literal->name);
            switch(len) {
                    case 4:
                            pos=atoi(literal->name);
                            lin = pos / 100;
                            col = pos - (100 * lin);
                            push_immed(lin);
                            push_immed(col);
                            asm_call("tcob_goxy");
                            break;
                    case 6:
                            pos=atoi(literal->name);
                            lin = pos / 1000;
                            col = pos - (1000 * lin);
                            push_immed(lin);
                            push_immed(col);
                            asm_call("tcob_goxy");
                            break;
                    default:
                            yyerror("DISPLAY AT must be followed by a 4 digits or 6 digits integer");
                            break;
            }
        } else {
            /* is a variable */
            switch(sy->len) {
                    case 4:
                            push_immed(4);
                            gen_loadloc(sy);        
                            asm_call("tcob_goxy_variable");
                            break;
                    case 6:
                            push_immed(6);
                            gen_loadloc(sy);
                            asm_call("tcob_goxy_variable");
                            break;
                    default:
                            yyerror("DISPLAY AT must be followed by a 4 digits or 6 digits variable");
                            break;
            }
            
                
        }
}
/*************** report section ******************/

void save_report( struct sym *rep, struct sym *file ) {
        struct rd *rd = (struct rd *)rep;
        struct list *item = malloc(sizeof(struct list));
        item->var = rd;
        item->next = report_list;
        report_list = item;
        rd->file = file;
        rd->type = 'W';
        rd->controls = rd->items = NULL;
        rd->page_limit = 66;
        rd->heading = 1;
        rd->footing = 66;
        rd->first_detail = rd->last_detail = 1;
}

void update_report_field( struct sym *sy ) { 
        update_field(curr_field);
        sy->type = 'Q';
}

void update_screen_field( struct sym *sy, struct scr_info *si ) { 
        struct sym *tmp;
        char *pic;
        update_field(curr_field);
        sy->type = DTYPE_ACCEPT_DISPLAY;
        sy->scr = si;
        si->label = screen_label++;
        /* if picture is empty (implicit filler), and there is a
                value declared, create its picture from value literal. */
        
        if (*(sy->uval9.picstr) == 0 && sy->value != NULL) {
                tmp = (struct sym *)sy->value;
                pic = sy->uval9.picstr = malloc(3);
                *pic++ = 'X';
                *pic++ = strlen(tmp->name);
                *pic = 0;
                sy->len = strlen(tmp->name);
        } 
}

void update_field(struct sym *sy) 
{

        if (sy == NULL) 
           return;

#ifdef DEBUG_COMPILER_LEVEL
        fprintf(stderr, "# debug 4250.000 : update_field: name: %s, len: %d, type: %c\n", 
                        sy->name, sy->len, sy->type); 
#endif

        if (sy->level != 88 && sy->level != 66) {
                gen_picture();
        }
        /* printf("upd_flds:symbol: %s, %d, piccnt: %d, %d\n", sy->name,
          sy->len, piccnt,pscale); */
        /* Physical sizes for BINARY and FLOAT types are not (generally)
         * affected by the PICTURE. */
        if ((sy->type != DTYPE_BININT) && 
            (sy->type != DTYPE_PACKED) && 
            (sy->type != DTYPE_FLOAT)) {
            if (piccnt == 1 && abs(pscale) == 1)
               sy->len = 1; /* only one P in the picture */
            else
               sy->len = piccnt - abs(pscale);
        }
        /* SIGN IS ... SEPARATE only affects field length when class is numeric,
         * usage is DISPLAY, and field is signed.  However, sign flags must be
         * temporarily retained in case this is a group item. */
        if ((sy->type == DTYPE_DISPLAY)  && 
            (sy->uval9.picstr[0] == 'S') && 
            (sy->flags.separate_sign)) {
            sy->len++;
        }
        /* fprintf(stderr,"symbol: %s, piccnt: %d, %d\n", sy->name,
          piccnt,pscale); */
        /* update COMP field length (but not BINARY-<something>) */
        if ((sy->type == DTYPE_BININT) && 
            (sy->len == 0)) {
             sy->len = query_comp_len(sy);
        }
        /* FIXME: This is a hack */
        if ((sy->type == DTYPE_PACKED) && 
            (sy->len == 0)) {
             //sy->len = piccnt - abs(pscale);
             //sy->len = symlen(sy);
             sy->len  = (pic_digits(sy, '9')/2) + 1;
        } 
#ifdef DEBUG_COMPILER_LEVEL
        fprintf(stderr, "# debug 4270.000 : update_field: name: %s, len: %d, type: %c\n", 
                        sy->name, sy->len, sy->type); 
#endif
}

void close_fields(void) {
  struct sym *sy;
  int saved_length;
  int ns_offset = 0;
  
  if (curr_field == NULL) 
     return;
  
#ifdef DEBUG_COMPILER_LEVEL
  fprintf(stderr, "# debug 4350.010 : close_fields: curr_field->name=%s, curr_field->len=%d\n", curr_field->name, curr_field->len); 
#endif
  
  /********** locate level 01 field   **************/
  for (sy=curr_field;sy->parent!=NULL;sy=sy->parent);
  if (sy->level != 1 && sy->level != 77 && sy->level != 66) {
     yyerror("field not subordinate to any other: %s",sy->name);
  }

#ifdef DEBUG_COMPILER_LEVEL
  fprintf(stderr,"# debug 4350.020 : close_fields: sy -> Name=%s, len=%d, level=%d, sec_no=%d, uval2.location=%d, flags.isfilerecord=%d\n", 
          sy->name, sy->len, sy->level, sy->sec_no, sy->uval2.location, sy->flags.isfilerecord); 
#endif
  
  /********** propagate value flags  *************/
  sy->flags.spec_value = set_field_value_sw(sy, 1);
  
  /********** update length of fields  *************/
  if (sy->linkage_flg) {
          linkage_offset += (set_field_length(sy, 1) * sy->times);
          set_field_location(sy, linkage_offset);
  } else if (sy->sec_no == SEC_DATA) {
          if (sy->flags.isfilerecord == 0) {
             saved_length = (set_field_length(sy, 1) * sy->times);
#ifdef DEBUG_COMPILER_LEVEL
  fprintf(stderr, "# debug 4350.040 : close_fields: sy -> Name=%s, len=%d, level=%d, sec_no=%d, uval2.location=%d; saved_length=%d, ns_offset=%d, data_offset=%d\n", 
          sy->name, sy->len, sy->level, sy->sec_no, sy->uval2.location, saved_length, ns_offset, data_offset); 
#endif
             set_field_location(sy, data_offset);
             /* data_offset += saved_length; */
             if (sy->level == 1) { 
                if (sy->uval6.redefines == NULL) 
                   data_offset += saved_length;
             }
             else {
                data_offset += saved_length;
             }

#ifdef DEBUG_COMPILER_LEVEL
  fprintf(stderr, "# debug 4350.060 : close_fields: sy -> Name=%s, len=%d, level=%d, sec_no=%d, uval2.location=%d; saved_length=%d, ns_offset=%d, data_offset=%d\n", 
          sy->name, sy->len, sy->level, sy->sec_no, sy->uval2.location, saved_length, ns_offset, data_offset); 
#endif
          }
          else {
             saved_length = (set_field_length(sy, 1) * sy->times);
#ifdef DEBUG_COMPILER_LEVEL
  fprintf(stderr, "# debug 4350.080 : close_fields: sy -> Name=%s, len=%d, level=%d, sec_no=%d, uval2.location=%d; saved_length=%d, ns_offset=%d\n", 
          sy->name, sy->len, sy->level, sy->sec_no, sy->uval2.location, saved_length, ns_offset); 
#endif
             set_field_location(sy, data_offset);
#ifdef DEBUG_COMPILER_LEVEL
  fprintf(stderr, "# debug 4350.100 : close_fields: sy -> Name=%s, len=%d, level=%d, sec_no=%d, uval2.location=%d; saved_length=%d, ns_offset=%d\n", 
          sy->name, sy->len, sy->level, sy->sec_no, sy->uval2.location, saved_length, ns_offset); 
#endif
          }
  } else if (sy->sec_no >= SEC_FIRST_NAMED) {
          saved_length = (set_field_length(sy, 1) * sy->times);
          set_field_location(sy, ns_offset);
          ns_offset += saved_length;
  } else {
          stack_offset += (set_field_length(sy, 1) * sy->times);
          set_field_location(sy, stack_offset);
  }
  check_fields(sy);
  curr_field=NULL;
}

/*int
show_labels() {
        struct sym *sy,*sy1,*sy2;
        int i,j=0;
        FILE *f;
        f = fopen("show.labels","w");
        for (i=0;i<HASHLEN;i++) {
        for (sy=labtab[i];sy!=NULL;sy=sy->next) {
                if (sy->type == 'f') continue;
                sy1 = sy;
                while (sy1) {
                        fprintf(f,"Label: %s, defined: %d, type: %c, parent: %s\n",
                                sy1->name, sy1->defined, sy1->type,
                                sy1->parent ? sy1->parent->name : "(NULL)");
                        j++;
                        sy1=sy1->clone;
                }        
        }
    }
        fclose(f);
        return j;
}*/

char * var_name ( struct sym *sy ) {
        unsigned int n;
        n = MAXNAMEBUF;
        strcpy(name_buf,"");
    while (n > strlen(sy->name)+4) {
                if (n < MAXNAMEBUF) 
                        strcat( name_buf," OF ");
                strcat( name_buf,sy->name );
                n -= strlen(sy->name)+4;
                if ((lookup(sy->name,SYTB_VAR)->clone == NULL)
                        || (sy->parent == NULL))
                                break;
                sy = sy->parent;
        }
        return name_buf;
}

/* save variable values, including 88-var range/values list */
void set_variable_values( struct lit *v1, struct lit *v2 ) {
        struct vrange /**vr,*/*new;
        if (curr_field->value == NULL) {
                curr_field->refmod_redef.vr = NULL;
                curr_field->value = v1;
                curr_field->uval4.value2 = v2;
                curr_field->flags.value = 1;
                curr_field->flags.spec_value = 1;
        }
        else {
                new = malloc(sizeof(struct vrange));
                new->value = v1;
                new->value2 = v2;
                /* spec_value is not used for 88 */
                new->next = curr_field->refmod_redef.vr;
                curr_field->refmod_redef.vr = new;
        }
}

void assign_expr( struct sym *sy, int opt, char end ) {
        push_immed(opt);
        gen_loadvar( sy );
        if (end == '1') {
           stackframe_cnt += sizeof(double); /* value to be poped too */
        }
        asm_call("tcob_assign_double");
}

int push_expr( struct sym *sy) {
        int retcode;
#ifdef DEBUG_COMPILER
        fprintf(o_src,"##### push_expr begin\n");
#endif
        retcode = push_subexpr(sy);
#ifdef DEBUG_COMPILER
        fprintf(o_src,"##### push_expr end\n");
#endif
        return retcode;
}

void alloc_file_entry(struct sym *f, int opt) 
{
  f->uval5.record = stack_offset;
  
  if (opt == 0) 
     f->uval10.sort_file = 0;          
  else 
     f->uval10.sort_file = 1;   

#ifdef DEBUG_COMPILER_LEVEL
  fprintf(stderr,"# debug 4410.000 : alloc_file_entry: f -> Name=%s, len=%d, level=%d, sec_no=%d, uval2.location=%d, uval5.record=%d\n", 
          f->name, f->len, f->level, f->sec_no, f->uval2.location, f->uval5.record); 
#endif
#ifdef DEBUG_COMPILER
  fprintf(o_src,"# Allocate space for Name '%s' Stack Addr(uval5.record): %d\n", f->name, stack_offset);
#endif
}

struct sym *file_description_append_rec(struct sym *sy1, struct sym *sy2) 
{
  struct sym *sy0, *sy4 = NULL;
  
#ifdef DEBUG_COMPILER_LEVEL2
  fprintf(stderr, "# debug 4391.000 : file_description_append_rec : name=%s, len=%d\n", sy1->name, sy1->len); 
  fprintf(stderr, "# debug 4392.000 : file_description_append_rec : name=%s, len=%d\n", sy2->name, sy2->len); 
#endif

  sy0 = sy1;
  while (sy0 != NULL) {
#ifdef DEBUG_COMPILER_LEVEL2
    fprintf(stderr, "# debug 4395.000 : file_description_append_rec : name=%s, len=%d\n", sy0->name, sy0->len); 
#endif
    sy4 = sy0;
    sy0 = sy0->uval6.recordsym; 
  }
  if (sy4 != NULL) {
    sy4->uval6.recordsym = sy2;
#ifdef DEBUG_COMPILER_LEVEL2
    sy0 = sy4->uval6.recordsym;
    fprintf(stderr, "# debug 4399.000 : file_description_append_rec : name=%s, len=%d\n", sy0->name, sy0->len); 
#endif
  }
  
  return sy1;
}

/*
  define a file, but don't generate code yet.
  (will be done later at dump_fdesc())
*/
void gen_fdesc(struct sym *f, struct sym *r) 
{
  int len;
  struct list *list, *templist;
  //struct alternate_list *alt;
  struct sym *sy, *sy0, *sy0Next, *sy1, *sy1Next, *sy2, *sy2Next, *sy3;

  list = (struct list *)malloc(sizeof(struct list));
  
  if (files_list == NULL) { 
     files_list = list;
  }
  else {
       templist=files_list; 
       while (templist->next != NULL) {
         templist = templist->next;
       }
       templist->next = list;
  }
  list->var = f;
  list->next = NULL;

// sy = f->uval6.recordsym; 
 sy = r; 
 while (sy != NULL) {
#ifdef DEBUG_COMPILER_LEVEL2
    fprintf(stderr, "# debug 4090.015 : gen_fdesc : name=%s, type=%c, len=%d\n", sy->name, sy->type, sy->len); 
#endif
    sy->ix_desc = f;
    sy = sy->uval6.recordsym; 
 }
/*
  sy1 = sy;
  sy2 = sy1;
  while (sy1 != NULL) {
#ifdef DEBUG_COMPILER_LEVEL2
     fprintf(stderr, "# debug 4137.000 : gen_fdesc : name=%s, level=%d, recLen=%d\n", sy1->name, sy1->level, sy1->len); 
#endif
     sy1->ix_desc = f;
     sy2 = sy1;
     sy1 = sy1->uval6.redefines;
  }
*/
  f->uval2.fdesc = global_offset;
  len = sizeof(struct file_desc);
  global_offset += len;
  data_offset += f->len;
  
  /* determine the max-record length from file data description entries */
#ifdef DEBUG_COMPILER_LEVEL2
  fprintf(stderr, "# debug 4091.015 : gen_fdesc : name=%s, uval2.fdesc=%d, global_offset=%d, recLen=%d\n", f->name, f->uval2.fdesc, global_offset, f->len); 
#endif

  return;
        


  /* Sort file record description entries linked-list in reverse order by record-length */

  sy0 = NULL;
  sy = r;
  sy1 = sy;
  while (sy1 != NULL) {
#ifdef DEBUG_COMPILER_LEVEL2
     fprintf(stderr, "# debug 4104.000 : gen_fdesc : name=%s, level=%d, recLen=%d\n", sy1->name, sy1->level, sy1->len); 
#endif
     if (sy1->uval6.redefines != NULL) {
        sy1Next = sy1->uval6.redefines;
        sy2 = sy1->uval6.redefines;
#ifdef DEBUG_COMPILER_LEVEL2
        fprintf(stderr, "# debug 4108.000 : gen_fdesc : name=%s, level=%d, recLen=%d\n", sy2->name, sy2->level, sy2->len);  
#endif
        if (sy1->len > sy2->len) {
           if (sy0 == NULL) {
              sy2Next = sy2->uval6.redefines;
              sy3 = sy1;
              sy1 = sy2;
              sy1->uval6.redefines = sy3;
              sy2 = sy3;
              sy2->uval6.redefines = sy2Next;
              /* reset the start of the list */
              sy = sy1;
              sy->uval6.redefines = sy1->uval6.redefines;
           }
           else {                    
#ifdef DEBUG_COMPILER_LEVEL2
              fprintf(stderr, "# debug 4117.000 : gen_fdesc : name=%s, level=%d, recLen=%d\n", sy2->name, sy2->level, sy2->len); 
#endif
              sy2Next = sy2->uval6.redefines;
              sy3 = sy1;
              sy1 = sy2;
              sy1->uval6.redefines = sy3;
              sy2 = sy3;
              sy2->uval6.redefines = sy2Next;
              sy0->uval6.redefines = sy1Next;
           }
           sy0 = NULL;
           sy1 = sy;
        }
        else {
           sy0 = sy1;
           sy0Next = sy1->uval6.redefines;
           sy1 = sy1->uval6.redefines;
        }
     }
     else {
        sy1 = sy1->uval6.redefines;
     }
  }

  sy1 = sy;
  sy2 = sy1;
  while (sy1 != NULL) {
#ifdef DEBUG_COMPILER_LEVEL2
     fprintf(stderr, "# debug 4137.000 : gen_fdesc : name=%s, level=%d, recLen=%d\n", sy1->name, sy1->level, sy1->len); 
#endif
     sy1->ix_desc = f;
     sy2 = sy1;
     sy1 = sy1->uval6.redefines;
  }
  /* Define the file record with the field with max record length */
//  f->uval6.recordsym = sy2;

#ifdef DEBUG_COMPILER_LEVEL2
  fprintf(stderr, "# debug 4171.000 : gen_fdesc : name=%s, level=%d, recLen=%d, loc: %d\n", sy2->name, sy2->level, sy2->len, sy2->uval2.location); 
#endif

  len = sizeof(struct file_desc); /* assume organization != INDEXED */
  /* This code is obsolete 
  if (f->uval1.organization == TCB_FILE_ORGANIZATION_INDEXED) { // indexed file 
     len += 4; // 4 --> size of terminating 'long == -1' 
     // now count each alternate description size 
     alt = f->uval8.alternate;
     while (alt) {
        len += sizeof(struct altkey_desc);
        alt = alt->next;
     }
  } 
  */
  f->uval2.fdesc = global_offset;
  global_offset += len;
/* file_offset += len; */

}

void gen_status(struct sym *f) 
{       
 if (f->parent) {
    push_eax();
    gen_loadloc(f->parent);
    asm_call("tcob_save_status");
 }
}

void gen_perform_decl(struct sym *f, void *poption) 
{
 struct sym *decl_sym = f->refmod_redef.declarative;
 int tmplabel, option=0;
 
#ifdef DEBUG_COMPILER_LEVEL2
 fprintf(stderr, "# debug 4720.020 : gen_perform_decl : f->name=%s\n", f->name); 
#endif
 
 if (poption == NULL) 
   option = 1; 

 if (decl_sym) {
#ifdef DEBUG_COMPILER
    fprintf(o_src, "# decl: on %s\n", decl_sym->name);
#endif
    gen_file_exception(f, TCB_FILE_OPEN_MODE_NONE, option);
    tmplabel = gen_check_zero();
    gen_perform(decl_sym);
    gen_dstlabel(tmplabel);
 }
 else {
   if ((declaratives_list != NULL) && (declaratives_list->modsize > 0)) {
      gen_file_exception(f, 1, option);
      fprintf(o_src,"\tmovl\t%%eax, %%ebx\n");
      tmplabel = gen_check_zero();
      fprintf(o_src,"\tleal\t.L%d, %%eax\n", tmplabel);
      fprintf(o_src,"\tpushl\t%%eax\n");
      fprintf(o_src,"\tleal\t.LB_DECLARATIVES_%s, %%eax\n", pgm_label);
      fprintf(o_src,"\tpushl\t%%eax\n");
      fprintf(o_src,"\tleal\t.LE_DECLARATIVES_%s, %%eax\n", pgm_label);
      fprintf(o_src,"\tpushl\t%%eax\n");
      fprintf(o_src,"\tjmp\t.LB_DECLARATIVES_%s\n", pgm_label);
      gen_dstlabel(tmplabel);
   }
 }
}

void gen_decl_select(struct tcb_declaratives_list *dsl, int jlabel) 
{
 int lb1;
 struct tcb_declarative_list *dl1, *dl2; 
 struct tcb_declarative *d;
 
 if ((dsl != NULL) && (dsl->modsize > 0)) {
#ifdef DEBUG_COMPILER_LEVEL
   fprintf(stderr, "# debug 4680.020 : gen_decl_select : dsl->size=%d, dsl->modsize=%d;\n", dsl->size, dsl->modsize); 
#endif
   dl1 = dsl->dl;
   while (dl1 != NULL) {
#ifdef DEBUG_COMPILER_LEVEL
       fprintf(stderr, "# debug 4680.040 : gen_decl_select : dl1->d->utype=%d;\n", dl1->d->utype); 
#endif
       dl2 = dl1; 
       dl1 = dl2->next;
   }
   dl1 = dsl->dl;

   fprintf(o_src,"\tjmp .L%d\n", jlabel);
   fprintf(o_src,".LB_DECLARATIVES_%s:\n", pgm_label);
   while (dl1 != NULL) {
     d = dl1->d;
#ifdef DEBUG_COMPILER_LEVEL
     fprintf(stderr, "# debug 4680.080 : gen_decl_select : d->utype=%d, d->secname->name=%s;\n", d->utype, d->secname->name); 
#endif
     if (d->utype != TCB_DECLARATIVE_USE_TYPE_NONE) {
        lb1=loc_label++;
        fprintf(o_src,"\tcmpl\t$%d, %%ebx\n", d->deo->u.omode);
        fprintf(o_src,"\tjne\t.L%d\n", lb1);
        fprintf(o_src,"\tleal\t.LE_DECLARATIVES_%s, %%eax\n", pgm_label);
        fprintf(o_src,"\tpushl\t%%eax\n");
        fprintf(o_src,"\tleal\t.LB_%s, %%eax\n", label_name(d->secname));
        fprintf(o_src,"\tpushl\t%%eax\n");
        fprintf(o_src,"\tleal\t.LE_%s, %%eax\n", label_name(d->secname));
        fprintf(o_src,"\tpushl\t%%eax\n");
        fprintf(o_src,"\tjmp .LB_%s\n", label_name(d->secname));
        fprintf(o_src,"\t.align\t16\n");
        //fprintf(o_src,"\tjmp .LE_DECLARATIVES_%s\n", pgm_label);
        fprintf(o_src,".L%d:\n", lb1);
     }
     dl2 = dl1->next;
     dl1 = dl2;
   }
  
   fprintf(o_src,".LE_DECLARATIVES_%s:\n", pgm_label);
   fprintf(o_src,"\taddl\t$8, %%esp\n");
   fprintf(o_src,"\tret\n");

 }
}

void gen_file_exception(struct sym *f, int imode, int option) 
{
 push_immed(option);
 push_immed(imode);
 gen_save_filedesc(f);
 asm_call("tcob_file_exception_code");
}

struct sym *create_status_register(char *name)
{
 struct sym *sy;
 
 char pic[] = {'9',2,0};
 sy = install(name,SYTB_VAR,0);        
 if (sy->type) return sy; /* it already exists */
 sy->type = DTYPE_DISPLAY;
 sy->uval9.picstr = malloc(strlen(pic)+1); 
 strcpy(sy->uval9.picstr,pic);
 sy->defined = 1;
 sy->occurs_flg = 0;
 sy->times = 1;
 sy->len = 2;
 sy->uval8.brother = NULL;
 sy->uval7.son = NULL;
 sy->linkage_flg = 0;
 sy->sec_no = SEC_DATA;
 sy->uval2.location = data_offset;
 data_offset += 2;
 sy->descriptor = literal_offset;
 literal_offset += FLD_DESC_SIZE1;
 sy->uval5.pic = literal_offset;
 literal_offset += strlen(pic)+1;
 save_field_in_list( sy );
 
 return sy;
}

/* sort statement related functions */
struct sort_node_container *alloc_node_container(int type, struct sortfile_node *sn)
{
 struct sort_node_container *snc;

 snc = malloc(sizeof(struct sort_node_container));
 snc->sn = sn;    
 snc->type = type;    

 return snc;
}

struct sortfile_node *append_sortfile_node(int type, struct sortfile_node *sn, struct sym *sy)
{
 struct sortfile_node *sn1;
 
 if (type == TCB_SORT_NODE_TYPE_FILE) {
    if (sy->type != 'F') {
       yyerror("Invalid variable '%s' expecting file", sy->name);
       return NULL;
    }
 }

 if (sn == NULL) {
    sn1 = malloc(sizeof(struct sortfile_node));
    sn1->next = NULL;
    sn1->sy = sy;    
 }
 else {
    sn1 = malloc(sizeof(struct sortfile_node));
    sn1->next = sn;
    sn1->sy = sy;
 }

 return sn1;
}

struct sortfile_node *alloc_sortfile_node(struct sym *sy)
{
 struct sortfile_node *sn;
 
 if (sy->type != 'F') {
    yyerror("Invalid variable '%s' expecting file", sy->name);
    return NULL;
 }
 sn = malloc(sizeof(struct sortfile_node));
 sn->next = NULL;
 sn->sy = sy;
 
 return sn;
}

struct sortfile_node *alloc_sortfile_node2(struct sym *sy1, struct sym *sy2)
{
 struct sortfile_node *sn1, *sn2;
 
 sn1 = malloc(sizeof(struct sortfile_node));
 sn1->sy = sy1;
 if (sy2 != NULL) {
    sn2 = malloc(sizeof(struct sortfile_node)); 
    sn2->sy = sy2;
    sn2->next = NULL;
    sn1->next = sn2;
 }
 else {
    sn1->next = NULL;
 }
 
 return sn1;
}

void gen_sort_using(struct sym *f, struct sortfile_node *sn) 
{
 struct sym *vstatus;

 vstatus = create_status_register("SORT-RETURN");
 gen_save_sort_fields(f, NULL);
 push_immed(0);
 while (sn) {
   gen_loadloc(sn->sy->uval7.filenamevar);
   gen_save_filedesc(sn->sy);
   sn = sn->next;
 }
 asm_call("tcob_sort_using");
 /* save status returned by operation */
 push_eax();
 gen_loadloc(vstatus);
 asm_call("tcob_save_status");
}

void gen_sort_giving(struct sym *f, struct sortfile_node *sn) 
{
 struct sym *vstatus;
 
 vstatus = create_status_register("SORT-RETURN");
 gen_save_sort_fields(f, NULL);
 push_immed(0);
 while (sn) {
   gen_loadloc(sn->sy->uval7.filenamevar);
   gen_save_filedesc(sn->sy);
   sn = sn->next;
 }
 asm_call("tcob_sort_giving");
 /* save status returned by operation */
 push_eax();
 gen_loadloc(vstatus);
 asm_call("tcob_save_status");
}

void gen_sort(struct sym *f, struct sort_node_container *snc1, struct sort_node_container *snc2) 
{
 struct sortfile_node *sn1;
 struct sym *vstatus, *sy1=NULL, *sy2=NULL;

 vstatus = create_status_register("SORT-RETURN");

/* gen_save_sort_fields(f, NULL); */

 gen_loadloc(f->uval7.filenamevar);
 gen_save_filedesc(f);
 asm_call("tcob_sort_open");
 
 /* save status returned by operation */
 push_eax();
 gen_loadloc(vstatus);
 asm_call("tcob_save_status");
 /* gen_status(f); */

 /* gen_perform_decl(f, NULL); */
 gen_close_sort(f);

/*
//struct sortfile_node {
//        struct sortfile_node *next;
//        struct sym *sy;
//struct sort_node_container {
//        struct sortfile_node *sn;
//        int type;
//        TCB_SORT_NODE_TYPE_FILE,  
//        TCB_SORT_NODE_TYPE_PROC  
//void gen_sort(struct sym *f) 
//void gen_sort_using(struct sym *f, struct sortfile_node *sn);
//void gen_sort_giving(struct sym *f, struct sortfile_node *sn);
//struct sort_node_container *alloc_node_container(int type, struct sortfile_node *sn);
//
// sort_statement:
// SORT name sort_keys 
// sort_duplicates_opt sort_collating_opt 
// sort_input
// sort_output 
// {
//  gen_sort($2); 
//  gen_sort_using($2, $5); 
//  gen_sort_giving($2, $6); 
// }
// perform_range: label perform_thru_opt
// {
//  gen_perform_thru($1,$2);
//  $$ = ($2 == NULL) ? $1 : $2;
// }
//
//void gen_perform_thru( struct sym *s1, struct sym *s2 ) {
*/

 if (snc1->type == TCB_SORT_NODE_TYPE_FILE) {
    gen_sort_using(f, snc1->sn); 
 }
 else {
    sn1 = snc1->sn;
    sy1 = sn1->sy;
    sn1 = sn1->next;
    if (sn1 != NULL) 
       sy2 = sn1->sy;
    gen_perform_thru(sy1, sy2);
 }

 if (snc2->type == TCB_SORT_NODE_TYPE_FILE) {
    gen_sort_giving(f, snc2->sn);     
 }
 else {
    sn1 = snc2->sn;
    sy1 = sn1->sy;
    sn1 = sn1->next;
    if (sn1 != NULL) 
       sy2 = sn1->sy;
    gen_perform_thru(sy1, sy2);    
 }
 
 //gen_save_filevar(f, NULL);
 gen_save_filedesc(f);
 asm_call("tcob_sort_close");
}

void gen_close_sort(struct sym *f) 
{
 struct sym *sortf;

 /* allocate memory for SORT descriptor */
 save_field_in_list(f);
 f->descriptor = literal_offset;
 /* sortf=(struct sym *)(f->uval4.sort_data); */
 sortf=f->uval4.sort_data;
 while (sortf != NULL) {
    literal_offset += 2;
    /* sortf = (struct sym *)(sortf->sort_data); */
    sortf = sortf->uval4.sort_data;
 }
 literal_offset++;
}

struct file_open_statement_list *set_file_open_stm(struct sym *f, struct file_open_statement_list *fol)
{
 struct file_open_statement_list *fol1, *fol2, *fol3;
 
 if (f == NULL) {
    fol1 = fol;
    return fol1;
 }
 
 if (f->type != 'F') {
    fol1 = fol;
    yyerror("Invalid variable '%s', file name expected", f->name);
    return fol1;
 }

 fol2 = malloc(sizeof(struct file_open_statement_list));

 fol2->mode = TCB_FILE_OPEN_MODE_NONE;
 fol2->fname = f;
 fol2->next = NULL;

#ifdef DEBUG_COMPILER_LEVEL2
 fprintf(stderr, "# debug 4310.020 : set_file_open_stm : f->name=%s, fol2->mode=%d;\n", f->name, fol2->mode ); 
#endif
 
 fol1 = fol;
 if (fol == NULL) {
 fol1 = fol2;
 }
 else {
    fol3 = fol;
    while (fol3->next != NULL) 
       fol3 = fol3->next; 
    fol3->next = fol2;
 }

 return fol1;
}

struct file_open_statement_list *set_file_open_stm_list(int mode, struct file_open_statement_list *fo1, struct file_open_statement_list *fo2)
{
 struct file_open_statement_list *fol1, *fol2, *fol3;

 fol1 = fo1;
 while (fol1 != NULL) {
#ifdef DEBUG_COMPILER_LEVEL2
    fprintf(stderr, "# debug 4342.020 : set_file_open_stm_list : fol1->fname->name=%s, mode=%d\n", fol1->fname->name, mode); 
#endif
    fol1->mode = mode;
    fol1 = fol1->next; 
 }

 fol3 = fo2;
 fol2 = fo2;
 if (fol2 == NULL) {
    fol3 = fo1;
#ifdef DEBUG_COMPILER_LEVEL2
    if (fol3 != NULL) 
       fprintf(stderr, "# debug 4342.040 : set_file_open_stm_list : fol3->fname->name=%s, fol3->mode=%d\n", fol3->fname->name, fol3->mode); 
#endif
 }
 else {
#ifdef DEBUG_COMPILER_LEVEL2
    if (fol1 != NULL)
      fprintf(stderr, "# debug 4342.050 : set_file_open_stm_list : fol1->fname->name=%s, fol1->mode=%d\n", fol1->fname->name, fol1->mode); 
#endif
    while (fol2->next != NULL) 
       fol2 = fol2->next; 
    fol2->next = fo1;
#ifdef DEBUG_COMPILER_LEVEL2
    fprintf(stderr, "# debug 4342.060 : set_file_open_stm_list : fo1->fname->name=%s, fo1->mode=%d\n", fo1->fname->name, fo1->mode); 
#endif
 }

 return fol3;
}

void gen_open_stm(struct file_open_statement_list *fol)
{
 struct file_open_statement_list *fol1;
 struct sym *f;
 int mode;

 fol1 = fol;
 while (fol1 != NULL) {    
    mode = fol1->mode;
    f = fol1->fname;
#ifdef DEBUG_COMPILER_LEVEL2
    fprintf(stderr, "# debug 4376.050 : gen_open_stm : f->name=%s, mode=%d\n", f->name, mode); 
#endif
    if ((f->uval1.organization == TCB_FILE_ORGANIZATION_LINESEQUENTIAL) && (mode == TCB_FILE_OPEN_MODE_IO))
       yyerror("File '%s' is organization type LINE SEQUENTIAL and does not support 'I-O' mode", f->name);
    else
       gen_open(mode, f);
    fol1 = fol1->next; 
 }
}

void gen_open(int mode, struct sym *f)
{
 push_immed(mode);
 gen_loadloc(f->uval7.filenamevar);
 gen_save_filedesc(f);
 asm_call("tcob_open");
 gen_status(f);
 gen_perform_decl(f, NULL); 
}

void gen_close(struct sym *f) 
{
 gen_save_filedesc(f);
 asm_call("tcob_close");
 gen_status(f);
 gen_perform_decl(f, NULL);
}

void gen_return_stmt(struct sym *f, struct sym *buf) 
{
 int iNull=0;
 struct rec_varying *rv;

 rv = f->uval9.rec_varying;
 if (rv != NULL) {
    gen_loadvar(rv->reclen);
 }
 else {
    push_immed(iNull);
    push_immed(iNull);
 }
 gen_save_filevar(f, buf);
 asm_call("tcob_sort_return");
 gen_status(f);
 /* gen_perform_decl(f, NULL); */
}

int gen_reads(struct sym *f, struct sym *buf, struct sym *key, 
              int next_prev, int sel, int withlock) 
{
  int r=0;
  int t_next_prev = next_prev;

  /* FIXME : Add code to trap more syntax errors */

  if (f->type != 'F') {
     yyerror("Identifier '%s' is NOT a file name", f->name);
     return (1);
  }

  if (((f->uval1.organization == TCB_FILE_ORGANIZATION_SEQUENTIAL) || 
       (f->uval1.organization == TCB_FILE_ORGANIZATION_LINESEQUENTIAL)
      ) && (key != NULL)
     ) {
     yyerror("Invalid READ format - KEY is not permitted for file organization (LINE)SEQUENTIAL : name %s", f->name);
     return (2);
  }

  if ((f->uval1.organization == TCB_FILE_ORGANIZATION_LINESEQUENTIAL) && 
      (next_prev == 2)
     ) {
     yyerror("Invalid READ format - PREVIOUS phrase not permitted for file organization LINE-SEQUENTIAL : name %s", f->name);
     return (3);
  }

  if ((f->uval1.organization == TCB_FILE_ORGANIZATION_INDEXED) && 
      (key != NULL) && (next_prev != 0)
     ) {
     yyerror("Invalid READ format - phrase NEXT-PREVIOUS with KEY phrase is not permitted : name %s", f->name);
     return (5);
  }

/* For file organization INDEXED and access mode RANDOM or DYNAMIC 
   the KEY defaults to primary key when the KEY phrase is NOT specified
  if ((f->uval1.organization == TCB_FILE_ORGANIZATION_INDEXED) && 
      (key == NULL) && (next_prev == 0)
     ) {
     yyerror("Invalid READ format - phrase NEXT-PREVIOUS is required without KEY phrase for file organization INDEXED : name %s", f->name);
     return (7);
  }

  if ((f->uval1.organization == TCB_FILE_ORGANIZATION_INDEXED) && 
      (f->uval3.access_mode == TCB_FILE_ACCESS_MODE_RANDOM) && 
      (key == NULL) && (next_prev == 0)
     ) {
     yyerror("Invalid READ format - KEY phrase is required for file organization INDEXED with RANDOM access mode : name %s", f->name);
     return (11);
  }
*/

  if ((f->uval1.organization == TCB_FILE_ORGANIZATION_INDEXED) && 
      (f->uval3.access_mode == TCB_FILE_ACCESS_MODE_SEQUENTIAL) && 
      (key != NULL)
     ) {
     yyerror("Invalid READ format - KEY phrase is NOT permitted for file organization INDEXED with SEQUENTIAL access mode : name %s", f->name);
     return (13);
  }

  if ((f->uval1.organization == TCB_FILE_ORGANIZATION_RELATIVE) && 
      (key != NULL)
     ) {
     yyerror("Invalid READ format - KEY phrase is NOT permitted for file organization RELATIVE : name %s", f->name);
     return (17);
  }

  if ((f->uval1.organization == TCB_FILE_ORGANIZATION_RELATIVE) && 
      (f->uval3.access_mode == TCB_FILE_ACCESS_MODE_RANDOM) && 
      (next_prev != 0)
     ) {
     yyerror("Invalid READ format - NEXT-PREVIOUS phrase is not permitted for file organization RELATIVE with RANDOM access mode : name %s", f->name);
     return (19);
  }

  /* READ with [NOT] AT END clauses - organization RELATIVE or INDEXED with SEQUENTIAL access mode only */
  if (((f->uval1.organization == TCB_FILE_ORGANIZATION_INDEXED) || 
       (f->uval1.organization == TCB_FILE_ORGANIZATION_RELATIVE) 
      ) && 
      (f->uval3.access_mode == TCB_FILE_ACCESS_MODE_RANDOM) &&
      (sel == TCB_FILE_READ_PHRASE_AT_END)
     ) {
     yyerror("Invalid READ format - [NOT] AT END phrases are not permitted for file organization RELATIVE-INDEXED with RANDOM access mode : name %s", f->name);
     return (23);
  }

  /* READ with [NOT] INVALID KEY clauses - file organization RELATIVE or INDEXED only */
  if (((f->uval1.organization == TCB_FILE_ORGANIZATION_SEQUENTIAL) || 
       (f->uval1.organization == TCB_FILE_ORGANIZATION_LINESEQUENTIAL) 
      ) && 
      (sel == TCB_FILE_READ_PHRASE_INVALID_KEY)
     ) {
     yyerror("Invalid READ format - [NOT] INVALID KEY phrases are not permitted for file organization (LINE)SEQUENTIAL : name %s", f->name);
     return (31);
  }

  /* READ with [NOT] INVALID KEY clauses - file organization RELATIVE or INDEXED with SEQUENTIAL or DYNAMIC access mode only */
  if (((f->uval1.organization == TCB_FILE_ORGANIZATION_INDEXED) || 
       (f->uval1.organization == TCB_FILE_ORGANIZATION_RELATIVE) 
      ) && 
      (f->uval3.access_mode == TCB_FILE_ACCESS_MODE_SEQUENTIAL) &&
      (sel == TCB_FILE_READ_PHRASE_INVALID_KEY)
     ) {
     yyerror("Invalid READ format - [NOT] INVALID KEY phrases are not permitted for file organization RELATIVE-INDEXED with SEQUENTIAL access mode : name %s", f->name);
     return (23);
  }

#if 0
        /* READ w/o [NOT] AT END or [NOT] INVALID KEY clauses */
         if (sel == 0) {
            if ((next_prev != 0) && (key != NULL)) {
                yyerror("invalid clause NEXT found in READ statement with KEY IS data-name option");
               r++;
            }
            else {
            } 
          
         }
        
        /* READ with [NOT] AT END clauses */
         if (sel == 1) {          
         }
        
        /* READ with [NOT] INVALID KEY clauses */
         if (sel == 2) {
           if (next_prev != 0) {
               yyerror("invalid clause NEXT found in READ statement with INVALID KEY option");
              r++;
           }
           else {
           } 
         }
           
        /* RETURN w/o [NOT] AT END clauses */
         if (sel == 4) {          
         }

        /* RETURN with [NOT] AT END clauses */
         if (sel == 5) {          
         }
#endif

        if (r == 0) {
           /* fprintf(stderr, "sel %d, np %d\n", sel, next_prev); */
           if (f->uval3.access_mode == TCB_FILE_ACCESS_MODE_SEQUENTIAL &&
              f->uval10.sort_file == 1) {
              gen_return_stmt(f, buf);
              return r;
              }
/*           if ((f->uval3.access_mode == TCB_FILE_ACCESS_MODE_SEQUENTIAL || f->uval3.access_mode == ACCEV_SEQUENTIAL) && */
           if ((f->uval3.access_mode == TCB_FILE_ACCESS_MODE_SEQUENTIAL) &&
                f->uval1.organization != TCB_FILE_ORGANIZATION_LINESEQUENTIAL) {
              if (t_next_prev == 0) t_next_prev = 1;
              gen_read_next(f, buf, t_next_prev, withlock);
              return r;
              }
           if ( (sel > -1) && (sel < 4) ) {
              /* if (sel == 1) t_next_prev = 1; */ /* AT END implies read next */
              if ( t_next_prev > 0 
                   && (f->uval1.organization == TCB_FILE_ORGANIZATION_INDEXED || f->uval1.organization == TCB_FILE_ORGANIZATION_RELATIVE)
                   && (f->uval3.access_mode  == TCB_FILE_ACCESS_MODE_DYNAMIC || f->uval3.access_mode  == TCB_FILE_ACCESS_MODE_SEQUENTIAL) 
                   ) {
                 gen_read_next(f, buf, t_next_prev, withlock); 
              }
              else {
                 /* READ ... KEY IS ... clause */
                 int ikey=-1;
                 if (key != NULL) {
                    /* READ KEY validation */
                    ikey = gen_read_key_validate(f,  key); 
                    if (ikey == -1)
                       r = 5;
                    else 
                       gen_read(f, buf, key, ikey, withlock);
                 }
                 else {
                    /* Read with NO NEXT clause implies READ using primary key */
                    if ((f->uval3.access_mode  != TCB_FILE_ACCESS_MODE_SEQUENTIAL) && (f->uval1.organization == TCB_FILE_ORGANIZATION_INDEXED)) {
                       ikey = 0;
                       gen_read(f, buf, f->ix_desc, ikey, withlock);
                    }
                    else {
                       gen_read(f, buf, key, ikey, withlock); 
                    }
                 }
              }
           }
           else {
              if (f->uval1.organization != TCB_FILE_ORGANIZATION_SEQUENTIAL)
                 gen_read_next(f, buf, next_prev, withlock);
              else
                 gen_return_stmt(f, buf);
           }
        }
        return r;
}

int gen_read_key_validate(struct sym *f,  struct sym *k) 
{
  int rc=22, kidx=-1, i;
  struct alternate_list *alt;
  struct sym *s1;

  /* Primary key must exist  */
  if (f->ix_desc == NULL) {
     yyerror("Primary KEY is not defined for file '%s'", f->name);
  }
  else {
     /* Check primary KEY  */
     s1 = f->ix_desc;
     /* Check KEY name  */
     rc = strcmp(s1->name, k->name);
     /* KEY name is primary KEY  */
     if (rc == 0) {
        kidx = 0;
     }
     else {
        /* Check secondary keys  */
        i=1;
        alt = f->uval8.alternate;
        while (alt != NULL) {
           s1 = alt->key;
          /* Check KEY name  */
          rc = 22;
          rc = strcmp(s1->name, k->name);
          /* KEY name is secondary KEY  */
          if (rc == 0) {
             kidx=i;
             break;
          }
          alt = alt->next;
          i++;
        }
     }     
  }     

  /* Error if KEY not found  */
  if (kidx == -1) { 
     yyerror("KEY name '%s' not defined for file '%s'", k->name, f->name);     
  }

  return kidx;
}

void gen_unlock(struct sym *f) 
{
        if (f->type != 'F') {
           yyerror("invalid variable \'%s\', file expected", f->name);
           return;
        }
        gen_save_filevar( f,NULL );
        /* asm_call("tcob_unlock"); */
        asm_call("tcob_unlock_record");
}

void gen_read(struct sym *f, struct sym *buf, struct sym *key, int ikey, int withlock) 
{
  struct rec_varying *rv = f->uval9.rec_varying;
  int iNull=0;

  if (f->uval1.organization == TCB_FILE_ORGANIZATION_INDEXED) {
     if (key != NULL)
        gen_loadvar(key);
     else {
        push_immed(iNull);
        push_immed(iNull);
     }
     push_immed(ikey);
  }

  /* pass the desc/address of reclen, if VARYING ... */
  if (rv != NULL) {
     gen_loadvar(rv->reclen);
  }
  else {
     push_immed(iNull);
     push_immed(iNull);
  }

  /* Save stack frame and set record number  */
  if (f->uval1.organization == TCB_FILE_ORGANIZATION_RELATIVE) {
     if (f->ix_desc != NULL) {
        gen_loadvar(f->ix_desc);
     }
     else {
        push_immed(iNull);
        push_immed(iNull);
     }
  }

  /* Generate INTO-FROM identifier structure 'file_desc' and storage location */
  if (buf != NULL) {
     gen_loadloc(buf);
     gen_loaddesc(buf); 
  }
  else {
     push_immed(iNull);
     push_immed(iNull);
  }

  /*gen_save_filevar(f, buf);*/
  gen_save_filevar2(f);

/*
  if (withlock == 1 ) 
     asm_call1("tcob_setlock");
  else 
     if (withlock == 2)
        asm_call1("tcob_ignorelock");
*/

  switch (f->uval1.organization)
  {
    case TCB_FILE_ORGANIZATION_INDEXED:
      asm_call("tcob_read_idx"); 
      break;
    
    case TCB_FILE_ORGANIZATION_RELATIVE:
      asm_call("tcob_read_rel"); 
      break;
    
    case TCB_FILE_ORGANIZATION_LINESEQUENTIAL:
      asm_call("tcob_read_lseq"); 
      break;
    
    case TCB_FILE_ORGANIZATION_SEQUENTIAL:
      if (f->flags.file_printer == 1) 
         yyerror("READ statement not permited for SEQUENTIAL file '%s' defined as PRINTER file", f->name);
      else
         asm_call("tcob_read_seq"); 
      break;

    default:
      yyerror("Read statement with unknown organization type '%d' for file '%s'", f->uval1.organization, f->name);
      break;
  }
                
  gen_status(f);
  /* Generated file exception if NO after At End or Invalid Key */
  /* gen_perform_decl(f, NULL);  */
}

void gen_read_next(struct sym *f, struct sym *buf, int next_prev, int withlock) 
{
  struct rec_varying *rv;
  int iNull=0;
  char asm_call_str[64] = "tcob_dummy_call";

  if ((next_prev == TCB_FILE_READ_REC_PREVIOUS) &&
      ((f->uval1.organization == TCB_FILE_ORGANIZATION_SEQUENTIAL) ||
       (f->uval1.organization == TCB_FILE_ORGANIZATION_LINESEQUENTIAL)
      )
     ) {
     yyerror("READ PREVIOUS statement not permited with organization type (LINE)SEQUENTIAL for file '%s'", f->name);
     return;
  }
  
  if ((f->flags.file_printer == 1) && (f->uval1.organization == TCB_FILE_ORGANIZATION_SEQUENTIAL) &&
      ((next_prev == 1) || (next_prev == 2))
     ) {
     yyerror("READ NEXT/PREVIOUS statement not permited for SEQUENTIAL file '%s' defined as PRINTER file", f->name);
     return;
  }
  
  switch (f->uval1.organization)
  {
    case TCB_FILE_ORGANIZATION_INDEXED:
      strcpy(asm_call_str, "tcob_read_next_idx");
      break;
  
    case TCB_FILE_ORGANIZATION_RELATIVE:
      strcpy(asm_call_str, "tcob_read_next_rel");
      break;
  
    case TCB_FILE_ORGANIZATION_LINESEQUENTIAL:
      strcpy(asm_call_str, "tcob_read_lseq"); 
      break;
  
    case TCB_FILE_ORGANIZATION_SEQUENTIAL:
      strcpy(asm_call_str, "tcob_read_next_seq");
      break;

    default:
      yyerror("READ NEXT/PREVIOUS statement with unknown organization type '%d' for file '%s'", f->uval1.organization, f->name);
      break;
  }
  
/*
  if (withlock == 1 )
     asm_call1("tcob_setlock");
  else 
     if (withlock == 2)
        asm_call1("tcob_ignorelock");
*/

  rv = f->uval9.rec_varying;
  if (rv != NULL) {
     gen_loadvar(rv->reclen);
  }
  else {
     push_immed(iNull);
     push_immed(iNull);
  }

  if (f->uval1.organization == TCB_FILE_ORGANIZATION_INDEXED)
      push_immed(next_prev);

  /* Save stack frame and set record number  */
  if (f->uval1.organization == TCB_FILE_ORGANIZATION_RELATIVE) {
     if (f->ix_desc != NULL) {
        gen_loadvar(f->ix_desc);
     }
     else {
        push_immed(iNull);
        push_immed(iNull);
     }
  }

  if (f->uval1.organization == TCB_FILE_ORGANIZATION_RELATIVE)
      push_immed(next_prev);

  // Generate INTO-FROM identifier structure 'file_desc' and storage location 
  if (buf != NULL) {
     gen_loadloc(buf);
     gen_loaddesc(buf); 
  }
  else {
     push_immed(iNull);
     push_immed(iNull);
  }

  //gen_save_filevar(f, buf);
  gen_save_filevar2(f);
  asm_call(asm_call_str); 
  /* Must be generated after At End or Invalid Key */
  gen_status(f);

}

void gen_release(struct sym *r, struct sym *buf) 
{
 struct sym *f;
 int iNull=0;
 struct rec_varying *rv;

 f=r->ix_desc;
 if (buf != NULL)
     gen_move(buf, r);

 rv = f->uval9.rec_varying;
 if (rv != NULL) {
    gen_loadvar(rv->reclen);
 }
 else {
    push_immed(iNull);
    push_immed(iNull);
 } 
 gen_save_sort_fields(f, buf);
 asm_call("tcob_sort_release");
 gen_status(f);
 /* gen_perform_decl(f, NULL); */
}

void gen_write_adv(struct sym *r, struct sym *advar, struct sym *ibuf, int opt) 
{
        struct sym *f, *sy1, *sy2;
        struct rec_varying *rv;
        struct file_record_varlen *dvrec;
        int iNull=0;
        struct sym *buf;

        buf = ibuf;
        f=r->ix_desc;
        rv = f->uval9.rec_varying;
        /* gen_check_varying(f); */

        /* opt indicates WITH ADVANCING clauses */
        
        /* INTO-FROM MOVE is done by run-time 
        if (buf != NULL) {
           gen_move(buf, r);
        }
        */
        /* Set the variable record length descriptor */
        if ((rv != NULL) && (r->ri != NULL)) {
           dvrec = (struct file_record_varlen *)r->ri;
           /* Set the variable record length depending on file record format */
           if (dvrec->type == TCB_RECORD_VARLEN_FORMAT3) {
              /* COMPUTE recordLength = minLength + (unitLength * occurances) */
              sy1 = (struct sym *)create_expr('*', (struct expr *)dvrec->ulen, (struct expr *)dvrec->vdepon); 
              sy2 = (struct sym *)create_expr('+', (struct expr *)dvrec->lrec, (struct expr *)sy1); 
              push_expr(sy2);
              assign_expr(rv->reclen, 0, '1'); 
           }
           else {
              /* Intialize rv->reclen */
              gen_move((struct sym *)dvrec->lrec, rv->reclen);
           }
        }
        if (rv != NULL) {
           gen_loadvar(rv->reclen);
        }
        else {
           push_immed(iNull);
           push_immed(iNull);
        }
        if (advar != NULL)
           gen_loadvar(advar);
        else {
           push_immed(iNull);
           push_immed(iNull);
        }
        push_immed(opt);

        /*  Generate INTO-FROM identifier structure 'file_desc' and storage location */
        if (buf != NULL) {
           gen_loadloc(buf);
           gen_loaddesc(buf); 
        }
        else {
           push_immed(iNull);
           push_immed(iNull);
        }
        
        /*  gen_save_filevar( f,buf ); */
        /* Is this code correct ??? It works but ... */
        
        /* gen_save_filevar(f, r); */
        gen_save_filevar2(f);

        /* asm_call("tcob_write_adv"); */
        switch (f->uval1.organization)
        {          
          case TCB_FILE_ORGANIZATION_LINESEQUENTIAL:
            asm_call("tcob_write_adv_lseq");
            break;
        
          case TCB_FILE_ORGANIZATION_SEQUENTIAL:
            if (f->flags.file_printer == 1) 
               asm_call("tcob_write_adv_lseq");
            else
               asm_call("tcob_write_adv_seq");
            break;

          case TCB_FILE_ORGANIZATION_INDEXED:
            yyerror("File '%s' contains an invalid WRITE clause for organization type INDEXED", f->name);
            break;
        
          case TCB_FILE_ORGANIZATION_RELATIVE:
           yyerror("File '%s' contains an invalid WRITE clause for organization type RELATIVE", f->name);
           break;
        
          default:
            yyerror("WRITE statement with unknown organization type '%d' for file '%s'", f->uval1.organization, f->name);
            break;
        }           
        gen_status(f);
        /* gen_perform_decl(f, NULL); */
}

void gen_write(struct sym *r, struct sym *advar, struct sym *ibuf) 
{
        struct sym *f, *sy1, *sy2;
        struct rec_varying *rv;
        struct file_record_varlen *dvrec;
        int iNull=0;
        struct sym *buf;

        buf = ibuf;
        /* Get the FILE structure */
        f=r->ix_desc;
        rv = f->uval9.rec_varying;
        /* gen_check_varying(f); */

/* Handle Write From by moving the data and then setting Buf to NULL
 * only if it is not a relative record.
 */
/*    if ((buf != NULL) && (f->uval1.organization != TCB_FILE_ORGANIZATION_RELATIVE)) { */

        /* INTO-FROM MOVE is done by run-time 
        if (buf != NULL)  {
           gen_move(buf, r);
           buf = NULL;
        }
        */
        if ((rv != NULL) && (r->ri != NULL)) {
           dvrec = (struct file_record_varlen *)r->ri;
           /* Set the variable record length depending on file record format */
           if (dvrec->type == TCB_RECORD_VARLEN_FORMAT3) {
              /* COMPUTE recordLength = minLength + (unitLength * occurances) */
              sy1 = (struct sym *)create_expr('*', (struct expr *)dvrec->ulen, (struct expr *)dvrec->vdepon); 
              sy2 = (struct sym *)create_expr('+', (struct expr *)dvrec->lrec, (struct expr *)sy1); 
              push_expr(sy2);
              assign_expr(rv->reclen, 0, '1'); 
           }
           else {
              /* Intialize rv->reclen */
              gen_move((struct sym *)dvrec->lrec, rv->reclen);
           }
        }
        if (rv != NULL) {
           gen_loadvar(rv->reclen);
        }
        else {
           push_immed(iNull);
           push_immed(iNull);
        }
        /* Save stack frame and set record number  */
        if (f->uval1.organization == TCB_FILE_ORGANIZATION_RELATIVE) {
           if (f->ix_desc != NULL) {
              gen_loadvar(f->ix_desc);
           }
           else {
              push_immed(iNull);
              push_immed(iNull);
           }
        }

        /* Generate INTO-FROM identifier structure 'file_desc' and storage location */
        if (buf != NULL) {
           gen_loadloc(buf);
           gen_loaddesc(buf); 
        }
        else {
           push_immed(iNull);
           push_immed(iNull);
        }

        /* gen_save_filevar(f, buf); */
        gen_save_filevar2(f);

        switch (f->uval1.organization)
        {
          case TCB_FILE_ORGANIZATION_INDEXED:
            asm_call("tcob_write_idx");
            break;
        
          case TCB_FILE_ORGANIZATION_RELATIVE:
            asm_call("tcob_write_rel");
            break;
        
          case TCB_FILE_ORGANIZATION_LINESEQUENTIAL:
            asm_call("tcob_write_lseq");
            break;

          case TCB_FILE_ORGANIZATION_SEQUENTIAL:
            if (f->flags.file_printer == 1) 
               asm_call("tcob_write_lseq");
            else
               asm_call("tcob_write_seq");
            break;

          default:
            yyerror("Unknown file organization type '%d'", f->uval1.organization);
            break;
        }           
        
        gen_status(f);
        /* gen_perform_decl(f, NULL); */
}

void gen_rewrite(struct sym *r, struct sym *buf) 
{
        struct sym *f, *sy1, *sy2;
        struct rec_varying *rv;
        struct file_record_varlen *dvrec;
        int iNull=0;

        f=r->ix_desc;
        if (f->uval1.organization == TCB_FILE_ORGANIZATION_LINESEQUENTIAL) {
           yyerror("File '%s' is organization type LINE SEQUENTIAL and does not support the 'REWRITE' statement", f->name);
           return;
        }

        rv = f->uval9.rec_varying;

        if ((rv != NULL) && (r->ri != NULL)) {
           dvrec = (struct file_record_varlen *)r->ri;
           /* Set the variable record length depending on file record format */
           if (dvrec->type == TCB_RECORD_VARLEN_FORMAT3) {
              /* COMPUTE recordLength = minLength + (unitLength * occurances) */
              sy1 = (struct sym *)create_expr('*', (struct expr *)dvrec->ulen, (struct expr *)dvrec->vdepon); 
              sy2 = (struct sym *)create_expr('+', (struct expr *)dvrec->lrec, (struct expr *)sy1); 
              push_expr(sy2);
              assign_expr(rv->reclen, 0, '1'); 
           }
           else {
              /* Intialize rv->reclen */
              gen_move((struct sym *)dvrec->lrec, rv->reclen);
           }
        }

        if (rv != NULL) {
           gen_loadvar(rv->reclen);
        }
        else {
           push_immed(iNull);
           push_immed(iNull);
        }
        if (f->uval1.organization == TCB_FILE_ORGANIZATION_RELATIVE) {
           if (f->ix_desc != NULL) {
              gen_loadvar(f->ix_desc);
           }
           else {
              push_immed(iNull);
              push_immed(iNull);
           }
        }

        // Generate INTO-FROM identifier structure 'file_desc' and storage location 
        if (buf != NULL) {
           gen_loadloc(buf);
           gen_loaddesc(buf); 
        }
        else {
           push_immed(iNull);
           push_immed(iNull);
        }

        //gen_save_filevar(f, buf);
        gen_save_filevar2(f);

        switch (f->uval1.organization)
        {
          case TCB_FILE_ORGANIZATION_INDEXED:
            asm_call("tcob_rewrite_idx");
            break;
          
          case TCB_FILE_ORGANIZATION_RELATIVE:
            asm_call("tcob_rewrite_rel");
            break;
          
          case TCB_FILE_ORGANIZATION_SEQUENTIAL:
            if (f->flags.file_printer == 1) 
               yyerror("REWRITE statement not permited for SEQUENTIAL file '%s' defined as PRINTER file", f->name);
            else
               asm_call("tcob_rewrite_seq");
            break;

          default:
            yyerror("Rewrite statement is not supported for file organization type '%d'", f->uval1.organization);
            break;
        }

        /* asm_call("tcob_rewrite"); */
        gen_status(f);
        /* gen_perform_decl(f, NULL); */
}

void gen_start(struct sym *f, int cond, struct sym *key) 
{
  int iNull=0, ikey=0, icond;
/*
  if ((cond == LEQ) && (f->uval1.organization == TCB_FILE_ORGANIZATION_RELATIVE))
     yyerror("Invalid START statement conditional LESS THAN OR EQUAL TO");
  if ((cond == LESS) && (f->uval1.organization == TCB_FILE_ORGANIZATION_RELATIVE)) 
     yyerror("Invalid START statement conditional LESS THAN");
*/ 
  /* gen_check_varying(f); */
  if (f->uval1.organization == TCB_FILE_ORGANIZATION_RELATIVE) { 
      if (f->ix_desc != NULL) {
         gen_loadvar(f->ix_desc);
      }
      else {
         push_immed(iNull);
         push_immed(iNull);
      }
      /* If KEY not defined, relative key and EQUAL condition is implied */
      if (cond == 0) 
         icond = EQUAL;
      else 
         icond = cond;
      push_immed(icond);        
      //gen_save_filevar(f, NULL);
      gen_save_filevar2(f);
      asm_call("tcob_start_rel");
  } 

//  else {
  if (f->uval1.organization == TCB_FILE_ORGANIZATION_INDEXED) {
      /* Key description and record */
      /* If KEY not defined, primary key and EQUAL condition is implied */
      if (key == NULL) {
         gen_loadvar(f->ix_desc);
         push_immed(ikey);
         icond = EQUAL;
      }
      /* Key description and record user defined */
      else {
         gen_loadvar(key);
         icond = cond;
         /* Key index (0 - N) */
         ikey = gen_start_key_validate(f,  key);
         push_immed(ikey);
      }      
      push_immed(icond);        
      //gen_save_filevar(f, NULL);
      gen_save_filevar2(f);
      asm_call("tcob_start_idx");
  }

/*
  push_immed(cond);        
  gen_save_filevar(f, NULL);
  if (f->uval1.organization==TCB_FILE_ORGANIZATION_RELATIVE) 
     asm_call("tcob_start_rel");
  if (f->uval1.organization==TCB_FILE_ORGANIZATION_INDEXED) 
     asm_call("tcob_start_idx");
*/
  gen_status(f);
  /* gen_perform_decl(f, NULL); */
}

int gen_start_key_validate(struct sym *f,  struct sym *k)
{
  int rc=22, kidx=-1, i;
  struct alternate_list *alt;
  struct sym *s1, *s2;

  /* Primary key must exist  */
  if (f->ix_desc == NULL) {
     yyerror("Primary KEY is not defined for file '%s'", f->name);
     return kidx;
  }

  /* Check primary KEY  */
  s1 = f->ix_desc;
  /* Check KEY name  */
  rc = strcmp(s1->name, k->name);
  /* KEY name is primary KEY  */
  if (rc == 0) {
     kidx = 0;
  }
  else {
     /* Check primary KEY son - for group items */
     if (s1->type  == DTYPE_GROUP) {
        if (s1->uval7.son != NULL) {
           s2 = s1->uval7.son;
           rc = strcmp(s2->name, k->name);
           if (rc == 0) 
              kidx = 0;
        }
     }
  }
  if (rc == 0) 
     return kidx;

  /* Check secondary keys  */
  i=1;
  alt = f->uval8.alternate;
  while (alt != NULL) {
     s1 = alt->key;
    /* Check KEY name  */
    rc = 22;
    rc = strcmp(s1->name, k->name);
    /* KEY name is secondary KEY  */
    if (rc == 0) {
       kidx = i;
       break;
    }
    else {
       /* Check secondary KEY son - for group items */
       if (s1->type  == DTYPE_GROUP) {
          if (s1->uval7.son != NULL) {
             s2 = s1->uval7.son;
             rc = strcmp(s2->name, k->name);
             if (rc == 0) {
                kidx = i;
                break;
             }
          }
       }
    }
    alt = alt->next;
    i++;
  }

  /* Error if KEY not found  */
  if (kidx == -1) { 
     yyerror("Invalid START key '%s' used for file '%s'", k->name, f->name);     
  }

  return kidx;
}

void gen_delete(struct sym *f) 
{
  int iNull=0;

  /* gen_check_varying(f); */
  if (f->uval1.organization == TCB_FILE_ORGANIZATION_RELATIVE) {
     if (f->ix_desc != NULL) {
        gen_loadvar(f->ix_desc);
     }
     else {
        push_immed(iNull);
        push_immed(iNull);
     }
  }
  //gen_save_filevar(f, NULL);
  gen_save_filevar2(f);
  
  if (f->uval1.organization == TCB_FILE_ORGANIZATION_INDEXED)
     asm_call("tcob_delete_idx");
  else
     asm_call("tcob_delete_rel");
  
  gen_status(f);
  /* gen_perform_decl(f, NULL); */
}

void append_declaratives_list(struct sym *secname, struct tcb_declarative *d)
{
 struct tcb_declarative_list *dl0, *dlw1, *dlw2;
 struct tcb_declaratives_list *dsl0;
 struct tcb_declarative_exception_option *deo;
 struct sym_list *syl1;
 
 if (d == NULL) 
    return;
 
 deo = d->deo;
 if ((deo->type == TCB_DECLARATIVE_USE_OPTIONS_FILE_NAME) && (deo->u.fname != NULL)) {
    deo->u.fname->refmod_redef.declarative = secname;
    syl1 = deo->next;
    while (syl1 != NULL) {
       syl1->sy->refmod_redef.declarative = secname;
       syl1 = syl1->next;
    }
 }

 d->secname = secname;

 dl0 = malloc(sizeof(struct tcb_declarative_list));
 dl0->d = d;
 dl0->next = NULL;

 if (declaratives_list == NULL) {
    dsl0 = malloc(sizeof(struct tcb_declaratives_list));
    dsl0->size = 1;
    if (deo->type == TCB_DECLARATIVE_USE_OPTIONS_FILE_NAME) 
       dsl0->modsize = 0;
    else
       dsl0->modsize = 1;
    dsl0->dl = dl0;
    declaratives_list = dsl0;
#ifdef DEBUG_COMPILER_LEVEL
    fprintf(stderr, "# debug 6050.060 : append_declaratives_list : dsl0->size=%d, dsl0->modsize=%d;\n", dsl0->size, dsl0->modsize); 
#endif
 }
 else {
    dlw1 = declaratives_list->dl;
    while (dlw1 != NULL) {
#ifdef DEBUG_COMPILER_LEVEL
      fprintf(stderr, "# debug 6050.110 : append_declaratives_list : dlw1->d->utype=%d;\n", dlw1->d->utype); 
#endif
       dlw2 = dlw1; 
       dlw1 = dlw2->next;
    }
    dlw2->next = dl0;
    declaratives_list->size++;
    if (deo->type == TCB_DECLARATIVE_USE_OPTIONS_FILE_OPENMODE) 
       declaratives_list->modsize++;
 } 
 
#ifdef DEBUG_COMPILER_LEVEL
 fprintf(stderr, "# debug 6050.210 : append_declaratives_list : declaratives_list->size=%d, declaratives_list->modsize=%d;\n", declaratives_list->size, declaratives_list->modsize); 
#endif

}

struct tcb_declarative * 
define_declarative(int utype, struct tcb_declarative_exception_option *deo, int gtype)
{
 struct tcb_declarative *d;
 
 d = malloc(sizeof(struct tcb_declarative));
 
 d->utype = utype;
 d->deo   = deo;
 //d->otype = otype;
 d->gtype = gtype;

 return d;
}

/*
struct tcb_declarative_exception_option *
set_declarative_exception_option(struct sym *fname, int mode)
{
 struct tcb_declarative_exception_option *deo;
 
 deo = malloc(sizeof(struct tcb_declarative_exception_option));
 
 deo->imode  = mode; 
 deo->fname = fname; 
 
 return deo;
}
*/

struct tcb_declarative_exception_option *
set_declarative_exception_option_mode(int mode)
{
 struct tcb_declarative_exception_option *deo;
 
 deo = malloc(sizeof(struct tcb_declarative_exception_option));
 
 deo->type  = TCB_DECLARATIVE_USE_OPTIONS_FILE_OPENMODE; 
 deo->u.omode = mode; 
 deo->next = NULL; 
 
 return deo;
}

struct tcb_declarative_exception_option *
set_declarative_exception_option_name(struct sym *fname, 
                                      struct tcb_declarative_exception_option *ideo)
{
 struct tcb_declarative_exception_option *deo;
 struct sym_list *syl1;

 if (ideo == NULL) {
    deo = malloc(sizeof(struct tcb_declarative_exception_option));
    deo->type  = TCB_DECLARATIVE_USE_OPTIONS_FILE_NAME; 
    deo->u.fname = fname; 
    deo->next = NULL; 
 }
 else {
    deo = ideo;
    syl1 = malloc(sizeof(struct sym_list)); 
    syl1->sy = fname;
    syl1->next = deo->next;
    deo->next = syl1;
 }

 return deo;
}

struct file_description_entry *set_fd_clause(struct file_description_entry *fd1, struct file_description_entry *fd2)
{
 struct file_description_entry *fd;
 
 if (fd1 == NULL) {
    fd = fd2;
 }
 else {
    if (fd2 == NULL) {
       fd = fd1;
    }
    else {
       fd = fd2;
       fd2->next=fd1; 
    }
 }
 
 return fd;
}

struct file_description_entry *set_fd_clause_external(void)
{
 struct file_description_entry *fd;
 
 fd = malloc(sizeof(struct file_description_entry));
 
 fd->type = TCB_TYPE_FD_EXTERNAL; 
 fd->fd.external=(int)'K'; 
 fd->next=NULL; 
 
 return fd;
}

struct file_description_entry *set_fd_clause_global(void)
{
 struct file_description_entry *fd;
 
 fd = malloc(sizeof(struct file_description_entry));
 
 fd->type = TCB_TYPE_FD_GLOBAL; 
 fd->fd.external=(int)'J'; 
 fd->next=NULL; 
 
 return fd;
}

struct file_description_entry *set_fd_clause_record(struct file_description_record *fdrec)
{
 struct file_description_entry *fd;
 
 fd = malloc(sizeof(struct file_description_entry));
 
 fd->type = TCB_TYPE_FD_RECORD; 
 fd->fd.recd=fdrec;
 fd->next=NULL; 
 
 return fd;
}

struct file_description_record *set_file_record_clause(struct lit *lrecmax, 
       struct lit *lrecmin, struct sym *lrec, int rectype)
{
 struct file_description_record *fdrec;
 char buflen[24];
/* 
// #ifdef DEBUG_COMPILER_LEVEL
//     fprintf(stderr, "# debug 4735.010 : set_file_record_clause : lrecmax->name=%s, lrecmin->name=%s;\n", lrecmax->name, lrecmin->name); 
// #endif
*/
 fdrec = malloc(sizeof(struct file_description_record));
 if (fdrec != NULL) {
    int i, j;
    char ch;

    if (lrecmax != NULL) {
       memset(buflen, 0, 24);
       buflen[0] = ' ';
       strncpy(buflen+1, lrecmax->name, 22);
       i = strlen(buflen);
       ch = buflen[i - 1];
       if (!isdigit(ch)) {
          j = char_to_sign(ch);
          buflen[i - 1] = (char)(j < 0 ? (j * -1) + '0': j + '0');
          if(j < 0)
            buflen[0] = '-';            
       }
       fdrec->imax = atoi(buflen);
       if (fdrec->imax < 1) {
         yyerror("Invalid maximum length %d in FD description", fdrec->imax);
         fdrec->imax = -1;
/*
         fdrec->lmax = NULL;
       }
       else {
          fdrec->lmax = lrecmax;
*/
       }
#ifdef DEBUG_COMPILER_LEVEL
    fprintf(stderr, "# debug 4730.020 : set_file_record_clause : lrecmax->name=%s, fdrec->imax=%d;\n", lrecmax->name, fdrec->imax); 
#endif
    }
    else {
       /* fdrec->lmax = NULL; */
/*       fdrec->imax = -1;        */
       fdrec->imax = 0;       
    }
    if (lrecmin != NULL) {
       memset(buflen, 0, 24);
       buflen[0] = ' ';
       strncpy(buflen+1, lrecmin->name, 22);
       i = strlen(buflen);
       ch = buflen[i - 1];
       if (!isdigit(ch)) {
          j = char_to_sign(ch);
          buflen[i - 1] = (char)(j < 0 ? (j * -1) + '0': j + '0');
          if(j < 0)
            buflen[0] = '-';            
       }
       fdrec->imin = atoi(buflen);
       if (fdrec->imin < 1) {
         yyerror("Invalid minimum length %d in FD description", fdrec->imin);
         fdrec->imin = 0;
/*
         fdrec->lmin = NULL; 
       }
       else {
         fdrec->lmin = lrecmin; 
*/
       }
#ifdef DEBUG_COMPILER_LEVEL
    fprintf(stderr, "# debug 4730.020 : set_file_record_clause : lrecmin->name=%s, fdrec->imin=%d;\n", lrecmin->name, fdrec->imin); 
#endif
    }
    else {
/*       fdrec->imin = -1;       */ 
       fdrec->imin = 0;       
      /*  fdrec->lmin = NULL; */
    }
    
    fdrec->lrec = lrec;
    fdrec->rectype = rectype;
/*
// #ifdef DEBUG_COMPILER_LEVEL
//     fprintf(stderr, "# debug 4750.120 : set_file_record_clause : lrecmin->name=%s, fdrec->imin=%d, lrecmax->name=%s, fdrec->imax=%d;\n", lrecmin->name, fdrec->imin, lrecmax->name, fdrec->imax); 
// #endif
*/
 }
  
 return fdrec;
}

 /* Verify the file description entries */
struct fd_entry *fd_entry_verify(struct sym *f, struct file_description_entry *fd)
{
 struct file_description_entry *fd0;
 struct fd_entry *fde=NULL;
 
 fde = malloc(sizeof(struct fd_entry));
 if (fde == NULL) 
    return fde;
 
 fde->ftype=TCB_TYPE_RECORD_NONE;
 fde->recd=NULL;

 fd0 = fd;    
 while (fd0 != NULL) {
    switch (fd0->type)
    {
      case TCB_TYPE_FD_EXTERNAL:
        if (fde->ftype == TCB_TYPE_RECORD_NONE) {
           fde->ftype = (char)fd0->fd.external;          
        }
        else {
          if (fde->ftype == 'K') {
             yywarn("Duplicate file description entry clause EXTERNAL ignored");
          }
          else {
             yyerror("File description entry clause EXTERNAL conflicts with GLOBAL clause");
          }
        }
        break;
    
      case TCB_TYPE_FD_GLOBAL:
        if (fde->ftype == TCB_TYPE_RECORD_NONE) {
           fde->ftype = (char)fd0->fd.global;                   
        }
        else {
          if (fde->ftype == 'J') {
             yywarn("Duplicate file description entry clause GLOBAL ignored");
          }
          else {
             yyerror("File description entry clause GLOBAL conflicts with EXTERNAL clause");
          }
        }
        break;
    
      case TCB_TYPE_FD_RECORD:
        if (fde->recd == NULL) {
           struct file_description_record *fdrec1;
           
           fde->recd = fd0->fd.recd;
           fdrec1 = fd0->fd.recd;                                
           /*           
           if (fdrec1->rectype == TCB_TYPE_RECORD_VARIABLE) {
             //if (f->uval1.organization == TCB_FILE_ORGANIZATION_LINESEQUENTIAL)
             //   yyerror("Variable record length file (%s) defined with organization 'LINE SEQUENTIAL' is NOT supported", f->name); 
             //
             //if (f->uval1.organization == TCB_FILE_ORGANIZATION_INDEXED) {
             //   yyerror("Variable record length for INDEXED files (%s) is currently NOT supported", f->name); 
             //}
             //if (f->uval1.organization == TCB_FILE_ORGANIZATION_RELATIVE) {
             //   yyerror("Variable record length for RELATIVE files (%s) is currently NOT supported", f->name); 
             //}           
           }           
           */
        }
        else {
           yyerror("Conflicting file description entry RECORD clause for file %s", f->name); 
        }
        break;
    
      default:
        break;
    }
    fd0 = fd0->next;   
 } 
 
 return fde;
}

/* Scan file record entry for OCCURS DEPENDING ON clauses */
struct occurs *gen_fd_record_entry_scan(struct sym *f, struct sym *sy, int *oculen)
{
 int r=0, i, dlen, ulen;
 struct sym *sy1[50];
 struct occurs *oc;

#ifdef DEBUG_COMPILER_LEVEL
 fprintf(stderr, "# debug 4821.000 : gen_fd_record_entry_scan : name=%s, len=%d\n", sy->name, sy->len); 
#endif

 i=0;    
 dlen = 0;
 ulen = 0;
 oc = NULL;
 
 memset (sy1, 0, 50);
 sy1[i] = sy; 
 while (sy1[i] != NULL) {
#ifdef DEBUG_COMPILER_LEVEL
   fprintf(stderr, "# debug 4821.030 : gen_fd_record_entry_scan : name[%02d]=%s, level=%02d, len=%d\n", i, sy1[i]->name, sy1[i]->level, sy1[i]->len); 
#endif
   if (sy1[i]->uval7.son != NULL) {    
       i++;
       sy1[i] = sy1[i - 1]->uval7.son;
#ifdef DEBUG_COMPILER_LEVEL
       fprintf(stderr, "# debug 4821.050 : gen_fd_record_entry_scan : name[%02d]=%s, level=%02d, len=%d\n", i, sy1[i]->name, sy1[i]->level, sy1[i]->len); 
#endif
       if (sy1[i]->occurs != NULL) {
          if (oc == NULL) {
             oc = sy1[i]->occurs;
             ulen = sy1[i]->len;
             dlen = dlen + ((sy1[i]->len * oc->max) - (sy1[i]->len * oc->min)); 
#ifdef DEBUG_COMPILER_LEVEL
             fprintf(stderr, "# debug 4821.055 : gen_fd_record_entry_scan : name[%02d]=%s, level=%02d, len=%d, min=%d, max=%d, dlen=%d\n", i, sy1[i]->name, sy1[i]->level, sy1[i]->len, oc->min, oc->max, dlen); 
#endif
          }
          else {
             yyerror("Multible OCCURS DEPENDING clause found in record description for file %s ", f->name);             
             r++;
          }
       }    
   }
   else {       
       if (sy1[i]->occurs != NULL) {
          if (oc == NULL) {
             oc = sy1[i]->occurs; 
             ulen = sy1[i]->len;
             dlen = dlen + ((sy1[i]->len * oc->max) - (sy1[i]->len * oc->min)); 
#ifdef DEBUG_COMPILER_LEVEL
             fprintf(stderr, "# debug 4821.065 : gen_fd_record_entry_scan : name[%02d]=%s, level=%02d, len=%d, min=%d, max=%d, dlen=%d\n", i, sy1[i]->name, sy1[i]->level, sy1[i]->len, oc->min, oc->max, dlen); 
#endif
          }
          else {
             yyerror("Multible OCCURS DEPENDING clause found in record description for file %s ", f->name);             
             r++;
          }
       }    
       if (sy1[i]->uval8.brother != NULL) {    
          sy1[i] = sy1[i]->uval8.brother;
#ifdef DEBUG_COMPILER_LEVEL
          fprintf(stderr, "# debug 4821.070 : gen_fd_record_entry_scan : name[%02d]=%s, level=%02d, len=%d\n", i, sy1[i]->name, sy1[i]->level, sy1[i]->len); 
#endif
       }
       else {       
          if (i > 0) {
             i--;                 
#ifdef DEBUG_COMPILER_LEVEL
             fprintf(stderr, "# debug 4821.090 : gen_fd_record_entry_scan : name[%02d]=%s, level=%02d, len=%d\n", i, sy1[i]->name, sy1[i]->level, sy1[i]->len); 
#endif
             if (sy1[i]->uval8.brother != NULL) {    
                sy1[i] = sy1[i]->uval8.brother;
                if (sy1[i]->level == 1)  {   
                   sy1[i] = NULL;
                }
                else {
#ifdef DEBUG_COMPILER_LEVEL
                   fprintf(stderr, "# debug 4821.110 : gen_fd_record_entry_scan : name[%02d]=%s, level=%02d, len=%d\n", i, sy1[i]->name, sy1[i]->level, sy1[i]->len); 
#endif
                }
             }
             else {
#ifdef DEBUG_COMPILER_LEVEL
                fprintf(stderr, "# debug 4821.120 : gen_fd_record_entry_scan : name[%02d]=%s, level=%02d, len=%d\n", i, sy1[i]->name, sy1[i]->level, sy1[i]->len); 
#endif
                sy1[i] = NULL;
/*
//                 if (sy1[i]->level == 1)  {   
//                    sy1[i] = NULL;
//                 }
*/
             }
          }
          else {
             sy1[i] = NULL;
          }
       }
   }
#ifdef DEBUG_COMPILER_LEVEL
   fprintf(stderr, "# debug 4821.130 : gen_fd_record_entry_scan : name=%s, len=%d, dlen=%d\n", sy->name, sy->len, dlen); 
#endif
 }
 *oculen = ulen;
         
#ifdef DEBUG_COMPILER_LEVEL
 if (oc == NULL) {
   fprintf(stderr, "# debug 4821.140 : gen_fd_record_entry_scan : name=%s, len=%d, dlen=%d, oc==NULL\n", sy->name, sy->len, dlen);
 }
 else {
   fprintf(stderr, "# debug 4821.150 : gen_fd_record_entry_scan : name=%s, len=%d, dlen=%d, oc!=NULL\n", sy->name, sy->len, dlen);
 }
#endif
 
 return oc; 
}

void set_rec_varying_info(struct sym *f, unsigned int imin, unsigned int imax, struct sym *reclen)
{
        char *s;
        int slen, lrec;
        struct rec_varying *rv;
        struct sym *sy, *tmp;
        char buflrec[24];
         
        /* Define an implicit identifier for record length */
        if (reclen == NULL) {        
        
           sy = malloc(sizeof(struct sym));
           memset(sy, 0, sizeof(struct sym));
           slen = strlen(f->name) + 8;
           s = malloc(slen);
           memset(sy, 0, slen);
           
           sy->litflag=0;
           sprintf(s, "%%RLEN-%s%%", f->name);
           sy->name=s;
           sy->uval1.decimals=0;
           sy->pscale=0;
           sy->level=77;
           sy->type=DTYPE_BININT;
           sy->uval6.redefines = NULL;
           sy->parent=NULL;
           sy->linkage_flg=0;
           sy->sec_no=SEC_DATA; /* not optimal; should be in stack */
           /* sy->sec_no=SEC_STACK; */
           sy->times=1;
           sy->occurs_flg=0;
           sy->occurs=NULL;
           sy->flags.just_r=0;
           sy->flags.separate_sign=0;
           sy->flags.leading_sign=0;
           sy->flags.blank=0;
           sy->uval7.son = NULL;
           sy->uval8.brother = NULL;
           sy->value = NULL;

#ifdef DEBUG_COMPILER_LEVEL
           fprintf(stderr, "# debug 4959.010 : set_rec_varying_info : name=%s\n", spe_lit_ZE->name); 
#endif

           /* Determine the BINARY size 5-9/3-4/1-2 (unsigned int/short/char) */
           memset(buflrec, 0, 24);
           sprintf(buflrec, "%d", imax);
           lrec=strlen(buflrec);
           if (lrec > 9)
              yyerror("Invalid variable record size %s (max: 9 digits) in RECORD clause for file %s", buflrec, f->name);
           
           picture[0] = '9';

           /* Type BINARY 9(5-9)/(3-4)/(1-2) (unsigned int/short/char) */
           switch (lrec)
           {
            case 1:
            case 2:
              sy->len=1; 
              picture[1] = 2;
              break;

            case 3:
            case 4:
              sy->len=2; 
              picture[1] = 4;
              break;
            
            default:
              sy->len=4; 
              picture[1] = 9;
              break;            
           }
          
           picture[2] = 0;
        
           tmp=curr_field;
           curr_field = sy;

           piccnt = sy->len;

/* 
           Initialize to ZERO - does not work ???
           set_variable_values(spe_lit_ZE, spe_lit_ZE);        
*/
           update_field(curr_field);
           close_fields();
           curr_field=tmp;
           tmp=NULL;
        
           reclen = sy;                
        }

        rv = malloc(sizeof(struct rec_varying));
        f->uval9.rec_varying = rv;
        rv->imin = imin;
        rv->imax = imax;
        rv->reclen = reclen;
}

int gen_fsd(struct sym *f, struct sym *fdesc, struct file_description_entry *fd, int iflag)
{
 int r=0, oculen, dlen;
 char lstr[24];
 struct lit *l1;  
 struct sym *sy;
 struct file_record_varlen *dvrec;
 struct fd_entry *fde=NULL;
 struct file_description_record *recd=NULL; 
 struct _ldata ldata;
 struct _vrdata *vrdata, *vdt1, *vdt2;
 struct occurs *oc, oc1;

 oc = NULL;
 vrdata = NULL;
 oc1.depend = NULL;
 oc1.min = 0;
 oc1.max = 0;

 if (fd != NULL) {
   fde = fd_entry_verify(f, fd);
   if (fde != NULL) {
      recd = fde->recd;
      if (fde->ftype != TCB_TYPE_RECORD_NONE)
         f->type = fde->ftype;
   } 
 }

 close_fields();

#ifdef DEBUG_COMPILER_LEVEL
 fprintf(stderr, "# debug 4902.015 : gen_fsd : filename=%s, type=%c, len=%d\n", f->name, f->type, f->len); 
#endif

 sy = fdesc; 
 while (sy != NULL) {
#ifdef DEBUG_COMPILER_LEVEL
    fprintf(stderr, "# debug 4904.005 : gen_fsd : name=%s, type=%c, len=%d\n", sy->name, sy->type, sy->len); 
#endif
    sy->flags.isfilerecord = 1;
#ifdef DEBUG_COMPILER_LEVEL
    fprintf(stderr, "# debug 4904.007 : gen_fsd : name=%s, type=%c, len=%d\n", sy->name, sy->type, sy->len); 
#endif
    sy = sy->uval6.redefines; 
 }

 f->uval6.recordsym = fdesc;
  
 /* Scan file record entries to determine type of file */
 ldata.imin = 0;
 ldata.imax = 0;
 sy = fdesc; 
 if (sy != NULL) {
    ldata.imax = sy->len;
    ldata.imin = sy->len;
 }
 while (sy != NULL) {
    oculen = 0;
    dlen = 0;
    vdt1 = malloc(sizeof(struct _vrdata));

    /* Scan file record entry for OCCURS DEPENDING ON clauses */
    oc = gen_fd_record_entry_scan(f, sy, &oculen);
#ifdef DEBUG_COMPILER_LEVEL
    fprintf(stderr, "# debug 4904.010 : gen_fsd : name=%s, len=%d, oculen=%d\n", sy->name, sy->len, oculen); 
    if (oc == NULL) 
       fprintf(stderr, "# debug 4904.015 : gen_fsd : name=%s, len=%d, oculen=%d, oc==NULL\n", sy->name, sy->len, oculen); 
#endif

    vdt1->type = TCB_TYPE_RECORD_NONE;
    vdt1->lrec = sy->len;
    vdt1->oc = oc;
    vdt1->oculen = oculen;
    vdt1->next = NULL;

    /* Determine the difference between max-min in OCCURS DEPENDING clause */ 
    if (oc != NULL) {
       dlen =  oculen * (oc->max - oc->min);
#ifdef DEBUG_COMPILER_LEVEL
       fprintf(stderr, "# debug 4904.020 : gen_fsd : name=%s, len=%d, dlen=%d, min=%d, max=%d\n", sy->name, sy->len, dlen, oc->min, oc->max); 
#endif
       ldata.imin = sy->len - dlen;
    }
#ifdef DEBUG_COMPILER_LEVEL
    else {
       fprintf(stderr, "# debug 4904.025 : gen_fsd : name=%s, len=%d, dlen=%d, min=%d, max=%d\n", sy->name, sy->len, dlen, ldata.imin, ldata.imax); 
    }
    fprintf(stderr, "# debug 4904.035 : gen_fsd : name=%s, len=%d, dlen=%d, min=%d, max=%d\n", sy->name, sy->len, dlen, ldata.imin, ldata.imax); 
#endif
    
    /* determine the max-min record length in the record list */
    if (sy->len >= ldata.imax) {
       if (ldata.imax == 0) {
          ldata.imax = sy->len;
       }
       else {
          if ((ldata.imax <= ldata.imin) || (ldata.imin == 0))
             ldata.imin = ldata.imax;
          ldata.imax = sy->len;
       }
/*
//       if ((ldata.imax <= ldata.imin) || (ldata.imin != 0))
//          ldata.imin = ldata.imax;
//       ldata.imax = sy->len;
*/
#ifdef DEBUG_COMPILER_LEVEL
    fprintf(stderr, "# debug 4925.035 : gen_fsd : name=%s, len=%d, dlen=%d, min=%d, max=%d\n", sy->name, sy->len, dlen, ldata.imin, ldata.imax); 
#endif
    }
    else {
       if (dlen == 0) {
          if (sy->len < ldata.imin) 
             ldata.imin = sy->len;
       }
       else {
          if ((sy->len - dlen) > ldata.imin) 
             ldata.imin = sy->len - dlen;
       }   
#ifdef DEBUG_COMPILER_LEVEL
    fprintf(stderr, "# debug 4925.055 : gen_fsd : name=%s, len=%d, dlen=%d, min=%d, max=%d\n", sy->name, sy->len, dlen, ldata.imin, ldata.imax); 
#endif
    }   

#ifdef DEBUG_COMPILER_LEVEL
    fprintf(stderr, "# debug 4980.015 : gen_fsd : name=%s, len=%d, min=%d, max=%d\n", sy->name, sy->len, ldata.imin, ldata.imax); 
#endif

    if (vrdata == NULL) {
      vrdata = vdt1;
    }
    else {
      vdt2 = vrdata;
      while (vdt2->next != NULL) {
        vdt2 = vdt2->next;
      }
      vdt2->next = vdt1;
    }
    
    sy = sy->uval6.redefines; 
 }

#ifdef DEBUG_COMPILER_LEVEL
 fprintf(stderr, "# debug 4985.010 : gen_fsd : filename=%s, filelen=%d, min=%d, max=%d\n", f->name, f->len, ldata.imin, ldata.imax); 
#endif

 /* If record type is VARIABLE then add variable length structures */
 if ((recd != NULL) || (ldata.imin != ldata.imax)) {
    
    sy = fdesc; 
    vdt1 = vrdata;
    while (sy != NULL) {
       if (vdt1 != NULL) {
          oc = vdt1->oc;
          oculen = vdt1->oculen;
       }
       else {
          oc = NULL;       
          oculen = 0;
       }
       sy->ri = NULL;
       if (recd == NULL) {
          dvrec = malloc(sizeof(struct file_record_varlen));
          if (oc == NULL) {
             memset(lstr, 0, 24);
             sprintf(lstr, "%d", sy->len);
             l1 = (struct lit *)install_lit(lstr, 0, 0);  
             save_literal(l1, DTYPE_DISPLAY);
#ifdef DEBUG_COMPILER_LEVEL
             fprintf(stderr, "# debug 5080.010 : gen_fsd : literal=%s\n", lstr); 
#endif
             dvrec->type = TCB_RECORD_VARLEN_FORMAT1;
             dvrec->lrec = l1;
             dvrec->ulen = NULL;
             dvrec->vdepon = NULL;
          }
          else {
             memset(lstr, 0, 24);
             dlen = sy->len - (oc->max * oculen);
             sprintf(lstr, "%d", dlen);
             l1 = (struct lit *)install_lit(lstr, 0, 0);  
             save_literal(l1, DTYPE_DISPLAY);
#ifdef DEBUG_COMPILER_LEVEL
             fprintf(stderr, "# debug 5080.020 : gen_fsd : literal=%s\n", lstr); 
#endif
             dvrec->lrec = l1;
             memset(lstr, 0, 24);
             sprintf(lstr, "%d", oculen);
             l1 = (struct lit *)install_lit(lstr, 0, 0);  
             save_literal(l1, DTYPE_DISPLAY);
#ifdef DEBUG_COMPILER_LEVEL
             fprintf(stderr, "# debug 5080.030 : gen_fsd : literal=%s\n", lstr); 
#endif
             dvrec->ulen = l1;
             dvrec->vdepon = oc->depend;
             dvrec->type = TCB_RECORD_VARLEN_FORMAT3;
          }
          sy->ri = (struct report_info *)dvrec;
       }
       else {
          if ((recd->lrec == NULL) && (recd->rectype == TCB_TYPE_RECORD_VARIABLE)) {   
              dvrec = malloc(sizeof(struct file_record_varlen));
              if (oc == NULL) {
                 memset(lstr, 0, 24);
                 sprintf(lstr, "%d", sy->len);
                 l1 = (struct lit *)install_lit(lstr, 0, 0);  
                 save_literal(l1, DTYPE_DISPLAY);
#ifdef DEBUG_COMPILER_LEVEL
                 fprintf(stderr, "# debug 5080.060 : gen_fsd : literal=%s\n", lstr); 
#endif
                 dvrec->type = TCB_RECORD_VARLEN_FORMAT1;
                 dvrec->lrec = l1;
                 dvrec->ulen = NULL;
                 dvrec->vdepon = NULL;
              }
              else {
                 memset(lstr, 0, 24);
                 dlen = sy->len - (oc->max * oculen);
                 sprintf(lstr, "%d", dlen);
                 l1 = (struct lit *)install_lit(lstr, 0, 0);  
                 save_literal(l1, DTYPE_DISPLAY);
#ifdef DEBUG_COMPILER_LEVEL
                 fprintf(stderr, "# debug 4864.040 : gen_fsd : literal=%s\n", lstr); 
#endif
                 dvrec->lrec = l1;
                 memset(lstr, 0, 24);
                 sprintf(lstr, "%d", oculen);
                 l1 = (struct lit *)install_lit(lstr, 0, 0);  
                 save_literal(l1, DTYPE_DISPLAY);
#ifdef DEBUG_COMPILER_LEVEL
                 fprintf(stderr, "# debug 5080.080 : gen_fsd : literal=%s\n", lstr); 
#endif
                 dvrec->ulen = l1;
                 dvrec->vdepon = oc->depend;
                 dvrec->type = TCB_RECORD_VARLEN_FORMAT3;
              }
              sy->ri = (struct report_info *)dvrec;
          }
       }
       sy = sy->uval6.redefines; 
       vdt1 = vdt1->next;
    }
 }

#ifdef DEBUG_COMPILER_LEVEL
 fprintf(stderr, "# debug 5180.030 : gen_fsd : filename=%s, filelen=%d, min=%d, max=%d\n", f->name, f->len, ldata.imin, ldata.imax); 
#endif

 /* Trap errors and warnings for the variable length structures if required */
 if (recd != NULL) {    
#ifdef DEBUG_COMPILER_LEVEL
    fprintf(stderr, "# debug 5180.050 : gen_fsd : filename=%s, filelen=%d, type=%d, ldata(%d %d), recd(%d %d)\n", 
                     f->name, f->len, recd->rectype, ldata.imin, ldata.imax, recd->imin, recd->imax); 
#endif
    if (recd->rectype == TCB_TYPE_RECORD_VARIABLE) {    
       /*
       if ((ldata.imin != recd->imin) && (recd->imin > 0))
          yyerror("Minimum record length description is inconsistent with minimum length FD description for file %s", f->name);
       if ((ldata.imax != recd->imax) && (recd->imax > 0))
          yyerror("Maximum record length description is inconsistent with maximum length FD description for file %s", f->name);
       if ((recd->imin >= recd->imax) && (recd->imin > 0) && (recd->imax > 0))
          yyerror("Invalid or inconsistent variable length FD description for file %s", f->name);
       */
    }
    else {
       if (ldata.imin != ldata.imax)
          yyerror("Variable length record description is inconsistent with fixed length FD description for file %s", f->name);
       if ((ldata.imax != recd->imax) && (recd->imax > 0))
          yyerror("Invalid or inconsistent variable length FD description for file %s", f->name);
    }
 }
 else {
#ifdef DEBUG_COMPILER_LEVEL
    fprintf(stderr, "# debug 5180.150 : gen_fsd : filename=%s, filelen=%d, ldata(%d %d)\n", 
                       f->name, f->len, ldata.imin, ldata.imax); 
#endif
    if (ldata.imin != ldata.imax) {
       if ((HTG_verbose_flag == TRUE) || (HTG_verbose_verbose_flag == TRUE))
          yywarn("Variable record length assumed for file %s", f->name);
    }
 }

#ifdef DEBUG_COMPILER_LEVEL
 fprintf(stderr, "# debug 5180.180 : gen_fsd : filename=%s, filelen=%d, ldata(%d %d)\n", 
                     f->name, f->len, ldata.imin, ldata.imax); 
#endif

 /* Generate file structures */
 alloc_file_entry(f, iflag);
 f->len = ldata.imax;
 f->minlen = ldata.imin; 
 if (ldata.imin != ldata.imax)
    f->flags.file_isvariable = 1;
 gen_fdesc(f, fdesc);

/* Generate the variable length structures if required */
 if (recd != NULL) {    
    if (recd->rectype == TCB_TYPE_RECORD_VARIABLE)    
       set_rec_varying_info(f, ldata.imin, ldata.imax, recd->lrec);    
 }
 else {
    if (ldata.imin != ldata.imax)
       set_rec_varying_info(f, ldata.imin, ldata.imax, NULL);    
 }

#ifdef DEBUG_COMPILER_LEVEL
 fprintf(stderr, "# debug 5180.190 : gen_fsd : filename=%s, filelen=%d, ldata(%d %d)\n", 
                     f->name, f->len, ldata.imin, ldata.imax); 
#endif

/*
 DO REMOVE : Will cause file memory problems in assembler code
 alloc_file_entry(f, iflag);
 f->len = ldata.imax;
 f->minlen = ldata.imin;
 gen_fdesc(f, fdesc);
*/

 return r;
}

/* Replaced by gen_fsd */
int gen_sd(struct sym *f, struct sym *fdesc, struct file_description_entry *fd)
{
 int r=0, oculen, dlen;
 char lstr[24];
 struct lit *l1;  
 struct sym *sy;
 struct file_record_varlen *dvrec;
 struct fd_entry *fde=NULL;
 struct file_description_record *recd=NULL; 
 struct _ldata ldata;
 struct _vrdata *vrdata, *vdt1, *vdt2;
 struct occurs *oc, oc1;

 oc = NULL;
 vrdata = NULL;
 oc1.depend = NULL;
 oc1.min = 0;
 oc1.max = 0;

 if (fd != NULL) {
   fde = fd_entry_verify(f, fd);
   if (fde != NULL) {
      recd = fde->recd;
      if (fde->ftype != TCB_TYPE_RECORD_NONE)
         f->type = fde->ftype;
   } 
 }

 close_fields();

#ifdef DEBUG_COMPILER_LEVEL
 fprintf(stderr, "# debug 5705.010 : gen_sd : filename=%s, type=%c, len=%d\n", f->name, f->type, f->len); 
#endif

 sy = fdesc; 
 while (sy != NULL) {
#ifdef DEBUG_COMPILER_LEVEL
    fprintf(stderr, "# debug 5705.020 : gen_sd : name=%s, type=%c, len=%d\n", sy->name, sy->type, sy->len); 
#endif
    sy->flags.isfilerecord = 1;
#ifdef DEBUG_COMPILER_LEVEL
    fprintf(stderr, "# debug 5705.030 : gen_sd : name=%s, type=%c, len=%d\n", sy->name, sy->type, sy->len); 
#endif
    sy = sy->uval6.redefines; 
 }

 f->uval6.recordsym = fdesc;


 /* Scan file record entries to determine type of file */
 ldata.imin = 0;
 ldata.imax = 0;
 sy = fdesc; 
 if (sy != NULL) {
    ldata.imax = sy->len;
    ldata.imin = sy->len;
 }
 while (sy != NULL) {
    oculen = 0;
    dlen = 0;
    vdt1 = malloc(sizeof(struct _vrdata));

    /* Scan file record entry for OCCURS DEPENDING ON clauses */
    oc = gen_fd_record_entry_scan(f, sy, &oculen);
#ifdef DEBUG_COMPILER_LEVEL
    fprintf(stderr, "# debug 5705.040 : gen_sd : name=%s, len=%d, oculen=%d\n", sy->name, sy->len, oculen); 
    if (oc == NULL) 
       fprintf(stderr, "# debug 5705.045 : gen_sd : name=%s, len=%d, oculen=%d, oc==NULL\n", sy->name, sy->len, oculen); 
#endif

    vdt1->type = TCB_TYPE_RECORD_NONE;
    vdt1->lrec = sy->len;
    vdt1->oc = oc;
    vdt1->oculen = oculen;
    vdt1->next = NULL;

    /* Determine the difference between max-min in OCCURS DEPENDING clause */ 
    if (oc != NULL) {
       dlen =  oculen * (oc->max - oc->min);
#ifdef DEBUG_COMPILER_LEVEL
       fprintf(stderr, "# debug 5705.060 : gen_sd : name=%s, len=%d, dlen=%d, min=%d, max=%d\n", sy->name, sy->len, dlen, oc->min, oc->max); 
#endif
    }
#ifdef DEBUG_COMPILER_LEVEL
    else {
       fprintf(stderr, "# debug 5705.085 : gen_sd : name=%s, len=%d, dlen=%d, min=%d, max=%d\n", sy->name, sy->len, dlen, ldata.imin, ldata.imax); 
    }
    fprintf(stderr, "# debug 5705.095 : gen_sd : name=%s, len=%d, dlen=%d, min=%d, max=%d\n", sy->name, sy->len, dlen, ldata.imin, ldata.imax); 
#endif
    
    /* determine the max-min record length in the record list */
    if (sy->len > ldata.imax) 
       ldata.imax = sy->len;
    if (dlen == 0) {
       if (sy->len < ldata.imin) 
          ldata.imin = sy->len;
    }
    else {
       if ((sy->len - dlen) < ldata.imin) 
          ldata.imin = sy->len - dlen;
    }   

#ifdef DEBUG_COMPILER_LEVEL
    fprintf(stderr, "# debug 5705.105 : gen_sd : name=%s, len=%d, min=%d, max=%d\n", sy->name, sy->len, ldata.imin, ldata.imax); 
#endif

    if (vrdata == NULL) {
      vrdata = vdt1;
    }
    else {
      vdt2 = vrdata;
      while (vdt2->next != NULL) {
        vdt2 = vdt2->next;
      }
      vdt2->next = vdt1;
    }

    sy = sy->uval6.redefines; 
 }

#ifdef DEBUG_COMPILER_LEVEL
 fprintf(stderr, "# debug 5705.115: gen_sd : filename=%s, filelen=%d, min=%d, max=%d\n", f->name, f->len, ldata.imin, ldata.imax); 
#endif

 /* If record type is VARIABLE then add variable length structures */
 if ((recd != NULL) || (ldata.imin != ldata.imax)) {
    
    sy = fdesc; 
    vdt1 = vrdata;
    while (sy != NULL) {
       if (vdt1 != NULL) {
          oc = vdt1->oc;
          oculen = vdt1->oculen;
       }
       else {
          oc = NULL;       
          oculen = 0;
       }
       sy->ri = NULL;
       if (recd == NULL) {
          dvrec = malloc(sizeof(struct file_record_varlen));
          if (oc == NULL) {
             memset(lstr, 0, 24);
             sprintf(lstr, "%d", sy->len);
             l1 = (struct lit *)install_lit(lstr, 0, 0);  
             save_literal(l1, DTYPE_DISPLAY);
#ifdef DEBUG_COMPILER_LEVEL
             fprintf(stderr, "# debug 5705.120 : gen_sd : literal=%s\n", lstr); 
#endif
             dvrec->type = TCB_RECORD_VARLEN_FORMAT1;
             dvrec->lrec = l1;
             dvrec->ulen = NULL;
             dvrec->vdepon = NULL;
          }
          else {
             memset(lstr, 0, 24);
             dlen = sy->len - (oc->max * oculen);
             sprintf(lstr, "%d", dlen);
             l1 = (struct lit *)install_lit(lstr, 0, 0);  
             save_literal(l1, DTYPE_DISPLAY);
#ifdef DEBUG_COMPILER_LEVEL
             fprintf(stderr, "# debug 5705.125 : gen_sd : literal=%s\n", lstr); 
#endif
             dvrec->lrec = l1;
             memset(lstr, 0, 24);
             sprintf(lstr, "%d", oculen);
             l1 = (struct lit *)install_lit(lstr, 0, 0);  
             save_literal(l1, DTYPE_DISPLAY);
#ifdef DEBUG_COMPILER_LEVEL
             fprintf(stderr, "# debug 5705.130 : gen_sd : literal=%s\n", lstr); 
#endif
             dvrec->ulen = l1;
             dvrec->vdepon = oc->depend;
             dvrec->type = TCB_RECORD_VARLEN_FORMAT3;
          }
          sy->ri = (struct report_info *)dvrec;
       }
       else {
          if ((recd->lrec == NULL) && (recd->rectype == TCB_TYPE_RECORD_VARIABLE)) {   
              dvrec = malloc(sizeof(struct file_record_varlen));
              if (oc == NULL) {
                 memset(lstr, 0, 24);
                 sprintf(lstr, "%d", sy->len);
                 l1 = (struct lit *)install_lit(lstr, 0, 0);  
                 save_literal(l1, DTYPE_DISPLAY);
#ifdef DEBUG_COMPILER_LEVEL
                 fprintf(stderr, "# debug 5705.160 : gen_sd : literal=%s\n", lstr); 
#endif
                 dvrec->type = TCB_RECORD_VARLEN_FORMAT1;
                 dvrec->lrec = l1;
                 dvrec->ulen = NULL;
                 dvrec->vdepon = NULL;
              }
              else {
                 memset(lstr, 0, 24);
                 dlen = sy->len - (oc->max * oculen);
                 sprintf(lstr, "%d", dlen);
                 l1 = (struct lit *)install_lit(lstr, 0, 0);  
                 save_literal(l1, DTYPE_DISPLAY);
#ifdef DEBUG_COMPILER_LEVEL
                 fprintf(stderr, "# debug 5705.170 : gen_sd : literal=%s\n", lstr); 
#endif
                 dvrec->lrec = l1;
                 memset(lstr, 0, 24);
                 sprintf(lstr, "%d", oculen);
                 l1 = (struct lit *)install_lit(lstr, 0, 0);  
                 save_literal(l1, DTYPE_DISPLAY);
#ifdef DEBUG_COMPILER_LEVEL
                 fprintf(stderr, "# debug 5705.180 : gen_sd : literal=%s\n", lstr); 
#endif
                 dvrec->ulen = l1;
                 dvrec->vdepon = oc->depend;
                 dvrec->type = TCB_RECORD_VARLEN_FORMAT3;
              }
              sy->ri = (struct report_info *)dvrec;
          }
       }
       sy = sy->uval6.redefines; 
       vdt1 = vdt1->next;
    }
 }

#ifdef DEBUG_COMPILER_LEVEL
 fprintf(stderr, "# debug 5705.210 : gen_sd : filename=%s, filelen=%d, min=%d, max=%d\n", f->name, f->len, ldata.imin, ldata.imax); 
#endif

 /* Trap errors and warnings for the variable length structures if required */
 if (recd != NULL) {    
    if (recd->rectype == TCB_TYPE_RECORD_VARIABLE) {    
       /*
       if ((ldata.imin != recd->imin) && (recd->imin > 0))
          yyerror("Minimum record length description is inconsistent with minimum length FD description for file %s", f->name);
       if ((ldata.imax != recd->imax) && (recd->imax > 0))
          yyerror("Maximum record length description is inconsistent with maximum length FD description for file %s", f->name);
       if ((recd->imin >= recd->imax) && (recd->imin > 0) && (recd->imax > 0))
          yyerror("Invalid or inconsistent variable length FD description for file %s", f->name);
       */
    }
    else {
       if (ldata.imin != ldata.imax)
          yyerror("Variable length record description is inconsistent with fixed length FD description for file %s", f->name);
       if ((ldata.imax != recd->imax) && (recd->imax > 0))
          yyerror("Invalid or inconsistent variable length FD description for file %s", f->name);
    }
 }
 else {
    if (ldata.imin != ldata.imax)
       yywarn("Variable record length assumed for file %s", f->name);
 }

 /* Generate the variable length structures if required */
 if (recd != NULL) {    
    if (recd->rectype == TCB_TYPE_RECORD_VARIABLE)    
       set_rec_varying_info(f, ldata.imin, ldata.imax, recd->lrec);    
 }
 else {
    if (ldata.imin != ldata.imax)
       set_rec_varying_info(f, ldata.imin, ldata.imax, NULL);    
 }

 
 alloc_file_entry(f, 1);
 f->len = ldata.imax;
 f->minlen = ldata.imin;
 gen_fdesc(f, fdesc);
 

 return r;
}

int get_switch_number( struct sym *sy) 
{
 return (sy->name[2] - '0');
}

void gen_get_switches() {
        struct list *l = switches_list;
        struct sym *svar;

        while(l != NULL) {
                svar = l->var;
                push_immed(get_switch_number(svar->ix_desc));
                gen_loadvar(svar);
                asm_call("tcob_get_switch");
                l = l-> next;
        }
}

void gen_set_switch( struct sym *var, struct sym *sy ) {

        gen_move(var, sy);
        push_immed(get_switch_number(sy->ix_desc));
        gen_loadvar(sy);
        asm_call("tcob_set_switch");

}

struct list *chain_var( struct sym *sy ) {
        vars_list = insert_list(vars_list, sy);
        return vars_list;
}

void gen_push_using( struct sym *sy ) {
        struct parm_list *list;
        if (sy->type=='F')
           yyerror("file name %s used as parameter in CALL statement", sy->name);
        list = (struct parm_list *)malloc(sizeof(struct parm_list));
        list->var = (void *)sy;
        list->next = parameter_list;
        list->location = 0;
        list->sec_no = 0;
        parameter_list = list;
}

void gen_save_usings(struct gvar_list *gsylst) {
   struct gvar_list *gl;
        
   for (gl=gsylst; gl->next != NULL; gl=gl->next) 
   {        
     gen_save_using (gl->u.sym);
   }        
   gen_save_using (gl->u.sym);
}

void gen_save_using( struct sym *sy ) {
        sy->linkage_flg = using_offset;
        using_offset += 4;
}

void gen_save_chainings(struct gvar_list *gsylst) {
   struct gvar_list *gl;
        
   for (gl=gsylst; gl->next != NULL; gl=gl->next) 
   {        
     gen_save_chaining (gl->u.sym);
   }        
   gen_save_chaining (gl->u.sym);
}

void gen_save_chaining( struct sym *sy ) {
        struct parm_list *list;
        if ( sy->type == 'F' )
                yyerror("only variables could be used as parameter in CHAINING");
        list = (struct parm_list *)malloc(sizeof(struct parm_list));
        list->var = (void *)sy;
        list->next = chaining_list;
        list->location = 0;
        list->sec_no = 0;
        chaining_list = list;
}

void gen_chain( struct sym *v, int stack_size, int exceplabel) {

        struct parm_list *list,*tmp;
        struct sym *cp;
#ifdef DEBUG_COMPILER
        fprintf(o_src, "#chain %s\n", v->name);
#endif
        push_immed(0);
        for (list=parameter_list;list!=NULL;list=tmp) {
                cp=(struct sym *)list->var;
                gen_loadvar( cp );
                tmp=list->next;
                free(list);
        }                
        parameter_list=NULL;
        gen_loadvar( v );
        asm_call("tcob_chain");

}

short get_std_val( struct sym *sy ) {
        if (sy->value == NULL) {return 0;}
        else if (sy->value == spe_lit_ZE) {return 2;}
        else if (sy->value == spe_lit_SP) {return 3;}
        else if (sy->value == spe_lit_LV) {return 4;}
        else if (sy->value == spe_lit_HV) {return 5;}
        else {return 1;}
}

/*
 *  Count the number of items under the field sy
 *  if (sw_val) ???
 */
int get_nb_fields( struct sym *sy, int sw_val ) {
        struct sym *tmp;
        int nb_fields = 1, tmpnf;
        char ftype = sy->type;
        short val;

        if (sy->type == DTYPE_GROUP) {
                for(tmp=sy->uval7.son;tmp!=NULL;tmp=tmp->uval8.brother) {
                        tmpnf = get_nb_fields(tmp, sw_val);

                        if (tmp->uval6.redefines == NULL)
                                nb_fields += tmpnf;
                }
        } else {
                /* Packed fields are presently considered non-homogenous */
                if (ftype == DTYPE_PACKED) ftype = '&';
                if (ftype == DTYPE_DISPLAY && sy->uval9.picstr[0] == 'S') ftype = '&';
                if (init_ctype == ' ') init_ctype = ftype;
                if (ftype != init_ctype && init_ctype != '&')
                        init_ctype = '&';
                if (sw_val) {
                        val = get_std_val(sy);
                        if (init_val == -1) init_val = val;
                        if (ftype == init_ctype && init_ctype != '&' &&
                                val != init_val)
                                init_ctype = '&';
                }
        }
        return nb_fields * sy->times;
}
/*
 * sy : field
 * initp : 0
 * init_loc : initial location 
 * nb_fields : number of fields 
 */
static int _build_init_str( struct sym *sy, int initp,
                            unsigned *init_loc, int nb_fields ) {
        char mem_warn[] = "**** WARNING invading end of malloced memory";
        struct sym *tmp;
        int stidx = -1, endidx = -1;
        int i, j;

        if (initp >= nb_fields) {
                fprintf(stderr, "%s, f,sym: %s\n", mem_warn, sy->name);
                return initp;
        }

        stidx = initp;
        istrp->ent[initp].sy = sy;
        istrp->ent[initp].type = sy->type;
        istrp->ent[initp].value = sy->value;
        istrp->ent[initp].len = symlen(sy);
        istrp->ent[initp].location = *init_loc;
        if (sy->type != DTYPE_GROUP){
                *init_loc += istrp->ent[initp].len;
        }
        initp++;
        if (sy->type == DTYPE_GROUP) {
                for(tmp=sy->uval7.son;tmp!=NULL;tmp=tmp->uval8.brother) {
                        if (tmp->uval6.redefines == NULL)
                                initp = _build_init_str(tmp, initp, init_loc, nb_fields);
                }
        }
        endidx = initp;

        for (i=1;i<sy->times;i++) {
                if (initp >= nb_fields) {
                        fprintf(stderr, "%s, i,sym: %s\n", mem_warn, sy->name);
                        break;
                }
                for (j=stidx;j<endidx;j++) {
                        if (initp >= nb_fields) {
                                fprintf(stderr, "%s, j,sym: %s\n", mem_warn, sy->name);
                                break;
                        }
                        istrp->ent[initp].sy = istrp->ent[j].sy;
                        istrp->ent[initp].type = istrp->ent[j].type;
                        istrp->ent[initp].value = istrp->ent[j].value;
                        istrp->ent[initp].len = istrp->ent[j].len;
                        istrp->ent[initp].location = *init_loc;
                        if (istrp->ent[j].type != DTYPE_GROUP)
                                *init_loc += istrp->ent[initp].len;
                        initp++;
                }
        }

        return initp;
}

int build_init_str( struct sym *sy, int nb_fields ) {
        unsigned init_loc = sy->uval2.location;
        return _build_init_str (sy, 0, &init_loc, nb_fields);
}

void gen_from_init_str(int nb_fields) {
        int i;

        for(i=0;i<nb_fields;i++) {
                unsigned temp_loc = istrp->ent[i].sy->uval2.location;
                istrp->ent[i].sy->uval2.location = istrp->ent[i].location;
                gen_init_str(istrp->ent[i].sy, istrp->ent[i].type, istrp->ent[i].len);
                istrp->ent[i].sy->uval2.location = temp_loc;
                }
}
/*
 *  Initialize field 'sy' of type 'init_ctype' and of length 'len' 
 *
 */
void gen_init_str( struct sym *sy, char init_ctype, int len ) {
#ifdef DEBUG_COMPILER
        fprintf(o_src,"# init_str %s, type %c, len %d, loc %d\n",sy->name, init_ctype, len, sy->uval2.location);
#endif
        switch (init_ctype) {
         case DTYPE_DISPLAY:
         case DTYPE_PACKED:
          gen_move((struct sym *)spe_lit_ZE, sy);
          break;
         case DTYPE_BININT:
          if (sy->type == DTYPE_BININT) {
             if (sy->flags.is_index == 1) 
                 gen_move((struct sym *)spe_lit_01, sy);
             else                 
                 gen_move((struct sym *)spe_lit_ZE, sy);
          }
          else
               gen_move((struct sym *)spe_lit_LV, sy);
          break;
         default:
          gen_move((struct sym *)spe_lit_SP, sy);
          break;
        }                
}
/*
 *  Generate an initialize field 
 *
 */
void gen_initializes(struct gvar_list *gsylst) {
   struct gvar_list *gl;
        
   for (gl=gsylst; gl->next != NULL; gl=gl->next) 
   {        
     gen_initialize(gl->u.sym);
   }        
   gen_initialize(gl->u.sym);
}

void gen_initialize( struct sym *sy_start ) {
        /*struct sym *sy;*/
        int nb_fields;
        struct init_str init_templ;
/*        Possible optimization:
 *        1) Compress the init sequence to reduce the number
 *           of elementary moves.
 */
        if (sy_start==NULL) 
           return;
     	if (sy_start->flags.external) 
           return;
        
#ifdef DEBUG_COMPILER
        fprintf(o_src,"# INITIALIZE %s, type %c\n",sy_start->name,sy_start->type);
#endif
        init_ctype = ' ';
        nb_fields = get_nb_fields(sy_start, 0);
        if (init_ctype != '&' && init_ctype != ' ') {
                gen_init_str(sy_start, init_ctype, symlen(sy_start));
                return;
        }
#ifdef DEBUG_COMPILER        
        fprintf(o_src,"#  (2) istrp = malloc(%d) nb_fields = %d\n",
                nb_fields * sizeof(init_templ),nb_fields);
#endif
        istrp = malloc(nb_fields * sizeof(init_templ));
        build_init_str(sy_start, nb_fields);
        gen_from_init_str(nb_fields);
        free(istrp);
        istrp=NULL;
#ifdef DEBUG_COMPILER
        fprintf(o_src,"# INITIALIZE (end) %s, type %c\n",sy_start->name,sy_start->type);
#endif
}

/*
 * Cancel statement
 * The parameter is the field or literal containing the name of the routine to cancel
 * if the parameter is NULL, a is a CANCEL ALL
*/
void gen_cancel(struct sym *routine_name)
{
        if (routine_name){
                gen_loadvar( routine_name );
                asm_call("tcob_cancel");
        } else {
                asm_call("tcob_cancel_all");
        }
}

/*
 * GOBACK statement.
 * If is a module generate EXIT PROGRAM, else STOP RUN 
*/
void gen_goback()
{
      if (module_flag) /* If is a module generate EXIT PROGRAM, else STOP RUN */
         gen_exit(1);
      else
         gen_stoprun();
}
void mark_actives( int first, int last ) {
        int i;
        if (last<first) last=first;
        if (first<0 || first>36) first=0;
        if (last<0 || last>36) last=0;
        for (i=first;i<=last;i++) active[i]=1;
}

int sort_exref_compare(const void *z1, const void *z2) {
        char ss1[256], ss2[256];

        strncpy(ss1, var_name( *(struct sym **)z1 ), sizeof(ss1));
        strncpy(ss2, var_name( *(struct sym **)z2 ), sizeof(ss2));
        return strncmp(ss1, ss2, sizeof(ss1));
}

void dump_symbols( ) {
        int i, j, k, arsize, slen;
        struct sym *sy,*sy1,**sytable;
        char t,*s, *str1, sa1[256];
        
        if (!HTG_list_flag)
            return;        

        if (o_lst == NULL)
            return;        
           
        fprintf(o_lst,
"\n=======================================================================");
        fprintf(o_lst,"\n\nSymbols of module: %s (%s)\n", main_entry_buf, pgm_label);
        fprintf(o_lst,    "--------------------------------------\n");
        for (i=0;i<HASHLEN;i++) {
/*            for (sy=labtab[i];sy!=NULL;sy=sy->next) { */
            for (sy=vartab[i];sy!=NULL;sy=sy->next) {
                t=sy->type;
                sy1 = sy;
                while (sy1) {
                        /* check if any variables (excluding intrinsic functions) 
                           are undefined */
                        if( (sy1->defined == 0) && (sy->type == 0) ) 
                        {
                             yyerror("Declared but undefined variable \'%s\' found.", sy1->name);
/*                             fprintf(stderr, "Undefined variable \'%s\', defined=%d, type=%c, line=%d;\n",
                               sy1->name, sy1->defined, sy1->type, sy1->xrefs.lineno[0]); */
                         }
#if 0
                        else {
                             fprintf(stderr, "Defined variable \'%s\', defined=%d, type=%c, line=%d;\n",
                               sy1->name, sy1->defined, sy1->type, sy1->xrefs.lineno[0]);
                        }
#endif
                        sy1=sy1->clone;
                }        
         }
        }

        if (!HTG_list_flag) {
           return;
        }
        if (o_lst == NULL)
           return;        


        /* Determine size of tree */
        for (i=0, j=0;i<HASHLEN;i++) {
            for (sy1=vartab[i];sy1!=NULL;sy1=sy1->next) {
                for (sy=sy1;sy;sy=sy->clone) {
                         if (sy->xrefs.lineno[0] != 0) {
                            j++;
                         }
                     }
            }
        }
        arsize = j;

        /* Allocate sort array  */
        sytable = (struct sym**) malloc( sizeof(struct sym *) * (arsize));

        /* Initialize sort array from hash tree */
        for (i=0, j=0;i<HASHLEN;i++) {
            for (sy1=vartab[i];sy1!=NULL;sy1=sy1->next) {
                     for (sy=sy1;sy;sy=sy->clone) {
                         if (sy->xrefs.lineno[0] != 0) {
                             sytable[j] = sy;
                        str1 = var_name(sytable[j]);
                             j++;
                         }
                     }
            }
        }
        
        /* Sort array using the quick sort function */
        qsort(sytable, arsize, sizeof(struct sym *), sort_exref_compare);

        if (HTG_xref_flag) {

           fprintf(o_lst,"\n---------------------------------------------------- Cross Refrence Listing --------------------------------------------------------\n\n");
           fprintf(o_lst,"Variable Symbol ( Qualifiers )             Locations\n");
           fprintf(o_lst,"-----------------------------------------+------------------------------------------------------------------------------------------\n");
           for (i=0; i<arsize; i++) {
               sy = sytable[i];
               if (sy->xrefs.lineno[0] != 0) {
                   s = var_name(sy);

                   strcpy(sa1, "");
                   j=0;
                   k=0;
                   slen = strlen(s);
                   if (slen > 40) {
                          for (j=0; j<(slen - 40); j = j + k) {
                              str1 = strstr(s+j, " OF ");
                              k = strlen(str1 + 4);
                              k = slen - j - k;
                            strncpy(sa1, s + j, k);
                             sa1[k] = '\0';
                             fprintf(o_lst,"%-40s\n", sa1);
                          }
                          strcpy(sa1, s+j);
                   }
                   else {
                       strcpy(sa1, s);
                   }
                   fprintf(o_lst, "%-40s ", sa1);

                   for (j=0; j<sy->xrefs.pos; j++) {
                       if ((j%8 == 0) && (j>0)) {
                          fprintf(o_lst, "\n%-40s ", "");
                       }
                       fprintf(o_lst, "%06d ", sy->xrefs.lineno[j]);
                   }
                   fprintf(o_lst, "\n");
               }
           }
        }
        
        if (!HTG_list_flag) {
           return;
        }                                 
        if (o_lst == NULL)
           return;        

        fprintf(o_lst,"\n---------------------------------------------------------------+-----------------\n");
        fprintf(o_lst,"Symbol ( Variables )                    Type Level Len Dec Mul | Desc Loc  Pic  S\n");
        fprintf(o_lst,"---------------------------------------------------------------+-----------------\n");
        for (i=0; i<arsize; i++) {
            sy = sytable[i];
              s = var_name(sy);

            strcpy(sa1, "");
            j=0;
            k=0;
            slen = strlen(s);
            if (slen > 40) {
                   for (j=0; j<(slen - 40); j = j + k) {
                          str1 = strstr(s+j, " OF ");
                          k = strlen(str1 + 4);
                          k = slen - j - k;
                        strncpy(sa1, s + j, k);
                         sa1[k] = '\0';
                         fprintf(o_lst,"%-40s\n", sa1);
                   }
                   strcpy(sa1, s+j);
            }
            else {
                strcpy(sa1, s);
            }
         
            fprintf(o_lst,
                        "%-40s%4c%1c%3d %5d %3d %3d%c| %04X %04X%c%04X %1d\n",
                        sa1,
/*                        sy->type, */
                        sy->type ? sy->type : '0', 
                        sy->flags.just_r ? 'R' : ' ',
                        sy->level,
                        sy->len,
                        sy->uval1.decimals,
                        sy->times,
                        sy->occurs_flg ? '*' : ' ',
                        sy->descriptor,
                        sy->uval2.location,
                        sy->linkage_flg ? '*' : ' ',
                        sy->uval5.pic,
                        sy->sec_no );
        }
        fprintf(o_lst, "\n\n");


        fprintf(o_lst,"\n-----------------------------------------------\n");
        fprintf(o_lst,"Symbol ( 88-condition )       Variable tested");
        fprintf(o_lst,"\n-----------------------------------------------\n");
        for (i=0;i<HASHLEN;i++) {
            for (sy=vartab[i];sy!=NULL;sy=sy->next) {
                     t=sy->type;
                     if (t=='8')
                                  fprintf(o_lst,"%22.22s %22.22s\n",
                                     sy->name,
                                     sy->parent->name);
            }
        }

        fprintf(o_lst,
"\n-----------------------------------------------------------------------\n");
        fprintf(o_lst,"%s%s%s",
                "                       Paragraph ",
                "                         Section "," Type");
        fprintf(o_lst,
"\n-----------------------------------------------------------------------\n");
        for (i=0;i<HASHLEN;i++) {
            for (sy=labtab[i];sy!=NULL;sy=sy->next) {
                        t=sy->type;
                        sy1 = sy;
                        while (sy1) {
                                if ((sy1->type == 'P') || (sy1->type == 'S')) {
                                   fprintf(o_lst,"%32.32s %32.32s    %c\n",
                                        (sy1->type == 'P') ? sy1->name : "", 
                                        (sy1->type == 'S') ? sy1->name :
                                                (sy1->parent ? sy1->parent->name : ""),
                                        sy1->type);
                                }
                                sy1=sy1->clone;
                        }        
                }
          }

        fprintf(o_lst,"\n\nTinyCOBOL compile audit summary:\n");
        fprintf(o_lst,"Total lines compiled           : %4d\n",source_lineno);
        fprintf(o_lst,"Total number of warnings       : %4d\n",wrncnt);
        fprintf(o_lst,"Total number of errors found   : %4d\n",errcnt);
          
}

void chg_underline( char *s ) {
        char *s1;
        while ((s1=strchr(s,'-'))!=NULL) *s1='_';
}

void gen_enter_runelement(int type) {
        /* this should be cleaned if we are going to load it */
        fprintf(o_src,"\tmovl\t$s_base%d+0, %%eax\n",pgm_segment);
        push_immed(type);
        push_immed(program_name_literal->len);
        loadloc_to_eax((struct sym *)program_name_literal);    
        push_eax();
        asm_call("tcob_enter_runelement");
}
/* end of HTCOBGEN.C */
