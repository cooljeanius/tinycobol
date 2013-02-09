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

#include "htcoblib.h"
#include "fileio.h" 
#include "fileisam.h"

/*
//#define DEBUG_FILEISAM_RTS0    1   // Open and close statements  
//#define DEBUG_FILEISAM_RTS1    1   // Read statements  
//#define DEBUG_FILEISAM_RTS2    1   // Read Next statement        
//#define DEBUG_FILEISAM_RTS3    1   // Write statement           
//#define DEBUG_FILEISAM_RTS4    1   // Start statement           
//#define DEBUG_FILEISAM_RTS5    1   // Start statement - LT and LTEQ  
//#define DEBUG_FILEISAM_RTS6    1   // Delete statement          
//#define DEBUG_FILEISAM_RTS7    1   // Rewrite statement         
//#define DEBUG_FILEISAM_RTS8    1   // cob_build_vbidx           
//#define DEBUG_FILEISAM_RTS9    1   // tcob_allocate_vbidx      
//#define DEBUG_FILEISAM_RTS10   1   // tcob_verify_vbidx      
*/

extern void save_status (struct file_desc *f, int status);
extern int tcob_save_status(char *status, int rt);

/*
// 
// ISAM open
// 
*/
int tcob_open_idx(struct file_desc *f, int mode) 
{
  int r=0;
  tcb_fileio_vbidx_handle *h;          

#ifdef DEBUG_FILEISAM_RTS0
  fprintf(stderr, "debug : tcob_open_idx : 0020.020 : filename=%s;\n", f->filename); 
#endif                                       
  
  if (f->dbp != NULL)
     return (99);

  if (f->filename == NULL)
     return (99);
  
  h = tcob_allocate_vbidx(f);
  if (h == NULL) 
     return (99);

  f->dbp = (void *)h;

  switch (mode) {

    case TCB_FILE_OPEN_MODE_INPUT: 
        r = tcob_open_input_idx(f);
        break;

    case TCB_FILE_OPEN_MODE_EXTEND: 
    case TCB_FILE_OPEN_MODE_IO: 
        r = tcob_open_io_idx(f); 
        break;

    case TCB_FILE_OPEN_MODE_OUTPUT: 
        r = tcob_open_output_idx(f);
        break;

    default:
       r = 99;
       break;

  }
  
  if (r != 0) {
     if (f->filename != NULL) 
        free(f->filename);
     tcob_free_vbidx(f);
     f->filename = NULL;
     f->dbp = NULL;
  }
  else {
    /* Save file handle */
    f->dbp = (void *)h;
    /* save mode to check later (read,write,start,...)  */
    f->open_mode = mode;
    /* Initialize flags  */
    f->flags.read_done = 0;
    f->flags.start_record = 0; 
    /* save the file in the list of open files */
    tcob_add_file_list(f);
  }
  
#ifdef DEBUG_FILEISAM_RTS0
  fprintf(stderr, "debug : tcob_open_idx : 0020.140 : r=%d\n", r); 
#endif                                       

  return r;
}

/*
//
//  ISAM open - INPUT
//
*/
int tcob_open_input_idx(struct file_desc *f) 
{
  int r=0, imode=0, ifilehandle;
  tcb_fileio_vbidx_handle *h;          
  struct stat st1, st2;

#ifdef DEBUG_FILEISAM_RTS0
  fprintf(stderr, "debug : tcob_open_input_idx : 030.020 : filename=%s;\n", f->filename); 
#endif                                       
  
  h = (tcb_fileio_vbidx_handle *)f->dbp;
  if ((stat(h->fdatname, &st1) == -1 && errno == ENOENT) ||
      (stat(h->fidxname, &st2) == -1 && errno == ENOENT)) 
     return (35);        

  if (f->flags.file_isvariable == 1)
     imode = ISINPUT+ISVARLEN+ISAUTOLOCK;
  else
     imode = ISINPUT+ISFIXLEN+ISAUTOLOCK;

  ifilehandle = isopen(f->filename, imode);
  /* Set return code depending on VB iserrno */
  if (ifilehandle < 0) {
     r = tcob_eisam2ecob(0);
  }

  /* Verify ISAM structures */
  if (r == 0) {
     r = tcob_verify_vbidx(f, ifilehandle);
     if (r != 0) { 
        isclose(ifilehandle);
        r = 99;
     }
  }

  if (r == 0) 
     h->ifilehandle = ifilehandle;
  
#ifdef DEBUG_FILEISAM_RTS0
  fprintf(stderr, "debug : tcob_open_input_idx : 030.140 : iserrno=%d, r=%d\n", iserrno, r); 
#endif                                       

  return r;
}


/*
//
//  ISAM open - OUTPUT
//
*/
int tcob_open_output_idx(struct file_desc *f) 
{
  int r=0, imode=0, ifilehandle;
  tcb_fileio_vbidx_handle *h;          
  struct stat st1, st2;

#ifdef DEBUG_FILEISAM_RTS0
  fprintf(stderr, "debug : tcob_open_output_idx : 040.020 : filename=%s;\n", f->filename); 
#endif                                       
  
  h = (tcb_fileio_vbidx_handle *)f->dbp;

  /* If the files do NOT exist build the files  */
  if ((stat(h->fdatname, &st1) == -1 && errno == ENOENT) ||
      (stat(h->fidxname, &st2) == -1 && errno == ENOENT)) {
     r = tcob_build_vbidx(f); 
#ifdef DEBUG_FILEISAM_RTS0
     fprintf(stderr, "debug : tcob_open_output_idx : 040.040 : r=%d;\n", r); 
#endif                                       
     if (r != 0)
        return (r);        
  }

  if (f->flags.file_isvariable == 1)
    imode = ISOUTPUT+ISVARLEN+ISAUTOLOCK;
  else
    imode = ISOUTPUT+ISFIXLEN+ISAUTOLOCK;

  ifilehandle = isopen(f->filename, imode);
  /* Set return code depending on VB iserrno */
  if (ifilehandle < 0)
     r = tcob_eisam2ecob(0);
  else
     h->ifilehandle = ifilehandle;

#ifdef DEBUG_FILEISAM_RTS0
  fprintf(stderr, "debug : tcob_open_output_idx : 040.140 : iserrno=%d, r=%d\n", iserrno, r); 
#endif                                       

  return r;
}


/*
//
//  ISAM open - IO
//
*/
int tcob_open_io_idx(struct file_desc *f) 
{
  int r=0, imode=0, ifilehandle;
  tcb_fileio_vbidx_handle *h;          
  struct stat st1, st2;

#ifdef DEBUG_FILEISAM_RTS0
  fprintf(stderr, "debug : tcob_open_io_idx : 050.020 : filename=%s;\n", f->filename); 
#endif                                       
  
  h = (tcb_fileio_vbidx_handle *)f->dbp;
  if ((stat(h->fdatname, &st1) == -1 && errno == ENOENT) ||
      (stat(h->fidxname, &st2) == -1 && errno == ENOENT))
     return (35);        

  if (f->flags.file_isvariable == 1)
    imode = ISINOUT+ISVARLEN+ISAUTOLOCK;
  else
    imode = ISINOUT+ISFIXLEN+ISAUTOLOCK;

  ifilehandle = isopen(f->filename, imode);
  /* Set return code depending on VB iserrno */
  if (ifilehandle < 0)
     r = tcob_eisam2ecob(0);

  /* Verify ISAM structures */
  if (r == 0) {
     r = tcob_verify_vbidx(f, ifilehandle);
     if (r != 0) { 
        isclose(ifilehandle);
        r = 99;
     }
  }

  if (r == 0) 
     h->ifilehandle = ifilehandle;

#ifdef DEBUG_FILEISAM_RTS0
  fprintf(stderr, "debug : tcob_open_io_idx : 050.140 : r=%d\n", r); 
#endif                                       

  return r;
}

/*
//
//  ISAM close
//
*/
int tcob_close_idx(struct file_desc *f) 
{
  int r=0;
  tcb_fileio_vbidx_handle *h;          

#ifdef DEBUG_FILEISAM_RTS0
  fprintf(stderr, "debug : tcob_close_idx : 060.020 : r=%d\n", r); 
#endif                                       

  if (f->dbp == NULL)
     return (99);

  if (f->filename == NULL)
     return (99);
  
  h = (tcb_fileio_vbidx_handle *)f->dbp;

  /* Flush and close VB-ISAM file */
  r = isflush(h->ifilehandle);
  if (r != 0) {
     r = tcob_eisam2ecob(0);
  }
  else {        
     /* Set return code depending on VB iserrno */
     r = isclose(h->ifilehandle);
     if (r != 0) {
        r = tcob_eisam2ecob(0);
     }
     else {
        tcob_remove_file_list(f);
        if (f->filename != NULL);
           free(f->filename);
        tcob_free_vbidx(f);
        f->filename = NULL;
        f->dbp = NULL;
     }
  }

#ifdef DEBUG_FILEISAM_RTS0
  fprintf(stderr, "debug : tcob_close_idx : 060.140 : r=%d\n", r); 
#endif                                       
  
  return r;
}

/*
//
//  ISAM read
//
*/
int tcob_read_idx(struct file_desc *f, struct fld_desc *rectofrom_desc, char *rectofrom_buf, 
                  struct fld_desc *reclen_desc, char *reclen_buf, 
                  int ikey, struct fld_desc *fkey, char *keybuf) 
{
  int iresult, r=0, reclen;
  tcb_fileio_vbidx_handle *h;
  tcob_file_key *k;
  char *crecord;
  struct keydesc *wkeydesc;   
         
#ifdef DEBUG_FILEISAM_RTS1
  fprintf(stderr, "debug : tcob_read_idx 070.020 : filename=%s, reclen=%d;\n", f->filename, f->reclen);
#endif                 

  f->flags.read_done = 0;
  f->flags.start_record = 0;

  /* ERROR check : File is open */
  if (f->dbp == NULL) {
     /* ERROR check : Set file-status condition when file is not available */
     if (f->flags.optional && f->flags.file_missing) 
        RETURN_STATUS(10);
     RETURN_STATUS(47);
  }

  /* ERROR check : Record length is valid - unknown error */
  if (f->reclen == -1)
     RETURN_STATUS(99);
  
  /* ERROR check : Must in INPUT or IO mode */
  if (((f->open_mode != TCB_FILE_OPEN_MODE_INPUT) && (f->open_mode != TCB_FILE_OPEN_MODE_IO)))
     RETURN_STATUS(47);
  
  /* Check that we didn't already hit eof */
  if ((f->open_mode == TCB_FILE_OPEN_MODE_INPUT || f->open_mode == TCB_FILE_OPEN_MODE_IO) && f->flags.eof_hit)
     RETURN_STATUS(46);
  
  /* ERROR check : For random key READ access mode must be RANDOM or DYNAMIC */
  if ((f->access_mode != TCB_FILE_ACCESS_MODE_RANDOM) &&
      (f->access_mode != TCB_FILE_ACCESS_MODE_DYNAMIC)
     )
     RETURN_STATUS(39);

 /* ERROR check : Key is required - unknown compiler error */
  if (fkey == NULL) 
     RETURN_STATUS(99);

  /* ERROR check : Key index is within bounds */
  if ((f->nkeys <= ikey) || (0 > ikey)) 
     RETURN_STATUS(99);
  
  h = (tcb_fileio_vbidx_handle *)f->dbp;
  k = f->keys;
  crecord = h->buf->buf[0]; 

  /* Read with key */
  memset (crecord, ' ', f->reclen);
  k = f->keys + ikey;
  memcpy (crecord+k->offset, keybuf, fkey->len);
  wkeydesc = h->skeydesc + ikey;
  iresult = isstart(h->ifilehandle, wkeydesc, f->reclen, crecord, ISEQUAL);
  if (iresult != 0) { 
     r = tcob_eisam2ecob(0);
     RETURN_STATUS(r);
  }
  iresult = isread(h->ifilehandle, crecord, ISCURR);
  if (iresult != 0) { 
     r = tcob_eisam2ecob(0);
     RETURN_STATUS(r);
  }

  /* Variable Length File */
  if (reclen_desc != NULL) {
     reclen = isreclen;  
     if (reclen > f->reclen) 
        RETURN_STATUS(99);
     /* Set record length buffer for variable length file */
     tcob_move(&_generic_4binary, (char *)&reclen, reclen_desc, reclen_buf);     
  }
  else {
     reclen = f->reclen;
  }

  /* Clear buffer and move data record */
  memset(f->record, ' ', f->reclen);
  memcpy (f->record, crecord, reclen);

  /* Copy buffer data to INTO identifiers buffer */
  if (rectofrom_desc != NULL) {
     memset(rectofrom_buf, ' ', rectofrom_desc->len);
     if (rectofrom_desc->len > reclen) 
        memcpy(rectofrom_buf, crecord, reclen);
     else
        memcpy(rectofrom_buf, crecord, rectofrom_desc->len);
  }

  f->flags.read_done = 1;

#ifdef DEBUG_FILEISAM_RTS1
  fprintf(stderr, "debug : tcob_read_idx 070.140 : r=%d;\n", r);
#endif                                       

  RETURN_STATUS(r);
}

/*
//
//  ISAM read NEXT - PREVIOUS
//
*/
int tcob_read_next_idx(struct file_desc *f, struct fld_desc *rectofrom_desc, char *rectofrom_buf, 
                       int nflag, 
                       struct fld_desc *reclen_desc, char *reclen_buf) 
{
  int iresult, r=0, imode, reclen;
  tcb_fileio_vbidx_handle *h;
  tcob_file_key *k;
  char *crecord;

  /* ERROR check : File is open */
  if (f->dbp == NULL) {
     /* ERROR check : Set file-status condition when file is not available */
     if (f->flags.optional && f->flags.file_missing) 
        RETURN_STATUS(10);
     RETURN_STATUS(47);
  }

#ifdef DEBUG_FILEISAM_RTS2
  fprintf(stderr, "debug : tcob_read_next_idx 080.020 : filename=%s, reclen=%d;\n", f->filename, f->reclen);
#endif                                       

  f->flags.read_done = 0;

  
  /* ERROR check : Record length is valid - unknown error */
  if (f->reclen == -1)
     RETURN_STATUS(99);
  
  /* ERROR check : Must be in INPUT or IO mode */
  if ((f->open_mode != TCB_FILE_OPEN_MODE_INPUT) && (f->open_mode != TCB_FILE_OPEN_MODE_IO))
     RETURN_STATUS(47);
  
  /* Check that we didn't already hit eof */
  if ((f->open_mode == TCB_FILE_OPEN_MODE_INPUT || 
       f->open_mode == TCB_FILE_OPEN_MODE_IO) && 
      (f->flags.eof_hit)
     )
     RETURN_STATUS(46);
  
  /* ERROR check : For sequential READ access mode must be SEQUENTIAL or DYNAMIC */
  if ((f->access_mode != TCB_FILE_ACCESS_MODE_SEQUENTIAL) &&
      (f->access_mode != TCB_FILE_ACCESS_MODE_DYNAMIC)
     )
     RETURN_STATUS(39);
 
  h = (tcb_fileio_vbidx_handle *)f->dbp;
  k = f->keys;
  crecord = h->buf->buf[0]; 

#ifdef DEBUG_FILEISAM_RTS2
  fprintf(stderr, "debug : tcob_read_next_idx 080.040 : isrecnum=%d;\n", isrecnum);
#endif                                       

  /* If there is a start record outstanding set current record for read */
  if ((f->flags.start_record == 1) || (f->flags.read_next_done == 1)) {
     imode = ISCURR;
#ifdef DEBUG_FILEISAM_RTS2
     fprintf(stderr, "debug : tcob_read_next_idx 080.060 : imode(ISCURR)=%d;\n", imode);
#endif                                       
  }
  else {
     //memcpy (crecord, record, f->reclen);
  /* Set record position for read */
     if (nflag == TCB_FILE_READ_REC_PREVIOUS) {
        imode = ISPREV;
#ifdef DEBUG_FILEISAM_RTS2
        fprintf(stderr, "debug : tcob_read_next_idx 080.062 : imode(ISPREV)=%d;\n", imode);
#endif                                       
     }
     else { 
        imode = ISNEXT;
#ifdef DEBUG_FILEISAM_RTS2
        fprintf(stderr, "debug : tcob_read_next_idx 080.064 : imode(ISNEXT)=%d;\n", imode);
#endif                                       
     }
  }
  f->flags.start_record = 0;
  f->flags.read_next_done = 0;

  /* Read record */
  iresult = isread(h->ifilehandle, crecord, imode);
#ifdef DEBUG_FILEISAM_RTS2
  fprintf(stderr, "debug : tcob_read_next_idx 080.080 : iresult=%d, isrecnum=%d;\n", iresult, isrecnum);
#endif                                       
  /* Set return code depending on VB iserrno */
  if (iresult != 0) { 
     r = tcob_eisam2ecob(0);
     RETURN_STATUS(r);
  }
  
  /* Variable Length File */
  if (reclen_desc != NULL) {
     reclen = isreclen;
     if (reclen > f->reclen) 
        RETURN_STATUS(99);
     tcob_move(&_generic_4binary, (char *)&reclen, reclen_desc, reclen_buf);     
  }
  else {
     reclen = f->reclen;
  }

#ifdef DEBUG_FILEISAM_RTS2
     fprintf(stderr, "debug : tcob_read_next_idx 080.100 : reclen=%d;\n", reclen);
     if (reclen > 0) {
        int i, ilen=reclen;
        char *pt = crecord;
        fprintf(stderr, "debug : tcob_read_next_idx 080.105 : record=");
        for (i=0; i<ilen; i++) {      
          fprintf(stderr, "%c", *(pt + i));
        }
        fprintf(stderr, ";\n");
     }
#endif                                       

  /* Clear buffer and move data record */
  memset(f->record, ' ', f->reclen);
  memcpy (f->record, crecord, reclen);

  /* Copy buffer data to INTO identifiers buffer */
  if (rectofrom_desc != NULL) {
     memset(rectofrom_buf, ' ', rectofrom_desc->len);
     if (rectofrom_desc->len > reclen) 
        memcpy(rectofrom_buf, crecord, reclen);
     else
        memcpy(rectofrom_buf, crecord, rectofrom_desc->len);
  }

  f->flags.read_done = 1;

#ifdef DEBUG_FILEISAM_RTS2
  fprintf(stderr, "debug : tcob_read_next_idx 080.120 : r=%d;\n", r);
#endif                                       

  RETURN_STATUS(r);
}

/*
//
//  ISAM write
//
*/
int tcob_write_idx(struct file_desc *f, struct fld_desc *rectofrom_desc, char *rectofrom_buf,
                   struct fld_desc *reclen_desc, char *reclen_buf) 
{
  int iresult, r=0, reclen;
  tcb_fileio_vbidx_handle *h;
  char *crecord;

  f->flags.read_done = 0;
  f->flags.start_record = 0; 
  
  /* ERROR check : File is open */
  if (f->dbp == NULL)
     RETURN_STATUS(48);
             
#ifdef DEBUG_FILEISAM_RTS3
  fprintf(stderr, "debug : tcob_write_idx 090.040 : filename=%s, reclen=%d\n", f->filename, f->reclen);
#endif

  /* ERROR check : Record length is valid - unknown error */
  if (f->reclen == -1) 
     RETURN_STATUS(99);
  
  /* ERROR check : Open mode must be OUTPUT, IO, EXTEND */
  if (f->open_mode == TCB_FILE_OPEN_MODE_INPUT)  
     RETURN_STATUS(48);

  /* ERROR check : IGNORED - not shure how to impliment
     When file ACCESS MODE is SEQUENTIAL the primary KEY should be in ascending order.
     Ascending order relative to previous write KEY ?
  */
  
  h = (tcb_fileio_vbidx_handle *)f->dbp;
  crecord = h->buf->buf[0]; 
  memset(crecord, ' ', f->reclen);

  /* Variable length record */                  
  if (reclen_desc != NULL) {
     /* Convert record to int type */
     tcob_move(reclen_desc, reclen_buf, &_generic_4binary, (char *)&reclen);     
     if (reclen > f->reclen) 
        RETURN_STATUS(99);
     isreclen = reclen;
#ifdef DEBUG_FILEISAM_RTS3
     fprintf(stderr, "debug : tcob_write_idx 090.060 : file variable len=(%d, %d) reclen=%d\n", f->reclen, f->reclen_min, reclen);
#endif
  }
  else {
     reclen = f->reclen;
  }

  /* Copy write buffer data to record and FROM identifier buffer */
  if (rectofrom_desc != NULL) {
     memset(f->record, ' ', f->reclen);
     if (rectofrom_desc->len > f->reclen) 
        memcpy(f->record, rectofrom_buf, f->reclen);
     else
        memcpy(f->record, rectofrom_buf, rectofrom_desc->len);
  }
  memcpy(crecord, f->record, reclen);

  /* write record */
  iresult = iswrite(h->ifilehandle, crecord);
  /* Set return code depending on VB iserrno */
  if (iresult != 0) 
     r = tcob_eisam2ecob(0);

#ifdef DEBUG_FILEISAM_RTS3
    fprintf(stderr, "debug : tcob_write_idx 090.080 : file status(r)=%d, iserrno=%d\n", r, iserrno);
#endif

  RETURN_STATUS(r);
}

/*
//
//  ISAM rewrite
//
*/
int tcob_rewrite_idx(struct file_desc *f, struct fld_desc *rectofrom_desc, char *rectofrom_buf,
                     struct fld_desc *reclen_desc, char *reclen_buf) 
{
  int iresult, r=0, reclen;
  tcb_fileio_vbidx_handle *h;
  char *crecord;

#ifdef DEBUG_FILEISAM_RTS7
  fprintf(stderr, "debug : tcob_rewrite_idx 100.080 : \n");
#endif                                       

  /* ERROR check : File is open */
  if (f->dbp == NULL)
     RETURN_STATUS(49);
  
  /* ERROR check : Record length is valid - unknown error */
  if (f->reclen == -1)
     RETURN_STATUS(99);
  
  /* ERROR check : Must in IO mode */
  if (f->open_mode != TCB_FILE_OPEN_MODE_IO)
     RETURN_STATUS(49);
  
  /* Check that we didn't already hit eof */
  if ((f->open_mode == TCB_FILE_OPEN_MODE_IO) && f->flags.eof_hit)
     RETURN_STATUS(43);
  
  /* Error check : If access mode is SEQUENTIAL the read done flag must be set to TRUE */
  if ((f->access_mode == TCB_FILE_ACCESS_MODE_SEQUENTIAL) && 
      (f->flags.read_done == 0))  
     RETURN_STATUS(39);

  h = (tcb_fileio_vbidx_handle *)f->dbp;
  crecord = h->buf->buf[0]; 

  /* Error check : Access mode SEQUENTIAL and primary KEY */
  /* The PREVIOUS READ primary KEY must be equal to primary KEY in record */
  if (f->access_mode == TCB_FILE_ACCESS_MODE_SEQUENTIAL) { 
     int sresult, startpos, poslen;
     tcob_file_key *k;
      
     k = f->keys;
     startpos = k->offset;
     poslen   = k->key_desc->len;    
     
     /* Compare keys */
     sresult = strncmp(crecord+startpos, f->record+startpos, poslen);
     if (sresult != 0)
        RETURN_STATUS(30);
  }
  
  /* Variable length record */                  
  if (reclen_desc != NULL) {
     /* Convert record to int type */
     tcob_move(reclen_desc, reclen_buf, &_generic_4binary, (char *)&reclen);     
     if (reclen > f->reclen) 
        RETURN_STATUS(99);
     isreclen = reclen;
  }
  else {
     reclen = f->reclen;
  }

  /* Copy write buffer data to record and FROM identifier buffer */
  if (rectofrom_desc != NULL) {
     memset(f->record, ' ', f->reclen);
     if (rectofrom_desc->len > f->reclen) 
        memcpy(f->record, rectofrom_buf, f->reclen);
     else
        memcpy(f->record, rectofrom_buf, rectofrom_desc->len);
  }
  memcpy(crecord, f->record, reclen);

  /* rewrite record */
  iresult = isrewrite(h->ifilehandle, crecord);
  /* Set return code depending on VB iserrno */
  if (iresult != 0) 
     r = tcob_eisam2ecob(0);

#ifdef DEBUG_FILEISAM_RTS7
  fprintf(stderr, "debug : tcob_rewrite_idx 100.080 : file status(r)=%d, iserrno=%d\n", r, iserrno);
#endif

  f->flags.read_done = 0;
  f->flags.start_record = 0; 

  RETURN_STATUS(r);

}

/*
//
//  ISAM delete
//
*/
int tcob_delete_idx(struct file_desc *f) 
{
  int iresult, r=0;
  long drecnum;
  tcb_fileio_vbidx_handle *h;
  tcob_file_key *k;
  char *crecord;
  /*struct keydesc *wkeydesc;  */ 


#ifdef DEBUG_FILEISAM_RTS6
  fprintf(stderr, "debug : tcob_delete_idx 110.020 : \n");
#endif                                       

  /* ERROR check : File is open */
  if (f->dbp == NULL)
     RETURN_STATUS(49);
  
  /* ERROR check : Record length is valid - unknown error */
  if (f->reclen == -1)
     RETURN_STATUS(99);
  
  
  /* ERROR check : Must be in IO mode */
  if (f->open_mode != TCB_FILE_OPEN_MODE_IO)
     RETURN_STATUS(49);

  /* Error check : If access mode is SEQUENTIAL the read done flag must be set to TRUE */
  if ((f->access_mode == TCB_FILE_ACCESS_MODE_SEQUENTIAL) && 
      (f->flags.read_done == 0))  
     RETURN_STATUS(39);

  h = (tcb_fileio_vbidx_handle *)f->dbp;
  k = f->keys;
  crecord = h->buf->buf[0]; 

/* Use record number to delete as defined in READ
  // If access mode is SEQUENTIAL and read flag is TRUE then use PREVIOUS READ as KEY 
  // If access mode is DYNAMIC or RANDOM then use primary KEY as defined in record 
  //if (f->access_mode != TCB_FILE_ACCESS_MODE_SEQUENTIAL) {
  //   memset (crecord, ' ', f->reclen);
  //   memcpy (crecord, record+k->offset, k->key_desc->len);
  //}
*/

#ifdef DEBUG_FILEISAM_RTS6
     fprintf(stderr, "debug : tcob_delete_idx 110.060 : f->reclen=%d;\n", f->reclen);
     if (f->reclen > 0) {
        int i, ilen=f->reclen;
        char *pt = record;
        fprintf(stderr, "debug : tcob_delete_idx 110.065 : record=");
        for (i=0; i<ilen; i++) {      
          fprintf(stderr, "%c", *(pt + i));
        }
        fprintf(stderr, ";\n");
     }
#endif                                       

#ifdef DEBUG_FILEISAM_RTS6
  fprintf(stderr, "debug : tcob_delete_idx 110.090 : isrecnum=%d;\n", isrecnum);
#endif                                       
  /* Save record number to be deleted */
  drecnum = isrecnum;

  /* Read NEXT or PREVIOUS record to set current record */
  f->flags.read_next_done = 1;
  iresult = isread(h->ifilehandle, crecord, ISNEXT);
#ifdef DEBUG_FILEISAM_RTS2
  fprintf(stderr, "debug : tcob_delete_idx 110.095 : iresult=%d, isrecnum=%d;\n", iresult, isrecnum);
#endif                                       
  if (iresult != 0) {
     iresult = isread(h->ifilehandle, crecord, ISPREV);
     f->flags.read_next_done = 0;
#ifdef DEBUG_FILEISAM_RTS2
  fprintf(stderr, "debug : tcob_delete_idx 110.098 : iresult=%d, isrecnum=%d;\n", iresult, isrecnum);
#endif                                       
  }

  /* Delete record using primary key - USE record number */
  /* iresult = isdelete(h->ifilehandle, crecord); */

  /* Delete record using record number */
  iresult = isdelrec(h->ifilehandle, drecnum);
#ifdef DEBUG_FILEISAM_RTS6
  fprintf(stderr, "debug : tcob_delete_idx 110.100 : iresult=%d, isrecnum=%d;\n", iresult, isrecnum);
#endif                                       
  /* Set return code depending on VB iserrno */
  if (iresult != 0) 
     r = tcob_eisam2ecob(0);

  /* Reset flags */
  f->flags.read_done    = 0;
  f->flags.init_done    = 0; 
  f->flags.start_record = 0;

#ifdef DEBUG_FILEISAM_RTS6
  fprintf(stderr, "debug : tcob_delete_idx 110.120 : r=%d;\n", r);
#endif                                       

  RETURN_STATUS(r);
}

/*
//
//  ISAM - START function
//
*/
int tcob_start_idx(struct file_desc *f,
                   int cond, int ikey,
                   struct fld_desc *recfdesc, char *key_ptr) 
{
  int iresult, cmode, startpos, poslen, r=0;
  tcb_fileio_vbidx_handle *h;
  tcob_file_key *k;
  char *crecord;
  struct keydesc *wkeydesc;   

  f->flags.eof_hit = 0;  /* additon AL : reset eof if already positioned */
  f->flags.read_done = 0;
  f->flags.start_record = 0;

#ifdef DEBUG_FILEISAM_RTS4
  fprintf(stderr, "debug : tcob_start_idx 110.040 :\n");
#endif                                       

  /* ERROR check : File is open */
  if (f->dbp == NULL)
     RETURN_STATUS(47);
  
  /* ERROR check : Record length is valid - unknown error */
  if (f->reclen == -1)
     RETURN_STATUS(99);
  
  /* ERROR check : Must be in INPUT or IO mode */
  if ((f->open_mode != TCB_FILE_OPEN_MODE_INPUT) && (f->open_mode != TCB_FILE_OPEN_MODE_IO))
     RETURN_STATUS(47);

  /* Special case for LT and LTEQ conditionals */ 
  if ((cond == TCB_CONDITIONAL_LT) || (cond == TCB_CONDITIONAL_LTEQ)) {
     r = tcob_start_lesscond_idx(f, cond, ikey, recfdesc, key_ptr); 
     RETURN_STATUS(r);
  }      
  
  h = (tcb_fileio_vbidx_handle *)f->dbp;
  k = f->keys + ikey;
  crecord = h->buf->buf[0]; 
  
  startpos = k->offset;
  poslen = recfdesc->len;
  
  memset (crecord, ' ', f->reclen);
  memcpy (crecord+startpos, key_ptr, poslen);

  switch (cond)
  {
    case TCB_CONDITIONAL_EQUAL:
      cmode = ISEQUAL;
      break;
    
    case TCB_CONDITIONAL_GT:
      cmode = ISGREAT;
      break;
    
    case TCB_CONDITIONAL_GTEQ:
      cmode = ISGTEQ;
      break;

    default:
      RETURN_STATUS(99);
      break;
  }
  
  wkeydesc = h->skeydesc + ikey;
  iresult = isstart(h->ifilehandle, wkeydesc, poslen, crecord, cmode);
  if (iresult != 0) { 
     r = tcob_eisam2ecob(0);
     RETURN_STATUS(r);
  }

  f->flags.start_record = 1;

  RETURN_STATUS(r);
}

/*
//
//  ISAM - Emulate START function for LT and LTEQ conditionals
//  Use the inverse start condition and the work backwards
//
*/
int tcob_start_lesscond_idx(struct file_desc *f, 
                   int cond, int ikey,
                   struct fld_desc *recfdesc, char *key_ptr) 
{
  int iresult, sresult, cmode, startpos, poslen, searchflag, r=0;
  tcb_fileio_vbidx_handle *h;
  tcob_file_key *k;
  char *crecord;
  struct keydesc *wkeydesc;   

#ifdef DEBUG_FILEISAM_RTS5
  fprintf(stderr, "debug : tcob_start_lesscond_idx 120.020 : \n");
#endif                                       

  h = (tcb_fileio_vbidx_handle *)f->dbp;
  k = f->keys + ikey;
  crecord = h->buf->buf[0]; 
  
  startpos = k->offset;
  poslen = recfdesc->len;
  
  memset (crecord, ' ', f->reclen);
  memcpy (crecord+startpos, key_ptr, poslen);
  
  /* Process LTEQ conditional */
  if (cond == TCB_CONDITIONAL_LTEQ) 
     cmode = ISGREAT;
  /* Process LT conditional */
  else
     cmode = ISGTEQ;

  /* Set the initial lower boundary */
  wkeydesc = h->skeydesc + ikey;
  iresult = isstart(h->ifilehandle, wkeydesc, poslen, crecord, cmode);
  if (iresult != 0) {
     cmode = ISLAST;
     iresult = isstart(h->ifilehandle, wkeydesc, poslen, crecord, cmode);
     if (iresult != 0)
         return (23); 
  }
#ifdef DEBUG_FILEISAM_RTS5
  {
   int i, ilen=poslen;
   char *pt;
   
   fprintf(stderr, "debug : tcob_start_lesscond_idx 120.060 : keyidx=%d, rec=", ikey);
   pt=crecord+startpos;
   for (i=0; i<ilen; i++) {      
      fprintf(stderr, "%c", pt[i]);
   }
   fprintf(stderr, "; key=");
   pt=key_ptr;
   for (i=0; i<ilen; i++) {      
      fprintf(stderr, "%c", pt[i]);
   }
   fprintf(stderr, ";\n");
  }
#endif                                       
  /* Read previous record to set new lower boundary */
  //iresult = isread(h->ifilehandle, crecord, ISPREV);
  iresult = isread(h->ifilehandle, crecord, ISCURR);
  if (iresult != 0)
     return (23); 
  /* Compare keys to check conditional */
  /* Loop and check for boundary condition */
  searchflag = 0;
  while (searchflag == 0) {
    
#ifdef DEBUG_FILEISAM_RTS5
  {
   int i, ilen=poslen;
   char *pt;
   
   fprintf(stderr, "debug : tcob_start_lesscond_idx 120.100 : keyidx=%d, rec=", ikey);
   pt=crecord+startpos;
   for (i=0; i<ilen; i++) {      
      fprintf(stderr, "%c", pt[i]);
   }
   fprintf(stderr, "; key=");
   pt=key_ptr;
   for (i=0; i<ilen; i++) {      
      fprintf(stderr, "%c", pt[i]);
   }
   fprintf(stderr, ";\n");
  }
#endif                                       
     /* Compare keys to check conditional */
     sresult = strncmp(crecord+startpos, key_ptr, poslen);
#ifdef DEBUG_FILEISAM_RTS5
  fprintf(stderr, "debug : tcob_start_lesscond_idx 120.140 : sresult=%d\n", sresult);
#endif                                       
     if (( (sresult < 0) && (cond == TCB_CONDITIONAL_LT)) ||
         ( (!(sresult > 0)) && (cond == TCB_CONDITIONAL_LTEQ)) 
        ) {
        searchflag = 1;
        break; 
     }

     /* Read previous record to set new lower boundary */
     iresult = isread(h->ifilehandle, crecord, ISPREV);
     if (iresult != 0)
        return (23); 
  }
       
  f->flags.start_record = 1;

#ifdef DEBUG_FILEISAM_RTS5
  fprintf(stderr, "debug : tcob_start_lesscond_idx 120.190 : r=%d\n", r);
#endif                                       

  return r;
}

/*
//
//  ISAM - build file cluster
//
*/
int tcob_build_vbidx(struct file_desc *f)
{ 
  int r=0, i=0, ifilehandle, iresult, imode;
  tcb_fileio_vbidx_handle *h;
  struct keydesc *wkeydesc;   

#ifdef DEBUG_FILEISAM_RTS8
     fprintf(stderr, "debug : tcob_build_vbidx 010.040 : f->filename=%s, f->flags.file_isvariable=%d;\n", f->filename, f->flags.file_isvariable);
#endif                                       
  
  h = (tcb_fileio_vbidx_handle *)f->dbp;

  if (f->flags.file_isvariable == 1) {
     imode = ISINOUT+ISVARLEN+ISEXCLLOCK;
     isreclen = f->reclen_min;
  }
  else {
     imode = ISINOUT+ISFIXLEN+ISEXCLLOCK;
  }

  wkeydesc = h->skeydesc;
  /* Define ISAM file - define primary key */  
  ifilehandle = isbuild(f->filename, f->reclen, wkeydesc, imode);
#ifdef DEBUG_FILEISAM_RTS8
  fprintf(stderr, "debug : tcob_build_vbidx 010.060 : f->filename=%s, f->reclen=%d, ifilehandle=%d;\n", f->filename, f->reclen, ifilehandle);
#endif                                       
  if (ifilehandle < 0) {
     r = tcob_eisam2ecob(0);
     return (r);        
  }

  /* Define ISAM file - define secondary keys */  
  for (i=1; i < f->nkeys; i++) {
     wkeydesc = h->skeydesc + i;
     iresult = isaddindex(ifilehandle, wkeydesc);
     if (iresult != 0) {
        r = tcob_eisam2ecob(0);
        iresult = isclose(ifilehandle);
        iserase (f->filename);
        return (r);        
     }
  }

  iresult = isclose(ifilehandle);
  if (iresult != 0) {
     r = tcob_eisam2ecob(0);
     iserase (f->filename);
     return (r);        
  }
  
  h->ifilehandle = ifilehandle;

#ifdef DEBUG_FILEISAM_RTS8
     fprintf(stderr, "debug : tcob_build_vbidx 010.080 : r=%d;\n", r);
#endif                                       

  RETURN_STATUS(r);        
}

/*
//
//  ISAM - allocate working structures
//
*/
tcb_fileio_vbidx_handle* tcob_allocate_vbidx(struct file_desc *f)
{
  int size, len, i;
  tcb_fileio_vbidx_handle *h;  
  tcob_file_key *k;
  struct keydesc *wkeydesc;  

  h = malloc(sizeof(tcb_fileio_vbidx_handle));
  if (h == NULL) {
     return (NULL);
  }
  
  len = strlen(f->filename);

  h->fdatname = (char *)malloc((sizeof(char) * len) + 5);
  if (h->fdatname == NULL) { 
     free(h);
     return (NULL);
  }
  strncpy(h->fdatname, f->filename, len + 1);
  strncat(h->fdatname, TCB_FILE_SUFFIX_DATA, 5);

  h->fidxname = (char *)malloc((sizeof(char) * len) + 5);
  if (h->fidxname == NULL) { 
     free(h->fdatname);
     free(h);
     return (NULL);
  }
  strncpy(h->fidxname, f->filename, len + 1);
  strncat(h->fidxname, TCB_FILE_SUFFIX_INDEX, 5);

  /* h->ckey  = -1; */

  h->buf = tcob_allocate_fbuffers(1, f->reclen + 5);
  if (h->buf == NULL) {
     free(h->fdatname);
     free(h->fidxname);
     free(h);
     return (NULL);
  }

  //h->nkeys = f->nkeys;     
  size = sizeof(struct keydesc);
  h->skeydesc = malloc(size * f->nkeys);
  if (h->skeydesc == NULL) {
     free(h->fdatname);
     free(h->fidxname);
     tcob_free_fbuffers(h->buf);
     free(h);
     return (NULL);
  }
  
  memset (h->skeydesc, 0, size * f->nkeys);
  for (i=0; i < f->nkeys; i++) {
     k = f->keys + i;
#ifdef DEBUG_FILEISAM_RTS9
     fprintf(stderr, "debug : tcob_allocate_vbidx 150.700 : index=%d, start=%d, len=%d;\n", i, k->offset, k->key_desc->len );
#endif                                       
     wkeydesc = h->skeydesc + i;
     if (k->flag == TCB_FILE_KEY_FLAG_INDEXED_DUPLICATES) 
        wkeydesc->k_flags  = ISDUPS;
     else
        wkeydesc->k_flags  = ISNODUPS;
     wkeydesc->k_nparts = 1;
     wkeydesc->k_start  = k->offset;
     wkeydesc->k_leng   = k->key_desc->len;
     wkeydesc->k_type   = CHARTYPE;
  }

  /* Set default current key */ 
  /* h->ckey = 0; */
  /* h->nkeys = f->nkeys; - NOT used */ 
    
  return h;
}

/*
//
//  ISAM - verify ISAM structures
//
*/
int tcob_verify_vbidx(struct file_desc *f, int ifilehandle)
{
  int r=0, /*numkeys,*/ i;
  short numkeys=0;
  //tcb_fileio_vbidx_handle *h;
  tcob_file_key *k;   
  struct dictinfo info;
  struct keydesc wkeydesc;  
  
  //h = (tcb_fileio_vbidx_handle *)f->dbp;

  isindexinfo(ifilehandle, &info, 0);

  /* NOTE: First test assumes 1 byte (ASCII) char-set */
  /* Verify the record length */
#ifdef DEBUG_FILEISAM_RTS10
  fprintf(stderr, "debug : tcob_verify_vbidx 250.100 : f->reclen=%d, f->reclen_min=%d, isreclen=%d, info.di_recsize=%d;\n", 
                   f->reclen, f->reclen_min, isreclen, info.di_recsize);
#endif                                       
  if (f->reclen != info.di_recsize) 
     r = 1;
      
  /* NOTE: When the record type is variable the MSB is set.
     The xISAM manual uses 0x7fff as a mask, but VB-ISAM requires 0xff7f on x86-32. */
  /* Verify the record type (variable or fixed) structure */
  if (r == 0) {
     /* Verify the record type has a variable type structure */
     if (f->reclen_min != 0) {
        /* numkeys = info.di_nkeys & 0x7fff; */ 
        numkeys = info.di_nkeys & 0xff7f; 
        if (f->reclen_min != isreclen) 
           r = 2;
     }
     /* Verify the record type has a fixed type structure */
     else {
        numkeys = info.di_nkeys;
        if (f->reclen != isreclen) 
           r = 3;
     }
#ifdef DEBUG_FILEISAM_RTS10
     fprintf(stderr, "debug : tcob_verify_vbidx 250.300 : f->nkeys=%d, numkeys=%d;\n", f->nkeys, numkeys);
#endif                                       
  }

  /* Verify the number of keys */
  if (r == 0) {
    if (f->nkeys != numkeys) 
       r = 5;
  }
     
  /* Verify the key structure */
  if (r == 0) {
     k = f->keys;
     for (i=1; i<=numkeys; i++, k++) {
        /* Get the index structure */
        isindexinfo (ifilehandle, &wkeydesc, i);

        /* Verify the key structure duplicate flag */
#ifdef DEBUG_FILEISAM_RTS10
        fprintf(stderr, "debug : tcob_verify_vbidx 250.410 : key=%d, k->flag=%d, wkeydesc.k_flags=%d;\n", i, k->flag, wkeydesc.k_flags);
#endif                                       
        if (((k->flag == TCB_FILE_KEY_FLAG_INDEXED_DUPLICATES) &&
             (wkeydesc.k_flags == ISNODUPS)
            )  ||
            ((k->flag == TCB_FILE_KEY_FLAG_INDEXED_UNIQUE) &&
             (wkeydesc.k_flags == ISDUPS)))  {
           r=6;
           break; 
        }

#ifdef DEBUG_FILEISAM_RTS10
        fprintf(stderr, "debug : tcob_verify_vbidx 250.420 : key=%d, k->offset=%d, wkeydesc.k_start=%d;\n", i, k->offset, wkeydesc.k_start);
#endif                                       
        /* Verify the key structure record offset */
        if (k->offset != wkeydesc.k_start) {
           r=7;
           break; 
        }

#ifdef DEBUG_FILEISAM_RTS10
        fprintf(stderr, "debug : tcob_verify_vbidx 250.430 : key=%d, k->key_desc->len=%ld, wkeydesc.k_leng=%d;\n", i, k->key_desc->len, wkeydesc.k_leng);
#endif                                       
        /* Verify the key structure key length */
        if (k->key_desc->len != wkeydesc.k_leng ) {
           r=8;
           break; 
        }
     }     
  }

  return r;
}

/*
//
//  ISAM - free working structures
//
*/
void tcob_free_vbidx(struct file_desc *f)
{
  tcb_fileio_vbidx_handle *h;
  
  if (f->dbp != NULL) {
     h = (tcb_fileio_vbidx_handle *)f->dbp;
     if (h->skeydesc != NULL)
        free(h->skeydesc); 
     if (h->buf != NULL)
        tcob_free_fbuffers(h->buf);
     if (h->fidxname != NULL)
        free(h->fidxname); 
     if (h->fdatname != NULL)
        free(h->fdatname); 
     free(h); 
     f->dbp = NULL;
  } 
}

/*
//
//  NOTE: This code was originally copied from OpenCOBOL 
//
//  ISAM - convert VB-ISAM error codes to standard COBOL file status codes
//
*/
int tcob_eisam2ecob(int enumber)
{
  int r;

  switch (iserrno) {

  case 0:
     r = TCB_STATUS_00_SUCCESS;
     break;

  case ENOREC:
     r = TCB_STATUS_23_KEY_NOT_EXISTS;
     break;

  case EENDFILE:
     r = TCB_STATUS_10_END_OF_FILE;
     break;

  case EPERM:
     r = TCB_STATUS_37_PERMISSION_DENIED;
     break;

  case EACCES:
     r = TCB_STATUS_37_PERMISSION_DENIED;
     break;

  case EISDIR:
     r = TCB_STATUS_37_PERMISSION_DENIED;
     break;

  case EDUPL:
     r = TCB_STATUS_22_KEY_EXISTS;
     break;

  case EKEXISTS:
     r = TCB_STATUS_22_KEY_EXISTS;
     break;

  case ENOENT:
     r = TCB_STATUS_35_NOT_EXISTS;
     break;

  case ENOCURR:
     if (enumber != TCB_STATUS_10_END_OF_FILE) {
        r = TCB_STATUS_21_KEY_INVALID;
     }
     break;

  case ELOCKED:
     r = TCB_STATUS_51_RECORD_LOCKED;
     break;

  case EFLOCKED:
     r = TCB_STATUS_61_FILE_SHARING;
     break;
     
  default:
     r = TCB_STATUS_99_UNKNOWN;
     break;
  }

  return r;
}
