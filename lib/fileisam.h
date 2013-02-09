/*
 * Copyright (C) 2009-2010   Rildo Pragana, David Essex.
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
 * TinyCOBOL Run Time Library -- ISAM file handling functions
 * 

*/

#ifndef _FILEISAM_H_
#define _FILEISAM_H_

#include <signal.h>
#include <vbisam.h>

#define TCB_FILE_SUFFIX_DATA        ".dat"
#define TCB_FILE_SUFFIX_INDEX       ".idx"

typedef struct _tcb_fileio_vbidx_handle {
  int  ifilehandle;           /* File handle  */ 
  char *fdatname;             /* File name : record data  */ 
  char *fidxname;             /* File name : index data  */ 
/* unsigned short ckey;        // Current key index - NOT USED */ 
/* unsigned short nkeys;       // Number of keys - NOT USED */ 
  tcb_fileio_buffers *buf;    /* File IO buffers handle  */ 
  struct keydesc *skeydesc;   /* key descriptions */ 
  /* unsigned long srecnum;      // Saved record number */ 
  /* unsigned int skey;          // Saved key index  */ 
} tcb_fileio_vbidx_handle;

/*  Indexed file IO Private functions */

int tcob_open_input_idx(struct file_desc *f); 
int tcob_open_output_idx(struct file_desc *f); 
int tcob_open_io_idx(struct file_desc *f);
int tcob_build_idx(struct file_desc *f); 

int tcob_start_lesscond_idx(struct file_desc *f,
                            int cond, int ikey, struct fld_desc *recfdesc, char *key_ptr);
int tcob_write_rec_idx(struct file_desc *f, struct fld_desc *rectofrom_desc, char *rectofrom_buf,
                       int recpos, 
                       struct fld_desc *reclen_desc, char *reclen_buf); 
int tcob_read_rec_idx(struct file_desc *f, struct fld_desc *rectofrom_desc, char *rectofrom_buf, 
                      long int recpos, 
                      struct fld_desc *reclen_desc, char *reclen_buf); 

tcb_fileio_vbidx_handle* tcob_allocate_vbidx(struct file_desc *f);

void tcob_free_vbidx(struct file_desc *f);

int tcob_build_vbidx(struct file_desc *f); 

int tcob_verify_vbidx(struct file_desc *f, int ifilehandle);

int tcob_eisam2ecob(int enumber);


/* Indexed file IO public functions */
/*
int tcob_read_idx(struct file_desc *f, struct fld_desc *rectofrom_desc, char *rectofrom_buf, 
                  struct fld_desc *reclen_desc, char *reclen_buf, 
                  int ikey, struct fld_desc *fkey, char *keybuf);
int tcob_read_next_idx(struct file_desc *f, struct fld_desc *rectofrom_desc, char *rectofrom_buf, 
                  int nflag, 
                  struct fld_desc *reclen_desc, char *reclen_buf);
int tcob_write_idx(struct file_desc *f, struct fld_desc *rectofrom_desc, char *rectofrom_buf, 
                   struct fld_desc *reclen_desc, char *reclen_buf);
int tcob_rewrite_idx(struct file_desc *f, struct fld_desc *rectofrom_desc, char *rectofrom_buf,
                     struct fld_desc *reclen_desc, char *reclen_buf);
int tcob_start_idx(struct file_desc *f, 
                   int cond, int ikey, struct fld_desc *recfdesc, char *key_ptr);
int tcob_delete_idx(struct file_desc *f);
*/

#endif 
