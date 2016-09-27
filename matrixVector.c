#include<stdio.h>
#include<omp.h>
#include<stdlib.h>
#include<math.h>
main(int argc , char **argv)
{
  int *arr,*arrM;
  int **arrR;
  struct timeval tv;
  double start_t,end_t;
  int arr_size, i,j,noOfThreads,col;
  printf("Enter the size of vector and no. of columns\n");
  scanf("%d %d",&arr_size,&col);
  noOfThreads=2;
  arr = (int *)malloc(sizeof(int)*arr_size);
  arrM = (int *)calloc(col,sizeof(int));
  arrR = (int **)malloc(sizeof(int*)*col);
  
  for(j=0;j<col;j++) {
	arrR[j] = (int *)malloc(sizeof(int)*arr_size);;
  }
  
  for(i=0;i<col;i++){
  	for(j=0;j<arr_size;j++){
  		arrR[i][j]=rand()%10;
  	}
  }
  for(j=0;j<arr_size;j++){
  	arr[j]=rand()%10;
  }
  
  printf("Matrix is \n");
  for(i=0;i<col;i++){
  	for(j=0;j<arr_size;j++){
  		printf("%d ",arrR[i][j]);
  	}
  	printf("\n");
  }
  printf("Vector is \n");
  for(j=0;j<arr_size;j++){
  	printf("%d ",arr[j]);
  }
  printf("\n");
  omp_set_num_threads(noOfThreads);
  
  gettimeofday(&tv, 0);
  start_t = (double)tv.tv_sec + (double)tv.tv_usec / 1000000.0;  
  #pragma omp parallel for collapse(2)
  for(i=0;i<col;i++){
  	for(j=0;j<arr_size;j++){
  		arrM[i]=arrM[i]+arrR[i][j]*arr[j];
  	}
  }
  
  gettimeofday(&tv, 0);
   end_t = (double)tv.tv_sec + (double)tv.tv_usec / 1000000.0;
  
  printf("Output is\n");
  for(j=0;j<col;j++){
  	printf("%d ",arrM[j]);
  }
   
   printf("\nTime taken for multiplication is %lf  \n",end_t-start_t);
   
}
