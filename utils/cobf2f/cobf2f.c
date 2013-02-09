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

/*
 *  Program to convert fixed to/from free COBOL format.
 *
 */

//#define GLOBAL_DEF

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
//#include <errno.h>
#include <assert.h>

#include <sys/types.h>
#include <sys/stat.h>

#include "htconfig.h"
#include "cobf2f.h"

#define EXPAND_CMD	COBPP_EXPAND_CMD_PATH" -t "

extern FILE *yyin;
extern FILE *yyout;

/* Global Env struct due to yywrap, yylex */

int main( int ac , char** av ) {

        int  argc=ac, rc = 0;
        char **argv=av; 
        char argtmp[MAXLINE]; 
	char *cmdstr = NULL;

	globalEnvPtr = &globalEnv ;
	rc = setDefaults( &globalEnv );
	if ( rc != 0 ){
		fprintf(stderr,"Error in setDefaults\n");
		return 9;
	}

	rc = setOptions( &globalEnv, argc, argv );
	/* error, or help/version printed */
	if ( rc == 1 ) {
    	   return 1;
	}

	/* print mini help */
	if ( globalEnv.errFlag != 0  ) {
	    printHelp();
	    return 2;
	}
		
	/* everything ok, continue and parse file */

        if (( globalEnv.ifname != NULL ) &&
            ( globalEnv.ofname != NULL )) {
           if ( strcmp(globalEnv.ifname, globalEnv.ofname) == 0 ) {
	   	fprintf(stderr, 
	   	        "Error: input file name \'%s\' is the same as output file name \'%s\'\n",
                        globalEnv.ifname, globalEnv.ofname);
	   	return 8;
           }
        }

        if ( globalEnv.ifname != NULL ) {
           yyin = fopen( globalEnv.ifname, "r");
           if ( yyin == NULL ) {
	   	fprintf(stderr,
	   		"Error: input file \'%s\' not found or not readable\n"
	   		,globalEnv.ifname
	   	);
	
	   	return 8;
	   }
	}
	else {
           yyin = stdin;
	}

        if ( globalEnv.ofname != NULL ) {
           yyout = fopen( globalEnv.ofname, "w");
           if ( yyout == NULL ) {
		fprintf(stderr,
			"Error: open failed for output file \'%s\'\n"
			,globalEnv.ofname
		);
	
		return 9;
	   }
	}
	else {
           yyout = stdout;
	}

	yylex();

	if ( globalEnvPtr->format == 0 ) {
           if ( yyout == stdout ) {
              fprintf(yyout, "\n");
           }
        }

	return rc;
}


/* 
 *  Initalize the Env struct passed to this fucntion 
 */
int setDefaults( Env* gEnv ) {

	gEnv->format      = 0;   /* free == 0, fixed == 1 */
	gEnv->debug       = 0;   /* off  -delete "^D.*" lines */
	gEnv->errFlag     = 0;   /* no error state by default */
	gEnv->tab2space   = 0;   /* expand tabs - not implimented */
	gEnv->linemul     = 0;   /* Fixed format line number multiplier (Default = 10) */ 
	gEnv->progName    = NULL;
	gEnv->ifname      = NULL;
	gEnv->ofname      = NULL;

	return atexit(CleanUp);
};

/*
 *  Function to clean up memory allocated in program.
 * 
 */
void CleanUp( void ) {
	
	Env *gEnv = globalEnvPtr;
	int i;
	void * tempItem;


	globalEnvPtr = NULL;
	if ( gEnv->progName != NULL )
		free(gEnv->progName);

	if ( gEnv->ifname != NULL )
		free( gEnv->ifname );

	if ( gEnv->ofname != NULL )
		free( gEnv->ofname );
	
}

/*
 * Read in command line options and set up the Env struct passed in
 * Alloc memory for program name string in Env struct.
 * 
 */
int setOptions( Env* gEnv, int argc, char** argv ) {
	
	/*  Read in args for option settings. */

	int option, opt, r=0;
	int temp, len;
	char * tempChar;

	/*
         * Check argc for number of args equal to zero 
         *  don't bother to check options, just error out.
         */
	if ( argc < 2 ) {
		gEnv->errFlag++;
	}

	tempChar = strdup( (char*)argv[0] );
	if( tempChar != NULL )
	    gEnv->progName = tempChar;
	else
	    gEnv->progName = PRGNAME;

       opterr = 0;
 
//       while ((opt = getopt (argc, argv, "hvt:xfi:o:")) != EOF) {
       while ((opt = getopt (argc, argv, option_list)) != EOF) {
         
         switch (opt) {

           /* Print version */
	   case COBF2F_OPT_VERSION:
	    printVersion(argv[0]);
	    return 1;
 	    break;
                
	   /* Set tabs expand factor */
	   case COBF2F_OPT_FLINEMUL:	     
	   gEnv->linemul = atoi(optarg);
	   break;
                
// 	   /* Set tabs expand factor */
// 	   case COBF2F_OPT_TABS:	
// 	   if ( gEnv->tab2space != 0 ) {
// 		gEnv->tab2space= atoi(optarg);
// 	   }	  
//  	   break;
                
	   /* Input fixed format */
	   case COBF2F_OPT_FIXED_FORMAT:	
	    gEnv->format = 1; /* free == 0, fixed == 1 */
 	    break;
                
	   /* Input free-format */
	   case COBF2F_OPT_FREE_FORMAT:	
	    gEnv->format = 0; /* free == 0, fixed == 1 */
 	    break;
                
	   /* Output file name */
	   case COBF2F_OPT_INPUT_FILE:	
	    /* Input file name */
            if (gEnv->ifname != NULL) {
               fprintf(stderr, "error: duplicate input file name '%s' ... aborting\n", optarg);
               gEnv->errFlag++;
               r = 20;
               return r;
            }
            len = strlen(optarg);
// 	    fprintf(stderr, "cobf2f debug: optarg=%s: len=%d\n", optarg, len);
            gEnv->ifname = (char*)malloc(len + 2);
            if (gEnv->ifname == NULL) {
               gEnv->errFlag++;
               r = 21;
               return r;
            }
	    strncpy(gEnv->ifname, optarg, len+1);
// 	    fprintf(stderr, "cobf2f debug: input file name :%s:, len=%d\n", gEnv->ifname, len);
 	    break;
                
	   /* Output file name */
	   case COBF2F_OPT_OUTPUT_FILE:	
            if (gEnv->ofname != NULL) {
               fprintf(stderr, "error: duplicate output file name '%s' ... aborting\n", optarg);
               gEnv->errFlag++;
               r = 40;
               return r;
            }
            len = strlen(optarg);
            gEnv->ofname = (char*)malloc(len + 2);
            if (gEnv->ofname == NULL) {
               gEnv->errFlag++;
               r = 41;
               return r;
            }
	    strncpy(gEnv->ofname, optarg, len+1);
// 	    fprintf(stderr, "cobpp debug: output file name '%s', len=%d\n", gEnv->ofname, len);
 	    break;
                
           /* help/default */
	   case COBF2F_OPT_HELP:	
	   default:
//	    printVersion(argv[0]);
	    printHelp();
	    return 1;
	    break;

	 }
       }
	
//    if ( gEnv->ifname == NULL  )
//    {
// 	fprintf(stderr,"%s: No input files\n", gEnv->progName);
// 	gEnv->errFlag++;
//    }
 
   return 0;

}

/* Print out the version and copy information
 * 
 */
void printVersion( char* pname ) {

	fprintf(stdout, "%s %s\n%s\n", 
	                COBF2F_NAME, 
	                COBF2F_VERSION, 
	                COBF2F_COPYWR); 
}

/* 
 *  Print out help 
 *   
 */
void printHelp( void ){

    fprintf (stderr, 
              "Usage: %s %s%s",
              globalEnvPtr->progName,
              usage_list0,
              usage_list1
              );
}

