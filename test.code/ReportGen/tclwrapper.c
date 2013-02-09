/*
	Report generator for TinyCobol
	Wrapper for tcl interpreter

	Recife, Brazil, 2001 -- Rildo Pragana
*/

//#define LOAD_TK
#include <tcl.h>

#ifdef LOAD_TK
#include <tk.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define min(x,y) ((x)<(y) ? (x) : (y))

Tcl_Interp *interp;
int error_code;
#ifdef LOAD_TK
	Tk_Window mainwin;
#endif
char script[] = "reportGen.tcl";

void tcl_do_exit() {
	char *einf;
	einf = Tcl_GetVar(interp,"errorInfo",TCL_GLOBAL_ONLY);
	fprintf(stderr,"*** ReportGen ERROR from Tcl interpreter:\n%s\n",einf);
	exit(1);
}

int rep_initiate(char *rep, char *lay) {
	char *r;
	int argc=0;
	char *argv[]= { "tinycobol", ""};
	char *cmdbuf=malloc(200);

	interp = Tcl_CreateInterp();
#ifdef LOAD_TK
	mainwin = Tk_MainWindow(interp);
#endif
	Tcl_AppInit(interp);
	if (Tcl_EvalFile(interp, script) != TCL_OK) {
		r=Tcl_GetStringResult(interp);
		tcl_do_exit();
	}
	strcpy(cmdbuf,"Initiate ");
	strcat(cmdbuf,rep);
	strcat(cmdbuf," ");
	strcat(cmdbuf,lay);
	if (Tcl_Eval(interp,cmdbuf) != TCL_OK) {
		r=Tcl_GetStringResult(interp);
		tcl_do_exit();
	}
	free(cmdbuf);
}

int rep_terminate() {
	char *r;

	if (Tcl_Eval(interp,"Terminate") != TCL_OK) {
		r=Tcl_GetStringResult(interp);
		tcl_do_exit();
	}
	Tcl_DeleteInterp(interp);
}

int rep_generate( char *record, ... ) {
	char *r;
	char *cmdbuf;
	char tmp[20];
	int pointer,i,nargs,reclen;
	char *nbstr,*rlstr;
	va_list args;
	va_start(args,record);

	nbstr = Tcl_GetVar(interp,"nbreaks",TCL_GLOBAL_ONLY);
	Tcl_GetInt(interp,nbstr,&nargs);
	
	rlstr = Tcl_GetVar(interp,"reclength",TCL_GLOBAL_ONLY);
	Tcl_GetInt(interp,rlstr,&reclen);
	
	cmdbuf = malloc(strlen(record)+(nargs+1)*20);
	strcpy(cmdbuf,"Generate \{");
	strncat(cmdbuf,record,reclen);
	strcat(cmdbuf,"}");
	
	for (i=0;i<nargs;i++) {
		pointer = va_arg(args,int);
		sprintf(tmp," 0x%x", pointer);
		strcat(cmdbuf,tmp);
	}
	va_end(args);
	
	if (Tcl_Eval(interp,cmdbuf) != TCL_OK) {
		r=Tcl_GetStringResult(interp);
		tcl_do_exit();
	}
	free(cmdbuf);
}

int set_register( ClientData clientData,
	Tcl_Interp *interp,
	int argc, char *argv[]) {
	int *reg,val;
	
	if (argc != 3) {
		interp->result = "usage: set_register reg_addr value";
		return TCL_ERROR;
	}
	
	if (Tcl_GetInt(interp,argv[1],(int *)&reg) != TCL_OK) {
		return TCL_ERROR;
	}
	if (Tcl_GetInt(interp,argv[2],(int *)&val) != TCL_OK) {
		return TCL_ERROR;
	}
	*reg = val;
	return TCL_OK;
}

int
Tcl_AppInit(Tcl_Interp *interp) {
    if (Tcl_Init(interp) == TCL_ERROR) {
		return TCL_ERROR;
    }
#ifdef LOAD_TK
    if (Tk_Init(interp) == TCL_ERROR) {
		return TCL_ERROR;
    }
	Tcl_StaticPackage(interp, "Tk", Tk_Init, Tk_SafeInit);
    Tcl_SetVar(interp, "tcl_rcFileName", "~/.wishrc", TCL_GLOBAL_ONLY);
#endif
	Tcl_CreateCommand(interp, "set_register", set_register, NULL, NULL);
    return TCL_OK;
}

