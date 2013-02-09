// 
//  Copyright (C) 1999 - 2003 David Essex
// 
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2, or (at your option)
//  any later version.
//  
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//  
//  You should have received a copy of the GNU General Public License
//  along with this software; see the file COPYING.  If not, write to
//  the Free Software Foundation, Inc., 59 Temple Place, Suite 330,
//  Boston, MA 02111-1307 USA
// 

#ifndef _COBPP_H
#define _COBPP_H

#define MAXLINE 	256
#define PRGNAME		"htcobf2f"

#define COBF2F_VERSION  "0.89.3 (alpha)"
#define COBF2F_NAME	"COBOL format conversion utility version"
#define COBF2F_COPYWR	"Copyright (C) 1999-2003  David Essex"

#define COBF2F_OPT_HELP			'h'
#define COBF2F_OPT_VERSION		'V'
#define COBF2F_OPT_TABS			't'
#define COBF2F_OPT_FLINEMUL		'm'
#define COBF2F_OPT_FIXED_FORMAT		'x'
#define COBF2F_OPT_FREE_FORMAT		'f'	
#define COBF2F_OPT_OUTPUT_FILE		'o'	
#define COBF2F_OPT_INPUT_FILE		'i'	

//#include <stdlib.h>
//#include <stdio.h>

/* command line options */
static char option_list[] = { "hVm:xfi:o:" };

/*      -t <num>      Expand tabs to <num> space(s) (Default = 8)\n\*/
/* Usage list */
/* Usage: htcobf2f  [<options>] [-i input_file ] [-o output_file ]"*/
static char usage_list0[] = { "[<options>] [-i input file ] [-o output file ]\n" };
static char usage_list1[] = { "where <options> are:\n\
      -h            This help screen\n\
      -V            Print out version\n\
      -x            Convert source to X/Open free format (Default)\n\
      -f            Convert source to Standard fixed column format\n\
      -m <num>      Fixed format line number multiplier (Default is blanks)\n\
      -i <filename> Input  filename (Default is standard input)\n\
      -o <filename> Output filename (Default is standard output)\n\
\n\
      Note: Tab expansion not supported (Hint: Use expand utility).\n\
" };

typedef short bool;

struct s_Env {
	bool fixedFormat;
	bool freeFormat;
	bool format; /* 1 is free , 0 is fixed */
	bool debug;
	int  errFlag;
	int  tab2space;
	int  linemul;
	char *progName;
	char *ifname;
	char *ofname;
	};

typedef struct s_Env Env;

Env globalEnv;
Env *globalEnvPtr;

/* lexyy.c */
int yylex(void);
int yywrap(void);

/* cobf2f.c */
int setOptions( Env*, int, char** );
int setDefaults( Env* );
void printVersion( char* );
void printHelp( void );
void CleanUp( void );

#endif
