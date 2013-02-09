/* 
 *  Copyright (C) 2004 Rildo Pragana, David Essex.
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

#ifndef _WPROG_H
#define _WPROG_H

#if defined(__MINGW32__ )

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <commctrl.h>

#define IDN_DIALOG                     10001
#define IDCH_DIALOG_CAPTION            "TinyCOBOL test using Windows"

#else

#define IDCH_DIALOG_CAPTION            "TinyCOBOL test using GTK+"

#endif /* MinGW */

#define IDCH_DIALOG_MSG                "Run the COBOL sub-program subp01 ?"

#endif 
/* _WPROG_H */

