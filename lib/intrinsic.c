/* 
 * Copyright (C) 2002, Ferran Pegueroles, 
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
 * TinyCOBOL Run Time Library -- Intrinsic functions
 *

*/

#include "htcoblib.h"
#include "rterrors.h"
#include <stdarg.h>
#ifdef __MINGW32__
#include <process.h>
#endif

//extern int bDecimalComma;
//extern char cCurrencySymbol;

#define NOT_IMPLEMENTED(x)  tcob_rt_error(x,TCB_RTERR_NOT_IMPLEMENTED)

#define decimal_char()	(bDecimalComma?',':'.')

#define MAX_ARG_NUMBER 100

//
//
//  Format for the intrinsic functions : 
//
//  MOVE FUNCTION <NAME> ( <ARGUMENT-1> [,<ARGUMENT-2>,...]) TO <DEST>.
//                           or 
//  MOVE FUNCTION <NAME> TO <DEST>.
//
//  void tcob_intrinsic_<name>( struct fld_desc *dest_desc, char *dest_data,...)
//                             [ struct fld_desc *arg_desc, char *arg_data,... ]  
//
//
//  All the functions accept a variable  number of arguments, but only use the asguments
//  they need. 
//  The first 2 arguments are the only required anr are the destination field.
//  The caller must push a NULL after last argument, so functions can 
//  now how many arguments are passed.
//
//

//
// Util function to convert any numeric field to an integer (similar to tcob_fldtod)
//
void fldtoint(struct fld_desc *desc, char *data,int *res){
	int *num;
	char pic[5];
	struct fld_desc int_desc = {
		4, //len
		DTYPE_BININT, //type
		0, // decimals
		0, //pscale 
		0,0,0,0,0,0, //flags
		NULL //PIC
	};
	tcob_picCreate(pic,5,'S',1,'9',9,NULL);
	int_desc.pic=pic;
	if (desc->type == DTYPE_BININT) {
		num = (int *)data;
		*res=*num;
		return ;
	}
	tcob_move(desc,data,&int_desc,(char *)res);
	
}

//{"ABS",ITYPE_FLOAT,1},
void tcob_intrinsic_abs(struct fld_desc *dest_desc, char *dest_data, ...) {
	va_list ap;
	struct fld_desc *parm_desc;
	char *parm_data;
	double num;
	va_start(ap,dest_data);
	parm_desc = va_arg(ap,struct fld_desc *);
	parm_data = va_arg(ap,char *);
	va_end(ap);
	if ((parm_desc == NULL) || (parm_data == NULL)) {
		tcob_rt_error("ABS",TCB_RTERR_INTRINSIC_BAD_ARG);
	}
	tcob_fldtod(parm_desc,parm_data,&num);
	tcob_dtofld(dest_desc,dest_data,0,fabs(num));
}
//{"ACOS",ITYPE_FLOAT,1},
void tcob_intrinsic_acos(struct fld_desc *dest_desc, char *dest_data, ...) {
	va_list ap;
	struct fld_desc *parm_desc;
	char *parm_data;
	double num;
	va_start(ap,dest_data);
	parm_desc = va_arg(ap,struct fld_desc *);
	parm_data = va_arg(ap,char *);
	va_end(ap);
	if ((parm_desc == NULL) || (parm_data == NULL)) {
		tcob_rt_error("ACOS",TCB_RTERR_INTRINSIC_BAD_ARG);
	}
	tcob_fldtod(parm_desc,parm_data,&num);
	tcob_dtofld(dest_desc,dest_data,0,cos(num));
}
//{"ANNUITY",ITYPE_FLOAT,2},
void tcob_intrinsic_annuity(struct fld_desc *dest_desc, char *dest_data, ...) {
	va_list ap;
	struct fld_desc *parm1_desc,*parm2_desc;
	char *parm1_data,*parm2_data;
	double num1,num2,res;
	va_start(ap,dest_data);
	parm1_desc = va_arg(ap,struct fld_desc *);
	parm1_data = va_arg(ap,char *);
	parm2_desc = va_arg(ap,struct fld_desc *);
	parm2_data = va_arg(ap,char *);
	va_end(ap);
	if ((parm1_desc == NULL) || (parm1_data == NULL) || 
	    (parm2_desc == NULL) || (parm2_data == NULL)) {
		tcob_rt_error("ANNUITY",TCB_RTERR_INTRINSIC_BAD_ARG);
	}
	tcob_fldtod(parm1_desc,parm1_data,&num1);
	tcob_fldtod(parm2_desc,parm2_data,&num2);
	if (num1 == 0) { 
		res = 1/num2;
	}else{ 
		res = (num1 / (1 -  pow((1 - num1),-num2)));
	}	
		
	tcob_dtofld(dest_desc,dest_data,0,res);
}
//{"ASIN",ITYPE_FLOAT,1},
void tcob_intrinsic_asin(struct fld_desc *dest_desc, char *dest_data, ...) {
	va_list ap;
	struct fld_desc *parm_desc;
	char *parm_data;
	double num;
	va_start(ap,dest_data);
	parm_desc = va_arg(ap,struct fld_desc *);
	parm_data = va_arg(ap,char *);
	va_end(ap);
	if ((parm_desc == NULL) || (parm_data == NULL)) {
		tcob_rt_error("ASIN",TCB_RTERR_INTRINSIC_BAD_ARG);
	}
	tcob_fldtod(parm_desc,parm_data,&num);
	tcob_dtofld(dest_desc,dest_data,0,asin(num));
}
//{"ATAN",ITYPE_FLOAT,1}, 
void tcob_intrinsic_atan(struct fld_desc *dest_desc, char *dest_data, ...) {
	va_list ap;
	struct fld_desc *parm_desc;
	char *parm_data;
	double num;
	va_start(ap,dest_data);
	parm_desc = va_arg(ap,struct fld_desc *);
	parm_data = va_arg(ap,char *);
	va_end(ap);
	if ((parm_desc == NULL) || (parm_data == NULL)) {
		tcob_rt_error("ATAN",TCB_RTERR_INTRINSIC_BAD_ARG);
	}
	tcob_fldtod(parm_desc,parm_data,&num);
	tcob_dtofld(dest_desc,dest_data,0,atan(num));
}
//{"CHAR",ITYPE_ALPHA,1}, // inline
//{"COS",ITYPE_FLOAT,1}, 
void tcob_intrinsic_cos(struct fld_desc *dest_desc, char *dest_data, ...) {
	va_list ap;
	struct fld_desc *parm_desc;
	char *parm_data;
	double num;
	va_start(ap,dest_data);
	parm_desc = va_arg(ap,struct fld_desc *);
	parm_data = va_arg(ap,char *);
	va_end(ap);
	if ((parm_desc == NULL) || (parm_data == NULL)) {
		tcob_rt_error("COS",TCB_RTERR_INTRINSIC_BAD_ARG);
	}
	tcob_fldtod(parm_desc,parm_data,&num);
	tcob_dtofld(dest_desc,dest_data,0,cos(num));
}
//{"CURRENT-DATE",ITYPE_DATETIME,0}, 
void tcob_intrinsic_current_date(struct fld_desc *dest_desc, char *dest_data, ...) {
	time_t now;
	char now_str[22];
	now = time(NULL);
	// Needs fix to full positions 15 to 21 (miliseconds and dif between local and Univeral Time)
	strftime(now_str,22,"%Y%m%d%H%M%S0000000",localtime(&now));
	memmove(dest_data,now_str,dest_desc->len);
}
//{"DATE-OF-INTEGER",ITYPE_DATE,1},
void tcob_intrinsic_date_of_integer(struct fld_desc *dest_desc, char *dest_data, ...) {
	va_list ap;
	struct fld_desc *parm_desc;
	char *parm_data, date_str[9];	
	int days;
	struct tm date_tm;
	time_t time;
	
	va_start(ap,dest_data);
	parm_desc = va_arg(ap,struct fld_desc *);
	parm_data = va_arg(ap,char *);
	va_end(ap);
	
	if ((parm_desc == NULL) || (parm_data == NULL)) {
		tcob_rt_error("DATE-OF-INTEGER",TCB_RTERR_INTRINSIC_BAD_ARG);
	}
	
	fldtoint(parm_desc,parm_data,&days);

	// Set the origin of time according to cobol standard
	// 31 Dec 1600
	date_tm.tm_sec=0;         /* seconds */
        date_tm.tm_min=0;         /* minutes */
        date_tm.tm_hour=0;        /* hours */
        date_tm.tm_mday=31;       /* day of the month */
        date_tm.tm_mon=11;        /* month  0 - 11 */
        //date_tm.tm_year= -300;    /* year */ /* the year 1600 */
	// -300 and 0 doesn't work, and by nou we use 1901 instead 
	// of 1600, needs fix 
	date_tm.tm_year=1;        /* year */ 
        date_tm.tm_wday=0;        /* day of the week */
        date_tm.tm_yday=0;        /* day in the year */
        date_tm.tm_isdst=0;       /* daylight saving time */
        // Add the number of days indicated

	date_tm.tm_mday += days;
	
	time = mktime(&date_tm);

	strftime(date_str,9,"%Y%m%d",localtime(&time));
	memmove(dest_data,date_str,dest_desc->len);
}
//{"DATE-TO-YYYYMMDD",ITYPE_DATE,1},
/*
  Needs to get and use an optinal 3rd argument (described on 2002 standard)
*/
void tcob_intrinsic_date_to_yyyymmdd(struct fld_desc *dest_desc, char *dest_data, ...) {
	va_list ap;
	struct fld_desc *parm1_desc,*parm2_desc;
	char *parm1_data, *parm2_data;
	double date,limit=500000;
	
	va_start(ap,dest_data);
	parm1_desc = va_arg(ap,struct fld_desc *);
	parm1_data = va_arg(ap,char *);
	parm2_desc = va_arg(ap,struct fld_desc *);
	parm2_data = va_arg(ap,char *);
	va_end(ap);
	
	if ((parm1_desc == NULL) || (parm1_data == NULL)) {
		tcob_rt_error("DATE-TO-YYYYMMDD",TCB_RTERR_INTRINSIC_BAD_ARG);
	}
	tcob_fldtod(parm1_desc,parm1_data,&date);
	
	if ((parm2_desc != NULL) && (parm2_data != NULL)) {
		tcob_fldtod(parm2_desc,parm2_data,&limit);
		limit *= 10000;
	}
	
        if (date > limit)  
		date += 20000000;
	else
		date += 19000000;
		
	tcob_dtofld(dest_desc,dest_data,0,date);
  
}
//{"DAY-OF-INTEGER",ITYPE_JULIANDATE,1},
void tcob_intrinsic_day_of_integer(struct fld_desc *dest_desc, char *dest_data, ...) {
	va_list ap;
	struct fld_desc *parm_desc;
	char *parm_data, day_str[8];	
	int days;
	struct tm date_tm;
	time_t time;
	
	va_start(ap,dest_data);
	parm_desc = va_arg(ap,struct fld_desc *);
	parm_data = va_arg(ap,char *);
	va_end(ap);
	
	if ((parm_desc == NULL) || (parm_data == NULL)) {
		tcob_rt_error("DAY-OF-INTEGER",TCB_RTERR_INTRINSIC_BAD_ARG);
	}
	
	fldtoint(parm_desc,parm_data,&days);

	// Set the origin of time according to cobol standard
	// 31 Dec 1600
	date_tm.tm_sec=0;         /* seconds */
        date_tm.tm_min=0;         /* minutes */
        date_tm.tm_hour=0;        /* hours */
        date_tm.tm_mday=31;       /* day of the month */
        date_tm.tm_mon=11;        /* month  0 - 11 */
        //date_tm.tm_year= -300;  /* year */ /* the year 1600 */
	// -300 and 0 doesn't work, and by nou we use 1901 instead 
	// of 1600, needs fix 
	date_tm.tm_year=1;        /* year */ 
        date_tm.tm_wday=0;        /* day of the week */
        date_tm.tm_yday=0;        /* day in the year */
        date_tm.tm_isdst=0;       /* daylight saving time */
        // Add the number of days indicated

	date_tm.tm_mday += days;
	
	time = mktime(&date_tm);

	strftime(day_str,8,"%Y%j",localtime(&time));
	memmove(dest_data,day_str,dest_desc->len);
}
//{"DAY-TO-YYYYDDD",ITYPE_JULIANDATE,1},
/*
  Needs to get and use an optinal 3rd argument (described on 2002 standard)
*/
void tcob_intrinsic_day_to_yyyyddd(struct fld_desc *dest_desc, char *dest_data, ...) {
	va_list ap;
	struct fld_desc *parm1_desc,*parm2_desc;
	char *parm1_data, *parm2_data;
	double date,limit=50000;
	
	va_start(ap,dest_data);
	parm1_desc = va_arg(ap,struct fld_desc *);
	parm1_data = va_arg(ap,char *);
	parm2_desc = va_arg(ap,struct fld_desc *);
	parm2_data = va_arg(ap,char *);
	va_end(ap);
	
	if ((parm1_desc == NULL) || (parm1_data == NULL)) {
		tcob_rt_error("DAY-TO-YYYYDDD",TCB_RTERR_INTRINSIC_BAD_ARG);
	}
	tcob_fldtod(parm1_desc,parm1_data,&date);
	
	if ((parm2_desc != NULL) && (parm2_data != NULL)) {
		tcob_fldtod(parm2_desc,parm2_data,&limit);
		limit *= 1000;
	}
	
        if (date > limit)  
		date += 2000000;
	else
		date += 1900000;
		
	tcob_dtofld(dest_desc,dest_data,0,date);
  
}
//{"FACTORIAL",ITYPE_INT,1}, 
static int fact(int num) {
	if (num < 2)  return 1;
	else          return ( fact(num - 1) * num );
}

void tcob_intrinsic_factorial(struct fld_desc *dest_desc, char *dest_data, ...) {
	va_list ap;
	struct fld_desc *parm_desc;
	char *parm_data;
	int num,*dest; 

	va_start(ap,dest_data);
	parm_desc = va_arg(ap,struct fld_desc *);
	parm_data = va_arg(ap,char *);
	va_end(ap);

	if ((parm_desc == NULL) || (parm_data == NULL)) {
		tcob_rt_error("FACTORIAL",TCB_RTERR_INTRINSIC_BAD_ARG);
	}
	dest = (int *)dest_data;
	
	fldtoint(parm_desc,parm_data,&num);
        *dest = fact(num); 	
}
//{"INTEGER",ITYPE_INT,1},
void tcob_intrinsic_integer(struct fld_desc *dest_desc, char *dest_data, ...) {
	va_list ap;
	struct fld_desc *parm_desc;
	char *parm_data;
	int num,*dest; 
	double parm;
	
	va_start(ap,dest_data);
	parm_desc = va_arg(ap,struct fld_desc *);
	parm_data = va_arg(ap,char *);
	va_end(ap);

	if ((parm_desc == NULL) || (parm_data == NULL)) {
		tcob_rt_error("INTEGER",TCB_RTERR_INTRINSIC_BAD_ARG);
	}
	tcob_fldtod(parm_desc,parm_data,&parm);
	fldtoint(parm_desc,parm_data,&num);
        // greatest Integer not greater than parm
	if (num > parm) num = num - 1;
	dest= (int *)dest_data;
	*dest=num;
}
//{"INTEGER-OF-DATE",ITYPE_INT,1}, 
void tcob_intrinsic_integer_of_date(struct fld_desc *dest_desc, char *dest_data, ...) {
	va_list ap;
	struct fld_desc *parm_desc;
	char *parm_data;
	struct tm date_tm,orig;
	int date,day,month,year,*dest; 
	double secs;

	va_start(ap,dest_data);
	parm_desc = va_arg(ap,struct fld_desc *);
	parm_data = va_arg(ap,char *);
	va_end(ap);

	if ((parm_desc == NULL) || (parm_data == NULL)) {
		tcob_rt_error("INTEGER-OF-DATE",TCB_RTERR_INTRINSIC_BAD_ARG);
	}
	
	fldtoint(parm_desc,parm_data,&date);
        // date : yyyymmdd
	
	day=date % 100;
	month=(date / 100) % 100;
	year=date / 10000;
	
	// Set the origin of time according to cobol standard
	// 31 Dec 1600
	orig.tm_sec=0;         /* seconds */
        orig.tm_min=0;         /* minutes */
        orig.tm_hour=0;        /* hours */
        orig.tm_mday=31;       /* day of the month */
        orig.tm_mon=11;        /* month  0 - 11 */
        //date_tm.tm_year= -300;    /* year */ /* the year 1600 */
	// -300 and 0 doesn't work, and by nou we use 1901 instead 
	// of 1600, needs fix 
	orig.tm_year=1;        /* year 0 = 1900*/ 
        orig.tm_wday=0;        /* day of the week */
        orig.tm_yday=0;        /* day in the year */
        orig.tm_isdst=0;       /* daylight saving time */
	
	date_tm.tm_sec=0;         /* seconds */
        date_tm.tm_min=0;         /* minutes */
        date_tm.tm_hour=0;        /* hours */
        date_tm.tm_mday=day;      /* day of the month */
        date_tm.tm_mon=month - 1;        /* month  0 - 11 */
	date_tm.tm_year=year - 1900;     /* year 0 = 1900*/ 
        date_tm.tm_wday=0;        /* day of the week */
        date_tm.tm_yday=0;        /* day in the year */
        date_tm.tm_isdst=0;       /* daylight saving time */
        // Add the number of days indicated
	
	secs = difftime(mktime(&date_tm),mktime(&orig));
	dest=(int *)dest_data;
	*dest=(int) (secs / (60 * 60 * 24)) + 1;
}
//{"INTEGER-OF-DAY",ITYPE_INT,1}, 
void tcob_intrinsic_integer_of_day(struct fld_desc *dest_desc, char *dest_data, ...) {
	va_list ap;
	struct fld_desc *parm_desc;
	char *parm_data;
	struct tm date_tm,orig;
	int date,day,year,*dest; 
	double secs;

	va_start(ap,dest_data);
	parm_desc = va_arg(ap,struct fld_desc *);
	parm_data = va_arg(ap,char *);
	va_end(ap);

	if ((parm_desc == NULL) || (parm_data == NULL)) {
		tcob_rt_error("INTEGER-OF-DAY",TCB_RTERR_INTRINSIC_BAD_ARG);
	}
	
	fldtoint(parm_desc,parm_data,&date);
        // date : yyyyddd
	
	day=date % 1000;
	year=date / 1000;
	
	// Set the origin of time according to cobol standard
	// 31 Dec 1600
	orig.tm_sec=0;         /* seconds */
        orig.tm_min=0;         /* minutes */
        orig.tm_hour=0;        /* hours */
        orig.tm_mday=31;       /* day of the month */
        orig.tm_mon=11;        /* month  0 - 11 */
        //date_tm.tm_year= -300;    /* year */ /* the year 1600 */
	// -300 and 0 doesn't work, and by nou we use 1901 instead 
	// of 1600, needs fix 
	orig.tm_year=1;        /* year 0 = 1900*/ 
        orig.tm_wday=0;        /* day of the week */
        orig.tm_yday=0;        /* day in the year */
        orig.tm_isdst=0;       /* daylight saving time */
	
	date_tm.tm_sec=0;         /* seconds */
        date_tm.tm_min=0;         /* minutes */
        date_tm.tm_hour=0;        /* hours */
        date_tm.tm_mday=day;        /* day of the month */
        date_tm.tm_mon=0;         /* month  0 - 11 */
	date_tm.tm_year=year - 1900;     /* year 0 = 1900*/ 
        date_tm.tm_wday=0;      /* day of the week */
        date_tm.tm_yday=0;        /* day in the year */
        date_tm.tm_isdst=0;       /* daylight saving time */
        // Add the number of days indicated
	
	//fprintf(stderr,"%s\n",ctime(mktime(&orig)));
	secs = difftime(mktime(&date_tm),mktime(&orig));
	dest=(int *)dest_data;
	*dest=(int) (secs / (60 * 60 * 24)) + 1;
}

//{"INTEGER-PART",ITYPE_INT,1}, 
void tcob_intrinsic_integer_part(struct fld_desc *dest_desc, char *dest_data, ...) {
	va_list ap;
	struct fld_desc *parm_desc;
	char *parm_data;
	int num,*dest; 
	double parm;
	
	va_start(ap,dest_data);
	parm_desc = va_arg(ap,struct fld_desc *);
	parm_data = va_arg(ap,char *);
	va_end(ap);

	if ((parm_desc == NULL) || (parm_data == NULL)) {
		tcob_rt_error("INTEGER-PART",TCB_RTERR_INTRINSIC_BAD_ARG);
	}
	tcob_fldtod(parm_desc,parm_data,&parm);
	fldtoint(parm_desc,parm_data,&num);
        // greatest Integer not greater than parm
	if (num > 0){
		if ( num > parm) num--;
	} else {
		if ( num < parm) num++;
	}
	dest= (int *)dest_data;
	*dest=num;
}

//{"LENGTH",ITYPE_INT,1}, // inline
//{"LOG",ITYPE_FLOAT,1},
void tcob_intrinsic_log(struct fld_desc *dest_desc, char *dest_data, ...) {
	va_list ap;
	struct fld_desc *parm_desc;
	char *parm_data;
	double num;
	va_start(ap,dest_data);
	parm_desc = va_arg(ap,struct fld_desc *);
	parm_data = va_arg(ap,char *);
	va_end(ap);
	if ((parm_desc == NULL) || (parm_data == NULL)) {
		tcob_rt_error("LOG",TCB_RTERR_INTRINSIC_BAD_ARG);
	}
	tcob_fldtod(parm_desc,parm_data,&num);
	tcob_dtofld(dest_desc,dest_data,0,log(num));
}

//{"LOG10",ITYPE_FLOAT,1},
void tcob_intrinsic_log10(struct fld_desc *dest_desc, char *dest_data, ...) {
	va_list ap;
	struct fld_desc *parm_desc;
	char *parm_data;
	double num;
	va_start(ap,dest_data);
	parm_desc = va_arg(ap,struct fld_desc *);
	parm_data = va_arg(ap,char *);
	va_end(ap);
	if ((parm_desc == NULL) || (parm_data == NULL)) {
		tcob_rt_error("LOG10",TCB_RTERR_INTRINSIC_BAD_ARG);
	}
	tcob_fldtod(parm_desc,parm_data,&num);
	tcob_dtofld(dest_desc,dest_data,0,log10(num));
}
//{"LOWER-CASE",ITYPE_ALPHA,1},
void tcob_intrinsic_lower_case(struct fld_desc *dest_desc, char *dest_data, ...) {
	va_list ap;
	struct fld_desc *parm_desc;
	char *parm_data;
	int i,max_len;
	va_start(ap,dest_data);
	parm_desc = va_arg(ap,struct fld_desc *);
	parm_data = va_arg(ap,char *);
	va_end(ap);
	if ((parm_desc == NULL) || (parm_data == NULL)) {
		tcob_rt_error("LOWER-CASE",TCB_RTERR_INTRINSIC_BAD_ARG);
	}
	if ((parm_desc->type != DTYPE_ALPHANUMERIC) && 
	    (parm_desc->type != DTYPE_ALPHA) &&
 	    (parm_desc->type != DTYPE_GROUP)) {
		tcob_rt_error("LOWER-CASE",TCB_RTERR_INTRINSIC_BAD_ARG);
	}
	max_len = tc_min(parm_desc->len,dest_desc->len);
	for(i=0;i < max_len;i++){
		dest_data[i]=tolower(parm_data[i]);
	}
	
}
//{"MAX",ITYPE_FLOAT,ANY_NUMBER}, 
void tcob_intrinsic_max(struct fld_desc *dest_desc, char *dest_data, ...) {
	va_list ap;
	struct fld_desc *parm_desc;
	char *parm_data;
	double num,max;
	va_start(ap,dest_data);
	parm_desc = va_arg(ap,struct fld_desc *);
	parm_data = va_arg(ap,char *);
	if ((parm_desc == NULL) || (parm_data == NULL)) { // At leas one argumetn is required
		tcob_rt_error("MAX",TCB_RTERR_INTRINSIC_BAD_ARG);
	}
	tcob_fldtod(parm_desc,parm_data,&max);  // move the first number to the maximum
	while((parm_desc !=NULL) && (parm_data !=NULL)){
		tcob_fldtod(parm_desc,parm_data,&num);
		if (num > max) max=num;
		parm_desc = va_arg(ap,struct fld_desc *);
		parm_data = va_arg(ap,char *);
	}
	
	va_end(ap);
	tcob_dtofld(dest_desc,dest_data,0,max);
}
//{"MEAN",ITYPE_FLOAT,ANY_NUMBER},
void tcob_intrinsic_mean(struct fld_desc *dest_desc, char *dest_data, ...) {
	va_list ap;
	struct fld_desc *parm_desc;
	char *parm_data;
	double num,mean;
	int count;
	va_start(ap,dest_data);
	parm_desc = va_arg(ap,struct fld_desc *);
	parm_data = va_arg(ap,char *);
	if ((parm_desc == NULL) || (parm_data == NULL)) { // At leas one argumetn is required
		tcob_rt_error("MEAN",TCB_RTERR_INTRINSIC_BAD_ARG);
	}
	tcob_fldtod(parm_desc,parm_data,&mean);  // move the first number to the mean
	count = 1;
	while((parm_desc !=NULL) && (parm_data !=NULL)){
		tcob_fldtod(parm_desc,parm_data,&num);
		mean = mean + num;
		count++;
		parm_desc = va_arg(ap,struct fld_desc *);
		parm_data = va_arg(ap,char *);
	}
	mean = mean / count;
	va_end(ap);
	tcob_dtofld(dest_desc,dest_data,0,mean);
}
//{"MEDIAN",ITYPE_FLOAT,ANY_NUMBER},
struct double_list {
	struct double_list *next;
	double num;
};

void tcob_intrinsic_median(struct fld_desc *dest_desc, char *dest_data, ...) {
	va_list ap;
	struct fld_desc *parm_desc;
	char *parm_data;
	double num;
	struct double_list *list;
	struct double_list *item;
	struct double_list *new_item;
	int count,i;
	va_start(ap,dest_data);
	parm_desc = va_arg(ap,struct fld_desc *);
	parm_data = va_arg(ap,char *);
	if ((parm_desc == NULL) || (parm_data == NULL)) { // At leas one argumetn is required
		tcob_rt_error("MEDIAN",TCB_RTERR_INTRINSIC_BAD_ARG);
	}
	tcob_fldtod(parm_desc,parm_data,&num);  // move the first number 
	list=tcob_rt_malloc("MEDIAN",sizeof(struct double_list));
	list->next = NULL;
	list->num = num;
	count = 1;
	while((parm_desc !=NULL) && (parm_data !=NULL)){  //create an ordered list
		tcob_fldtod(parm_desc,parm_data,&num);
		for(item=list;item->next!=NULL;item=item->next)
		{
			if (item->num > num){
				new_item=tcob_rt_malloc("MEDIAN",sizeof(struct double_list));
				new_item->next = item->next;
				new_item->num = num;
				item->next = new_item;
				break;
			}
		}
		count++;
		parm_desc = va_arg(ap,struct fld_desc *);
		parm_data = va_arg(ap,char *);
	}
	// find the element in the middle of list
	for(i=0,item=list;i< count/2;i++,item=item->next) ;
	num = item->num;
	va_end(ap);
	tcob_dtofld(dest_desc,dest_data,0,num);
}

//{"MIDRANGE",ITYPE_FLOAT,ANY_NUMBER},
void tcob_intrinsic_midrange(struct fld_desc *dest_desc, char *dest_data, ...) {
	va_list ap;
	struct fld_desc *parm_desc;
	char *parm_data;
	double num,min,max;
	va_start(ap,dest_data);
	parm_desc = va_arg(ap,struct fld_desc *);
	parm_data = va_arg(ap,char *);
	if ((parm_desc == NULL) || (parm_data == NULL)) { // At leas one argumetn is required
		tcob_rt_error("MIDRANGE",TCB_RTERR_INTRINSIC_BAD_ARG);
	}
	tcob_fldtod(parm_desc,parm_data,&min);  // move the first number to the minimum
	max = min;			   // and to the maximum
	while((parm_desc !=NULL) && (parm_data !=NULL)){
		tcob_fldtod(parm_desc,parm_data,&num);
		if (num < min) min=num;
		if (num > max) max=num;
		parm_desc = va_arg(ap,struct fld_desc *);
		parm_data = va_arg(ap,char *);
	}
	va_end(ap);
	num = (max - min) / 2;
	tcob_dtofld(dest_desc,dest_data,0,num);
}

//{"MIN",ITYPE_FLOAT,ANY_NUMBER},
void tcob_intrinsic_min(struct fld_desc *dest_desc, char *dest_data, ...) {
	va_list ap;
	struct fld_desc *parm_desc;
	char *parm_data;
	double num,min;
	va_start(ap,dest_data);
	parm_desc = va_arg(ap,struct fld_desc *);
	parm_data = va_arg(ap,char *);
	if ((parm_desc == NULL) || (parm_data == NULL)) { // At leas one argumetn is required
		tcob_rt_error("MIN",TCB_RTERR_INTRINSIC_BAD_ARG);
	}
	tcob_fldtod(parm_desc,parm_data,&min);  // move the first number to the minimum
	while((parm_desc !=NULL) && (parm_data !=NULL)){
		tcob_fldtod(parm_desc,parm_data,&num);
		if (num < min) min=num;
		parm_desc = va_arg(ap,struct fld_desc *);
		parm_data = va_arg(ap,char *);
	}
	
	va_end(ap);
	tcob_dtofld(dest_desc,dest_data,0,min);
}
//{"MOD",ITYPE_INT,2}, 
void tcob_intrinsic_mod(struct fld_desc *dest_desc, char *dest_data, ...) {
	va_list ap;
	struct fld_desc *parm_desc;
	char *parm_data;
	int int1,int2;
	int *mod;
	va_start(ap,dest_data);
	parm_desc = va_arg(ap,struct fld_desc *);
	parm_data = va_arg(ap,char *);
	if ((parm_desc == NULL) || (parm_data == NULL)) { // Argument 1
		tcob_rt_error("MOD",TCB_RTERR_INTRINSIC_BAD_ARG);
	}
	fldtoint(parm_desc,parm_data,&int1);  
	parm_desc = va_arg(ap,struct fld_desc *);
	parm_data = va_arg(ap,char *);
	if ((parm_desc == NULL) || (parm_data == NULL)) { // Argument 2
		tcob_rt_error("MOD",TCB_RTERR_INTRINSIC_BAD_ARG);
	}
	fldtoint(parm_desc,parm_data,&int2);  
	va_end(ap);
	mod=(int *)dest_data;
	*mod=int1%int2;
}

/*
 * Parses the string and returns the number that the string represents.
 * Is currency = 1, the string can ccontain currency simbols.
 *
 */
static double parse_numval(char *str,int currency){
	char *p;
	char digits[50];
	int num_digits=0,sign=0;
	double num;

	p=str;
	
	while(isspace((int)*p)) p++;

	if (currency) {
		if (*p == cCurrencySymbol) {
			p++;
			while(isspace((int)*p)) p++;
		}
	}
	
	
	if (*p=='+') { sign = +1; p++; }
	else if (*p=='-') { sign = -1; p++; }
	
	while(isspace((int)*p)) p++;
	
	while(isdigit((int)*p)){
		digits[num_digits]=*p;
		num_digits++;
		p++;
	}
	if (*p == decimal_char()){
		digits[num_digits]='.';
		num_digits++;
		p++;
	}
	while(isdigit((int)*p)){
		digits[num_digits]=*p;
		num_digits++;
		p++;
	}
	while(isspace((int)*p)) p++;

	if (*p=='+') { sign = +1; p++; }
	else if (*p=='-') { sign = -1; p++; }
	else if ( strncasecmp(p,"CR",2) == 0) { sign = -1; p+=2; }
	else if ( strncasecmp(p,"DB",2) == 0) { sign = -1; p+=2; }

	if (currency) {
		if (*p == cCurrencySymbol) {
			p++;
			while(isspace((int)*p)) p++;
		}
	}
	
	digits[num_digits]='\0';
	num  = atof(digits);
	if (sign < 0)
		num = num * -1 ;
	return num;
}
//{"NUMVAL",ITYPE_FLOAT,1},
void tcob_intrinsic_numval(struct fld_desc *dest_desc, char *dest_data, ...) {
	va_list ap;
	struct fld_desc *parm_desc;
	char *parm_data;
	char *str;
	double num;

	va_start(ap,dest_data);
	parm_desc = va_arg(ap,struct fld_desc *);
	parm_data = va_arg(ap,char *);
	if ((parm_desc == NULL) || (parm_data == NULL)) { // Argument 1
		tcob_rt_error("NUMVAL",TCB_RTERR_INTRINSIC_BAD_ARG);
	}
	va_end(ap);
	str = tcob_rt_malloc("NUMVAL",parm_desc->len + 1);
	memmove(str,parm_data,parm_desc->len);
	str[parm_desc->len]='\0';
	
	num = parse_numval(str,0);
	free(str);
	//fprintf(stderr,"str:<%s>digits<%s>n:<%f>\n",str,digits,num);
		
	tcob_dtofld(dest_desc,dest_data,0,num);
}
//{"NUMVAL-C",ITYPE_FLOAT,ANY_NUMBER},
void tcob_intrinsic_numval_c(struct fld_desc *dest_desc, char *dest_data, ...) {
	va_list ap;
	struct fld_desc *parm_desc;
	char *parm_data;
	char *str;
	double num;

	va_start(ap,dest_data);
	parm_desc = va_arg(ap,struct fld_desc *);
	parm_data = va_arg(ap,char *);
	if ((parm_desc == NULL) || (parm_data == NULL)) { // Argument 1
		tcob_rt_error("NUMVAL-C",TCB_RTERR_INTRINSIC_BAD_ARG);
	}
	va_end(ap);
	str = tcob_rt_malloc("NUMVAL-C",parm_desc->len + 1);
	if (str == NULL ){
		//report error
	}
	memmove(str,parm_data,parm_desc->len);
	str[parm_desc->len]='\0';
	
	num = parse_numval(str,1);
	free(str);
	//fprintf(stderr,"str:<%s>digits<%s>n:<%f>\n",str,digits,num);
		
	tcob_dtofld(dest_desc,dest_data,0,num);
}
//{"ORD",ITYPE_INT,1},    // inline
//{"ORD-MAX",ITYPE_INT,ANY_NUMBER},
void tcob_intrinsic_ord_max(struct fld_desc *dest_desc, char *dest_data, ...) {
	va_list ap;
	struct fld_desc *parm_desc;
	char *parm_data;
	double num,max;
	int *ord_max,count;
	ord_max=(int *)dest_data;
	va_start(ap,dest_data);
	parm_desc = va_arg(ap,struct fld_desc *);
	parm_data = va_arg(ap,char *);
	if ((parm_desc == NULL) || (parm_data == NULL)) { // At leas one argumetn is required
		tcob_rt_error("ORD-MAX",TCB_RTERR_INTRINSIC_BAD_ARG);
	}
	tcob_fldtod(parm_desc,parm_data,&max);  // move the first number to the maximum
	count = 1;
	*ord_max = 1;
	while((parm_desc !=NULL) && (parm_data !=NULL)){
		tcob_fldtod(parm_desc,parm_data,&num);
		count++;
		if (num > max) { max=num; *ord_max=count;}
		parm_desc = va_arg(ap,struct fld_desc *);
		parm_data = va_arg(ap,char *);
	}
	va_end(ap);
}
//{"ORD-MIN",ITYPE_INT,ANY_NUMBER},
void tcob_intrinsic_ord_min(struct fld_desc *dest_desc, char *dest_data, ...) {
	va_list ap;
	struct fld_desc *parm_desc;
	char *parm_data;
	double num,min;
	int *ord_min,count;
	ord_min=(int *)dest_data;
	va_start(ap,dest_data);
	parm_desc = va_arg(ap,struct fld_desc *);
	parm_data = va_arg(ap,char *);
	if ((parm_desc == NULL) || (parm_data == NULL)) { // At leas one argumetn is required
		tcob_rt_error("ORD-MIN",TCB_RTERR_INTRINSIC_BAD_ARG);
	}
	tcob_fldtod(parm_desc,parm_data,&min);  // move the first number to the minimum
	count = 1;
	*ord_min = 1;
	while((parm_desc !=NULL) && (parm_data !=NULL)){
		tcob_fldtod(parm_desc,parm_data,&num);
		count++;
		if (num < min) { min=num; *ord_min=count;}
		parm_desc = va_arg(ap,struct fld_desc *);
		parm_data = va_arg(ap,char *);
	}
	va_end(ap);
}
//{"PRESENT-VALUE",ITYPE_FLOAT,ANY_NUMBER},
void tcob_intrinsic_present_value(struct fld_desc *dest_desc, char *dest_data, ...) {
	va_list ap;
	struct fld_desc *parm_desc;
	char *parm_data;
	double args[MAX_ARG_NUMBER]; 
	double res;
	int count,i;
	va_start(ap,dest_data);
	parm_desc = va_arg(ap,struct fld_desc *);
	parm_data = va_arg(ap,char *);
	if ((parm_desc == NULL) || (parm_data == NULL)) { // At leas two arguments are required
		tcob_rt_error("PRESENT-VALUE",TCB_RTERR_INTRINSIC_BAD_ARG);
	}
	tcob_fldtod(parm_desc,parm_data,&args[0]);  // move the first number 
	parm_desc = va_arg(ap,struct fld_desc *);
	parm_data = va_arg(ap,char *);
	count = 1;
	while((parm_desc !=NULL) && (parm_data !=NULL)){
		tcob_fldtod(parm_desc,parm_data,&args[count]);
		count++;
		parm_desc = va_arg(ap,struct fld_desc *);
		parm_data = va_arg(ap,char *);
	}
	va_end(ap);
	if (count < 2) { // At leas two arguments are required
		tcob_rt_error("PRESENT-VALUE",TCB_RTERR_INTRINSIC_BAD_ARG);
	}
	for(i = 1;i< count;i++) {
		res = res + ( args[i] / pow( 1 + args[0],i));
	}
	tcob_dtofld(dest_desc,dest_data,0,res);
}
//{"RANDOM",ITYPE_FLOAT,1},
void tcob_intrinsic_random(struct fld_desc *dest_desc, char *dest_data, ...) {
	va_list ap;
	struct fld_desc *parm_desc;
	char *parm_data;
	int seed;
	va_start(ap,dest_data);
	parm_desc = va_arg(ap,struct fld_desc *);
	parm_data = va_arg(ap,char *);
	if ((parm_desc != NULL) && (parm_data != NULL)) { // If an argument is speciufied is the seed
		fldtoint(parm_desc,parm_data,&seed);  // move the seed
		srand(seed);
	}
	tcob_dtofld(dest_desc,dest_data,0,rand());
}
//{"RANGE",ITYPE_FLOAT,ANY_NUMBER},
void tcob_intrinsic_range(struct fld_desc *dest_desc, char *dest_data, ...) {
	va_list ap;
	struct fld_desc *parm_desc;
	char *parm_data;
	double min,max,num;
	va_start(ap,dest_data);
	parm_desc = va_arg(ap,struct fld_desc *);
	parm_data = va_arg(ap,char *);
	if ((parm_desc == NULL) || (parm_data == NULL)) { // At leas one argumetn is required
		tcob_rt_error("RANGE",TCB_RTERR_INTRINSIC_BAD_ARG);
	}
	tcob_fldtod(parm_desc,parm_data,&min);  // move the first number to the minimum
	max = min;			   // and to the maximum
	while((parm_desc !=NULL) && (parm_data !=NULL)){
		tcob_fldtod(parm_desc,parm_data,&num);
		if (num < min) min=num;
		if (num > max) max=num;
		parm_desc = va_arg(ap,struct fld_desc *);
		parm_data = va_arg(ap,char *);
	}
	va_end(ap);
	tcob_dtofld(dest_desc,dest_data,0,(max - min));
}
//{"REM",ITYPE_INT,2},
void tcob_intrinsic_rem(struct fld_desc *dest_desc, char *dest_data, ...) {
	va_list ap;
	struct fld_desc *parm_desc;
	char *parm_data;
	int int1,int2,div;
	int *res;
	va_start(ap,dest_data);
	parm_desc = va_arg(ap,struct fld_desc *);
	parm_data = va_arg(ap,char *);
	if ((parm_desc == NULL) || (parm_data == NULL)) { // 2 arguments required
		tcob_rt_error("REM",TCB_RTERR_INTRINSIC_BAD_ARG);
	}
	fldtoint(parm_desc,parm_data,&int1);  
	parm_desc = va_arg(ap,struct fld_desc *);
	parm_data = va_arg(ap,char *);
	if ((parm_desc == NULL) || (parm_data == NULL)) { // 2 arguments required
		tcob_rt_error("REM",TCB_RTERR_INTRINSIC_BAD_ARG);
	}
	fldtoint(parm_desc,parm_data,&int2);  
	va_end(ap);
	res=(int *)dest_data;
	div = int1 / int2;
	*res=int1 - int2*div;
}
//{"REVERSE",ITYPE_ALPHA,1},
void tcob_intrinsic_reverse(struct fld_desc *dest_desc, char *dest_data, ...) {
	va_list ap;
	struct fld_desc *parm_desc;
	char *parm_data;
	int i,max_len;
	va_start(ap,dest_data);
	parm_desc = va_arg(ap,struct fld_desc *);
	parm_data = va_arg(ap,char *);
	va_end(ap);
	if ((parm_desc == NULL) || (parm_data == NULL)) {
		tcob_rt_error("REVERSE",TCB_RTERR_INTRINSIC_BAD_ARG);
	}
	if ((parm_desc->type != DTYPE_ALPHANUMERIC) && 
	    (parm_desc->type != DTYPE_ALPHA) &&
 	    (parm_desc->type != DTYPE_GROUP)) {
		tcob_rt_error("REVERSE",TCB_RTERR_INTRINSIC_BAD_ARG);
	}
	max_len = tc_min(parm_desc->len,dest_desc->len);
	for(i=0;i < max_len;i++){
		dest_data[i]=parm_data[parm_desc->len - i];
	}
	
}
//{"SIN",ITYPE_FLOAT,1},
void tcob_intrinsic_sin(struct fld_desc *dest_desc, char *dest_data, ...) {
	va_list ap;
	struct fld_desc *parm_desc;
	char *parm_data;
	double num;
	va_start(ap,dest_data);
	parm_desc = va_arg(ap,struct fld_desc *);
	parm_data = va_arg(ap,char *);
	va_end(ap);
	if ((parm_desc == NULL) || (parm_data == NULL)) {
		tcob_rt_error("SIN",TCB_RTERR_INTRINSIC_BAD_ARG);
	}
	tcob_fldtod(parm_desc,parm_data,&num);
	tcob_dtofld(dest_desc,dest_data,0,sin(num));
}
//{"SQRT",ITYPE_FLOAT,1}, 
void tcob_intrinsic_sqrt(struct fld_desc *dest_desc, char *dest_data, ...) {
	va_list ap;
	struct fld_desc *parm_desc;
	char *parm_data;
	double num;
	va_start(ap,dest_data);
	parm_desc = va_arg(ap,struct fld_desc *);
	parm_data = va_arg(ap,char *);
	va_end(ap);
	if ((parm_desc == NULL) || (parm_data == NULL)) {
		tcob_rt_error("SQRT",TCB_RTERR_INTRINSIC_BAD_ARG);
	}
	tcob_fldtod(parm_desc,parm_data,&num);
	tcob_dtofld(dest_desc,dest_data,0,sqrt(num));
}
//{"STANDARD-DEVIATION",ITYPE_FLOAT,ANY_NUMBER},
void tcob_intrinsic_standard_deviation(struct fld_desc *dest_desc, char *dest_data, ...) {
	va_list ap;
	struct fld_desc *parm_desc;
	char *parm_data;
	double args[MAX_ARG_NUMBER]; 
	double mean;
	double res;
	int i,count;
	va_start(ap,dest_data);
	parm_desc = va_arg(ap,struct fld_desc *);
	parm_data = va_arg(ap,char *);
	if ((parm_desc == NULL) || (parm_data == NULL)) { // At leas one argumetn is required
		tcob_rt_error("STANDARD-DEVIATION",TCB_RTERR_INTRINSIC_BAD_ARG);
	}
	count=1;
	tcob_fldtod(parm_desc,parm_data,&args[0]);  // move the first number
	while((parm_desc !=NULL) && (parm_data !=NULL)){
		tcob_fldtod(parm_desc,parm_data,&args[count]);
		count ++;
		parm_desc = va_arg(ap,struct fld_desc *);
		parm_data = va_arg(ap,char *);
	}
	va_end(ap);
	// calculate the mean;
	mean=0;
	for(i=0;i<count;i++){
		mean=mean+args[i];
	}
	mean=mean/count;
	res=0;
	for(i=0;i<count;i++){
		res=res +pow(fabs(mean - args[i]),2);
	}
	res=sqrt(res / count);	
	tcob_dtofld(dest_desc,dest_data,0,res);
}
//{"SUM",ITYPE_FLOAT,ANY_NUMBER},
void tcob_intrinsic_sum(struct fld_desc *dest_desc, char *dest_data, ...) {
	va_list ap;
	struct fld_desc *parm_desc;
	char *parm_data;
	double res,num;
	va_start(ap,dest_data);
	parm_desc = va_arg(ap,struct fld_desc *);
	parm_data = va_arg(ap,char *);
	if ((parm_desc == NULL) || (parm_data == NULL)) { // At leas one argumetn is required
		tcob_rt_error("SUM",TCB_RTERR_INTRINSIC_BAD_ARG);
	}
	tcob_fldtod(parm_desc,parm_data,&res);  // move the first number
	while((parm_desc !=NULL) && (parm_data !=NULL)){
		tcob_fldtod(parm_desc,parm_data,&num);
		res+=num;
		parm_desc = va_arg(ap,struct fld_desc *);
		parm_data = va_arg(ap,char *);
	}
	va_end(ap);
	tcob_dtofld(dest_desc,dest_data,0,res);
}
//{"TAN",ITYPE_FLOAT,1}, 
void tcob_intrinsic_tan(struct fld_desc *dest_desc, char *dest_data, ...) {
	va_list ap;
	struct fld_desc *parm_desc;
	char *parm_data;
	double num;
	va_start(ap,dest_data);
	parm_desc = va_arg(ap,struct fld_desc *);
	parm_data = va_arg(ap,char *);
	va_end(ap);
	if ((parm_desc == NULL) || (parm_data == NULL)) {
		tcob_rt_error("TAN",TCB_RTERR_INTRINSIC_BAD_ARG);
	}
	tcob_fldtod(parm_desc,parm_data,&num);
	tcob_dtofld(dest_desc,dest_data,0,tan(num));
}
//{"TEST-DATE-YYYYMMDD",ITYPE_INT,1},
void tcob_intrinsic_test_date_yyyymmdd(struct fld_desc *dest_desc, char *dest_data, ...) {
	va_list ap;
	struct fld_desc *parm_desc;
	char *parm_data;
	int *res;
	int date,day,month,year;
	
	va_start(ap,dest_data);
	parm_desc = va_arg(ap,struct fld_desc *);
	parm_data = va_arg(ap,char *);
	va_end(ap);
	
	if ((parm_desc == NULL) || (parm_data == NULL)) {
		tcob_rt_error("TEST-DATE-YYYYMMDD",TCB_RTERR_INTRINSIC_BAD_ARG);
	}
	fldtoint(parm_desc,parm_data,&date);
	
	day=date % 100;
	month=(date / 100) % 100;
	year=date / 10000;
		
	res=(int *)dest_data;
	if ((year < 1600) || (year > 9999)){
		*res=1;
		return;
	}
	if ((month < 1) || (month > 12)){
		*res=1;
		return;
	}
	switch(month){
		case 2:
			if (day > 29) {
				*res=1;
				return;
			}
			break;
		case 4:
		case 6:
		case 9:	
		case 11:	
			if (day > 29) {
				*res=1;
				return;
			}
			break;
		default:
			if (day > 31) {
				*res=1;
				return;
			}
			break;
	}
	*res=0;	
	
}
//{"TEST-DAY-YYYYDDD",ITYPE_INT,1},
void tcob_intrinsic_test_day_yyyyddd(struct fld_desc *dest_desc, char *dest_data, ...) {
	va_list ap;
	struct fld_desc *parm_desc;
	char *parm_data;
	int *res;
	int date,day,year;
	
	va_start(ap,dest_data);
	parm_desc = va_arg(ap,struct fld_desc *);
	parm_data = va_arg(ap,char *);
	va_end(ap);
	
	if ((parm_desc == NULL) || (parm_data == NULL)) {
		tcob_rt_error("TEST-DAY-YYYYDDD",TCB_RTERR_INTRINSIC_BAD_ARG);
	}
	fldtoint(parm_desc,parm_data,&date);
	
	day=date % 1000;
	year=date / 1000;
		
	res=(int *)dest_data;
	if ((year < 1600) || (year > 9999)){
		*res=1;
		return;
	}
	if ((day < 1) || (day > 366)){
		*res=1;
		return;
	}
	*res=0;	
	
}

//{"UPPER-CASE",ITYPE_ALPHA,1},
void tcob_intrinsic_upper_case(struct fld_desc *dest_desc, char *dest_data, ...) {
	va_list ap;
	struct fld_desc *parm_desc;
	char *parm_data;
	int i,max_len;
	va_start(ap,dest_data);
	parm_desc = va_arg(ap,struct fld_desc *);
	parm_data = va_arg(ap,char *);
	va_end(ap);
	if ((parm_desc == NULL) || (parm_data == NULL)) {
		tcob_rt_error("UPPER-CASE",TCB_RTERR_INTRINSIC_BAD_ARG);
	}
	if ((parm_desc->type != DTYPE_ALPHANUMERIC) && 
	    (parm_desc->type != DTYPE_ALPHA) &&
 	    (parm_desc->type != DTYPE_GROUP)) {
		tcob_rt_error("UPPER-CASE",TCB_RTERR_INTRINSIC_BAD_ARG);
	}
	max_len = tc_min(parm_desc->len,dest_desc->len);
	for(i=0;i < max_len;i++){
		dest_data[i]=toupper(parm_data[i]);
	}
}
//{"VARIANCE",ITYPE_FLOAT,ANY_NUMBER},
void tcob_intrinsic_variance(struct fld_desc *dest_desc, char *dest_data, ...) {
	va_list ap;
	struct fld_desc *parm_desc;
	char *parm_data;
	double args[MAX_ARG_NUMBER]; 
	double mean;
	double res;
	int i,count;
	va_start(ap,dest_data);
	parm_desc = va_arg(ap,struct fld_desc *);
	parm_data = va_arg(ap,char *);
	if ((parm_desc == NULL) || (parm_data == NULL)) { // At leas one argumetn is required
		tcob_rt_error("VARIANCE",TCB_RTERR_INTRINSIC_BAD_ARG);
	}
	count=1;
	tcob_fldtod(parm_desc,parm_data,&args[0]);  // move the first number
	while((parm_desc !=NULL) && (parm_data !=NULL)){
		tcob_fldtod(parm_desc,parm_data,&args[count]);
		count ++;
		parm_desc = va_arg(ap,struct fld_desc *);
		parm_data = va_arg(ap,char *);
	}
	va_end(ap);
	// calculate the mean;
	mean=0;
	for(i=0;i<count;i++){
		mean=mean+args[i];
	}
	mean=mean/count;
	res=0;
	for(i=0;i<count;i++){
		res=res +pow(fabs(mean - args[i]),2);
	}
	res=res / count;	
	tcob_dtofld(dest_desc,dest_data,0,res);
}

//{"WHEN-COMPILED",ITYPE_DATETIME}, //inline
//{"YEAR-TO-YYYY",ITYPE_YEAR},
void tcob_intrinsic_year_to_yyyy(struct fld_desc *dest_desc, char *dest_data, ...) {
	va_list ap;
	struct fld_desc *parm1_desc,*parm2_desc;
	char *parm1_data, *parm2_data;
	int limit=50;
	double year;
	
	va_start(ap,dest_data);
	parm1_desc = va_arg(ap,struct fld_desc *);
	parm1_data = va_arg(ap,char *);
	parm2_desc = va_arg(ap,struct fld_desc *);
	parm2_data = va_arg(ap,char *);
	va_end(ap);
	
	if ((parm1_desc == NULL) || (parm1_data == NULL)) {
		tcob_rt_error("YEAR-TO-YYYY",TCB_RTERR_INTRINSIC_BAD_ARG);
	}
	tcob_fldtod(parm1_desc,parm1_data,&year);
	
	if ((parm2_desc != NULL) && (parm2_data != NULL)) {
		fldtoint(parm2_desc,parm2_data,&limit);
	}
	if (year < 100) {
		if (year > limit) { 
			year += 2000;
		} else {
			year += 1900;
		}
	}
	tcob_dtofld(dest_desc,dest_data,0,year);
  
}
