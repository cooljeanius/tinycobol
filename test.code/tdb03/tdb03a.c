/* test program for libpq (postgresql) */

#include <stdio.h>
#include <stdlib.h>

#include <libpq-fe.h>

void
do_exit(PGconn *conn) {
	PQfinish(conn);
	exit(1);
};

/* this function assumes a command buffer of 80 characters */
void 
sql_exec_query( int *dbhandle, char *query, int *qryhandle, int *status ) {
	char *r,*s=query;
	int nfields, i, j;
	PGconn *conn = (PGconn *)*dbhandle;
	PGresult *res;

	res = PQexec(conn, query);
	*status = PQresultStatus(res);
	*qryhandle = (int) res;
}

void
sql_status_message( int *dbhandle, char *message ) {
	PGconn *conn = (PGconn *)*dbhandle;
	char *s;
	s = PQerrorMessage(conn);
	while (*s) {
		*message++ = *s++;
	}
}

void
sql_max_tuple( int *qryhandle, int *maxtuple ) {
	*maxtuple = PQntuples((PGresult *)*qryhandle);
}

void
sql_max_field( int *qryhandle, int *maxfield ) {
	*maxfield = PQnfields((PGresult *)*qryhandle);
}

void
sql_get_value( int *qryhandle, int *ntuple, int *nfield, char *value ) {
	char *s;
	s = PQgetvalue((PGresult *)*qryhandle,*ntuple,*nfield);
	while (*s) {
		if (*s == '\n') continue;
		*value++ = *s++;
	}
}

void
sql_get_tuple( int *qryhandle, int *ntuple, char *tuple ) {
	char *s;
	int nfield=0;
	int maxfield = PQnfields((PGresult *)*qryhandle);
	while (nfield < maxfield) {
		s = PQgetvalue((PGresult *)*qryhandle,*ntuple,nfield);
		while (*s) {
			*tuple++ = *s++;
		}
		nfield++;
	}
}

void
sql_clear_query( int *qryhandle ) {
	PQclear((PGresult *)*qryhandle);
}

void
sql_connect_db( char *dbname, int *dbhandle, int *status ) {
	PGconn *conn;
	char db[81];
	char *s;
	/* trim right spaces on the buffer */
	memmove(db,dbname,80);
	db[80]=0;
	s = db+79;
	while ((s >= db) && (*s == ' ')) s--;
	if (s >= db) 
		*(s+1)=0;
	conn = PQsetdb("","","","",db);
	*status = PQstatus(conn);
	*dbhandle = (int)conn;
}

void
sql_disconnect_db( int *dbhandle ) {
	PGconn *conn = (PGconn *)*dbhandle;
	PQfinish(conn);
}

