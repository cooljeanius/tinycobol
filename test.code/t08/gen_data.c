#include <stdlib.h>
#include <stdio.h>
int main()
{
	int r=0;
	int key;
	int key1;
	char lines[21]="aaaaaaaaaaaaaaaaaaa";
	char lines1[38]="ddddddddddddddddddddddddddddddddddddd";
	long int i;
	for (i=0;i<10000;i++)
	{
		key=1+(int) (999.0*rand()/(RAND_MAX+1.0)); 
		key1=1+(int) (999.0*rand()/(RAND_MAX+1.0)); 
		printf("%3i%20s%3i%37s",key,lines,key1,lines1);
	}
	return r;
}
