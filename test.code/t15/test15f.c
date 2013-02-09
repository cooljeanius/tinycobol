/*    
 *  test15f.c  
 *
 *  Sample C program called from COBOL main-program (test15e.cob).
 *
 *  Bernard Giroud       August 2000
*/

#include <stdio.h>

void  STEST901(char *s);
void  STEST902(int v, short s, long long ll);
void  STEST903(int v);
void  STEST904(char * p1, int p2, int p3, char *p4, char *p5);
void  STEST905(long long v);
void  STEST906(long long v);
short STEST907(short v);
int   STEST908(short v);
long long STEST909(unsigned short v);
void  STEST910(char *s1, char *s2, char *s3, char *s4);

/* -------------------- */

void STEST901(char *s) {
     printf("sub  (test15f) C901:(%20s):(ABCDEFGHIJ0123456789):Call by ref from variable\n", s);
}

void STEST902(int v, short s, long long ll) {
//void STEST902(int v) {
     printf("sub  (test15f) C902   input: (%d:3):(%d:5):(%lld:6666666666): Call by value from variable\n", 
            v, s, ll
            );
     v  = 33;
     s  = 55;
     ll = 66;
     printf("sub  (test15f) C902 changed: (%d:33):(%d:55):(%lld:66): Call by value from variable\n", 
            v, s, ll
            );
}

void STEST903(int v) {
     printf("sub  (test15f) C903:(%d):(5):Call by value from literal\n", v);
}

void STEST904(char * p1, int p2, int p3, char *p4, char *p5) {
     printf("sub  (test15f) C904:(%3s,%d,%d,%3s,%3s):(XYZ,3,5,XYZ,123):Call alternating modes\n",
     p1, p2, p3, p4, p5);
     p2 = 6;
     p3 = 4;
     printf("sub  (test15f) C904:(%3s,%d,%d,%3s,%3s):(XYZ,6,4,XYZ,123):Call alternating modes\n",
     p1, p2, p3, p4, p5);
}

void STEST905(long long v) {
     printf("sub  (test15f - C905): Call by value long long literal: (%13lld=1234567890123)\n", v);
     v = v - 3;
     printf("sub  (test15f - C905): Call by value long long literal: (%13lld=1234567890120)\n", v);
}

void STEST906(long long v) {
     printf("sub  (test15f - C906): Call by value long long literal :(%13lld=1234567890123)\n", v);
     v = v - 3;
     printf("sub  (test15f - C906): Call by value long long literal :(%13lld=1234567890120)\n", v);
}

short STEST907(short v) {
     short r = v + 133; 
     printf("sub  (test15f - C907): Call by value short :(%3d=5) returning short :(%3d=138)\n", v, r);
     v = v - 3;
     printf("sub  (test15f - C907): Call by value short :(%3d=5) returning short :(%3d=138)\n", v, r);
     return r;
}

int STEST908(short v) {
     int r = v + 133; 
     printf("sub  (test15f - C908): Call by value short :(%3d=5) returning int :(%3d=138)\n", v, r);
     v = v - 3;
     printf("sub  (test15f - C908): Call by value short :(%3d=2) returning int :(%3d=138)\n", v, r);
     return r;
}

long long STEST909(unsigned short v) {
     long long r = v + 133; 
     printf("sub  (test15f - C909): Call by value short :(%3d=5) returning long long :(%3lld=138)\n", v, r);
     v = v - 3;
     printf("sub  (test15f - C909): Call by value short :(%3d=2) returning long long :(%3lld=138)\n", v, r);
     return r;
}

void STEST910(char *s1, char *s2, char *s3, char *s4) {
	printf("sub  (test15f - C910): Alternate calls (reference content reference content):  input=(%4s%4s%4s%4s)\n", s1, s2, s3, s4);
	s1[2]='9'; s2[2]='9'; s3[2]='9';s4[2]='9';
	printf("sub  (test15f - C910): Alternate calls (reference content reference content): output=(%4s%4s%4s%4s)\n", s1, s2, s3, s4);
}
