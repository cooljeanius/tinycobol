/*
 * Copyright (C) 2007-2010  Rildo Pragana, David Essex.
 * Copyright (C) 1999-2004  Rildo Pragana, Ferran Pegueroles, Jim Noeth,
 *                          Bernard Giroud, David Essex, Andrew Cameron. 
 * Copyright (C) 1993, 1991 Rildo Pragana.
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
 * TinyCOBOL Run Time Library -- Relative file Handling functions
 * 

*/

#ifndef _FILEREL_H_
#define _FILEREL_H_

enum tcb_file_write_rec_mode {
  TCB_FILE_WRITE_REC_NONE,  
  TCB_FILE_WRITE_REC_REPLACE,  
  TCB_FILE_WRITE_REC_APPEND,  
  TCB_FILE_WRITE_REC_EXPAND  
};

enum tcb_file_relative_conditional {
  TCB_FILE_RELATIVE_CONDITIONAL_CURRENT, 
  TCB_FILE_RELATIVE_CONDITIONAL_NEXT,  
  TCB_FILE_RELATIVE_CONDITIONAL_PREVIOUS,  
  TCB_FILE_RELATIVE_CONDITIONAL_EQUAL,
  TCB_FILE_RELATIVE_CONDITIONAL_GT,
  TCB_FILE_RELATIVE_CONDITIONAL_GTEQ,
  TCB_FILE_RELATIVE_CONDITIONAL_LT,
  TCB_FILE_RELATIVE_CONDITIONAL_LTEQ,
  TCB_FILE_RELATIVE_CONDITIONAL_FIRST, 
  TCB_FILE_RELATIVE_CONDITIONAL_LAST
};

enum tcb_file_relative_error_number {
  TCB_FILE_RELATIVE_ENONE,            // No error
  TCB_FILE_RELATIVE_EOF = 101,        // End-Of-File 
  TCB_FILE_RELATIVE_SOF = 102         // Start-Of-File 
};

enum tcb_file_relative_mode {
  TCB_FILE_RELATIVE_MODE,            
  TCB_FILE_RELATIVE_MODE_WRITE_NORMAL = 101,  // Write normal record 
  TCB_FILE_RELATIVE_MODE_WRITE_DUMMY  = 102   // Write dummy (blanck) record  
};

#define TCB_FILE_RELATIVE_POSITION_UNDEFINED   -1

typedef struct _tcb_filerel_handle {
        union {                        // File handle (FILE/fileid-int)  
          int fi;
          FILE *fh;
        } uval;        
        unsigned int mrecidx;          // Number of (indexes) records in file   
        int crecidx;                   // Current record index   
        unsigned int mreclen;          // Full record length - prefix + record   
        tcb_fileio_buffers *buf;       // File IO buffers handle   
        unsigned short precsize;       // Size of record length prefix   
        unsigned short errnum;         // Error code   
} tcb_filerel_handle;


int tcob_open_rel(struct file_desc *f, int mode);
int tcob_close_rel(struct file_desc *f);
/*
int tcob_read_rel(struct file_desc *f, struct fld_desc *rectofrom_desc, char *rectofrom_buf, struct fld_desc *cnt_desc, char *cnt_buf, struct fld_desc *reclen_desc, char *reclen_buf);
int tcob_read_next_rel(struct file_desc *f, struct fld_desc *rectofrom_desc, char *rectofrom_buf, int iflag, struct fld_desc *cnt_desc, char *cnt_buf, struct fld_desc *reclen_desc, char *reclen_buf);
int tcob_write_rel(struct file_desc *f, struct fld_desc *rectofrom_desc, char *rectofrom_buf, struct fld_desc *cnt_desc, char *cnt_buf, struct fld_desc *reclen_desc, char *reclen_buf);
int tcob_rewrite_rel(struct file_desc *f, struct fld_desc *rectofrom_desc, char *rectofrom_buf, struct fld_desc *cnt_desc, char *cnt_buf, struct fld_desc *reclen_desc, char *reclen_buf); 
int tcob_delete_rel(struct file_desc *f, struct fld_desc *cnt_desc, char *cnt_buf);
int tcob_start_rel(struct file_desc *f, int cond, struct fld_desc *cnt_desc, char *cnt_buf); 
*/
int tcob_write_relrec(struct file_desc *f, struct fld_desc *rectofrom_desc, char *rectofrom_buf, int irecidx, int imode, struct fld_desc *reclen_desc, char *reclen_buf);
int tcob_read_relrec(struct file_desc *f, struct fld_desc *rectofrom_desc, char *rectofrom_buf, int irecidx, int imode, struct fld_desc *reclen_desc, char *reclen_buf);

tcb_filerel_handle* tcob_allocate_frel(struct file_desc *f);
void tcob_free_frel(tcb_filerel_handle *h);

#endif 
