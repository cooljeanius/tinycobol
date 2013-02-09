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
 * TinyCOBOL Run Time Library -- Relative file handling functions
 * 

*/

#include "htcoblib.h"
#include "fileio.h"
#include "filerel.h"

/*
#define DEBUG_FILEREL_RTS0    1   // OPEN and CLOSE statements  
#define DEBUG_FILEREL_RTS1    1   // READ statements  
#define DEBUG_FILEREL_RTS2    1   // READ NEXT statement        
#define DEBUG_FILEREL_RTS3    1   // WRITE statement           
#define DEBUG_FILEREL_RTS4    1   // REWRITE statement         
#define DEBUG_FILEREL_RTS5    1   // DELETE statement          
#define DEBUG_FILEREL_RTS6    1   // START statement  
#define DEBUG_FILEREL_RTS7    1   // READ rec   
#define DEBUG_FILEREL_RTS8    1   // WRITE rec            
#define DEBUG_FILEREL_RTS9    1   // (de)Allocate relative structures            
*/

//+---------------------------------------------------------------------------------+
// Relative files use a constant record length for both variable and fixed record.                                                      
// The format is defined by a unsigned int32 prefix plus the max record length.                                                      
// The unsigned int32 prefix defines the real length of that record.                                                      
// A real record length of zero indicates that the record is not defined.                                                      
//+---------------------------------------------------------------------------------+

extern void save_status (struct file_desc *f, int status);
extern int tcob_save_status(char *status, int rt);

/*
// 
//  OPEN relative
// 
*/
int tcob_open_rel(struct file_desc *f, int mode) 
{
  int r=0, result;
  int sflags = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH; 
  int oflags = 0;
  tcb_filerel_handle *h;
  struct stat stbuf;

#ifdef DEBUG_FILEREL_RTS0
  fprintf(stderr, "debug : tcob_open_rel : 010.020 : filename=%s;\n", f->filename); 
#endif                                       

  /* Initialize file structure */
  f->open_mode = 0;
  //f->recloc = TCB_FILE_RECORD_LOCATION_ERROR;
  f->flags.read_done = 0;
  f->flags.eof_hit = 0;
  f->flags.file_missing = 0;
  f->flags.init_done = 0;
  f->flags.start_record = 0; 

#ifdef DEBUG_FILEIO_RTS0
  fprintf(stderr, "debug : tcob_open_rel 010.040 : f->flags file_external=%d, eof_hit=%d, file_printer=%d, file_std_flag=%d;\n", 
                        f->flags.file_external, f->flags.eof_hit, f->flags.file_printer, f->file_std_flag);
#endif                                       

  switch (mode) {

    case TCB_FILE_OPEN_MODE_INPUT: 
        oflags = O_RDONLY; 
        break;
    case TCB_FILE_OPEN_MODE_IO: 
        oflags = O_RDWR;
        if (f->flags.optional) 
           oflags = O_CREAT | O_RDWR;
        break;
    case TCB_FILE_OPEN_MODE_OUTPUT: 
        oflags = O_CREAT | O_TRUNC | O_WRONLY; 
        break;
    case TCB_FILE_OPEN_MODE_EXTEND: 
        oflags =  O_RDWR | O_APPEND;
        if (f->flags.optional)
            oflags = O_CREAT | O_RDWR | O_APPEND;
        break;
  }

#if defined(__MINGW32__) || defined(__CYGWIN__)
  oflags |= O_BINARY;
#endif

  h = tcob_allocate_frel(f);
  if (h == NULL) {
     r = 99;
  }
  else {
     h->uval.fi = open(f->filename, oflags, sflags);
     if (h->uval.fi == TCB_FILE_OPEN_ERROR) {
        tcob_free_frel(h);
        if (f->flags.optional && mode == TCB_FILE_OPEN_MODE_INPUT) {
           f->flags.file_missing = 1;
        } 
        else {
           r = 91;
           if (errno == EINVAL) 
              r = 37;
           if (errno == ENOENT) 
              r = 35;
        }
     }
     else {
       h->mrecidx = 0;  
       h->crecidx = 0;
       h->errnum  = TCB_FILE_RELATIVE_SOF;
       
       result = fstat(h->uval.fi, &stbuf);
       if (result == -1) {
          close(h->uval.fi);
          tcob_free_frel(h);
          return (99);
       }
       r = result % h->mreclen;
       if (r != 0) {
          close(h->uval.fi);
          tcob_free_frel(h);
          return (99);
       }
       h->mrecidx = stbuf.st_size / h->mreclen;
       
       if ((f->access_mode == TCB_FILE_ACCESS_MODE_SEQUENTIAL) && 
           (mode == TCB_FILE_OPEN_MODE_EXTEND)
          )
          h->crecidx = h->mrecidx;
     }
  }

#ifdef DEBUG_FILEREL_RTS0
  fprintf(stderr, "debug : tcob_open_rel : 010.220 : h->crecidx=%d, h->mrecidx=%d, r=%d\n", h->crecidx, h->mrecidx, r); 
#endif                                       

  if ((r == 0) && (f->flags.file_missing == 0)) 
     f->dbp = (void*)h;
  else 
    f->dbp = NULL;
 
  /* save mode */
  f->open_mode = mode;
  
  return r;
}

/*
//
//  CLOSE relative
//
*/
int tcob_close_rel(struct file_desc *f) 
{
  int r=0;
  tcb_filerel_handle *h;

#ifdef DEBUG_FILEREL_RTS0
  fprintf(stderr, "debug : tcob_close_rel : 020.020 : r=%d\n", r); 
#endif                                       

  if (f->dbp == NULL)
     return (99);
  
  h = (tcb_filerel_handle *)f->dbp;
  
  close(h->uval.fi);
  tcob_free_frel(h);

  f->dbp = NULL;

#ifdef DEBUG_FILEREL_RTS0
  fprintf(stderr, "debug : tcob_close_rel : 020.140 : r=%d\n", r); 
#endif                                       
  
  return r;
}

/*
//
//  READ relative 
//
*/
int tcob_read_rel(struct file_desc *f, struct fld_desc *rectofrom_desc, char *rectofrom_buf, 
                  struct fld_desc *cnt_desc, char *cnt_buf, 
                  struct fld_desc *reclen_desc, char *reclen_buf) 
{
  int fdbp, recidx, r=0;
  tcb_filerel_handle *h;

  f->flags.read_done = 0;

  /* ERROR check : File is open */
  if (f->dbp == NULL) {
      if (f->flags.optional && f->flags.file_missing) 
         RETURN_STATUS(TCB_STATUS_10_END_OF_FILE);        
      RETURN_STATUS(TCB_STATUS_47_INPUT_DENIED);
  }

  /* Check to see that the record length is valid */
  if (f->reclen == -1)
      RETURN_STATUS(TCB_STATUS_99_UNKNOWN);
  
  /* ERROR check : Must in INPUT or IO mode */
  if (((f->open_mode != TCB_FILE_OPEN_MODE_INPUT) && (f->open_mode != TCB_FILE_OPEN_MODE_IO)))
     RETURN_STATUS(TCB_STATUS_47_INPUT_DENIED);
  
  /* Check that we didn't already hit eof */
  if ((f->open_mode == TCB_FILE_OPEN_MODE_INPUT || f->open_mode == TCB_FILE_OPEN_MODE_IO) && f->flags.eof_hit)
     RETURN_STATUS(TCB_STATUS_46_READ_ERROR);

  h = (tcb_filerel_handle *)f->dbp;
  fdbp = h->uval.fi;
  //record = f->record;

#ifdef DEBUG_FILEREL_RTS1
  fprintf(stderr, "debug : tcob_read_rel : 040.040 : h->crecidx=%d, f->flags.start_record=%d, f->reclen=%d\n", h->crecidx, f->flags.start_record, f->reclen);
#endif

  if ((f->access_mode == TCB_FILE_ACCESS_MODE_SEQUENTIAL) && (h->crecidx == TCB_FILE_RELATIVE_POSITION_UNDEFINED)) 
     return (TCB_STATUS_10_END_OF_FILE);
  
  /* START record read */
  if (f->flags.start_record == 1) {
     f->flags.start_record = 0; 
     r = tcob_read_relrec(f, rectofrom_desc, rectofrom_buf, TCB_FILE_RELATIVE_POSITION_UNDEFINED, TCB_FILE_RELATIVE_CONDITIONAL_CURRENT, reclen_desc, reclen_buf); 
     RETURN_STATUS(r);
  }

#ifdef DEBUG_FILEREL_RTS1
  fprintf(stderr, "debug : tcob_read_rel : 040.060 : f->access_mode=%d\n", f->access_mode);
#endif

  /* SEQUENTIAL read */
  if (f->access_mode == TCB_FILE_ACCESS_MODE_SEQUENTIAL) { 
     r = tcob_read_relrec(f, rectofrom_desc, rectofrom_buf, TCB_FILE_RELATIVE_POSITION_UNDEFINED, TCB_FILE_RELATIVE_CONDITIONAL_NEXT, reclen_desc, reclen_buf); 
     if (r == 0) {
        /* Move relative position to index */
        if (cnt_desc != NULL) {
           recidx = h->crecidx;
           recidx++;
           tcob_move(&_generic_4binary, (char *)&recidx, cnt_desc, cnt_buf);     
        }
     }
     RETURN_STATUS(r);
  }

  /* RANDOM or DYNAMIC  read */
  if (cnt_desc == NULL) 
     RETURN_STATUS(TCB_STATUS_99_UNKNOWN);
  /* Move relative position to index */
  tcob_move(cnt_desc, cnt_buf, &_generic_4binary, (char *)&recidx);     
  recidx--;
  //if ((recidx < 0) || (recidx > h->mrecidx))
  //   RETURN_STATUS(TCB_STATUS_14_OUT_OF_KEY_RANGE);
  r = tcob_read_relrec(f, rectofrom_desc, rectofrom_buf, recidx, TCB_FILE_RELATIVE_CONDITIONAL_EQUAL, reclen_desc, reclen_buf); 

  if (r == 0)
     f->flags.read_done = 1;

#ifdef DEBUG_FILEREL_RTS1
  fprintf(stderr, "debug : tcob_read_rel : 040.080 : r=%d\n", r);
#endif

  RETURN_STATUS(r);
}

/*
//
//  READ NEXT - PREVIOUS relative
//
*/
int tcob_read_next_rel(struct file_desc *f, struct fld_desc *rectofrom_desc, char *rectofrom_buf, 
                       int iflag,
                       struct fld_desc *cnt_desc, char *cnt_buf, 
                       struct fld_desc *reclen_desc, char *reclen_buf) 
{
  int fdbp, recidx, nflag, r=0;
  tcb_filerel_handle *h;
  
  /* ERROR check : File is open */
  if (f->dbp == NULL) {
     if (f->flags.optional && f->flags.file_missing) 
        RETURN_STATUS(TCB_STATUS_10_END_OF_FILE);        
     RETURN_STATUS(TCB_STATUS_47_INPUT_DENIED);
  }
#ifdef DEBUG_FILEREL_RTS2
  fprintf(stderr, "debug : tcob_read_next_rel : 050.020 : f->filename=%s\n", f->filename);
#endif
  
  /* ERROR check : Must in INPUT or IO mode */
  if (((f->open_mode != TCB_FILE_OPEN_MODE_INPUT) && (f->open_mode != TCB_FILE_OPEN_MODE_IO)))
     RETURN_STATUS(TCB_STATUS_47_INPUT_DENIED);
  
  /* Check that we didn't already hit eof */
  if ((f->open_mode == TCB_FILE_OPEN_MODE_INPUT || f->open_mode == TCB_FILE_OPEN_MODE_IO) && f->flags.eof_hit)
     RETURN_STATUS(TCB_STATUS_46_READ_ERROR);

  h = (tcb_filerel_handle *)f->dbp;
  fdbp = h->uval.fi;

#ifdef DEBUG_FILEREL_RTS2
  fprintf(stderr, "debug : tcob_read_next_rel : 050.040 : h->crecidx=%d, f->flags.start_record=%d, f->reclen=%d\n", h->crecidx, f->flags.start_record, f->reclen);
#endif

  /* FIXME : Determine file status code on READ NEXT - PREVIOUS 
             when file position is undefined */
  //if ((f->access_mode == TCB_FILE_ACCESS_MODE_SEQUENTIAL) && (h->crecidx == TCB_FILE_RELATIVE_POSITION_UNDEFINED)) 
  //   return (10);
  //if ((f->access_mode == TCB_FILE_ACCESS_MODE_DYNAMIC) && (h->crecidx == TCB_FILE_RELATIVE_POSITION_UNDEFINED)) 
  //   return (23);
  if (h->crecidx == TCB_FILE_RELATIVE_POSITION_UNDEFINED) 
     RETURN_STATUS(TCB_STATUS_10_END_OF_FILE);

#ifdef DEBUG_FILEREL_RTS2
  fprintf(stderr, "debug : tcob_read_next_rel : 050.060 : f->access_mode=%d\n", f->access_mode);
#endif

  /* Read START or CURRENT record */
  if (f->flags.start_record == 1) {
     nflag = TCB_FILE_RELATIVE_CONDITIONAL_CURRENT;
  }
  else {
  /* Read NEXT - PREVIOUS record */
      if (iflag == TCB_FILE_READ_REC_NEXT) 
         nflag = TCB_FILE_RELATIVE_CONDITIONAL_NEXT;
      else 
         nflag = TCB_FILE_RELATIVE_CONDITIONAL_PREVIOUS;
  }
  r = tcob_read_relrec(f, rectofrom_desc, rectofrom_buf, TCB_FILE_RELATIVE_POSITION_UNDEFINED, nflag, reclen_desc, reclen_buf); 
  if (r == 0) {
     /* Move relative position to index */
     if (cnt_desc != NULL) {
        recidx = h->crecidx;
        recidx++;
        tcob_move(&_generic_4binary, (char *)&recidx, cnt_desc, cnt_buf);     
     }
  }

  f->flags.read_done = 1;
  f->flags.start_record = 0; 

#ifdef DEBUG_FILEREL_RTS2
  fprintf(stderr, "debug : tcob_read_next_rel : 050.080 : r=%d\n", r);
#endif

  RETURN_STATUS(r);
}

/*
//
//  WRITE relative
//
*/
int tcob_write_rel(struct file_desc *f, struct fld_desc *rectofrom_desc, char *rectofrom_buf,                   
                   struct fld_desc *cnt_desc, char *cnt_buf, 
                   struct fld_desc *reclen_desc, char *reclen_buf) 
{
  int fdbp, sreclen, recidx, r=0;
  unsigned int ureclen;
  tcb_filerel_handle *h;
//  char *record;
        
  f->flags.read_done = 0;
  sreclen = sizeof(ureclen);
  
  /* ERROR check : File is open */
  if (f->dbp == NULL)
     RETURN_STATUS(TCB_STATUS_48_OUTPUT_DENIED);
  
#ifdef DEBUG_FILEREL_RTS3
  fprintf(stderr, "debug : tcob_write_rel : 060.020 : f->reclen=%d\n", f->reclen);
#endif

  /* Check to see that the record length is valid */
  if (f->reclen == -1) 
     RETURN_STATUS(TCB_STATUS_99_UNKNOWN);
  
  /* Check the mode the file is opened in to make sure that write is Allowed */
  if (((f->open_mode != TCB_FILE_OPEN_MODE_OUTPUT) && 
       (f->open_mode != TCB_FILE_OPEN_MODE_IO) && 
       (f->open_mode != TCB_FILE_OPEN_MODE_EXTEND)))
     RETURN_STATUS(TCB_STATUS_48_OUTPUT_DENIED);

  /* For IO open mode access mode must be DYNAMIC or RANDOM */
  if ((f->open_mode == TCB_FILE_OPEN_MODE_IO) &&
      (f->access_mode == TCB_FILE_ACCESS_MODE_SEQUENTIAL)) 
     RETURN_STATUS(TCB_STATUS_48_OUTPUT_DENIED);
  
/*
  // DYNAMIC or RANDOM access mode must be opened in IO mode 
  if (((f->access_mode == TCB_FILE_ACCESS_MODE_DYNAMIC) ||
       (f->access_mode == TCB_FILE_ACCESS_MODE_RANDOM)) &&
      (f->open_mode != TCB_FILE_OPEN_MODE_IO)
     ) {
     RETURN_STATUS(TCB_STATUS_48_OUTPUT_DENIED);
  }
*/
  
  h = (tcb_filerel_handle *)f->dbp;
  fdbp = h->uval.fi;

#ifdef DEBUG_FILEREL_RTS3
  fprintf(stderr, "debug : tcob_write_rel : 060.040 : f->access_mode=%d\n", f->access_mode); 
#endif                                    

  /* If no index just write the record at the end of file */
  if (f->access_mode == TCB_FILE_ACCESS_MODE_SEQUENTIAL) {
     
     recidx = h->mrecidx;
#ifdef DEBUG_FILEREL_RTS3
     fprintf(stderr, "debug : tcob_write_rel : 060.060 : recidx=%d\n", recidx); 
#endif                                    

     r = tcob_write_relrec(f, rectofrom_desc, rectofrom_buf, recidx, TCB_FILE_RELATIVE_MODE_WRITE_NORMAL, reclen_desc, reclen_buf); 
#ifdef DEBUG_FILEREL_RTS3
     fprintf(stderr, "debug : tcob_write_rel : 060.080 : recidx=%d, r=%d\n", recidx, r); 
#endif                                    
     if (r == 0) {
        /* Move relative position to index */
        if (cnt_desc != NULL) {
           recidx++;
           tcob_move(&_generic_4binary, (char *)&recidx, cnt_desc, cnt_buf);     
        }
     }
#ifdef DEBUG_FILEREL_RTS3
     fprintf(stderr, "debug : tcob_write_rel : 060.100 : recidx=%d, r=%d\n", recidx, r); 
#endif                                    
    
     RETURN_STATUS(r);
  }

  /* Dynamic uses record key to set file offset - inserts dummy records in between indexes  */
  if ((f->access_mode == TCB_FILE_ACCESS_MODE_DYNAMIC) || (f->access_mode == TCB_FILE_ACCESS_MODE_RANDOM))
  {

     if (cnt_desc == NULL)  
        RETURN_STATUS(TCB_STATUS_99_UNKNOWN);

     /* Determine record index */
     tcob_move(cnt_desc, cnt_buf, &_generic_4binary, (char *)&recidx);     
#ifdef DEBUG_FILEREL_RTS3
     fprintf(stderr, "debug : tcob_write_rel : 060.220 : recidx=%d, r=%d\n", recidx, r); 
#endif                                    
     if (recidx < 1)  
        RETURN_STATUS(21);
     
     recidx--;
     /* Write record at index */
     r = tcob_write_relrec(f, rectofrom_desc, rectofrom_buf, recidx, TCB_FILE_RELATIVE_MODE_WRITE_NORMAL, reclen_desc, reclen_buf); 

#ifdef DEBUG_FILEREL_RTS3
     fprintf(stderr, "debug : tcob_write_rel : 060.260 : recidx=%d, r=%d\n", recidx, r); 
#endif                                    
    
    RETURN_STATUS(r);
  }


  RETURN_STATUS(r);
}

/*
//
//  REWRITE relative
//  
*/
int tcob_rewrite_rel(struct file_desc *f, struct fld_desc *rectofrom_desc, char *rectofrom_buf, 
                     struct fld_desc *cnt_desc, char *cnt_buf, 
                     struct fld_desc *reclen_desc, char *reclen_buf) 
{
  int fdbp, recidx, r;
  tcb_filerel_handle *h;
 // char *record;
        
  /* ERROR check : File is open */
  if (f->dbp == NULL)
      RETURN_STATUS(TCB_STATUS_49_I_O_DENIED);

  /* Check to see that the record length is valid */
  if (f->reclen == -1)
      RETURN_STATUS(TCB_STATUS_99_UNKNOWN);

#ifdef DEBUG_FILEREL_RTS4
  fprintf(stderr, "debug : tcob_rewrite_rel : 070.020 : f->reclen=%d\n", f->reclen);
#endif
  
  /* Check the mode the file is opened in to make sure that rewrite is Allowed */
  if (f->open_mode != TCB_FILE_OPEN_MODE_IO)
     RETURN_STATUS(TCB_STATUS_49_I_O_DENIED);
          
  h = (tcb_filerel_handle *)f->dbp;
  fdbp = h->uval.fi;

  /* FIXME : Add error check for equal record length */
  /* Sequential ACCESS MODE rewrite */
  if (f->access_mode == TCB_FILE_ACCESS_MODE_SEQUENTIAL) {
     if (f->flags.read_done == 0)
        RETURN_STATUS(TCB_STATUS_43_READ_NOT_DONE);
     recidx = h->crecidx;
     /* Rewrite record */
     r = tcob_write_relrec(f, rectofrom_desc, rectofrom_buf, recidx, TCB_FILE_RELATIVE_MODE_WRITE_NORMAL, reclen_desc, reclen_buf); 
  }
  else {
  /* Dynamic or random ACCESS MODE rewrite */
     if (cnt_desc == NULL) 
        RETURN_STATUS(TCB_STATUS_99_UNKNOWN);
     tcob_move(cnt_desc, cnt_buf, &_generic_4binary, (char *)&recidx);     
     recidx--;
     /* Rewrite record */
     r = tcob_write_relrec(f, rectofrom_desc, rectofrom_buf, recidx, TCB_FILE_RELATIVE_MODE_WRITE_NORMAL, reclen_desc, reclen_buf); 
  }

  f->flags.read_done = 0;
  f->flags.start_record = 0;

#ifdef DEBUG_FILEREL_RTS4
  fprintf(stderr, "debug : tcob_rewrite_rel : 070.200 : r=%d\n", r);
#endif              

  RETURN_STATUS(r);  
}

/*
//
//  DELETE relative
//
*/
int tcob_delete_rel(struct file_desc *f, struct fld_desc *cnt_desc, char *cnt_buf) 
{
  int fdbp, r, recidx;
  tcb_filerel_handle *h;
  //char *record;
        
  /* ERROR check : File is open */
  if (f->dbp == NULL)
     RETURN_STATUS(TCB_STATUS_49_I_O_DENIED);

  /* Check to see that the record length is valid */
  if (f->reclen == -1)
     RETURN_STATUS(TCB_STATUS_99_UNKNOWN);

  /*  Verify that the file must be open in I-O mode */
  if (f->open_mode != TCB_FILE_OPEN_MODE_IO)
     RETURN_STATUS(TCB_STATUS_49_I_O_DENIED);
     
  h = (tcb_filerel_handle *)f->dbp;
  fdbp = h->uval.fi;

  /* Sequential ACCESS MODE delete */
  if (f->access_mode == TCB_FILE_ACCESS_MODE_SEQUENTIAL) {
     if (f->flags.read_done == 0)
        RETURN_STATUS(TCB_STATUS_43_READ_NOT_DONE);
     recidx = h->crecidx;
     /* Rewrite with dummy record */
     r = tcob_write_relrec(f, NULL, NULL, recidx, TCB_FILE_RELATIVE_MODE_WRITE_DUMMY, NULL, NULL); 
  }
  else {
     /* Dynamic or random ACCESS MODE delete */
     if (cnt_desc == NULL) 
        RETURN_STATUS(TCB_STATUS_99_UNKNOWN);
     tcob_move(cnt_desc, cnt_buf, &_generic_4binary, (char *)&recidx);     
     recidx--;
     /* Rewrite with dummy record */
     r = tcob_write_relrec(f, NULL, NULL, recidx, TCB_FILE_RELATIVE_MODE_WRITE_DUMMY, NULL, NULL); 
  }
  
  f->flags.read_done = 0;
  f->flags.start_record = 0;

#ifdef DEBUG_FILEREL_RTS5
  fprintf(stderr, "debug : tcob_delete_rel : 080.200 : r=%d\n", r);
#endif              

  RETURN_STATUS(r);  
}

/*
//
//  START relative
//
*/
int tcob_start_rel(struct file_desc *f, int cond, 
                   struct fld_desc *cnt_desc, char *cnt_buf) 
{
  int fdbp, recidx, r;
  tcb_filerel_handle *h;
  //char *record;
                
  f->flags.eof_hit = 0;  
  f->flags.read_done = 0;
  f->flags.start_record = 0;
  
  /* ERROR check : File is open */
  if (f->dbp == NULL) 
     RETURN_STATUS(TCB_STATUS_47_INPUT_DENIED);
   
  /* Check to see that the record length is valid */
  if (f->reclen == -1)
     RETURN_STATUS(TCB_STATUS_99_UNKNOWN);
  
  /* ERROR check : Must in INPUT or IO mode */
  if (((f->open_mode != TCB_FILE_OPEN_MODE_INPUT) && (f->open_mode != TCB_FILE_OPEN_MODE_IO)))
     RETURN_STATUS(TCB_STATUS_47_INPUT_DENIED);

  /* Check for valid relative index */
  if (cnt_desc == NULL)
     RETURN_STATUS(TCB_STATUS_99_UNKNOWN);
  
  h = (tcb_filerel_handle *)f->dbp;
  fdbp = h->uval.fi;

  tcob_move(cnt_desc, cnt_buf, &_generic_4binary, (char *)&recidx); 
  recidx--;    
#ifdef DEBUG_FILEREL_RTS6
  fprintf(stderr, "debug : tcob_start_rel : 090.040: cond=%d, recidx=%d\n", cond, recidx); 
#endif                                       
        
  switch(cond) {
    case TCB_CONDITIONAL_EQUAL: 
         r = tcob_read_relrec(f, NULL, NULL, recidx, TCB_FILE_RELATIVE_CONDITIONAL_EQUAL, NULL, NULL); 
         break;

    case TCB_CONDITIONAL_GT: 
         r = tcob_read_relrec(f, NULL, NULL, recidx, TCB_FILE_RELATIVE_CONDITIONAL_GT, NULL, NULL); 
         break;

    case TCB_CONDITIONAL_GTEQ:
         r = tcob_read_relrec(f, NULL, NULL, recidx, TCB_FILE_RELATIVE_CONDITIONAL_GTEQ, NULL, NULL); 
         break;

    case TCB_CONDITIONAL_LT: 
         r = tcob_read_relrec(f, NULL, NULL, recidx, TCB_FILE_RELATIVE_CONDITIONAL_LT, NULL, NULL); 
         break;

    case TCB_CONDITIONAL_LTEQ: 
         r = tcob_read_relrec(f, NULL, NULL, recidx, TCB_FILE_RELATIVE_CONDITIONAL_LTEQ, NULL, NULL); 
         break;

    default:
         r = 99;
         /* Adjust the current record index */
         h->crecidx = -1;
         break;
  }
  
  if (r == 0) 
     f->flags.start_record = 1;

#ifdef DEBUG_FILEREL_RTS6
  fprintf(stderr, "debug : tcob_start_rel : 090.900 : r=%d\n", r);
#endif              

  RETURN_STATUS(r);
}

/*
//
//  READ record relative
//
*/
int tcob_read_relrec(struct file_desc *f, struct fld_desc *rectofrom_desc, char *rectofrom_buf,
                     int irecidx, int imode,
                     struct fld_desc *reclen_desc, char *reclen_buf) 
{
  int r=0, result, fdbp, recpos, reclen, recidx;
  unsigned int ureclen;
  char *crecord;
  tcb_filerel_handle *h;
  struct stat stbuf;

  h = (tcb_filerel_handle *)f->dbp;
  fdbp = h->uval.fi;

#ifdef DEBUG_FILEREL_RTS7
  fprintf(stderr, "debug : tcob_read_relrec 100.040 : h->crecidx=%d, h->mrecidx=%d, irecidx=%d, imode=%d\n", h->crecidx, h->mrecidx, irecidx, imode); 
#endif     

  /* Set the search index */
  if (irecidx == TCB_FILE_RELATIVE_POSITION_UNDEFINED) {
     /* FIXME : Is this the correct file status  */
     /* Check for valid current index  */
     if (h->crecidx == TCB_FILE_RELATIVE_POSITION_UNDEFINED) 
        return (TCB_STATUS_14_OUT_OF_KEY_RANGE);
     //   return (TCB_STATUS_23_KEY_NOT_EXISTS);

     /* Default is current index */
     recidx = h->crecidx;

     /* Set read to NEXT index */
     if (imode == TCB_FILE_RELATIVE_CONDITIONAL_NEXT) {
        if (h->errnum == TCB_FILE_RELATIVE_SOF)
           h->errnum = 0; 
        else
           recidx++;
     }
          
     /* Set read to PREVIOUS index */
     if (imode == TCB_FILE_RELATIVE_CONDITIONAL_PREVIOUS) { 
        recidx--;
     }
     
     /* Check for EOF conditions */
     if ((recidx < 0) || (recidx >= h->mrecidx)) { 
        h->crecidx = TCB_FILE_RELATIVE_POSITION_UNDEFINED;
        h->errnum  = TCB_FILE_RELATIVE_EOF;
        return (10);
     }  
  }
  else {
     /* Set the search index defined by input */
     recidx = irecidx;

     /* Set index for LT */
     if (imode == TCB_FILE_RELATIVE_CONDITIONAL_LT) 
        recidx--;

     /* Set index for GT */
     if (imode == TCB_FILE_RELATIVE_CONDITIONAL_GT) 
        recidx++;

     /* Check for valid key range  */
     if (((recidx < 0) || (recidx >= h->mrecidx)) && 
         ((imode == TCB_FILE_RELATIVE_CONDITIONAL_GT) ||
          (imode == TCB_FILE_RELATIVE_CONDITIONAL_LT) 
         )
        ) {
        h->crecidx = TCB_FILE_RELATIVE_POSITION_UNDEFINED;
        return (TCB_STATUS_23_KEY_NOT_EXISTS);
     }
  }

  h->errnum = 0; 
  
  /* Check for valid key range  */
  if ((recidx < 0) || (recidx > h->mrecidx)) { 
     h->crecidx = TCB_FILE_RELATIVE_POSITION_UNDEFINED;
     h->errnum = TCB_FILE_RELATIVE_EOF; 
     return (TCB_STATUS_23_KEY_NOT_EXISTS);
  }
  
  /* Set file read position */
  recpos = h->mreclen * recidx;
    
  /* Get the file information */
  result = fstat(fdbp, &stbuf);
  if (result == -1) 
     return (TCB_STATUS_99_UNKNOWN);

  if (stbuf.st_size < recpos) {
     h->crecidx = TCB_FILE_RELATIVE_POSITION_UNDEFINED;
     return (TCB_STATUS_21_KEY_INVALID);
  }
    
  result = lseek(fdbp, recpos, SEEK_SET);
#ifdef DEBUG_FILEREL_RTS7
  fprintf(stderr, "debug : tcob_read_relrec 100.080 : result=%d, recpos=%d\n", result, recpos); 
#endif     
  if (result == -1) 
     return (TCB_STATUS_99_UNKNOWN);
    
  crecord = h->buf->buf[1];
  memset(crecord, ' ', h->mreclen);

  /* Read record - max length */
  result = read(fdbp, crecord, h->mreclen);
  if (result != h->mreclen) {
     h->crecidx = TCB_FILE_RELATIVE_POSITION_UNDEFINED;
     if ((result == -1) || (result > h->mreclen))
        return (TCB_STATUS_99_UNKNOWN);
     if (result == 0)
        return (TCB_STATUS_10_END_OF_FILE);
  }
  
#ifdef DEBUG_FILEREL_RTS7
  fprintf(stderr, "debug : tcob_read_relrec 100.100 : result=%d, h->mreclen=%d\n", result, h->mreclen);
#endif                 

  /* Determine record length */                  
  memcpy(&ureclen, crecord, h->precsize);

#ifdef DEBUG_FILEREL_RTS7
  fprintf(stderr, "debug : tcob_read_relrec 100.120 : recidx=%d, ureclen=%d\n", recidx, ureclen);
  if (ureclen > 0) {
    int i, ilen=ureclen;
    char *pt = crecord + h->precsize;
    fprintf(stderr, "debug : tcob_read_relrec 100.125 : record=");
    for (i=0; i<ilen; i++) {      
      fprintf(stderr, "%c", *(pt + i));
    }
    fprintf(stderr, ";\n");
  }
#endif                 

  /* Key does not exist */                  
  if ((ureclen == 0) &&
      ((imode == TCB_FILE_RELATIVE_CONDITIONAL_CURRENT) || 
       (imode == TCB_FILE_RELATIVE_CONDITIONAL_EQUAL)
      )
     ) {
     h->crecidx = TCB_FILE_RELATIVE_POSITION_UNDEFINED;
     return (TCB_STATUS_23_KEY_NOT_EXISTS);
  }
  /* If record length is zero (dummy record) */                  
  if (ureclen == 0) {

     /* Scan forward until EOF or record length is NOT zero */                  
     if ((imode == TCB_FILE_RELATIVE_CONDITIONAL_NEXT) ||
         (imode == TCB_FILE_RELATIVE_CONDITIONAL_GTEQ) ||
         (imode == TCB_FILE_RELATIVE_CONDITIONAL_GT) 
        ) {
        recidx++;
        result = 99;
        while ((recidx >= 0) && (recidx <= h->mrecidx)) {       
           result = read(fdbp, crecord, h->mreclen);
           if (result != h->mreclen) 
              return (99);
           /* Determine record length */                  
           memcpy(&ureclen, crecord, h->precsize);
#ifdef DEBUG_FILEREL_RTS7
  fprintf(stderr, "debug : tcob_read_relrec 100.140 : recidx=%d, ureclen=%d\n", recidx, ureclen);
  if (ureclen > 0) {
    int i, ilen=ureclen;
    char *pt = crecord + h->precsize;
    fprintf(stderr, "debug : tcob_read_relrec 100.145 : record=");
    for (i=0; i<ilen; i++) {      
      fprintf(stderr, "%c", *(pt + i));
    }
    fprintf(stderr, ";\n");
  }
#endif                 
           if (ureclen != 0) {
              result = 0;
              break;
           }
           recidx++;
        }
        if (result != 0) {
           h->crecidx = TCB_FILE_RELATIVE_POSITION_UNDEFINED;
           return (TCB_STATUS_10_END_OF_FILE);
        }
     }
  
     /* Scan backwards until EOF or record length is NOT zero */                  
     if ((imode == TCB_FILE_RELATIVE_CONDITIONAL_PREVIOUS) ||
         (imode == TCB_FILE_RELATIVE_CONDITIONAL_LTEQ) ||
         (imode == TCB_FILE_RELATIVE_CONDITIONAL_LT) 
        ) {
        recidx--;
        result = 99;
        while ((recidx >= 0) && (recidx <= h->mrecidx)) {       
           /* Set file read position */
           recpos = h->mreclen * recidx;
           result = lseek(fdbp, recpos, SEEK_SET);
           /* Read record - max length */
           result = read(fdbp, crecord, h->mreclen);
           if (result != h->mreclen) 
              return (TCB_STATUS_99_UNKNOWN);
           /* Determine record length */                  
           memcpy(&ureclen, crecord, h->precsize);
#ifdef DEBUG_FILEREL_RTS7
  fprintf(stderr, "debug : tcob_read_relrec 100.160 : recidx=%d, ureclen=%d\n", recidx, ureclen);
  if (ureclen > 0) {
    int i, ilen=ureclen;
    char *pt = crecord + h->precsize;
    fprintf(stderr, "debug : tcob_read_relrec 100.165 : record=");
    for (i=0; i<ilen; i++) {      
      fprintf(stderr, "%c", *(pt + i));
    }
    fprintf(stderr, ";\n");
  }
#endif                 
           if (ureclen != 0) {
              result = 0;
              break;
           }
           recidx--;
        }
        if (result != 0) {
           h->crecidx = TCB_FILE_RELATIVE_POSITION_UNDEFINED;
           return (TCB_STATUS_10_END_OF_FILE);
        }
     }

  }

  /* Variable length record */                  
  if (reclen_desc != NULL) {
     reclen = ureclen;
     tcob_move(&_generic_4binary, (char *)&reclen, reclen_desc, reclen_buf);     
  }
  else {
     reclen = f->reclen;
  }

  /* Clear buffer and move data record  */
  memset(f->record, ' ', f->reclen);
  memcpy(f->record, crecord + h->precsize, reclen);
  /* Copy buffer data to INTO identifiers buffer */
  if (rectofrom_desc != NULL) {
     memset(rectofrom_buf, ' ', rectofrom_desc->len);
     if (rectofrom_desc->len > reclen) 
        memcpy(rectofrom_buf, f->record, reclen);
     else
        memcpy(rectofrom_buf, f->record, rectofrom_desc->len);
  }

  /* Adjust the current record index */
  h->crecidx = recidx;

#ifdef DEBUG_FILEREL_RTS7
  fprintf(stderr, "debug : tcob_read_relrec 100.240 : h->creclen=%d, r=%d\n", h->crecidx, r);
#endif                 

  return (r);
}

/*
//
//  WRITE record relative
//
*/
int tcob_write_relrec(struct file_desc *f, 
                      struct fld_desc *rectofrom_desc, char *rectofrom_buf, 
                      int irecidx, int imode, 
                      struct fld_desc *reclen_desc, char *reclen_buf) 
{
  int r=0, result, fdbp, recpos, reclen;
  unsigned int ureclen;
  char *crecord;
  tcb_filerel_handle *h;
  struct stat stbuf;

  h = (tcb_filerel_handle *)f->dbp;
  fdbp = h->uval.fi;

#ifdef DEBUG_FILEREL_RTS8
  fprintf(stderr, "debug : tcob_write_relrec 110.020 : h->crecidx=%d, h->mrecidx=%d, irecidx=%d\n", h->crecidx, h->mrecidx, irecidx); 
#endif     

  if (irecidx < 0) 
     return (TCB_STATUS_99_UNKNOWN);

  result = fstat(fdbp, &stbuf);
  if (result == -1) 
     return (TCB_STATUS_99_UNKNOWN);

  /* Get the location based on record index and full record length */
  if (irecidx > h->mrecidx) 
     recpos = h->mreclen * h->mrecidx;
  else
     recpos = h->mreclen * irecidx;

#ifdef DEBUG_FILEREL_RTS8
  fprintf(stderr, "debug : tcob_write_relrec 110.040 : recpos=%d;\n", recpos); 
#endif     
  
  result = lseek(fdbp, recpos, SEEK_SET);
#ifdef DEBUG_FILEREL_RTS8
  fprintf(stderr, "debug : tcob_write_relrec 110.060 : result=%d, recpos=%d;\n", result, recpos); 
#endif     
  if (result == -1) 
     return (TCB_STATUS_99_UNKNOWN);
  
  /* Clear buffer */
  crecord = h->buf->buf[1];
  memset(crecord, ' ', h->mreclen);

  /* If index is greater than max index insert dummy records */
  if (irecidx > h->mrecidx) {
     int i;
     ureclen = 0;
     memcpy(crecord, &ureclen, h->precsize);
     /* Write dummy records */
     for (i=h->mrecidx; i < irecidx; i++) {
        /* Write the max record including length prefix */
        result = write(fdbp, crecord, h->mreclen);        
#ifdef DEBUG_FILEREL_RTS8
        fprintf(stderr, "debug : tcob_write_relrec 110.080 : idx=%d, result=%d\n", i, result); 
#endif                                    
        if (result == -1) 
           return (TCB_STATUS_99_UNKNOWN);
        /* Adjust the record indexes */
        h->mrecidx++;
     }
  }

  /* Write record at index */
  /* Dummy record (zero length record) */                  
  if (imode == TCB_FILE_RELATIVE_MODE_WRITE_DUMMY) {
     ureclen = 0;
  }
  else {
     /* Variable length record */                  
     if (reclen_desc != NULL) {
         /* Convert record length to integer */
         tcob_move(reclen_desc, reclen_buf, &_generic_4binary, (char *)&reclen);     
         if (reclen > f->reclen)
            return (TCB_STATUS_30_PERMANENT_ERROR);
         ureclen = reclen;
     }
     else {
       /* Fixed record  */                  
       ureclen = f->reclen;        
     }
  }

  /* If it is not a dummy record copy record                   
     Copy write buffer data to record and FROM identifiers buffer */
  if ((rectofrom_desc != NULL) && (ureclen != 0)) {
     memset(f->record, ' ', f->reclen);
     if (rectofrom_desc->len > f->reclen) 
        memcpy(f->record, rectofrom_buf, f->reclen);
     else
        memcpy(f->record, rectofrom_buf, rectofrom_desc->len);
  }

  memcpy(crecord, &ureclen, h->precsize);
  /* If it is not a dummy record copy record */                  
  if (ureclen != 0)
     memcpy(crecord + h->precsize, f->record, ureclen);

#ifdef DEBUG_FILEREL_RTS8
  fprintf(stderr, "debug : tcob_write_relrec 110.120 : ureclen=%d, h->precsize=%d\n", ureclen, h->precsize); 
  if (ureclen > 0) {
    int i, ilen=ureclen;
    fprintf(stderr, "debug : tcob_write_relrec 110.125 : record=");
    for (i=0; i<ilen; i++) {      
      fprintf(stderr, "%c", *(record + i));
    }
    fprintf(stderr, ";\n");
  }
#endif     

  /* Write the max record including length prefix */
  result = write(fdbp, crecord, h->mreclen);        
#ifdef DEBUG_FILEREL_RTS8
  fprintf(stderr, "debug : tcob_write_relrec 110.160 : result=%d, h->mreclen=%d\n", result, h->mreclen); 
#endif     
  if (result > h->mreclen)
     return (TCB_STATUS_99_UNKNOWN);
  if (result == 0)
     return (TCB_STATUS_10_END_OF_FILE);
  if (result != h->mreclen)
     return (TCB_STATUS_30_PERMANENT_ERROR);

  /* Adjust the record indexes */
  if (irecidx >= h->mrecidx) 
     h->mrecidx++;

  result = fstat(h->uval.fi, &stbuf);
#ifdef DEBUG_FILEREL_RTS8
  fprintf(stderr, "debug : tcob_write_relrec 110.170 : result=%d, stbuf.st_size=%ld, h->mrecidx=%d, h->crecidx=%d, irecidx=%d\n", result, stbuf.st_size, h->mrecidx, h->crecidx, irecidx); 
#endif     
  /* Verify */
  if (h->mrecidx != (stbuf.st_size / h->mreclen))
     return (TCB_STATUS_30_PERMANENT_ERROR);
  h->crecidx = irecidx;

#ifdef DEBUG_FILEREL_RTS8
  fprintf(stderr, "debug : tcob_write_relrec 110.180 : result=%d, stbuf.st_size=%ld, h->mrecidx=%d, h->crecidx=%d\n", result, stbuf.st_size, h->mrecidx, h->crecidx); 
#endif     

  return r;
}

/*
//
//  Allocate relative file working structures
//
*/
tcb_filerel_handle* tcob_allocate_frel(struct file_desc *f)
{
  tcb_filerel_handle *h;  

  h = malloc(sizeof(tcb_filerel_handle));
  if (h == NULL) 
     return (NULL);
  
  h->precsize = sizeof(int);
  h->mreclen  = h->precsize + f->reclen;
  h->mrecidx  = 0;  
  h->crecidx = TCB_FILE_RELATIVE_POSITION_UNDEFINED;

  h->buf = tcob_allocate_fbuffers(2, h->mreclen + 1);
  if (h->buf == NULL) {
     free(h);
     return (NULL);
  }
    
  return h;
}

/*
//
//  Free relative working structures
//
*/
void tcob_free_frel(tcb_filerel_handle *h)
{  
  if (h != NULL) {
     if (h->buf != NULL)
        tcob_free_fbuffers(h->buf);
     free(h); 
  } 
}
