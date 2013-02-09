/* 
 * 
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
 * TinyCOBOL Run Time Library -- Dynamic CALL statement functions
 *

*/

/* #define DEBUG_DYNCALL_RTS 1 */

#include "htcoblib.h"
#include "rterrors.h"

#ifndef PATH_MAX 
#define PATH_MAX                        1024
#endif

#define SUBR_HASHLEN                     128
#define HTCOB_PATH_PWD_STR                "."

/* max of 64 chars sub-routine names */
#define HTCOB_DYNLIBS_MAX_NAME		65

#ifdef __MINGW32__
# include "dlfcnwin32.h"
#else
# include <dlfcn.h>
# include <glob.h>
#endif // MINGW32

#ifdef __WINDOWS__
# define HTCOB_DYNLIBS_PATTERN           "*.dll"
# define HTCOB_DYNLIBS_SUFIX             ".dll"
# define HTCOB_PATH_SEP_CHAR                ';'
# define HTCOB_PATH_DELIM_STR                "\\"
#else
# define HTCOB_DYNLIBS_PATTERN           "*.so"
# define HTCOB_DYNLIBS_SUFIX             ".so"
# define HTCOB_PATH_SEP_CHAR                ':'
# define HTCOB_PATH_DELIM_STR                "/"
#endif

/* store sub-routine names */
static char subrname[PATH_MAX]; 
static char subr_libname[PATH_MAX]; 

static struct resolve_handle {
        void *handle;
        struct resolve_handle *next;
} *resolve_handles=NULL;

/* 
   this mini-symtable will register previously called subroutines 
   to speed up resolving their names to pointers 
*/
static struct subr_desc {
        struct subr_desc *next;
        char *name;
        void *(*subr)();
} *subrtab[ SUBR_HASHLEN ]={NULL};

#ifndef __MINGW32__
static char libs_pattern[]=HTCOB_DYNLIBS_PATTERN;
#endif

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          subr_hash                                     |
 |                                                                        |
\*------------------------------------------------------------------------*/

static int subr_hash( char *s ) {
        int val=0, i;
        for (i=0; s[i]!='\0'; i++)
                val += s[i];
        return( val % SUBR_HASHLEN );
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          savename                                      |
 |                                                                        |
\*------------------------------------------------------------------------*/

static char *savename( char *s ) {
        char *ap;
        if ((ap = (char *) tcob_malloc( strlen(s) + 1 )) != NULL)
                strcpy(ap,s);
        return( ap );
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          subr_lookup                                   |
 |                                                                        |
\*------------------------------------------------------------------------*/

static struct subr_desc *subr_lookup( char *s ) {
        struct subr_desc *sd;
        for ( sd = subrtab[ subr_hash(s) ] ; sd != NULL ; sd = sd->next )
                if ( strcmp( s, sd->name ) == 0 )
                        return sd;
        return NULL;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          subr_install                                  |
 |                                                                        |
\*------------------------------------------------------------------------*/

static struct subr_desc *subr_install( char *name,void *(*subr)() ) {
        int val;
        struct subr_desc *sd=subr_lookup(name);
        if (sd == NULL) {
                sd = tcob_malloc( sizeof(struct subr_desc) );
                if (sd==NULL)
                        return NULL;
                if ( (sd->name = savename( name ) )  == NULL )
                        return NULL;
                val = subr_hash( sd->name );
                sd->next = subrtab[ val ];
                sd->subr = subr;
                subrtab[ val ] = sd;
        }
        return sd;
}
/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          subr_uninstall                                |
 |                                                                        |
\*------------------------------------------------------------------------*/

static void subr_uninstall( char *name) {
        struct subr_desc *sd=NULL;
        struct subr_desc *ant=NULL;
	int hash;
	hash = subr_hash(name);
	
        for ( sd = subrtab[ hash ] ; sd != NULL ; sd = sd->next ){
                if ( strcmp( name, sd->name ) == 0 ){
			if (ant == NULL)
		            subrtab[ hash ] = sd->next;
			else
			    ant->next = sd->next;
			if ( sd->name )free(sd->name);
			if ( sd ) free(sd);
			return;
		}
		ant = sd;
	}
}
/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          module_install                                |
 |                                                                        |
\*------------------------------------------------------------------------*/
static void module_install(void *module){

	struct resolve_handle *rh;

        rh = tcob_malloc(sizeof(struct resolve_handle));
     	rh->handle = module;
        rh->next = resolve_handles;

        resolve_handles = rh;

}
/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          module_uninstall                              |
 |                                                                        |
\*------------------------------------------------------------------------*/
static void module_uninstall(void *module){

	struct resolve_handle *rh;
	struct resolve_handle *ant=NULL;
        for (rh=resolve_handles; rh != NULL; rh=rh->next) {
	     	if (rh->handle == module) {
			if(ant)
				ant->next = rh->next;
			else
				resolve_handles = rh->next;
			if ( rh ) free(rh);
			return ;
		}
		ant = rh;
	}	

}
/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          chkmalloc                                     |
 |                                                                        |
\*------------------------------------------------------------------------*/

/*static void * chkmalloc( size_t size ) {

        void *ptr=malloc(size);
        if (ptr == NULL) {
                fprintf(stderr,"*** Fatal error in malloc(%d)\n",size);
        }
        return ptr;
}*/

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                     tcob_resolve_subr_error                            |
 |                                                                        |
\*------------------------------------------------------------------------*/

void tcob_resolve_subr_error(void) {

        fprintf(stderr,"*** RT Error: dynamic library call \"%s\" not found!\n",
                subrname);
}

/*
 *
 * tcob_resolve_in_previous_libs 
 * 
 * Try to resolve a routine handler on previous opened libs
 *
 *
 */
static void *tcob_resolve_in_previous_libs(char *subrname){

        struct resolve_handle *rh;        
        void *(* _dynsubr)()=NULL;

        for (rh=resolve_handles; rh != NULL; rh=rh->next) {

                _dynsubr = dlsym(rh->handle,subrname);
                if (_dynsubr != NULL)  {
                        subr_install(subrname,_dynsubr);
                        return _dynsubr;
                }
        }
	return NULL;

}
/*
 *
 * tcob_cancel_subr
 *
 * Cancel a dynamically loaded module and uninstall it.
 *
 */
void tcob_cancel_subr(char *name){
	struct resolve_handle *rh;
        void *(* _dynsubr)()=NULL;

        for (rh=resolve_handles; rh != NULL; rh=rh->next) {
                _dynsubr = dlsym(rh->handle,subrname);
                if (_dynsubr)  {
	        	dlclose(rh->handle);	
			module_uninstall(rh->handle);
			break;
                }
        }
        subr_uninstall(name);
}
/*
 * tcob_find_in_lib
 *
 * Try to find a library handler on a library name
 *
 */
static void *tcob_find_in_lib(char *rutname,char *libname){

        void *(* _dynsubr)()=NULL;
        void *module;

#ifdef DEBUG_DYNCALL_RTS
        fprintf(stderr, "debug: dyncall : tcob_find_in_lib 2010 : rutname=%s, libname=%s;\n", rutname, libname);
        //fprintf(stderr,"findinf '%s' in '%s'\n",rutname,libname);
#endif                                       
	/* Open the library */
        module = dlopen(libname,RTLD_LAZY);
	
        if (module != NULL) {
#ifdef DEBUG_DYNCALL_RTS
                fprintf(stderr, "debug: dyncall : tcob_find_in_lib 2050 : rutname=%s, libname=%s, subrname=%s;\n", rutname, libname, subrname);
#endif                                       
                _dynsubr = dlsym(module,subrname);
                if (_dynsubr != NULL)  {
#ifdef DEBUG_DYNCALL_RTS
                        fprintf(stderr, "debug: dyncall : tcob_find_in_lib 2080 : rutname=%s, libname=%s, subrname=%s;\n", rutname, libname, subrname);
#endif                                       
                        subr_install(rutname,_dynsubr);
                	// save for speeding up next search 
			module_install(module);
			// return the resolved handler
                        return _dynsubr;
                } 
        	dlclose(module);
#ifdef DEBUG_DYNCALL_RTS
	} 
        else {
               fprintf(stderr, "debug: dyncall : tcob_find_in_lib 2120 : rutname=%s, libname=%s;\n", rutname, libname);
//        	fprintf(stderr,"error '%s' \n",lt_dlerror());
#endif                                       
	}
	return NULL;
}

/*
 * tcob_resolve 
 *
 * Try to resolve the routine name
 * The paths specified by LD_LIBRARY_PATH and TCOB_LD_LIBRARY_PATH
 * 
 */
void *tcob_resolve(char *rutname){

        void *(* _dynsubr)()=NULL;
        char *libs = NULL;
        char *libs1 = NULL, *libstmp=NULL;

#ifndef __MINGW32__	

	char **libname;
        char *ldlib = NULL;
        glob_t g;
        
        //
        // Search calling program and currently linked libraries 
 	//
        _dynsubr = tcob_find_in_lib(subrname, NULL);
#ifdef DEBUG_DYNCALL_RTS
        fprintf(stderr, "debug: dyncall : tcob_resolve 2350 : subrname=%s;\n", subrname);
#endif                                       
	if (_dynsubr) { 
           return _dynsubr;
	}

        //
        // Search loaded shared libraries
        //
        _dynsubr = tcob_resolve_in_previous_libs(subrname);
	if (_dynsubr) { 
           return _dynsubr;
	}
        
        // First find a library named as the routine on all the library path
#ifdef DEBUG_DYNCALL_RTS
        fprintf(stderr, "debug: dyncall : tcob_resolve 2380 : subrname=%s, subrname=%s;\n", subrname, subrname);
#endif                                       
	_dynsubr = tcob_find_in_lib(subrname, subrname);
	if (_dynsubr) { 
		return _dynsubr;
	}
	
	// find rutname.so 
        strcpy(subr_libname,subrname);
        strcat(subr_libname,HTCOB_DYNLIBS_SUFIX);
#ifdef DEBUG_DYNCALL_RTS
        fprintf(stderr, "debug: dyncall : tcob_resolve 2420 : subrname=%s, subr_libname=%s;\n", subrname, subr_libname);
#endif                                       
	_dynsubr = tcob_find_in_lib(subrname,subr_libname);
	if (_dynsubr) { 
		return _dynsubr;
	}
	
	// find ./rutname.so 
        strcpy(subr_libname,".");
        strcat(subr_libname,HTCOB_PATH_DELIM_STR);
        strcat(subr_libname,subrname);
        strcat(subr_libname,HTCOB_DYNLIBS_SUFIX);
#ifdef DEBUG_DYNCALL_RTS
        fprintf(stderr, "debug: dyncall : tcob_resolve 2460 : subrname=%s, subr_libname=%s;\n", subrname, subr_libname);
#endif                                       
	_dynsubr = tcob_find_in_lib(subrname,subr_libname);
	if (_dynsubr) { 
		return _dynsubr;
	}

	// find ./librutname.so 
        strcpy(subr_libname,".");
        strcat(subr_libname,HTCOB_PATH_DELIM_STR);
        strcat(subr_libname,"lib");
        strcat(subr_libname,subrname);
        strcat(subr_libname,HTCOB_DYNLIBS_SUFIX);
#ifdef DEBUG_DYNCALL_RTS
        fprintf(stderr, "debug: dyncall : tcob_resolve 2480 : subrname=%s, subr_libname=%s;\n", subrname, subr_libname);
#endif                                       
	_dynsubr = tcob_find_in_lib(subrname,subr_libname);
	if (_dynsubr) { 
		return _dynsubr;
	}


        // The following functionality is not implimented on MinGW (Win32)

        // Now find the modules on the current dir and on the TC library PATH 
        // setup our libraries names to search (in current directory) 
        g.gl_offs = 0;
        glob(libs_pattern, 0,NULL,&g);
        // add libraries found in TCOB_LD_LIBRARY_PATH
        libs1 = getenv(HTCOB_LD_PATH);
        if (libs1 != NULL) {
                libstmp = tcob_malloc(strlen(libs1)+1);
                strcpy(libstmp,libs1);
                libs1=libstmp;
        }
#ifdef DEBUG_DYNCALL_RTS
        fprintf(stderr, "debug: dyncall : tcob_resolve 2560 : libs=%s;\n", libs);
#endif                                       
        // find all the libraries on the TCOB_LD_LIBRARY_PATH	
        while ((libs=libs1)!=NULL) {
#ifdef DEBUG_DYNCALL_RTS
                fprintf(stderr, "debug: dyncall : tcob_resolve 2580 : libs=%s, libs1=%s;\n", libs, libs1);
#endif                                       
                if ((libs1 = strchr(libs,HTCOB_PATH_SEP_CHAR)) != NULL) {
                        *libs1++ = 0;
                }
                ldlib = tcob_malloc(strlen(libs)+strlen(libs_pattern)+2);
                strcpy(ldlib,libs);
		
                strcat(ldlib,HTCOB_PATH_DELIM_STR);
                strcat(ldlib,libs_pattern);
		
                glob(ldlib, GLOB_APPEND, NULL,&g);
                free(ldlib);
        }

        if (libstmp != NULL)
                free(libstmp);

        // loop until we find a function with the name given 
        libname = g.gl_pathv;
        if (libname != NULL) {
                for ( ; *libname!=NULL; libname++) { 
#ifdef DEBUG_DYNCALL_RTS
                       fprintf(stderr, "debug: dyncall : tcob_resolve 2620 : subrname=%s, *libname=%s;\n", subrname, *libname);
#endif                                       
		       _dynsubr = tcob_find_in_lib(subrname,*libname);
                       if (_dynsubr != NULL)  {
#ifdef DEBUG_DYNCALL_RTS
                               fprintf(stderr, "debug: dyncall : tcob_resolve 2640 : subrname=%s, *libname=%s;\n", subrname, *libname);
#endif                                       
			       return _dynsubr;
		       }		
                }
        }
        globfree(&g);

#else
        
//        DWORD mNameLen;
//        HMODULE mHandle=NULL;
        HANDLE findFileHandle=NULL;
//        LPWIN32_FIND_DATA lpFindFileData=NULL;
        WIN32_FIND_DATA uFindFileData, *lpFindFileData;
        
        lpFindFileData = &uFindFileData;

        // Since the calling program is not a DLL
        // This does not work on Win32
/*
        // 
        // Search the calling program 
        //
#ifdef DEBUG_DYNCALL_RTS
        fprintf(stderr, "debug: dyncall : tcob_resolve 2660 : subrname=%s, subr_libname=%s;\n", subrname, subr_libname);
#endif                                       
        mNameLen = GetModuleFileName (NULL, subr_libname, sizeof (subr_libname));
        if (mNameLen != 0) {
#ifdef DEBUG_DYNCALL_RTS
           fprintf(stderr, "debug: dyncall : tcob_resolve 2720 : subrname=%s, subr_libname=%s;\n", subrname, subr_libname);
#endif                                       
           mHandle = GetModuleHandle(subr_libname);
           if (mHandle != NULL) {
#ifdef DEBUG_DYNCALL_RTS
               fprintf(stderr, "debug: dyncall : tcob_resolve 2740 : subrname=%s, subr_libname=%s;\n", subrname, subr_libname);
#endif                                       
              _dynsubr = dlsym(mHandle, subrname);
              if (_dynsubr != NULL)  {
#ifdef DEBUG_DYNCALL_RTS
                 fprintf(stderr, "debug: dyncall : tcob_resolve 2760 : subrname=%s, subr_libname=%s;\n", subrname, subr_libname);
#endif                                       
                 return _dynsubr;
              }
           }
        }
*/

        //
        // Search loaded DLL's
        //
#ifdef DEBUG_DYNCALL_RTS
        fprintf(stderr, "debug: dyncall : tcob_resolve 2780 : subrname=%s, subr_libname=%s;\n", subrname, subr_libname);
#endif                                       
        _dynsubr = tcob_resolve_in_previous_libs(subrname);
	if (_dynsubr) { 
#ifdef DEBUG_DYNCALL_RTS
           fprintf(stderr, "debug: dyncall : tcob_resolve 2820 : subrname=%s, subr_libname=%s;\n", subrname, subr_libname);
#endif                                       
           return _dynsubr;
	}

        // 
        // Locate and search DLL's in the TCOB_LD_LIBRARY_PATH paths 
        //
        libs1 = getenv(HTCOB_LD_PATH);
        if (libs1 != NULL) {
          libstmp = tcob_malloc(strlen(libs1)+1);
          strcpy(libstmp, libs1);
          libs=libstmp;
#ifdef DEBUG_DYNCALL_RTS
          fprintf(stderr, "debug: dyncall : tcob_resolve 2840 : libs=%s;\n", libs);
#endif                                       
          //
          // Find all DLL's in the TCOB_LD_LIBRARY_PATH	paths
          //
          libs1 = strchr(libs, HTCOB_PATH_SEP_CHAR);
          if (libs1 != NULL) 
             *libs1++ = 0;
          while (libs != NULL) {
             strcpy(subr_libname, libs);
             strcat(subr_libname, HTCOB_PATH_DELIM_STR);
             strcat(subr_libname, HTCOB_DYNLIBS_PATTERN);
#ifdef DEBUG_DYNCALL_RTS
             fprintf(stderr, "debug: dyncall : tcob_resolve 2860 : subrname=%s, subr_libname=%s;\n", subrname, subr_libname);
#endif                                       
             findFileHandle = FindFirstFile(subr_libname, lpFindFileData);
             if (findFileHandle != INVALID_HANDLE_VALUE) {
#ifdef DEBUG_DYNCALL_RTS
                 fprintf(stderr, "debug: dyncall : tcob_resolve 2880 : subrname=%s, subr_libname=%s;\n", subrname, subr_libname);
#endif                                       
                 strcpy(subr_libname, lpFindFileData->cFileName);
#ifdef DEBUG_DYNCALL_RTS
                 fprintf(stderr, "debug: dyncall : tcob_resolve 2920 : subrname=%s, subr_libname=%s;\n", subrname, subr_libname);
#endif                                       
                 _dynsubr = tcob_find_in_lib(subrname, subr_libname);
                 if (_dynsubr) { 
#ifdef DEBUG_DYNCALL_RTS
                    fprintf(stderr, "debug: dyncall : tcob_resolve 2940 : subrname=%s, subr_libname=%s;\n", subrname, subr_libname);
#endif                                       
                    return _dynsubr;
                 }
                 while (FindNextFile(findFileHandle, lpFindFileData) == TRUE) {                      
                   strcpy(subr_libname, lpFindFileData->cFileName);
#ifdef DEBUG_DYNCALL_RTS
                   fprintf(stderr, "debug: dyncall : tcob_resolve 2960 : subrname=%s, subr_libname=%s;\n", subrname, subr_libname);
#endif                                       
                   _dynsubr = tcob_find_in_lib(subrname, subr_libname);
                   if (_dynsubr) { 
#ifdef DEBUG_DYNCALL_RTS
                       fprintf(stderr, "debug: dyncall : tcob_resolve 2960 : subrname=%s, subr_libname=%s;\n", subrname, subr_libname);
#endif                                       
                       return _dynsubr;
                    }
                 }
             }
#ifdef DEBUG_DYNCALL_RTS
             fprintf(stderr, "debug: dyncall : tcob_resolve 2980 : subrname=%s, subr_libname=%s;\n", subrname, subr_libname);
#endif                                       
             libs1 = strchr(libs, HTCOB_PATH_SEP_CHAR);
             if (libs1 != NULL) {
                 *libs1++ = 0;
             }
             libs = libs1;
          }
          free(libstmp);
        }

#endif	
        return NULL;

}
/*------------------------------------------------------------------------*\
 |                                                                        |
 |                         tcob_resolve_subr                              |
 |                                                                        |
\*------------------------------------------------------------------------*/


void *tcob_resolve_subr(struct fld_desc *f, char *s, int stacklen) {
        
	int r=0, i, j, len, trans_len;
        char *p;

        // get our subroutine name to call 
        strncpy(subrname,s,f->len);
        subrname[f->len]=0;

        // remove trailing spaces 
        p = strchr (subrname, ' ');
        if (p)
          *p = '\0';

        // TC supports C, GNU assembler, and COBOL user-defined-words
        // names. 
        // Check for valid characters and substitute for DASH ('-').
        // Valid '[a-zA-Z0-9]_$.-'
        len = strlen(subrname);

#ifdef DEBUG_DYNCALL_RTS
        fprintf(stderr, "debug: dyncall : tcob_resolve 3020 : in-name=%s, len=%d;\n", subrname, len);
#endif                                       

        // Name can NOT begin nor end with a DASH ('-').
        if ((subrname[0] == CHR_DASH) || (subrname[len - 1] == CHR_DASH))  
           {
           r++;
        }
        trans_len = strlen(TCOB_STR_DASH_REDEFINE) - 1;
        for (i=0, j=0; i<len; i++, j++) {
          if ( isalnum(subrname[i]) || 
               (subrname[i] == CHR_DOLLARD_SIGN) ||
               (subrname[i] == CHR_PERIOD) ||
               (subrname[i] == CHR_DASH) ||
               (subrname[i] == CHR_UNDERSCORE) 
             ) 
             {
             // Substitute for DASH ('-').
             if (subrname[i] == CHR_DASH) { 
                strcat(subr_libname, TCOB_STR_DASH_REDEFINE);
                j = j + trans_len;
             }
             else {
                subr_libname[j] = subrname[i];
                subr_libname[j+1] = CHR_EOS;
             }
          }
          else {
            r++;
          }
        }
        if (r != 0) {
           fprintf(stderr, "*** RT Error: Invalid characters in sub-routine name ('%s') found.\n",
                          subrname);
	   return NULL;          
        }
        else {
           strcpy(subrname, subr_libname);
        }

#ifdef __MINGW32__	
        // An non-zero stack length implies an Pascal (WINAPI) call convention 
        if (stacklen != 0) {
           sprintf(subr_libname, "%s@%d", subrname,  stacklen - 1);
           strcpy(subrname, subr_libname);
        }
#endif	

#ifndef __MINGW32__	
        if (strlen(subrname) > HTCOB_DYNLIBS_MAX_NAME) {
           fprintf(stderr,"*** RT Error: Maximun of length of %d characters in sub-routine name ('%s') execced.\n",
                HTCOB_DYNLIBS_MAX_NAME, subrname);
	   return NULL;          
        }
#endif	

#ifdef DEBUG_DYNCALL_RTS
        len = strlen(subrname);
        fprintf(stderr, "debug: dyncall : tcob_resolve 3120 : out-name=%s, len=%d;\n", subrname, len);
#endif                                       

        return tcob_resolve(subrname);
}

int tcob_call_loadlib(struct fld_desc *f, char *s)
{
	int r=0; 
	char *p; 
        void *module;

        strncpy(subr_libname, s, f->len);
        subr_libname[f->len] = '\0';

        // remove traling spaces and add NULL delimiter 
        p = strchr (subr_libname, ' ');
        if (p)
           *p = '\0';

	// open the library
        module = dlopen(subr_libname, RTLD_LAZY);	
        if (module != NULL) {
           // save handle to improve search sequence for next search 
	   module_install(module);
           r = 1;
        }
 
	return r;        
}

/* end of dyncall.c */
