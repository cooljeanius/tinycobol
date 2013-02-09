/* 
 * Copyright (C) 2002,2001, 2000, 1999,  Rildo Pragana, Jim Noeth, 
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
 * TinyCOBOL Run Time Library -- Managing the configuration file functions 
 *

*/

#ifndef _CONFIG_H
#define _CONFIG_H

#ifndef LT_DIRSEP_CHAR
#define LT_DIRSEP_CHAR          '/'
#endif
#ifndef LT_DIRSEP_STR
#define LT_DIRSEP_STR           "/"
#endif

/* Run-time resource (options) file name  */
#define TCB_RTOPTFILE_DEFAULT   "htrtconf"

#include "htcoblib.h"
#include "screenio.h"

#if defined(SunOS)
#include <curses.h>
#else
#  if defined(__CYGWIN__)
#  include <ncurses/ncurses.h>
#  else
#    if defined(__MINGW32__)
#    include <pdcurses.h>
#    else
#    include <curses.h>
#    endif
#  endif
#endif

#include "rterrors.h"
/* define a macro for CTRL modifier on keys */
#ifndef CTRL
#define CTRL(x) ((x) & 0x1f)
#endif
/* PDcurses 2.4 does not have the following defenetion */
#ifndef KEY_CODE_YES
#define KEY_CODE_YES	0x100	/* A wchar_t contains a key code */
#endif

//#define CONFIG_FILENAME "htrtconf"
#define CONFIG_MAXLINE 256
#define TCOBRT_CONFIG_DIR "TCOB_RTCONFIG_PATH"

struct config_item {
    char *key;
    char *value;
    int intvalue;
    struct config_item *next;
};

char *tcob_get_str_config(char *key);
int tcob_get_int_config(char *key);
struct KeyBinding * tcob_get_keybindings();

#endif /* _CONFIG_H */
