/* 
 *  Copyright (C) 1999 - 2003 David Essex
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
*/ 

%{

#undef yywrap

#include <stdio.h>
#include <assert.h>

#include "cobf2f.h"
 
int i;
unsigned long columnLen;
unsigned long columnCount = 1;
unsigned long lineCount = 1;
char lineout[80];

void lineExpand(void) ;
void tabExpand(void) ;
//void lexError( char * msg ) ;

%}

eol	[\n]
tab	[\t]
blank   [ ]
Quote	['"]
ws	[ \n]

%x INITAL FREE FIXED FIXED_7 FIXED_A FIXED_LC COMMENT 

%%
		if ( globalEnvPtr->format == 0 ) {
		  /* free == 0, fixed == 1 */
		        if (globalEnvPtr->linemul != 0) {
                           fprintf(yyout, "%06d", lineCount*globalEnvPtr->linemul);
		        }
		        else {
		           fprintf(yyout, "      "); 
		        }		
			BEGIN( FREE ) ;}
		else if ( globalEnvPtr->format == 1)
			BEGIN( FIXED ) ;
		else {
			assert(1);
		}
<*>{tab}	{ tabExpand();  }

<FREE>{eol}	{ 
		lineCount++;
		columnCount=0; 
		if (globalEnvPtr->linemul != 0) {
		   fprintf(yyout, "\n%06d", lineCount*globalEnvPtr->linemul); 
		}
		else {
		   fprintf(yyout, "\n      "); 
		}		
}
<FREE>{Quote}{ws}+"&"{ws}+{Quote}  { /*remove for concatination */; }
<FREE>^"*".*$		{ ECHO; /* remove line */ ; }

<FREE>^[^ ]		{ 
			columnCount++;
			  fprintf(stderr,
			    	    "%s:%lu: Invaild character (%c) in"
				    "column 7.\n"
				    ,globalEnvPtr->ifname
				    ,lineCount
				    ,yytext[0]
				);
				/* remove line */  }
<FREE>^"/".*$		{ /* remove line */ ; }
<FREE>^"D".*$		{ 	if ( globalEnvPtr->debug == 1 ) {
					yytext[0]=' ';
					 ECHO;
			   	} /* else remove line */
			}
<FREE>^"$".*$		{ 	fprintf(stderr,
					"%s:%lu: Warning: Directive ignored.\n"
					,globalEnvPtr->ifname
					,lineCount); 
				 globalEnvPtr->errFlag++;
			}	
<FREE>.*		{
                         columnLen = strlen(yytext);
                         /* Ensure that position 7 is blank */
                         if( columnCount == 0 ) {
                           if( yytext[0] != ' ' ) {
                             fprintf(yyout, " ");
                             columnCount++;
                           }
                         }
			 if ( columnLen > 66 ) {
                            lineExpand();
                         }
                         else {
                            columnCount = columnCount + columnLen;  
                            ECHO; 
                         }
}


<FIXED,FIXED_A>{eol}	{ 
			 lineCount++;
			 columnCount=0;
			 ECHO; 
			 BEGIN(FIXED); 
}
<COMMENT>{eol}		{ 
			 lineCount++;
			 columnCount=0; 
			 ECHO; 
			 BEGIN(FIXED); 
}
<COMMENT>.		{ 
			 columnCount++;
			 if ( columnCount > 72 ) {
			     BEGIN(FIXED_LC);
			 }
			 else {
			    ECHO;
			    /*
                            fprintf(stderr, "debug: <COMMENT>: char=%s, columnCount=%d, lineCount=%d\n", 
                                  yytext,
                                  columnCount,
                                  lineCount
                                  );
                            */
			 }
}
<FIXED_LC>.	{ /* eat comments */ /*printf("*")*/ ; }
<FIXED_LC>{eol}		{ 
			ECHO; 
			lineCount++;
			columnCount=0; 
			BEGIN(FIXED); 
}
<FIXED_LC>{eol}.{6}"-"{blank}{4,58}{Quote}	 { 
			/* Continuation line remove */ 
			lineCount++;
			/*columnCount=12;*/
			/* columnCount=0; */ 
		 	columnCount = yyleng - 1; 
			BEGIN(FIXED_A); 
}


<FIXED>^.{6}		{ 
			  /*  remove sequence number */ 
			  columnCount+=6 ; 
			  BEGIN(FIXED_7); 
                          /*
                          fprintf(stderr, "debug: <FIXED>^.{6}: columnCount=%d, lineCount=%d\n", 
                                  columnCount,
                                  lineCount
                                  );
                          */
}
<FIXED_7>"*"	|
<FIXED_7>"/" 	|
<FIXED_7>"$" 		{ 
                         /* comment line remove */ 
                         ECHO; 
			 columnCount++;
                         BEGIN(COMMENT); 
}
	
<FIXED_7>"D" 		{ 
			 columnCount++;
			 if ( globalEnvPtr->debug == 1 ) 
			    BEGIN(FIXED_A);
			 else 
			     BEGIN(COMMENT);
			   
}

<FIXED_7>[\n]		{ BEGIN(FIXED); lineCount++; columnCount=0; ECHO; }
<FIXED_7>[ ]		{ columnCount++; BEGIN(FIXED_A); ECHO; }
<FIXED_7>[^ \n]		{ 
			  globalEnvPtr->errFlag++;
			  fprintf(stderr,
			    	    "%s:%lu: Invaild character (%c) in"
				    "column 7.\n"
				    ,globalEnvPtr->ifname
				    ,lineCount
				    ,yytext[0]
				);
			  BEGIN(COMMENT);
}
	
<FIXED_A>{eol}.{6}"-"{blank}{4,58}{Quote}	 { 
			/* Continuation line remove */ 
			lineCount++;
			/* columnCount=0;  */
		 	columnCount = yyleng - 1; 
			BEGIN(FIXED_A); 
}

<FIXED_A>{Quote}{eol}.{6}"-"{blank}{4,58}{Quote} { 
			/* Continuation line remove */  
			lineCount++;
			/* columnCount=0;  */
		 	columnCount = yyleng - 1; 
			BEGIN(FIXED_A);
}
					
<FIXED,FIXED_A>.	{ 
			 /* any other line */
			 columnCount++;
			 /* don't echo */
			 if ( columnCount > 72 ) {
			    BEGIN(FIXED_LC);
			 }
			 /* }else if ( columnCount > 80 ){ 
			  * lexError( "Record Exceeded 80 cols!"); } 
			  */
			 else {
			    ECHO;
			 }
}	


%%
/*
 * Expand line.
 */
void lineExpand(void) {
  int nlines, j;
  char *s = yytext, delm = '0';
  
  for(j=0; j<columnLen; j++) {
     if( (yytext[j] == '\'') || (yytext[j] == '"') ) {
        delm = yytext[j];
        j = columnLen + 3;
     }
  }
  if(delm == '0') {
    fprintf(stderr, "Error: literal quote/double expected in \'%s\', not found\n", s);
    return;
  }
  strncpy(lineout, s, 66);
  lineout[66] = '\0';
  fprintf(yyout, "%s", lineout);
  columnCount = 66;
  s = yytext + 66;
  nlines = ((columnLen - 66) / 60) + 1;

  for(j=1; j<nlines; j++) {
     sprintf(lineout, "-    %c", delm);
     strncat(lineout, s, 60);
     lineout[66] = '\0';
     s = s + 60;
     columnCount =  columnCount + 66;
     lineCount++;
     if (globalEnvPtr->linemul != 0) {
        fprintf(yyout, "\n%06d%s", lineCount*10, lineout); 
     }
     else {
        fprintf(yyout, "\n      %s", lineout); 
     }		
  }

  if( (j = strlen(s)) > 0) {
    sprintf(lineout, "-    %c", delm);
    strncat(lineout, s, j);
    lineout[6 + j] = '\0';
    lineCount++;
    if (globalEnvPtr->linemul != 0) {
       fprintf(yyout, "\n%06d%s", lineCount*10, lineout); 
    }
    else {
       fprintf(yyout, "\n      %s", lineout); 
    }		
  }
  		    
/*
    fprintf(stderr,
           "%s: Character (%c) in column %d, line %lu.\n",
	    globalEnvPtr->ifname,
	    yytext[0],
            columnCount,
            lineCount);
*/
}

/* print error on tab and stop. */
void tabExpand(void) {
 
        /*
         * Check the warning level settings 
         * output the appropriate message.
         *
         */
/*
        if ( globalEnvPtr->tab2space == 0 ) {
*/
/* now is a tab always an error?? yes? */
/*	(void)fprintf(stderr,
		"%s:%lu: Error tab in column %lu\n"
		,globalEnvPtr->ifname
		, lineCount, columnCount
	);
       globalEnvPtr->errFlag++;
	return;
*/
/*
        }
*/
    globalEnvPtr->errFlag++;
    fprintf(stderr, 
            "error: tabs exapntion is not supported ...aborting\n"
            "Hint: use expand utility to process tabs\n"
            ); 
    return;
 
}

// void lexError( char * msg ) {
// 
// 	(void)fprintf(stderr,
// 		"%s:%lu: %s\n"
// 		,globalEnvPtr->ifname
// 		,lineCount
// 		,msg
// 	);
// 	globalEnvPtr->errFlag++;
// 	return;
// }
 
int yywrap(void) {
 
/* yywrap will be called to open files from the List of Files in the
 * Global Env struct.
 */
	return 1;
}

