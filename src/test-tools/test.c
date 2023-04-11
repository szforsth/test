#include <stdio.h>
#include "test.h"

#define MAX_LEN 10

void print_args(int argc, char *argv[])
{
	log_mesg(LOG_DEBUG, 0, 1, 0, "argc=%d\n", argc);
	while(argc--)
	{
		log_mesg(LOG_DEBUG, 0, 1, 0, "argv:%s\n",argv[argc]);
	}
}

void init_rand(int *p)
{
	int i = 0;
	for(i=0;i<MAX_LEN;i++)
	{
		p[i] = rand()%100;
	}

}

void print_rand(int *p)
{
	int i=0;
	for(i=0;i<MAX_LEN;i++)
		printf("%-4d",p[i]);
	 printf("\n");
}

void sort_1(int *p)
{
	int i,j;
	for(i=0;i<MAX_LEN;i++)
	{
		for(j=i+1;j<MAX_LEN;j++)
		{
			if(p[i]>p[j])
			{
				int tmp = p[i];
				p[i] = p[j];
				p[j] = tmp;
			}
		}
	}
	
}

void sort_2(int *p)
{
	int i,j,key;
	for(i=1;i<MAX_LEN;i++)
	{
		key = p[i];
		for(j=i-1;j>=0;j--)
		{
			if(p[j]>key)
				p[j+1] = p[j];
			else
				break;
		}
		p[j+1] = key;
	}
}

int test(int argc, char *argv[])
{
	print_args(argc, argv);
	srand(time(NULL));
	int arr[MAX_LEN] = {0};
	init_rand(arr);
	print_rand(arr);
	sort_1(arr);
	print_rand(arr);
	init_rand(arr);
	print_rand(arr);
	sort_2(arr);
	print_rand(arr);
	return 0;
}
