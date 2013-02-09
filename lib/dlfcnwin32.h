/* 
 * Copyright (C) 2004 David Essex.
 * Copyright (C) 2001, 2000, 1999  Rildo Pragana, Jim Noeth, 
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
 *
 * This source is derived from a post on the MinGW list by Wu Yongwei.
 *
 * Emulates some of the POSIX functions found in "dlfcn.h"
 *

 *
 * TinyCOBOL Run Time Library -- Dynamic library load emulations functions
 *

*/

#ifndef _DLFCN_WIN32_H
#define _DLFCN_WIN32_H
 
#ifdef WIN32_LEAN_AND_MEAN
# include <windows.h>
#else
# define WIN32_LEAN_AND_MEAN
# include <windows.h>
# undef WIN32_LEAN_AND_MEAN
#endif

#include <errno.h>

#define dlopen(P,G) (void*)LoadLibrary(P)
#define dlsym(D,F) (void*)GetProcAddress((HMODULE)(D),(F))
#define dlclose(D) FreeLibrary((HMODULE)(D))
 __inline const char* dlerror()
{
     static char szMsgBuf[256];
     FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
             NULL,
             GetLastError(),
             MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
             szMsgBuf,
             sizeof szMsgBuf,
             NULL);
     return szMsgBuf;
}
 
#endif /* _DLFCN_WIN32_H */
 
