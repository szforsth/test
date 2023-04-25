#include <stdio.h>
#include "test.h"

#define MAX_LEN 10
#define MAX_SORT 4

void bubble_sort(int *p, int left, int right);
void insert_sort(int *p, int left, int right);
void quick_sort(int *p, int left, int right);
void select_sort(int *p, int left, int right);
void (*sort[MAX_SORT])(int *p, int left, int right) = {bubble_sort,insert_sort,quick_sort,select_sort};

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

void quick_sort(int *p, int left, int right)
{
	if(left >= right)
		return;
	int i=left,j=right;
	int key = p[i];
	while(i<j)
	{
		while(i<j && p[j]>key)
			j--;
		if(i<j)
			p[i++] = p[j];
		while(i<j && p[i]<key)
			i++;
		if(i<j)
			p[j--] = p[i];
	}
	p[i] = key;
	quick_sort(p, left, i-1);
	quick_sort(p, j+1, right);
}

void bubble_sort(int *p, int left, int right)
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

void select_sort(int *p, int left, int right)
{
	int i,j;
	for(i=0;i<MAX_LEN-1;i++)
	{
		int min = i;
		for(j=i+1;j<MAX_LEN;j++)
		{
			if(p[min] > p[j])
				min = j;
		}
		if(min != i)
		{
			int tmp = p[i];
			p[i] = p[min];
			p[min] = tmp;
		}
	}
}

void insert_sort(int *p, int left, int right)
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
	int i;
	for(i=0;i<MAX_SORT;i++)
	{
		init_rand(arr);
		print_rand(arr);
		sort[i](arr,0,MAX_LEN-1);
		print_rand(arr);
		printf("======================================\n");
	}
	return 0;
}
