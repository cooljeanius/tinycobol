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
 * TinyCOBOL Run Time Library -- BDB Indexed file handling functions
 * 

*/

#ifndef _SORTIO_H_
#define _SORTIO_H_

#define SBDB_FILE_SUFFIX_BDBINDEX    "sdbx"

typedef struct _bdb_sortfile {
  DB   *fdbpx;           /* File : BDB index data  */ 
  char *fdbxname;        /* File name : record data  */ 
} bdb_sortfile;

//int tcob_sort_open(struct file_desc *f, char *record, char *fname);
//int tcob_sort_close(struct file_desc *f, char *record);
int tcob_sort_open(struct file_desc *f, char *fname);
int tcob_sort_close(struct file_desc *f);
int tcob_sort_release(struct file_desc *f, char *record, struct fld_desc *reclen_desc, 
                      char *reclen_buf, char *sd, ...);
int tcob_sort_return(struct file_desc *f, char *record, struct fld_desc *reclen_desc, 
                     char *reclen_buf);
int tcob_sort_using(struct file_desc *f1, char *fname1, ...);
int tcob_sort_giving (struct file_desc *f1, char *fname1, ...);

bdb_sortfile* tcob_allocate_sbdb(char *filename, char *isuffix);
void tcob_free_sbdb(bdb_sortfile *fbdb);

#endif 
