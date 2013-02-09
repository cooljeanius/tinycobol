/* 
 * Copyright (C) 2001,2001  David Essex
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

#ifndef MWINDOWS_H
#define MWINDOWS_H

/* Canonicalise Windows and Cygwin recognition macros.  */
#ifdef __CYGWIN32__
#  ifndef __CYGWIN__
#    define __CYGWIN__ __CYGWIN32__
#  endif
#endif
#if defined(_WIN32) || defined(WIN32)
#  ifndef __WINDOWS__
#    ifdef _WIN32
#      define __WINDOWS__ _WIN32
#    else
#      ifdef WIN32
#        define __WINDOWS__ WIN32
#      endif
#    endif
#  endif
#endif

#define DLL_EXPIMP

/* Not required by MinGW
#ifdef _MSC_VER

#if defined(_WIN32)
#if defined(DLL_EXPORTS)
#define DLL_EXPIMP __declspec(dllexport)
//#define DLL_EXPIMP __declspec(dllimport)
#else
#define DLL_EXPIMP __declspec(dllimport)
//#define DLL_EXPIMP __declspec(dllexport)
#endif
#else // Win32 
#define DLL_EXPIMP
#endif

#endif

// #if defined(DLL) && defined(_WIN32)
// #define _DL_IMPORT __delcspec(dllimport)
// #else
// #define _DL_IMPORT
// #endif
// 
// #if 0
// #if !defined(STATIC) && defined(_WIN32)
// #  define _DL_IMPORT __delcspec(dllimport)
// #else
// #  define _DL_IMPORT
// #endif
// #endif
*/

/* LT_DIRSEP_CHAR is accepted *in addition* to '/' as a directory separator when it is set. */
#ifdef __WINDOWS__
#  ifndef __CYGWIN__
#    ifndef _MWINDOWS_H
#      define _MWINDOWS_H

/*  Emulate group other permissions - S_IRGRP S_IROTH */
#      ifndef S_IRGRP
/*#        define S_IRGRP(a) 0 */
#        define S_IRGRP 0
#      endif
#      ifndef S_IROTH
/*#        define S_IROTH(a) 0 */
#        define S_IROTH 0
#      endif


/*  We have strcasecmp and strncasecmp, just under a different name. */
#      define strcasecmp stricmp
#      define strncasecmp strnicmp


#    endif
#  endif
#endif

#endif /* MWINDOWS_H */
