/* test program for libdb */

#include <sys/param.h>
#include <sys/stat.h>

#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Setup BDB includes */
#include "htconfig.h" 
#include "fileiodb.h"
/*
#ifdef USE_DB
#include <db.h>
#else
#include <db_185.h>
#endif
*/

//#define db_open dbopen

DBTYPE typedat = DB_RECNO;  /* Database types */
DBTYPE typendx = DB_BTREE;
int oflags = O_CREAT | O_RDWR;
int sflags = S_IRUSR | S_IWUSR; 
u_int flags=0;
//DB *dbpdat,*dbpndx;
DB *dbpndx;
int dbpdat;

int tcdb_open(char *filename, int *reclen, char *record)
{
  int r=0;
  char tmp[120];
  DBT data, key;
  
  strcpy(tmp, filename);
  strcat(tmp, ".dat");
  dbpdat = open(tmp, oflags, sflags);
//  dbpdat = db_open(tmp, oflags, sflags, type, infop);
  strcpy(tmp, filename);
  strcat(tmp, ".ndx");
  dbpndx = dbopen(tmp, oflags, sflags, typendx, NULL);
  
  return r;
}

int tcdb_close()
{
   int r=0;
   
   close(dbpdat);
   dbpndx->close(dbpndx);
   
   return r;
}

/* 
 * write a data record with two indexes
 */
int tcdb_put2( int *record_len, char *record, int *ndx1_len, char *ndx1,
        int *ndx2_len, char *ndx2)
{
  int r=0;
  DBT data, key;
  char sel;
  int recno;
  int retcode;
  int offset;
  char tmp[1024]; /* what is the maximum key size? */
  
  offset = lseek(dbpdat,0,SEEK_END);
  write(dbpdat,record,*record_len);
  recno = offset / *record_len;
  
  tmp[0]=0+'A'; /* first index */
  strncpy(tmp+1,ndx1,*ndx1_len);
  key.data = tmp;
  key.size = *ndx1_len+1;
  data.data = &recno;
  data.size = sizeof(int);
  dbpndx->put(dbpndx,&key,&data,flags);

  tmp[0]=1+'A'; /* second index */
  strncpy(tmp+1,ndx2,*ndx2_len);
  key.data = tmp;
  key.size = *ndx2_len+1;
  data.data = &recno;
  data.size = sizeof(int);
  retcode = dbpndx->put(dbpndx,&key,&data,flags);
  //printf("put retcode: %d\n",retcode);
  return r;
}

/*
  retrieve the data record, given a index 
  sel = 1 or 2 for the first or second index
*/
int tcdb_qry( int *index_sel, int *ndx_len, char *ndx, 
        int *record_len, char *record ) 
{
  int r=0;
  DBT data, key;
  char tmp[1024]; /* what is the maximum key size? */
  int retcode;
  
  tmp[0]=*index_sel+'A'; 
  strncpy(tmp+1,ndx,*ndx_len);
  key.data = tmp;
  key.size = *ndx_len+1;
  retcode = dbpndx->get(dbpndx,&key,&data,flags);
  //printf("qry retcode: %d\n",retcode);
  if (retcode == 0) {
          //printf("record number: %d\n",*(int*)(data.data));
          lseek(dbpdat,*(int*)(data.data)*(*record_len),SEEK_SET);
          read(dbpdat,record,*record_len);
  }
  return r;
}

