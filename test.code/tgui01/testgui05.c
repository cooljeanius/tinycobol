/*
	Example embedding a tcl interpreter 
	for GUI enabling a Cobol program.

	Recife, Brazil, 2001 -- Rildo Pragana
*/

#include <tcl.h>
#include <tk.h>
#include <stdio.h>
#include <stdlib.h>

#define min(x,y) ((x)<(y) ? (x) : (y))
/**** general use tcl procs for processing arguments ****/
char cobtools[] = "proc split_fields {} {\n"
	"global data_block cobol_fields result_format\n"
	"set ix 0\nset result_format \"\"\n"
	"foreach {varname size} $cobol_fields {\nglobal $varname\n"
	"set $varname [string range $data_block $ix [expr $ix+$size-1]]\n"
	"incr ix $size\nappend result_format \"%-$size.${size}s\"\n}\n}\n"
	"proc do_exit {} {\nglobal result_format result ready cobol_fields\n"
	"foreach child [winfo children .] {\ndestroy $child\n"
	"}\nset vars {}\nforeach {varname size} $cobol_fields {\n"
	"upvar $varname v\nlappend vars $v\n}\n"
	"set result [eval format $result_format $vars]\nset ready 1\n}";

Tcl_Interp *interp;
int error_code;
Tk_Window mainwin;

int
call_cobol(ClientData *clientData, Tcl_Interp *interp, 
	int argc, char *argv[] ) {

	char buf[81];
	if (argc!=2) {
		Tcl_SetResult(interp, "wrong number of arguments",
			TCL_STATIC);
		return TCL_ERROR;
	}
	memset(buf,' ',80);
	memmove(buf,argv[1],min(strlen(argv[1]),80));
	testgui06(buf);
	return TCL_OK;
}

int initTcl () {
	int argc=0;
	char *argv[]= { "tinycobol", ""};

	interp = Tcl_CreateInterp();
	mainwin = Tk_MainWindow(interp);
	Tcl_AppInit(interp);
	Tcl_CreateCommand(interp, "call_cobol", call_cobol, NULL, NULL);
	Tcl_Eval(interp,cobtools);
}

int endTcl () {
	Tcl_DeleteInterp(interp);
}

/* this function assumes a command buffer of 80 characters */
int exec_tcl(char *cmd, char *result) {
	char cmdbuf[81];
	char *r,*s=cmd;
	/* trim right spaces on the cmd buffer */
	memmove(cmdbuf,cmd,80);
	cmdbuf[80]=0;
	s = cmdbuf+79;
	while ((s >= cmdbuf) && (*s == ' ')) s--;
	if (s >= cmdbuf) 
		*(s+1)=0;
	//printf("Eval: [%s]\n",cmdbuf);
	Tcl_Eval(interp,cmdbuf);
	r=Tcl_GetStringResult(interp);
	memset(result,' ',80);
	memmove(result,r,min(strlen(r),80));
}

int
Tcl_AppInit(Tcl_Interp *interp) {
    if (Tcl_Init(interp) == TCL_ERROR) {
	return TCL_ERROR;
    }
    if (Tk_Init(interp) == TCL_ERROR) {
	return TCL_ERROR;
    }
    Tcl_StaticPackage(interp, "Tk", Tk_Init, Tk_SafeInit);
    Tcl_SetVar(interp, "tcl_rcFileName", "~/.wishrc", TCL_GLOBAL_ONLY);
    return TCL_OK;
}

