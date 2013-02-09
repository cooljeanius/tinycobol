/* 
 *  Copyright (C) 2001, 2000, 1999,  Rildo Pragana, David Essex. 
 *  Copyright (C) 1993, 1991  Rildo Pragana.
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


#define HASHLEN 		100

#define TCOB_KW_TCEXT 		0
#define TCOB_KW_STD 		1
#define TCOB_KW_STD74 		74
#define TCOB_KW_STD85 		85
#define TCOB_KW_STD2 		200
/*
#define TCOB_KW_DIAL_MF 	4
#define TCOB_KW_DIAL_TC 	5
*/
struct reserved_symbol {
        char *name;
        int token;
        unsigned minor;
        unsigned char dialect;
};



struct reserved_sym {
        char *name;
        struct reserved_sym *next;
        int i; /* index on reserved symbol table */
};

struct intrinsic_sym {
        char *name;
        struct intrinsic_sym *next;
        int i; /* index on intrinsic symbol table */
};



void install_reserved (void);
int reserved( char *s );

struct intrinsic_sym *lookup_intrinsic_sym( char *s );

