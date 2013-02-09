/*
 * Copyright (C) 2009        Rildo Pragana, David Essex.
 * Copyright (C) 1999-2004,  Rildo Pragana, Ferran Pegueroles, Jim Noeth,
 *                           Bernard Giroud, David Essex, Andrew Cameron. 
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
 * TinyCOBOL Run Time Library -- BDB headers and defines
 * 

*/

#ifndef _FILEBDB_H_
#define _FILEBDB_H_

#ifndef TCB_BDB_ERROR
#define TCB_BDB_ERROR -1
#endif

/* Set library db headers and version 1.85 compatibility API for versions >= 2.xx */
#ifdef USE_DB
#include <db.h>
#endif

#ifdef USE_DB_1
#include <db1/db.h>
#endif

#ifdef USE_DB_23
#define DB_LIBRARY_COMPATIBILITY_API
#include <db_185.h>
#endif

#ifdef USE_DB_41
#define DB_LIBRARY_COMPATIBILITY_API
#include <db_185.h>
#endif

#ifdef USE_DB_2
#define DB_LIBRARY_COMPATIBILITY_API
#include <db2/db_185.h>
#endif

#ifdef USE_DB_3
#define DB_LIBRARY_COMPATIBILITY_API
#include <db3/db_185.h>
#endif

#ifdef USE_DB_4
#define DB_LIBRARY_COMPATIBILITY_API
#include <db4/db_185.h>
#endif

#ifdef USE_DB_4_1
#define DB_LIBRARY_COMPATIBILITY_API
#include <db4.1/db_185.h>
#endif

#ifdef USE_DB_4_2
#define DB_LIBRARY_COMPATIBILITY_API
#include <db4.2/db_185.h>
#endif

#ifdef USE_DB_4_3
#define DB_LIBRARY_COMPATIBILITY_API
#include <db4.3/db_185.h>
#endif

#ifdef USE_DB_4_4
#define DB_LIBRARY_COMPATIBILITY_API
#include <db4.4/db_185.h>
#endif

#ifdef USE_DB_4_5
#define DB_LIBRARY_COMPATIBILITY_API
#include <db4.5/db_185.h>
#endif

#ifdef USE_DB_4_6
#define DB_LIBRARY_COMPATIBILITY_API
#include <db46/db_185.h>
#endif

#endif 
