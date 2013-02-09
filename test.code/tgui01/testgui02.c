/* 
 *  Copyright (C) 2001 Rildo Pragana.
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
 *
 *
    Example embedding a tcl interpreter for GUI enabling a Cobol program.

    Recife, Brazil, 2001 -- Rildo Pragana
*/

#include <tcl.h>
#include <tk.h>
#include <stdio.h>
#include <stdlib.h>

/**** general use tcl procs for processing arguments ****/
char cobtools[] = "set argc 0\nset argv {}\n"
	"proc split_fields {} {\n"
	"global data_block cobol_fields result_format\n"
	"set ix 0\nset result_format \"\"\n"
	"foreach {varname size} $cobol_fields {\nglobal $varname\n"
	"set $varname [string range $data_block $ix [expr $ix+$size-1]]\n"
	"incr ix $size\nappend result_format \"%-$size.${size}s\"\n}\n}\n"
	"proc do_exit {} {\nglobal result_format result ready cobol_fields\n"
	"set vars {}\nforeach {varname size} $cobol_fields {\n"
	"upvar $varname v\nlappend vars $v\n}\n"
	"set result [eval format $result_format $vars]\nset ready 1\n}\n"
	"proc cobol_update {} { }\n";
char wait_ready[]= "split_fields\nset ready 0\ntkwait variable ready";
char newgui[]= "foreach child [winfo children .] {\n"
	"destroy $child\n}";

Tcl_Interp *interp;
int error_code;
Tk_Window mainwin;
int script_sourced=0;

int initTcl () {
	int argc=0;
	char *argv[]= { "tinycobol", ""};

	interp = Tcl_CreateInterp();
	Tcl_AppInit(interp);
	mainwin = Tk_MainWindow(interp);
}

int newGui () {
	script_sourced=0;
	error_code = Tcl_Eval(interp,newgui);
}

int endTcl () {
	Tcl_DeleteInterp(interp);
}

int testgui02(char *data, int *size, char *scriptn) {
	char *r;
	char *cobbuf;
	char script[65],*s;
	cobbuf = malloc(*size+1);
	memmove(cobbuf,data,*size);
	cobbuf[*size]=0;
	memmove(script,scriptn,64);
	s=script;
	while (*s != ' ') s++;
	*s=0;
	//printf("C script: %s received: %s\n",script,cobbuf);
	Tcl_SetVar(interp,"data_block",cobbuf,TCL_GLOBAL_ONLY);
	if (!script_sourced) {
		script_sourced++;
		error_code = Tcl_Eval(interp,cobtools);
		error_code = Tcl_EvalFile(interp, script);
	}
	else {
		Tcl_Eval(interp,"cobol_update");
	}
	Tcl_Eval(interp,wait_ready);
	r=Tcl_GetVar(interp, "result", TCL_GLOBAL_ONLY);
	if (r!=NULL) {
		memmove(data,r,strlen(r));
	}
	free(cobbuf);
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

