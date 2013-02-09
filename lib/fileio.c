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
 * TinyCOBOL Run Time Library -- File handling functions
 * 

*/

#include "htcoblib.h"
#include "fileio.h"

/*
//#define DEBUG_FILEIO_RTS0 1  // Debug open and close files 
//#define DEBUG_FILEIO_RTS1 1  // Debug sequential files 
//#define DEBUG_FILEIO_RTS2 1  // Debug line-sequential files 
//#define DEBUG_FILEIO_RTS3 1  // Debug relative files 
//#define DEBUG_FILEIO_RTS9 1  // Debug exception code 
*/

#ifdef  USE_MF_COMPATABILITY
#define TCOB_EXTERNFILE_MFCOMP  1
#endif

int ignore_lock=0;
int need_lock=0;

/*
//
// Save file status
//
*/
//static void save_status (struct file_desc *f, int status)
void save_status (struct file_desc *f, int status)
{
  f->file_status[0] = status / 10 + '0';
  f->file_status[1] = status % 10 + '0';
}

/*
//
// Save file status
//
*/
int tcob_save_status(char *status, int rt) 
{
  status[0] = rt/10+'0';
  status[1] = rt%10+'0';
  return rt;
}

#ifdef TCOB_EXTERNFILE_MFCOMP 

/*-----------------------------------------------------------*\
 *  map_file_name                                            *
 *                                                           *
 *  When the programmer wrote the COBOL SELECT statement,    *
 *  we assume he intended the User to define an Environment  *
 *  Variable that will tell the program where to find the    *
 *  file.                                                    *
 *                                                           *
 *  There are several possibilities:                         *
 *                                                           *
 *  1.  The programmer wants the User to specify the base    *
 *      directory for the data.  In this case, the           *
 *      programmer would have put something like             *
 *      "DATA/Stock/ProductFile" in the SELECT clause.       *
 *                                                           *
 *      In this case, we would expect the User to set an     *
 *      Environment Variable named "$DD_DATA".               *
 *      Example (i)                                          *
 *          DD_DATA=/usr/local/AccountsData                  *
 *          In this case, the full name of the file will     *
 *          be: /usr/local/AccountsData/Stock/ProductFile    *
 *                                                           *
 *      However, Users like to do dumb things so we also     *
 *      check to see whether they set up an environment      *
 *      Variable named "$DATA".                              *
 *      Example (ii)                                         *
 *          DATA=/u/Accts                                    *
 *          In this case, the full name of the file will     *
 *          be :  /u/Accts/Stock/ProductFile                 *
 *                                                           *
 *      (Note that these two examples prove that dumb Users  *
 *      always use shorter, less meaningful names than the   *
 *      theoretically possible intellegent User.)            *
 *                                                           *
 *  2.  The programmer wants the User to specify the full    *
 *      file name.  In this case, the programmer would have  *
 *      put something like "PRODUCTFILE" in his SELECT       *
 *      statement.                                           *
 *                                                           *
 *      In this case, we would like the User to have set     *
 *      up an Environment Variable named "$DD_PRODUCTFILE".  *
 *      Example (iii)                                        *
 *          DD_PRODUCTFILE=/u/Data/Stock/ProductFile         *
 *          In this case, the full name of the file will     *
 *          simply be : /u/Data/Stock/ProductFile            *
 *                                                           *
 *      Again, we need to cater for the less intelligent     *
 *      User, so we also check to see whether he named the   *
 *      Environment Variable "$PRODUCTFILE".                 *
 *      Example (iv)                                         *
 *          PRODUCTFILE=/ProductFile                         *
 *          In this case, the full name of the file will     *
 *          simply be : /ProductFile                         *
 *      (Note that example (iv) is a true to life example    *
 *      showing just how dumb Users can be.  It takes a      *
 *      truly ingenious kind of studidity to manage to       *
 *      set your data files up in the root directory.)       *
 *                                                           *
 *  3.  (a) The programmer wants to hard-code the name of    *
 *          file himself and hence will have something       *
 *          like "/Data/Stock/ProductFile" in his            *
 *          SELECT statement.                                *
 *      (b) The programmer really wanted the User to         *
 *          specify an Environment Variable, but the User    *
 *          stuffed up the installation process and there    *
 *          is no Environment Variable to be found.          *
 *                                                           *
 *      In this case, we can do nothing except to use the    *
 *      name the programmer typed in the SELECT statement    *
 *      as the actual name of the file.                      *
 *      That is, we actually look for a file called :        *
 *      "/Data/Stock/ProductFile".                           *
 *                                                           *
 *      (Note that in this case we can be confident that     *
 *      "/Data" is a separate partition and not a            *
 *      directory in the root partition - Yeah, sure!)       *
 *                                                           *
\*-----------------------------------------------------------*/
char *map_file_name(char *evname)
{
        int slash_pos;
        int len, lenDD, lenSuffix;
        char *file_name;
        char *evDataDir, *dataDir, *file_Suffix;

        file_name = NULL;

//        fprintf(stderr, "debug: map_file_name: LT_DIRSEP_STR=%s;\n", LT_DIRSEP_STR);  

        /* First we search through the file name specified
         * by the COBOL programmer and find the first
         * occurance of the character "/".
         * We will then use this to divide the name into
         * the "Data Directory" and the "File Suffix".
         * ( If there is no "/" in the name, then we treat
         * the entire name as the "Data Directory" and
         * assume a NULL File Suffix.  I know it sounds
         * crazy, but no less crazy than assuming a Null
         * Data Directory). 
         */
        slash_pos = strcspn(evname, LT_DIRSEP_STR);

        /* Now we cheat a little by setting file_suffix
         * to point to the same string as "evname",
         * but starting half way through.
         * This is naughty, and we must be careful that
         * we don't go changing the contents of evname.
         */
        file_Suffix = evname + slash_pos;
        lenSuffix = strlen(file_Suffix);

        /* Next we start forming up the name of the 
         * Environment Variable we wepect to find.
         * We allocate enough room to hold the
         * prefix for the environment variable 
         *  :-     "DD_"
         * as well as the "Name" and the terminating
         * Null character. 
         */
        evDataDir = malloc(slash_pos + 4);

        strncpy(evDataDir, "DD_", 3);
        strncpy(evDataDir + 3, evname, slash_pos);
        evDataDir[slash_pos + 3] = 0;

        /* Now lets see if the Environment Variable 
         * has been set up/
         */
        dataDir = getenv(evDataDir);

        /*  If we failed to find an environment variable named 
         *  "$DD_DataDir" then we don't give up yet...
         *
         *  We will see whether the User has defined an
         *  environment variable named "$DataDir".
         *  Obviously, To do this, we just drop the first three
         *  characters from "DD_DataDir".
         */
        if (dataDir == NULL)
                {
                evDataDir = evDataDir + 3;
                dataDir = getenv(evDataDir);
                }

        /*  If we found an environment variable containing the
         *  Data Directory, then we go ahead and use it.
         *  That is, we glue the file Suffix onto the end
         *  of the Data Directory to give us the full name
         *  of the file.
         */
        if (dataDir != NULL)
                {
                lenDD = strlen(dataDir);
                file_name = malloc(lenDD + lenSuffix + 1);
                strcpy(file_name, dataDir);
                strcpy(file_name + lenDD, file_Suffix);
                }

        else
                /*  If we failed to find an environment variable
                 *  containing the name of the Data Directory,
                 *  then we assume that the Programmer has
                 *  Hard-Coded the file name.
                 *  That is, we assume the name of the Environment
                 *  Variable is really the name of the file itself.
                 */
                {
                len = strlen(evname);
                file_name = malloc(len+1);
                strncpy(file_name,evname,len);
                file_name[len] = '\0';
                }

/*        fprintf(stderr, "debug: map_file_name: file_name=%s;\n", file_name); */

        return(file_name);

} 
#endif


/*
//
//  Resolve file name
//
*/
char *tcob_resolve_file_name(struct file_desc *f, char *fname)
{
  int len;
  char *filename=NULL, *evname=NULL, *pt;

  /*
  BEWARE: 
  fname points to a field storage (non null-terminated) 
  we must copy fname to a C string and terminate it with a '\0'
  and also trim spaces at the end. 

  NOTE: 
  The 'file_external' flag in the file structure 'struct file_desc'
  is used to indicate how the value stored in 'fname' is used.
  It can be used to define a filename variable or a environment
  variable.
  
  If the flag is set, then 'fname' is used as an environment 
  variable which is used to determined the actual filename.
  Else 'fname' is used to define a filename. 
  
  If no environment variable is found or is empty, then the 
  filename defaults to the value stored in 'fname'.
  
  Standard input/output/error files have the 'file_external' flag
  set on by default.
  The environment variables STANDARD_[INPUT | OUTPUT | ERROR] can be used 
  to override (redirect) these files.
  
  If an environment variable is found and is not empty, then the name in the 
  environment variable is used as a file name.

  If no environment variable is found or is empty, then these files defualt to
  standard input/output/error as defined by the originating program.
  
  
  */

//#ifdef DEBUG_FILEIO_RTS0
// fprintf(stderr, "debug : tcob_resolve_file_name 0260.020 : filename=%s, reclen=%d;\n", filename, f->reclen);
//#endif                                       

  if (f->flags.file_external == 0) {
     len = f->fname_desc->len;
     filename = malloc(len + 1);
     memmove(filename, fname, len);
     do {
        filename[len--] = 0;
     } while (filename[len] == ' ');
     evname = NULL;
  } 
  else {
//     len = f->fname_desc->len;
//     evname = malloc(len + 1);
     if (f->file_std_flag != 0)  {
        len = 23;
        evname = malloc(len + 1);
        memset(evname, '\0', len + 1);
        if (f->file_std_flag == TCB_FILE_STD_FLAG_INPUT)
            strncpy(evname, "STANDARD_INPUT", len);
        if (f->file_std_flag == TCB_FILE_STD_FLAG_OUTPUT)
            strncpy(evname, "STANDARD_OUTPUT", len);
        if (f->file_std_flag == TCB_FILE_STD_FLAG_ERROR)
            strncpy(evname, "STANDARD_ERROR", len);
     }
     else {
        len = f->fname_desc->len;
        evname = malloc(len + 1);
        memmove(evname, fname, len);
        do {
            evname[len--] = 0;
        } while (evname[len] == ' ');
     }

     /* Get environment variable, if it exists */
#ifdef TCOB_EXTERNFILE_MFCOMP 
     filename = map_file_name(evname);
#else
     if ((pt = getenv(evname)) != NULL) {
        len = strlen(pt);
        if (len > 0) {
           filename = malloc(len + 1);
           strncpy(filename, pt, len);
           /* Override standard input/output/error files by environment variable */
           f->file_std_flag  = TCB_FILE_STD_FLAG_NONE;
        } 
        else {
           len = strlen(evname);
           filename = malloc(len + 1);
           strncpy(filename, evname, len);
        }
     } 
     else {
        len = strlen(evname);
        filename = malloc(len + 1);
        strncpy(filename, evname, len);
     }
     filename[len] = '\0';
#endif
  }

  if (evname != NULL)
     free(evname);

#ifdef DEBUG_FILEIO_RTS0
 fprintf(stderr, "debug : tcob_resolve_file_name 0260.120 : filename=%s, len=%d;\n", filename, len);
#endif                                       
  
  return (filename);
} 

/*
//
// Open file
//
*/
int tcob_open(struct file_desc *f, char *fname, int mode) 
{
  int r;

  /* Check the correct structure */
  /*
  if (f->vers_id < RTL_FILE_VERSION) {
     fprintf(stderr, "You need to recompile your program\n");
     fprintf(stderr, "Version mismatch; structure %x, RTL %x\n", f->vers_id, RTL_FILE_VERSION);
     RETURN_STATUS(TCB_STATUS_99_UNKNOWN);
  } */

  /* Check to see if the file is already open */
  if (f->dbp != NULL)
     RETURN_STATUS(41);

  /* Resolve name to real file name */
  f->filename = tcob_resolve_file_name(f, fname);
#ifdef DEBUG_FILEIO_RTS0
  fprintf(stderr, "debug : tcob_open 0370.020 : filename=%s, reclen=%d;\n", f->filename, f->reclen);
#endif                                       
  if (f->filename == NULL) 
     RETURN_STATUS(TCB_STATUS_99_UNKNOWN);
  
  /* Select OPEN based on file organization */
  switch (f->organization)
  {
    case TCB_FILE_ORGANIZATION_INDEXED:
      r = tcob_open_idx(f, mode); 
      break;
    
    case TCB_FILE_ORGANIZATION_RELATIVE:
      r = tcob_open_rel(f, mode); 
      break;
    
    default:
      r = tcob_open_real(f, mode);
      break;
  }
    
  /* Save the file in the list of open files for the process */
  if (r == 0) { 
    tcob_add_file_list(f);
  }
  else {
    if (f->filename != NULL) {
       free(f->filename);
       f->filename = NULL;
    }
  }
  
  RETURN_STATUS(r);
}

/*
//
// Open file - real
//
*/
int tcob_open_real(struct file_desc *f, int mode) 
{
  int sflags = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH; 
  int oflags=0;
  tcb_fileio_handle *h;
  int r=0;
   
  /* Initialize file structure */
  f->open_mode = 0;
  /* f->recloc = TCB_FILE_RECORD_LOCATION_UNDEFINED; */
  f->flags.read_done = 0;
  f->flags.eof_hit = 0;
  f->flags.file_missing = 0;
  f->flags.init_done = 0;
  f->flags.start_record = 0; 

#ifdef DEBUG_FILEIO_RTS0
  fprintf(stderr, "debug : tcob_open_real 0370.010 : f->flags file_external=%d, eof_hit=%d, file_printer=%d, file_std_flag=%d;\n", 
                        f->flags.file_external, f->flags.eof_hit, f->flags.file_printer, f->file_std_flag);
#endif                                       

          
  switch (mode) {

    case TCB_FILE_OPEN_MODE_INPUT: 
        /* Standard output type files do not support INPUT mode */
        if ((f->file_std_flag == TCB_FILE_STD_FLAG_OUTPUT) || 
            (f->file_std_flag == TCB_FILE_STD_FLAG_ERROR))
           return (99);
        oflags = O_RDONLY; 
        break;
    case TCB_FILE_OPEN_MODE_IO: 
        /* Line Sequential does not Support Mode IO */
        if (f->organization == TCB_FILE_ORGANIZATION_LINESEQUENTIAL)
           return (37);
        /* Standard input/output/error type files do not support IO mode */
        if (f->file_std_flag != 0)
           return (99);
        oflags = O_RDWR;
        if (f->flags.optional) 
           oflags = O_CREAT | O_RDWR;
        break;
    case TCB_FILE_OPEN_MODE_OUTPUT: 
        /* Standard input type files does not support OUTPUT mode */
        if (f->file_std_flag == TCB_FILE_STD_FLAG_INPUT) 
           return (99);
        /* BDB doesn't support O_WRONLY */ 
        //oflags = O_CREAT | O_TRUNC | O_RDWR; 
        oflags = O_CREAT | O_TRUNC | O_WRONLY; 
        break;
    case TCB_FILE_OPEN_MODE_EXTEND: 
        /* Standard input type files does not support OUTPUT mode */
        if (f->file_std_flag == TCB_FILE_STD_FLAG_INPUT) 
           return (99);
        oflags =  O_RDWR | O_APPEND;
        if (f->flags.optional)
            oflags = O_CREAT | O_RDWR | O_APPEND;
        break;
  }

#if defined(__MINGW32__) || defined(__CYGWIN__)
  oflags |= O_BINARY;
#endif

#ifdef DEBUG_FILEIO_RTS0
 fprintf(stderr, "debug : tcob_open 0370.040 : filename=%s, f->fname_desc->len=%d, mode=%d, oflags=%d, sflags=%d;\n", f->filename, f->fname_desc->len, mode, oflags, sflags);
#endif                                       

 switch (f->organization)
 {

   case TCB_FILE_ORGANIZATION_LINESEQUENTIAL:
     h = tcob_allocate_fhandle(1, f->reclen * 2);
     if (h == NULL) {
        r = 99;
     }
     else {
        h->uval.fh = NULL; 
        h->recloc = TCB_FILE_RECORD_LOCATION_UNDEFINED;
        if (mode == TCB_FILE_OPEN_MODE_INPUT) {
           if (f->file_std_flag == TCB_FILE_STD_FLAG_INPUT) { 
              h->uval.fh = stdin;
           }
           else {
              //h->rfilename = fname;
              h->uval.fh = fopen(f->filename, "r");
           }
        }
        else {
           if ((f->file_std_flag == TCB_FILE_STD_FLAG_ERROR) ||
               (f->file_std_flag == TCB_FILE_STD_FLAG_OUTPUT))
           {
              if (f->file_std_flag == TCB_FILE_STD_FLAG_OUTPUT)
                 h->uval.fh = stdout;
              if (f->file_std_flag == TCB_FILE_STD_FLAG_ERROR)
                 h->uval.fh = stderr;
           }
           else {
              //h->rfilename = fname;
              h->uval.fh = fopen(f->filename, "w");
           }
        }
     }
     /* FIX ME - add proper file IO status codes */
     if (h->uval.fh == NULL) { 
        tcob_free_fhandle(h);
        if (f->flags.optional && mode == TCB_FILE_OPEN_MODE_INPUT) {
           f->flags.file_missing = 1;
        } 
        else {
           /*r = 99; */
           r = 91;
           if (errno == EINVAL) 
              r = 37;
           if (errno == ENOENT) 
              r = 35;
        }
     }
     break;
   
   case TCB_FILE_ORGANIZATION_SEQUENTIAL:

     h = tcob_allocate_fhandle(1, f->reclen * 2);
     if (h == NULL) {
        r = 99;
     }
     else {
        //h->rfilename = fname;
        h->recloc = TCB_FILE_RECORD_LOCATION_UNDEFINED;
        if (f->file_std_flag != 0) {
           if (f->file_std_flag == TCB_FILE_STD_FLAG_INPUT)
              h->uval.fi = 0;
           if (f->file_std_flag == TCB_FILE_STD_FLAG_OUTPUT)
              h->uval.fi = 1;
           if (f->file_std_flag == TCB_FILE_STD_FLAG_ERROR)
              h->uval.fi = 2;
        }
        else {
           h->uval.fi = open(f->filename, oflags, sflags);
           if (h->uval.fi == TCB_FILE_OPEN_ERROR) {
              tcob_free_fhandle(h);
              if (f->flags.optional && mode == TCB_FILE_OPEN_MODE_INPUT) {
                 f->flags.file_missing = 1;
              } 
              else {
                 r = 99;
                 if (errno == EINVAL) 
                    r = 37;
                 if (errno == ENOENT) 
                    r = 35;
              }
           }
        }
     }
     break;

   /* Otherwise it is an error */
   case TCB_FILE_ORGANIZATION_RELATIVE:
   case TCB_FILE_ORGANIZATION_INDEXED:
   default:
     r = 99; 
     break;


 }
 
// if (r == 0) {
//    if (f->flags.file_missing == 0) 
 if ((r == 0) && (f->flags.file_missing == 0)) 
    f->dbp = (void*)h;
 else 
    f->dbp = NULL;
 
 /* save mode to check later (read,write,start,...) */
 f->open_mode = mode;


#ifdef DEBUG_FILEIO_RTS0
 fprintf(stderr, "debug : tcob_open 0370.080 : filename=%s, r=%d;\n", f->filename, r);
#endif                                       

 return r;
}

/*
//
// CLose file
//
*/
int tcob_close(struct file_desc *f) 
{
 int r;

 /* Close file and free buffers if requird */
 r = tcob_close_real(f);
 /* Remove file from Run-Time open files list */
 if (r == 0) 
    tcob_remove_file_list(f);

 RETURN_STATUS(r);
}

/*
//
// Close file - real
//
*/
int tcob_close_real(struct file_desc *f) 
{
  int r=0;
  //unsigned char file_organization;
  tcb_fileio_handle *h;

  f->flags.read_done = 0;
  
  /* COBOL 85 Standard : Check if file is open and return FILE-STATUS 42 on FALSE */ 
  if (f->dbp == NULL) {
     if (f->flags.optional && f->flags.file_missing) 
        return (0);
     return (42);
  }

  h = (tcb_fileio_handle *)f->dbp;
  
  if (f->flags.optional && f->flags.file_missing) {
     if (f->filename != NULL) {
        free(f->filename);
        f->filename = NULL;
     }  
     tcob_free_fhandle(h);
     f->dbp = NULL;
     return r;
  }
  
  switch (f->organization)
  {
    case TCB_FILE_ORGANIZATION_INDEXED:
      r = tcob_close_idx(f);
      break;    
    
    case TCB_FILE_ORGANIZATION_RELATIVE:
      r = tcob_close_rel(f);
      break;

    case TCB_FILE_ORGANIZATION_LINESEQUENTIAL:
      if (f->file_std_flag == TCB_FILE_STD_FLAG_NONE)
         fclose(h->uval.fh);
      tcob_free_fhandle(h);
      break;
    
    /* File is SEQUENTIAL */
    default:
      if (f->file_std_flag == TCB_FILE_STD_FLAG_NONE)
         close(h->uval.fi);
      tcob_free_fhandle(h);
      break;
  }
    
  if (r == 0) {
     if (f->filename != NULL) {
        free(f->filename);
        f->filename = NULL;
     }  
     f->dbp = NULL;
  }
  
  return r;
}

/*
//
// 
//
*/
int tcob_file_init(struct file_desc *f) 
{
#ifdef DEBUG_RTS
        fprintf(stderr, "file_init: \n");
#endif
        tcob_close(f);
        f->open_mode = 0;
        f->flags.file_missing = 0;
        return 0;
}

/*
//
// Set file lock
//
*/
void tcob_setlock() 
{
  /* this just make aware we need to lock current record, used before a read */
  need_lock = 1;
}

/*
//
// Set record lock
// 
*/
/* static int tcob_lock_record(int fd, int len) */
int tcob_lock_record(int fd, int len) 
{
#if defined(__MINGW32__)
   return -1;      
#else
#ifdef HAVE_FCNTL
   struct flock lk;
   lk.l_type = F_WRLCK;
   lk.l_whence = SEEK_CUR;
   lk.l_start = 0;
   lk.l_len = len;
   lk.l_pid = getpid();
   need_lock = 0;
   return (fcntl(fd,F_SETLK,&lk));        
#else
   return -1;      
#endif
#endif
}

/*
//
// Unlock file record
//
*/
void tcob_unlock_record(struct file_desc *f) 
{
#if defined(__MINGW32__)
   return; 
#else
#ifdef HAVE_FCNTL
   {
   struct flock lk;
   lk.l_type = F_UNLCK;
   lk.l_whence = SEEK_CUR;
   lk.l_start = 0;
   lk.l_len = f->reclen;
   lk.l_pid = getpid();
   fcntl((int)f->dbp,F_SETLK,&lk);
   }        
#else
   return; 
#endif
#endif
}


/*
//
// Ignore file lock
//
*/
void tcob_ignorelock() 
{
 /* this just make aware we need to ignore locks on the current record, used before a read */
        ignore_lock = 1;
}

//+---------------------------------------------------------------------------------+
// Line-sequential are variable length files which use a <LF> as a record delimiter.                                                        
//                                                       
//+---------------------------------------------------------------------------------+
/*
//
// Read line-sequential file
//
*/
int tcob_read_lseq(struct file_desc *f, struct fld_desc *rectofrom_desc, char *rectofrom_buf, struct fld_desc *reclen_desc, char *reclen_buf) 
{
  int reclen, r=0;
  int ich;
  char *record;
  FILE *fdbp;
  tcb_fileio_handle *h;
 
  f->flags.read_done = 0;
  /* Check to see if file is open */
  if (f->dbp == NULL) {
      if (f->flags.optional && f->flags.file_missing) 
         RETURN_STATUS(TCB_STATUS_10_END_OF_FILE);        
      RETURN_STATUS(TCB_STATUS_47_INPUT_DENIED);
  }

  /* Check to see that the record length is valid */
  if (f->reclen == -1)
      RETURN_STATUS(TCB_STATUS_99_UNKNOWN);
  
  /* Check the mode the file is opened in to make sure that read is Allowed */
  if (((f->open_mode != TCB_FILE_OPEN_MODE_INPUT) && (f->open_mode != TCB_FILE_OPEN_MODE_IO)))
     RETURN_STATUS(TCB_STATUS_47_INPUT_DENIED);
  
  /* Check that we didn't already hit eof */
  if ((f->open_mode == TCB_FILE_OPEN_MODE_INPUT || f->open_mode == TCB_FILE_OPEN_MODE_IO) && f->flags.eof_hit)
     RETURN_STATUS(TCB_STATUS_46_READ_ERROR);
  
#ifdef DEBUG_FILEIO_RTS2
  fprintf(stderr, "debug : tcob_read_lseq 0945.060 : f->reclen=%d\n", f->reclen);
#endif                 

  h = (tcb_fileio_handle *)f->dbp;
  fdbp = h->uval.fh;
  record = h->buf->buf[0];

  reclen = 0;
  ich = 0;  
  memset(record, ' ', f->reclen);

  ich = fgetc(fdbp);
  while (ich != EOF) { 
    if (ich == '\n') {
       break;
    }
    if (ich != '\r') {
       if(reclen < f->reclen) 
         *(record+reclen) = (char)ich;
       reclen++;
    }
    ich = fgetc(fdbp);
  }

#ifdef DEBUG_FILEIO_RTS2
  fprintf(stderr, "debug : tcob_read_lseq 0945.120 : reclen=%d, f->reclen=%d\n", reclen, f->reclen);
#endif                 

  if (reclen > f->reclen)
      RETURN_STATUS(TCB_STATUS_99_UNKNOWN);
  /* Trap case where LF is omitted */
  if ((ich == EOF) && (reclen == 0))
     RETURN_STATUS(TCB_STATUS_10_END_OF_FILE); 

  /* Copy data to file and identifiers buffers */
  memset(f->record, ' ', f->reclen);
  memcpy(f->record, record, reclen);
  if (rectofrom_desc != NULL) {
     memset(rectofrom_buf, ' ', rectofrom_desc->len);
     if (rectofrom_desc->len > f->reclen) 
        memcpy(rectofrom_buf, record, f->reclen);
     else
        memcpy(rectofrom_buf, record, rectofrom_desc->len);
  }

  /* Copy variable length data */
  if (reclen_desc != NULL)                 
     tcob_move(&_generic_4binary, (char *)&reclen, reclen_desc, reclen_buf);             

  f->flags.read_done = 1;

#ifdef DEBUG_FILEIO_RTS2
  fprintf(stderr, "debug : tcob_read_lseq 0945.240 : reclen=%d\n", reclen);
  if (reclen > 0) {
    int i, ilen=reclen;
    fprintf(stderr, "debug : tcob_read_lseq 0945.245 : record=");
    for (i=0; i<ilen; i++) {      
      fprintf(stderr, "%c", *(record + i));
    }
    fprintf(stderr, ";\n");
  }
#endif                 

  RETURN_STATUS(r);
}

/*
//
// Write line-sequential file
//
*/
int tcob_write_lseq(struct file_desc *f, struct fld_desc *rectofrom_desc, char *rectofrom_buf, 
                    struct fld_desc *reclen_desc, char *reclen_buf) 
{
  int reclen, r=0, i;
  FILE *fdbp;
  tcb_fileio_handle *h;
  char *record;
  
  f->flags.read_done = 0;
  
  /* Check to see if file is open */
  if (f->dbp == NULL)
     RETURN_STATUS(TCB_STATUS_48_OUTPUT_DENIED);
  
  /* Check to see that the record length is valid */
  if (f->reclen == -1) 
     RETURN_STATUS(TCB_STATUS_99_UNKNOWN);
  
#ifdef DEBUG_FILEIO_RTS2
  fprintf(stderr, "debug : tcob_write_lseq 1200.080 : f->reclen=%d\n\n", f->reclen);
#endif

  /* Check the mode the file is opened in to make sure that write is permitted */
  if (((f->open_mode != TCB_FILE_OPEN_MODE_OUTPUT) && 
       (f->open_mode != TCB_FILE_OPEN_MODE_IO) && 
       (f->open_mode != TCB_FILE_OPEN_MODE_EXTEND)))
     RETURN_STATUS(TCB_STATUS_48_OUTPUT_DENIED);

  h = (tcb_fileio_handle *)f->dbp;
  fdbp = h->uval.fh;
  record = h->buf->buf[0];

  /* Copy write buffer data to record and FROM identifiers buffer */
  if (rectofrom_desc != NULL) {
     memset(f->record, ' ', f->reclen);
     if (rectofrom_desc->len > f->reclen) 
        memcpy(f->record, rectofrom_buf, f->reclen);
     else
        memcpy(f->record, rectofrom_buf, rectofrom_desc->len);
  }
  memcpy(record, f->record, f->reclen);
    
  /* If variable length record is defined  */
  if (reclen_desc != NULL) {

     /* Convert record to int type */
     tcob_move(reclen_desc, reclen_buf, &_generic_4binary, (char *)&reclen);     
#ifdef DEBUG_FILEIO_RTS2
     fprintf(stderr, "debug : tcob_write_lseq 1200.180 : reclen=%d, f->reclen=%d\n", reclen, f->reclen); 
#endif     
  
     /* Check that the record length is not greater than max */ 
     if (reclen > f->reclen)
        RETURN_STATUS(TCB_STATUS_99_UNKNOWN);

     /* Write the record with no trailing blanks truncation */
     for (i=0; i<reclen; i++) {
       fputc(*(record + i), fdbp);
     }
     /* Write the record delimiter 
     // A printer SEQUENTIAL file is equivalent to a LINE SEQUENTIAL file 
     */
     if (f->flags.file_printer == 1) {
        fputc('\r', fdbp);
        fputc('\n', fdbp);
     } 
     else {
        fputc('\n', fdbp);
     } 
  } 
  else {
     /* 
     //  Standard LS record with trailing blanks truncation 
     //  Determine length of record by truncating trailing blanks 
     */
     reclen = f->reclen;
     if (f->flags.file_printer == 0) {
        for(i=f->reclen - 1; i >= 0; i--) {
            if (*(record + i) != ' ') {
               reclen = i + 1;
     //        i = -1;
               break;
            }
        }
     } 
     /* Write the record */
     if(reclen > 0) {
       for (i=0; i<reclen; i++) {
         fputc(*(record + i), fdbp);
       }
     } 
     /* Write the record delimiter */
     if (f->flags.file_printer == 1) {
        fputc('\r', fdbp);
        fputc('\n', fdbp);
     } 
     else {
       fputc('\n', fdbp);
     } 
  } 
           
  RETURN_STATUS(r);
}

/*
//
// Write line-sequential file - advancing
//
*/
int tcob_write_adv_lseq(struct file_desc *f, struct fld_desc *rectofrom_desc, char *rectofrom_buf,  
                        int opt, 
                        struct fld_desc *cnt_desc, char *cnt_buf, 
                        struct fld_desc *reclen_desc, char *reclen_buf) 
{
  int i, r=0, len=0, lines=0;
  FILE *fdbp; 
  tcb_fileio_handle *h;
  char *record;

  /* Check to see if file is open */ 
  if (f->dbp == NULL)
     RETURN_STATUS(TCB_STATUS_48_OUTPUT_DENIED);
  
  /* Check the mode the file is opened in to make sure that write permitted */
  if (((f->open_mode != TCB_FILE_OPEN_MODE_OUTPUT) && 
       (f->open_mode != TCB_FILE_OPEN_MODE_IO) && 
       (f->open_mode != TCB_FILE_OPEN_MODE_EXTEND)))
     RETURN_STATUS(TCB_STATUS_48_OUTPUT_DENIED);

#ifdef DEBUG_FILEIO_RTS2
  fprintf(stderr, "debug : tcob_write_adv_lseq 0810.040 : f->reclen=%d\n", f->reclen); 
#endif     

  h = (tcb_fileio_handle *)f->dbp;
  fdbp = h->uval.fh;
  record = h->buf->buf[0];
  
  /* Copy write buffer data to record and FROM identifiers buffer */
  if (rectofrom_desc != NULL) {
     memset(f->record, ' ', f->reclen);
     if (rectofrom_desc->len > f->reclen) 
        memcpy(f->record, rectofrom_buf, f->reclen);
     else
        memcpy(f->record, rectofrom_buf, rectofrom_desc->len);
  }
  memcpy(record, f->record, f->reclen);

  f->flags.with_advancing = 1;
  f->flags.adv_before = 0;

#ifdef DEBUG_FILEIO_RTS2
  fprintf(stderr, "debug : tcob_write_adv_lseq 0810.060 : opt=%d, lines=%d\n", opt, lines); 
#endif     
  if (opt > 0) {
     if (cnt_desc != NULL) 
        lines = tcob_get_index(cnt_desc, cnt_buf);
#ifdef DEBUG_FILEIO_RTS2
  fprintf(stderr, "debug : tcob_write_adv_lseq 0810.070 : opt=%d, lines=%d\n", opt, lines); 
#endif     
  }

#ifdef DEBUG_FILEIO_RTS2
  fprintf(stderr, "debug : tcob_write_adv_lseq 0810.080 : len=%d\n", len); 
#endif     
  if (reclen_desc != NULL) {
     tcob_move(reclen_desc, reclen_buf, &_generic_4binary, (char *)&len);     
  }
  else {
     len = f->reclen;
  }

#ifdef DEBUG_FILEIO_RTS2
  fprintf(stderr, "debug : tcob_write_adv_lseq 0810.120 : len=%d\n", len); 
#endif     

  /* Remove trailling blanks */
  if (f->flags.file_printer == 0) {
     while (len > 0 && record[len-1] == ' ')
        len--;
  }
  
#ifdef DEBUG_FILEIO_RTS2
  fprintf(stderr, "debug : tcob_write_adv_lseq 0810.130 : len=%d\n", len); 
#endif     

  switch (opt)
  {
    /* 1: write record before advancing N lines */
    case 1:
#ifdef DEBUG_FILEIO_RTS2
      fprintf(stderr, "debug : tcob_write_adv_lseq 0810.210 : len=%d, lines=%d\n", len, lines); 
#endif     
      for (i=0; i<len; i++) 
        fputc(*(record + i), fdbp);
      fputc('\r', fdbp);
      for (i=lines; i>0; i--) 
          fputc('\n', fdbp);
      break;

    /* 2: write record after advancing N lines */
    case 2:
#ifdef DEBUG_FILEIO_RTS2
     fprintf(stderr, "debug : tcob_write_adv_lseq 0810.220 : len=%d, lines=%d\n", len, lines); 
#endif     
     for (i=lines; i>0; i--) 
          fputc('\n', fdbp);
      for (i=0; i<len; i++) 
        fputc(*(record + i), fdbp);
      fputc('\r', fdbp);
      break;

    /* -1: write record before advancing page */
    case -1:
#ifdef DEBUG_FILEIO_RTS2
      fprintf(stderr, "debug : tcob_write_adv_lseq 0810.230 : len=%d, lines=%d\n", len, lines); 
#endif     
      for (i=0; i<len; i++) 
        fputc(*(record + i), fdbp);
      fputc('\r', fdbp);
      fputc('\f', fdbp);
      break;

    /* -2: write record after advancing page */
    case -2:
#ifdef DEBUG_FILEIO_RTS2
      fprintf(stderr, "debug : tcob_write_adv_lseq 0810.240 : len=%d, lines=%d\n", len, lines); 
#endif     
      fputc('\f', fdbp);
      for (i=0; i<len; i++) 
        fputc(*(record + i), fdbp);
      fputc('\r', fdbp);
      break;

    /* write record before advancing 1 line */
    default:
#ifdef DEBUG_FILEIO_RTS2
      fprintf(stderr, "debug : tcob_write_adv_lseq 0810.260 : len=%d, lines=%d\n", len, lines); 
#endif     
      for (i=0; i<len; i++) 
        fputc(*(record + i), fdbp);
      fputc('\r', fdbp);
      fputc('\n', fdbp);
      break;
  }
  
  RETURN_STATUS(r);
}


//+---------------------------------------------------------------------------------+
// Sequential files use a constant length for fixed records and a unsigned int prefix                                                       
// for variable records.                                                      
// The variable format is defined by a unsigned int prefix plus the record length.                                                      
// The unsigned int prefix defines the actual length of that variable record.                                                      
//+---------------------------------------------------------------------------------+

/*
//
// Read sequential file
//
*/
int tcob_read_seq(struct file_desc *f, struct fld_desc *rectofrom_desc, char *rectofrom_buf, struct fld_desc *reclen_desc, char *reclen_buf) 
{
  int r=0, rpos=-1;
  
  f->flags.read_done = 0;
  
  /* Check to see if file is open */
  if (f->dbp == NULL) {
      if (f->flags.optional && f->flags.file_missing) 
         RETURN_STATUS(TCB_STATUS_10_END_OF_FILE);        
      RETURN_STATUS(TCB_STATUS_47_INPUT_DENIED);
  }

  /* Check to see that the record length is valid */
  if (f->reclen == -1)
      RETURN_STATUS(TCB_STATUS_99_UNKNOWN);
  
  /* Check the mode the file is opened in to make sure that read
     is Allowed */
  if (((f->open_mode != TCB_FILE_OPEN_MODE_INPUT) && (f->open_mode != TCB_FILE_OPEN_MODE_IO)))
     RETURN_STATUS(TCB_STATUS_47_INPUT_DENIED);
  
  /* Check that we didn't already hit eof */
  if ((f->open_mode == TCB_FILE_OPEN_MODE_INPUT || f->open_mode == TCB_FILE_OPEN_MODE_IO) && f->flags.eof_hit)
     RETURN_STATUS(TCB_STATUS_46_READ_ERROR);
  
#ifdef DEBUG_FILEIO_RTS1
  fprintf(stderr, "debug : tcob_read_seq 0720.060 : f->reclen=%d\n", f->reclen);
#endif                 

  r = tcob_read_rec(f, rectofrom_desc, rectofrom_buf, rpos, reclen_desc, reclen_buf); 

#ifdef DEBUG_FILEIO_RTS1
  fprintf(stderr, "debug : tcob_read_seq 0720.120 : r=%d\n", r);
#endif                 

  if (r == 10) 
     f->flags.eof_hit = 1;
  if (r == 0) 
     f->flags.read_done = 1;

  RETURN_STATUS(r);
}

/*
//
// Read sequential file - NEXT
//
*/
int tcob_read_next_seq(struct file_desc *f, struct fld_desc *rectofrom_desc, char *rectofrom_buf, struct fld_desc *reclen_desc, char *reclen_buf) 
{
  int r=0, rpos=-1;
  
  f->flags.read_done = 0;

  /* Check to see if file is open */
  if (f->dbp == NULL) {
     if (f->flags.optional && f->flags.file_missing) 
        RETURN_STATUS(TCB_STATUS_10_END_OF_FILE);        
     RETURN_STATUS(TCB_STATUS_47_INPUT_DENIED);
  }
  
  /* Check the mode the file is opened in to make sure that read is Allowed */
  if (((f->open_mode != TCB_FILE_OPEN_MODE_INPUT) && (f->open_mode != TCB_FILE_OPEN_MODE_IO)))
     RETURN_STATUS(TCB_STATUS_47_INPUT_DENIED);
  
  /* Check that we didn't already hit eof */
  if ((f->open_mode == TCB_FILE_OPEN_MODE_INPUT || f->open_mode == TCB_FILE_OPEN_MODE_IO) && f->flags.eof_hit)
     RETURN_STATUS(TCB_STATUS_46_READ_ERROR);
  
#ifdef DEBUG_FILEIO_RTS1
  fprintf(stderr, "debug : tcob_read_next_seq 0975.080 : f->reclen=%d\n", f->reclen);
#endif

  r = tcob_read_rec(f, rectofrom_desc, rectofrom_buf, rpos, reclen_desc, reclen_buf); 

#ifdef DEBUG_FILEIO_RTS1
  fprintf(stderr, "debug : tcob_read_next_seq 0975.160 : r=%d\n", r);
#endif

  if (r == 10) 
     f->flags.eof_hit = 1;
  if (r == 0) 
     f->flags.read_done = 1;

  RETURN_STATUS(r);

}

/*
//
// Write sequential file
//
*/
int tcob_write_seq(struct file_desc *f, struct fld_desc *rectofrom_desc, char *rectofrom_buf, struct fld_desc *reclen_desc, char *reclen_buf) 
{
  int rpos=-1, r=0;
        
  f->flags.read_done = 0;
  
  /* Check to see if file is open */
  if (f->dbp == NULL)
     RETURN_STATUS(TCB_STATUS_48_OUTPUT_DENIED);
  
  /* Check to see that the record length is valid */
  if (f->reclen == -1) 
     RETURN_STATUS(TCB_STATUS_48_OUTPUT_DENIED);

#ifdef DEBUG_FILEIO_RTS1
   fprintf(stderr, "debug : tcob_write_seq 0920.080 : f->reclen=%d\n", f->reclen);
#endif
   
   /* Check the mode the file is opened in to make sure that a write is permitted */
   if (((f->open_mode != TCB_FILE_OPEN_MODE_OUTPUT) && 
        /* (f->open_mode != TCB_FILE_OPEN_MODE_IO) && - applies to INDEXED and RELATIVE files only */
        (f->open_mode != TCB_FILE_OPEN_MODE_EXTEND)))
      RETURN_STATUS(TCB_STATUS_48_OUTPUT_DENIED);

   r = tcob_write_rec(f, rectofrom_desc, rectofrom_buf, rpos, reclen_desc, reclen_buf); 
#ifdef DEBUG_FILEIO_RTS1
   fprintf(stderr, "debug : tcob_write_seq 0920.160 : r=%d\n", r);
#endif

   RETURN_STATUS(r);
}

/*
//
// Write sequential file - Advancing
//
*/
int tcob_write_adv_seq(struct file_desc *f, struct fld_desc *rectofrom_desc, char *rectofrom_buf,
                       int opt, 
                       struct fld_desc *cnt_desc, char *cnt_buf, 
                       struct fld_desc *reclen_desc, char *reclen_buf) 
{
  int result, fdbp, reclen, len, lines=0, r=0;
  tcb_fileio_handle *h;
  char *record;

  /* Check to see if file is open */
  if (f->dbp == NULL)
     RETURN_STATUS(TCB_STATUS_48_OUTPUT_DENIED);
  
  /* Check the mode the file is opened in to make sure that write is permitted */
  if (((f->open_mode != TCB_FILE_OPEN_MODE_OUTPUT) && 
       (f->open_mode != TCB_FILE_OPEN_MODE_IO) && 
       (f->open_mode != TCB_FILE_OPEN_MODE_EXTEND)))
     RETURN_STATUS(TCB_STATUS_48_OUTPUT_DENIED);

#ifdef DEBUG_FILEIO_RTS1
  fprintf(stderr, "debug : tcob_write_adv_seq 1090.040 : f->reclen=%d\n", f->reclen); 
#endif     

  h = (tcb_fileio_handle *)f->dbp;
  fdbp = h->uval.fi;
  record = h->buf->buf[0];

  /* Copy write buffer data to record and FROM identifiers buffer */
  if (rectofrom_desc != NULL) {
     memset(f->record, ' ', f->reclen);
     if (rectofrom_desc->len > f->reclen) 
        memcpy(f->record, rectofrom_buf, f->reclen);
     else
        memcpy(f->record, rectofrom_buf, rectofrom_desc->len);
  }
  
  if (opt > 0) 
     lines = tcob_get_index(cnt_desc, cnt_buf);
  
  if (reclen_desc != NULL) {
     tcob_move(reclen_desc, reclen_buf, &_generic_4binary, (char *)&reclen);
     len = reclen;     
  }
  else {
     len = f->reclen;
  }

#ifdef DEBUG_FILEIO_RTS2
  fprintf(stderr, "debug : tcob_write_adv_seq 1090.120 : len=%d\n", len); 
#endif     

  /* Check for buffer overflow */
  reclen = len + lines + 2;
  if (reclen > (f->reclen * 2)) 
     RETURN_STATUS(TCB_STATUS_99_UNKNOWN);
  
  f->flags.with_advancing = 1;
  f->flags.adv_before = 0;

  switch (opt)
  {
    /* 1: write before advancing N lines */
    case TCB_FILE_WRITE_ADVANCING_NLINES_BEFORE:
      memcpy(record, f->record, len);
      if (f->flags.file_printer == 1) {
         memset(record + len, 0x0d, 1);
         memset(record + len + 1, 0x0a, lines);
         reclen = len + lines + 1;
      }
      else {
         memset(record + len, 0x0a, lines);
         reclen = len + lines;
      }
      break;

    /* 2: write after advancing N lines */
    case TCB_FILE_WRITE_ADVANCING_NLINES_AFTER:
      if (f->flags.file_printer == 1) {
          memset(record, 0x0a, lines);
          memcpy(record + lines, f->record, len);
          memset(record + lines + len, 0x0d, 1);
          reclen = len + lines + 1;
      }
      else {
          memset(record, 0x0a, lines);
          memcpy(record + lines, f->record, len);
          reclen = len + lines;
      }
      break;

    /* -1: before advancing page */
    case TCB_FILE_WRITE_ADVANCING_PAGE_BEFORE:
      if (f->flags.file_printer == 1) {
          memcpy(record, f->record, len);
          memset(record + len, 0x0d, 1);            
          memset(record + len + 1, 0x0c, 1);            
          reclen = len + 2;
      }
      else {
          memcpy(record, f->record, len);
          memset(record + len, 0x0c, 1);            
          reclen = len + 1;
      }
      break;

    /* -2: after advancing page */
    case TCB_FILE_WRITE_ADVANCING_PAGE_AFTER:
      if (f->flags.file_printer == 1) {
          memset(record, 0x0d, 1);            
          memset(record + 1, 0x0c, 1);            
          memcpy(record + 2, f->record, len);
          memset(record + len + 2, 0x0d, 1);            
          reclen = len + 3;
      }
      else {
          memset(record, 0x0c, 1);            
          memcpy(record + 1, f->record, len);
          reclen = len + 1;
      }
      break;

    /* only normal write (error?) */
    default:
      r = 99;
      break;
  }

  if (r == 0) {        
            
      /* Variable length record */                  
      if (reclen_desc != NULL) {
         int sreclen;
         unsigned int ureclen;

         sreclen = sizeof(ureclen);
         ureclen = reclen;

         /* Write the record length */
         result = write(fdbp, &ureclen, sreclen);        
#ifdef DEBUG_FILEIO_RTS1
         fprintf(stderr, "debug : tcob_write_adv_seq 1090.240 : result=%d, sreclen=%d, ureclen=%d \n", result, sreclen, ureclen); 
#endif     
         if (result != sreclen)
            RETURN_STATUS(TCB_STATUS_99_UNKNOWN);
      }

      result = write(fdbp, record, reclen);
#ifdef DEBUG_FILEIO_RTS1
      fprintf(stderr, "debug : tcob_write_adv_seq 1090.280 : reclen=%d, result=%d\n", reclen, result);
#endif       
      if (result != reclen)
         RETURN_STATUS(TCB_STATUS_30_PERMANENT_ERROR);
      if (result == -1)
         RETURN_STATUS(TCB_STATUS_99_UNKNOWN);
  
  }

  RETURN_STATUS(r);
}

/*
//
// ReWrite sequential file
//
*/
int tcob_rewrite_seq(struct file_desc *f, struct fld_desc *rectofrom_desc, char *rectofrom_buf, struct fld_desc *reclen_desc, char *reclen_buf) 
{
  int r=0, fdbp, srecpos, result;
  int read_done;
  tcb_fileio_handle *h;
        
  read_done = f->flags.read_done;
  f->flags.read_done = 0;

  /* Check to see if file is open */
  if (f->dbp == NULL)
     RETURN_STATUS(TCB_STATUS_49_I_O_DENIED);

#ifdef DEBUG_FILEIO_RTS1
  fprintf(stderr, "debug : tcob_rewrite_seq 2458.020 : f->reclen=%d;\n", f->reclen); 
#endif     

  /* Check to see that the record length is valid */
  if (f->reclen == -1)
      RETURN_STATUS(TCB_STATUS_99_UNKNOWN);
  
  /* Check the mode the file is opened in to make sure that rewrite permitted */
  if (f->open_mode != TCB_FILE_OPEN_MODE_IO)
     RETURN_STATUS(TCB_STATUS_49_I_O_DENIED);
  
  /* Check that we didn't already hit eof */
  if ((f->open_mode == TCB_FILE_OPEN_MODE_IO) && f->flags.eof_hit)
      RETURN_STATUS(TCB_STATUS_43_READ_NOT_DONE);
  
  /* Check that we had a previous successful read */
  if (!read_done)
      RETURN_STATUS(TCB_STATUS_43_READ_NOT_DONE);
        
#ifdef DEBUG_FILEIO_RTS1
  fprintf(stderr, "debug : tcob_rewrite_seq 2458.040 : f->reclen=%d;\n", f->reclen); 
#endif     

  h = (tcb_fileio_handle *)f->dbp;
  fdbp = h->uval.fi;        

  /* Save current file location */
  result = lseek(fdbp, 0, SEEK_CUR);
#ifdef DEBUG_FILEIO_RTS1
  fprintf(stderr, "debug : tcob_rewrite_seq 2458.060 : result=%d;\n", result);
#endif
  if (result == -1)
     RETURN_STATUS(TCB_STATUS_99_UNKNOWN);
  srecpos = result;

  /* If variable length record check that new and old record length are equal */
  if (reclen_desc != NULL) {
     int reclen, sreclen;
     unsigned int ureclen;

     sreclen = sizeof(ureclen);

     /* Get the new record  record length */
     tcob_move(reclen_desc, reclen_buf, &_generic_4binary, (char *)&reclen);     

     /* Set file location to saved start position */
     result = lseek(fdbp, h->recloc, SEEK_SET);
#ifdef DEBUG_FILEIO_RTS1
     fprintf(stderr, "debug : tcob_rewrite_seq 2458.120 : result=%d\n", result);
#endif                 

     /* Read record length */
     result = read(fdbp, (char *)&ureclen, sreclen);
#ifdef DEBUG_FILEIO_RTS1
     fprintf(stderr, "debug : tcob_rewrite_seq 2458.160 : sreclen=%d, result=%d\n", sreclen, result);
#endif                 
     /* On error try to reset the old file location */
     if (result == 0) {
        result = lseek(fdbp, srecpos, SEEK_SET);
        RETURN_STATUS(TCB_STATUS_10_END_OF_FILE);
     }

#ifdef DEBUG_FILEIO_RTS1
     fprintf(stderr, "debug : tcob_rewrite_seq 2458.180 : reclen=%d, ureclen=%d, f->reclen=%d\n", reclen, ureclen, f->reclen);
#endif                 
     /* On error try to reset the old file location */
     if (reclen != ureclen) {
        result = lseek(fdbp, srecpos, SEEK_SET);
        RETURN_STATUS(TCB_STATUS_44_RECORD_OVERFLOW);
     }
  }
  
  /* Write the new record */
  if (r == 0)
     r = tcob_write_rec(f, rectofrom_desc, rectofrom_buf, h->recloc, reclen_desc, reclen_buf); 
#ifdef DEBUG_FILEIO_RTS1
  fprintf(stderr, "debug : tcob_rewrite_seq 2458.240 : r=%d;\n", r);
#endif

  RETURN_STATUS(r);
}

/*
//
// Read sequential record
//
*/
int tcob_read_rec(struct file_desc *f, struct fld_desc *rectofrom_desc, char *rectofrom_buf, int recpos, struct fld_desc *reclen_desc, char *reclen_buf) 
{
  int result, fdbp, crecpos;
  tcb_fileio_handle *h;
  char *record;
  
  h = (tcb_fileio_handle *)f->dbp;
  fdbp = h->uval.fi;
  record = h->buf->buf[0];
  
  if (recpos > -1)  {
     struct stat stbuf;
     
     result = fstat(fdbp, &stbuf);
     if (result == -1) 
        return (TCB_STATUS_99_UNKNOWN);

     if (stbuf.st_size < recpos) 
        return (TCB_STATUS_99_UNKNOWN);
     
     result = lseek(fdbp, recpos, SEEK_SET);
     if (result == -1) 
        return (TCB_STATUS_23_KEY_NOT_EXISTS);
  }
  
  crecpos = lseek(fdbp, 0, SEEK_CUR);

  // Variable Length Sequential File 
  if (reclen_desc != NULL) {
     int reclen, sreclen;
     unsigned int ureclen;
         
     sreclen = sizeof(ureclen);

     // Read record length 
     result = read(fdbp, (char *)&ureclen, sreclen);
#ifdef DEBUG_FILEIO_RTS1
     fprintf(stderr, "debug : tcob_read_rec 2440.120 : result=%d, sreclen=%d\n", result, sreclen);
#endif                 
     if (result == 0)
        return (TCB_STATUS_10_END_OF_FILE);

     reclen = ureclen;
     tcob_move(&_generic_4binary, (char *)&reclen, reclen_desc, reclen_buf);     

     /* Read data into buffer using the read-in record length */
     result = read(fdbp, record, reclen);
#ifdef DEBUG_FILEIO_RTS1
     fprintf(stderr, "debug : tcob_read_rec 2440.240 : result=%d, reclen=%d\n", result, reclen);
     {
      int i, ilen=reclen;
      fprintf(stderr, "debug : tcob_read_rec 2440.145 : record=");
      for (i=0; i<ilen; i++) {      
         fprintf(stderr, "%c", *(record + i));
      }
      fprintf(stderr, ";\n");
     }
#endif                 
     if (result > f->reclen)
         return (TCB_STATUS_99_UNKNOWN);
     if (result == 0)
         return (TCB_STATUS_10_END_OF_FILE);
     if (result != reclen)
         return (TCB_STATUS_30_PERMANENT_ERROR);

     /* If valid read copy buffer data to record and INTO identifiers buffer */
     memset(f->record, ' ', f->reclen);
     memcpy(f->record, record, reclen);
     if (rectofrom_desc != NULL) {
        memset(rectofrom_buf, ' ', rectofrom_desc->len);
        if (rectofrom_desc->len > reclen) 
           memcpy(rectofrom_buf, record, reclen);
        else
           memcpy(rectofrom_buf, record, rectofrom_desc->len);
     }
     
  }
  else {     
     result = read(fdbp, record, f->reclen);
#ifdef DEBUG_FILEIO_RTS1
     fprintf(stderr, "debug : tcob_read_rec 2440.260 : result=%d, f->reclen=%d\n", result, f->reclen);
#endif                 
     if (result == 0)
        return (TCB_STATUS_10_END_OF_FILE);
     if (result != f->reclen)
        return (TCB_STATUS_30_PERMANENT_ERROR);

     /* If valid read copy buffer data to record and INTO identifiers buffer */
     memcpy(f->record, record, f->reclen);
     if (rectofrom_desc != NULL) {
        memset(rectofrom_buf, ' ', rectofrom_desc->len);
        if (rectofrom_desc->len > f->reclen) 
           memcpy(rectofrom_buf, record, f->reclen);
        else
           memcpy(rectofrom_buf, record, rectofrom_desc->len);
     }
  }

  /* save the record start position */
  h->recloc = crecpos;  

  return (TCB_STATUS_00_SUCCESS);
}

/*
//
// Write sequential record
//
*/
int tcob_write_rec(struct file_desc *f, struct fld_desc *rectofrom_desc, char *rectofrom_buf, int recpos, struct fld_desc *reclen_desc, char *reclen_buf) 
{
  int result, fdbp;
  tcb_fileio_handle *h;
  char * record;

  //fdbp = (int)f->dbp;
  h = (tcb_fileio_handle *)f->dbp;
  fdbp = h->uval.fi;
  record = h->buf->buf[0];

  /* Copy write buffer data to record and FROM identifiers buffer */
  //memcpy(f->record, record, reclen);
  if (rectofrom_desc != NULL) {
     memset(f->record, ' ', f->reclen);
     if (rectofrom_desc->len > f->reclen) 
        memcpy(f->record, rectofrom_buf, f->reclen);
     else
        memcpy(f->record, rectofrom_buf, rectofrom_desc->len);
  }
  memcpy(record, f->record, f->reclen);

  if (recpos > -1)  {
     struct stat stbuf;
     
     result = fstat(fdbp, &stbuf);
     if (result == -1) 
        return (TCB_STATUS_99_UNKNOWN);

     if (stbuf.st_size < recpos) 
        return (TCB_STATUS_99_UNKNOWN);
     
     result = lseek(fdbp, recpos, SEEK_SET);
#ifdef DEBUG_FILEIO_RTS1
  fprintf(stderr, "debug : tcob_write_rec 2490.060 : result=%d, recpos=%d;\n", result, recpos); 
#endif     
     if (result == -1) 
        return (TCB_STATUS_99_UNKNOWN);
  }

#ifdef DEBUG_FILEIO_RTS1
  fprintf(stderr, "debug : tcob_write_rec 2490.080 : h->recloc=%d\n", h->recloc); 
#endif     
  
  /* Variable length record */                  
  if (reclen_desc != NULL) {
     int reclen, sreclen;
     unsigned int ureclen;

     sreclen = sizeof(ureclen);
     /* Convert record to int type */
     tcob_move(reclen_desc, reclen_buf, &_generic_4binary, (char *)&reclen);     
     ureclen = reclen;

     if ((reclen > f->reclen) || (reclen < f->reclen_min))
        return (TCB_STATUS_44_RECORD_OVERFLOW);

#ifdef DEBUG_FILEIO_RTS1
     fprintf(stderr, "debug : tcob_write_rec 2490.120 : ureclen=%d, reclen=%d\n", ureclen, reclen); 
     {
      int i, ilen=reclen;
      fprintf(stderr, "debug : tcob_write_rec 2490.125 : record=");
      for (i=0; i<ilen; i++) {      
         fprintf(stderr, "%c", *(record + i));
      }
      fprintf(stderr, ";\n");
     }
#endif     
        
     /* Write the record length */
     result = write(fdbp, &ureclen, sreclen);        
#ifdef DEBUG_FILEIO_RTS1
     fprintf(stderr, "debug : tcob_write_rec 2490.180 : result=%d, sreclen=%d\n", result, sreclen); 
#endif     
     if (result > f->reclen)
        return (TCB_STATUS_99_UNKNOWN);
     if (result == 0)
        return (TCB_STATUS_10_END_OF_FILE);

     /* Write the record  */
     result = write(fdbp, record, reclen);        
#ifdef DEBUG_FILEIO_RTS1
     fprintf(stderr, "debug : tcob_write_rec 2490.240 : reclen=%d, result=%d\n", reclen, result);
#endif       
     if (result > f->reclen)
        return (TCB_STATUS_99_UNKNOWN);
     if (result == 0)
        return (TCB_STATUS_10_END_OF_FILE);
     if (result != reclen)
        return (TCB_STATUS_30_PERMANENT_ERROR);
  } 
  else {
     result = write(fdbp, record, f->reclen);
#ifdef DEBUG_FILEIO_RTS1
     fprintf(stderr, "debug : tcob_write_rec 2490.280 : f->reclen=%d, result=%d\n", f->reclen, result);
     {
      int i, ilen=f->reclen;
      fprintf(stderr, "debug : tcob_write_rec 2490.285 : record(%d)=", ilen);
      for (i=0; i<ilen; i++) {      
          fprintf(stderr, "%c", *(record + i));
      }
      fprintf(stderr, ";\n");
     }
#endif
     if (result == 0)
        return (TCB_STATUS_99_UNKNOWN);
     if (result != f->reclen)
        return (TCB_STATUS_30_PERMANENT_ERROR);
  }

  return (TCB_STATUS_00_SUCCESS);
}

/* Determine exception code using status code */
/*
//
// Write sequential record
//
*/
int tcob_file_exception_code(struct file_desc *f, int imode, int option)
{
  int r=0, fstatus; 
  
  fstatus = f->file_status[0] - 48;
#ifdef DEBUG_FILEIO_RTS9
  fprintf(stderr, "debug : tcob_file_exception_code 1770.020 : f->file_status[0]=%d,%c, fstatus=%d\n", f->file_status[0], f->file_status[0], fstatus); 
#endif     

  switch (fstatus)
  {
    case TCB_EC_I_O_NONE:
      break;
    
    case TCB_EC_I_O_AT_END:
      if (option == 1) 
         r = 1;
      break;
    
    case TCB_EC_I_O_INVALID_KEY:
      r = 1;
      break;
    
    case TCB_EC_I_O_PERMANENT_ERROR:
      r = 1;
      break;
    
    case TCB_EC_I_O_LOGIC_ERROR:
      r = 1;
      break;
    
    case TCB_EC_I_O_RECORD_OPERATION:
      r = 1;
      break;
    
    case TCB_EC_I_O_FILE_SHARING:
      r = 1;
      break;
    
    case TCB_EC_I_O_IMP:
      r = 1;
      break;
    
    default:
      break;
  }

  if ((r != 0) && (imode != TCB_FILE_OPEN_MODE_NONE))
    r = f->open_mode;
      
#ifdef DEBUG_FILEIO_RTS9
  fprintf(stderr, "debug : tcob_file_exception_code 1770.120 : r=%d\n", r); 
#endif     
  return r;
}

tcb_fileio_handle* tcob_allocate_fhandle(int num, int size)
{
  
  tcb_fileio_handle *h;
  
  h = malloc(sizeof(tcb_fileio_handle));
  if (h == NULL) 
     return (NULL);
 
  h->buf = tcob_allocate_fbuffers(num, size);
  if (h->buf == NULL) {
     free(h);
     return (NULL);
  }

  //h->rfilename = NULL; 
  h->uval.fi = -1;

  return h;
}

void tcob_free_fhandle(tcb_fileio_handle *h)
{
  if (h != NULL) {
     //if (h->rfilename != NULL) 
     //   free(h->rfilename);
     tcob_free_fbuffers(h->buf);
     free(h);
  }
}


tcb_fileio_buffers* tcob_allocate_fbuffers(int num, int size)
{
  int r=0, i;
  tcb_fileio_buffers *w;  

  /* Allocate structure */ 
  w = malloc(sizeof(tcb_fileio_buffers));
  if (w == NULL) 
     return NULL;

  /* Allocate buffers pointers - clean upon allocation failure */ 
  w->buf = malloc(sizeof(char*) * num);
  if (w->buf == NULL) { 
     free(w);
     w = 0;
     return NULL;
  }

  /* Allocate buffers - clean upon allocation failure */ 
  for (i=0; i<num; i++)
     w->buf[i] = malloc(sizeof(char) * size);
  for (i=0; i<num; i++) {
     if (w->buf[i] == NULL)
        r++;
  }
  if (r != 0) { 
     for (i=0; i<num; i++) {
         if (w->buf[i] != NULL)
            free(w->buf[i]);
     }
     free(w);
     w = 0;
     return NULL;
  }
  
  /* Set work to file structure */ 
  w->size = num;

  return w;
}

void tcob_free_fbuffers(tcb_fileio_buffers *b)
{
  int i;
  tcb_fileio_buffers *w;  

  if (b != NULL) { 
     w = b;
     for (i=0; i<w->size; i++) {
        if (w->buf[i] != NULL)
           free(w->buf[i]);
     }
     free(w);
  }
}

/* EOF fileio.c */
