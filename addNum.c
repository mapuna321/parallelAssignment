#include<stdio.h>
#include<omp.h>
#include<stdlib.h>
#include<math.h>
main(int argc , char **argv)
{
  int *arr,*arrM, serial_sum, sum;
  struct timeval tv;
  double start_t,end_t;
  int arr_size, i,j,noOfThreads;
  printf("Enter the size in multiples of two\n");
  scanf("%d",&arr_size);
  noOfThreads=2;
  arr = (int *)malloc(sizeof(int)*arr_size);
  arrM = (int *)malloc(sizeof(int)*arr_size);
  for(j=0;j<arr_size;j++) {
	arr[j] = rand()%100;
  }
  for(j=0;j<arr_size;j++) {
	printf("%d ",arr[j]);
  }
  printf("\n");
  omp_set_num_threads(noOfThreads);
  
  gettimeofday(&tv, 0);
  start_t = (double)tv.tv_sec + (double)tv.tv_usec / 1000000.0;  
  #pragma omp parallel
  {
  int check=arr_size;
  while(check/2>0){
 	 #pragma omp for
  	for(i=0;i<arr_size;i++){
  	arrM[i]=arr[2*i]+arr[2*i+1];
 	}
 	
 	#pragma omp for
 	for(i=0;i<arr_size/2;i++){
 	arr[i]=arrM[i];
 	}
     check=check/2;
  }
  }
   gettimeofday(&tv, 0);
   end_t = (double)tv.tv_sec + (double)tv.tv_usec / 1000000.0;
   printf("Time taken to sum using manual reduction is %lf and sum is %d \n",end_t-start_t,arr[0]);
   
   
}
