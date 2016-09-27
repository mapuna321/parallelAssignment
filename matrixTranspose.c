#include<stdio.h>
#include<omp.h>
#include<stdlib.h>
#include<math.h>
main(int argc , char **argv)
{
  int **arrR,**arrT;
  struct timeval tv;
  double start_t,end_t;
  int arr_size, i,j,noOfThreads;
  printf("Enter the size of square Matrix\n");
  scanf("%d",&arr_size);
  noOfThreads=2;
  arrT = (int **)malloc(sizeof(int*)*arr_size);
  arrR = (int **)malloc(sizeof(int*)*arr_size);
  
  for(j=0;j<arr_size;j++) {
	arrR[j] = (int *)malloc(sizeof(int)*arr_size);
	arrT[j] = (int *)malloc(sizeof(int)*arr_size);
  }
  
  for(i=0;i<arr_size;i++){
  	for(j=0;j<arr_size;j++){
  		arrR[i][j]=rand()%10;
  	}
  }
  printf("Matrix is \n");
  for(i=0;i<arr_size;i++){
  	for(j=0;j<arr_size;j++){
  		printf("%d ",arrR[i][j]);
  	}
  	printf("\n");
  }
  
  omp_set_num_threads(noOfThreads);
  
  gettimeofday(&tv, 0);
  start_t = (double)tv.tv_sec + (double)tv.tv_usec / 1000000.0;  
  #pragma omp parallel for collapse(2)
  for(i=0;i<arr_size;i++){
  	for(j=0;j<arr_size;j++){
  		arrT[j][i]=arrR[i][j];
  	}
  }
  
  gettimeofday(&tv, 0);
   end_t = (double)tv.tv_sec + (double)tv.tv_usec / 1000000.0;
  
  printf("Output is\n");
  for(i=0;i<arr_size;i++){
  	for(j=0;j<arr_size;j++){
  		printf("%d ",arrT[i][j]);
  	}
  	printf("\n");
  }
   
   printf("\nTime taken for transposing is %lf  \n",end_t-start_t);
   
}
