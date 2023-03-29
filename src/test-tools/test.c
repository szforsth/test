#include <stdio.h>
#include "test.h"



int test(int argc, char *argv[])
{
	printf("argc=%d\n",argc);
	while(argc--)
	{
		printf("argv:%s\n",argv[argc]);
	}
	return 0;
}
