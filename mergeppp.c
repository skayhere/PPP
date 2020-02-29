#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#define CHUNK_TH 10000 

void merge(int a[], int l, int m, int r)
{
	int temp[m-l+1], temp2[r-m];

	for(int i=0; i<(m-l+1); i++)
		temp[i]=a[l+i];

	for(int i=0; i<(r-m); i++)
		temp2[i]=a[m+1+i];
	int i=0, j=0, k=l;

	while(i<(m-l+1) && j<(r-m))
	{
		if(temp[i]<temp2[j])
			a[k++]=temp[i++];
		else
			a[k++]=temp2[j++];
	}

	while(i<(m-l+1))
		a[k++]=temp[i++];
	while(j<(r-m))
		a[k++]=temp2[j++];

}

void mergeSort(int a[], int l, int r)
{
	if(l<r)
	{
		int m=(l+r)/2;
		#pragma omp parallel sections num_threads(2)
		{
			#pragma omp section
			{
				mergeSort(a,l,m); //call 1
			}
			#pragma omp section
			{
				mergeSort(a,m+1,r); //call 2
			}
		}
		merge(a,l,m,r);  
	}
}
int main()
{
	int len;
	printf("Enter number of elements to sort : ");
	scanf("%d",&len);
	int arr[len];// = {0};
	//printf("Enter %d elements : \n",len);
	for(int i=0; i<len; i++)
		//scanf("%d",&arr[i]);
		arr[i]=rand();
	omp_set_num_threads(2);
        long start, end;
        struct timeval timecheck;
        gettimeofday(&timecheck, NULL);
        start = (long)timecheck.tv_sec * 1000 + (long)timecheck.tv_usec / 1000;


    
	mergeSort(arr,0,len-1);
        gettimeofday(&timecheck, NULL);
        end = (long)timecheck.tv_sec * 1000 + (long)timecheck.tv_usec / 1000;
        printf("%ld milliseconds elapsed\n", (end - start));
        for (int i = 0; i < len; i++){
	  	printf("%d ", arr[i]);
	  }
	  printf("\n");
	return 0;
}
