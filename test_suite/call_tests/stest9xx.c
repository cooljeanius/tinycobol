#include <stdio.h>

#define EC(n) WS_COB.ws_char3[n]
struct {
   int ws_b4;
   short ws_b2;
   char ws_char3[3];
} WS_COB;

void STEST901(char *s) {
	printf("C901:(%20s):(ABCDEFGHIJ0123456789):Call by ref from variable\n", s);
}
void STEST902(int v) {
	printf("C902:(%d):(3):Call by value from variable\n", v);
}
void STEST903(int v) {
	printf("C903:(%d):(5):Call by value from literal\n", v);
}
void STEST904(char * p1, int p2, int p3, char *p4, char *p5) {
	printf("C904:(%3s,%d,%d,%3s,%3s):(XYZ,3,5,XYZ,123):Call modes alternance\n",
	p1, p2, p3, p4, p5);
}
void STEST905(long long v) {
	printf("C905:(%13lld):(1234567890123):Call by value long long literal\n", v);
}
void STEST906(long long v) {
	printf("C906:(%13lld):(1234567890123):Call by value long long var\n", v);
}
short STEST907(long v) {
	return v+3;
}
int STEST908(long v) {
	return v+3;
}
long long STEST909(long v) {
	return v+3;
}
void STEST910(char *s1, char *s2, char *s3, char *s4) {
	printf("C910:(%4s%4s%4s%4s):(ABCD0123EFGH4567):Call by ref and content in alternance\n", s1, s2, s3, s4);
	s1[2]='9'; s2[2]='9'; s3[2]='9';s4[2]='9';
}
void STEST930() {
	EC(0) = 'E'; EC(1) = 'U'; EC(2) = 'R';
	WS_COB.ws_b2++;
	WS_COB.ws_b4++;
	printf("C930:(%c%c%c%04d%04d):(EUR12356790):Received in EXTERNAL from Cobol\n", EC(0), EC(1), EC(2), WS_COB.ws_b2, WS_COB.ws_b4);
}
