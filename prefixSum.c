#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

int *arr;
int **arrF;
int **arrR;

void prefixSum(int n){
   int h,i;
    struct timeval tv;
    double start_t,end_t;
    
   int t1 =n+1;
   #pragma omp parallel
   {   
     #pragma omp for
      for(i=1;i<t1;i++)
      {
	arrF[0][i]=arr[i];
      }
   }
    
    gettimeofday(&tv, 0);
    start_t = (double)tv.tv_sec + (double)tv.tv_usec / 1000000.0; 
    int j;
    for(h=1;h<=((int)(log2(n))+1);h++)
    {
        int t =n/(int)pow(2,h);
		#pragma omp parallel
		{   
		#pragma omp for
		for(j=1;j<=t;j++)
		{
	int i1=omp_get_thread_num();

	
		    arrF[h][j]=arrF[h-1][(2*j)-1] + arrF[h-1][(2*j)];
		}
		}
	
    }
    
         for(h=((int)log2(n)+1);h>=0;h--)
    {
        int t =n/(int)pow(2,h);
	#pragma omp parallel
	{   
	#pragma omp for
		for(j=1;j<=t;j++)
		{
		    if((j%2)==0)
		    {
		        arrR[h][j] = arrR[h+1][j/2];
		    }
		    else if(j==1)
		    {
		        arrR[h][1]= arrF[h][1];
		    }
		    else
		    {
		        arrR[h][j] = arrR[h+1][(j-1)/2] + arrF[h][j];
		    }
		}
	}	
    }
    gettimeofday(&tv, 0);
    end_t = (double)tv.tv_sec + (double)tv.tv_usec / 1000000.0;
    printf("\n time taken is %lf output is \n",(end_t-start_t));


}

int main()
{
    int n,h,i;
    struct timeval tv;
    double start_t,end_t;
    printf("Enter size in multiple of 2\n");
    scanf("%d",&n);
    arr = (int *)malloc((n+1) * sizeof(int));
    int rows =(int)(log2(n));
    rows= rows+1;
    arrF = (int **)malloc(rows * sizeof(int *));
    arrR = (int **)malloc(rows * sizeof(int *));
    for (i=0; i<rows; i++)
    {
       arrF[i] = (int *)malloc((n+1) * sizeof(int));
	arrR[i] = (int *)malloc((n+1) * sizeof(int));
    }
	omp_set_num_threads(4);
	int t1 =n+1;
  
	 for(i=1;i<t1;i++)
	    {
		arr[i]=rand()%100;
	    }
	    printf("Input array is\n");
	    for(i=1;i<t1;i++)
	    {
		printf("%d ",arr[i]);
	    }
	    printf("\n");
	prefixSum(n);
	
	for(i=1;i<=n;i++)
	    {
		printf("%d ",arrR[0][i]);
	    }
	

    return 0;
}
