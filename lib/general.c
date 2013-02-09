/* 
 * Copyright (C) 2003,  Rildo Pragana, Ferran Pegueroles, Bernard Giroud 
 * Copyright (C) 2001, 2000, 1999,  Rildo Pragana, Jim Noeth, 
 *               Andrew Cameron, David Essex.
 * Copyright (C) 1993, 1991  Rildo Pragana.
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2.1,
 * or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; see the file COPYING.LIB.  If
 * not, write to the Free Software Foundation, Inc., 59 Temple Place,
 * Suite 330, Boston, MA 02111-1307 USA

 *
 * TinyCOBOL Run Time Library -- General functions
 *

*/

#include "htcoblib.h"
#include "rterrors.h"
#include <stdarg.h>
#ifdef __MINGW32__
#include <process.h>
#endif

char* screen_status = NULL;    /* defined here to not force linking to curses */
char* screen_cursor = NULL;    /* defined here to not force linking to curses */

//extern int  bDecimalComma;
//extern char  cCurrencySymbol;

static struct runelement_list *loaded_elements=NULL; /* all the run elements loaded */
static struct runelement_list *process_stack=NULL;   /* the process/routines stack */
static struct runelement_info *running_element=NULL; /* the current run element */

static int catch_cntrlc = 0;
void tcob_catch_cntrlc(int sig_num);
extern void tcob_scr_finish(void);
extern int tcob_close_real(struct file_desc *f); 

/* #define DEBUG_RTS 1 */

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                         setDecimalComma                                |
 |                                                                        |
\*------------------------------------------------------------------------*/
void setDecimalComma(void) 
{
     bDecimalComma = 1;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                         tcob_catch_cntrlc                              |
 | Trap control-c key press and ignore or perform clean exit                        |
\*------------------------------------------------------------------------*/
void tcob_catch_cntrlc(int sig_num)
{
    /* User defined action */
    if(catch_cntrlc == 1) {   
      /* re-set the (Ctrl-C) signal handler */
      signal(SIGINT, tcob_catch_cntrlc);
      /* fprintf(stderr, "Control-C doesn't work\n"); */
      /* fflush(stderr); */
    }
    else {
      /* tcob_scr_finish(); */
      tcob_stop_run();
      /* fprintf(stderr, "TC RTL debug : tcob_catch_cntrlc : control-C pressed\n"); */ 
      fprintf (stderr, "TC run-time warning(s) : Control-C trapped. Abnormal termination of run unit.\n");
      fflush(stderr); 
      exit(1);
    }
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_stop_run                                 |
 |                                                                        |
\*------------------------------------------------------------------------*/
void tcob_stop_run(void) 
{
//static struct runelement_list *loaded_elements=NULL; /* all the run elements loaded */
//static struct runelement_list *process_stack=NULL;   /* the process/routines stack */
//static struct runelement_info *running_element=NULL; /* the current run element */

#ifdef DEBUG_RTS
	fprintf(stderr, "stop run on element '%s'\n",tcob_get_current_runelement()->name);
#endif		
    /* 
      This is required, sometimes a routine opens curses and
      the main program does not close curses 
    */
    tcob_do_scrio_finish();

    if (loaded_elements != NULL) {
	tcob_cancel_all(); /* when stop run, we cancel all the routines */
	tcob_unload_runelement(tcob_get_current_runelement()); /* close the current run element */
    }
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_fldLength                                |
 |                                                                        |
\*------------------------------------------------------------------------*/
unsigned int tcob_fldLength(struct fld_desc *f) 
{
	unsigned int len;
	
	if (f->type == DTYPE_BININT) {
		switch (f->len) {
			case 1: len = 3; break;
			case 2: len = 5; break;
			case 4: len = 10; break;
			default: len = 18; break;
		}
	} else if (f->type == DTYPE_FLOAT)
		len = (f->len == 4) ? 14 : 30;
	else
		len = f->len;
	
	return len;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                           tcob_dup_data                                |
 |                                                                        |
\*------------------------------------------------------------------------*/
char *tcob_dup_data(struct fld_desc *pfldDesc1, char *caData1) 
{
        int len;
        char *caData2;
        
        len = sizeof(char) * (pfldDesc1->len + 1);
        caData2 = (char *)malloc(len);
        if (caData2 != NULL) {
           memset(caData2, 0, len);
           memcpy(caData2, caData1, pfldDesc1->len); 
        }           

        return caData2;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_get_switch                               |
 |                                                                        |
\*------------------------------------------------------------------------*/
int tcob_get_switch(struct fld_desc *f, short *sw, int swnum) 
{
	char sw_name[5];
	char *res;

	sprintf(sw_name, "SW%1d", swnum);
	res = getenv(sw_name);
	*sw = ((res != NULL) && (res[0] == '1')) ? 1 : 0;
#ifdef DEBUG_RTS
	fprintf(stderr, "Getting switch SW%1d, val is %1d\n", swnum, *sw);
#endif	
	return 0;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_set_switch                               |
 |                                                                        |
\*------------------------------------------------------------------------*/
int tcob_set_switch(struct fld_desc *f, short *sw, int swnum) 
{
	int res = 0;
	char *sw_set_cmd;

#ifdef HAVE_PUTENV
#ifndef __MINGW32__
	sw_set_cmd = malloc(7);		/* size of SWnn=b */
	sprintf(sw_set_cmd, "SW%1d=%1d", swnum, *sw);
	res = putenv(sw_set_cmd);
	free(sw_set_cmd);
#endif	
#ifdef DEBUG_RTS
	fprintf(stderr, "Setting switch SW%1d to %1d, res %d\n", swnum, *sw, res);
#endif	
#endif	
	return res;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_chain                                    |
 |                                                                        |
\*------------------------------------------------------------------------*/
void tcob_chain( struct fld_desc *f, char *data ,...) 
{
	char *p;
	unsigned int i;
#ifndef __MINGW32__        
	struct fld_desc *par_des;
	char *par_dat;
	int status=0;
	int files[2];
	va_list ap;
	if (pipe(files)<0) /* create a pipe to pass data to chained program */
	{
	  tcob_rt_error("tcob_chain",TCB_RTERR_GEN_NOPIPE,strerror(errno));
	}
	
	va_start(ap,data);
	par_des=va_arg(ap,struct fld_desc *);
	while(par_des)
	{
	  par_dat=va_arg(ap,char *);
	  status=write(files[1],par_dat,par_des->len); /* write data to pipe */
	  if (status < 0)	  
	  {
	     tcob_rt_error("tcob_chain",TCB_RTERR_GEN_BADDATA,strerror(errno));
	  }
	  par_des=va_arg(ap,struct fld_desc *);
	}
	va_end(ap);

	status=dup2(files[0],100);
	if (status < 0)
           tcob_rt_error("tcob_chain",TCB_RTERR_GEN_BAD_PIPE,strerror(errno));
	close(files[0]);
	close(files[1]);

#endif /* __MINGW32__ */

	for(i=f->len; (i>0) && (data[i-1]==' '); i--)
		; /* intentionally empty */
	p=tcob_malloc(i + 1);
	memcpy(p,data,i);
	p[i]='\0';
	execlp(p,p,NULL);

	/* If we reach this point, the exec has failed */
	tcob_rt_error("tcob_chain",TCB_RTERR_GEN_NOEXEC,strerror(errno)); 
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_chaining                                 |
 |                                                                        |
\*------------------------------------------------------------------------*/
void tcob_chaining( struct fld_desc *f, char *data ,...) 
{
#ifndef __MINGW32__        
	char *p;
        
	struct fld_desc *par_des;
	char *par_dat;

        struct fld_desc *des_list[20];
        char *dat_list[20];
	
	unsigned int i=0, len=0;
	unsigned int num_pars=0;
	int status;
	va_list ap;

	if (f == NULL)
            return;

	des_list[num_pars]=f;
	dat_list[num_pars]=data;
	des_list[num_pars + 1]=NULL;
	dat_list[num_pars + 1]=NULL;
        len += f->len;
        num_pars++;

	va_start(ap,data);
	par_des=va_arg(ap,struct fld_desc *);
	while(par_des)
	{
	  par_dat=va_arg(ap,char *);

	  des_list[num_pars]=par_des;
	  dat_list[num_pars]=par_dat;
	  des_list[num_pars + 1]=NULL;
	  dat_list[num_pars + 1]=NULL;
          len += par_des->len;
          num_pars++;

	  par_des=va_arg(ap,struct fld_desc *);
	}
	va_end(ap);
        p = tcob_malloc(len);

	for(i=0; (status=read(100,p+i,1)>0) && (i<len); i++) ;
	if (status < 0)
	    tcob_rt_error("tcob_chaining",TCB_RTERR_GEN_BAD_ARG,strerror(errno));

	close(100);
        if (i == 0) {
		return;
	} else if( i < len) {
		tcob_rt_error("tcob_chaining",TCB_RTERR_GEN_SIZE_ERR);
        	return; 
	}
	for(i=0; i<num_pars; i++) {
	  memmove(dat_list[i],p,des_list[i]->len);
	  p += des_list[i]->len;
	}
#endif /*__MINGW32__*/
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          run element functions                         |
 |                                                                        |
 | These functions control the data stored on the runtime for each        |
 | program or routine.                                                    |
 |                                                                        |
\*------------------------------------------------------------------------*/
static struct runelement_list* find_in_runelement_list(struct runelement_list *list,
		                                struct runelement_info *element)
{
	if (list == NULL)
		return NULL;
	while( list ) {
		if (list->element == element)
			return list;
		list = list->next;
	}
	return list;
}
		
/*------------------------------------------------------------------------*\
 |                                                                        |
 |                   add_to_runelement_list                               |
 |                                                                        |
\*------------------------------------------------------------------------*/
static struct runelement_list* add_to_runelement_list(struct runelement_list *list,
		                                struct runelement_info *element)
{
	struct runelement_list *new_item;
	struct runelement_list *last_item;
	new_item = (struct runelement_list *)tcob_malloc(sizeof(struct runelement_list)); 
	new_item->element = element;
	new_item->next = NULL;
	
	if (list == NULL){ /* is the first item */
		new_item->prev = NULL;
		return new_item;
	}
	
        /* find the last item */
	last_item = list;
	while (last_item->next) { last_item = last_item->next; }

	last_item->next = new_item;
	new_item->prev = last_item;

	return list;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                    remove_from_runelement_list                         |
 |                                                                        |
\*------------------------------------------------------------------------*/
static struct runelement_list* remove_from_runelement_list(struct runelement_list *list,
		                     struct runelement_info *element)
{	
	struct runelement_list *remove_item=NULL;
	struct runelement_list *prev_item=NULL;
	struct runelement_list *next_item=NULL;

	if (list == NULL)
		return NULL;
	if (element == NULL)
		return list;
        remove_item = list; 
	while(remove_item){
		if(remove_item->element == element) {
			prev_item = remove_item->prev;
			next_item = remove_item->next;
                        if (prev_item) prev_item->next = remove_item->next;
			if (next_item) next_item->prev = remove_item->prev;
			if (remove_item) free(remove_item);
			if ((prev_item == NULL)&&(next_item == NULL))
				return NULL;  /* empty list */
			remove_item = next_item;
		} else {
		        remove_item = remove_item->next;
		}
	}
	return list;
}
#ifdef UNUSED 
static void free_runelement_list(struct runelement_list *list){
	
	struct runelement_list *item = NULL;
	struct runelement_list *item_prev = NULL;
	
	if (list == NULL)
		return;
        item=list;
	/* find the last one */
	while(item->next) item = item->next;
	while(item){
		item_prev = item->prev;
		free(item);
		item = item_prev;
	}
}
#endif

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_get_current_runelement()                 |
 |                                                                        |
 | Return info from the current run element, used by file open to store   |
 | information about open files.                                          |
 |                                                                        |
\*------------------------------------------------------------------------*/
struct runelement_info* tcob_get_current_runelement(void)
{
	return running_element;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_enter_runelement                         |
 |                                                                        |
 | Enter a run element, when a program is called, from anoter program or  |
 | by the shell, and when a program returns from a call statement.        |
 |                                                                        |
\*------------------------------------------------------------------------*/
void tcob_enter_runelement(char *prog_name, int prog_name_len,int type)
{
	char *name = NULL;
	struct runelement_list *actual = NULL;
	struct runelement_info *new_element = NULL;
	struct runelement_list *last_element = NULL;

        /* prepare the name of the run element */
        name = tcob_malloc(prog_name_len + 1);
	memmove(name,prog_name,prog_name_len);
	name[prog_name_len]='\0';
#ifdef DEBUG_RTS
        fprintf(stderr,"Enter run element '%s' ",name);	
#endif
        /* find if we have entered this element before */
        actual = loaded_elements; 
        while(actual != NULL ){
		last_element = actual;
		if (strcmp(actual->element->name,name)==0)
			break;
	        actual = actual->next;
	}
	if ((actual == NULL) && (type == TCB_RUN_ELEMENT_RETURN)){
		tcob_rt_error("tcob_chain",TCB_RTERR_GEN_RUNELEMENT);
	}

	if (actual == NULL) { /* Is the first time is called */
#ifdef DEBUG_RTS
                fprintf(stderr,"for first time\n");	
#endif
		new_element = (struct runelement_info *)tcob_malloc(sizeof(struct runelement_info)); 
		new_element->name = name;
		new_element->screen_status = screen_status;
		new_element->screen_cursor = screen_cursor;
		new_element->decimal_comma = bDecimalComma;
		new_element->currency_symbol = cCurrencySymbol;
        	/*new_element->handler = tcob_resolve_subr(); */
		new_element->files = NULL;

                loaded_elements = add_to_runelement_list(loaded_elements,new_element); 
                actual = find_in_runelement_list(loaded_elements,new_element); 
		if (actual == NULL){
		    tcob_rt_error("tcob_chain",TCB_RTERR_GEN_RUNELEMENT);
		}
	} else {
#ifdef DEBUG_RTS
               fprintf(stderr,"reloading values\n");	
#endif
	       /* restore saved values */
	       screen_status = actual->element->screen_status;
	       screen_cursor = actual->element->screen_cursor;
	       bDecimalComma = actual->element->decimal_comma;
	       cCurrencySymbol = actual->element->currency_symbol;
	}	
	/* update the actual run element. */
	running_element = actual->element;

	if (type == TCB_RUN_ELEMENT_ENTER){
		process_stack = add_to_runelement_list(process_stack,running_element);  
#ifdef DEBUG_RTS
	        fprintf(stderr,"adding to process stack '%s'\n",running_element->name);	
#endif
	} else {
		/* We shold POP from the process stack, but first we
		 * must be sure the previous call has made a push.
		 * If the previous call is not a call to a cobol program,
		 * it hasn't made a push.
		 */
		last_element = process_stack;
		
		while( last_element->next ) last_element = last_element->next;

                /* remove the last one */
		if ( last_element->prev &&
		   ( last_element->prev->element == running_element )) { 
#ifdef DEBUG_RTS
		     fprintf(stderr,"removing from process stack '%s'\n",last_element->element->name);	
#endif
		     last_element->prev->next = NULL;
		     if ( last_element ) free(last_element);
		} else {
		     if ( running_element != last_element->element){ 
                     /* 
                      something stange, mix between cobol programs and
		      non cobol porograms 
                     */
#ifdef DEBUG_RTS
		     fprintf(stderr,"something strange\n");	
#endif
		     } else {  /* last call not a cobol program: do nothing */
#ifdef DEBUG_RTS
		     fprintf(stderr,"last program is not a cobol program\n");	
#endif
		     }
		}     
	}


	return;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_unload_runelement                        |
 |                                                                        |
\*------------------------------------------------------------------------*/
void tcob_unload_runelement(struct runelement_info *element)
{
	struct file_list *files = NULL;
	struct file_list *tmp = NULL;
#ifdef DEBUG_RTS
        fprintf(stderr,"unloading element '%s'\n",element->name);	
#endif
	/* here we should close all files for run element */
	files = element->files; 
	while(files != NULL){
		tcob_close_real(files->file);
		tmp = files;
		files = files->next;
		if ( tmp ) free(tmp);
	}
	element->files = NULL;
	/* remove reference from dynamic calls */
	tcob_cancel_subr(element->name);
	if ( element ) free(element);
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_cancel/tcob_cancel_all                   |
 |                                                                        |
 |  We cancel the specified routine or we cancel all the routines except  |
 |  the routines that are in the execution stack                          |
 |                                                                        |
\*------------------------------------------------------------------------*/
void tcob_cancel(struct fld_desc *f, char *s) 
{
	struct runelement_list *element_to_cancel;
	char *name;
	unsigned int i;
	if ((f ==NULL) || (s == NULL)) { 
		return;
	}

	/* prepare the name of the run element, removing trailing spaces */
	for (i=f->len; (i>0) && (s[i-1]==' '); i--)
		; /* intentionally empty */
	name = tcob_malloc(i + 1);
	memcpy(name,s,i);
	name[i]='\0';

#ifdef DEBUG_RTS
        fprintf(stderr,"Trying to cancel '%s' ",name);	
#endif
        /* find if we have entered this element before */
        element_to_cancel = loaded_elements; 
        while(element_to_cancel != NULL ){
		if (strcmp(element_to_cancel->element->name,name)==0)
			break;
	        element_to_cancel = element_to_cancel->next;
	}

	if (!element_to_cancel){
#ifdef DEBUG_RTS
        	fprintf(stderr,"not found, doing nothing");	
#endif	
		return;	
	} 
        /* find if is on the process stack */
        if (find_in_runelement_list(process_stack,element_to_cancel->element)){
#ifdef DEBUG_RTS
        	fprintf(stderr,"in the process stack, doing nothing");	
#endif	
		return;	
	}
	 
#ifdef DEBUG_RTS
        fprintf(stderr,"found cancelling\n");	
#endif
	tcob_unload_runelement(element_to_cancel->element);
	loaded_elements = remove_from_runelement_list(loaded_elements,element_to_cancel->element);
}
void tcob_cancel_all(){
	struct runelement_list *list;
#ifdef DEBUG_RTS
       	fprintf(stderr,"cancelling all\n");
#endif		
	list = loaded_elements;
	while(list){
                if ( ! find_in_runelement_list(process_stack,list->element)){
			tcob_unload_runelement(list->element);
		}
		list = list->next;
	}
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                   tcob_add_file_list                                   |
 |  Routines to keep a list of the files open for the current run element.|
 |  This files are closed when tcob_stop_run or when the run element      |
 |  is cancelled                                                          |
\*------------------------------------------------------------------------*/
void tcob_add_file_list(struct file_desc *f)
{
	struct runelement_info *current;
	struct file_list *new_item;
	struct file_list *last_item;
	new_item = (struct file_list *) tcob_malloc(sizeof(struct file_list));
	new_item->file = f;
	new_item->next = NULL;
	current = tcob_get_current_runelement();
#ifdef DEBUG_RTS
       	fprintf(stderr,"adding file to run element '%s'\n",current->name);	
#endif	
        if (current->files == NULL){
		current->files = new_item;
	} else {
		last_item = current->files;
		while (last_item->next) last_item = last_item->next;
		last_item->next = new_item;
	}
	return;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                   tcob_remove_file_list                                |
 |  Routines to keep a list of the files open for the current run element.|
 |  This files are closed when tcob_stop_run or when the run element      |
 |  is cancelled                                                          |
\*------------------------------------------------------------------------*/
void tcob_remove_file_list(struct file_desc *f){
	struct runelement_info *current = NULL;
	struct file_list *prev_item = NULL;
	struct file_list *remove_item = NULL;

	current = tcob_get_current_runelement();
#ifdef DEBUG_RTS
       	fprintf(stderr,"removing file from run element '%s'\n",current->name);	
#endif	
        if (current->files == NULL){
		return;
	}
	
        remove_item = current->files;
	/* if is the first in the list */
	if ( remove_item->file == f ) {
		current->files = remove_item->next;
		if ( remove_item ) free(remove_item);
		return;
	}
	while( remove_item && remove_item->file != f){
		prev_item = remove_item;
		remove_item = remove_item->next;
	}
	if ( prev_item && remove_item ) {
		prev_item->next = remove_item->next;
		if ( remove_item ) free(remove_item);
	} else {
		fprintf(stderr,"runtime error");
	/* file not found */
	}
	return;
}
/* End of general.c */
