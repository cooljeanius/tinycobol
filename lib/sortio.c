/*
 * Copyright (C) 2007        Rildo Pragana, David Essex.
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
 * TinyCOBOL Run Time Library -- Sort I/O functions
 * 
 
*/

#include "htcoblib.h"
#include "fileio.h" 
#include "filebdb.h"
#include "sortio.h"

/* extern struct fld_desc _generic_4binary; */

/*
//#define DEBUG_SORTIO_RTS0   1  // Open - Close 
//#define DEBUG_SORTIO_RTS1   1  // SORT release 
//#define DEBUG_SORTIO_RTS2   1  // SORT return  
//#define DEBUG_SORTIO_RTS3   1  // SORT using   
//#define DEBUG_SORTIO_RTS4   1  // SORT giving  
*/

extern void save_status (struct file_desc *f, int status);
extern int tcob_save_status(char *status, int rt);

#define db_open dbopen

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_sort_open                                |
 |                                                                        |
\*------------------------------------------------------------------------*/
int tcob_sort_open(struct file_desc *f, char *fname)  
{
  int r=0 /*, len */ /*, fdbp */ ;
  int sflags = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH; 
  int oflags = O_CREAT | O_TRUNC  | O_RDWR;
  char *filename /*, *fn */;
  bdb_sortfile *fbdb;  
  //DB *fdbpx;  
  DBTYPE type;
  BTREEINFO xkey;
//  va_list args;

#if defined(__MINGW32__) || defined(__CYGWIN__)
  oflags |= O_BINARY;
#endif

  f->dbp = NULL;
  type = DB_BTREE;

  xkey.flags      = R_DUP;
  xkey.cachesize  = 0;
  xkey.maxkeypage = 0;
  xkey.minkeypage = 0;
  xkey.psize      = 0;
  xkey.compare    = NULL;
  xkey.prefix     = NULL;
  xkey.lorder     = 0;

  f->flags.eof_hit = 0;

#ifdef DEBUG_FILEDBIO_RTS0
  fprintf(stderr, "debug : tcob_sort_open 0040.040 : fname=%s, oflags=%d, sflags=%d;\n", fname, oflags, sflags); 
#endif                                       

  filename = tcob_resolve_file_name(f, fname);
  if (filename == NULL) 
     RETURN_STATUS(99);

#ifdef DEBUG_SORTIO_RTS0
  fprintf(stderr, "debug : tcob_sort_open 0040.080 : filename=%s;\n", filename);
#endif                                       

/*
 sd = va_arg(args, char *);
 for(key_num=0; key_num <(strlen(sd)/2); key_num++) {
    fld[key_num] = va_arg(args, char *);
 }
 
 va_end(args);
*/

/*
  // FIXME: file suffix should be user defined //
  // Open sequential data file //
  fdbp = open(filename, oflags, sflags);
  if (fdbp == -1) {
#ifdef DEBUG_SORTIO_RTS0
     fprintf(stderr, "debug : tcob_sort_open 0040.120 : fdbp == -1\n");
#endif                                       
     free(filename);
     f->dbp=0;
     r = 99;
     RETURN_STATUS(r);
  }
*/ 
 
/*
  // File IO record buffers - not used
  r = tcob_allocate_fbuffers(f, 3, f->reclen * 2);
  if (r != 0) {
     r = 99;
     RETURN_STATUS(r);
  }
*/

  //len = strlen(filename);
  //fn = (char *)malloc((sizeof(char) * len) + 10);

  fbdb = tcob_allocate_sbdb(filename, SBDB_FILE_SUFFIX_BDBINDEX);
  if (fbdb == NULL) 
     RETURN_STATUS(99);

  /* FIXME: file suffix should be user defined */
  /* Open BDB index file */
  //strncpy(fn, filename, len + 1);
  /* strncat(fn, ".dbx", 5);  // Temporary patch */
  //fdbpx = db_open(fn, oflags, sflags, type, &xkey);
  /* Open BDB index file */
  fbdb->fdbpx = db_open(fbdb->fdbxname, oflags, sflags, type, &xkey);
  if (fbdb->fdbpx == NULL) {
//  free(fn);
//  free(filename);
//  if (fdbpx == NULL) {
#ifdef DEBUG_SORTIO_RTS0
     fprintf(stderr, "debug : tcob_sort_open 0040.120 : fdbpx == NULL\n");
#endif                                       
     /* close(fdbp); // Temporary patch */
     r = 91;
     if (errno == EINVAL) {
        r = 37;
     }
     if (errno == ENOENT) {
        r = 35;
     }
     tcob_free_sbdb(fbdb);
     //f->dbpx = NULL; 
     f->dbp = NULL; 
     RETURN_STATUS(r);
  }

  //f->recloc = -1;
  /* f->dbp = (void *)fdbp; // Temporary patch */
  //f->dbpx = (void *)fdbpx;
  f->dbp = (void *)fbdb;

  /* save mode to check later  */
  f->open_mode = TCB_FILE_OPEN_MODE_IO;
  /* save the file in the list of open files for the proces */
  tcob_add_file_list(f);
        
#ifdef DEBUG_SORTIO_RTS0
  fprintf(stderr, "debug : tcob_sort_open 0040.220 : r=%d;\n", r);
#endif                                       

  RETURN_STATUS(r);        
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_sort_close                               |
 |                                                                        |
\*------------------------------------------------------------------------*/
int tcob_sort_close(struct file_desc *f)  
{
  int r=0 /*, fdbp */;
  DB *fdbpx;
  bdb_sortfile *fbdb;  

#ifdef DEBUG_FILEDBIO_RTS0
  fprintf(stderr, "debug : tcob_sort_close : 0150.020 : r=%d\n", r); 
#endif                                       

  if (f->dbp == NULL)
     return (99);
  fbdb = (bdb_sortfile *)f->dbp;  

  /* Close BDB index file */
  //fdbpx = (DB *)f->dbpx;
  fdbpx = fbdb->fdbpx;
  fdbpx->close(fdbpx);
  //f->dbpx = NULL;

  /* Close sequential data file */
  /* fdbp = (int)f->dbp; // Temporary patch */
  /* close(fdbp); // Temporary patch */
  f->dbp = NULL;
  tcob_free_sbdb(fbdb);

  /* Free file IO record buffers - not used */
  /* r = tcob_free_fbuffers(f); */
  
  if (r == 0) 
     tcob_remove_file_list(f);

#ifdef DEBUG_FILEDBIO_RTS0
  fprintf(stderr, "debug : tcob_sort_close : 0150.120 : r=%d\n", r); 
#endif                                       

  RETURN_STATUS(r);        
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_sort_release                             |
 |                                                                        |
\*------------------------------------------------------------------------*/
int tcob_sort_release(struct file_desc *f, char *record, struct fld_desc *reclen_desc, char *reclen_buf, char *sd, ...) 
{
  int result, reclen, /* fdbp, */ r=0;
  DB *fdbpx;
  bdb_sortfile *fbdb;  
  DBT key, data;
  char *key1, *key_ptr;
  unsigned int i;
  va_list args;
  
  if (f->dbp == NULL)
     RETURN_STATUS(99);  
  fbdb = (bdb_sortfile *)f->dbp;

  /* fdbp = (int)f->dbp; // Temporary patch  */
  //fdbpx = (DB *)f->dbpx;
  if (fbdb->fdbpx == NULL) 
     RETURN_STATUS(99);
  fdbpx = (DB *)fbdb->fdbpx;
 
  // Set the record data
  data.data = record;
  // Set the record length data  
  if (reclen_desc != NULL) {                
     tcob_move(reclen_desc, reclen_buf, &_generic_4binary, (char *)&reclen);     
  }
  else {
     reclen = f->reclen;
  }
  data.size = reclen;
  
#ifdef DEBUG_SORTIO_RTS1
  fprintf(stderr, "debug : tcob_sort_release 0090.040 : reclen=%d;\n", reclen);
  {
   int i, ilen=reclen;
   fprintf(stderr, "debug : tcob_sort_release 0090.045 : record(%d)=", ilen);
   for (i=0; i<ilen; i++) {      
       fprintf(stderr, "%c", *(record + i));
   }
   fprintf(stderr, ";\n");
  }
#endif                                       
  key_ptr = key1 = (char *) malloc (f->reclen);
  va_start(args, sd);
  for(i=0; sd[i]; i+=2) {
     unsigned int element_size = (unsigned char) sd[i+1];
     char *fld = va_arg(args, char *);

     memcpy (key_ptr, fld, element_size);
#ifdef DEBUG_SORTIO_RTS1
     {
      int i, ilen=element_size;
      fprintf(stderr, "debug : tcob_sort_release 0090.060 : fld(%d)=", ilen);
      for (i=0; i<ilen; i++) {      
          fprintf(stderr, "%c", *(fld + i));
      }
      fprintf(stderr, ";\n");
     }
#endif                                       
     if (sd[i] == 2) {
     /* If the key is descending then for each character we
        perform a binary complement giving the final value.
        This way we can combine the Ascending and Descending 
        Keys into one long key. The result is the final key and
        saves us from having to run sort. 
     */
        unsigned int j;
        for (j=0; j<element_size; j++)
             key_ptr[j] = ~ key_ptr[j];
     }
     key_ptr += element_size;
  }
  va_end(args);
  
  key.data = key1;
  key.size = key_ptr - key1;
  
  result = fdbpx->put(fdbpx, &key, &data, 0);
#ifdef DEBUG_SORTIO_RTS1
  fprintf(stderr, "debug : tcob_sort_release 0090.100 : result=%d;\n", result);
  {
   int i, ilen=key.size;
   fprintf(stderr, "debug : tcob_sort_release 0090.105 : key.data(%d)=", ilen);
   for (i=0; i<ilen; i++) {      
       fprintf(stderr, "%c", *((char *)key.data + i));
   }
   fprintf(stderr, ";\n");
  }
#endif                                       
  if (result != 0) /* error */ 
     r=99;

  free (key1);
/*
  if (!result) // success 
     r=0;
  else // failure 
     r=99;
*/

#ifdef DEBUG_SORTIO_RTS1
  fprintf(stderr, "debug : tcob_sort_release 0090.120 : r=%d;\n", r);
#endif                                       

  RETURN_STATUS(r);
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_sort_return                              |
 |                                                                        |
\*------------------------------------------------------------------------*/
int tcob_sort_return(struct file_desc *f, char *record, struct fld_desc *reclen_desc, char *reclen_buf) 
{
  int result, /* fdbp, */ reclen, r=0;
  DBT key, data;
  DB *fdbpx;        
  bdb_sortfile *fbdb;  
  int flags=R_NEXT;

  if (f->dbp == NULL)
     RETURN_STATUS(99);  
  fbdb = (bdb_sortfile *)f->dbp;
  /* fdbp = (int)f->dbp; // Temporary patch  */
  if (fbdb->fdbpx == NULL) 
     RETURN_STATUS(99);
  //fdbpx = (DB *)f->dbpx;
  fdbpx = (DB *)fbdb->fdbpx;

  result = fdbpx->seq(fdbpx, &key, &data, flags);
#ifdef DEBUG_SORTIO_RTS2
  fprintf(stderr, "debug : tcob_sort_return 0150.040 : result=%d: \n", result);
#endif                                       
  if (result != 0) 
     RETURN_STATUS(10);
#ifdef DEBUG_SORTIO_RTS2
     {
      int i, ilen=key.size;
      fprintf(stderr, "debug : tcob_sort_return 0150.045 : key.data(%d)=", ilen);
      for (i=0; i<ilen; i++) {      
          fprintf(stderr, "%c", *((char *)key.data + i));
      }
      fprintf(stderr, ";\n");
     }
#endif                                       

     reclen = (int)data.size;

     if (result != 0) {
        //RETURN_STATUS(10);
        r = 10;
     }
     else {
        if (reclen < f->reclen) {
            r = 10;
        }
        else {
            // If variable length file move record length data to decriptor 
            if (reclen_desc != NULL) 
               tcob_move(&_generic_4binary, (char *)&reclen, reclen_desc, reclen_buf);     
            
            memmove(record, data.data, reclen);
        }
#ifdef DEBUG_SORTIO_RTS2
        fprintf(stderr, "debug : tcob_sort_return 0150.080 : reclen=%d: \n", reclen);
        {
         int i, ilen=reclen;
         if (reclen < 1000) {
            fprintf(stderr, "debug : tcob_sort_return 0150.085 : record(%d)=", ilen);
            for (i=0; i<ilen; i++) {      
                fprintf(stderr, "%c", *(record + i));
            }
            fprintf(stderr, ";\n");
         }
        }
#endif                                       
  }
  
#ifdef DEBUG_SORTIO_RTS2
  fprintf(stderr, "debug : tcob_sort_return 0150.120 : r=%d: \n", r);
#endif                                       

  RETURN_STATUS(r);
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_sort_using                               |
 |                                                                        |
\*------------------------------------------------------------------------*/
int tcob_sort_using(struct file_desc *f1, char *fname1, ...) 
{
  int result, idx, r=0;
  int sflags=S_IRUSR | S_IWUSR; 
  int oflags = O_RDONLY;
  DB *fdbpx;        
  bdb_sortfile *fbdb;  
  DBT key, data;
  unsigned int cnt;
  unsigned int file_num=0;
  unsigned int key_num;
  struct fld_desc *reclen_desc;
  char *reclen_buf;
  struct file_desc *temp_f;
  char *temp_fname;
  struct file_desc *sort_file;
  char *sd;
  char *record, *rec=NULL;
  struct file_desc *f[TCOB_MAX_PATHLN];
  char *fname[TCOB_MAX_PATHLN];
  char *fld[TCOB_MAX_PATHLN];
  char *filename;
  va_list args;

#if defined(__MINGW32__) || defined(__CYGWIN__)
  oflags |= O_BINARY;
#endif

// struct fld_desc *reclen_desc, char *reclen_buf

#ifdef DEBUG_SORTIO_RTS3
  fprintf(stderr, "debug : tcob_sort_using 0180.020 : \n");
#endif                                       

  va_start(args, fname1);

  f[file_num]=f1;
  fname[file_num]=fname1;
  temp_f=f1;
  while (temp_f != NULL) {
    temp_f = va_arg(args, struct file_desc *);
    if (temp_f == NULL)
       break;
    temp_fname = va_arg(args, char *);
    file_num++;
    f[file_num]=temp_f;
    fname[file_num]=temp_fname;
  }
 
  sort_file = va_arg(args, struct file_desc *);
  record = va_arg(args, char *);
  reclen_desc = va_arg(args, struct fld_desc *);
  reclen_buf = va_arg(args, char *);
 
  sd = va_arg(args, char *);
  for(key_num=0; key_num <(strlen(sd)/2); key_num++) {
     fld[key_num] = va_arg(args, char *);
  }
 
  va_end(args);

  if (sort_file->dbp == NULL)
     return 99;

  fbdb = (bdb_sortfile *)sort_file->dbp;
  if (fbdb->fdbpx == NULL) 
     return 99;
  fdbpx = (DB *)fbdb->fdbpx;

  for (cnt=0; cnt<=file_num; cnt++) {        
     filename=NULL;
     unsigned int adjusted_reclen;
     int len;

     filename = tcob_resolve_file_name(f[cnt], fname[cnt]);
#ifdef DEBUG_SORTIO_RTS3
     fprintf(stderr, "debug : tcob_sort_using 0165.040 : filename=%s;\n", filename);
#endif                                       
     /* Fixme: unwind files */
     if (filename == NULL) 
        return 99;

     adjusted_reclen = f[cnt]->reclen;
#ifdef DEBUG_SORTIO_RTS3
     fprintf(stderr, "debug : tcob_sort_using 0165.060 : adjusted_reclen=%d, f[%d]->reclen=%d;\n", adjusted_reclen, cnt, f[cnt]->reclen);
#endif                                       

     if (f[cnt]->organization != TCB_FILE_ORGANIZATION_LINESEQUENTIAL) {
        f[cnt]->dbp = (void *)open(filename, oflags, sflags);
#ifdef DEBUG_SORTIO_RTS3
        fprintf(stderr, "debug : tcob_sort_using 0165.080 : filename=%s, f[%d]->dbp=%d;\n", filename, cnt, f[cnt]->dbp);
#endif                                       
        free(filename);
        if (!f[cnt]->dbp) {
            if (errno == EINVAL) {
               f[cnt]->dbp = NULL; 
               return 37;
            }
            if (errno == ENOENT) {
               f[cnt]->dbp = NULL; 
               return 35;
            }
            f[cnt]->dbp = NULL; 
            return 91;
        }
     }
     else {
        /* create read buffer which can include record delimiters CR, LF */
        rec = (char *) malloc(f1->reclen + 3);
        if (rec == NULL) {
           free(filename);
           return 91;
        }
        f[cnt]->dbp = (void *)fopen(filename, "r");
        free(filename);
        if (f[cnt]->dbp == NULL) {
           free(rec);
           return 91;
        }
        adjusted_reclen = adjusted_reclen + 2;
     }

#ifdef DEBUG_SORTIO_RTS3
     fprintf(stderr, "debug : tcob_sort_using 0165.120 : \n");
#endif                                       

     /*
     FIXME:
     This code will result in a error condition
     when EOF is reached, regarless.
     */ 
     result = 0;
     while (result == 0) {        
        unsigned int i;
        char *key1, *key_ptr;

        if (f[cnt]->organization != TCB_FILE_ORGANIZATION_LINESEQUENTIAL) {
           result = read((int)f[cnt]->dbp, record, adjusted_reclen);
//#ifdef DEBUG_SORTIO_RTS3
//         fprintf(stderr, "debug : tcob_sort_using 0165.220 : result=%d, adjusted_reclen=%d, f(cnt)=%d;\n", result, adjusted_reclen, cnt);
//#endif                                       
           if (result == 0) {
                close((int)f[cnt]->dbp);
                f[cnt]->dbp = NULL;        
                result = 99;
                break;        
           }
           if (result != f[cnt]->reclen) {
                close((int)f[cnt]->dbp);
                f[cnt]->dbp = NULL;
                result = 99;        
                return 30;        
           }
        }
        else {
           if (fgets(rec, adjusted_reclen, (FILE *)f[cnt]->dbp) == NULL) {
              fclose((FILE *)f[cnt]->dbp);
              f[cnt]->dbp = NULL;        
              result = 99;
              break;                           
           }
           else {
              /*                         
               remove trailing CR, LF and pad short record 
               length with blanks 
              */
              len = strlen(rec);
              idx = 0;
              while ((len > 0) && (idx < 2)) {
                if ((rec[len - 1] == '\r') || 
                    (rec[len - 1] == '\n')) {
                   rec[len - 1] = '\0';
                   len--;
                }
                idx++;
              }
              while (len <= f[cnt]->reclen) {
                   rec[len - 1] = ' ';
                   len++;
              }
              memcpy (record, rec, f[cnt]->reclen);
              result = f[cnt]->reclen;        
           }
        }
              
        data.data = record;
        data.size = f[cnt]->reclen;
//#ifdef DEBUG_SORTIO_RTS3
//      fprintf(stderr, "debug : tcob_sort_using 0165.240 : f[%d]->reclen=%d;\n", cnt, f[cnt]->reclen);
//#endif                                       

        key_ptr = key1 = (char *) malloc (f1->reclen);
        for(i=0; sd[i]; i+=2) {
            unsigned int element_size = (unsigned char) sd[i+1];

            memcpy (key_ptr, fld[i>>1], element_size);
            if (sd[i] == 2) {
            /* If the key is descending then for each 
               character we perform a binary complement
               giving the final value. This way we can
               combine the Ascending and Descending keys
               into one long key. The result is the final
               key and saves us from having to run sort.
            */
               unsigned int j;
               for (j=0; j<element_size; j++)
                   key_ptr[j] = ~ key_ptr[j];
            }
            key_ptr += element_size;
        }
        
        key.data = key1;
        key.size = key_ptr - key1;

        /* result = sort_file->dbp->put(sort_file->dbp, &key, &data, 0); */
        //fdbpx = (DB *)sort_file->dbpx;
        result = fdbpx->put(fdbpx, &key, &data, 0);
        free (key1);
        if (result) /* failure */
           return 99;
     }
     if (rec)
        free(rec);
  }

#ifdef DEBUG_SORTIO_RTS3
  fprintf(stderr, "debug : tcob_sort_using 0165.920 : \n");
#endif                                       

  return r;
}

/*------------------------------------------------------------------------*\
 |                                                                        |
 |                          tcob_sort_giving                              |
 |                                                                        |
\*------------------------------------------------------------------------*/
int tcob_sort_giving (struct file_desc *f1, char *fname1, ...) 
{
  int result, r=0;
  int sflags=S_IRUSR | S_IWUSR;
  DB *fdbpx;        
  bdb_sortfile *fbdb;  
  DBT key, data;
  int flags=R_NEXT;
  struct file_desc *f[TCOB_MAX_PATHLN];
  char *fname[TCOB_MAX_PATHLN];
  int file_num=0;
  int cnt=0;
  struct fld_desc *reclen_desc;
  char *reclen_buf;
  char *temp_fname;
  struct file_desc *temp_f;
  char *filename;
  struct file_desc *sort_file;
  char *record, **rec, *pt;
  int len;
  va_list args;

#ifdef DEBUG_SORTIO_RTS4
  fprintf(stderr, "debug : tcob_sort_giving 0380.040 : \n");
#endif                                       
  va_start(args, *fname1);
  f[file_num]=f1;
  fname[file_num]=fname1;
  temp_f=f1;
  while (temp_f !=NULL) {
      temp_f = va_arg(args, struct file_desc *);
      if (temp_f == NULL)
              break;
      temp_fname = va_arg(args, char *);
      file_num++;
      f[file_num]=temp_f;
      fname[file_num]=temp_fname;
  }
  sort_file = va_arg(args, struct file_desc *);
  record = va_arg(args, char *);
  reclen_desc = va_arg(args, struct fld_desc *);
  reclen_buf = va_arg(args, char *);
  va_end(args);

  if (sort_file->dbp == NULL)
     return 99;

  fbdb = (bdb_sortfile *)sort_file->dbp;
  if (fbdb->fdbpx == NULL) 
     return 99;
  fdbpx = (DB *)fbdb->fdbpx;

/*
  Bug fix for zero size rec pointer array being
  allocated when there is just one file.

  rec = (char **) malloc(sizeof(char*) * file_num);
*/
  rec = (char **) malloc(sizeof(char*) * (file_num + 1));
  for (cnt=0; cnt <= file_num; cnt++) {
     int oflags = O_CREAT | O_TRUNC | O_RDWR;

#if defined(__MINGW32__) || defined(__CYGWIN__)
     oflags |= O_BINARY;
#endif

     filename = tcob_resolve_file_name(f[cnt], fname[cnt]);
#ifdef DEBUG_SORTIO_RTS4
     fprintf(stderr, "debug : tcob_sort_giving 0380.080 : filename=%s;\n", filename);
#endif                                       
     if (filename == NULL) 
        return 99;
/*
     // 
      beware: 
      fname points to a field storage (non null-terminated) 
      we must copy fname to a C string and terminate it with a \0
      and also trim spaces at the end. 
     //
     len = f[cnt]->fname_desc->len;
     filename = malloc(len+1);
     memmove(filename,fname[cnt],len);
     do {
        filename[len--] = 0;
     } while (filename[len] == ' ');
*/
     if (f[cnt]->organization != TCB_FILE_ORGANIZATION_LINESEQUENTIAL) {
        rec[cnt] = NULL;
     }
     else {
        rec[cnt] = (char*)malloc(f[cnt]->reclen + 3);
     }
     f[cnt]->dbp = (void *)open(filename, oflags, sflags);
     free(filename);
     if (!f[cnt]->dbp) {
        if (errno == EINVAL) {
           f[cnt]->dbp = NULL; 
           return 37;
        }
        if (errno == ENOENT) {
           f[cnt]->dbp = NULL; 
           return 35;
        }
        f[cnt]->dbp = NULL; 
           return 91;
     }
     result = 0;
  }
  result = 0;
  while(result == 0) {        
     /* result = sort_file->dbpx->seq(sort_file->dbpx, &key, &data, flags); */
     //fdbpx = (DB *)sort_file->dbpx;
     result = fdbpx->seq(fdbpx, &key, &data, flags);
     if (result) {
        result = 10;
        break;
     }
     if ((int)data.size < sort_file->reclen) {
        result = 10;
        break;
     }
     memmove (record, data.data, sort_file->reclen);
     for (cnt=0; cnt <= file_num; cnt++) {
        if (f[cnt]->organization != TCB_FILE_ORGANIZATION_LINESEQUENTIAL) {
            result = write((int)f[cnt]->dbp, record, f[cnt]->reclen);
            if (!result)
                return 99;
            else
                result = 0;
        }
        else {
            memmove (rec[cnt], record, f[cnt]->reclen);
            len = f[cnt]->reclen;
            pt = rec[cnt];
            pt[len--] = '\0';
            while ((pt[len] == ' ') && (len >= 0))  {
                 pt[len] = '\0';
                 len--;
            }
            len = strlen(pt);
            pt[len++] = '\n';
            pt[len] = '\0';
            result = write((int)f[cnt]->dbp, rec[cnt], len);
            if (!result)
               return 99;
            else
                result = 0;
        } 
     }
  }
  if (result != 10)
     return 99;
  for (cnt=0; cnt <= file_num; cnt++) {
        if (f[cnt]->dbp != NULL) {
           close((int)f[cnt]->dbp);
           f[cnt]->dbp = NULL;
        }
        if (rec[cnt] != NULL) {
           free(rec[cnt]); 
           rec[cnt] = NULL;
        }
  }
  free(rec); 

  return r;
}

bdb_sortfile* tcob_allocate_sbdb(char *filename, char *isuffix)
{
  int len;
  bdb_sortfile *fbdb;  

  fbdb = malloc(sizeof(bdb_sortfile));
  if (fbdb == NULL) 
     return (NULL);

  len = strlen(filename);

  fbdb->fdbxname = (char *)malloc((sizeof(char) * len) + 10);
  if (fbdb->fdbxname == NULL) { 
     free(fbdb->fdbxname);
     free(fbdb);
     return (NULL);
  }
  strncpy(fbdb->fdbxname, filename, len + 1);
  /* strncat(fbdb->fdbxname, STR_PERIOD, 1); */
  /* strncat(fbdb->fdbxname, isuffix, 5); */

  return fbdb;
}

void tcob_free_sbdb(bdb_sortfile *fbdb)
{
  
  if (fbdb != NULL) { 
     if (fbdb->fdbxname != NULL) 
        free(fbdb->fdbxname);
     free(fbdb);
  }

}

/* EOF sortio.c */
