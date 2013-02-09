/* 
 *  Copyright (C) 2004-2008 David Essex, Rildo Pragana.
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
 *  HTCOBRUN is a program to load and run TinyCOBOL modules (shared-libraries) 
 *
 *  This source is derived from a posting on the OpenCOBOL mailing-list by Roger While.
*/

#include <stdio.h>
#include <getopt.h>

#include "htcoblib.h"
#include "tcrunhelp.h"
#include "tcrunversion.h"

/* #define DEBUG_COBORUN 1 */                   

#define TCOBRUN_CMDOPTION_LIST	"Vh"
#define TCOBRUN_CMDOPT_VERSION   'V'
#define TCOBRUN_CMDOPT_HELP      'h'

#define TCOBRUN_TITLE		"Load and run TinyCOBOL compiled modules"
#define TCOBRUN_COPYWR		"Copyright (C) 2004-2010  David Essex, Rildo Pragana"

/* command line options */
static char option_list[] = { TCOBRUN_CMDOPTION_LIST };


int processCmdLine(int argc, char **argv) {

  int r=0, sw;

  while ((sw = getopt(argc, argv, option_list)) != EOF) {

      switch (sw) {

        /* Display version number */
        case TCOBRUN_CMDOPT_VERSION:
           fprintf(stdout, "%s - %s\n%s\n", TCOBRUN_TITLE, TCOBRUN_PGM_VERSION, TCOBRUN_COPYWR);  
           r = 3;
	break;

        /* Display command line help  */
        case TCOBRUN_CMDOPT_HELP:
        default:
           fprintf(stderr, "Usage: %s %s%s", argv[0], usage_list0, usage_list1);
           r = 5;
	break;
   
      }
  }

  if (r == 0) {
     if (argc < 2) {
        fprintf(stderr, "ERROR: Module parameter not specified\nUsage: %s %s%s", argv[0], usage_list0, usage_list1);
        r = 1;
     }
  }

  return r;
}

int main (int argc, char **argv)
{
  int r=0;
  int (*func)();
  char modname[255];
  struct fld_desc fds;

  r = processCmdLine(argc, argv);
  if (r == 0) {
        tcob_init(argc - 1, &argv[1]);
        strcpy(modname, argv[1]);
        fds.len = strlen(argv[1]);
        func = tcob_resolve_subr(&fds, modname, 0);
        if (func == NULL) {
           fprintf(stderr, "ERROR: Failed to resolve module \'%s\'\n", modname);
           r = 3;
        }
        else {
#ifdef DEBUG_COBORUN
           fprintf(stderr, "htcobrun: debug 333 : \n"); 
#endif
           r = func();
           /* 
            If the function returns then a 'STOP RUN' was not executed,
            and the run-time unit needs to be cleared.
           */
#ifdef DEBUG_COBORUN
           fprintf(stderr, "htcobrun: debug 555 : \n"); 
#endif
           tcob_stop_run();
#ifdef DEBUG_COBORUN
           fprintf(stderr, "htcobrun: debug 777a : \n"); 
#endif
        }
  }
  return r;
}
